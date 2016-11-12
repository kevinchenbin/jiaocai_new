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
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSpeedButton *spOK;
	TRadioGroup *RadioGroup1;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TEdit *edtvalue;
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
