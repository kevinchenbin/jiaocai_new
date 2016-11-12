//---------------------------------------------------------------------------

#ifndef systemsetH
#define systemsetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <Buttons.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class Tfrmsystemset : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSpeedButton *sbok;
	TSpeedButton *sbcancel;
	TADOQuery *aquery;
	TGroupBox *GroupBox2;
	TCheckBox *cbchangeDanHaoDisplay;
	TADOQuery *qryretairange;
	TDataSource *dsrcretairange;
	TButton *Button1;
	TADOConnection *fcon;
	TImageList *ImageList1;
	TLabel *Label1;
	TLabel *Label2;
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmsystemset(TComponent* Owner,TADOConnection* con);
	void Readydata();
	int userid;
	int storageid;
	AnsiString logmessage;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsystemset *frmsystemset;
//---------------------------------------------------------------------------
#endif
