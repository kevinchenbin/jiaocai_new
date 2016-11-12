//---------------------------------------------------------------------------

#ifndef retailbookupH
#define retailbookupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "UnitBIOrder.h"
#include "UnitDiaobo.h"
#include "ProcureMng.h"
//---------------------------------------------------------------------------
class Tfrmretailbookup : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnExit;
	TADOConnection *fcon;
	TRzToolButton *BtnView;
	TDataSource *dsdetail;
	TADOQuery *qudetail;
	TSaveDialog *savedlg;
	TPanel *Panel1;
	TGroupBox *书目检索条件;
	TDateTimePicker *dtpbegin;
	TCheckBox *chbegin;
	TDateTimePicker *dtpend;
	TCheckBox *chend;
	TButton *Button2;
	TLabel *Label1;
	TEdit *Edit1;
	TEdit *Edit2;
	TDBGridEh *dgdetail;
	TButton *btall;
	TButton *btconcel;
	TRzToolButton *BtnExport1;
	TCheckBox *chpress;
	TEdit *edpress;
	TCheckBox *chbkinfo;
	TComboBox *cbpress;
	TLabel *Label2;
	TEdit *edmin;
	TLabel *Label3;
	TEdit *edmax;
	TCheckBox *chls;
	TLabel *Label4;
	TEdit *edlsmin;
	TLabel *Label5;
	TEdit *edlsmax;
	TCheckBox *chws;
	TLabel *Label6;
	TEdit *edwsmin;
	TLabel *Label7;
	TEdit *edwsmax;
	TCheckBox *CheckBox1;
	TPopupMenu *pm;
	TMenuItem *N1;
	TComboBox *cbsupplier;
	TEdit *edsupplier;
	TCheckBox *chsupplier;
	TCheckBox *chbox2;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall dtpbeginChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall dgdetailTitleClick(TColumnEh *Column);
	void __fastcall btallClick(TObject *Sender);
	void __fastcall btconcelClick(TObject *Sender);
	void __fastcall BtnExport1Click(TObject *Sender);
	void __fastcall dgdetailDblClick(TObject *Sender);
	void __fastcall edminChange(TObject *Sender);
	void __fastcall edlsminChange(TObject *Sender);
	void __fastcall edwsminChange(TObject *Sender);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall edsupplierKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
	int  supplierid ;
public:		// User declarations
	__fastcall Tfrmretailbookup(TComponent* Owner,TADOConnection *con,int stgid,int userid);
	bool __fastcall DbgridToExcel(TDBGridEh* dbg);
	int fstgid,maxlen,fuserid ;
	int modle;//1为订单，2为调拨
	AnsiString sqlwhere,sqltime,sqlws,sqlls,sqlstorage ;
	TfrmBIorder *Ord;
	Tfrmdiaobo *Diaobo;
	TfrmProcureMng *Pro;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmretailbookup *frmretailbookup;
//---------------------------------------------------------------------------
#endif
