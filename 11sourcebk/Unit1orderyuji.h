//---------------------------------------------------------------------------

#ifndef Unit1orderyujiH
#define Unit1orderyujiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzEdit.hpp"
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include "RzButton.hpp"
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmorderyuji : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *aq;
	TADOConnection *con;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TCheckBox *chclient;
	TCheckBox *chday;
	TEdit *edminday;
	TEdit *edmaxday;
	TCheckBox *chorderstart;
	TDateTimePicker *dtporderstart;
	TCheckBox *chorderend;
	TDateTimePicker *dtporderend;
	TCheckBox *chyujistart;
	TDateTimePicker *dtpyjstart;
	TCheckBox *chyjend;
	TDateTimePicker *dtpyjend;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TSpeedButton *spselectClient;
	TRzEdit *edtQryVendor;
	TEdit *edtclient;
	TSaveDialog *savedlg;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall edtQryVendorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall DBGrid1TitleClick(TColumn *Column);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmorderyuji(TComponent* Owner,TADOConnection *cn,int stgid);
	int fstgid,ClientID;
	void ClientView();
	void Query();
	bool  DbgridToExcel(TDBGrid* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmorderyuji *frmorderyuji;
//---------------------------------------------------------------------------
#endif
