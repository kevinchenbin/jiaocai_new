//---------------------------------------------------------------------------

#ifndef settypressH
#define settypressH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmsettyperss : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TCheckBox *chprice;
	TCheckBox *chpress;
	TEdit *edprice;
	TEdit *edpress;
	TComboBox *cbpress;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TADOConnection *con;
	TADOQuery *aq;
	TCheckBox *chisbn;
	TEdit *edisbn;
	TCheckBox *chname;
	TEdit *edname;
	TCheckBox *chauthor;
	TEdit *edauthor;
	TCheckBox *chpresscount;
	TEdit *edpresscount;
	void __fastcall edpriceKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edpriceChange(TObject *Sender);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall edisbnChange(TObject *Sender);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall edauthorChange(TObject *Sender);
	void __fastcall edpresscountChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmsettyperss(TComponent* Owner,TADOConnection *cn);
	float price;
	AnsiString ISBN,Name,Author,PressName,PressCount;
	int pressid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsettyperss *frmsettyperss;
//---------------------------------------------------------------------------
#endif
