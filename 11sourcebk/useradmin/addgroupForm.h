//---------------------------------------------------------------------------

#ifndef addgroupFormH
#define addgroupFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmaddgroup : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TEdit *edt1;
	TButton *btn1;
	TButton *btn2;
	TLabel *Label1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btn2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmaddgroup(TComponent* Owner);
	 void Init(LandInfo* li);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmaddgroup *frmaddgroup;
//---------------------------------------------------------------------------
#endif
