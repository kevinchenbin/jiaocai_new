//---------------------------------------------------------------------------

#ifndef ClearingProvidForm11H
#define ClearingProvidForm11H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzGrids.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ImgList.hpp>
#include <Buttons.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
//---------------------------------------------------------------------------
class TfrmClearingProvid11 : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton1;
	TImageList *ImageList1;
	TPanel *Panel1;
	TRzToolButton *BtnAlignBottom;
	TADOConnection *fcon;
	TDataSource *ds;
	TADOQuery *query;
	TCheckBox *chstorage;
	TComboBox *cbstorage;
	TRzLabel *RzLabel1;
	TCheckBox *cbend;
	TCheckBox *cbstart;
	TDateTimePicker *dtp1;
	TDateTimePicker *dtp2;
	TEdit *edclient;
	TCheckBox *chpress;
	TComboBox *cpress;
	TCheckBox *chtype;
	TComboBox *cbtype;
	TCheckBox *chisbn;
	TEdit *edisbn;
	TCheckBox *chname;
	TEdit *edname;
	TComboBox *cbsupplier;
	TDBGridEh *DBGridEh1;
	TRadioGroup *rg;
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall DBGridEh1TitleClick(TColumnEh *Column);
private:	// User declarations
	String storageformat,retaiformat,saleformat;
public:		// User declarations
	__fastcall TfrmClearingProvid11(TComponent* Owner);
		void   Init(TApplication* app, TADOConnection* con);
	int type,stgid;
	void Query();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmClearingProvid11 *frmClearingProvid11;
//---------------------------------------------------------------------------
#endif
