//---------------------------------------------------------------------------

#ifndef SupplierLocalH
#define SupplierLocalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrmsalecustomer : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRadioGroup *RadioGroup1;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TEdit *edtvalue;
	TSpeedButton *spOK;
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmsalecustomer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsalecustomer *frmsalecustomer;
//---------------------------------------------------------------------------
#endif
