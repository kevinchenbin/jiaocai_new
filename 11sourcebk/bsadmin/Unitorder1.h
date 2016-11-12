//---------------------------------------------------------------------------

#ifndef Unitorder1H
#define Unitorder1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmunitorder1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnSave;
	TDBGrid *DBGrid1;
	TADOConnection *fcon;
	TSaveDialog *savedlg;
	TADOQuery *query;
	TDataSource *ds;
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall BtnExportClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmunitorder1(TComponent* Owner,TADOConnection *con,int headerid);
	bool DbgridToExcel(TDBGrid* dbg);
	AnsiString rkcode;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmunitorder1 *frmunitorder1;
//---------------------------------------------------------------------------
#endif
