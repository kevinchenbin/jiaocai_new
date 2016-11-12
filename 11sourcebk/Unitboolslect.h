//---------------------------------------------------------------------------

#ifndef UnitboolslectH
#define UnitboolslectH
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
#include <DB.hpp>
#include <ADODB.hpp>
//---------------------------------------------------------------------------
class Tfrmselectbook : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TRzToolButton *Btn;
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *aq;
	void __fastcall BtnClick(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall DBGrid1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmselectbook(TComponent* Owner,TADOQuery *query);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmselectbook *frmselectbook;
//---------------------------------------------------------------------------
#endif
