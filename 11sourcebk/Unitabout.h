//---------------------------------------------------------------------------

#ifndef UnitaboutH
#define UnitaboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmAboutsoftware : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmAboutsoftware(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAboutsoftware *frmAboutsoftware;
//---------------------------------------------------------------------------
#endif
