//---------------------------------------------------------------------------

#ifndef NotCheckBookH
#define NotCheckBookH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmNotCheckBook : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnPreviewNextPage;
	TRzDBGrid *RzDBGrid1;
	TRzToolButton *BtnImport;
	TADOQuery *ADOQuery1;
	TDataSource *ds;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall BtnPreviewNextPageClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmNotCheckBook(TComponent* Owner,TADOQuery *aquery);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNotCheckBook *frmNotCheckBook;
//---------------------------------------------------------------------------
#endif
