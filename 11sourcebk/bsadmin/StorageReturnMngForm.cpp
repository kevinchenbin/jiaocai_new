//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StorageReturnMngForm.h"
#include <systdate.h>
#include "NoteCode.h"
#include "QryNoteCodeForm.h"
#include "SetNotesForm.h"
#include "mytrace.h"
#include "Print.h"
#include "pdtypes.h"
#include "..\catalogadmin\catalogadmin.h"
//#include "..\customer\customer.h"
#include "..\supplier\detailemessage.h"
#include "Dialogs.hpp"
#include "NewBookinput.h"
#include "NewBookModify.h"
#include "bookQuery.h"
#include "RecMoneyForm.h"
#include "QueryDanHao.h"
#include "Addsyslog.h"
#include   <math.h>
#include "Unitcaigouquery.h"
#include "SelectCatalogForm.h"
#include "bookhistory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzCommon"
#pragma link "RzDBLook"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TfrmStorageReturnMng *frmStorageReturnMng;
//---------------------------------------------------------------------------
__fastcall TfrmStorageReturnMng::TfrmStorageReturnMng(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_catalogSearchMode(0)
	, m_bsmode(BSUnknown)
	, m_opmode(OPUnknown)
{
	m_module = MTStorageMng;
	m_catalogSearchMode = 1;
	this->WindowState = wsMaximized ;
	stackchange = false;
}

void TfrmStorageReturnMng::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = "#,##0.00";

	lblOpName->Caption = li->UserName ;
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
	dsetSupplier->Connection = m_con;
	dsetStaff->Connection = m_con;
	dsetLkpSupplier->Connection = m_con;
	adospupdatewsaleprice->Connection = m_con;
	adospcopy->Connection = m_con;
	dsetCatalog->Connection = m_con;
	spsave->Connection = m_con;
	querydan->Connection = m_con;
	sptuihuo->Connection = m_con;
   //	dsetBkstack->Connection = m_con;
  ///	dsetBkstack->Active = true;
	GetBkStackInfo();
	query->Connection = m_con;
	qudetail->Connection = m_con;
	qrystorge->Connection = m_con;
	dsetCatalog->Active = true;
	dsetSupplier->Active = true;
	dsetStaff->Active = true;
	ChangeCatalogSearchMode();
	dblkpcbbSupplierID->KeyValue = 0;
	//退货密码是否启用
	String sql;
	sql = "select * from SYS_BSSET where name = 'rkusetuihuo'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	tuihuopassword  = query->FieldByName("value")->AsBoolean ;
	if (tuihuopassword) {
		if (!CheckOperateAuthority()) {
			Close();
			return;
		}
	}
	ChangeBsmode(BSNoteSendback);
	RzToolButton5Click(BtnNew);
	sql = "select ID,Name from SYS_StorageInfo where id = " + IntToStr(li->storageID) ;
	qrystorge->Close();
	qrystorge->SQL->Clear();
	qrystorge->SQL->Add(sql);
	qrystorge->Open();
	while (!qrystorge->Eof )
	{
		cbstorgename->AddObject(qrystorge->FieldByName("Name")->AsString ,(TObject*)qrystorge->FieldByName("ID")->AsInteger );
		qrystorge->Next();
	}
	cbstorgename->ItemIndex = (int)(cbstorgename->Items->IndexOfObject((TObject*)li->storageID ));
	cbstorgename->Enabled = false;
	edStoryNum->Text = IntToStr((int)(cbstorgename->Items->Objects[cbstorgename->ItemIndex]));
	edStoryNum->Enabled = false;
	ChangeOpmode(OPAddNtHeader);
	sql = "select * from SYS_BSSET where name = 'storageday'" ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("value")->AsBoolean  ) {
		dgdetail->Visible = true;
	}
	else
	{
		dgdetail->Visible = false;
	}
	sql = "select * from SYS_BSSET where name = 'xiaoshudian'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	format = "￥###,###,##" + query->FieldByName("bk")->AsString ;
	RzDBNumericEdit3->DisplayFormat = "￥###,###,##0.00";
	RzDBNumericEdit4->DisplayFormat = format;

    sql = "select rkprinttitle,rkcontact,rktel,rkaddress,rkprintbk from sys_printtitle where stgid = " + IntToStr(m_storageID);
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	rkbk = query->FieldByName("rkprintbk")->AsAnsiString ;
	printtitle = query->FieldByName("rkprinttitle")->AsAnsiString ;
	contact = query->FieldByName("rkcontact")->AsAnsiString ;
	tel = query->FieldByName("rktel")->AsAnsiString ;
	address = query->FieldByName("rkaddress")->AsAnsiString ;

	/*sql = "select bk from sys_bsset where value = 1 and name = 'rkprintbk'" ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	rkbk = query->FieldByName("bk")->AsAnsiString ;  */

	sql = "select * from SYS_BSSET where name = 'rktuihuoguanli'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	rktuihuoguanli  = query->FieldByName("value")->AsBoolean ;

    //change danhao
	sql = "select * from SYS_BSSET where name = 'changeDanHaoDisplay'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	ChangeDisplay  = query->FieldByName("value")->AsBoolean ;

	if (ChangeDisplay) {
	  editdanhao->Visible = true;
	  dbedtStgNtCode->Visible = false;
	   DBNav->Visible = true;
	   dgdetail->Columns->Items[1]->Visible = true;
	   dgdetail->Columns->Items[0]->Visible = false;
	}else
	{
	  editdanhao->Visible = false;
	  dbedtStgNtCode->Visible = true;
	  /*Sbutfirst->Visible = true;
		Sbutbefore->Visible = true;
		Sbutnext->Visible = true;
		Sbutend->Visible = true;
		DBNav->Visible = false; */
		dgdetail->Columns->Items[1]->Visible = false;
		dgdetail->Columns->Items[0]->Visible = true;
	}
	//所有供应商历史明细
	sql = "select * from SYS_BSSET where name = 'rkallsupplier'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	allsupplier  = query->FieldByName("value")->AsBoolean ;
	//查单密码是否启用
	sql = "select * from SYS_BSSET where name = 'rkusefind'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	findpassword  = query->FieldByName("value")->AsBoolean ;
	//删单密码是否启用
	sql = "select * from SYS_BSSET where name = 'rkusedelete'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	deletepassword  = query->FieldByName("value")->AsBoolean ;
	//修改单头密码是否启用
	sql = "select * from SYS_BSSET where name = 'rkusechange'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	changepassword  = query->FieldByName("value")->AsBoolean ;

	sql = "select * from SYS_BSSET where name = 'storagesametishi'" ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	sameid =   query->FieldByName("value")->AsBoolean ;




          if (li->FormatStr=="1") {
            newsupplier=true;
            sbnewcustomer->Enabled = true;
          }else {newsupplier = false;
          sbnewcustomer->Enabled = false;}

          checknewsupplier();



	FormView();
}
void TfrmStorageReturnMng::GetBkStackInfo()
{
   AnsiString sql= "select   name , ID from STK_BookstackInfo where StgID = " + IntToStr(m_storageID);
   TADOQuery *aq  = new TADOQuery(Application);
  try
  {

   aq->Connection = m_con ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   while(!aq->Eof)
   {
	 cbbkstackID->AddItem(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger);
	 aq->Next();
   }
   cbbkstackID->ItemIndex = 0;
  }
  __finally
  {
	delete aq;
  }
}
void TfrmStorageReturnMng::ChangeCatalogSearchMode()
{
  /*	if (!chckbxSwitch->Checked)
	{
        return;
	}

	m_catalogSearchMode++;
	if (m_catalogSearchMode >= 4)
	{
		m_catalogSearchMode = 1;
	}

	switch (m_catalogSearchMode)
	{
	case 1:
		edtCatalog->MaxLength = 13;
		lblCatalog->Caption = "书        号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
    	lblCatalog->Caption = "自  编  码";
		break;
	case 3:
        edtCatalog->MaxLength = 0;
    	lblCatalog->Caption = "书        名";
    	break;
    default:
		break;
	}   */
}

void TfrmStorageReturnMng::ChangeBsmode(BSMode bsmode)
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

void TfrmStorageReturnMng::ChangeOpmode(OPMode opmode)
{
   //	if (opmode == m_opmode
   //		&& (opmode == OPDelNtHeader))
   //		return;

	//1为查单模式 2为添加单头模式 3为删除单头模式 4为添加单模式 5为删除单模式 6为统一模式 7为现场收款模式
	switch (opmode)
	{
	case OPFind:
		{
			if (!SaveStorage(1))
			{
				return;
			}


			if (findpassword) {
            	if (!CheckOperateAuthority())
					return;
			}
			DBNav->Enabled = true;

			Tfrmcaigouquery* frm = new Tfrmcaigouquery(Application,m_con,m_storageID,2,1);
				if (frm->ShowModal() == mrOk)
				{
                    String sql;
					sql = " select * from CUST_CustomerInfo where Type =1 order by name ";
					dsetSupplier->Active = false;
					dsetSupplier->CommandText = sql;
					dsetSupplier->Active = true;
					dsetSupplier->First();
					dblkpcbbSupplierID->KeyValue = dsetSupplier->FieldByName("ID")->AsInteger ;

					DelInvalidNtHeader();
					edtCatalog->Text = "";
					edtQrySupplier->Text = "";
					AnsiString code = frm->GetNoteCode();
					AnsiString sqlwhere = frm->GetWhere();
					try
					{
						QryNtHeader(code);
						String sql,codetmp;
						if (sqlwhere != "") {
							sql = "select * from BS_StorageNoteHeader " + sqlwhere;
							querydan->Close();
							querydan->SQL->Clear();
							querydan->SQL->Add(sql);
							querydan->Open();
							TLocateOptions Opts;
							Opts.Clear();
							Opts << loPartialKey;
							querydan->Locate("StgNtCode", code, Opts);
						}
					}
					__finally
					{
					}
					m_opmode = opmode;
					dtpdate->Date = dbdtedtHdTime->Date;
					delete frm;
					SaveOrNot = true;
					BtnSave->Enabled = false;
					dblkpcbbSupplierID->Enabled = false;
					sbnewcustomer->Enabled = false;
					//dbedtSupplySN->Enabled = false;
					dbnbedtAddCosts->Enabled = false;
				}

			/*if (ChangeDisplay) {
            	TfrmQuery * frm = new TfrmQuery(this);
				frm->Init(&linfo);
				if (frm->ShowModal() == mrOk  )
				{
				   //	DBNav->Enabled = true;
					edtCatalog->Text = "";
					edtQrySupplier->Text = "";

				  AnsiString sql;
				  if (frm->RDanhao) {  //按单号来查询
					  sql = "select * from BS_StorageNoteHeader where  TStgNtCodeInt between ";
					  sql = sql + IntToStr(frm->Max) + " and " + IntToStr(frm->Min) + " and totalamount <= 0";
				  }else
				  {
					   sql = "select * from BS_StorageNoteHeader where  hdtime between '";
					   sql = sql + DateToStr(frm->FMax )  + " 0:00:00' and '" + DateToStr(frm->TMin) + " 23:59:59' and totalamount <= 0";
				  }
					querydan->Close();
					querydan->SQL->Clear();
					querydan->SQL->Add(sql);
					querydan->Open();
					querydan->First();
					QryNtHeader(querydan->FieldByName("StgNtCode")->AsAnsiString  );
					editdanhao->Text = querydan->FieldByName("StgNtCodeStr")->AsAnsiString ;

					m_opmode = opmode;
					dtpdate->Date =  dbdtedtHdTime->Date ;//更新日期
					delete frm;
					SaveOrNot = true;
					BtnSave->Enabled = false;
					dblkpcbbSupplierID->Enabled = false;
					sbnewcustomer->Enabled = false;
					dbedtSupplySN->Enabled = false;
					dbnbedtAddCosts->Enabled = false;
					dbedtRemarks->Enabled = false;
			   }
			}
			else
			{
				TfrmQryNoteCode* frm = new TfrmQryNoteCode(this,1);
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
					edtQrySupplier->Text = "";
					String code = frm->GetNoteCode();
					try
					{
					//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
						QryNtHeader(code);
						String sql,codetmp;
						codetmp = code;
						/*if (codetmp != "") {
							codetmp = codetmp.SubString(0,10);
							if (m_bsmode == BSNote) {
								sql = "select StgNtCode from BS_StorageNoteHeader where StgNtCode >= " +  codetmp + "00000 and StgNtCode <= " + codetmp + "09999";
							}
							else
							{
								sql = "select StgNtCode from BS_StorageNoteHeader where StgNtCode >= " +  codetmp + "10000 and StgNtCode <= " + codetmp + "99999";
							}
							query->Close();
							query->SQL->Clear();
							query->SQL->Add(sql);
							query->Open();
							query->Last();
							codetmp = query->FieldByName("StgNtCode")->AsString ;
						}
						MaxNote = codetmp;
						if (MaxNote.Length() == 13 ) {
							MaxNote = "00" + MaxNote;
						}
						else if (MaxNote.Length() == 14 ) {
							MaxNote = "0" + MaxNote;
						} *
						if (codetmp != "") {
							codetmp = codetmp.SubString(0,10);
							sql = "select * from BS_StorageNoteHeader where StgNtCode >= " +  codetmp + "10000 and StgNtCode <= " + codetmp + "99999";
							querydan->Close();
							querydan->SQL->Clear();
							querydan->SQL->Add(sql);
							querydan->Open();
							querydan->First();
						}
					}
					__finally
					{
					//LockWindowUpdate(NULL);
					}
					m_opmode = opmode;
					dtpdate->Date = dbdtedtHdTime->Date;
					delete frm;
					SaveOrNot = true;
					BtnSave->Enabled = false;
					dblkpcbbSupplierID->Enabled = false;
					sbnewcustomer->Enabled = false;
					dbedtSupplySN->Enabled = false;
					dbnbedtAddCosts->Enabled = false;
					dbedtRemarks->Enabled = false;
				}

			}  */
		}
		break;
	case OPAddNtHeader:
		{
			//如果上次是添加模式，并且没有加进任何数据，则不能添加
			if (m_opmode == OPAddNtHeader &&
				dsetNote->Active && dsetNote->RecordCount < 1)
				DelInvalidNtHeader();

			if (m_opmode == OPDelNote
				&& dsetNote->Active && dsetNote->RecordCount < 1)
				DelInvalidNtHeader();

			edtCatalog->Text = "";
			edtQrySupplier->Text = "";
			AddNtHeader();
			m_opmode = opmode;
			edtQrySupplier->SetFocus();
			dtpdate->Date = dbdtedtHdTime->Date;
        }
		break;
	case OPDelNtHeader:
		{
			if (deletepassword) {
            	if (!CheckOperateAuthority())
					return;
			}
			else
			{
				if (MessageBoxA(0,"是否要删除该单?","询问",MB_ICONQUESTION|MB_OKCANCEL)!=1 )
					return;
			}

			edtCatalog->Text = "";
			edtQrySupplier->Text = "";
			DelNtHeader();
			m_opmode = opmode;
        }
		break;
	case OPAddNote:
    	edtCatalog->Text = "";
		edtCatalog->SetFocus();
		m_opmode = opmode;
		break;
	case OPDelNote:
		{
			if (dsetNote->IsEmpty() ) {
            	return;
			}
			if (MessageBoxA(0,"是否要删除该书目?","询问",MB_ICONQUESTION|MB_OKCANCEL)==1 )
			{
				DelNote();

				ResetNtHeader();
				m_opmode = opmode;
				break;
			}else
			{

			 return;
			}
        }

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
		//现场付款模式
		if (editdanhao->Text == "") {
			return;
		}
		if (!SaveStorage(1))
		{
			return;
		}
        if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
		{
			//首先把修改的更新一下哈
			dbgrdNote->SetFocus();
			//其次把最新数据刷新一下哈
			QryNtHeader();
			//
			/*String NtHeader = dbedtStgNtCode->Text.Trim(),Headerdate;
			if (NtHeader == "" || NtHeader == "0") {
				return;
			}
			if (NtHeader.Length() == 13) {
				Headerdate = NtHeader.SubString(0,4)+ "-" + NtHeader.SubString(5,2) + "-" + NtHeader.SubString(7,2);
			}
			else if (NtHeader.Length() == 14)
			{
				Headerdate = NtHeader.SubString(1,4)+ "-" + NtHeader.SubString(6,2) + "-" + NtHeader.SubString(8,2);
			}
			else if (NtHeader.Length() == 15) {
				Headerdate = NtHeader.SubString(2,4)+ "-" + NtHeader.SubString(7,2) + "-" + NtHeader.SubString(9,2);
			}
			if (StrToDate(Headerdate) != Date()) {
				MessageBox(0,"现场付款只能付当日的！","入库退货单" ,MB_OK);
				return;
			}   */
			if (StrToDate(dsetNtHeader->FieldByName("HdTime")->AsAnsiString ) != Date()  ) {
				MessageBox(0,"现场付款只能付当日的！","入库退货单" ,MB_OK);
				return;
			}
			TfrmRecMoney* frm = new TfrmRecMoney(this);
			frm->SetDiscountedPrice(dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat);
			frm->SetChecked(dsetNtHeader->FieldByName("Checked")->AsFloat);
			if (mrOk == frm->ShowModal())
			{
				if (frm->numedtUnchecked ->Value > 0) {
					if (MessageBox(0,"你还有未付金额，是否继续？","现场付款",MB_ICONQUESTION|MB_OKCANCEL)!=1) {
						frm->ShowModal();
						return;
					}
				}
				AnsiString sql;
				if (dsetNtHeader->FieldByName("Checked")->AsFloat + frm->GetReceived() >= dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat ) {
					sql = "update BS_StorageNoteHeader set Checked = Checked + " + FloatToStr(frm->GetReceived()) + ",State = 1 where id = " + dsetNtHeader->FieldByName("ID")->AsString ;
				}
				else
				{
					sql = "update BS_StorageNoteHeader set Checked = Checked + " + FloatToStr(frm->GetReceived()) + " where id = " + dsetNtHeader->FieldByName("ID")->AsString ;
                }
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
				AnsiString Code = NoteCode::BuildCode(query, GetDBTime(query), 0, "FN_CUSEndMoneyDocuments", "MoneyCode");
				sql = "insert into FN_CUSEndMoneyDocuments (MoneyCode,date,state,type,userid,CustmerName,ClearingType,Clearingstyle) values ("+Code+",getdate(),1,1," + IntToStr(m_userID) +",'" + dblkpcbbSupplierID->Text + "','现场付款','现金')";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
				sql = "insert into FN_CUSEndMoneyDtails(EndMoneyDocumentID,stgntcode,thistime,type,CodeStr) values(" + Code + "," + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString + "," + FloatToStr(frm->GetReceived()) + ",1,'" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString + "')";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
			}
			delete frm;
		}
    	m_opmode = opmode;
    	break;
    default:
        break;
	}
	//ModifyEnable();
	
}

void TfrmStorageReturnMng::AddNtHeader()//添加单头
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNtHeader->Parameters->ParamByName("@CODEMODE")->Value = 1;
	cmdAddNtHeader->Execute();
	int id = cmdAddNtHeader->Parameters->ParamByName("@RETURN_VALUE")->Value;
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

void TfrmStorageReturnMng::QryNtHeader(String code, bool qrybkstack)//查询单头
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	spQryNtHeader1->Parameters->ParamByName("@NtCode")->Value = code;
	spQryNtHeader1->Parameters->ParamByName("@Bsmode")->Value = 1;
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
		//dsetNote->Last();
		dsetNote->AfterScroll = dsetNoteAfterScroll;
		if (dsetNtHeader->FieldByName("TotalAmount")->AsInteger > 0 ){
				dsrcNote->DataSet = NULL;
				dsetNote->AfterScroll = NULL;
				return;
		}
		if (qrybkstack)
		{
			QryBkstack();
		}
		editdanhao->Text = dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		dtpdate->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 ) {
			grpbxNote->Enabled = false;
			BtnChangeOptions->Enabled = false;
			RzToolButton2->Enabled = false;
			RzToolButton3->Enabled = false;
			Image1->Visible = true;
		}
		else
		{
			grpbxNote->Enabled = true;
			BtnChangeOptions->Enabled = true;
			RzToolButton2->Enabled = true;
			RzToolButton3->Enabled = true;
			Image1->Visible = false;
		}
                lock(dsetNtHeader->FieldByName("lock")->AsInteger);
	}
	catch(...)
	{
		//ShowMessage("该单不存在！");
	}
}

void TfrmStorageReturnMng::QryNtHeader(bool qrybkstack)//查询单头
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
		spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
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
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
			operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
			dtpdate->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
			membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
			if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 ) {
				grpbxNote->Enabled = false;
				BtnChangeOptions->Enabled = false;
				RzToolButton2->Enabled = false;
				RzToolButton3->Enabled = false;
				Image1->Visible = true;
			}
			else
			{
				grpbxNote->Enabled = true;
				BtnChangeOptions->Enabled = true;
				RzToolButton2->Enabled = true;
				RzToolButton3->Enabled = true;
				Image1->Visible = false;
			}
                        lock(dsetNtHeader->FieldByName("lock")->AsInteger);
		}
		catch(...)
		{
            //ShowMessage("该单不存在！");
		}
	}
}

void TfrmStorageReturnMng::QryNtHeader(int id, bool qrybkstack)//查询单头
{
	//查询单头
	spQryNtHeader1->Active = false;
	spQryNtHeader->Active = false;
	spQryNtHeader->Parameters->ParamByName("@ID")->Value = id;
	spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
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
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		dtpdate->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 ) {
			grpbxNote->Enabled = false;
			BtnChangeOptions->Enabled = false;
			RzToolButton2->Enabled = false;
			RzToolButton3->Enabled = false;
			Image1->Visible = true;
		}
		else
		{
			grpbxNote->Enabled = true;
			BtnChangeOptions->Enabled = true;
			RzToolButton2->Enabled = true;
			RzToolButton3->Enabled = true;
			Image1->Visible = false;
		}
                lock(dsetNtHeader->FieldByName("lock")->AsInteger);
	}
	catch(...)
	{
    	//ShowMessage("该单不存在！");
    }
}

void TfrmStorageReturnMng::DelNtHeader()//删除单头
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdDelNtHeader->Parameters->ParamByName("@ID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		int id = dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdDelNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
		cmdDelNtHeader->Execute();
		if (ChangeDisplay) {
			logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		}
		else
		{
			logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
		}
		AddEvent(1,"一般入库退货窗口",m_userID,m_storageID,logmessage,linfo.con);
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

void TfrmStorageReturnMng::UpdateNtHeader()//更新单头
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
			membk->Text;
		cmdUpdateNtHeader->Parameters->ParamByName("@SupplySN")->Value =
			dsetNtHeader->FieldByName("SupplySN")->AsWideString;
		cmdUpdateNtHeader->Parameters->ParamByName("@CustomerID")->Value =
			dsetNtHeader->FieldByName("SupplierID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
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

bool TfrmStorageReturnMng::AddNote(int supplierID, int catalogID)//添加单
{
	bool result = false;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetCatalog->Active )
	{
		if (rktuihuoguanli) {
        	AnsiString sql;
			sql = "select * from BS_StorageNote where amount >= 0 and BkInfoID in (select id from stk_bookinfo where stgid = " + IntToStr(m_storageID) + " and SupplierID = " + IntToStr(supplierID) + " and BkcatalogID = " + IntToStr(catalogID) + ")";
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->IsEmpty() ) {
				MessageBox(0,"该书没在此供应商处进过货，不能退货!","提示",MB_ICONEXCLAMATION);
				return true;
			}
		}
		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
		   =catalogID;//	= dsetCatalog->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@SupplierID")->Value
		   =supplierID;//	= dsetNtHeader->FieldByName("SupplierID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 1;
		cmdAddNote->Parameters->ParamByName("@bkstackID")->Value = (int)(cbbkstackID->Items->Objects[cbbkstackID->ItemIndex]);
		MYTRACEF(_T("add note @NtHeaderID=%d,@BkcatalogID=%d,@SupplierID=%d,@Bsmode=%d,@bkstackID=%d")
			, dsetNtHeader->FieldByName("ID")->AsInteger
			, catalogID//dsetCatalog->FieldByName("ID")->AsInteger
			, supplierID//dsetNtHeader->FieldByName("SupplierID")->AsInteger
			, 1);
		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;

		if (ret > 0)//插入成功
		{
			//int bkinfoid = dsetNote->FieldByName("BkInfoID")->AsInteger;
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}

			if (dsetNtHeader->FieldByName("printcount")->AsInteger > 0 || m_userID != dsetNtHeader->FieldByName("OperatorID")->AsInteger ) {
				if (ChangeDisplay) {
					logmessage = "添加一般入库退货单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
				}
				else
				{
					logmessage = "添加一般入库退货单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
				}
				logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
				AddEvent(1,"一般入库退货窗口",m_userID,m_storageID,logmessage,linfo.con);
			}

			result = true;
		}
		else if (ret == 0)//查无此书
		{

		}
		else if (ret == -1)//库存出错了
		{

		}
		else 	if (ret == -2) {
			if (sameid) {
				MessageBox(0,"不能添加相同目录的书!","提示",MB_ICONEXCLAMATION);
			}

            result = true;
		}
	}
	return result;
}

bool TfrmStorageReturnMng::AddNote(int id)
{
	bool result = false;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
        if (rktuihuoguanli) {
        	AnsiString sql;
			sql = "select * from BS_StorageNote where amount >= 0 and BkInfoID in (select id from stk_bookinfo where stgid = " + IntToStr(m_storageID) + " and SupplierID = " + dsetNtHeader->FieldByName("SupplierID")->AsString + " and BkcatalogID = " + IntToStr(id) + ")";
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->IsEmpty() ) {
				MessageBox(0,"该书没在此供应商处进过货，不能退货!","提示",MB_ICONEXCLAMATION);
				return true;
			}
		}
		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
			= id;
		cmdAddNote->Parameters->ParamByName("@SupplierID")->Value
			= dsetNtHeader->FieldByName("SupplierID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 1;
				cmdAddNote->Parameters->ParamByName("@bkstackID")->Value = (int)(cbbkstackID->Items->Objects[cbbkstackID->ItemIndex]);
		MYTRACEF(_T("add note @NtHeaderID=%d,@BkcatalogID=%d,@SupplierID=%d,@Bsmode=%d,@bkstackID=%d")
			, dsetNtHeader->FieldByName("ID")->AsInteger
			, dsetCatalog->FieldByName("ID")->AsInteger
			, dsetNtHeader->FieldByName("SupplierID")->AsInteger
			, 1);
		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
		if (ret > 0)//插入成功
		{
			//int bkinfoid = dsetNote->FieldByName("BkInfoID")->AsInteger;
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			//提示插入相同书目;
			//ShowMessage(dsetNote->Lookup("BkInfoID", bkinfoid, "BkInfoID").VInteger);
			result = true;
		}
		else if (ret == 0)//查无此书
		{

		}
		else if (ret == -1)//库存出错了
		{

		}
		else if (ret == -2) {
			MessageBox(0,"不能添加相同目录的书!","提示",MB_ICONEXCLAMATION);
            result = true;
		}

	}
	return result;
}

bool TfrmStorageReturnMng::IsOverlapCatalog(int headerid, int catalogid, int supplierid)
{

}

void TfrmStorageReturnMng::UpdateNote()//更新单
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
        if (dsetNtHeader->FieldByName("printcount")->AsInteger > 0 || m_userID != dsetNtHeader->FieldByName("OperatorID")->AsInteger ) {
			AnsiString sql;
			sql = "select amount,discount from BS_StorageNote where id = " + dsetNote->FieldByName("ID")->AsAnsiString;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			float discount;
			int amount;
			amount = query->FieldByName("amount")->AsInteger ;
			discount = query->FieldByName("discount")->AsFloat ;
			AnsiString ss;
			if (amount != - abs(dsetNote->FieldByName("Amount")->AsInteger)) {
				ss = "数量" + IntToStr(amount) + "为-" + dsetNote->FieldByName("Amount")->AsAnsiString;
			}
			if (discount != fabs(dsetNote->FieldByName("Discount")->AsFloat)) {
				ss = ss + "折扣" + FloatToStr(discount) + "为" + dsetNote->FieldByName("Discount")->AsAnsiString;
			}
			if (ss != "") {
				if (ChangeDisplay) {
					logmessage = "修改一般入库退货单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
				}
				else
				{
					logmessage = "修改一般入库退货单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
				}
				logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
                logmessage = logmessage + ss;
				AddEvent(1,"一般入库退货窗口",m_userID,m_storageID,logmessage,linfo.con);
			}
		}

		cmdUpdateNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
			= - abs(dsetNote->FieldByName("Amount")->AsInteger);
		cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
			= fabs(dsetNote->FieldByName("Discount")->AsFloat);
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
		cmdUpdateNote->Parameters->ParamByName("@bkstackID")->Value = (int)(cbbkstackID->Items->Objects[cbbkstackID->ItemIndex]);
		if (stackchange) {
			cmdUpdateNote->Parameters->ParamByName("@bkchange")->Value = 1;
		}
		else
		{
			cmdUpdateNote->Parameters->ParamByName("@bkchange")->Value = 0;
		}
		cmdUpdateNote->Execute();
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}


void TfrmStorageReturnMng::UpdateNote1()//更新单
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		cmdUpdateNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= - abs(dsetNote->FieldByName("Amount")->AsInteger);
		cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
			= fabs(dsetNote->FieldByName("Discount")->AsFloat);
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
		cmdUpdateNote->Execute();
	}
}


void TfrmStorageReturnMng::DelNote()//删除单
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdDelNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
			cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 1;
			if (ChangeDisplay) {
				logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
			AddEvent(1,"一般入库退货窗口",m_userID,m_storageID,logmessage,linfo.con);
			cmdDelNote->Execute();
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
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			String ids = "";
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = ids + dsetNote->FieldByName("ID")->AsString;
			if (ChangeDisplay) {
				logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
			AddEvent(1,"一般入库退货窗口",m_userID,m_storageID,logmessage,linfo.con);
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				if (ChangeDisplay) {
					logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
				}
				else
				{
					logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
				}
				logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
				AddEvent(1,"一般入库退货窗口",m_userID,m_storageID,logmessage,linfo.con);
			}
			cmdBatchDelNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchDelNote->Parameters->ParamByName("@Bsmode")->Value = 1;
			cmdBatchDelNote->Execute();
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
}

void TfrmStorageReturnMng::BatchSetNotes(int amount, float discount, int mode)
{
	String ids = "";
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (mode == 1 || mode == 2) {

			if (dbgrdNote->SelectedRows->Count == 0)
			{
				if (rktuihuoguanli) {
					AnsiString sql;
					sql = "select A.amount - B.amount as amount from "
						" (select sum(amount) as amount from BS_StorageNote where BkInfoID = " + dsetNote->FieldByName("BkInfoID")->AsString  + ") A,"
						" (select amount from BS_StorageNote where id = " + dsetNote->FieldByName("ID")->AsString + ") B " ;
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					if (abs(amount) > query->FieldByName("amount")->AsInteger ) {
						dsetNote->Edit();
						dsetNote->FieldByName("Amount")->AsInteger = query->FieldByName("amount")->AsInteger;
						if (mode == 1) {
							dsetNote->FieldByName("discount")->AsFloat =  discount;
						}
						dsetNote->UpdateBatch(arCurrent);
						//MessageBox(0,"退货数量大于入库总数量！","提示" ,MB_OK);
						UpdateNote1();
					}
					else
					{
						ids = ids + dsetNote->FieldByName("ID")->AsString;
					}
				}
				else
				{
					ids = ids + dsetNote->FieldByName("ID")->AsString;
				}
			}
			else if (dbgrdNote->SelectedRows->Count > 0)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
                if (rktuihuoguanli) {
					AnsiString sql;
					sql = "select A.amount - B.amount as amount from "
						" (select sum(amount) as amount from BS_StorageNote where BkInfoID = " + dsetNote->FieldByName("BkInfoID")->AsString  + ") A,"
						" (select amount from BS_StorageNote where id = " + dsetNote->FieldByName("ID")->AsString + ") B " ;
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					if (abs(amount) > query->FieldByName("amount")->AsInteger ) {
						dsetNote->Edit();
						dsetNote->FieldByName("Amount")->AsInteger = query->FieldByName("amount")->AsInteger;
						if (mode == 1) {
							dsetNote->FieldByName("discount")->AsFloat =  discount;
						}
						dsetNote->UpdateBatch(arCurrent);
						//MessageBox(0,"退货数量大于入库总数量！","提示" ,MB_OK);
						UpdateNote1();
					}
					else
					{
						ids = ids + dsetNote->FieldByName("ID")->AsString;
					}
				}
				else
				{
					ids = ids + dsetNote->FieldByName("ID")->AsString;
				}
				for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
				{
					dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
					if (rktuihuoguanli) {
						AnsiString sql;
						sql = "select A.amount - B.amount as amount from "
							" (select sum(amount) as amount from BS_StorageNote where BkInfoID = " + dsetNote->FieldByName("BkInfoID")->AsString  + ") A,"
							" (select amount from BS_StorageNote where id = " + dsetNote->FieldByName("ID")->AsString + ") B " ;
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->Open();
						if (abs(amount) > query->FieldByName("amount")->AsInteger ){
							dsetNote->Edit();
							dsetNote->FieldByName("Amount")->AsInteger = query->FieldByName("amount")->AsInteger;
                            if (mode == 1) {
								dsetNote->FieldByName("discount")->AsFloat =  discount;
							}
							dsetNote->UpdateBatch(arCurrent);
							//MessageBox(0,"退货数量大于入库总数量！","提示" ,MB_OK);
							UpdateNote1();
						}
						else
						{
							ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
						}
					}
					else
					{
						ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
					}
				}
			}
			else
				return;
		}
		else if (mode == 3) {

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
		}

		if (ids == "") {
			QryNtHeader();
		}
		else
		{
        	switch(mode)
			{
			case 1://两者均更新
				cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
				cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
				cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
				cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
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
				cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
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
				cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
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
}

void __fastcall TfrmStorageReturnMng::edtQrySupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		if (!dsetNtHeader->Active
			|| !dsetNote->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;
		if (!dblkpcbbSupplierID->Enabled ) {
		   return;
		}
		String sql;
		sql = " select * from CUST_CustomerInfo where Type =1 and Name like '%"+ edtQrySupplier->Text.Trim() + "%' order by name";
		dsetSupplier->Active = false;
		dsetSupplier->CommandText = sql;
		dsetSupplier->Active = true;
		dsetSupplier->First();
		dblkpcbbSupplierID->KeyValue = dsetSupplier->FieldByName("ID")->AsInteger ;
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("SupplierID")->AsInteger = dsetSupplier->FieldByName("ID")->AsInteger;
		dsetNtHeader->Post();
		dblkpcbbSupplierID->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dblkpcbbStaffIDKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmStorageReturnMng::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}
	if (Key == '\r')
	{
        if (BtnSave->Enabled) {
			MessageBox(0,"请先保存入库退货单！","入库退货" ,MB_ICONEXCLAMATION);
			return;
		}
		if (!dsetNote->Active || !dsetNtHeader->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;

		if (edtCatalog->Text == "")
		{
			changeInputMode();
		}
		else
		{
			float price;
			if (m_catalogSearchMode == 6) {
				try {
					price = StrToFloat(edtCatalog->Text.Trim());
				} catch (...) {
					MessageBox(0,"请输入正确的定价！","入库退货" ,MB_ICONEXCLAMATION);
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

					String ISBN;
					bool exec = true;

					TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
					//frm->BtnWeekView ->Visible = false;
					LandInfo li;
					li.app = m_app;
					li.con = m_con;
					li.userID = m_userID;
					li.storageID = m_storageID;
					frm->Init(&li);
					if (lbcaption->Caption == "入库退货单") {
					//frm->Supplier   = dblkpcbbSupplierID->Text  ;
					}

					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					frm->DoModalType = 8;
					frm->qikan = chqikan->Checked ;
					frm->qikanhao = edqikan->Text ;
					frm->StorageReturnfrm = this;

			  //	if (dsetCatalog->RecordCount > 1 && (exec = dblkpdlgISBN->Execute()))//找到多本书
				if (mrOk == frm->ShowModal())
				{
				   int supplierID = -1,catalogID = -1;
				   frm->GetSelectResult(supplierID, catalogID);
					 supplierID = dsetSupplier->FieldByName("ID")->AsInteger ;
					 if (frm->SelectAll) {                           //全选
						  for (int i = 0; i < frm->lengthint  ; i++) {
							 if (AddNote(supplierID,frm->BkcatalogiD[i])) {

								 Key = 0;
								 Perform(WM_NEXTDLGCTL, 0, 0);

							 }
						   }
						  } else
						  {
							if (supplierID >= 0 && catalogID >= 0)
							{
                                TLocateOptions   Opts;
								Opts.Clear();
								Opts   <<   loPartialKey;
								String   str   = AnsiString(catalogID);
								if ( !dsetNote->Locate("BkcatalogID",str,Opts)){
								if (AddNote(supplierID, catalogID))
								{
									Key=0;
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
								{
									if (sameid) {
										MessageBox(0,"有相同记录请核实！","提示" ,MB_ICONEXCLAMATION);
									}
									dbgrdNote->SelectedRows->CurrentRowSelected = true;
									dbgrdNote->SetFocus();
									dbnbedtAmount->SetFocus();
								}

								   //	MessageBox(0,"库存无该书!","入库单",MB_ICONEXCLAMATION);
							}
						  }
					 }
					 Key=0;
					 edtCatalog->Text = "";
					 edqikan->Text = "";
				   delete frm;
				   historyview();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageReturnMng::dbedtSupplySNKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		dbnbedtAddCosts->SetFocus();
		//Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng::dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
        if (chfoceset->Checked) {
			if (chfsdiscount->Checked) {
				Perform(WM_NEXTDLGCTL, 0, 0);
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
			Perform(WM_NEXTDLGCTL, 0, 0);
		}
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
		historyview();
	}
}
//---------------------------------------------------------------------------

void TfrmStorageReturnMng::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1 && dsetNtHeader->FieldByName("StgNtCode")->AsInteger  == 0)
	{
    	DelNtHeader();
	}
}

void __fastcall TfrmStorageReturnMng::FormClose(TObject *Sender, TCloseAction &Action)
{
	/*if (!SaveStorage(2)) {
		return;
	}  */
	DelInvalidNtHeader();
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	dsetSupplier->Active = false;
	dsetStaff->Active = false;
	dsetLkpSupplier->Active = false;
	dsetCatalog->Active = false;
	dsetSupplier->Active = false;
	dsetBkstack->Active = false;
	TfrmMDIChild::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::RzToolButton9Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::RzToolButton8Click(TObject *Sender)
{
	//打印
	if (!SaveStorage(1))
	{
	  return;
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->PrintStorage(StrToInt(dsetNtHeader->FieldByName("ID")->AsString));

		frm->DanhaoChange = ChangeDisplay ;      //change danhao
		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;
		frm->RvSystem1->DefaultDest   = rdPrinter ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
		frm->Maker = 	lblOpName->Caption;
		frm->rkbk = rkbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;
		frm->tuihuo = 1;
		frm->PrintStorageExe(0);
		/*if (lbcaption->Caption == "入库单")
		{
			 frm->PrintStorageExe(1);
		}else
		{
			 frm->PrintStorageExe(2);
		}    */

		frm->Close();
		delete frm;
        AnsiString sql = "update BS_StorageNoteHeader set printcount = printcount + 1 where id = " + dsetNtHeader->FieldByName("id")->AsString ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
			QryNtHeader();

	}





}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dblkpcbbSupplierIDExit(TObject *Sender)
{
	//
	//UpdateNtHeader();
	//dblkpcbbSupplierID->Enabled = sbnewcustomer->Enabled;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::RzToolButton6Click(TObject *Sender)
{
	//Excel导出
	if (!SaveStorage(1))
	{
		return;
	}
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		DbgridToExcel(dbgrdNote);
	}
}
bool __fastcall TfrmStorageReturnMng::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = StringReplace(dblkpcbbSupplierID->Text+editdanhao->Text ,"\\","-",TReplaceFlags()<<rfReplaceAll)+ "入库退货单";
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
		path =  DBPath;
	}
	else
	{
    	return false;
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
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	*/

	Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");

	/*if(k == 0)
	{
		MessageBox(0,"没有数据！","错误确认" ,MB_OK);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	temptext = "'"+ lbcaption->Caption;
	v.OlePropertyGet("Cells",1,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","单位" );
	temptext = "'"+ dblkpcbbSupplierID->Text;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","日期" );
	temptext = "'"+ DateToStr(dbdtedtHdTime->Date);
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",3,7).OlePropertySet("Value","单号");
	if (ChangeDisplay) {
		temptext = "'"+ editdanhao->Text;
	}
	else
	{
		temptext = "'"+ dbedtStgNtCode->Text;
	}
	v.OlePropertyGet("Cells",3,8).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,1).OlePropertySet("Value","供货编号" );
	temptext = "'"+ dbedtSupplySN->Text;
	v.OlePropertyGet("Cells",4,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,4).OlePropertySet("Value","采购员" );
  //	temptext = "'"+ cbstaff->Text;
	v.OlePropertyGet("Cells",4,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,4).OlePropertySet("Value","附加费用" );
	temptext = "'"+ dbnbedtAddCosts->Text;
	v.OlePropertyGet("Cells",4,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",5,1).OlePropertySet("Value","备注" );
	temptext = "'"+ dbedtRemarks->Text;
	v.OlePropertyGet("Cells",5,2).OlePropertySet("Value",temptext .c_str() );
	*/
	n=0;

	int t1= 0;
	temptext = "\n";
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			//temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	for(int i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
                	t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );
					//temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				/*else if (dbg->Columns ->Items [j-1]->FieldName == "CatalogName") {
                	AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					temptext = temptext + bookname + ",";
				}*/
				else if (dbg->Columns ->Items [j-1]->FieldName == "id"){

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
		//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+2,t1)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);


	v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","合计");
	temptext = RzDBNumericEdit2->Text ;
	v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );
	temptext = RzDBNumericEdit3->Text ;
	v.OlePropertyGet("Cells",t2+2+n,11).OlePropertySet("Value",temptext .c_str() );
	temptext = RzDBNumericEdit4->Text ;
	v.OlePropertyGet("Cells",t2+2+n,12).OlePropertySet("Value",temptext .c_str() );
	dbg->DataSource ->DataSet->EnableControls();

    try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (Exception &E) {
		//ShowMessage(E.Message);
	}

	/*AnsiString rkamount,mayang,shiyang;
	mayang =  RzDBNumericEdit3->Text;
	shiyang = RzDBNumericEdit4->Text;
	rkamount = RzDBNumericEdit2->Text ;
	mayang = StringReplace(mayang , ",","",TReplaceFlags()<<rfReplaceAll);
	shiyang = StringReplace(shiyang , ",","",TReplaceFlags()<<rfReplaceAll);
	rkamount = StringReplace(rkamount , ",","",TReplaceFlags()<<rfReplaceAll);
	temptext = "\n";
	temptext = temptext + "合计,,,,,,,," + rkamount + ",,'" + mayang + ",'" + shiyang ;

	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);  */
	return false;
}

//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dbnbedtAmountExit(TObject *Sender)
{
    if (dsetNote->IsEmpty() ) {
        return;
	}
	if (rktuihuoguanli) {
		AnsiString sql;

		sql = "select A.amount - B.amount as amount from "
			" (select usableamount as amount from order_lock join stk_bookinfo on order_lock.bkcatalogid = stk_bookinfo.bkcatalogid and stk_bookinfo.stgid = order_lock.stgid where stk_bookinfo.id = " + dsetNote->FieldByName("BkInfoID")->AsString  + ") A,"
			" (select amount from BS_StorageNote where id = " + dsetNote->FieldByName("ID")->AsString + ") B " ;
        query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (dbnbedtAmount->IntValue > query->FieldByName("amount")->AsInteger ) {
			dsetNote->Edit();
			dsetNote->FieldByName("Amount")->AsInteger = query->FieldByName("amount")->AsInteger;
			dsetNote->UpdateBatch(arCurrent);
			MessageBox(0,"退货数量大于可退库存数量！","提示" ,MB_OK);
		}
		sql = "select A.amount - B.amount as amount from "
			" (select sum(amount) as amount from BS_StorageNote where BkInfoID = " + dsetNote->FieldByName("BkInfoID")->AsString  + ") A,"
			" (select amount from BS_StorageNote where id = " + dsetNote->FieldByName("ID")->AsString + ") B " ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (dbnbedtAmount->IntValue > query->FieldByName("amount")->AsInteger ) {
			dsetNote->Edit();
			dsetNote->FieldByName("Amount")->AsInteger = query->FieldByName("amount")->AsInteger;
			dsetNote->UpdateBatch(arCurrent);
			MessageBox(0,"退货数量大于入库总数量！","提示" ,MB_OK);
		}
	}
	UpdateNote();
	tuihuolv();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::mniBsNoteSendbackClick(TObject *Sender)
{
	TMenuItem* mi = dynamic_cast<TMenuItem*>(Sender);
	if (mi != NULL)
	{
		if (mi->Tag == BSNoteSendback && !CheckOperateAuthority())
			return;

		if (mi->Tag == 2) {
			lbcaption->Caption  = "入库退货单";
		} else if (mi->Tag == 1) {
              lbcaption->Caption  = "入库单";
			   }
		ChangeBsmode(mi->Tag);

	  RzToolButton5Click(BtnNew);

	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void TfrmStorageReturnMng::QryBkstack()
{
   if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		String sql;
		sql = " SELECT STK_BookstackInfo.ID, STK_BookstackInfo.Name "
			" FROM STK_BookInfo LEFT OUTER JOIN"
			" STK_BookstackInfo ON STK_BookInfo.BkstackID = STK_BookstackInfo.ID"
			" where SupplierID=" + dsetNtHeader->FieldByName("SupplierID")->AsString
			 + " and BkcatalogID=" + dsetNote->FieldByName("BkcatalogID")->AsString
			 + " and STK_BookstackInfo.StgID=" + dsetNtHeader->FieldByName("StgID")->AsString;
		TADOQuery *aq  = new TADOQuery(Application);
		aq->Connection = m_con ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while(!aq->Eof)
		{
		  aq->Next();
		}
	}
}

void __fastcall TfrmStorageReturnMng::dsetNoteAfterScroll(TDataSet *DataSet)
{
	//
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		QryBkstack();
    }
}
//---------------------------------------------------------------------------

void TfrmStorageReturnMng::OnHotKeyPress(DWORD vkCode, bool ctrlpress)
{
	//快捷键

}

void TfrmStorageReturnMng::ResetNtHeader()
{
	//重置单头
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0)
	{
		cmdResetNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdResetNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
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
void __fastcall TfrmStorageReturnMng::sbnewcustomerClick(TObject *Sender)
{
	//添加新供应商
	String ID;
	ID = "";

   dsetSupplier->Active = false;
   dsetSupplier->CommandText = "select ID, Name from CUST_CustomerInfo where Type=1";
   dsetSupplier->Active = true;

	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)//此时不能修改供应商
	{

	}
	else if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1)//可以修改供应商
	{

		int count1 = dsetSupplier->RecordCount;
		TDetaileForm * frm = new TDetaileForm(m_app,1,1,ID.c_str() ,m_con);
		frm->ShowModal();
		delete frm;

		dsetSupplier->Active = false;
		dsetSupplier->Active = true;
		int count2 = dsetSupplier->RecordCount;
		if (count2 > count1)
		{
			dsetSupplier->Last();
			dsetNtHeader->Edit();
			dsetNtHeader->FieldByName("SupplierID")->AsInteger = dsetSupplier->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
			dblkpcbbSupplierID->SetFocus();
		}
	}

	   //	NewSupplier(m_app, m_con);

	 //  i = NewSupplier(m_app,m_con);
			 //	NewCustomer(m_app, m_con);
	   /*  LandInfo *li;
		 li->con = m_con;
		 li->userID = m_userID;



		 frmSupplierinfo = new TfrmSupplierinfo(m_app);
		 frmSupplierinfo->Init(li);
		 frmSupplierinfo->ShowModal();
		 delete frmSupplierinfo;
		 delete li;*/
}
//---------------------------------------------------------------------------



void __fastcall TfrmStorageReturnMng::BtnViewClick(TObject *Sender)
{
    if (!SaveStorage(1))
	{
		return;
	}
	//DelInvalidNtHeader();
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		PM->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N1Click(TObject *Sender)
{
   	lblCatalog->Caption = "书号";
	m_catalogSearchMode = 1;
	if (chqikan->Checked ) {
		edtCatalog->MaxLength = 15;
	}
	else
	{
		edtCatalog->MaxLength = 13;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码";
	m_catalogSearchMode = 2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名";
	m_catalogSearchMode  = 3;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnClearClick(TObject *Sender)
{
	if (!SaveStorage(1))
	{
	  return;
	}
		if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->PrintStorage(StrToInt(dsetNtHeader->FieldByName("ID")->AsString));
		frm->DanhaoChange = ChangeDisplay ;                      //change danhao
		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;
		frm->RvSystem1->DefaultDest  = rdPreview ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPreview;
		 frm->Maker = 	lblOpName->Caption;
		 frm->rkbk = rkbk;
		 frm->printtitle = printtitle;
		 frm->contact = contact;
		 frm->tel = tel;
		 frm->address = address;
		 frm->tuihuo = 1;
		 frm->PrintStorageExe(1);
		/*if (lbcaption->Caption == "入库单")
		{
			 frm->PrintStorageExe(1);
		}else
		{
			 frm->PrintStorageExe(2);
		}  */

		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::RzToolButton3Click(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageReturnMng::RzToolButton5Click(TObject *Sender)
{
    if (dsetNtHeader->IsEmpty() ) {
		return;
	}
	if (dsetNtHeader->FieldByName("StgNtCode")->AsInteger == 0) {
    	return;
	}
	if (!SaveStorage(1))
	{
		return;
	}
	DelInvalidNtHeader();
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::RzToolButton2Click(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::FormResize(TObject *Sender)
{
	 //dbgrdNote->Width = 720;
	 //dbgrdNote->Height = 352;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageReturnMng::dblkpcbbSupplierIDKeyPress(TObject *Sender, wchar_t &Key)

{
   if (Key == VK_RETURN) {
		if (dblkpcbbSupplierID->Text == "") {
			MessageBox(0,"请选择供应商！","提示" ,MB_OK);
			return;
	   }
	   else
	   {
			AnsiString sql = "select Salesman from CUST_CustomerInfo where id = " + IntToStr(dsetSupplier->FieldByName("ID")->AsInteger );
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			sql = "select * from SYS_StaffInfo where Name = '" + query->FieldByName("Salesman")->AsString + "' and stgID = " + IntToStr(m_storageID) + " and Career = 1";
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (!query->IsEmpty() ) {
				int staff = query->FieldByName("ID")->AsInteger;
				dblkpcbbStaffID->KeyValue = staff;
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("StaffID")->AsInteger = staff;
				dsetNtHeader->Post();
			}
			supplierDI = dsetSupplier->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
			sbnewcustomer->Enabled = false;
			dblkpcbbSupplierID->Enabled = false;
			//dbedtSupplySN->SetFocus();
			edtCatalog->Text = "";
			dbnbedtAmount->Value = 0;
			dbnbedtDiscount->Value = 100.00;
			dbnbedt1->Value = 0;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
			BtnSave->Click();
	   }
   }
}
//---------------------------------------------------------------------------

void  TfrmStorageReturnMng::FindNote(String code)
{
	DelInvalidNtHeader();
	edtCatalog->Text = "";
	edtQrySupplier->Text = "";
	dblkpcbbSupplierID->Enabled  = false;
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader(code);
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
	dtpdate->Date = dbdtedtHdTime->Date;
	SaveOrNot = true;
	BtnSave->Enabled = false;
	dblkpcbbSupplierID->Enabled = false;
	sbnewcustomer->Enabled = false;
}

//---------------------------------------------------------------------------



void __fastcall TfrmStorageReturnMng::dbgrdNoteDblClick(TObject *Sender)
{
	/*if (dsetNote->RecordCount > 0) {
		TfrmNewBookModify * frm = new TfrmNewBookModify(m_app,m_con,dsetNote->FieldByName("BkcatalogID")->AsInteger );
		frm->ShowModal();
		delete frm;
		spQryNtHeader->Active = false;
		spQryNtHeader1->Active = false;
		spQryNtHeader1->Parameters->ParamByName("@NtCode")->Value = dbedtStgNtCode->Text;
		spQryNtHeader1->Parameters->ParamByName("@Bsmode")->Value = 1;
		MYTRACEF(_T("query note header @NtCode=%S"), dbedtStgNtCode->Text.c_str());
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
				lbcaption->Caption = "入库退货单";
			}
			dsetNote->AfterScroll = dsetNoteAfterScroll;
		}
		catch(...)
		{
			//ShowMessage("该单不存在！");
		}
	}   */
	if (dsetNote->IsEmpty() ) {
		return;
	}
          if (bcatalogmodify) {
              return;
          }
          if (dblclicklock) {
             return;
        }
		TfrmNewBookModify * frm = new TfrmNewBookModify(m_app,m_con,dsetNote->FieldByName("BkcatalogID")->AsInteger,m_storageID,m_userID);
		frm->ShowModal();
		delete frm;
		QryNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dbgrdNoteCellClick(TColumn *Column)
{

	if (dsetNote->IsEmpty()) {
		return;
	}
    	AnsiString sql;
		sql = "select harmnum  from BS_StorageNote_attachment where bs_storageNoteid =" + dbgrdNote->DataSource->DataSet->FieldByName("ID")->AsAnsiString  ;
		TADOQuery *aq =new TADOQuery(NULL);
		aq->Connection = m_con ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		editshun->Text = aq->FieldByName("harmnum")->AsAnsiString ;
		delete aq;
		historyview();
}
//---------------------------------------------------------------------------


void TfrmStorageReturnMng::historyview()
{
	String sql;
	if (dsetNote->RecordCount > 0) {
		sql = "select * from SYS_BSSET where name = 'storageday'" ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		int day = query->FieldByName("bk")->AsInteger ;
		DATE datetime = Date();
		datetime = datetime - day;
		sql = "select BS_StorageNoteHeader.StgNtCode as Ntcode,BS_StorageNoteHeader.StgNtCodeStr,BS_StorageNote.Amount,BS_StorageNote.Discount,Convert(varchar(20),BS_StorageNoteHeader.HdTime,111) as HdTime,CUST_CustomerInfo.Name,BS_BookCatalog.Price from BS_StorageNote left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.ID "
			  "left join STK_BookInfo on BS_StorageNote.BkInfoID = STK_BookInfo.ID left join CUST_CustomerInfo on STK_BookInfo.SupplierID = CUST_CustomerInfo.id right join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.ID "
			  "WHERE BS_BookCatalog.ID IN (SELECT BS_BookCatalog.ID FROM STK_BookInfo LEFT JOIN BS_BookCatalog ON BS_BookCatalog.ID = STK_BookInfo.BkcatalogID ";
		sql = sql + "WHERE STK_BookInfo.ID = " + dsetNote->FieldByName("BkInfoID")->AsString ;
		sql = sql + ") and BS_StorageNoteHeader.HdTime >= '" +  DateToStr(datetime) ;
		sql = sql + "' and BS_StorageNoteHeader.StgID = " + edStoryNum->Text ;
		if (!allsupplier) {
			sql = sql + " and BS_StorageNoteHeader.SupplierID = " + dsetSupplier->FieldByName("ID")->AsString ;
		}
		qudetail->Close();
		qudetail->SQL->Clear();
		qudetail->SQL->Add(sql);
		qudetail->Open();
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0%";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
        int totamount = 0;
		qudetail->DisableControls();
		qudetail->First();
		while(!qudetail->Eof)
		{
            totamount = totamount + qudetail->FieldByName("Amount")->AsInteger ;
			qudetail->Next();
		}
		qudetail->EnableControls();
        edtotamount->Text = IntToStr(totamount);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N5Click(TObject *Sender)
{
    if (dsetNote->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= dsetNote->RecordCount; i++) {
		dbgrdNote->DataSource->DataSet->RecNo = i;
		dbgrdNote->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N6Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode  = 6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnNewClick(TObject *Sender)
{
lock(0);
    if (!SaveStorage(1))
	{
	  return;
	}
	//DelInvalidNtHeader();

	querydan->Active = false;
	querydan->Active = true;
	DBNav->Enabled = false;
	String sql;
	sql = " select * from CUST_CustomerInfo where Type =1 order by name ";
	dsetSupplier->Active = false;
	dsetSupplier->CommandText = sql;
	dsetSupplier->Active = true;
	ChangeBsmode(BSNoteSendback);
	RzToolButton5Click(BtnNew);
	dblkpcbbSupplierID->KeyValue = 0;
	SaveOrNot = false;
	BtnSave->Enabled = true;
	dbnbedtAddCosts->Enabled = true;
	dblkpcbbSupplierID->Enabled = true;
    dbedtSupplySN->Enabled = true;
	dsetNtHeader->Edit();
	dsrcNtHeader->DataSet->FieldByName("AddCosts")->Value =  0.0;
	dsrcNtHeader->DataSet->FieldByName("Remarks")->Value =  "";
	dsrcNtHeader->DataSet->FieldByName("SupplySN")->Value =  "";
	dsetNtHeader->UpdateRecord();
	 if (newsupplier) {
                  sbnewcustomer->Enabled = true;
                }else sbnewcustomer->Enabled = false;

	membk->Text = "";
	dbedtSupplySN->Text = "";
	editdanhao->Text = "";
	dbnbedtAddCosts->Value = 0.0;
	dblkpcbbStaffID->KeyValue = -1;
	dblkpcbbSupplierID->SetFocus();
	try {
    	qudetail->Active = false;
	} catch (...) {
	}
}
//---------------------------------------------------------------------------


void  TfrmStorageReturnMng::ModifyEnable()
{
	if (m_opmode == OPFind) {
		dbnbedtAmount->Enabled = false;
		dbnbedtDiscount->Enabled = false;
		cbbkstackID->Enabled = false;
		if (dsetNote->FieldByName("amount")->AsInteger < 0 ) {
			lbcaption->Caption = "入库退货单";
		}
		else
		{
			lbcaption->Caption = "入库单";
		}
	}
	else
	{
        lbcaption->Caption = "入库退货单";
		dbnbedtAmount->Enabled = true;
		dbnbedtDiscount->Enabled = true;
		cbbkstackID->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dtpdateChange(TObject *Sender)
{
   dbdtedtHdTime->Date = dtpdate->Date ;

}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnChangeOptionsClick(TObject *Sender)
{
	/*if (m_opmode != OPFind) {
		return;
	}
	if (dsetNote->IsEmpty() ) {
        return;
	}
	int supplier = dsetSupplier->FieldByName("ID")->AsInteger;
	String sql;
	int bkid;
	dsetNote->First();
	while (!dsetNote->Eof )
		{
			sql = "select * from STK_BookInfo where BkcatalogID = " + dsetNote->FieldByName("BkcatalogID")->AsString + " and SupplierID = " + IntToStr(supplier) + " and BkstackID = " + dsetNote->FieldByName("BkstackID")->AsString;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount > 0) {
				bkid = query->FieldByName("ID")->AsInteger ;
			}
			else
			{
				sql = "insert into STK_BookInfo(Amount,BkcatalogID,BkstackID,SupplierID,State) values (0," + dsetNote->FieldByName("BkcatalogID")->AsString + "," + dsetNote->FieldByName("BkstackID")->AsString + "," + IntToStr(supplier) + ",0)";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
				sql = "select max(id) as id from STK_BookInfo";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->Open();
				bkid = query->FieldByName("id")->AsInteger ;
			}
			sql = "update BS_StorageNote set BkInfoID = " + IntToStr(bkid) + " where id = " + dsetNote->FieldByName("ID")->AsString ;
            query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();

			dsetNote->Next();
		} */
		if (changepassword) {
			if (!CheckOperateAuthority())
					return;
		}
		try {
			beforesupplier = dsetSupplier->FieldByName("ID")->AsInteger;
			beforesuppliername = dsetSupplier->FieldByName("Name")->AsAnsiString ;
		} catch (...) {
		}
		dbedtSupplySN->Enabled = true;
		dbnbedtAddCosts->Enabled = true;
		BtnSave->Enabled = true;
		SaveOrNot = false;
		dblkpcbbSupplierID->Enabled = true;
		 if (newsupplier) {
                  sbnewcustomer->Enabled = true;
                }else sbnewcustomer->Enabled = false;

		dtpdate->Enabled =  true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if (Key == VK_F1)  //查单
	{
		if (!BtnView->Enabled ) {
			return;
		}
		BtnView->Click();
	}
	if (Key == VK_F2) {   //增单
		if (!BtnNew->Enabled ) {
			return;
		}
		BtnNew->Click();
	}
	if (Key == VK_F3) {   //保存
		if (!BtnSave->Enabled ) {
			return;
		}
		BtnSave->Click();
	}
	if (Key == VK_F4) {   //修改单头
		if (!BtnChangeOptions->Enabled ) {
			return;
		}
		BtnChangeOptions->Click();
	}
	if (Key == VK_F5) {   //删行
		if (!RzToolButton2->Enabled ) {
			return;
		}
		RzToolButton2->Click();
	}
	if (Key == VK_F6) {   //统一
		if (!RzToolButton3->Enabled ) {
			return;
		}
		RzToolButton3->Click();
	}
	if (Key == VK_F7) {   //现场付款
		if (!BtnReminder->Enabled ) {
			return;
		}
		BtnReminder->Click();
	}
	if (Key == VK_F8) {   //导出
		if (!RzToolButton6->Enabled ) {
			return;
		}
		RzToolButton6->Click();
	}
	if (Key == VK_F9) {   //删单
		if (!RzToolButton5->Enabled ) {
			return;
		}
		RzToolButton5->Click();
	}
	if (Key == VK_F10) {   //打印
		if (!RzToolButton8->Enabled ) {
			return;
		}
		RzToolButton8->Click();
	}
	if (Key == VK_F11) {   //预览
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

	if (Shift.Contains(ssCtrl)&& Key ==81  ) {
		RzToolButton9->Click();
	}

	if (Shift.Contains(ssCtrl)&& Key ==78  ) {
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==70  ) {
		BtnView1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------
void TfrmStorageReturnMng::changeInputMode()
{
  switch (m_catalogSearchMode) {
	case 1:
		N2->Click();
		break;
	case 2:
		N3->Click();
		break;
	 case 3:
		N6->Click();
		break;
	 case 6:
		N10->Click();
		break;
	 case 5:
		N1->Click();
		break;
  default:
	  ;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N8Click(TObject *Sender)
{
	if (dsetNote->IsEmpty()) {
    	return;
	}
	AnsiString path;
	AnsiString StgID;
	AnsiString sql;
	StgID = "-1";
	dsetNote->DisableControls();
	if (dbgrdNote->SelectedRows->Count > 0) {
    	for (int i=0; i < dbgrdNote->SelectedRows->Count; i++)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
			StgID = StgID + "," + dsetNote->FieldByName("ID")->AsString;
		}
	}
	else
	{
    	StgID = StgID + "," + dsetNote->FieldByName("ID")->AsString;
	}

	adospcopy->ProcedureName = "CopyData";
	adospcopy->Parameters->Clear();
	adospcopy->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),1);
	adospcopy->Parameters->CreateParameter("@ID",ftString,pdInput,StgID.Length(),StgID.c_str());
	adospcopy->Parameters->CreateParameter("@userid",ftInteger,pdInput,sizeof(int),linfo.userID );
	adospcopy->ExecProc();

	dsetNote->EnableControls();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
		 int CurrNo;
  if (Button == mbLeft ) {
	  if (!blSelect) {
		 BookMark = dsetNote->GetBookmark();   //dataset
		 blSelect  = true;
		 return;
	  }
  }
   if (Shift.Contains(ssShift)) {
		  CurrNo = dsetNote->FieldByName("ID")->AsInteger ;
		  dsetNote->DisableControls();
		  dsetNote->GotoBookmark(BookMark);
		  dbgrdNote->SelectedRows->CurrentRowSelected = true;
		  if (CurrNo > dsetNote->FieldByName("ID")->AsInteger) {
			  while(CurrNo > dsetNote->FieldByName("ID")->AsInteger)
			  {
				dbgrdNote->SelectedRows->CurrentRowSelected = true;
				dsetNote->Next();
			  }
		  }
		  if ( CurrNo < dsetNote->FieldByName("ID")->AsInteger ) {
				  while(CurrNo < dsetNote->FieldByName("ID")->AsInteger)
			  {
				dbgrdNote->SelectedRows->CurrentRowSelected = true;
				dsetNote->Prior() ;
			  }
		  }
		  dsetNote->EnableControls();
		  dsetNote->FreeBookmark(BookMark);
		  blSelect = false;
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N9Click(TObject *Sender)
{
    if (BtnSave->Enabled) {
		MessageBoxA(0,"本单还未保存，请先保存！","提示",MB_ICONASTERISK);
		return;
	}
	adospcopy->ProcedureName = "StickData";
	adospcopy->Parameters->Clear();
	adospcopy->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),3);
	adospcopy->Parameters->CreateParameter("@HeadId",ftInteger,pdInput,sizeof(int),dsetNtHeader->FieldByName("ID")->AsInteger);
	adospcopy->Parameters->CreateParameter("@userid",ftInteger,pdInput,sizeof(int),linfo.userID );
	adospcopy->ExecProc();
	QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);

	Screen->Cursor = crDefault ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnView1Click(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,linfo.con,linfo.storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnSaveClick(TObject *Sender)
{
	if (!SaveOK()) {
        return;
	}
	edtCatalog->SetFocus();
}
//---------------------------------------------------------------------------

bool TfrmStorageReturnMng::SaveOK()
{
	/*if (dblkpcbbSupplierID->Enabled) {
		MessageBoxA(0,"请在单位处用回车键确认供应商！","提示",MB_ICONASTERISK);
		return false;
  }  */
	if (dsetNtHeader->RecordCount > 0) {
		AnsiString sql = "update BS_StorageNoteHeader set HdTime = '" + DateToStr(dtpdate->Date)  + "' where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}

  if (dsetNote->RecordCount > 0) {
  	if (dsetSupplier->FieldByName("ID")->AsInteger != beforesupplier) {
		ChangeSupplier();
		if (ChangeDisplay) {
			logmessage = "把入库退货单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		}
		else
		{
			logmessage = "把入库退货单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
		}
		logmessage = logmessage + "的供应商由" + beforesuppliername + "修改为" + dsetSupplier->FieldByName("Name")->AsAnsiString;
		AddEvent(1,"一般入库退货窗口",m_userID,m_storageID,logmessage,linfo.con);
		beforesupplier = dsetSupplier->FieldByName("ID")->AsInteger;
		UpdateNtHeader();
	}
		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		//dbedtSupplySN->Enabled = false;
		dblkpcbbSupplierID->Enabled = false;
		sbnewcustomer->Enabled = false;
		dtpdate->Enabled =  false;
		return true;
  }
  else if (dsetNote->IsEmpty() && dsetNtHeader->FieldByName("StgNtCode")->AsInteger  != 0  ) {
		UpdateNtHeader();
		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		//dbedtSupplySN->Enabled = false;
		dblkpcbbSupplierID->Enabled = false;
		sbnewcustomer->Enabled = false;
		dtpdate->Enabled =  false;
		return true;
  }
	spsave->Parameters->ParamByName("@MODE")->Value = 1;
  spsave->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger ;
  spsave->Parameters->ParamByName("@STGID")->Value = linfo.storageID;
  spsave->Parameters->ParamByName("@TYPE")->Value = 1;
  spsave->Parameters->ParamByName("@CODEMODE")->Value = 1;
  spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
  spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
  spsave->ExecProc() ;



  if (ChangeDisplay) {
	logmessage = "添加入库退货单" + spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
  }
  else
  {
	logmessage = "添加入库退货单" + spsave->Parameters->ParamByName("@ReturnCode")->Value ;
  }
  AddEvent(1,"一般入库退货窗口",m_userID,m_storageID,logmessage,linfo.con);
  historyview();     //SaveBenDan
  dbedtStgNtCode->Text = spsave->Parameters->ParamByName("@ReturnCode")->Value ;
  editdanhao->Text = spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
  UpdateNtHeader();
  SaveOrNot = true;
  BtnSave->Enabled = false;
  dbnbedtAddCosts->Enabled = false;
  //dbedtSupplySN->Enabled = false;
  dblkpcbbSupplierID->Enabled = false;
  sbnewcustomer->Enabled = false;
  dtpdate->Enabled =  false;
  QryNtHeader();
  return true;
}
//---------------------------------------------------------------------------

 bool TfrmStorageReturnMng::SaveStorage(int mode)
{
	if (dsrcNote->DataSet == NULL) {
		return true;
	}
	if (dsetNote->IsEmpty() ) {
    	return true;
	}
	int recordRN = dbgrdNote->DataSource->DataSet->RecordCount;
	if ((!SaveOrNot)&& (recordRN != 0)) {                      //SaveBenDan
	if (mode == 1) {                      //打印或预

		MessageBoxA(0,"本单还未保存，请先保存！","提示",MB_ICONASTERISK);
		return false;

	}else
	{
		  if( MessageBoxA(0,"本单还未保存，是否需要保存？","提示",MB_ICONQUESTION||MB_YESNO)==1)
		  {
			  if (!SaveOK()) {
				  return false;
			  }
		  }else
		  {
			spsave->Parameters->ParamByName("@MODE")->Value = 2;
			spsave->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger ;
			spsave->Parameters->ParamByName("@STGID")->Value = 0;
			spsave->Parameters->ParamByName("@TYPE")->Value = 1;
			spsave->Parameters->ParamByName("@CODEMODE")->Value = 1;
			spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
			spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
			spsave->ExecProc() ;
		  }
	  }
	}else return true;

}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng::dbnbedtAddCostsExit(TObject *Sender)
{
	if (dsetNtHeader->RecordCount > 0) {
		AnsiString sql = "update BS_StorageNoteHeader set AddCosts = " + FloatToStr(abs(dsetNtHeader->FieldByName("AddCosts")->AsFloat))  + " where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng::dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		membk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnReminderClick(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::DBNavClick(TObject *Sender, TNavigateBtn Button)

{
	AnsiString code ;
   code = querydan->FieldByName("StgNtCode")->AsAnsiString ;
   editdanhao->Text = querydan->FieldByName("StgNtCodeStr")->AsAnsiString ;
	QryNtHeader(code,false);
}
//---------------------------------------------------------------------------
void TfrmStorageReturnMng::ChangeSupplier()
{
	if (dsetNote->IsEmpty() ) {
        return;
	}
	int supplier = dsetSupplier->FieldByName("ID")->AsInteger,supplierid,BkcatalogID;
	String sql;
	int bkid;
	dsetNote->First();
	while (!dsetNote->Eof )
		{

                  sql= " exec changsupplier "+IntToStr(dsetSupplier->FieldByName("ID")->AsInteger)+","+
                        IntToStr(dsetNote->FieldByName("BkcatalogID")->AsInteger)+","+ dsetNote->FieldByName("BkstackID")->AsString+
                        ","+ IntToStr(linfo.storageID)+","+ dsetNote->FieldByName("ID")->AsString;

                        query->Close();

                        query->SQL->Clear();
                        query->SQL->Add(sql);
                        query->ExecSQL();

                /*
			supplierid = dsetNote->FieldByName("SupplierID")->AsInteger ;

			BkcatalogID =  dsetNote->FieldByName("BkcatalogID")->AsInteger ;
			sql = "select * from STK_BookInfo where BkcatalogID = " + dsetNote->FieldByName("BkcatalogID")->AsString + " and SupplierID = " + IntToStr(supplier) + " and BkstackID = " + dsetNote->FieldByName("BkstackID")->AsString;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount > 0) {
				bkid = query->FieldByName("ID")->AsInteger ;
			}
			else
			{
				sql = "insert into STK_BookInfo(Amount,BkcatalogID,BkstackID,SupplierID,State) values (0," + dsetNote->FieldByName("BkcatalogID")->AsString + "," + dsetNote->FieldByName("BkstackID")->AsString + "," + IntToStr(supplier) + ",0)";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
				sql = "select max(id) as id from STK_BookInfo";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->Open();
				bkid = query->FieldByName("id")->AsInteger ;
			}
			sql = "update BS_StorageNote set BkInfoID = " + IntToStr(bkid) + " where id = " + dsetNote->FieldByName("ID")->AsString ;
            query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();  */
			dsetNote->Next();
		}

}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dbgrdNoteTitleClick(TColumn *Column)
{
	if (dsetNote->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetNote->Sort == "") {
		dsetNote->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetNote->Sort == qusort) {
		dsetNote->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetNote->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void TfrmStorageReturnMng::FormView()
{
	AnsiString sql;
	sql = "select * from BS_SYS_Formview where stgid = " + IntToStr(m_storageID) + " and ParentID = 6";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof)
	{
		if (query->FieldByName("Name")->AsAnsiString == "查单" ) {
			BtnView->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "增单" ) {
			BtnNew->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "保存" ) {
			BtnSave->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "修改" ) {
			BtnChangeOptions->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "删单" ) {
			RzToolButton5->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "删行" ) {
			RzToolButton2->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "统一" ) {
			RzToolButton3->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "现场付款" ) {
			BtnReminder->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "Excel导出" ) {
			RzToolButton6->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "预览" ) {
			BtnClear->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "打印" ) {
			RzToolButton8->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "查书" ) {
			BtnView1->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "最小化" ) {
			BtnAlignBottom->Visible = query->FieldByName("state")->AsBoolean ;
		}
		query->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
		Key = 0;
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
			Perform(WM_NEXTDLGCTL, 0, 0);
		}
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
		historyview();
	}
}
void TfrmStorageReturnMng::tuihuolv()
{
	if (dsetNote->IsEmpty() ) {
        return;
	}
	 FLOAT yeartuihuo,timetuihuo;
 yeartuihuo =0.00,
 timetuihuo =0.00;
 int totalamountall;
	   sptuihuo->Parameters->ParamByName("@clientID")->Value =  supplierDI;
	   sptuihuo->Parameters->ParamByName("@timelv")->Value =  0.00;
	   sptuihuo->Parameters->ParamByName("@yearlv")->Value =  0.00;

	   sptuihuo->ExecProc();
	   timetuihuo = sptuihuo->Parameters->ParamByName("@timelv")->Value;
	   yeartuihuo = sptuihuo->Parameters->ParamByName("@yearlv")->Value;

	   edityear->Text = FormatFloat("0.00",yeartuihuo) + "%" ;
	   editbenqi->Text  = FormatFloat("0.00",timetuihuo)+ "%" ;
	   if (yeartuihuo >= 100.00) {
		   edityear->Color = clRed ;
	   }else
	   {
		edityear->Color = cl3DLight ;
	   }
	   if (timetuihuo >= 100.00) {
		  editbenqi->Color = clRed ;
	   }else
	   {
		 editbenqi->Color = cl3DLight ;

	   }


}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N10Click(TObject *Sender)
{
	lblCatalog->Caption = "作者";
	m_catalogSearchMode  = 5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::editshunExit(TObject *Sender)
{
	 if (editshun->Text == "") {
		editshun->Text = "0";
	}
	UpdateWsaleDiscout(3);
	QryNtHeader();
}
//---------------------------------------------------------------------------
void TfrmStorageReturnMng::UpdateWsaleDiscout(int mode)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		adospupdatewsaleprice->Parameters->ParamByName("@storageNoteID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 3;
		int harmnum ;
		try {
			harmnum =  StrToInt(editshun->Text);
			if (harmnum > 0) {
				harmnum = 0 - harmnum;
			}
		} catch (...) {
			return;
		}
		adospupdatewsaleprice->Parameters->ParamByName("@harmnum")->Value
			=  harmnum;
		adospupdatewsaleprice->ExecProc();
	}
}
//---------------------------------------------------------------------------
void  TfrmStorageReturnMng::operterview(int operterid)
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = linfo.con ;
	sql = "select name from sys_user where id = " + IntToStr(operterid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	lblOpName->Caption = aq->FieldByName("name")->AsString;
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::editshunKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edtCatalog->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::membkExit(TObject *Sender)
{
	if (dsetNtHeader->RecordCount > 0) {
		AnsiString sql = "update BS_StorageNoteHeader set Remarks = '" + membk->Text + "' where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::membkKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
	   edtCatalog->Text = "";
	   //edtCatalog->SetFocus();
	   dbnbedtAmount->Value = 0;
	   dbnbedtDiscount->Value = 100.00;
	   dbnbedt1->Value = 0;
	   ((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
	   ((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
	   BtnSave->Click();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng::SpeedButton1Click(TObject *Sender)
{
	if (GroupBox1->Visible) {
		GroupBox1->Visible = false;
	}
	else
	{
    	GroupBox1->Visible = true;
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::chfsluruClick(TObject *Sender)
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

void __fastcall TfrmStorageReturnMng::chqikanClick(TObject *Sender)
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

void __fastcall TfrmStorageReturnMng::edqikanKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (m_catalogSearchMode == 6) {
        	float price;
				try {
					price = StrToFloat(edtCatalog->Text.Trim());
				} catch (...) {
					MessageBox(0,"请输入正确的定价！","入库退货" ,MB_ICONEXCLAMATION);
					return;
				}
			}

		String ISBN;
		bool exec = true;

		TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
		//frm->BtnWeekView ->Visible = false;
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->Init(&li);
		if (lbcaption->Caption == "入库退货单") {
		//frm->Supplier   = dblkpcbbSupplierID->Text  ;
		}

		frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
		frm->DoModalType = 8;
		frm->qikan = chqikan->Checked ;
		frm->qikanhao = edqikan->Text ;
		frm->StorageReturnfrm = this;

			  //	if (dsetCatalog->RecordCount > 1 && (exec = dblkpdlgISBN->Execute()))//找到多本书
		if (mrOk == frm->ShowModal())
		{
			int supplierID = -1,catalogID = -1;
			frm->GetSelectResult(supplierID, catalogID);
			supplierID = dsetSupplier->FieldByName("ID")->AsInteger ;
			if (frm->SelectAll) {                           //全选
				for (int i = 0; i < frm->lengthint  ; i++) {
					if (AddNote(supplierID,frm->BkcatalogiD[i])) {
						Key = 0;
						Perform(WM_NEXTDLGCTL, 0, 0);
					}
				}
			} else
			{
				if (supplierID >= 0 && catalogID >= 0)
				{
					TLocateOptions   Opts;
					Opts.Clear();
					Opts   <<   loPartialKey;
					String   str   = AnsiString(catalogID);
					if ( !dsetNote->Locate("BkcatalogID",str,Opts)){
						if (AddNote(supplierID, catalogID))
						{
							Key=0;
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
					{
						dbgrdNote->SelectedRows->CurrentRowSelected = true;
						dbgrdNote->SetFocus();
						dbnbedtAmount->SetFocus();
					}

				}
			}
		}
		Key=0;
		edtCatalog->Text = "";
		edqikan->Text = "";
		delete frm;
		historyview();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng::N11Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con,m_storageID,dsetNote->FieldByName("BkcatalogID")->AsInteger,m_userID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::cbbkstackIDSelect(TObject *Sender)
{
	stackchange = true;
	UpdateNote();
	stackchange = false;
}
void TfrmStorageReturnMng::lock(int type)
{

      if (type==1) {
            BtnSave->Enabled = false;
            BtnChangeOptions->Enabled = false;
            RzToolButton5->Enabled = false;
            RzToolButton2->Enabled = false;
            RzToolButton3->Enabled = false;
            BtnReminder->Enabled = false;
            edtQrySupplier->Enabled = false;
            sbnewcustomer->Enabled = false;
            chqikan->Enabled = false;
            edtCatalog->Enabled = false;
            dbnbedtAmount->Enabled = false;
            dbnbedtDiscount->Enabled = false;
            editshun->Enabled = false;
            membk->Enabled = false;
            selectmenu->AutoPopup = false;
            cbbkstackID->Enabled = false;
            dbedtSupplySN->Enabled = false;
            membk->Enabled = false;
           dblkpcbbStaffID->Enabled = false;
               //imagelock->Visible = true;
               lblock->Caption = "已锁定";
               dblclicklock=true;
      }else
      {
       dblclicklock=false;
      dblkpcbbStaffID->Enabled = true;
       //  BtnSave->Enabled = true;
            BtnChangeOptions->Enabled = true;
            RzToolButton5->Enabled = true;
            RzToolButton2->Enabled = true;
            RzToolButton3->Enabled = true;
            BtnReminder->Enabled = true;
            edtQrySupplier->Enabled = true;


              if (newsupplier) {
                  sbnewcustomer->Enabled = true;
                }else sbnewcustomer->Enabled = false;

            chqikan->Enabled = true;
            edtCatalog->Enabled = true;
            dbnbedtAmount->Enabled = true;
            dbnbedtDiscount->Enabled = true;
            editshun->Enabled = true;
            membk->Enabled = true;
          selectmenu->AutoPopup = true;
            cbbkstackID->Enabled = true;

            dbedtSupplySN->Enabled = true;
            lblock->Caption = "";
            disablenewsupplierornewbook();
      }




}
void TfrmStorageReturnMng::checknewsupplier()
{
   AnsiString sql;
   sql = "select * from sys_lock_table where lockname in('bookcatalog','supplier') and stgid ="+IntToStr(linfo.storageID);
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
void TfrmStorageReturnMng::disablenewsupplierornewbook()
{

     //bool  supplier,bookcatalogadd,bcatalogmodify;
     if (supplier) {
        sbnewcustomer->Enabled = false;
     }
     







}
//---------------------------------------------------------------------------

