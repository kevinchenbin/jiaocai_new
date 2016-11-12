//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitchaigoufromorder.h"
#include "ProcureMng.h"
#include "ordertocaigoupipei.h"
#include "firstcaigou.h"
#include "UnitFeizhensi.h"
#include "unitchaigoufromorderchakan.h"
#include "UnitcaigouOrderSelect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmchaigoufromorder *frmchaigoufromorder;
//---------------------------------------------------------------------------
__fastcall Tfrmchaigoufromorder::Tfrmchaigoufromorder(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	groupid = -1;
	firstfahuo = -1;
	confirmcaigou = -1;
	detail = false;
}
//---------------------------------------------------------------------------
void Tfrmchaigoufromorder::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	query->Connection = li->con ;
	aq->Connection = li->con ;
	cmdAddNote->Connection = li->con;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmchaigoufromorder::SpeedButton1Click(TObject *Sender)
{
	Tfrmcaigouorderselect * frm = new Tfrmcaigouorderselect(Application,linfo.con,linfo.storageID,0,0,linfo.userID);
	frm->Show();
	//delete frm;

	return;

	AnsiString sql;
	if (groupid == -1) {
		sql = "select max(groupid) as groupid from BS_Tmporder ";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->IsEmpty() ) {
			groupid = 0;
		}
		else
		{
			groupid = query->FieldByName("groupid")->AsInteger + 1;
		}
	}
	groupid = 0;
	sql = "select BS_OrderNoteHeader.id,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.PressCount,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_OrderNote.Amount,BS_OrderNote.UnsendAmount,BS_OrderNote.localnum,BS_OrderNoteHeader.OrderNtCode,BS_OrderNote.BkcatalogID,"
			"Order_lock.usableamount,BS_PressInfo.AbbreviatedName,BS_PressInfo.FullName,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_OrderNoteHeader.VendorID,BS_OrderNote.Discount,BS_OrderNote.id as ordernoteid  "
			"from BS_OrderNoteHeader left join BS_OrderNote on BS_OrderNoteHeader.id = BS_OrderNote.OrderNtHeaderID "
			"left join STK_BookInfo on BS_OrderNote.BkcatalogID = STK_BookInfo.BkcatalogID "
			"left join BS_BookCatalog on BS_OrderNote.BkcatalogID = BS_BookCatalog.id "
			"left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
			"left join Order_lock on BS_OrderNote.BkcatalogID = Order_lock.BkcatalogID "
			"where BS_OrderNoteHeader.StgID = " + IntToStr(linfo.storageID) + " and BS_OrderNoteHeader.state in (0,1) and BS_OrderNote.state = 0  "
			"group by BS_OrderNoteHeader.id,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_OrderNote.UnsendAmount,BS_OrderNoteHeader.OrderNtCode,BS_OrderNote.BkcatalogID,BS_PressInfo.AbbreviatedName,BS_OrderNoteHeader.VendorID,BS_OrderNoteHeader.state,BS_OrderNote.Discount,BS_OrderNote.id,BS_OrderNote.localnum,Order_lock.usableamount,BS_BookCatalog.PressCount,BS_OrderNote.Amount,BS_PressInfo.FullName "
			"order by BS_OrderNoteHeader.id,BS_OrderNoteHeader.VendorID ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount > 0 && firstfahuo == -1) {
		Tfrmordertocaigoupipei * frm = new Tfrmordertocaigoupipei(Application,aq);
		frm->groupid = groupid;
		if (frm->ShowModal() == mrOk ) {
			firstfahuo = 1;
		}
	}
	Tfrmfirstcaigou * fram = new Tfrmfirstcaigou(Application);
	fram->groupid = groupid;
	fram->Init(&linfo);
	if (fram->ShowModal() ==  mrOk ) {
		confirmcaigou = 1;
		if (MessageBoxA(0,"已生成非正式采购单，是否查看","询问",MB_ICONQUESTION|MB_OKCANCEL)==1 )
		{
			SpeedButton2->Click();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmchaigoufromorder::SpeedButton2Click(TObject *Sender)
{
	/*if (confirmcaigou == -1) {
        MessageBoxA(0,"无采购书目！","提示",MB_ICONASTERISK);
		return;
	}  */
	Tfrmfeizhengshicai *frm = new Tfrmfeizhengshicai(Application,m_con,0,m_storageID,linfo.userID);
	//frm->Show();
	if (frm->ShowModal() == mrOk ) {
		if (MessageBoxA(0,"是否生成正式采购单","询问",MB_ICONQUESTION|MB_OKCANCEL)==1 )
		{
			SpeedButton3->Click();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmchaigoufromorder::SpeedButton3Click(TObject *Sender)
{
	if (AddCaigou()!=1) {
		return;
	}
	AnsiString sql;
	sql = "select id from BS_ProcureNoteHeader where ProcureNtCode in(" + returncode + ")" ;

	Tfrmdaochu *frm = new Tfrmdaochu(Application);
	frm->init(linfo.con,linfo.storageID);
	frm->info  = "已生成采购单：\n" + returncode + "\n是否查看？";;
	frm->DanHao = returncode;
	if (mrOk  == frm->ShowModal())
	{
		TfrmProcureMng * frm = new TfrmProcureMng(Application);
		frm->Init(&linfo);
        frm->DelInvalidNtHeader();
		frm->QryNtHeader(sgfirsthid);
		frm->DBNavigator1->Enabled = true;
		frm->aqheader->Close();
		frm->aqheader->SQL->Clear();
		frm->aqheader->SQL->Add(sql);
		frm->aqheader->Open();
	}
	delete frm;
	sql = "delete BS_Tmporder where modle = 1 and userid = " + IntToStr(linfo.userID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
 /*	if (MessageBoxA(0,returncode.c_str(),"询问",MB_ICONQUESTION|MB_OKCANCEL)==1 )
  ///	{
	//转采购单查询
		TfrmProcureMng * frm = new TfrmProcureMng(Application);
		frm->Init(&linfo);
		frm->QryNtHeader(sgfirsthid);
		frm->DBNavigator1->Enabled = true;
		frm->aqheader->Close();
		frm->aqheader->SQL->Clear();
		frm->aqheader->SQL->Add(sql);
		frm->aqheader->Open();
	}   */
    groupid = -1;
	firstfahuo = -1;
	confirmcaigou = -1;
	detail = false;
}
//---------------------------------------------------------------------------

int Tfrmchaigoufromorder::AddCaigou()
{
	cmdAddNote->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNote->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNote->Parameters->ParamByName("@CODEMODE")->Value = 0;
	cmdAddNote->Parameters->ParamByName("@groupid")->Value = 0;
	cmdAddNote->Execute();
	try
	{
		returncode =  cmdAddNote->Parameters->ParamByName("@ReturnCode")->Value ;
		sgfirsthid =  cmdAddNote->Parameters->ParamByName("@Returnint")->Value ;
		sgheaderid =  cmdAddNote->Parameters->ParamByName("@return_value")->Value;
		return 1;
	}
	catch(...)
	{
		return 0;
	}
}
//---------------------------------------------------------------------------

