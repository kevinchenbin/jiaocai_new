//---------------------------------------------------------------------------

#ifndef AdjustStockFormH
#define AdjustStockFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <MDIChild.h>
#include <Grids.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmAdjustStock : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TRzToolButton *RzToolButton10;
	TRzLabel *lbl3;
	TRzDBEdit *edtNum;
	TRzDBEdit *edtName;
	TRzLabel *lbl4;
	TRzEdit *RzEditInfor;
	TComboBox *cbbType;
	TRzDBGrid *rzdbgrdGridCust;
	TADODataSet *dsStoreName;
	TDataSource *ds2;
	TADOQuery *qryName;
	TDataSource *ds1;
	TADODataSet *dsAdjustStock;
	TDataSource *ds4;
	TRzGroupBox *rzgrpbx1;
	TRzDBEdit *edtContact;
	TRzLabel *lbl5;
	TRzNumericEdit *edtSingle;
	TRzLabel *lbl6;
	TComboBox *cbbNum;
	TRzDBEdit *edtContact1;
	TRzLabel *lbl2;
	TRzLabel *lbl1;
	TRzGroupBox *rzgrpbx2;
	TRzLabel *lbl8;
	TRzLabel *lbl10;
	TComboBox *cbbNum1;
	TADODataSet *dsetwhole;
	TDataSource *ds5;
	TADOCommand *cmdwhole;
	TADOCommand *cmdSingle;
	TDataSource *ds3;
	TADODataSet *dsetID;
	TLabel *Label1;
	void __fastcall RzEditInforKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbbTypeSelect(TObject *Sender);
	void __fastcall cbb2Select(TObject *Sender);
	void __fastcall cbbNum1Select(TObject *Sender);
	void __fastcall cbbNumSelect(TObject *Sender);
	void __fastcall edtSingleKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzToolButton10Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
		// --------------²éÑ¯º¯Êý--------------------
		void Query();
		TApplication* app1;
		 TADOConnection* con1;
public:		// User declarations
	__fastcall TfrmAdjustStock(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAdjustStock *frmAdjustStock;
//---------------------------------------------------------------------------
#endif
