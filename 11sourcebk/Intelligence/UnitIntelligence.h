//---------------------------------------------------------------------------

#ifndef UnitIntelligenceH
#define UnitIntelligenceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "pdtypes.h"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmIntelligence : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSpeedButton *sbselect;
	TADOStoredProc *StoreSelect;
	TSpeedButton *SpeedButton1;
	void __fastcall sbselectClick(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
	int ID;
	TADOConnection *fcon;
	int m_stogeID;
public:		// User declarations
	__fastcall TfrmIntelligence(TComponent* Owner,LandInfo *li);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmIntelligence *frmIntelligence;
//---------------------------------------------------------------------------
#endif
