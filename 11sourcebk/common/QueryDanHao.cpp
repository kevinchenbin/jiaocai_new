//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "QueryDanHao.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
TfrmQuery *frmQuery;
//---------------------------------------------------------------------------
__fastcall TfrmQuery::TfrmQuery(TComponent* Owner)
	: TForm(Owner)
{
	dtfrom->Date = Date();
	dtto->Date = Date();
}
void TfrmQuery::Init(LandInfo* li)
{
   	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;

	AnsiString sql;
	sql = "select ID,Name from SYS_StorageInfo";
	aq->Connection = li->con ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	while(!aq->Eof)
	{
	  cbstore->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
	  aq->Next();
	}

	 int i = cbstore->Items->IndexOfObject((TObject*)linfo.storageID);
	 cbstore->ItemIndex = i;
	 cbstoreChange(NULL);
	 if (linfo.storageID==0) {
		editstorehao->Enabled = false;
		cbstore->Enabled = false;
	 }else
	 {
		editstorehao->Enabled = false;
		cbstore->Enabled = false;

	 }

	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TfrmQuery::sefromExit(TObject *Sender)
{
   if (rb1->Checked) {
	 if (sefrom->Value > seto->Value) {
	  sefrom->Value = seto->Value ;
	}
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmQuery::cbstoreChange(TObject *Sender)
{
	editstorehao->Text =  IntToStr((int)cbstore->Items->Objects[cbstore->ItemIndex]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmQuery::dtfromExit(TObject *Sender)
{
     if (rb2->Checked ) {
	if (dtfrom->Date > dtto->Date ) {
		dtfrom->Date = dtto->Date ;
	}
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmQuery::spcancelClick(TObject *Sender)
{
  ModalResult = mrCancel ;
}
//---------------------------------------------------------------------------


void __fastcall TfrmQuery::spokClick(TObject *Sender)
{
   if (rb1->Checked) {
	 Max = sefrom->Value;
	 Min = seto->Value ;
	 if (Max > Min) {
		MessageBox(0,"请输入正确的单号范围！","错误" ,MB_OK);
		 return;
	 }
	 RDanhao = true;

   }else if (rb2->Checked) {
	 FMax = dtfrom->Date ;
	 TMin = dtto->Date ;
	 if (DateToStr(FMax) > DateToStr(TMin)) {
		MessageBox(0,"请输入正确的时间范围！","错误" ,MB_OK);
		 return;
	 }
	 RDanhao = false;
   }
   ModalResult = mrOk ;

}
//---------------------------------------------------------------------------

void __fastcall TfrmQuery::sefromKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        sefrom->SetFocus();
	}
}
//---------------------------------------------------------------------------


