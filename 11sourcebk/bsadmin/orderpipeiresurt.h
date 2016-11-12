//---------------------------------------------------------------------------

#ifndef orderpipeiresurtH
#define orderpipeiresurtH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "pdtypes.h"
#include <DB.hpp>
#include <ADODB.hpp>
#include "RzPanel.hpp"
#include <Buttons.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
//---------------------------------------------------------------------------
class Tfrmorderresurt : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGridEh *DBGridEh1;
	TDataSource *ds;
	TADOQuery *aq;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TADOQuery *aquery;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmorderresurt(TComponent* Owner,TADOQuery *query);
	int groupid;
	void firstcreate();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmorderresurt *frmorderresurt;
//---------------------------------------------------------------------------
#endif
