//---------------------------------------------------------------------------

#ifndef RetailNoteFormH
#define RetailNoteFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzChkLst.hpp"
#include "RzDBEdit.hpp"
#include "RzDBList.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzLstBox.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "RzLine.hpp"
#include "RzCmboBx.hpp"
#include "RzDBCmbo.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
#include "RzDBChk.hpp"
#include "RzRadChk.hpp"
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include "MDIChild.h"
//---------------------------------------------------------------------------
class TfrmRetailNote : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TADOQuery *qryRetailNoteName;
	TDataSource *Ds1;
	TDataSource *dsNotePrint;
	TADODataSet *dsetRetailNote;
	TDataSource *ds2;
	TADODataSet *dsPrint;
	TADODataSet *dsretail;
	TDataSource *ds4;
	TPanel *Panel1;
	TRzGroupBox *RzGroupBox4;
	TRzLabel *RzLabel1;
	TRzLabel *RzLabel3;
	TRzLabel *RzLabel4;
	TRzLabel *RzLabel5;
	TRzLine *RzLine1;
	TRzLabel *RzLabel6;
	TRzLabel *RzLabel7;
	TRzLabel *lbl1;
	TRzDBEdit *dbedtWelcomeMessage;
	TRzDBEdit *dbedtAddress;
	TRzDBEdit *dbedtTel;
	TRzDBEdit *dbedtRemarks;
	TRzDBCheckBox *CHKPrice;
	TRzDBCheckBox *CHKBookName;
	TRzDBCheckBox *CHKDiscount;
	TButton *btn1;
	TButton *btn2;
	TRzButton *btn3;
	TRzDBCheckBox *CHKtotalamount;
	TRzDBCheckBox *CHKjine;
	TRzDBCheckBox *CHKCardrec;
	TRzDBCheckBox *CHKtotalhang;
	TLabel *labstorage;
	TButton *Button1;
	TButton *Button2;
	TADOConnection *con;
	TComboBox *dbcbbPort;
	TRzDBCheckBox *chprintmayang;
	TRzDBCheckBox *chprintdiscount;
	TRzDBCheckBox *chkpostcard;
	TRzDBCheckBox *chkyouhuiquan;
	TRadioGroup *rgtype;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall btn2Cick(TObject *Sender);
	void __fastcall btn3Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TfrmRetailNote(TComponent* Owner);
		void Init(TApplication* app, TADOConnection* cn);
		void print();
   int stgid;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRetailNote *frmRetailNote;
//---------------------------------------------------------------------------
#endif
