//---------------------------------------------------------------------------

#ifndef procureheaderH
#define procureheaderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "DBCtrlsEh.hpp"
#include <Mask.hpp>
#include <Buttons.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class Tfrmprocureheader : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TCheckBox *chprocure;
	TEdit *edprocurecode;
	TCheckBox *chsupplier;
	TEdit *edquery;
	TComboBox *cbsupplier;
	TCheckBox *chstart;
	TDBDateTimeEditEh *dtstart;
	TCheckBox *chend;
	TDBDateTimeEditEh *dtend;
	TSpeedButton *SpeedButton1;
	TDataSource *ds1;
	TDataSource *ds2;
	TADOQuery *aq1;
	TADOQuery *aq2;
	TADOQuery *aq;
	TPopupMenu *pqpm;
	TMenuItem *N1;
	TSpeedButton *SpeedButton3;
	TDBGrid *DBGrid1;
	TPopupMenu *pm;
	TMenuItem *N2;
	TDBGrid *DBGrid2;
	TSpeedButton *SpeedButton2;
	TCheckBox *chznprocure;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmprocureheader(TComponent* Owner);
	LandInfo linfo;
	void Init(LandInfo* li);
	int groupid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmprocureheader *frmprocureheader;
//---------------------------------------------------------------------------
#endif
