//---------------------------------------------------------------------------

#ifndef StationeryAdminFormH
#define StationeryAdminFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzCmboBx.hpp"
#include "RzDBCmbo.hpp"
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzRadChk.hpp"
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include "RzSpnEdt.hpp"
#include "RzDBGrid.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "MDIChild.h"
//---------------------------------------------------------------------------
class TfrmStationeryAdmin : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzCheckBox *chckbxInput;
	TRzLabel *lbl1;
	TRzLabel *lbl2;
	TRzLabel *lbl3;
	TRzLabel *lbl4;
	TRzLabel *lbl5;
	TRzLabel *lbl6;
	TRzLabel *lbl7;
	TRzLabel *lbl8;
	TRzLabel *lbl9;
	TRzLabel *lbl10;
	TRzLabel *lbl11;
	TRzDBEdit *dbedtBarcode;
	TRzDBEdit *dbedtName;
	TRzDBEdit *dbedtPrice;
	TRzDBEdit *dbedt4;
	TRzDBEdit *dbedt5;
	TRzSpinEdit *edt1;
	TRzSpinEdit *edt2;
	TRzSpinEdit *edt3;
	TRzSpinEdit *edt4;
	TRzSpinEdit *edt5;
	TRzDBGrid *rzdbgrdPress1;
	TRzToolButton *btnExit1;
	TRzToolButton *btnExit2;
	TRzToolButton *btnExit3;
	TADODataSet *dsetStationery;
	TDataSource *dsrcStationery;
	TADOTable *tbl1;
	TDataSource *dsrc1;
	TRzDBLookupComboBox *cbb2;
	TRzDBEdit *dbedtUserDefCode;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall btn2Click(TObject *Sender);
	void __fastcall btn4Click(TObject *Sender);
	void __fastcall btnExit1Click(TObject *Sender);
	void __fastcall btnExit2Click(TObject *Sender);
	void __fastcall btnExit3Click(TObject *Sender);
	void __fastcall cbb2KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbedtBarcodeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbedtNameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbedtPriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbedt4KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbedt5KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbb1KeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
void OnHotKeyPress(DWORD vkCode);
public:		// User declarations
	__fastcall TfrmStationeryAdmin(TComponent* Owner);
	char TfrmStationeryAdmin::GetPYIndexChar(char *str);
	void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStationeryAdmin *frmStationeryAdmin;
//---------------------------------------------------------------------------
#endif
