//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "backdatabase.h"
#include <winsock2.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzEdit"
#pragma link "RzShellDialogs"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
TBakDatabase *BakDatabase;
//---------------------------------------------------------------------------
__fastcall TBakDatabase::TBakDatabase(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
  quBakDatabase->Connection = cn;
}
//---------------------------------------------------------------------------
void __fastcall TBakDatabase::SelectPathClick(TObject *Sender)
{
	String defaultname,hostname;
	defaultname = "dbbak"+ Date().FormatString("yyyymmdd");
	SavedlgBakPath->FileName = defaultname;
	Word wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(1, 1);
	WSAStartup(wVersionRequested, &wsaData);

	hostent *p;
	char s[128];


	gethostname(s, 128);
	p = gethostbyname(s);
	hostname = AnsiString(p->h_name);
	WSACleanup();
	if (SavedlgBakPath->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(SavedlgBakPath->FileName .c_str()  );
		Name = ExtractFileName(SavedlgBakPath->FileName .c_str() );
		CheckPath =  DBPath;
		DBPath = DBPath + Name;
		int pos =  DBPath.Pos(":");
		if (DBPath.Pos("\\\\")== 0 ) {
			DBPath = DBPath.Delete(1,pos );
			DBPath = "\\\\" + hostname + DBPath;
		}
		edBakPath->Text = DBPath;
	}
}
//---------------------------------------------------------------------------






void __fastcall TBakDatabase::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TBakDatabase::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TBakDatabase::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TBakDatabase::RzButton1Click(TObject *Sender)
{
	AnsiString str;

	if (edBakPath->Text == "") {
		MessageBox(0,"请选择备份路径！","系统提示" ,MB_OK);
	}
	else
	{   if (DirectoryExists(CheckPath)) {
			str = "BACKUP DATABASE [book] TO DISK =N'" + edBakPath->Text + "' WITH NOFORMAT, NOINIT,  NAME = N'book-完整 数据库 备份', SKIP, NOREWIND, NOUNLOAD,  STATS = 10";

			quBakDatabase->Close();
			quBakDatabase->SQL->Clear();
			quBakDatabase->SQL->Add(str);
			try {
				 quBakDatabase->ExecSQL();
				 MessageBox(0,"备份数据成功！","系统提示" ,MB_OK);
			} catch (...) {
				 MessageBox(0,"备份数据失败！","系统提示" ,MB_OK);
			}
		}
		else
		{
			MessageBox(0,"路径不合法！","系统提示" ,MB_OK);
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TBakDatabase::RzButton2Click(TObject *Sender)
{
		Close();
}
//---------------------------------------------------------------------------

