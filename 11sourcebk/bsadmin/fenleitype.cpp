//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fenleitype.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmfenleitype *frmfenleitype;
//---------------------------------------------------------------------------
__fastcall Tfrmfenleitype::Tfrmfenleitype(TComponent* Owner,TADOQuery *aq,int headerid)
	: TForm(Owner)
{
	ds->DataSet = aq;
	aquery->Connection = aq->Connection ;
	query=aq;
	/*AnsiString sql  = "select '合计',null,null,sum(BS_ZN_ProcureNote.amount) as amount,null,null,null,null,null,null,null,null,null,'总合计',sum(BS_ZN_ProcureNote.FixedPrice) as FixedPrice,sum(BS_ZN_ProcureNote.DiscountedPrice) as DiscountedPrice,0 as totalamount "
			"from BS_ZN_ProcureNote where ZNProcureNtHeaderID = " + IntToStr(headerid);
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();   */
	DBGrid1->OnDrawColumnCell=DBGrid1DrawColumnCell;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfenleitype::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfenleitype::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfenleitype::BtnExportClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
        return;
	}
	query->First();
	count = 0;
	while (count < query->RecordCount-1 )
	{
		//query->MoveBy(count);
		DbgridToExcel(DBGrid1);
	}
}
//---------------------------------------------------------------------------
//Excel导出函数
bool Tfrmfenleitype::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString temptext ,ExcelFileName;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	Variant     v,vSheet,Wb;
	temptext = query->FieldByName("SupplierName")->AsString ;
	if (temptext == "") {
    	temptext = "新书";
	}
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
	
	v.OlePropertyGet("Cells",2,5).OlePropertySet("Value",temptext .c_str() );
	n=2;

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
	//dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					t1++;
					temptext = "'"+ query->FieldByName("ISBN")->AsAnsiString ;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
				else
				{
                	t1++;
					temptext = query ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
			}
		}
		if (query->FieldByName("typename")->AsString == "合计"  ) {
        	query->Next();
			count++;
			break;
		}
		query->Next();
		count++;
	}

	try {
		Wb.OleProcedure("SaveAs",ExcelFileName.c_str() );//保存表格
	} catch (...) {
	}
	Wb.OleProcedure("Close");//关闭表格
	v.OleFunction("Quit");//退出Excel
	return false;
}

//---------------------------------------------------------------------------

void __fastcall Tfrmfenleitype::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (DBGrid1->DataSource->DataSet->FieldByName("typename")->AsString  == "合计" ) {
		//DBGrid1->Canvas->Brush->Color = clFuchsia ;
		DBGrid1->Canvas->FillRect(Rect);
		DBGrid1->Canvas->Font->Color = clBlue ;
		DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;
		DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfenleitype::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   	if (Key == VK_F3) {
		BtnExport->Click();
	}
		if (Shift.Contains(ssCtrl)&& Key ==81  ) {
	   BtnExit->Click();
	}

}
//---------------------------------------------------------------------------

