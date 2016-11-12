//---------------------------------------------------------------------------

#ifndef BookQueryH
#define BookQueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzCmboBx.hpp"
#include "RzEdit.hpp"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "ModalDialog.h"
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>

//---------------------------------------------------------------------------
class TfrmBookQuery : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TEdit *edisbn;
	TRzButton *btOK;
	TRzButton *btConcel;
	TADOConnection *fcon;
	TCheckBox *chpress;
	TComboBox *cbpress;
	TEdit *edpress;
	TCheckBox *chtype;
	TComboBox *cbtype;
	TEdit *edtype;
	TCheckBox *chisbn;
	TEdit *edname;
	TCheckBox *chname;
	TEdit *edprice;
	TCheckBox *chprice;
	TEdit *edauthor;
	TCheckBox *chauthor;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btOKClick(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edisbnChange(TObject *Sender);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall edpriceChange(TObject *Sender);
	void __fastcall edauthorChange(TObject *Sender);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall cbtypeChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmBookQuery(TComponent* Owner,TADOConnection *con);
	AnsiString getcontion();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBookQuery *frmBookQuery;
//---------------------------------------------------------------------------
#endif
