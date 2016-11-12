//---------------------------------------------------------------------------

#ifndef MainUIH
#define MainUIH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
#include "localadjust.h"
#include "StockalarmSet.h"
#include <ADODB.hpp>
#include <DB.hpp>

//---------------------------------------------------------------------------
class TfrmUI : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *aqalarm;
	TPanel *Panel1;
	TPanel *ptongji;
	TSpeedButton *SpeedButton43;
	TSpeedButton *SpeedButton44;
	TSpeedButton *SpeedButton46;
	TSpeedButton *SpeedButton47;
	TSpeedButton *SpeedButton48;
	TSpeedButton *SpeedButton49;
	TSpeedButton *spsaleman;
	TSpeedButton *SpeedButton3;
	TSpeedButton *spstore;
	TSpeedButton *SpeedButton5;
	TSpeedButton *SpeedButton7;
	TSpeedButton *sbbuymanage;
	TImage *imagewl;
	TImage *imagecg;
	TImage *imagekc;
	TImage *imagels;
	TImage *imagetj;
	TImage *imagepx;
	TLabel *Label1;
	TLabel *Label2;
	void __fastcall pcDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect,
          bool Active);
	void __fastcall pcChange(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall sbsaleMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall spsalemanClick(TObject *Sender);
	void __fastcall spstoreClick(TObject *Sender);
	void __fastcall sbpsaleClick(TObject *Sender);
	void __fastcall sbsaleClick(TObject *Sender);
	void __fastcall sbjiezhangClick(TObject *Sender);
	void __fastcall spinputClick(TObject *Sender);
	void __fastcall sppandianClick(TObject *Sender);
	void __fastcall sbClick(TObject *Sender);
	void __fastcall sbbuymanageClick(TObject *Sender);
	void __fastcall SpeedButton8Click(TObject *Sender);
	void __fastcall SpeedButton9Click(TObject *Sender);
	void __fastcall SpeedButton10Click(TObject *Sender);
	void __fastcall SpeedButton11Click(TObject *Sender);
	void __fastcall SpeedButton12Click(TObject *Sender);
	void __fastcall SpeedButton13Click(TObject *Sender);
	void __fastcall SpeedButton15Click(TObject *Sender);
	void __fastcall SpeedButton16Click(TObject *Sender);
	void __fastcall SpeedButton17Click(TObject *Sender);
	void __fastcall SpeedButton14Click(TObject *Sender);
	void __fastcall SpeedButton18Click(TObject *Sender);
	void __fastcall SpeedButton19Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton20Click(TObject *Sender);
	void __fastcall SpeedButton22Click(TObject *Sender);
	void __fastcall SpeedButton23Click(TObject *Sender);
	void __fastcall SpeedButton24Click(TObject *Sender);
	void __fastcall SpeedButton25Click(TObject *Sender);
	void __fastcall SpeedButton27Click(TObject *Sender);
	void __fastcall SpeedButton26Click(TObject *Sender);
	void __fastcall SpeedButton28Click(TObject *Sender);
	void __fastcall SpeedButton29Click(TObject *Sender);
	void __fastcall SpeedButton30Click(TObject *Sender);
	void __fastcall SpeedButton31Click(TObject *Sender);
	void __fastcall SpeedButton32Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton33Click(TObject *Sender);
	void __fastcall SpeedButton34Click(TObject *Sender);
	void __fastcall SpeedButton35Click(TObject *Sender);
	void __fastcall SpeedButton38Click(TObject *Sender);
	void __fastcall SpeedButton36Click(TObject *Sender);
	void __fastcall SpeedButton37Click(TObject *Sender);
	void __fastcall SpeedButton40Click(TObject *Sender);
	void __fastcall SpeedButton39Click(TObject *Sender);
	void __fastcall SpeedButton41Click(TObject *Sender);
	void __fastcall SpeedButton42Click(TObject *Sender);
	void __fastcall SpeedButton7Click(TObject *Sender);
	void __fastcall SpeedButton46Click(TObject *Sender);
	void __fastcall SpeedButton44Click(TObject *Sender);
	void __fastcall SpeedButton47Click(TObject *Sender);
	void __fastcall SpeedButton49Click(TObject *Sender);
	void __fastcall SpeedButton48Click(TObject *Sender);
	void __fastcall SpeedButton43Click(TObject *Sender);
	void __fastcall SpeedButton6Click(TObject *Sender);
	void __fastcall SpeedButton5Click(TObject *Sender);
	void __fastcall imageuiMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall imageuiClick(TObject *Sender);
	void __fastcall imagetjMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall imagewlMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall imagelsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall imagepxMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);








private:	// User declarations
public:		// User declarations
	__fastcall TfrmUI(TComponent* Owner);
	virtual void __fastcall CreateParams(Controls::TCreateParams & Params);
	void LoadPUI();
	void Display(AnsiString PUIName);
	int uix,uiy;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmUI *frmUI;
//---------------------------------------------------------------------------
#endif
