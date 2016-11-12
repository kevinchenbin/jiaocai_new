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
	//con1->Mode = cmRead;
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
	dsdg->Active = true;

	AnsiString BSID;
	dspress->Active = false;
	sql = "select ID from STK_BookstackInfo where Name = '默认库位' and stgid = " + IntToStr(fstgid) ;
	dspress->CommandText = sql;
	dspress->Active = true;
	BSID = dspress->FieldByName("ID")->AsString ;

	int j = qry1->RecordCount ;
	float percent = 0;
	qry1->DisableControls();
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = dspress->Connection ;
	for(int i=1;i<=j;i++)
	{
		//qry1->Active = true;
        bool cg = true;
		int catalogid = -2;
		String isbn =  qry1->FieldByName("ISBN")->AsString.Trim();
		isbn = StringReplace(isbn , "-","",TReplaceFlags()<<rfReplaceAll);
		sql = "select BS_BookCatalog.ID from BS_BookCatalog join BS_PressInfo on bs_pressinfo.id = bs_bookcatalog.pressid where bs_bookcatalog.Name = '" + qry1->FieldByName("书名")->AsString.Trim() + "' and bs_bookcatalog.Price = " + qry1->FieldByName("定价")->AsString + " and bs_bookcatalog.author = '" + qry1->FieldByName("作者")->AsString + "' and BS_PressInfo.AbbreviatedName = '" + qry1->FieldByName("版别")->AsString + "' and bs_bookcatalog.isbn = '" + isbn + "'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount > 0) {
			catalogid = aq->FieldByName("ID")->AsInteger ;
		}
		else
		{
			//书目导入
			//**********//
		if (dsdg->State != dsInsert) {
			dsdg->Append();
		}
		if(chckbxTypeName->Checked && qry1->FieldByName("类别")->AsString != "")
		{
			dspress->Active = false;
			sql = "select count(*) as count from BS_BookType ";
			dspress->CommandText = sql;
			dspress->Active = true;
			int count = dspress->FieldByName("count")->AsInteger ;
			if (count > 0) {
				dspress->Active = false;
				sql = "select ID,Name from BS_BookType where Name = '" + qry1->FieldByName("类别")->AsString  + "'";
				dspress->CommandText = sql;
				dspress->Active = true;
				if (dspress->RecordCount == 0 ) {
					dsdg->FieldByName("typename")->AsString  = qry1->FieldByName("类别")->AsString  ;
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
				dsdg->FieldByName("typename")->AsString  = qry1->FieldByName("类别")->AsString;
				dsdg->FieldByName("smallBookTypeID")->AsInteger = 0;
			}
		}

		if(chckbxBarcode->Checked )
		{
			String barcode = qry1->FieldByName("条码")->AsString.Trim() ;
			barcode = StringReplace(barcode , "-","",TReplaceFlags()<<rfReplaceAll);
			dsdg->FieldByName("Barcode")->Value = barcode ;
		}

		if(chckbxISBN->Checked )
		{
			//String isbn =  qry1->FieldByName("ISBN")->AsString.Trim();
			//isbn = StringReplace(isbn , "-","",TReplaceFlags()<<rfReplaceAll);
			dsdg->FieldByName("ISBN")->AsString  = isbn ;
		}

		if(!chckbxBarcode->Checked )
		if(chckbxISBN->Checked )
		{
			//String isbn =  qry1->FieldByName("ISBN")->AsString.Trim() ;
			//isbn = StringReplace(isbn , "-","",TReplaceFlags()<<rfReplaceAll);
			if (isbn != "") {
				try {
                	isbn = ISBNToBarcode(isbn);
					dsdg->FieldByName("Barcode")->AsAnsiString = isbn;
				} catch (...) {
				}
			}
		}

		if(!chckbxISBN->Checked )
		if(chckbxBarcode->Checked )
		{
			String barcode = qry1->FieldByName("条码")->AsString.Trim()  ;
			barcode = StringReplace(barcode , "-","",TReplaceFlags()<<rfReplaceAll);
			if (barcode != "") {
				try {
                	barcode = BuildISBNCode(barcode);
					dsdg->FieldByName("ISBN")->AsAnsiString = barcode;
				} catch (...) {
				}
			}
		}

		if(chckbxName->Checked )
		{
			dsdg->FieldByName("Name")->AsString = qry1->FieldByName("书名")->AsString.Trim() ;
		}

		if(chckbxAuthor->Checked )
		{
			dsdg->FieldByName("Author")->AsString = qry1->FieldByName("作者")->AsString.Trim() ;
		}

		if(chckbxUserDefCode->Checked && qry1->FieldByName("自编号")->AsString != "")
		{

			dsdg->FieldByName("UserDefCode")->Value = qry1->FieldByName("自编号")->AsString.Trim();
		}
		else
		{
			char* t;
			char t2;
			String t1,t3,t4;
			t1 = qry1->FieldByName("书名")->AsString;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;
			int t5=1,i =qry1->FieldByName("书名")->AsString.Length() ;
			for( int j=1;j<=i;j++)
			{
			//if (j == 9) break;
			t3 = t1.SubString(j,1);
			t = t3.t_str();
			//if(t3 < 160) continue;
			Word k = int (t[0])<<8;
			k = k >> 8;
			if(k<160) continue;
			//if(int(t[0])< 160) continue;
			//if (t3 >= 'a' && t3 <= 'z' || t3 >= 'A' && t3 <= 'Z'|| t3 >= 0 && t3 <= 9||t3 == '!'||t3 == '@'||t3=='#'||t3=='$'||t3=='%') continue;
			t5++;
			if (t5 == 9) break;
			t = t3.t_str();
			t2 = GetPYIndexChar(t);
			t4 = t4 + t2;
			}
			dsdg->FieldByName("UserDefCode")->Value = t4;
		}

		if(chckbxDate->Checked )
		{
			try {
				dsdg->FieldByName("Pressdate")->Value = qry1->FieldByName("出版时间")->Value ;
			} catch (...) {
			}
		}
		if(chckbxPrice->Checked )
		{
			try {
				dsdg->FieldByName("Price")->Value = qry1->FieldByName("定价")->Value ;
			} catch (...) {
			}
		}

		if(chhuojiangstate->Checked )
		{
			try {
				dsdg->FieldByName("huojiangstate")->Value = qry1->FieldByName("获奖情况")->Value ;
			} catch (...) {
			}
		}

		if(chbaoce->Checked )
		{
			try {
				if (qry1->FieldByName("包/册")->AsString == "") {
					dsdg->FieldByName("BookWords")->Value = 1;
				}
				else
				{
					dsdg->FieldByName("BookWords")->Value = qry1->FieldByName("包/册")->Value ;
				}
			} catch (...) {
			}
		}

		if(chckbxPress->Checked )
		{
			dspress->Active = false;
			AnsiString press = qry1->FieldByName("版别")->AsString.Trim();
			if (press != "") {
				sql = "select ID,PresentNum from BS_PressInfo where AbbreviatedName = '" + qry1->FieldByName("版别")->AsString.Trim()  + "'";
				dspress->CommandText = sql;
				dspress->Active = true;
				if (dspress->FieldByName("PresentNum")->AsString != ""  ) {
					dsdg->FieldByName("pid")->AsInteger = dspress->FieldByName("ID")->AsInteger;
				}
			}
		}
		/*if (chckbxTotalAmount->Checked ) {
			AnsiString totalamount = qry1->FieldByName("库存")->AsString ;
			if (totalamount != "") {
				try {
                	int amount = qry1->FieldByName("库存")->AsInteger ;
					if (amount < 0) {
						dsdg->FieldByName("TotalAmount")->AsInteger = 0;
					}
					else
					{
						dsdg->FieldByName("TotalAmount")->Value = qry1->FieldByName("库存数量")->Value ;
					}
				} catch (...) {
				}
			}
		} */

		try {
			dsdg->UpdateBatch(arCurrent);
		} catch (...) {
			try {
				cg = false;
				vExcelApp.OlePropertyGet("Cells",2+i,1).OlePropertySet("Value","添加书目信息出错" );
			} catch (...) {
			}
		}

		dsdg->Append();
		}
        //***************//

		if (chckbxTotalAmount->Checked && cg) {
			AnsiString BCID,SPID;
			//STK_BookInfo的BkcatalogID
			if (catalogid > -2) {
				BCID = IntToStr(catalogid);
			}
			else
			{
            	dspress->Active = false;
				sql = "select max(id) as ID from BS_BookCatalog ";
				dspress->CommandText = sql;
				dspress->Active = true;
				BCID = dspress->FieldByName("ID")->AsString ;
			}

			//STK_BookInfo的BkstackID         +*-

			//STK_BookInfo的SupplierID
			dspress->Active = false;
			if (checkbsupplier->Checked ) {
            	try {
					sql = "select ID from CUST_CustomerInfo where Name = '" + qry1->FieldByName("供应商")->AsString + "' and Type = 1";
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
			AnsiString totalamount = qry1->FieldByName("库存")->AsString ;
			if (totalamount != "") {
				int amount;
				try {
					amount = qry1->FieldByName("库存")->AsInteger ;
				} catch (...) {
				}

				if (amount < 0) {
					totalamount = "0";
				}
			}
			else
			{
				totalamount = "0" ;
			}
			sql = "insert into STK_BookInfo (Amount,BkcatalogID,BkstackID,SupplierID,stgid) values ("+totalamount + "," + BCID + "," + BSID + "," + SPID + "," + IntToStr(fstgid) + ")";
			query1->Close();
			query1->SQL->Clear();
			query1->SQL->Add(sql);
			query1->ExecSQL();
		}
		//lbsum->Caption = IntToStr(j);
		//lbnow->Caption = IntToStr(i);
		//percent = i*100/j;
		//prgrsbrExcelImport->Percent = percent;
		qry1->RecNo ++;
	}
    delete aq;
	qry1->EnableControls();
	//dsdg->Append();
	lblExcel->Caption = "EXCEL导入完毕！";
	MessageBoxA(0,"数据导入成功！","Excel导入",MB_ICONEXCLAMATION);
	Import= true;

	Wb.OleProcedure("Close");
	con1->Connected =false;
	vExcelApp.OleProcedure("Quit");
	vExcelApp = Unassigned;

	this->Close();
}
//---------------------------------------------------------------------------

char TfrmExcelImport::GetPYIndexChar(char *str)
{
	Word x = 0;
	Word y = 0;//int y = 0;
	//x = StrToInt()

	 x = (int(str[0]))<<8;
	 y = (int(str[1]))<<8;
	 y = y>>8;
	 x = x + y;//str[1];
	Word Address[] = { 0xB0C4,0xB2C0,0xB4ED,0xB6E9,0xB7A1,
	0xB8C0,0xB9FD,0xBBF6,0xBFA5,0xC0AB,
	0xC2E7,0xC4C2,0xC5B5,0xC5BD,0xC6D9,
	0xC8BA,0xC8F5,0xCBF9,0xCDD9,0xCEF3,
	0xD188,0xD4D0,0xD7F9 };
	char Rchar[25] = "ABCDEFGHJKLMNOPQRSTWXYZ ";
	int i=0;
	for(;i<24;i++)
	if(Address[i] >= x) break;
	return Rchar[i];
}
//---------------------------------------------------------------------------

void TfrmExcelImport::Init(TApplication* app, TADOConnection* con,int stgid)
{
	TfrmModalDialog::Init(app, con);
	dset1->Connection = m_con;
	fstgid = stgid;
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
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

