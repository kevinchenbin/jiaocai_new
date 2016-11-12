//---------------------------------------------------------------------------

#ifndef alteramountH
#define alteramountH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrmalteramount : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *ednum;
	void __fastcall ednumKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmalteramount(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmalteramount *frmalteramount;
//---------------------------------------------------------------------------
#endif
