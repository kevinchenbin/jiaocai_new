//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CatalogManage.h"
#include "catalogadmin.h"
#include "PressAdminForm.h"
#include "pdutil.h"
#include "catalogadmin.h"
#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include "MDIChild.h"
#include "ExcelImport.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzEdit"
#pragma link "RzLine"
#pragma link "RzRadChk"
#pragma link "RzRadGrp"
#pragma link "RzSpnEdt"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TFormCatalogMan *FormCatalogMan;
//---------------------------------------------------------------------------
__fastcall TFormCatalogMan::TFormCatalogMan(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TFormCatalogMan::Init(TApplication* app, TADOConnection* con)
{
	queryCatlog->Connection = con;
	qryPressQuery->Connection = con;
	qryCatalogType->Connection = con;
	qryPressQuery->Active = true;
	qryCatalogType->Active = true;
	rdpressdate->Date = Date();
	edtpresscount->Value = 1;
	edtQuery->SetFocus();
	manybook = false;
}
//---------------------------------------------------------------------------
void TFormCatalogMan::Query(String condition)
{
	if (queryCatlog->Active)
	{
		queryCatlog->Active = false;
	}
	String sql;
	if(cbQueryType->Value == 1)
	{
		if(condition.Length() != 13 )
		{
			ShowMessage("位数不正确！");
			return;
		}
		for(int i=1;i<condition.Length();i++ )
		if(condition.SubString(i,1)>='0'&&condition.SubString(i,1)<='9'  )
		continue;
		else
		{
			ShowMessage("请输入数字！");
			return;
		}
		sql = "select * from UV_PressAndBookCatalogQuery where Barcode like '%" + condition + "%'";
	}
	else if(cbQueryType->Value == 2)
	{
		int i = condition.Length();
		if(i!=13)
		if(i!=10 )
		{
			ShowMessage("查询位数不正确！");
			return;
		}
		for(int i=1;i<condition.Length();i++ )
		if(condition.SubString(i,1)>='0'&&condition.SubString(i,1)<='9'  )
		continue;
		else
		{
			ShowMessage("请输入数字！");
			return;
		}
		sql = "select * from UV_PressAndBookCatalogQuery where ISBN like '%" + condition + "%'";
	}
	else if(cbQueryType->Value == 3)
	{
		for(int i=1;i<condition.Length();i++ )
		if(condition.SubString(i,1)>='a'&&condition.SubString(i,1)<='z'||condition.SubString(i,1)>='A'&&condition.SubString(i,1)<='Z'    )
		continue;
		else
		{
			ShowMessage("请输入正确的自编码！");
			return;
		}
		sql = "select * from UV_PressAndBookCatalogQuery where UserDefCode like '%" + condition + "%'";
	}
	else if(cbQueryType->Value == 4)
	{
		sql = "select * from UV_PressAndBookCatalogQuery where Name like '%" + condition + "%'";
	}
	queryCatlog->Close();
	queryCatlog->SQL->Clear();
	queryCatlog->SQL->Add(sql);
	queryCatlog->Active = true;
}

