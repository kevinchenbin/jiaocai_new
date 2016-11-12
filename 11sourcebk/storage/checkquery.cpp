//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CheckQuery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzDTP"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzRadChk"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TCheckInQuery *CheckInQuery;
//---------------------------------------------------------------------------
__fastcall TCheckInQuery::TCheckInQuery(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{

Querybase->Connection = cn;
Querymingxi->Connection = cn;
Querylocal->Connection = cn;
}
//---------------------------------------------------------------------------
void __fastcall TCheckInQuery::LabelselectMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
	 	PM->Popup(pt.x,pt.y);
  }
}
//---------------------------------------------------------------------------
void __fastcall TCheckInQuery::useselfcodeClick(TObject *Sender)
{
	serchModle = 1;
	Labelselect->Caption = "自编码：";
	condition->MaxLength = 13;
}
//---------------------------------------------------------------------------

void __fastcall TCheckInQuery::bencnoClick(TObject *Sender)
{
	serchModle = 2;
	Labelselect->Caption = "条码：";
	condition->MaxLength = 13;
}
//---------------------------------------------------------------------------
void __fastcall TCheckInQuery::booknameClick(TObject *Sender)
{
	serchModle = 3;
	Labelselect->Caption = "书名：";
}
//---------------------------------------------------------------------------
void __fastcall TCheckInQuery::authorClick(TObject *Sender)
{
	serchModle = 4;
	Labelselect->Caption = "作者：";
}
//---------------------------------------------------------------------------
void __fastcall TCheckInQuery::ISBNClick(TObject *Sender)
{
	serchModle = 5;
	Labelselect->Caption = "ISBN：";
	condition->MaxLength = 13;
}
//---------------------------------------------------------------------------
void __fastcall TCheckInQuery::FormShow(TObject *Sender)
{
	 AnsiString sql;
	 sql = "select name from SYS_StorageInfo";
	Querylocal->Close();
	Querylocal->SQL->Clear();
	Querylocal->SQL->Add(sql);
	Querylocal->Open();


	edtstore->Text = Querylocal->FieldByName("name")->AsAnsiString  ;
	DBGridmingxi->Visible = false;
	 sql = "select STK_BookstackInfo.ID,STK_BookstackInfo.Name as N from STK_BookstackInfo inner join SYS_StorageInfo on STK_BookstackInfo.StgID = SYS_StorageInfo.ID where SYS_StorageInfo.Name = '";  //查询库位
	sql = sql + edtstore->Text + "'";
	Querylocal->Close();
	Querylocal->SQL->Clear();
	Querylocal->SQL->Add(sql);
	Querylocal->Open();
	Querylocal->First();
	while(!Querylocal->Eof )
	{
	  cblocal->AddObject(Querylocal->FieldByName("N")->AsAnsiString ,(TObject*)Querylocal->FieldByName("ID")->AsInteger );
	  Querylocal->Next();
	}
	cblocal->ItemIndex = 0;
	DTPstarttime->Enabled = false;
	DTPendtime->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TCheckInQuery::BtnViewClick(TObject *Sender)
{
	AnsiString sql,wherestr;
	sql = "select SYS_StorageInfo.Name as Sname,STK_BookstackInfo.Name as lname,STK_CheckStockinfo.checkstockNum,"
		  "STK_CheckStockinfo.checkdate,STK_CheckStockinfo.bk from STK_CheckStockinfo left join SYS_StorageInfo on "
		  "SYS_StorageInfo.ID = STK_CheckStockinfo.checkstore left join STK_BookstackInfo on STK_BookstackInfo.ID = STK_CheckStockinfo.checkstocklocal ";
	wherestr = "where SYS_StorageInfo.Name = '" + edtstore->Text + "' and STK_BookstackInfo.Name = '" + cblocal->Text + "'";
	if (CBstarttime->Checked) {
		wherestr = wherestr + " and STK_CheckStockinfo.checkdate >= '" + DateToStr(DTPstarttime->Date) + " 00:00:00' ";
	}
	if (CBendtime->Checked ) {
		wherestr = wherestr + " and STK_CheckStockinfo.checkdate <= '" + DateToStr(DTPendtime->Date) + " 23:59:59' ";
	}
	sql = sql + wherestr;
	Querybase->Close();
	Querybase->SQL->Clear();
	Querybase->SQL->Add(sql);
	Querybase->Open();
	DBGridbase->Columns->Items[0]->Width = 60;
	DBGridbase->Columns->Items[1]->Width = 60;
	DBGridbase->Columns->Items[2]->Width = 100;
	DBGridbase->Columns->Items[3]->Width = 100;
	DBGridbase->Columns->Items[4]->Width = 100;
}
//---------------------------------------------------------------------------
void __fastcall TCheckInQuery::DBGridbaseCellClick(TColumn *Column)
{
	String sql,sqlwhere,recordstr;
	sql = "select * from STK_StockInventories where NoteCode = '" + Querybase->FieldByName("checkstockNum")->AsAnsiString  + "'"  ;
	if (condition->Text != "") {
    	if (serchModle == 1) {
			sqlwhere = " and UserDefCode like '%" + Trim(condition->Text) + "%'";
		}
		if (serchModle == 2) {
			sqlwhere = " and Barcode like '%" + Trim(condition->Text) + "%'";
		}
		if (serchModle == 3) {
			sqlwhere = " and BookName like '%" + Trim(condition->Text) + "%'";
		}
		if (serchModle == 4) {
			sqlwhere = " and author like '%" + Trim(condition->Text) + "%'";
		}
		if (serchModle == 5) {
			sqlwhere = " and ISBN like '%" + Trim(condition->Text) + "%'";
		}
	}

	sql = sql + sqlwhere;
	Querymingxi->Close();
	Querymingxi->SQL->Clear();
	Querymingxi->SQL->Add(sql);
	Querymingxi->Open();
	DBGridmingxi->Visible = true;
	recordstr = "总共有"+ IntToStr(Querymingxi->RecordCount) + "条明细记录！" ;
	Labelrecord->Caption = recordstr;
	DBGridmingxi->Columns->Items[0]->Width = 80;
	DBGridmingxi->Columns->Items[1]->Width = 64;
	DBGridmingxi->Columns->Items[2]->Width = 80;
	DBGridmingxi->Columns->Items[3]->Width = 64;
	DBGridmingxi->Columns->Items[4]->Width = 64;
	DBGridmingxi->Columns->Items[5]->Width = 64;
	DBGridmingxi->Columns->Items[6]->Width = 64;
	DBGridmingxi->Columns->Items[7]->Width = 80;
	DBGridmingxi->Columns->Items[8]->Width = 64;
	DBGridmingxi->Columns->Items[9]->Width = 64;
	DBGridmingxi->Columns->Items[10]->Width = 64;
	DBGridmingxi->Columns->Items[11]->Width = 64;
}
//---------------------------------------------------------------------------
void __fastcall TCheckInQuery::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TCheckInQuery::CBstarttimeClick(TObject *Sender)
{
	if (CBstarttime->Checked ) {
		DTPstarttime->Enabled = true;
	}
	else
	{
    	DTPstarttime->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TCheckInQuery::CBendtimeClick(TObject *Sender)
{
	if (CBendtime->Checked) {
		DTPendtime->Enabled = true;
	}
	else
	{
		DTPendtime->Enabled = false;
	}
}
//---------------------------------------------------------------------------


