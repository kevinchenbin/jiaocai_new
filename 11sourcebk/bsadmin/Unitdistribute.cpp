//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitdistribute.h"
#include "UnitClientyouxianji.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmdaohuofenfa *frmdaohuofenfa;
//---------------------------------------------------------------------------
__fastcall Tfrmdaohuofenfa::Tfrmdaohuofenfa(TComponent* Owner)
	: TForm(Owner)
{

}
void Tfrmdaohuofenfa::Init(LandInfo *li)
{
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	aq->Connection = li->con ;
	aq1->Connection = li->con ;
	aq2->Connection = li->con ;
	clientset = 0;
	ReadData();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaohuofenfa::BtnExitClick(TObject *Sender)
{
 	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaohuofenfa::BtnAlignBottomClick(TObject *Sender)
{
  	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmdaohuofenfa::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void  Tfrmdaohuofenfa::ReadData()

{
	AnsiString sql;
	sql = "select BS_OrderNoteHeader.id,OrderNtCode,HdTime,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as ClientName,TotalAmount,"
			"Remarks,sum(localnum) as localnum,sum(fenfainum) as fenfainum,case when sum(Amount) <> 0 then sum(SendAmount)/sum(Amount) else 0 end as fahuorate "
			"from BS_OrderNote left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			"where BS_OrderNote.state = 0 and BS_OrderNoteHeader.state in (0,1) and BS_OrderNoteHeader.StgID = " +  IntToStr(linfo.storageID) +
			"group by BS_OrderNoteHeader.id,OrderNtCode,HdTime,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID),Remarks,TotalAmount " ;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaohuofenfa::RzDBGrid1CellClick(TColumn *Column)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	AnsiString sql;
	sql = "select BS_OrderNote.*,ISBN,Name,Price,UserDefCode,Author,PressCount,AbbreviatedName "
			"from BS_OrderNote left join BS_BookCatalog on BS_OrderNote.BkcatalogID = BS_BookCatalog.id "
			"left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
			"where BS_OrderNote.state = 0 and BS_OrderNote.OrderNtHeaderID = " + aq1->FieldByName("ID")->AsString ;
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaohuofenfa::SpeedButton1Click(TObject *Sender)
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = linfo.con;
	sql = "exec USP_BS_fenfa " +  IntToStr(linfo.storageID) + ",1,0,-1" ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	ReadData();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaohuofenfa::Btn1Click(TObject *Sender)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = linfo.con;
	AnsiString sql;
	sql = "update BS_OrderNote set localnum = localnum-fenfainum,fenfainum = 0 where OrderNtHeaderID =  " +  aq1->FieldByName("ID")->AsString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	aq1->Active = false;
	aq1->Active = true;
	if (!aq2->IsEmpty() ) {
		aq2->Active = false;
		aq2->Active = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaohuofenfa::Btn2Click(TObject *Sender)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = linfo.con;
	AnsiString sql;
	sql = "update BS_OrderNote set localnum = 0,fenfainum = 0 where OrderNtHeaderID =  " +  aq1->FieldByName("ID")->AsString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	aq1->Active = false;
	aq1->Active = true;
	if (!aq2->IsEmpty() ) {
		aq2->Active = false;
		aq2->Active = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaohuofenfa::BtnAlignNoneClick(TObject *Sender)
{
	TfrmClientyouxianji *frm = new TfrmClientyouxianji(Application,linfo.con,linfo.storageID);
	frm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaohuofenfa::SpeedButton2Click(TObject *Sender)
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = linfo.con;
	sql = "exec USP_BS_fenfa " +  IntToStr(linfo.storageID) + ",0,0,-1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	ReadData();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaohuofenfa::SpeedButton3Click(TObject *Sender)
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = linfo.con;
	sql = "exec USP_BS_fenfa " +  IntToStr(linfo.storageID) + ",1,1,-1" ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	ReadData();
}
//---------------------------------------------------------------------------


