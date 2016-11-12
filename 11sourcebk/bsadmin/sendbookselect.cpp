//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "sendbookselect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
Tfrmsendbookselect *frmsendbookselect;
//---------------------------------------------------------------------------
__fastcall Tfrmsendbookselect::Tfrmsendbookselect(TComponent* Owner,TADOConnection* con,int stgid)
	: TForm(Owner)
{
	m_catalogSearchMode = 1;
	m_storageID = stgid;
	aq->Connection = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsendbookselect::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------
void Tfrmsendbookselect::ChangeCatalogSearchMode()
{

	if (m_catalogSearchMode==4) {
		m_catalogSearchMode=1;
	}else
	{
	m_catalogSearchMode++;  }
	if (m_catalogSearchMode >= 5)
	{
		m_catalogSearchMode = 1;
	}

	switch (m_catalogSearchMode)
	{
	case 1:
		edtCatalog->MaxLength = 13;
		lblCatalog->Caption = "书 号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "自编码";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "书  名";
		break;
	case 4:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "定 价";
		break;
	default:
		break;
	}
}

//---------------------------------------------------------------------------
void __fastcall Tfrmsendbookselect::N1Click(TObject *Sender)
{
	lblCatalog->Caption = "书 号:";
	m_catalogSearchMode = 1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsendbookselect::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名:";
	 m_catalogSearchMode = 3;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsendbookselect::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码:";
	 m_catalogSearchMode = 2;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsendbookselect::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "定价:";
	 m_catalogSearchMode = 4;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsendbookselect::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
    	if (edtCatalog->Text == "") {
			ChangeCatalogSearchMode();
		}
		else
		{
			Query(edtCatalog->Text.Trim());
		}
	}
}
//---------------------------------------------------------------------------
void Tfrmsendbookselect::Query(AnsiString strwhere)
{
	String sql;
	sql = "select BS_BookCatalog.ID,STK_BookInfo.ID as BKID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,STK_BookInfo.ID as STK_BookinfoID,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.AbbreviatedName ,STK_BookstackInfo.name LocalName "
			"from STK_BookInfo  join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(m_storageID);
	switch (m_catalogSearchMode) {
		case 1:  //书号
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Barcode='" + strwhere  + "'";
		break;
		case 2:  //自编码
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.UserDefCode like '%" + strwhere  + "%'";
		break;
		case 3:  //书名
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Name like '%" + strwhere  + "%'";
		break;
		case 4:  //定价
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Price =" + strwhere;
		break;
	default:
        ;
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsendbookselect::BtnAlignNoneClick(TObject *Sender)
{
	ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsendbookselect::dgcatalogselectDblClick(TObject *Sender)
{
	ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsendbookselect::dgcatalogselectKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key = '\r') {
    	ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------
