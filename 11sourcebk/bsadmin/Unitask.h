//---------------------------------------------------------------------------

#ifndef UnitaskH
#define UnitaskH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmorderask : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDateTimePicker *dtpstart;
	TCheckBox *chstart;
	TDateTimePicker *dtpend;
	TCheckBox *chend;
	TCheckBox *chpress;
	TEdit *edpress;
	TComboBox *cbpress;
	TCheckBox *chclient;
	TSpeedButton *spselectClient;
	TEdit *edclient;
	TEdit *edtclient;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExport;
	TDBGrid *DBGrid1;
	TADOConnection *fcon;
	TDataSource *ds;
	TADOQuery *query;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnAlignBottom;
	TSaveDialog *savedlg;
	TCheckBox *chuseamount;
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall DBGrid1TitleClick(TColumn *Column);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmorderask(TComponent* Owner,TADOConnection *con,int stgid,int userid);
	bool DbgridToExcel();
	void ClientView();
	int fstgid,ClientID,fuserid;
	AnsiString storagename;
	bool DbgridToExcel1();
	AnsiString sqlpress,sqldaochu,sqlgroup,sqltiaojian;
	bool checked;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmorderask *frmorderask;
//---------------------------------------------------------------------------
#endif
