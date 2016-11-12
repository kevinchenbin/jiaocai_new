//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzDBGrid"
#pragma link "RzLine"
#pragma resource "*.dfm"
TfrmMember *frmMember;
//---------------------------------------------------------------------------
__fastcall TfrmMember::TfrmMember(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMember::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;	
}
//---------------------------------------------------------------------------



void __fastcall TfrmMember::FormShow(TObject *Sender)
{
	//产生级别树
	AnsiString sql;
	TTreeNode * Node;
	AnsiString Value;

	MemberinfoList = new TStringList();

	sql = "select IDType,Type as T from cust_membertype order by discount desc ";
	AQMemberList->Close();
	AQMemberList->SQL->Clear();
	AQMemberList->SQL->Add(sql);
	AQMemberList->Open();
	tvclass->Items->AddChild(NULL,"会员管理");
	Root = tvclass->Items->Item[0];
	while(!AQMemberList->Eof )
	{
	  Value =  AQMemberList->FieldByName("T")->AsAnsiString + "=" QMemberList->FieldByName("IDType")->AsAnsiString;
	  MemberinfoList->Add(value);
	  tvclass->Items->AddChild(Root,AQMemberList->FieldByName("T")->AsAnsiString);
	  AQMemberList->Next();
	 }

    tvclass->AutoExpand = true;

}
//---------------------------------------------------------------------------

