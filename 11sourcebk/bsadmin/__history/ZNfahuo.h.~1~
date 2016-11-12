//---------------------------------------------------------------------------

#ifndef ZNfahuoH
#define ZNfahuoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include "MDIChild.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

//---------------------------------------------------------------------------
class TfrmZNfahuo : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TADOQuery *aq;
	TADOCommand *cmdAddNtHeader;
	TADOCommand *cmdAddNote;
	TADOQuery *query;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmZNfahuo(TComponent* Owner);
	LandInfo linfo;
	void Init(LandInfo* li);
	int groupid,sgheaderid,firstfahuo,confirmfahuo,sgfirsthid,headgroupid;
	bool detail;
	AnsiString returncode;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmZNfahuo *frmZNfahuo;
//---------------------------------------------------------------------------
#endif
