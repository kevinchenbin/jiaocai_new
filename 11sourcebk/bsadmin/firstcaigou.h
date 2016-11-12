//---------------------------------------------------------------------------

#ifndef firstcaigouH
#define firstcaigouH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "pdtypes.h"
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class Tfrmfirstcaigou : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGridEh *DBGridEh1;
	TSpeedButton *SpeedButton1;
	TDataSource *ds;
	TADOQuery *aq;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmfirstcaigou(TComponent* Owner);
	int groupid;
	void Init(LandInfo* li);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmfirstcaigou *frmfirstcaigou;
//---------------------------------------------------------------------------
#endif
