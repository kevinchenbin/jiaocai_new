//---------------------------------------------------------------------------

#ifndef WsaleH
#define WsaleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include "RzTabs.hpp"
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include "retailprint.h"

//---------------------------------------------------------------------------
class TfrmWsale : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnPrint;
	TRzGroupBox *RzGroupBox1;
	TDateTimePicker *dtpstart;
	TDateTimePicker *dtpend;
	TRzCheckBox *cbend;
	TRzCheckBox *cbstart;
	TRzRadioButton *rbwsale;
	TRzRadioButton *rbback;
	TRzPageControl *pg;
	TRzTabSheet *tsday;
	TRzDBGrid *dgday;
	TRzTabSheet *tsmonth;
	TRzDBGrid *dgmonth;
	TImageList *ImageList1;
	TDataSource *ds1;
	TDataSource *ds2;
	TADOQuery *aqday;
	TADOQuery *aqmonth;
	TRzToolButton *BtnAlignBottom;
	TComboBox *cbstorage;
	TCheckBox *chstorage;
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall pgChange(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
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
	__fastcall TfrmWsale(TComponent* Owner,TADOConnection *cn,int stgid);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
		void Day(AnsiString wherestr);
	void Month(AnsiString wherestr);
	  //	void RPGrid(TRzDBGrid *dg,TQRPGrid *PRdg );
	String Disc;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWsale *frmWsale;
//---------------------------------------------------------------------------
#endif
