//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "catalogbuilt.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
Tfrmcatalogbuit *frmcatalogbuit;
//---------------------------------------------------------------------------
__fastcall Tfrmcatalogbuit::Tfrmcatalogbuit(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	aq->Connection = con;
	query->Connection = con;
	AnsiString sql;
	sql = "select ID,Name from BS_BookType";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
        cbtype->AddItem(aq->FieldByName("Name")->AsString,(TObject *)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	sql = "select ID,AbbreviatedName from BS_PressInfo ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString,(TObject *)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString sql;
		sql = "select ID,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + edquery->Text + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbpress->Clear();
		while (!aq->Eof )
		{
        	cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString,(TObject *)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject *)aq->FieldByName("ID")->AsInteger );
		cbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------
void  Tfrmcatalogbuit::Query()
{
	AnsiString sql,sqlwhere;
	sql = "select RANK() OVER(order by BS_BookCatalog.id) as xuhao,BS_BookCatalog.Name,ISBN,UserDefCode,Price,Author,Pressdate,PressCount,BS_BookType.Name as typename,BS_PressInfo.AbbreviatedName ";
	if (chbookinfo->Checked ) {
		sql = sql + ",sum(STK_BookInfo.amount) as amount ";
	}
	else
	{
    	sql = sql + ", 0 as amount ";
	}
	sql = sql + " from BS_BookCatalog left join BS_BookType on BS_BookCatalog.smallBookTypeID = BS_BookType.id ";
	sql = sql + " left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id ";
	if (chbookinfo->Checked ) {
		sql = sql + " right join STK_BookInfo on STK_BookInfo.BkcatalogID = BS_BookCatalog.id ";
	}
	sql = sql + " where BS_BookCatalog.type = " + IntToStr(rg->ItemIndex);
	if (chisbn->Checked) {
		sql = sql + " and (BS_BookCatalog.ISBN like '%" + edisbn->Text + "%' or BS_BookCatalog.Barcode like '%" + edisbn->Text + "%') ";
	}
	if (chname->Checked ) {
		sql = sql + " and BS_BookCatalog.Name like '%" + edname->Text + "%'";
	}
	if (chuserdef->Checked ) {
		sql = sql + " and BS_BookCatalog.UserDefCode like '%" + eduserdef->Text + "%'";
	}
	if (chauthor->Checked ) {
		sql = sql + " and BS_BookCatalog.Author like '%" + edauthor->Text + "%'";
	}
	if (chprice->Checked ) {
		if (edminprice->Text != "") {
			sql = sql + " and BS_BookCatalog.Price >= " + edminprice->Text;
		}
		if (edmaxprice->Text != "") {
			sql = sql + " and BS_BookCatalog.Price <= " + edmaxprice->Text ;
		}
	}
	if (chtype->Checked ) {
		sql = sql + " and BS_BookType.Name = '" + cbtype->Text + "'";
	}
	if (chpress->Checked ) {
		sql = sql + " and BS_PressInfo.AbbreviatedName = '" + cbpress->Text + "'";
	}
	sql = sql + " group by BS_BookCatalog.id,BS_BookCatalog.Name,BS_BookCatalog.ISBN,BS_BookCatalog.UserDefCode,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookCatalog.Pressdate,PressCount,BS_BookType.Name,BS_PressInfo.AbbreviatedName";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	try {
		query->Open();
	} catch (Exception &E) {
    	ShowMessage(E.Message);
		return;
	}
	if (chbookinfo->Checked) {
		DBGridEh1->Columns->Items[10]->Visible = true;
		DBGridEh1->Columns->Items[10]->Field = query->FieldByName("amount");
		DBGridEh1->Columns->Items[10]->Footer->ValueType = fvtSum ;

	}
	else
	{
		DBGridEh1->Columns->Items[10]->Visible = false;
		DBGridEh1->Columns->Items[10]->Field = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::BtnViewClick(TObject *Sender)
{
	Query();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::edminpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  	Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogbuit::edmaxpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogbuit::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::BtnExportClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	DbgridToExcel(DBGridEh1);
}
//---------------------------------------------------------------------------
//Excel导出函数
bool Tfrmcatalogbuit::DbgridToExcel(TDBGridEh* dbg)
{
	AnsiString temptext,path,s;
	//TStrings* ss = new TStringList();
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(savedlg->FileName .c_str()  );
		Name = ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
	//path =  ExtractFilePath(Application->ExeName) + "catalog.csv";
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	int count =0,row =0,col =0;
	if(k == 0)
	{
		MessageBox(0,"没有数据！","错误确认" ,MB_OK);
		return false;
	}
	/*Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	v.OlePropertyGet("Cells",1,5).OlePropertySet("Value","目录制作" ); */
   //	s = ",,,,目录制作";
   //	ss->Text = s;
   //	ss->SaveToFile(path);
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	else
		iFileHandle = FileCreate(path.c_str());





	if (rg->ItemIndex == 0) {
		temptext = "图书";
	}
	else if (rg->ItemIndex == 1) {
		temptext = "期刊";
	}
	else
	{
		temptext = "文具";
	}
	/*v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","经营类型" );
	v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
	count ++;
	if (chisbn->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","书号" );
		temptext = "'"+ edisbn->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}

	if (chname->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","书名" );
		temptext = "'"+ edname->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}

	if (chuserdef->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","自编码" );
		temptext = "'"+ eduserdef->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}

	if (chauthor->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","作者" );
		temptext = "'"+ edauthor->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}

	if (chtype->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","类别" );
		temptext = "'"+ cbtype->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}

	if (chpress->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","版别" );
		temptext = "'"+ cbpress->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}

	if (chprice->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","定价" );
		temptext = "'>="+ edminprice->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		temptext = "'<="+ edmaxprice->Text;
		v.OlePropertyGet("Cells",3+row,3*col+3).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}    */

	if (count == 0) {
		n = 2;
	}
	else if (count%4 == 0) {
		n = 3+count/4;
	}
	else if (count%4 != 0){
		n = 4+count/4;
	}


	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			//t1++;
			//temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			//v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			//v.OlePropertyGet("Cells",1+n,t1).OleFunction("BorderAround",1,2,1);
			temptext = dbg->Columns ->Items [q]->Title ->Caption + ",";
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		}
	}
	temptext = "\n";
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());


	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet->DisableControls();
	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				//t1++;
				//temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->DisplayText ;
				//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				//v.OlePropertyGet("Cells",i,t1).OleFunction("BorderAround",1,2,1);
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					temptext = "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->DisplayText + ",";
				}
				else
				{
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->DisplayText + ",";
                }
				iFileLength   =   FileSeek(iFileHandle,0,2);
				FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
		temptext = "\n";
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
	}
	dbg->DataSource ->DataSet->EnableControls();

	t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		/*if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			v.OlePropertyGet("Cells",t2+2+n,t1).OleFunction("BorderAround",1,2,1);
		} */
	}
	t1 = 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		/*if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->GetFooterValue(0,dbg->Columns->Items[q]);
			v.OlePropertyGet("Cells",t2+2+n,t1).OlePropertySet("Value",temptext .c_str() );
		}*/
	}
	FileClose(iFileHandle);
    MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::edisbnChange(TObject *Sender)
{
	if (edisbn->Text == "") {
		chisbn->Checked = false;
	}
	else
	{
    	chisbn->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::edauthorChange(TObject *Sender)
{
	if (edauthor->Text == "") {
		chauthor->Checked = false;
	}
	else
	{
    	chauthor->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::cbtypeChange(TObject *Sender)
{
	if (cbtype->Text == "") {
		chtype->Checked = false;
	}
	else
	{
    	chtype->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::ednameChange(TObject *Sender)
{
	if (edname->Text == "") {
		chname->Checked = false;
	}
	else
	{
    	chname->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::eduserdefChange(TObject *Sender)
{
	if (eduserdef->Text == "") {
		chuserdef->Checked = false;
	}
	else
	{
    	chuserdef->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::cbpressChange(TObject *Sender)
{
	if (cbpress->Text == "") {
		chpress->Checked = false;
	}
	else
	{
    	chpress->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::edminpriceChange(TObject *Sender)
{
	if (edminprice->Text == "") {
		chprice->Checked = false;
	}
	else
	{
		chprice->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::edmaxpriceChange(TObject *Sender)
{
	if (edmaxprice->Text == "") {
		chprice->Checked = false;
	}
	else
	{
    	chprice->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogbuit::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogbuit::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == 117) {   //导出
		BtnExport->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 70 ) {    //查询
		BtnView->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogbuit::DBGridEh1TitleClick(TColumnEh *Column)
{
	if (query->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (query->Sort == "") {
		query->Sort =  Column->FieldName + " ASC";
	}
	else if (query->Sort == qusort) {
		query->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		query->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

