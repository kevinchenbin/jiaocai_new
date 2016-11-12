//---------------------------------------------------------------------------

#ifndef UnitchaigoufromorderH
#define UnitchaigoufromorderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmchaigoufromorder : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TImage *Image1;
	TImage *Image2;
	TADOQuery *query;
	TADOQuery *aq;
	TADOCommand *cmdAddNote;
	TLabel *Label1;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmchaigoufromorder(TComponent* Owner);
	void Init(LandInfo* li);
	AnsiString head;
	int groupid,sgheaderid,firstfahuo,confirmcaigou,sgfirsthid,feizhengshi;
	bool detail;
	AnsiString returncode;
	LandInfo linfo;
	int AddCaigou();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmchaigoufromorder *frmchaigoufromorder;
//---------------------------------------------------------------------------
#endif
