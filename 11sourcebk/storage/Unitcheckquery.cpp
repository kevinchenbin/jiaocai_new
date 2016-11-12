//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitcheckquery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmcheck *frmcheck;
//---------------------------------------------------------------------------
__fastcall Tfrmcheck::Tfrmcheck(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
  querydetail->Connection = cn;
  queryhead->Connection = cn;
  dtbegin->Date = Date();
  dtend->Date = Date();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcheck::BtnViewClick(TObject *Sender)
{
   AnsiString sql;
   AnsiString betime,entime;
   betime = DateToStr(dtbegin->Date);
   entime = DateToStr(dtend->Date);
   betime = betime + " 00:00:00";
   entime = entime + " 23:59:59";
   sql = "select A.checkstockNum,convert(varchar(20),A.checkdate,23) as date,B.name as lockname,U.name,A.bk,sum(ShouldAmount) as ShouldAmount,sum(ActualAmount) as ActualAmount,sum(Balance) as Balance  from STK_CheckStockinfo A  "
		 " left join STK_BookstackInfo B ON A.checkstocklocal =  B.ID "
		 " left join STK_StockInventories on A.checkstockNum = STK_StockInventories.NoteCode"
		 " left join sys_user U ON A.employ = U.ID where checkdate between  '"+betime+"' and '" + entime + "' group by A.checkstockNum,A.checkdate,B.name,U.name,A.bk";
   queryhead->Close();
   queryhead->SQL->Clear();
   queryhead->SQL->Add(sql);
   queryhead->Open();
   int pandianamount = 0,totalblance = 0;
   queryhead->DisableControls();
   while (!queryhead->Eof )
   {
		pandianamount = pandianamount + queryhead->FieldByName("ActualAmount")->AsInteger ;
		totalblance = totalblance + queryhead->FieldByName("Balance")->AsInteger ;
		queryhead->Next();
   }
   queryhead->EnableControls();
   edtotalpandian->Text = IntToStr(pandianamount);
   edtotalblance->Text = IntToStr(totalblance);

}
//---------------------------------------------------------------------------
void __fastcall Tfrmcheck::dgheadCellClick(TColumn *Column)
{
   AnsiString sql;
   AnsiString notecode;
   notecode = queryhead->FieldByName("checkstockNum")->AsAnsiString ;
   sql = "select STK_StockInventories.*,BS_BookCatalog.Price from STK_StockInventories left join STK_BookInfo on STK_StockInventories.STK_BookInfoID = STK_BookInfo.ID left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.id where STK_StockInventories.NoteCode = '"+notecode+"'";
   querydetail->Close();
   querydetail->SQL->Clear();
   querydetail->SQL->Add(sql);
   querydetail->Open();

}
//---------------------------------------------------------------------------
void __fastcall Tfrmcheck::BtnExitClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcheck::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree ;
}
//---------------------------------------------------------------------------
bool Tfrmcheck::DbgridToExcel(TDBGrid* dbg)
{
 AnsiString temptext  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		MessageBox(0,"没有数据！","错误确认" ,MB_OK);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	v.OlePropertyGet("Cells",1,4).OlePropertySet("Value","盘点单" );
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","盘点单号" );
	temptext = "'"+ queryhead->FieldByName("checkstockNum")->AsAnsiString  ;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );

	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","库位" );
	temptext = "'"+ queryhead->FieldByName("lockname")->AsAnsiString ;
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());

	v.OlePropertyGet("Cells",3,6).OlePropertySet("Value","日期" );
	temptext = "'" + queryhead->FieldByName("date")->AsAnsiString ;
	v.OlePropertyGet("Cells",3,7).OlePropertySet("Value",temptext .c_str());

		v.OlePropertyGet("Cells",3,8).OlePropertySet("Value","操作员" );
	temptext = "'" + queryhead->FieldByName("name")->AsAnsiString ;
	v.OlePropertyGet("Cells",3,9).OlePropertySet("Value",temptext .c_str());

	v.OlePropertyGet("Cells",4,1).OlePropertySet("Value","备注" );
	temptext = "'"+ queryhead->FieldByName("date")->AsAnsiString ;
	v.OlePropertyGet("Cells",4,2).OlePropertySet("Value",temptext .c_str());

	n=4;

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

	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}
	return false;



}
//---------------------------------------------------------------------------
void __fastcall Tfrmcheck::BtnExportClick(TObject *Sender)
{
  DbgridToExcel(dgdetail);
}
//---------------------------------------------------------------------------
