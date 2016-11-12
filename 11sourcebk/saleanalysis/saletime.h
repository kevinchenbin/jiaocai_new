//---------------------------------------------------------------------------

#ifndef saletimeH
#define saletimeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include "RzGrids.hpp"
//---------------------------------------------------------------------------
class Tfrmsaletime : public TForm
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
	TImageList *ImageList1;
	TDataSource *ds1;
	TADOQuery *aqday;
	TPanel *Panel2;
	TLabel *Label2;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *editfix;
	TEdit *editdis;
	TEdit *editamount;
	TPanel *Panel3;
	TADOQuery *aqday1;
	TRzStringGrid *strg;
	TRzToolButton *BtnAlignBottom;
	TComboBox *cbstorage;
	TCheckBox *chstorage;
	TLabel *Label1;
	TLabel *Label3;
	TEdit *edprice;
	TEdit *edprofite;
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
private:	// User declarations
   void Query(AnsiString sqlstr);
   String retaiformat,saleformat;
public:		// User declarations
	__fastcall Tfrmsaletime(TComponent* Owner,TADOConnection *cn,int stgid);
	bool __fastcall DbgridToExcel(TRzStringGrid* dbg);
	String Disc;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsaletime *frmsaletime;
//---------------------------------------------------------------------------
#endif
