//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StationeryAdminForm.h"
#include "MDIChild.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "MDIChild"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzRadChk"
#pragma link "RzSpnEdt"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TfrmStationeryAdmin *frmStationeryAdmin;
//---------------------------------------------------------------------------
__fastcall TfrmStationeryAdmin::TfrmStationeryAdmin(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	m_module = MTBkcatalog;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStationeryAdmin::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStationeryAdmin::btn1Click(TObject *Sender)
{
	//dsetStationery->Edit()
	//dsetStationery->Append();

}
//---------------------------------------------------------------------------


void __fastcall TfrmStationeryAdmin::btn2Click(TObject *Sender)
{
//if(!dsetStationery->IsEmpty())
   //	{
   //		dsetStationery->Delete();
   //	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStationeryAdmin::btn4Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStationeryAdmin::btnExit1Click(TObject *Sender)
{
	if (!dsetStationery->Active)
	{   dsetStationery->Connection = m_con;
		dsetStationery->Active = true;
	}
	dbedtBarcode->SetFocus();
	dsetStationery->Append();
	//dsetStationery->FieldByName("ISBN")->AsAnsiString   =  "465465" ;
	dsetStationery->FieldByName("ParentID")->AsString = "1";
}
//---------------------------------------------------------------------------

void __fastcall TfrmStationeryAdmin::btnExit2Click(TObject *Sender)
{
if(!dsetStationery->IsEmpty())
	{
		try
		{
			dsetStationery->Delete();
		}
		catch (...)
		{
        	ShowMessage("不能删除，有相关引用！") ;
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStationeryAdmin::btnExit3Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStationeryAdmin::cbb2KeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==VK_RETURN) //
	{
		if(chckbxInput->Checked == true)
		{
			dsetStationery->Append();
			dsetStationery->FieldByName("ParentID")->AsString = "1";
			dbedtBarcode->SetFocus();
		}
		else
		dsetStationery->Post();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStationeryAdmin::dbedtBarcodeKeyPress(TObject *Sender, wchar_t &Key)

{
	 if (Key==VK_RETURN) //
	{
		if(dbedtBarcode->Text.Length()  != 13)
		{
			ShowMessage("条码错误！");
			return;
		}
		else
    	dsetStationery->FieldByName("Barcode")->AsAnsiString   =  dbedtBarcode->Text  ;
		dbedtName->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStationeryAdmin::dbedtNameKeyPress(TObject *Sender, wchar_t &Key)

{
	 if (Key==VK_RETURN) //
	{
		//dbedt3->SetFocus();

		char* t;
		char t2;
		String t1,t3,t4="";
		t1 = dbedtName->Text;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;
		int t5=1,i = dbedtName->Text.Length() ;
		for( int j=1;j<=i;j++)
		{
//			//if (j == 9) break;
//			t3 = t1.SubString(j,1);
//			if (t3 >= 'a' && t3 <= 'z' || t3 >= 'A' && t3 <= 'Z') continue;
//			t5++;
//			if (t5 == 9) break;
//			t = t3.t_str();
//			t2 = GetPYIndexChar(t);
//			t4 = t4 + t2;
//			//ShowMessage(t2);

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
		dbedtUserDefCode->Text = t4;
		dsetStationery->FieldByName("UserDefCode")->AsAnsiString = t4;
		dbedtPrice->SetFocus();
	}
}
//--------------------------------------
//---------------------------------------------------------------------------
char TfrmStationeryAdmin::GetPYIndexChar(char *str)
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

void __fastcall TfrmStationeryAdmin::dbedtPriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key==VK_RETURN) //
	{
		//cbb1->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStationeryAdmin::dbedt4KeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key==VK_RETURN) //
	{
		dbedt5->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStationeryAdmin::dbedt5KeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key==VK_RETURN) //
	{
	   //	cbb1->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStationeryAdmin::cbb1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN) //
	{
		cbb2->SetFocus();
	}

	//dsetStationery->FieldByName("ISBN")->AsAnsiString   =  "465465" ;
	//dsetStationery->FieldByName("ParentID")->AsString = "1";
}
//---------------------------------------------------------------------------
void TfrmStationeryAdmin::OnHotKeyPress(DWORD vkCode)
{
	if(vkCode == VK_F6)
	{
		 btnExit1Click(NULL);
	}
	if(vkCode == VK_ESCAPE)
	{
    	 btnExit3Click(NULL);
	}
	if(vkCode == VK_DELETE)
	{
    	 btnExit2Click(NULL);
	}
}
//------------
void TfrmStationeryAdmin::Init(TApplication* app, TADOConnection* con)
{
	TfrmMDIChild::Init(app, con);
	dsetStationery->Connection = m_con;
	tbl1->Connection = m_con;
	dsetStationery->Active = true;
	tbl1->Active = true;
}
