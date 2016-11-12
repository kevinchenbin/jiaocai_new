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


	 //1���� 2Ϊ�Ա��� 3Ϊ����  4 ISBN 5 ����

	switch (m_searchMode)
	{
	case 1://����
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
		if (!zerodisplay) {                //��ѯҵ�����ÿ��Ϊ0���Ƿ���ʾ

		   sql = sql + "and STK_BookInfo.Amount > 0 " ;

		}
		break;
	case 2://�Ա���
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
	case 3://����
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
	case 5://����
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

	if (dsetQry->Active && dsetQry->RecordCount > 1)//���ҵ�������¼
	{
		dbgrdQry->SetFocus();
	}
	else if (dsetQry->Active && dsetQry->RecordCount == 1)//���ҵ�һ����¼
	{
    	m_ok = true;
		PostMessage(Handle, WM_CLOSE, 0, 0);
	}
	else if (dsetQry->Active && dsetQry->RecordCount < 1)//δ�ҵ���¼
	{
    	m_ok = true;
		PostMessage(Handle, WM_CLOSE, 0, 0);
	}
	else//���ҳ���
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

