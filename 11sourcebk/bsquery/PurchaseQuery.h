//---------------------------------------------------------------------------

#ifndef PurchaseQueryH
#define PurchaseQueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzDBDTP.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzDTP.hpp"
#include "RzEdit.hpp"
#include "RzRadChk.hpp"
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmPurchaseQuery : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzGroupBox *rzgrpbx2;
	TRzLabel *lbl3;
	TRzLabel *lbl4;
	TRzLabel *lbl5;
	TRzLabel *lbl6;
	TRzLabel *lbl7;
	TRzLabel *lbl8;
	TRzLabel *lbl9;
	TRzLabel *lbl10;
	TRzLabel *lbl11;
	TRzLabel *lbl12;
	TRzLabel *lbl17;
	TRzLabel *lbl18;
	TLabel *lbl15;
	TLabel *lbl16;
	TRzRadioButton *rb1;
	TRzRadioButton *rb2;
	TRzRadioButton *rb3;
	TRzRadioButton *rb4;
	TRzRadioButton *rb5;
	TRzGroupBox *rzgrpbx3;
	TLabel *lbl13;
	TLabel *lbl14;
	TRzDBDateTimePicker *rzdbdtmpckr1;
	TRzDBDateTimePicker *rzdbdtmpckr2;
	TRzGroupBox *rzgrpbx4;
	TLabel *lbl1;
	TLabel *lbl2;
	TRzCheckBox *chckbx1;
	TRzCheckBox *chckbx2;
	TRzCheckBox *chckbx3;
	TRzCheckBox *chckbx4;
	TRzCheckBox *chckbx5;
	TRzCheckBox *chckbx6;
	TRzCheckBox *chckbx7;
	TRzCheckBox *chckbx8;
	TRzCheckBox *chckbx9;
	TRzCheckBox *chckbx10;
	TRzCheckBox *chckbx11;
	TRzCheckBox *chckbx12;
	TRzEdit *edt1;
	TRzEdit *edt2;
	TRzEdit *edt3;
	TRzEdit *edt4;
	TRzEdit *edt5;
	TRzEdit *edt6;
	TRzEdit *edt7;
	TRzEdit *edt8;
	TRzEdit *edt9;
	TRzEdit *edt10;
	TRzEdit *edt11;
	TRzEdit *edt12;
	TRzEdit *edt13;
	TRzToolbar *rztlbr1;
	TRzToolButton *btnExit1;
	TRzToolButton *btnExit2;
	TRzToolButton *btnExit3;
	TRzToolButton *btnExit4;
	TRzDBGrid *rzdbgrd1;
	TDataSource *ds2;
	TADODataSet *ds1;
	TImageList *ImageList1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnExit4Click(TObject *Sender);
private:	// User declarations
String m_sql;
public:		// User declarations
	__fastcall TfrmPurchaseQuery(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPurchaseQuery *frmPurchaseQuery;
//---------------------------------------------------------------------------
#endif
