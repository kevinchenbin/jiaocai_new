//---------------------------------------------------------------------------

#ifndef UnitdistributeH
#define UnitdistributeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <Buttons.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrmdaohuofenfa : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *Btn;
	TRzToolButton *Btn1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TADOQuery *aq;
	TDataSource *ds1;
	TDataSource *ds2;
	TADOQuery *aq1;
	TADOQuery *aq2;
	TPanel *Panel1;
	TGroupBox *GroupBox2;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *Edit10;
	TEdit *Edit11;
	TEdit *Edit12;
	TRzDBGrid *RzDBGrid1;
	TRzDBGrid *RzDBGrid2;
	TRzToolButton *Btn2;
	TRzToolButton *BtnAlignNone;
	TSpeedButton *SpeedButton3;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzDBGrid1CellClick(TColumn *Column);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall Btn1Click(TObject *Sender);
	void __fastcall Btn2Click(TObject *Sender);
	void __fastcall BtnAlignNoneClick(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmdaohuofenfa(TComponent* Owner);
	void Init(LandInfo *li);
	LandInfo linfo;
	void  ReadData();
	int type,clientset; //type 1按按书，2为按客户
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmdaohuofenfa *frmdaohuofenfa;
//---------------------------------------------------------------------------
#endif
