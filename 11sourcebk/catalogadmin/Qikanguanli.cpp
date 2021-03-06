//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Qikanguanli.h"
#include "ExcelImport.h"
#include "BookQuery.h"
#include "PressAdminForm.h"
#include "BooKTypeAdminForm.h"
#include "Setunite.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma link "RzRadChk"
#pragma link "RzEdit"
#pragma link "RzLine"
#pragma link "RzRadGrp"
#pragma link "RzLabel"
#pragma link "RzSpnEdt"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TfrmQikanguanli *frmQikanguanli;
//---------------------------------------------------------------------------
__fastcall TfrmQikanguanli::TfrmQikanguanli(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	query->Connection = con;
	aqinsert->Connection = con;
	addqikan->Connection = con;
	aquery->Connection = con;
	fcon = con;
	ReadyData();
	int maxid;
	AnsiString sql;
	sql = "select max(id) as id from BS_BookCatalog " ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	maxid = query->FieldByName("id")->AsInteger + 1;
	sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,"
		 "A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,A.kanzhong,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(maxid) ;

	sql = sql + " and A.type = 1";

	aqinsert->Close();
	aqinsert->SQL->Clear();
	aqinsert->SQL->Add(sql);
	aqinsert->Open();
	modle = 1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmQikanguanli::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmQikanguanli::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
String  TfrmQikanguanli:: GetID()
{
	return ID;
}
//---------------------------------------------------------------------------
char TfrmQikanguanli::GetPYIndexChar(char *str)
{
	Word x = 0;
	Word y = 0;//int y = 0;
	//x = StrToInt()

	x = (int(str[0]))<<8;
	y = (int(str[1]))<<8;
	y = y>>8;
	x = x + y;//str[1];
	Word Address[] = { 0xB0C4,0xB2C0,0xB4ED,0xB6E9,0xB7A1,
	0xB8C0,0xB9FD,0xBBF6,0xBFA5,0xC0AB,
	0xC2E7,0xC4C2,0xC5B5,0xC5BD,0xC6D9,
	0xC8BA,0xC8F5,0xCBF9,0xCDD9,0xCEF3,
	0xD188,0xD4D0,0xD7F9 };
	char Rchar[25] = "ABCDEFGHJKLMNOPQRSTWXYZ ";
	int i=0;
	for(;i<24;i++)
	if(Address[i] >= x) break;
	return Rchar[i];
}
//---------------------------------------------------------------------------

void TfrmQikanguanli::Query(String condition)
{
	if (aqinsert->Active)
	{
		aqinsert->Active = false;
	}
	String sql;
	sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,"
			"A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,A.kanzhong,"
			"B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
			" on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID " + condition + " and type = 1";
	aqinsert->Close();
	aqinsert->SQL->Clear();
	aqinsert->SQL->Add(sql);
	aqinsert->Active = true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmQikanguanli::BtnNewClick(TObject *Sender)
{
	int maxid;
	AnsiString sql;
	sql = "select max(id) as id from BS_BookCatalog " ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	maxid = query->FieldByName("id")->AsInteger + 1;
	sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,"
		 "A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,A.kanzhong,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(maxid) ;

	sql = sql + " and A.type = 1";
	aqinsert->Close();
	aqinsert->SQL->Clear();
	aqinsert->SQL->Add(sql);
	aqinsert->Active = true;

	editqikanissn->Text ="";
	editqikanname->Text = "";
	editqikanself->Text = "";
	editqikanprice->Text="0.00";
	editqikanmao->Text= "";
	editqikanqihao->Text="";
	rcbtype->Text = "";
	chduokan->Checked = false;
	cbduokan->ItemIndex = 0;
	cbduokan->Visible = false;
	sedkannum->Value = 1;
	sedkannum->Visible = false;
	Label3->Visible = false;
	edyearprice->Text = "0.00";
	edkanhao->Text = "";
	edtykanhao->Text = "";
	cbyoufa->Text = "";
	youfacode->Text = "";
	edpressarea->Text = "";
	bk->Text = "";
	cbkanzhong->ItemIndex = 0;
	Press(0);

	editqikanmao->SetFocus();

	BtnClear->Enabled = false;
	BtnCancel->Enabled = false;
	BtnDelete->Enabled = false;
	BtnImport->Enabled = false;
	BtnExport->Enabled = false;
	BtnNew->Enabled = false;
	BtnJumptoLine->Enabled = false;
	BtnSave->Enabled = true;

	pcqikan->Enabled = true;

	modle = 1;
}
//---------------------------------------------------------------------------


void __fastcall TfrmQikanguanli::BtnClearClick(TObject *Sender)
{
	//  修改模式
	if (aqinsert->IsEmpty() ) {
		return;
	}
	modle = 2;
	BtnClear->Enabled = false;
	BtnCancel->Enabled = false;
	BtnDelete->Enabled = false;
	BtnImport->Enabled = false;
	BtnExport->Enabled = false;
	BtnNew->Enabled = false;
	BtnJumptoLine->Enabled = false;
	BtnSave->Enabled = true;

	pcqikan->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::radiogroupClick(TObject *Sender)
{
	AnsiString sql;
	modle = 0;
	if (radiogroup->ItemIndex == 0) {
		try {
			aqinsert->Active = false;
			return;
		} catch (...) {
		}
	}
	else if (radiogroup->ItemIndex == 1) {
		sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,"
		 "A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,A.kanzhong,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.type = 1 ";
	}
	else if (radiogroup->ItemIndex == 2) {
		sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,"
		 "A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,A.kanzhong,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.type = 1 and Unavailable = 0";
	}
	else if (radiogroup->ItemIndex == 3) {
		sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,"
		 "A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,A.kanzhong,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.type = 1 and Unavailable = 1";
	}
    aqinsert->Close();
	aqinsert->SQL->Clear();
	aqinsert->SQL->Add(sql);
	aqinsert->Active = true;

	editqikanissn->Text ="";
	editqikanname->Text = "";
	editqikanself->Text = "";
	editqikanprice->Text="0.00";
	editqikanmao->Text= "";
	editqikanqihao->Text="";
	rcbtype->Text = "";
	chduokan->Checked = false;
	cbduokan->ItemIndex = 0;
	cbduokan->Visible = false;
	sedkannum->Value = 1;
	sedkannum->Visible = false;
	Label3->Visible = false;
	edyearprice->Text = "0.00";
	edkanhao->Text = "";
	edtykanhao->Text = "";
	cbyoufa->Text = "";
	youfacode->Text = "";
	edpressarea->Text = "";
	bk->Text = "";
	Press(0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::BtnCancelClick(TObject *Sender)
{
	if (!aqinsert->IsEmpty() ) {
		for (int i=0; i < dg->SelectedRows->Count; i++) {
			aqinsert->GotoBookmark(dg->SelectedRows->Items[i]);
			aqinsert->Edit();
			aqinsert->FieldByName("Unavailable")->Value = 0;
			aqinsert->UpdateBatch(arCurrent);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::BtnDeleteClick(TObject *Sender)
{
	AnsiString sql,ids;
	if (aqinsert->IsEmpty()) {
		return;
	}

	if (!aqinsert->IsEmpty()) {
		if (MessageBox(0,"确认要删除吗？","警告" ,MB_ICONQUESTION||MB_OKCANCEL)==1)
		{
			if (dg->SelectedRows->Count == 0)
			{
				ids = ids + aqinsert->FieldByName("ID")->AsString;
			}
			else if (dg->SelectedRows->Count > 0)
			{
				aqinsert->Bookmark = dg->SelectedRows->Items[0];
				ids = aqinsert->FieldByName("ID")->AsString;
				for (int i=1; i < dg->SelectedRows->Count; i++)
				{
					aqinsert->Bookmark = dg->SelectedRows->Items[i];
					ids = ids + "," + aqinsert->FieldByName("ID")->AsString;
				}
			}
			TADOQuery *aq = new TADOQuery(this);
			aq->Connection = fcon;
			AnsiString sql;
			sql = "delete from BS_BookCatalog where id in (" + ids + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			delete aq;
			aqinsert->Active = false;
			aqinsert->Active = true;
		}
	}

	editqikanissn->Text ="";
	editqikanname->Text = "";
	editqikanself->Text = "";
	editqikanprice->Text="0.00";
	editqikanmao->Text= "";
	editqikanqihao->Text="";
	rcbtype->Text = "";
	chduokan->Checked = false;
	cbduokan->ItemIndex = 0;
	cbduokan->Visible = false;
	sedkannum->Value = 1;
	sedkannum->Visible = false;
	Label3->Visible = false;
	edyearprice->Text = "0.00";
	edkanhao->Text = "";
	edtykanhao->Text = "";
	cbyoufa->Text = "";
	youfacode->Text = "";
	edpressarea->Text = "";
	bk->Text = "";
	Press(0);

	editqikanmao->SetFocus();
}
//---------------------------------------------------------------------------

int __fastcall TfrmQikanguanli::BrocodeToPress(String brocode)
{
	if (brocode.Length() != 13 ) {
		return -1;
	}
	String tmp = brocode.SubString(5,1),pressnum;
	int bit = StrToInt(tmp);
	switch (bit) {
		case 0:
			pressnum =  brocode.SubString(4,3);
			break;
		case 1:
		case 2:
		case 3:
			pressnum =  brocode.SubString(4,4);
			break;
		case 5:
		case 6:
		case 7:
			pressnum =  brocode.SubString(4,5);
			break;
		case 8:
			pressnum =  brocode.SubString(4,6);
			break;
	default:
		;
	}
	AnsiString sql;
	sql = "select ID from BS_PressInfo where PresentNum like '%" + pressnum + "%'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	int pressid = query->FieldByName("ID")->AsInteger ;
	return pressid;
}


void __fastcall TfrmQikanguanli::FormShow(TObject *Sender)
{
  //	edtQuery->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::BtnExportClick(TObject *Sender)
{
	if (aqinsert->IsEmpty() ) {
		return;
	}
	DbgridToExcel(dg);
}
//---------------------------------------------------------------------------

//Excel导出函数
bool __fastcall TfrmQikanguanli::DbgridToExcel(TDBGridEh* dbg)
{
	AnsiString temptext,path,ss;
	savedlg->FileName = "期刊品目管理";
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(savedlg->FileName .c_str()  );
		Name = ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
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

	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;
	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	while(!dbg->DataSource ->DataSet->Eof )
	{
		//t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {

				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN" || dbg->Columns ->Items [j-1]->FieldName == "kanhao") {
					temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "name") {
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
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();
	FileClose(iFileHandle);
	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmQikanguanli::BtnImportClick(TObject *Sender)
{
    /*int maxid;
	AnsiString sql;
	sql = "select max(id) as id from BS_BookCatalog " ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	ds->DataSet = NULL;
	maxid = query->FieldByName("id")->AsInteger + 1;
	sql = "select A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,"
		  "A.Yizhe,A.Pressdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,A.taoshu,"
		  "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		  " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(maxid) ;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Active = true;
	TfrmExcelImport* frm = new TfrmExcelImport(Owner,aquery);
	frm->Init(Application,fcon);
	if (frm->ShowModal() == mrOk)
	{

	}
	delete frm;
	ds->DataSet = aquery;    */
}
//---------------------------------------------------------------------------


void __fastcall TfrmQikanguanli::BtnViewClick(TObject *Sender)
{
	TfrmBookQuery *frm = new  TfrmBookQuery(Application,fcon);
	if (mrOk == frm->ShowModal()) {
		//int type = frm->cbQueryType->ItemIndex ;
		String Condition = frm->getcontion();
		Query(Condition);
	}
	delete frm;
	modle = 0;
	BtnClear->Enabled = true;
	BtnCancel->Enabled = true;
	BtnDelete->Enabled = true;
	BtnImport->Enabled = true;
	BtnExport->Enabled = true;
	BtnNew->Enabled = true;

	BtnSave->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmQikanguanli::editqikanmaoKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		if (editqikanmao->Text != "") {
			if (editqikanmao->Text.Length() >= 13 ) {
				editqikanqihao->Text = editqikanmao->Text.SubString(14,editqikanmao->Text.Length()-13);
                editqikanmao->Text = editqikanmao->Text.SubString(0,13);
			}
			else if (editqikanmao->Text.Length() != 13) {
				MessageBoxA(0,"请输入正确的条码","提示",MB_ICONASTERISK);
				return;
			}
			editqikanissn->Text = BarCodeToISSN(editqikanmao->Text.Trim());
		}
		editqikanqihao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::editqikanqihaoKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		if (editqikanqihao->Text == "") {
			editqikanqihao->SetFocus();
			MessageBoxA(0,"期号必须录入!","提示",MB_ICONASTERISK);
			return;
		}
    	sedyear->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::editqikannameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		if (editqikanname->Text == "") {
			MessageBoxA(0,"请输入期刊名!","警告",MB_ICONASTERISK);
			return;
		}
		editqikanself->Text = GetSelf(editqikanname->Text.Trim() );
		editqikanself->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::editqikanissnKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		if (editqikanissn->Text.Length() < 8  )
		{
			MessageBoxA(0,"请输入正确的ISSN编号","提示",MB_ICONASTERISK);
			return;
		}
		if (editqikanissn->Text != "" && editqikanmao->Text == "") {
			editqikanmao->Text = ISSNToBarCode(editqikanissn->Text.Trim() )  ;
		}
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::editqikanpriceKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == VK_RETURN) {
		if (editqikanprice->Text=="￥0.00" || editqikanprice->Text == "") {
			MessageBoxA(0,"请输入定价!","警告",MB_ICONASTERISK);
			return;
		}
		rcbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

AnsiString TfrmQikanguanli::GetSelf(AnsiString context)
{
	char* t;
	char t2;
	String t1,t3,t4;
	t1 = context;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;
	int t5=1,i = context.Length()  ;
	for( int j=1;j<=i;j++)
	{
	//if (j == 9) break;
	t3 = t1.SubString(j,1);
	t = t3.t_str();
	//if(t3 < 160) continue;
	Word k = int (t[0])<<8;
	k = k >> 8;
	if(k<160) continue;
	//if(int(t[0])< 160) continue;
	//if (t3 >= 'a' && t3 <= 'z' || t3 >= 'A' && t3 <= 'Z'|| t3 >= 0 && t3 <= 9||t3 == '!'||t3 == '@'||t3=='#'||t3=='$'||t3=='%') continue;
	t5++;
	if (t5 == 9) break;
	t = t3.t_str();
	t2 = GetPYIndexChar(t);
	t4 = t4 + t2;
	}
	return t4;
}
//---------------------------------------------------------------------------
AnsiString TfrmQikanguanli::BarCodeToISSN(AnsiString BarCode)
{
	AnsiString ISSN;
	int j[7];
	int k[7] = {8,7,6,5,4,3,2};
	int p = 0;
	for (int i = 4; i < 11;i++,p++) {
		 j[p] = StrToInt(BarCode.SubString(i,1));
	}
	int a = 0;
	int b= 0;
	int c = 0;
	int d = 0;

	for (int i = 0; i < 7; i++) {
		a = a + j[i]*k[i];
	}

	b = a % 11;
	c = 11 -b;
	for (int i = 0; i < 7; i++) {
		ISSN = ISSN + IntToStr(j[i]) ;
	}
	if (c == 10) {
		ISSN = ISSN + "X";
	}else
	{
		ISSN = ISSN + IntToStr(c);
	}
  	return ISSN;
}
//---------------------------------------------------------------------------
AnsiString TfrmQikanguanli::ISSNToBarCode(AnsiString ISSN)
{
  //ISSN与EAN的对应关系为：977 + ISSN前7码 + 00 + EAN检查码
	 ISSN = ReplaceStr(ISSN,"-","");

	 AnsiString BarCode;
	 BarCode = "977";
	 for (int i = 1; i < 8; i++) {
		 BarCode = BarCode + ISSN.SubString(i,1);
	 }
	 int a=0;
	 int b= 0;
	 int c= 0;
	 int d = 0;
	 for (int i = 2; i < 11; i++) {
		 a = a + StrToInt(BarCode.SubString(i,1) );
		 i++;
	 }
	 for (int i = 1; i < 11; i++) {
	   b = b + StrToInt(BarCode.SubString(i,1) );
	   i++;
	 }
	 a = a *3;
	 c = b + a;
	 d = c % 10;           //取得校验码
	 d = 10 -d;
	 BarCode = BarCode + "00" + IntToStr(d);
	 return BarCode;
}

//---------------------------------------------------------------------------
void __fastcall TfrmQikanguanli::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {  //添加
		 BtnNew->Click();
	}	if (Key == VK_F4) {     //保存
		BtnSave->Click();
	}
		if (Key == VK_F5) {     //修改
		BtnClear->Click();
	}
		if (Key == VK_F9) {     //作废
		BtnCancel->Click();
	}
		if (Key == VK_F8) {      //删除
		BtnDelete->Click();
	}
		if (Key == VK_F3) {   //统一
		BtnJumptoLine->Click();
	}
	if (Key == VK_F7) {     //导入
		BtnImport->Click();
	}
		if (Key == VK_F6) {      //导出
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

void __fastcall TfrmQikanguanli::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::chtaoshuKeyPress(TObject *Sender, wchar_t &Key)

{
  //	if (Key == VK_RETURN) {
  //		BtnSave->Click();
 //	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmQikanguanli::dgCellClick(TColumnEh *Column)
{
	if ( aqinsert->IsEmpty() ) {
		return;
	}

	editqikanissn->Text  = aqinsert->FieldByName("isbn")->AsAnsiString   ;
	editqikanname->Text  =	aqinsert->FieldByName("name")->AsAnsiString  ;
	editqikanself->Text =	aqinsert->FieldByName("userdefcode")->AsAnsiString ;
	editqikanprice->Text =	aqinsert->FieldByName("price")->AsAnsiString  ;
	editqikanmao->Text =	aqinsert->FieldByName("barcode")->AsAnsiString  ;
	editqikanqihao->Text=  aqinsert->FieldByName("presscount")->AsAnsiString ;
	sedyear->Text = aqinsert->FieldByName("year")->AsAnsiString ;
	rcbtype->ItemIndex = rcbtype->Items->IndexOfObject((TObject*)aqinsert->FieldByName("smallbooktypeid")->AsInteger);
	rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aqinsert->FieldByName("pid")->AsInteger);
	cbkanqi->Text = aqinsert->FieldByName("Bookformat")->AsAnsiString ;
	chduokan->Checked = aqinsert->FieldByName("duokan")->AsBoolean ;
	if (aqinsert->FieldByName("duokan")->AsBoolean) {
		cbduokan->Text = aqinsert->FieldByName("duokantext")->AsAnsiString ;
		sedkannum->Text = aqinsert->FieldByName("duokannum")->AsAnsiString ;
		cbduokan->Visible = true;
		sedkannum->Visible = true;
		Label3->Visible = true;
	}
	else
	{
		cbduokan->Visible = false;
		sedkannum->Visible = false;
		Label3->Visible = false;
	}
	edyearprice->Text = aqinsert->FieldByName("yearprice")->AsAnsiString ;
	edkanhao->Text = aqinsert->FieldByName("kanhao")->AsAnsiString ;
	edtykanhao->Text = aqinsert->FieldByName("tongyikanhao")->AsAnsiString ;
	cbyoufa->Text = aqinsert->FieldByName("youfa")->AsAnsiString ;
	youfacode->Text = aqinsert->FieldByName("youfacode")->AsAnsiString ;
	edpressarea->Text = aqinsert->FieldByName("pressarea")->AsAnsiString ;
	bk->Text = aqinsert->FieldByName("Bk")->AsAnsiString ;
	cbkanzhong->Text = aqinsert->FieldByName("kanzhong")->AsAnsiString ;
	if (modle != 1) {
    	BtnClear->Enabled = true;
		BtnCancel->Enabled = true;
		BtnDelete->Enabled = true;
		BtnImport->Enabled = true;
		BtnExport->Enabled = true;
		BtnNew->Enabled = true;
		BtnJumptoLine->Enabled = true;
		BtnSave->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::BtnSaveClick(TObject *Sender)
{
	int pressid = -1,booktypeid = -1;
	AnsiString sql;
	if (rcbpress->Text != "") {
		try {
			pressid = (int)rcbpress->Items->Objects[rcbpress->ItemIndex];
		} catch (...) {
			MessageBoxA(0,"请选择正确的出版社!","警告",MB_ICONASTERISK);
			return;
		}
	}
	if (rcbtype->Text != "") {
		try {
			booktypeid = (int)rcbtype->Items->Objects[rcbtype->ItemIndex];
		} catch (...) {
			MessageBoxA(0,"请选择正确的类别!","警告",MB_ICONASTERISK);
			return;
		}
	}
	if (edyearprice->Text == "") {
        edyearprice->Text = "0";
	}
	int totalkanqi;
	float price = 0.0;
	int qikanshu;
	if (editqikanqihao->Text == "") {
		editqikanqihao->SetFocus();
		MessageBoxA(0,"期号必须录入!","提示",MB_ICONASTERISK);
		return;
	}
	try {
		price = StrToFloat(editqikanprice->Text);
		qikanshu = StrToInt(editqikanqihao->Text);
	} catch (...) {
    	MessageBoxA(0,"请录入正确的期号和定价!","提示",MB_ICONASTERISK);
    	return;
	}
	if (modle == 1) {
		if (editqikanprice->Text=="￥0.00" || editqikanprice->Text == "") {
			MessageBoxA(0,"请输入定价!","警告",MB_ICONASTERISK);
			return;
		}
		if (editqikanname->Text == "") {
			MessageBoxA(0,"请输入期刊名!","警告",MB_ICONASTERISK);
			return;
		}
		sql = "select * from BS_BookCatalog where type = 1 and name = '" + editqikanname->Text.Trim() + "' and presscount = '" + editqikanqihao->Text.Trim() + "' and (isbn = '" + editqikanissn->Text.Trim() + "' or Barcode = '" + editqikanmao->Text.Trim() + "') and year = '" + sedyear->Text.Trim() + "'" ;
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (!aquery->IsEmpty() ) {
			MessageBoxA(0,"该期刊已存在，请重新录入期刊!","提示",MB_ICONASTERISK);
			return;
		}
		try
		{
			if (MessageBoxA(0,"确定要产生新期刊吗？","提示",MB_ICONQUESTION||MB_OKCANCEL)== 1) {
				aqinsert->Append();
				aqinsert->FieldByName("isbn")->AsAnsiString =  editqikanissn->Text ;
				aqinsert->FieldByName("name")->AsAnsiString = editqikanname->Text ;
				aqinsert->FieldByName("userdefcode")->AsAnsiString =   editqikanself->Text ;
				aqinsert->FieldByName("price")->AsFloat  =  StrToFloat(editqikanprice->Text);
				aqinsert->FieldByName("barcode")->AsAnsiString = editqikanmao->Text ;
				aqinsert->FieldByName("date")->AsDateTime  =  Now();
				aqinsert->FieldByName("Unavailable")->AsInteger  =  1;
				aqinsert->FieldByName("type")->AsInteger  =  1;
				aqinsert->FieldByName("presscount")->AsAnsiString =  editqikanqihao->Text ;
				aqinsert->FieldByName("year")->AsAnsiString =  sedyear->Text ;
				aqinsert->FieldByName("pid")->AsInteger  =  pressid;
				aqinsert->FieldByName("smallBookTypeID")->AsInteger  =  booktypeid;
				aqinsert->FieldByName("Bookformat")->AsAnsiString =  cbkanqi->Text ;
				aqinsert->FieldByName("duokan")->AsBoolean = chduokan->Checked;
				if (chduokan->Checked ) {
					aqinsert->FieldByName("duokantext")->AsAnsiString = cbduokan->Text;
					aqinsert->FieldByName("duokannum")->AsInteger = sedkannum->Value;
				}
				aqinsert->FieldByName("yearprice")->AsFloat =  StrToFloat(edyearprice->Text);
				aqinsert->FieldByName("kanhao")->AsAnsiString =  edkanhao->Text ;
				aqinsert->FieldByName("tongyikanhao")->AsAnsiString =  edtykanhao->Text ;
				aqinsert->FieldByName("youfa")->AsAnsiString =  cbyoufa->Text ;
				aqinsert->FieldByName("youfacode")->AsAnsiString =  youfacode->Text ;
				aqinsert->FieldByName("pressarea")->AsAnsiString =  edpressarea->Text ;
				aqinsert->FieldByName("Bk")->AsAnsiString =  bk->Text ;
				aqinsert->FieldByName("kanzhong")->AsAnsiString = cbkanzhong->Text ;
				aqinsert->UpdateBatch(arAll);

				editqikanissn->Text ="";
				editqikanname->Text = "";
				editqikanself->Text = "";
				editqikanprice->Text="0.00";
				editqikanmao->Text= "";
				editqikanqihao->Text="";
				rcbtype->Text = "";
				chduokan->Checked = false;
				cbduokan->ItemIndex = 0;
				cbduokan->Visible = false;
				sedkannum->Value = 1;
				sedkannum->Visible = false;
				Label3->Visible = false;
				edyearprice->Text = "0.00";
				edkanhao->Text = "";
				edtykanhao->Text = "";
				cbyoufa->Text = "";
				youfacode->Text = "";
				edpressarea->Text = "";
				bk->Text = "";
				Press(0);
				editqikanmao->SetFocus();
				if (rzcbinput->Checked) {
					modle = 1;
				}
				else
				{
					modle = 0;
					BtnClear->Enabled = true;
					BtnCancel->Enabled = true;
					BtnDelete->Enabled = true;
					BtnImport->Enabled = true;
					BtnExport->Enabled = true;
					BtnNew->Enabled = true;
					BtnJumptoLine->Enabled = true;
					BtnSave->Enabled = false;
				}
			}
		}
		catch(...)
		{}
	}
	if (modle == 2) {   //修改
		if (aqinsert->IsEmpty() ) {
			return;
		}
		if (MessageBox(0,"确认修改期刊信息？","期刊" ,MB_OKCANCEL||MB_ICONQUESTION)==1)
		{
			sql = "update BS_BookCatalog set isbn ='" + editqikanissn->Text + "', name='" +editqikanname->Text + "',userdefcode = '";
			sql = sql +  editqikanself->Text + "', price = " + editqikanprice->Text + ",barcode = '" + editqikanmao->Text + "',kanzhong = '" + cbkanzhong->Text;
			sql = sql + "', presscount = '" + editqikanqihao->Text + "',year = '" + sedyear->Text + "',PressID = " + IntToStr(pressid) + ",smallBookTypeID = " + IntToStr(booktypeid) ;
			sql = sql + ",Bookformat = '" + cbkanqi->Text + "',yearprice = " + edyearprice->Text + ",kanhao = '" + edkanhao->Text + "',tongyikanhao = '" + edtykanhao->Text + "'";
			sql = sql + ",youfa = '" + cbyoufa->Text + "',youfacode = '" + youfacode->Text + "',pressarea = '" + edpressarea->Text + "',Bk = '" + bk->Text + "',duokan = " + BoolToStr(chduokan->Checked);
			if (chduokan->Checked ) {
				sql = sql + ",duokantext = '" + cbduokan->Text + "',duokannum = " + sedkannum->Text ;
			}
			else
			{
				sql = sql + ",duokantext = '',duokannum = 0 ";
			}
			sql = sql  + " where ID = " + aqinsert->FieldByName("ID")->AsAnsiString ;

			TADOQuery * aq = new TADOQuery(NULL);
			aq->Connection = fcon;
			aq->SQL->Add(sql);
			try {
				aq->ExecSQL();
            } catch (...) {
			}

			delete aq;

            TLocateOptions   Opts;
			Opts.Clear();
			Opts   <<   loPartialKey;
			String   str   = aqinsert->FieldByName("ID")->AsAnsiString;
			aqinsert->Active = false;
			aqinsert->Active = true;
			aqinsert->Locate("ID",str,Opts);

			BtnClear->Enabled = true;
			BtnCancel->Enabled = true;
			BtnDelete->Enabled = true;
			BtnImport->Enabled = true;
			BtnExport->Enabled = true;
			BtnNew->Enabled = true;
			BtnJumptoLine->Enabled = true;
			BtnSave->Enabled = false;
			modle = 0;
			pcqikan->Enabled = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::chduokanClick(TObject *Sender)
{
	if (chduokan->Checked ) {
		cbduokan->Visible = true;
		Label3->Visible = true;
		sedkannum->Visible = true;
	}
	else
	{
		cbduokan->Visible = false;
		Label3->Visible = false;
		sedkannum->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::dgTitleClick(TColumnEh *Column)
{
	if (aqinsert->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqinsert->Sort == "") {
		aqinsert->Sort =  Column->FieldName + " ASC";
	}
	else if (aqinsert->Sort == qusort) {
		aqinsert->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqinsert->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edquery->Text != "") {
			Press(1);
		}
		rcbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::rcbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        editqikanname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void TfrmQikanguanli::Press(int mode)
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	if (mode == 1) {
		sql = "select ID,presentnum,abbreviatedname from BS_PressInfo where abbreviatedname like '%" + edquery->Text.Trim() + "%'" ;
	}
	else
	{
		sql = "select ID,presentnum,abbreviatedname from BS_PressInfo ";
	}
	rcbpress->Clear();
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while(!aq->Eof)
	{
		rcbpress->AddItem(aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	aq->First();
	if (mode == 1) {
		rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger);
	}
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::editqikanselfKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        editqikanprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::rcbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        cbkanqi->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::cbkanqiKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        chduokan->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::chduokanKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (chduokan->Checked ) {
        	cbduokan->SetFocus();
		}
		else
		{
        	edyearprice->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::edyearpriceKeyPress(TObject *Sender, wchar_t &Key)

{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == '\r') {
        edkanhao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::edkanhaoKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		edtykanhao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::edtykanhaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        cbyoufa->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::cbyoufaKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        youfacode->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::youfacodeKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edpressarea->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::edpressareaKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        bk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::bkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------
void TfrmQikanguanli::ReadyData()
{
	String sql ;
	sql = "select ID,Name from BS_BookType ";
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while(!aq->Eof)
	{
		rcbtype->AddItem(aq->FieldByName("ID")->AsAnsiString + aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
	 	aq->Next();
	}
	sql = "select ID,abbreviatedname,PresentNum from BS_PressInfo ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while(!aq->Eof)
	{
		rcbpress->AddItem(aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
	AnsiString date = DateToStr(Date());
	date = date.SubString(0,4);
	sedyear->Value = StrToInt(date);
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::sedyearKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edquery->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::sedkannumKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edyearprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::cbduokanKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
    	sedkannum->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmQikanguanli::BtnInsertRecordClick(TObject *Sender)
{
	if (aqinsert->IsEmpty() ) {
		return;
	}
	if (MessageBoxA(0,"确认期刊书目信息正确，若生成后发现书目有误，需要一本一本修改。","生成年度书目",MB_ICONQUESTION|MB_OKCANCEL)!= 1) {
    	return;
	}
	addqikan->ProcedureName = "USP_BS_Createqikan";
	addqikan->Parameters->Clear();
	addqikan->Parameters->CreateParameter("@ID",ftInteger,pdInput,sizeof(int),aqinsert->FieldByName("ID")->AsInteger);
	addqikan->Parameters->CreateParameter("@year",ftString,pdInput,10,"2010" );
	addqikan->Parameters->CreateParameter("@insertcount",ftString,pdOutput,10,"0" );
	try {
		addqikan->ExecProc();
		if (addqikan->Parameters->ParamByName("@insertcount")->Value > 0  ) {
			MessageBoxA(0,"年度期刊生成成功！","提示",MB_ICONASTERISK);
			aqinsert->Active = false;
			aqinsert->Active = true;
		}
		else
		{
			MessageBoxA(0,"期刊存在，不需再生成！","提示",MB_ICONASTERISK);
		}
	} catch (...) {
		MessageBoxA(0,"年度期刊生成失败！","提示",MB_ICONASTERISK);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::cbkanqiExit(TObject *Sender)
{
	int totalkanqi;
	float price = 0.00;
	int qikanshu;
	try {
		price = StrToFloat(editqikanprice->Text);
		qikanshu = StrToInt(editqikanqihao->Text);
	} catch (...) {
    	return;
	}
	if (cbkanqi->Text != "") {
		if (cbkanqi->Text == "周刊") {
			totalkanqi = 52;
		}
		else if (cbkanqi->Text == "旬刊") {
			totalkanqi = 36;
		}
		else if (cbkanqi->Text == "半月刊") {
			totalkanqi = 24;
		}
		else if (cbkanqi->Text == "月刊") {
			totalkanqi = 12;
		}
		else if (cbkanqi->Text == "双月刊") {
			totalkanqi = 6;
		}
		else if (cbkanqi->Text == "季刊") {
			totalkanqi = 4;
		}
		else if (cbkanqi->Text == "半年刊") {
			totalkanqi = 2;
		}
		else if (cbkanqi->Text == "年刊") {
			totalkanqi = 1;
		}
		edyearprice->Text = FormatFloat("0.00",price*totalkanqi);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::sedkannumExit(TObject *Sender)
{
	int totalkanqi;
	float price = 0.00;
	try {
		price = StrToFloat(editqikanprice->Text);
	} catch (...) {
		return;
	}
	if (cbkanqi->Text != "") {
		if (cbkanqi->Text == "周刊") {
			totalkanqi = 52;
		}
		else if (cbkanqi->Text == "半月刊") {
			totalkanqi = 24;
		}
		else if (cbkanqi->Text == "月刊") {
			totalkanqi = 12;
		}
		else if (cbkanqi->Text == "双月刊") {
			totalkanqi = 6;
		}
		else if (cbkanqi->Text == "季刊") {
			totalkanqi = 4;
		}
		else if (cbkanqi->Text == "半年刊") {
			totalkanqi = 2;
		}
		else if (cbkanqi->Text == "年刊") {
			totalkanqi = 1;
		}
		edyearprice->Text = FormatFloat("0.00",price*totalkanqi*sedkannum->Value);
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmQikanguanli::editqikanqihaoExit(TObject *Sender)
{
	if (editqikanqihao->Text != "") {
		if (editqikanqihao->Text.Length() == 1 ) {
            editqikanqihao->Text = "0" + editqikanqihao->Text;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::BtnUndoClick(TObject *Sender)
{
	if (!aqinsert->IsEmpty() ) {
		for (int i=0; i < dg->SelectedRows->Count; i++) {
			aqinsert->GotoBookmark(dg->SelectedRows->Items[i]);
			aqinsert->Edit();
			aqinsert->FieldByName("Unavailable")->Value = 1;
			aqinsert->UpdateBatch(arCurrent);
		}
	}
}
//---------------------------------------------------------------------------

