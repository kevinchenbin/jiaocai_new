//---------------------------------------------------------------------------

#ifndef CheckStockFormH
#define CheckStockFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "RzGrids.hpp"
#include "IWBaseControl.hpp"
#include "IWBaseHTMLControl.hpp"
#include "IWControl32.hpp"
#include "IWDBGrids32.hpp"
#include "IWGrids32.hpp"
#include "IWVCLBaseControl.hpp"
#include <DB.hpp>
#include "RzCmboBx.hpp"
#include "RzDBCmbo.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include <MDIChild.h>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmCheckStock : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzLabel *lbl2;
	TComboBox *cbbNum;
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton5;
	TRzToolButton *RzToolButton1;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton6;
	TRzEdit *RzEdit1;
	TComboBox *cbbType;
	TRzLabel *lbl4;
	TADOQuery *qryName;
	TDataSource *ds1;
	TDataSource *ds2;
	TADODataSet *dsCheckStock;
	TRzNumericEdit *edtnum1;
	TRzGroupBox *rzgrpbx1;
	TRzDBGrid *rzdbgrd1;
	TDataSource *ds3;
	TADODataSet *dscheck;
	TADOCommand *cmdCreate;
	TADOCommand *cmd1;
	TRzDBEdit *edtNum;
	TRzLabel *lbl1;
	TRzLabel *lbl;
	TRzGroupBox *rzgrpbx2;
	TRzDBGrid *rzdbgrd2;
	TRzDBEdit *edtName;
	TRzLabel *lbl3;
	TADODataSet *dsStore;
	TDataSource *ds4;
	TRzEdit *RzEdit2;
	TADOQuery *qryCode;
	TDataSource *ds5;
	TRzLabel *lbl5;
	TRzDBEdit *edtName1;
	TADODataSet *dsqryinventory;
	TDataSource *ds7;
	TRzGroupBox *rzgrpbx3;
	TRzDBGrid *rzdbgrd3;
	TRzToolButton *RzToolButton4;
	TADODataSet *dsinventory;
	TDataSource *ds8;
	TDateTimePicker *dtp1;
	TDateTimePicker *dtp2;
	TLabel *lbl6;
	TLabel *lbl7;
	void __fastcall RzEdit1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall cbbTypeSelect(TObject *Sender);
	void __fastcall edtnum1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall rzdbgrd2DblClick(TObject *Sender);
	void __fastcall cbbNumSelect(TObject *Sender);
	void __fastcall RzToolButton6Click(TObject *Sender);
	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall edtName1Click(TObject *Sender);
	void __fastcall RzToolButton2Click(TObject *Sender);
	void __fastcall RzToolButton4Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dtp1Change(TObject *Sender);
	void __fastcall dtp2Change(TObject *Sender);
private:	// User declarations
		void Check();

		String Code1;
		bool flag;
		 TApplication* app1;
		 TADOConnection* con1;
           //TADOConnection* con1;
public:		// User declarations
	__fastcall TfrmCheckStock(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCheckStock *frmCheckStock;
//---------------------------------------------------------------------------
#endif
