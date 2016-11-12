//---------------------------------------------------------------------------

#ifndef accoutnsdueH
#define accoutnsdueH
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
#include "RzDBGrid.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzCmboBx.hpp"
#include <Buttons.hpp>
#include "RpBase.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpSystem.hpp"
#include <Dialogs.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "DataDriverEh.hpp"
#include "MemTableDataEh.hpp"
#include "MemTableEh.hpp"
//---------------------------------------------------------------------------
class TAccountDoe : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnView;
	TDataSource *ds;
	TADOQuery *aquery;
	TADOQuery *aqcustom;
	TRzToolButton *BtnExport;
	TRvDataSetConnection *rvdatacon;
	TRvProject *RvProject1;
	TRvSystem *RvSystem1;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnPrintPreview;
	TRzToolButton *BtnAlignBottom;
	TSaveDialog *savedlg;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TSpeedButton *spselectClient;
	TRzComboBox *cbCusName;
	TDateTimePicker *DTPstart;
	TDateTimePicker *DTPend;
	TCheckBox *CBstart;
	TCheckBox *CBend;
	TEdit *edquery;
	TEdit *edtclient;
	TLabel *Label4;
	TRzComboBox *cbInOut;
	TLabel *Label2;
	TCheckBox *chname;
	TCheckBox *chhuizong;
	TCheckBox *chprofite;
	TDBGridEh *DBGridtotal;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall BtnPrintPreviewClick(TObject *Sender);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall DTPstartChange(TObject *Sender);
	void __fastcall DTPendChange(TObject *Sender);
	void __fastcall DBGridtotalTitleClick(TColumnEh *Column);
private:	// User declarations
	TADOConnection *fcon;
	int type;
	String Disc;
public:		// User declarations
	__fastcall TAccountDoe(TComponent* Owner,int Type,TADOConnection *cn,int stgid);
	bool __fastcall DbgridToExcel(TDBGridEh* dbg);
	AnsiString querysql,username,stogName;
	int fstgid;
	int ClientID;
	void ClientView();
};
//---------------------------------------------------------------------------
extern PACKAGE TAccountDoe *AccountDoe;
//---------------------------------------------------------------------------
#endif
