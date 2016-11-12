//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Addstorge.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmAddstorge *frmAddstorge;
//---------------------------------------------------------------------------
__fastcall TfrmAddstorge::TfrmAddstorge(TComponent* Owner,TADOQuery *aquery,int modle)
	: TForm(Owner)
{
	query = aquery;
	querymod->Connection = aquery->Connection ;
	Modle = modle;
	con = aquery->Connection ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAddstorge::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::BtnSaveClick(TObject *Sender)
{
	String sql;
	if (edname->Text == "") {
		MessageBox(0,"店（仓）的名字不能为空！","系统提示" ,MB_OK);
		return;
	}
	if (Modle == 1) {  //  添加
		sql = "select count(*) as count from SYS_StorageInfo where Name = '" + edname->Text + "'" ;
		querymod->Close();
		querymod->SQL->Clear();
		querymod->SQL->Add(sql);
		querymod->Open();
		if (querymod->FieldByName("count")->AsInteger > 0) {
			MessageBox(0,"该店（仓）已存在！","系统提示" ,MB_OK);
			return;
		}
		if (MessageBox(0,"确认添加该店（仓）？","添加店（仓）" ,MB_OKCANCEL)==1) {
			sql = "insert into SYS_StorageInfo(Name,Address,Contact,Tel,printtitle) values('" + edname->Text.Trim() + "','" + edaddress->Text.Trim() + "','" + edcontact->Text.Trim() + "','" + edtel->Text.Trim() + "','" + edprinttitle->Text.Trim() + "')";
			querymod->Close();
			querymod->SQL->Clear();
			querymod->SQL->Add(sql);
			querymod->ExecSQL();
			logmessage = "添加店（仓）" + edname->Text ;
			AddEvent(1,"添加店（仓）",userid,storageid,logmessage,con);
			query->Active = false;
			query->Active = true;
			Close();
		}
	}
	else    //   修改
	{
		sql = "select count(*) as count from SYS_StorageInfo where Name = '" + edname->Text + "' and ID <> " + query->FieldByName("ID")->AsString;
		querymod->Close();
		querymod->SQL->Clear();
		querymod->SQL->Add(sql);
		querymod->Open();
		if (querymod->FieldByName("count")->AsInteger > 0) {
			MessageBox(0,"该店（仓）已存在！","系统提示" ,MB_OK);
			return;
		}
		if (MessageBox(0,"确认修改该店（仓）？","修改店（仓）" ,MB_OKCANCEL)==1) {
			sql = "update SYS_StorageInfo set Name = '" + edname->Text.Trim() + "',Tel = '" + edtel->Text.Trim();
			sql = sql + "',Contact = '" + edcontact->Text.Trim() + "',Address = '" + edaddress->Text.Trim() + "',printtitle = '" + edprinttitle->Text.Trim() ;
			sql = sql + "' where ID = " + query->FieldByName("ID")->AsString ;
			querymod->Close();
			querymod->SQL->Clear();
			querymod->SQL->Add(sql);
			querymod->ExecSQL();
			query->Refresh();
            Close();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::FormShow(TObject *Sender)
{
	if (Modle == 2) {
		this->Caption = "修改店（仓）";
		edname->Text = query->FieldByName("Name")->AsString ;
		edtel->Text = query->FieldByName("Tel")->AsString ;
		edcontact->Text = query->FieldByName("Contact")->AsString ;
		edaddress->Text = query->FieldByName("Address")->AsString ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::ednameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edtel->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::edtelKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edcontact->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::edcontactKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edaddress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::edaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key ==115) {   //保存
		BtnSave->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

