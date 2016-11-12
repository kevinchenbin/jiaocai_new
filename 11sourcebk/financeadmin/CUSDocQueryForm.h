//---------------------------------------------------------------------------

#ifndef CUSDocQueryFormH
#define CUSDocQueryFormH
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
class TfrmCUSDocQuery : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton1;
	TRzLabel *lbl4;
	TComboBox *cbbType;
	TADOQuery *qrySupply;
	TDataSource *ds;
	TRzLabel *lbl1;
	TDateTimePicker *dtp1;
	TRzLabel *lbl3;
	TDateTimePicker *dtp2;
	TComboBox *cbb2;
	TRzLabel *lbl2;
	TComboBox *cbb3;
	TRzLabel *lbl6;
	TComboBox *cbb1;
	TRzLabel *lbl5;
	TRzGroupBox *rzgrpbx1;
	TRzDBGrid *rzdbgrd1;
	TRzGroupBox *rzgrpbx4;
	TRzDBGrid *rzdbgrd3;
	TADODataSet *dsSNoteHD;
	TDataSource *ds2;
	TADODataSet *dsDoc;
	TDataSource *ds1;
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall rzdbgrd1DblClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
		void query();


public:		// User declarations
	__fastcall TfrmCUSDocQuery(TComponent* Owner);
		void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCUSDocQuery *frmCUSDocQuery;
//---------------------------------------------------------------------------
#endif
