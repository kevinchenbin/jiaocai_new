//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NewBookinput.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
Tfrmnewbook *frmnewbook;
//---------------------------------------------------------------------------
__fastcall Tfrmnewbook::Tfrmnewbook(TComponent* Owner,TADOConnection *con,TfrmStorageMng *frm)
	: TForm(Owner)
{
   aquery->Connection = con;
   fcon = con;
   from = frm;
  ReadyData();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook::BtnExitClick(TObject *Sender)
{
 ModalResult = mbOK ;
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

	   sql = "select A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,B.abbreviatedname from bs_bookcatalog A left join BS_PressInfo B "
			 " on A.pressid = B.ID where barcode =  '" + editcode->Text + "'";
	   aquery->Close();
	   aquery->SQL->Clear();
	   aquery->SQL->Add(sql);
	   aquery->Open();
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
 if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')) {
	  Key = NULL;
  }
  if (Key==VK_RETURN) {
	editauthor->SetFocus();
  }

}
void Tfrmnewbook::ReadyData()
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
	 rcbtype->AddObject(aq->FieldByName("ID")->AsAnsiString + aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
	 aq->Next();
   }
	sql = "select ID,abbreviatedname from BS_PressInfo ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
      while(!aq->Eof)
   {
	 rcbpress->AddObject(aq->FieldByName("ID")->AsAnsiString + aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
	 aq->Next();
   }
   delete aq;
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
	   rcbpress->SetFocus();
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
	   BtnSave->Click();
		
	}
}
char Tfrmnewbook::GetPYIndexChar(char *str)
{

	Word x = 0;
	Word y = 0;//int y = 0;
	//x = StrToInt()

	 x = (int(str[0]))<<8;
	 y = (int(str[1]))<<8;
	 y = y>>8;
	 x = x + y;//str[1];
	 //y = int(str[1]);
//	 x<<8;
//	 y = (int(str[1]));
	 //x = x + y;//0xD3;//+str[1];
	//ShowMessage(0xBE<<8);
	//ShowMessage(0xD3);
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
   if (editcode->Text == "") {
					 MessageBox(0,"条码不能为空!","新录书目",MB_ICONWARNING);
				 return;
   }
   if (editbookname->Text == "") {
			MessageBox(0,"书名不能为空!","新录书目",MB_ICONWARNING);
			return;
   }
   if (editprice->Text  == "") {

			MessageBox(0,"定价不能为空!","新录书目",MB_ICONWARNING);
			return;
   }

		  if (MessageBox(0,"确定产生新书吗？","新录书目",MB_ICONQUESTION|MB_OKCANCEL )==1) {
			aquery->Insert();
			aquery->Append();
			aquery->FieldByName("barcode")->AsAnsiString = editcode->Text ;
			aquery->FieldByName("ISBN")->AsAnsiString = editisbn->Text ;
			aquery->FieldByName("name")->AsAnsiString = editbookname->Text ;
			aquery->FieldByName("userdefcode")->AsAnsiString = editbookself->Text ;
			aquery->FieldByName("author")->AsAnsiString = editauthor->Text ;
			if (editprice->Text == "") {
                editprice->Text = "0.00";
			}
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
			aquery->FieldByName("price")->AsAnsiString = editprice->Text ;

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
            editprice->Text = "0.00";
			editcode->SetFocus();
			ID =  aquery->FieldByName("ID")->AsAnsiString ;
			from->AddNote(StrToInt(ID));

		 }

		  }

}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook::RzDBGrid1CellClick(TColumn *Column)
{
	editcode->Text  = aquery->FieldByName("barcode")->AsAnsiString;
	editisbn->Text = aquery->FieldByName("ISBN")->AsAnsiString;
	editbookname->Text = aquery->FieldByName("name")->AsAnsiString;
	editbookself->Text = aquery->FieldByName("userdefcode")->AsAnsiString;
	editauthor->Text =aquery->FieldByName("author")->AsAnsiString;
	editprice->Text = aquery->FieldByName("price")->AsAnsiString;
	rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aquery->FieldByName("pid")->AsInteger );
	rcbtype->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aquery->FieldByName("smallbooktypeid")->AsInteger );
}
//---------------------------------------------------------------------------
