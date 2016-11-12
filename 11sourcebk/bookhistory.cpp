//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bookhistory.h"
#include "alteramount.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmbookhistory *frmbookhistory;
//---------------------------------------------------------------------------
__fastcall Tfrmbookhistory::Tfrmbookhistory(TComponent* Owner,TADOConnection *con,int stgid,int catalogid,int userid)
	: TForm(Owner)
{
	fcon = con;
	fstgid = stgid;
	m_catalogSearchMode = 0;
	fuserid = userid;
	dtpstart->Date = Date();
	dtpend->Date = Date();
	aq1->Connection = con;
	aq2->Connection = con;
	aq3->Connection = con;
	aq4->Connection = con;
	aq5->Connection = con;
	aq6->Connection = con;
	aq7->Connection = con;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select * from SYS_BSSET where name = 'changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	ChangeDisplay  = aq->FieldByName("value")->AsBoolean ;

	sql = "select sum(amount) as amount from stk_bookinfo where stgid = " + IntToStr(stgid) + " and bkcatalogid = " + IntToStr(catalogid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edamount->Text = aq->FieldByName("amount")->AsAnsiString ;

	sql = "select name from bs_bookcatalog where id = " + IntToStr(catalogid);
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	bookname = aq->FieldByName("name")->AsAnsiString ;

	sql = "select ReadPurview from SYS_GroupAction left join SYS_UserGroup on SYS_GroupAction.GroupID = SYS_UserGroup.GroupID "
			" left join sys_action A1 on SYS_GroupAction.actionid = A1.Code "
			" left join sys_action A2 ON A2.CODE = A1.parent "
			" where A1.ActionName = '折扣查询' "
			" and A2.ActionName = '入库查询' "
			" and SYS_UserGroup.Userid = " + IntToStr(fuserid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	rkdiscount = aq->FieldByName("ReadPurview")->AsBoolean ;

	sql = "select ReadPurview from SYS_GroupAction left join SYS_UserGroup on SYS_GroupAction.GroupID = SYS_UserGroup.GroupID "
			" left join sys_action A1 on SYS_GroupAction.actionid = A1.Code "
			" left join sys_action A2 ON A2.CODE = A1.parent "
			" where A1.ActionName = '折扣查询' "
			" and A2.ActionName = '入库查询' "
			" and SYS_UserGroup.Userid = " + IntToStr(fuserid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	rkdiscount = aq->FieldByName("ReadPurview")->AsBoolean ;

	sql = "select ReadPurview from SYS_GroupAction left join SYS_UserGroup on SYS_GroupAction.GroupID = SYS_UserGroup.GroupID "
			" left join sys_action A1 on SYS_GroupAction.actionid = A1.Code "
			" left join sys_action A2 ON A2.CODE = A1.parent "
			" where A1.ActionName = '折扣查询' "
			" and A2.ActionName = '发货查询' "
			" and SYS_UserGroup.Userid = " + IntToStr(fuserid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	wsdiscount = aq->FieldByName("ReadPurview")->AsBoolean ;

   	dg1->OnDrawColumnCell=dg1DrawColumnCell;
	delete aq;
	bkcatalogid = catalogid;
	Query();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbookhistory::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void Tfrmbookhistory::Query()
{
	AnsiString sql;
	switch (rg->ItemIndex ) {
		case 0://订单
			sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.OrderNtCode AS Code,dbo.UF_BS_GetClientName(B.VendorID) as Name,A.state,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,A.SendAmount,A.UnsendAmount,sys_user.name as opname,A.class,A.localnum "
					" from BS_OrderNote A left join BS_OrderNoteHeader B on A.OrderNtHeaderID = B.id left join sys_user on B.OperatorID = sys_user.id where A.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0";
			}
			sql = sql +"  union all  ";
			sql = sql+" select 1 id, convert (nvarchar(10),HdTime,120) hdtime,OrderNtCode code,orderuser name,0 state,"
					" amount, discount, fixedprice,discountedprice,sended,amount-sended unsendamount,'C网' opname,'' class,os.stocklockamount "
					" from dbo.C_OrderSearchDetail cd left join dbo.C_BS_Order_Stocklock os on cd.c_bs_orderNoteID=os.COrderNoteID where bookcatalogid = " + IntToStr(bkcatalogid);
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
			}

			aq1->Close();
			aq1->SQL->Clear();
			aq1->SQL->Add(sql);
			aq1->Open();
		  /*	dg1->Columns->Items[0]->Title->Caption = "客户名称";
			dg1->Columns->Items[2]->Title->Caption = "订货数量";
			dg1->Columns->Items[6]->Title->Caption = "已发数量";
			dg1->Columns->Items[7]->Title->Caption = "未发数量";
			dg1->Columns->Items[6]->Visible = true;
			dg1->Columns->Items[7]->Visible = true;
			dg1->Columns->Items[8]->Visible = true;
		  */


				dg1->Visible = true;
				dbgridcg->Visible = false;
				dbgridrk->Visible = false;
				dbgridfh->Visible = false;
				dbgridls->Visible = false;
				dbgridps->Visible = false;
		break;
		case 1: //采购
			sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.ProcureNtCode AS Code,CUST_CustomerInfo.Name as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,A.RecAmount as SendAmount,A.UnrecAmount as UnsendAmount,sys_user.name as opname "
					" from BS_ProcureNote A left join BS_ProcureNoteHeader B on A.ProcureNtHeaderID = B.id "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join CUST_CustomerInfo on B.SupplierID = CUST_CustomerInfo.id where A.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0";
			}

			aq3->Close();
			aq3->SQL->Clear();
			aq3->SQL->Add(sql);
			aq3->Open();
		   /*	dg1->Columns->Items[0]->Title->Caption = "供应商名称";
			dg1->Columns->Items[2]->Title->Caption = "采购数量";
			dg1->Columns->Items[6]->Title->Caption = "已到数量";
			dg1->Columns->Items[7]->Title->Caption = "未到数量";
			dg1->Columns->Items[6]->Visible = true;
			dg1->Columns->Items[7]->Visible = true;
			dg1->Columns->Items[8]->Visible = false;
			dg1->Visible = true; */
				dg1->Visible = false;
				dbgridcg->Visible = true;
				dbgridrk->Visible = false;
				dbgridfh->Visible = false;
				dbgridls->Visible = false;
				dbgridps->Visible = false;

		break;
		case 2:
		//入库
			if (ChangeDisplay) {
				sql = "select distinct isnull(att.camount,0) camount,A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.StgNtCodeStr AS Code,CUST_CustomerInfo.Name as Name,"
					" A.Amount,A.amount + isnull(att.camount,0) totalamount,A.Discount,A.FixedPrice+isnull(att.camount,0)*ca.price as totalfixedprice ,A.DiscountedPrice + isnull(att.camount,0)*ca.price*A.discount*0.01 as totaldiscountprice,sys_user.name as opname,0 as SendAmount,0 as UnsendAmount "
					" from BS_StorageNote A left join BS_StorageNoteHeader B on A.StgNtHeaderID = B.id "
					" left join CUST_CustomerInfo on B.SupplierID = CUST_CustomerInfo.id "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id "
					" left join BS_BookCatalog ca on STK_BookInfo.BkcatalogID = ca.id "
					" left join BS_StorageNote_attachment att on A.id  = att.BS_StorageNoteID where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
			}
			else
			{
				sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.StgNtCode AS Code,CUST_CustomerInfo.Name as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,sys_user.name as opname,0 as SendAmount,0 as UnsendAmount "
					" from BS_StorageNote A left join BS_StorageNoteHeader B on A.StgNtHeaderID = B.id "
					" left join CUST_CustomerInfo on B.SupplierID = CUST_CustomerInfo.id "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
			}

			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0 order by HdTime";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0 order by HdTime";
			}

			aq4->Close();
			aq4->SQL->Clear();
			aq4->SQL->Add(sql);
			aq4->Open();
			/*
			dg1->Columns->Items[0]->Title->Caption = "供应商名称";
			dg1->Columns->Items[2]->Title->Caption = "入库数量";
			dg1->Columns->Items[6]->Visible = false;
			dg1->Columns->Items[7]->Visible = false;
			dg1->Columns->Items[8]->Visible = false;
			dg1->Visible = true;  */
			//dbgridcg->DataSource=ds1;
				dg1->Visible = false;
				dbgridcg->Visible = false;
				dbgridrk->Visible = true;
				dbgridfh->Visible = false;
				dbgridls->Visible = false;
				dbgridps->Visible = false;
		break;
		case 3://发货
			if (ChangeDisplay) {
				sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.WsaleNtCodeStr AS Code,dbo.UF_BS_GetClientName(B.VendorID) as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,sys_user.name as opname,0 as SendAmount,0 as UnsendAmount,A.class "
					" from BS_WsaleNote A left join BS_WsaleNoteHeader B on A.WsaleNtHeaderID = B.id "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
			}
			else
			{
				sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.WsaleNtCode AS Code,dbo.UF_BS_GetClientName(B.VendorID) as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,sys_user.name as opname,0 as SendAmount,0 as UnsendAmount,A.class "
					" from BS_WsaleNote A left join BS_WsaleNoteHeader B on A.WsaleNtHeaderID = B.id "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
			}

			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0 order by HdTime";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0 order by HdTime";
			}

			aq5->Close();
			aq5->SQL->Clear();
			aq5->SQL->Add(sql);
			aq5->Open();
			/*
			dg1->Columns->Items[0]->Title->Caption = "客户名称";
			dg1->Columns->Items[2]->Title->Caption = "发货数量";
			dg1->Columns->Items[6]->Visible = false;
			dg1->Columns->Items[7]->Visible = false;
			dg1->Columns->Items[8]->Visible = true;
			dg1->Visible = true;   */
				//dbgridcg->DataSource=ds1;
				dg1->Visible = false;
				dbgridcg->Visible = false;
				dbgridrk->Visible = false;
				dbgridfh->Visible = true;
				dbgridls->Visible = false;
				dbgridps->Visible = false;
		break;
		case 4://零售
			sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.RetailNtCode AS Code,CUST_MemberInfo.Name as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,sys_user.name as opname,0 as SendAmount,0 as UnsendAmount "
					" from BS_RetailNote A left join BS_RetailNoteHeader B on A.RetailNtHeaderID = B.id "
					" left join CUST_MemberInfo on B.MemberID = CUST_MemberInfo.ID "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0";
			}


			aq6->Close();
			aq6->SQL->Clear();
			aq6->SQL->Add(sql);
			aq6->Open();
			/*
			dg1->Columns->Items[0]->Title->Caption = "会员名称";
			dg1->Columns->Items[2]->Title->Caption = "零售数量";
			dg1->Columns->Items[6]->Visible = false;
			dg1->Columns->Items[7]->Visible = false;
			dg1->Columns->Items[8]->Visible = false;
			dg1->Visible = true; */
					//dbgridcg->DataSource=ds1;
				dg1->Visible = false;
				dbgridcg->Visible = false;
				dbgridrk->Visible = false;
				dbgridfh->Visible = false;
				dbgridls->Visible = true;
				dbgridps->Visible = false;
		break;
		case 5: //配送
			sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.ZNDiaoNtCode AS Code,C.Name as Name,D.name as outname,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,sys_user.name as opname,0 as SendAmount,0 as UnsendAmount "
					" from BS_ZN_DiaoNote A left join BS_ZN_DiaoNoteHeader B on A.DiaoNtHeaderID = B.id "
					" left join SYS_StorageInfo C on B.outstorage = C.ID "
					" left join SYS_StorageInfo D on B.instorage = D.ID "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join STK_BookInfo on A.Bkinfoid = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid) + " and (B.outstorage = " + IntToStr(fstgid) + " or B.instorage = " + IntToStr(fstgid) + ")";
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0";
			}

			aq7->Close();
			aq7->SQL->Clear();
			aq7->SQL->Add(sql);
			aq7->Open();
		   /*	dg1->Columns->Items[0]->Title->Caption = "调出店";
			dg1->Columns->Items[1]->Width = 80;
			dg1->Columns->Items[2]->Title->Caption = "配送数量";
            	dg1->Columns->Items[1]->Field = aq1->FieldByName("outname");
			dg1->Columns->Items[6]->Visible = false;
			dg1->Columns->Items[7]->Visible = false;
			dg1->Columns->Items[8]->Visible = false;
			dg1->Columns->Items[1]->Visible = true;
			dg1->Visible = true;  */
          // 	dg1->Columns->Items[1]->Field = aq1->FieldByName("outname");
				//dbgridcg->DataSource=ds1;
				dg1->Visible = false;
				dbgridcg->Visible = false;
				dbgridrk->Visible = false;
				dbgridfh->Visible = false;
				dbgridls->Visible = false;
				dbgridps->Visible = true;
		break;
    default:
        ;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbookhistory::rgClick(TObject *Sender)
{

   //	dg1->Columns->Items[1]->Field = NULL;
   //	dg1->Columns->Items[1]->Visible = false;
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::dg1TitleClick(TColumnEh *Column)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aq1->Sort == "") {
		aq1->Sort =  Column->FieldName + " ASC";
	}
	else if (aq1->Sort == qusort) {
		aq1->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aq1->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::N1Click(TObject *Sender)
{
if (aq1->IsEmpty() || aq1->RecordCount == 0 || rg->ItemIndex != 0) {
    	return;
	}
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	Tfrmalteramount * frm = new Tfrmalteramount(Application);
	if (frm->ShowModal() == mrOk  ) {
		int amount = aq1->FieldByName("SendAmount")->AsInteger ;
		sql = "update BS_OrderNote set SendAmount = " + frm->ednum->Text + " where id = " + aq1->FieldByName("id")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		AnsiString msg;
		msg = "更改订单" + aq1->FieldByName("Code")->AsAnsiString + "的书目《" + bookname + "》发货数量" + IntToStr(amount) + "为" + frm->ednum->Text;

		AddEvent(3,"历史明细",fuserid,fstgid,msg.c_str(),fcon);
		aq1->Active = false;
		aq1->Active = true;
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::N3Click(TObject *Sender)
{
if (aq3->IsEmpty() || aq3->RecordCount == 0 ) {
    	return;
	}
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	Tfrmalteramount * frm = new Tfrmalteramount(Application);
	if (frm->ShowModal() == mrOk  ) {
		int amount = aq3->FieldByName("SendAmount")->AsInteger ;
		sql = "update BS_ProcureNote set RecAmount = " + frm->ednum->Text + " where id = " + aq3->FieldByName("id")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		AnsiString msg;
		msg = "更改采购单" + aq3->FieldByName("Code")->AsAnsiString + "的书目《" + bookname + "》到货数量" + IntToStr(amount) + "为" + frm->ednum->Text;

		AddEvent(3,"历史明细",fuserid,fstgid,msg.c_str(),fcon);
		aq1->Active = false;
		aq1->Active = true;
		delete aq;
	}
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::dg1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumnEh *Column, Gridseh::TGridDrawState State)
{	 if (rg->ItemIndex == 0 && aq1->FieldByName("state")->AsInteger == 1 ) {
		dg1->Canvas->Font->Color = clRed ;
		dg1->Canvas->FillRect(Rect);
		dg1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
	else
	{
		dg1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}

}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::dbgridcgTitleClick(TColumnEh *Column)
{
  if (aq3->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aq3->Sort == "") {
		aq3->Sort =  Column->FieldName + " ASC";
	}
	else if (aq3->Sort == qusort) {
		aq3->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aq3->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::dbgridfhTitleClick(TColumnEh *Column)
{
if (aq5->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aq5->Sort == "") {
		aq5->Sort =  Column->FieldName + " ASC";
	}
	else if (aq5->Sort == qusort) {
		aq5->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aq5->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::dbgridlsTitleClick(TColumnEh *Column)
{
if (aq6->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aq6->Sort == "") {
		aq6->Sort =  Column->FieldName + " ASC";
	}
	else if (aq6->Sort == qusort) {
		aq6->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aq6->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::dbgridpsTitleClick(TColumnEh *Column)
{
if (aq7->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aq7->Sort == "") {
		aq7->Sort =  Column->FieldName + " ASC";
	}
	else if (aq7->Sort == qusort) {
		aq7->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aq7->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::dbgridrkTitleClick(TColumnEh *Column)
{
if (aq4->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aq4->Sort == "") {
		aq4->Sort =  Column->FieldName + " ASC";
	}
	else if (aq4->Sort == qusort) {
		aq4->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aq4->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

