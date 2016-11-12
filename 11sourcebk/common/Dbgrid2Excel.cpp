//---------------------------------------------------------------------
#pragma hdrstop

#include "Dbgrid2Excel.h"
//---------------------------------------------------------------------
Dbgrid2Excel::Dbgrid2Excel(TRzDBGrid* dbg)
:m_dbg(dbg)
{}

Dbgrid2Excel::DbgridToExcel(TRzDBGrid* dbg)
{
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=1;i< t2+1 ;i++)
	{
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			v.OlePropertyGet("Cells",i,j).OlePropertySet("Value",dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString .c_str() );  // AsString .c_str()
		}
		dbg->DataSource ->DataSet ->Next() ;
	}

}

