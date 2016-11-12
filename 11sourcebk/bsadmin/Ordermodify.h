//---------------------------------------------------------------------------

#ifndef OrdermodifyH
#define OrdermodifyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class Tfrmordermodify : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TRzToolButton *BtnView;
	TGroupBox *GroupBox1;
	TRadioGroup *RadioGroup1;
	TLabel *Label1;
	TComboBox *cbuser;
	TCheckBox *chordercode;
	TEdit *edordercode;
	TCheckBox *chbk;
	TEdit *edbk;
	TCheckBox *chclient;
	TEdit *edclient;
	TCheckBox *chdate;
	TDateTimePicker *dtpdate;
	TDBGrid *DBGrid1;
	TDataSource *ds1;
	TADOQuery *aq1;
	TDBGrid *DBGrid2;
	TDataSource *ds2;
	TADOQuery *aq2;
	TADOConnection *con;
	TRzToolButton *BtnOK;
	TRzToolButton *BtnCancel;
	TSpeedButton *spselectClient;
	TEdit *edtclient;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnExport1;
	TPopupMenu *Pop;
	TMenuItem *N2;
	TSaveDialog *filepath;
	TRzToolButton *BtnAlignNone;
	TRzDateTimeEdit *dtedtDate;
	TRzSpinEdit *spedtID;
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall DBGrid2DblClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall BtnCancelClick(TObject *Sender);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall BtnExport1Click(TObject *Sender);
	void __fastcall BtnAlignNoneClick(TObject *Sender);
	void __fastcall edbkChange(TObject *Sender);
	void __fastcall edtclientChange(TObject *Sender);
	void __fastcall edordercodeChange(TObject *Sender);
	void __fastcall dtpdateChange(TObject *Sender);
	void __fastcall dtedtDateChange(TObject *Sender);
	void __fastcall spedtIDChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmordermodify(TComponent* Owner,TADOConnection *cn,int stgid);
	int fstgid,ClientID;
	void ClientView();
	void DbgridToExcel();
	void DbgridToExcel(AnsiString headerid);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmordermodify *frmordermodify;
//---------------------------------------------------------------------------
#endif
