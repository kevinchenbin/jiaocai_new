//---------------------------------------------------------------------------

#ifndef retailH
#define retailH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzDBGrid.hpp"
#include "RzRadChk.hpp"
#include "RzTabs.hpp"
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>

//---------------------------------------------------------------------------
class Tfrmretail : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnPrint;
	TRzGroupBox *RzGroupBox1;
	TDateTimePicker *dtpstart;
	TDateTimePicker *dtpend;
	TRzCheckBox *cbend;
	TRzCheckBox *cbstart;
	TRzRadioButton *rbretail;
	TRzRadioButton *rbback;
	TRzPageControl *pg;
	TRzTabSheet *tsday;
	TRzTabSheet *tsmonth;
	TRzDBGrid *dgday;
	TRzDBGrid *dgmonth;
	TDataSource *ds1;
	TDataSource *ds2;
	TADOQuery *aqday;
	TADOQuery *aqmonth;
	TRzToolButton *BtnAlignBottom;
	TComboBox *cbstorage;
	TCheckBox *chstorage;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall pgChange(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall dgmonthTitleClick(TColumn *Column);
	void __fastcall dgdayTitleClick(TColumn *Column);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
private:	// User declarations
    BOOL query;
public:		// User declarations
	__fastcall Tfrmretail(TComponent* Owner,TADOConnection *cn,int stgid);
	void Day(AnsiString wherestr);
	void Month(AnsiString wherestr);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	//void RPGrid(TRzDBGrid *dg,TQRPGrid *PRdg );
	String Disc;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmretail *frmretail;
//---------------------------------------------------------------------------
#endif
