//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CoustomerImport.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzRadChk"
#pragma link "RzPanel"
#pragma link "RzPrgres"
#pragma link "RzShellDialogs"
#pragma resource "*.dfm"
TFormCousImport *FormCousImport;
//---------------------------------------------------------------------------
__fastcall TFormCousImport::TFormCousImport(TComponent* Owner,TADOQuery * query,int type)
	: TForm(Owner)
{
	Type = type;
	Import = true;
	if (Type == 1) {
		this->Caption = "供应商数据导入";
		chsaleman->Caption = "采购员";
		cbname->Caption = "供应商名称";
	}
	if (Type == 2) {
		this->Caption = "客户数据导入";
		cbname->Caption = "客户名称";
	}
	dsdg = query;
	aqdetail->Connection = query->Connection ;
}
//---------------------------------------------------------------------------
void __fastcall TFormCousImport::btselectpathClick(TObject *Sender)
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
void __fastcall TFormCousImport::BtnImportClick(TObject *Sender)
{
	if(edtExcelPath->Text == "")
		return;
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
	//String sql = "select * from " + ExtractFileName(opndlgExcelPath->FileName .c_str() ) + " where Type = " ;
	//sql = sql +  IntToStr(Type);
	//EXCEL导入
	String sql = "select * from [11$] where Type = ";
	sql = sql +  IntToStr(Type);
	String str = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	str = str + edtExcelPath->Text ;
	str = str + ";Mode=Read;Extended Properties=\"Excel 8.0;HDR=Yes;IMEX=1\";" ;
	 //C:\\Documents and Settings\\Administrator\\桌面\\11.xls;Mode=Read;Extended Properties=Excel 8.0;Persist Security Info=False";

	//con1->Provider = "Microsoft.Jet.OLEDB.4.0";
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

	//int j = qry1->DataSource ->DataSet ->RecordCount ;
	int j = qry1->RecordCount ;
	float percent = 0;
	for(int i=1;i<=j;i++)
	{

		qry1->Active = true;
		dsdg->Active = true;
		if (dsdg->State != dsInsert) {
        	dsdg->Append();
		}
		if (cbtype->Checked ) {
			if (Type == 1) {
				dsdg->FieldByName("Type")->AsInteger  = 1;
			}
			if (Type == 2) {
				dsdg->FieldByName("Type")->AsInteger  = 2;
			}
		}
		if (cbname->Checked ) {
			dsdg->FieldByName("Name")->AsString = qry1->FieldByName("Name")->AsString;
		}
		if (cbaddress->Checked ) {
			dsdg->FieldByName("Address")->AsString = qry1->FieldByName("Address")->AsString;
		}
		if (cbcode->Checked ) {
			AnsiString code = qry1->FieldByName("Code")->AsString ;
			if (code != "") {
				dsdg->FieldByName("Code")->Value = qry1->FieldByName("Code")->Value;
			}
		}
		if (cbtelphone->Checked ) {
			dsdg->FieldByName("Telephone")->AsString  = qry1->FieldByName("Telephone")->AsString;
		}
		if (cbfax->Checked ) {
			dsdg->FieldByName("Fax")->AsString = qry1->FieldByName("Fax")->AsString;
		}
		if (cbcontex->Checked ) {
			dsdg->FieldByName("Contact")->AsString = qry1->FieldByName("Contact")->AsString;
		}
		if (cbdate->Checked ) {

			dsdg->FieldByName("Date")->Value  = qry1->FieldByName("Date")->Value ;

		}
		if (chsaleman->Checked ) {
			dsdg->FieldByName("Salesman")->AsString  = qry1->FieldByName("Salesman")->AsString  ;
		}
		if (cbbalance->Checked ) {
			AnsiString balance =  qry1->FieldByName("Balance")->AsString ;
			if (balance != "") {
				dsdg->FieldByName("Balance")->Value  = qry1->FieldByName("Balance")->Value ;
			}
		}
		if (cbarea->Checked ) {
			dsdg->FieldByName("Local")->AsString  = qry1->FieldByName("Local")->AsString ;
		}
		if (cbBsLessBus->Checked ) {
			AnsiString   BookstoreLessBusiness =  qry1->FieldByName("BookstoreLessBusiness")->AsString ;
			if (BookstoreLessBusiness != "") {
            	dsdg->FieldByName("BookstoreLessBusiness")->Value  = qry1->FieldByName("BookstoreLessBusiness")->Value ;
			}
		}
		if (cbBusLessBs->Checked ) {
			AnsiString  BusinessLessBookstore = qry1->FieldByName("BusinessLessBookstore")->AsString ;
			if (BusinessLessBookstore != "") {
				dsdg->FieldByName("BusinessLessBookstore")->Value  = qry1->FieldByName("BusinessLessBookstore")->Value ;
			}
		}
		dsdg->Append() ;
		sql =  "select max(ID) as id from cust_customerinfo";
		aqdetail->Close();
		aqdetail->SQL->Clear();
		aqdetail->SQL->Add(sql);
		aqdetail->Open();
		int customerid = aqdetail->FieldByName("id")->AsInteger ;
		sql = "insert into CUST_CustomerStartMoney(CustomerID) values (" + IntToStr(customerid)  + ")" ;
		aqdetail->Close();
		aqdetail->SQL->Clear();
		aqdetail->SQL->Add(sql);
		aqdetail->ExecSQL();
		lbsum->Caption = IntToStr(j);
		lbnow->Caption = IntToStr(i);
		percent = i*100/j;
		prgrsbrExcelImport->Percent = percent;
		qry1->RecNo ++;

	}
	dsdg->UpdateBatch(arAll);
	//dsdg->Append();
	lblExcel->Caption = "EXCEL导入完毕！";
	MessageBoxA(0,"数据导入成功！","Excel导入",MB_ICONEXCLAMATION);
	Import= true;
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormCousImport::BtnExitClick(TObject *Sender)
{
	if (Import) {
		Close();
	}else
	{
		MessageBoxA(0,"正在导入中，不能退出！","Excel导入",MB_ICONASTERISK);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormCousImport::cballcheckClick(TObject *Sender)
{
	if (cballcheck->Checked ) {
		cbname->Checked = true;
		cbtype->Checked = true;
		cbaddress->Checked = true;
		cbcontex->Checked = true;
		cbtelphone->Checked = true;
		cbfax->Checked = true;
		cbcode->Checked = true;
		chsaleman->Checked = true;
		cbdate->Checked = true;
		cbbalance->Checked = true;
		cbarea->Checked = true;
		cbBsLessBus->Checked = true;
		cbBusLessBs->Checked = true;
	}
	else
	{
		cbname->Checked = false;
		cbtype->Checked = false;
		cbaddress->Checked = false;
		cbcontex->Checked = false;
		cbtelphone->Checked = false;
		cbfax->Checked = false;
		cbcode->Checked = false;
		chsaleman->Checked = false;
		cbdate->Checked = false;
		cbbalance->Checked = false;
		cbarea->Checked = false;
		cbBsLessBus->Checked = false;
		cbBusLessBs->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormCousImport::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TFormCousImport::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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

