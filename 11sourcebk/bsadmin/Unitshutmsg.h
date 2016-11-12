//---------------------------------------------------------------------------

#ifndef UnitshutmsgH
#define UnitshutmsgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrmshortmessage : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TButton *bsave;
	TButton *Button2;
	TMemo *memo1;
	TMemo *Memo2;
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmshortmessage(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmshortmessage *frmshortmessage;
//---------------------------------------------------------------------------
#endif
