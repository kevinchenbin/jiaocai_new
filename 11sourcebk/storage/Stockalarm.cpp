//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Stockalarm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmalarm *frmalarm;
//---------------------------------------------------------------------------
__fastcall Tfrmalarm::Tfrmalarm(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
	aquery->Connection = con;
	fstgid = stgid;
    aquery->Active = false;
	aquery->Parameters->ParamByName("stgid")->Value = fstgid;
	aquery->Active = true;
	if (aquery->IsEmpty() ) {
		Close();
		return;
	}
	query->Connection = con;
	AnsiString sql;
	sql = "select ID,Name from CUST_CustomerInfo where type = 1";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof )
	{
		cbsupplier->AddItem(query->FieldByName("Name")->AsAnsiString ,(TObject*)query->FieldByName("ID")->AsInteger );
		query->Next();
	}
	sql = "select ID,AbbreviatedName from BS_PressInfo ";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof )
	{
		cbpress->AddItem(query->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)query->FieldByName("ID")->AsInteger );
		query->Next();
	}
	sql = "select ID,Name from BS_BookType ";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof )
	{
		cbtype->AddItem(query->FieldByName("Name")->AsAnsiString ,(TObject*)query->FieldByName("ID")->AsInteger );
		query->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmalarm::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::BtnExportClick(TObject *Sender)
{
	if (!dgalarm->DataSource->DataSet->IsEmpty() ) {
		DbgridToExcel(dgalarm);
	}
}
//---------------------------------------------------------------------------
bool __fastcall Tfrmalarm::DbgridToExcel(TRzDBGrid* dbg)
{
    AnsiString temptext,path  ;

	savedlg->FileName = "库存预警";
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(savedlg->FileName .c_str()  );
		Name = ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
	else
	{
    	return false;
	}
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	while (!dbg->DataSource->DataSet ->Eof)
	{
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "name" || dbg->Columns ->Items [j-1]->FieldName == "author") {
                	AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					temptext = temptext + bookname + ",";
				}
				else
				{
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}

	dbg->DataSource ->DataSet->EnableControls();

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F8) //导出
	{
		BtnExport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==81  )
	{
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {
		BtnView->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {
		BtnAlignBottom->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::edchaochuminChange(TObject *Sender)
{
	if (edchaochumin->Text != "") {
		chchaochu->Checked = true;
	}
	else
	{
    	chchaochu->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::edchaochumaxChange(TObject *Sender)
{
	if (edchaochumax->Text != "") {
		chchaochu->Checked = true;
	}
	else
	{
		chchaochu->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::edduanqueminChange(TObject *Sender)
{
	if (edduanquemin->Text != "") {
		chduanque->Checked = true;
	}
	else
	{
    	chduanque->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::edduanquemaxChange(TObject *Sender)
{
	if (edduanquemax->Text != "") {
		chduanque->Checked = true;
	}
	else
	{
		chduanque->Checked = false;
	}
}
//---------------------------------------------------------------------------


void Tfrmalarm::Filter()
{

	AnsiString filterstr,sql;
	sql = "select cast(rank() over (order by A.id) as nvarchar(10)) as xuhao,C.Name as client,B.ISBN,B.name,B.author,B.price,A.amount,A.maxstock,A.minstock,D.Name as typename,E.AbbreviatedName,"
			" case when A.amount-A.Maxstock > 0 then A.amount-A.Maxstock else 0 end as c, "
			" case when A.minstock - a.amount > 0 then A.minstock - a.amount else 0 end as d from STK_BookInfo A left join BS_BookCatalog B "
			" on A.bkcatalogID = B.ID  "
			" left join CUST_CustomerInfo C on A.supplierid = C.ID  "
			" left join BS_BookType D ON B.smallBookTypeID = D.id "
			" left join BS_PressInfo E on B.PressID = E.id "
			" where A.stgid = " + IntToStr(fstgid) + " and (A.amount > A.Maxstock or A.amount < A.minstock) and (A.Maxstock <> 0 or A.minstock <> 0)";
	if (chchaochu->Checked ) {
		if (edchaochumin->Text != "" && edchaochumin->Text != "0") {
			filterstr = " and A.amount-A.Maxstock >= " + edchaochumin->Text ;
		}
		if (edchaochumax->Text != "" && edchaochumax->Text != "0") {
			filterstr = filterstr + " and A.amount-A.Maxstock <= " + edchaochumax->Text ;
		}
	}
	if (chduanque->Checked ) {
		if (edduanquemin->Text != "" && edduanquemin->Text != "0") {
			filterstr = filterstr + " and A.minstock - a.amount >= " + edduanquemin->Text ;
		}
		if (edduanquemax->Text != "" && edduanquemax->Text != "0") {
			filterstr = filterstr + " and A.minstock - a.amount <= " + edduanquemax->Text ;
		}
	}
	if (chsupplier->Checked && cbsupplier->Text != "") {
		filterstr = filterstr + " and C.Name = '" + cbsupplier->Text + "'";
	}
	if (chpress->Checked && cbpress->Text != "") {
		filterstr = filterstr + " and E.AbbreviatedName = '" + cbpress->Text + "'";
	}
	if (chtype->Checked && cbtype->Text != "") {
		filterstr = filterstr + " and D.Name = '" + cbtype->Text + "'";
	}
	sql = sql +  filterstr;
	sql = sql + " union "
			" select '合计',null,null,null,null,null,null,null,null,null,null, "
			" sum(case when A.amount-A.Maxstock > 0 then A.amount-A.Maxstock else 0 end) as c,"
			" sum(case when A.minstock - a.amount > 0 then A.minstock - a.amount else 0 end) as d from STK_BookInfo A left join BS_BookCatalog B "
			" on A.bkcatalogID = B.ID "
			" left join CUST_CustomerInfo C on A.supplierid = C.ID "
			" left join BS_BookType D ON B.smallBookTypeID =	D.id "
			" left join BS_PressInfo E on B.PressID = E.id "
			" where (A.amount > A.Maxstock or A.amount < A.minstock) "
			" and (A.Maxstock <> 0 or A.minstock <> 0) " + filterstr;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();

}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type = 1 and name like '%" + edquery->Text.Trim() + "%'";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		cbsupplier->Clear();
		while (!query->Eof )
		{
			cbsupplier->AddItem(query->FieldByName("Name")->AsAnsiString ,(TObject*)query->FieldByName("ID")->AsInteger );
			query->Next();
		}
		query->First();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)query->FieldByName("ID")->AsInteger);
        cbsupplier->SetFocus();
		edquery->Text = "";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::edpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
    	AnsiString sql;
		sql = "select ID,AbbreviatedName from BS_PressInfo where  AbbreviatedName like '%" + edpress->Text.Trim() + "%'";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		cbpress->Clear();
		while (!query->Eof )
		{
			cbpress->AddItem(query->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)query->FieldByName("ID")->AsInteger );
			query->Next();
		}
		query->First();
		cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)query->FieldByName("ID")->AsInteger);
        cbpress->SetFocus();
		edpress->Text = "";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::cbsupplierChange(TObject *Sender)
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

void __fastcall Tfrmalarm::cbpressChange(TObject *Sender)
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

void __fastcall Tfrmalarm::cbtypeChange(TObject *Sender)
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

void __fastcall Tfrmalarm::BtnViewClick(TObject *Sender)
{
	Filter();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::cbsupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::cbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        cbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::cbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edchaochumin->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::edchaochuminKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edchaochumax->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::edchaochumaxKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edduanquemin->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::edduanqueminKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edduanquemax->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmalarm::edduanquemaxKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
    	Filter();
	}
}
//---------------------------------------------------------------------------

