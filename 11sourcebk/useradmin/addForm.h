//---------------------------------------------------------------------------

#ifndef addFormH
#define addFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ModalDialog.h"
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrmadd : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TADOCommand *cmd;
	TDataSource *ds1;
	TADODataSet *dsUserGroup;
	TEdit *edt1;
	TLabel *Label1;
	void __fastcall btnOkClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmadd(TComponent* Owner);
	void Init(LandInfo* li);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmadd *frmadd;
//---------------------------------------------------------------------------
#endif
