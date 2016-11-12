//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZNProcureMng.h"
#include "NoteCode.h"
#include "QryNoteCodeForm.h"
#include "SetNotesForm.h"
#include "mytrace.h"
#include "SelectCustomerForm.h"
#include "RecMoneyForm.h"
#include "SelectCatalogForm.h"
#include "..\supplier\detailemessage.h"
#include "bookup.h"
#include "selectbook.h"
#include "fenleitype.h"
#include "Addsyslog.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzDBCmbo"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzDBGrid"
#pragma link "RzDBLbl"
#pragma link "RzCommon"
#pragma link "RzDBLook"
#pragma link "RzRadGrp"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TfrmZNProcureMng *frmZNProcureMng;
//---------------------------------------------------------------------------
__fastcall TfrmZNProcureMng::TfrmZNProcureMng(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_catalogSearchMode(0)
	, m_bsmode(BSUnknown)
	, m_opmode(OPUnknown)
	, m_supplierID(-1)
{
	m_module = MTPur;
	this->WindowState = wsMaximized ;
	findagain = 0;
}
//---------------------------------------------------------------------------
void TfrmZNProcureMng::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	m_storageID = li->storageID ;
	lblOpName->Caption = m_opName;
	cmdAddNtHeader->Connection = m_con;
	spQryNtHeader->Connection = m_con;
	spQryNtHeader1->Connection = m_con;
	cmdUpdateNtHeader->Connection = m_con;
	cmdAddNote->Connection = m_con;
	cmdUpdateNote->Connection = m_con;
	cmdDelNote->Connection = m_con;
	cmdDelNtHeader->Connection = m_con;
	cmdBatchDelNote->Connection = m_con;
	cmdBatchUpdateNote->Connection = m_con;
	cmdResetNtHeader->Connection = m_con;
	spQryNtHeader1->Connection = m_con;
	cmdDelNote->Connection = m_con;
	dsetStaff->Connection = m_con;
	dsetBkstack->Connection = m_con;
	query->Connection = m_con;
	comfenlei->Connection = m_con;
	dsetBkstack->Active = true;
	dsetStaff->Active = true;
	bearsaledataset->Connection = m_con;
	bearsaledataset->Active = true;
	dsetStaff->Connection = m_con;
	ChangeCatalogSearchMode();
	chckbxSwitch->Checked = false;
	ChangeBsmode(BSNote);
	ChangeOpmode(OPAddNtHeader);
	addnotereturnvalue = 0;
	Sbutfirst->Enabled = false;
	Sbutbefore->Enabled = false;
	Sbutnext->Enabled = false;
	Sbutend->Enabled = false;
	AnsiString sql;
	sql = "select * from sys_bsset where name = 'znprocurefindpwd'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	findpwd = query->FieldByName("Value")->AsBoolean ;
	sql = "select * from sys_bsset where name = 'znprocuredeletepwd'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	deletepwd = query->FieldByName("Value")->AsBoolean ;

	sql = "select ID,Name from SYS_StorageInfo where id = " + IntToStr(m_storageID);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	Edit1->Text = query->FieldByName("ID")->AsString;
	Edit2->Text = query->FieldByName("Name")->AsString ;
}

void __fastcall TfrmZNProcureMng::FormClose(TObject *Sender, TCloseAction &Action)
{
    DelInvalidNtHeader();
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	dsetStaff->Active = false;
	dsetBkstack->Active = false;
	TfrmMDIChild::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::tlbtn1Click(TObject *Sender)
{
	//删除
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con)
	{
		ChangeOpmode(con->Tag);
	}

}
//---------------------------------------------------------------------------


void __fastcall TfrmZNProcureMng::tlbtn7Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}
	//
	if (Key == '\r')
	{
		if (!dsetNote->Active || !dsetNtHeader->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;
		
		if (edtCatalog->Text == "")
		{
			ChangeCatalogSearchMode();
		}
		else
		{

            findagain = 0;
			AnsiString sql,sqlwhere,SearchCont = edtCatalog->Text;
			sql = " select BS_BookCatalog.ID,BS_BookCatalog.Author,STK_BookInfo.ID as bkinfoid,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.fullname,STK_BookstackInfo.Name as BKStName,STK_BookstackInfo.ID as BSKID "
				  " from BS_BookCatalog  join STK_BookInfo on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
				  " left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
				  " left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
				  " left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
				  " where   BS_BookCatalog.Unavailable=1 and STK_BookstackInfo.StgID = " + IntToStr(m_storageID) ;
				switch (m_catalogSearchMode)
				{
				case 1://条码

					if (SearchCont.Length()==10 ) {
						SearchCont = SearchCont.Delete(10,1);
						SearchCont = SearchCont + "%";
						sqlwhere = "  and BS_BookCatalog.ISBN like '" + SearchCont + "'";
					}else if (SearchCont.Length()==9) {
						SearchCont = SearchCont + "%";
						sqlwhere = sqlwhere + "  and BS_BookCatalog.ISBN like '" + SearchCont + "'";
					}
					else if (SearchCont.Length()==13) {
						SearchCont = SearchCont.Delete(13,1);
						SearchCont = SearchCont + "%";
						sqlwhere = sqlwhere + "  and BS_BookCatalog.Barcode like '" + SearchCont + "'";
					}else if (SearchCont.Length()==12) {
						SearchCont = SearchCont + "%";
						sqlwhere = sqlwhere + "  and BS_BookCatalog.Barcode like '" + SearchCont + "'";
					}else
					{
						sqlwhere = sqlwhere + "  and BS_BookCatalog.Barcode = '" + SearchCont + "'";
					}
					break;
				case 2://自编码
					sqlwhere = "  and BS_BookCatalog.UserDefCode like '%" + SearchCont + "%'";
					break;
				case 3://书名
					sqlwhere = sqlwhere +  " and  BS_BookCatalog.Name like '%" + SearchCont + "%'";
					break;
				case 6://定价
					sqlwhere = sqlwhere +  " and BS_BookCatalog.price=" + SearchCont;
					break;
				default:
					break;
				}
				TLocateOptions   Opts;
				Opts.Clear();
				Opts   <<   loPartialKey;
				sql = sql + sqlwhere;
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->Open();
				if (query->RecordCount == 1) {
					String   str   = query->FieldByName("ID")->AsString;
					if (!dsetNote->Locate("BkcatalogID",str,Opts)) {
                    	if (AddNote(query->FieldByName("SupplierID")->AsInteger,query->FieldByName("ID")->AsInteger))
						{
							Perform(WM_NEXTDLGCTL, 0, 0);
						}
						else
						{
						}
					}
					else
					{
						dbgrdNote->SelectedRows->CurrentRowSelected = true;
						dbgrdNote->SetFocus();
						dbnbedtAmount->SetFocus();
					}

				}
				else if (query->RecordCount > 1) {
					//新from
					Tfrmfindbook *frm = new Tfrmfindbook(Application,query,findagain);
					frm->ZNProcurefrm = this;
					frm->DoModalType = 1;
					if (mrOk == frm->ShowModal() ) {
						if (frm->SelectAll) {
							query->First();
							while (!query->Eof )
							{
								if (AddNote(query->FieldByName("SupplierID")->AsInteger,query->FieldByName("ID")->AsInteger))
								{
									Perform(WM_NEXTDLGCTL, 0, 0);
								}
								else
								{
								}
								query->Next();
							}
						}
						else
						{
                            String   str   = query->FieldByName("ID")->AsString;
							if (!dsetNote->Locate("BkcatalogID",str,Opts)){
								if (AddNote(query->FieldByName("SupplierID")->AsInteger,query->FieldByName("ID")->AsInteger))
								{
									Perform(WM_NEXTDLGCTL, 0, 0);
								}
								else
								{
								}
							}
							else
							{
                            	dbgrdNote->SelectedRows->CurrentRowSelected = true;
								dbgrdNote->SetFocus();
								dbnbedtAmount->SetFocus();
							}

						}
					}
					delete frm;
				}
				else
				{
                    findagain = 1;
					sql = "select BS_BookCatalog.ID,BS_BookCatalog.Author,BS_BookCatalog.Name,BS_BookCatalog.Barcode,BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,BS_BookCatalog.Price ,BS_PressInfo.fullname "
							" from BS_BookCatalog left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
							 " where   BS_BookCatalog.Unavailable=1" ;
					sql = sql +  sqlwhere;
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					if (query->RecordCount == 1) {
						String   str   = query->FieldByName("ID")->AsString;
						if ( !dsetNote->Locate("BkcatalogID",str,Opts))
						{
							if (AddNote(-1,query->FieldByName("ID")->AsInteger))
							{
								Perform(WM_NEXTDLGCTL, 0, 0);
							}
							else
							{
							}
						}
						else
						{
							dbgrdNote->SelectedRows->CurrentRowSelected = true;
							dbgrdNote->SetFocus();
							dbnbedtAmount->SetFocus();
						}
					}
					else if (query->RecordCount > 1) {
						//新from
						Tfrmfindbook *frm = new Tfrmfindbook(Application,query,findagain);
						frm->ZNProcurefrm = this;
						frm->DoModalType = 1;
						if (mrOk == frm->ShowModal() ) {
							if (frm->SelectAll) {
								query->First();
								while (!query->Eof )
								{
									if (AddNote(-1,query->FieldByName("ID")->AsInteger))
									{
										Perform(WM_NEXTDLGCTL, 0, 0);
									}
									else
									{
									}
									query->Next();
								}
							}
							else
							{
								String   str   = query->FieldByName("ID")->AsString;
								if (!dsetNote->Locate("BkcatalogID",str,Opts)) {
                                	if (AddNote(-1,query->FieldByName("ID")->AsInteger))
									{
										Perform(WM_NEXTDLGCTL, 0, 0);
									}
									else
									{
									}
								}
								else
								{
                                	dbgrdNote->SelectedRows->CurrentRowSelected = true;
									dbgrdNote->SetFocus();
									dbnbedtAmount->SetFocus();
								}
							}
						}
						delete frm;
					}
					else
					{
					}
				}
		}
	}
}
//---------------------------------------------------------------------------

void TfrmZNProcureMng::ChangeCatalogSearchMode()
{
if (m_catalogSearchMode==3) {
		m_catalogSearchMode=6;
	}else
	{
	m_catalogSearchMode++;  }
	if (m_catalogSearchMode >= 7)
	{
		m_catalogSearchMode = 1;
	}

	switch (m_catalogSearchMode)
	{
	case 1:
		edtCatalog->MaxLength = 13;
		lblCatalog->Caption = "书 号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "自编码";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "书  名";
		break;
	case 6:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "定 价";
		break;
    default:
        break;
	}
}

void TfrmZNProcureMng::ChangeBsmode(BSMode bsmode)
{
	if (bsmode != m_bsmode)
	{
        m_bsmode = bsmode;
    }

	if (m_bsmode == BSNote)
	{
	  //	grpbxNtHeader->Caption = "采购信息";
	  //	grpbxNote->Caption = "图书采购信息";
		Label2->Caption = "智 能 采 购 单";
		mniBsNote->Checked = true;
		mniBsNoteSendback->Checked = false;
	}
	else if (m_bsmode == BSNoteSendback)
	{
	   //	grpbxNtHeader->Caption = "采购撤消单信息";
	  //	grpbxNote->Caption = "图书采购撤消单信息";
		Label2->Caption = "采 购 撤 消 单";
		mniBsNote->Checked = false;
		mniBsNoteSendback->Checked = true;
	}
}

void TfrmZNProcureMng::ChangeOpmode(OPMode opmode)
{
	if (opmode == m_opmode
		&& (opmode == OPDelNtHeader))
		return;

	//1为查单模式 2为添加单头模式 3为删除单头模式 4为添加单模式 5为删除单模式 6为统一模式 7为现场收款模式
	switch (opmode)
	{
	case OPFind:
		{
			if (findpwd) {
            	if (!CheckOperateAuthority())
					return;
			}

			TfrmQryNoteCode* frm = new TfrmQryNoteCode(this,0);
			LandInfo li;
			li.app = m_app;
			li.con = m_con;
			li.userID = m_userID;
			li.storageID = m_storageID;
			frm->Init(&li);
			if (frm->ShowModal() == mrOk)
			{
            	DelInvalidNtHeader();
				edtCatalog->Text = "";
				String code = frm->GetNoteCode();
				try
				{
					//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
					QryNtHeader(code);
					cbstate->ItemIndex = dsetNtHeader->FieldByName("state")->AsInteger ;
					String sql,codetmp;
					codetmp = code;
					if (codetmp != "") {
						codetmp = codetmp.SubString(0,10);
						int codenext = StrToInt(codetmp) + 1;
						sql = "select ProcureNtCode from BS_ProcureNoteHeader where ProcureNtCode >= " +  codetmp + "00000 and ProcureNtCode < " + IntToStr(codenext) + "00000";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->Open();
						query->Last();
						codetmp = query->FieldByName("ProcureNtCode")->AsString ;
					}
					MaxNote = codetmp;
				}
				__finally
				{
					//LockWindowUpdate(NULL);
				}
			}
			m_opmode = opmode;
			delete frm;
        }
		break;
	case OPAddNtHeader:
		{
			//如果上次是添加模式，并且没有加进任何数据，则不能添加
			if (m_opmode == OPAddNtHeader &&
				dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			if (m_opmode == OPDelNote
				&& dsetNote->Active && dsetNote->RecordCount < 1)
				return;
			edtCatalog->Text = "";
			AddNtHeader();
			m_opmode = opmode;
        }
		break;
	case OPDelNtHeader:
		{
			if (!CheckOperateAuthority())
				return;

			edtCatalog->Text = "";
//			DelNtHeader();
			m_opmode = opmode;
        }
		break;
	case OPAddNote:
    	edtCatalog->Text = "";
		edtCatalog->SetFocus();
		m_opmode = opmode;
		break;
	case OPDelNote:
		if (deletepwd) {
        	if (!CheckOperateAuthority())
				return;
		}
		else
		{
        	if (MessageBoxA(0,"是否要删除该条记录?","询问",MB_ICONQUESTION|MB_OKCANCEL)!=1 )
					return;
		}

		DelNote();
		ResetNtHeader();
    	m_opmode = opmode;
		break;
	case OPSetNotes:
    	if (dsetNote->Active && dsetNote->RecordCount >= 1)
		{
			//统一模式
			if (dbgrdNote->SelectedRows->Count == 0 || dbgrdNote->SelectedRows->Count == 1) {
            	for (int i = 1; i <= dsetNote->RecordCount ; i++) {
					dbgrdNote->DataSource->DataSet->RecNo = i;
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
				}
			}
			TfrmSetNotes* frm = new TfrmSetNotes(this);
			frm->ChangeBsmode(m_bsmode);
			if (frm->ShowModal() == mrOk)
			{
				int amount = 0;
				float discount = 0;
				bool bsetAmount = frm->GetAmount(amount);
				bool bsetDiscount = frm->GetDiscount(discount);
				if (bsetAmount && bsetDiscount)
				{
					BatchSetNotes(amount, discount, 1);
				}
				else if (bsetAmount && !bsetDiscount)
				{
					BatchSetNotes(amount, discount, 2);
				}
				else if (!bsetAmount && bsetDiscount)
				{
                	BatchSetNotes(amount, discount, 3);
				}
				else
				{

                }
			}
			delete frm;
			m_opmode = opmode;
        }
		break;
	case OPRecCash:
		//现场收款模式
	 /*	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
		{
			//首先把修改的更新一下哈
			dbgrdNote->SetFocus();
			//其次把最新数据刷新一下哈
			QryNtHeader();
			//
			TfrmRecMoney* frm = new TfrmRecMoney(this);
			frm->SetDiscountedPrice(dsetNtHeader->FieldByName("DiscountedPrice")->AsFloat);
			frm->SetChecked(dsetNtHeader->FieldByName("Checked")->AsFloat);
			if (mrOk == frm->ShowModal())
			{
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("Checked")->AsFloat =
					dsetNtHeader->FieldByName("Checked")->AsFloat + frm->GetReceived();
				UpdateNtHeader();
			}
			delete frm;
		}
    	m_opmode = opmode;
		break;*/
    default:
        break;
	}
	try {
		NtCodeChange();
	} catch (...) {
	}
}

void TfrmZNProcureMng::BatchSetNotes(int amount, float discount, int mode)
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
    	String ids = "";
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			ids = ids + dsetNote->FieldByName("ID")->AsString;
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = dsetNote->FieldByName("ID")->AsString;
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
			}
		}
		else
			return;

		switch(mode)
		{
		case 1://两者均更新
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 6;
			cmdBatchUpdateNote->Execute();
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader();
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			break;
		case 2://只更新Amount
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = "";
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 6;
			cmdBatchUpdateNote->Execute();
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader();
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			break;
		case 3://只更新Discount
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = "";
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 6;
			cmdBatchUpdateNote->Execute();
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader();
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			break;
		default:
			break;
		}
	}
}

void __fastcall TfrmZNProcureMng::mniBsNoteSendbackClick(TObject *Sender)
{
	//添加单据类型
	TMenuItem* item = dynamic_cast<TMenuItem*>(Sender);
	if (item != NULL)
	{
		if (item->Tag == BSNoteSendback && !CheckOperateAuthority())
			return;

		ChangeBsmode(item->Tag);
		ChangeOpmode(OPAddNtHeader);
 	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmZNProcureMng::tlbtn4Click(TObject *Sender)
{
	//Excel导出
	//Excel导出
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
        DbgridToExcel(dbgrdNote);
	}
}//Excel导出函数
bool __fastcall TfrmZNProcureMng::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		MessageBox(0,"没有数据！","错误确认" ,MB_OK);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	temptext = "'"+ Label2->Caption;
	v.OlePropertyGet("Cells",1,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","单号" );
	temptext = "'"+ dbedtWsaleNtCode->Text;
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",3,7).OlePropertySet("Value","日期");
	temptext = "'"+ DateToStr(dbdtedtHdTime->Date);
	v.OlePropertyGet("Cells",3,8).OlePropertySet("Value",temptext .c_str() );

	v.OlePropertyGet("Cells",4,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,4).OlePropertySet("Value","附加费用" );
	temptext = "'"+ dbnbedtAddCosts->Text;
	v.OlePropertyGet("Cells",4,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",5,1).OlePropertySet("Value","备注");
	temptext = "'"+ dbedtRemarks->Text;
	v.OlePropertyGet("Cells",5,2).OlePropertySet("Value",temptext .c_str() );

	n=6;

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
		}
	}



	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}
	return false;
}
//---------------------------------------------------------------------------}
//---------------------------------------------------------------------------
void TfrmZNProcureMng::QryNtHeader(String code, bool qrybkstack)
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	spQryNtHeader1->Parameters->ParamByName("@NtCode")->Value = code;
	spQryNtHeader1->Parameters->ParamByName("@Bsmode")->Value = 6;
	spQryNtHeader1->Parameters->ParamByName("@Neworold")->Value = rg->ItemIndex ;
	MYTRACEF(_T("query note header @NtCode=%S"), code.c_str());
	try
	{
		spQryNtHeader1->Active = true;
		dsrcNtHeader->DataSet = NULL;
		dsetNtHeader->Recordset = spQryNtHeader1->Recordset;
		dsrcNtHeader->DataSet = dsetNtHeader;
		dsetNtHeader->Last();
		int count = 0;
		dsrcNote->DataSet = NULL;
		dsetNote->AfterScroll = NULL;
		dsetNote->Recordset = spQryNtHeader1->NextRecordset(count);
        dsrcNote->DataSet = dsetNote;
		dsetNote->Last();
	if (dsetNote->FieldByName("amount")->AsInteger < 0 ) {
			   Label2->Caption = "采购撤消单";
			   m_bsmode = BSNoteSendback;
		}
		dsetNote->AfterScroll = dsetNoteAfterScroll;
		if (qrybkstack)
		{
            QryBkstack();
		}
	}
	catch(...)
	{
		//ShowMessage("该单不存在！");
	}
}

void TfrmZNProcureMng::QryNtHeader(bool qrybkstack)
{
	//保存查询之前的当前活动记录ID
	int noteID = 0;
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
        noteID = dsetNote->FieldByName("ID")->AsInteger;
	}
	//查询单头
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		spQryNtHeader1->Active = false;
		spQryNtHeader->Active = false;
		spQryNtHeader->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger;
		spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value =6;
		spQryNtHeader->Parameters->ParamByName("@Neworold")->Value = rg->ItemIndex ;
		try
		{
			spQryNtHeader->Active = true;
			dsrcNtHeader->DataSet = NULL;
			dsetNtHeader->Recordset = spQryNtHeader->Recordset;
			dsrcNtHeader->DataSet = dsetNtHeader;
			dsetNtHeader->Last();
			int count = 0;
			dsrcNote->DataSet = NULL;
			dsetNote->AfterScroll = NULL;
			dsetNote->Recordset = spQryNtHeader->NextRecordset(count);
			dsrcNote->DataSet = dsetNote;
			if (noteID > 0)//将当前记录的ID重新调整至noteID
			{
                TLocateOptions Opts;
				Opts.Clear();
				Opts << loPartialKey;
				if (!dsetNote->Locate("ID", noteID, Opts))
					dsetNote->Last();
			}
			else
			{
				dsetNote->Last();
			}
			dsetNote->AfterScroll = dsetNoteAfterScroll;
			if (qrybkstack)
			{
				QryBkstack();
			}
		}
		catch(...)
		{
		   //	ShowMessage("该单不存在！");
		}
	}
}

void TfrmZNProcureMng::QryNtHeader(int id, bool qrybkstack)
{
	//查询单头
	spQryNtHeader1->Active = false;
	spQryNtHeader->Active = false;
	spQryNtHeader->Parameters->ParamByName("@ID")->Value = id;
	spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 6;
	spQryNtHeader->Parameters->ParamByName("@Neworold")->Value = rg->ItemIndex ;
	try
	{
		spQryNtHeader->Active = true;
		dsrcNtHeader->DataSet = NULL;
		dsetNtHeader->Recordset = spQryNtHeader->Recordset;
		dsrcNtHeader->DataSet = dsetNtHeader;


		dsetNtHeader->Last();
		int count = 0;
		dsrcNote->DataSet = NULL;
		dsetNote->AfterScroll = NULL;
		dsetNote->Recordset = spQryNtHeader->NextRecordset(count);
		dsrcNote->DataSet = dsetNote;
		dsetNote->Last();
		dsetNote->AfterScroll = dsetNoteAfterScroll;
		if (qrybkstack)
		{
			QryBkstack();
		}
	}
	catch(Exception *E)
	{

		//ShowMessage(E->Message);
	}
}

void TfrmZNProcureMng::AddNtHeader()
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 6;     //采购
	MYTRACEF(_T("add note header @StgID=%d,@OperatorID=%d,@Bsmode=%d"),m_storageID,m_userID,6);
	cmdAddNtHeader->Execute();
	int id = cmdAddNtHeader->Parameters->ParamByName("@RETURN_VALUE")->Value;
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader(id);
		logmessage = "添加智能采购单" + dsetNtHeader->FieldByName("ZNProcureNtCode")->AsString ;
		AddEvent(1,"智能采购窗口",m_userID,m_storageID,logmessage,m_con);
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
}

void TfrmZNProcureMng::DelInvalidNtHeader()
{
	if (!dsetNtHeader->IsEmpty() ) {
		AnsiString sql;
		sql = "select * from BS_ZN_ProcureNote where ZNProcureNtHeaderID = " + dsetNtHeader->FieldByName("ID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->IsEmpty() ) {
			DelNtHeader();
		}
	}
}

void TfrmZNProcureMng::DelNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdDelNtHeader->Parameters->ParamByName("@ID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		int id = dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdDelNtHeader->Parameters->ParamByName("@Bsmode")->Value = 6;
		MYTRACEF(_T("del note header @ID=%d,@Bsmode=%d"), id, 6);
		cmdDelNtHeader->Execute();
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader(id);
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

void TfrmZNProcureMng::UpdateNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdUpdateNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@HdTime")->Value =
			dsetNtHeader->FieldByName("HdTime")->AsDateTime;
		cmdUpdateNtHeader->Parameters->ParamByName("@StgID")->Value =
			dsetNtHeader->FieldByName("StgID")->AsInteger;
		if (dsetNtHeader->FieldByName("StaffID")->AsString != "")
			cmdUpdateNtHeader->Parameters->ParamByName("@StaffID")->Value =
				dsetNtHeader->FieldByName("StaffID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@AddCosts")->Value =
			abs(dsetNtHeader->FieldByName("AddCosts")->AsFloat);
		cmdUpdateNtHeader->Parameters->ParamByName("@Remarks")->Value =
			dsetNtHeader->FieldByName("Remarks")->AsWideString;


		cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value =  cbstate->ItemIndex ;



		cmdUpdateNtHeader->Parameters->ParamByName("@Bsmode")->Value = 6;
		cmdUpdateNtHeader->Execute();

		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

bool TfrmZNProcureMng::AddNote(int supplierID, int catalogID)
{
	bool result = false;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
			= catalogID;
		cmdAddNote->Parameters->ParamByName("@SupplierID")->Value = supplierID;
			cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 6;
				cmdAddNote->Parameters->ParamByName("@NoteMode")->Value = -1;

		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
		if (ret > 0)//插入成功
		{
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。

				QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			result = true;
		}
		else if (ret == 0)//查无此书
		{

		}
		else if (ret == -1)//库存出错了
		{

		}
		else if (ret == -2) {
				  addnotereturnvalue = -2;
						//负库存
				  MessageBox(0,"不能添加相同目录的书!","提示",MB_ICONEXCLAMATION);
				  result = true;

			 }

	}
	return result;
}
void TfrmZNProcureMng::UpdateNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		cmdUpdateNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		if (m_bsmode == BSNote)
		{
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= abs(dsetNote->FieldByName("Amount")->AsInteger);
		}
		else
		{
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= - abs(dsetNote->FieldByName("Amount")->AsInteger);
		}
		cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
			= abs(dsetNote->FieldByName("Discount")->AsFloat);
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 6;
		cmdUpdateNote->Execute();
	}
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader();
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
}
void TfrmZNProcureMng::DelNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdDelNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
			cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 6;
			logmessage = "删除智能采购单" + dsetNtHeader->FieldByName("ZNProcureNtCode")->AsString + "的书目《" + dsetNote->FieldByName("CatalogName")->AsString + "》";
			AddEvent(1,"智能采购单窗口",m_userID,m_storageID,logmessage,m_con);
			cmdDelNote->Execute();
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			String ids = "";
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = ids + dsetNote->FieldByName("ID")->AsString;
			logmessage = "删除智能采购单" + dsetNtHeader->FieldByName("ZNProcureNtCode")->AsString + "的书目《" + dsetNote->FieldByName("CatalogName")->AsString + "》";
			AddEvent(1,"智能采购单窗口",m_userID,m_storageID,logmessage,m_con);
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				logmessage = "删除智能采购单" + dsetNtHeader->FieldByName("ZNProcureNtCode")->AsString + "的书目《" + dsetNote->FieldByName("CatalogName")->AsString + "》";
				AddEvent(1,"智能采购单窗口",m_userID,m_storageID,logmessage,m_con);
			}
			cmdBatchDelNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchDelNote->Parameters->ParamByName("@Bsmode")->Value = 6;
			cmdBatchDelNote->Execute();
		}
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

void __fastcall TfrmZNProcureMng::dblkpcbbBkstackIDKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		tlbtn1Click(tlbtnAddNote);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmZNProcureMng::dbedtRemarksKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		tlbtn1Click(tlbtnAddNote);
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmZNProcureMng::dblkpcbbStaffIDExit(TObject *Sender)
{
	UpdateNtHeader();
}
//---------------------------------------------------------------------------


void __fastcall TfrmZNProcureMng::dbnbedtAmountExit(TObject *Sender)
{
	UpdateNote();
}
//---------------------------------------------------------------------------


void __fastcall TfrmZNProcureMng::tlbtn5Click(TObject *Sender)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->PrintType = 2;//采购
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString,0);

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

		frm->RvSystem1->DefaultDest   = rdPrinter ;

		 frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
        	frm->previewprint(1,4);
		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------


void TfrmZNProcureMng::QryBkstack()
{
  /*	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)
	{
   /*		String sql;
		sql = " SELECT STK_BookstackInfo.ID, STK_BookstackInfo.Name "
			" FROM STK_BookInfo LEFT OUTER JOIN"
			" STK_BookstackInfo ON STK_BookInfo.BkstackID = STK_BookstackInfo.ID"
			" where SupplierID=" + dsetNote->FieldByName("SupplierID")->AsString
			 + " and BkcatalogID=" + dsetNote->FieldByName("BkcatalogID")->AsString
			 + " and StgID=" + dsetNtHeader->FieldByName("StgID")->AsString;
	  //	dsetBkstack->Active = false;
	 //	dblkpcbbBkstackID->ListSource = NULL;
	 //	dblkpcbbBkstackID->DataSource = NULL;
	  //	dsetBkstack->CommandText = sql;
	  //	dsetBkstack->Active = true;
	 //	dblkpcbbBkstackID->ListSource = dsrcBkstack;
	//	dblkpcbbBkstackID->DataSource = dsrcNote;
		//ShowMessage("OK");
	}    */
}

void __fastcall TfrmZNProcureMng::dsetNoteAfterScroll(TDataSet *DataSet)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
        QryBkstack();
}
//---------------------------------------------------------------------------

void TfrmZNProcureMng::ResetNtHeader()
{
	//重置单头
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
	)
	{
		cmdResetNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdResetNtHeader->Parameters->ParamByName("@Bsmode")->Value = 6;
		cmdResetNtHeader->Execute();
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}


void __fastcall TfrmZNProcureMng::N1Click(TObject *Sender)
{
		lblCatalog->Caption = "书        号";
		m_catalogSearchMode=1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::N2Click(TObject *Sender)
{
lblCatalog->Caption = "自  编  码";
m_catalogSearchMode=2;
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::N3Click(TObject *Sender)
{
lblCatalog->Caption = "书        名";
m_catalogSearchMode=3;
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::N11Click(TObject *Sender)
{
  tlbtn5->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::N21Click(TObject *Sender)
{
  /* if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString);

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

		frm->RvSystem1->DefaultDest    = rdPrinter ;
		// frm->RvSystem1->SystemSetups<<ssAllowSetup;
		 frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
	  //	 frm->RvSystem1->SystemSetups<<ssAllowPrinterSetup;



		if (Label2->Caption == "批销单")
		{
			frm->previewprint(1,2);
		}else
		{
		   frm->previewprint(2,2);
		}
		  //1,批销单 2.批销退货单 //1打印格式1 2 打印格式2
		frm->Close();
		delete frm;
	}*/
}
//---------------------------------------------------------------------------


void __fastcall TfrmZNProcureMng::BtnClearClick(TObject *Sender)
{
   if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->PrintType = 2;//采购
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString,0);

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;



		frm->RvSystem1->DefaultDest  = rdPreview ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPreview;


			frm->previewprint(1,4);

		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::N22Click(TObject *Sender)
{
  /*	 if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString);

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;



		frm->RvSystem1->DefaultDest  = rdPreview ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPreview;
		if (Label2->Caption == "批销单")
		{
			frm->previewprint(1,2);
		}else
		{
		   frm->previewprint(2,2);
		}
		  //1,批销单 2.批销退货单 //1打印格式1 2 打印格式2
		frm->Close();
		delete frm;
	} */
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::N12Click(TObject *Sender)
{
  BtnClear->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{
    if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
	if (Key == '\r')
	{
	 // Perform(WM_NEXTDLGCTL, 0, 0);
	  edtCatalog->Text = "";
	  edtCatalog->SetFocus();

	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmZNProcureMng::FormResize(TObject *Sender)
{
 //dbgrdNote->Height = 389;
  //dbgrdNote->Width = 708;

}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::N4Click(TObject *Sender)
{
lblCatalog->Caption = "定 价";
m_catalogSearchMode=6;
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::dbnbedtTotalAmountKeyPress(TObject *Sender, wchar_t &Key)

{
       if (Key == '\r')
	{
	  Perform(WM_NEXTDLGCTL, 0, 0);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::cbstateChange(TObject *Sender)
{
	UpdateNtHeader();
}
//---------------------------------------------------------------------------

void  TfrmZNProcureMng::FindNote(String code)
{
	DelInvalidNtHeader();
	edtCatalog->Text = "";
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader(code);
		cbstate->ItemIndex = dsetNtHeader->FieldByName("state")->AsInteger ;
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
}

//---------------------------------------------------------------------------
void TfrmZNProcureMng::NtCodeChange()
{
  	AnsiString sql;
	int max,index;
	String code = dbedtWsaleNtCode->Text;
	if (code != "" && MaxNote != "") {
        max = StrToInt(MaxNote.SubString(11,5));
		index = StrToInt(code.SubString(9,5));
		if (index == 0 && max == 0) {
			Sbutfirst->Enabled = true;
			Sbutbefore->Enabled = false;
			Sbutnext->Enabled = false;
			Sbutend->Enabled = false;
		}
		if (index == 0 && max != 0) {
			Sbutfirst->Enabled = false;
			Sbutbefore->Enabled = false;
			Sbutnext->Enabled = true;
			Sbutend->Enabled = true;
		}
		if (index != 0 && index < max) {
			Sbutfirst->Enabled = true;
			Sbutbefore->Enabled = true;
			Sbutnext->Enabled = true;
			Sbutend->Enabled = true;
		}
		if (index != 0 && index == max) {
			Sbutfirst->Enabled = true;
			Sbutbefore->Enabled = true;
			Sbutnext->Enabled = false;
			Sbutend->Enabled = false;
		}
		if (index != 0 && index == max + 1) {
			Sbutfirst->Enabled = true;
			Sbutbefore->Enabled = true;
			Sbutnext->Enabled = false;
			Sbutend->Enabled = false;
		}
		if (index != 0 && index > max + 1) {
			Sbutfirst->Enabled = true;
			Sbutbefore->Enabled = false;
			Sbutnext->Enabled = false;
			Sbutend->Enabled = false;
		}
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmZNProcureMng::SbutfirstClick(TObject *Sender)
{
	if (dbedtWsaleNtCode->Text == "") {
		return;
	}
	String correntcode = dbedtWsaleNtCode->Text.Trim() ;
	String code = correntcode.SubString(0,8);
	code = code + "00000";
	dbedtWsaleNtCode->Text = code;
	code = "00" + code;
	FindNote(code);
	NtCodeChange();
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::SbutbeforeClick(TObject *Sender)
{
	if (dbedtWsaleNtCode->Text == "") {
		return;
	}
	String correntcode = dbedtWsaleNtCode->Text.Trim() ;
	int code = StrToInt(correntcode.SubString(9,5) );
	code = code - 1;
	if (code < 10) {
		correntcode = correntcode.SubString(0,8) + "0000" + IntToStr(code);
	}
	else if (code < 100) {
		correntcode = correntcode.SubString(0,8) + "000" + IntToStr(code);
	}
	else if (code < 1000) {
		correntcode = correntcode.SubString(0,8) + "00" + IntToStr(code);
	}
	else if (code < 10000) {
		correntcode = correntcode.SubString(0,8) + "0" + IntToStr(code);
	}
	else if (code < 100000) {
		correntcode = correntcode.SubString(0,8) + IntToStr(code);
	}
	//QryNtHeader(correntcode);
	dbedtWsaleNtCode->Text = correntcode;
	correntcode = "00" + correntcode;
	FindNote(correntcode);
	NtCodeChange();
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::SbutnextClick(TObject *Sender)
{
	if (dbedtWsaleNtCode->Text == "") {
		return;
	}
	String correntcode = dbedtWsaleNtCode->Text.Trim() ;
	int code = StrToInt(correntcode.SubString(9,5) );
	code = code + 1;
	if (code < 10) {
		correntcode = correntcode.SubString(0,8) + "0000" + IntToStr(code);
	}
	else if (code < 100) {
		correntcode = correntcode.SubString(0,8) + "000" + IntToStr(code);
	}
	else if (code < 1000) {
		correntcode = correntcode.SubString(0,8) + "00" + IntToStr(code);
	}
	else if (code < 10000) {
		correntcode = correntcode.SubString(0,8) + "0" + IntToStr(code);
	}
	else if (code < 100000) {
		correntcode =  correntcode.SubString(0,8) + IntToStr(code);
	}
	//QryNtHeader(correntcode);
	dbedtWsaleNtCode->Text = correntcode;
	correntcode = "00" + correntcode;
	FindNote(correntcode);
	NtCodeChange();
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::SbutendClick(TObject *Sender)
{
	if (dbedtWsaleNtCode->Text == "") {
		return;
	}
	String correntcode = MaxNote ;
	dbedtWsaleNtCode->Text = correntcode;
	correntcode = "00" + correntcode;
	FindNote(correntcode);
	NtCodeChange();
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::N6Click(TObject *Sender)
{
	for (int i = 1; i <= dsetNote->RecordCount; i++) {
		dbgrdNote->DataSource->DataSet->RecNo = i;
		dbgrdNote->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmZNProcureMng::BtnMonthViewClick(TObject *Sender)
{
  Tfrmbookup * frm = new Tfrmbookup(Application,2,m_con);
  frm->stgid = m_storageID ;
  frm->pro = this;
  frm->Show();

}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
		if (Key == VK_F1) {
	RzToolButton1->Click();
	}
		if (Key == VK_F2) {
		 mtbbtnAddNtHeader->Click();
	}	if (Key == VK_F3) {
		tlbtn1->Click();
	}
		if (Key == VK_F4) {
		tlbtn2->Click();
	}
		if (Key == VK_F5) {
		tlbtn3->Click();
	}
		if (Key == VK_F6) {
		BtnMonthView->Click();
	}
		if (Key == VK_F8) {
		BtnClear->Click();
	}
		if (Key == VK_F9) {
		tlbtn5->Click();
	}


   	if (Shift.Contains(ssCtrl)&& Key ==81  ) {
	   tlbtn7->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {
	   BtnAlignBottom->Click();
	}

			if (Shift.Contains(ssCtrl)&& Key ==90) {
            	WindowState = wsNormal  ;
		}

}
//---------------------------------------------------------------------------


void __fastcall TfrmZNProcureMng::dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        dbnbedtDiscount->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmZNProcureMng::rgClick(TObject *Sender)
{
	QryNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::BtnExportClick(TObject *Sender)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1){
		comfenlei->Active = false;
		comfenlei->Parameters->ParamByName("@headerid")->Value = dsetNtHeader->FieldByName("ID")->AsInteger ;
		try
		{
			comfenlei->Active = true;
			query->Recordset = comfenlei->Recordset;
			if (query->RecordCount > 1) {
				Tfrmfenleitype * frm = new Tfrmfenleitype(Application,query,dsetNtHeader->FieldByName("ID")->AsInteger);
				frm->Show();
			}
		}
		catch(...)
		{
		//ShowMessage("该单不存在！");
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNProcureMng::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

