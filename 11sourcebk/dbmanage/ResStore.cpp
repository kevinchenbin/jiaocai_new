//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ResStore.h"
#include <winsock2.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
TResDatabase *ResDatabase;
//---------------------------------------------------------------------------
__fastcall TResDatabase::TResDatabase(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
   quResDatabase->Connection = cn;

}
//---------------------------------------------------------------------------
void __fastcall TResDatabase::Button1Click(TObject *Sender)
{

	String hostname;
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
	if (OpendlgResPath->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(OpendlgResPath->FileName .c_str()  );
		Name = ExtractFileName(OpendlgResPath->FileName .c_str() );
		DBPath = DBPath + Name;
		int pos =  DBPath.Pos(":");
		if (DBPath.Pos("\\\\")== 0 ) {
			DBPath = DBPath.Delete(1,pos );
			DBPath = "\\\\" + hostname + DBPath;
		}
		edResPath->Text = DBPath;
	}
}
//---------------------------------------------------------------------------
void __fastcall TResDatabase::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TResDatabase::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TResDatabase::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TResDatabase::RzButton1Click(TObject *Sender)
{
	AnsiString str;
	if (edResPath->Text == "") {
		MessageBox(0,"��ѡ��Ҫ�ָ������ݣ�","ϵͳ��ʾ" ,MB_OK);
	}
	else
	{   if (FileExists(edResPath->Text)) {
			str = "RESTORE DATABASE [UFSub] FROM  DISK = N'" + edResPath->Text + "' WITH  FILE = 1,  NOUNLOAD,  STATS = 10";

			quResDatabase->Close();
			quResDatabase->SQL->Clear();
			quResDatabase->SQL->Add(str);
			try {
				 quResDatabase->ExecSQL();
				 MessageBox(0,"�ָ����ݳɹ���","ϵͳ��ʾ" ,MB_OK);
			} catch (...) {
				 MessageBox(0,"�ָ�����ʧ�ܣ�","ϵͳ��ʾ" ,MB_OK);
			}
		}
		else
		{
			MessageBox(0,"ѡ��ԭ�����ݲ����ڣ���ȷ�ϣ�","ϵͳ��ʾ" ,MB_OK);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TResDatabase::RzButton2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

