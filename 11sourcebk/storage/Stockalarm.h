//---------------------------------------------------------------------------

#ifndef StockalarmH
#define StockalarmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmalarm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TRzDBGrid *dgalarm;
	TDataSource *ds;
	TADOQuery *aquery;
	TRzToolButton *BtnExport;
	TADOConnection *fcon;
	TRzToolButton *BtnView;
	TRzToolButton *BtnAlignBottom;
	TGroupBox *GroupBox1;
	TCheckBox *chchaochu;
	TEdit *edchaochumin;
	TEdit *edchaochumax;
	TLabel *Label1;
	TCheckBox *chduanque;
	TEdit *edduanquemin;
	TEdit *edduanquemax;
	TLabel *Label2;
	TCheckBox *chsupplier;
	TEdit *edquery;
	TComboBox *cbsupplier;
	TCheckBox *chpress;
	TEdit *edpress;
	TComboBox *cbpress;
	TCheckBox *chtype;
	TComboBox *cbtype;
	TADOQuery *query;
	TLabel *Label3;
	TLabel *Label4;
	TSaveDialog *savedlg;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edchaochuminChange(TObject *Sender);
	void __fastcall edchaochumaxChange(TObject *Sender);
	void __fastcall edduanqueminChange(TObject *Sender);
	void __fastcall edduanquemaxChange(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbsupplierChange(TObject *Sender);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall cbtypeChange(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall cbsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edchaochuminKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edchaochumaxKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edduanqueminKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edduanquemaxKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmalarm(TComponent* Owner,TADOConnection *con,int stgid);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	void Tfrmalarm::Filter();
	int fstgid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmalarm *frmalarm;
//---------------------------------------------------------------------------
#endif
