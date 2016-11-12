//---------------------------------------------------------------------------

#ifndef UnitbslockH
#define UnitbslockH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmbslock : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TCheckBox *chstart;
	TDateTimePicker *dtpstart;
	TCheckBox *chend;
	TDateTimePicker *dtpend;
	TRadioGroup *rg;
	TDBGrid *dg1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExport;
	TCheckBox *cksupplier;
	TADOConnection *con;
	TDataSource *ds;
	TADOQuery *aq;
	TCheckBox *chclient;
	TEdit *edclient;
	TEdit *edtclient;
	TSpeedButton *spselectClient;
	TEdit *editsupplier;
	TComboBox *cbsupplier;
	TPopupMenu *pm;
	TMenuItem *Q1;
	TMenuItem *L1;
	TMenuItem *N1;
	TRzToolButton *RzToolButton1;
	TCheckBox *chuser;
	TComboBox *cbuser;
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtclientChange(TObject *Sender);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall editsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbsupplierChange(TObject *Sender);
	void __fastcall dg1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Q1Click(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
private:	// User declarations
         int m_catalogSearchMode,bkcatalogid,fstgid,ClientID;
          TADOConnection *fcon;
          void ClientView();
          TBookmark bookmark;//记录先前的位置
       int oldrec;
       int currrec;
public:		// User declarations
	__fastcall Tfrmbslock(TComponent* Owner,TADOConnection *con,int stgid);
        void query();
        void lock(int type);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmbslock *frmbslock;
//---------------------------------------------------------------------------
#endif
