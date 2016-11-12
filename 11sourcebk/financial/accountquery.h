//---------------------------------------------------------------------------

#ifndef accountqueryH
#define accountqueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzCmboBx.hpp"
#include "RzRadChk.hpp"
#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TAccQuery : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExit;
	TADOQuery *aquery;
	TDataSource *ds1;
	TDataSource *ds2;
	TADOQuery *adoquery1;
	TADOQuery *adoquery2;
	TRzToolButton *BtnAlignBottom;
	TSaveDialog *savedlg;
	TRzToolButton *BtnExport;
	TRzDBGrid *RzDBGrid1;
	TRzDBGrid *RzDBGrid2;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TSpeedButton *spselectClient;
	TRzCheckBox *CBstart;
	TDateTimePicker *DTPstart;
	TRzCheckBox *CBend;
	TDateTimePicker *DTPend;
	TRzComboBox *CBstyle;
	TRzComboBox *CBclass;
	TRzComboBox *CBcustom;
	TRzComboBox *CBaudit;
	TEdit *edquery;
	TEdit *edtclient;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall RzDBGrid1CellClick(TColumn *Column);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall DTPstartChange(TObject *Sender);
	void __fastcall DTPendChange(TObject *Sender);
private:	// User declarations
	int type,ClientID;
	String Disc;
	TADOConnection *fcon;
	bool ChangeDisplay;
public:		// User declarations
	__fastcall TAccQuery(TComponent* Owner,int Type,TADOConnection *cn,int stgid,bool master);
	void ClientView();
	bool DbgridToExcel(TRzDBGrid* dbg);
	int fstgid;
	bool fmaster;
};
//---------------------------------------------------------------------------
extern PACKAGE TAccQuery *AccQuery;
//---------------------------------------------------------------------------
#endif
