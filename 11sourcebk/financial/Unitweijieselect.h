//---------------------------------------------------------------------------

#ifndef UnitweijieselectH
#define UnitweijieselectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "Unitbalance.h"
//---------------------------------------------------------------------------
class Tfrmselectjiedan : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnOK;
	TRzToolButton *BtnPost;
	TRzToolButton *BtnSendtoBack;
	TRzToolButton *BtnExit;
	TADOQuery *aqdg;
	TDataSource *ds;
	TRzToolButton *BtnAlignBottom;
	TLabel *Label1;
	TEdit *edfapiaotext;
	TCheckBox *chduizhang;
	TADOConnection *con;
	TDBGridEh *dg;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall BtnPostClick(TObject *Sender);
	void __fastcall BtnSendtoBackClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edfapiaotextKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall chduizhangClick(TObject *Sender);
	void __fastcall dgDblClick(TObject *Sender);
private:	// User declarations
	BOOL mselect;
public:		// User declarations
	 int Type;
	 String ID;
	 TADOQuery *selectaq;
	 String Disc;
	__fastcall Tfrmselectjiedan(TComponent* Owner,TADOConnection *cn,TADOQuery *aq);
	void GetdgData(String ID);
	TStringList *selectedID;
		String DanCode;
	bool ChangeDisplay;
	int stgid;
	bool master;
	bool AddEnable(int type,AnsiString code);
	Tfrmbalance *balance;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmselectjiedan *frmselectjiedan;
//---------------------------------------------------------------------------
#endif
