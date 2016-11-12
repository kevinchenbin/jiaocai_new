//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Staffdetail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
TfrmStaffdetail *frmStaffdetail;
//---------------------------------------------------------------------------
__fastcall TfrmStaffdetail::TfrmStaffdetail(TComponent* Owner,int savamod,String id,TADOConnection *cnn,int Stgid)
	: TForm(Owner)
{
	modsave = savamod;
	fstgid = Stgid;
	ID = id;
	aqinit->Connection = cnn;
	aqdetail->Connection = cnn;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStaffdetail::FormShow(TObject *Sender)
{
	edName->SetFocus();
	if (modsave == 2) {
		cbCareer->Enabled = false;
	}
	AnsiString sql;
	cbCareer->AddItem("采购员",(TObject*)1);
	cbCareer->AddItem("业务员",(TObject*)2);
	cbCareer->ItemIndex = cbCareer->Items->IndexOfObject((TObject*)1);
	cbSex->Add("男");
	cbSex->Add("女");
	cbSex->Text = "男";
	if (modsave == 2) {
		sql = "select * from SYS_StaffInfo where ID = " + ID;
        aqinit->Close();
		aqinit->SQL->Clear();
		aqinit->SQL->Add(sql);
		aqinit->Open();
		edName->Text = aqinit->FieldByName("Name")->AsString;
		edtphone->Text = aqinit->FieldByName("Tel")->AsString;
		cbSex->Text = aqinit->FieldByName("Sex")->AsString;
		edMobile->Text = aqinit->FieldByName("Mobile")->AsString;
		edqq->Text = aqinit->FieldByName("QQ")->AsString;
		edemail->Text = aqinit->FieldByName("Email")->AsString;
		edaddress->Text = aqinit->FieldByName("Address")->AsString;
		cbCareer->ItemIndex = cbCareer->Items->IndexOfObject((TObject*)aqinit->FieldByName("Career")->AsInteger );
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmStaffdetail::BtnSaveClick(TObject *Sender)
{
	AnsiString sql,sdf;

	if (modsave == 1) {
			sql = "select * from SYS_StaffInfo where Name = '" + edName->Text.Trim() + "' and Career = " + IntToStr(int(cbCareer->Items->Objects[cbCareer->ItemIndex])) + " and StgID = " + IntToStr(fstgid) ;
			aqdetail->Close();
			aqdetail->SQL->Clear();
			aqdetail->SQL->Add(sql);
			aqdetail->Open();
			if (aqdetail->RecordCount > 0) {
				if (cbCareer->Text == "采购员") {
					MessageBox(0,"该采购员已经录入，请确认！","录入重复" ,MB_ICONWARNING);
					return;
				}
				else
				{
					MessageBox(0,"该业务员已经录入，请确认！","录入重复" ,MB_ICONWARNING);
					return;
				}
			}
		if (edName->Text == "") {
			MessageBox(0,"请输入姓名！","信息错误" ,MB_ICONWARNING);
			return;
		}
		else
		{
			if (cbCareer->Text == "采购员") {
				sdf = "确认添加采购员" + edName->Text +"吗？" ;
			}
			else {
				sdf = "确认添加业务员" + edName->Text +"吗？" ;
			}
			if (MessageBox(0,sdf.c_str() ,"添加确认" ,MB_ICONQUESTION|MB_OKCANCEL)==1) {
				if (aqdetail->State != dsInsert) {
					aqdetail->Append();
				}
				aqdetail->FieldByName("Name")->AsString = edName->Text.Trim();
				aqdetail->FieldByName("Sex")->AsString =  cbSex->Text.Trim();
				aqdetail->FieldByName("Tel")->AsString =  edtphone->Text.Trim();
				aqdetail->FieldByName("Mobile")->AsString =  edMobile->Text.Trim();
				aqdetail->FieldByName("QQ")->AsString = edqq->Text.Trim();
				aqdetail->FieldByName("Email")->AsString   = edemail->Text.Trim();
				aqdetail->FieldByName("Address")->AsString =  edaddress->Text.Trim();
				aqdetail->FieldByName("StgID")->AsInteger  =  fstgid;
				if (cbCareer->Text == "采购员") {
					aqdetail->FieldByName("Career")->AsInteger = 1;
				}
				else
				{
					aqdetail->FieldByName("Career")->AsInteger = 2;
				}
				aqdetail->UpdateBatch(arAll);
				this->Close();
			}
		}
	}
	if (modsave == 2) {
		AnsiString sql,sdf;
		sql = "update SYS_StaffInfo set name = '" +edName->Text +"',Sex = '" + cbSex->Text.Trim()+ "',Tel = '";
		sql = sql + edtphone->Text.Trim() + "',Mobile = '" + edMobile->Text.Trim() + "',QQ = '" + edqq->Text.Trim();
		sql = sql + "',Email = '" + edemail->Text.Trim() +"',Address = '" + edaddress->Text.Trim();
		sql = sql + "' where ID = " + ID;

		if (cbCareer->Text == "采购员") {
			sdf = "确认修改采购员" + edName->Text +"吗？" ;
		}
		else
		{
			sdf = "确认修改业务员" + edName->Text +"吗？" ;
		}
		if (MessageBox(0,sdf.c_str() ,"修改确认" ,MB_ICONQUESTION|MB_OKCANCEL)==1) {
			try {
				aqinit->Close();
				aqinit->SQL->Clear();
				aqinit->SQL->Add(sql);
				aqinit->ExecSQL();
				this->Close();
			} catch (Exception &E) {
				MessageBox(0,"该数据跟系统其他数据有关联，不能修改！","修改错误" ,MB_ICONWARNING );
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmStaffdetail::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStaffdetail::edNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStaffdetail::edaddressKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStaffdetail::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F5) {     //保存
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

