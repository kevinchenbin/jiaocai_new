//---------------------------------------------------------------------------

#ifndef UnitshengjiH
#define UnitshengjiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class Tfrmshengji : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TLabel *Label2;
	TImage *Image1;
	TPanel *Panel2;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TImage *Image2;
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmshengji(TComponent* Owner);
	void picview();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmshengji *frmshengji;
//---------------------------------------------------------------------------
#endif
