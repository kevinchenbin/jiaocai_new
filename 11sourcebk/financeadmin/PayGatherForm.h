//---------------------------------------------------------------------------

#ifndef PayGatherFormH
#define PayGatherFormH
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
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmPayGather : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TRzToolButton *RzToolButton3;
	TComboBox *cbbType;
	TRzLabel *lbl4;
	TRzDBGrid *rzdbgrd2;
	TRzToolButton *RzToolButton1;
	TDateTimePicker *dtp1;
	TDateTimePicker *dtp2;
	TRzLabel *lbl1;
	TRzLabel *lbl2;
	TComboBox *cbb2;
	TRzLabel *lbl5;
	TCheckBox *chk1;
	TDataSource *ds2;
	TADODataSet *dsQuery;
	TDataSource *ds;
	TADOQuery *qrySupply;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
		void Init(TApplication* app, TADOConnection* con);
	__fastcall TfrmPayGather(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPayGather *frmPayGather;
//---------------------------------------------------------------------------
#endif
