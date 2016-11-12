//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitsiglefenfa.h"
#include "checkselbook.h"
#include "..\Unitboolslect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmsiglefenfa *frmsiglefenfa;
//---------------------------------------------------------------------------
__fastcall Tfrmsiglefenfa::Tfrmsiglefenfa(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
	fcon = con;
	fstgid = stgid;
	m_catalogSearchMode = 0;
	dtpstart->Date = Date();
	dtpend->Date = Date();
	aq->Connection = con;
	bkcatalogid = -1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglefenfa::N1Click(TObject *Sender)
{
	m_catalogSearchMode = 0;
	Label4->Caption = "书号：";
	edquery->MaxLength = 13;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglefenfa::N2Click(TObject *Sender)
{
	m_catalogSearchMode = 1;
	Label4->Caption = "书名：";
	edquery->MaxLength = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglefenfa::N3Click(TObject *Sender)
{
	m_catalogSearchMode = 2;
	Label4->Caption = "自编码：";
	edquery->MaxLength = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglefenfa::N4Click(TObject *Sender)
{
	m_catalogSearchMode = 3;
	Label4->Caption = "定价：";
	edquery->MaxLength = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglefenfa::N5Click(TObject *Sender)
{
	m_catalogSearchMode = 4;
	Label4->Caption = "作者：";
	edquery->MaxLength = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglefenfa::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (m_catalogSearchMode == 3) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
			Key = NULL;
		}
	}
	if (Key == '\r') {
		if (edquery->Text == "") {
			ChangeCatalogSearchMode();
		}
		else
		{
        	float price;
			if (m_catalogSearchMode == 3) {
				try {
					price = StrToFloat(edquery->Text.Trim());
				} catch (...) {
					MessageBox(0,"请输入正确的定价！","入库" ,MB_ICONEXCLAMATION);
					return;
				}
			}
			AnsiString sql;
			TADOQuery *aq = new TADOQuery(this);
			aq->Connection = fcon;
			sql = "select BS_BookCatalog.id,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.UserDefCode,Price,PressCount,BS_BookCatalog.Author,BS_PressInfo.AbbreviatedName,BS_BookType.Name AS typename "
					" from BS_BookCatalog left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
					" left join BS_BookType on BS_BookCatalog.smallBookTypeID = BS_BookType.id where BS_BookCatalog.Unavailable = 1";
			switch (m_catalogSearchMode) {
				case 0:
					sql = sql + " and BS_BookCatalog.ISBN = '" + edquery->Text + "'" ;
				break;
				case 1:
					sql = sql + " and BS_BookCatalog.Name like '%" + edquery->Text + "%'";
				break;
				case 2:
					sql = sql + " and BS_BookCatalog.UserDefCode like '%" + edquery->Text + "%'";
				break;
				case 3:
					sql = sql + " and BS_BookCatalog.Price = " + edquery->Text ;
				break;
				case 4:
					sql = sql + " and BS_BookCatalog.Author like '%" + edquery->Text + "%'";
				break;
            default:
                ;
			}
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount >1) {
				Tfrmselectbook *frm = new Tfrmselectbook(Application,aq);
				if (frm->ShowModal() == mrOk ) {
                	bkcatalogid = aq->FieldByName("id")->AsInteger ;
					edisbn->Text = aq->FieldByName("ISBN")->AsAnsiString ;
					edname->Text = aq->FieldByName("Name")->AsAnsiString ;
					edprice->Text = aq->FieldByName("Price")->AsAnsiString ;
					edpress->Text = aq->FieldByName("AbbreviatedName")->AsAnsiString ;
					edpresscount->Text = aq->FieldByName("PressCount")->AsAnsiString ;
					edtype->Text = aq->FieldByName("typename")->AsAnsiString ;
					edauthor->Text = aq->FieldByName("Author")->AsAnsiString ;
					Query();
				}
			}
			else if (aq->RecordCount == 1) {
				bkcatalogid = aq->FieldByName("id")->AsInteger ;
				edisbn->Text = aq->FieldByName("ISBN")->AsAnsiString ;
				edname->Text = aq->FieldByName("Name")->AsAnsiString ;
				edprice->Text = aq->FieldByName("Price")->AsAnsiString ;
				edpress->Text = aq->FieldByName("AbbreviatedName")->AsAnsiString ;
				edpresscount->Text = aq->FieldByName("PressCount")->AsAnsiString ;
				edtype->Text = aq->FieldByName("typename")->AsAnsiString ;
				edauthor->Text = aq->FieldByName("Author")->AsAnsiString ;
				Query();
			}
			delete aq;
		}
	}
}
//---------------------------------------------------------------------------
void Tfrmsiglefenfa::ChangeCatalogSearchMode()
{
	m_catalogSearchMode++;
	if (m_catalogSearchMode >= 5)
	{
		m_catalogSearchMode = 0;
	}

	switch (m_catalogSearchMode)
	{
	case 0:
		edquery->MaxLength = 13;
		Label4->Caption = "书号：";
		break;
	case 1:
		edquery->MaxLength = 0;
		Label4->Caption = "书名：";
		break;
	case 2:
		edquery->MaxLength = 0;
		Label4->Caption = "自编码：";
		break;
	case 3:
		edquery->MaxLength = 0;
		Label4->Caption = "定价：";
		break;
	case 4:
		edquery->MaxLength = 0;
		Label4->Caption = "作者：";
		break;
	default:
        break;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglefenfa::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void Tfrmsiglefenfa::Query()
{
    AnsiString sql;
	sql = "select A.id,A.class,A.localnum,A.Amount,A.Discount,A.UnsendAmount,A.SendAmount,B.ISBN,B.Name as bookname,B.price,B.PressCount,C.AbbreviatedName,Order_lock.usableamount,case when E.shenheistate = 0 then '未审核' else '已审核' end as state,"
			" E.OrderNtCode,dbo.UF_BS_GetClientName(E.VendorID) as clientName "
			" from BS_OrderNote A left join "
			" BS_BookCatalog B ON A.BkcatalogID = B.id left join "
			" BS_PressInfo C ON B.PressID = C.id left join "
			" Order_lock ON A.BkcatalogID = Order_lock.BkcatalogID left join "
			" BS_OrderNoteHeader E ON A.OrderNtHeaderID = E.ID "
			" where E.stgid = " + IntToStr(fstgid) + " and E.state in (0,1) and A.BkcatalogID = " + IntToStr(bkcatalogid) + " and Order_lock.stgid = " + IntToStr(fstgid);
	if (chstart->Checked ) {
		sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',E.HdTime) >= 0";
	}
	if (chend->Checked ) {
		sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',E.HdTime) <= 0";
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsiglefenfa::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsiglefenfa::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		BtnView->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsiglefenfa::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsiglefenfa::BtnViewClick(TObject *Sender)
{
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsiglefenfa::aqAfterPost(TDataSet *DataSet)
{
    TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = aq->FieldByName("id")->AsAnsiString ;
	aq->Active = false;
	aq->Active = true;
	aq->Locate("id",str,Opts);
}
//---------------------------------------------------------------------------

