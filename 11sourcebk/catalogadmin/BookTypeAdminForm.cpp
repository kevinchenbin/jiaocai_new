//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BooKTypeAdminForm.h"

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
TfrmBookTypeAdmin *frmBookTypeAdmin;
//---------------------------------------------------------------------------
__fastcall TfrmBookTypeAdmin::TfrmBookTypeAdmin(TComponent* Owner)
  :TForm(Owner)
   //	: TfrmMDIChild(Owner)
{
	 //	m_module = MTBkcatalog;
		Modal = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBookTypeAdmin::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------


void TfrmBookTypeAdmin::Init(TApplication* app, TADOConnection* con)
{
  //	TfrmMDIChild::Init(app, con);

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

	TTreeNode   *   pRoot=tvbookclass->Items->Item[0];
	pRoot->Expand(true);

}




void __fastcall TfrmBookTypeAdmin::btn6Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------



//------------------------------------------------------------------------
void __fastcall TfrmBookTypeAdmin::btnExit1Click(TObject *Sender)
{

   btnExit1->Enabled = false;
   BtnSave->Enabled = true;
   rtbmodify->Enabled = false;
   btnExit2->Enabled = false;
   Modal = 1;
//	if(dbedtCode->Text == ""&&dbedtTypeName->Text == "")
//	{return;}
//	else
   /*	dsetBookType->Active = true;
	dsetBookType->Append();
	//dsetBookType->Edit();
	dsetBookType->FieldByName("ParentID")->Value = 1;
	dbedtCode->SetFocus();   */

	String sql;
	sql = "select Max(ID) as id from BS_BookType";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	ettypenum->Text = IntToStr(aquery->FieldByName("id")->AsInteger + 1);
	edtname->Text = "";
	edtback->Text = "";
	edtname->Enabled = true;
	edtback->Enabled = true;
	edtname->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookTypeAdmin::btnExit2Click(TObject *Sender)
{
	String sql;
	AnsiString sdf;



	   if (tvbookclass->Selected != NULL && tvbookclass->Selected->Parent != NULL) {

			 sdf = "确认要删除类别"+ tvbookclass->Selected->Text +"吗？";
			 if (MessageBox(0,sdf.c_str() ,"删除确认" ,MB_OKCANCEL)==1 ) {
				 sql = "select count(*) as C from BS_BookCatalog inner join BS_BookType on BS_BookType.ID = BS_BookCatalog.smallBookTypeID where BS_BookType.Name = '" +  tvbookclass->Selected->Text + "'";
				 aquery->Close();
				 aquery->SQL->Clear();
				 aquery->SQL->Add(sql);
				 aquery->Open();
				 if (aquery->FieldByName("C")->AsInteger > 0 ) {

					 MessageBoxA(0,"该类型所属还有图书，不能删除！","书类别",MB_ICONEXCLAMATION);
					 return;
				 }

				 sql = "delete BS_BookType where Name = '" + tvbookclass->Selected->Text.Trim()+"'" ;

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

void __fastcall TfrmBookTypeAdmin::btnExit3Click(TObject *Sender)
{
	DbgridToExcel(RzDBGrid1);

}
//---------------------------------------------------------------------------

void __fastcall TfrmBookTypeAdmin::btn1Click(TObject *Sender)
{

	//rvprjct1->Engine ->ExecuteAction();
	//rvprjct1->New();
}
//---------------------------------------------------------------------------


void __fastcall TfrmBookTypeAdmin::dbedtCodeKeyPress(TObject *Sender, wchar_t &Key)
{
 /*	if(Key == VK_RETURN)
	{
		if(dbedtCode->Text == "")
		{
			ShowMessage("代号为空");
			return;
		}
		dbedtTypeName->SetFocus();
	}  */
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookTypeAdmin::dbedtTypeNameKeyPress(TObject *Sender, wchar_t &Key)

{
  /*	if(Key == VK_RETURN)
	{
		if(dbedtTypeName->Text == "")
		{
			ShowMessage("类名为空");
			return;
		}
		else
		{
			if(dsetBookType->State != dsInsert)
			{
			ShowMessage("不是添加状态");
			return;
			}
			dsetBookType->Post();
			dbedtCode->Text = "";
			dbedtTypeName->Text = "";
		}
//		dsetBookType->Post();
//		dbedtCode->Text = "";
//		dbedtTypeName->Text = "";

	}   */
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookTypeAdmin::RzToolButton1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void TfrmBookTypeAdmin::OnHotKeyPress(DWORD vkCode)
{
  /*	if(vkCode == VK_F6)
	{
		 btnExit1Click(NULL);
	}
	if(vkCode == VK_DELETE)
	{
    	 btnExit2Click(NULL);
	}
	if(vkCode == VK_ESCAPE)
	{
    	 RzToolButton1Click(NULL);
	}  */
}

void __fastcall TfrmBookTypeAdmin::BtnSaveClick(TObject *Sender)
{
   AnsiString sql ;
   TTreeNode *node;
   String ClassName;
   AnsiString number;
   ClassName = edtname->Text.Trim();
   if (edtname->Text == "") {
		MessageBox(0,"请输入类别名称！","" ,MB_OK);
		return;
   }
	sql = "select count(*) as count from bs_booktype where name = '" + edtname->Text.Trim() + "'";
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
			sql = "insert into bs_booktype(parentid,name,bk) values(1,'";
			sql = sql + ClassName+"','"+edtback->Text.Trim()  +  "')";
			aqbookclass->Close();
			aqbookclass->SQL->Clear();
			aqbookclass->SQL->Add(sql);
			aqbookclass->ExecSQL();

			node = tvbookclass->Items->Item[0] ;
			tvbookclass->Items->AddChild(node,ClassName);
			//number = edtnum->Text;
			//ClassType->AddObject(ClassName,(TObject*)StrToInt(number));
			ClassType->Add(ClassName);
			edtname->Text = "";
			edtback->Text = "";
			break;

	   case 2:

			sql = "update bs_booktype Set Name = '" + ClassName + "' where Name = '" + tvbookclass->Selected->Text + "'";
			aqbookclass->Close();
			aqbookclass->SQL->Clear();
			aqbookclass->SQL->Add(sql);
			aqbookclass->ExecSQL();
			tvbookclass->Selected->Text =ClassName;
			//ClassType->AddObject(ClassName,(TObject*)StrToInt(edtnum->Text));
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


void __fastcall TfrmBookTypeAdmin::rtbmodifyClick(TObject *Sender)
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
	   MessageBoxA(0,"请选择类型","书类别",MB_ICONEXCLAMATION);
   }

}
//---------------------------------------------------------------------------


void __fastcall TfrmBookTypeAdmin::tvbookclassClick(TObject *Sender)
{
	BtnSave->Enabled = false;
	edtname->Enabled = false;
	edtback->Enabled = false;
	btnExit2->Enabled = true;
	AnsiString name,sql;
	sql = "select ID,name,bk from BS_BookType where name = '" + tvbookclass->Selected->Text.Trim() + "'" ;
	aqbookclass->Close();
	aqbookclass->SQL->Clear();
	aqbookclass->SQL->Add(sql);
	aqbookclass->Open();

	if (tvbookclass->Selected != NULL&&tvbookclass->Selected->Parent != NULL) {
		 name =  tvbookclass->Selected->Text;
		 ettypenum->Text = aqbookclass->FieldByName("ID")->AsString ;
		 edtname->Text  = name;
		 edtback->Text = aqbookclass->FieldByName("bk")->AsString ;
	   //	 edtnum->Text =  IntToStr((int)ClassType->Objects[ClassType->IndexOf(tvbookclass->Selected->Text)]);
		 btnExit1->Enabled = true;
		 rtbmodify->Enabled = true;
       //  edtnum->Enabled = false;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmBookTypeAdmin::edtnameKeyPress(TObject *Sender, wchar_t &Key)

{
	 if (Key=='\r') {
         BtnSave->Click();
	 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookTypeAdmin::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookTypeAdmin::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {  //添加
		 btnExit1->Click();
	}	if (Key == VK_F4) {     //保存
		BtnSave->Click();
	}
		if (Key == VK_F5) {      //删除
		btnExit2->Click();
	}
		if (Key == VK_F3) {   //修改
		rtbmodify->Click();
	}
		if (Key == VK_F6) {      //导出
		btnExit3->Click();
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

