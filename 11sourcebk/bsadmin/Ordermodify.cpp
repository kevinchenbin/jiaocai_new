//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Ordermodify.h"
#include "Orderdetail.h"
#include "UnitSelectClient.h"
#include "UnitClientyouxianji.h"
#include "NoteCode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
Tfrmordermodify *frmordermodify;
//---------------------------------------------------------------------------
__fastcall Tfrmordermodify::Tfrmordermodify(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
	dtpdate->Date = Date();
	con = cn;
	aq1->Connection = cn;
	aq2->Connection = cn;
	fstgid = stgid;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = cn;
	AnsiString sql;
	sql = "select ID,Name from sys_user where stgid = " + IntToStr(stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbuser->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
	dtedtDate->Date = Date();
    chordercode->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmordermodify::BtnViewClick(TObject *Sender)
{
	AnsiString sql;
	sql = "select  rank() over(order by A.id) as xuhao, A.*,B.Name,dbo.UF_BS_GetClientName(A.VendorID) as clientname, convert(nvarchar(10),HdTime,20) as ordertime,case when A.shenheistate = 0 then '未审核' else '已审核' end as state1 from BS_OrderNoteHeader A left join sys_user B on A.OperatorID = B.id  where A.StgID = " + IntToStr(fstgid) + " and A.state in (0,1) ";

   		if (chordercode->Checked && edordercode->Text != "") {
			sql = sql + " and A.OrderNtCode = " + edordercode->Text ;
		}
		if (chbk->Checked ) {
			sql = sql + " and A.Remarks = " + edbk->Text ;
		}
		if (chclient->Checked && edtclient->Text != "" ) {
			sql = sql + " and A.VendorID = " + IntToStr(ClientID);
		}
		if (cbuser->Text != "") {
			int userid;
			try {
				userid =  (int)cbuser->Items->Objects[cbuser->ItemIndex];
			} catch (...) {
				MessageBoxA(0,"请选择正确的操作员！","提示",MB_ICONASTERISK);
				return;
			}
			sql = sql + " and A.OperatorID = " + IntToStr(userid);
		}
		if (chdate->Checked ) {
			sql = sql + " and datediff(day,'"+DateToStr(dtpdate->Date) +"',A.HdTime) = 0" ;
		}
		if (RadioGroup1->ItemIndex == 1) {
			sql = sql + " and A.shenheistate = 1";
		}
		if (RadioGroup1->ItemIndex == 2) {
			sql = sql + " and A.shenheistate = 0";
		}

	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	aq2->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmordermodify::edclientKeyPress(TObject *Sender, wchar_t &Key)

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
void Tfrmordermodify::ClientView()
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
void __fastcall Tfrmordermodify::DBGrid1CellClick(TColumn *Column)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	AnsiString sql;
	sql = "select A.*,B.ISBN,B.Name as bookname,B.Author,B.price,B.PressCount,C.AbbreviatedName,Order_lock.usableamount,case when BS_OrderNoteHeader.shenheistate = 0 then '未审核' else '已审核' end as state1 from BS_OrderNote A left join "
			" BS_BookCatalog B ON A.BkcatalogID = B.id left join "
			" BS_OrderNoteHeader on A.OrderNtHeaderID = BS_OrderNoteHeader.id left join "
			" BS_PressInfo C ON B.PressID = C.id left join "
			" Order_lock "
			" ON A.BkcatalogID = Order_lock.BkcatalogID where A.OrderNtHeaderID = " + aq1->FieldByName("ID")->AsString + " and A.state = 0";
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();
	if (aq1->FieldByName("state1")->AsAnsiString == "已审核" ) {
		DBGrid2->Columns->Items[5]->ReadOnly = true;
		DBGrid2->Columns->Items[6]->ReadOnly = true;
		BtnOK->Enabled = false;
		BtnCancel->Enabled = true;
	}
	else
	{
		DBGrid2->Columns->Items[5]->ReadOnly = false;
		DBGrid2->Columns->Items[6]->ReadOnly = false;
		BtnOK->Enabled = true;
		BtnCancel->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmordermodify::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordermodify::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmordermodify::DBGrid2DblClick(TObject *Sender)
{
	if (aq2->IsEmpty() ) {
		return;
	}
	TfrmOrderdetail *frm = new TfrmOrderdetail(Application,con,aq2->FieldByName("BkcatalogID")->AsInteger ,fstgid );
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordermodify::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordermodify::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {   //查单
		BtnView->Click();
	}
	if (Key == VK_F5) {   //审核
		BtnOK->Click();
	}
	if (Key == VK_F6) {   //反审核
		BtnCancel->Click();
	}
	if (Key == VK_F7) {   //按单导出
		BtnExport->Click();
	}
	if (Key == VK_F8) {   //按客户导出
		BtnExport1->Click();
	}
	if (Key == VK_F9) {   //设置客户优先级
		BtnAlignNone->Click();
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

void __fastcall Tfrmordermodify::BtnOKClick(TObject *Sender)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	AnsiString sql = "exec USP_BS_Order_shenhei 0," + aq1->FieldByName("ID")->AsString  ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	aq1->Active = false;
	aq1->Active = true;
	if (!aq2->IsEmpty() ) {
		aq2->Active = false;
		aq2->Active = true;
	}
	DBGrid2->Columns->Items[5]->ReadOnly = true;
	DBGrid2->Columns->Items[6]->ReadOnly = true;
	BtnOK->Enabled = false;
	BtnCancel->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordermodify::BtnCancelClick(TObject *Sender)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	AnsiString sql = "exec USP_BS_Order_shenhei 1," + aq1->FieldByName("ID")->AsString  ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	aq1->Active = false;
	aq1->Active = true;
	if (!aq2->IsEmpty() ) {
		aq2->Active = false;
		aq2->Active = true;
	}
	DBGrid2->Columns->Items[5]->ReadOnly = false;
	DBGrid2->Columns->Items[6]->ReadOnly = false;
	BtnOK->Enabled = true;
	BtnCancel->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordermodify::spselectClientClick(TObject *Sender)
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

void __fastcall Tfrmordermodify::BtnExportClick(TObject *Sender)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	if (aq1->Active && aq1->RecordCount > 0) {
		DbgridToExcel();
	}
}
//---------------------------------------------------------------------------

void Tfrmordermodify::DbgridToExcel()
{
	AnsiString temptext ,ExcelFileName,FileName;
	int k = 0 ,n=0;
	//Variant     v,vSheet,Wb;
	aq1->First();
	temptext = aq1->FieldByName("OrderNtCode")->AsString ;
	filepath->FileName =  temptext;
	if (!filepath->Execute())
	{
    	return;
	}
	ExcelFileName = ExtractFilePath(filepath->FileName.c_str());
	aq1->DisableControls();
	aq2->DisableControls();
	while (!aq1->Eof)
	{
		AnsiString sql;
		/*sql = "select A.*,B.ISBN,B.Name as bookname,B.price,B.PressCount,C.AbbreviatedName,D.useamount,case when BS_OrderNoteHeader.shenheistate = 0 then '未审核' else '已审核' end as state1 from BS_OrderNote A left join "
			" BS_BookCatalog B ON A.BkcatalogID = B.id left join "
			" BS_OrderNoteHeader on A.OrderNtHeaderID = BS_OrderNoteHeader.id left join "
			" BS_PressInfo C ON B.PressID = C.id left join "
			" (SELECT B.BkcatalogID,(A.Amount-B.Amount) as useamount from "
			" (select sum(localnum) as Amount,BkcatalogID from BS_OrderNoteHeader left join "
			" BS_OrderNote A ON BS_OrderNoteHeader.ID = A.OrderNtHeaderID where BS_OrderNoteHeader.state IN(0,1) group by BkcatalogID) as B "
			" left join "
			" (select sum(STK_BookInfo.Amount) as Amount,STK_BookInfo.BkcatalogID from STK_BookInfo group by BkcatalogID) as A "
			" on A.BkcatalogID = B.BkcatalogID) as D "
			" ON A.BkcatalogID = D.BkcatalogID where A.OrderNtHeaderID = " + aq1->FieldByName("ID")->AsString + " and A.state = 0";
		*/
		sql = "select A.*,B.ISBN,replace(B.Name,',','.') as bookname,B.Author,B.price,B.PressCount,C.AbbreviatedName,Order_lock.usableamount,case when BS_OrderNoteHeader.shenheistate = 0 then '未审核' else '已审核' end as state1 from BS_OrderNote A left join "
			" BS_BookCatalog B ON A.BkcatalogID = B.id left join "
			" BS_OrderNoteHeader on A.OrderNtHeaderID = BS_OrderNoteHeader.id left join "
			" BS_PressInfo C ON B.PressID = C.id left join "
			" Order_lock "
			" ON A.BkcatalogID = Order_lock.BkcatalogID where A.OrderNtHeaderID = " + aq1->FieldByName("ID")->AsString + " and A.state = 0";

		if (N2->Checked) {
			sql = sql + " and (Order_lock.usableamount > 0 or A.localnum > 0)";
		}
		aq2->Close();
		aq2->SQL->Clear();
		aq2->SQL->Add(sql);
		aq2->Open();
		if (aq2->RecordCount > 0) {
			temptext = aq1->FieldByName("OrderNtCode")->AsString ;
			FileName = ExcelFileName + temptext + ".csv";
			/*Variant     v,vSheet,Wb;
			v   =Variant::CreateObject("Excel.Application");
			v.OlePropertySet("Visible",false);
			v.OlePropertyGet("WorkBooks").OleFunction("Add",1);
			Wb = v.OlePropertyGet("ActiveWorkBook");
			vSheet = Wb.OlePropertyGet("ActiveSheet");
			vSheet.OlePropertySet("name",temptext .c_str());*/

			int  iFileHandle;
			int   iFileLength;
			if(FileExists(FileName))
			   //iFileHandle = FileOpen(FileName.c_str() ,fmOpenReadWrite);
			   if (DeleteFileA(FileName))
					iFileHandle = FileCreate(FileName.c_str());
			   else
					return;
			else
				iFileHandle = FileCreate(FileName.c_str());

			n=1;

			int t1= 0;
			temptext = "";
			for(int q=0;q<DBGrid2->FieldCount ;++q)
			{
				t1++;
				//temptext = "'"+ DBGrid2->Columns ->Items [q]->Title ->Caption;
				//v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
				temptext = temptext + DBGrid2->Columns ->Items [q]->Title ->Caption + ",";
			}
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

			int t2 = aq2->RecordCount ;
			int h1 = 2+n;

			aq2->First();
			for(int   i=2+n;i<=t2+1+n ;i++)
			{
				t1=0;
				temptext = "\n";
				for(int j=1;j<DBGrid2->Columns ->Count+1;j++)
				{
					if (DBGrid2->Columns ->Items [j-1]->FieldName == "ISBN") {
						t1++;
						//temptext = "'"+ aq2->FieldByName(DBGrid2->Columns ->Items [j-1]->FieldName )->AsAnsiString;
						//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
						temptext = temptext + "'" + aq2->FieldByName(DBGrid2->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
					else {
						t1++;
						//temptext = aq2->FieldByName(DBGrid2->Columns ->Items [j-1]->FieldName )->AsAnsiString;
						//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
						temptext = temptext + aq2->FieldByName(DBGrid2->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
				}
                iFileLength   =   FileSeek(iFileHandle,0,2);
				FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
				aq2->Next();
			}

			/*int h2 = t2+1+n;
			v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","合计");
			temptext = "=SUM(F" + IntToStr(h1) + ":F" + IntToStr(h2) + ")";
			v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value",temptext .c_str() );
			temptext = "=SUM(H" + IntToStr(h1) + ":H" + IntToStr(h2) + ")";
			v.OlePropertyGet("Cells",t2+2+n,8).OlePropertySet("Value",temptext .c_str() );
			temptext = "=SUM(I" + IntToStr(h1) + ":I" + IntToStr(h2) + ")";
			v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );
			temptext = "=SUM(J" + IntToStr(h1) + ":J" + IntToStr(h2) + ")";
			v.OlePropertyGet("Cells",t2+2+n,10).OlePropertySet("Value",temptext .c_str() );
			temptext = "=SUM(K" + IntToStr(h1) + ":K" + IntToStr(h2) + ")";
			v.OlePropertyGet("Cells",t2+2+n,11).OlePropertySet("Value",temptext .c_str() );


			try {
				Wb.OleProcedure("SaveAs",FileName.c_str() );//保存表格
			} catch (...) {
			}
			Wb.OleProcedure("Close");//关闭表格
			v.OleFunction("Quit");//退出Excel   */
			FileClose(iFileHandle);
		}
		aq1->Next();
	}
	aq2->EnableControls();
	aq1->EnableControls();
	MessageBoxA(0,"导出成功,请在指定的目录下注意查看！","提示",MB_ICONASTERISK);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordermodify::BtnExport1Click(TObject *Sender)
{
	if (aq1->IsEmpty() ) {
        return;
	}
	AnsiString headid;
	aq1->DisableControls();
	aq1->First();
	while (!aq1->Eof )
	{
		if (headid == "") {
			headid = aq1->FieldByName("id")->AsString ;
		}
		else
		{
			headid = headid + "," + aq1->FieldByName("id")->AsString ;
		}
		aq1->Next();
	}
	aq1->EnableControls();
	DbgridToExcel(headid);
}
//---------------------------------------------------------------------------
void Tfrmordermodify::DbgridToExcel(AnsiString headerid)
{
	AnsiString temptext ,ExcelFileName,FileName,sql;
	int k = 0 ,n=0;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	sql = "select distinct A.ID,A.Name from BS_OrderNoteHeader  left join CUST_CustomerInfo  A ON BS_OrderNoteHeader.VendorID = A.ID where BS_OrderNoteHeader.id in (" +  headerid + ")";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	aq->First();
	temptext = aq->FieldByName("Name")->AsString ;
	filepath->FileName =  temptext;
	if (!filepath->Execute())
	{
    	return;
	}
	ExcelFileName = ExtractFilePath(filepath->FileName.c_str());
	aq2->DisableControls();
	while (!aq->Eof)
	{
        AnsiString sql;
        /*sql = "select A.*,B.ISBN,B.Name as bookname,B.price,B.PressCount,C.AbbreviatedName,D.useamount,case when BS_OrderNoteHeader.shenheistate = 0 then '未审核' else '已审核' end as state1 from BS_OrderNote A left join "
			" BS_BookCatalog B ON A.BkcatalogID = B.id left join "
			" BS_OrderNoteHeader on A.OrderNtHeaderID = BS_OrderNoteHeader.id left join "
			" BS_PressInfo C ON B.PressID = C.id left join "
			" (SELECT B.BkcatalogID,(A.Amount-B.Amount) as useamount from "
			" (select sum(localnum) as Amount,BkcatalogID from BS_OrderNoteHeader left join "
			" BS_OrderNote A ON BS_OrderNoteHeader.ID = A.OrderNtHeaderID where BS_OrderNoteHeader.state IN(0,1) group by BkcatalogID) as B "
			" left join "
			" (select sum(STK_BookInfo.Amount) as Amount,STK_BookInfo.BkcatalogID from STK_BookInfo group by BkcatalogID) as A "
			" on A.BkcatalogID = B.BkcatalogID) as D "
			" ON A.BkcatalogID = D.BkcatalogID where A.OrderNtHeaderID in (" + headerid + ") and BS_OrderNoteHeader.VendorID = " + aq->FieldByName("ID")->AsString + " and A.state = 0 ";
		if (N2->Checked) {
			sql = sql + " and D.useamount > 0";
		}*/

        sql = "select A.*,B.ISBN,replace(B.Name,',','.') as bookname,B.Author,B.price,B.PressCount,C.AbbreviatedName,Order_lock.usableamount,case when BS_OrderNoteHeader.shenheistate = 0 then '未审核' else '已审核' end as state1 from BS_OrderNote A left join "
			" BS_BookCatalog B ON A.BkcatalogID = B.id left join "
			" BS_OrderNoteHeader on A.OrderNtHeaderID = BS_OrderNoteHeader.id left join "
			" BS_PressInfo C ON B.PressID = C.id left join "
			" Order_lock "
			" ON A.BkcatalogID = Order_lock.BkcatalogID where A.OrderNtHeaderID in (" + headerid + ") and BS_OrderNoteHeader.VendorID = " + aq->FieldByName("ID")->AsString + " and A.state = 0 ";

		if (N2->Checked) {
			sql = sql + " and (Order_lock.usableamount > 0 or A.localnum > 0)";
		}

		aq2->Close();
		aq2->SQL->Clear();
		aq2->SQL->Add(sql);
		aq2->Open();
		if (aq2->RecordCount > 0) {
			temptext = aq->FieldByName("Name")->AsString ;
			FileName = ExcelFileName + temptext + ".csv";
			/*Variant     v,vSheet,Wb;
			v   =Variant::CreateObject("Excel.Application");
			v.OlePropertySet("Visible",false);
			v.OlePropertyGet("WorkBooks").OleFunction("Add",1);
			Wb = v.OlePropertyGet("ActiveWorkBook");
			vSheet = Wb.OlePropertyGet("ActiveSheet");
			vSheet.OlePropertySet("name",temptext .c_str()); */

            int  iFileHandle;
			int   iFileLength;
			if(FileExists(FileName))
			   //iFileHandle = FileOpen(FileName.c_str() ,fmOpenReadWrite);
			   if (DeleteFileA(FileName))
					iFileHandle = FileCreate(FileName.c_str());
			   else
					return;
			else
				iFileHandle = FileCreate(FileName.c_str());

			n=1;

			int t1= 0;
			temptext = "";
			for(int q=0;q<DBGrid2->FieldCount ;++q)
			{
				t1++;
				//temptext = "'"+ DBGrid2->Columns ->Items [q]->Title ->Caption;
				//v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
				temptext = temptext + DBGrid2->Columns ->Items [q]->Title ->Caption + ",";
			}

			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

			int t2 = aq2->RecordCount ;
			int h1 = 2+n;
			aq2->First();
			for(int   i=2+n;i<=t2+1+n ;i++)
			{
				t1=0;
				temptext = "\n";
				for(int j=1;j<DBGrid2->Columns ->Count+1  ;j++)
				{
					if (DBGrid2->Columns ->Items [j-1]->FieldName == "ISBN") {
						t1++;
						//temptext = "'"+ aq2->FieldByName(DBGrid2->Columns ->Items [j-1]->FieldName )->AsAnsiString;
						//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
						temptext = temptext + "'"+ aq2->FieldByName(DBGrid2->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
					else
					{
						t1++;
						//temptext = aq2->FieldByName(DBGrid2->Columns ->Items [j-1]->FieldName )->AsAnsiString;
						//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
						temptext = temptext + aq2->FieldByName(DBGrid2->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
				}
				iFileLength   =   FileSeek(iFileHandle,0,2);
				FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
				aq2->Next();
			}

			/*int h2 = t2+1+n;
			v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","合计");
			temptext = "=SUM(F" + IntToStr(h1) + ":F" + IntToStr(h2) + ")";
			v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value",temptext .c_str() );
			temptext = "=SUM(H" + IntToStr(h1) + ":H" + IntToStr(h2) + ")";
			v.OlePropertyGet("Cells",t2+2+n,8).OlePropertySet("Value",temptext .c_str() );
			temptext = "=SUM(I" + IntToStr(h1) + ":I" + IntToStr(h2) + ")";
			v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );
			temptext = "=SUM(J" + IntToStr(h1) + ":J" + IntToStr(h2) + ")";
			v.OlePropertyGet("Cells",t2+2+n,10).OlePropertySet("Value",temptext .c_str() );
			temptext = "=SUM(K" + IntToStr(h1) + ":K" + IntToStr(h2) + ")";
			v.OlePropertyGet("Cells",t2+2+n,11).OlePropertySet("Value",temptext .c_str() );

			try {
				Wb.OleProcedure("SaveAs",FileName.c_str() );//保存表格
			} catch (...) {
			}
			Wb.OleProcedure("Close");//关闭表格
			v.OleFunction("Quit");//退出Excel */
			FileClose(iFileHandle);

		}
		aq->Next();
	}
	aq2->EnableControls();
	delete aq;
	MessageBoxA(0,"导出成功，请在指定的目录下注意查看！","提示",MB_ICONASTERISK);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordermodify::BtnAlignNoneClick(TObject *Sender)
{
	TfrmClientyouxianji *frm = new TfrmClientyouxianji(Application,con,fstgid);
	frm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordermodify::edbkChange(TObject *Sender)
{
	if (edbk->Text != "") {
		chbk->Checked = true;
	}
	else
	{
    	chbk->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordermodify::edtclientChange(TObject *Sender)
{
	if (edtclient->Text != "") {
		chclient->Checked = true;
	}
	else
	{
    	chclient->Checked = false;
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmordermodify::edordercodeChange(TObject *Sender)
{
	chordercode->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordermodify::dtpdateChange(TObject *Sender)
{
	chdate->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordermodify::dtedtDateChange(TObject *Sender)
{
	NoteCode nc(dtedtDate->Date, fstgid, spedtID->IntValue);
	edordercode->Text = nc.AsString();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordermodify::spedtIDChange(TObject *Sender)
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

