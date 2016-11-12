//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitBIOrderbk.h"
#include "UnitSelectClient.h"
#include "SelectCatalogForm.h"
#include "SetNotesForm.h"
#include "UnitClient.h"
#include "QryNoteCodeForm.h"
#include "..\..\supplier\detailemessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzLabel"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TfrmBIorderbk *frmBIorderbk;
//---------------------------------------------------------------------------
__fastcall TfrmBIorderbk::TfrmBIorderbk(TComponent* Owner)
	: TForm(Owner)
{
  ClientID = -1;
  m_catalogSearchMode = 1;
  dtpdate->Date = Date();
  dtpfahuo->Date = Date();
}
void TfrmBIorderbk::init(LandInfo* li)
{
	UserID = li->userID ;
	UserName =  li->UserName ;
	StgID = li->storageID ;
	fcon = li->con ;
	if (StgID == 0) {
		cbtype->ItemIndex = 0;
		cbtype->Enabled = false;
	}
	//SAddHead->Connection = fcon;
	ReadyDate();
	RefreshHead();


}
void TfrmBIorderbk::init(LandInfo*li,AnsiString Danhao)
{
   	UserID = li->userID ;
	UserName =  li->UserName ;
	StgID = li->storageID ;
	fcon = li->con ;
	if (StgID == 0) {
		cbtype->ItemIndex = 0;
		cbtype->Enabled = false;
	}
	//SAddHead->Connection = fcon;
	ReadyDate();
	RefreshHead();
	if (Danhao == "") {
		return;
	}
	TLocateOptions Opts;
	Opts.Clear();
	Opts << loPartialKey;

	if(aqupdatehead->Locate("OrderNtCode", Variant(Danhao), Opts))
	{
		RefreshDetail();
	}
}
void TfrmBIorderbk::ReadyDate()
{
	AnsiString sql = "select * from SYS_StaffInfo ";// where ID = " + IntToStr((int)(ccbclient->Items->Objects[ccbclient->ItemIndex])) ;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = fcon;
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
	sql = "select ID,Name from CUST_CustomerInfo where type in(2,3) order by name";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbclient->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
    ClientID = 1;

	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)1);

}
void TfrmBIorderbk::AddNewHead()
{
	int ret;
	adospaddhead->Connection = fcon;
	adospaddhead->Parameters->ParamByName("@CustomerID")->Value  = 1;
	adospaddhead->Parameters->ParamByName("@type")->Value  = 0;
	adospaddhead->Parameters->ParamByName("@Bsmode")->Value  = 4;
	adospaddhead->Parameters->ParamByName("@OperatorID")->Value  = UserID ;
	adospaddhead->Parameters->ParamByName("@StgID")->Value  = StgID ;
	adospaddhead->ExecProc();
	ret =   adospaddhead->Parameters->ParamByName("@RETURN_VALUE")->Value;
	if (ret < 0 ) {
		MessageBox(0,"��Ӷ�������","��ʾ",MB_ICONASTERISK);
	}else
	{
	   aqorderdetail->Active = false;
	   aqorderdetail->Parameters->ParamByName("ID")->Value = aqupdatehead->FieldByName("ID")->AsInteger ;
	   aqorderdetail->Connection = fcon;
	   aqorderdetail->Active = true;
	   cbclient->Enabled = true;
	   SpeedButton2->Enabled = true;
	}
   // adospaddhead->Last();
}
AnsiString TfrmBIorderbk::GetField(AnsiString sql,AnsiString Field)
{
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	return	aq->FieldByName(Field)->AsAnsiString ;
	delete aq;
}
void TfrmBIorderbk::ExecSQL(AnsiString sql)
{  	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}
BOOL TfrmBIorderbk::UpdateHead()
{
	if (!aqupdatehead->Active) {
		  return false;
	}
	if (cbclient->Text == "" ) {
		MessageBoxA(0,"��ѡ��ͻ�","��ʾ",MB_ICONEXCLAMATION);
		return false;
	}
	aqupdatehead->Edit();
	aqupdatehead->FieldByName("state")->AsInteger = cbstate->ItemIndex;
	aqupdatehead ->FieldByName("type")->AsInteger = 	cbtype->ItemIndex ;
	aqupdatehead->FieldByName("hdtime")->AsDateTime = dtpdate->Date ;
	aqupdatehead->FieldByName("arravaldate")->AsDateTime = dtpfahuo->Date ;
	if (cbvendor->ItemIndex == -1) {
	   aqupdatehead->FieldByName("staffid")->AsInteger = 0;
	} else
	{
	  aqupdatehead->FieldByName("staffid")->AsInteger = (int)(cbvendor->Items->Objects[cbvendor->ItemIndex]);
	}
	if (ClientID != -1 )
	{
	   aqupdatehead->FieldByName("vendorID")->AsInteger =  ClientID;
	}

	aqupdatehead->UpdateBatch(arCurrent);
}
//---------------------------------------------------------------------------



void __fastcall TfrmBIorderbk::BtnNewClick(TObject *Sender)
{
    edclientview();
	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)1);
	ClientID = 1;
	AddNewHead();
	RefreshHead();
	dbn->BtnClick(3);   //���һ��
	edtCatalog->Text = "";
	editamount->Text = "0";
    editdiscount->Text = "100";
}
void TfrmBIorderbk::RefreshHead()
{
	int vendor;

	aqupdatehead->Active = false;
	aqupdatehead->Connection = fcon;
	aqupdatehead->Active = true;
	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aqupdatehead->FieldByName("vendorID")->AsInteger );
	cbstate->ItemIndex = aqupdatehead->FieldByName("state")->AsInteger ;
	cbtype->ItemIndex = aqupdatehead ->FieldByName("type")->AsInteger ;
	dtpdate->Date = aqupdatehead->FieldByName("hdtime")->AsDateTime ;
	dtpfahuo->Date  = aqupdatehead->FieldByName("arravaldate")->AsDateTime ;
	vendor = aqupdatehead->FieldByName("staffid")->AsInteger;
	for (int i =0; i < cbvendor->Items->Count ; i++) {
	  if ((int)(cbvendor->Items->Objects[i])== vendor) {
		  cbvendor->ItemIndex = i;
		  break;
	  }
	}         //������ϸ
	RefreshDetail();

}
//---------------------------------------------------------------------------


void __fastcall TfrmBIorderbk::BtnOKClick(TObject *Sender)
{
	if (!GroupBox1->Enabled) {
		return;
	}
	try
	{
		HeaderRec = aqupdatehead->RecNo;
		if (!UpdateHead())
		{
			return ;
	   	}

	}
	catch(...)
	{
	   MessageBoxA(0,"����ʧ�ܣ�������!","����",MB_ICONEXCLAMATION);
       return;
	}
	MessageBoxA(0,"����ɹ�!","��ʾ",MB_ICONWARNING);
	GroupBox1->Enabled = false;
	GroupBox2->Enabled = true;
	//RefreshHead();
	//aqupdatehead->First();
	//if (HeaderRec!=0) {
	//	aqupdatehead->MoveBy(HeaderRec-1);
	//}
   //RefreshDetail();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::dbnClick(TObject *Sender, TNavigateBtn Button)
{
    edclientview();
	int  vendor;
	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aqupdatehead->FieldByName("vendorID")->AsInteger );
	cbstate->ItemIndex = aqupdatehead->FieldByName("state")->AsInteger ;
	cbtype->ItemIndex = aqupdatehead ->FieldByName("type")->AsInteger ;
	dtpdate->Date = aqupdatehead->FieldByName("hdtime")->AsDateTime ;
	dtpfahuo->Date  = aqupdatehead->FieldByName("arravaldate")->AsDateTime ;
	vendor = aqupdatehead->FieldByName("staffid")->AsInteger;
	for (int i =0; i < cbvendor->Items->Count ; i++) {
	  if ((int)(cbvendor->Items->Objects[i])== vendor) {
		  cbvendor->ItemIndex = i;
		  break;
	  }
	}
   RefreshDetail();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::N1Click(TObject *Sender)
{
		lblCatalog->Caption = "�� ��";
		m_catalogSearchMode=1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::N2Click(TObject *Sender)
{
   lblCatalog->Caption = "�Ա���";
m_catalogSearchMode=2;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::N3Click(TObject *Sender)
{
	  lblCatalog->Caption = "�� ��";
m_catalogSearchMode=3;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::N4Click(TObject *Sender)
{
lblCatalog->Caption = "�� ��";
m_catalogSearchMode=6;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
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
				TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,fcon);
					LandInfo li;
					li.app = Application;
					li.con = fcon;
					li.userID = UserID ;
					li.storageID = StgID ;
					frm->Init(&li);
					frm->DoModalType = 4;
					frm->order  = this;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					if (mrOk == frm->ShowModal())
					{
						int supplierID = -1,catalogID = -1;
						if (frm->SelectAll) {

							 for (int i = 0; i < frm->lengthint  ; i++) {
								 AddNote(supplierID,frm->BkcatalogiD[i]);

							 }

						}else
						{
							frm->GetSelectResult(supplierID, catalogID);

							if (catalogID >= 0)
							{
								AddNote(-1, catalogID);
								edtCatalog->Text  = "";
								Perform(WM_NEXTDLGCTL, 0, 0);
							}
						}
					}
					delete frm;
			}
	}
}



void TfrmBIorderbk::ChangeCatalogSearchMode()
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
		lblCatalog->Caption = "�� ��";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "�Ա���";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "��  ��";
		break;
	case 6:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "�� ��";
		break;
    default:
        break;
	}
}


void TfrmBIorderbk::AddNote(int SupplierID,int CatalogID)
{
   if (!aqupdatehead->Active) {
	   return;
   }
   aqorderdetail->Append();
   aqorderdetail->FieldByName("OrderNtHeaderID")->AsInteger = aqupdatehead->FieldByName("ID")->AsInteger ;
   aqorderdetail->FieldByName("bkcatalogid")->AsInteger = CatalogID;
   aqorderdetail->UpdateBatch(arCurrent);
   RefreshDetail();
   aqorderdetail->Last();

   AnsiString sql = " select sum(amount) as stockamount from STK_BookInfo where BkcatalogID ="+IntToStr(CatalogID)+" and amount > 0";
   if ( GetField(sql,"stockamount")=="")
   {
	  editstockamount->Text = "0";
   }else
   {

	 editstockamount->Text = GetField(sql,"stockamount");
   }


}
void TfrmBIorderbk::RefreshDetail()
{
    aqorderdetail->Active = false;
   aqorderdetail->Parameters->ParamByName("ID")->Value = aqupdatehead->FieldByName("ID")->AsInteger ;
   aqorderdetail->Connection = fcon;
   aqorderdetail->Active = true;
   if (aqorderdetail->RecordCount > 0) {
		GroupBox2->Enabled = true;
		GroupBox1->Enabled = false;
	}
	else
	{
		GroupBox2->Enabled = false;
		GroupBox1->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::editamountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
	 if (!aqupdatehead->Active) {
	   return;
   }
	   aqorderdetail->Edit() ;
	   aqorderdetail->FieldByName("amount")->AsInteger = StrToInt(editamount->Text.Trim()) ;
       aqorderdetail->UpdateBatch(arCurrent);
	   RefreshDetail();
		aqorderdetail->Last();
	   Perform(WM_NEXTDLGCTL, 0, 0);
	   editamount->Text = "0";

	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::editdiscountKeyPress(TObject *Sender, wchar_t &Key)
{
    if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
	if (Key == VK_RETURN) {
	 if (!aqupdatehead->Active) {
	   return;
   }
	   aqorderdetail->Edit() ;
	   try {
			aqorderdetail->FieldByName("Discount")->AsFloat =  StrToFloat(editdiscount->Text);
	   } catch (...) {
			MessageBoxA(0,"��������ȷ���ۿۣ�","��ʾ",MB_ICONERROR);
			return;
	   }
	   aqorderdetail->UpdateBatch(arCurrent);
	   RefreshDetail();
	   aqorderdetail->Last();
	   Perform(WM_NEXTDLGCTL, 0, 0);
	   editdiscount->Text = "100";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::editdetailbkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
	 if (!aqupdatehead->Active) {
	   return;
   }
	aqorderdetail->Edit() ;
	aqorderdetail->FieldByName("bk")->AsAnsiString  = editdetailbk->Text ;
	aqorderdetail->UpdateBatch(arCurrent);
	RefreshDetail();
	aqorderdetail->Last();
	edtCatalog->SetFocus();
	editdetailbk->Text = "";
	}	
}
//---------------------------------------------------------------------------


void __fastcall TfrmBIorderbk::BtnDeleteClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
	 return;
   }
  if (MessageBoxA(0,"ȷ��Ҫɾ����","��ʾ",MB_ICONQUESTION)==1)
  {
	//aqorderdetail->Edit();
	//aqorderdetail->Delete();
	AnsiString sql = "delete from BS_OrderNote where id = " + aqorderdetail->FieldByName("id")->AsString ;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	aqorderdetail->Active = false;
    aqorderdetail->Active = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::BtnChangeOptionsClick(TObject *Sender)
{
        	TfrmSetNotes* frm = new TfrmSetNotes(this);
			frm->ChangeBsmode(1);
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
                RefreshDetail();
			}
}
void TfrmBIorderbk::BatchSetNotes(int amount, float discount, int mode)
{
		 if (aqorderdetail->IsEmpty() ) {
			 return;
		   }

		switch(mode)
		{
		case 1://���߾�����

			 for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
				aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
				aqorderdetail->Edit();
				aqorderdetail->FieldByName("amount")->AsInteger = amount;
				aqorderdetail->FieldByName("Discount")->AsFloat  = discount;
                aqorderdetail->UpdateBatch(arCurrent);
			 }

			break;
		case 2://ֻ����Amount

			try
			{
				 for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
				aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
				aqorderdetail->Edit();
				aqorderdetail->FieldByName("amount")->AsInteger = amount;
				aqorderdetail->UpdateBatch(arCurrent);
			 }
			}
			__finally
			{
				LockWindowUpdate(NULL);
			}
			break;
		case 3://ֻ����Discount

			try
			{
               	 for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
				aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
				aqorderdetail->Edit();
				aqorderdetail->FieldByName("Discount")->AsFloat  = discount;
                aqorderdetail->UpdateBatch(arCurrent);
			 }
			}
			__finally
			{
				LockWindowUpdate(NULL);
			}
			break;
		default:
			break;
		}


}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::SpeedButton2Click(TObject *Sender)
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
	   TDetaileForm * frm = new TDetaileForm(Application,2,1,0 ,fcon);
		frm->ParentID = -1;
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
			cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)ClientID );
	   }
		delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::BtnViewClick(TObject *Sender)
{
		edclientview();
		TfrmQryNoteCode* frm = new TfrmQryNoteCode(this,0);
			LandInfo li;
			li.app = Application;
			li.con = fcon;
			li.userID = UserID ;
			li.storageID = StgID ;
			frm->Init(&li);
		if (frm->ShowModal()==mrOk ) {

		   AnsiString code = frm->GetNoteCode();

		 AnsiString str =  LeftBStr(code,2);
		   if (str == "00") {
			code = AnsiRightStr(code,code.Length()-2) ;

		}else
		   {
			  str = LeftBStr(code,1);
			  if (str == "0") {
						code = AnsiRightStr(code,code.Length()-1) ;
			  }

		   }

			TLocateOptions Opts;
			Opts.Clear();
			Opts << loPartialKey;
		   if(aqupdatehead->Locate("OrderNtCode", Variant(code), Opts))
		   {
			RefreshDetail();

		   }else
		   {

			 MessageBoxA(0,"��ѯ���Ϊ�գ�","��ʾ",MB_ICONWARNING);
		   }


		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::BtnUpOneLevelClick(TObject *Sender)
{
   if (!aqupdatehead->Active)
   {
      return;
   }
   AnsiString sql;    //���´���״̬
   sql = "update BS_OrderNoteHeader set state = 6 where ID = " + aqupdatehead->FieldByName("ID")->AsAnsiString ;
   ExecSQL(sql);
   	if (aqorderdetail->Active && aqorderdetail->RecordCount >= 1)
	{
		DbgridToExcel(dgdetail,"�ͻ��ظ浥");
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmBIorderbk::BtnClearClick(TObject *Sender)
{
  if (aqupdatehead->Active) {


		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,fcon);
		::ShowWindow(frm->Handle, SW_HIDE);
	  //	LandInfo li;
	  //	li.app = m_app;
	   //	li.con = m_con;
	   //	li.userID = m_userID;
	   //	li.storageID = m_storageID;
		frm->PrintType = 1;//����
		frm->InputPara(aqupdatehead->FieldByName("ID")->AsAnsiString );

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;



		frm->RvSystem1->DefaultDest  = rdPreview ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPreview;


			frm->previewprint(1,3);

		frm->Close();
		delete frm;
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::FormClose(TObject *Sender, TCloseAction &Action)
{
    Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::BtnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmBIorderbk::BtnExportClick(TObject *Sender)
{
	//Excel����
	if (aqorderdetail->Active && aqorderdetail->RecordCount >= 1)
	{
		DbgridToExcel(dgdetail,"һ�㶩��");
	}
}
//---------------------------------------------------------------------------

//Excel��������
bool __fastcall TfrmBIorderbk::DbgridToExcel(TDBGrid* dbg,AnsiString Title)
{
	AnsiString temptext ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		MessageBox(0,"û�����ݣ�","����ȷ��" ,MB_OK);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  ��Excel�г��ַ�����ʾ
	temptext = "'"+ Title;
	v.OlePropertyGet("Cells",1,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","�ͻ�" );
	temptext = "'"+ cbclient->Text;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","������" );
	temptext = "'"+ dbeditdanhao->Text;
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",3,7).OlePropertySet("Value","��������");
	temptext = "'"+ DateToStr(dtpdate->Date);
	v.OlePropertyGet("Cells",3,8).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,10).OlePropertySet("Value","����״̬");
	temptext = "'"+ cbstate->Text ;
	v.OlePropertyGet("Cells",3,11).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,1).OlePropertySet("Value","ҵ��Ա" );
	temptext = "'"+ cbvendor->Text;
	v.OlePropertyGet("Cells",4,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,4).OlePropertySet("Value","���ӷ���" );
	temptext = "'"+ dbeditaddcost->Text;
	v.OlePropertyGet("Cells",4,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,7).OlePropertySet("Value","Ԥ�Ʒ���ʱ��" );
	temptext = "'"+ DateToStr(dtpfahuo->Date);
	v.OlePropertyGet("Cells",4,8).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,10).OlePropertySet("Value","��������" );
	temptext = "'"+ cbtype->Text ;
	v.OlePropertyGet("Cells",4,11).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",5,1).OlePropertySet("Value","��ע" );
	temptext = "'"+ dbbk->Text ;
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

	v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","�ϼ�");
	//v.OlePropertyGet("Cells",t2+2+n,2).OlePropertySet("Value","������");
	temptext = RzDBNumericEdit1->Text ;
	v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value",temptext .c_str() );
	//v.OlePropertyGet("Cells",t2+2+n,4).OlePropertySet("Value","������");
	temptext = RzDBNumericEdit2->Text ;
	v.OlePropertyGet("Cells",t2+2+n,8).OlePropertySet("Value",temptext .c_str() );
	//v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value","��ʵ��");
	temptext = RzDBNumericEdit3->Text ;
	v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );

	return false;
}
//---------------------------------------------------------------------------}



void __fastcall TfrmBIorderbk::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type in (2,3) and Name like '%" + edclient->Text + "%'";
		TADOQuery *aq = new TADOQuery(NULL);
		aq->Connection = fcon;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbclient->Clear();
		while (!aq->Eof)
		{
            cbclient->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
        cbclient->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::cbclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		try {
			ClientID = (int)(cbclient->Items->Objects[cbclient->ItemIndex]);
		} catch (...) {
			MessageBoxA(0,"��ѡ����ȷ�Ŀͻ���","��ʾ",MB_ICONERROR);
			return;
		}
		dbeditaddcost->SetFocus();
	}
}
//---------------------------------------------------------------------------

void TfrmBIorderbk::edclientview()
{
        edclient->Text = "";
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type in (2,3) order by Name";
		TADOQuery *aq = new TADOQuery(NULL);
		aq->Connection = fcon;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbclient->Clear();
		while (!aq->Eof)
		{
            cbclient->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorderbk::dgdetailCellClick(TColumn *Column)
{
	if (aqorderdetail->IsEmpty() ) {
	 return;
   }
   //edtCatalog->Text = aqorderdetail->FieldByName("ISBN")->AsAnsiString ;
   editamount->Text = aqorderdetail->FieldByName("amount")->AsAnsiString ;
   editdiscount->Text = aqorderdetail->FieldByName("Discount")->AsAnsiString ;
   editdetailbk->Text = aqorderdetail->FieldByName("bk")->AsAnsiString ;
}
//---------------------------------------------------------------------------

