//---------------------------------------------------------------------------

#ifndef MoneydiscountH
#define MoneydiscountH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmMonerydiscount : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TEdit *edcondition;
	TLabel *Label5;
	TLabel *Label6;
	TADOConnection *fcon;
	TADOQuery *aq;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TDataSource *ds1;
	TDataSource *ds2;
	TADOQuery *query1;
	TADOQuery *query2;
	TLabel *Label3;
	TComboBox *cbcondition;
	TComboBox *cbsupplier;
	TComboBox *cbtype;
	TSpeedButton *btquery;
	TGroupBox *GroupBox4;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edmoney;
	TLabel *Label4;
	TLabel *Label7;
	TDateTimePicker *dtpend;
	TDateTimePicker *dtpstart;
	TDBGrid *DBGrid1;
	TDBGrid *DBGrid2;
	TButton *btquerydiscount;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TComboBox *cbstorage;
	TLabel *Label8;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall edmoneyExit(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edmoneyKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dtpstartKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dtpendKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbconditionKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbsupplierKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbtypeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btquerydiscountClick(TObject *Sender);
	void __fastcall edconditionKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btqueryClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbstorageSelect(TObject *Sender);




private:	// User declarations
	int fstgid;
public:		// User declarations
	__fastcall TfrmMonerydiscount(TComponent* Owner,TADOConnection *con,int stgid);
	void __fastcall Query();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMonerydiscount *frmMonerydiscount;
//---------------------------------------------------------------------------
#endif
