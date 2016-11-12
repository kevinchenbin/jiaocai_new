//---------------------------------------------------------------------------

#ifndef aboutH
#define aboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class Tfrmabout : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TMemo *Memo1;
	TButton *Button1;
	TImage *Image1;
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmabout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmabout *frmabout;
//---------------------------------------------------------------------------
#endif
