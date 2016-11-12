//---------------------------------------------------------------------------

#ifndef pdutilH
#define pdutilH
//---------------------------------------------------------------------------

#include <vcl.h>
#include <ADODB.hpp>
#include "RzDBGrid.hpp"



typedef enum
{
	BSUnknown = 0,
	BSNote = 1,
	BSNoteSendback
}BSMode;
TDateTime GetDBTime(TADOQuery* qry);
String BuildISBNCode(String barcode);
int StringToIsbn(String str,int rs[]);
bool DataSetToExcel(TADODataSet* dset);
bool DataSetToExcel(TDataSet* dset);
bool DbgridToExcel(TRzDBGrid* dbg);
bool DbgridToExcel(TDBGrid* dbg);
String ISBNToBarcode(String ISBN);
#endif
