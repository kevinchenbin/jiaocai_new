//---------------------------------------------------------------------------

#ifndef PaydetailFormH
#define PaydetailFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmPaydetail : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton1;
	TComboBox *cbb2;
	TRzLabel *lbl2;
	TDateTimePicker *dtp2;
	TRzLabel *lbl3;
	TDateTimePicker *dtp1;
	TRzLabel *lbl1;
	TRzLabel *lbl4;
	TComboBox *cbbType;
	TRzGroupBox *rzgrpbx1;
	TEdit *edt1;
	TRzGroupBox *rzgrpbx2;
	TRzDBGrid *rzdbgrd2;
	TRzGroupBox *rzgrpbx3;
	TRzDBGrid *rzdbgrd1;
	TRzLabel *lbl5;
	TEdit *edt2;
	TEdit *edt3;
	TEdit *edt4;
	TRzLabel *lbl6;
	TRzLabel *lbl7;
	TRzLabel *lbl8;
	TRzLabel *lbl9;
	TEdit *edt5;
	TDataSource *ds;
	TADOQuery *qrySupply;
	TADODataSet *dsDoc;
	TDataSource *ds1;
	TRzGroupBox *rzgrpbx4;
	TRzDBGrid *rzdbgrd3;
	TDataSource *ds2;
	TADODataSet *dsbalance;
	TDataSource *ds3;
	TADODataSet *dsdetail;
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall rzdbgrd3DblClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations

public:		// User declarations
	__fastcall TfrmPaydetail(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPaydetail *frmPaydetail;
//---------------------------------------------------------------------------
#endif
