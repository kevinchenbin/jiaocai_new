//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitcaigouOrderSelect.h"
#include "UnitSelectClient.h"
#include "NoteCode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzDBCmbo"
#pragma link "RzDTP"
#pragma link "RzSpnEdt"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmcaigouorderselect *frmcaigouorderselect;
//---------------------------------------------------------------------------
__fastcall Tfrmcaigouorderselect::Tfrmcaigouorderselect(TComponent* Owner,TADOConnection *cn,int stgid,int hgid,int gid,int userid)
	: TForm(Owner)
{
	con = cn;
	fstgid = stgid;
	fuserid = userid;
	ClientID = -1;
	query->Connection = cn;
	query2->Connection = cn;
	aq->Connection = cn;
	sp->Connection=cn;
   //	aqsupplier->Connection = cn;
	dtpdate->Date = Date();
	groupid = gid;
	hgroupid = hgid;
	SelectIndex =0;
	dtpdate->Date = Date();
	dtenddate->Date = Date();
	dtedtDate->Date = Date();
	chordercode->Checked = false;
	AnsiString sql;
	sql = "select * from sys_user";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbuser->AddItem(aq->FieldByName("stgid")->AsAnsiString + "店" + aq->FieldByName("name")->AsAnsiString,(TObject*)aq->FieldByName("id")->AsInteger);
		aq->Next();
	}


}

//---------------------------------------------------------------------------
void __fastcall Tfrmcaigouorderselect::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TfrmselectClient * frm = new TfrmselectClient(Application,con,edclient->Text,fstgid);
		if (mrOk == frm->ShowModal())
		{
			ClientID = frm->GetSelectID();
			ClientView();
			edtclient->SetFocus();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------
void Tfrmcaigouorderselect::ClientView()
{
		if (ClientID == -1) {
			return;
		}
	   String sql;
	   TADOQuery * aq = new TADOQuery(NULL);
	   aq->Connection = con;
	   sql = "exec USP_BS_Client_View 0," + IntToStr(ClientID)  ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		edtclient->Text = aq->FieldByName("Name")->AsAnsiString ;
		delete aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcaigouorderselect::spselectClientClick(TObject *Sender)
{

	TfrmselectClient * frm = new TfrmselectClient(Application,con,"",fstgid);
	   if (mrOk == frm->ShowModal())
	   {
			ClientID = frm->GetSelectID();
			edtclient->SetFocus();
			ClientView();
	   }
	   delete frm;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcaigouorderselect::RzButton1Click(TObject *Sender)
{
	AnsiString sql,stgstr,csqlwhere;
	stgstr = "-1";
	csqlwhere="";
	bool bsearch;
	bool csearch;
	bsearch=false;
	csearch=false;
	int SearchStates;
	TADOQuery *aq;
	if (cbstg->Text== "全部") {

		for (int i = 1 ; i < cbstg->Items->Count; i++) {
		stgstr = stgstr + "," + IntToStr((int)(cbstg->Items->Objects[i]));
	}
	}else
	{
		stgstr = stgstr + "," + IntToStr((int)(cbstg->Items->Objects[cbstg->ItemIndex]));
	}
	//case when OL.UnsendAmount - OL.stkamount - OL.UnrecAmount < 0 then 0 when OL.UnsendAmount - OL.stkamount - OL.UnrecAmount < BS_OrderNote.UnsendAmount-BS_OrderNote.localnum THEN OL.UnsendAmount - OL.stkamount - OL.UnrecAmount ELSE BS_OrderNote.UnsendAmount-BS_OrderNote.localnum END as needprocurenum

   /*  此段代码改到存储过程中实现
	  sql = "select distinct BS_OrderNoteHeader.OrderNtCode,BS_OrderNoteHeader.ID as OID,BS_OrderNoteHeader.VendorID as ClientID,"
			" dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as ClientName,BS_OrderNoteHeader.id, "
			" convert(nvarchar(10),BS_OrderNoteHeader.HdTime,120) as HdTime,BS_OrderNoteHeader.Remarks,STG.name as stgname ,"
			" BS_OrderNote.UnsendAmount-BS_OrderNote.localnum as needprocurenum,BS_OrderNote.ID as NoteID,BS_OrderNote.fixedprice,BS_OrderNote.discountedprice,BS_OrderNote.discount,OL.stkamount, OL.stkamount - OL.localnum as usableamount,OL.UnrecAmount, "
			" BS_OrderNote.amount,BS_OrderNote.UnsendAmount,BS_OrderNote.localnum,OL.UnsendAmount AS toatalunamount,BS_OrderNote.ID DetailID ,C.ID as Bkcatalogid,C.ISBN,C.name ,C.price,C.author,"
			" BP.FullName,BP.AbbreviatedName,BT.Name "
			" from BS_OrderNoteHeader left join BS_OrderNote on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" Left join bs_bookcatalog C ON BS_OrderNote.bkcatalogid = C.ID "
			" left join BS_PressInfo BP ON  C.Pressid = BP.ID "
			" left join BS_BookType BT ON C.Smallbooktypeid = BT.ID "
			" left join SYS_StorageInfo STG ON BS_OrderNoteHeader.stgid = STG.ID "
			" left join UV_order_pro OL ON BS_OrderNote.Bkcatalogid = OL.bkcatalogid and OL.stgid = STG.ID "
			" where BS_OrderNoteHeader.shenheistate = 2 ";
		*/
		sql="";
	if (chshiji->Checked)	//是否列出不需要负采购数量												 //全店
	{
        //(OL.UnsendAmount - OL.stkamount - OL.UnrecAmount > 0 and BS_OrderNote.UnsendAmount > 0)
		sql = sql + " and  BS_OrderNote.UnsendAmount > BS_OrderNote.localnum  and BS_OrderNoteHeader.StgID in( " +stgstr + ") and BS_OrderNoteHeader.state in (0,1) and BS_OrderNoteHeader.type=0 and BS_OrderNote.needprocurenum = 0 and BS_OrderNote.state = 0 ";
	}else
	{
		sql = sql + " and BS_OrderNoteHeader.StgID in( " +stgstr + ") and BS_OrderNoteHeader.state in (0,1) and BS_OrderNoteHeader.type=0 and BS_OrderNote.needprocurenum = 0 and BS_OrderNote.state = 0 ";
	}

	if (chordercode->Checked && edordercode->Text != "") {
		sql = sql + " and BS_OrderNoteHeader.OrderNtCode = " + edordercode->Text ;
	   bsearch=true;
	}
	if (chdate->Checked ) {
		sql = sql + " and datediff(day,'" + DateToStr(dtpdate->Date) + "',BS_OrderNoteHeader.HdTime) >= 0 " ;
	   bsearch=true;
	   csearch=true;
	}
	if (cbenddate->Checked) {
		sql = sql + " and datediff(day,'" + DateToStr(dtenddate->Date) + "',BS_OrderNoteHeader.HdTime) <= 0 " ;
	   bsearch=true;
	   csearch=true;
	}

	if (chclient->Checked && edtclient->Text != "") {
		sql = sql + " and BS_OrderNoteHeader.VendorID in( select id from dbo.GetChild(" + IntToStr(ClientID) + "))";
	 bsearch=true;
	}
	if (chuser->Checked && cbuser->Text != "") {
		int user;
		try {
			user = (int)cbuser->Items->Objects[cbuser->ItemIndex];
		} catch (...) {
			MessageBoxA(0,"请选择正确的操作员！","提示",MB_ICONINFORMATION);
        	return;
		}
		sql = sql + " and BS_OrderNoteHeader.OperatorID = " + IntToStr(user);
	 bsearch=true;
	}

	if (cbclient->Checked) {
	   csqlwhere=csqlwhere+ " and OrderUser like '%"+editclient->Text+"%'";
	 csearch=true;
	}
	if (cbordernum->Checked) {
	   csqlwhere=csqlwhere+ " and OrderNtCode like '%"+editordernum->Text+"%'";
	 csearch=true;
	}

	if (chbook->Checked && edtCatalog->Text != "" ) {
	   bsearch=true;
	   csearch=true;
	  switch (SelectIndex ) {
			case 0:
			   sql = sql + " and C.barcode = '" + edtCatalog->Text +"'";
			   csqlwhere=csqlwhere+  " and C.barcode = '" + edtCatalog->Text +"'";
			break;
			case 1:
			   sql = sql + " and C.userdefcode like '%" + edtCatalog->Text +"%'";
				csqlwhere=csqlwhere+ " and C.userdefcode like '%" + edtCatalog->Text +"%'";
			break;
			case 2:
			   sql = sql + " and C.name like '%" + edtCatalog->Text +"%'";
				csqlwhere=csqlwhere+ " and C.name like '%" + edtCatalog->Text +"%'";
			break;
			case 3:
			   sql = sql + " and C.price = " + edtCatalog->Text ;
			   csqlwhere=csqlwhere+  " and C.price = " + edtCatalog->Text ;
			break;
			case 4:
			   sql = sql + " and C.author like '%" + edtCatalog->Text +"%'";
			   csqlwhere=csqlwhere+" and C.author like '%" + edtCatalog->Text +"%'";
			break;
	  default:
		  ;
	  }
	}


	if (chpress->Checked && cbpress->Text !="") {
		sql = sql+ " and C.pressID = "+IntToStr((int)(cbpress->Items->Objects[cbpress->ItemIndex]));  ;
	   csqlwhere=csqlwhere+ " and PressInfoID = "+IntToStr((int)(cbpress->Items->Objects[cbpress->ItemIndex]));
       bsearch=true;
	   csearch=true;

	}
	if (chtype->Checked && cbtype->Text !="") {
		sql = sql+ " and C.smallbooktypeid = "+IntToStr(cbtype->Items->IndexOfName(cbtype->Text))  ;
		bsearch=true;
	   csearch=true;
	}

	  try
	  {
 //	sp->ProcedureName="C_zncgcx";
  //	sp->Refresh();
  //	sp->Parameters->Refresh();
   //	sp->Parameters->ParamByName("@BnetWhere")->Value=sql;
   //	sp->Parameters->ParamByName("@CnetWhere")->Value=csqlwhere;
   //	sp->Active=true;
	//ds->DataSet=NULL;

	/*  if ((bsearch)&&(!csearch)) {
		   SearchStates=2;
	   }
		if ((!bsearch)&&(csearch)) {
		   SearchStates=1;
	   }
	   if ((!bsearch)&&(!csearch)) {
		   SearchStates=0;
	   }
	   if ((bsearch)&&(csearch)) {
		   SearchStates=3;
	   }  */


	   SearchStates=rg->ItemIndex;



	  query->Close();
	  query->SQL->Clear();
	  query->SQL->Add("exec C_zncgcx :Bwhere,:cnetwher,:SearchStates");
	  query->Parameters->ParamByName("Bwhere")->Value =sql ;
	   query->Parameters->ParamByName("cnetwher")->Value =csqlwhere ;
	   query->Parameters->ParamByName("SearchStates")->Value =SearchStates;
	   query->Open();

	  }catch(...){};
}
//---------------------------------------------------------------------------

void Tfrmcaigouorderselect::IntoTmporder()
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	sql = "delete from BS_Tmporder where groupid = " + IntToStr(groupid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = "insert into BS_Tmporder(groupid,orderheaderid,ISBN,bookname,Price,Author,Amount,OrderNtCode,bkcatalogid,bkamount,Pressname,ClientName,Clientid,Discount,ordernoteid) "
				"select " + IntToStr(groupid) + ",BS_OrderNoteHeader.id,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_OrderNote.UnsendAmount,BS_OrderNoteHeader.OrderNtCode,BS_OrderNote.BkcatalogID,"
				"case when (BS_OrderNote.localnum + Order_lock.usableamount) > BS_OrderNote.UnsendAmount then BS_OrderNote.UnsendAmount else BS_OrderNote.localnum + Order_lock.usableamount end as amount,BS_PressInfo.AbbreviatedName,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_OrderNoteHeader.VendorID,BS_OrderNote.Discount,BS_OrderNote.id "
				"from BS_OrderNote left join BS_OrderNoteHeader on BS_OrderNoteHeader.id = BS_OrderNote.OrderNtHeaderID "
				"left join Order_lock on BS_OrderNote.Bkcatalogid = Order_lock.bkcatalogid and Order_lock.stgid = BS_OrderNoteHeader.stgid "
				"left join BS_BookCatalog on BS_OrderNote.BkcatalogID = BS_BookCatalog.id "
				"left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
				"where BS_OrderNote.UnsendAmount > 0 and BS_OrderNote.state = 0 and BS_OrderNoteHeader.id in (select headerid from BS_Tmpheader where groupid = " + IntToStr(hgroupid) + ") "
				"group by BS_OrderNoteHeader.id,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_OrderNote.UnsendAmount,BS_OrderNoteHeader.OrderNtCode,BS_OrderNote.BkcatalogID,BS_PressInfo.AbbreviatedName,BS_OrderNoteHeader.VendorID,BS_OrderNoteHeader.state,BS_OrderNote.Discount,BS_OrderNote.id,Order_lock.usableamount,BS_OrderNote.localnum ";
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}
void Tfrmcaigouorderselect::bandData()
{
   AnsiString sql;
   sql= "select ID,Name,Master from dbo.SYS_StorageInfo ";
	query2->Close();
	query2->SQL->Clear();
	query2->SQL->Add(sql);
	query2->Open();
	cbstg->Items->AddObject("全部" ,(TObject*)(-1));
   while(!query2->Eof)
   {
	 if (query2->FieldByName("Master")->AsBoolean) {
		if(fstgid != query2->FieldByName("ID")->AsInteger)
		{
		   cbstg->Items->Clear();
		   cbstg->Items->AddObject(query2->FieldByName("Name")->AsAnsiString ,(TObject*)(query2->FieldByName("ID")->AsInteger));

		   break;
		}

	 }
	 cbstg->Items->AddObject(query2->FieldByName("Name")->AsAnsiString ,(TObject*)(query2->FieldByName("ID")->AsInteger));
	 query2->Next();
   }
   cbstg->ItemIndex =0;

   sql = "select ID,abbreviatedName from dbo.BS_PressInfo";
	query2->Close();
	query2->SQL->Clear();
	query2->SQL->Add(sql);
	query2->Open();

	while(!query2->Eof)
	{
	 cbpress->Items->AddObject(query2->FieldByName("abbreviatedName")->AsAnsiString ,(TObject*)(query2->FieldByName("ID")->AsInteger));
	 query2->Next();
   }

   /*sql ="select ID,Name from dbo.CUST_CustomerInfo where type = 1";

	query2->Close();
	query2->SQL->Clear();
	query2->SQL->Add(sql);
	query2->Open();
	while(!query2->Eof)
	{
	 cbsupplier->Items->AddObject(query2->FieldByName("Name")->AsAnsiString ,(TObject*)(query2->FieldByName("ID")->AsInteger));
	 query2->Next();
   }      */



   sql ="select ID,Name from dbo.BS_BookType ";
	query2->Close();
	query2->SQL->Clear();
	query2->SQL->Add(sql);
	query2->Open();
	while(!query2->Eof)
	{
	 cbtype->Items->AddObject(query2->FieldByName("Name")->AsAnsiString ,(TObject*)(query2->FieldByName("ID")->AsInteger));
	 query2->Next();
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcaigouorderselect::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::editindexsupplierKeyPress(TObject *Sender,
          wchar_t &Key)
{
	 /*if (Key == VK_RETURN) {
		String sql = "select ID,Name from CUST_CustomerInfo where type = 1 and Name like '%" + cbsupplier->Text + "%'";
		query2->Close();
		query2->SQL->Clear();
		query2->SQL->Add(sql);
		query2->Open();
		query2->First();
		cbsupplier->Items->Clear();
		while(!query2->Eof)
		{
			cbsupplier->Items->AddObject(query2->FieldByName("Name")->AsAnsiString ,(TObject*)(query2->FieldByName("ID")->AsInteger));
			query2->Next();
		}
	 }  */
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::editindexKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		String sql = "select ID,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + editindex->Text + "%'";
		query2->Close();
		query2->SQL->Clear();
		query2->SQL->Add(sql);
		query2->Open();
		query2->First();
		cbpress->Items->Clear();
		while(!query2->Eof)
		{
			cbpress->Items->AddObject(query2->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)(query2->FieldByName("ID")->AsInteger));
			query2->Next();
		}
		cbpress->ItemIndex =0;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::N1Click(TObject *Sender)
{
 int i =  ((TMenuItem*)(Sender))->Tag ;
 SelectIndex =i;
 switch (i) {
		case 0:
			lblCatalog->Caption = "书号";
		break;
		case 1:
			lblCatalog->Caption = "自编码";
		break;
		case 2:
			lblCatalog->Caption = "书名";
		break;
		case 3:
			lblCatalog->Caption = "定价";
		break;
		case 4:
			lblCatalog->Caption = "作者";
		break;

 default:
	 ;
 }



}
//---------------------------------------------------------------------------


void __fastcall Tfrmcaigouorderselect::FormShow(TObject *Sender)
{
   bandData();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::RzButton2Click(TObject *Sender)
{
	AnsiString sql ;
	TBookmark bm;
	Screen->Cursor = crHourGlass ;
	sql = "delete BS_Tmporder where modle = 1 and userid = " + IntToStr(fuserid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();

	if (DBGrid2->SelectedRows ->Count == 0) {
		MessageBox(NULL,"请选择需要采购的明细！","提示",MB_OK|MB_ICONINFORMATION);
		Screen->Cursor = crDefault ;
		return;
	}

	sql= "select * from BS_Tmporder where 1=2";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str ;
	try
	{
		DBGrid2->DataSource->DataSet->DisableControls();
		for (int i = 0 ; i < DBGrid2->SelectedRows->Count ; i++) {

		 DBGrid2->DataSource->DataSet->Bookmark = DBGrid2->SelectedRows->Items[i];
		 bm = DBGrid2->DataSource->DataSet->GetBookmark();
		 DBGrid2->DataSource->DataSet->GotoBookmark(bm);

		 //amount 实际采购数量，bkamount 未发数量
			sql = "select sum(BS_Tmporder.bkamount) as bkamount,sum(BS_Tmporder.amount) as amount,sum(BS_OrderNote.localnum) as localnum from BS_Tmporder join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where groupid = 0 and BS_Tmporder.bkcatalogid = " + DBGrid2->DataSource->DataSet->FieldByName("Bkcatalogid")->AsAnsiString ;
			query2->Close();
			query2->SQL->Clear();
			query2->SQL->Add(sql);
			query2->Open();
			int cc = 0;

			if (aq->State != dsInsert) {
				aq->Append();
			}
			aq->FieldByName("groupid")->AsInteger =0;

			aq->FieldByName("modle")->AsInteger =1;
			aq->FieldByName("orderheaderid")->AsInteger = DBGrid2->DataSource->DataSet->FieldByName("OID")->AsInteger;
			aq->FieldByName("ordernoteid")->AsInteger = DBGrid2->DataSource->DataSet->FieldByName("DetailID")->AsInteger;

			/*if (query2->FieldByName("bkamount")->AsAnsiString != "" ) {
					cc = query->FieldByName("toatalunamount")->AsInteger - query->FieldByName("stkamount")->AsInteger - query->FieldByName("UnrecAmount")->AsInteger - query2->FieldByName("amount")->AsInteger;
					if (cc < query->FieldByName("needprocurenum")->AsInteger) {
						if (cc < 0) {
							aq->FieldByName("amount")->AsInteger = 0;
						}
						else
						{
							aq->FieldByName("amount")->AsInteger = cc;
						}
					}
					else
					{
						aq->FieldByName("amount")->AsInteger = query->FieldByName("needprocurenum")->AsInteger;
					}
			}
			else
			{
				aq->FieldByName("amount")->AsInteger =  query->FieldByName("needprocurenum")->AsInteger;
			}
			*/
			aq->FieldByName("amount")->AsInteger =  query->FieldByName("needprocurenum")->AsInteger;
			aq->FieldByName("ISBN")->AsAnsiString = DBGrid2->DataSource->DataSet->FieldByName("ISBN")->AsAnsiString;
			aq->FieldByName("BookName")->AsAnsiString = DBGrid2->DataSource->DataSet->FieldByName("bookname")->AsAnsiString;
			aq->FieldByName("price")->AsFloat  = DBGrid2->DataSource->DataSet->FieldByName("price")->AsFloat;
			aq->FieldByName("author")->AsAnsiString = DBGrid2->DataSource->DataSet->FieldByName("author")->AsAnsiString;
			aq->FieldByName("orderNtCode")->AsAnsiString = DBGrid2->DataSource->DataSet->FieldByName("OrderNtCode")->AsAnsiString;
			aq->FieldByName("bkcatalogid")->AsInteger = DBGrid2->DataSource->DataSet->FieldByName("Bkcatalogid")->AsInteger;

			aq->FieldByName("bkamount")->AsInteger = DBGrid2->DataSource->DataSet->FieldByName("UnsendAmount")->AsInteger;   // 订单订数
			aq->FieldByName("pressname")->AsAnsiString = DBGrid2->DataSource->DataSet->FieldByName("FullName")->AsAnsiString;
			aq->FieldByName("clientName")->AsAnsiString = DBGrid2->DataSource->DataSet->FieldByName("ClientName")->AsAnsiString;
			aq->FieldByName("clientid")->AsInteger = DBGrid2->DataSource->DataSet->FieldByName("ClientID")->AsInteger;
			aq->FieldByName("discount")->AsFloat  = DBGrid2->DataSource->DataSet->FieldByName("discount")->AsFloat; ;
			aq->FieldByName("fixedprice")->AsFloat = DBGrid2->DataSource->DataSet->FieldByName("fixedprice")->AsFloat;
			aq->FieldByName("discountprice")->AsFloat = DBGrid2->DataSource->DataSet->FieldByName("discountedprice")->AsFloat;
			aq->FieldByName("ISCNet")->AsInteger= DBGrid2->DataSource->DataSet->FieldByName("ISCNet")->AsInteger;



			aq->FieldByName("chenked")->AsBoolean  = true;
			aq->FieldByName("supplierid")->AsInteger = -1;
			aq->FieldByName("fahuoclient")->AsInteger = 0;
			aq->FieldByName("userid")->AsInteger = fuserid;
			aq->Post();
		 //}
	}
	DBGrid2->DataSource->DataSet->EnableControls() ;
	}catch(...)
	{
		MessageBox(NULL,"生成非正式采购单失败！","提示",MB_OK|MB_ICONINFORMATION);
		Screen->Cursor = crDefault ;
		return;
	}
	sql = "exec USP_BS_SetSupplier " + IntToStr(0)+','+IntToStr(fuserid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	MessageBox(NULL,"已生成非正式采购单！","提示",MB_OK|MB_ICONINFORMATION);
	Screen->Cursor = crDefault ;
    //Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::DBGrid2MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	int CurrNo;
		return;
	if (Button == mbLeft ) {
		if (!blSelect) {
			BookMark = query->GetBookmark();   //dataset
			blSelect = true;
			return;
		}
	}
   	if (Shift.Contains(ssShift)) {
		  CurrNo = query->FieldByName("NoteID")->AsInteger ;
		  query->DisableControls();

		  query->GotoBookmark(BookMark);
		  DBGrid2->SelectedRows->CurrentRowSelected = true;
		  if (CurrNo > query->FieldByName("NoteID")->AsInteger) {
			  while(CurrNo > query->FieldByName("NoteID")->AsInteger)
			  {
				DBGrid2->SelectedRows->CurrentRowSelected = true;
				query->Next();
			  }
		  }
		  if ( CurrNo < query->FieldByName("NoteID")->AsInteger ) {
				  while(CurrNo < query->FieldByName("NoteID")->AsInteger)
			  {
				DBGrid2->SelectedRows->CurrentRowSelected = true;
				query->Prior() ;
			  }
		  }
		  query->EnableControls();
		  query->FreeBookmark(BookMark);
		  blSelect = false;
		}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::S1Click(TObject *Sender)
{
	DBGrid2->DataSource->DataSet->DisableControls();
	query->First();
	while(!query->Eof)
	{
		DBGrid2->SelectedRows->CurrentRowSelected = true;
		query->Next();
	}
  	DBGrid2->DataSource->DataSet->EnableControls() ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::cbpressChange(TObject *Sender)
{
	if (cbpress->Text != "")
	{
    	chpress->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::cbsupplierChange(TObject *Sender)
{
	if (cbtype->Text  != "")
	{
		chtype->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::edtclientChange(TObject *Sender)
{
	if (edtclient->Text != "")
	{
		chclient->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::edordercodeChange(TObject *Sender)
{
	if (edordercode->Text != "")
	{
		chordercode->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::dtedtDateChange(TObject *Sender)
{
	NoteCode nc(dtedtDate->Date, fstgid, spedtID->IntValue);
	edordercode->Text = nc.AsString();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::spedtIDChange(TObject *Sender)
{
	if (spedtID->IntValue < 0 || spedtID->IntValue > 99999)
	{
		ShowMessage("单号错误!");
		return;
	}
	NoteCode nc(dtedtDate->Date, fstgid, spedtID->IntValue);
	edordercode->Text = nc.AsString();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::cbstgClick(TObject *Sender)
{
	int stgid;
	try {
		stgid = (int)(cbstg->Items->Objects[cbstg->ItemIndex]);
	} catch (...) {
		return;
	}
	AnsiString sql;
	sql = "select * from sys_user where stgid = " + IntToStr(stgid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbuser->Clear();
	while (!aq->Eof )
	{
		cbuser->AddItem(aq->FieldByName("stgid")->AsAnsiString + "店" + aq->FieldByName("name")->AsAnsiString,(TObject*)aq->FieldByName("id")->AsInteger);
		aq->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::cbuserChange(TObject *Sender)
{
	if (cbuser->Text != "") {
		chuser->Checked = true;
	}
	else
	{
    	chuser->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::DBGrid2TitleClick(TColumn *Column)
{
	if (query->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (query->Sort == "") {
		query->Sort =  Column->FieldName + " ASC";
	}
	else if (query->Sort == qusort) {
		query->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		query->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::editclientChange(TObject *Sender)
{
  if (editclient->Text!="") {
	 cbclient->Checked=true;
  }else cbclient->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouorderselect::editordernumChange(TObject *Sender)
{
   if (editordernum->Text!="") {
	 cbordernum->Checked=true;
  }else cbordernum->Checked=false;
}
//---------------------------------------------------------------------------

