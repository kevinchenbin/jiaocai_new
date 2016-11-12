//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ExcelImport.h"
#include "pdutil.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma link "ModalDialog"
#pragma link "RzRadChk"
#pragma link "RzRadGrp"
#pragma link "RzShellDialogs"
#pragma link "RzPrgres"
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
TfrmExcelImport *frmExcelImport;
//---------------------------------------------------------------------------
__fastcall TfrmExcelImport::TfrmExcelImport(TComponent* Owner,TADOQuery * query)
	: TfrmModalDialog(Owner)
{
   Import= true;
   dsdg = query;
   query1->Connection = query->Connection ;
   dspress->Connection = query->Connection ;
}

//---------------------------------------------------------------------------
void __fastcall TfrmExcelImport::btn2Click(TObject *Sender)
{
	//
	if(edtExcelPath->Text == "")
	return;
	if (!chckbxName->Checked ) {
		MessageBox(0,"书名必须要导入！","",MB_OK);
		return;
	}
	else
	{
		MessageBoxA(0,"确定要导入？","Excel导入",MB_ICONQUESTION);
		lblExcel->Visible = true;
		lblExcel->Caption = "导入正在进行,请稍后...";
	}
	Import= false;
	Variant vExcelApp,vSheet,Wb;
	vExcelApp = Variant::CreateObject("Excel.Application");
	AnsiString s = ExtractFilePath(opndlgExcelPath->FileName .c_str());
	s = s + ExtractFileName(opndlgExcelPath->FileName .c_str() );
	vExcelApp.OlePropertyGet("WorkBooks").OleProcedure("Open",s.c_str()   );// opndlgExcelPath->f  FileName .c_str() );
	Wb = vExcelApp.OlePropertyGet("ActiveWorkBook");
	vSheet = Wb.OlePropertyGet("ActiveSheet");
	vSheet.OlePropertySet("name","11");
	Wb.OleProcedure("Save");
	Wb.OleProcedure("Close");
	vExcelApp.OleFunction("Quit");
	//CSV导入
	//String sql = "select * from " + ExtractFileName(opndlgExcelPath->FileName .c_str() ) ;
	//EXCEL导入
	String sql = "select * from [11$]";

	String str = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	//EXCEL导入
	str = str + edtExcelPath->Text ;
	str = str + ";Mode=Read;Extended Properties=\"Excel 8.0;HDR=Yes;IMEX=1\";" ;

	//CSV导入
	//str = str + ExtractFilePath(opndlgExcelPath->FileName .c_str()) ;
	//str = str + ";Mode=Read;Extended Properties=\"text;HDR=Yes;IMEX=1;FMT=Delimited\";" ;

	con1->ConnectionString = "";
	try
	{
		con1->ConnectionString =  str ;
	}
	catch(...)
	{
			MessageBoxA(0,"该数据已经导入！","Excel导入",MB_ICONEXCLAMATION);
			Import = true;
			return;
	}
	con1->LoginPrompt = false;
	con1->ConnectOptions = coConnectUnspecified ;
	con1->KeepConnection = true;
	con1->Mode = cmRead;
	try
	{
		 con1->Connected = true;
	}
	catch(...)
	{
		MessageBoxA(0,"数据源配置错误！","Excel导入",MB_ICONHAND);
		Import= true;
		return;
	}
	qry1->Connection = con1;
	qry1->Active = false;
	qry1->SQL->Clear();
	qry1->SQL ->Add(sql);
	qry1->Active = true;
	ds1->DataSet = qry1;

	int j = qry1->RecordCount ;
	float percent = 0;
	for(int i=1;i<=j;i++)
	{
		qry1->Active = true;
		dsdg->Active = true;
		if (dsdg->State != dsInsert) {
			dsdg->Append();
		}
		if(chckbxTypeName->Checked && qry1->FieldByName("Type")->AsString != "")
		{
			dspress->Active = false;
			sql = "select count(*) as count from BS_BookType ";
            dspress->CommandText = sql;
			dspress->Active = true;
			int count = dspress->FieldByName("count")->AsInteger ;
			if (count > 0) {
				dspress->Active = false;
				sql = "select ID,Name from BS_BookType where Name = '" + qry1->FieldByName("Type")->AsString  + "'";
				dspress->CommandText = sql;
				dspress->Active = true;
				if (dspress->RecordCount == 0 ) {
					dsdg->FieldByName("typename")->AsString  = qry1->FieldByName("Type")->AsString  ;
					dspress->Active = false;
					sql = "select max(ID) as id from BS_BookType ";
					dspress->CommandText = sql;
					dspress->Active = true;
					dsdg->FieldByName("smallBookTypeID")->AsInteger  =  dspress->FieldByName("id")->AsInteger + 1;
				}
				else
				{
					dsdg->FieldByName("smallBookTypeID")->AsInteger = dspress->FieldByName("ID")->AsInteger;
				}
			}
			else
			{
				dsdg->FieldByName("typename")->AsString  = qry1->FieldByName("Type")->AsString;
				dsdg->FieldByName("smallBookTypeID")->AsInteger = 0;
			}
		}

		if(chckbxBarcode->Checked )
		{
			String barcode = qry1->FieldByName("Barcode")->AsString ;
			if (barcode!= "") {
            	dsdg->FieldByName("Barcode")->Value = qry1->FieldByName("Barcode")->Value ;
			}
		}

		if(chckbxISBN->Checked )
		{
			/*String isbn =  qry1->FieldByName("ISBN")->AsString;
			if (isbn != "") {
				dsdg->FieldByName("ISBN")->AsString  = qry1->FieldByName("ISBN")->AsString ;
			}*/
			try {
				dsdg->FieldByName("ISBN")->Value = qry1->FieldByName("ISBN")->Value ;
			} catch (...) {
			}

		}

		if(!chckbxBarcode->Checked )
		if(chckbxISBN->Checked )
		{
			String isbn =  qry1->FieldByName("ISBN")->AsString ;
			if (isbn != "") {
				isbn = ISBNToBarcode(isbn);
				dsdg->FieldByName("Barcode")->AsAnsiString = isbn;
			}
		}

		if(!chckbxISBN->Checked )
		if(chckbxBarcode->Checked )
		{
			String barcode = qry1->FieldByName("Barcode")->AsString  ;
			if (barcode != "") {
				barcode = BuildISBNCode(barcode);
				dsdg->FieldByName("ISBN")->AsAnsiString = barcode;
			}
		}

		if(chckbxName->Checked )
		{
		   AnsiString name = qry1->FieldByName("Name")->AsString ;
		   if (name != "") {
				dsdg->FieldByName("Name")->AsString = qry1->FieldByName("Name")->AsString ;
		   }
		}

		if(chckbxAuthor->Checked )
		{
		  AnsiString author = qry1->FieldByName("Author")->AsString ;
		  if (author != "") {
			dsdg->FieldByName("Author")->AsString = qry1->FieldByName("Author")->AsString ;
		  }
		}

		if(chckbxUserDefCode->Checked )
		{
		   AnsiString userdefcode =  qry1->FieldByName("UserDefCode")->AsString;
		   if (userdefcode != "") {
				dsdg->FieldByName("UserDefCode")->Value = qry1->FieldByName("UserDefCode")->Value ;
		   }
		}

		if(chckbxDate->Checked )
		{
			dsdg->FieldByName("Pressdate")->Value = qry1->FieldByName("Date")->Value ;
		}
		if(chckbxPrice->Checked )
		{
			dsdg->FieldByName("Price")->Value = qry1->FieldByName("Price")->Value ;
		}

		if(chckbxPress->Checked )
		{
			dspress->Active = false;
			AnsiString press = qry1->FieldByName("Press")->AsString;
			if (press != "") {
            	sql = "select ID,PresentNum from BS_PressInfo where AbbreviatedName = '" + qry1->FieldByName("Press")->AsString  + "'";
				dspress->CommandText = sql;
				dspress->Active = true;
				if (dspress->FieldByName("PresentNum")->AsString != ""  ) {
					dsdg->FieldByName("pid")->AsInteger = dspress->FieldByName("ID")->AsInteger;
				}
			}
		}
		if (chckbxTotalAmount->Checked ) {
			AnsiString totalamount = qry1->FieldByName("TotalAmount")->AsString ;
			if (totalamount != "") {
				int amount = qry1->FieldByName("TotalAmount")->AsInteger ;
				if (amount < 0) {
					dsdg->FieldByName("TotalAmount")->AsInteger = 0;
				}
				else
				{
					dsdg->FieldByName("TotalAmount")->Value = qry1->FieldByName("TotalAmount")->Value ;
				}
			}
		}
		dsdg->Append();
		dsdg->UpdateBatch(arAll);
		if (chckbxTotalAmount->Checked ) {
			AnsiString BCID,BSID,SPID;
			//STK_BookInfo的BkcatalogID
			dspress->Active = false;
			sql = "select max(id) as ID from BS_BookCatalog ";
			dspress->CommandText = sql;
			dspress->Active = true;
			BCID = dspress->FieldByName("ID")->AsString ;
			//STK_BookInfo的BkstackID         +*-
			dspress->Active = false;
			sql = "select ID from STK_BookstackInfo where Name = '默认库位'";
			dspress->CommandText = sql;
			dspress->Active = true;
			BSID = dspress->FieldByName("ID")->AsString ;
			//STK_BookInfo的SupplierID
			dspress->Active = false;
			if (checkbsupplier->Checked ) {
            	try {
					sql = "select ID from CUST_CustomerInfo where Name = '" + qry1->FieldByName("Supplier")->AsString + "' and Type = 1";
				} catch (...) {
					sql = "select ID from CUST_CustomerInfo where Name = '" + cbsupplier->Text + "' and Type = 1";
				}
			}
			else
			{
            	sql = "select ID from CUST_CustomerInfo where Name = '" + cbsupplier->Text + "' and Type = 1";
			}

			dspress->CommandText = sql;
			dspress->Active = true;
			SPID = dspress->FieldByName("ID")->AsString ;
			AnsiString totalamount = qry1->FieldByName("TotalAmount")->AsString ;
			if (totalamount != "") {
				int amount = qry1->FieldByName("TotalAmount")->AsInteger ;
				if (amount < 0) {
					totalamount = "0";
				}
			}
			else
			{
				totalamount = "0" ;
			}
			sql = "insert into STK_BookInfo (Amount,BkcatalogID,BkstackID,SupplierID) values ("+totalamount + "," + BCID + "," + BSID + "," + SPID + ")";
			query1->Close();
			query1->SQL->Clear();
			query1->SQL->Add(sql);
			query1->ExecSQL();
		}
		lbsum->Caption = IntToStr(j);
		lbnow->Caption = IntToStr(i);
		percent = i*100/j;
		prgrsbrExcelImport->Percent = percent;
		qry1->RecNo ++;
	}
	//dsdg->Append();
	lblExcel->Caption = "EXCEL导入完毕！";
	MessageBoxA(0,"数据导入成功！","Excel导入",MB_ICONEXCLAMATION);
	Import= true;
	this->Close();
}
//---------------------------------------------------------------------------

void TfrmExcelImport::Init(TApplication* app, TADOConnection* con)
{
	TfrmModalDialog::Init(app, con);
	dset1->Connection = m_con;
}


void __fastcall TfrmExcelImport::spselectpathClick(TObject *Sender)
{
	if (opndlgExcelPath->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(opndlgExcelPath->FileName .c_str()  );
		Name = ExtractFileName(opndlgExcelPath->FileName .c_str() );
		DBPath = DBPath + Name;
		edtExcelPath->Text = DBPath;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmExcelImport::BtnImportClick(TObject *Sender)
{
   btn2->Click();
}
//---------------------------------------------------------------------------


void __fastcall TfrmExcelImport::BtnExitClick(TObject *Sender)
{
  if (Import) {
	  Close();
  }else
  {
	  MessageBoxA(0,"正在导入中，不能退出！","Excel导入",MB_ICONASTERISK);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::chckbxTotalAmountClick(TObject *Sender)
{
	if (chckbxTotalAmount->Checked ) {
		checkbsupplier->Enabled = true;
		cbsupplier->Enabled = true;
	}
	else
	{
		checkbsupplier->Enabled = false;
		cbsupplier->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::FormShow(TObject *Sender)
{
	AnsiString sql;
	sql = "select Name from CUST_CustomerInfo where Type = 1";
	dspress->Active = false;
	dspress->CommandText = sql;
	dspress->Active = true;
	while (!dspress->Eof)
	{
		cbsupplier->Add(dspress->FieldByName("Name")->AsString );
		dspress->Next();
	}
	cbsupplier->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F7) {     //导入
		BtnImport->Click();
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

void __fastcall TfrmExcelImport::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

