//---------------------------------------------------------------------------

#ifndef YewutongjiH
#define YewutongjiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ImgList.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tfrmywtongji : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton3;
	TDataSource *ds;
	TPanel *Panel3;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	TDBGridEh *DBGridEh1;
	TADOConnection *fcon;
	TGroupBox *GroupBox1;
	TCheckBox *chsupplier;
	TCheckBox *chpress;
	TDateTimePicker *dtp1;
	TDateTimePicker *dtp2;
	TComboBox *cbsupplier;
	TCheckBox *chtype;
	TComboBox *cbtype;
	TCheckBox *chstart;
	TCheckBox *chend;
	TComboBox *cbpress;
	TCheckBox *chstorage;
	TComboBox *cbstorage;
	TEdit *edsupplier;
	TEdit *edtype;
	TEdit *edpress;
	TLabel *Label1;
	TEdit *edminamount;
	TLabel *Label2;
	TEdit *edmaxamount;
	TCheckBox *chamount;
	TCheckBox *chclient;
	TEdit *edclient;
	TLabel *Label3;
	TSpeedButton *spselectClient;
	TEdit *edtclient;
	TRadioGroup *rg3;
	TRadioGroup *rg1;
	TADOQuery *query;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TRzButton *RzButton3;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGridEh1TitleClick(TColumnEh *Column);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall edsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtp1Change(TObject *Sender);
	void __fastcall dtp1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtp2Change(TObject *Sender);
	void __fastcall RzEdit5KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbsupplierChange(TObject *Sender);
	void __fastcall cbsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbtypeChange(TObject *Sender);
	void __fastcall cbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall edminamountChange(TObject *Sender);
	void __fastcall edtclientChange(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton3Click(TObject *Sender);
private:	// User declarations
		TObject *Sender1;
		String storageformat,retaiformat,saleformat;
public:		// User declarations
	__fastcall Tfrmywtongji(TComponent* Owner);
	int stgid;
	void  Init(TApplication* app, TADOConnection* con);
	bool DbgridToExcel(TDBGridEh* dbg);
	int ClientID;
	void ClientView();
	void Query(int modle);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmywtongji *frmywtongji;
//---------------------------------------------------------------------------
#endif
