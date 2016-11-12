//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitjxcbijiao.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "Series"
#pragma resource "*.dfm"
Tfrmjxcbijiao *frmjxcbijiao;
//---------------------------------------------------------------------------
__fastcall Tfrmjxcbijiao::Tfrmjxcbijiao(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
	con = cn;
	fstgid = stgid;
	aqrk->Connection = cn;
	aqpx->Connection = cn;
	aqls->Connection = cn;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = cn;
	AnsiString sql;
	sql = "select ID,Name from SYS_StorageInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbstorage->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger);
		aq->Next();
	}
	cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)stgid);

		sql = "select Master from SYS_StorageInfo where id = " + IntToStr(stgid);
        aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		master = aq->FieldByName("Master")->AsBoolean;
		if (aq->FieldByName("Master")->AsBoolean ) {
			cbstorage->Enabled = true;
			chstorage->Enabled = true;
		}
		else
		{
			cbstorage->Enabled = false;
			chstorage->Enabled = false;
		}

	delete aq;
	sql = "select  CONVERT(varchar(100), HdTime, 23) as Name,sum(BS_StorageNoteHeader.TotalAmount) as TotalAmount,sum(BS_StorageNoteHeader.TotalFixedPrice) as TotalFixedPrice,sum(BS_StorageNoteHeader.TotalDiscountedPrice) as TotalDiscountedPrice "
			" from BS_StorageNoteHeader "
			" where (datediff(d,BS_StorageNoteHeader.HdTime,getdate()) < 7) and BS_StorageNoteHeader.Stgid = " + IntToStr(stgid) +
			" group by  CONVERT(varchar(100), HdTime, 23)";
	aqrk->Close();
	aqrk->SQL->Clear();
	aqrk->SQL->Add(sql);
	aqrk->Open();

	sql = "SELECT A.Name,sum(A.TotalAmount) as TotalAmount,sum(TotalFixedPrice) as TotalFixedPrice,sum(TotalDiscountedPrice) as TotalDiscountedPrice "
			" from "
			" (select  CONVERT(varchar(100), HdTime, 23) as Name,sum(BS_WsaleNoteHeader.TotalAmount) as TotalAmount,sum(BS_WsaleNoteHeader.FixedPrice) as TotalFixedPrice,sum(BS_WsaleNoteHeader.DiscountedPrice) as TotalDiscountedPrice "
			" from BS_WsaleNoteHeader "
			" where (datediff(d,BS_WsaleNoteHeader.HdTime,getdate()) < 7) and BS_WsaleNoteHeader.Stgid = " + IntToStr(stgid) +
			" group by  CONVERT(varchar(100), HdTime, 23) "
			" union "
			" select  CONVERT(varchar(100), HdTime, 23) as Name,sum(BS_RetailNoteHeader.TotalAmount) as TotalAmount,sum(BS_RetailNoteHeader.TotalFixedPrice) as TotalFixedPrice,sum(BS_RetailNoteHeader.TotalDiscountedPrice) as TotalDiscountedPrice "
			" from BS_RetailNoteHeader "
			" where (datediff(d,BS_RetailNoteHeader.HdTime,getdate()) < 7) and BS_RetailNoteHeader.Stgid = " + IntToStr(stgid) +
			" group by  CONVERT(varchar(100), HdTime, 23))as A "
			" group by A.Name";
	aqpx->Close();
	aqpx->SQL->Clear();
	aqpx->SQL->Add(sql);
	aqpx->Open();


	title = "最近一周进销存数量按日对比";
	charjxc->Title->Text->Clear();
	charjxc->Title->Text->Add(title);
	charjxc->Series[0]->Clear();
	charjxc->Series[1]->Clear();
	charjxc->Series[2]->Clear();
	charjxc->Series[3]->Clear();
	for (int i = 1; i <= aqrk->RecordCount ; i++) {
		charjxc->Series[0]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
		charjxc->Series[1]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
		charjxc->Series[2]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
		charjxc->Series[3]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
	   aqrk->Next();
	   aqpx->Next();
	}

	charjxc->Series[2]->Visible = false;
	charjxc->Series[3]->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmjxcbijiao::SpeedButton2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmjxcbijiao::SpeedButton1Click(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmjxcbijiao::rg2Click(TObject *Sender)
{
    charjxc->Series[0]->Clear();
	charjxc->Series[1]->Clear();
	charjxc->Series[2]->Clear();
	charjxc->Series[3]->Clear();
	aqrk->First();
	aqpx->First();
	switch (rg2->ItemIndex ) {
		case 0:
			for (int i = 1; i <= aqrk->RecordCount ; i++) {
				charjxc->Series[0]->AddY(aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
				//charjxc->Series[0]->AddY(aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
				charjxc->Series[0]->Add(aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
			   //	charjxc->Series[0]->Add(aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
				charjxc->Series[2]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
				charjxc->Series[3]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
				aqrk->Next();
				aqpx->Next();
			}
			break;
		case 1:
            for (int i = 1; i <= aqrk->RecordCount ; i++) {
				charjxc->Series[0]->AddXY(i,aqrk->FieldByName("TotalFixedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
				charjxc->Series[1]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
			   //	charjxc->Series[0]->Add(aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
				charjxc->Series[2]->AddXY(i,aqrk->FieldByName("TotalFixedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
				charjxc->Series[3]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
				aqrk->Next();
				aqpx->Next();
			}
			break;
		case 2:
            for (int i = 1; i <= aqrk->RecordCount ; i++) {
				charjxc->Series[0]->AddXY(i,aqrk->FieldByName("TotalDiscountedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
				charjxc->Series[1]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
			   //	charjxc->Series[0]->Add(aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
				charjxc->Series[2]->AddXY(i,aqrk->FieldByName("TotalDiscountedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
				charjxc->Series[3]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
				aqrk->Next();
				aqpx->Next();
			}
			break;
	default:
		;
	}

	switch (rgview->ItemIndex ) {
	case 0:
		charjxc->Series[0]->Visible = true;
		charjxc->Series[1]->Visible = true;
		charjxc->Series[2]->Visible = false;
		charjxc->Series[3]->Visible = false;
		break;
	case 1:
		charjxc->Series[0]->Visible = false;
		charjxc->Series[1]->Visible = false;
		charjxc->Series[2]->Visible = true;
		charjxc->Series[3]->Visible = true;
		break;
	default:
		;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmjxcbijiao::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmjxcbijiao::rg1Click(TObject *Sender)
{
	int storageid;
	AnsiString sql;
	try {
		storageid = (int)(cbstorage->Items->Objects[cbstorage->ItemIndex]);
	} catch (...) {
		MessageBox(0,"请选择正确的店名！","警告" ,MB_ICONWARNING);
    	return;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmjxcbijiao::rgviewClick(TObject *Sender)
{
	switch (rgview->ItemIndex ) {
	case 0:
		charjxc->Series[0]->Visible = true;
		charjxc->Series[1]->Visible = true;
		charjxc->Series[2]->Visible = false;
		charjxc->Series[3]->Visible = false;
		break;
	case 1:
		charjxc->Series[0]->Visible = false;
		charjxc->Series[1]->Visible = false;
		charjxc->Series[2]->Visible = true;
		charjxc->Series[3]->Visible = true;
		break;
	default:
		;
	}
}
//---------------------------------------------------------------------------
