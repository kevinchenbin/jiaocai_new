//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AreaSet.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TMemberAreaSet *MemberAreaSet;
//---------------------------------------------------------------------------
__fastcall TMemberAreaSet::TMemberAreaSet(TComponent* Owner,TADOConnection *cnn)
	: TForm(Owner)
{
	Root = tvArea->Items->Item[0];
	quArea->Connection = cnn;
}
//---------------------------------------------------------------------------
void __fastcall TMemberAreaSet::FormShow(TObject *Sender)
{
	AnsiString sql;
	sql = "select * from Sys_Local ";
	quArea->Close();
	quArea->SQL->Clear();
	quArea->SQL->Add(sql);
	quArea->Open();
	while(!quArea->Eof )
	{
	  tvArea->Items->AddChild(Root,quArea->FieldByName("Local")->AsAnsiString);
	  quArea->Next();
	}
	tvArea->AutoExpand = true;
}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::BtnNewClick(TObject *Sender)
{
	savamodle = 1;//1为添加
	BtnChangeOptions->Enabled = false;
	BtnSave->Enabled = true;
	edAreaId->Enabled = false;
	AnsiString sql;
	sql = "select max(ID) as id from Sys_Local";
    quArea->Close();
	quArea->SQL->Clear();
	quArea->SQL->Add(sql);
	quArea->Open();
	int AreaId = quArea->FieldByName("id")->AsInteger + 1;
	edAreaId->Text = IntToStr(AreaId);
	edName->Text = "";
	edName->Enabled = true;
	edName->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::BtnChangeOptionsClick(TObject *Sender)
{

	BtnNew->Enabled = false;
	BtnSave->Enabled = true;
	if (savamodle == 1 && edName->Enabled == true) {
		MessageBox(0,"现在为添加状态，不能修改！","修改错误" ,MB_OK);
	}
	else
	{
    	edName->Enabled = true;
	}
	savamodle = 2;//2为修改

}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::BtnDeleteClick(TObject *Sender)
{
	if (tvArea->Selected->Level != 1) {
		MessageBox(0,"请选择一个区域！","没有选择" ,MB_OK);
	}
	else
	{
		AnsiString sql,sdf;
		sql = "select * from CUST_CustomerInfo where Local = '" + Trim(tvArea->Selected->Text) + "'";
		quArea->Close();
		quArea->SQL->Clear();
		quArea->SQL->Add(sql);
		quArea->Open();
		if (!quArea->IsEmpty() ) {
			MessageBox(0,"该区域的顾客信息存在，不能删除！","错误确认" ,MB_OK);
		}
		else
		{
			sql = "delete from Sys_Local where Local = '" + Trim(tvArea->Selected->Text) + "'";
			sdf = "确认删除区域：" + Trim(tvArea->Selected->Text) + "吗？";
			if (MessageBox(0,sdf.c_str() ,"删除确认" ,MB_OKCANCEL)==1){
				try {
                	quArea->Close();
					quArea->SQL->Clear();
					quArea->SQL->Add(sql);
					quArea->ExecSQL();
					tvArea->Selected->Delete();
					edName->Text = "";
					edAreaId->Text = "";
				} catch (Exception &E) {
					MessageBox(0,"该数据跟系统其他数据有关联，不能删除！","错误确认" ,MB_OK);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::tvAreaClick(TObject *Sender)
{
	AnsiString sql;
	BtnNew->Enabled = true;
	BtnChangeOptions->Enabled  = true;
	BtnSave->Enabled  = false;
	edAreaId->Enabled = false;
	edName->Enabled = false;
	sql = "select * from Sys_Local where Local = '" + Trim(tvArea->Selected->Text) + "'";
	quArea->Close();
	quArea->SQL->Clear();
	quArea->SQL->Add(sql);
	quArea->Open();
	if (tvArea->Selected->Level == 1) {
		edAreaId->Text =  quArea->FieldByName("ID")->AsString;
		edName->Text = Trim(tvArea->Selected->Text);
	}
}
//---------------------------------------------------------------------------

// 添加保存函数
void __fastcall TMemberAreaSet::Newsava()
{
	AnsiString sql,sdf;
	if (edName->Text == "") {
		MessageBox(0,"请输入区域名称！","区域为空" ,MB_OK);
	}
	else
	{
		sql = "select * from Sys_Local where Local = '" + Trim(edName->Text) + "'";
		quArea->Close();
		quArea->SQL->Clear();
		quArea->SQL->Add(sql);
		quArea->Open();
		sdf = "区域" + Trim(edName->Text) + "已经存在！";
		if (!quArea->IsEmpty() ) {
			MessageBox(0,sdf.c_str(),"区域重复" ,MB_OK);
		}
		else
		{
			sdf = "确认添加区域：" + Trim(edName->Text) + "吗？";
			if (quArea->State !=dsInsert) {
            	quArea->Append();
			}
			if (MessageBox(0,sdf.c_str() ,"添加确认" ,MB_OKCANCEL)==1){
				if (quArea->State ==dsInsert) {
					quArea->FieldByName("Local")->AsString = Trim(edName->Text);
					quArea->Post();
					tvArea->Items->AddChild(Root,Trim(edName->Text));
					edAreaId->Enabled = false;
					edName->Enabled = false;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

//修改保存函数
void __fastcall TMemberAreaSet::Changesava()
{
	AnsiString sql;
	if (tvArea->Selected->Level != 1) {
		MessageBox(0,"请选择一个区域！","没有选择" ,MB_OK);
	}
	else
	{
    	sql = "select * from CUST_CustomerInfo where Local = '" + Trim(tvArea->Selected->Text) + "'";
		quArea->Close();
		quArea->SQL->Clear();
		quArea->SQL->Add(sql);
		quArea->Open();
		if (!quArea->IsEmpty() ) {
			MessageBox(0,"该区域的顾客信息存在，不能修改！","错误确认" ,MB_OK);
		}
		else
		{
           	if (edName->Text == "") {
				MessageBox(0,"请输入区域名称！","区域为空" ,MB_OK);
			}
			else
			{
				AnsiString sql,sdf;
				int id;
				sql = "select * from Sys_Local where Local = '" + Trim(tvArea->Selected->Text) + "'";
				quArea->Close();
				quArea->SQL->Clear();
				quArea->SQL->Add(sql);
				quArea->Open();
				id = quArea->FieldByName("ID")->AsInteger;
				if (quArea->IsEmpty() ) {
					sdf = "区域" + Trim(tvArea->Selected->Text) + "不存在！";
					MessageBox(0,sdf.c_str(),"修改出错" ,MB_OK);
				}
				else
				{
					sql = "update Sys_Local set Local = '" + Trim(edName->Text) + "' where ID = " + id;
					sdf = "确认修改区域：" + Trim(tvArea->Selected->Text) + "吗？";
					if (MessageBox(0,sdf.c_str() ,"修改确认" ,MB_OKCANCEL)==1) {
						try {
							quArea->Close();
							quArea->SQL->Clear();
							quArea->SQL->Add(sql);
							quArea->ExecSQL();
							tvArea->Selected->Text =  Trim(edName->Text);
							edAreaId->Enabled = false;
							edName->Enabled = false;
							BtnNew->Enabled = true;
							BtnChangeOptions->Enabled = true;
						} catch (Exception &E) {
							MessageBox(0,"该数据跟系统其他数据有关联，不能修改！","错误确认" ,MB_OK);
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TMemberAreaSet::BtnSaveClick(TObject *Sender)
{
	if (savamodle == 1) {
		Newsava();
	}
	else if (savamodle == 2) {
		Changesava();
	}
	else
    {}
}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {     //添单
		BtnNew->Click();
	}
	if (Key == VK_F3) {     //修改
		BtnChangeOptions->Click();
	}
	if (Key == VK_F4) {     //保存
		BtnSave->Click();
	}
	if (Key == VK_F5) {     //删除
		BtnDelete->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

