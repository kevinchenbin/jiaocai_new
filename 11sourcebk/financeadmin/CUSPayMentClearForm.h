//---------------------------------------------------------------------------

#ifndef CUSPayMentClearFormH
#define CUSPayMentClearFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzLine.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TfrmCUSPayMentClear : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TADOCommand *cmdcheck;
	TADOQuery *qrySupply;
	TDataSource *ds;
	TDataSource *ds2;
	TADODataSet *dsPurchase;
	TADODataSet *dstruncheck;
	TDataSource *ds7;
	TADOCommand *cmdtruncheck;
	TADOCommand *cmdState;
	TDataSource *ds6;
	TADODataSet *dsQuery;
	TADODataSet *dscheck;
	TDataSource *ds5;
	TADOCommand *cmdNewDocuments;
	TDataSource *ds4;
	TADODataSet *dsNewDoc;
	TDataSource *ds3;
	TADOQuery *qryTotal;
	TDataSource *ds1;
	TADODataSet *dsSupplyInit;
	TRzToolButton *RzToolButton8;
	TRzToolbar *rztlbr2;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton13;
	TRzToolButton *RzToolButton2;
	TRzToolButton *RzToolButton4;
	TRzToolButton *RzToolButton5;
	TRzToolButton *RzToolButton6;
	TRzToolButton *RzToolButton7;
	TRzLine *RzLine2;
	TRzLine *RzLine1;
	TRzGroupBox *rzgrpbx3;
	TRzDBGrid *rzdbgrd1;
	TRzGroupBox *rzgrpbx2;
	TStringGrid *lst;
	TRzGroupBox *rzgrpbx1;
	TRzLabel *lbl4;
	TRzLabel *lbl6;
	TRzLabel *lbl13;
	TRzDBEdit *edtName1;
	TRzDBEdit *edtName2;
	TEdit *edt1;
	TRzButton *RzButton3;
	TRzButton *RzButton2;
	TRzButton *RzButton1;
	TRzLabel *lbl9;
	TRzLabel *lbl8;
	TRzLabel *lbl7;
	TRzLabel *lbl5;
	TRzLabel *lbl3;
	TRzLabel *lbl2;
	TRzLabel *lbl14;
	TRzLabel *lbl11;
	TRzLabel *lbl10;
	TRzLabel *lbl1;
	TEdit *edtNum;
	TEdit *edtMoney;
	TEdit *edt6;
	TEdit *edt5;
	TEdit *edt4;
	TEdit *edt3;
	TEdit *edt2;
	TComboBox *cbbType;
	TComboBox *cbb2;
	TComboBox *cbb1;
	TRzGroupBox *rzgrpbx6;
	TRzLabel *lbl12;
	TRzDBGrid *rzdbgrd2;
	TRzButton *RzButton8;
	TRzButton *RzButton10;
	TEdit *edtquery;
	TRzGroupBox *rzgrpbx7;
	TRzDBGrid *rzdbgrd4;
	TRzButton *RzButton11;
	TRzButton *RzButton12;
	TRzButton *RzButton13;
	TADOCommand *cmddel;
	TADODataSet *dsdel;
	TDataSource *ds9;
	void __fastcall cbbTypeSelect(TObject *Sender);
	void __fastcall rzdbgrd1DblClick(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton3Click(TObject *Sender);
	void __fastcall lstSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall lstDblClick(TObject *Sender);
	void __fastcall edtMoneyKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzToolButton2Click(TObject *Sender);
	void __fastcall cbb1Select(TObject *Sender);
	void __fastcall cbb2Select(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton13Click(TObject *Sender);
	void __fastcall edt6KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edt3KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall RzButton13Click(TObject *Sender);
	void __fastcall RzButton11Click(TObject *Sender);
	void __fastcall RzToolButton6Click(TObject *Sender);
	void __fastcall RzButton12Click(TObject *Sender);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall edtqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzButton10Click(TObject *Sender);
	void __fastcall RzToolButton7Click(TObject *Sender);
	void __fastcall RzButton8Click(TObject *Sender);
	void __fastcall RzToolButton4Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations

		int ACol1;
	 int ARow1;
	  bool flag;
	   bool flag1;
	  bool newdocflag;//是否是新单
	  TADOConnection* con1;
		String code;//结款单号
		float customBalance;
public:		// User declarations
	__fastcall TfrmCUSPayMentClear(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);
	void check();
	void turncheck();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCUSPayMentClear *frmCUSPayMentClear;
//---------------------------------------------------------------------------
#endif
