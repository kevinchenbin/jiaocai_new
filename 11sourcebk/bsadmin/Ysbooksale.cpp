//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Ysbooksale.h"
#include "UnitSelectClient.h"
#include "SelectCatalogForm.h"
#include "SetNotesForm.h"
#include "UnitClient.h"
#include "QryNoteCodeForm.h"
#include "QueryDanHao.h"
#include "..\..\supplier\detailemessage.h"
#include "bookQuery.h"
#include "UnitClient.h"
#include "UnitSelectClient.h"
#include "Unitorderquery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzLabel"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzDBGrid"
#pragma link "RpBase"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpSystem"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma resource "*.dfm"
TfrmYsbooksale *frmYsbooksale;
//---------------------------------------------------------------------------
__fastcall TfrmYsbooksale::TfrmYsbooksale(TComponent* Owner)
	: TForm(Owner)
{
  ClientID = -1;
  m_catalogSearchMode = 1;
  dtpdate->Date = Date();
  headerid = -1;
}
void TfrmYsbooksale::init(LandInfo* li)
{
	UserID = li->userID ;
	UserName =  li->UserName ;
	StgID = li->storageID ;
	fcon = li->con ;
	spcopy->Connection = li->con;
	spsave->Connection = fcon;
	aqhd->Connection = fcon;
	aqhd->Active = false;
	aqhd->Active = true;
	AnsiString sql;
	sql = "select * from sys_bsset where name = 'changeDanHaoDisplay'";
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->FieldByName("Value")->AsBoolean ) {
		dbeditdanhao->Visible = false;
		dbeCodeStr->Visible = true;
	}
	else
	{
		dbeditdanhao->Visible = true;
		dbeCodeStr->Visible = false;
	}
	ChangeDisplay = aq->FieldByName("Value")->AsBoolean;
	//SAddHead->Connection = fcon;
	ReadyDate();
	RefreshHead();
	BtnNew->Click();
}
void TfrmYsbooksale::init(LandInfo*li,AnsiString Danhao)
{
   	UserID = li->userID ;
	UserName =  li->UserName ;
	StgID = li->storageID ;
	fcon = li->con ;
	spcopy->Connection = li->con;
	//SAddHead->Connection = fcon;
	ReadyDate();
	RefreshHead();
	if (Danhao == "") {
		return;
	}
	TLocateOptions Opts;
	Opts.Clear();
	Opts << loPartialKey;

	if(aqupdatehead->Locate("WsaleNtCode", Variant(Danhao), Opts))
	{
		RefreshDetail();
	}
}
void TfrmYsbooksale::ReadyDate()
{
	AnsiString sql = "select * from SYS_StaffInfo ";// where ID = " + IntToStr((int)(ccbclient->Items->Objects[ccbclient->ItemIndex])) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbvendor->Items->Clear();
	while(!aq->Eof)
	{
	   cbvendor->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger);
	   aq->Next();
	}
	sql = "select ID,Name from SYS_StorageInfo where id = " + IntToStr(StgID);
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edstorageid->Text = aq->FieldByName("ID")->AsString ;
	edstoragename->Text = aq->FieldByName("Name")->AsAnsiString ;

}
void TfrmYsbooksale::AddNewHead()
{
	int ret;
	adospaddhead->Connection = fcon;
	adospaddhead->Parameters->ParamByName("@CustomerID")->Value  = 1;
	adospaddhead->Parameters->ParamByName("@type")->Value  = 0;
	adospaddhead->Parameters->ParamByName("@Bsmode")->Value  = 7;
	adospaddhead->Parameters->ParamByName("@OperatorID")->Value  = UserID ;
	adospaddhead->Parameters->ParamByName("@StgID")->Value  = StgID ;
	adospaddhead->ExecProc();
	ret =   adospaddhead->Parameters->ParamByName("@RETURN_VALUE")->Value;
	headerid = ret;
	if (ret < 0 ) {
		MessageBox(0,"添加赠书单错误！","提示",MB_ICONASTERISK);
	}else
	{
	   /*aqorderdetail->Active = false;
	   aqorderdetail->Parameters->ParamByName("ID")->Value = headerid ;
	   aqorderdetail->Connection = fcon;
	   aqorderdetail->Active = true;     */
	   //cbclient->Enabled = true;
	   edtclient->Enabled = true;
	   edclient->Enabled = true;
	   spselectClient->Enabled = true;
	   SpeedButton2->Enabled = true;
	}
   // adospaddhead->Last();
}
AnsiString TfrmYsbooksale::GetField(AnsiString sql,AnsiString Field)
{
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	return	aq->FieldByName(Field)->AsAnsiString ;
}
void TfrmYsbooksale::ExecSQL(AnsiString sql)
{
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
}
BOOL TfrmYsbooksale::UpdateHead()
{
	if (!aqupdatehead->Active) {
		  return false;
	}
	aqupdatehead->Edit();
	aqupdatehead->FieldByName("hdtime")->AsDateTime = dtpdate->Date ;
	aqupdatehead->FieldByName("Remarks")->AsAnsiString = membk->Text ;
	/*if (cbvendor->ItemIndex == -1) {
		aqupdatehead->FieldByName("staffid")->AsInteger = 0;
	} else
	{
	  	aqupdatehead->FieldByName("staffid")->AsInteger = (int)(cbvendor->Items->Objects[cbvendor->ItemIndex]);
	} */
	if (ClientID != -1 )
	{
	   	aqupdatehead->FieldByName("VendorID")->AsInteger = ClientID;
	}

	aqupdatehead->UpdateBatch(arCurrent);
	if (aqupdatehead->FieldByName("WsaleNtCode")->AsInteger == 0 ) {
		spsave->Parameters->ParamByName("@MODE")->Value = 1;
		spsave->Parameters->ParamByName("@ID")->Value = aqupdatehead->FieldByName("ID")->AsInteger ;
		spsave->Parameters->ParamByName("@STGID")->Value = StgID;
		spsave->Parameters->ParamByName("@TYPE")->Value = 2;
		spsave->Parameters->ParamByName("@CODEMODE")->Value = 0;
		spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
		spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
		spsave->Parameters->ParamByName("@codestyle")->Value = 2;
		spsave->ExecProc() ;
	}

	RefreshHead(aqupdatehead->FieldByName("id")->AsInteger );
	return true;
	 //dbeditdanhao->Text = spsave->Parameters->ParamByName("@ReturnCode")->Value ;
	//dbeCodeStr->Text = spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
}
//---------------------------------------------------------------------------



void __fastcall TfrmYsbooksale::BtnNewClick(TObject *Sender)
{
	edclientview();
	ClientID = 1;
	if ((aqupdatehead->FieldByName("WsaleNtCode")->AsInteger != 0 && aqorderdetail->RecordCount > 0) || aqupdatehead->IsEmpty()) {
		AddNewHead();
		RefreshHead(headerid);
	}
	//dbn->BtnClick(3);   //最后一个
	edtCatalog->Text = "";
	editamount->Text = "0";
	edclient->SetFocus();

}
void TfrmYsbooksale::RefreshHead()
{
	int vendor;
	AnsiString sql;
	sql = "select A.*,S.ID as sid,C.Name as Clientname,S.Name as StgName,U.ID,U.name as OpName from BS_WsaleNoteHeader A "
		"left join SYS_StorageInfo S ON A.stgID = S.ID "
		"left join SYS_User U ON A.operatorID = U.ID "
		"left join CUST_customerinfo C ON C.ID = A.vendorID "
		"where A.state = 2";
	aqupdatehead->Connection = fcon;
	aqupdatehead->Close();
	aqupdatehead->SQL->Clear();
	aqupdatehead->SQL->Add(sql);
	aqupdatehead->Open();
	ClientID = aqupdatehead->FieldByName("vendorID")->AsInteger;
	ClientView();
	dtpdate->Date = aqupdatehead->FieldByName("hdtime")->AsDateTime ;
	vendor = aqupdatehead->FieldByName("staffid")->AsInteger;
	membk->Text = aqupdatehead->FieldByName("Remarks")->AsString ;
	edopname->Text = aqupdatehead->FieldByName("OpName")->AsString ;
	for (int i =0; i < cbvendor->Items->Count ; i++) {
	  if ((int)(cbvendor->Items->Objects[i])== vendor) {
		  cbvendor->ItemIndex = i;
		  break;
	  }
	}         //更新明细
	RefreshDetail();
}
//---------------------------------------------------------------------------
void TfrmYsbooksale::RefreshHead(int headid)
{
	int vendor;
	AnsiString sql;
	sql = "select A.*,S.ID as sid,C.Name as Clientname,S.Name as StgName,U.ID,U.name as OpName from BS_WsaleNoteHeader A "
		"left join SYS_StorageInfo S ON A.stgID = S.ID "
		"left join SYS_User U ON A.operatorID = U.ID "
		"left join CUST_customerinfo C ON C.ID = A.vendorID "
		"where A.id = " + IntToStr(headid) ;
	aqupdatehead->Connection = fcon;
	aqupdatehead->Close();
	aqupdatehead->SQL->Clear();
	aqupdatehead->SQL->Add(sql);
	aqupdatehead->Open();
	ClientID = aqupdatehead->FieldByName("vendorID")->AsInteger;
	ClientView();
	dtpdate->Date = aqupdatehead->FieldByName("hdtime")->AsDateTime ;
	vendor = aqupdatehead->FieldByName("staffid")->AsInteger;
	membk->Text = aqupdatehead->FieldByName("Remarks")->AsString ;
	edopname->Text = aqupdatehead->FieldByName("OpName")->AsString ;
	for (int i =0; i < cbvendor->Items->Count ; i++) {
	  if ((int)(cbvendor->Items->Objects[i])== vendor) {
		  cbvendor->ItemIndex = i;
		  break;
	  }
	}         //更新明细
	RefreshDetail();
}
//---------------------------------------------------------------------------


void __fastcall TfrmYsbooksale::BtnOKClick(TObject *Sender)
{
	if (!edclient->Enabled) {
		return;
	}
	try
	{
		HeaderRec = aqupdatehead->RecNo;
		if (!UpdateHead())
		{
			return ;
		}
		aqhd->Active = false;
		aqhd->Active = true;
	}
	catch(...)
	{
	   MessageBoxA(0,"保存失败，请重试!","警告",MB_ICONEXCLAMATION);
       return;
	}
	//MessageBoxA(0,"保存成功!","提示",MB_ICONWARNING);

	edclient->Enabled = false;
	edtclient->Enabled = false;
	spselectClient->Enabled = false;
	SpeedButton2->Enabled = false;
	dbeditaddcost->Enabled = false;
	dtpdate->Enabled = false;
	membk->Enabled = false;

	edtCatalog->Enabled = true;
	edqikan->Enabled = true;
	editamount->Enabled = true;
	edtCatalog->SetFocus();
	//RefreshHead();
	//aqupdatehead->First();
	//if (HeaderRec!=0) {
	//	aqupdatehead->MoveBy(HeaderRec-1);
	//}
   //RefreshDetail();
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::dbnClick(TObject *Sender, TNavigateBtn Button)
{
	edclientview();
	DelInvalidNtHeader();
	int  vendor;
	ClientID = aqupdatehead->FieldByName("vendorID")->AsInteger;
	ClientView();
	dtpdate->Date = aqupdatehead->FieldByName("hdtime")->AsDateTime ;
	vendor = aqupdatehead->FieldByName("staffid")->AsInteger;
	for (int i =0; i < cbvendor->Items->Count ; i++) {
	  if ((int)(cbvendor->Items->Objects[i])== vendor) {
		  cbvendor->ItemIndex = i;
		  break;
	  }
	}
	RefreshHead(aqhd->FieldByName("id")->AsInteger );
   //RefreshDetail();
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::N1Click(TObject *Sender)
{
		lblCatalog->Caption = "书 号";
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

void __fastcall TfrmYsbooksale::N2Click(TObject *Sender)
{
   lblCatalog->Caption = "自编码";
	m_catalogSearchMode=2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::N3Click(TObject *Sender)
{
	  lblCatalog->Caption = "书名";
	  m_catalogSearchMode=3;
	  edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode=6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}

	if (Key == '\r')
	{
			if (edtCatalog->Text == "") {
				ChangeCatalogSearchMode();
			}
			else
			{
				float price;
				if (m_catalogSearchMode == 6) {
				try {
						price = StrToFloat(edtCatalog->Text.Trim());
					} catch (...) {
						MessageBox(0,"请输入正确的定价！","入库" ,MB_ICONEXCLAMATION);
						return;
					}
				}
				if (chqikan->Checked && m_catalogSearchMode != 1) {
					edqikan->SetFocus();
					return;
				}
				if (m_catalogSearchMode == 1 && chqikan->Checked) {
					if (edtCatalog->Text.Length() == 13 ) {
						edqikan->SetFocus();
						return;
					}
					if (edtCatalog->Text.Length() == 15 ) {
						edqikan->Text = edtCatalog->Text.SubString(14,2);
						edtCatalog->Text = edtCatalog->Text.SubString(0,13);
					}
				}

				TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,fcon);
					LandInfo li;
					li.app = Application;
					li.con = fcon;
					li.userID = UserID ;
					li.storageID = StgID ;
					frm->Init(&li);
					frm->DoModalType = 12;
					frm->Ysbooksale = this;
					frm->qikan = chqikan->Checked ;
					frm->qikanhao = edqikan->Text ;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					if (mrOk == frm->ShowModal())
					{
						int bookinfoid = -1;
						if (frm->SelectAll) {
							 for (int i = 0; i < frm->lengthint  ; i++) {
								AddNote(frm->stkbkid[i]);
							 }

						}else
						{
							bookinfoid = frm->BKinfoid;
							if (bookinfoid >= 0)
							{
								AddNote(bookinfoid);
								edtCatalog->Text = "";
								editamount->SetFocus();
							}
						}
					}
					delete frm;
			}
	}
}



void TfrmYsbooksale::ChangeCatalogSearchMode()
{
if (m_catalogSearchMode==3) {
		m_catalogSearchMode=5;
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


void TfrmYsbooksale::AddNote(int bkinfoid)
{
   if (!aqupdatehead->Active) {
	   return;
   }
   TLocateOptions   Opts;
   Opts.Clear();
   Opts   <<   loPartialKey;
   String   str   = AnsiString(bkinfoid);
   if ( !aqorderdetail->Locate("BkInfoID",str,Opts))
   {
		AnsiString sql;
		sql = "insert into BS_WsaleNote(Discount,WsaleNtHeaderID,BkInfoID) values (0," + aqupdatehead->FieldByName("ID")->AsString + "," + IntToStr(bkinfoid) + ")";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		RefreshDetail();
   }
   else
   {
		dgdetail->SelectedRows->CurrentRowSelected = true;
		dgdetail->SetFocus();
		editamount->SetFocus();
   }
}
void TfrmYsbooksale::RefreshDetail()
{
    aqorderdetail->Active = false;
	aqorderdetail->Parameters->ParamByName("ID")->Value = aqupdatehead->FieldByName("ID")->AsInteger ;
	aqorderdetail->Connection = fcon;
	aqorderdetail->Active = true;
	if (aqorderdetail->RecordCount > 0) {
		edtCatalog->Enabled = true;
		edqikan->Enabled = true;
		editamount->Enabled = true;

		edclient->Enabled = false;
		edtclient->Enabled = false;
		spselectClient->Enabled = false;
		SpeedButton2->Enabled = false;
		dbeditaddcost->Enabled = false;
		dtpdate->Enabled = false;
		membk->Enabled = false;

		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "￥0.00";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
	}
	else
	{
		edtCatalog->Enabled = false;
		edqikan->Enabled = false;
		editamount->Enabled = false;

		edclient->Enabled = true;
		edtclient->Enabled = true;
		spselectClient->Enabled = true;
		SpeedButton2->Enabled = true;
		dbeditaddcost->Enabled = true;
		dtpdate->Enabled = true;
		membk->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::editamountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
	 if (!aqupdatehead->Active) {
	   return;
	   }
	   aqorderdetail->Edit() ;
	   aqorderdetail->FieldByName("amount")->AsInteger = StrToInt(editamount->Text.Trim()) ;
       aqorderdetail->UpdateBatch(arCurrent);
	   RefreshDetail();
	   RefreshHead(aqupdatehead->FieldByName("id")->AsInteger );
	   aqorderdetail->Last();
	   edtCatalog->SetFocus();
	   editamount->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::BtnDeleteClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	if (MessageBoxA(0,"确认要删除吗？","提示",MB_ICONQUESTION)==1)
	{
		AnsiString sql;
		if (dgdetail->SelectedRows->Count > 0) {
        	for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
				aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
				sql = "delete from BS_WsaleNote where id = " + aqorderdetail->FieldByName("id")->AsString ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
			}
		}
		else
		{
			sql = "delete from BS_WsaleNote where id = " + aqorderdetail->FieldByName("id")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
		aqorderdetail->Active = false;
		aqorderdetail->Active = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::BtnChangeOptionsClick(TObject *Sender)
{
		if (aqorderdetail->IsEmpty() ) {
			return;
		}
		TfrmSetNotes* frm = new TfrmSetNotes(this);
		frm->salediscount = 2;
		frm->ChangeBsmode(1);
		if (frm->ShowModal() == mrOk)
		{
			int amount = 0;
			float discount = 0;
			bool bsetAmount = frm->GetAmount(amount);
			//bool bsetDiscount = frm->GetDiscount(discount);
			if (bsetAmount)
			{
				BatchSetNotes(amount);
			}
			//RefreshDetail();
			RefreshHead(aqupdatehead->FieldByName("id")->AsInteger);
		}
}
void TfrmYsbooksale::BatchSetNotes(int amount)
{
		 if (aqorderdetail->IsEmpty() ) {
			 return;
		 }
		for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
				aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
				aqorderdetail->Edit();
				aqorderdetail->FieldByName("amount")->AsInteger = amount;
				aqorderdetail->UpdateBatch(arCurrent);
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::SpeedButton2Click(TObject *Sender)
{

	   AnsiString sql;
	   TADOQuery * aq = new TADOQuery(NULL);
	   aq->Connection = fcon;
	   sql = "select * from cust_customerinfo";
	   aq->Close();
	   aq->SQL->Clear();
	   aq->SQL->Add(sql);
	   aq->Open();
	   int count1 = aq->RecordCount ;
	   /*TDetaileForm * frm = new TDetaileForm(Application,2,1,0 ,fcon);
		frm->ParentID = -1;
		frm->ShowModal();
	   delete frm; */

	   Tfrmclient * frm = new Tfrmclient(Application,fcon,StgID);

	   frm->FormStyle = fsNormal ;
	   frm->Visible = false;
	   frm->WindowState = wsNormal ;
	   frm->Position = poMainFormCenter ;
		frm->ShowModal();
	   delete frm;
	   sql = "select * from cust_customerinfo";
	   aq->Close();
	   aq->SQL->Clear();
	   aq->SQL->Add(sql);
	   aq->Open();
	   int count2 = aq->RecordCount ;
	   if (count2 > count1) {
			sql = "select top 1 ID,Name from cust_customerinfo order by ID desc ";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			ClientID =	aq->FieldByName("ID")->AsInteger  ;
			ClientView();
	   }
		delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::BtnViewClick(TObject *Sender)
{
		Tfrmorderquery* frm = new Tfrmorderquery(Application,fcon,StgID,2,2,false);
		if (frm->ShowModal() == mrOk)
		{
			edclientview();

			DelInvalidNtHeader();
			dbn->Enabled = true;
			edtCatalog->Text = "";
			edclient->Text = "";
			AnsiString code = frm->GetNoteCode();
			AnsiString sqlwhere = frm->GetWhere();
			try
			{
				//QryNtHeader(code);
				String sql;
				if (sqlwhere != "") {
					sql = "select * from BS_WsaleNoteHeader " + sqlwhere;
					aqhd->Close();
					aqhd->SQL->Clear();
					aqhd->SQL->Add(sql);
					aqhd->Open();
				}

				TLocateOptions Opts;
				Opts.Clear();
				Opts << loPartialKey;
				aqhd->Locate("WsaleNtCode", code , Opts);
				RefreshHead(aqhd->FieldByName("id")->AsInteger );
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			delete frm;
		}
}
//---------------------------------------------------------------------------




void __fastcall TfrmYsbooksale::FormClose(TObject *Sender, TCloseAction &Action)
{
    DelInvalidNtHeader();
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::BtnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmYsbooksale::BtnExportClick(TObject *Sender)
{
	//Excel导出
	if (aqorderdetail->Active && aqorderdetail->RecordCount >= 1)
	{
		DbgridToExcel(dgdetail,"样/赠书处理");
	}
}
//---------------------------------------------------------------------------

//Excel导出函数
bool __fastcall TfrmYsbooksale::DbgridToExcel(TDBGrid* dbg,AnsiString Title)
{
	AnsiString temptext ;
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
	temptext = "'"+ Title;
	v.OlePropertyGet("Cells",1,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","客户" );
	temptext = "'"+ edtclient->Text;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","单号" );
	temptext = "'"+ dbeditdanhao->Text;
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",3,7).OlePropertySet("Value","日期");
	temptext = "'"+ DateToStr(dtpdate->Date);
	v.OlePropertyGet("Cells",3,8).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,1).OlePropertySet("Value","业务员" );
	temptext = "'"+ cbvendor->Text;
	v.OlePropertyGet("Cells",4,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,4).OlePropertySet("Value","附加费用" );
	temptext = "'"+ dbeditaddcost->Text;
	v.OlePropertyGet("Cells",4,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",5,1).OlePropertySet("Value","备注" );
	temptext = "'"+ membk->Text ;
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
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
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
	temptext = RzDBNumericEdit1->Text ;
	v.OlePropertyGet("Cells",t2+2+n,8).OlePropertySet("Value",temptext .c_str() );
	//v.OlePropertyGet("Cells",t2+2+n,4).OlePropertySet("Value","总码洋");
	temptext = RzDBNumericEdit2->Text ;
	v.OlePropertyGet("Cells",t2+2+n,10).OlePropertySet("Value",temptext .c_str() );
	//v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value","总实洋");
	temptext = RzDBNumericEdit3->Text ;
	v.OlePropertyGet("Cells",t2+2+n,11).OlePropertySet("Value",temptext .c_str() );

	return false;
}
//---------------------------------------------------------------------------}



void __fastcall TfrmYsbooksale::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edclient->Text,StgID);
	   if (mrOk == frm->ShowModal())
	   {
			ClientID = frm->GetSelectID();
			ClientView();
			edtclient->SetFocus();
	   }
	   delete frm;
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void TfrmYsbooksale::edclientview()
{
      
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::dgdetailCellClick(TColumn *Column)
{
	if (aqorderdetail->IsEmpty() ) {
	 return;
   }
   //edtCatalog->Text = aqorderdetail->FieldByName("ISBN")->AsAnsiString ;
   editamount->Text = aqorderdetail->FieldByName("amount")->AsAnsiString ;
}
//---------------------------------------------------------------------------
void TfrmYsbooksale::DelInvalidNtHeader()
{
	if (!aqupdatehead->IsEmpty() ) {
    	if (aqupdatehead->FieldByName("WsaleNtCode")->AsInteger == 0) {
			AnsiString sql;
			sql = "delete from BS_WsaleNoteHeader where id = " + aqupdatehead->FieldByName("id")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmYsbooksale::N5Click(TObject *Sender)
{
	for (int i = 1; i <= aqorderdetail->RecordCount; i++) {
		dgdetail->DataSource->DataSet->RecNo = i;
		dgdetail->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void  TfrmYsbooksale::Printorview(int type)
{
		if (aqorderdetail->IsEmpty() ) {
        	return;
		}
		RvSystem1->SystemSetups >>ssAllowSetup;
		RvSystem1->SystemSetups >>ssAllowDestPreview;
		RvSystem1->SystemSetups >>ssAllowDestPrinter;
		RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		RvSystem1->SystemSetups >>ssAllowDestFile;
		if (type == 1) {
			RvSystem1->DefaultDest  = rdPreview ;
		}
		else
		{
			RvSystem1->DefaultDest  = rdPrinter ;
		}
		RvSystem1->SystemSetups<<ssAllowDestPreview;
		RvProject1->ProjectFile = ExtractFilePath(Application->ExeName) + "ysbooksale.rav";
		if (ChangeDisplay) {
			RvProject1->SetParam("code",dbeCodeStr->Text);
		}
		else
		{
        	RvProject1->SetParam("code",dbeditdanhao->Text);
		}
		RvProject1->SetParam("date",DateToStr(dtpdate->Date));
		RvProject1->SetParam("clientname", edtclient->Text);
		RvProject1->SetParam("totalamount",RzDBNumericEdit1->Text);
		RvProject1->SetParam("totalfixedprice",RzDBNumericEdit2->Text);
		RvProject1->SetParam("bk",membk->Text);
		RvProject1->SetParam("user",UserName);
		RvProject1->SetParam("nowdate",DateToStr(Date()));
		RvProject1->Open();
		RvProject1->Execute();
		RvProject1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::BtnClearClick(TObject *Sender)
{
	Printorview(1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::BtnPrintClick(TObject *Sender)
{
	Printorview(2);
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {   //查单
		BtnView->Click();
	}
	if (Key == VK_F2) {   //添单
		BtnNew->Click();
	}
	if (Key == VK_F3) {   //保存
		BtnOK->Click();
	}
	if (Key == VK_F4) {   //修改单头
		BtnChange->Click();
	}
	if (Key == VK_F5) {   //删行
		BtnDelete->Click();
	}
	if (Key == VK_F6) {   //统一
		BtnChangeOptions->Click();
	}
	if (Key == VK_F8) {   //导出
		BtnExport->Click();
	}
	if (Key == VK_F10) {   //打印
		BtnPrint->Click();
	}
	if (Key == VK_F11) {   //预览
		BtnClear->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {   //查书
	   BtnView1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::BtnView1Click(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,fcon,StgID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",StgID);
	   if (mrOk == frm->ShowModal())
	   {
			ClientID = frm->GetSelectID();
			ClientView();
			dbeditaddcost->SetFocus();
	   }
	   delete frm;

}
//---------------------------------------------------------------------------
void TfrmYsbooksale::ClientView()
{
		if (ClientID == -1) {
			return;
		}
	   String sql;
	   TADOQuery * aq = new TADOQuery(NULL);
	   aq->Connection = fcon;
	   sql = "exec USP_BS_Client_View 0," + IntToStr(ClientID)  ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		edtclient->Text = aq->FieldByName("Name")->AsAnsiString ;
		delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::edtclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        dbeditaddcost->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::dbeditaddcostKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		membk->SetFocus();
	}
}
//---------------------------------------------------------------------------


 void __fastcall TfrmYsbooksale::N6Click(TObject *Sender)
{
	if (dbeCodeStr->Text == "") {
		MessageBoxA(0,"本单还未保存，请先保存！","提示",MB_ICONASTERISK);
		return;
	}
	spcopy->ProcedureName = "StickData";
	spcopy->Parameters->Clear();
	spcopy->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),5);
	spcopy->Parameters->CreateParameter("@HeadId",ftInteger,pdInput,sizeof(int),aqupdatehead->FieldByName("id")->AsInteger);
	spcopy->Parameters->CreateParameter("@userid",ftInteger,pdInput,sizeof(int),UserID );
	spcopy->ExecProc();
	RefreshHead(aqupdatehead->FieldByName("id")->AsInteger );
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::BtnChangeClick(TObject *Sender)
{
	//GroupBox1->Enabled = true;

	edclient->Enabled = true;
	edtclient->Enabled = true;
	spselectClient->Enabled = true;
	SpeedButton2->Enabled = true;
	dbeditaddcost->Enabled = true;
	dtpdate->Enabled = true;
	membk->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::dgdetailTitleClick(TColumn *Column)
{
	if (aqorderdetail->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqorderdetail->Sort == "") {
		aqorderdetail->Sort =  Column->FieldName + " ASC";
	}
	else if (aqorderdetail->Sort == qusort) {
		aqorderdetail->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqorderdetail->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::membkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        BtnOK->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::chqikanClick(TObject *Sender)
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

void __fastcall TfrmYsbooksale::N8Click(TObject *Sender)
{
	lblCatalog->Caption = "作者";
	m_catalogSearchMode=5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmYsbooksale::edqikanKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        if (edtCatalog->Text == "") {
				ChangeCatalogSearchMode();
			}
			else
			{
				float price;
				if (m_catalogSearchMode == 6) {
				try {
						price = StrToFloat(edtCatalog->Text.Trim());
					} catch (...) {
						MessageBox(0,"请输入正确的定价！","入库" ,MB_ICONEXCLAMATION);
						return;
					}
				}

				TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,fcon);
					LandInfo li;
					li.app = Application;
					li.con = fcon;
					li.userID = UserID ;
					li.storageID = StgID ;
					frm->Init(&li);
					frm->DoModalType = 12;
					frm->Ysbooksale = this;
					frm->qikan = chqikan->Checked ;
					frm->qikanhao = edqikan->Text ;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					if (mrOk == frm->ShowModal())
					{
						int bookinfoid = -1;
						if (frm->SelectAll) {
							 for (int i = 0; i < frm->lengthint  ; i++) {
								AddNote(frm->stkbkid[i]);
							 }

						}else
						{
							bookinfoid = frm->BKinfoid;
							if (bookinfoid >= 0)
							{
								AddNote(bookinfoid);
								edtCatalog->Text = "";
								edqikan->Text = "";
								editamount->SetFocus();
							}
						}
					}
					delete frm;
			}
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmYsbooksale::dgdetailKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
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
}
//---------------------------------------------------------------------------

