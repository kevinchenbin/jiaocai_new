//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Catalogkanli.h"
#include "ExcelImport.h"
#include "BookQuery.h"
#include "PressAdminForm.h"
#include "BooKTypeAdminForm.h"
#include "Setunite.h"
#include "mutibooktongyi.h"
#include "Addsyslog.h"
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
#pragma link "RzDTP"
#pragma resource "*.dfm"
TfrmCatalogkanli *frmCatalogkanli;
//---------------------------------------------------------------------------
__fastcall TfrmCatalogkanli::TfrmCatalogkanli(TComponent* Owner,TADOConnection *con,int stgid,int userid)
	: TForm(Owner)
{
   aquery->Connection = con;
   query->Connection = con;
   fcon = con;
   fstgid = stgid;
   fuserid = userid;
   editqikanqihao->Text = "0";
   ReadyData();
   int maxid;
   AnsiString sql;
   sql = "select max(id) as id from BS_BookCatalog " ;
   query->Close();
   query->SQL->Clear();
   query->SQL->Add(sql);
   query->Open();
   maxid = query->FieldByName("id")->AsInteger + 1;
   sql = "select A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,"
		 "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(maxid) ;
   if (cbsaletype->Text == "ͼ��") {
		sql = sql + " and A.type = 0";
   }
   else if (cbsaletype->Text == "�ڿ�") {
		sql = sql + " and A.type = 1";
   }
   else if (cbsaletype->Text == "�ľ�") {
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
   datapressday->Date = Date();
   PageControlBook->ActivePage = tsbase;
	modle = 1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::FormClose(TObject *Sender, TCloseAction &Action)
{
  	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::editcodeKeyPress(TObject *Sender, wchar_t &Key)
{
	String sql;
	if (Key==VK_RETURN)
	{
		AnsiString barcode = editcode->Text.Trim() ;
		if (barcode != "" && barcode.Length() != 13 ) {
			MessageBox(0,"��������ȷ����!","�������",MB_ICONWARNING);
			return;
		}

		if (modle == 1) {
        	sql = "select A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,"
			 "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,"
			 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
			 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where barcode =  '" + editcode->Text + "'";
		   if (cbsaletype->Text == "ͼ��") {
				sql = sql + " and A.type = 0";
			}
			else if (cbsaletype->Text == "�ڿ�") {
				sql = sql + " and A.type = 1";
			}
			else if (cbsaletype->Text == "�ľ�") {
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

		   ((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "��0.00";
		   float totalprice = 0.00;
		   while (!aquery->Eof)
		   {
				totalprice = totalprice + aquery->FieldByName("Price")->AsFloat;
				aquery->Next();
		   }
		   edtotalrecord->Text = IntToStr(aquery->RecordCount);
		   edtotalmayang->Text = FormatFloat("��0.00",totalprice);
		}
		int pressid = BrocodeToPress(editcode->Text);
		   rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)pressid );
		   editisbn->Text = editcode->Text ;
		   editbookname->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::SpeedButton1Click(TObject *Sender)
{
  	editisbn->Text =  BuildISBNCode(editisbn->Text);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::editbooknameKeyPress(TObject *Sender, wchar_t &Key)
{
	   if (Key==VK_RETURN) {
		 if (editbookname->Text =="") {
				MessageBox(0,"��������Ϊ��!","��¼��Ŀ",MB_ICONWARNING);
				return;
		 }
		 if (editbookself->Text == "") {
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
		 }
		 editbookself->SetFocus();
	   }

}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::editpriceKeyPress(TObject *Sender, wchar_t &Key)
{
	String sql;
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}

	if (Key==VK_RETURN) {
		if (editprice->Text == "") {
			editprice->Text = "0.00";
		}
		else
		{
			String price = editprice->Text ;
			price = price.SubString(price.Pos("��")+1,price.Length()-price.Pos("��") );
			editprice->Text = price;
		}
		float fprice = StrToFloat(editprice->Text) ;
		editprice->Text = FormatFloat("��0.00",fprice);
		editauthor->SetFocus();
	}
}
void TfrmCatalogkanli::ReadyData()
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
        checknewsupplier();
        disablenewsupplierornewbook();

}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::editauthorKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN)
	{
		spepack->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::rcbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN)
	{
	   edquery->SetFocus();
	}
}
//---------------------------------------------------------------------------
String  TfrmCatalogkanli:: GetID()
{
	return ID;
}
void __fastcall TfrmCatalogkanli::rcbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN)
	{
	   datapressday->SetFocus();
	}
}
char TfrmCatalogkanli::GetPYIndexChar(char *str)
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
void __fastcall TfrmCatalogkanli::BtnSaveClick(TObject *Sender)
{
	if (edtotalmayang->Text == "") {
        edtotalmayang->Text = "0";
	}
	String mayang = edtotalmayang->Text ;
	mayang = mayang.SubString(mayang.Pos("��")+1,mayang.Length()-mayang.Pos("��") );
	//edtotalmayang->Text = mayang;
	float totalprice = StrToFloat(mayang);
 if (1 == type || 2 == type) {
	if (modle == 1) {


	 if (1 == type) {
		 PostMessage(editqikanfaxing->Handle , WM_KEYDOWN,VK_RETURN,0);
		 pcqikan->Enabled = false;
		 modle = 0;
		 return;
	  }
	  if (2 == type ) {
		 PostMessage(editwenjuprice->Handle , WM_KEYDOWN,VK_RETURN,0);
		 pcwenju->Enabled = false;
		 modle = 0;
		 return;
	  }

	}
  if (modle == 2) {   //�޸�
	 if (1 == type ) {       //�ڿ�
		if (MessageBox(0,"ȷ���޸��ڿ���Ϣ��","�ڿ�" ,MB_OKCANCEL||MB_ICONQUESTION)==1)
	 {
	   AnsiString sql;
	   sql = "select Price from BS_BookCatalog where id = " + aqinsert->FieldByName("ID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		totalprice = totalprice - query->FieldByName("Price")->AsFloat;
		editqikanqihao->Text = "0";
	   sql = "update BS_BookCatalog set isbn ='" + editqikanissn->Text + "', name='" +editqikanname->Text + "',userdefcode = '";
	   sql = sql +  editqikanself->Text + "', price = " + editqikanprice->Text + ",barcode = '" + editqikanmao->Text ;
	   sql = sql + "', presscount = " + editqikanqihao->Text + ", bk = '"  +  editqikanfaxing->Text + "'";
	   sql = sql  + " where ID = " + aqinsert->FieldByName("ID")->AsAnsiString ;

		TADOQuery * aq = new TADOQuery(NULL);
		aq->Connection = fcon;
		aq->SQL->Add(sql);
		aq->ExecSQL();
		totalprice = totalprice + StrToFloat(editqikanprice->Text);
		delete aq;
		aqinsert->Refresh();
		BtnClear->Enabled = true;
		BtnCancel->Enabled = true;
		BtnDelete->Enabled = true;
		BtnImport->Enabled = true;
		BtnExport->Enabled = true;
		BtnNew->Enabled = true;
		BtnJumptoLine->Enabled = true;
		modle = 0;
		pcqikan->Enabled = false;
	 }
	 }
	 if (2 == type ) {      //  �ľ�
	 if (MessageBox(0,"ȷ���޸��ľ���Ϣ��","�ľ�" ,MB_OKCANCEL||MB_ICONQUESTION)==1)
	 {
		   AnsiString sql;
		   sql = "select Price from BS_BookCatalog where id = " + aqinsert->FieldByName("ID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		totalprice = totalprice - query->FieldByName("Price")->AsFloat;
	   sql = "update BS_BookCatalog set isbn ='" + editwenjutiaomao->Text + "', name='" +editwenjuname->Text + "',userdefcode = '";
	   sql = sql +  editwenjuself->Text + "', price = " + editwenjuprice->Text + ",barcode = '" + editwenjutiaomao->Text ;
	   sql = sql  + "' where ID = " + aqinsert->FieldByName("ID")->AsAnsiString ;

		TADOQuery * aq = new TADOQuery(NULL);
		aq->Connection = fcon;
		aq->SQL->Add(sql);
		aq->ExecSQL();
		totalprice = totalprice + StrToFloat(editwenjuprice->Text);
		delete aq;
		aqinsert->Refresh();
		BtnClear->Enabled = true;
		BtnCancel->Enabled = true;
		BtnDelete->Enabled = true;
		BtnImport->Enabled = true;
		BtnExport->Enabled = true;
		BtnNew->Enabled = true;
		BtnJumptoLine->Enabled = true;
		modle = 0;
		pcwenju->Enabled = false;
	 }
	 }
	 edtotalrecord->Text = IntToStr(aqinsert->RecordCount);
	 edtotalmayang->Text = FormatFloat("��0.00",totalprice);

	 return;

  }
 }
 


   String sql;
   if (editbookname->Text == "") {
		MessageBox(0,"��������Ϊ��!","ϵͳ��ʾ",MB_ICONWARNING);
		return;
   }
   if (editprice->Text  == "") {
		MessageBox(0,"���۲���Ϊ��!","ϵͳ��ʾ",MB_ICONWARNING);
		return;
   }
   if (editprice->Text == "") {
   		editprice->Text = "0.00";
   }
   else
   {
		String price = editprice->Text ;
		price = price.SubString(price.Pos("��")+1,price.Length()-price.Pos("��") );
		editprice->Text = price;
   }
 
   int pressid,bktypeid;
   if (rcbpress->Text!="") {
		try {
			pressid = (int)(rcbpress->Items->Objects[rcbpress->ItemIndex]);
		} catch (...) {
			MessageBox(0,"��ѡ����ȷ�ĳ�����!","��¼��Ŀ",MB_ICONWARNING);
			return;
		}
   }
   if (rcbtype->Text != "") {
    	try {
			bktypeid = (int)(rcbtype->Items->Objects[rcbtype->ItemIndex]);
		} catch (...) {
			MessageBox(0,"��ѡ����ȷ�����!","��¼��Ŀ",MB_ICONWARNING);
			return;
		}
   }

   if (modle == 1) {

		if (MessageBox(0,"ȷ������������","��¼��Ŀ",MB_ICONQUESTION|MB_OKCANCEL )==1) {
            sql = "select * from BS_BookCatalog where ISBN = '" + editisbn->Text + "' and Name = '" + editbookname->Text.Trim() + "' and Price = " + editprice->Text ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount > 0) {
				if (MessageBox(0,"�ǲ����ظ�¼�룿","��¼��Ŀ",MB_ICONQUESTION|MB_OKCANCEL )!=1) {
                	return;
				}
			}
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
			aquery->FieldByName("PressCount")->AsString  = edpresscount->Text ;
			aquery->FieldByName("ISBNType")->AsString = edISBNtype->Text ;
			aquery->FieldByName("Yizhe")->AsString = edyizhe->Text ;
			aquery->FieldByName("Printcount")->AsInteger = edprintcount->Value ;
			aquery->FieldByName("Affix")->AsString = edaffix->Text ;
			aquery->FieldByName("Bookformat")->AsString = cbformat->Text ;
			aquery->FieldByName("Bind")->AsString = cbbind->Text ;
			aquery->FieldByName("Collectbook")->AsString = edbook->Text ;
			aquery->FieldByName("BookWords")->AsInteger  = spepack->Value ;
		  	aquery->FieldByName("huojiangstate")->AsString = edhuojiangstate->Text ;
			aquery->FieldByName("Bk")->AsString = edbk->Text ;
			//aquery->FieldByName("taoshu")->AsString = edtaoshu->Text ;
		   //	 if (chtaoshu->Checked) {
		   //		aquery->FieldByName("taoshu")->AsInteger=1;
		   //	 }else
		  //	 {
		  //		aquery->FieldByName("taoshu")->AsInteger=0;
		 //	 }


			aquery->UpdateBatch(arAll);
			totalprice = totalprice + StrToFloat(editprice->Text);
		if (!rzcbinput->Checked) {
			 ID =  aquery->FieldByName("ID")->AsAnsiString ;
			 ModalResult = mbOK ;
			 modle = 0;
			 tsbase->Enabled = false;
			 tsdetail->Enabled = false;
			 //PageControlBook->Enabled = false;
		 }else     //����¼��
		 {
			editcode->Text  = "";
			editisbn->Text = "";
			editbookname->Text = "";
			editbookself->Text = "";
			editauthor->Text = "";
			rcbpress->ItemIndex = -1;
			rcbtype->ItemIndex  = -1;
			editprice->Text = "��0.00";
			datapressday->Date = Date();
			edpresscount->Text = "";
			edISBNtype->Text = "";
			edyizhe->Text = "";
			edprintcount->Value = 0;
			edaffix->Text = "";
			cbformat->ItemIndex = 0;
			cbbind->ItemIndex = 0;
			edbook->Text = "";
			edhuojiangstate->Text = "";
			spepack->Value = 1;
			edbk->Text = "";
			PageControlBook->ActivePage = tsbase;
			editcode->SetFocus();
			ID =  aquery->FieldByName("ID")->AsAnsiString ;
			modle = 1;
		 }
		 BtnClear->Enabled = true;
		 BtnCancel->Enabled = true;
		 BtnDelete->Enabled = true;
		 BtnImport->Enabled = true;
		 BtnExport->Enabled = true;
		 BtnNew->Enabled = true;
		 BtnJumptoLine->Enabled = true;
	  }
   }
   if (modle == 2) {
		AnsiString sql;
		sql = "select Price from BS_BookCatalog where id = " + aquery->FieldByName("ID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		totalprice = totalprice - query->FieldByName("Price")->AsFloat;
    	int pressid,booktypeid;
		if(editbookname->Text == "" )
			return;
		if (aquery->RecordCount == 0)
			return;
		if (rcbpress->Text=="") {
			pressid  = -1;
		} else
		{
			pressid = (int)(rcbpress->Items->Objects[rcbpress->ItemIndex]);
		}
		if (rcbtype->Text == "") {
			booktypeid = -1;
		} else
		{
			booktypeid = (int)(rcbtype->Items->Objects[rcbtype->ItemIndex]);
		}
		if (MessageBox(0,"ȷ���޸���Ŀ��Ϣ��","�޸���Ŀ" ,MB_OKCANCEL)==1)
		{
			logmessage = "�޸���Ŀ��" + aquery->FieldByName("name")->AsAnsiString + "������ϢΪ��" + editbookname->Text.Trim() + "��";
			AddEvent(1,"ͼ��Ŀ¼����",fuserid,fstgid,logmessage,fcon);

			sql = "update BS_BookCatalog set name = '" + editbookname->Text.Trim() + "',userdefcode = '" + editbookself->Text.Trim() + "',isbn = '" + editisbn->Text.Trim() + "',Barcode = '" + editcode->Text ;
			sql = sql + "',author = '" +  editauthor->Text.Trim()  + "',price = " + editprice->Text + ",PressID = " + IntToStr(pressid);
			sql = sql + ",smallbooktypeid = " + IntToStr(booktypeid) + ",Pressdate = '" + DateToStr(datapressday->Date) + "',PressCount = '" + edpresscount->Text ;
			sql = sql + "',ISBNType = '" + edISBNtype->Text + "',Yizhe = '" + edyizhe->Text + "',Printcount = " + int(edprintcount->Value) ;
			sql = sql + ",Affix = '" + edaffix->Text + "',Bookformat = '" + cbformat->Text + "',Bind = '" + cbbind->Text ;
			sql = sql + "',Collectbook = '" + edbook->Text + "',BookWords = " + int(spepack->Value) + ",Bk = '" + edbk->Text + "',huojiangstate = '" + edhuojiangstate->Text + "',";
		  /*	if (chtaoshu->Checked ) {
				sql = sql + "taoshu = 1";
			}
			else
			{
				sql = sql + "taoshu = 0";
			} */
			sql = sql + " where ID = " + aquery->FieldByName("ID")->AsString ;
			try {
            	query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
				totalprice = totalprice + StrToFloat(editprice->Text);
				//((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "��0.00";
				BtnClear->Enabled = true;
				BtnCancel->Enabled = true;
				BtnDelete->Enabled = true;
				BtnImport->Enabled = true;
				BtnExport->Enabled = true;
				BtnNew->Enabled = true;
				BtnJumptoLine->Enabled = true;
				modle = 0;
			} catch (...) {
			}
			aquery->Active = false;
			aquery->Active = true;
			((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "��0.00";
			tsbase->Enabled = false;
			tsdetail->Enabled = false;
			//PageControlBook->Enabled = false;
            editprice->Enabled = true;
		}
   }
  // float totalprice = 0.00;
  // while (!aquery->Eof)
   //{
   //		totalprice = totalprice + aquery->FieldByName("Price")->AsFloat;
   //		aquery->Next();
   //}
   edtotalrecord->Text = IntToStr(aquery->RecordCount);
   edtotalmayang->Text = FormatFloat("��0.00",totalprice);
}
//---------------------------------------------------------------------------

void TfrmCatalogkanli::Query(String condition)
{
	if (aquery->Active)
	{
		aquery->Active = false;
	}
	String sql;
	sql = "select A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,"
			 "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,A.taoshu,"
			 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
			 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID " + condition;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Active = true;
	((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "��0.00";
}

void __fastcall TfrmCatalogkanli::edtQueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key==VK_RETURN) {
		BtnClear->Enabled = true;
		BtnCancel->Enabled = true;
		BtnDelete->Enabled = true;
		BtnImport->Enabled = true;
		BtnExport->Enabled = true;
		BtnNew->Enabled = true;
		float totalprice = 0.00;
		while (!aquery->Eof)
		{
			totalprice = totalprice + aquery->FieldByName("Price")->AsFloat;
			aquery->Next();
		}
		edtotalrecord->Text = IntToStr(aquery->RecordCount);
		edtotalmayang->Text = FormatFloat("��0.00",totalprice);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::BtnNewClick(TObject *Sender)
{
	int maxid;
	AnsiString sql;
	sql = "select max(id) as id from BS_BookCatalog " ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	maxid = query->FieldByName("id")->AsInteger + 1;
	sql = "select A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,"
		  "A.Yizhe,A.Pressdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,A.taoshu,"
		  "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		  " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(maxid) ;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Active = true;
	if ( 2== type ) {
		editwenjutiaomao->Text ="";
		editwenjuname->Text = "";
		editwenjuself->Text = "";
		editwenjuprice->Text="��0.00";
		editwenjutiaomao->Text= "";
		editwenjutiaomao->SetFocus();
		pcwenju->Enabled = true;
		return;
	}
	if (1 == type ) {
		editqikanissn->Text ="";
		editqikanname->Text = "";
		editqikanself->Text = "";
		editqikanprice->Text="��0.00";
		editqikanmao->Text= "";
		editqikanqihao->Text="";
		editqikanfaxing->Text = "";
		editqikanmao->SetFocus();
		pcqikan->Enabled = true;
        return;
	}
	edquery->Text = "";
	Press(0);

	//PageControlBook->Enabled = true;
	PageControlBook->ActivePage = tsbase;
	tsbase->Enabled = true;
	tsdetail->Enabled = true;
	editcode->SetFocus();
	modle = 1;// ����ģʽ
	BtnClear->Enabled = false;
	BtnCancel->Enabled = false;
	BtnDelete->Enabled = false;
	BtnImport->Enabled = false;
	BtnExport->Enabled = false;
	BtnNew->Enabled = false;
	BtnJumptoLine->Enabled = false;
	BtnSave->Enabled = true;

	editcode->Text = "";
	editisbn->Text = "";
	editbookname->Text = "";
	editbookself->Text = "";
	editprice->Text = "��0.00";
	editauthor->Text = "";
	rcbtype->Text = "";
	rcbpress->Text = "";
	datapressday->Date = Date();
	edpresscount->Text = "";
	edISBNtype->Text = "";
	edyizhe->Text = "";
	edprintcount->Value = 1;
	edaffix->Text = "";
	cbformat->ItemIndex = 0;
	cbbind->ItemIndex = 0;
	edbook->Text = "";
	spepack->Value = 1;
	edhuojiangstate->Text = "";
	edbk->Text = "";

}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogkanli::BtnClearClick(TObject *Sender)
{
	modle = 2;//  �޸�ģʽ
	if (type == 0 && (!aquery->Active || aquery->RecordCount == 0) ) {
		return;
	}
	else if ((type == 1 || type == 2)&& (!aqinsert->Active || aqinsert->RecordCount == 0)) {
    	return;
	}
	AnsiString sql;
	if (type == 0) {
    	sql = "declare @modify int ;"
			" exec modifprice " + aquery->FieldByName("ID")->AsString  + ",-1," + IntToStr(fstgid) + ",@modify output ; "
			" select @modify as modify" ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->FieldByName("modify")->AsInteger == 1 ) {
			editprice->Enabled = false;
		}
	}
	BtnClear->Enabled = false;
	BtnCancel->Enabled = false;
	BtnDelete->Enabled = false;
	BtnImport->Enabled = false;
	BtnExport->Enabled = false;
	BtnNew->Enabled = false;
	BtnJumptoLine->Enabled = false;
	BtnSave->Enabled = true;

	pcqikan->Enabled = true;
	//PageControlBook->Enabled = true;
    tsbase->Enabled = true;
	tsdetail->Enabled = true;
	pcwenju->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::radiogroupClick(TObject *Sender)
{
	AnsiString sql;
	float totalprice = 0.00;
	modle = 0;
	if (radiogroup->ItemIndex == 0) {
		try {
			aquery->Active = false;
			aqinsert->Active = false;
			return;
		} catch (...) {
		}
	}
	else if (radiogroup->ItemIndex == 1) {
		sql = "select A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,"
			  "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,A.taoshu,"
			  "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
			  " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID";
		if (cbsaletype->Text == "ͼ��") {
			sql = sql + " where A.type = 0";
		}
		else if (cbsaletype->Text == "�ڿ�") {
			  ShowInput(1);
				aqinsert->DisableControls();
				while (!aqinsert->Eof)
				{
					totalprice = totalprice + aqinsert->FieldByName("Price")->AsFloat;
					aqinsert->Next();
				}
				aqinsert->EnableControls();
				edtotalrecord->Text = IntToStr(aqinsert->RecordCount);
				edtotalmayang->Text = FormatFloat("��0.00",totalprice);
			  return;
		}
		else if (cbsaletype->Text == "�ľ�") {
			ShowInput(2);
			aqinsert->DisableControls();
			while (!aqinsert->Eof)
			{
				totalprice = totalprice + aqinsert->FieldByName("Price")->AsFloat;
				aqinsert->Next();
			}
			aqinsert->EnableControls();
				edtotalrecord->Text = IntToStr(aqinsert->RecordCount);
				edtotalmayang->Text = FormatFloat("��0.00",totalprice);
			return;
		}
		else
		{
			sql = sql + " where A.type > 2";
		}
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "��0.00";
		BtnClear->Enabled = true;
		BtnCancel->Enabled = true;
		BtnDelete->Enabled = true;
		BtnImport->Enabled = true;
		BtnExport->Enabled = true;
		BtnNew->Enabled = true;
	}
	else if (radiogroup->ItemIndex == 2) {
		sql = "select A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,"
			  "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,A.taoshu,"
			  "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
			  " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where Unavailable = 0";
		if (cbsaletype->Text == "ͼ��") {
			sql = sql + " and A.type = 0";
		}
		else if (cbsaletype->Text == "�ڿ�") {
			 ShowInput(9);
			aqinsert->DisableControls();
			while (!aqinsert->Eof)
			{
				totalprice = totalprice + aqinsert->FieldByName("Price")->AsFloat;
				aqinsert->Next();
			}
			aqinsert->EnableControls();
			edtotalrecord->Text = IntToStr(aqinsert->RecordCount);
			edtotalmayang->Text = FormatFloat("��0.00",totalprice);
			return;
			 return;
		}
		else if (cbsaletype->Text == "�ľ�") {
			 ShowInput(8);
			aqinsert->DisableControls();
			while (!aqinsert->Eof)
			{
				totalprice = totalprice + aqinsert->FieldByName("Price")->AsFloat;
				aqinsert->Next();
			}
			aqinsert->EnableControls();
			edtotalrecord->Text = IntToStr(aqinsert->RecordCount);
			edtotalmayang->Text = FormatFloat("��0.00",totalprice);
			 return;
		}
		else
		{
			sql = sql + " where A.type > 2";
		}
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "��0.00";
		BtnClear->Enabled = true;
		BtnCancel->Enabled = true;
		BtnDelete->Enabled = true;
		BtnImport->Enabled = true;
		BtnExport->Enabled = true;
		BtnNew->Enabled = true;
	}
	else if (radiogroup->ItemIndex == 3) {
		sql = "select A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,"
			  "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,A.taoshu,"
			  "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
			  " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where Unavailable = 1";
		if (cbsaletype->Text == "ͼ��") {
			sql = sql + " and A.type = 0";
		}
		else if (cbsaletype->Text == "�ڿ�") {
		  ShowInput(1);
			  return;
		}
		else if (cbsaletype->Text == "�ľ�") {
				ShowInput(2);
			return;
		}
		else
		{
			sql = sql + " where A.type > 2";
		}
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "��0.00";
		BtnClear->Enabled = true;
		BtnCancel->Enabled = true;
		BtnDelete->Enabled = true;
		BtnImport->Enabled = true;
		BtnExport->Enabled = true;
		BtnNew->Enabled = true;
	}

	aquery->DisableControls();
	while (!aquery->Eof)
	{
		totalprice = totalprice + aquery->FieldByName("Price")->AsFloat;
		aquery->Next();
	}
	aquery->EnableControls();
	edtotalrecord->Text = IntToStr(aquery->RecordCount);
	edtotalmayang->Text = FormatFloat("��0.00",totalprice);


	if (type == 1) {
    	editqikanissn->Text ="";
		editqikanname->Text = "";
		editqikanself->Text = "";
		editqikanprice->Text="��0.00";
		editqikanmao->Text= "";
		editqikanqihao->Text="";
		editqikanfaxing->Text = "";
		editqikanmao->SetFocus();
	}
	else if (type == 2) {
    	editwenjutiaomao->Text ="";
		editwenjuname->Text = "";
		editwenjuself->Text = "";
		editwenjuprice->Text="��0.00";
		editwenjutiaomao->Text= "";
		editwenjutiaomao->SetFocus();
	}
	else
	{
		editcode->Text = "";
		editisbn->Text = "";
		editbookname->Text = "";
		editbookself->Text = "";
		editprice->Text = "��0.00";
		editauthor->Text = "";
		rcbtype->Text = "";
		rcbpress->Text = "";
		datapressday->Date = Date();
		edpresscount->Text = "";
		edISBNtype->Text = "";
		edyizhe->Text = "";
		edprintcount->Value = 1;
		edaffix->Text = "";
		cbformat->ItemIndex = 0;
		cbbind->ItemIndex = 0;
		edbook->Text = "";
		spepack->Value = 1;
		edhuojiangstate->Text = "";
		edbk->Text = "";
		edquery->Text = "";
		Press(0);
	}
	if (cbsaletype->Text == "ͼ��") {
     	BtnJumptoLine->Enabled = true;
	}

disablenewsupplierornewbook();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::BtnCancelClick(TObject *Sender)
{
    if (1 == type||2 == type) {
			if (!aqinsert->IsEmpty() ) {
				for (int i=0; i < dg->SelectedRows->Count; i++) {
					aqinsert->GotoBookmark(dg->SelectedRows->Items[i]);
					aqinsert->Edit();
					aqinsert->FieldByName("Unavailable")->Value = 0;
					aqinsert->UpdateBatch(arCurrent);
				}
		}
		return;
	}
	for (int i =0; i < DBGrid1->SelectedRows->Count ; i++) {
		aquery->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
		if (aquery->RecordCount > 0) {
			try {
				aquery->Edit();
				aquery->FieldByName("Unavailable")->Value = 0;
				aquery->UpdateBatch(arCurrent);
			} catch (...) {
			}
		}
	}
	aquery->Active = false;
	aquery->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::BtnDeleteClick(TObject *Sender)
{
	String mayang = edtotalmayang->Text ;
	mayang = mayang.SubString(mayang.Pos("��")+1,mayang.Length()-mayang.Pos("��") );
	AnsiString sql;
	if (1==type || 2== type) {
    	if (aqinsert->IsEmpty()) {
			return;
		}
		float totalprice = StrToFloat(mayang);
		if (!aqinsert->IsEmpty()) {
			if (MessageBox(0,"ȷ��Ҫɾ����","����" ,MB_ICONQUESTION||MB_OKCANCEL)==1)
			{
				for (int i=0; i < dg->SelectedRows->Count; i++) {
					aqinsert->GotoBookmark(dg->SelectedRows->Items[i]);
				  //	aqinsert->Edit();
				  totalprice = totalprice - aqinsert->FieldByName("Price")->AsFloat ;
					aqinsert->Delete();
				}
					aqinsert->UpdateBatch(arAll);
			}
		}
		edtotalrecord->Text = IntToStr(aqinsert->RecordCount);
		edtotalmayang->Text = FormatFloat("��0.00",totalprice);
		if ( 2== type ) {
			editwenjutiaomao->Text ="";
			editwenjuname->Text = "";
			editwenjuself->Text = "";
			editwenjuprice->Text="��0.00";
			editwenjutiaomao->Text= "";
			editwenjutiaomao->SetFocus();
			return;
		}
		if (1 == type ) {
			editqikanissn->Text ="";
			editqikanname->Text = "";
			editqikanself->Text = "";
			editqikanprice->Text="��0.00";
			editqikanmao->Text= "";
			editqikanqihao->Text="";
			editqikanfaxing->Text = "";
			editqikanmao->SetFocus();
			return;
		}
	}
	if (aquery->IsEmpty() ) {
		return;
	}
	if (MessageBox(0,"ȷ��ɾ����","����" ,MB_OKCANCEL)!=1)
	{
		return;
	}

	float totalprice = StrToFloat(mayang);
	for (int i =0; i < DBGrid1->SelectedRows->Count ; i++) {
		aquery->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
		if (aquery->RecordCount > 0) {
			try {
				totalprice = totalprice - aquery->FieldByName("Price")->AsFloat ;
				sql = "delete from BS_BookCatalog where ID = " +  aquery->FieldByName("ID")->AsString ;
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
			} catch (Exception &E) {
				MessageBox(0,"�����ݸ�ϵͳ���������й���������ɾ����","ϵͳ��ʾ" ,MB_OK);
			}
		}
	}
	aquery->Active = false;
	aquery->Active = true;
	edtotalrecord->Text = IntToStr(aquery->RecordCount);
	edtotalmayang->Text = FormatFloat("��0.00",totalprice);
	editcode->Text = "";
	editisbn->Text = "";
	editbookname->Text = "";
	editbookself->Text = "";
	editprice->Text = "��0.00";
	editauthor->Text = "";
	rcbtype->Text = "";
	rcbpress->Text = "";
	datapressday->Date = Date();
	edpresscount->Text = "";
	edISBNtype->Text = "";
	edyizhe->Text = "";
	edprintcount->Value = 1;
	edaffix->Text = "";
	cbformat->ItemIndex = 0;
	cbbind->ItemIndex = 0;
	edbook->Text = "";
	spepack->Value = 1;
	edhuojiangstate->Text = "";
	edbk->Text = "";
}
//---------------------------------------------------------------------------

int __fastcall TfrmCatalogkanli::BrocodeToPress(String brocode)
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


void __fastcall TfrmCatalogkanli::FormShow(TObject *Sender)
{
  //	edtQuery->SetFocus();

  if (!add) {
      BtnNew->Enabled=false;
  }
  if (!mod) {
      BtnClear->Enabled=false;
  }

   if (!del) {
      BtnDelete->Enabled=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::BtnExportClick(TObject *Sender)
{
	if (aquery->Active &&  aquery->RecordCount > 0) {
		DbgridToExcel(DBGrid1);
   }
}
//---------------------------------------------------------------------------

//Excel��������
bool __fastcall TfrmCatalogkanli::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString temptext,path,ss;
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
	   iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	else
		iFileHandle = FileCreate(path.c_str());

	temptext = ",,,ͼ��ƷĿ����";
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	/*if(k == 0)
	{
		MessageBox(0,"û�����ݣ�","����ȷ��" ,MB_OK);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  ��Excel�г��ַ�����ʾ
	v.OlePropertyGet("Cells",1,4).OlePropertySet("Value","ͼ��ƷĿ����" );
	n = 1;

	int t1= 0;  */
	temptext = "\n";
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			/*t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() ); */
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;
	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		//t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				/*t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()         */
				ss = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				temptext = temptext + ss + ",";
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();
	FileClose(iFileHandle);
	MessageBox(0,"������ϣ�","��ʾ" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::BtnImportClick(TObject *Sender)
{
    int maxid;
	AnsiString sql;
	sql = "select max(id) as id from BS_BookCatalog " ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	ds->DataSet = NULL;
	maxid = query->FieldByName("id")->AsInteger + 1;
	sql = "select A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,"
		  "A.Yizhe,A.Pressdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,"
		  "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		  " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(maxid) ;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Active = true;
	TfrmExcelImport* frm = new TfrmExcelImport(Owner,aquery);
	frm->Init(Application,fcon,fstgid);
	if (frm->ShowModal() == mrOk)
	{

	}
	delete frm;
	ds->DataSet = aquery;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::DBGrid1CellClick(TColumn *Column)
{
	if (aquery->IsEmpty()   ) {
	 	return ;
	}
	editcode->Text  = aquery->FieldByName("barcode")->AsAnsiString.Trim() ;
	editisbn->Text = aquery->FieldByName("ISBN")->AsAnsiString.Trim() ;
	editbookname->Text = aquery->FieldByName("name")->AsAnsiString.Trim() ;
	editbookself->Text = aquery->FieldByName("userdefcode")->AsAnsiString.Trim();
	editauthor->Text =aquery->FieldByName("author")->AsAnsiString.Trim();
	editprice->Text = FormatFloat("��0.00",aquery->FieldByName("price")->AsFloat);
	if (aquery->FieldByName("pid")->AsAnsiString == "") {
		rcbpress->ItemIndex = -1;
	}
	else
	{
		rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aquery->FieldByName("pid")->AsInteger );
	}

	if (aquery->FieldByName("smallbooktypeid")->AsString == "") {
		rcbtype->ItemIndex = -1;
	}
	else
	{
    	rcbtype->ItemIndex = rcbtype->Items->IndexOfObject((TObject*)aquery->FieldByName("smallbooktypeid")->AsInteger );
	}
	datapressday->Date = aquery->FieldByName("Pressdate")->AsDateTime ;
	edpresscount->Text = aquery->FieldByName("PressCount")->AsString.Trim() ;
	edISBNtype->Text = aquery->FieldByName("ISBNType")->AsString.Trim() ;
	edyizhe->Text = aquery->FieldByName("Yizhe")->AsString.Trim() ;
	edprintcount->Text = aquery->FieldByName("Printcount")->AsString.Trim() ;
	edaffix->Text = aquery->FieldByName("Affix")->AsString.Trim() ;
	cbformat->Text = aquery->FieldByName("Bookformat")->AsString.Trim() ;
	cbbind->Text = aquery->FieldByName("Bind")->AsString.Trim() ;
	edbook->Text = aquery->FieldByName("Collectbook")->AsString.Trim() ;
	edhuojiangstate->Text = aquery->FieldByName("huojiangstate")->AsString.Trim() ;
	spepack->Value = aquery->FieldByName("BookWords")->AsInteger ;
	edbk->Text = aquery->FieldByName("Bk")->AsString.Trim() ;
	edhuojiangstate->Text = aquery->FieldByName("huojiangstate")->AsString.Trim() ;

   /*	if (aquery->FieldByName("taoshu")->AsInteger==1) {
	 chtaoshu->Checked =true;
	}else
	{
		chtaoshu->Checked =false;

	} */


	if (modle != 1) {
		pcqikan->Enabled = false;
		pcwenju->Enabled = false;
		tsbase->Enabled = false;
		tsdetail->Enabled = false;
		//PageControlBook->Enabled = false;
		BtnClear->Enabled = true;
		BtnCancel->Enabled = true;
		BtnDelete->Enabled = true;
		BtnImport->Enabled = true;
		BtnExport->Enabled = true;
		BtnNew->Enabled = true;
		BtnJumptoLine->Enabled = true;
		BtnSave->Enabled = false;
		editprice->Enabled = true;
	}
	//edtaoshu->Text = aquery->FieldByName("taoshu")->AsString ;
	//modle = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::datapressdayKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		edpresscount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::sedpresscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
	   //	PageControlBook->ActivePage = tsdetail;
       BtnSave->Click();
	   editcode->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edISBNtypeKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
    	edyizhe->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edyizheKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edprintcount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edprintcountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
        edaffix->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edaffixKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        cbformat->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::cbformatKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
        cbbind->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::cbbindKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edbook->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edbookKeyPress(TObject *Sender, wchar_t &Key)
{
  //	if (Key == VK_RETURN) {
  //		chtaoshu->SetFocus();
  //	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edwordsKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edbk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edbkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::BtnViewClick(TObject *Sender)
{
	TfrmBookQuery *frm = new  TfrmBookQuery(Application,fcon);
	if (mrOk == frm->ShowModal()) {
		//int type = frm->cbQueryType->ItemIndex ;
		String Condition = frm->getcontion();
		Query(Condition);
		aquery->DisableControls();
		float totalprice = 0.00;
		try {
			while (!aquery->Eof)
			{
				totalprice = totalprice + aquery->FieldByName("Price")->AsFloat;
				aquery->Next();
			}
			edtotalrecord->Text = IntToStr(aquery->RecordCount);
			edtotalmayang->Text = FormatFloat("��0.00",totalprice);
		} catch (...) {
		}
		aquery->EnableControls();
	}
	delete frm;
	modle = 0;
	edquery->Text = "";
	Press(0);
	BtnClear->Enabled = true;
	BtnCancel->Enabled = true;
	BtnDelete->Enabled = true;
	BtnImport->Enabled = true;
	BtnExport->Enabled = true;
	BtnNew->Enabled = true;
	editprice->Enabled = true;
	//BtnSave->Enabled = false;
	if (cbsaletype->Text == "ͼ��") {
     	BtnJumptoLine->Enabled = true;
	}
        disablenewsupplierornewbook();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::btaddtypeClick(TObject *Sender)
{
	TfrmBookTypeAdmin* frm = new TfrmBookTypeAdmin(Application);
	frm->Init(Application,fcon);
    frm->Visible = false;
	frm->ShowModal();
	delete frm;
	String sql ;
	sql = "select ID,Name from BS_BookType ";
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	rcbtype->Clear();
	while(!aq->Eof)
	{
		rcbtype->AddItem(aq->FieldByName("ID")->AsAnsiString + aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::btaddpressClick(TObject *Sender)
{
	TfrmPressAdmin* frm = new TfrmPressAdmin(Application);
	frm->Init(Application, fcon);
	frm->FormStyle = fsNormal ;
    frm->Visible = false;
	frm->Position = poMainFormCenter ;
	frm->ShowModal();
	delete frm;
	String sql;
	sql = "select ID,abbreviatedname,PresentNum from BS_PressInfo ";
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	rcbpress->Clear();
	while(!aq->Eof)
	{
		rcbpress->AddItem(aq->FieldByName("PresentNum")->AsAnsiString.Trim() + aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
   	}
	delete aq;
}

//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::cbsaletypeChange(TObject *Sender)
{
	 if (cbsaletype->Text == "ͼ��") {

	  PageControlBook->Visible = true;
	  pcqikan->Visible = false;
	  pcwenju->Visible = false;
	  dg->Visible = false;
      DBGrid1->Visible = true;
	  type = 0;
      BtnJumptoLine->Enabled = true;
	 }
	 if (cbsaletype->Text == "�ڿ�") {
		 pcqikan->Visible = true;
		 pcwenju->Visible = false;
		 PageControlBook->Visible = false;
		 type = 1;
		 ShowInput(-1);
		 BtnJumptoLine->Enabled = false;
	 }
	 if (cbsaletype->Text == "�ľ�") {
		 pcwenju->Visible = true;
		 PageControlBook->Visible = false;
		 pcqikan->Visible = false;
		 type = 2;
		 ShowInput(-2);
		 BtnJumptoLine->Enabled = false;
	 }

}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::editqikanmaoKeyPress(TObject *Sender, wchar_t &Key)

{
   if (Key == VK_RETURN) {
	   if (editqikanmao->Text.Length() != 13 ) {
	   MessageBoxA(0,"��������ȷ������","��ʾ",MB_ICONASTERISK);
	   return;

	   }
	   editqikanissn->Text = BarCodeToISSN(editqikanmao->Text.Trim());
       Perform(WM_NEXTDLGCTL, 0, 0);
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::editqikanqihaoKeyPress(TObject *Sender, wchar_t &Key)

{
  if (Key == VK_RETURN) {


  if (editqikanprice->Text=="��0.00") {
	   MessageBoxA(0,"�����붨��!","����",MB_ICONASTERISK);
	   return;
  }
  if (editqikanname->Text == "") {
		 MessageBoxA(0,"�������ڿ���!","����",MB_ICONASTERISK);
	   return;
  }
  try
  {
	if (MessageBoxA(0,"ȷ��Ҫ�������ڿ���","��ʾ",MB_ICONQUESTION||MB_OKCANCEL)== 1) {

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


		editqikanmao->Text= "";
		editqikanqihao->Text="";
		editqikanfaxing->Text = "";
		editqikanmao->SetFocus();
				if (edtotalmayang->Text =="") {
		edtotalmayang->Text = "0";

		}
		edtotalmayang->Text = FloatToStr(StrToFloat(editqikanprice->Text) + StrToFloat(edtotalmayang->Text));
		editqikanprice->Text="��0.00";
	}
	}
	catch(...)
	{}

  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::editwenjupriceKeyPress(TObject *Sender, wchar_t &Key)

{
	float totalsiyang;
   if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
	  Key = NULL;
  }
  if (Key == VK_RETURN) {
  if (modle == 2) {
	  BtnSave->Click();
	  return;
  }

  if (editwenjuprice->Text=="��0.00") {
	   MessageBoxA(0,"�����붨��!","����",MB_ICONASTERISK);
	   return;
  }
  if (editwenjuname->Text == "") {
		 MessageBoxA(0,"������Ʒ��!","����",MB_ICONASTERISK);
	   return;
  }
	if (MessageBoxA(0,"ȷ��Ҫ�����ľ���","��ʾ",MB_ICONQUESTION||MB_OKCANCEL)== 1) {
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

		editwenjutiaomao->Text= "";
		editwenjutiaomao->SetFocus();

		edtotalrecord->Text = IntToStr(aqinsert->RecordCount);

		if (edtotalmayang->Text =="") {
		edtotalmayang->Text = "0";

		}
		String totalmayang = edtotalmayang->Text ;
		totalmayang = totalmayang.SubString(totalmayang.Pos("��")+1,totalmayang.Length()-totalmayang.Pos("��") );
		edtotalmayang->Text = totalmayang;
		//edtotalmayang->Text = FloatToStr(StrToFloat(editwenjuprice->Text) + StrToFloat(edtotalmayang->Text));
		edtotalmayang->Text = FormatFloat("��0.00",StrToFloat(editwenjuprice->Text) + StrToFloat(edtotalmayang->Text));
		editwenjuprice->Text="��0.00";
		}catch(...)
		{}
	}

  }
}
//---------------------------------------------------------------------------
void TfrmCatalogkanli::ShowInput(int type)
{
  AnsiString sql;
  TColumn *Column;

		 switch (type) {
			   case 0:
				  dg->Visible = false;
				  DBGrid1->Visible = true;
			   break;
			   case -1:
			   case 1:                   //�ڿ�
			   case 9:
				  dg->Columns->Clear();
				  dg->Visible = true;
				  DBGrid1->Visible = false;
					aqinsert->Active = false;

				   aqinsert->Connection = fcon ;

					if (type == 9) {                                    //��ʾ���ϼ�¼
						aqinsert->Parameters->ParamByName("@Type")->Value = 1;
						aqinsert->Parameters->ParamByName("@available")->Value = 0;
					}
					else if (type == -1) {
						aqinsert->Parameters->ParamByName("@Type")->Value = -1;
						aqinsert->Parameters->ParamByName("@available")->Value = 1;

					}
					else
						{

						aqinsert->Parameters->ParamByName("@Type")->Value = 1;
						aqinsert->Parameters->ParamByName("@available")->Value = 1;
					}

				   aqinsert->Active = true;



				  Column = dg->Columns->Add();
				  Column->FieldName = "isbn";
				  Column->Title->Caption = "ISSN";
				  Column->Width = 80;

				  Column = dg->Columns->Add();
				  Column->FieldName = "name";
				  Column->Title->Caption = "����";
				  Column->Width = 300;

				  Column = dg->Columns->Add();

				  Column->FieldName = "price";
				  Column->Title->Caption = "����";
				  Column->Width = 70;
				  Column = dg->Columns->Add();

				  Column->FieldName = "bk";
				  Column->Title->Caption = "���е�λ";
				  Column->Width = 140;
				  Column = dg->Columns->Add();

				  Column->FieldName = "presscount";
				  Column->Title->Caption = "�ں�";
				  Column->Width = 80;

			   break;
			   case -2:
			   case 2:                    //�ľ�
			   case 8:

				  dg->Columns->Clear();
				  dg->Visible = true;
				  DBGrid1->Visible = false;
				//  sql = "select isbn,name,userdefcode,price,barcode,date,Unavailable,type,presscount from bs_bookcatalog where 1=2 ";
				   aqinsert->Active = false;
				   aqinsert->Connection = fcon ;
				   if (type == -2) {
						aqinsert->Parameters->ParamByName("@Type")->Value = -2;
						aqinsert->Parameters->ParamByName("@available")->Value = 1;
				   }else if (type == 8) {
						 aqinsert->Parameters->ParamByName("@Type")->Value = 2;
						 aqinsert->Parameters->ParamByName("@available")->Value = 0;
				   }else
				   {
						 aqinsert->Parameters->ParamByName("@Type")->Value = 2;
						 aqinsert->Parameters->ParamByName("@available")->Value = 1;
				   }

				   aqinsert->Active = true;

				  Column = dg->Columns->Add();
				   Column->FieldName = "barcode";
				  Column->Title->Caption = "����";
				  Column->Width = 90;

				  Column = dg->Columns->Add();
				  Column->FieldName = "name";
				  Column->Title->Caption = "Ʒ��";
				  Column->Width =300;

				  Column = dg->Columns->Add();
				  Column->FieldName = "userdefcode";
				  Column->Title->Caption = "�Ա���";
				  Column->Width =90;
			   break;
		 default:
			 ;


		 }






}

void __fastcall TfrmCatalogkanli::editqikannameKeyPress(TObject *Sender, wchar_t &Key)

{
  if (Key == VK_RETURN) {
	 if (editqikanname->Text == "") {
		 MessageBoxA(0,"�������ڿ���!","����",MB_ICONASTERISK);
	   return;
  }
  editqikanself->Text = GetSelf(editqikanname->Text.Trim() );
  Perform(WM_NEXTDLGCTL, 0, 0);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::editqikanissnKeyPress(TObject *Sender, wchar_t &Key)

{
 if (Key == VK_RETURN) {
	if (editqikanissn->Text.Length() < 8  )
	{
	   MessageBoxA(0,"��������ȷ��ISSN���","��ʾ",MB_ICONASTERISK);
	   return;
	}
	 if (editqikanissn->Text != "" && editqikanmao->Text == "") {

		editqikanmao->Text = ISSNToBarCode(editqikanissn->Text.Trim() )  ;
	 }
     Perform(WM_NEXTDLGCTL, 0, 0);
 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::editqikanpriceKeyPress(TObject *Sender, wchar_t &Key)

{
  if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
	  Key = NULL;
  }
  if (Key == VK_RETURN) {
  if (editqikanprice->Text=="��0.00") {
	   MessageBoxA(0,"�����붨��!","����",MB_ICONASTERISK);
	   return;
  }
	  Perform(WM_NEXTDLGCTL, 0, 0);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::editqikanfaxingKeyPress(TObject *Sender, wchar_t &Key)

{
 if (Key == VK_RETURN) {

  if (modle == 2) {
	  BtnSave->Click();
	  return;
  }
  if (editqikanprice->Text=="��0.00") {
	   MessageBoxA(0,"�����붨��!","����",MB_ICONASTERISK);
	   return;
  }
  if (editqikanname->Text == "") {
		 MessageBoxA(0,"�������ڿ���!","����",MB_ICONASTERISK);
	   return;
  }
  try
  {
	if (MessageBoxA(0,"ȷ��Ҫ�������ڿ���","��ʾ",MB_ICONQUESTION||MB_OKCANCEL)== 1) {

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


		editqikanmao->Text= "";
		editqikanqihao->Text="";
		editqikanfaxing->Text = "";
		editqikanmao->SetFocus();
		if (edtotalmayang->Text =="") {
		edtotalmayang->Text = "0";

		}
		String totalmayang = edtotalmayang->Text ;
		totalmayang = totalmayang.SubString(totalmayang.Pos("��")+1,totalmayang.Length()-totalmayang.Pos("��") );
		edtotalmayang->Text = totalmayang;
		//edtotalmayang->Text = FloatToStr(StrToFloat(editqikanprice->Text) + StrToFloat(edtotalmayang->Text));
		edtotalmayang->Text = FormatFloat("��0.00",StrToFloat(editqikanprice->Text) + StrToFloat(edtotalmayang->Text));
		editqikanprice->Text="��0.00";
	}
	}
	catch(...)
	{}

  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::editwenjutiaomaoKeyPress(TObject *Sender, wchar_t &Key)

{
  if (Key == VK_RETURN) {
	Perform(WM_NEXTDLGCTL, 0, 0);
 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::editwenjunameKeyPress(TObject *Sender, wchar_t &Key)

{
  if (Key == VK_RETURN) {

   if (editwenjuname->Text == "") {
		 MessageBoxA(0,"������Ʒ��!","����",MB_ICONASTERISK);
	   return;
  }
	editwenjuself->Text = GetSelf(editwenjuname->Text.Trim());
	Perform(WM_NEXTDLGCTL, 0, 0);
 }
}
//---------------------------------------------------------------------------
AnsiString TfrmCatalogkanli::GetSelf(AnsiString context)
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
AnsiString TfrmCatalogkanli::BarCodeToISSN(AnsiString BarCode)
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
AnsiString TfrmCatalogkanli::ISSNToBarCode(AnsiString ISSN)
{
  //ISSN��EAN�Ķ�Ӧ��ϵΪ��977 + ISSNǰ7�� + 00 + EAN�����
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
	 d = c % 10;           //ȡ��У����
	 d = 10 -d;
	 BarCode = BarCode + "00" + IntToStr(d);
	 return BarCode;

}
void __fastcall TfrmCatalogkanli::dgCellClick(TColumn *Column)
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


void __fastcall TfrmCatalogkanli::BtnJumptoLineClick(TObject *Sender)
{
	if (!aquery->Active || aquery->RecordCount == 0) {
    	return;
	}
	String mayang = edtotalmayang->Text ;
	mayang = mayang.SubString(mayang.Pos("��")+1,mayang.Length()-mayang.Pos("��") );
	float totalprice = StrToFloat(mayang);
	String sql;
	TfrmSetunite *frm = new TfrmSetunite(Application,fcon);
	if (frm->ShowModal() == mrOk ) {
		for (int i = 0; i < DBGrid1->SelectedRows->Count; i++) {
			aquery->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
            sql = "select Price from BS_BookCatalog where id = " + aquery->FieldByName("ID")->AsString ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			sql = "";
			totalprice = totalprice - query->FieldByName("Price")->AsFloat;
			if (frm->cbprice->Checked ) {
				sql = "update BS_BookCatalog set Price = " + frm->editprice->Text;
			}
			if (frm->cbbook->Checked && sql != "") {
				sql = sql + ",Collectbook = '" + frm->edbook->Text + "'";
			}
			if (frm->cbbook->Checked && sql == "") {
				sql = "update BS_BookCatalog set Collectbook = '" + frm->edbook->Text + "'";
			}
			if (frm->cbtype->Checked && sql != "") {
				sql = sql + ",smallBookTypeID = " + IntToStr(frm->Gettypeid() );
			}
			if (frm->cbtype->Checked && sql == "") {
				sql = "update BS_BookCatalog set smallBookTypeID = " + IntToStr(frm->Gettypeid() );
			}
			if (frm->cbpress->Checked && sql != "") {
				sql = sql + ",PressID = " + IntToStr(frm->Getpressid() );
			}
			if (frm->cbpress ->Checked && sql == "") {
				sql = "update BS_BookCatalog set PressID = " + IntToStr(frm->Getpressid() );
			}
			if (frm->cbpressday ->Checked && sql != "") {
				sql = sql + ",Pressdate = '" + DateToStr(frm->datapressday->Date) + "'";
			}
			if (frm->cbpressday ->Checked && sql == "") {
				sql = "update BS_BookCatalog set Pressdate = '" + DateToStr(frm->datapressday->Date) + "'";
			}
			if (frm->cbpresscount ->Checked && sql != "") {
				sql = sql + ",PressCount = " + IntToStr(frm->sedpresscount->IntValue);
			}
			if (frm->cbpresscount ->Checked && sql == "") {
				sql = "update BS_BookCatalog set PressCount = " + IntToStr(frm->sedpresscount->IntValue);
			}
			if (sql == "") {
				return;
			}
			if (sql != "") {
				sql = sql + " where id = " + aquery->FieldByName("ID")->AsString ;
			}
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
			totalprice = totalprice + StrToFloat(frm->editprice->Text);
		}
	}
	delete frm;
	aquery->Active = false;
	aquery->Active = true;
	edtotalrecord->Text = IntToStr(aquery->RecordCount);
	edtotalmayang->Text = FormatFloat("��0.00",totalprice);
}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogkanli::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {  //����
		 BtnNew->Click();
	}
	if (Key == VK_F4) {     //����
		BtnSave->Click();
	}
	if (Key == VK_F5) {     //�޸�
		BtnClear->Click();
	}
	if (Key == VK_F9) {     //����
		BtnCancel->Click();
	}
	if (Key == VK_F8) {      //ɾ��
		BtnDelete->Click();
	}
	if (Key == VK_F3) {   //ͳһ
		BtnJumptoLine->Click();
	}
	if (Key == VK_F7) {     //����
		BtnImport->Click();
	}
	if (Key == VK_F6) {      //����
		BtnExport->Click();
	}
	if (Key == VK_F10) {      //�ϲ�����
		BtnAlignClient->Click();
	}
	if (Key == VK_F11) {
		if (PageControlBook->ActivePage == tsdetail)
		{
			PageControlBook->ActivePage = tsbase;
		}
		else
		{
			PageControlBook->ActivePage = tsdetail;
		}
	}
	if (Shift.Contains(ssAlt)&& Key == 70 ) {    //��ѯ
		BtnView->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void TfrmCatalogkanli::Press(int mode)
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
	else
	{
    	rcbpress->ItemIndex = -1;
	}

	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edquery->Text != "") {
			Press(1);
		}
		rcbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::editisbnKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		AnsiString bro;
		try {
			bro = ISBNToBarcode(editisbn->Text);
		} catch (...) {
		}
		editcode->Text =  bro;
		int pressid = BrocodeToPress(editcode->Text);
		rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)pressid );
        editbookname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::chtaoshuKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		edbk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::editbookselfKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        editprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::N1Click(TObject *Sender)
{
	for (int i = 1; i <= aquery->RecordCount; i++) {
		DBGrid1->DataSource->DataSet->RecNo = i;
		DBGrid1->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::DBGrid1TitleClick(TColumn *Column)
{
	if (aquery->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aquery->Sort == "") {
		aquery->Sort =  Column->FieldName + " ASC";
	}
	else if (aquery->Sort == qusort) {
		aquery->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aquery->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogkanli::BtnAlignClientClick(TObject *Sender)
{
	Tfrmmutibook *frm = new Tfrmmutibook(Application,fcon);
	frm->stgid = fstgid;
	frm->userid = fuserid;
	frm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edhuojiangstateKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		PageControlBook->ActivePage = tsdetail;
		edISBNtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::spepackKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		rcbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edpresscountKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if (Key == '\r') {
		edhuojiangstate->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogkanli::BtnUndoClick(TObject *Sender)
{
	if (1 == type||2 == type) {
			if (!aqinsert->IsEmpty() ) {
				for (int i=0; i < dg->SelectedRows->Count; i++) {
					aqinsert->GotoBookmark(dg->SelectedRows->Items[i]);
					aqinsert->Edit();
					aqinsert->FieldByName("Unavailable")->Value = 1;
					aqinsert->UpdateBatch(arCurrent);
				}
		}
		return;
	}
	for (int i =0; i < DBGrid1->SelectedRows->Count ; i++) {
		aquery->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
		if (aquery->RecordCount > 0) {
			try {
				aquery->Edit();
				aquery->FieldByName("Unavailable")->Value = 1;
				aquery->UpdateBatch(arCurrent);
			} catch (...) {
			}
		}
	}
	aquery->Active = false;
	aquery->Active = true;
}

void TfrmCatalogkanli::checknewsupplier()
{
   AnsiString sql;
   sql = "select * from sys_lock_table where lockname in('bookcatalog') and stgid ="+IntToStr(fstgid);
    TADOQuery *aq = new TADOQuery(Application);
    aq->Connection = fcon;
    aq->Close();
    aq->SQL->Clear();
    aq->SQL->Add(sql);
    aq->Open();
    aq->First();
    if (aq->FieldByName("lockname")->AsAnsiString=="bookcatalog") {
        bookcatalogadd=aq->FieldByName("lockadd")->AsBoolean;
        bcatalogmodify=aq->FieldByName("lockmodify")->AsBoolean;
        bdel=aq->FieldByName("lockdel")->AsBoolean;
    }

    delete aq;
}
void TfrmCatalogkanli::disablenewsupplierornewbook()
{


     if (bookcatalogadd) {
        BtnNew->Enabled = false;
        BtnSave->Enabled = false;
     }
     if (bcatalogmodify) {
          BtnClear->Enabled = false;
           BtnSave->Enabled = false;
     }
      if (bdel) {
          BtnDelete->Enabled = false;
     }

}
//---------------------------------------------------------------------------
