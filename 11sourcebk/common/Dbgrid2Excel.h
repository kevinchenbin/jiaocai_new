//---------------------------------------------------------------------------

#ifndef Dbgrid2ExcelH
#define Dbgrid2ExcelH

#include <vcl.h>

//---------------------------------------------------------------------------
class Dbgrid2Excel
{
public:
	Dbgrid2Excel(TRzDBGrid* dbg);
	void DbgridToExcel(TRzDBGrid* dbg);
private:
	TRzDBGrid* m_dbg;

};


#endif