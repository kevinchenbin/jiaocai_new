//---------------------------------------------------------------------------

#ifndef CUSPayGatherFormH
#define CUSPayGatherFormH
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
class TfrmCUSPayGather : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzDBGrid *rzdbgrd2;
	TADOQuery *qrySupply;
	TDataSource *ds;
	TADODataSet *dsQuery;
	TDataSource *ds2;
	TDateTimePicker *dtp2;
	TRzLabel *lbl2;
	TDateTimePicker *dtp1;
	TRzLabel *lbl1;
	TRzLabel *lbl4;
	TComboBox *cbbType;
	TRzToolbar *RzToolbar1;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton1;
	TComboBox *cbb2;
	TRzLabel *lbl5;
	TCheckBox *chk1;
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations

public:		// User declarations
	__fastcall TfrmCUSPayGather(TComponent* Owner);
		void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCUSPayGather *frmCUSPayGather;
//---------------------------------------------------------------------------
#endif
