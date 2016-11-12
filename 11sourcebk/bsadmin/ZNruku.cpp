//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZNruku.h"
#include "procureheader.h"
#include "procuredetail.h"
#include "StorageMngForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "MDIChild"
TfrmZNruku *frmZNruku;
//---------------------------------------------------------------------------
__fastcall TfrmZNruku::TfrmZNruku(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	groupid = -1;
	detail = false;
}
//---------------------------------------------------------------------------
void TfrmZNruku::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	aq->Connection = m_con;
	cmdAddNtHeader->Connection = m_con ;
	cmdAddNote->Connection = m_con ;
}
void __fastcall TfrmZNruku::SpeedButton1Click(TObject *Sender)
{
	Tfrmprocureheader * frm = new Tfrmprocureheader(Application);
	frm->groupid = groupid;
	frm->Init(&linfo);
	if (frm->ShowModal() == mrOk) {
		groupid = frm->groupid ;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmZNruku::SpeedButton2Click(TObject *Sender)
{
	if (groupid == -1) {
		MessageBoxA(0,"请先筛选采购单！","提示",MB_ICONASTERISK);
		return;
	}
	Tfrmprocuredetail * frm = new Tfrmprocuredetail(Application);
	frm->groupid = groupid;
	frm->Init(&linfo);
	if (frm->ShowModal() == mrOk ) {
		detail = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmZNruku::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNruku::SpeedButton3Click(TObject *Sender)
{
	if (groupid == -1) {
		MessageBoxA(0,"请先筛选采购单！","提示",MB_ICONASTERISK);
		return;
	}
	AddNtHeader();
	detail = false;
	groupid = -1;
	returncode = "已生成入库单：\n" + returncode + "\n是否查看？";
	AnsiString sql;
	sql = "select * from BS_StorageNoteHeader where id >= " + IntToStr(sgfirstid) + " and id <= " + IntToStr(sgheaderid) ;
	if (MessageBoxA(0,returncode.c_str(),"询问",MB_ICONQUESTION|MB_OKCANCEL)==1 )
	{
	//转入库单查询
		TfrmStorageMng * frm = new TfrmStorageMng(Application);
		frm->Init(&linfo);
		frm->QryNtHeader(sgfirstid);
		frm->editdanhao->Text = frm->dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		//frm->BtnSave->Click();
		frm->SaveOrNot = true;
		frm->BtnSave->Enabled = false;
		frm->dbnbedtAddCosts->Enabled = false;
		frm->membk->Enabled = false;
		frm->dbedtSupplySN->Enabled = false;
		frm->dblkpcbbSupplierID->Enabled = false;
		frm->sbnewcustomer->Enabled = false;
		frm->querydan->Connection = linfo.con;
		frm->querydan->Close();
		frm->querydan->SQL->Clear();
		frm->querydan->SQL->Add(sql);
		frm->querydan->Open();
	}
}
//---------------------------------------------------------------------------
void TfrmZNruku::AddNtHeader()//单头入库
{
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
	cmdAddNtHeader->Parameters->ParamByName("@CODEMODE")->Value = 0;
	cmdAddNtHeader->Parameters->ParamByName("@groupid")->Value = groupid;
	cmdAddNtHeader->Parameters->ParamByName("@bkstackID")->Value = 0;
	//cmdAddNtHeader->Parameters->ParamByName("@ReturnCode")->Value = "1";
	cmdAddNtHeader->Execute();
	returncode =  cmdAddNtHeader->Parameters->ParamByName("@ReturnCode")->Value ;
	sgfirstid =  cmdAddNtHeader->Parameters->ParamByName("@Returnint")->Value ;
	sgheaderid =  cmdAddNtHeader->Parameters->ParamByName("@RETURN_VALUE")->Value;
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNruku::SpeedButton4Click(TObject *Sender)
{
	if (!detail) {
    	MessageBoxA(0,"请先筛选明细！","提示",MB_ICONASTERISK);
		return;
	}
	AddNote();
	detail = false;
	groupid = -1;
	returncode = "已生成入库单：\n" + returncode + "\n是否查看？";
	AnsiString sql;
	sql = "select * from BS_StorageNoteHeader where id >= " + IntToStr(sgfirstid) + " and id <= " + IntToStr(sgheaderid) ;
	if (MessageBoxA(0,returncode.c_str(),"询问",MB_ICONQUESTION|MB_OKCANCEL)==1 )
	{
	//转入库单查询
    	TfrmStorageMng * frm = new TfrmStorageMng(Application);
		frm->Init(&linfo);
		frm->QryNtHeader(sgfirstid);
		frm->editdanhao->Text = frm->dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		//frm->BtnSave->Click();
		frm->SaveOrNot = true;
		frm->BtnSave->Enabled = false;
		frm->dbnbedtAddCosts->Enabled = false;
		frm->membk->Enabled = false;
		frm->dbedtSupplySN->Enabled = false;
		frm->dblkpcbbSupplierID->Enabled = false;
		frm->sbnewcustomer->Enabled = false;
		frm->querydan->Connection = linfo.con;
		frm->querydan->Close();
		frm->querydan->SQL->Clear();
		frm->querydan->SQL->Add(sql);
		frm->querydan->Open();
	}
}
//---------------------------------------------------------------------------
void TfrmZNruku::AddNote()//明细入库
{
	cmdAddNote->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNote->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 1;
	cmdAddNote->Parameters->ParamByName("@CODEMODE")->Value = 0;
	cmdAddNote->Parameters->ParamByName("@groupid")->Value = groupid;
	cmdAddNote->Parameters->ParamByName("@bkstackID")->Value = 0;
	//cmdAddNote->Parameters->ParamByName("@ReturnCode")->Value = "1";
	cmdAddNote->Execute();
	returncode =  cmdAddNote->Parameters->ParamByName("@ReturnCode")->Value ;
	sgfirstid =  cmdAddNote->Parameters->ParamByName("@Returnint")->Value ;
	sgheaderid =  cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
}
//---------------------------------------------------------------------------

