//---------------------------------------------------------------------------

#ifndef SetTongyiH
#define SetTongyiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TfrmSetTongyi : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TCheckBox *chyjpxdiscount;
	TCheckBox *chyilsdiscount;
	TRzNumericEdit *edyjpx;
	TRzNumericEdit *edyjls;
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmSetTongyi(TComponent* Owner);
	bool Getpxdiscount(float& pxdiscount);
	bool Getlsdiscount(float& lsdiscount);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSetTongyi *frmSetTongyi;
//---------------------------------------------------------------------------
#endif
