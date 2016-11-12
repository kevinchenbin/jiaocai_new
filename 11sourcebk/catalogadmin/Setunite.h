//---------------------------------------------------------------------------

#ifndef SetuniteH
#define SetuniteH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmSetunite : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *btok;
	TButton *btcancel;
	TGroupBox *GroupBox1;
	TLabel *Label21;
	TLabel *Label22;
	TSpeedButton *btaddtype;
	TSpeedButton *btaddpress;
	TEdit *editprice;
	TComboBox *rcbtype;
	TComboBox *rcbpress;
	TDateTimePicker *datapressday;
	TRzSpinEdit *sedpresscount;
	TEdit *edbook;
	TCheckBox *cbprice;
	TCheckBox *cbtype;
	TCheckBox *cbbook;
	TCheckBox *cbpress;
	TCheckBox *cbpressday;
	TCheckBox *cbpresscount;
	TADOQuery *query;
	void __fastcall cbpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbbookKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edbookKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rcbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rcbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpressdayKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall datapressdayKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpresscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sedpresscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btokClick(TObject *Sender);
	void __fastcall btcancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btaddtypeClick(TObject *Sender);
	void __fastcall btaddpressClick(TObject *Sender);
private:	// User declarations
	TADOConnection *fcon;
public:		// User declarations
	__fastcall TfrmSetunite(TComponent* Owner,TADOConnection *con);
	int Gettypeid();
	int Getpressid();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSetunite *frmSetunite;
//---------------------------------------------------------------------------
#endif
