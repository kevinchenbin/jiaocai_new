//---------------------------------------------------------------------------

#ifndef UnitjxcbijiaoH
#define UnitjxcbijiaoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "Chart.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include "Series.hpp"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tfrmjxcbijiao : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TCheckBox *chstorage;
	TRadioGroup *rg1;
	TComboBox *cbstorage;
	TADOConnection *con;
	TADOQuery *aqrk;
	TChart *charjxc;
	TBarSeries *Series1;
	TRadioGroup *rg2;
	TADOQuery *aqpx;
	TADOQuery *aqls;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TRadioGroup *rgview;
	TFastLineSeries *Series3;
	TFastLineSeries *Series4;
	TBarSeries *Series2;
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall rg2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall rg1Click(TObject *Sender);
	void __fastcall rgviewClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmjxcbijiao(TComponent* Owner,TADOConnection *cn,int stgid);
	int fstgid;
	bool master;
	AnsiString title;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmjxcbijiao *frmjxcbijiao;
//---------------------------------------------------------------------------
#endif
