//---------------------------------------------------------------------------

#ifndef fenleitypeH
#define fenleitypeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmfenleitype : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *query;
	TSaveDialog *filepath;
	TADOQuery *aquery;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmfenleitype(TComponent* Owner,TADOQuery *aq,int headerid);
	bool DbgridToExcel(TDBGrid* dbg);
	int count;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmfenleitype *frmfenleitype;
//---------------------------------------------------------------------------
#endif
