//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZNNewBookinput.h"
#include "..\catalogadmin\PressAdminForm.h"
#include "..\catalogadmin\BooKTypeAdminForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma link "RzRadChk"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma link "RzLine"
#pragma resource "*.dfm"
Tfrmnewbook *frmnewbook;
//---------------------------------------------------------------------------
__fastcall Tfrmnewbook::Tfrmnewbook(TComponent* Owner,TADOConnection *con,TfrmStorageMng *frm)
	: TForm(Owner)
{
   aquery->Connection = con;
   fcon = con;
   from = frm;
   String sql;
   sql = "select max(id) as id from bs_bookcatalog";
   TADOQuery *aq = new TADOQuery(this);
   aq->Connection = con;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   int id = aq->FieldByName("id")->AsInteger ;
   delete aq;
   sql = "select A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,"
		 "A.Yizhe,A.Pressdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(id) ;
   if (cbsaletype->Text == "图书") {
		sql = sql + " and A.type = 0";
   }
   else if (cbsaletype->Text == "期刊") {
		sql = sql + " and A.type = 1";
   }
   else if (cbsaletype->Text == "文具") {
		sql = sql + " and A.type = 2";
   }
   else
   {
   		sql = sql + " and A.type > 2";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->Open();
   ReadyData();
   datapressday->Date = Date();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook::BtnExitClick(TObject *Sender)
{
	ModalResult = mbCancel  ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook::FormClose(TObject *Sender, TCloseAction &Action)
{
  	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook::editcodeKeyPress(TObject *Sender, wchar_t &Key)
{
	String sql;
	if (Key==VK_RETURN)
	{
	   sql = "select A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,"
		 "A.Yizhe,A.Pressdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.barcode =  '" + editcode->Text + "'";
		 if (cbsaletype->Text == "图书") {
			sql = sql + " and A.type = 0";
		 }

	   aquery->Close();
	   aquery->SQL->Clear();
	   aquery->SQL->Add(sql);
	   aquery->Open();
	   int pressid;
	   pressid = BrocodeToPress(editcode->Text);
	   rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)pressid);
	   ((TFloatField *)RzDBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "￥0.00";
	   if (aquery->RecordCount == 0) {

	   }
	   editisbn->Text = editcode->Text ;
	   editbookname->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook::SpeedButton1Click(TObject *Sender)
{
  	editisbn->Text =  BuildISBNCode(editisbn->Text);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook::editbooknameKeyPress(TObject *Sender, wchar_t &Key)
{
	   if (Key==VK_RETURN) {
		 if (editbookname->Text =="") {
				MessageBox(0,"书名不能为空!","新录书目",MB_ICONWARNING);
				return;
		 }
			char* t;
			char t2;
			String t1,t3,t4;
			t1 = editbookname->Text;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;
			int t5=1,i = editbookname->Text.Length() ;
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
			editbookself->Text = t4;
			editprice->SetFocus();
	   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook::editpriceKeyPress(TObject *Sender, wchar_t &Key)
{
 if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
  }
  if (Key==VK_RETURN) {
	AnsiString pricest;
	pricest = ReplaceStr(editprice->Text,"￥","");
	float price = StrToFloat(pricest) ;
	editprice->Text = FormatFloat("￥0.00",price);
	editauthor->SetFocus();
  }

}
void Tfrmnewbook::ReadyData()
{  try
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
	sql = "select ID,presentnum,abbreviatedname from BS_PressInfo ";
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
   }catch(...)
   {}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook::editauthorKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN)
	{
		rcbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook::rcbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN)
	{
	   edquery->SetFocus();
	}
}
//---------------------------------------------------------------------------
String  Tfrmnewbook:: GetID()
{
	return ID;
}
void __fastcall Tfrmnewbook::rcbpressKeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==VK_RETURN)
	{
	   datapressday->SetFocus();
	}
}
char Tfrmnewbook::GetPYIndexChar(char *str)
{
	Word x = 0;
	Word y = 0;//int y = 0;
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
void __fastcall Tfrmnewbook::BtnSaveClick(TObject *Sender)
{

   if (1== type) {
	  if (editqikanname->Text == "" )
	  {
			MessageBox(0,"刊名不能为空!","新录书目",MB_ICONWARNING);
			return;

	  }
	  if (editqikanprice->Text == "￥0.00") {
			MessageBox(0,"定价不能为空!","新录书目",MB_ICONWARNING);
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
		aqinsert->FieldByName("bk")->AsAnsiString = editqikanfaxing->Text ;
        aqinsert->UpdateBatch(arCurrent);
		editqikanissn->Text ="";
		editqikanname->Text = "";
		editqikanself->Text = "";

		editqikanprice->Text = "￥0.00";
		editqikanmao->Text= "";
		editqikanqihao->Text="";
		editqikanfaxing->Text = "";
		editqikanmao->SetFocus();
		int ID ;
		if (!rzcbinput->Checked) {
			 ID =  aqinsert->FieldByName("ID")->AsInteger  ;
			 from->AddNote(ID);
			 ModalResult = mbOK ;


		 }else     //连续录入
		 {
            ID =  aqinsert->FieldByName("ID")->AsInteger  ;
			 from->AddNote(ID);
		   return;

		 }

	}
	}
	catch(...)
	{}

   }
   if (2 == type) {

  if (editwenjuprice->Text=="￥0.00") {
	   MessageBoxA(0,"请输入定价!","警告",MB_ICONASTERISK);
	   return;
  }
  if (editwenjuname->Text == "") {
		 MessageBoxA(0,"请输入品名!","警告",MB_ICONASTERISK);
	   return;
  }
	if (MessageBoxA(0,"确定要产生文具吗？","提示",MB_ICONQUESTION||MB_OKCANCEL)== 1) {
		try
		{
		aqinsert->Insert();
		aqinsert->Append();
		aqinsert->FieldByName("isbn")->AsAnsiString =  editwenjutiaomao->Text ;
		aqinsert->FieldByName("name")->AsAnsiString = editwenjuname->Text ;
		aqinsert->FieldByName("userdefcode")->AsAnsiString =   editwenjuself->Text ;
		aqinsert->FieldByName("price")->AsFloat  =  StrToFloat(editwenjuprice->Text);
		aqinsert->FieldByName("barcode")->AsAnsiString = editwenjutiaomao->Text ;
		aqinsert->FieldByName("date")->AsDateTime  =  Now();
		aqinsert->FieldByName("Unavailable")->AsInteger  =  1;
		aqinsert->FieldByName("type")->AsInteger  =  2;
		aqinsert->UpdateBatch(arCurrent);
		editwenjutiaomao->Text ="";
		editwenjuname->Text = "";
		editwenjuself->Text = "";
		editwenjuprice->Text = "￥0.00";
		editwenjutiaomao->Text= "";
		editwenjutiaomao->SetFocus();
		int ID;
			if (!rzcbinput->Checked) {
			 ID =  aqinsert->FieldByName("ID")->AsInteger  ;
			 from->AddNote(ID);
			 ModalResult = mbOK ;

		 }else     //连续录入
		 {
             ID =  aqinsert->FieldByName("ID")->AsInteger  ;
			 from->AddNote(ID);
		   return;

		 }

		}catch(...)
		{}

   }
   }

 if (0==type) {

   if (editbookname->Text == "") {
			MessageBox(0,"书名不能为空!","新录书目",MB_ICONWARNING);
			return;
   }
   if (editprice->Text  == "") {

			MessageBox(0,"定价不能为空!","新录书目",MB_ICONWARNING);
			return;
   }
   if (editprice->Text == "") {
		editprice->Text = "0.00";
   }
   else
   {
		String price = editprice->Text ;
		price = price.SubString(price.Pos("￥")+1,price.Length()-price.Pos("￥") );
		editprice->Text = price;
   }
   String sql;
   int pressid,bktypeid;
   if (rcbpress->Text!="") {
		try {
			pressid = (int)(rcbpress->Items->Objects[rcbpress->ItemIndex]);
		} catch (...) {
			MessageBox(0,"请选择正确的出版社!","新录书目",MB_ICONWARNING);
			return;
		}
   }
   if (rcbtype->Text != "") {
    	try {
			bktypeid = (int)(rcbtype->Items->Objects[rcbtype->ItemIndex]);
		} catch (...) {
			MessageBox(0,"请选择正确的类别!","新录书目",MB_ICONWARNING);
			return;
		}
   }
		  if (MessageBox(0,"确定产生新书吗？","新录书目",MB_ICONQUESTION|MB_OKCANCEL )==1) {
            sql = "select * from BS_BookCatalog where ISBN = '" + editisbn->Text + "' and Name = '" + editbookname->Text.Trim() + "' and Price = " + editprice->Text ;
            TADOQuery *aq = new TADOQuery(this);
			aq->Connection = fcon;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				if (MessageBox(0,"是不是重复录入？","新录书目",MB_ICONQUESTION|MB_OKCANCEL )!=1) {
                	return;
				}
			}
			delete aq;
			aquery->Insert();
			aquery->Append();
			aquery->FieldByName("barcode")->AsAnsiString = editcode->Text ;
			aquery->FieldByName("ISBN")->AsAnsiString = editisbn->Text ;
			aquery->FieldByName("name")->AsAnsiString = editbookname->Text ;
			aquery->FieldByName("userdefcode")->AsAnsiString = editbookself->Text ;
			aquery->FieldByName("author")->AsAnsiString = editauthor->Text ;
			aquery->FieldByName("price")->AsAnsiString = editprice->Text ;
			if (rcbpress->Text=="") {
			  aquery->FieldByName("pid")->AsInteger  = -1;
			} else
			{
			 aquery->FieldByName("pid")->AsInteger = (int)(rcbpress->Items->Objects[rcbpress->ItemIndex]);

			}
			if (rcbtype->Text == "") {
				aquery->FieldByName("smallbooktypeid")->AsInteger = -1;
			} else
			{
			   aquery->FieldByName("smallbooktypeid")->AsInteger = (int)(rcbtype->Items->Objects[rcbtype->ItemIndex]);

			}
			aquery->FieldByName("Pressdate")->AsDateTime = datapressday->Date;
			aquery->FieldByName("PressCount")->AsString = sedpresscount->Text ;
			aquery->FieldByName("ISBNType")->AsString = edISBNtype->Text ;
			aquery->FieldByName("Yizhe")->AsString = edyizhe->Text ;
			aquery->FieldByName("Printcount")->AsString = edprintcount->Text ;
			aquery->FieldByName("Affix")->AsString = edaffix->Text ;
			aquery->FieldByName("Bookformat")->AsString = cbformat->Text ;
			aquery->FieldByName("Bind")->AsString = cbbind->Text ;
			aquery->FieldByName("Collectbook")->AsString = edbook->Text ;
			aquery->FieldByName("BookWords")->AsString = edwords->Text ;
			aquery->FieldByName("Bk")->AsString = edbk->Text ;
			aquery->UpdateBatch(arAll);
		if (!rzcbinput->Checked) {
			 ID =  aquery->FieldByName("ID")->AsAnsiString ;
			 from->AddNote(StrToInt(ID));
			 ModalResult = mbOK ;

		 }else     //连续录入
		 {
			editcode->Text  = "";
			editisbn->Text = "";
			editbookname->Text = "";
			editbookself->Text = "";
			editauthor->Text = "";
			rcbpress->ItemIndex = -1;
			rcbtype->ItemIndex  = -1;
			editprice->Text = "￥0.00";
			datapressday->Date = Date();
			sedpresscount->Value = 0;
			edISBNtype->Text = "";
			edyizhe->Text = "";
			edprintcount->Value = 0;
			edaffix->Text = "";
			cbformat->ItemIndex = 0;
			cbbind->ItemIndex = 0;
			edbook->Text = "";
			edwords->Text = "";
			edbk->Text = "";
			PageControlBook->ActivePage = tsbase;
			editcode->SetFocus();
			ID =  aquery->FieldByName("ID")->AsAnsiString ;
			from->AddNote(StrToInt(ID));
			edquery->Text = "";
			Press(0);
		 }
	  }
		  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook::RzDBGrid1CellClick(TColumn *Column)
{
   if (aquery->IsEmpty()) {
	   return;
   }
	editcode->Text  = aquery->FieldByName("barcode")->AsAnsiString;
	editisbn->Text = aquery->FieldByName("ISBN")->AsAnsiString;
	editbookname->Text = aquery->FieldByName("name")->AsAnsiString;
	editbookself->Text = aquery->FieldByName("userdefcode")->AsAnsiString;
	editauthor->Text =aquery->FieldByName("author")->AsAnsiString;
	editprice->Text = FormatFloat("￥0.00",aquery->FieldByName("price")->AsFloat);
	rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aquery->FieldByName("pid")->AsInteger );
	rcbtype->ItemIndex = rcbtype->Items->IndexOfObject((TObject*)aquery->FieldByName("smallbooktypeid")->AsInteger );
	datapressday->Date = aquery->FieldByName("Pressdate")->AsDateTime ;
	sedpresscount->Text = aquery->FieldByName("PressCount")->AsString ;
	edISBNtype->Text = aquery->FieldByName("ISBNType")->AsString ;
	edyizhe->Text = aquery->FieldByName("Yizhe")->AsString ;
	edprintcount->Text = aquery->FieldByName("Printcount")->AsString ;
	edaffix->Text = aquery->FieldByName("Affix")->AsString ;
	cbformat->Text = aquery->FieldByName("Bookformat")->AsString ;
	cbbind->Text = aquery->FieldByName("Bind")->AsString ;
	edbook->Text = aquery->FieldByName("Collectbook")->AsString ;
	edwords->Text = aquery->FieldByName("BookWords")->AsString ;
	edbk->Text = aquery->FieldByName("Bk")->AsString ;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmnewbook::datapressdayKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        sedpresscount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::sedpresscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
	   BtnSave->Click();
		editcode->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::edISBNtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
    	edyizhe->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::edyizheKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edprintcount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::edprintcountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edaffix->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::edaffixKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        cbformat->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::cbformatKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        cbbind->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::cbbindKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edbook->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::edbookKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edwords->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::edwordsKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edbk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::edbkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        BtnSave->Click();
	}
}
int Tfrmnewbook::BrocodeToPress(String brocode)
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
	sql = "select ID from BS_PressInfo where PresentNum = '" + pressnum + "'";
	TADOQuery * query = new TADOQuery(NULL);
	query->Connection = fcon;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	int pressid = query->FieldByName("ID")->AsInteger ;
	return pressid;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmnewbook::cbsaletypeChange(TObject *Sender)
{
	 if (cbsaletype->Text == "图书") {
	  PageControlBook->Visible = true;
	  pcqikan->Visible = false;
	  pcwenju->Visible = false;
	  dg->Visible = false;
	  RzDBGrid1->Visible = true;
	  type = 0;
	  Press(0);
	 }
	 if (cbsaletype->Text == "期刊") {
		 pcqikan->Visible = true;
		 pcwenju->Visible = false;
		 PageControlBook->Visible = false;
		 type = 1;
		 ShowInput(1);
	 }
	 if (cbsaletype->Text == "文具") {
		 pcwenju->Visible = true;
		 PageControlBook->Visible = false;
		 pcqikan->Visible = false;
		 type = 2;
		 ShowInput(2);
	 }
}
void Tfrmnewbook::ShowInput(int type)
{
  AnsiString sql;
  TColumn *Column;

		 switch (type) {
			   case 0:
				  dg->Visible = false;
				  RzDBGrid1->Visible = true;
			   break;

			   case 1:                   //期刊

				  dg->Columns->Clear();
				  dg->Visible = true;
				  RzDBGrid1->Visible = false;
					aqinsert->Active = false;

					sql = "select ID,isbn,name,userdefcode,price,barcode,date,Unavailable,type,presscount,bk from bs_bookcatalog where type = 1  and unavailable =1 and 1=2" ;
					   aqinsert->Connection = fcon ;
						aqinsert->Close();
					aqinsert->SQL->Clear();
					aqinsert->SQL->Add(sql);
					aqinsert->Active = true;

				  Column = dg->Columns->Add();
				  Column->FieldName = "isbn";
				  Column->Title->Caption = "ISSN";
				  Column->Width = 80;

				  Column = dg->Columns->Add();
				  Column->FieldName = "name";
				  Column->Title->Caption = "刊名";
				  Column->Width = 300;

				  Column = dg->Columns->Add();

				  Column->FieldName = "price";
				  Column->Title->Caption = "定价";
				  Column->Width = 70;
				  Column = dg->Columns->Add();

				  Column->FieldName = "bk";
				  Column->Title->Caption = "发行单位";
				  Column->Width = 140;
				  Column = dg->Columns->Add();

				  Column->FieldName = "presscount";
				  Column->Title->Caption = "期号";
				  Column->Width = 80;

			   break;

			   case 2:                    //文具
					dg->Columns->Clear();
					dg->Visible = true;
					RzDBGrid1->Visible = false;


					aqinsert->Connection = fcon ;

					sql = "select ID,isbn,name,userdefcode,price,barcode,date,Unavailable,type,presscount,bk from bs_bookcatalog where type = 2  and unavailable =1 and 1=2" ;
					aqinsert->Connection = fcon ;
					aqinsert->Close();
					aqinsert->SQL->Clear();
					aqinsert->SQL->Add(sql);
					aqinsert->Active = true;

					Column = dg->Columns->Add();
					Column->FieldName = "barcode";
					Column->Title->Caption = "条码";
					Column->Width = 90;

					Column = dg->Columns->Add();
					Column->FieldName = "name";
					Column->Title->Caption = "品名";
					Column->Width =150;

					Column = dg->Columns->Add();
					Column->FieldName = "userdefcode";
					Column->Title->Caption = "自编码";
					Column->Width =90;
			   break;
		 default:
			 ;


		 }



	 }


//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::editqikanqihaoKeyPress(TObject *Sender, wchar_t &Key)

{
if (Key == VK_RETURN) {
	BtnSave->Click();
    editqikanmao->SetFocus();
}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::editwenjupriceKeyPress(TObject *Sender, wchar_t &Key)

{
  if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
	  Key = NULL;
  }
  if (Key == VK_RETURN) {
      BtnSave->Click();
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::editqikanmaoKeyPress(TObject *Sender, wchar_t &Key)
{
	  if (Key == VK_RETURN) {
	   if (editqikanmao->Text.Length() != 13 ) {
	   MessageBoxA(0,"请输入正确的条码","提示",MB_ICONASTERISK);
	   return;

	   }
	   editqikanissn->Text = BarCodeToISSN(editqikanmao->Text.Trim());

		AnsiString sql;
		sql = "select ID,isbn,name,userdefcode,price,barcode,date,Unavailable,type,presscount,bk from bs_bookcatalog where type = 1  and unavailable =1" ;
		sql = sql + " and barcode = '" + editqikanmao->Text + "'";
		aqinsert->Connection = fcon ;
		aqinsert->Close();
		aqinsert->SQL->Clear();
		aqinsert->SQL->Add(sql);
		aqinsert->Open();
	   Perform(WM_NEXTDLGCTL, 0, 0);
   }
}
AnsiString Tfrmnewbook::GetSelf(AnsiString context)
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
AnsiString Tfrmnewbook::BarCodeToISSN(AnsiString BarCode)
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
AnsiString Tfrmnewbook::ISSNToBarCode(AnsiString ISSN)
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

void __fastcall Tfrmnewbook::editqikanissnKeyPress(TObject *Sender, wchar_t &Key)

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

void __fastcall Tfrmnewbook::editqikannameKeyPress(TObject *Sender, wchar_t &Key)

{
  if (Key == VK_RETURN) {
	 if (editqikanname->Text == "") {
		 MessageBoxA(0,"请输入期刊名!","警告",MB_ICONASTERISK);
	   return;
  }
  editqikanself->Text = GetSelf(editqikanname->Text.Trim() );
  Perform(WM_NEXTDLGCTL, 0, 0);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::editqikanpriceKeyPress(TObject *Sender, wchar_t &Key)

{
  if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
	  Key = NULL;
  }
  if (Key == VK_RETURN) {
  if (editqikanprice->Text=="￥0.00") {
	   MessageBoxA(0,"请输入定价!","警告",MB_ICONASTERISK);
	   return;
  }
	  Perform(WM_NEXTDLGCTL, 0, 0);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::editqikanfaxingKeyPress(TObject *Sender, wchar_t &Key)

{
 if (Key == VK_RETURN) {
	Perform(WM_NEXTDLGCTL, 0, 0);
 }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::editwenjutiaomaoKeyPress(TObject *Sender, wchar_t &Key)

{
  if (Key == VK_RETURN) {

	AnsiString sql;
	sql = "select ID,isbn,name,userdefcode,price,barcode,date,Unavailable,type,presscount,bk from bs_bookcatalog where type = 2  and unavailable =1" ;
	sql = sql + " and barcode = '" + editqikanmao->Text + "'";
	aqinsert->Connection = fcon ;
	aqinsert->Close();
	aqinsert->SQL->Clear();
	aqinsert->SQL->Add(sql);
	aqinsert->Open();
	Perform(WM_NEXTDLGCTL, 0, 0);
 }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::editwenjunameKeyPress(TObject *Sender, wchar_t &Key)

{
  if (Key == VK_RETURN) {

   if (editwenjuname->Text == "") {
		 MessageBoxA(0,"请输入品名!","警告",MB_ICONASTERISK);
	   return;
  }
	editwenjuself->Text = GetSelf(editwenjuname->Text.Trim());
	Perform(WM_NEXTDLGCTL, 0, 0);
 }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::dgCellClick(TColumn *Column)
{
     if ( aqinsert->IsEmpty() ) {
   return;

  }

  if (1 == type ) {

		editqikanissn->Text  = aqinsert->FieldByName("isbn")->AsAnsiString   ;
		editqikanname->Text  =	aqinsert->FieldByName("name")->AsAnsiString  ;
		editqikanself->Text =	aqinsert->FieldByName("userdefcode")->AsAnsiString ;
		editqikanprice->Text =	aqinsert->FieldByName("price")->AsAnsiString  ;
		editqikanmao->Text =	aqinsert->FieldByName("barcode")->AsAnsiString  ;
		editqikanqihao->Text=  aqinsert->FieldByName("presscount")->AsAnsiString ;
		editqikanfaxing->Text = aqinsert->FieldByName("bk")->AsAnsiString  ;

  }
  if (2 == type ) {
	  editwenjutiaomao->Text   =	aqinsert->FieldByName("isbn")->AsAnsiString   ;
	  editwenjuname->Text =	aqinsert->FieldByName("name")->AsAnsiString  ;
	  editwenjuself->Text =	aqinsert->FieldByName("userdefcode")->AsAnsiString ;
	  editwenjuprice->Text = aqinsert->FieldByName("price")->AsAnsiString ;
	  editwenjutiaomao->Text = aqinsert->FieldByName("barcode")->AsAnsiString  ;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if (Key == 27) {
		BtnExit->Click();
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		Press(1);
		rcbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------


void Tfrmnewbook::Press(int mode)
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
		rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger);
		delete aq;

}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook::editisbnKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        editbookname->SetFocus();
	}
}
//---------------------------------------------------------------------------

