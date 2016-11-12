//---------------------------------------------------------------------------

#ifndef QueryDanHaoH
#define QueryDanHaoH
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
#include "pdtypes.h"
//---------------------------------------------------------------------------
class TfrmQuery : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TComboBox *cbstore;
	TRadioButton *rb1;
	TRadioButton *rb2;
	TRzSpinEdit *sefrom;
	TRzSpinEdit *seto;
	TDateTimePicker *dtfrom;
	TLabel *Label2;
	TSpeedButton *spok;
	TSpeedButton *spcancel;
	TDateTimePicker *dtto;
	TLabel *Label3;
	TADOQuery *aq;
	TEdit *editstorehao;
	void __fastcall sefromExit(TObject *Sender);
	void __fastcall cbstoreChange(TObject *Sender);
	void __fastcall dtfromExit(TObject *Sender);
	void __fastcall spcancelClick(TObject *Sender);
	void __fastcall spokClick(TObject *Sender);
	void __fastcall sefromKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmQuery(TComponent* Owner);
	void Init(LandInfo* li);
	LandInfo linfo;
	int Max,Min;
	DATE FMax,TMin;
	bool RDanhao;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmQuery *frmQuery;
//---------------------------------------------------------------------------
#endif
