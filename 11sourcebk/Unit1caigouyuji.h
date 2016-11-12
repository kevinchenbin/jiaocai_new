//---------------------------------------------------------------------------

#ifndef Unit1caigouyujiH
#define Unit1caigouyujiH
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
#include "RzButton.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmcaigouyuji : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *aq;
	TADOConnection *con;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnAlignBottom;
	TGroupBox *GroupBox1;
	TCheckBox *chsupplier;
	TRzEdit *edsupplier;
	TComboBox *cbsupplier;
	TCheckBox *chday;
	TEdit *edminday;
	TLabel *Label1;
	TEdit *edmaxday;
	TCheckBox *chorderstart;
	TDateTimePicker *dtporderstart;
	TCheckBox *chorderend;
	TDateTimePicker *dtporderend;
	TCheckBox *chyujistart;
	TDateTimePicker *dtpyjstart;
	TCheckBox *chyjend;
	TDateTimePicker *dtpyjend;
	TSaveDialog *savedlg;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall edsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall DBGrid1TitleClick(TColumn *Column);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmcaigouyuji(TComponent* Owner,TADOConnection *cn,int stgid);
	int fstgid;
	void Query();
	bool DbgridToExcel(TDBGrid* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmcaigouyuji *frmcaigouyuji;
//---------------------------------------------------------------------------
#endif
