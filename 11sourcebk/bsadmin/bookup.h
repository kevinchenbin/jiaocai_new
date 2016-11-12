//---------------------------------------------------------------------------

#ifndef bookupH
#define bookupH
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
#include "ZNProcureMng.h"
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class Tfrmbookup : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnExit;
	TADOConnection *fcon;
	TRzToolButton *BtnView;
	TDataSource *dssupplier;
	TADOQuery *qusupplier;
	TADOStoredProc *spsupplier;
	TDataSource *dsdetail;
	TADOQuery *qudetail;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TCheckBox *cbstart;
	TDateTimePicker *dtstart;
	TCheckBox *cbend;
	TDateTimePicker *dtend;
	TComboBox *cbsupplier;
	TComboBox *cbpress;
	TCheckBox *CheckBox1;
	TEdit *edmax;
	TEdit *edmin;
	TCheckBox *cbmax;
	TCheckBox *cbmin;
	TCheckBox *chsupplier;
	TCheckBox *chpress;
	TDBGrid *DBGrid1;
	TDBGrid *dgdetail;
	TGroupBox *书目检索条件;
	TDateTimePicker *dtpbegin;
	TCheckBox *chbegin;
	TDateTimePicker *dtpend;
	TCheckBox *chend;
	TButton *Button1;
	TButton *Button2;
	TBitBtn *BitBtn1;
	TButton *btsearch;
	TLabel *Label1;
	TDataSource *dssum;
	TADOQuery *aqsum;
	TRzDBNumericEdit *RzDBNumericEdit1;
	TLabel *Label2;
	TRzDBNumericEdit *RzDBNumericEdit2;
	TLabel *Label3;
	TRzDBNumericEdit *RzDBNumericEdit3;
	TSaveDialog *filepath;
	TRzToolButton *BtnAlignBottom;
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall dgdetailTitleClick(TColumn *Column);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall btsearchClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	int  supplierid ;
	BOOL Dupsupplier;
	int type;//1为零售调用，2为采购调用
public:		// User declarations
	__fastcall Tfrmbookup(TComponent* Owner,int Type,TADOConnection *con);
	bool __fastcall DbgridToExcel(TDBGrid* dbg);
	TfrmZNProcureMng *pro;
	int stgid ;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmbookup *frmbookup;
//---------------------------------------------------------------------------
#endif
