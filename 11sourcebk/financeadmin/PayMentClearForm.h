//---------------------------------------------------------------------------

#ifndef PayMentClearFormH
#define PayMentClearFormH
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
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include "RzSpnEdt.hpp"
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include "RzLine.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmPayMentCle : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzLabel *lbl11;
	TRzLabel *lbl5;
	TRzLabel *lbl3;
	TRzLabel *lbl9;
	TRzLabel *lbl10;
	TRzLabel *lbl7;
	TComboBox *cbb1;
	TRzLabel *lbl2;
	TComboBox *cbb2;
	TRzGroupBox *rzgrpbx1;
	TRzLabel *lbl4;
	TRzLabel *lbl6;
	TRzDBEdit *edtName1;
	TRzDBEdit *edtName2;
	TComboBox *cbbType;
	TRzLabel *lbl1;
	TRzToolbar *rztlbr2;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton13;
	TRzToolButton *RzToolButton2;
	TRzToolButton *RzToolButton4;
	TRzToolButton *RzToolButton5;
	TRzToolButton *RzToolButton6;
	TRzToolButton *RzToolButton7;
	TRzLabel *lbl13;
	TRzLabel *lbl14;
	TRzGroupBox *rzgrpbx2;
	TRzGroupBox *rzgrpbx3;
	TRzDBGrid *rzdbgrd1;
	TRzLine *RzLine2;
	TRzLine *RzLine1;
	TRzToolButton *RzToolButton8;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TRzButton *RzButton3;
	TDataSource *ds;
	TADOQuery *qrySupply;
	TADODataSet *dsSupplyInit;
	TDataSource *ds1;
	TADODataSet *dsPurchase;
	TDataSource *ds2;
	TStringGrid *lst;
	TEdit *edt1;
	TADOCommand *cmdState;
	TADOQuery *qryTotal;
	TDataSource *ds3;
	TEdit *edtMoney;
	TEdit *edt2;
	TEdit *edt3;
	TEdit *edt4;
	TEdit *edt5;
	TRzGroupBox *rzgrpbx4;
	TRzDBGrid *rzdbgrd2;
	TEdit *edtNum;
	TRzLabel *lbl8;
	TEdit *edt6;
	TADOCommand *cmdNewDocuments;
	TADODataSet *dsNewDoc;
	TDataSource *ds4;
	TRzButton *RzButton4;
	TRzButton *RzButton5;
	TRzButton *RzButton6;
	TADOCommand *cmdcheck;
	TDataSource *ds5;
	TADODataSet *dscheck;
	TRzGroupBox *rzgrpbx5;
	TRzDBGrid *rzdbgrd3;
	TRzButton *RzButton7;
	TRzButton *RzButton9;
	TADODataSet *dsQuery;
	TDataSource *ds6;
	TEdit *edtquery;
	TRzLabel *lbl15;
	TADODataSet *dstruncheck;
	TDataSource *ds7;
	TADOCommand *cmdtruncheck;
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
	void __fastcall RzButton6Click(TObject *Sender);
	void __fastcall RzButton4Click(TObject *Sender);
	void __fastcall RzToolButton6Click(TObject *Sender);
	void __fastcall RzButton5Click(TObject *Sender);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall edtqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzButton9Click(TObject *Sender);
	void __fastcall RzToolButton7Click(TObject *Sender);
	void __fastcall RzButton7Click(TObject *Sender);
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
	__fastcall TfrmPayMentCle(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);
	void check();
    void turncheck();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPayMentCle *frmPayMentCle;
//---------------------------------------------------------------------------
#endif
