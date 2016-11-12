//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bookup.h"
#include "hoistoryview.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma resource "*.dfm"
Tfrmbookup *frmbookup;
//---------------------------------------------------------------------------
__fastcall Tfrmbookup::Tfrmbookup(TComponent* Owner,int Type,TADOConnection *con)
	: TForm(Owner)
{
	fcon = con;
	type = Type;
	qusupplier->Connection = con;
	aqsum->Connection = con;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	String sql;
	sql  = "select ID,Name from CUST_CustomerInfo where Type = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof ) {
		cbsupplier->AddItem(aq->FieldByName("ID")->AsString + aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger);
		aq->Next();
	}
	sql = "select ID,PresentNum,AbbreviatedName from BS_PressInfo ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof ) {
		cbpress->AddItem(aq->FieldByName("PresentNum")->AsString + aq->FieldByName("AbbreviatedName")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger);
		aq->Next();
	}
	delete aq;
	spsupplier->Connection = con;
	dtstart->Date = Date();
	dtend->Date = Date();
	dtpbegin->Date = Date();
	dtpend->Date = Date();
	Dupsupplier = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbookup::BtnViewClick(TObject *Sender)
{
	String sql;
	sql = "select CUST_CustomerInfo.ID,CUST_CustomerInfo.name from CUST_CustomerInfo "
		  "left join STK_BookInfo on CUST_CustomerInfo.id = STK_BookInfo.SupplierID "
		  "left join BS_BookCatalog on BS_BookCatalog.id = STK_BookInfo.BkcatalogID "
		  "left join BS_PressInfo on BS_PressInfo.id = BS_BookCatalog.PressID "
		  "left join BS_RetailNote on BS_RetailNote.BkInfoID = STK_BookInfo.id "
		  "left join BS_RetailNoteHeader on BS_RetailNoteHeader.id = BS_RetailNote.RetailNtHeaderID  where CUST_CustomerInfo.Type =1 ";
	if (chsupplier->Checked ) {
		try {
			sql = sql + " and CUST_CustomerInfo.id = " + IntToStr((int)cbsupplier->Items->Objects[cbsupplier->ItemIndex]);
		} catch (...) {
			MessageBox(0,"请选择正确的供应商！","错误确认" ,MB_OK);
			return;
		}
	}
	if (chpress->Checked ) {
		try {
			sql = sql + " and BS_PressInfo.id =" + IntToStr((int)cbpress->Items->Objects[cbpress->ItemIndex]) ;
		} catch (...) {
			MessageBox(0,"请选择正确的出版社！","错误确认" ,MB_OK);
			return;
		}
	}
	if (cbstart->Checked ) {
		sql = sql + " and datediff(d,BS_RetailNoteHeader.HdTime,'"+DateToStr(dtstart->Date)+"')<=0";
	}
	if (cbend->Checked ) {
		sql = sql + " and datediff(d,BS_RetailNoteHeader.HdTime,'"+DateToStr(dtend->Date)+"')>=0";
	}
	if (cbmax->Checked ) {
		if (edmax->Text == "") {
			edmax->Text = "0";
		}
		sql = sql + " and STK_BookInfo.Amount <= " + edmax->Text ;
	}
	if (cbmin->Checked ) {
		if (edmin->Text == "") {
        	edmin->Text = "0";
		}
		sql = sql + " and STK_BookInfo.Amount >= " + edmin->Text ;
	}
	sql = sql + " group by CUST_CustomerInfo.ID,CUST_CustomerInfo.name ";
	qusupplier->Close();
	qusupplier->SQL->Clear();
	qusupplier->SQL->Add(sql);
	qusupplier->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbookup::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookup::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbookup::BtnExportClick(TObject *Sender)
{
	if (qudetail->IsEmpty() ) {
        return;
	}
	if (qudetail->Active && qudetail->RecordCount > 0) {
    	DbgridToExcel(dgdetail);
	}
}
//---------------------------------------------------------------------------
//Excel导出函数
bool __fastcall Tfrmbookup::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString temptext ,ExcelFileName;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		MessageBox(0,"没有数据！","错误确认" ,MB_OK);
		return false;
	}
	Variant     v,vSheet,Wb;
	temptext = qusupplier->FieldByName("Name")->AsString ;
	filepath->FileName =  temptext;
	if (filepath->Execute())
	{
		ExcelFileName = ExtractFilePath(filepath->FileName.c_str()) + temptext +".xls";
	}
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",false);
	v.OlePropertyGet("WorkBooks").OleFunction("Add",1);
	//v.OlePropertyGet("WorkBooks").OleFunction("Add");
	Wb = v.OlePropertyGet("ActiveWorkBook");
	vSheet = Wb.OlePropertyGet("ActiveSheet");
	vSheet.OlePropertySet("name",temptext .c_str());

//  在Excel中成字符串显示
	temptext = "'补书上架";
	v.OlePropertyGet("Cells",1,5).OlePropertySet("Value",temptext .c_str() );
	temptext = "'"+ qusupplier->FieldByName("Name")->AsString ;
	v.OlePropertyGet("Cells",2,5).OlePropertySet("Value",temptext .c_str() );
	n=3;

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
	int h1 = 2+n;
	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
				else
				{
                	t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}

			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}
	int h2 = t2+1+n;
	v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","合计");
	temptext = "=SUM(D" + IntToStr(h1) + ":D" + IntToStr(h2) + ")";
	v.OlePropertyGet("Cells",t2+2+n,4).OlePropertySet("Value",temptext .c_str() );
	temptext = "=SUM(E" + IntToStr(h1) + ":E" + IntToStr(h2) + ")";
	v.OlePropertyGet("Cells",t2+2+n,5).OlePropertySet("Value",temptext .c_str() );
	temptext = "=SUM(G" + IntToStr(h1) + ":G" + IntToStr(h2) + ")";
	v.OlePropertyGet("Cells",t2+2+n,7).OlePropertySet("Value",temptext .c_str() );
	temptext = "=SUM(H" + IntToStr(h1) + ":H" + IntToStr(h2) + ")";
	v.OlePropertyGet("Cells",t2+2+n,8).OlePropertySet("Value",temptext .c_str() );
	temptext = "=SUM(I" + IntToStr(h1) + ":I" + IntToStr(h2) + ")";
	v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );
	temptext = "=SUM(J" + IntToStr(h1) + ":J" + IntToStr(h2) + ")";
	v.OlePropertyGet("Cells",t2+2+n,10).OlePropertySet("Value",temptext .c_str() );
	temptext = "=SUM(K" + IntToStr(h1) + ":K" + IntToStr(h2) + ")";
	v.OlePropertyGet("Cells",t2+2+n,11).OlePropertySet("Value",temptext .c_str() );
	temptext = "=SUM(L" + IntToStr(h1) + ":L" + IntToStr(h2) + ")";
	v.OlePropertyGet("Cells",t2+2+n,12).OlePropertySet("Value",temptext .c_str() );

	try {
		Wb.OleProcedure("SaveAs",ExcelFileName.c_str() );//保存表格
	} catch (...) {
	}
	Wb.OleProcedure("Close");//关闭表格
	v.OleFunction("Quit");//退出Excel
	return false;
}

//---------------------------------------------------------------------------

void __fastcall Tfrmbookup::CheckBox1Click(TObject *Sender)
{
	if (CheckBox1->Checked ) {
		dgdetail->Columns->Items[10]->Visible = true;
		dgdetail->Columns->Items[11]->Visible = true;
		dgdetail->Columns->Items[6]->Visible = true;
		dgdetail->Columns->Items[7]->Visible = true;
		dgdetail->Columns->Items[8]->Visible = true;
		dgdetail->Columns->Items[9]->Visible = true;
	}
	else
	{
		dgdetail->Columns->Items[10]->Visible = false;
		dgdetail->Columns->Items[11]->Visible = false;
		dgdetail->Columns->Items[6]->Visible = false;
		dgdetail->Columns->Items[7]->Visible = false;
		dgdetail->Columns->Items[8]->Visible = false;
		dgdetail->Columns->Items[9]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookup::FormCreate(TObject *Sender)
{
   if (type == 2) {
	   dgdetail->PopupMenu  = pm ;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookup::N1Click(TObject *Sender)
{
								
	for (int i = 1; i <= dgdetail->DataSource->DataSet->RecordCount ; i++) {
		dgdetail->DataSource->DataSet->RecNo = i;
		dgdetail->SelectedRows ->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookup::N2Click(TObject *Sender)
{
  //转入采购
  int ramount,wamount;
  float discount;
  ramount = 0;
  wamount= 0;
  if (qudetail->IsEmpty() ) {
	return; 
  }
   for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
		qudetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
		pro->AddNote(supplierid,qudetail->FieldByName("id")->AsInteger);

		if (qudetail->FieldByName("Ramount")->AsAnsiString == "" ) {
		  ramount = 0;
			
		}else
		{
		  ramount =  ramount + qudetail->FieldByName("Ramount")->AsInteger ;

		}
		if (qudetail->FieldByName("Wamount")->AsAnsiString == "") {
			wamount = 0;
		}else
		{
			wamount = wamount + qudetail->FieldByName("Wamount")->AsInteger ;
		}
	
		if (qudetail->FieldByName("Discount")->AsFloat == 0) {
		  discount = 100;	
		}
		else
		{
		  discount = qudetail->FieldByName("Discount")->AsFloat ;

		}
		pro->dsetNote->Edit();
		pro->dsetNote->FieldByName("Amount")->AsInteger =  ramount + wamount;
		pro->UpdateNote();
		pro->dsetNote->Edit();
		pro->dsetNote->FieldByName("Discount")->AsFloat   =  discount  ; 
		pro->UpdateNote(); 
		Dupsupplier = true; 
   }

	
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookup::dgdetailTitleClick(TColumn *Column)
{
	if (qudetail->RecordCount > 0) {
    	AnsiString qusort;
		qusort =  Column->FieldName + " ASC";
		if (qudetail->Sort == "") {
			qudetail->Sort =  Column->FieldName + " ASC";
		}
		else if (qudetail->Sort == qusort) {
			qudetail->Sort =  Column->FieldName + " DESC";
		}
		else
		{
			qudetail->Sort =  Column->FieldName + " ASC";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookup::N4Click(TObject *Sender)
{
	if (qudetail->RecordCount > 0) {
    	Tfrmhistoryview *frm = new Tfrmhistoryview(Application,fcon,qudetail->FieldByName("id")->AsInteger );
		frm->ShowModal();
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmbookup::btsearchClick(TObject *Sender)
{
	if (qusupplier->IsEmpty() ) {
        return;
	}
	supplierid =  qusupplier->FieldByName("ID")->AsInteger;
	if (qusupplier->Active && qusupplier->RecordCount > 0) {
			spsupplier->Active = false;
			spsupplier->Parameters->ParamByName("@supplierid")->Value = qusupplier->FieldByName("ID")->AsInteger ;
			if (chbegin->Checked ) {
				spsupplier->Parameters->ParamByName("@starttime")->Value = DateToStr(dtpbegin->Date) + " 0:00:00";
			}
			else
			{
				spsupplier->Parameters->ParamByName("@starttime")->Value = "2009-01-01 0:00:00";
			}
			if (chend->Checked ) {
				spsupplier->Parameters->ParamByName("@endtime")->Value = DateToStr(dtpend->Date) + " 0:00:00";
			}
			else
			{
				spsupplier->Parameters->ParamByName("@endtime")->Value = "2200-01-01 0:00:00";
			}
			spsupplier->Parameters->ParamByName("@stgid")->Value = stgid;
			spsupplier->Active = true;
			dsdetail->DataSet = NULL;
			qudetail->Recordset = spsupplier->Recordset ;
			dsdetail->DataSet =  qudetail;
			int count = 0;
			dssum->DataSet = NULL;
			aqsum->Recordset = spsupplier->NextRecordset(count)  ;
			dssum->DataSet =  aqsum;
		}
	/*if (type == 2) {
	  if (supplierid != qusupplier->FieldByName("id")->AsInteger && !Dupsupplier)
	   {

			pro->dsetVendor->Last();
			pro->dsetNtHeader->Edit();
			pro->dsetNtHeader->FieldByName("VendorID")->AsInteger = qusupplier->FieldByName("ID")->AsInteger  ;
			pro->UpdateNtHeader();
			supplierid = qusupplier->FieldByName("ID")->AsInteger;
	   }
	} */
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookup::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookup::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F6) {
		BtnExport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		BtnView->Click();
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

