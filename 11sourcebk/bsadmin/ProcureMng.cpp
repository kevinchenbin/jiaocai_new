//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProcureMng.h"
#include "NoteCode.h"
#include "QryNoteCodeForm.h"
#include "SetNotesForm.h"
#include "mytrace.h"
#include "SelectCustomerForm.h"
#include "RecMoneyForm.h"
#include "SelectCatalogForm.h"
#include "..\supplier\detailemessage.h"
#include "bookup.h"
#include "Addsyslog.h"
#include "NewBookinput1.h"
#include "bookQuery.h"
#include "NewBookModify.h"
#include "Unitcaigouquery.h"
#include "Unitorderquery.h"
#include "UnitBIOrder.h"
#include "unitinorder.h"
#include "bookhistory.h"
#include "retailbookup.h"
#include "Unitshutmsg.h"

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
TfrmProcureMng *frmProcureMng;
//---------------------------------------------------------------------------
__fastcall TfrmProcureMng::TfrmProcureMng(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_catalogSearchMode(0)
	, m_bsmode(BSUnknown)
	, m_opmode(OPUnknown)
	, m_supplierID(-1)
{
	m_module = MTPur;
	this->WindowState = wsMaximized ;
}
//---------------------------------------------------------------------------
void TfrmProcureMng::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	userid = li->userID ;
	stgid = li->storageID ;
	//m_storageID = li->storageID ;
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
	dsetVendor->Connection = m_con;
	dsetStaff->Connection = m_con;
	dsetLkpVendor->Connection = m_con;
	dsetBkstack->Connection = m_con;
	query->Connection = m_con;
	aq2->Connection = m_con;
	aqheader->Connection = m_con;
	adoshurtmsg->Connection=m_con;
	ShortMsgSP->Connection=m_con;
	dsetBkstack->Active = true;
	dsetVendor->Active = true;
	dsetStaff->Active = true;
	dblkpcbbVendorID->KeyValue = 0;
	bearsaledataset->Connection = m_con;
	bearsaledataset->Active = true;
	dsetStaff->Connection = m_con;
	ChangeCatalogSearchMode();
	ChangeBsmode(BSNote);
	ChangeOpmode(OPAddNtHeader);
	addnotereturnvalue = 0;
	AnsiString sql;
	sql = "select * from sys_bsset where name = 'procurefindpwd'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	findpwd = query->FieldByName("Value")->AsBoolean ;
	sql = "select * from sys_bsset where name = 'procuredeletepwd'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	deletepwd = query->FieldByName("Value")->AsBoolean ;
	sql = "select ID,Name,Master from SYS_StorageInfo where id = " + IntToStr(stgid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	Edit1->Text = query->FieldByName("ID")->AsString;
	Edit2->Text = query->FieldByName("Name")->AsString ;
	if (!query->FieldByName("Master")->AsBoolean  ) {
    	BtnWeekView->Enabled = false;
	}

	sql = "select catalogmodle from BS_Fastelurustyle where Name = '采购' and stgid = " + IntToStr(li->storageID);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {
		m_catalogSearchMode = query->FieldByName("catalogmodle")->AsInteger;
		switch (m_catalogSearchMode) {
			case 1:
				lblCatalog->Caption = "书  号";
				break;
			case 2:
				lblCatalog->Caption = "自编码";
				break;
			case 3:
				lblCatalog->Caption = "书  名";
				break;
			case 5:
				lblCatalog->Caption = "作  者";
				break;
			case 6:
				lblCatalog->Caption = "定  价";
				break;
		default:
			;
		}
	}

	sql = "select cgprinttitle,cgcontact,cgtel,cgaddress,cgprintbk,shaddress,shcontact,shtel from sys_printtitle where stgid = " + IntToStr(m_storageID);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	printbk = query->FieldByName("cgprintbk")->AsAnsiString ;
	printtitle = query->FieldByName("cgprinttitle")->AsAnsiString ;
	contact = query->FieldByName("cgcontact")->AsAnsiString ;
	tel = query->FieldByName("cgtel")->AsAnsiString ;
	address = query->FieldByName("cgaddress")->AsAnsiString ;
	shaddress = query->FieldByName("shaddress")->AsAnsiString ;
	shtel = query->FieldByName("shtel")->AsAnsiString ;
	shcontact = query->FieldByName("shcontact")->AsAnsiString ;

	sql = "select tel from sys_user where id = " + IntToStr(userid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	usertel = query->FieldByName("tel")->AsAnsiString ;


          if (li->FormatStr=="1") {
            newsupplier=true;
             RzButton1->Enabled = true;
          }else {newsupplier = false;
           RzButton1->Enabled = false;}
         checknewsupplier();

}
//---------------------------------------------------------------------------
void __fastcall TfrmProcureMng::FormClose(TObject *Sender, TCloseAction &Action)
{
    DelInvalidNtHeader();
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	dsetStaff->Active = false;
	dsetLkpVendor->Active = false;
	dsetBkstack->Active = false;
	dsetVendor->Active = false;
	TfrmMDIChild::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::tlbtn1Click(TObject *Sender)
{
	//删除
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con)
	{
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmProcureMng::tlbtn7Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::edtQryVendorKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		if (!dsetNtHeader->Active
			|| !dsetNote->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;
		if (!dblkpcbbVendorID->Enabled ) {
		   return;
		}
		String sql;
		sql = " select * from CUST_CustomerInfo where Type =1 and Name like '%"+ edtQryVendor->Text.Trim() + "%' order by name";
		dsetVendor->Active = false;
		dsetVendor->CommandText = sql;
		dsetVendor->Active = true;
		dsetVendor->First();
		dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("VendorID")->AsInteger = dsetVendor->FieldByName("ID")->AsInteger;
		dsetNtHeader->Post();
		dblkpcbbVendorID->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmProcureMng::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
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
		if (dblkpcbbVendorID->Enabled) {
			MessageBox(0,"在供应商处使用回车键确定所选择的供应商！","采购" ,MB_ICONEXCLAMATION);
			return;
		}
		if (edtCatalog->Text == "")
		{
			ChangeCatalogSearchMode();
		}
		else
		{
            float price;
			if (m_catalogSearchMode == 6) {
				try {
					price = StrToFloat(edtCatalog->Text.Trim());
				} catch (...) {
					MessageBox(0,"请输入正确的定价！","采购" ,MB_ICONEXCLAMATION);
					return;
				}
			}

				if (chqikan->Checked && m_catalogSearchMode != 1) {
					edqikan->SetFocus();
					return;
				}
				if (m_catalogSearchMode == 1 && chqikan->Checked) {
					if (edtCatalog->Text.Length() == 15 ) {
						edqikan->Text = edtCatalog->Text.SubString(14,2);
						edtCatalog->Text = edtCatalog->Text.SubString(0,13);
					}
					else
					{
                    	edqikan->SetFocus();
						return;
					}
				}


					TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
					LandInfo li;
					li.app = m_app;
					li.con = m_con;
					li.userID = userid;
					li.storageID = stgid;
					frm->Init(&li);
					frm->DoModalType = 5;
					frm->Procurefrm  = this;
					frm->qikan = chqikan->Checked ;
					frm->qikanhao = edqikan->Text ;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);

					if (mrOk == frm->ShowModal())
					{
						int supplierID = -1,catalogID = -1;
						frm->GetSelectResult(supplierID, catalogID);
						supplierID = dsetVendor->FieldByName("ID")->AsInteger ;
						if (frm->SelectAll) {
							supplierID = dsetVendor->FieldByName("ID")->AsInteger ;
							 for (int i = 0; i < frm->lengthint  ; i++) {
								 if (AddNote(supplierID,frm->BkcatalogiD[i])) {
									 Key = 0;
									 Perform(WM_NEXTDLGCTL, 0, 0);
									 dbnbedtAmount->SetFocus();

								 }
								 historyview();
							 }

						} else
						{
							if (supplierID >= 0 && catalogID >= 0)
							{
                                TLocateOptions   Opts;
								Opts.Clear();
								Opts   <<   loPartialKey;
								String   str   = AnsiString(catalogID);
								if ( !dsetNote->Locate("BkcatalogID",str,Opts))
								{

								if (AddNote(supplierID, catalogID))
								{
									if (addnotereturnvalue == -2) {
									   //	 MessageBox(0,"不充许负库存销售！","批销" ,MB_ICONEXCLAMATION);
                                         addnotereturnvalue = 0;
										} else
										{
											Key=0;
											//Perform(WM_NEXTDLGCTL, 0, 0);

											  historyview();

											  if (chfoceset->Checked) {
													if (chfsamount->Checked ) {
														dbnbedtAmount->SetFocus();
													}
													else if (chfsdiscount->Checked ) {
														dbnbedtDiscount->SetFocus();
													}
													else if (chfsluru->Checked) {
														edtCatalog->SetFocus();
													}
												}
												else
												{
													dbnbedtAmount ->SetFocus();
												}

										 }
								}
								else

									ShowMessage("库存无该书!");
								}
								else
								{
                                	dbgrdNote->SelectedRows->CurrentRowSelected = true;
									dbgrdNote->SetFocus();
									dbnbedtAmount->SetFocus();
								}
							}

						}
					}
					else {               //未锁定
                            	if ((!frm->findbook)&&(!bookcatalogadd)) {     //产生新书

										//新书目
									if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
									{
									   Tfrmnewbook1 *frma = new Tfrmnewbook1(m_app,m_con);
									   frma->ProcureMng = this;
									   frma->modle = 3;

									   if (chqikan->Checked) {
											frma->cbsaletype->Text = "期刊";
											frma->cbsaletypeChange(this);
											frma->editqikanmao->Text =edtCatalog->Text + edqikan->Text;
											PostMessage(frma->editqikanmao->Handle, WM_KEYDOWN,VK_RETURN,0);
									   }
									   else
									   {
											frma->editcode->Text = edtCatalog->Text ;
											PostMessage(frma->editcode->Handle, WM_KEYDOWN,VK_RETURN,0);
									   }
										//frma->editcode->Text = edtCatalog->Text ;
										//PostMessage(frma->editcode->Handle, WM_KEYDOWN,VK_RETURN,0);
									   if (mbOK == frma->ShowModal())
									   {

									   }
									   delete frma;
									   dbnbedtAmount->SetFocus();
									}

							   }
							}
							edtCatalog->Text = "";
                            edqikan->Text = "";
							delete frm;
		}
	}
}
//---------------------------------------------------------------------------

void TfrmProcureMng::ChangeCatalogSearchMode()
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
		if (chqikan->Checked ) {
			edtCatalog->MaxLength = 15;
		}
		else
		{
			edtCatalog->MaxLength = 13;
		}
		lblCatalog->Caption = "书号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "自编码";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "书名";
		break;
	case 5:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "作者";
		break;
	case 6:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "定价";
		break;
    default:
        break;
	}
}

void TfrmProcureMng::ChangeBsmode(BSMode bsmode)
{
	if (bsmode != m_bsmode)
	{
        m_bsmode = bsmode;
    }

	if (m_bsmode == BSNote)
	{
		mniBsNote->Checked = true;
		mniBsNoteSendback->Checked = false;
	}
	else if (m_bsmode == BSNoteSendback)
	{
		mniBsNote->Checked = false;
		mniBsNoteSendback->Checked = true;
	}
}

void TfrmProcureMng::ChangeOpmode(OPMode opmode)
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
			VendorView();

			DelInvalidNtHeader();
			Tfrmcaigouquery *frm = new Tfrmcaigouquery(Application,m_con,stgid,1,0);
            if (frm->ShowModal() == mrOk)
			{

				edtCatalog->Text = "";
				edtQryVendor->Text = "";
				AnsiString code = frm->GetNoteCode();
				AnsiString sqlwhere = frm->GetWhere();
				try
				{
					//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
					QryNtHeader(code);
					DBNavigator1->Enabled = true;
					cbstate->ItemIndex = dsetNtHeader->FieldByName("state")->AsInteger ;
					AnsiString sql;
					if (sqlwhere != "") {
						sql = "select * from BS_ProcureNoteHeader " + sqlwhere ;
						aqheader->Close();
						aqheader->SQL->Clear();
						aqheader->SQL->Add(sql);
						aqheader->Open();
						TLocateOptions Opts;
						Opts.Clear();
						Opts << loPartialKey;
						aqheader->Locate("ProcureNtCode", code, Opts);
					}
				}
				__finally
				{
					//LockWindowUpdate(NULL);
				}
			}
			/*TfrmQryNoteCode* frm = new TfrmQryNoteCode(this,0);
			LandInfo li;
			li.app = m_app;
			li.con = m_con;
			li.userID = userid;
			li.storageID = stgid;
			frm->Init(&li);
			if (frm->ShowModal() == mrOk)
			{
				DelInvalidNtHeader();
				edtCatalog->Text = "";
				edtQryVendor->Text = "";
				String code = frm->GetNoteCode();
				try
				{
					//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
					QryNtHeader(code);
					DBNavigator1->Enabled = true;
					cbstate->ItemIndex = dsetNtHeader->FieldByName("state")->AsInteger ;
					String sql,codetmp;
					codetmp = code;
					if (codetmp != "") {
						codetmp = codetmp.SubString(0,10);
						int codenext = StrToInt(codetmp) + 1;
						/*sql = "select ProcureNtCode from BS_ProcureNoteHeader where ProcureNtCode >= " +  codetmp + "00000 and ProcureNtCode < " + IntToStr(codenext) + "00000";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->Open();
						query->Last();
						codetmp = query->FieldByName("ProcureNtCode")->AsString ;
						sql = "select id from BS_ProcureNoteHeader where ProcureNtCode >= " +  codetmp + "00000 and ProcureNtCode < " + IntToStr(codenext) + "00000";
						aqheader->Close();
						aqheader->SQL->Clear();
						aqheader->SQL->Add(sql);
						aqheader->Open();
					}
					MaxNote = codetmp;
				}
				__finally
				{
					//LockWindowUpdate(NULL);
				}
			} */
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
			dblkpcbbVendorID->Enabled = true;
			edtQryVendor->Enabled = true;
			spnewbook->Enabled = false;
			VendorView();
			dblkpcbbVendorID->KeyValue = 0;
			edtCatalog->Text = "";
			edtQryVendor->Text = "";
			AddNtHeader();
			DBNavigator1->Enabled = false;
			m_opmode = opmode;
            edtQryVendor->SetFocus();
        }
		break;
	case OPDelNtHeader:
		{
			if (!CheckOperateAuthority())
				return;

			edtCatalog->Text = "";
			edtQryVendor->Text = "";
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
	/*try {
		NtCodeChange();
	} catch (...) {
	} */
}

void TfrmProcureMng::BatchSetNotes(int amount, float discount, int mode)
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
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 5;
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
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 5;
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
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 5;
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

void __fastcall TfrmProcureMng::mniBsNoteSendbackClick(TObject *Sender)
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
void __fastcall TfrmProcureMng::tlbtn4Click(TObject *Sender)
{
	//Excel导出
	//Excel导出
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
        DbgridToExcel(dbgrdNote);
	}
}//Excel导出函数
bool __fastcall TfrmProcureMng::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = StringReplace(dblkpcbbVendorID->Text.Trim() +dbedtWsaleNtCode->Text.Trim() ,"\\","-",TReplaceFlags()<<rfReplaceAll) + "采购单";

	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
		path =  DBPath;
	}
	if(FileExists(path))
		try {
			DeleteFileA(path);
		} catch (...) {
			return false;
		}


	/*int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   //iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());
	*/
   Screen->Cursor=crHourGlass;
    Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",false);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",1,1),vSheet.OlePropertyGet("Cells",t2+11,14)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	v.OlePropertyGet("Cells",1,1).OlePropertySet("Value",printtitle .c_str() );

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",1,1),vSheet.OlePropertyGet("Cells",2,14)); //取得合并的区域
	R.OleProcedure("Merge");
	R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Bold",true);
	R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Name","宋体");   //字体
	R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("size",16);
	R.OlePropertySet("HorizontalAlignment",3);

	temptext = "联系人：" + lblOpName->Caption ;
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,1),vSheet.OlePropertyGet("Cells",3,4)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "电话：" + usertel ;
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,5),vSheet.OlePropertyGet("Cells",3,14)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "地址：" + address ;
	v.OlePropertyGet("Cells",4,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",4,1),vSheet.OlePropertyGet("Cells",4,14)); //取得合并的区域
	R.OleProcedure("Merge");

    temptext = "采购单号：" + dbedtWsaleNtCode->Text ;
	v.OlePropertyGet("Cells",5,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",5,1),vSheet.OlePropertyGet("Cells",5,4)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "供应商名称：" + dblkpcbbVendorID->Text ;
	v.OlePropertyGet("Cells",5,5).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",5,5),vSheet.OlePropertyGet("Cells",5,8)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "联系人："+ dsetVendor->FieldByName("Contact")->AsString ;
	v.OlePropertyGet("Cells",5,9).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",5,9),vSheet.OlePropertyGet("Cells",5,14)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "采购日期：" +  DateToStr(dbdtedtHdTime->Date ) ;
	v.OlePropertyGet("Cells",6,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",6,1),vSheet.OlePropertyGet("Cells",6,4)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "供应商电话：" + dsetVendor->FieldByName("Telephone")->AsString ;
	v.OlePropertyGet("Cells",6,5).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",6,5),vSheet.OlePropertyGet("Cells",6,8)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "传真："+ dsetVendor->FieldByName("Fax")->AsString ;
	v.OlePropertyGet("Cells",6,9).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",6,9),vSheet.OlePropertyGet("Cells",6,14)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "备注：" + membk->Text;
	v.OlePropertyGet("Cells",7,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",7,1),vSheet.OlePropertyGet("Cells",7,14)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "供应商地址："+ dsetVendor->FieldByName("Address")->AsString ;
	v.OlePropertyGet("Cells",8,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",8,1),vSheet.OlePropertyGet("Cells",8,14)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "总品种：" +  IntToStr(t2) ;
	v.OlePropertyGet("Cells",9,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",9,1),vSheet.OlePropertyGet("Cells",9,4)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "总数量：" + dbnbedt2->Text ;
	v.OlePropertyGet("Cells",9,5).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",9,5),vSheet.OlePropertyGet("Cells",9,8)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "总码洋："+ dbnbedt3->Text ;
	v.OlePropertyGet("Cells",9,9).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",9,10),vSheet.OlePropertyGet("Cells",9,14)); //取得合并的区域
	R.OleProcedure("Merge");

    n = 9;
	int t1= 0;
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	//iFileLength   =   FileSeek(iFileHandle,0,2);
	//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	dsetNote->DisableControls();
	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					//temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				/*else if (dbg->Columns ->Items [j-1]->FieldName == "CatalogName") {
					t1++;
					AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					//temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + bookname + ",";
				} */
				else if (dbg->Columns ->Items [j-1]->FieldName == "Discount") {
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					//temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + "%,";
				}
				else
				{
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					//temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		//iFileLength   =   FileSeek(iFileHandle,0,2);
		//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,3),vSheet.OlePropertyGet("Cells",t2+10,3)); //取得合并的区域  、
	R.OlePropertySet("WrapText", true);//设置指定区域中所有的单元格中的文本自动换行

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,14),vSheet.OlePropertyGet("Cells",t2+10,14)); //取得合并的区域  、
	R.OlePropertySet("WrapText", true);//设置指定区域中所有的单元格中的文本自动换行

	v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","合计");
	temptext = dbnbedt2->Text ;
	v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );
	temptext = dbnbedt3->Text ;
	v.OlePropertyGet("Cells",t2+2+n,11).OlePropertySet("Value",temptext .c_str() );
	temptext = dbnbedt4->Text ;
	v.OlePropertyGet("Cells",t2+2+n,12).OlePropertySet("Value",temptext .c_str() );

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,11),vSheet.OlePropertyGet("Cells",t2+11,12)); //取得合并的区域  、
	R.OlePropertySet("NumberFormatLocal", "0.00");//设置指定区域中的所有单元格格式为小数百分比

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,7),vSheet.OlePropertyGet("Cells",t2+11,7)); //取得合并的区域  、
	R.OlePropertySet("NumberFormatLocal", "0.00");//设置指定区域中的所有单元格格式为小数百分比

	temptext = "制单员：" + lblOpName->Caption ;
	v.OlePropertyGet("Cells",t2+3+n,1).OlePropertySet("Value",temptext .c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+3+n,1),vSheet.OlePropertyGet("Cells",t2+3+n,14)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "收货联系人：" + shcontact ;
	v.OlePropertyGet("Cells",t2+4+n,1).OlePropertySet("Value",temptext .c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+4+n,1),vSheet.OlePropertyGet("Cells",t2+4+n,14)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "收货联系电话：" + shtel ;
	v.OlePropertyGet("Cells",t2+5+n,1).OlePropertySet("Value",temptext .c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+5+n,1),vSheet.OlePropertyGet("Cells",t2+5+n,14)); //取得合并的区域
	R.OleProcedure("Merge");

	temptext = "收货地址：" + shaddress ;
	v.OlePropertyGet("Cells",t2+6+n,1).OlePropertySet("Value",temptext .c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+6+n,1),vSheet.OlePropertyGet("Cells",t2+6+n,14)); //取得合并的区域
	R.OleProcedure("Merge");

	v.OlePropertyGet("Cells",t2+7+n,1).OlePropertySet("Value",printbk .c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+7+n,1),vSheet.OlePropertyGet("Cells",t2+7+n,14)); //取得合并的区域
	R.OleProcedure("Merge");

	dsetNote->EnableControls();

	try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
		xWorkbook.OleFunction( "Close");
		 v.OleFunction("Quit");
		 MessageBox(Handle,"导出完毕！","提示" ,MB_OK|MB_ICONINFORMATION);
	} catch (Exception &E) {
		//ShowMessage(E.Message);
		Screen->Cursor=crDefault;
	}
     Screen->Cursor=crDefault;
	/*temptext = "\n";
	AnsiString tamount,mayang,shiyang;
	tamount =  dbnbedt2->Text;
	mayang = dbnbedt3->Text;
	shiyang = dbnbedt4->Text;
	mayang = StringReplace(mayang , ",","",TReplaceFlags()<<rfReplaceAll);
	shiyang = StringReplace(shiyang , ",","",TReplaceFlags()<<rfReplaceAll);
	tamount = StringReplace(tamount , ",","",TReplaceFlags()<<rfReplaceAll);

	temptext = temptext + "合计,,,,,,,," + tamount + ",," + mayang + "," + shiyang ;

	temptext = temptext + "合计,,,,,," + RzDBNumericEdit1->Text + ",," + mayang + "," + shiyang;
	temptext = temptext + "合计,,,,,," + RzDBNumericEdit1->Text + ",," + RzDBNumericEdit2->Text + "," + RzDBNumericEdit3->Text;
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);     */
	return false;
}
//---------------------------------------------------------------------------}
//---------------------------------------------------------------------------
void TfrmProcureMng::QryNtHeader(String code, bool qrybkstack)
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	spQryNtHeader1->Parameters->ParamByName("@NtCode")->Value = code;
	spQryNtHeader1->Parameters->ParamByName("@Bsmode")->Value = 5;
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
		if (dsetNote->RecordCount > 0) {
        	dblkpcbbVendorID->Enabled = false;
			spnewbook->Enabled = true;
		}
		dsrcNote->DataSet = dsetNote;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥0.00";
		dbdtedtHdTime->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
		dbdtedtHdyujiTime->Date = dsetNtHeader->FieldByName("yujidate")->AsDateTime ;
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		dsetNote->Last();
		if (dsetNote->FieldByName("amount")->AsInteger < 0 ) {
			   Label2->Caption = "采购撤消单";
			   m_bsmode = BSNoteSendback;
		}

                lock(dsetNtHeader->FieldByName("lock")->AsInteger);
		dsetNote->AfterScroll = dsetNoteAfterScroll;
		if (qrybkstack)
		{
            QryBkstack();
		}
	}
	catch(Exception &E)
	{
		//ShowMessage(E.Message);
		//ShowMessage("该单不存在！");
	}
}

void TfrmProcureMng::QryNtHeader(bool qrybkstack)
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
		spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value =5;
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
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥0.00";
            dbdtedtHdTime->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
			dbdtedtHdyujiTime->Date = dsetNtHeader->FieldByName("yujidate")->AsDateTime ;
			operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
			membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
			dsetNote->AfterScroll = dsetNoteAfterScroll;
			if (qrybkstack)
			{
				QryBkstack();
			}
                        lock(dsetNtHeader->FieldByName("lock")->AsInteger);
		}
		catch(...)
		{
			//ShowMessage("该单不存在！");
		}
	}
}

void TfrmProcureMng::QryNtHeader(int id, bool qrybkstack)
{
	//查询单头
	spQryNtHeader1->Active = false;
	spQryNtHeader->Active = false;
	spQryNtHeader->Parameters->ParamByName("@ID")->Value = id;
	spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 5;
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
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥0.00";
		dsetNote->AfterScroll = dsetNoteAfterScroll;
        dbdtedtHdTime->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
		dbdtedtHdyujiTime->Date = dsetNtHeader->FieldByName("yujidate")->AsDateTime ;
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		if (qrybkstack)
		{
			QryBkstack();
		}
                lock(dsetNtHeader->FieldByName("lock")->AsInteger);
	}
	catch(...)
	{
    	//ShowMessage("该单不存在！");
    }
}

void TfrmProcureMng::AddNtHeader()
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = stgid;
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = userid;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 5;     //采购
	MYTRACEF(_T("add note header @StgID=%d,@OperatorID=%d,@Bsmode=%d"),stgid,userid,5);
	cmdAddNtHeader->Execute();
	int id = cmdAddNtHeader->Parameters->ParamByName("@RETURN_VALUE")->Value;
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader(id);
		logmessage = "添加一般采购单" + dsetNtHeader->FieldByName("ProcureNtCode")->AsString ;
		AddEvent(1,"一般采购窗口",userid,stgid,logmessage,m_con);
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
}

void TfrmProcureMng::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0)
	{
        DelNtHeader();
    }
}

void TfrmProcureMng::DelNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdDelNtHeader->Parameters->ParamByName("@ID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		int id = dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdDelNtHeader->Parameters->ParamByName("@Bsmode")->Value = 5;
		MYTRACEF(_T("del note header @ID=%d,@Bsmode=%d"), id, 5);
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

void TfrmProcureMng::UpdateNtHeader()
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
		cmdUpdateNtHeader->Parameters->ParamByName("@CustomerID")->Value =
			dsetNtHeader->FieldByName("VendorID")->AsInteger;


			cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value =  cbstate->ItemIndex ;



		cmdUpdateNtHeader->Parameters->ParamByName("@Bsmode")->Value = 5;
		cmdUpdateNtHeader->Parameters->ParamByName("@yijidate")->Value =
			dsetNtHeader->FieldByName("yujidate")->AsDateTime ;
			//ShowMessage(DateToStr(dsetNtHeader->FieldByName("yujidate")->AsDateTime));
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

int TfrmProcureMng::AddNote(int supplierID, int catalogID)
{
	int result = 0;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
			= catalogID;
		cmdAddNote->Parameters->ParamByName("@SupplierID")->Value = supplierID;
			cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 5;
				cmdAddNote->Parameters->ParamByName("@NoteMode")->Value = -1;

		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
		if (ret > 0)//插入成功
		{
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
                clearbkinfo();//清除回告
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			result = 1;
		}
		else if (ret == 0)//查无此书
		{

		}
		else if (ret == -1)//库存出错了
		{

		}
		else if (ret == -2) {
        	TLocateOptions   Opts;
			Opts.Clear();
			Opts   <<   loPartialKey;
			String   str   = AnsiString(catalogID);
			dsetNote->Locate("BkcatalogID",str,Opts);
			MessageBox(0,"该书已做过采购!","提示",MB_ICONEXCLAMATION);
			result = 2;
				  //addnotereturnvalue = -2;
                        //负库存
				  //result = true;

		}

	}
	return result;
}
void TfrmProcureMng::UpdateNote()
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
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 5;
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
void TfrmProcureMng::DelNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (dbgrdNote->SelectedRows->Count == 0)
		{
		  //	cmdDelNote->Parameters->ParamByName("@ID")->Value
		  //		= dsetNote->FieldByName("ID")->AsInteger;
		  //	cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 5;
		 //	logmessage = "删除一般采购单" + dsetNtHeader->FieldByName("ProcureNtCode")->AsString + "的书目《" + dsetNote->FieldByName("CatalogName")->AsString + "》";
		 //	AddEvent(1,"一般采购窗口",userid,stgid,logmessage,m_con);
		  //	cmdDelNote->Execute();
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			String ids = "";
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = ids + dsetNote->FieldByName("ID")->AsString;
			logmessage = "删除一般采购单" + dsetNtHeader->FieldByName("ProcureNtCode")->AsString + "的书目《" + dsetNote->FieldByName("CatalogName")->AsString + "》";
			AddEvent(1,"一般采购窗口",userid,stgid,logmessage,m_con);
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				logmessage = "删除一般采购单" + dsetNtHeader->FieldByName("ProcureNtCode")->AsString + "的书目《" + dsetNote->FieldByName("CatalogName")->AsString + "》";
				AddEvent(1,"一般采购窗口",userid,stgid,logmessage,m_con);
			}
			cmdBatchDelNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchDelNote->Parameters->ParamByName("@Bsmode")->Value = 5;
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

void __fastcall TfrmProcureMng::dblkpcbbBkstackIDKeyPress(TObject *Sender, wchar_t &Key)
{
	//

}
//---------------------------------------------------------------------------
void __fastcall TfrmProcureMng::dblkpcbbVendorIDKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		if (dblkpcbbVendorID->Text == "") {
			MessageBox(0,"请选择供应商！","提示" ,MB_OK);
			return;
	   }
	   edtCatalog->SetFocus();
        UpdateNtHeader();
		dblkpcbbVendorID->Enabled = false;
		spnewbook->Enabled = true;
		edtCatalog->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmProcureMng::dbnbedtAmountExit(TObject *Sender)
{
	UpdateNote();
}
//---------------------------------------------------------------------------


void __fastcall TfrmProcureMng::tlbtn5Click(TObject *Sender)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = userid;
		li.storageID = stgid;
		frm->PrintType = 2;//采购
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString,0);

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

		frm->RvSystem1->DefaultDest   = rdPrinter ;

		frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
		frm->pxbk = printbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;
		frm->shaddress = shaddress;
		frm->shtel = shtel;
		frm->shcontact = shcontact;
		frm->previewprint(0,4);
		frm->Close();
		delete frm;
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("printcount")->AsInteger = dsetNtHeader->FieldByName("printcount")->AsInteger + 1;
		dsetNtHeader->Post();
	  //	QryNtHeader();
	}
}
//---------------------------------------------------------------------------


void TfrmProcureMng::QryBkstack()
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

void __fastcall TfrmProcureMng::dsetNoteAfterScroll(TDataSet *DataSet)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
        QryBkstack();
}
//---------------------------------------------------------------------------

void TfrmProcureMng::ResetNtHeader()
{
	//重置单头
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
	)
	{
		cmdResetNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdResetNtHeader->Parameters->ParamByName("@Bsmode")->Value = 5;
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


void __fastcall TfrmProcureMng::N1Click(TObject *Sender)
{
	lblCatalog->Caption = "书号";
	m_catalogSearchMode=1;
	if (chqikan->Checked ) {
		edtCatalog->MaxLength = 15;
	}
	else
	{
		edtCatalog->MaxLength = 13;
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码";
	m_catalogSearchMode=2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名";
	m_catalogSearchMode=3;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N11Click(TObject *Sender)
{
  tlbtn5->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N21Click(TObject *Sender)
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


void __fastcall TfrmProcureMng::BtnClearClick(TObject *Sender)
{
   if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = userid;
		li.storageID = stgid;
		frm->PrintType = 2;//采购
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString,0);

		/*frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;



		frm->RvSystem1->DefaultDest  = rdPreview ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;   */
		dsetNote->Last();
		frm->num = dsetNote->FieldByName("xuhao")->AsAnsiString ;
        frm->pxbk = printbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;
		frm->shaddress = shaddress;
		frm->shtel = shtel;
		frm->shcontact = shcontact;

		frm->previewprint(1,4);

		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N22Click(TObject *Sender)
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

void __fastcall TfrmProcureMng::N12Click(TObject *Sender)
{
  BtnClear->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
	if (Key == '\r')
	{
	 // Perform(WM_NEXTDLGCTL, 0, 0);
	  edtCatalog->Text = "";

      if (chfoceset->Checked) {
			if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbnbedtAmount->SetFocus();
				}
			}
			else if (chfsdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbnbedtDiscount->SetFocus();
				}
			}
		}
		else
		{
			edtCatalog->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::FormResize(TObject *Sender)
{
 //dbgrdNote->Height = 389;
  //dbgrdNote->Width = 708;

}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode=6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::dbnbedtTotalAmountKeyPress(TObject *Sender, wchar_t &Key)

{
       if (Key == '\r')
	{
	  Perform(WM_NEXTDLGCTL, 0, 0);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::cbstateChange(TObject *Sender)
{
	UpdateNtHeader();
}
//---------------------------------------------------------------------------

void  TfrmProcureMng::FindNote(String code)
{
	DelInvalidNtHeader();
	edtCatalog->Text = "";
	edtQryVendor->Text = "";
	VendorView();
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







void __fastcall TfrmProcureMng::N6Click(TObject *Sender)
{
	for (int i = 1; i <= dsetNote->RecordCount; i++) {
		dbgrdNote->DataSource->DataSet->RecNo = i;
		dbgrdNote->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmProcureMng::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {    //查单
		if (!RzToolButton1->Enabled ) {
			return;
		}
		RzToolButton1->Click();
	}
	if (Key == VK_F2) {   //增单
		if (!mtbbtnAddNtHeader->Enabled ) {
			return;
		}
		mtbbtnAddNtHeader->Click();
	}
	if (Key == VK_F3) {   //保存
		if (!BtnSave->Enabled ) {
			return;
		}
		BtnSave->Click();
	}
	if (Key == VK_F4) {   //修改
		if (!BtnProperties->Enabled ) {
			return;
		}
		BtnProperties->Click();
	}
	if (Key == VK_F5) {  //删行
		if (!tlbtn2->Enabled ) {
			return;
		}
		tlbtn2->Click();
	}
	if (Key == VK_F6) {   //统一
		if (!tlbtn3->Enabled ) {
			return;
		}
		tlbtn3->Click();
	}
	if (Key == VK_F7) {   //现场收款
		if (!RzToolButton2->Enabled ) {
			return;
		}
		RzToolButton2->Click();
	}
	if (Key == VK_F8) {   //导出
		if (!tlbtn4->Enabled ) {
			return;
		}
		tlbtn4->Click();
	}
	if (Key == VK_F9) {   //删单
		if (!tlbtn1->Enabled ) {
			return;
		}
		tlbtn1->Click();
	}
	if (Key == VK_F10) {  //打印
		if (!tlbtn5->Enabled ) {
			return;
		}
		tlbtn5->Click();
	}
	if (Key == VK_F11) {  //预览
		if (!BtnClear->Enabled ) {
			return;
		}
		BtnClear->Click();
	}

	if (Shift.Contains(ssAlt)&& Key == 88) {    //期刊
		if (chqikan->Checked ) {
			chqikan->Checked = false;
		}
		else
		{
			chqikan->Checked = true;
		}
		chqikan->OnClick ;
	}
	if (Shift.Contains(ssAlt)&& Key == 67) {    //定位
		SpeedButton1->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {
		WindowState = wsNormal  ;
	}
	if (Shift.Contains(ssAlt)&& Key ==81  ) {
	   tlbtn7->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 70 ) {   //查书
	   BtnView->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {
	   BtnAlignBottom->Click();
	}
}
//---------------------------------------------------------------------------
void TfrmProcureMng::VendorView()
{
		edtQryVendor->Text = "";
		AnsiString sql;
		sql = " select * from CUST_CustomerInfo where Type =1 order by name";
		dsetVendor->Active = false;
		dsetVendor->CommandText = sql;
		dsetVendor->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
    	if (chfoceset->Checked) {
			if (chfsdiscount->Checked) {
				dbnbedtDiscount->SetFocus();
			}
			else if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbnbedtAmount->SetFocus();
				}
			}
		}
		else
		{
			dbnbedtDiscount->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::RzButton1Click(TObject *Sender)
{
	String ID;
	ID = "";
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		int count1 = dsetVendor->RecordCount;

	   //	TDetaileForm * frm = new TDetaileForm(m_app,2,1,ID.c_str() ,m_con);
	   TDetaileForm * frm = new TDetaileForm(m_app,1,1,ID.c_str() ,m_con);
		frm->ShowModal();
		delete frm;

		dsetVendor->Active = false;
		dsetVendor->Active = true;
		int count2 = dsetVendor->RecordCount;
		if (count2 > count1)
		{
			dsetVendor->Last();
			dsetNtHeader->Edit();
			dsetNtHeader->FieldByName("VendorID")->AsInteger = dsetVendor->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::spnewbookClick(TObject *Sender)
{
	//新书目
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
	   Tfrmnewbook1 *frm = new Tfrmnewbook1(m_app,m_con);
	   frm->ProcureMng = this;
	   frm->modle = 3;//采购
	   if (chqikan->Checked) {
			frm->cbsaletype->Text = "期刊";
			frm->cbsaletypeChange(this);
	   }
	   if (mbOK == frm->ShowModal())
	   {
			edtCatalog->Text  = "";
			dbnbedtAmount->Text = "0";
			dbnbedtDiscount->Text = "100";
			dbnbedtAmount->SetFocus();
	   }else
	   {
			edtCatalog->SetFocus();
	   }
	   delete frm;
	   return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::BtnViewClick(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,m_con,m_storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void TfrmProcureMng::historyview()
{
	AnsiString sql;
	sql = "select BS_ProcureNote.Amount,BS_ProcureNote.RecAmount,BS_ProcureNote.Discount,BS_ProcureNoteHeader.ProcureNtCode,"
		" BS_ProcureNoteHeader.HdTime,CUST_CustomerInfo.Name "
		" from BS_ProcureNote left join BS_ProcureNoteHeader on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id "
		" left join CUST_CustomerInfo on BS_ProcureNoteHeader.SupplierID = CUST_CustomerInfo.id "
		" where BS_ProcureNoteHeader.stgid = " + IntToStr(stgid)  + " and BS_ProcureNote.BkcatalogID =  " + dsetNote->FieldByName("BkcatalogID")->AsString +
		" union "
		" select BS_ZN_ProcureNote.Amount,BS_ZN_ProcureNote.RecAmount,BS_ZN_ProcureNote.Discount,BS_ZN_ProcureNoteHeader.ZNProcureNtCode,"
		" BS_ZN_ProcureNoteHeader.HdTime,CUST_CustomerInfo.Name "
		" from BS_ZN_ProcureNote left join BS_ZN_ProcureNoteHeader on BS_ZN_ProcureNote.ZNProcureNtHeaderID = BS_ZN_ProcureNoteHeader.id "
		" left join CUST_CustomerInfo on BS_ZN_ProcureNote.SupplierID = CUST_CustomerInfo.id "
		" where BS_ZN_ProcureNoteHeader.stgid = " + IntToStr(stgid)  + " and BS_ZN_ProcureNote.BkcatalogID = " + dsetNote->FieldByName("BkcatalogID")->AsString  ;
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::dbgrdNoteCellClick(TColumn *Column)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	editdetailbk->Text = dsetNote->FieldByName("clientname")->AsAnsiString ;
	editremarks->Text= dsetNote->FieldByName("backto")->AsAnsiString ;
	historyview();
}
//---------------------------------------------------------------------------


void __fastcall TfrmProcureMng::DBNavigator1Click(TObject *Sender, TNavigateBtn Button)

{
	QryNtHeader(aqheader->FieldByName("id")->AsInteger);
}
//---------------------------------------------------------------------------
void  TfrmProcureMng::operterview(int operterid)
{
	AnsiString sql;
	sql = "select name from sys_user where id = " + IntToStr(operterid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	lblOpName->Caption = query->FieldByName("name")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::membkExit(TObject *Sender)
{
	dsetNtHeader->Edit();
	dsetNtHeader->FieldByName("Remarks")->AsAnsiString = membk->Text ;
	UpdateNtHeader();
}
//---------------------------------------------------------------------------


void __fastcall TfrmProcureMng::SpeedButton1Click(TObject *Sender)
{
	if (GroupBox3->Visible) {
		GroupBox3->Visible = false;
	}
	else
	{
		GroupBox3->Visible = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::BtnPropertiesClick(TObject *Sender)
{

	GroupBox1->Enabled = true;
	dblkpcbbVendorID->Enabled = true;
	edtQryVendor->Enabled = true;
	dblkpcbbStaffID->Enabled = true;
	dbnbedtAddCosts->Enabled = true;
	cbstate->Enabled = true;
	RzButton1->Enabled = true;
	dbdtedtHdTime->Enabled = true;
	dbdtedtHdyujiTime->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::BtnSaveClick(TObject *Sender)
{
	if (!edtQryVendor->Enabled) {
		return;
	}
	try
	{
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("Remarks")->AsAnsiString = membk->Text ;
		UpdateNtHeader();

	}
	catch(...)
	{
	   MessageBoxA(0,"保存失败，请重试!","警告",MB_ICONEXCLAMATION);
	   return;
	}
	//GroupBox1->Enabled = false;
	edtQryVendor->Enabled = false;
	dblkpcbbStaffID->Enabled = false;
	dbnbedtAddCosts->Enabled = false;
	cbstate->Enabled = false;
	RzButton1->Enabled = false;
	dbdtedtHdTime->Enabled = false;
	dbdtedtHdyujiTime->Enabled = false;
	dblkpcbbVendorID->Enabled = false;
	BtnSave->Enabled=false;

	GroupBox2->Enabled = true;
	spnewbook->Enabled = true;
	edtCatalog->SetFocus();
}
void TfrmProcureMng::clearbkinfo()
{
 editremarks->Text ="";
 editdetailbk->Text="";

}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::chfsluruClick(TObject *Sender)
{
	if (chfsluru->Checked ) {
		chfoceset->Checked = true;
	}
	else if (chfsamount->Checked ) {
		chfoceset->Checked = true;
	}
	else if (chfsdiscount->Checked ) {
		chfoceset->Checked = true;
	}
	else
	{
		chfoceset->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::chqikanClick(TObject *Sender)
{
	if (chqikan->Checked ) {
		edqikan->Visible = true;
		if (m_catalogSearchMode == 1) {
			edtCatalog->MaxLength = 15;
		}
		else
		{
			edtCatalog->MaxLength = 0;
		}
	}
	else
	{
		edqikan->Visible = false;
		if (m_catalogSearchMode == 1) {
			edtCatalog->MaxLength = 13;
		}
		else
		{
			edtCatalog->MaxLength = 0;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N7Click(TObject *Sender)
{
	lblCatalog->Caption = "作者";
	m_catalogSearchMode=5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::edqikanKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (m_catalogSearchMode == 6) {
        	float price;
				try {
					price = StrToFloat(edtCatalog->Text.Trim());
				} catch (...) {
					MessageBox(0,"请输入正确的定价！","采购" ,MB_ICONEXCLAMATION);
					return;
				}
			}

        TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = userid;
		li.storageID = stgid;
		frm->Init(&li);
		frm->DoModalType = 5;
		frm->Procurefrm  = this;
		frm->qikan = chqikan->Checked ;
		frm->qikanhao = edqikan->Text ;
		frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);

		if (mrOk == frm->ShowModal())
		{
			int supplierID = -1,catalogID = -1;
			frm->GetSelectResult(supplierID, catalogID);
			supplierID = dsetVendor->FieldByName("ID")->AsInteger ;
			if (frm->SelectAll) {
				supplierID = dsetVendor->FieldByName("ID")->AsInteger ;
				for (int i = 0; i < frm->lengthint  ; i++) {
					if (AddNote(supplierID,frm->BkcatalogiD[i])) {
						Key = 0;
						Perform(WM_NEXTDLGCTL, 0, 0);
						dbnbedtAmount->SetFocus();
					}
					historyview();
				 }
			}
			else
			{
				if (supplierID >= 0 && catalogID >= 0)
				{
					TLocateOptions   Opts;
					Opts.Clear();
					Opts   <<   loPartialKey;
					String   str   = AnsiString(catalogID);
					if ( !dsetNote->Locate("BkcatalogID",str,Opts))
					{
						if (AddNote(supplierID, catalogID))
						{
							if (addnotereturnvalue == -2) {
								addnotereturnvalue = 0;
							} else
							{
								Key=0;
								historyview();
								if (chfoceset->Checked) {
									if (chfsamount->Checked ) {
										dbnbedtAmount->SetFocus();
									}
									else if (chfsdiscount->Checked ) {
										dbnbedtDiscount->SetFocus();
									}
									else if (chfsluru->Checked) {
										edtCatalog->SetFocus();
									}
								}
								else
								{
									dbnbedtAmount ->SetFocus();
								}
							}
						}
						else
							ShowMessage("库存无该书!");
					}
					else
						{
							dbgrdNote->SelectedRows->CurrentRowSelected = true;
							dbgrdNote->SetFocus();
							dbnbedtAmount->SetFocus();
						}
				}
			}
		}
		else {
			if (!frm->findbook) {     //产生新书
				if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
				{
					Tfrmnewbook1 *frma = new Tfrmnewbook1(m_app,m_con);
					frma->ProcureMng = this;
					frma->modle = 3;

					if (chqikan->Checked) {
						frma->cbsaletype->Text = "期刊";
						frma->cbsaletypeChange(this);
						frma->editqikanmao->Text =edtCatalog->Text + edqikan->Text;
						PostMessage(frma->editqikanmao->Handle, WM_KEYDOWN,VK_RETURN,0);
					}
					else
					{
						frma->editcode->Text = edtCatalog->Text ;
						PostMessage(frma->editcode->Handle, WM_KEYDOWN,VK_RETURN,0);
					}
					if (mbOK == frma->ShowModal())
					{
					}
					delete frma;
					dbnbedtAmount->SetFocus();
				}
			}
		}
		edtCatalog->Text = "";
		edqikan->Text = "";
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::BtnWeekViewClick(TObject *Sender)
{

		/*Tfrmorderquery *frm = new Tfrmorderquery(Application,m_con,0,100,0);     //调用订单中的查单模块
		if (frm->ShowModal()==mrOk ) {
		  //	dbn->Enabled = true;
		  LandInfo li;
		  li.app = Application;
		  li.con =m_con;
		  li.userID = userid ;
		  li.storageID = stgid ;
		   AnsiString code = frm->GetNoteCode();
		  delete frm;
		   TfrmBIorder * frmorder = new TfrmBIorder(NULL);
		   frmorder->init(&li);
		   frmorder->RefreshHead(code);
		   frmorder->cbtype->Enabled = false;
		   frmorder->Show();    */
	if (dsetNtHeader->FieldByName("id")->AsAnsiString == "" ) {
		return;
	}
	Tfrminorder *frm = new Tfrminorder(Application,m_con,m_storageID,m_userID,dsetNtHeader->FieldByName("id")->AsInteger );
	frm->pro = this;
	frm->supplierid = dsetNtHeader->FieldByName("VendorID")->AsInteger;
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------



void __fastcall TfrmProcureMng::dbgrdNoteDblClick(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
        if (bcatalogmodify) {
              return ;
        }

         if (dblclicklock) {
             return;
        }

	TfrmNewBookModify * frm = new TfrmNewBookModify(Application,m_con,dsetNote->FieldByName("BkcatalogID")->AsInteger,m_storageID,m_userID);
	frm->ShowModal();
	delete frm;
	QryNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N8Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con,m_storageID,dsetNote->FieldByName("BkcatalogID")->AsInteger ,m_userID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------


void __fastcall TfrmProcureMng::BtnFinishClick(TObject *Sender)
{
	if (dsetNtHeader->IsEmpty() ) {
        return;
	}
	Tfrmretailbookup *frm = new Tfrmretailbookup(Application,m_con,m_storageID,m_userID);
	frm->Pro  = this;
	frm->modle = 3;
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::editdetailbkKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		if (dsetNote->IsEmpty() ) {
			return;
		}
		dsetNote->Edit() ;
		dsetNote->FieldByName("clientname")->AsAnsiString  = editdetailbk->Text ;
		dsetNote->UpdateBatch(arCurrent);
		if (edtCatalog->Enabled ) {
			edtCatalog->SetFocus();
		}
	}
}
void TfrmProcureMng::lock(int type)
{
    if (type==1) {
        BtnSave->Enabled=false;
        BtnProperties->Enabled=false;
        tlbtn1->Enabled=false;
        tlbtn2->Enabled=false;
        tlbtn3->Enabled=false;
        RzToolButton2->Enabled=false;
        BtnWeekView->Enabled=false;
        BtnFinish->Enabled=false;
        edtQryVendor->Enabled=false;
        dblkpcbbVendorID->Enabled=false;
        RzButton1->Enabled=false;
        dbdtedtHdTime->Enabled=false;
        dbdtedtHdyujiTime->Enabled=false;
        cbstate->Enabled=false;
        dblkpcbbStaffID->Enabled=false;
        dbnbedtAddCosts->Enabled=false;
        membk->Enabled=false;
        edtCatalog->Enabled=false;
        dbnbedtAmount->Enabled=false;
        dbnbedtDiscount->Enabled=false;
        chqikan->Enabled=false;
        editdetailbk->Enabled=false;
       // imglock->Visible= true;
       lblock->Caption = "已锁定";
        selectmenu->AutoPopup = false;
        spnewbook->Enabled=false;
        dblclicklock=true;

    }else
    {
    dblclicklock=false;
    spnewbook->Enabled=true;
            BtnSave->Enabled=true;
        BtnProperties->Enabled=true;
        tlbtn1->Enabled=true;
        tlbtn2->Enabled=true;
        tlbtn3->Enabled=true;
        RzToolButton2->Enabled=true;
        BtnWeekView->Enabled=true;
        BtnFinish->Enabled=true;
	  //  edtQryVendor->Enabled=true;
	   // dblkpcbbVendorID->Enabled=true;

          if (newsupplier) {
                  RzButton1->Enabled = true;
                }else RzButton1->Enabled = false;

	  //  dbdtedtHdTime->Enabled=true;
	   // dbdtedtHdyujiTime->Enabled=true;
	   // cbstate->Enabled=true;
	 //   dblkpcbbStaffID->Enabled=true;
	 //   dbnbedtAddCosts->Enabled=true;
	  //	membk->Enabled=true;
        edtCatalog->Enabled=true;
        dbnbedtAmount->Enabled=true;
        dbnbedtDiscount->Enabled=true;
        chqikan->Enabled=true;
        editdetailbk->Enabled=true;
     //   imglock->Visible= false;
     lblock->Caption = "";
        selectmenu->AutoPopup = true;
        disablenewsupplierornewbook();

    }

}
void TfrmProcureMng::checknewsupplier()
{
   AnsiString sql;
   sql = "select * from sys_lock_table where lockname in('bookcatalog','supplier') and stgid ="+IntToStr(stgid);
    TADOQuery *aq = new TADOQuery(Application);
    aq->Connection = m_con;
    aq->Close();
    aq->SQL->Clear();
    aq->SQL->Add(sql);
    aq->Open();
    aq->First();
    if (aq->FieldByName("lockname")->AsAnsiString=="bookcatalog") {
        bookcatalogadd=aq->FieldByName("lockadd")->AsBoolean;
        bcatalogmodify=aq->FieldByName("lockmodify")->AsBoolean;
    }else
    {
       supplier =aq->FieldByName("lockadd")->AsBoolean;
    }

    aq->Next();
    if (aq->FieldByName("lockname")->AsAnsiString=="bookcatalog") {
        bookcatalogadd=aq->FieldByName("lockadd")->AsBoolean;
        bcatalogmodify=aq->FieldByName("lockmodify")->AsBoolean;
    }else
    {
       supplier =aq->FieldByName("lockadd")->AsBoolean;
    }
    delete aq;
}
void TfrmProcureMng::disablenewsupplierornewbook()
{

     //bool  supplier,bookcatalogadd,bcatalogmodify;
     if (supplier) {
        RzButton1->Enabled = false;
     }
     if (bookcatalogadd) {
          spnewbook->Enabled = false;
     }
}

//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::RzToolButton2Click(TObject *Sender)
{
///短信模板设置
Tfrmshortmessage *frm  = new Tfrmshortmessage(Application);


adoshurtmsg->Close();
adoshurtmsg->SQL->Clear();
adoshurtmsg->SQL->Add("select * from dbo.C_ShortMsgModal order by atype");
adoshurtmsg->Open();
frm->memo1->Lines->Add(adoshurtmsg->FieldByName("ShutMsgModal")->AsAnsiString);
adoshurtmsg->Next();
frm->Memo2->Lines->Add(adoshurtmsg->FieldByName("ShutMsgModal")->AsAnsiString);
if (frm->ShowModal()==mrOk) {
	 ShortMsgSP->ProcedureName="C_updateShortModal";
	 ShortMsgSP->Parameters->Refresh();
	 ShortMsgSP->Parameters->ParamByName("@SMsg1")->Value=frm->memo1->Text;
	 ShortMsgSP->Parameters->ParamByName("@SMsg2")->Value=frm->Memo2->Text;
	 ShortMsgSP->ExecProc();
     MessageBoxA(0,"更新成功!","提示",MB_ICONEXCLAMATION);
}
delete frm;
}

void TfrmProcureMng::syncbackinfo(int IsSendMsg)
{

	   AnsiString timestr;
	   timestr = FormatDateTime("yyyy-MM-dd",Now());
	 try
	 {
	 editremarks->Text=editremarks->Text+"("+timestr+")";
	 ShortMsgSP->ProcedureName="C_BackToOrderFormCaiGou";
	 ShortMsgSP->Parameters->Refresh();
	 ShortMsgSP->Parameters->ParamByName("@caigouDetail")->Value=dsetNote->FieldByName("id")->AsInteger;
	 ShortMsgSP->Parameters->ParamByName("@backto")->Value=Trim(editremarks->Text);
	 ShortMsgSP->Parameters->ParamByName("@IssendMsg")->Value=IsSendMsg;
	 ShortMsgSP->ExecProc();
	 //刷新明细
	 }
	 catch (Exception &E) {
												//+AnsiString(E.Message)
			MessageBox(Handle,"同步订单回告失败!详细信息","同步提示",MB_ICONWARNING);
		}







}
//---------------------------------------------------------------------------


void __fastcall TfrmProcureMng::editremarksKeyPress(TObject *Sender, wchar_t &Key)

{
if (Key == VK_RETURN) {
		if (dsetNote->IsEmpty() ) {
			return;
		}
		if ((cbbackto->Checked)&&ISCOrder(dsetNote->FieldByName("COrderDetailID")->AsAnsiString)) {
			if(MessageBox(0,"该书有C网订单，是否要向客户发送短信？" ,"确认" ,MB_ICONQUESTION|MB_OKCANCEL)==1)
			{
				syncbackinfo(1);
			}

		QryNtHeader(aqheader->FieldByName("id")->AsInteger);
		} else
		{
		 syncbackinfo(0);
		 QryNtHeader(aqheader->FieldByName("id")->AsInteger);
		}
		 //同步B网不需要发送短信
}
}
bool TfrmProcureMng::ISCOrder(AnsiString OrderID)
{
   TStringList *str;
  str = new TStringList();
	bool delimitresult;
	delimitresult=false;
   str->Delimiter =',';
   str->DelimitedText =OrderID;
   for (int i=0; i < str->Count; i++) {
	 if (str->Strings[i]!="-1") {
		 delimitresult=true;
		 break;
	 }
   }
   return delimitresult;

}
//---------------------------------------------------------------------------

