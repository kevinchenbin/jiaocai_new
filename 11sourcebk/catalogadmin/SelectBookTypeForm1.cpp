//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectBookTypeForm1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma link "SelectBookTypeForm"
#pragma link "RzShellDialogs"
#pragma link "RzRadChk"
#pragma link "RzRadGrp"
#pragma link "RzPrgres"
#pragma resource "*.dfm"
TfrmSelectBookType1 *frmSelectBookType1;
//---------------------------------------------------------------------------
__fastcall TfrmSelectBookType1::TfrmSelectBookType1(TComponent* Owner)
	: TfrmSelectBookType(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSelectBookType1::btn2Click(TObject *Sender)
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

void __fastcall TfrmSelectBookType1::btnExit1Click(TObject *Sender)
{
//	Variant my_excel,all_workbooks,my_workbook, my_worksheet;
//	my_excel = CreateOleObject("excel.Application");
//	all_workbooks = my_excel.OlePropertyGet("WorkBooks");
//	Procedure Open("Open");
//	all_workbooks.Exec(Open<<opndlgExcelPath->FileName );
//	my_workbook = my_excel.OlePropertyGet("ActiveWorkbook");
//	my_worksheet = my_workbook.OlePropertyGet("ActiveSheet");
//  String sql = "select * from [11$]";
	if(edtExcelPath->Text == "")
	return;
	else
	{

		ShowMessage("确定要导入？");
		lblExcel->Visible = true;
	}
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
	String sql = "select * from [11$]" ;
//	sql = sql + vSheet;
//	sql = sql + "$]";
	String str = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	str = str + edtExcelPath->Text ;
	str = str + ";Mode=Read;Extended Properties=Excel 8.0;Persist Security Info=False";
	 //C:\\Documents and Settings\\Administrator\\桌面\\11.xls;Mode=Read;Extended Properties=Excel 8.0;Persist Security Info=False";

	//con1->Provider = "Microsoft.Jet.OLEDB.4.0";
	try
	{
		con1->ConnectionString =  str ;
	}
	catch(...)
	{
		ShowMessage("该数据已经导入！");
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
		ShowMessage("数据源配置错误！");
	}
	qry1->Connection = con1;
	qry1->Active = false;
	qry1->SQL->Clear();
	qry1->SQL ->Add(sql);
	qry1->Active = true;
	ds1->DataSet = qry1;

   //	int j = qry1->DataSource ->DataSet ->RecordCount ;

	for(int i=1;i<=5;i++)
	{
		qry1->Active = true;
		dset1->Active = true;
		dset1->Append();
		if(chckbxBarcode->Checked )
		dset1->FieldByName("Barcode")->Value = qry1->FieldByName("Barcode")->Value ;
		if(chckbxISBN->Checked )
		dset1->FieldByName("ISBN")->Value = qry1->FieldByName("ISBN")->Value ;
		if(chckbxName->Checked )
		dset1->FieldByName("Name")->Value = qry1->FieldByName("Name")->Value ;
		if(chckbxAuthor->Checked )
		dset1->FieldByName("Author")->Value = qry1->FieldByName("Author")->Value ;
		if(chckbxUserDefCode->Checked )
		dset1->FieldByName("UserDefCode")->Value = qry1->FieldByName("UserDefCode")->Value ;
		if(chckbxDate->Checked )
		dset1->FieldByName("Date")->Value = qry1->FieldByName("Date")->Value ;
//		if(chckbxPress->Checked )
//		dset1->FieldByName("Press")->Value = qry1->DataSource ->DataSet ->FieldByName("Press")->Value ;
		if(chckbxPrice->Checked )
		dset1->FieldByName("Price")->Value = qry1->FieldByName("Price")->Value ;
		qry1->RecNo ++;
		//prgrsbrExcel->
	}

	ShowMessage("数据导入成功！");
	lblExcel->Visible = false;
//	Wb.OleProcedure("Save");
//	Wb.OleProcedure("Close");
//	vExcelApp.OleFunction("Quit");
	// qry1->DataSource ->DataSet ->RecNo = 1;


//		int j= qry1->DataSource ->DataSet ->RecordCount ;// ->RecordCount;
//	for(int i=1;i<=2;i++ )
//	{
//
//		dsetCatlog->Active = true;
//		dsetCatlog->Append();
//		dsetCatlog->FieldByName("ISBN")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("ISBN")->Value ;
//		dsetCatlog->FieldByName("Name")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Name")->Value ;
//		dsetCatlog->FieldByName("Barcode")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Barcode")->Value ;
//		dsetCatlog->FieldByName("UserDefCode")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("UserDefCode")->Value ;
//		dsetCatlog->FieldByName("Price")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Price")->Value ;
//		dbgrdExcelCatlog->DataSource->DataSet ->RecNo++;
//	}
//	ShowMessage("快来看啊，数据导完了！");
//	dbgrdExcelCatlog->DataSource->DataSet->RecNo=1;
//	con1->ConnectionString =  "Provider=Microsoft.Jet.OLEDB.4.0;Mode=Read;Extended Properties=Excel 8.0;Persist Security Info=False"
}
//---------------------------------------------------------------------------


void __fastcall TfrmSelectBookType1::FormClose(TObject *Sender, TCloseAction &Action)

{
	//TfrmBookTypeAdmin::FormClose(Sender, Action);
	Action = caFree;
}
//---------------------------------------------------------------------------

