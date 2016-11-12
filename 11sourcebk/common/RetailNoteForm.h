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
//---------------------------------------------------------------------------
class TfrmRetailNote : public TForm
{
__published:	// IDE-managed Components
	TRzGroupBox *RzGroupBox4;
	TRzLabel *RzLabel2;
	TRzDBEdit *dbedtTitle;
	TRzGroupBox *RzGroupBox1;
	TRzLine *RzLine2;
	TRzLabel *RzLabel1;
	TRzDBEdit *dbedtWelcomeMessage;
	TRzLabel *RzLabel3;
	TRzDBEdit *dbedtAddress;
	TRzLabel *RzLabel4;
	TRzDBEdit *dbedtTel;
	TRzDBEdit *dbedtRemarks;
	TRzLabel *RzLabel5;
	TRzLine *RzLine1;
	TRzLabel *RzLabel6;
	TRzDBComboBox *dbcbbPort;
	TADOQuery *qryRetailNoteName;
	TDataSource *Ds1;
	TDataSource *dsNotePrint;
	TADODataSet *dsetRetailNote;
	TListBox *LBRetailNote;
	TRzLabel *RzLabel7;
	TRzDBCheckBox *CHKPrice;
	TRzDBCheckBox *CHKISBN;
	TRzDBCheckBox *CHKBookName;
	TRzDBCheckBox *CHKDiscount;
	TButton *btn1;
	TDataSource *ds2;
	TADODataSet *dsPrint;
	TButton *btn2;
	TRzLabel *lbl1;
	TADODataSet *dsretail;
	TDataSource *ds4;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall LBRetailNoteClick(TObject *Sender);
	void __fastcall LBRetailNoteDblClick(TObject *Sender);
	void __fastcall LBRetailNoteKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall btn2Click(TObject *Sender);

private:	// User declarations
           TADOConnection* con1;
public:		// User declarations
	__fastcall TfrmRetailNote(TComponent* Owner);
		void Init(TADOConnection* con);
		void print(String ID,TADOConnection* con);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRetailNote *frmRetailNote;
//---------------------------------------------------------------------------
#endif
