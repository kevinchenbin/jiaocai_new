//---------------------------------------------------------------------------

#ifndef StockanalysisH
#define StockanalysisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzCmboBx.hpp"
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzRadChk.hpp"
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmstockanalysis : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnPrintPreview;
	TPanel *Panel4;
	TLabel *Label2;
	TDataSource *ds;
	TADOQuery *aq;
	TLabel *Label1;
	TEdit *edittotal;
	TRzToolButton *BtnAlignBottom;
	TLabel *Label3;
	TEdit *edtotalmayang;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *edtotalshiyang;
	TSaveDialog *savedlg;
	TPanel *Panel3;
	TRzDBGrid *dg;
	TGroupBox *GroupBox1;
	TDateTimePicker *dtpstart;
	TDateTimePicker *dtpend;
	TRzCheckBox *cbend;
	TRzCheckBox *cbstart;
	TEdit *edbook;
	TComboBox *cbtype;
	TComboBox *cbsupplier;
	TComboBox *cbstact;
	TComboBox *cbstorage;
	TCheckBox *chstorage;
	TCheckBox *chisbn;
	TEdit *edname;
	TCheckBox *chname;
	TCheckBox *chtype;
	TCheckBox *chstack;
	TCheckBox *chsupplier;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnPrintPreviewClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall dgTitleClick(TColumn *Column);
	void __fastcall cbsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbstartKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtpstartKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbendKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtpendKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbstactKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbstorageSelect(TObject *Sender);
	void __fastcall ednameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edbookKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edbookChange(TObject *Sender);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall cbsupplierChange(TObject *Sender);
	void __fastcall cbtypeChange(TObject *Sender);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall cbstactChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
   //	void dgcreate(TADOQuery *aq,TRzDBGrid * dg);

private:	// User declarations
	void dgcolumn(TADOQuery *aq,TRzDBGrid *dg);
	void TypeQuery(String wherestr);
	void ReadyData();
	TADOConnection *fcon;
	int fstgid;
public:		// User declarations
	__fastcall Tfrmstockanalysis(TComponent* Owner,TADOConnection *cn,int stgid);
	bool DbgridToExcel(TRzDBGrid* dbg);

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmstockanalysis *frmstockanalysis;
//---------------------------------------------------------------------------
#endif
