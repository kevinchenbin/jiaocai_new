//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitExcelImport.h"
#include "pdutil.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
  fcon  = con;
  press = new TStringList(NULL);
  AnsiString sql;
  sql = "select ID,abbreviatedname from bs_pressinfo";
  TADOQuery *aq = new TADOQuery(NULL);
  aq->Connection = fcon;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();
  while(!aq->Eof)
  {
	press->AddObject(aq->FieldByName("abbreviatedname")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );

	aq->Next();
  }
}
int TForm1::getpressid(AnsiString name)
{

   int i;
   i = press->IndexOf(name);
   if (i>=0) {
		return (int)press->Objects[i];
   }else
   {
	 return -1;
   }


}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
	if (opndlgExcelPath->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(opndlgExcelPath->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(opndlgExcelPath->FileName .c_str() );
		DBPath = DBPath + Name;
		edtExcelPath->Text = DBPath;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnImportClick(TObject *Sender)
{
	AnsiString barcode;
	Variant vExcelApp,vSheet,Wb;
	vExcelApp = Variant::CreateObject("Excel.Application");
	AnsiString s = Sysutils::ExtractFilePath(opndlgExcelPath->FileName .c_str());
	s = s + Sysutils::ExtractFileName(opndlgExcelPath->FileName .c_str() );
	vExcelApp.OlePropertyGet("WorkBooks").OleProcedure("Open",s.c_str()   );// opndlgExcelPath->f  FileName .c_str() );
	Wb = vExcelApp.OlePropertyGet("ActiveWorkBook");
	vSheet = Wb.OlePropertyGet("ActiveSheet");
	vSheet.OlePropertySet("name","11");
	Wb.OleProcedure("Save");
	Wb.OleProcedure("Close");
	vExcelApp.OleFunction("Quit");
	//CSV导入
	//String sql = "select * from " + ExtractFileName(opndlgExcelPath->FileName .c_str() ) ;
	//EXCEL导入
	String sql = "select * from [11$]";

	String str = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	//EXCEL导入
	str = str + edtExcelPath->Text ;
	str = str + ";Mode=Read;Extended Properties=\"Excel 8.0;HDR=Yes;IMEX=1\";" ;

	//CSV导入
	//str = str + ExtractFilePath(opndlgExcelPath->FileName .c_str()) ;
	//str = str + ";Mode=Read;Extended Properties=\"text;HDR=Yes;IMEX=1;FMT=Delimited\";" ;
	    	con1->ConnectionString = "";
	try
	{
		con1->ConnectionString =  str ;
	}
	catch(...)
	{
			MessageBoxA(0,"该数据已经导入！","Excel导入",MB_ICONEXCLAMATION);
		   //	Import = true;
			return;
	}
	con1->LoginPrompt = false;
	con1->ConnectOptions = coConnectUnspecified ;
	con1->KeepConnection = true;
	con1->Mode = cmRead;
	try
	{
		 con1->Connected = true;
	}
	catch(...)
	{
		MessageBoxA(0,"数据源配置错误！","Excel导入",MB_ICONHAND);
	  //	Import= true;
		return;
	}
	qry1->Connection = con1;
	qry1->Active = false;
	qry1->SQL->Clear();
	qry1->SQL ->Add(sql);
	qry1->Active = true;
	while(!qry1->Eof)
	{
	 AnsiString name,pressname;
	 float price;
	 AnsiString isbn = qry1->FieldByName("isbn")->AsAnsiString ;
	 name =  qry1->FieldByName("name")->AsAnsiString;
	 price = qry1->FieldByName("price")->AsFloat ;
	 pressname = qry1->FieldByName("press")->AsAnsiString ;
	  barcode = ISBNToBarcode(isbn);
	 AnsiString sqlselect;

	 sqlselect  = "select ID from bs_bookcatalog   ";
	sqlselect = sqlselect + "where isbn ='"+isbn+"' and name = '"+qry1->FieldByName("isbn")->AsAnsiString +"' and ";
	sqlselect = sqlselect + " price = "+qry1->FieldByName("price")->AsAnsiString+" and barcode = '" +barcode +"'";
	 TADOQuery * aq = new TADOQuery(NULL);
	 aq->Connection = fcon;
	 aq->Close();
	 aq->SQL->Clear();
	 aq->SQL->Add(sqlselect);
	 aq->Open();
	 int bookid;
	 if (aq->RecordCount == 0 ) {   //添加新书木
	   AnsiString sqlinsert ;
	   sqlinsert = "insert bs_bookcatalog (isbn,name,price,barcode,pressid)";
	   sqlinsert = sqlinsert + " values('" + isbn + "','" + name + "'," + FloatToStr(price) + "";
	   AnsiString selfcode =   GetSelf(name) ;
	   sqlinsert = sqlinsert +  ",'" + barcode +  "',"  + IntToStr(getpressid(pressname)) + ")";
	   aq->Close();
	   aq->SQL->Clear();
	   aq->SQL->Add(sqlinsert);
	   aq->ExecSQL();


	 AnsiString sqlgetid;               //找出新书ID
	 sqlgetid = "select ID from bs_bookcatalog ";
		sqlgetid = sqlgetid + "where isbn ='"+isbn+"' and name = '"+qry1->FieldByName("name")->AsAnsiString +"' and ";
	sqlgetid = sqlgetid + " price = "+qry1->FieldByName("price")->AsAnsiString+" and barcode = '" +barcode +"'";
	  aq->Close();
	  aq->SQL->Clear();
	  aq->SQL->Add(sqlgetid);
	  aq->Open();
	  bookid = aq->FieldByName("ID")->AsInteger ;
	  } else
	  {bookid = aq->FieldByName("ID")->AsInteger ; }
	  //入库
	  st->AddNote(0,bookid);
	//  st->dbnbedtAmount->Value  = qry1->FieldByName("amount")->AsInteger ;
	   st->dsetNote->Edit();
	  st->dsetNote->FieldByName("Amount")->AsInteger =  qry1->FieldByName("amount")->AsInteger ;
	  // st->dsetNote->Post();
	  st->UpdateNote();
	  st->dsetNote->Edit();
	  st->dsetNote->FieldByName("Discount")->AsInteger  = qry1->FieldByName("discount")->AsFloat ;
	  st->UpdateNote();
	  delete aq;
	  qry1->Next();
	}



}
AnsiString TForm1::GetSelf(AnsiString context)
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
char TForm1::GetPYIndexChar(char *str)
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
