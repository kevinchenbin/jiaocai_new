//---------------------------------------------------------------------------

#ifndef adduserFormH
#define adduserFormH
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
class Tfrmadduser : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TDataSource *ds1;
	TADODataSet *dsUser;
	TADOCommand *cmd;
	TDataSource *ds2;
	TADODataSet *dsGroupID;
	TLabel *lbl1;
	TLabel *lbl2;
	TLabel *lbl3;
	TLabel *lbl4;
	TLabel *lbl5;
	TEdit *edt1;
	TEdit *edt2;
	TEdit *edt3;
	TEdit *edt4;
	void __fastcall btnOkClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
		String str1;
		int Type1;
public:		// User declarations
	__fastcall Tfrmadduser(TComponent* Owner);
		void Init(LandInfo* li);
		void deal(String str,int Type);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmadduser *frmadduser;
//---------------------------------------------------------------------------
#endif
