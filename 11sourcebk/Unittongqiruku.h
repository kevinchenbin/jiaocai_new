//---------------------------------------------------------------------------

#ifndef UnittongqirukuH
#define UnittongqirukuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ComCtrls.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include <Buttons.hpp>
#include "DBCtrlsEh.hpp"
#include <Mask.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzEdit.hpp"
#include <Provider.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmtongqiruku : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGridEh *dg;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExit;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TRadioGroup *rg;
	TEdit *edname;
	TComboBox *cbtype;
	TComboBox *cpress;
	TEdit *edclient;
	TLabel *Label2;
	TADOConnection *fcon;
	TRzToolButton *BtnAlignBottom;
	TDataSource *ds;
	TADOQuery *query;
	TComboBox *cbsupplier;
	TDataSource *ds1;
	TADOQuery *aq1;
	TADOStoredProc *adosp;
	TADODataSet *adodataset;
	TADODataSet *adods;
	TDateTimePicker *dtpstart;
	TDateTimePicker *dtpend;
	TDateTimePicker *dtpstart3;
	TDateTimePicker *dtpstart4;
	TLabel *Label3;
	TLabel *Label4;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	TEdit *editselect;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall editselectMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmtongqiruku(TComponent* Owner,TADOConnection *con,int stgid);
	int fstgid,SupplierID;
	bool clientAll;
	String format;
	int danpingselect;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmtongqiruku *frmtongqiruku;
//---------------------------------------------------------------------------
#endif
