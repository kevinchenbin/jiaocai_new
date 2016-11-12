//---------------------------------------------------------------------------

#ifndef ZNrukuH
#define ZNrukuH
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
class TfrmZNruku : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SpeedButton3;
	TADOQuery *aq;
	TADOCommand *cmdAddNtHeader;
	TADOCommand *cmdAddNote;
	TImage *Image1;
	TImage *Image2;
	TImage *Image4;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmZNruku(TComponent* Owner);
	LandInfo linfo;
	void Init(LandInfo* li);
	int groupid,sgheaderid,sgfirstid;
	bool detail;
	void AddNtHeader();//单头入库
	AnsiString returncode;
	void AddNote();//明细入库
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmZNruku *frmZNruku;
//---------------------------------------------------------------------------
#endif
