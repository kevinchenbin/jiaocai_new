//---------------------------------------------------------------------------

#ifndef firstfahuoH
#define firstfahuoH
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
class Tfrmfirstfahuo : public TForm
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
	TRzToolButton *BtnDelete;
	TADOConnection *fcon;
	TADOQuery *query;
	TGroupBox *GroupBox1;
	TCheckBox *chxuexiao;
	TCheckBox *chxiaoqu;
	TCheckBox *chxueyuan;
	TCheckBox *chclass;
	TADOQuery *aq1;
	TADOQuery *aq2;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnDeleteClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmfirstfahuo(TComponent* Owner);
	int groupid,modresult;
	void Init(LandInfo* li);
	void Createyufacode();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmfirstfahuo *frmfirstfahuo;
//---------------------------------------------------------------------------
#endif
