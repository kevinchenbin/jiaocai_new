//---------------------------------------------------------------------------

#ifndef bsorderH
#define bsorderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzRadChk.hpp"
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "Chart.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include "Series.hpp"
//---------------------------------------------------------------------------
class Tfrmorder : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnExit;
	TPanel *Panel2;
	TADOQuery *aquery;
	TDataSource *ds;
	TADOStoredProc *dsp;
	TADOCommand *acd;
	TADOQuery *aqdisplay;
	TPanel *Panel1;
	TRadioGroup *rgtype;
	TDBGridEh *dg;
	TCheckBox *chstorage;
	TComboBox *cbstorage;
	TDateTimePicker *dtpstart;
	TRzCheckBox *cbstart;
	TDateTimePicker *dtpend;
	TRzCheckBox *cbend;
	TRzToolButton *BtnAlignBottom;
	TRadioGroup *rgstyle;
	TRadioGroup *rgkind;
	TLabel *Label1;
	TRzSpinEdit *senum;
	TLabel *Label2;
	TChart *Chart1;
	TBarSeries *Series1;
	TRadioGroup *rgviewstyle;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	bool __fastcall DbgridToExcel(TDBGridEh* dbg);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dgTitleClick(TColumnEh *Column);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
private:	// User declarations
	TADOConnection *fcon;
	String StartTime,EndTime;
public:		// User declarations
	__fastcall Tfrmorder(TComponent* Owner,TADOConnection *con,int stgid);
	void Query();
	String Disc;
	AnsiString storageformat,retaiformat,saleformat;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmorder *frmorder;
//---------------------------------------------------------------------------
#endif
