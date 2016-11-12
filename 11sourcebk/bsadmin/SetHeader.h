//---------------------------------------------------------------------------

#ifndef SetHeaderH
#define SetHeaderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmSetHeader : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *edheadername;
	TButton *Btok;
	TButton *btconcel;
	void __fastcall btconcelClick(TObject *Sender);
	void __fastcall BtokClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmSetHeader(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSetHeader *frmSetHeader;
//---------------------------------------------------------------------------
#endif
