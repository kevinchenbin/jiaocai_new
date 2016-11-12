//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StockalarmSet.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TfrmalarmSet *frmalarmSet;
//---------------------------------------------------------------------------
__fastcall TfrmalarmSet::TfrmalarmSet(TComponent* Owner,TADOConnection* con,int stgid,int userid)
	: TForm(Owner)
{
  aquery->Connection = con;
  aquerydisplay->Connection = con;
  adosp->Connection = con;
  AnsiString sql;
  sql = "select ID,Name from SYS_StorageInfo where id = " + IntToStr(stgid);
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  Edit1->Text = aquery->FieldByName("ID")->AsString ;
  Edit2->Text = aquery->FieldByName("Name")->AsString ;
  sql = "select id,name from sys_user where id = " + IntToStr(userid) ;
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  Edit6->Text = aquery->FieldByName("name")->AsString ;
  fstgid = stgid;
}
//---------------------------------------------------------------------------//---------------------------------------------------------------------------
void TfrmalarmSet::search()
{
	AnsiString sql ;

	sql = "SELECT rank() over(order by STK_Bookinfo.ID) as xuhao,STK_Bookinfo.ID,BS_BookCatalog.Name,BS_BookCatalog.Price, BS_BookCatalog.ISBN,"
		" BS_BookType.Name AS SmallBktypeName, BS_PressInfo.AbbreviatedName,"
		" STK_BookInfo.Amount,STK_Bookinfo.MaxStock,STK_Bookinfo.MinStock, "
		" CUST_CustomerInfo.Name AS SupplierName, STK_BookInfo.SupplierID, "
		" STK_BookstackInfo.Name AS BkstackName "
		" FROM   STK_BookInfo LEFT OUTER JOIN "
		" BS_BookCatalog ON STK_BookInfo.BkcatalogID = BS_BookCatalog.ID"
		" LEFT OUTER JOIN STK_BookstackInfo ON STK_BookInfo.BkstackID = STK_BookstackInfo.ID"
		" LEFT OUTER JOIN CUST_CustomerInfo ON STK_BookInfo.SupplierID = CUST_CustomerInfo.ID"
		" LEFT OUTER JOIN BS_BookType ON BS_BookCatalog.smallBookTypeID = BS_BookType.ID"
		" LEFT OUTER JOIN BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID";
		 //searchModal 1: 类别 2:供应商,3：ISBN，4：书名 5：出版社

	sqlwhere = " where STK_BookInfo.stgid = " + IntToStr(fstgid) ;
	if (chisbn->Checked && edtisbn->Text != "") {
		sqlwhere = sqlwhere + " and (BS_BookCatalog.isbn like '%" + edtisbn->Text.Trim() + "%' or Barcode like '%" + edtisbn->Text.Trim() + "%')";
	}
	if (chname->Checked && edname->Text != "") {
		sqlwhere = sqlwhere + " and BS_BookCatalog.name like '%" + edname->Text.Trim() + "%'";
	}
	if (chtype->Checked && cbtype->Text != "") {
		sqlwhere = sqlwhere + " and BS_BookType.name like '%" + cbtype->Text.Trim() + "%'";
	}
	if (chsupplier->Checked && cbsupplier->Text != "") {
		sqlwhere = sqlwhere + " and CUST_CustomerInfo.name like '%" + cbsupplier->Text.Trim() + "%' and CUST_CustomerInfo.type = 1";
	}
	if (chpress->Checked && cbpress->Text != "") {
		sqlwhere = sqlwhere + " and BS_PressInfo.AbbreviatedName like '%" + cbpress->Text.Trim() + "%'";
	}
	sql = sql + sqlwhere;

	aquerydisplay->Close();
	aquerydisplay->SQL->Clear();
	aquerydisplay->SQL->Add(sql);
	try {
		aquerydisplay->Open();
	} catch (Exception &E) {
		MessageBox(0,"请输入正确的检索条件!" ,"提示" ,MB_ICONASTERISK);
		return;
	}
	if (aquerydisplay->RecordCount == 0) {
		MessageBox(0,"没有查询记录!" ,"库存超限预警" ,MB_ICONASTERISK);
	}
}
//---------------------------------------------------------------------------
void TfrmalarmSet::ReadyData()
{
	   String sql;
	   //类别
	   sql = "select ID,Name from bs_bookType";
	   aquery->Close();
	   aquery->SQL->Clear();
	   aquery->SQL->Add(sql);
	   aquery->Open();
	   while (!aquery->Eof)
	   {
		   cbtype->AddItem(aquery->FieldByName("Name")->AsAnsiString ,(TObject*)aquery->FieldByName("ID")->AsInteger );
		   aquery->Next();
	   }
	   //供应商
	   sql = "select ID,Name from CUST_CustomerInfo where type = 1";
	   aquery->Close();
	   aquery->SQL->Clear();
	   aquery->SQL->Add(sql);
	   aquery->Open();
	   while(!aquery->Eof)
	   {
			cbsupplier->AddItem(aquery->FieldByName("Name")->AsAnsiString ,(TObject*)aquery->FieldByName("ID")->AsInteger );
			aquery->Next();
	   }
	   //出版商
	   sql = "select ID,AbbreviatedName from BS_Pressinfo order by AbbreviatedName";
	   aquery->Close();
	   aquery->SQL->Clear();
	   aquery->SQL->Add(sql);
	   aquery->Open();
	   while(!aquery->Eof)
	   {
			cbpress->AddItem(aquery->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)aquery->FieldByName("ID")->AsInteger );
			aquery->Next();
	   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmalarmSet::FormCreate(TObject *Sender)
{
	ReadyData();
}
//---------------------------------------------------------------------------
void __fastcall TfrmalarmSet::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::dgalarmlistCellClick(TColumn *Column)
{
	if (aquerydisplay->IsEmpty() ) {
		return;
	}
	edtmax->Text = aquerydisplay->FieldByName("MaxStock")->AsAnsiString ;
	edtmin->Text = aquerydisplay->FieldByName("MinStock")->AsAnsiString ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmalarmSet::edtminKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == VK_RETURN) {

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::edtmaxKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key != '\b')) {
	  Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmalarmSet::BtnViewClick(TObject *Sender)
{
	search();
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::RzButton2Click(TObject *Sender)
{
	if (aquerydisplay->IsEmpty() ) {
        return;
	}
	AnsiString strwhere;
	int MaxStock,MinStock,UpdateMode;
	MinStock = 0;
	MaxStock = 0;
	strwhere = "(";
	if (cball->Checked ) {
		strwhere = strwhere + " select BS_BookCatalog.id "
		" FROM STK_BookInfo LEFT OUTER JOIN "
		" BS_BookCatalog ON STK_BookInfo.BkcatalogID = BS_BookCatalog.ID"
		" LEFT OUTER JOIN STK_BookstackInfo ON STK_BookInfo.BkstackID = STK_BookstackInfo.ID"
		" LEFT OUTER JOIN CUST_CustomerInfo ON STK_BookInfo.SupplierID = CUST_CustomerInfo.ID"
		" LEFT OUTER JOIN BS_BookType ON BS_BookCatalog.smallBookTypeID = BS_BookType.ID"
		" LEFT OUTER JOIN BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID " + sqlwhere + " )";
   }
   else
   {
   		strwhere = strwhere + aquerydisplay->FieldByName("ID")->AsAnsiString + ")";
   }

   if (edtmax->Text != "" ) {
	  MaxStock = StrToInt(edtmax->Text.Trim());
	  UpdateMode =  1;
   }
   if (edtmin->Text != "") {
	   MinStock = StrToInt(edtmin->Text.Trim());
	   UpdateMode =  2;
   }
   if (edtmin->Text != "" && edtmax->Text != "" ) {
	   UpdateMode = 3;
   }
	adosp->ProcedureName = "UpdateMaxMinStock";
	adosp->Parameters->Clear();
	adosp->Parameters->CreateParameter("@Modal",ftInteger ,pdInput,sizeof(int), &UpdateMode);
	adosp->Parameters->CreateParameter("@MaxStock",ftInteger ,pdInput,sizeof(int), &MaxStock);
	adosp->Parameters->CreateParameter("@MinStock",ftInteger ,pdInput,sizeof(int), &MinStock);
	adosp->Parameters->CreateParameter("@where",ftString  ,pdInput,strwhere.Length(), strwhere);
	adosp->ExecProc();

	MessageBoxA(0,"库存预警成功设置！","提示",MB_ICONWARNING);
	aquerydisplay->Active = false;
	aquerydisplay->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::edtisbnChange(TObject *Sender)
{
	if (edtisbn->Text != "") {
		chisbn->Checked = true;
	}
	else
	{
		chisbn->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::edtisbnKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::ednameChange(TObject *Sender)
{
	if (edname->Text != "") {
		chname->Checked = true;
	}
	else
	{
		chname->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::ednameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::edtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString sql;
		//类别
		sql = "select ID,Name from bs_bookType where Name like '%" + edtype->Text + "%'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		cbtype->Clear();
		while (!aquery->Eof)
		{
			cbtype->AddItem(aquery->FieldByName("Name")->AsAnsiString ,(TObject*)aquery->FieldByName("ID")->AsInteger );
			aquery->Next();
		}
		aquery->First();
		cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)aquery->FieldByName("ID")->AsInteger );
		cbtype->SetFocus();
		edtype->Text = "" ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::edsupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString sql;
		//供应商
		sql = "select ID,Name from CUST_CustomerInfo where type = 1 and Name like '%" + edsupplier->Text + "%'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		cbsupplier->Clear();
		while(!aquery->Eof)
		{
			cbsupplier->AddItem(aquery->FieldByName("Name")->AsAnsiString ,(TObject*)aquery->FieldByName("ID")->AsInteger );
			aquery->Next();
		}
		aquery->First();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aquery->FieldByName("ID")->AsInteger );
		cbsupplier->SetFocus();
		edsupplier->Text = "";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::edpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString sql;
		//出版商
		sql = "select ID,AbbreviatedName from BS_Pressinfo where AbbreviatedName like '%" + edpress->Text + "%'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		cbpress->Clear();
		while(!aquery->Eof)
		{
			cbpress->AddItem(aquery->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)aquery->FieldByName("ID")->AsInteger );
			aquery->Next();
		}
		aquery->First();
		cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aquery->FieldByName("ID")->AsInteger );
		cbpress->SetFocus();
		edpress->Text = "";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::cbtypeChange(TObject *Sender)
{
	if (cbtype->Text != "") {
		chtype->Checked = true;
	}
	else
	{
		chtype->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::cbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		edsupplier->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::cbpressChange(TObject *Sender)
{
	if (cbpress->Text != "") {
		chpress->Checked = true;
	}
	else
	{
		chpress->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::cbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::cbsupplierChange(TObject *Sender)
{
	if (cbsupplier->Text != "") {
		chsupplier->Checked = true;
	}
	else
	{
    	chsupplier->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmalarmSet::cbsupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

