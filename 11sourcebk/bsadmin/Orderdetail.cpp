//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Orderdetail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmOrderdetail *frmOrderdetail;
//---------------------------------------------------------------------------
__fastcall TfrmOrderdetail::TfrmOrderdetail(TComponent* Owner,TADOConnection *cn,int bkcatalogid,int stgid)
	: TForm(Owner)
{
	aq->Connection = cn;
	fcon = cn;
	AnsiString sql;
	sql = "select A.id,A.localnum,A.xiaoqu,A.xueyuan,A.incode,A.course,A.Amount,A.Discount,A.UnsendAmount,A.SendAmount,B.ISBN,B.Name as bookname,B.price,B.PressCount,C.AbbreviatedName,Order_lock.usableamount,Order_lock.stkamount,BS_OrderNoteHeader.HdTime,case when BS_OrderNoteHeader.shenheistate = 0 then '未审核' else '已审核' end as state,"
			" E.OrderNtCode,dbo.UF_BS_GetClientName(E.VendorID) as clientName "
			" from BS_OrderNote A left join "
			" BS_OrderNoteHeader on BS_OrderNoteHeader.id = A.OrderNtHeaderID left join "
			" BS_BookCatalog B ON A.BkcatalogID = B.id left join "
			" BS_PressInfo C ON B.PressID = C.id left join "
			" Order_lock ON A.BkcatalogID = Order_lock.BkcatalogID left join "
			" BS_OrderNoteHeader E ON A.OrderNtHeaderID = E.ID "
			" where A.state = 0 and E.state in (0,1) and A.BkcatalogID = " + IntToStr(bkcatalogid) + " and Order_lock.stgid = " + IntToStr(stgid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderdetail::RzButton1Click(TObject *Sender)
{
	if (aq->IsEmpty() ) {
        return;
	}
	TADOQuery *query = new TADOQuery(this);
	query->Connection = fcon;
	aq->First();
	int amount = 0;
	while (!aq->Eof )
	{
		amount = amount + aq->FieldByName("localnum")->AsInteger ;
		aq->Next();
	}
	if (amount > aq->FieldByName("stkamount")->AsInteger ) {
    	MessageBoxA(0,"锁定数量大于库存数量！","提示",MB_ICONASTERISK);
		return;
	}
	else
	{
		aq->UpdateBatch(arAll);
        ModalResult = mrOk ;
	}
	delete query;
}
//---------------------------------------------------------------------------

