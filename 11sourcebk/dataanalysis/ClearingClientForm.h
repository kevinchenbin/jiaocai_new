//---------------------------------------------------------------------------

#ifndef ClearingClientFormH
#define ClearingClientFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzGrids.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ImgList.hpp>
#include <Buttons.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmClearingClient : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton1;
	TADODataSet *dsCUS;
	TDataSource *ds1;
	TADODataSet *dsSupply;
	TDataSource *ds3;
	TADODataSet *dsSale;
	TDataSource *ds5;
	TADODataSet *dschecked;
	TDataSource *ds6;
	TADODataSet *dsReturn;
	TDataSource *ds4;
	TDataSource *ds2;
	TADODataSet *dsStock;
	TDataSource *ds7;
	TADODataSet *dsWholesale;
	TImageList *ImageList1;
	TPanel *Panel1;
	TRzToolButton *BtnAlignBottom;
	TDataSource *ds;
	TADOQuery *query;
	TDBGridEh *dg;
	TGroupBox *GroupBox1;
	TRzLabel *lbl3;
	TSpeedButton *spselectClient;
	TCheckBox *cbend;
	TCheckBox *cbstart;
	TDateTimePicker *dtp1;
	TDateTimePicker *dtp2;
	TCheckBox *chstorage;
	TComboBox *cbstorage;
	TEdit *edclient;
	TEdit *edtclient;
	TCheckBox *chpress;
	TComboBox *cpress;
	TCheckBox *chtype;
	TComboBox *cbtype;
	TCheckBox *chisbn;
	TEdit *edisbn;
	TCheckBox *chname;
	TEdit *edname;
	TRadioGroup *rg;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall dgTitleClick(TColumnEh *Column);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtp1Change(TObject *Sender);
	void __fastcall dtp2Change(TObject *Sender);
	void __fastcall cpressChange(TObject *Sender);
	void __fastcall edisbnChange(TObject *Sender);
	void __fastcall cbtypeChange(TObject *Sender);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
private:	// User declarations
	TADOConnection *fcon;
	String format;
public:		// User declarations
	__fastcall TfrmClearingClient(TComponent* Owner);
		void   Init(TApplication* app, TADOConnection* con);
	int type,stgid,ClientID;
	void Query();
	void ClientView();
        bool DbgridToExcel(TDBGridEh* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmClearingClient *frmClearingClient;
//---------------------------------------------------------------------------
#endif
