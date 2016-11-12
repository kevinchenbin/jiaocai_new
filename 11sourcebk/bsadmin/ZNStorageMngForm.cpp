//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZNStorageMngForm.h"
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
#include "UnitExcelImport.h"
#include "SelectCatalogForm.h"
#include "bookQuery.h"
#include "RecMoneyForm.h"
#include "QueryDanHao.h"
//#include "procurequery.h"
#include   <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzCommon"
#pragma link "RzDBLook"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TfrmZNStorageMng *frmZNStorageMng;
//---------------------------------------------------------------------------
__fastcall TfrmZNStorageMng::TfrmZNStorageMng(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_catalogSearchMode(0)
	, m_bsmode(BSUnknown)
	, m_opmode(OPUnknown)
{
	m_module = MTStorageMng;
	m_catalogSearchMode = 1;
	this->WindowState = wsMaximized ;
	stackchange = false;
	blSelect = false;//shilf 多选
}

void TfrmZNStorageMng::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	lblOpName->Caption = li->UserName;
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
	dsetCatalog->Connection = m_con;
	adospupdatewsaleprice->Connection = m_con;
	spsave->Connection = m_con;
    querydan->Connection = m_con;
   //	dsetBkstack->Connection = m_con;
  ///	dsetBkstack->Active = true;
	dtpdate->Date =  dbdtedtHdTime->Date ;
	//取得库位
	GetBkStackInfo();
	query->Connection = m_con;
	qudetail->Connection = m_con;
	qrystorge->Connection = m_con;
	aq->Connection = m_con;
	dsetCatalog->Active = true;
	dsetSupplier->Active = true;
	dsetStaff->Active = true;

	dblkpcbbSupplierID->KeyValue = 0 ;
	ChangeCatalogSearchMode();
	//chckbxSwitch->Checked = false;
	ChangeBsmode(BSNote);
	String sql;
	sql = "select ID,Name from SYS_StorageInfo";
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
	//添单
	ChangeOpmode(OPAddNtHeader);

	Sbutfirst->Enabled = false;
	Sbutbefore->Enabled = false;
	Sbutnext->Enabled = false;
	Sbutend->Enabled = false;
	sql = "select * from SYS_BSSET where name = 'storageday'" ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("value")->AsBoolean  ) {
	   //	GroupBox2->Visible = true;
	   dgdetail->Visible = true;
	}
	else
	{
	   //	GroupBox2->Visible = false;
		dgdetail->Visible = false;
	}

    sql = "select * from SYS_BSSET where name = 'rkprintbk' and value = 1";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	rkbk = query->FieldByName("bk")->AsAnsiString ;
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
	  Sbutfirst->Visible = false;
	   Sbutbefore->Visible = false;
	   Sbutnext->Visible = false;
	   Sbutend->Visible = false;
	   DBNav->Visible = true;
	   dgdetail->Columns->Items[1]->Visible = true;
	   dgdetail->Columns->Items[0]->Visible = false;
	}else
	{
	  editdanhao->Visible = false;
	  dbedtStgNtCode->Visible = true;
	  Sbutfirst->Visible = true;
		Sbutbefore->Visible = true;
		Sbutnext->Visible = true;
		Sbutend->Visible = true;
		DBNav->Visible = false;
		dgdetail->Columns->Items[1]->Visible = false;
		dgdetail->Columns->Items[0]->Visible = true;
	}

	sql = "select * from SYS_BSSET where name = 'xiaoshudian'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	format = "￥" + query->FieldByName("bk")->AsString ;
	sql = "select * from SYS_BSSET where name = 'autologout'";
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	autologout = query->FieldByName("value")->AsBoolean ;
	sql = "select * from SYS_BSSET where name = 'adddotenable'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	addnote = query->FieldByName("value")->AsBoolean;
	sql = "select * from SYS_BSSET where name = 'lastyjpxdiscount'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	lastjypxdiscount = query->FieldByName("value")->AsBoolean;
	if (lastjypxdiscount && addnote) {
		sql = "select * from SYS_BSSET where name = 'yjpxfirstkind'";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		yjpxkind = query->FieldByName("bk")->AsAnsiString;
	}
	RzDBNumericEdit3->DisplayFormat = format;
	RzDBNumericEdit4->DisplayFormat = format;
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
	BtnImport->Click();
}
void TfrmZNStorageMng::GetBkStackInfo()
{
   AnsiString sql= "select  CAST(stgid as varchar(10)) + ' 店 ' + name  as name, ID from STK_BookstackInfo where StgID = " + IntToStr(m_storageID);
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
void TfrmZNStorageMng::ChangeCatalogSearchMode()
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

void TfrmZNStorageMng::ChangeBsmode(BSMode bsmode)
{
	if (bsmode != m_bsmode)
	{
		m_bsmode = bsmode;
	}

	if (m_bsmode == BSNote)
	{
		grpbxNtHeader->Caption = "";
		grpbxNote->Caption = "";
		mniBsNote->Checked = true;
		mniBsNoteSendback->Checked = false;
	}
	else if (m_bsmode == BSNoteSendback)
	{
		grpbxNtHeader->Caption = "入库退货单信息";
		grpbxNote->Caption = "图书入库退货信息";
		mniBsNote->Checked = false;
		mniBsNoteSendback->Checked = true;
	}
}

void TfrmZNStorageMng::ChangeOpmode(OPMode opmode)
{
	if (opmode == m_opmode
		&& (opmode == OPDelNtHeader))
		return;
	//1为查单模式 2为添加单头模式 3为删除单头模式 4为添加单模式 5为删除单模式 6为统一模式 7为现场收款模式
	switch (opmode)
	{
	case OPFind:
		{
			if (!SaveStorage(1))
			{
				return;
			}
            String sql;
			sql = " select * from CUST_CustomerInfo where Type =1 order by name ";
			dsetSupplier->Active = false;
			dsetSupplier->CommandText = sql;
			dsetSupplier->Active = true;
			dsetSupplier->First();
			dblkpcbbSupplierID->KeyValue = dsetSupplier->FieldByName("ID")->AsInteger ;
			if (findpassword) {
            	if (!CheckOperateAuthority())
					return;
			}
													   //change danhao
			if (ChangeDisplay) {

			   TfrmQuery * frm = new TfrmQuery(this);
			   frm->Init(&linfo);
			   if (frm->ShowModal() == mrOk  )
			   {
				  DBNav->Enabled = true;
					edtCatalog->Text = "";
					edtQrySupplier->Text = "";

				  AnsiString sql;
				  if (frm->RDanhao) {  //按单号来查询
					  sql = "select * from BS_StorageNoteHeader where  stgNtcodeInt between ";
					  sql = sql + IntToStr(frm->Max) + " and " + IntToStr(frm->Min) + " and totalamount > 0";
				  }else
				  {
					   sql = "select * from BS_StorageNoteHeader where  hdtime between '";
					   sql = sql + DateToStr(frm->FMax )  + " 0:00:00' and '" + DateToStr(frm->TMin) + " 23:59:59' and totalamount > 0";
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
			}else
			{
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
					edtQrySupplier->Text = "";
					String code = frm->GetNoteCode();
					try
					{
						//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
						QryNtHeader(code);
						String sql,codetmp;
						codetmp = code;
						if (codetmp != "") {
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
						}
					}
					__finally
					{
						//LockWindowUpdate(NULL);
					}
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


		} }
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
			dtpdate->Date =  dbdtedtHdTime->Date ;//更新日期
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
			TfrmSetNotes* frm = new TfrmSetNotes(this);
			frm->salediscount = 1;
			frm->ChangeBsmode(m_bsmode);
			if (frm->ShowModal() == mrOk)
			{
				int amount = 0;
				float discount = 0;
				pixiaodiscount = 0;
				bool bsetAmount = frm->GetAmount(amount);
				bool bsetDiscount = frm->GetDiscount(discount);
				bsetpixiaodiscount = frm->GetpixiaoDiscount(pixiaodiscount);
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
				else if (bsetpixiaodiscount) {
					BatchSetNotes(amount, discount, 0);
				}
				QryNtHeader();

			}
			delete frm;
			m_opmode = opmode;

        }
		break;
	case OPRecCash:
		//现场付款模式
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

			String NtHeader = dbedtStgNtCode->Text.Trim(),Headerdate;
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
				MessageBox(0,"现场付款只能付当日的！","入库单" ,MB_OK);
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
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
			}
			delete frm;
		}
		m_opmode = opmode;
		break;
    default:
		break;
	}
	//ModifyEnable();
	try {
		NtCodeChange();
	} catch (...) {
	}
}

void TfrmZNStorageMng::AddNtHeader()//添加单头
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNtHeader->Parameters->ParamByName("@CODEMODE")->Value = 0;
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

void TfrmZNStorageMng::QryNtHeader(String code, bool qrybkstack)//查询单头
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
		if (dsetNtHeader->FieldByName("TotalAmount")->AsInteger < 0 ){
            	dsrcNote->DataSet = NULL;
				dsetNote->AfterScroll = NULL;
				return;
		}
		if (qrybkstack)
		{
			QryBkstack();
		}
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = format;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
	}
	catch(...)
	{
		//ShowMessage("该单不存在！");
	}
}


void TfrmZNStorageMng::QryNtHeader(bool qrybkstack)//查询单头
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
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = format;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
        }
		catch(...)
		{
            //ShowMessage("该单不存在！");
		}
	}
}

void TfrmZNStorageMng::QryNtHeader(int id, bool qrybkstack)//查询单头
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
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = format;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
	}
	catch(...)
	{
    	//ShowMessage("该单不存在！");
    }
}

void TfrmZNStorageMng::DelNtHeader()//删除单头
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdDelNtHeader->Parameters->ParamByName("@ID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		int id = dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdDelNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
		cmdDelNtHeader->Execute();
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader(id);
		}
		__finally
		{
		   //	LockWindowUpdate(NULL);
		}
	}
}

void TfrmZNStorageMng::UpdateNtHeader()//更新单头
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
				dsetNtHeader->FieldByName("StaffID")->AsString;
		cmdUpdateNtHeader->Parameters->ParamByName("@AddCosts")->Value =
			abs(dsetNtHeader->FieldByName("AddCosts")->AsFloat);
		cmdUpdateNtHeader->Parameters->ParamByName("@Remarks")->Value =
			dsetNtHeader->FieldByName("Remarks")->AsWideString;
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

bool TfrmZNStorageMng::AddNote(int supplierID, int catalogID)//添加单
{
	bool result = false;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetCatalog->Active )
	{
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
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = format;
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
				editjingjiaprice->Text = dbgrdNote->DataSource->DataSet->FieldByName("Price")->AsAnsiString ;
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
		else 	if (ret == -2) {
			MessageBox(0,"不能添加相同目录的书!","提示",MB_ICONEXCLAMATION);
            result = true;
		}



	}
	return result;
}

bool TfrmZNStorageMng::AddNote(int id)
{
	bool result = false;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
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
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = format;
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
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

bool TfrmZNStorageMng::IsOverlapCatalog(int headerid, int catalogid, int supplierid)
{

}

void TfrmZNStorageMng::UpdateNote()//更新单
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
			= fabs(dsetNote->FieldByName("Discount")->AsFloat);
		cmdUpdateNote->Parameters->ParamByName("@bkstackID")->Value = (int)(cbbkstackID->Items->Objects[cbbkstackID->ItemIndex]);
		if (stackchange) {
			cmdUpdateNote->Parameters->ParamByName("@bkchange")->Value = 1;
		}
		else
		{
			cmdUpdateNote->Parameters->ParamByName("@bkchange")->Value = 0;
		}
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
		cmdUpdateNote->Execute();
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = format;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

void TfrmZNStorageMng::DelNote()//删除单
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdDelNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
			cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 1;
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
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
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

void TfrmZNStorageMng::BatchSetNotes(int amount, float discount, int mode)
{
if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		String ids = "";
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			ids = ids + dsetNote->FieldByName("ID")->AsString;
			if (bsetpixiaodiscount) {
				BatchsetWsaleDiscout(pixiaodiscount);
			}

		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			if (bsetpixiaodiscount) {
				BatchsetWsaleDiscout(pixiaodiscount);
			}
			ids = dsetNote->FieldByName("ID")->AsString;
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{

				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				if (bsetpixiaodiscount) {
					BatchsetWsaleDiscout(pixiaodiscount);
				}
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

void __fastcall TfrmZNStorageMng::edtQrySupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		if (!dsetNtHeader->Active
			|| !dsetNote->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
        	return;

		dsetLkpSupplier->Active = false;
		String sql;
		sql = Sysutils::Format("select * from CUST_CustomerInfo where (ID>0 and Type=1) and Name='%s'",
			ARRAYOFCONST((edtQrySupplier->Text.c_str())));
        dsetLkpSupplier->CommandText = sql;
		dsetLkpSupplier->Active = true;
		if (dsetLkpSupplier->RecordCount > 1
			 && dblkpdlgSupplier->Execute())//找到多个供应商
		{
			dsetNtHeader->Edit();
			dsetNtHeader->FieldByName("SupplierID")->AsInteger
				= dsetLkpSupplier->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
			Key = 0;
			Perform(WM_NEXTDLGCTL, 0, 0);
		}
		else if (dsetLkpSupplier->RecordCount == 1)//找到一个供应商
		{
			dsetNtHeader->Edit();
			dsetNtHeader->FieldByName("SupplierID")->AsInteger
				= dsetLkpSupplier->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
			Key = 0;
			Perform(WM_NEXTDLGCTL, 0, 0);
		}
		else//未能找到批销商
		{

        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::dblkpcbbStaffIDKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmZNStorageMng::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}
	if (Key == '\r')
	{
	 if (BtnSave->Enabled) {
			MessageBox(0,"请先保存入库单！","入库" ,MB_ICONEXCLAMATION);
			return;
	}
	 if (edtCatalog->Text == "") {
	   changeInputMode();
	   return;
	 }
	 float price;
	 if (m_catalogSearchMode == 6) {
		try {
			price = StrToFloat(edtCatalog->Text.Trim());
		} catch (...) {
			MessageBox(0,"请输入正确的定价！","入库" ,MB_ICONEXCLAMATION);
			return;
		}
	 }
		if (!dsetNote->Active || !dsetNtHeader->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;

		if (edtCatalog->Text == "")
		{
			ChangeCatalogSearchMode();
		}
		else
		{
			String ISBN;
			bool exec = true;
		/*	switch (m_catalogSearchMode)
			{
			case 1:                                     //条码
				if (edtCatalog->Text.Length() != 13)
				{
					ShowMessage("条码输入错误！");
					return;
				}
				dsetCatalog->Active = false;
				dsetCatalog->CommandText = "select BS_BookCatalog.ID,Barcode as 书号,ISBN,BS_BookCatalog.Name as 书名,"
					" Price as 定价,AbbreviatedName as 出版社,Author as 作者,"
					" PressCount as 版次,Date as 出版日期,BS_BookType.Name as 小类"
					" from BS_BookCatalog left join BS_PressInfo on BS_BookCatalog.PressID=BS_PressInfo.ID"
					" left join BS_BookType on smallBookTypeID=BS_BookType.ID where Barcode='" + edtCatalog->Text + "'";
			  //	dsetCatalog->Active = true;
			  //	dsetCatalog->First();   */


					TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
					LandInfo li;
					li.app = m_app;
					li.con = m_con;
					li.userID = m_userID;
					li.storageID = m_storageID;
					frm->Init(&li);
					if (lbcaption->Caption == "入库退货单") {
				     	frm->Supplier   = dblkpcbbSupplierID->Text  ;
					}

					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					frm->DoModalType = 11;
					frm->ZNStorageMng = this;

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
								//	if (dbnbedtDiscount->Value != 100) {
							   //		addwsalediscount();

							   //		}
								 Perform(WM_NEXTDLGCTL, 0, 0);

							 }
						   }
						  } else
						  {
							if (supplierID >= 0 && catalogID >= 0)
							{
							 //  BkcatalogID

							   //	   dsetNote->Filtered = false;
								//   ShowMessage(dsetNote->FieldByName("BkcatalogID")->AsAnsiString);
								 //  dsetNote->Filter = "BkcatalogID=" + ;

								//   dsetNote->Filtered = True;
							 TLocateOptions   Opts;
				  Opts.Clear();
				  Opts   <<   loPartialKey;
				  String   str   = AnsiString(catalogID);
				 if ( !dsetNote->Locate("BkcatalogID",str,Opts))
				 {


								if (AddNote(supplierID, catalogID))
								{
									Key=0;
									//if (dbnbedtDiscount->Value != 100) {
									yjpxdiscount();


                                   dbnbedtAmount ->SetFocus();
								}else
								{

									//MessageBox(0,"库存无该书AAAAA!","入库单",MB_ICONEXCLAMATION);

								}
							 }
								  //
							}
							else
							{
								dbgrdNote->SelectedRows->CurrentRowSelected = true;
								dbgrdNote->SetFocus();
								dbnbedtAmount->SetFocus();
							}
						  }
					 }else  {
							   if (!frm->findbook) {     //产生新书
                                    	//新书目
									if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
									{
									   Tfrmnewbook *frma = new Tfrmnewbook(m_app,m_con);
									   frma->ZNStorageMng = this;
									   frma->modle = 2;
										frma->editcode->Text = edtCatalog->Text ;
										PostMessage(frma->editcode->Handle, WM_KEYDOWN,VK_RETURN,0);
									   if (mbOK == frma->ShowModal())
									   {

									   }
									   delete frma;
									   dbnbedtAmount->SetFocus();
									}

							   }
						   }

					 Key=0;
					 edtCatalog->Text = "";
					 editshun->Text = "0";
					 editque->Text = "0";
				   //	 editpxdiscount->Text = "100.00";
					 editjingjiaprice->Text = FormatFloat("0.00", dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat * dbnbedtDiscount->Value * 0.01);
					 editpxprice->Text =  FormatFloat("0.00", dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat);

				   delete frm;
				   historyview();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmZNStorageMng::dbedtSupplySNKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		dbnbedtAddCosts->SetFocus();
		//Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::dblkpcbbBkstackIDKeyPress(TObject *Sender, wchar_t &Key)
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

void __fastcall TfrmZNStorageMng::dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		Perform(WM_NEXTDLGCTL, 0, 0);
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
		historyview();
	}
}
//---------------------------------------------------------------------------

void TfrmZNStorageMng::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1 && dsetNtHeader->FieldByName("StgNtCode")->AsInteger == 0)
	{
    	DelNtHeader();
	}
}

void __fastcall TfrmZNStorageMng::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (!SaveStorage(2)) {
		return;
	}
	if (m_opmode == OPAddNtHeader && autologout) {
		AutologPro();
		UpdateProHeader();
	}
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

void __fastcall TfrmZNStorageMng::RzToolButton9Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::RzToolButton8Click(TObject *Sender)
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

		frm->DanhaoChange = ChangeDisplay ;                      //change danhao
		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;
		frm->RvSystem1->DefaultDest   = rdPrinter ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
		frm->Maker = lblOpName->Caption ;
        frm->rkbk = rkbk;
		if (lbcaption->Caption == "入库单")
		{
			 frm->PrintStorageExe(1);
		}else
		{
			 frm->PrintStorageExe(2);
		}

		frm->Close();
		delete frm;

	}

}
//---------------------------------------------------------------------------


void __fastcall TfrmZNStorageMng::RzToolButton6Click(TObject *Sender)
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
bool __fastcall TfrmZNStorageMng::DbgridToExcel(TRzDBGrid* dbg)
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

	n=6;

	int t1= 0;
	for(int q=0;q<dbg->FieldCount-1 ;++q)
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
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
                	t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );
				}
				else
				{
                	t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}

	v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","合计");
	//v.OlePropertyGet("Cells",t2+2+n,2).OlePropertySet("Value","总数量");
	temptext = RzDBNumericEdit2->Text ;
	v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value",temptext .c_str() );
	//v.OlePropertyGet("Cells",t2+2+n,4).OlePropertySet("Value","总码洋");
	temptext = RzDBNumericEdit3->Text ;
	v.OlePropertyGet("Cells",t2+2+n,8).OlePropertySet("Value",temptext .c_str() );
	//v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value","总实洋");
	temptext = RzDBNumericEdit4->Text ;
	v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );

	return false;
}

//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::dbnbedtAmountExit(TObject *Sender)
{

	UpdateNote();

}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------


void TfrmZNStorageMng::QryBkstack()
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

void __fastcall TfrmZNStorageMng::dsetNoteAfterScroll(TDataSet *DataSet)
{
	//
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		QryBkstack();
    }
}
//---------------------------------------------------------------------------

void TfrmZNStorageMng::OnHotKeyPress(DWORD vkCode, bool ctrlpress)
{
	//快捷键

}

void TfrmZNStorageMng::ResetNtHeader()
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

void __fastcall TfrmZNStorageMng::spnewbookClick(TObject *Sender)
{
	//新书目
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
	   Tfrmnewbook *frm = new Tfrmnewbook(m_app,m_con);
	   frm->ZNStorageMng = this;
	   frm->modle = 2;//入库
	   if (mbOK == frm->ShowModal())
	   {
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


void __fastcall TfrmZNStorageMng::BtnViewClick(TObject *Sender)
{
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

void __fastcall TfrmZNStorageMng::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		PM->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::N1Click(TObject *Sender)
{
   lblCatalog->Caption = "书 号:";
	m_catalogSearchMode = 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码:";
	m_catalogSearchMode = 2;
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书 名:";
	m_catalogSearchMode  = 3;
}
void TfrmZNStorageMng::changeInputMode()
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
		N1->Click();
		break;
  default:
      ;
  }



}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------




void __fastcall TfrmZNStorageMng::BtnClearClick(TObject *Sender)
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
		frm->Maker = lblOpName->Caption ;
		frm->rkbk = rkbk;
		if (lbcaption->Caption == "入库单")
		{
			 frm->PrintStorageExe(1);
		}else
		{
			 frm->PrintStorageExe(2);
		}

		frm->Close();
		delete frm;


	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::RzToolButton3Click(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmZNStorageMng::RzToolButton5Click(TObject *Sender)
{
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

void __fastcall TfrmZNStorageMng::RzToolButton2Click(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::FormResize(TObject *Sender)
{
	 //dbgrdNote->Width = 720;
	 //dbgrdNote->Height = 352;
}
//---------------------------------------------------------------------------
void __fastcall TfrmZNStorageMng::dblkpcbbSupplierIDKeyPress(TObject *Sender, wchar_t &Key)

{
   if (Key == VK_RETURN) {
	   if (dblkpcbbSupplierID->Text == "") {
			MessageBox(0,"请选择供应商！","提示" ,MB_OK);
			return;
	   }
	   else
	   {
            AnsiString sql = "select Salesman from CUST_CustomerInfo where id = " + IntToStr(dsetSupplier->FieldByName("ID")->AsInteger );
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			sql = "select * from SYS_StaffInfo where Name = '" + aq->FieldByName("Salesman")->AsString + "' and stgID = " + IntToStr(m_storageID) + " and Career = 1";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (!aq->IsEmpty() ) {
				int staff = aq->FieldByName("ID")->AsInteger;
				dblkpcbbStaffID->KeyValue = staff;
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("StaffID")->AsInteger = staff;
				dsetNtHeader->Post();
			}
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

void  TfrmZNStorageMng::FindNote(String code)
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

void TfrmZNStorageMng::NtCodeChange()
{
		AnsiString sql;
		int min,max,index;
		if (m_bsmode == BSNote) {
			min = 0;
		}
		else
		{
			min = 10000;
		}
		String code = dbedtStgNtCode->Text;
		if (code != "" && MaxNote != "" ) {
			max = StrToInt(MaxNote.SubString(11,5));
			index = StrToInt(code.SubString(9,5));
			if (index == min && max == 0) {
				Sbutfirst->Enabled = true;
				Sbutbefore->Enabled = false;
				Sbutnext->Enabled = false;
				Sbutend->Enabled = false;
			}
			if (index == min && max != 0) {
				Sbutfirst->Enabled = false;
				Sbutbefore->Enabled = false;
				Sbutnext->Enabled = true;
				Sbutend->Enabled = true;
			}
			if (index != min && index < max) {
				Sbutfirst->Enabled = true;
				Sbutbefore->Enabled = true;
				Sbutnext->Enabled = true;
				Sbutend->Enabled = true;
			}
			if (index != min && index == max) {
				Sbutfirst->Enabled = true;
				Sbutbefore->Enabled = true;
				Sbutnext->Enabled = false;
				Sbutend->Enabled = false;
			}
			if (index != min && index == max + 1) {
				Sbutfirst->Enabled = true;
				Sbutbefore->Enabled = true;
				Sbutnext->Enabled = false;
				Sbutend->Enabled = false;
			}
			if (index != min && index > max + 1) {
				Sbutfirst->Enabled = true;
				Sbutbefore->Enabled = false;
				Sbutnext->Enabled = false;
				Sbutend->Enabled = false;
			}
		}
}





void __fastcall TfrmZNStorageMng::SbutfirstClick(TObject *Sender)
{
	if (dbedtStgNtCode->Text == "" || dbedtStgNtCode->Text == "0") {
		return;
	}
	String correntcode = dbedtStgNtCode->Text.Trim() ;
	String code = correntcode.SubString(0,8);
	if (m_bsmode == BSNote) {
		code = code + "00000";
	}
	else
	{
		code = code + "10000";
	}
	dbedtStgNtCode->Text = code;
	//code = "00" + code;
	FindNote(code);
	NtCodeChange();
	m_opmode == OPFind;
	//ModifyEnable();
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::SbutbeforeClick(TObject *Sender)
{
	if (dbedtStgNtCode->Text == "" || dbedtStgNtCode->Text == "0") {
		return;
	}
	String correntcode = dbedtStgNtCode->Text.Trim() ;
	int code = StrToInt(correntcode.SubString(9,5) );
	if (code < 1) {
        return;
	}
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
	dbedtStgNtCode->Text = correntcode;
	AnsiString sql = "select * from BS_StorageNoteHeader where StgNtCode = " + correntcode;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount == 0) {
		Sbutbefore->Click();
	}
	//correntcode = "00" + correntcode;
	FindNote(correntcode);
	NtCodeChange();
	m_opmode == OPFind;
	//ModifyEnable();
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::SbutnextClick(TObject *Sender)
{
	if (dbedtStgNtCode->Text == "" || dbedtStgNtCode->Text == "0") {
		return;
	}
	String correntcode = dbedtStgNtCode->Text.Trim() ;
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
	dbedtStgNtCode->Text = correntcode;
	AnsiString sql = "select * from BS_StorageNoteHeader where StgNtCode = " + correntcode;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount == 0) {
		if (StrToFloat(correntcode) < StrToFloat(MaxNote) ) {
			Sbutnext->Click();
		}
	}
	//correntcode = "00" + correntcode;
	FindNote(correntcode);
	NtCodeChange();
	m_opmode == OPFind;
	//ModifyEnable();
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::SbutendClick(TObject *Sender)
{
	if (dbedtStgNtCode->Text == "" || dbedtStgNtCode->Text == "0") {
		return;
	}
	String correntcode = MaxNote ;
	dbedtStgNtCode->Text = correntcode;
	//correntcode = "00" + correntcode;
	FindNote(correntcode);
	NtCodeChange();
	m_opmode == OPFind;
	//ModifyEnable();
}
//---------------------------------------------------------------------------


void __fastcall TfrmZNStorageMng::dbgrdNoteDblClick(TObject *Sender)
{
	/*if (dsetNote->RecordCount > 0) {
		TfrmNewBookModify * frm = new TfrmNewBookModify(m_app,m_con,dsetNote);
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
				//lbcaption->Caption = "入库退货单";
			}
			dsetNote->AfterScroll = dsetNoteAfterScroll;
		}
		catch(...)
		{
			//ShowMessage("该单不存在！");
		}
	}     */
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::dbgrdNoteCellClick(TColumn *Column)
{
	if (dsetNote->RecordCount > 0) {
		//cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)dsetNote->FieldByName("BkstackID")->AsInteger ) ;
	   AnsiString sql;
	   sql = "select wsalediscount from BS_StorageNote_attachment where bs_storageNoteid =" + dbgrdNote->DataSource->DataSet->FieldByName("ID")->AsAnsiString  ;
	   TADOQuery *aq =new TADOQuery(NULL);
	   aq->Connection = m_con ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		editpxdiscount->Text = aq->FieldByName("wsalediscount")->AsAnsiString ;
		delete aq;
		historyview();
	}

}
//---------------------------------------------------------------------------

void TfrmZNStorageMng::historyview()
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
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = format;
		   
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::N5Click(TObject *Sender)
{
	for (int i = 1; i <= dsetNote->RecordCount; i++) {
		dbgrdNote->DataSource->DataSet->RecNo = i;
		dbgrdNote->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmZNStorageMng::mniBsNoteClick(TObject *Sender)
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

void __fastcall TfrmZNStorageMng::N6Click(TObject *Sender)
{
	lblCatalog->Caption = "定  价:";
	m_catalogSearchMode  = 6;
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::BtnNewClick(TObject *Sender)
{
	if (!SaveStorage(1))
	{
	  return;
	}

								//search dan
   // DelInvalidNtHeader();
	querydan->Active = false;
	querydan->Active = true;
	DBNav->Enabled = false;
	String sql;
	sql = " select * from CUST_CustomerInfo where Type =1 order by name ";
	dsetSupplier->Active = false;
	dsetSupplier->CommandText = sql;
	dsetSupplier->Active = true;
	if (m_opmode == OPAddNtHeader && autologout) {
		AutologPro();
		UpdateProHeader();
	}
	ChangeBsmode(BSNote);
	RzToolButton5Click(BtnNew);
	dblkpcbbSupplierID->KeyValue = 0;
	SaveOrNot = false;
	BtnSave->Enabled = true;
	dbnbedtAddCosts->Enabled = true;
  	dbedtRemarks->Enabled = true;
	dblkpcbbSupplierID->Enabled = true;
	sbnewcustomer->Enabled = true;
	dbedtSupplySN->Enabled = true;
	dsetNtHeader->Edit();
	dsrcNtHeader->DataSet->FieldByName("AddCosts")->Value =  0.0;
	dsrcNtHeader->DataSet->FieldByName("Remarks")->Value =  "";
	dsrcNtHeader->DataSet->FieldByName("SupplySN")->Value =  "";
	dsetNtHeader->UpdateRecord();
	dbedtRemarks->Text = "";
	dbedtSupplySN->Text = "";
	RzEdit1->Text = "";
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

void  TfrmZNStorageMng::ModifyEnable()
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
        lbcaption->Caption = "入库单";
		dbnbedtAmount->Enabled = true;
		dbnbedtDiscount->Enabled = true;
		cbbkstackID->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::dtpdateChange(TObject *Sender)
{
	dbdtedtHdTime->Date =  dtpdate->Date;

}
//---------------------------------------------------------------------------
void TfrmZNStorageMng::UpdateWsaleDiscout(int mode)
{
if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{

		adospupdatewsaleprice->Parameters->ParamByName("@storageNoteID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		if (mode == 2) {
			adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 2;
			adospupdatewsaleprice->Parameters->ParamByName("@stockprice")->Value
			= StrToFloat(editjingjiaprice->Text);
		}
		if (mode == 1) {
         	adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 1;
			adospupdatewsaleprice->Parameters->ParamByName("@wsalediscount")->Value
			=  StrToFloat(editpxdiscount->Text);
		}
		if (mode == 0) {
			adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 0;
			adospupdatewsaleprice->Parameters->ParamByName("@wsaleprice")->Value
			=  StrToFloat(editpxprice->Text);
		}
		if (mode == 3) {
			adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 3;
			adospupdatewsaleprice->Parameters->ParamByName("@harmnum")->Value
			=  StrToFloat(editshun->Text);
		}
		if (mode == 4) {
			adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 4;
			adospupdatewsaleprice->Parameters->ParamByName("@damagenum")->Value
			=  StrToFloat(editque->Text);
		}
		if (mode == 5) {
			 adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 5;
			adospupdatewsaleprice->Parameters->ParamByName("@returnflag")->Value
			= cbreturn->Checked ;
		}
		 adospupdatewsaleprice->ExecProc();


	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::editpxdiscountExit(TObject *Sender)
{
   float price;
   float pxprice;
   if (editpxdiscount->Text == "") {
	   editpxdiscount->Text = "0.00";
   }
   price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
	pxprice = price * StrToFloat(editpxdiscount->Text) * 0.01 ;
	editpxprice->Text =  FormatFloat("0.00",pxprice);

   UpdateWsaleDiscout(1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::dbnbedtDiscountExit(TObject *Sender)
{

	float jinjia;
	float discount;
	float price ;
	UpdateNote();
	try
	{
	if (editjingjiaprice->Text == "") {

	  editjingjiaprice->Text = "0.00";
	}
	price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
	jinjia = price * dbnbedtDiscount->Value * 0.01 ;
	editjingjiaprice->Text =  FormatFloat("0.00",jinjia);
	yjpxdiscount();
	}
	catch(...)
	{}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::editjingjiapriceExit(TObject *Sender)
{
  if (editjingjiaprice->Text == ""){
	 editjingjiaprice->Text = "0.00";
  }
  float price ;
  float discount;
  price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
  if (price != 0) {
	 discount = StrToFloat(editjingjiaprice->Text)/price;


	 dbnbedtDiscount->DataSource->DataSet->Edit();
	 dbnbedtDiscount->DataSource->DataSet->FieldByName("Discount")->AsAnsiString =  FormatFloat("0.00",discount*100) ;
	 UpdateNote();
	 //UpdateWsaleDiscout(2);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::editjingjiapriceKeyPress(TObject *Sender, wchar_t &Key)

{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == '\r')
	{
		Key = 0;
		Perform(WM_NEXTDLGCTL, 0, 0);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::editpxdiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == '\r')
	{
		Key = 0;
		Perform(WM_NEXTDLGCTL, 0, 0);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::editpxpriceExit(TObject *Sender)
{
/*	float price ;
	float discount;
	price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
	if (price != 0) {
	discount = StrToFloat(editpxprice->Text)/price;
	editpxdiscount->Text = FormatFloat("0.00",discount*100) ;
  }     */
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::editpxpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
		Key = 0;
		Perform(WM_NEXTDLGCTL, 0, 0);
		edtCatalog->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::editshunExit(TObject *Sender)
{
 if (editshun->Text == "") {
	 editshun->Text = "0";
 }
UpdateWsaleDiscout(3);

}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::editqueExit(TObject *Sender)
{
 if (editque->Text == "") {
	 editque->Text = "0";
 }
UpdateWsaleDiscout(4);
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::editqueKeyPress(TObject *Sender, wchar_t &Key)
{
   if (Key == '\r')
	{
		Key = 0;

	   edtCatalog->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::editshunKeyPress(TObject *Sender, wchar_t &Key)
{

	if (Key == '\r')
	{
		Key = 0;
			Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmZNStorageMng::cbreturnExit(TObject *Sender)
{
	UpdateWsaleDiscout(5);
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::cbbkstackIDSelect(TObject *Sender)
{
	stackchange = true;
	UpdateNote();
	stackchange = false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmZNStorageMng::BtnChangeOptionsClick(TObject *Sender)
{
	/*if (m_opmode != OPFind) {
		return;
	}
	if (dsetNote->IsEmpty() ) {
        return;
	}
	int supplier = dsetSupplier->FieldByName("ID")->AsInteger,supplierid,BkcatalogID;
	String sql;
	int bkid;
	dsetNote->First();
	while (!dsetNote->Eof )
		{
			supplierid = dsetNote->FieldByName("SupplierID")->AsInteger ;
			BkcatalogID =  dsetNote->FieldByName("BkcatalogID")->AsInteger ;
			if (autologout) {
				AutologProS(supplierid,BkcatalogID);
			}
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
			if (autologout) {
				AutologProA();
			}
		}
		if (autologout) {
			UpdateProHeader();
		} */
		try {
			beforesupplier = dsetSupplier->FieldByName("ID")->AsInteger;
		} catch (...) {
		}
		dbedtSupplySN->Enabled = true;
		dbnbedtAddCosts->Enabled = true;
		dbedtRemarks->Enabled = true;
		BtnSave->Enabled = true;
		SaveOrNot = false;
		BtnSave->Enabled = true;
		dblkpcbbSupplierID->Enabled = true;
		sbnewcustomer->Enabled = true;

}
//---------------------------------------------------------------------------

void  TfrmZNStorageMng::AutologProA()
{
	if (dsetNote->IsEmpty() ) {
        return;
	}
	int supplier = dsetSupplier->FieldByName("ID")->AsInteger;
	String sql;
	int bkid;
	sql = "select BS_ProcureNote.id,UnrecAmount from BS_ProcureNote left join BS_ProcureNoteHeader on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id where BS_ProcureNote.BkcatalogID = " + dsetNote->FieldByName("BkcatalogID")->AsString + " and BS_ProcureNoteHeader.SupplierID = " + IntToStr(supplier) + " and (BS_ProcureNoteHeader.state = 0 or BS_ProcureNoteHeader.state = 1)";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("UnrecAmount")->AsInteger > 0 ) {
		sql = " update BS_ProcureNote set RecAmount = RecAmount + " + dsetNote->FieldByName("Amount")->AsString + ",UnrecAmount = UnrecAmount - " + dsetNote->FieldByName("Amount")->AsString + " where id = " + query->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void  TfrmZNStorageMng::AutologProS(int supplier,int BkcatalogID)
{
	if (dsetNote->IsEmpty() ) {
        return;
	}
	String sql;
	int bkid;
	sql = "select BS_ProcureNote.id,UnrecAmount from BS_ProcureNote left join BS_ProcureNoteHeader on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id where BS_ProcureNote.BkcatalogID = " + IntToStr(BkcatalogID) + " and BS_ProcureNoteHeader.SupplierID = " + IntToStr(supplier) + " and (BS_ProcureNoteHeader.state = 0 or BS_ProcureNoteHeader.state = 1)";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("UnrecAmount")->AsInteger > 0 ) {
		sql = " update BS_ProcureNote set RecAmount = RecAmount - " + dsetNote->FieldByName("Amount")->AsString + ",UnrecAmount = UnrecAmount + " + dsetNote->FieldByName("Amount")->AsString + " where id = " + query->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void  TfrmZNStorageMng::AutologPro()
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	dsetNote->First();
	while (!dsetNote->Eof )
	{
		AutologProA();
		dsetNote->Next();
	}
}
//---------------------------------------------------------------------------

void  TfrmZNStorageMng::UpdateProHeader()
{
	String sql;
	sql = "SELECT DISTINCT BS_ProcureNoteHeader.ID FROM BS_ProcureNoteHeader  LEFT JOIN BS_ProcureNote ON  BS_ProcureNoteHeader.ID = BS_ProcureNote.ProcureNtHeaderID "
		  "WHERE BS_ProcureNote.RecAmount >= Amount AND (BS_ProcureNoteHeader.state = 0 or BS_ProcureNoteHeader.state = 1)";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof )
	{
		sql = "update BS_ProcureNoteHeader set state = 2 where id = " + query->FieldByName("ID")->AsString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		query->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmZNStorageMng::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{

	if (Key == VK_F1)
	{
	  BtnView->Click();
	}
	if (Key == VK_F2) {
		 BtnNew->Click();
	}
		if (Key == VK_F5) {
		RzToolButton5->Click();
	}
			if (Key == VK_F6) {
		RzToolButton2->Click();
	}
			if (Key == VK_F8) {
		RzToolButton3->Click();
	}
			if (Key == VK_F6) {
		RzToolButton5->Click();
	}
			if (Key == VK_F9) {
		BtnClear->Click();
	}
			if (Key == VK_F10) {
		RzToolButton8->Click();
	}
			if (Key == VK_F12) {
		RzToolButton6->Click();
	}
	if (Key == VK_F4) {
		BtnSave->Click();
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
void TfrmZNStorageMng::BatchsetWsaleDiscout(float pidiscount)
{

				adospupdatewsaleprice->Parameters->ParamByName("@storageNoteID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
				adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
				= 1;
				adospupdatewsaleprice->Parameters->ParamByName("@wsalediscount")->Value
				=  pidiscount;
				adospupdatewsaleprice->ExecProc();
}

//---------------------------------------------------------------------------



void __fastcall TfrmZNStorageMng::dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button,
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


void __fastcall TfrmZNStorageMng::N9Click(TObject *Sender)
{
 //   dsetNote->SaveToFile("D:\\sd",pfADTG);
	bool storagediscount;
	bool wholsediscount;
	AnsiString updatesql,updatepxdiscount;
	storagediscount = false;
	wholsediscount = false;
	int ret ;
	AnsiString path;
	path = ExtractFilePath(Application->ExeName);
	path = path + "CopyData";
	TADODataSet *dataset = new TADODataSet(NULL);
	dataset->LoadFromFile(path);
	if ( MessageBoxA(0,"需要导入入库折扣吗？","询问",MB_ICONQUESTION||MB_OKCANCEL) ==1  ) {
	  storagediscount= true;
	}
	if ( MessageBoxA(0,"需要导入批销折扣吗？","询问",MB_ICONQUESTION||MB_OKCANCEL) ==1  ) {
	  wholsediscount= true;
	}

	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = m_con ;

	Screen->Cursor =  crHourGlass ;
	dataset->First();
	while(!dataset->Eof)
	{
		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
			= dataset->FieldByName("BkcatalogID")->AsInteger   ;
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
		if (ret <= 0 ) {

		   MessageBoxA(0,"导入数据出错！请重新再试","错误",MB_ICONHAND);
           break;
		}else
		{

		 updatesql = " update BS_StorageNote set amount = " +dataset->FieldByName("Amount")->AsAnsiString ;
		 if (storagediscount) {
		   updatesql =updatesql  +  " ,discount = " +dataset->FieldByName("Discount")->AsAnsiString + " where id = "+ StrToInt(ret)  ;
		 }else
		 {
		   updatesql = updatesql + " where id = "+ StrToInt(ret) ;
		 }

		if(wholsediscount)
		{
			updatepxdiscount = "update BS_StorageNote_attachment set wsalediscount= "+ dataset->FieldByName("wsalediscount")->AsAnsiString ;
			updatepxdiscount = updatepxdiscount + " WHERE bs_storagenoteid = " + StrToInt(ret);
		}
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(updatesql);
		aq->ExecSQL();

		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(updatepxdiscount);
		aq->ExecSQL();
		}
	   dataset->Next();
	}


	QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);

	Screen->Cursor = crDefault ;
	delete aq;
}
//---------------------------------------------------------------------------



void __fastcall TfrmZNStorageMng::N8Click(TObject *Sender)
{
  AnsiString path;
  AnsiString StgID;
  AnsiString sql;
  StgID = "(-1";
  path = ExtractFilePath(Application->ExeName);
  path = path + "CopyData";
  dsetNote->DisableControls();
  TADODataSet *dataset = new TADODataSet(NULL);

	for (int i=0; i < dbgrdNote->SelectedRows->Count; i++)
	{
		dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
		StgID = StgID + "," + dsetNote->FieldByName("ID")->AsString;
	}
	StgID = StgID + ")";
   sql = "	SELECT   BS_StorageNote.ID, BS_StorageNote.StgNtHeaderID, BS_StorageNote.Amount, BS_StorageNote.Discount,  "
					  " BS_StorageNote.BkInfoID, STK_BookInfo.BkcatalogID, BS_BookCatalog.ISBN, BS_BookCatalog.Name AS CatalogName, "
					  "  BS_StorageNote_attachment.wsalediscount,"
					  "	 BS_BookCatalog.Price, BS_BookCatalog.PressID, BS_PressInfo.AbbreviatedName, "
					 "	STK_BookstackInfo.Name AS BkstackName, BS_BookCatalog.UserDefCode, "
					  "	BS_StorageNote.FixedPrice,STK_BookInfo.BkstackID, STK_BookInfo.SupplierID, "
					  "	BS_StorageNote.DiscountedPrice,   "
					  "	STK_BookInfo.Amount as TotalAmount    "
					  "	FROM   BS_StorageNote left JOIN "
					  "	STK_BookInfo ON BS_StorageNote.BkInfoID = STK_BookInfo.ID left JOIN  "
					  "	BS_BookCatalog ON STK_BookInfo.BkcatalogID = BS_BookCatalog.ID left JOIN  "
					   "	BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID left JOIN   "
					  "	STK_BookstackInfo ON STK_BookInfo.BkstackID = STK_BookstackInfo.ID"
					  " left join BS_StorageNote_attachment ON BS_StorageNote.ID=BS_StorageNote_attachment.bs_storageNoteid ";
   sql = sql +  " where BS_StorageNote.ID in " +  StgID;
   dataset->Connection = m_con ;
   dataset->CommandText = sql;
   dataset->Open();
   dataset->SaveToFile(path,pfXML);
   delete dataset;
   dsetNote->EnableControls();
}
//---------------------------------------------------------------------------
void TfrmZNStorageMng::addwsalediscount()
{
	AnsiString sql;
	sql = "select wsaletype from BS_WsaleDiscount where stgid = " + IntToStr(m_storageID) + " and active = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	float wsalediscount = 100;
	switch (aq->FieldByName("wsaletype")->AsInteger ) {
		case 1:
			sql = "select * from BS_WsaletypeDiscountInfo where type = 1 and stgid = " + IntToStr(m_storageID);
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			wsalediscount = dbnbedtDiscount->Value + aq->FieldByName("alldot")->AsFloat ;
			if (wsalediscount > 100) {
				wsalediscount = 100;
			}
			editpxdiscount->Text = FloatToStr(wsalediscount);
		break;
		case 2:
			if (dsetNote->FieldByName("PressID")->AsString != "") {
            	sql = "select * from BS_WsaletypeDiscountInfo where type = 2 and stgid = " + IntToStr(m_storageID) + " and pressid = " + dsetNote->FieldByName("PressID")->AsString ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				wsalediscount = dbnbedtDiscount->Value + aq->FieldByName("pressdot")->AsFloat ;
            	if (wsalediscount > 100) {
					wsalediscount = 100;
				}
				editpxdiscount->Text = FloatToStr(wsalediscount);
			}
		break;
		case 3:
			if (dsetNote->FieldByName("smallBookTypeID")->AsString != "") {
            	sql = "select * from BS_WsaletypeDiscountInfo where type = 3 and stgid = " + IntToStr(m_storageID) + " and typeid = " + dsetNote->FieldByName("smallBookTypeID")->AsString ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				wsalediscount = dbnbedtDiscount->Value + aq->FieldByName("typedot")->AsFloat ;
            	if (wsalediscount > 100) {
					wsalediscount = 100;
				}
				editpxdiscount->Text = FloatToStr(wsalediscount);
			}
		break;
		case 4:
			sql = "select * from BS_WsaletypeDiscountInfo where type = 4 and stgid = " + IntToStr(m_storageID) + " and supplierid = " + dsetSupplier->FieldByName("ID")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			wsalediscount = dbnbedtDiscount->Value + aq->FieldByName("supplierdot")->AsFloat ;
			if (wsalediscount > 100) {
				wsalediscount = 100;
			}
			editpxdiscount->Text = FloatToStr(wsalediscount);
		break;
	default:
		;
	}

}
//---------------------------------------------------------------------------

void TfrmZNStorageMng::lastyjpxdiscount()
{
	AnsiString sql;
	sql = "select top 1 wsalediscount from BS_StorageNote_attachment where BkInfoID = " + dsetNote->FieldByName("BkInfoID")->AsString + " and wsalediscount <> 0 order by ID DESC";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	float wsalediscount = 100;
	if (aq->RecordCount > 0) {
		wsalediscount =  aq->FieldByName("wsalediscount")->AsFloat;
	}
	editpxdiscount->Text = FloatToStr(wsalediscount);
}
//---------------------------------------------------------------------------

void TfrmZNStorageMng::yjpxdiscount()
{
	if (lastjypxdiscount && yjpxkind == "") {
		lastyjpxdiscount();
	}
	else if (addnote && yjpxkind == "") {
		addwsalediscount();
	}
	else if (yjpxkind == "lastyjpxdiscount") {
		lastyjpxdiscount();
		if (editpxdiscount->Text == "100") {
			addwsalediscount();
		}
	}
	else if (yjpxkind == "adddotenable") {
		addwsalediscount();
		if (editpxdiscount->Text == "100") {
			lastyjpxdiscount();
		}
	}
	float price,pxprice;
	price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
	pxprice = price * StrToFloat(editpxdiscount->Text) * 0.01 ;
	editpxprice->Text =  FormatFloat("0.00",pxprice);
	UpdateWsaleDiscout(1);
}
//---------------------------------------------------------------------------


void __fastcall TfrmZNStorageMng::BtnView1Click(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,linfo.con,linfo.storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::dbedtSupplySNExit(TObject *Sender)
{
  	UpdateNtHeader();
}
//---------------------------------------------------------------------------


void __fastcall TfrmZNStorageMng::BtnSaveClick(TObject *Sender)
{
	if (!SaveOK()) {
        return;
	}
	edtCatalog->SetFocus();
}
//---------------------------------------------------------------------------
bool TfrmZNStorageMng::SaveOK()
{
	/*if (dblkpcbbSupplierID->Enabled) {
		MessageBoxA(0,"请在单位处用回车键确认供应商！","提示",MB_ICONASTERISK);
		return false;
  }  */
  if (dsetNote->RecordCount > 0 && dsetNtHeader->FieldByName("StgNtCode")->AsInteger  != 0) {
	if (dsetSupplier->FieldByName("ID")->AsInteger != beforesupplier) {
		ChangeSupplier();
		beforesupplier = dsetSupplier->FieldByName("ID")->AsInteger;
		UpdateNtHeader();
	}
		SaveOrNot = true;
		BtnSave->Enabled = false;
        dbnbedtAddCosts->Enabled = false;
		dbedtRemarks->Enabled = false;
		dbedtSupplySN->Enabled = false;
		dblkpcbbSupplierID->Enabled = false;
		sbnewcustomer->Enabled = false;
		return true;
  }
  else if (dsetNote->IsEmpty() && dsetNtHeader->FieldByName("StgNtCode")->AsInteger  != 0  ) {
		UpdateNtHeader();
		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		dbedtRemarks->Enabled = false;
		dbedtSupplySN->Enabled = false;
		dblkpcbbSupplierID->Enabled = false;
		sbnewcustomer->Enabled = false;
		return true;
  }
	spsave->Parameters->ParamByName("@MODE")->Value = 1;
  spsave->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger ;
  spsave->Parameters->ParamByName("@STGID")->Value = linfo.storageID;
  spsave->Parameters->ParamByName("@TYPE")->Value = 1;
  spsave->Parameters->ParamByName("@CODEMODE")->Value = 0;
  spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
	spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
  spsave->ExecProc() ;
  historyview();     //SaveBenDan
  dbedtStgNtCode->Text = spsave->Parameters->ParamByName("@ReturnCode")->Value ;
  editdanhao->Text = spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
  UpdateNtHeader();
  SaveOrNot = true;
  BtnSave->Enabled = false;
  dbnbedtAddCosts->Enabled = false;
  dbedtRemarks->Enabled = false;
  dbedtSupplySN->Enabled = false;
  dblkpcbbSupplierID->Enabled = false;
  sbnewcustomer->Enabled = false;
  QryNtHeader();
  return true;
}
//---------------------------------------------------------------------------


 bool TfrmZNStorageMng::SaveStorage(int mode)
{
    if (dsrcNote->DataSet == NULL) {
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
			spsave->Parameters->ParamByName("@CODEMODE")->Value = 0;
			spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
			spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
			spsave->ExecProc() ;
		  }
	  }
	}else return true;

}
//---------------------------------------------------------------------------


void __fastcall TfrmZNStorageMng::RzEdit1KeyPress(TObject *Sender, wchar_t &Key)
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
		sql = " select * from CUST_CustomerInfo where Type =1 and Name like '%"+ RzEdit1->Text.Trim() + "%' order by name";
		dsetSupplier->Active = false;
		dsetSupplier->CommandText = sql;
		dsetSupplier->Active = true;
		dsetSupplier->First();
		dblkpcbbSupplierID->KeyValue = dsetSupplier->FieldByName("ID")->AsInteger ;
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("SupplierID")->AsInteger = dsetSupplier->FieldByName("ID")->AsInteger;
		dsetNtHeader->Post();
		dblkpcbbSupplierID->SetFocus();
        //Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::dblkpcbbSupplierIDExit(TObject *Sender)
{
	//dblkpcbbSupplierID->Enabled = sbnewcustomer->Enabled ;
	//edtCatalog->SetFocus();
  /*
	AnsiString sql = "select Salesman from CUST_CustomerInfo where id = " + IntToStr(dsetSupplier->FieldByName("ID")->AsInteger );
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	sql = "select * from SYS_User where Name = '" + aq->FieldByName("Salesman")->AsString + "' and stgID = " + IntToStr(m_storageID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (!aq->IsEmpty() ) {
		int staff = aq->FieldByName("ID")->AsInteger;
		dblkpcbbStaffID->KeyValue = staff;
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("StaffID")->AsInteger = staff;
		dsetNtHeader->Post();
	}
	else
	{
		dblkpcbbStaffID->KeyValue = NULL;
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("StaffID")->AsString = "";
		dsetNtHeader->Post();
	}
	UpdateNtHeader(); */
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::dbnbedtAddCostsExit(TObject *Sender)
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

void __fastcall TfrmZNStorageMng::dbedtRemarksExit(TObject *Sender)
{
	if (dsetNtHeader->RecordCount > 0) {
		AnsiString sql = "update BS_StorageNoteHeader set Remarks = '" + dbedtRemarks->Text + "' where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		dbedtRemarks->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::BtnReminderClick(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNStorageMng::DBNavClick(TObject *Sender, TNavigateBtn Button)
{
   AnsiString code ;
   code = querydan->FieldByName("StgNtCode")->AsAnsiString ;
   editdanhao->Text = querydan->FieldByName("StgNtCodeStr")->AsAnsiString ;
   QryNtHeader(code,false);

}
//---------------------------------------------------------------------------
void TfrmZNStorageMng::ChangeSupplier()
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
			supplierid = dsetNote->FieldByName("SupplierID")->AsInteger ;
			BkcatalogID =  dsetNote->FieldByName("BkcatalogID")->AsInteger ;
			if (autologout) {
				AutologProS(supplierid,BkcatalogID);
			}
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
			if (autologout) {
				AutologProA();
			}
		}
		if (autologout) {
			UpdateProHeader();
		}

}
//---------------------------------------------------------------------------





void __fastcall TfrmZNStorageMng::BtnImportClick(TObject *Sender)
{
  //	Tfrmprocurequery * frm = new Tfrmprocurequery(Application);
  //	frm->ZNStorage = this;
   //	frm->Init(&linfo);
}
//---------------------------------------------------------------------------


