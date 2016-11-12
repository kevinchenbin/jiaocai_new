//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Staffmanage.h"
#include "Staffdetail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TfrmStaff *frmStaff;
//---------------------------------------------------------------------------
__fastcall TfrmStaff::TfrmStaff(TComponent* Owner,TADOConnection *cnn,int stgid)
	: TForm(Owner)
{
	cn = cnn;
	fstgid = stgid;
	aqinit->Connection = cnn;
	aqrecord->Connection = cnn;
	query->Connection = cnn;
	AnsiString sql;
	sql = "select SYS_StaffInfo.*,case Career when 1 then '采购员' when 2 then '业务员'  end as careername from SYS_StaffInfo where StgID = " + IntToStr(fstgid) ;
	aqrecord->Close();
	aqrecord->SQL->Clear();
	aqrecord->SQL->Add(sql);
	aqrecord->Open();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStaff::BtnViewClick(TObject *Sender)
{
	AnsiString sql;
	sql = "select SYS_StaffInfo.*,case Career when 1 then '采购员' when 2 then '业务员'  end as careername from SYS_StaffInfo where name like '%" + etname->Text.Trim() + "%' and StgID = " + IntToStr(fstgid) ;
	aqrecord->Close();
	aqrecord->SQL->Clear();
	aqrecord->SQL->Add(sql);
	aqrecord->Open();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStaff::BtnNewClick(TObject *Sender)
{
	TfrmStaffdetail * frm = new TfrmStaffdetail(Application,1,"",cn,fstgid);
	frm->ShowModal() ;
	delete frm;
	aqrecord->Active = false;
	aqrecord->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStaff::BtnFinishClick(TObject *Sender)
{
	if (aqrecord->IsEmpty() ) {
		return;
	}
	TfrmStaffdetail * frm = new TfrmStaffdetail(Application,2,aqrecord->FieldByName("ID")->AsString,cn,fstgid);
	frm->ShowModal() ;
	delete frm;
	aqrecord->Active = false;
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStaff::BtnDeleteClick(TObject *Sender)
{
	AnsiString sql,sdf;
	if (aqrecord->IsEmpty() ) {
    	return;
	}
	sql = "delete from SYS_StaffInfo where id = " + aqrecord->FieldByName("ID")->AsString ;
	if (aqrecord->FieldByName("ID")->AsInteger == 1) {
		sdf = "确认删除采购员"+aqrecord->FieldByName("name")->AsString +"吗？" ;
	}
	else {
		sdf = "确认删除业务员"+aqrecord->FieldByName("name")->AsString +"吗？" ;
	}

	if (MessageBox(0,sdf.c_str() ,"删除确认" ,MB_OKCANCEL)==1) {
		try {
			aqinit->Close();
			aqinit->SQL->Clear();
			aqinit->SQL->Add(sql);
			aqinit->ExecSQL();
		} catch (Exception &E) {
			MessageBox(0,"该数据跟系统其他数据有关联，不能删除！","删除错误" ,MB_ICONWARNING);
		}
	}
	aqrecord->Active = false;
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStaff::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStaff::BtnExportClick(TObject *Sender)
{
	if (aqrecord->RecordCount > 0) {
    	DbgridToExcel(DBGridrecord);
	}
}
//---------------------------------------------------------------------------

//Excel导出函数
bool __fastcall TfrmStaff::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		MessageBox(0,"没有数据！","错误确认" ,MB_ICONWARNING);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	v.OlePropertyGet("Cells",1,5).OlePropertySet("Value","采购员/业务员" );

/*v.OlePropertyGet("Cells",2,1).OlePropertySet("Value","单位名称" );
	temptext = "'"+ etname->Text;
	v.OlePropertyGet("Cells",2,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",2,4).OlePropertySet("Value","联系人" );
	temptext = "'"+ etcontax->Text;
	v.OlePropertyGet("Cells",2,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","所属区域" );
	temptext = "'"+ CBlocal->Text;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","采购员" );
	temptext = "'"+ CBsale->Text;
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());  */

	n=1;

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

void __fastcall TfrmStaff::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStaff::etnameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStaff::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStaff::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {     //新单
		BtnNew->Click();
	}
	if (Key == VK_F3) {     //修改
		BtnFinish->Click();
	}
	if (Key == VK_F5) {     //删除
		BtnDelete->Click();
	}
	if (Key == VK_F6) {     //导出
		BtnExport->Click();
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

