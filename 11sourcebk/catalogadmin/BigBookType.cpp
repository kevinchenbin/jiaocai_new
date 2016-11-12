//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BigBookType.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzLstBox"
#pragma link "RzTreeVw"
#pragma link "RzListVw"
#pragma link "RzDBList"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzDBGrid"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma resource "*.dfm"
TfrmBigBookType *frmBigBookType;
//---------------------------------------------------------------------------
__fastcall TfrmBigBookType::TfrmBigBookType(TComponent* Owner)
  :TForm(Owner)
{
	Modal = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBigBookType::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------

void TfrmBigBookType::Init(TApplication* app, TADOConnection* con)
{
	aqbookclass->Connection = con;
	aquery->Connection = con;
	dsp->Connection = con;

	ClassType = new TStringList(NULL);
	TTreeNode * node;
	AnsiString ClassName;
	AnsiString sql ;
	sql = "select id,code,name,bk from bs_booktype";
	aqbookclass->Close();
	aqbookclass->SQL->Clear();
	aqbookclass->SQL->Add(sql);
	aqbookclass->Open() ;
	node = tvbookclass->Items->Item[0];
	while(!aqbookclass->Eof )
	{
		ClassName = aqbookclass->FieldByName("name")->AsAnsiString;
		tvbookclass->Items->AddChild(node, ClassName);
		ClassType->AddObject(ClassName,(TObject*)aqbookclass->FieldByName("code")->AsInteger);
		aqbookclass->Next();
	}

	TTreeNode* pRoot=tvbookclass->Items->Item[0];
	pRoot->Expand(true);
}
//------------------------------------------------------------------------

void __fastcall TfrmBigBookType::btn6Click(TObject *Sender)
{
	Close();
}
//------------------------------------------------------------------------
void __fastcall TfrmBigBookType::btnExit1Click(TObject *Sender)
{
	btnExit1->Enabled = false;
	BtnSave->Enabled = true;
	rtbmodify->Enabled = false;
	btnExit2->Enabled = false;
	Modal = 1;

	edtname->Text = "";
	edtback->Text = "";
	edtname->Enabled = true;
	edtback->Enabled = true;
	edtname->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBigBookType::btnExit2Click(TObject *Sender)
{
	AnsiString sql,sdf;
	if (tvbookclass->Selected != NULL && tvbookclass->Selected->Parent != NULL) {
		sdf = "确认要删除租赁类别"+ tvbookclass->Selected->Text +"吗？";
		if (MessageBox(0,sdf.c_str() ,"删除确认" ,MB_OKCANCEL)==1 ) {
			sql = "select count(*) as C from BS_BookCatalog inner join BS_BigBookType on BS_BigBookType.ID = BS_BookCatalog.bigBookTypeID where BS_BigBookType.Name = '" +  tvbookclass->Selected->Text + "'";
			aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->Open();
			if (aquery->FieldByName("C")->AsInteger > 0 ) {
				MessageBoxA(0,"该类型所属还有图书，不能删除！","租赁类别",MB_ICONEXCLAMATION);
				return;
			}

			sql = "delete BS_BigBookType where Name = '" + tvbookclass->Selected->Text.Trim()+"'" ;

			aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			try {
				aquery->ExecSQL();
				tvbookclass->Selected->Delete();
				edtname->Text = "";
				edtback->Text = "";
			} catch (...) {
				MessageBoxA(0,"该数据跟系统其他数据有关联，不能删除！","系统提示",MB_ICONEXCLAMATION);
			}
		}
	} else
	{
		MessageBoxA(0,"请选择类型","书类别",MB_ICONEXCLAMATION);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBigBookType::RzToolButton1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBigBookType::BtnSaveClick(TObject *Sender)
{
	AnsiString sql ;
	TTreeNode *node;
	String ClassName;
	AnsiString number;
	ClassName = edtname->Text.Trim();
	if (edtname->Text == "") {
		MessageBox(0,"请输入租赁类别名称！","" ,MB_OK);
		return;
	}
	sql = "select count(*) as count from BS_BigBookType where name = '" + edtname->Text.Trim() + "'";
	aqbookclass->Close();
	aqbookclass->SQL->Clear();
	aqbookclass->SQL->Add(sql);
	aqbookclass->Open();
	if (aqbookclass->FieldByName("count")->AsInteger > 0 ) {
		MessageBox(0,"该类别名称已存在，请输入其他类别名称！","" ,MB_OK);
		return;
	}
    switch (Modal) {  //添加
	   case 1:
			sql = "insert into BS_BigBookType(name,bk) values('";
			sql = sql + ClassName+"','"+edtback->Text.Trim()  +  "')";
			aqbookclass->Close();
			aqbookclass->SQL->Clear();
			aqbookclass->SQL->Add(sql);
			aqbookclass->ExecSQL();

			node = tvbookclass->Items->Item[0] ;
			tvbookclass->Items->AddChild(node,ClassName);
			ClassType->Add(ClassName);
			edtname->Text = "";
			edtback->Text = "";
			break;

	   case 2:
			sql = "update BS_BigBookType Set Name = '" + ClassName + "' where Name = '" + tvbookclass->Selected->Text + "'";
			aqbookclass->Close();
			aqbookclass->SQL->Clear();
			aqbookclass->SQL->Add(sql);
			aqbookclass->ExecSQL();
			tvbookclass->Selected->Text =ClassName;
			ClassType->Add(ClassName);
			break;
	   default:
			;
	}
	BtnSave->Enabled = false;
	btnExit1->Enabled = true;
	rtbmodify->Enabled = true;
	edtname->Enabled = false;
	edtback->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBigBookType::rtbmodifyClick(TObject *Sender)
{
	if (tvbookclass->Selected != NULL && tvbookclass->Selected->Parent != NULL) {
    	btnExit1->Enabled = false;
		BtnSave->Enabled = true;
		rtbmodify->Enabled = false;
		btnExit2->Enabled = false;
		Modal = 2;
		edtname->Enabled = true;
		edtback->Enabled = true;
   } else
   {
	   MessageBoxA(0,"请选择类型","租赁类别",MB_ICONEXCLAMATION);
   }
}
//---------------------------------------------------------------------------


void __fastcall TfrmBigBookType::tvbookclassClick(TObject *Sender)
{
	BtnSave->Enabled = false;
	edtname->Enabled = false;
	edtback->Enabled = false;
	btnExit2->Enabled = true;
	AnsiString name,sql;
	sql = "select ID,name,bk from BS_BigBookType where name = '" + tvbookclass->Selected->Text.Trim() + "'" ;
	aqbookclass->Close();
	aqbookclass->SQL->Clear();
	aqbookclass->SQL->Add(sql);
	aqbookclass->Open();

	if (tvbookclass->Selected != NULL&&tvbookclass->Selected->Parent != NULL) {
    	Modal = 0;
		name =  tvbookclass->Selected->Text;
		edtname->Text  = name;
		edtback->Text = aqbookclass->FieldByName("bk")->AsString ;
		btnExit1->Enabled = true;
		rtbmodify->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBigBookType::edtnameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key=='\r') {
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBigBookType::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBigBookType::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {  //添加
		 btnExit1->Click();
	}
	if (Key == VK_F4) {     //保存
		BtnSave->Click();
	}
	if (Key == VK_F5) {      //删除
		btnExit2->Click();
	}
	if (Key == VK_F3) {   //修改
		rtbmodify->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		RzToolButton1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

