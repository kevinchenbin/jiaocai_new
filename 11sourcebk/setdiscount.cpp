//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "setdiscount.h"
#include "SetTongyi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmsetdiscount *frmsetdiscount;
//---------------------------------------------------------------------------
__fastcall Tfrmsetdiscount::Tfrmsetdiscount(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
	fstgid = stgid;
	fcon = con;
	query->Connection = con;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	AnsiString sql;
	sql = "select ID,Name from BS_BookType";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbtype->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	sql = "select ID,AbbreviatedName from BS_PressInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	sql = "select ID,Name from CUST_CustomerInfo where type = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsetdiscount::BtnViewClick(TObject *Sender)
{
	AnsiString sql;
	sql = "select A.id,A.BkInfoID,wsalediscount,wsaleprice,lsdiscount,lsprice,Discount,BS_BookCatalog.Price,BS_BookCatalog.ISBN,BS_BookCatalog.Name, "
			" CUST_CustomerInfo.Name as suppliername,BS_BookType.Name as typename,BS_PressInfo.AbbreviatedName from "
			" (select max(BS_StorageNote_attachment.id) as id,BS_StorageNote_attachment.BkInfoID "
			" from BS_StorageNote_attachment group by BS_StorageNote_attachment.BkInfoID) A "
			" join BS_StorageNote_attachment on A.id = BS_StorageNote_attachment.id "
			" join BS_StorageNote on BS_StorageNote_attachment.BS_StorageNoteID = BS_StorageNote.id "
			" join STK_BookInfo on A.BkInfoID = STK_BookInfo.ID "
			" left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.id "
			" left join CUST_CustomerInfo on STK_BookInfo.SupplierID = CUST_CustomerInfo.id "
			" left join BS_BookType on  BS_BookCatalog.smallBookTypeID = BS_BookType.id "
			" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id where STK_BookInfo.stgid = " + IntToStr(fstgid) ;
	if (chisbn->Checked && edisbn->Text != "") {
		sql = sql + " and BS_BookCatalog.ISBN like '%" + edisbn->Text.Trim() + "%'";
	}
	if (chname->Checked && edname->Text != "") {
		sql = sql + " and BS_BookCatalog.Name like '%" + edname->Text.Trim() + "%'";
	}
	if (chtype->Checked && cbtype->Text != "") {
		int type;
		try {
			type = (int)cbtype->Items->Objects[cbtype->ItemIndex];
		} catch (...) {
			MessageBox(0,"请选择正确的类别！","提示" ,MB_ICONINFORMATION);
			return;
		}
		sql = sql + " and BS_BookCatalog.smallBookTypeID = " + IntToStr(type);
	}
	if (chpress->Checked && cbpress->Text != "") {
		int pressid;
		try {
			pressid = (int)cbpress->Items->Objects[cbpress->ItemIndex];
		} catch (...) {
			MessageBox(0,"请选择正确的出版社！","提示" ,MB_ICONINFORMATION);
			return;
		}
		sql = sql + " and BS_BookCatalog.PressID = " + IntToStr(pressid);
	}
	if (chsupplier->Checked && cbsupplier->Text != "") {
		int supplierid;
		try {
			supplierid = (int)cbsupplier->Items->Objects[cbsupplier->ItemIndex];
		} catch (...) {
			MessageBox(0,"请选择正确的供应商！","提示" ,MB_ICONINFORMATION);
			return;
		}
		sql = sql + " and STK_BookInfo.SupplierID = " + IntToStr(supplierid);
	}
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsetdiscount::BtnDeleteRecordClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsetdiscount::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsetdiscount::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsetdiscount::edpressqueryKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		AnsiString sql;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		sql = "select ID,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + edpressquery->Text.Trim() + "%'" ;
        aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbpress->Items->Clear();
        while (!aq->Eof )
		{
			cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsetdiscount::edsupplierqueryKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		AnsiString sql;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		sql = "select ID,Name from CUST_CustomerInfo where type = 1 and Name like '%" + edsupplierquery->Text.Trim() + "%'" ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbsupplier->Items->Clear();
        while (!aq->Eof )
		{
			cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsetdiscount::edisbnChange(TObject *Sender)
{
	if (edisbn->Text != "") {
		chisbn->Checked = true;
	}
	else
	{
		chisbn->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsetdiscount::ednameChange(TObject *Sender)
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

void __fastcall Tfrmsetdiscount::cbtypeChange(TObject *Sender)
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

void __fastcall Tfrmsetdiscount::cbpressChange(TObject *Sender)
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

void __fastcall Tfrmsetdiscount::cbsupplierChange(TObject *Sender)
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

void __fastcall Tfrmsetdiscount::edpxdiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
		Key = NULL;
	}
	if (Key == '\r') {
    	if (query->IsEmpty() ) {
        	return;
		}
		if (edpxdiscount->Text != "") {
			float pxdiscount;
			try {
				pxdiscount = StrToFloat(edpxdiscount->Text);
				edpxprice->Text = FormatFloat("0.00",pxdiscount*query->FieldByName("Price")->AsFloat/100);
			} catch (...) {
				MessageBox(0,"请输入正确的批销折扣！","提示" ,MB_ICONINFORMATION);
				edpxdiscount->SetFocus();
			}
		}
        edpxprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsetdiscount::edpxpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
		Key = NULL;
	}
	if (Key == '\r') {
    	if (query->IsEmpty() ) {
			return;
		}
		if (edpxprice->Text != "") {
			float pxprice;
			try {
				pxprice = StrToFloat(edpxprice->Text);
				edpxdiscount->Text = FormatFloat("0.00",pxprice*100/query->FieldByName("Price")->AsFloat);
			} catch (...) {
				MessageBox(0,"请输入正确的批销价格！","提示" ,MB_ICONINFORMATION);
				edpxprice->SetFocus();
			}
		}
		edlsdiscount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsetdiscount::edlsdiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
		Key = NULL;
	}
	if (Key == '\r') {
    	if (query->IsEmpty() ) {
			return;
		}
		if (edlsdiscount->Text != "") {
			float lsdiscount;
			try {
				lsdiscount = StrToFloat(edlsdiscount->Text);
				edlsprice->Text = FormatFloat("0.00",lsdiscount*query->FieldByName("Price")->AsFloat/100);
			} catch (...) {
				MessageBox(0,"请输入正确的零售折扣！","提示" ,MB_ICONINFORMATION);
				edlsdiscount->SetFocus();
			}
		}
		edlsprice->SetFocus();
	}
}
//---------------------------------------------------------------------------




void __fastcall Tfrmsetdiscount::edlspriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
		Key = NULL;
	}
	if (Key == '\r') {
    	if (query->IsEmpty() ) {
			return;
		}
		if (edlsprice->Text != "") {
			float lsprice;
			try {
				lsprice = StrToFloat(edlsprice->Text);
				edlsdiscount->Text = FormatFloat("0.00",lsprice*100/query->FieldByName("Price")->AsFloat);
			} catch (...) {
				MessageBox(0,"请输入正确的零售价格！","提示" ,MB_ICONINFORMATION);
				edlsprice->SetFocus();
			}
		}
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------



void __fastcall Tfrmsetdiscount::BtnSaveClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	if(MessageBox(0,"确认保存？","确认" ,MB_ICONQUESTION|MB_OKCANCEL)!=1) {
		return;
	}
	if (edlsdiscount->Text != "") {
		float lsdiscount;
		try {
			lsdiscount = StrToFloat(edlsdiscount->Text);
		} catch (...) {
			MessageBox(0,"请输入正确的零售折扣！","提示" ,MB_ICONINFORMATION);
			edlsdiscount->SetFocus();
			return;
		}
	}
	else
	{
    	edlsdiscount->Text = "100";
	}
	if (edlsprice->Text != "") {
		float lsprice;
		try {
			lsprice = StrToFloat(edlsprice->Text);
		} catch (...) {
			MessageBox(0,"请输入正确的零售价格！","提示" ,MB_ICONINFORMATION);
			edlsprice->SetFocus();
			return;
		}
	}
	else
	{
		edlsprice->Text = "100";
	}
	if (edpxprice->Text != "") {
		float pxprice;
		try {
			pxprice = StrToFloat(edpxprice->Text);
		} catch (...) {
			MessageBox(0,"请输入正确的批销价格！","提示" ,MB_ICONINFORMATION);
			edpxprice->SetFocus();
			return;
		}
	}
	else
	{
		edpxprice->Text = "100";
	}
	if (edpxdiscount->Text != "") {
		float pxdiscount;
		try {
			pxdiscount = StrToFloat(edpxdiscount->Text);
		} catch (...) {
			MessageBox(0,"请输入正确的批销折扣！","提示" ,MB_ICONINFORMATION);
			edpxdiscount->SetFocus();
			return;
		}
	}
	else
	{
    	edpxdiscount->Text = "100";
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql ;
	sql = "update BS_StorageNote_attachment set wsalediscount = " + edpxdiscount->Text + ",wsaleprice = " + edpxprice->Text + ",lsdiscount = " +
			edlsdiscount->Text + ",lsprice = " + edlsprice->Text + " where id = " + query->FieldByName("id")->AsAnsiString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = query->FieldByName("id")->AsAnsiString ;
	query->Active = false;
	query->Active = true;
	query->Locate("id",str,Opts);
	delete aq;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmsetdiscount::BtnChangeOptionsClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	TfrmSetTongyi *frm = new TfrmSetTongyi(Application);
	if (frm->ShowModal() == mrOk ) {
		float pxdiscount = 0.00;
		float lsdiscount = 0.00;
		bool yjpx = frm->Getpxdiscount(pxdiscount);
		bool yjls = frm->Getlsdiscount(lsdiscount);
		BatchSetNotes(pxdiscount,lsdiscount,yjpx,yjls);
	}
}
//---------------------------------------------------------------------------

void Tfrmsetdiscount::BatchSetNotes(float pxdiscount,float lsdiscount,bool yjpx,bool yjls)
{
	String ids = "";
	if (dg->SelectedRows->Count == 0)
	{
		ids = ids + query->FieldByName("id")->AsString;
	}
	else if (dg->SelectedRows->Count > 0)
	{
		query->Bookmark = dg->SelectedRows->Items[0];
		ids = query->FieldByName("id")->AsString;
		for (int i=1; i < dg->SelectedRows->Count; i++)
		{
			query->Bookmark = dg->SelectedRows->Items[i];
			ids = ids + "," + query->FieldByName("id")->AsString;
		}
	}
	else
		return;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql ;
	if (yjpx && yjls) {
		sql = "update BS_StorageNote_attachment set wsalediscount = " + FloatToStr(pxdiscount) + ",lsdiscount = " + FloatToStr(lsdiscount)+ " where id in (" + ids + ")";
	}
	else if (yjpx) {
		sql = "update BS_StorageNote_attachment set wsalediscount = " + FloatToStr(pxdiscount) + " where id in (" + ids + ")";
	}
	else if (yjls) {
		sql = "update BS_StorageNote_attachment set lsdiscount = " + FloatToStr(lsdiscount)+ " where id in (" + ids + ")";
	}
	else
    	return;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = query->FieldByName("id")->AsAnsiString ;
	query->Active = false;
	query->Active = true;
	query->Locate("id",str,Opts);
}
void __fastcall Tfrmsetdiscount::dgCellClick(TColumn *Column)
{
	if (query->IsEmpty() ) {
    	return;
	}
	try {
		if (query->FieldByName("wsalediscount")->AsAnsiString == "" || query->FieldByName("wsalediscount")->AsAnsiString == "0") {
        	edpxdiscount->Text = "0";
			edpxprice->Text = "0.00";
		}
		else
		{
        	edpxdiscount->Text = FormatFloat("0.00",query->FieldByName("wsalediscount")->AsFloat );
			edpxprice->Text = FormatFloat("0.00",query->FieldByName("Price")->AsFloat * 100 / query->FieldByName("wsalediscount")->AsFloat );
		}

		if (query->FieldByName("lsdiscount")->AsAnsiString == "" || query->FieldByName("lsdiscount")->AsAnsiString == "0") {
        	edlsdiscount->Text = "0";
			edlsprice->Text = "0.00";
		}
		else
		{
        	edlsdiscount->Text = FormatFloat("0.00",query->FieldByName("lsdiscount")->AsFloat );
			edlsprice->Text = FormatFloat("0.00",query->FieldByName("Price")->AsFloat * 100 / query->FieldByName("lsdiscount")->AsFloat );
		}
	} catch (...) {
	}
}
//---------------------------------------------------------------------------


