//---------------------------------------------------------------------------

#ifndef WarnStockFormH
#define WarnStockFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <DB.hpp>
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpBase.hpp"
#include "RpSystem.hpp"
#include "RpRender.hpp"
#include "RpRenderCanvas.hpp"
#include "RpRenderPreview.hpp"
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <MDIChild.h>
//---------------------------------------------------------------------------
class TfrmWarnStock : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton5;
	TRzToolButton *RzToolButton3;
	TComboBox *cbbType;
	TRzLabel *lbl4;
	TRzEdit *RzEdtInfor;
	TRzLabel *lbl1;
	TRzLabel *lbl2;
	TRzNumericEdit *edtnum1;
	TRzNumericEdit *RzNumericEdit1;
	TRzDBGrid *rzdbgrd2;
	TDataSource *ds1;
	TADODataSet *dsWarnStock;
	TComboBox *cbb1;
	TRzToolButton *RzToolButton1;
	TComboBox *cbbSupply;
	TCheckBox *chk1;
	TCheckBox *chk2;
	TDataSource *ds2;
	TADOQuery *qryName;
	TADOQuery *qrySupply;
	TDataSource *ds3;
	TButton *btn1;
	TButton *btn2;
	TADOCommand *cmdSetWarn;
	TRzLabel *lbl3;
	TCheckBox *rb1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall cbbTypeSelect(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall RzEdtInforKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbb1Select(TObject *Sender);
	void __fastcall cbbSupplySelect(TObject *Sender);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall btn2Click(TObject *Sender);
	void __fastcall edtnum1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzNumericEdit1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rb1Click(TObject *Sender);
	void __fastcall chk1Click(TObject *Sender);
	void __fastcall chk2Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
       //	TADOConnection  con1;
public:		// User declarations
	__fastcall TfrmWarnStock(TComponent* Owner);
	TADOConnection* con1;
	void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWarnStock *frmWarnStock;
//---------------------------------------------------------------------------
#endif
