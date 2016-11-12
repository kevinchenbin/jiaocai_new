//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Stockcheckxuyi.h"
#include "SelectCatalogForm.h"
#include "QryNoteCodeForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzLabel"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RpBase"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpSystem"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma resource "*.dfm"
TfrmStockcheckxuyi *frmStockcheckxuyi;
//---------------------------------------------------------------------------
__fastcall TfrmStockcheckxuyi::TfrmStockcheckxuyi(TComponent* Owner)
	: TForm(Owner)
{
   m_catalogSearchMode = 1;
   dtpdate->Date = Now();
}
void TfrmStockcheckxuyi::init(LandInfo *li)
{

   fcon  = li->con ;
   aq->Connection = fcon;
	UserID = li->userID ;
	Stgid = li->storageID ;
	editusername->Text = li->UserName ;
	aqhead->Connection = fcon;
	aqhead->Active = true;
     BtnNew->Click();
      aqdetail->Connection = fcon;
   adostoreaddnote->Connection = fcon;

   //aqhead->Last();
	edtCatalog->SetFocus();
	AnsiString sql="select name from SYS_StorageInfo where id =" + IntToStr(Stgid);
		TADOQuery *aq = new TADOQuery(Application);
	aq->Connection = fcon ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edstorageid->Text = IntToStr(Stgid);
   editstorage->Text = aq->FieldByName("name")->AsAnsiString ;
   edstorageid->Text = IntToStr(Stgid);
   /*sql="select name from sys_user where id =" + IntToStr(UserID);
   aq->Connection = fcon ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
   editusername->Text = aq->FieldByName("name")->AsAnsiString ;        */

   delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStockcheckxuyi::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		PM->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::N1Click(TObject *Sender)
{
	lblCatalog->Caption = "书号";
	m_catalogSearchMode=1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码";
	m_catalogSearchMode=2;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名";
	m_catalogSearchMode=3;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::N6Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode=6;
}
//---------------------------------------------------------------------------
void TfrmStockcheckxuyi::ExecSQL(AnsiString sql)
{
	TADOQuery *aq = new TADOQuery(Application);
	aq->Connection = fcon ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}
void __fastcall TfrmStockcheckxuyi::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)

{

   if (Key == VK_RETURN)
	{

	 if (edtCatalog->Text =="") {
	   ChangeCatalogSearchMode();
	   return;

	 }
	 if (BtnSave->Enabled) {
		MessageBoxA(0,"请先保存！","提示",MB_ICONWARNING);
		return;
	 }
			TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,fcon);
					LandInfo li;
					li.app = Application;
					li.con = fcon;
					li.userID = UserID;
					li.storageID = Stgid;
					frm->Init(&li);
					frm->DoModalType = 10;
					frm->stockcheckxuyi  = this;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					if (mrOk == frm->ShowModal())
					{
						if (frm->SelectAll) {
							 for (int i = 0; i < frm->lengthint  ; i++) {
								AddNote(frm->SupplierID[i],frm->BkcatalogiD[i],frm->BKSKid[i],frm->stkbkid[i]);
							 }
						}else
						{
						   frm->GetSelectResult(supplierID, catalogID);
						   AddNote(supplierID,catalogID,frm->BSKid,frm->BKinfoid);
						   editadjust->SetFocus();
						}
					}

                  	delete frm;
					edtCatalog->Text = "";
	}
}
void TfrmStockcheckxuyi::AddNote(int supplierID,int CatalogId,int stackid,int stkid)
{
	String sql;
	int amount;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   =  IntToStr(stkid);
	if ( aqdetail->Locate("sbkid",str,Opts))
	{
		MessageBoxA(0,"该书已在盘点!","虚拟盘点管理",MB_ICONASTERISK);
		return;
	}
	sql = "select * from STK_stockxuyiDetail,STK_stockxuyiHeader where STK_stockxuyiHeader.AdjustHeaderID = STK_stockxuyiDetail.AdjustHeaderID and STK_stockxuyiHeader.state = 0 and STK_stockxuyiDetail.bkinfoid = " + IntToStr(stkid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount > 0) {
		MessageBox(0,"该书在其它单中正在进行盘点！","提示",MB_ICONWARNING);
		return ;
	}
	sql = "exec USP_BS_StockCheckXuYiAddNote ";
	sql = sql +editnum->Text + "," + IntToStr(supplierID) + "," + IntToStr(CatalogId);
	adostoreaddnote->Parameters->ParamByName("@HeaderID")->Value = editnum->Text;
	adostoreaddnote->Parameters->ParamByName("@SupplierID")->Value = supplierID;
	adostoreaddnote->Parameters->ParamByName("@BkcatalogID")->Value = CatalogId;
	adostoreaddnote->Parameters->ParamByName("@stackid")->Value = stackid;
	adostoreaddnote->Parameters->ParamByName("@bookinfoid")->Value = stkid;

	adostoreaddnote->ExecProc()  ;
	amount=adostoreaddnote->Parameters->ParamByName("@stockamount")->Value;
	editamount->Text = IntToStr(amount);
	RefreshDetail();
}
void TfrmStockcheckxuyi::RefreshDetail()
{

	aqdetail->Active = false;
	aqdetail->Connection = fcon;
	aqdetail->Parameters->ParamByName("num")->Value = editnum->Text ;
	aqdetail->Active = true;
	aqdetail->Last();
}
//---------------------------------------------------------------------------




void __fastcall TfrmStockcheckxuyi::BtnNewClick(TObject *Sender)
{
   Deletecode();
   DBN->Enabled = false;
   String danhao ;
   String sql;
   sql = "select dbo.UF_BSI_Stockcheckxuyi(0,getdate()) as Danhao ";
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   danhao = aq->FieldByName("danhao")->AsAnsiString ;
   sql = "insert into STK_stockxuyiHeader (adjustheaderid,stg) values('" + danhao + "',"+IntToStr(Stgid)+")";
   ExecSQL(sql);
   aqhead->Active = false;
   aqhead->Active = true;
   aqhead->Last();
   editnum->Text = danhao;
   BtnNew->Enabled = false;
   BtnOK->Enabled = true;
	dtpdate->Enabled = true;
	BtnSave->Enabled = true;
	dtpdate->Date  = Now();
   RefreshDetail();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::dgCellClick(TColumn *Column)
{
   if (aqdetail->IsEmpty()) {
	  return;
   }

   editamount->Text = aqdetail->FieldByName("Amount")->AsAnsiString ;
   editadjust->Text = aqdetail->FieldByName("adjustAmount")->AsAnsiString ;
   edsamount->Text = aqdetail->FieldByName("damagenum")->AsAnsiString ;
   edbak->Text = aqdetail->FieldByName("bk")->AsAnsiString;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::editadjustKeyPress(TObject *Sender, wchar_t &Key)

{
 int blanceamount;
  if ((Key < '0' && Key > '9')&&(Key != VK_RETURN)&&(Key != '-')) {
  Key = NULL;

  }
  if (editadjust->Text == "") {
	   return;
  }

  if (Key == VK_RETURN) {
	if (aqdetail->IsEmpty() ) {
    	return;
	}
   blanceamount =  StrToInt(editadjust->Text)- aqdetail->FieldByName("Amount")->AsInteger;
  //	for (int i = 0; i < dg->SelectedRows->Count  ; i++) {
  //		aqdetail->GotoBookmark(dg->SelectedRows->Items[i]);
		aqdetail->Edit();
		aqdetail->FieldByName("adjustAmount")->AsInteger = StrToInt(editadjust->Text) ;
		aqdetail->FieldByName("blanceamount")->AsInteger = blanceamount;
		aqdetail->UpdateBatch(arCurrent );
   //	}

	RefreshDetail();
	editadjust->Text = "0";
	edtCatalog->SetFocus();
  }

}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::BtnSaveClick(TObject *Sender)
{
   String sql ;
   sql = " update STK_stockxuyiHeader  set adjustDate = '"+ DateToStr(dtpdate->Date) +"',adjustemployee = '"+editusername->Text +"',bk = '"+membk->Text +"', ";
   sql =  sql + " state = 0 where AdjustheaderID = " + editnum->Text ;
   ExecSQL(sql);
	editstate->Text = "未确认库存";
	BtnSave->Enabled = false;
	BtnNew->Enabled = true;
	dtpdate->Enabled = false;
	dtpdate->Enabled = false;
	BtnDelete->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::BtnOKClick(TObject *Sender)
{

  if (aqdetail->IsEmpty() ) {
  	return;
  }
  String sql;
   if (MessageBox(0,"确定要修该库存数吗？","询问",MB_ICONQUESTION ||MB_YESNO )==1) {
	 sql = "exec USP_BS_StockCheckxuyiUpdate " + editnum->Text ;
	 ExecSQL(sql);
	 RefreshDetail();

		aqhead->Active = false;
		aqhead->Connection = fcon;
		aqhead->Active = true;
		BtnOK->Enabled = false;
		BtnDelete->Enabled = false;
   }
   editstate->Text = "已确认库存";
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::DBNClick(TObject *Sender, TNavigateBtn Button)
{

  /*if (Button == 0) {
	  aqhead->First();
  }
  if (Button == 3) {
	 aqhead->Last();
  }
  if (Button == 1) {
	 aqhead->Prior();

  }
  if (Button == 2) {
	  aqhead->Next();
  } */
  Deletecode();
  /*if (BtnSave->Enabled) {
	if(MessageBoxA(0,"本单还未保存，是否保存？","提示",MB_OKCANCEL||MB_ICONQUESTION)==1)
	{
	  BtnSave->Click();
	}else
	{
	  //aqhead->Last();
	  Deletecode();
	   BtnSave->Enabled = false;
	   BtnNew->Enabled = true;
	}

  }  */

   if (aqhead->IsEmpty() ) {
	return;
   }
  editnum->Text =  aqhead->FieldByName("adjustHeaderID")->AsAnsiString ;
  dtpdate->Date = aqhead->FieldByName("adjustdate")->AsDateTime ;
  membk->Text =   aqhead->FieldByName("bk")->AsAnsiString ;
  editusername->Text = aqhead->FieldByName("adjustemployee")->AsAnsiString ;
  dtpdate->Enabled = false;
  BtnSave->Enabled = false;
  if (aqhead->FieldByName("state")->AsInteger ==1) {
   editstate->Text = "已确认库存";
	BtnOK->Enabled = false;
	edtCatalog->Enabled = false;
	editadjust->Enabled = false;
	dtpdate->Enabled = false;
	BtnDelete->Enabled = false;
  } else
  {
	editstate->Text = "未确认库存";
	BtnOK->Enabled = true;
	edtCatalog->Enabled = true;
	editadjust->Enabled = true;
	dtpdate->Enabled = true;
	BtnDelete->Enabled = true;
  }
  RefreshDetail();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::FormClose(TObject *Sender, TCloseAction &Action)

{
	Deletecode();
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::BtnExitClick(TObject *Sender)
{
  Close();
}
void TfrmStockcheckxuyi::ChangeCatalogSearchMode()
{
	if (m_catalogSearchMode==3) {
		m_catalogSearchMode=5;
	}else
	{
	m_catalogSearchMode++;  }
	if (m_catalogSearchMode >= 7)
	{
		m_catalogSearchMode = 1;
	}

	switch (m_catalogSearchMode)
	{
	case 1:
		edtCatalog->MaxLength = 13;
		lblCatalog->Caption = "书号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "自编码";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "书名";
		break;
	case 5:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "作者";
		break;
	case 6:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "定价";
		break;
    default:
        break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::BtnDeleteClick(TObject *Sender)
{
  if (aqdetail->IsEmpty() ) {
      return;
  }
  if (MessageBoxA(0,"确认要删除吗？","提示",MB_OKCANCEL||MB_ICONQUESTION)==1 ) {
	 AnsiString sql;
	 sql = "delete STK_stockxuyiDetail where id = " + aqdetail->FieldByName("ID")->AsAnsiString ;
     ExecSQL(sql);
	 aqdetail->Delete() ;

  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::BtnClearClick(TObject *Sender)
{
		RvSystem1->SystemSetups >>ssAllowSetup;
		RvSystem1->SystemSetups >>ssAllowDestPreview;
		RvSystem1->SystemSetups >>ssAllowDestPrinter;
		RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		RvSystem1->SystemSetups >>ssAllowDestFile;



		RvSystem1->DefaultDest  = rdPreview ;
		RvSystem1->SystemSetups<<ssAllowDestPreview;

		pandianproject->ProjectFile = "Stockcheckxuyi.rav";
		 pandianproject->Open();
		 pandianproject->SetParam("title",editstorage->Text + "盘点单");
		 pandianproject->SetParam("danhao","盘点单号:"+aqhead->FieldByName("AdjustHeaderID")->AsAnsiString );
		 pandianproject->SetParam("date","盘点日期:"+aqhead->FieldByName("adjustDate")->AsAnsiString );
		 pandianproject->SetParam("stage","当前盘点店:"+editstorage->Text);
		 pandianproject->SetParam("datetime",aqhead->FieldByName("adjustDate")->AsAnsiString);
		 pandianproject->SetParam("maker",editusername->Text);
		 pandianproject->Execute();
		 pandianproject->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::BtnPrintClick(TObject *Sender)
{
	RvSystem1->SystemSetups >>ssAllowSetup;
		RvSystem1->SystemSetups >>ssAllowDestPreview;
		RvSystem1->SystemSetups >>ssAllowDestPrinter;
		RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		RvSystem1->SystemSetups >>ssAllowDestFile;



		RvSystem1->DefaultDest  = rdPrinter ; ;
		RvSystem1->SystemSetups<<ssAllowDestPrinter;

		 pandianproject->ProjectFile = "Stockcheckxuyi.rav";
		 pandianproject->Open();
		 pandianproject->SetParam("title",editstorage->Text + "盘点单");
		 pandianproject->SetParam("danhao","盘点单号:"+aqhead->FieldByName("AdjustHeaderID")->AsAnsiString );
		 pandianproject->SetParam("date","盘点日期:"+aqhead->FieldByName("adjustDate")->AsAnsiString );
		 pandianproject->SetParam("stage","当前盘点店:"+editstorage->Text);
		 pandianproject->SetParam("datetime",aqhead->FieldByName("adjustDate")->AsAnsiString);
		 pandianproject->SetParam("maker",editusername->Text);
		 pandianproject->SetParam("bk",aqhead->FieldByName("bk")->AsAnsiString);
		 pandianproject->Execute();
		 pandianproject->Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmStockcheckxuyi::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {   //查单
		BtnView->Click();
	}
	if (Key == VK_F2) {   //增单
		BtnNew->Click();
	}
	if (Key == VK_F3) {   //保存
		BtnOK->Click();
	}
	if (Key == VK_F5) {   //删行
		BtnDelete->Click();
	}
	if (Key == VK_F7) {   //确认库存
		BtnOK->Click();
	}
	if (Key == VK_F10) {   //打印
		BtnPrint->Click();
	}
	if (Key == VK_F11) {   //预览
		BtnClear->Click();
	}
	if (Key == VK_F8) {   //导出
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

void __fastcall TfrmStockcheckxuyi::edsamountKeyPress(TObject *Sender, wchar_t &Key)
{
	  if (Key == VK_RETURN) {
		if (edsamount->Text == "") {
        	return;
		}
		if (aqdetail->IsEmpty() ) {
            return;
		}
		try {
        	int blanceamount =  aqdetail->FieldByName("adjustAmount")->AsInteger- aqdetail->FieldByName("Amount")->AsInteger-StrToInt(edsamount->Text) ;

			aqdetail->Edit();
			aqdetail->FieldByName("damagenum")->AsInteger = StrToInt(edsamount->Text) ;
			aqdetail->FieldByName("blanceamount")->AsInteger = blanceamount;
			aqdetail->UpdateBatch(arCurrent );

			RefreshDetail();
			edsamount->Text = "0";
			edbak->SetFocus();
		} catch (...) {
		}

	  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::edbakKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		if (edbak->Text == "") {
        	return;
		}
		if (aqdetail->IsEmpty() ) {
            return;
		}
		aqdetail->Edit();
		aqdetail->FieldByName("bk")->AsAnsiString  = edbak->Text ;
		aqdetail->UpdateBatch(arCurrent );

		RefreshDetail();
		edbak->Text = "";
		edtCatalog->SetFocus();
	  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::BtnExportClick(TObject *Sender)
{
	//Excel导出
	if (aqdetail->IsEmpty() ) {
		return;
	}
	DbgridToExcel(dg);
}
//---------------------------------------------------------------------------
bool TfrmStockcheckxuyi::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = "局部盘点" + editnum->Text ;
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

	temptext = ",,,局部盘点";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n";
	temptext = temptext + "单号,'" + editnum->Text + ",日期," + DateToStr(dtpdate->Date) + ",操作员," + editusername->Text + ",状态," + editstate->Text + ",备注," + membk->Text ;
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n\n";

	int t1= 0;
	for(int q=0;q<dbg->FieldCount-3 ;++q)
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
		for(int j=1;j<dbg->Columns ->Count-2  ;j++)
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
	temptext = temptext + "合计,,,,,,,=SUM(H5:H" + IntToStr(h) + "),=SUM(I5:I" + IntToStr(h) + "),=SUM(J5:J" + IntToStr(h) + "),=SUM(K5:K" + IntToStr(h) + "),=SUM(L5:L" + IntToStr(h) +"),=SUM(M5:M" + IntToStr(h) + ")";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------
void TfrmStockcheckxuyi::Deletecode()
{
	AnsiString sql ;
	if (!aqhead->IsEmpty() && aqdetail->IsEmpty() && editnum->Text != "" ) {
		sql = "delete from STK_stockxuyiHeader where AdjustHeaderID = " + editnum->Text ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		aqhead->Active = false;
		aqhead->Active = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "作者";
	m_catalogSearchMode=5;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockcheckxuyi::BtnViewClick(TObject *Sender)
{
	TfrmQryNoteCode *frm = new TfrmQryNoteCode(Application,0);
	frm->SetstgID(Stgid);
	if (frm->ShowModal() == mrOk) {
		DBN->Enabled = true;
		Deletecode();

		AnsiString Code = frm->GetNoteCode();
		delete frm;

		AnsiString sql;
		sql = "select * from STK_stockxuyiHeader where AdjustHeaderID = " + Code;
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

		editnum->Text =  aq->FieldByName("AdjustHeaderID")->AsString ;
		dtpdate->Date = aq->FieldByName("adjustdate")->AsDateTime ;
		membk->Text =   aq->FieldByName("bk")->AsAnsiString ;
		editusername->Text = aq->FieldByName("adjustemployee")->AsAnsiString ;
		dtpdate->Enabled = false;
		BtnSave->Enabled = false;
		if (aq->FieldByName("state")->AsInteger ==1) {
			editstate->Text = "已确认库存";
			BtnOK->Enabled = false;
			edtCatalog->Enabled = false;
			editadjust->Enabled = false;
			dtpdate->Enabled = false;
			BtnDelete->Enabled = false;
		} else
		{
			editstate->Text = "未确认库存";
			BtnOK->Enabled = true;
			edtCatalog->Enabled = true;
			editadjust->Enabled = true;
			dtpdate->Enabled = true;
			BtnDelete->Enabled = true;
		}
		RefreshDetail();
	}

}
//---------------------------------------------------------------------------

