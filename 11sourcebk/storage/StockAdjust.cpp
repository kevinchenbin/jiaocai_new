//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StockAdjust.h"
#include "SelectCatalogForm.h"
#include "QryNoteCodeForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzLabel"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmStockAdjust *frmStockAdjust;
//---------------------------------------------------------------------------
__fastcall TfrmStockAdjust::TfrmStockAdjust(TComponent* Owner)
	: TForm(Owner)
{
   m_catalogSearchMode = 1;
   dtpdate->Date = Now();
}
void TfrmStockAdjust::init(LandInfo *li)
{
   	fcon  = li->con ;
	aq->Connection = fcon;
	UserID = li->userID ;
	Stgid = li->storageID ;
	editusername->Text = li->UserName ;
	BtnNew->Click();
	aqdetail->Connection = fcon;
	aqhead->Connection = fcon;
	aqhead->Active = true;

	AnsiString sql;
	sql = "select ID,Name from SYS_StorageInfo where id = " + IntToStr(Stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	Edit1->Text = aq->FieldByName("ID")->AsString;
	Edit2->Text = aq->FieldByName("Name")->AsString ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStockAdjust::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		PM->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::N1Click(TObject *Sender)
{
	lblCatalog->Caption = "书 号";
	m_catalogSearchMode=1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码";
	m_catalogSearchMode=2;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名";
	m_catalogSearchMode=3;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::N6Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode=6;
}
//---------------------------------------------------------------------------
void TfrmStockAdjust::ExecSQL(AnsiString sql)
{
	TADOQuery *aq = new TADOQuery(Application);
	aq->Connection = fcon ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}
void __fastcall TfrmStockAdjust::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\'') {
		Key = NULL;
	}
	if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
			Key = NULL;
		}
	}
   if (Key == VK_RETURN)
	{
			if (edtCatalog->Text == "") {
            	return;
			}
			if (m_catalogSearchMode==6) {
					  FLOAT price;
					  try
					  {
						price = StrToFloat(edtCatalog->Text);
					   }
					   catch(...)
					   {
						  MessageBox(0,"请输入正确的价格！","提示",MB_ICONWARNING);
						  return ;
					   }

					}

			TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,fcon);
					LandInfo li;
					li.app = Application;
					li.con = fcon;
					li.userID = UserID;
					li.storageID = Stgid;
					frm->Init(&li);
					frm->DoModalType = 9;
					frm->StockAdjust  = this;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					if (mrOk == frm->ShowModal())
					{
						if (frm->SelectAll) {
							 for (int i = 0; i < frm->lengthint  ; i++) {
								AddNote(frm->SupplierID[i],frm->BkcatalogiD[i],frm->stkbkid[i],frm->skAmount[i]);
							 }
						}else
						{
						   frm->GetSelectResult(supplierID, catalogID);
						   AddNote(supplierID,catalogID,frm->BKinfoid,frm->Amount);
						   editadjust->SetFocus();
						}
					}

                  	delete frm;
					edtCatalog->Text = "";
	}
}
void TfrmStockAdjust::AddNote(int supplierID,int CatalogId,int bkinfoid,int amount)
{
    TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	Variant   locvalues[2];
	locvalues[0]   =   Variant(IntToStr(supplierID));
	locvalues[1]   =   Variant(IntToStr(CatalogId));
	if ( !aqdetail->Locate("SupplierID;bkcatalogID",VarArrayOf(locvalues,1),Opts))
	{
    	String sql;
		sql = "exec USP_BS_StockAdjustAddNote ";
		sql = sql +editnum->Text + "," + IntToStr(supplierID) + "," + IntToStr(CatalogId) + "," + IntToStr(bkinfoid) + "," + IntToStr(amount) ;
		ExecSQL(sql);
		aqdetail->Active = false;
		aqdetail->Active = true;
		aqdetail->Last();
		editamount->Text = IntToStr(amount) ;
	}
	else
	{
		dg->SelectedRows->CurrentRowSelected = true;
		dg->SetFocus();
	}
}
void TfrmStockAdjust::RefreshDetail()
{

	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	Variant   locvalues[2];
	if (!aqdetail->IsEmpty() ) {
    	locvalues[0]   =   aqdetail->FieldByName("SupplierID")->AsAnsiString ;
		locvalues[1]   =   aqdetail->FieldByName("bkcatalogID")->AsAnsiString ;
	}


	aqdetail->Active = false;
	aqdetail->Connection = fcon;
	aqdetail->Parameters->ParamByName("num")->Value = editnum->Text ;
	aqdetail->Active = true;
	aqdetail->Locate("SupplierID;bkcatalogID",VarArrayOf(locvalues,1),Opts);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::BtnNewClick(TObject *Sender)
{
   Deletenote();
   DBN->Enabled = false;
   String danhao ;
   String sql;
   sql = "select dbo.UF_BSI_StockAdjust(0,getdate()) as Danhao ";
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   danhao = aq->FieldByName("danhao")->AsAnsiString ;
   sql = "insert into STK_AdjustHeader (adjustheaderid,AdjustDate,Stgid,Adjustemployee) values('" + danhao + "',getdate()," + IntToStr(Stgid) + ",'" + editusername->Text + "')";
   ExecSQL(sql);
   editnum->Text = danhao;
   dtpdate->Date = Date();
   edtCatalog->Text = "";
   editadjust->Text = "";
   edsamount->Text = "";
   editamount->Text = "";
   BtnNew->Enabled = false;
   BtnOK->Enabled = true;
   RefreshDetail();
   edstate->Text = "未确认库存";
   BtnDelete->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::dgCellClick(TColumn *Column)
{
   if (aqdetail->IsEmpty()) {
	  return;
   }

   editamount->Text = aqdetail->FieldByName("Amount")->AsAnsiString ;
   edsamount->Text = aqdetail->FieldByName("damagenum")->AsAnsiString;
   editadjust->Text = aqdetail->FieldByName("adjustAmount")->AsAnsiString;
   edbak->Text = aqdetail->FieldByName("bk")->AsAnsiString;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::editadjustKeyPress(TObject *Sender, wchar_t &Key)
{
  if ((Key < '0' && Key > '9')&&(Key != VK_RETURN)&&(Key != '-') && (Key != '\b')) {
  		Key = NULL;

  }
  if (Key == VK_RETURN) {
		if (dg->SelectedRows->Count == 0 ) {
        	aqdetail->Edit();
			try {
				aqdetail->FieldByName("adjustAmount")->AsInteger = StrToInt(editadjust->Text) ;
			} catch (...) {
			}
			aqdetail->UpdateBatch(arAll);
		}
		else
		{
        	for (int i = 0; i < dg->SelectedRows->Count  ; i++) {
			aqdetail->GotoBookmark(dg->SelectedRows->Items[i]);

			aqdetail->Edit();
			try {
				aqdetail->FieldByName("adjustAmount")->AsInteger = StrToInt(editadjust->Text) ;
			} catch (...) {
			}
			aqdetail->UpdateBatch(arAll);
			}
		}

	RefreshDetail();
	editadjust->Text = "";
	edtCatalog->SetFocus();
  }
}
//---------------------------------------------------------------------------


void __fastcall TfrmStockAdjust::BtnOKClick(TObject *Sender)
{
  String sql;
  if (editnum->Text == "") {
      return;
  }
  if (aqdetail->IsEmpty() ) {
  	return;
  }
   if (MessageBox(0,"确定要修该库存数量吗？","询问",MB_ICONQUESTION ||MB_YESNO )==1) {
	 sql = "exec USP_BS_StockAdjustUpdate 0," + editnum->Text + ",0,1";
	 ExecSQL(sql);
	 RefreshDetail();

		aqhead->Active = false;
		aqhead->Connection = fcon;
		aqhead->Active = true;
		BtnOK->Enabled = false;
		BtnNew->Enabled = true;
		edstate->Text = "已确认库存";
		BtnDelete->Enabled = false;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::DBNClick(TObject *Sender, TNavigateBtn Button)
{

  /*if (Button == 0) {
	  aqhead->First();
  }
  if (Button == 0) {
	 aqhead->Last();
  }
  if (Button == 1) {
	 aqhead->Prior();

  }
  if (Button == 2) {
	  aqhead->Next();
  }*/
  Deletenote();
  editnum->Text =  aqhead->FieldByName("adjustHeaderID")->AsAnsiString ;
  dtpdate->Date = aqhead->FieldByName("adjustdate")->AsDateTime ;
  membk->Text =   aqhead->FieldByName("bk")->AsAnsiString ;
  editusername->Text = aqhead->FieldByName("adjustemployee")->AsAnsiString ;
  if (aqhead->FieldByName("state")->AsAnsiString==1) {

	BtnOK->Enabled = false;
	edstate->Text = "已确认库存";
	BtnDelete->Enabled = false;
  } else
  {
	BtnOK->Enabled = true;
	edstate->Text = "未确认库存";
	BtnDelete->Enabled = true;
  }
  BtnNew->Enabled = true;
  BtnSave->Enabled = false;
  RefreshDetail();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::FormClose(TObject *Sender, TCloseAction &Action)

{
	Deletenote();
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {   //查单
		BtnView->Click();
	}
	if (Key == VK_F2) {   //添单
		BtnNew->Click();
	}
	if (Key == VK_F3) {   //保存
		BtnSave->Click();
	}
	if (Key == VK_F7) {   //确认库存
		BtnOK->Click();
	}
	if (Key == VK_F8) {   //导出
		BtnExport->Click();
	}
	if (Key == VK_F5) {   //删除
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

void __fastcall TfrmStockAdjust::edsamountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		aqdetail->Edit();
		try {
			aqdetail->FieldByName("damagenum")->AsInteger = StrToInt(edsamount->Text) ;
		} catch (...) {
		}
		aqdetail->UpdateBatch(arAll);
		RefreshDetail();
		edsamount->Text = "0";
		edbak->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::edbakExit(TObject *Sender)
{
    if (aqdetail->IsEmpty() ) {
		return;
	}
	aqdetail->Edit();
	aqdetail->FieldByName("bk")->AsAnsiString  = edbak->Text ;
	aqdetail->UpdateBatch(arAll);
	RefreshDetail();
	edbak->Text = "";
	edtCatalog->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::edsamountClick(TObject *Sender)
{
	if (true) {

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::BtnExportClick(TObject *Sender)
{
	//Excel导出
	if (aqdetail->IsEmpty() ) {
		return;
	}
	DbgridToExcel(dg);
}
//---------------------------------------------------------------------------
bool TfrmStockAdjust::DbgridToExcel(TDBGrid* dbg)
{
   	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = "库存调整" + editnum->Text ;
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
	else
	{
    	return false;
	}
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   //iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	temptext = ",,,库存调整";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n";
	temptext = temptext + "单号,'" + editnum->Text + ",日期," + DateToStr(dtpdate->Date) + ",操作员," + editusername->Text + ",状态," + edstate->Text + ",备注," + membk->Text ;
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n\n";

	int t1= 0;
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			//temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			//v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());


	int t2 = dbg->DataSource ->DataSet ->RecordCount ;
	aqdetail->DisableControls();
	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					t1++;
					//temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "name") {
					t1++;
					AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					//temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + bookname + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "discount") {
					t1++;
					//temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + "%,";
				}
				else
				{
					t1++;
					//temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	aqdetail->EnableControls();
	int h =  aqdetail->RecordCount + 4;
    temptext = "\n";
	temptext = temptext + "合计,,,,,=SUM(F5:F" + IntToStr(h) + "),=SUM(G5:G" + IntToStr(h) + "),=SUM(H5:H" + IntToStr(h) + "),=SUM(I5:I" + IntToStr(h) + "),=SUM(J5:J" + IntToStr(h) + "),=SUM(K5:K" + IntToStr(h) + ")";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------

void TfrmStockAdjust::Deletenote()
{
	if (!aqhead->IsEmpty() && aqdetail->IsEmpty() && (editnum->Text != "" || editnum->Text != NULL)) {
		AnsiString sql;
		sql = "delete from STK_AdjustHeader where AdjustHeaderID = " + editnum->Text;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		aqhead->Active = false;
		aqhead->Active = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "作者";
	m_catalogSearchMode=5;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::BtnViewClick(TObject *Sender)
{
	TfrmQryNoteCode *frm = new TfrmQryNoteCode(Application,0);
	frm->SetstgID(Stgid);
	if (frm->ShowModal() == mrOk) {
		DBN->Enabled = true;
		Deletenote();

		AnsiString Code = frm->GetNoteCode();
		delete frm;

		AnsiString sql;
		sql = "select * from STK_AdjustHeader where AdjustHeaderID = " + Code;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->IsEmpty() ) {
			return;
		}

		TLocateOptions Opts;
		Opts.Clear();
		Opts << loPartialKey;
		aqhead->Locate("id", aq->FieldByName("id")->AsAnsiString, Opts);

		editnum->Text =  aq->FieldByName("adjustHeaderID")->AsAnsiString ;
		dtpdate->Date = aq->FieldByName("adjustdate")->AsDateTime ;
		membk->Text =   aq->FieldByName("bk")->AsAnsiString ;
		editusername->Text = aq->FieldByName("adjustemployee")->AsAnsiString ;
		if (aq->FieldByName("state")->AsAnsiString==1) {

			BtnOK->Enabled = false;
			edstate->Text = "已确认库存";
			BtnDelete->Enabled = false;
		} else
		{
			BtnOK->Enabled = true;
			edstate->Text = "未确认库存";
			BtnDelete->Enabled = true;
		}
		BtnNew->Enabled = true;
		BtnSave->Enabled = false;
		RefreshDetail();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::membkExit(TObject *Sender)
{
	String sql ;
	if (editnum->Text == "") {
		return;
	}
	sql = " update STK_AdjustHeader set adjustDate = '"+ DateToStr(dtpdate->Date) +"',adjustemployee = '"+editusername->Text +"',bk = '"+membk->Text +"', ";
	sql =  sql + " state = 0 where AdjustheaderID = " + editnum->Text ;
	ExecSQL(sql);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockAdjust::BtnDeleteClick(TObject *Sender)
{
	if (aqdetail->IsEmpty()  ) {
		return;
	}
    String sql ;
	sql = "delete from stk_adjustdetail where id = " + aqdetail->FieldByName("id")->AsString ;
	ExecSQL(sql);
	RefreshDetail();
}
//---------------------------------------------------------------------------


