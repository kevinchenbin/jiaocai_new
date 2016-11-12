//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "checkselbook.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmcatalogselect *frmcatalogselect;
//---------------------------------------------------------------------------
__fastcall Tfrmcatalogselect::Tfrmcatalogselect(TComponent* Owner,TADOConnection* con,TADOQuery * aquery)
	: TForm(Owner)
{
	dsselect->DataSet = aquery ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogselect::BtnExitClick(TObject *Sender)
{
  Close();
}
/*
void Tfrmcatalogselect::QueryBook(int m_storageID, int m_local,AnsiString value)
{
	String sql;
	bool Display;


	 //1条码 2为自编码 3为书名  4 ISBN 5 作者

	switch (m_searchMode)
	{
	case 1://条码
		sql = "select BS_BookCatalog.ID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.fullname "
			"from STK_BookInfo left join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(m_storageID);
			+ " and  STK_BookstackInfo.id = " + IntToStr(m_local)
			+ " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Barcode='" + value + "'";
		if (!zerodisplay) {                //查询业务设置库存为0的是否显示

		   sql = sql + "and STK_BookInfo.Amount > 0 " ;

		}
		break;
	case 2://自编码
		sql = "select BS_BookCatalog.ID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.fullname "
			"from STK_BookInfo left join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(m_storageID)
			+ " and  STK_BookstackInfo.id = " + IntToStr(m_local)
			+ " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.UserDefCode='" + value + "'";

		if (!zerodisplay) {

		   sql = sql + "and STK_BookInfo.Amount > 0 " ;

		}
		break;
	case 3://书名
		sql = "select BS_BookCatalog.ID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price,BS_PressInfo.fullname  "
			"from STK_BookInfo left join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(m_storageID)
			+ " and  STK_BookstackInfo.id = " + IntToStr(m_local)
			+ " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Name='" + value + "'";

		if (!zerodisplay) {

		   sql = sql + "and STK_BookInfo.Amount > 0 " ;
			}
		break;
	case 4: //ISBN
		sql = "select BS_BookCatalog.ID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price,BS_PressInfo.fullname  "
			"from STK_BookInfo left join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(m_storageID)
			+ " and  STK_BookstackInfo.id = " + IntToStr(m_local)
			+ " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.ISBN='" + value + "'";

		if (!zerodisplay) {

			sql = sql + "and STK_BookInfo.Amount > 0 " ;
			}

		break;
	case 5://作者
			sql = "select BS_BookCatalog.ID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price,BS_PressInfo.fullname  "
			"from STK_BookInfo left join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(m_storageID)
			+ + " and  STK_BookstackInfo.id = " + IntToStr(m_local)
			+ " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Author='" + value + "'";

		if (!zerodisplay) {

		sql = sql + "and STK_BookInfo.Amount > 0 " ;
		}
		break;
	default:
		break;
	}

	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();

	   /*
	dsetQry->Active = false;
		dsetQry->CommandText = sql;
		dsetQry->Active = true;

	if (dsetQry->Active && dsetQry->RecordCount > 1)//查找到多条记录
	{
		dbgrdQry->SetFocus();
	}
	else if (dsetQry->Active && dsetQry->RecordCount == 1)//查找到一条记录
	{
    	m_ok = true;
		PostMessage(Handle, WM_CLOSE, 0, 0);
	}
	else if (dsetQry->Active && dsetQry->RecordCount < 1)//未找到记录
	{
    	m_ok = true;
		PostMessage(Handle, WM_CLOSE, 0, 0);
	}
	else//查找出错
	{
		edtSearch->SetFocus();
	}    */

//}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogselect::FormClose(TObject *Sender, TCloseAction &Action)

{
	   Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogselect::BtnPropertiesClick(TObject *Sender)
{
	  ModalResult = mrOk;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcatalogselect::dgcatalogselectKeyPress(TObject *Sender, wchar_t &Key)

{
	      if (Key = '\r') {
          ModalResult = mrOk ;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogselect::dgcatalogselectDblClick(TObject *Sender)
{

          ModalResult = mrOk ;

}
//---------------------------------------------------------------------------

