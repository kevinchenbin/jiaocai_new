//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "hoistoryview.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmhistoryview *frmhistoryview;
//---------------------------------------------------------------------------
__fastcall Tfrmhistoryview::Tfrmhistoryview(TComponent* Owner,TADOConnection *con,int bkid)
	: TForm(Owner)
{
	aq->Connection = con;
	String sql ;
	sql = "select BS_StorageNoteHeader.StgNtCode as Ntcode,BS_StorageNote.Amount,BS_StorageNote.Discount,Convert(varchar(20),BS_StorageNoteHeader.HdTime,111) as HdTime,CUST_CustomerInfo.Name,BS_BookCatalog.Price from BS_StorageNote left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.ID "
			  "left join STK_BookInfo on BS_StorageNote.BkInfoID = STK_BookInfo.ID left join CUST_CustomerInfo on STK_BookInfo.SupplierID = CUST_CustomerInfo.id right join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.ID "
			  "WHERE BS_BookCatalog.ID = " + IntToStr(bkid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmhistoryview::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmhistoryview::BtnExitClick(TObject *Sender)
{
  Close();

}
//---------------------------------------------------------------------------

