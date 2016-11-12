//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberImport.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzRadChk"
#pragma link "RzPanel"
#pragma link "RzPrgres"
#pragma link "RzShellDialogs"
#pragma resource "*.dfm"
TFormMemImport *FormMemImport;
//---------------------------------------------------------------------------
__fastcall TFormMemImport::TFormMemImport(TComponent* Owner,TADOQuery * query)
	: TForm(Owner)
{
	Import = true;
	dsdg = query ;
	aqdetail->Connection = query->Connection ;
}
//---------------------------------------------------------------------------
void __fastcall TFormMemImport::btselectpathClick(TObject *Sender)
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
void __fastcall TFormMemImport::BtnImportClick(TObject *Sender)
{
	if(edtExcelPath->Text == "")
	return;
	else
	{
		MessageBoxA(0,"确定要导入？","CSV导入",MB_ICONQUESTION);
		lblExcel->Visible = true;
		lblExcel->Caption = "导入正在进行,请稍后...";
	}
	Import= false;
	Variant vExcelApp,vSheet,Wb,vCsvApp;
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
	//String sql = "select * from " +  ExtractFileName(opndlgExcelPath->FileName .c_str() );
	//EXCEL导入
	String sql = "select * from [11$]";
	String str = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	str = str + edtExcelPath->Text;
	str = str + ";Mode=Read;Extended Properties=\"Excel 8.0;HDR=Yes;IMEX=1\";" ;
	con1->ConnectionString = "";
	try
	{
		con1->ConnectionString =  str ;
	}
	catch(...)
	{
			MessageBoxA(0,"该数据已经导入！","CSV导入",MB_ICONEXCLAMATION);
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
		MessageBoxA(0,"数据源配置错误！","CSV导入",MB_ICONHAND);
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
			dsdg->FieldByName("MemberType")->AsString = qry1->FieldByName("MemberType")->AsString;
		}
		if (cbname->Checked ) {
			dsdg->FieldByName("Name")->AsString = qry1->FieldByName("Name")->AsString;
		}
		if (cbcardid->Checked ) {
			dsdg->FieldByName("CardID")->AsString = qry1->FieldByName("CardID")->AsString;
			dsdg->FieldByName("CardSN")->AsString = qry1->FieldByName("CardID")->AsString;
		}
		if (cbsex->Checked ) {
			dsdg->FieldByName("Sex")->AsString = qry1->FieldByName("Sex")->AsString;
		}
		if (cbmobile->Checked ) {
			dsdg->FieldByName("Mobile")->AsString = qry1->FieldByName("Mobile")->AsString;
		}
		if (cbtelphone->Checked ) {
			dsdg->FieldByName("Tel")->AsString = qry1->FieldByName("Tel")->AsString;
		}
		if (cbaddress->Checked ) {
			dsdg->FieldByName("Address")->AsString = qry1->FieldByName("Address")->AsString;
		}
		if (cbcode->Checked ) {
			AnsiString postalcode =  qry1->FieldByName("PostalCode")->AsString ;
			if (postalcode != "") {
				dsdg->FieldByName("PostalCode")->Value  = qry1->FieldByName("PostalCode")->Value ;
			}
		}
		if (cbbirthday->Checked ) {
			dsdg->FieldByName("Birthday")->AsString  = qry1->FieldByName("Birthday")->AsString  ;
		}
		if (cbbalance->Checked ) {
			AnsiString balance =  qry1->FieldByName("Balance")->AsString ;
			if (balance != "") {
				dsdg->FieldByName("Balance")->Value  = qry1->FieldByName("Balance")->Value ;
			}
		}
		if (chtotalcons->Checked ) {
			AnsiString totalcomsumption =  qry1->FieldByName("TotalConsumption")->AsString ;
			if (totalcomsumption != "") {
				dsdg->FieldByName("TotalConsumption")->Value  = qry1->FieldByName("TotalConsumption")->Value ;
			}
		}
		dsdg->Append();
		dsdg->UpdateBatch(arAll);
		sql =  "select max(ID) as id from CUST_MemberInfo";
		aqdetail->Close();
		aqdetail->SQL->Clear();
		aqdetail->SQL->Add(sql);
		aqdetail->Open();
		AnsiString balance =  qry1->FieldByName("Balance")->AsString ;
		if (balance == "") {
			balance = "0";
		}
		int memberid = aqdetail->FieldByName("id")->AsInteger ;
		sql = "insert into CUST_MemberCard(CardID,Type,BalanceAmount,MIfID) values ('" + qry1->FieldByName("CardID")->AsString ;
		sql = sql + "'," + qry1->FieldByName("MemberType")->AsString + "," + balance ;
		sql = sql + "," + IntToStr(memberid) + ")";
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
	lblExcel->Caption = "EXCEL导入完毕！";
	MessageBoxA(0,"数据导入成功！","Excel导入",MB_ICONEXCLAMATION);
	Import= true;
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormMemImport::BtnExitClick(TObject *Sender)
{
	if (Import) {
		Close();
	}else
	{
		MessageBoxA(0,"正在导入中，不能退出！","Excel导入",MB_ICONASTERISK);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormMemImport::cballcheckClick(TObject *Sender)
{
	if (cballcheck->Checked ) {
		cbtype->Checked = true;
		cbname->Checked = true;
		cbcardid->Checked = true;
		cbsex->Checked = true;
		cbmobile->Checked = true;
		cbtelphone->Checked = true;
		cbaddress->Checked = true;
		cbcode->Checked = true;
		cbbirthday->Checked = true;
		cbbalance->Checked = true;
		chtotalcons->Checked = true;
	}
	else
	{
		cbtype->Checked = false;
		cbname->Checked = false;
		cbcardid->Checked = false;
		cbsex->Checked = false;
		cbmobile->Checked = false;
		cbtelphone->Checked = false;
		cbaddress->Checked = false;
		cbcode->Checked = false;
		cbbirthday->Checked = false;
		cbbalance->Checked = false;
		chtotalcons->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMemImport::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
			if (Key == VK_F2) {
		 BtnImport->Click();
	   }

		if (Shift.Contains(ssCtrl)&& Key ==90) {
			WindowState = wsNormal  ;
		}
		if (Shift.Contains(ssCtrl)&& Key ==81  ) {
			BtnExit->Click();
		}

}
//---------------------------------------------------------------------------

