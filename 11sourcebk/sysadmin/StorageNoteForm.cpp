//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include<VCl\Printers.hpp>


#include "StorageNoteForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzDBList"
#pragma link "RzLstBox"
#pragma link "RzChkLst"
#pragma link "RzDBChk"
#pragma link "RzRadChk"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "MDIChild"
#pragma resource "*.dfm"
TfrmStorageNote *frmStorageNote;
//---------------------------------------------------------------------------
__fastcall TfrmStorageNote::TfrmStorageNote(TComponent* Owner)
	: TfrmMDIChild(Owner)
{   
	m_module = MTSysadmin;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageNote::FormClose(TObject *Sender,
      TCloseAction &Action)
{
				dsetStorageNote->Active=false;
				Action = caFree;

}
//---------------------------------------------------------------------------



void __fastcall TfrmStorageNote::dblbStorageNameClick(TObject *Sender)
{
   //	dsetStorageNote->RecNo = dblbStorageName->ItemIndex + 1;


}
//---------------------------------------------------------------------------

void TfrmStorageNote::Init(TApplication* app, TADOConnection* con)
{
	TfrmMDIChild::Init(app, con);
	qryStorageName->Connection = m_con;
	 qryStorageName->SQL->Add("select Name from SYS_StorageInfo");
	 qryStorageName->Open();
	// dblbStorageName->Clear();
	 //dblbStorageName->DataField = "Name";
	 RzDBCheckBox1->DataField = "ShowStorageNoteIndex";
	 CHKBarcode->DataField = "ShowStorageNoteBarcode";
	 CHKISBN->DataField = "ShowStorageNoteISBN";
	 CHKBarcode->DataField = "ShowStorageNoteBarcode";
	 CHKCatalog->DataField = "ShowStorageNoteCatalog";
	 CHKBookName->DataField = "ShowStorageNoteBookName";
	 CHKPrice->DataField = "ShowStorageNotePrice";
	 CHKAuthor->DataField = "ShowStorageNoteAuthor";
	 CHKRevision->DataField = "ShowStorageNoteRevision";
	 CHKPublicDate->DataField = "ShowStorageNotePublicDate";
	 CHKCategory->DataField = "ShowStorageNoteCategory";
	 CHKPress->DataField = "ShowStorageNotePress";
	 CHKFixedPrice->DataField = "ShowStorageNoteFixedPrice";
	 CHKDiscountedPrice->DataField = "ShowStorageNoteDiscountedPrice";



	 qryStorageName->First();
	 //dblbStorageName->Action=true;
   //	 dblbStorageName->ReadOnly=true;
	 //dblbStorageName->Enabled=true;


	 while (!qryStorageName->Eof)
	 {
	   //	dblbStorageName->Items->Add(qryStorageName->FieldByName("Name")->AsString);
		//RzListBox1->Items->Add(qryStorageName->FieldByName("Name")->AsString);
		ListBox1->Items->Add(qryStorageName->FieldByName("Name")->AsString);
		qryStorageName->Next();
	 }

	 qryStorageName->Close();
	 dsetStorageNote->Connection = m_con;
	 dsetStorageNote->CommandText = "select * from SYS_StorageInfo";
	 dsetStorageNote->Active = true;
}

void __fastcall TfrmStorageNote::dblbStorageNameDblClick(TObject *Sender)
{
   //	dsetStorageNote->RecNo = dblbStorageName->ItemIndex + 1;
}
//---------------------------------------------------------------------------





void __fastcall TfrmStorageNote::ListBox1Click(TObject *Sender)
{
  dsetStorageNote->RecNo = ListBox1->ItemIndex + 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageNote::ListBox1DblClick(TObject *Sender)
{
		  dsetStorageNote->RecNo = ListBox1->ItemIndex + 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageNote::ListBox1KeyPress(TObject *Sender, char &Key)
{
 dsetStorageNote->RecNo = ListBox1->ItemIndex + 1;

}
//---------------------------------------------------------------------------







void __fastcall TfrmStorageNote::btn1Click(TObject *Sender)
{
        	if (dsetStorageNote->State == dsEdit || dsetStorageNote->State == dsInsert)
	{
		dsetStorageNote->Post();
		ShowMessage("±£´æ³É¹¦£¡");
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageNote::btn2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------
void __fastcall TfrmStorageNote::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	  		if (Shift.Contains(ssCtrl)&&Key==83) {   //S
			this->btn1->Click();
			 }
				if (Key==0x1B) {   //esc
				this->btn2->Click();
		}
}
//---------------------------------------------------------------------------
