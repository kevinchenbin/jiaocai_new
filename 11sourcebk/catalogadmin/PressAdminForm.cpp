

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PressAdminForm.h"
#include "MDIChild.h"
#include "pdutil.h"

//---------------------------------------------------------------------------
//jia---------------------------------------------------------------------------
  #include   "ComObj.hpp"
  #define       PG       OlePropertyGet
  #define       PS       OlePropertySet
  #define       FN       OleFunction
  #define       PR       OleProcedure
 //jia----------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzDBGrid"

#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzShellDialogs"
#pragma link "RzLine"
#pragma resource "*.dfm"
TfrmPressAdmin *frmPressAdmin;
//---------------------------------------------------------------------------
__fastcall TfrmPressAdmin::TfrmPressAdmin(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
 
}
//---------------------------------------------------------------------------
void __fastcall TfrmPressAdmin::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPressAdmin::btnQueryClick(TObject *Sender)
{
	//ShowMessage("hello");
	Query(edtQuery->Text );
}
//---------------------------------------------------------------------------
void TfrmPressAdmin::Init(TApplication* app, TADOConnection* con)
{
	TfrmMDIChild::Init(app, con);
	m_con = con;
	dsetPress->Connection = m_con;
	dsetPress->CommandText = "select * from BS_PressInfo";
	dsetPress->Active = true;
	//dsetPress->First();
}

void TfrmPressAdmin::Query(String condition)
{
	if (dsetPress->Active)
	{
		dsetPress->Active = false;
	}

	String sql;
	if(cbQueryType->Value == 1)
	{

		//sql = "select * from BS_PressInfo where PresentNum = 1";
		if(condition=="")
		{
		sql = "select * from BS_PressInfo" ;  //
		}
		else sql = "select * from BS_PressInfo where PresentNum like '%" + condition + "%'";// + condition;
	}
	else if(cbQueryType->Value == 3)
	{
		sql = "select * from BS_PressInfo where FullName like '%" + condition + "%'";
	}
	else if(cbQueryType->Value == 2)
	{
		sql = "select * from BS_PressInfo where AbbreviatedName like '%" + condition + "%'";
	}
	dsetPress->CommandText = sql;
	dsetPress->Active = true;
}

void __fastcall TfrmPressAdmin::RzToolButton4Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmPressAdmin::RzToolButton2Click(TObject *Sender)
{
	/*if(dsetPress->State == dsInsert&&dbedtPreNum->Text != "")
	{
	dbedtAbbrNam->ReadOnly = false;
	dsetPress->Post();
	dsetPress->Refresh();
	}*/



}
//---------------------------------------------------------------------------



void __fastcall TfrmPressAdmin::btnAddClick(TObject *Sender)
{
	//
	RzDBEdit2->SetFocus();
	int i;
	i=123;
	String s;
	s=IntToStr(i);
	ShowMessage(s);
	dsetPress->Append();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnDeleteClick(TObject *Sender)
{
	if(!dsetPress->IsEmpty())
	{
		dsetPress->Delete();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::frmExportClick(TObject *Sender)
{
	//ShowMessage("ok");

	if (svdlgExport->Execute())
	{

	}


}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnExitClick(TObject *Sender)
{
	//
	Close();
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::edtQueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
		if (Key==VK_RETURN) {
				Query(edtQuery->Text);
		 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit2KeyPress(TObject *Sender, wchar_t &Key)
{
	  if (Key==VK_RETURN) //
	{

			RzDBEdit3->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit3KeyPress(TObject *Sender, wchar_t &Key)
{
     if (Key==VK_RETURN) //
	{

			RzDBEdit4->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit4KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN) //
	{

			RzDBEdit5->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit5KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN) //
	{

			RzDBEdit6->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit6KeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==VK_RETURN) //
	{

			RzDBEdit7->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit7KeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==VK_RETURN) //
	{

			RzDBEdit8->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit8KeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==VK_RETURN) //
	{

			RzDBEdit9->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit9KeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==VK_RETURN) //
	{

			RzDBEdit10->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit10KeyPress(TObject *Sender, wchar_t &Key)

{
if (Key==VK_RETURN) //
	{

			RzDBEdit11->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit11KeyPress(TObject *Sender, wchar_t &Key)

{
if (Key==VK_RETURN) //
	{

			RzDBEdit12->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit12KeyPress(TObject *Sender, wchar_t &Key)

{
if (Key==VK_RETURN) //
	{

			RzDBEdit2->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnExit1Click(TObject *Sender)
{
	Query(edtQuery->Text );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnExit2Click(TObject *Sender)
{
    GroupBox1->Enabled = true;
	edtQuery->Text = "" ;
	//
	RzDBEdit2->SetFocus();
	int i;
	i=123;
	String s;
	s=IntToStr(i);
	//ShowMessage(s);
	dsetPress->Append();
	//dsetPress->Refresh();
	//dsetBookType->Edit();
	//dsetBookType->FieldByName("ParentID")->Value = 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnExit3Click(TObject *Sender)
{
	if(!dsetPress->IsEmpty())
	{
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = m_con ;
		AnsiString sql;
		sql = "select * from bs_bookcatalog where pressid = " + dsetPress->FieldByName("id")->AsString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->IsEmpty() ) {
			dsetPress->Delete();
		}
		else
		{
			MessageBox(0,"该记录有引用，不能删除！","提示" ,MB_ICONEXCLAMATION);
		}
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnExit4Click(TObject *Sender)
{

//	if (svdlgExport->Execute())
//	{
//
//	}
	if (dsetPress->Active && dsetPress->RecordCount > 0) {
		DbgridToExcel(dbgrdPress);
	}

}
//Excel导出函数
bool __fastcall TfrmPressAdmin::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		MessageBox(0,"没有数据！","错误确认" ,MB_OK);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	v.OlePropertyGet("Cells",1,4).OlePropertySet("Value","出版社管理" );

	n = 1;

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
		}
	}



	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}

	return false;

}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnExit5Click(TObject *Sender)
{
	try
	{
	//if(dsetPress->State == dsInsert)
		dsetPress->Post();
		GroupBox1->Enabled = false;
	}
	catch(...)
	{
		//ShowMessage("基本数据不完整！");
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btn1Click(TObject *Sender)
{
//	int j = dbgrdPressAdd->DataSource ->DataSet ->RecordCount ;
//	for( int i=1;i<=dbgrdPressAdd->DataSource ->DataSet ->RecordCount ;i++)
//	{
//		dsetPress->Active = true;
//		dsetPress->Append();
//		dsetPress->FieldByName("AbbreviatedName")->Value = dbgrdPressAdd ->DataSource ->DataSet ->FieldByName("AbbreviatedName")->Value ;
//		dsetPress->FieldByName("PresentNum")->Value = dbgrdPressAdd->DataSource ->DataSet ->FieldByName("PressNum")->Value ;
//		dsetPress->FieldByName("FullName")->Value = dbgrdPressAdd->DataSource ->DataSet ->FieldByName("FullName")->Value ;
//		dbgrdPressAdd->DataSource->DataSet ->RecNo ++;
//	}

//	dsetCatlog->FieldByName("Name")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Name")->Value ;
//	dsetCatlog->FieldByName("Barcode")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Barcode")->Value ;
//	dsetCatlog->FieldByName("UserDefCode")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("UserDefNum")->Value ;
////	dsetCatlog->FieldByName("AbbreviatedName")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Press")->Value ;
////	dsetCatlog->FieldByName("Date")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName(dbgrdExcelCatlog->Columns ->Items [1]->FieldName  )->AsAnsiString .c_str(); // ->Value ;
//	dsetCatlog->FieldByName("Price")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Price")->Value ;
//	dsetCatlog->FieldByName("smallBookTypeID")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Type")->Value ;
//	dsetCatlog->FieldByName("Author")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Author")->Value ;
////	dsetCatlog->FieldByName("PressCount")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("PressCount")->Value ;
//	dsetCatlog->FieldByName("PressID")->Value = 1;
//	dsetCatlog->FieldByName("smallBookTypeID")->Value = 2;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzToolButton1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void TfrmPressAdmin::OnHotKeyPress(DWORD vkCode)
{
//	if(vkCode == 81)
//	{
//		 btnExit1Click(NULL);
//	}
	if(vkCode == VK_F6)
	{
    	 btnExit2Click(NULL);
	}
	if(vkCode == VK_ESCAPE)
	{
    	 RzToolButton1Click(NULL);
	}
}

void __fastcall TfrmPressAdmin::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {  //添加
		 btnExit2->Click();
	}	if (Key == VK_F4) {     //保存
		btnExit5->Click();
	}
		if (Key == VK_F5) {      //删除
		btnExit3->Click();
	}
		if (Key == VK_F6) {      //导出
		btnExit4->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		btnExit1->Click();
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


void __fastcall TfrmPressAdmin::BtnChangeOptionsClick(TObject *Sender)
{
	if (dsetPress->IsEmpty() ) {
		return;
	}
	GroupBox1->Enabled = true;
}
//---------------------------------------------------------------------------



void __fastcall TfrmPressAdmin::dbgrdPressCellClick(TColumn *Column)
{
	if (dsetPress->IsEmpty() ) {
        return;
	}
	GroupBox1->Enabled = false;
}
//---------------------------------------------------------------------------

