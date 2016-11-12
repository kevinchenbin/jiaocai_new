//---------------------------------------------------------------------------

#ifndef accountdetailH
#define accountdetailH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include <ComCtrls.hpp>
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzRadChk.hpp"
#include <Buttons.hpp>
#include "RpBase.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpSystem.hpp"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TAccDetail : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExit;
	TDataSource *ds1;
	TDataSource *da2;
	TADOQuery *Querybase;
	TADOQuery *Querydetail;
	TADOQuery *aquery;
	TADOQuery *Querybance;
	TRzToolButton *BtnExport;
	TADOQuery *aq;
	TRvSystem *RvSystem1;
	TRvProject *RvProject1;
	TRvDataSetConnection *dc;
	TADOQuery *aqprint;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnPrintPreview;
	TRzToolButton *BtnAlignBottom;
	TRzDBGrid *DBGridbase;
	TRzDBGrid *DBGriddetail;
	TSaveDialog *savedlg;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TSpeedButton *spselectClient;
	TDateTimePicker *DTPstart;
	TDateTimePicker *DTPend;
	TRzCheckBox *CBstart;
	TRzCheckBox *CBend;
	TRzComboBox *CBcustom;
	TRzComboBox *CBstate;
	TEdit *edquery;
	TEdit *edtclient;
	TCheckBox *chguolv;
	TGroupBox *GroupBox2;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TRzEdit *etshiyang;
	TRzEdit *etchecked;
	TRzEdit *etleftmoney;
	TRzEdit *etaddcost;
	TRzEdit *etcount;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall DBGridbaseCellClick(TColumn *Column);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall BtnPrintPreviewClick(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall DTPstartChange(TObject *Sender);
	void __fastcall DTPendChange(TObject *Sender);
	void __fastcall DBGridbaseTitleClick(TColumn *Column);
	void __fastcall DBGriddetailTitleClick(TColumn *Column);
private:	// User declarations
	int type,type1;
	String Disc;
	TADOConnection *fcon;
	bool ChangeDisplay;
	AnsiString sqlwhere;
	AnsiString sql1,sql;
public:		// User declarations
	__fastcall TAccDetail(TComponent* Owner,int Type,TADOConnection *cn,int stgid);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	void PrintFunction(int  type);
	AnsiString stogName,Maker;
	int fstgid;
	int ClientID;
	void ClientView();
	String storageformat,saleformat;
};
//---------------------------------------------------------------------------
extern PACKAGE TAccDetail *AccDetail;
//---------------------------------------------------------------------------
#endif
