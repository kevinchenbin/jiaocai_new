//---------------------------------------------------------------------------

#ifndef UnitlockH
#define UnitlockH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmlock : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TCheckBox *sadd;
	TCheckBox *smodify;
	TGroupBox *GroupBox2;
	TCheckBox *cadd;
	TCheckBox *cmodify;
	TCheckBox *cdel;
	TGroupBox *GroupBox3;
	TCheckBox *sdel;
	TCheckBox *badd;
	TCheckBox *bmodify;
	TCheckBox *bdel;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TADOQuery *aq;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:	// User declarations
       int stgid;
public:		// User declarations
	__fastcall Tfrmlock(TComponent* Owner,TADOConnection *fcn,int fstgid);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmlock *frmlock;
//---------------------------------------------------------------------------
#endif
