//---------------------------------------------------------------------------

#ifndef CUSPayDetailFormH
#define CUSPayDetailFormH
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
class TfrmCUSPayDetail : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzLabel *lbl2;
	TRzLabel *lbl3;
	TRzLabel *lbl1;
	TRzLabel *lbl4;
	TRzToolbar *RzToolbar1;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton1;
	TComboBox *cbb2;
	TDateTimePicker *dtp2;
	TDateTimePicker *dtp1;
	TComboBox *cbbType;
	TRzGroupBox *rzgrpbx1;
	TRzLabel *lbl5;
	TRzLabel *lbl6;
	TRzLabel *lbl7;
	TRzLabel *lbl8;
	TRzLabel *lbl9;
	TEdit *edt1;
	TEdit *edt2;
	TEdit *edt3;
	TEdit *edt4;
	TEdit *edt5;
	TRzGroupBox *rzgrpbx2;
	TRzDBGrid *rzdbgrd2;
	TDataSource *ds;
	TADOQuery *qrySupply;
	TADODataSet *dsDoc;
	TDataSource *ds1;
	TDataSource *ds2;
	TADODataSet *dsbalance;
	TDataSource *ds3;
	TADODataSet *dsdetail;
	TRzGroupBox *rzgrpbx3;
	TRzDBGrid *rzdbgrd1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall rzdbgrd2DblClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations

public:		// User declarations
	__fastcall TfrmCUSPayDetail(TComponent* Owner);
		void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCUSPayDetail *frmCUSPayDetail;
//---------------------------------------------------------------------------
#endif
