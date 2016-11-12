//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StorageMngForm.h"
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
#include "NewBookinput1.h"
#include "NewBookModify.h"
#include "UnitExcelImport.h"
#include "SelectCatalogForm.h"
#include "bookQuery.h"
#include "RecMoneyForm.h"
#include "QueryDanHao.h"
#include "Addsyslog.h"
#include "Unitdistribute.h"
#include   <math.h>
#include "Unitcaigouquery.h"
#include "unitorder.h"
#include "unitinorderfenfa.h"
#include "bookhistory.h"
#include "unitCorder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzCommon"
#pragma link "RzDBLook"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TfrmStorageMng *frmStorageMng;
//---------------------------------------------------------------------------
__fastcall TfrmStorageMng::TfrmStorageMng(TComponent* Owner)
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

	dbgrdNote->OnDrawColumnCell=dbgrdNoteDrawColumnCell;
}

void TfrmStorageMng::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = "#,##0.00";

	lblOpName->Caption = li->UserName;
	cmdAddNtHeader->Connection = m_con;
	spQryNtHeader->Connection = m_con;
	spQryNtHeader1->Connection = m_con;
	cmdUpdateNtHeader->Connection = m_con;
	cmdAddNote->Connection = m_con;
	cmdUpdateNote->Connection = m_con;
	adospcopy->Connection = m_con;
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
	adosp->Connection=m_con;
   adogetTotalNum->Connection=m_con;


   	//	dsetBkstack->Connection = m_con;
	//	dsetBkstack->Active = true;
	dtpdate->Date =  dbdtedtHdTime->Date ;
	GetBkStackInfo();
	query->Connection = m_con;
	qudetail->Connection = m_con;
	qrystorge->Connection = m_con;
	aq->Connection = m_con;
	dsetCatalog->Active = true;
	dsetSupplier->Active = true;
	dsetStaff->Active = true;
	dblkpcbbSupplierID->KeyValue = 0;
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
	ChangeOpmode(OPAddNtHeader);
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

	sql = "select * from SYS_BSSET where name = 'storagesametishi'" ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	sameid =   query->FieldByName("value")->AsBoolean ;

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

	rkbk = query->FieldByName("bk")->AsAnsiString ;   */

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
		DBNav->Visible = false;*/
		dgdetail->Columns->Items[1]->Visible = false;
		dgdetail->Columns->Items[0]->Visible = true;
	}

	sql = "select * from SYS_BSSET where name = 'xiaoshudian'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	format = "￥###,###,##" + query->FieldByName("bk")->AsString ;
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
	RzDBNumericEdit3->DisplayFormat = "￥###,###,##0.00";
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
	//修改单头密码是否启用
	sql = "select * from SYS_BSSET where name = 'rkusechange'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	changepassword  = query->FieldByName("value")->AsBoolean ;

	strlist = NULL;
	strlist =new TStringList();
	sql = "select BkcatalogID from BS_OrderNote join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id where BS_OrderNote.state = 0 and (BS_OrderNote.UnsendAmount > BS_OrderNote.localnum) and BS_OrderNoteHeader.type = 1 and BS_OrderNoteHeader.stgid <> " + IntToStr(m_storageID) ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	//catalogidlist = "-1";
	while (!query->Eof )
	{
		strlist->Add(query->FieldByName("BkcatalogID")->AsAnsiString);
		//catalogidlist = catalogidlist + "," + query->FieldByName("BkcatalogID")->AsAnsiString;
		query->Next();
	}


        //新建供应商权限设置
          
          if (li->FormatStr.SubString(1,1)=="1") {
            newsupplier=true;
             sbnewcustomer->Enabled = true;
          }else {
            newsupplier = false;
           sbnewcustomer->Enabled = false;}



           if (li->FormatStr.SubString(2,1)=="1") {
             bookcatalogadd=true;
           }else bookcatalogadd=false;
           if (li->FormatStr.SubString(3,1)=="1") {
             bcatalogmodify=true;
           }else bcatalogmodify=false;


           //新建供印商　书目以及修改书目，是否被锁定
           // checknewsupplier();
           disablenewsupplierornewbook();
		 FormView();



if (linfo.storageID==2) {
	   editcamount->Visible=false;
	   Label14->Visible=false;
	   sbtongbu->Visible=false;
	   lblAmount->Caption="数量";

	   dbgrdNote->Columns->Items[9]->Visible=false;
	   dbgrdNote->Columns->Items[8]->Title->Caption ="数量";
	}

   if (linfo.storageID==0)  //B网
   {
			 BtnBullets->Caption="B"+BtnBullets->Caption;
   } else if (linfo.storageID==3 ) { //C网

       BtnBullets->Caption="C"+BtnBullets->Caption;
   }


}
void TfrmStorageMng::GetBkStackInfo()
{
   AnsiString sql= "select name, ID,stgid from STK_BookstackInfo ";// where stgid="+IntToStr(linfo.storageID);
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

	if ((linfo.storageID==0)||(linfo.storageID==3)) {


	 if (aq->FieldByName("stgid")->AsInteger   ==0) {
		 cbbkstackID->AddItem(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger);

	 }else if (aq->FieldByName("stgid")->AsInteger ==3) {
		cbckuwei->AddItem(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger);

	 }
	 } else  {

      if (aq->FieldByName("stgid")->AsInteger ==3) {
		cbckuwei->AddItem(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger);

	 }
	  if (aq->FieldByName("stgid")->AsInteger ==4) {

		cbbkstackID->AddItem(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger);

	 } 	}
	 aq->Next();

   }
		cbckuwei->ItemIndex = 0;
	   cbbkstackID->ItemIndex = 0;
  }
  __finally
  {
	delete aq;
  }
}
void TfrmStorageMng::ChangeCatalogSearchMode()
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

void TfrmStorageMng::ChangeBsmode(BSMode bsmode)
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

void TfrmStorageMng::ChangeOpmode(OPMode opmode)
{
	//if (opmode == m_opmode
	 //	&& (opmode == OPDelNtHeader))
	 //	return;
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

			Tfrmcaigouquery* frm = new Tfrmcaigouquery(Application,m_con,m_storageID,2,0);
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
					AnsiString code = frm->GetNoteCode();
					AnsiString sqlwhere = frm->GetWhere();
					try
					{
						QryNtHeader(code);
						String sql,codetmp;
						codetmp = code;
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
                     GetTotalNum(dsetNtHeader->FieldByName("ID")->AsInteger);

					}
					__finally
					{
					}
					m_opmode = opmode;
					dtpdate->Date =  dbdtedtHdTime->Date ;//更新日期
					delete frm;
					SaveOrNot = true;
					BtnSave->Enabled = false;
					dblkpcbbSupplierID->Enabled = false;
					sbnewcustomer->Enabled = false;
					//dbedtSupplySN->Enabled = false;
					dbnbedtAddCosts->Enabled = false;
					cbtype->Enabled = false;
				}


													   //change danhao
			/*if (ChangeDisplay) {

			   TfrmQuery * frm = new TfrmQuery(this);
			   frm->Init(&linfo);
			   if (frm->ShowModal() == mrOk  )
			   {
				  //DBNav->Enabled = true;
					edtCatalog->Text = "";
					edtQrySupplier->Text = "";

				  AnsiString sql;
				  if (frm->RDanhao) {  //按单号来查询
					  sql = "select * from BS_StorageNoteHeader where  stgNtcodeInt between ";
					  sql = sql + IntToStr(frm->Max) + " and " + IntToStr(frm->Min) + " and totalamount >= 0";
				  }else
				  {
					   sql = "select * from BS_StorageNoteHeader where  hdtime between '";
					   sql = sql + DateToStr(frm->FMax )  + " 0:00:00' and '" + DateToStr(frm->TMin) + " 23:59:59' and totalamount >= 0";
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
							sql = "select * from BS_StorageNoteHeader where StgNtCode >= " +  codetmp + "00000 and StgNtCode <= " + codetmp + "09999";
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


			}*/
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
			AddNtHeader();
			m_opmode = opmode;
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
			frm->salediscount = 1;
			frm->ChangeBsmode(m_bsmode);
			if (frm->ShowModal() == mrOk)
			{
				int amount = 0;
				float discount = 0;
				pixiaodiscount = 0.00;
				lsdiscount = 0.00;
				bool bsetAmount = frm->GetAmount(amount);
				bool bsetDiscount = frm->GetDiscount(discount);
				bsetpixiaodiscount = frm->GetpixiaoDiscount(pixiaodiscount);
				bsetlsdiscount = frm->GetlsDiscount(lsdiscount);
				if (cbtype->Text == "样书入库") {
                	bsetDiscount = false;
				}
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
				else if (bsetlsdiscount) {
					BatchSetNotes(amount, discount, 4);
				}
				QryNtHeader();

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
				MessageBox(0,"现场付款只能付当日的！","入库单" ,MB_OK);
				return;
			}*/
			if (StrToDate(dsetNtHeader->FieldByName("HdTime")->AsAnsiString) != Date()  ) {
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
				AnsiString Code = NoteCode::BuildCode(aq, GetDBTime(aq), 0, "FN_CUSEndMoneyDocuments", "MoneyCode");
				sql = "insert into FN_CUSEndMoneyDocuments (MoneyCode,date,state,type,userid,CustmerName,ClearingType,Clearingstyle) values ("+Code+",getdate(),1,1," + IntToStr(m_userID) +",'" + dblkpcbbSupplierID->Text + "','现场付款','现金')";
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
				sql = "insert into FN_CUSEndMoneyDtails(EndMoneyDocumentID,stgntcode,thistime,type,CodeStr) values(" + Code + "," + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString + "," + FloatToStr(frm->GetReceived()) + ",1,'" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString + "')";
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

}

void TfrmStorageMng::AddNtHeader()//添加单头
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

void TfrmStorageMng::QryNtHeader(String code, bool qrybkstack)//查询单头
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
		grdCellClick();
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
		if (dsetNtHeader->FieldByName("state")->AsInteger == 0 ) {
			cbtype->ItemIndex = 0;
		}
		else
		{
			cbtype->ItemIndex = 1;
		}

                lock(dsetNtHeader->FieldByName("lock")->AsInteger);
	}
	catch(Exception &E)
	{
		//ShowMessage("该单不存在！");
		logmessage = E.Message ;
		AddEvent(3,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);
	}
}


void TfrmStorageMng::QryNtHeader(bool qrybkstack)//查询单头
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
			grdCellClick();
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
			if (dsetNtHeader->FieldByName("state")->AsInteger == 0 ) {
				cbtype->ItemIndex = 0;
			}
			else
			{
				cbtype->ItemIndex = 1;
			}
		}
		catch(Exception &E)
		{
			//ShowMessage("该单不存在！");
			logmessage = E.Message;
			AddEvent(3,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);
		}
	}
}

void TfrmStorageMng::QryNtHeader(int id, bool qrybkstack)//查询单头
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
		grdCellClick();
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
		if (dsetNtHeader->FieldByName("state")->AsInteger == 0 ) {
			cbtype->ItemIndex = 0;
		}
		else
		{
			cbtype->ItemIndex = 1;
		}
	}
	catch(Exception &E)
	{
			//ShowMessage("该单不存在！");
		logmessage = E.Message;
		AddEvent(3,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);
	}
}

void TfrmStorageMng::DelNtHeader()//删除单头
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdDelNtHeader->Parameters->ParamByName("@ID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		int id = dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdDelNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
		cmdDelNtHeader->Execute();
		if (ChangeDisplay) {
				logmessage = "删除入库单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		}
		else
		{
				logmessage = "删除入库单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
		}
		AddEvent(1,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);
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

void TfrmStorageMng::UpdateNtHeader()//更新单头
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
			membk->Text ;
		cmdUpdateNtHeader->Parameters->ParamByName("@SupplySN")->Value =
			dsetNtHeader->FieldByName("SupplySN")->AsWideString;
		cmdUpdateNtHeader->Parameters->ParamByName("@CustomerID")->Value =
			dsetNtHeader->FieldByName("SupplierID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
		cmdUpdateNtHeader->Execute();

		if (dsetNtHeader->RecordCount > 0) {
			AnsiString sql ;
        	if (cbtype->Text == "正常入库") {
				sql = "update BS_StorageNoteHeader set state = 0 where id = " + dsetNtHeader->FieldByName("id")->AsString ;
			}
			else
			{
            	sql = "update BS_StorageNoteHeader set state = 2 where id = " + dsetNtHeader->FieldByName("id")->AsString ;
			}

			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
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

bool TfrmStorageMng::AddNote(int supplierID, int catalogID)//添加单
{
	bool result = false;
	int kuwei;
	int ckuwei;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetCatalog->Active )
	{
		//获取库位
		 kuwei= GetKuWeizuijing(catalogID,supplierID,linfo.storageID,ckuwei);
		 if (kuwei!=-1) {
			for (int i =0; i < cbbkstackID->Items->Count ; i++) {
			if ((int)(cbbkstackID->Items->Objects[i])== kuwei) {
			cbbkstackID->ItemIndex = i;
			break;
			}
			}
		 } else cbbkstackID->ItemIndex=0;
		  if (ckuwei!=-1) {
			for (int i =0; i < cbckuwei->Items->Count ; i++) {
			if ((int)(cbckuwei->Items->Objects[i])== kuwei) {
			cbckuwei->ItemIndex = i;
			break;
			}
			}
		 }else cbckuwei->ItemIndex =0;


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
				editjingjiaprice->Text = dbgrdNote->DataSource->DataSet->FieldByName("Price")->AsAnsiString ;
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}

			if (dsetNtHeader->FieldByName("printcount")->AsInteger > 0 || m_userID != dsetNtHeader->FieldByName("OperatorID")->AsInteger ) {
				if (ChangeDisplay) {
					logmessage = "添加一般入库单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
				}
				else
				{
					logmessage = "添加一般入库单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
				}
				logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
				AddEvent(1,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);
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

bool TfrmStorageMng::AddNote(int id)
{
	bool result = false;
	int kuwei;
	int ckuwei;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{

		//获取库位
	 kuwei= GetKuWeizuijing(id,dsetNtHeader->FieldByName("SupplierID")->AsInteger,linfo.storageID,ckuwei);
		 if (kuwei!=-1) {
			for (int i =0; i < cbbkstackID->Items->Count ; i++) {
			if ((int)(cbbkstackID->Items->Objects[i])== kuwei) {
			cbbkstackID->ItemIndex = i;
			break;
			}
			}
		 } else cbbkstackID->ItemIndex=0;

		  if (ckuwei!=-1) {
			for (int i =0; i < cbckuwei->Items->Count ; i++) {
			if ((int)(cbckuwei->Items->Objects[i])== kuwei) {
			cbckuwei->ItemIndex = i;
			break;
			}
			}
		 } else cbckuwei->ItemIndex =0;

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



void TfrmStorageMng::UpdateNote()//更新单
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
			if (amount != abs(dsetNote->FieldByName("Amount")->AsInteger)) {
				ss = "数量" + IntToStr(amount) + "为" + dsetNote->FieldByName("Amount")->AsAnsiString;
			}
			if (discount != fabs(dsetNote->FieldByName("Discount")->AsFloat)) {
				ss = ss + "折扣" + FloatToStr(discount) + "为" + dsetNote->FieldByName("Discount")->AsAnsiString;
			}
			if (ss != "") {
				if (ChangeDisplay) {
					logmessage = "修改一般入库单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
				}
				else
				{
					logmessage = "修改一般入库单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
				}
				logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
                logmessage = logmessage + ss;
				AddEvent(1,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);
			}
		}

		cmdUpdateNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;


                 cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
			= abs(dsetNote->FieldByName("Amount")->AsInteger);




		if (cbtype->Text == "正常入库") {


                            cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
			= fabs(dsetNote->FieldByName("Discount")->AsFloat);


		}
		else
		{

                     cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
			= 0;


		}

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

void TfrmStorageMng::DelNote()//删除单
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdDelNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
			cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 1;
			if (ChangeDisplay) {
				logmessage = "删除入库单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "删除入库单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
			AddEvent(1,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);
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
				logmessage = "删除入库单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "删除入库单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
			AddEvent(1,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				if (ChangeDisplay) {
					logmessage = "删除入库单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
				}
				else
				{
					logmessage = "删除入库单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
				}
				logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
				AddEvent(1,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);
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

void TfrmStorageMng::BatchSetNotes(int amount, float discount, int mode)
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
			if (bsetlsdiscount) {
				BatchsetLsDiscout(lsdiscount);
			}

		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			if (bsetpixiaodiscount) {
				BatchsetWsaleDiscout(pixiaodiscount);
			}
			if (bsetlsdiscount) {
				BatchsetLsDiscout(lsdiscount);
			}
			ids = dsetNote->FieldByName("ID")->AsString;
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{

				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				if (bsetpixiaodiscount) {
					BatchsetWsaleDiscout(pixiaodiscount);
				}
				if (bsetlsdiscount) {
					BatchsetLsDiscout(lsdiscount);
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

void __fastcall TfrmStorageMng::edtQrySupplierKeyPress(TObject *Sender, wchar_t &Key)
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
			ARRAYOFCONST((dblkpcbbSupplierID->Text.c_str())));
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

void __fastcall TfrmStorageMng::dblkpcbbStaffIDKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
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
				AddEvent(3,"一般入库窗口",m_userID,m_storageID,"定价输入不规范",linfo.con);
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
						frm->DoModalType = 3;
						frm->Storagefrm = this;
						frm->qikan = chqikan->Checked ;
						frm->qikanhao = edqikan->Text ;


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
					 if ( !dsetNote->Locate("BkcatalogID",str,Opts))
					 {


									if (AddNote(supplierID, catalogID))
									{
										Key=0;

										yjpxdiscount();

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
									}else
									{



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
									  //
								}

							  }
						 }else  {
								   if ((!frm->findbook)&&(!bookcatalogadd)) {     //产生新书
											//新书目
                                                                                 if (bookcatalogadd) {


										if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
										{
										   Tfrmnewbook1 *frma = new Tfrmnewbook1(m_app,m_con);
										   frma->StorageMng = this;
										   frma->modle = 1;
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

								   }else   MessageBox(0,"无权限新建书目！","提示",MB_ICONWARNING );
                                                                              }
							   }

						 Key=0;
						 edtCatalog->Text = "";
						 edqikan->Text = "";
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
void __fastcall TfrmStorageMng::dbedtSupplySNKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		dbnbedtAddCosts->SetFocus();
		//Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng::dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;

		if (chfoceset->Checked) {
			if (chfsdiscount->Checked) {
				Perform(WM_NEXTDLGCTL, 0, 0);
			}
			else if (chpxdiscount->Checked ) {
				editpxdiscount->SetFocus();
			}
			else if (chpxprice->Checked ) {
				editpxprice->SetFocus();
			}
			else if (chlsdiscount->Checked ) {
				 edlsdiscount->SetFocus();
			}
			else if (chlsprice->Checked ) {
            	edtlsprice->SetFocus();
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
			if (cbtype->Text == "正常入库") {
				Perform(WM_NEXTDLGCTL, 0, 0);
			}
			else
			{
            	edtCatalog->SetFocus();
			}
		}
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
		historyview();
	}
}
//---------------------------------------------------------------------------

void TfrmStorageMng::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1 && dsetNtHeader->FieldByName("StgNtCode")->AsInteger == 0)
	{
    	DelNtHeader();
	}
}

void __fastcall TfrmStorageMng::FormClose(TObject *Sender, TCloseAction &Action)
{
	/*if (!SaveStorage(2)) {
		return;
	} */
	/*if (m_opmode == OPAddNtHeader && autologout) {
		AutologPro();
		UpdateProHeader();
	} */
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

void __fastcall TfrmStorageMng::RzToolButton9Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::RzToolButton8Click(TObject *Sender)
{
	//打印
	if (N11->Checked ) {    //异常打印
        if (dsetNtHeader->IsEmpty() || dsetNote->IsEmpty()) {
			return;
		}
		AnsiString sql;
		sql = "select * from BS_StorageNote_attachment left join BS_StorageNote on BS_StorageNote.id = BS_StorageNote_attachment.BS_StorageNoteID where (harmnum > 0 or damagenum > 0) and BS_StorageNote.StgNtHeaderID = " + dsetNtHeader->FieldByName("ID")->AsString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->IsEmpty() ) {
			return;
		}
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
			frm->PrintStoragechashu(StrToInt(dsetNtHeader->FieldByName("ID")->AsString));

			frm->DanhaoChange = ChangeDisplay ;                      //change danhao
			frm->RvSystem1->SystemSetups >>ssAllowSetup;
			frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
			frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
			frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
			frm->RvSystem1->SystemSetups >>ssAllowDestFile;
			frm->RvSystem1->DefaultDest   = rdPreview ;
			frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
			frm->Maker = lblOpName->Caption ;
			frm->rkbk = rkbk;
			frm->printtitle = printtitle;
			frm->contact = contact;
			frm->tel = tel;
			frm->address = address;
			frm->PrintStorageExe();
			/*if (lbcaption->Caption == "入库单")
			{
				 frm->PrintStorageExe(1);
			}else
			{
				 frm->PrintStorageExe(2);
			}    */

			frm->Close();
			delete frm;
		}
		N11->Checked = false;
	}
	else                  //一般打印
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
			frm->RvSystem1->DefaultDest   = rdPrinter ;
			frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
			frm->Maker = lblOpName->Caption ;
			frm->rkbk = rkbk;
			frm->printtitle = printtitle;
			frm->contact = contact;
			frm->tel = tel;
			frm->address = address;
			frm->supplycode = dbedtSupplySN->Text ;
			frm->PrintStorageExe(0);

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
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng::RzToolButton6Click(TObject *Sender)
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

//---------------------------------------------------------------------------
bool __fastcall TfrmStorageMng::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = StringReplace(dblkpcbbSupplierID->Text+editdanhao->Text ,"\\","-",TReplaceFlags()<<rfReplaceAll) + "入库单";
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

	temptext = ",,,一般入库单";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n";
	temptext = temptext + "供应商," + dblkpcbbSupplierID->Text + ",日期," + DateToStr(dtpdate->Date)  + ",单号,'" + editdanhao->Text;
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n";
	temptext = temptext + "供货编号," + dbedtSupplySN->Text + ",附加费用," + dbnbedtAddCosts->Text  + ",采购员," + dblkpcbbStaffID->Text;
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

    temptext = "\n";
	temptext = temptext + "备注," + membk->Text ;
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());    */

	Screen->Cursor=crHourGlass;
	Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",false);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");
//  在Excel中成字符串显示
	/*temptext = "供货商：" + dblkpcbbSupplierID->Text;
	v.OlePropertyGet("Cells",1,1).OlePropertySet("Value",temptext .c_str() );
	temptext = "单号：" + editdanhao->Text;
	v.OlePropertyGet("Cells",2,1).OlePropertySet("Value",temptext .c_str() );
	temptext = "日期：" + DateToStr(dtpdate->Date);
	v.OlePropertyGet("Cells",2,4).OlePropertySet("Value",temptext .c_str() );
	temptext = "备注：" + membk->Text;
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value",temptext .c_str() );  */
	

	n=0;

	int t1= 0;
	temptext = "\n";
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			//temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}

	}
	//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		//temptext = "\n";
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
				} */
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
	//R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n,1),vSheet.OlePropertyGet("Cells",n,t1)); //取得合并的区域
	//R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+2,t1)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	v.OlePropertyGet("Cells",t2+2,1).OlePropertySet("Value","合计");
	//v.OlePropertyGet("Cells",t2+2+n,2).OlePropertySet("Value","总数量");
	temptext = RzDBNumericEdit2->Text ;
	v.OlePropertyGet("Cells",t2+2,9).OlePropertySet("Value",temptext .c_str() );
	//v.OlePropertyGet("Cells",t2+2+n,4).OlePropertySet("Value","总码洋");
	temptext = RzDBNumericEdit3->Text ;
	v.OlePropertyGet("Cells",t2+2,11).OlePropertySet("Value",temptext .c_str() );
	//v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value","总实洋");
	temptext = RzDBNumericEdit4->Text ;
	v.OlePropertyGet("Cells",t2+2,12).OlePropertySet("Value",temptext .c_str() );
	dbg->DataSource ->DataSet->EnableControls();

	try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
			 xWorkbook.OleFunction( "Close");
		 v.OleFunction("Quit");
	MessageBox(Handle,"导出完毕！","提示" ,MB_OK|MB_ICONINFORMATION);
	} catch (...) {
	Screen->Cursor=crDefault;
	}
    Screen->Cursor=crDefault;
	/*AnsiString rkamount,mayang,shiyang;
	mayang =  RzDBNumericEdit3->Text;
	shiyang = RzDBNumericEdit4->Text;
	rkamount = RzDBNumericEdit2->Text ;
	mayang = StringReplace(mayang , ",","",TReplaceFlags()<<rfReplaceAll);
	shiyang = StringReplace(shiyang , ",","",TReplaceFlags()<<rfReplaceAll);
	rkamount = StringReplace(rkamount , ",","",TReplaceFlags()<<rfReplaceAll);
	temptext = "\n";
	temptext = temptext + "合计,,,,,,,," + rkamount + ",," + mayang + "," + shiyang ;

	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);   */

    //MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}

//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::dbnbedtAmountExit(TObject *Sender)
{
	UpdateNote();
	GetTotalNum(dsetNtHeader->FieldByName("ID")->AsInteger);
}

//---------------------------------------------------------------------------


void TfrmStorageMng::QryBkstack()
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

void __fastcall TfrmStorageMng::dsetNoteAfterScroll(TDataSet *DataSet)
{
	//
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		QryBkstack();
    }
}
//---------------------------------------------------------------------------

void TfrmStorageMng::OnHotKeyPress(DWORD vkCode, bool ctrlpress)
{
	//快捷键

}

void TfrmStorageMng::ResetNtHeader()
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
void __fastcall TfrmStorageMng::sbnewcustomerClick(TObject *Sender)
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
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::spnewbookClick(TObject *Sender)
{
	//新书目
	if (dblkpcbbSupplierID->Enabled ) {
        return;
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
	   Tfrmnewbook1 *frm = new Tfrmnewbook1(m_app,m_con);
	   frm->StorageMng = this;
	   frm->modle = 1;//入库
	   if (chqikan->Checked) {
			frm->cbsaletype->Text = "期刊";
			frm->cbsaletypeChange(this);
	   }
	   if (mbOK == frm->ShowModal())
	   {
			edtCatalog->Text  = "";
			dbnbedtAmount->Text = "0";
			dbnbedtDiscount->Text = "100";
			editpxdiscount->Text = "100";
			edlsdiscount->Text = "100";
			editshun->Text = "0";
			editque->Text = "0";
			editjingjiaprice->Text = "0.00";
			editpxprice->Text = "0.00";
			edtlsprice->Text = "0.00";
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


void __fastcall TfrmStorageMng::BtnViewClick(TObject *Sender)
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

void __fastcall TfrmStorageMng::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		PM->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::N1Click(TObject *Sender)
{
    lblCatalog->Caption = "书号";
	m_catalogSearchMode = 1;
	if (chqikan->Checked) {
		edtCatalog->MaxLength = 15;
	}
	else
	{
    	edtCatalog->MaxLength = 13;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码";
	m_catalogSearchMode = 2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名";
	m_catalogSearchMode  = 3;
	edtCatalog->MaxLength = 0;
}
void TfrmStorageMng::changeInputMode()
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
	 case 5:
		N1->Click();
		break;
	 case 6:
		N10->Click();
		break;
  	default:
      ;
	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::BtnClearClick(TObject *Sender)
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
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;
		frm->supplycode = dbedtSupplySN->Text ;
		frm->PrintStorageExe(1);
		/*if (lbcaption->Caption == "入库单")
		{
			 frm->PrintStorageExe(1);
		}else
		{
			 frm->PrintStorageExe(2);
		} */

		frm->Close();
		delete frm;


	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::RzToolButton3Click(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageMng::RzToolButton5Click(TObject *Sender)
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

void __fastcall TfrmStorageMng::RzToolButton2Click(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::FormResize(TObject *Sender)
{
	 //dbgrdNote->Width = 720;
	 //dbgrdNote->Height = 352;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageMng::dblkpcbbSupplierIDKeyPress(TObject *Sender, wchar_t &Key)

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

void  TfrmStorageMng::FindNote(String code)
{
	DelInvalidNtHeader();
	edtCatalog->Text = "";
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



void __fastcall TfrmStorageMng::dbgrdNoteDblClick(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
        if (!bcatalogmodify) {
              return ;
        }
       
		TfrmNewBookModify * frm = new TfrmNewBookModify(m_app,m_con,dsetNote->FieldByName("BkcatalogID")->AsInteger,m_storageID,m_userID);
		frm->ShowModal();
		delete frm;
		QryNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::dbgrdNoteCellClick(TColumn *Column)
{
	grdCellClick();
}
//---------------------------------------------------------------------------
void TfrmStorageMng::grdCellClick()
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	if (dsetNote->RecordCount > 0) {
		cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)dsetNote->FieldByName("BkstackID")->AsInteger ) ;
	   	AnsiString sql;
		sql = "select wsalediscount,lsdiscount,returnflag,harmnum,damagenum,camount,ckuwei from BS_StorageNote_attachment where BS_StorageNoteID =" + dbgrdNote->DataSource->DataSet->FieldByName("ID")->AsAnsiString  ;
		TADOQuery *aq =new TADOQuery(NULL);
		aq->Connection = m_con ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		editpxdiscount->Text = aq->FieldByName("wsalediscount")->AsAnsiString ;
		edlsdiscount->Text = aq->FieldByName("lsdiscount")->AsAnsiString ;
		editshun->Text = aq->FieldByName("harmnum")->AsAnsiString ;
		editque->Text = aq->FieldByName("damagenum")->AsAnsiString ;
		cbreturn->Checked = aq->FieldByName("returnflag")->AsBoolean ;

		cbckuwei->ItemIndex = cbckuwei->Items->IndexOfObject((TObject*)aq->FieldByName("ckuwei")->AsInteger ) ;
		editcamount->Text = aq->FieldByName("camount")->AsInteger;

		float jinjia;
		float discount;
		float price ;
		if (editjingjiaprice->Text == "") {
			editjingjiaprice->Text = "0.00";
		}
		try {
			price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
			jinjia = price * dbnbedtDiscount->Value * 0.01 ;
			editjingjiaprice->Text =  FormatFloat("0.00",jinjia);
			editpxprice->Text = FormatFloat("0.00",price*aq->FieldByName("wsalediscount")->AsFloat*0.01);
			edtlsprice->Text = FormatFloat("0.00",price*aq->FieldByName("lsdiscount")->AsFloat*0.01);
		} catch (Exception &E) {
        	logmessage = E.Message;
			AddEvent(3,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);
		}
		delete aq;
		historyview();
	}
}
//---------------------------------------------------------------------------

void TfrmStorageMng::historyview()
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

void __fastcall TfrmStorageMng::N5Click(TObject *Sender)
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



void __fastcall TfrmStorageMng::mniBsNoteClick(TObject *Sender)
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

void __fastcall TfrmStorageMng::N6Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode  = 6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::BtnNewClick(TObject *Sender)
{
         lock(0);
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
	/*if (m_opmode == OPAddNtHeader && autologout) {
		AutologPro();
		UpdateProHeader();
	}*/
	ChangeBsmode(BSNote);
	RzToolButton5Click(BtnNew);
	dblkpcbbSupplierID->KeyValue = 0;
	SaveOrNot = false;
	BtnSave->Enabled = true;
	dbnbedtAddCosts->Enabled = true;
	dblkpcbbSupplierID->Enabled = true;

	 if (newsupplier) {
                  sbnewcustomer->Enabled = true;
                }else sbnewcustomer->Enabled = false;

	dbedtSupplySN->Enabled = true;
	cbtype->Enabled = true;
	dsetNtHeader->Edit();
	dsrcNtHeader->DataSet->FieldByName("AddCosts")->Value =  0.0;
	dsrcNtHeader->DataSet->FieldByName("Remarks")->Value =  "";
	dsrcNtHeader->DataSet->FieldByName("SupplySN")->Value =  "";
	dsetNtHeader->UpdateRecord();
	membk->Text = "";
	cbtype->ItemIndex = 0;
	dbedtSupplySN->Text = "";
	RzEdit1->Text = "";
	editdanhao->Text = "";
	dbnbedtAddCosts->Value = 0.0;
	dblkpcbbStaffID->KeyValue = -1;
	dblkpcbbSupplierID->SetFocus();

		 totalnum->Text = "";
	 editshiyang->Text= "";
	 edittotalmayang->Text = "";
	try {
    	qudetail->Active = false;
	} catch (...) {
	}

}
//---------------------------------------------------------------------------

void  TfrmStorageMng::ModifyEnable()
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

void __fastcall TfrmStorageMng::dtpdateChange(TObject *Sender)
{
	dbdtedtHdTime->Date =  dtpdate->Date;

}
//---------------------------------------------------------------------------
void TfrmStorageMng::UpdateWsaleDiscout(int mode)
{
	if (dsetNote->IsEmpty() ) {
        return;
	}
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
		if (mode == 6) {
			 adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 6;
			adospupdatewsaleprice->Parameters->ParamByName("@lsdiscount")->Value
			= StrToFloat(edlsdiscount->Text);
		}
		if (mode == 7) {
			adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 7;
			adospupdatewsaleprice->Parameters->ParamByName("@lsprice")->Value
			=  StrToFloat(edtlsprice->Text);
		}
		if (mode == 8) {
			adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 8;

			   //同时更新库位信息

			adospupdatewsaleprice->Parameters->ParamByName("@harmnum")->Value
			=   (int)(cbckuwei->Items->Objects[cbckuwei->ItemIndex]);
			adospupdatewsaleprice->Parameters->ParamByName("@camount")->Value
			=  StrToInt(editcamount->Text);


		} //只更新c版库位
		if (mode == 9) {
			adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 8;

			   //同时更新库位信息

			adospupdatewsaleprice->Parameters->ParamByName("@harmnum")->Value
			=   (int)(cbckuwei->Items->Objects[cbckuwei->ItemIndex]);
			adospupdatewsaleprice->Parameters->ParamByName("@camount")->Value
			=  0;


		}



		 adospupdatewsaleprice->ExecProc();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::editpxdiscountExit(TObject *Sender)
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

void __fastcall TfrmStorageMng::dbnbedtDiscountExit(TObject *Sender)
{

	float jinjia;
	float discount;
	float price ;
	UpdateNote();

	if (!dsetNote->IsEmpty() ) {
		if (editjingjiaprice->Text == "") {
			editjingjiaprice->Text = "0.00";
		}
		try {
        	price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
			jinjia = price * dbnbedtDiscount->Value * 0.01 ;
			editjingjiaprice->Text =  FormatFloat("0.00",jinjia);
			yjpxdiscount();
		} catch (Exception &E) {
        	logmessage = E.Message;
			AddEvent(3,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);
		}
		GetTotalNum(dsetNtHeader->FieldByName("ID")->AsInteger);
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::editjingjiapriceExit(TObject *Sender)
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

void __fastcall TfrmStorageMng::editjingjiapriceKeyPress(TObject *Sender, wchar_t &Key)

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

void __fastcall TfrmStorageMng::editpxdiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == '\r')
	{
		Key = 0;
		if (chfoceset->Checked) {
			if (chpxprice->Checked ) {
				editpxprice->SetFocus();
			}
			else if (chlsdiscount->Checked ) {
				 edlsdiscount->SetFocus();
			}
			else if (chlsprice->Checked ) {
            	edtlsprice->SetFocus();
			}
			else if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbgrdNote->SetFocus();
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
			else if (chpxdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editpxdiscount->SetFocus();
				}
			}
		}
		else
		{
			editpxprice->SetFocus();
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::editpxpriceExit(TObject *Sender)
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

void __fastcall TfrmStorageMng::editpxpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == '\r')
	{
		Key = 0;
		if (chfoceset->Checked) {
			if (chlsdiscount->Checked ) {
				 edlsdiscount->SetFocus();
			}
			else if (chlsprice->Checked ) {
            	edtlsprice->SetFocus();
			}
			else if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!dsetNote->Eof) {
					//dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbgrdNote->SetFocus();
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
			else if (chpxdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editpxdiscount->SetFocus();
				}
			}
			else if (chpxprice->Checked ) {
            	if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editpxprice->SetFocus();
				}
			}
		}
		else
		{
			edlsdiscount->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::editshunExit(TObject *Sender)
{
 if (editshun->Text == "") {
	 editshun->Text = "0";
 }
	UpdateWsaleDiscout(3);
	QryNtHeader();

}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::editqueExit(TObject *Sender)
{
 if (editque->Text == "") {
	 editque->Text = "0";
 }
	UpdateWsaleDiscout(4);
	QryNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::editqueKeyPress(TObject *Sender, wchar_t &Key)
{
   if (Key == '\r')
	{
		Key = 0;

	   edtCatalog->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::editshunKeyPress(TObject *Sender, wchar_t &Key)
{

	if (Key == '\r')
	{
		Key = 0;
			Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmStorageMng::cbreturnExit(TObject *Sender)
{
	UpdateWsaleDiscout(5);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::cbbkstackIDSelect(TObject *Sender)
{
	stackchange = true;
	UpdateNote();
	stackchange = false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng::BtnChangeOptionsClick(TObject *Sender)
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
		BtnSave->Enabled = true;
		dblkpcbbSupplierID->Enabled = true;
		 if (newsupplier) {
                  sbnewcustomer->Enabled = true;
                }else sbnewcustomer->Enabled = false;

		dtpdate->Enabled =  true;
		if (dsetNote->RecordCount > 0) {
			cbtype->Enabled = false;
		}
		else
		{
        	cbtype->Enabled = true;
		}

}
//---------------------------------------------------------------------------

void  TfrmStorageMng::AutologProA()
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

void  TfrmStorageMng::AutologProS(int supplier,int BkcatalogID)
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

void  TfrmStorageMng::AutologPro()
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	dsetNote->First();
	dsetNote->DisableControls();
	while (!dsetNote->Eof )
	{
		AutologProA();
		dsetNote->Next();
	}
	dsetNote->EnableControls();
}
//---------------------------------------------------------------------------

void  TfrmStorageMng::UpdateProHeader()
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
void __fastcall TfrmStorageMng::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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


	if (Shift.Contains(ssAlt)&& Key ==81  ) {
		RzToolButton9->Click();
	}

	if (Shift.Contains(ssAlt)&& Key ==78  ) {
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==70  ) {
		BtnView1->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------
void TfrmStorageMng::BatchsetWsaleDiscout(float pidiscount)
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
void TfrmStorageMng::BatchsetLsDiscout(float lsdiscount)
{

				adospupdatewsaleprice->Parameters->ParamByName("@storageNoteID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
				adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
				= 6;
				adospupdatewsaleprice->Parameters->ParamByName("@lsdiscount")->Value
				=  lsdiscount;
				adospupdatewsaleprice->ExecProc();
}

//---------------------------------------------------------------------------



void __fastcall TfrmStorageMng::dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button,
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


void __fastcall TfrmStorageMng::N9Click(TObject *Sender)
{
 //   dsetNote->SaveToFile("D:\\sd",pfADTG);
	if (BtnSave->Enabled) {
		MessageBoxA(0,"本单还未保存，请先保存！","提示",MB_ICONASTERISK);
		return;
	}
	adospcopy->ProcedureName = "StickData";
	adospcopy->Parameters->Clear();
	adospcopy->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),1);
	adospcopy->Parameters->CreateParameter("@HeadId",ftInteger,pdInput,sizeof(int),dsetNtHeader->FieldByName("ID")->AsInteger);
	adospcopy->Parameters->CreateParameter("@userid",ftInteger,pdInput,sizeof(int),linfo.userID );
	adospcopy->ExecProc();
	QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);

	Screen->Cursor = crDefault ;

}
//---------------------------------------------------------------------------



void __fastcall TfrmStorageMng::N8Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
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
void TfrmStorageMng::addwsalediscount()
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

void TfrmStorageMng::lastyjpxdiscount()
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

void TfrmStorageMng::yjpxdiscount()
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
	if (editpxdiscount->Text == "") {
		editpxdiscount->Text = "100";
	}
	price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
	pxprice = price * StrToFloat(editpxdiscount->Text) * 0.01 ;
	editpxprice->Text =  FormatFloat("0.00",pxprice);
	UpdateWsaleDiscout(1);
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng::BtnView1Click(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,linfo.con,linfo.storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::dbedtSupplySNExit(TObject *Sender)
{
  	UpdateNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::BtnSaveClick(TObject *Sender)
{
	if (!SaveOK()) {
        return;
	}
	cbtype->Enabled = false;
	edtCatalog->SetFocus();
}
//---------------------------------------------------------------------------
bool TfrmStorageMng::SaveOK()
{
	/*if (dblkpcbbSupplierID->Enabled) {
		MessageBoxA(0,"请在单位处用回车键确认供应商！","提示",MB_ICONASTERISK);
		return false;
	}  */
	if (dsetNtHeader->RecordCount > 0) {
		AnsiString sql = "update BS_StorageNoteHeader set HdTime = '" + DateToStr(dtpdate->DateTime)  + "' where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}

  if (dsetNote->RecordCount > 0) {
	if (dsetSupplier->FieldByName("ID")->AsInteger != beforesupplier) { //修该供应商
		ChangeSupplier();
		if (ChangeDisplay) {
			logmessage = "把入库单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		}
		else
		{
			logmessage = "把入库单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
		}
		logmessage = logmessage + "的供应商由" + beforesuppliername + "修改为" + dsetSupplier->FieldByName("Name")->AsAnsiString;
		AddEvent(1,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);
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
	spsave->Parameters->ParamByName("@CODEMODE")->Value = 0;
	spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
	spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
	spsave->ExecProc() ;

  if (ChangeDisplay) {
	logmessage = "添加入库单" + spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
  }
  else
  {
	logmessage = "添加入库单" + spsave->Parameters->ParamByName("@ReturnCode")->Value ;
  }
  AddEvent(1,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);
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


 bool TfrmStorageMng::SaveStorage(int mode)
{
	if (dsrcNote->DataSet->IsEmpty() ) {
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
            if (ChangeDisplay) {
				logmessage = "取消保存入库单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "取消保存入库单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
			}
			AddEvent(1,"一般入库窗口",m_userID,m_storageID,logmessage,linfo.con);

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


void __fastcall TfrmStorageMng::RzEdit1KeyPress(TObject *Sender, wchar_t &Key)
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

void __fastcall TfrmStorageMng::dblkpcbbSupplierIDExit(TObject *Sender)
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

void __fastcall TfrmStorageMng::dbnbedtAddCostsExit(TObject *Sender)
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


void __fastcall TfrmStorageMng::dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		membk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::BtnReminderClick(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::DBNavClick(TObject *Sender, TNavigateBtn Button)
{
   AnsiString code ;
   code = querydan->FieldByName("StgNtCode")->AsAnsiString ;
   editdanhao->Text = querydan->FieldByName("StgNtCodeStr")->AsAnsiString ;
   QryNtHeader(code,false);
   GetTotalNum(dsetNtHeader->FieldByName("ID")->AsInteger);
}
//---------------------------------------------------------------------------
void TfrmStorageMng::ChangeSupplier()
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
			/*if (autologout) {
				AutologProS(supplierid,BkcatalogID);
			} */
                        /*
			sql = "select id from STK_BookInfo where BkcatalogID = " + dsetNote->FieldByName("BkcatalogID")->AsString + " and SupplierID = " + IntToStr(supplier) + " and BkstackID = " + dsetNote->FieldByName("BkstackID")->AsString;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount > 0) {
				bkid = query->FieldByName("ID")->AsInteger ;
			}
			else
			{
				sql = "insert into STK_BookInfo(Amount,BkcatalogID,BkstackID,SupplierID,State,stgid) values (0," + dsetNote->FieldByName("BkcatalogID")->AsString + "," + dsetNote->FieldByName("BkstackID")->AsString + "," + IntToStr(supplier) + ",0," + IntToStr(m_storageID) + ")";
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
			query->ExecSQL(); */
			dsetNote->Next();

		}

}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::dbgrdNoteTitleClick(TColumn *Column)
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

void __fastcall TfrmStorageMng::edlsdiscountExit(TObject *Sender)
{
	float price;
   float lsprice;
   if (edlsdiscount->Text == "") {
	   edlsdiscount->Text = "0.00";
   }
   price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
	lsprice = price * StrToFloat(edlsdiscount->Text) * 0.01 ;
	edtlsprice->Text =  FormatFloat("0.00",lsprice);

   UpdateWsaleDiscout(6);
}
//---------------------------------------------------------------------------

void TfrmStorageMng::FormView()
{
	AnsiString sql;
	sql = "select * from BS_SYS_Formview where stgid = " + IntToStr(m_storageID) + " and ParentID = 5";
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
		if (query->FieldByName("Name")->AsAnsiString == "客户订单" ) {
			BtnBullets->Visible = query->FieldByName("state")->AsBoolean ;
		}
		query->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
		Key = 0;
		if (chfoceset->Checked) {
			if (chpxdiscount->Checked ) {
				editpxdiscount->SetFocus();
			}
			else if (chpxprice->Checked ) {
				editpxprice->SetFocus();
			}
			else if (chlsdiscount->Checked ) {
				 edlsdiscount->SetFocus();
			}
			else if (chlsprice->Checked ) {
            	edtlsprice->SetFocus();
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
//---------------------------------------------------------------------------

void  TfrmStorageMng::operterview(int operterid)
{
	AnsiString sql;
	sql = "select name from sys_user where id = " + IntToStr(operterid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	lblOpName->Caption = aq->FieldByName("name")->AsString;
}
//---------------------------------------------------------------------------



void __fastcall TfrmStorageMng::membkExit(TObject *Sender)
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

void __fastcall TfrmStorageMng::membkKeyPress(TObject *Sender, wchar_t &Key)
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


void __fastcall TfrmStorageMng::SpeedButton1Click(TObject *Sender)
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

void __fastcall TfrmStorageMng::chfsluruClick(TObject *Sender)
{
	if (cbtype->Text == "样书入库" && chfsdiscount->Checked) {
    	chfsdiscount->Checked = false;
	}
	if (!chfsluru->Checked && !chfsamount->Checked && !chfsdiscount->Checked && !chpxdiscount->Checked && !chpxprice->Checked && !chlsdiscount->Checked && !chlsprice->Checked ) {
		chfoceset->Checked = false;
	}
	else
	{
		chfoceset->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::chqikanClick(TObject *Sender)
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

void __fastcall TfrmStorageMng::N10Click(TObject *Sender)
{
	lblCatalog->Caption = "作者";
	m_catalogSearchMode  = 5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::edqikanKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (m_catalogSearchMode == 6) {
        	float price;
			try {
				price = StrToFloat(edtCatalog->Text.Trim());
			} catch (...) {
				MessageBox(0,"请输入正确的定价！","入库" ,MB_ICONEXCLAMATION);
				AddEvent(3,"一般入库窗口",m_userID,m_storageID,"定价输入不规范",linfo.con);
				return;
			}
		 }

		String ISBN;
		bool exec = true;

		TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->Init(&li);
		

		frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
		frm->DoModalType = 3;
		frm->Storagefrm = this;
		frm->qikan = chqikan->Checked ;
		frm->qikanhao = edqikan->Text ;


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
					if ( !dsetNote->Locate("BkcatalogID",str,Opts))
					{
						if (AddNote(supplierID, catalogID))
						{
							Key=0;
							yjpxdiscount();
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
						}else
						{}
					}
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
					Tfrmnewbook1 *frma = new Tfrmnewbook1(m_app,m_con);
					frma->StorageMng = this;
					frma->modle = 1;
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
					{}
					delete frma;
					dbnbedtAmount->SetFocus();
				}
			}
		}

		Key=0;
		edtCatalog->Text = "";
		edqikan->Text = "";
		editshun->Text = "0";
		editque->Text = "0";
		editjingjiaprice->Text = FormatFloat("0.00", dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat * dbnbedtDiscount->Value * 0.01);
		editpxprice->Text =  FormatFloat("0.00", dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat);

		delete frm;
		historyview();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::FormShow(TObject *Sender)
{
	RzEdit1->SetFocus();
   //根据店号不同，显示不同的界面
   if (linfo.storageID ==3) //墨嘉
   {

	   editcamount->Visible=false;
	   Label14->Visible=false;



   }


}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::edlsdiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
	  	Key = NULL;
	}
	if (Key == '\r')
	{
		Key = 0;

		if (chfoceset->Checked) {
			if (chlsprice->Checked ) {
                edtlsprice->SetFocus();
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
			else if (chfsdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbnbedtDiscount->SetFocus();
				}
			}
			else if (chpxdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editpxdiscount->SetFocus();
				}
			}
			else if (chlsdiscount->Checked ) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					edlsdiscount->SetFocus();
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

void __fastcall TfrmStorageMng::edtlspriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
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
			else if (chpxdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editpxdiscount->SetFocus();
				}
			}
			else if (chlsdiscount->Checked ) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					edlsdiscount->SetFocus();
				}
			}
			else if (chlsprice->Checked ) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					edtlsprice->SetFocus();
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

void __fastcall TfrmStorageMng::BtnBulletsClick(TObject *Sender)
{
	if (dsetNtHeader->IsEmpty() || dsetNote->IsEmpty()) {
		return;
	}
	AnsiString sql;
	if (linfo.storageID==0) {   //B网

		sql = "exec USP_BS_fenfa " +  IntToStr(m_storageID) + ",0,0," + dsetNtHeader->FieldByName("id")->AsString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		Tfrmunitorder * frm = new Tfrmunitorder(Application,m_con,dsetNtHeader->FieldByName("id")->AsInteger );
		frm->ISBNET=1;
		frm->rkcode = editdanhao->Text;
		frm->ShowModal();
		delete frm;
	} else if (linfo.storageID==3 ) { //C网

	 sql = "exec C_RukuRedoLockOrder " +  IntToStr(dsetNtHeader->FieldByName("id")->AsInteger) ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		TCfrmunitorder * frm = new TCfrmunitorder(Application,m_con,dsetNtHeader->FieldByName("id")->AsInteger );
        frm->ISBNET=2;
		frm->rkcode = editdanhao->Text;
		frm->ShowModal();
		delete frm;

	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::N11Click(TObject *Sender)
{
	if (N11->Checked ) {
		N11->Checked = false;
	}
	else
	{
		N11->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageMng::dbgrdNoteDrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (strlist->IndexOf(dbgrdNote->DataSource->DataSet->FieldByName("BkcatalogID")->AsString) != -1) {
		dbgrdNote->Canvas->Font->Color = clRed ;
		dbgrdNote->Canvas->FillRect(Rect);
		dbgrdNote->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
	else
	{
		dbgrdNote->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::BtnSetTabsClick(TObject *Sender)
{
	if (dsetNtHeader->IsEmpty() || dsetNote->IsEmpty()) {
		return;
	}

	Tfrmunitinorder * frm = new Tfrmunitinorder(Application,m_con,dsetNtHeader->FieldByName("id")->AsInteger,catalogidlist );
	frm->stgid = m_storageID ;
	frm->userid = m_userID ;
	frm->rkcode = editdanhao->Text;
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::N12Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con,m_storageID,dsetNote->FieldByName("BkcatalogID")->AsInteger,m_userID );
	frm->ShowModal();
	delete frm;
}
void TfrmStorageMng::lock(int type)
{
    if (type==1) {  //锁定

                BtnSave->Enabled = false;
                BtnChangeOptions->Enabled = false;
                RzToolButton5->Enabled = false;
                RzToolButton2->Enabled = false;
                RzToolButton3->Enabled = false;
                BtnReminder->Enabled = false;
                BtnSetTabs->Enabled = false;
                BtnBullets->Enabled = false;
                RzEdit1->Enabled = false;
                edtCatalog->Enabled = false;
                dbnbedtAmount->Enabled = false;
                dbnbedtDiscount->Enabled = false;
                spnewbook->Enabled = false;
                chqikan->Enabled = false;
                sbnewcustomer->Enabled = false;
                editshun->Enabled = false;
                editque->Enabled = false;
                cbbkstackID->Enabled = false;
                selectmenu->AutoPopup = false;
                //imagelock->Visible = true;
                lblock->Caption = "已锁定";
                membk->Enabled = false;
                dbedtSupplySN->Enabled = false;
                editpxdiscount->Enabled= false;
                edlsdiscount->Enabled= false;
                dbnbedtAddCosts->Enabled= false;
                cbstorgename->Enabled= false;
                cbreturn->Enabled= false;
                dblkpcbbStaffID->Enabled= false;
                editjingjiaprice->Enabled= false;
                cbtype->Enabled= false;
                dblclicklock=true;

    }else
    {  cbtype->Enabled= true;
    cbreturn->Enabled= true;
    editjingjiaprice->Enabled= true;
    dblclicklock=false;
                dblkpcbbStaffID->Enabled= true;
                 dbedtSupplySN->Enabled = true;
                editpxdiscount->Enabled= true;
                edlsdiscount->Enabled= true;
                dbnbedtAddCosts->Enabled= true;
                cbstorgename->Enabled= true;
                membk->Enabled = true;
                BtnSave->Enabled = true;
                BtnChangeOptions->Enabled = true;
                RzToolButton5->Enabled = true;
                RzToolButton2->Enabled = true;
                RzToolButton3->Enabled = true;
                BtnReminder->Enabled = true;
                BtnSetTabs->Enabled = true;
                BtnBullets->Enabled = true;
                RzEdit1->Enabled = true;
                edtCatalog->Enabled = true;
                dbnbedtAmount->Enabled = true;
                dbnbedtDiscount->Enabled = true;
                 if (newsupplier) {
                   spnewbook->Enabled = true;
                 }else spnewbook->Enabled = false;


                chqikan->Enabled = true;
                if (newsupplier) {
                  sbnewcustomer->Enabled = true;
                }else sbnewcustomer->Enabled = false;



                editshun->Enabled = true;
                editque->Enabled = true;
                cbbkstackID->Enabled = true;
                selectmenu->AutoPopup = true;
                //imagelock->Visible = false;
                lblock->Caption = "";
                disablenewsupplierornewbook();//
    }




}
void TfrmStorageMng::checknewsupplier()
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
void TfrmStorageMng::disablenewsupplierornewbook()
{

     //bool  supplier,bookcatalogadd,bcatalogmodify;
     if (newsupplier) {
        sbnewcustomer->Enabled = true;
     }else sbnewcustomer->Enabled = false;
     if (bookcatalogadd) {
          spnewbook->Enabled = true;
     }else spnewbook->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng::editcamountExit(TObject *Sender)
{
//
   if (editcamount->Text!="") {
	 UpdateWsaleDiscout(8);
	 QryNtHeader();
	 GetTotalNum(dsetNtHeader->FieldByName("ID")->AsInteger);
   }

}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::editcamountKeyPress(TObject *Sender, wchar_t &Key)

{
//
if (Key == '\r')
	{
		Key = 0;
		dbnbedtDiscount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng::sbtongbuClick(TObject *Sender)
{
//同步生成c网入库单
  /* try
{
 adosp->ProcedureName="C_RukuRedoLockOrder";
 adosp->Parameters->Refresh();
 adosp->Parameters->ParamByName("@BS_StorageNoteHeaderID")->Value=dsetNtHeader->FieldByName("id")->AsInteger;
 adosp->ExecProc();
	MessageBox(0,"重新锁定订单库存成功！","入库" ,MB_ICONEXCLAMATION);
}catch(...)
{
	MessageBox(0,"重新锁定订单库单失败，请重试！","入库" ,MB_ICONEXCLAMATION);

}    */

try
{
 adosp->ProcedureName="C_createCNetRuKuDan";
 adosp->Parameters->Refresh();
 adosp->Parameters->ParamByName("@BS_StorageNoteHeaderID")->Value=dsetNtHeader->FieldByName("id")->AsInteger;
 adosp->ExecProc();
	MessageBox(0,"同步C网入库单成功！","入库" ,MB_ICONEXCLAMATION);
}catch(...)
{
  	MessageBox(0,"同步C网入库单失败，请重试！","入库" ,MB_ICONEXCLAMATION);

}

}
int TfrmStorageMng::GetKuWeizuijing(int bkcatalogid,int supplierid,int stgid,int &ckuwei)
{
	  int kuwei;
     	 try
	 {

	 adosp->ProcedureName="C_GetKuwei";
	 adosp->Parameters->Refresh();
	 adosp->Parameters->ParamByName("@stgid")->Value=stgid;
	 adosp->Parameters->ParamByName("@bkcatalogid")->Value=bkcatalogid;
	 adosp->Parameters->ParamByName("@supplierid")->Value=supplierid;
	 adosp->Parameters->ParamByName("@kuwei")->Value=-1;
	  adosp->Parameters->ParamByName("@ckuwei")->Value=-1;
	 adosp->ExecProc();
	 kuwei= adosp->Parameters->ParamByName("@kuwei")->Value;
	 ckuwei= adosp->Parameters->ParamByName("@ckuwei")->Value;
	 return kuwei;
	 //刷新明细
	 }
	 catch (Exception &E) {
												//+AnsiString(E.Message)
		   //	MessageBox(Handle,"同步订单回告失败!详细信息","同步提示",MB_ICONWARNING);
		}




}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng::cbckuweiSelect(TObject *Sender)
{
//
UpdateWsaleDiscout(9);
}
void TfrmStorageMng::GetTotalNum(int headid)
{

try
{
	 adogetTotalNum->ProcedureName="C_GetTotalNum";
	 adogetTotalNum->Parameters->Refresh();
	 adogetTotalNum->Parameters->ParamByName("@headid")->Value=headid;
	 adogetTotalNum->Parameters->ParamByName("@totalnum")->Value=-1;
	 adogetTotalNum->Parameters->ParamByName("@fixprice")->Value=-1;
	 adogetTotalNum->Parameters->ParamByName("@discountprice")->Value=-1;
	 adogetTotalNum->ExecProc();

	 totalnum->Text = adogetTotalNum->Parameters->ParamByName("@totalnum")->Value;
	 editshiyang->Text= adogetTotalNum->Parameters->ParamByName("@discountprice")->Value;
	 edittotalmayang->Text = adogetTotalNum->Parameters->ParamByName("@fixprice")->Value;
  }catch(...)
  {}


}
//---------------------------------------------------------------------------

