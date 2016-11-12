//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NewBookModify.h"
#include "Unitgenhuanselect.h"
#include "pdutil.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
TfrmNewBookModify *frmNewBookModify;
//---------------------------------------------------------------------------
__fastcall TfrmNewBookModify::TfrmNewBookModify(TComponent* Owner,TADOConnection *con,int bkcatalogid,int stgid,int userid)
	: TForm(Owner)
{
	catalogid = bkcatalogid;
	fcon = con;
	comAddcatalog->Connection = fcon;
	aquery->Connection = con;
	fstgid = stgid;
	fuserid = userid;
	ybkcatalogid =  bkcatalogid;
	ReadyData();
	AnsiString sql ;

	sql = "select * from BS_BookCatalog where id = " + IntToStr(bkcatalogid);
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	ybookname = aquery->FieldByName("name")->AsAnsiString.Trim();
	if (aquery->FieldByName("type")->AsInteger == 1 ) {
		pgqikan->Visible = true;
		PageControlBook->Visible = false;
		editqikanissn->Text  = aquery->FieldByName("isbn")->AsAnsiString.Trim()    ;
		editqikanname->Text  =	aquery->FieldByName("name")->AsAnsiString.Trim()   ;
		editqikanself->Text =	aquery->FieldByName("userdefcode")->AsAnsiString.Trim()  ;
		editqikanprice->Text =	aquery->FieldByName("price")->AsAnsiString.Trim()   ;
		editqikanmao->Text =	aquery->FieldByName("barcode")->AsAnsiString.Trim()   ;
		editqikanqihao->Text=  aquery->FieldByName("presscount")->AsAnsiString.Trim()  ;
		sedyear->Text = aquery->FieldByName("year")->AsAnsiString.Trim()  ;
        if (aquery->FieldByName("smallBookTypeID")->AsString == "") {
			rcbtype->ItemIndex = -1;
		}
		else
		{
			cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)aquery->FieldByName("smallbooktypeid")->AsInteger);
		}

		if (aquery->FieldByName("PressID")->AsString == "") {
			rcbpress->ItemIndex = -1;
		}
		else
		{
			cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aquery->FieldByName("PressID")->AsInteger);
		}
		cbkanqi->Text = aquery->FieldByName("Bookformat")->AsAnsiString.Trim()  ;
		chduokan->Checked = aquery->FieldByName("duokan")->AsBoolean ;
		if (aquery->FieldByName("duokan")->AsBoolean) {
			cbduokan->Text = aquery->FieldByName("duokantext")->AsAnsiString.Trim()  ;
			sedkannum->Text = aquery->FieldByName("duokannum")->AsAnsiString.Trim()  ;
			cbduokan->Visible = true;
			sedkannum->Visible = true;
			Label31->Visible = true;
		}
		else
		{
			cbduokan->Visible = false;
			sedkannum->Visible = false;
			Label31->Visible = false;
		}
		edyearprice->Text = aquery->FieldByName("yearprice")->AsAnsiString.Trim()  ;
		edkanhao->Text = aquery->FieldByName("kanhao")->AsAnsiString.Trim()  ;
		edtykanhao->Text = aquery->FieldByName("tongyikanhao")->AsAnsiString.Trim()  ;
	}
	else
	{
		editcode->Text = aquery->FieldByName("Barcode")->AsString.Trim()  ;
		editisbn->Text = aquery->FieldByName("ISBN")->AsString.Trim()  ;
		editbookname->Text = aquery->FieldByName("Name")->AsString.Trim()  ;
		editbookself->Text = aquery->FieldByName("UserDefCode")->AsString.Trim()  ;
		editprice->Text = FormatFloat("0.00",aquery->FieldByName("Price")->AsFloat);
		editauthor->Text = aquery->FieldByName("Author")->AsString.Trim()  ;
		if (aquery->FieldByName("smallBookTypeID")->AsString == "") {
			rcbtype->ItemIndex = -1;
		}
		else
		{
			rcbtype->ItemIndex = rcbtype->Items->IndexOfObject((TObject*)aquery->FieldByName("smallBookTypeID")->AsInteger );
		}

		if (aquery->FieldByName("PressID")->AsString == "") {
			rcbpress->ItemIndex = -1;
		}
		else
		{
			rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aquery->FieldByName("PressID")->AsInteger );
		}

		datapressday->Date =  aquery->FieldByName("Pressdate")->AsDateTime ;
		edpresscount->Text = aquery->FieldByName("PressCount")->AsString.Trim() ;
		edISBNtype->Text = aquery->FieldByName("ISBNType")->AsString.Trim()  ;
		edyizhe->Text = aquery->FieldByName("Yizhe")->AsString.Trim()  ;
		edprintcount->Value = aquery->FieldByName("Printcount")->AsInteger ;
		edaffix->Text = aquery->FieldByName("Affix")->AsString.Trim()  ;
		cbformat->Text = aquery->FieldByName("Bookformat")->AsString.Trim()  ;
		cbbind->Text = aquery->FieldByName("Bind")->AsString.Trim()  ;
		edbook->Text = aquery->FieldByName("Collectbook")->AsString.Trim()  ;
		edbk->Text = aquery->FieldByName("Bk")->AsString.Trim()  ;
		edhuojiangstate->Text = aquery->FieldByName("huojiangstate")->AsAnsiString.Trim()  ;
		spepack->Text = aquery->FieldByName("BookWords")->AsAnsiString.Trim()  ;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewBookModify::SpeedButton1Click(TObject *Sender)
{
	editisbn->Text =  BuildISBNCode(editisbn->Text);
}
//---------------------------------------------------------------------------
void TfrmNewBookModify::ReadyData()
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
	 cbtype->AddItem(aq->FieldByName("ID")->AsAnsiString + aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
	 aq->Next();
   }
	sql = "select ID,PresentNum,abbreviatedname from BS_PressInfo ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
      while(!aq->Eof)
   {
	 rcbpress->AddItem(aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
	 cbpress->AddItem(aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
	 aq->Next();
   }

   	sql = "declare @modify int ;"
			" exec modifprice " + IntToStr(ybkcatalogid) + ",-1," + IntToStr(fstgid) + ",@modify output ; "
			" select @modify as modify" ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->FieldByName("modify")->AsInteger == 1 ) {
		editqikanprice->Enabled = false;
		editprice->Enabled = false;
	}

   delete aq;
}
void __fastcall TfrmNewBookModify::BtnSaveClick(TObject *Sender)
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	int pressid = -1,booktypeid = -1;
	if (pgqikan->Visible ) {
		if (cbpress->Text != "") {
			try {
				pressid = (int)cbpress->Items->Objects[rcbpress->ItemIndex];
			} catch (...) {
				MessageBoxA(0,"请选择正确的出版社!","警告",MB_ICONASTERISK);
				return;
			}
		}
		if (cbtype->Text != "") {
			try {
				booktypeid = (int)cbtype->Items->Objects[cbtype->ItemIndex];
			} catch (...) {
				MessageBoxA(0,"请选择正确的类别!","警告",MB_ICONASTERISK);
				return;
			}
		}
		if (edyearprice->Text == "") {
			edyearprice->Text = "0";
		}
		if (editqikanname->Text == "" )
		{
			MessageBox(0,"刊名不能为空!","新录书目",MB_ICONWARNING);
			return;
		}
		if (editqikanprice->Text == "") {
			editqikanprice->Text = "0";
		}

		int totalkanqi;
		float price = 0.0;
		int qikanshu;
		if (editqikanqihao->Text == "") {
			MessageBox(0,"期刊号不能为空!","提示",MB_ICONWARNING);
			editqikanqihao->SetFocus();
			return;
		}
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
		}

	}
	else
	{
		if (editbookname->Text == "") {
			MessageBox(0,"书名不能为空!","新录书目修改",MB_ICONWARNING);
			return;
		}
		if (editprice->Text  == "") {
			MessageBox(0,"定价不能为空!","新录书目修改",MB_ICONWARNING);
			return;
		}


		if (rcbpress->Text=="") {
			pressid  = -1;
		} else
		{
			try {
				pressid = (int)(rcbpress->Items->Objects[rcbpress->ItemIndex]);
			} catch (...) {
				return;
			}
		}
	}

	if (newbook == 1) {
		sql = "select id from BS_BookCatalog where ISBN = '" + editisbn->Text + "' and Barcode = '" + editcode->Text + "' and Price = " + editprice->Text + " and Author = '" + editauthor->Text + "' and Name = '" + editbookname->Text + "' and PressID = " + IntToStr(pressid) + " and PressCount like '%" + edpresscount->Text + "%'" ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->IsEmpty() ) {
			comAddcatalog->Parameters->ParamByName("@ISBN")->Value = editisbn->Text;
			comAddcatalog->Parameters->ParamByName("@Name")->Value = editbookname->Text;
			comAddcatalog->Parameters->ParamByName("@Price")->Value = editprice->Text;
			comAddcatalog->Parameters->ParamByName("@Author")->Value = editauthor->Text;
			comAddcatalog->Parameters->ParamByName("@PressCount")->Value = edpresscount->Text;
			comAddcatalog->Parameters->ParamByName("@Press")->Value = rcbpress->Text;
			comAddcatalog->Execute();
			newcatalogid =  comAddcatalog->Parameters->ParamByName("@return_value")->Value;
		}
		else
		{
			newcatalogid = aq->FieldByName("id")->AsInteger ;
		}
		delete aq;
		ModalResult = mrOk ;
	}
	else
	{
		if (pgqikan->Visible ) {
			if (MessageBox(0,"确定修改该期刊吗？","期刊修改",MB_ICONQUESTION|MB_OKCANCEL )==1) {

                sql = "update BS_BookCatalog set isbn ='" + editqikanissn->Text + "', name='" +editqikanname->Text + "',userdefcode = '";
				sql = sql +  editqikanself->Text + "', price = " + editqikanprice->Text + ",barcode = '" + editqikanmao->Text ;
				sql = sql + "', presscount = '" + editqikanqihao->Text + "',year = '" + sedyear->Text + "',PressID = " + IntToStr(pressid) + ",smallBookTypeID = " + IntToStr(booktypeid) ;
				sql = sql + ",Bookformat = '" + cbkanqi->Text + "',yearprice = " + edyearprice->Text + ",kanhao = '" + edkanhao->Text + "',tongyikanhao = '" + edtykanhao->Text + "'";
				sql = sql + ",duokan = " + BoolToStr(chduokan->Checked);
				if (chduokan->Checked ) {
					sql = sql + ",duokantext = '" + cbduokan->Text + "',duokannum = " + sedkannum->Text ;
				}
				else
				{
					sql = sql + ",duokantext = '',duokannum = 0 ";
				}
				sql = sql  + " where ID = " + IntToStr(catalogid) ;


				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				try {
					aq->ExecSQL();
				} catch (...) {
				}
				delete aq;
				ModalResult = mrOk ;
			}
		}
		else
		{
			if (MessageBox(0,"确定修改该书目吗？","书目修改",MB_ICONQUESTION|MB_OKCANCEL )==1) {
				if (editprice->Text == "") {
					editprice->Text = "0.00";
				}
				int booktypeid;

				if (rcbtype->Text == "") {
					booktypeid = -1;
				} else
				{
					try {
						booktypeid = (int)(rcbtype->Items->Objects[rcbtype->ItemIndex]);
					} catch (...) {
						return;
					}
				}
				logmessage = "修改书目《" + ybookname + "》的信息为《" + editbookname->Text.Trim() + "》";
				AddEvent(1,"书目信息修改",fuserid,fstgid,logmessage,fcon);

				sql = "update BS_BookCatalog set Barcode = '" + editcode->Text + "',ISBN = '" + editisbn->Text + "',Name = '" + editbookname->Text;
				sql = sql + "',UserDefCode = '" + editbookself->Text + "',Author = '" + editauthor->Text + "',Price = " + editprice->Text;
				sql = sql + ",PressID = " + IntToStr(pressid) + ",smallbooktypeid = " + IntToStr(booktypeid) + ",Pressdate = '" + DateToStr(datapressday->Date);
				sql = sql + "',PressCount = '" + edpresscount->Text + "',ISBNType = '" + edISBNtype->Text + "',Yizhe = '" + edyizhe->Text;
				sql = sql + "',Printcount = " + IntToStr(edprintcount->IntValue) + ",Affix = '" + edaffix->Text + "',Bookformat = '" + cbformat->Text;
				sql = sql + "',Bind = '" + cbbind->Text + "',Collectbook = '" + edbook->Text + "',BookWords = " + IntToStr(spepack->IntValue) ;
				sql = sql + ",Bk = '" + edbk->Text + "',huojiangstate = '" + edhuojiangstate->Text + "' where id = " + IntToStr(catalogid);
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				try {
					aq->ExecSQL();
				} catch (...) {
				}
				delete aq;
				ModalResult = mrOk ;
			}
		}
	}
}
//---------------------------------------------------------------------------
void TfrmNewBookModify::Press1(int mode)
{

		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		AnsiString sql;
		if (mode == 1) {
			sql = "select ID,presentnum,abbreviatedname from BS_PressInfo where abbreviatedname like '%" + edpress->Text.Trim() + "%'" ;
		}
		else
		{
			sql = "select ID,presentnum,abbreviatedname from BS_PressInfo ";
		}
		cbpress->Clear();
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while(!aq->Eof)
		{
			cbpress->AddItem(aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		if (mode == 1) {
			cbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger);
		}

		delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewBookModify::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewBookModify::editcodeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        editisbn->Text = editcode->Text ;
	  	editbookname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editbooknameKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if (Key==VK_RETURN) {
		if (editbookname->Text =="") {
			MessageBox(0,"书名不能为空!","新录书目",MB_ICONWARNING);
			return;
		}
		char* t;
		char t2;
		String t1,t3,t4;
		t1 = editbookname->Text;
		int t5=1,i = editbookname->Text.Length() ;
		for( int j=1;j<=i;j++)
		{
			t3 = t1.SubString(j,1);
			t = t3.t_str();
			Word k = int (t[0])<<8;
			k = k >> 8;
			if(k<160) continue;
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
char TfrmNewBookModify::GetPYIndexChar(char *str)
{

	Word x = 0;
	Word y = 0;

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
void __fastcall TfrmNewBookModify::editpriceKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key==VK_RETURN) {
		editauthor->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editauthorKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key==VK_RETURN)
	{
		rcbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::rcbtypeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key==VK_RETURN)
	{
	   rcbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::rcbpressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewBookModify::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
		if (Key == VK_F4) {
		BtnSave->Click();
	}
		if (Shift.Contains(ssCtrl)&& Key ==81  ) {
	   BtnExit->Click();
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edqueryKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (edquery->Text != "") {
			Press(1);
		}
		rcbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------
void TfrmNewBookModify::Press(int mode)
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

void __fastcall TfrmNewBookModify::FormShow(TObject *Sender)
{
	if (newbook == 1) {
    	this->Caption = "更换书目";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editcodeKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		AnsiString isbn;
		try {
			isbn = BuildISBNCode(editcode->Text);
		} catch (...) {
		}
		editisbn->Text = isbn;
		editisbn->SetFocus();
		if (isbn.Length() == 13 || isbn.Length() == 10 ) {
        	isbn = isbn.Delete(isbn.Length(),1);
		}

		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		AnsiString sql;
		sql = "select BS_BookCatalog.ID,ISBN,Name,UserDefCode,Price,PressCount,Author,AbbreviatedName from BS_BookCatalog left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id where BS_BookCatalog.isbn like '%" + isbn + "%' or BS_BookCatalog.Barcode like '%" + isbn + "%'";
		aq->Connection = fcon;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount >= 1 ) {
			Tfrmchangeselect *frm = new Tfrmchangeselect(Application,aq);
			if (frm->ShowModal() == mrOk)
			{
				if (frm->continuechange == 1) {
                	delete aq;
					delete frm;
				}
				else
				{
					newcatalogid = aq->FieldByName("ID")->AsInteger ;
					delete aq;
					delete frm;
                    ModalResult = mrOk ;
				}
			}
			else
			{
				delete aq;
				delete frm;
			}
		}
		else
		{
			delete aq;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editisbnKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		AnsiString bro;
		try {
			bro = ISBNToBarcode(editisbn->Text);
		} catch (...) {
		}
		editcode->Text =  bro;
		editbookname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::chduokanClick(TObject *Sender)
{
	if (chduokan->Checked ) {
		cbduokan->Visible = true;
		Label31->Visible = true;
		sedkannum->Visible = true;
	}
	else
	{
		cbduokan->Visible = false;
		Label31->Visible = false;
		sedkannum->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editqikanmaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		if (editqikanmao->Text != "") {
			if (editqikanmao->Text.Length() >= 13 ) {
				editqikanqihao->Text = editqikanmao->Text.SubString(14,editqikanmao->Text.Length()-13);
				editqikanmao->Text = editqikanmao->Text.SubString(0,13);

				editqikanname->SetFocus();
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

void __fastcall TfrmNewBookModify::editqikanqihaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
    	if (editqikanqihao->Text == "") {
			MessageBox(0,"期刊号不能为空!","提示",MB_ICONWARNING);
			editqikanqihao->SetFocus();
			return;
		}
		editqikanname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editqikanissnKeyPress(TObject *Sender, wchar_t &Key)

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

void __fastcall TfrmNewBookModify::editqikannameKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		if (editqikanname->Text == "") {
			MessageBoxA(0,"请输入期刊名!","警告",MB_ICONASTERISK);
			return;
		}
		editqikanself->Text = GetSelf(editqikanname->Text.Trim() );
		sedyear->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::sedyearKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (editqikanprice->Enabled ) {
			editqikanprice->SetFocus();
		}
		else
		{
        	edpress->SetFocus();
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editqikanpriceExit(TObject *Sender)
{
	float price;
	try {
		price = StrToFloat(editqikanprice->Text);
	} catch (...) {
		return;
	}
	editqikanprice->Text = FormatFloat("0.00",price);
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editqikanpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == VK_RETURN) {
	if (editqikanprice->Text=="￥0.00") {
		MessageBoxA(0,"请输入定价!","警告",MB_ICONASTERISK);
		return;
	}
	edpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edpressKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (edpress->Text != "") {
			Press1(1);
		}
		cbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::cbpressKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		cbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::cbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        cbkanqi->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::cbkanqiExit(TObject *Sender)
{
	int totalkanqi;
	float price = 0.0;
	int qikanshu;
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
		edyearprice->Text = FloatToStr(price*totalkanqi);
	}
	try {
		qikanshu = StrToInt(editqikanqihao->Text);
	} catch (...) {
	}
	if (totalkanqi < qikanshu) {
		editqikanqihao->SetFocus();
		MessageBoxA(0,"录入期数过大，请重新录入！","提示",MB_ICONASTERISK);
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::cbkanqiKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        chduokan->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::chduokanKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (cbduokan->Visible ) {
			cbduokan->SetFocus();
		}
		else
		{
			edkanhao->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::cbduokanKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        sedkannum->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::sedkannumExit(TObject *Sender)
{
	int totalkanqi;
	float price = 0.0;
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
		edyearprice->Text = FloatToStr(price*totalkanqi*sedkannum->Value);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::sedkannumKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edkanhao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edkanhaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edtykanhao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edtykanhaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edyearprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edyearpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------
AnsiString TfrmNewBookModify::BarCodeToISSN(AnsiString BarCode)
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
AnsiString TfrmNewBookModify::ISSNToBarCode(AnsiString ISSN)
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
AnsiString TfrmNewBookModify::GetSelf(AnsiString context)
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

void __fastcall TfrmNewBookModify::editbooknameKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (editbookself->Text == "") {
			editbookself->Text =  GetSelf(editbookname->Text);
		}
		editbookself->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editbookselfKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (editprice->Enabled ) {
			editprice->SetFocus();
		}
		else
		{
			editauthor->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        editauthor->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editauthorKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        spepack->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::rcbtypeKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
    	edquery->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::rcbpressKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        datapressday->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::datapressdayKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edpresscount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edpresscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
       edhuojiangstate->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edISBNtypeKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edyizhe->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edyizheKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edprintcount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edprintcountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edaffix->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edaffixKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        cbformat->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::cbformatKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        cbbind->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::cbbindKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edbook->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edbookKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edbk->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmNewBookModify::edbkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edhuojiangstateKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::spepackKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        rcbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

