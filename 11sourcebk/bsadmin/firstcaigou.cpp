//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "firstcaigou.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmfirstcaigou *frmfirstcaigou;
//---------------------------------------------------------------------------
__fastcall Tfrmfirstcaigou::Tfrmfirstcaigou(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void Tfrmfirstcaigou::Init(LandInfo* li)
{
	aq->Connection = li->con;
	AnsiString sql;
	sql = "select BS_Tmporder.*,sum(dbo.BS_OrderNote.localnum) as localnum,sum(dbo.BS_OrderNote.UnsendAmount) as UnsendAmount from BS_Tmporder left join BS_OrderNote on BS_Tmporder.bkcatalogid = BS_OrderNote.BkcatalogID "
			" left  join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" where groupid = " + IntToStr(groupid) + "and BS_OrderNoteHeader.caigou = 0 and BS_OrderNoteHeader.state in(0,1) and BS_OrderNoteHeader.shenheistate = 1 and BS_OrderNote.state = 0 "
			" group by BS_Tmporder.id,BS_Tmporder.groupid,BS_Tmporder.orderheaderid,BS_Tmporder.ISBN,BS_Tmporder.bookname,Price,"
			" Author,BS_Tmporder.amount,BS_Tmporder.OrderNtCode,BS_Tmporder.bkcatalogid,bkamount,Pressname,ClientName,Clientid,modle,"
			" BS_Tmporder.Discount,ordernoteid,BS_Tmporder.FixedPrice,DiscountPrice,chenked,BS_Tmporder.supplierid,BS_Tmporder.FahuoClient";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfirstcaigou::SpeedButton1Click(TObject *Sender)
{
	if (!aq->IsEmpty() ) {
		ModalResult = mrOk ;
	}
	else
	{
    	Close();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfirstcaigou::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfirstcaigou::BtnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfirstcaigou::BtnAlignBottomClick(TObject *Sender)
{
		WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfirstcaigou::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	  	if (Shift.Contains(ssCtrl)&& Key == 78 ) {
	   BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {
	   BtnExit->Click();
	}
			if (Shift.Contains(ssCtrl)&& Key ==90) {
				WindowState = wsNormal  ;
		}
}
//---------------------------------------------------------------------------

