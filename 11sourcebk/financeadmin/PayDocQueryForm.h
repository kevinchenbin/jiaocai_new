//---------------------------------------------------------------------------

#ifndef PayDocQueryFormH
#define PayDocQueryFormH
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
class TfrmPayDocQuery : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton1;
	TRzGroupBox *rzgrpbx4;
	TRzDBGrid *rzdbgrd3;
	TRzLabel *lbl2;
	TRzLabel *lbl1;
	TDateTimePicker *dtp1;
	TRzLabel *lbl3;
	TDateTimePicker *dtp2;
	TComboBox *cbb2;
	TRzLabel *lbl4;
	TComboBox *cbbType;
	TRzGroupBox *rzgrpbx1;
	TRzDBGrid *rzdbgrd1;
	TDataSource *ds1;
	TADODataSet *dsDoc;
	TADOQuery *qrySupply;
	TDataSource *ds;
	TDataSource *ds2;
	TADODataSet *dsSNoteHD;
	TComboBox *cbb1;
	TRzLabel *lbl5;
	TComboBox *cbb3;
	TRzLabel *lbl6;
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall rzdbgrd3ColumnMoved(TObject *Sender, int FromIndex, int ToIndex);
	void __fastcall rzdbgrd1DblClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:	// User declarations
		void query();
public:		// User declarations
	__fastcall TfrmPayDocQuery(TComponent* Owner);
		void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPayDocQuery *frmPayDocQuery;
//---------------------------------------------------------------------------
#endif
