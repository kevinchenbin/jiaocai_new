//---------------------------------------------------------------------------

#ifndef UnitwanglaiH
#define UnitwanglaiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "pdtypes.h"
//#include <DBGrids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RpBase.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpSystem.hpp"
#include <SysUtils.hpp>
#include <Grids.hpp>
#include <DBGrids.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>


//---------------------------------------------------------------------------
class Tfrmwanglaizhang : public TForm
{
__published:	// IDE-managed Components
	TDataSource *DataSource2;
	TADOQuery *query;
	TRvProject *duizhang;
	TRvSystem *RvSystem1;
	TRvDataSetConnection *Rvcondizhang;
	TADOQuery *aqprint;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnView;
	TRzToolButton *BtnPrintPreview;
	TRzToolButton *BtnPrint;
	TADOConnection *fcon;
	TPopupMenu *pm;
	TMenuItem *N1;
	TRzToolButton *BtnProperties;
	TRzToolButton *BtnNextRecord;
	TPopupMenu *pmfapiao;
	TMenuItem *N2;
	TMenuItem *N3;
	TPopupMenu *pmdz;
	TMenuItem *N4;
	TMenuItem *N5;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TLabel *Label7;
	TLabel *Label6;
	TLabel *Label5;
	TLabel *Label4;
	TLabel *Label3;
	TLabel *Label1;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *editfax;
	TEdit *edittel;
	TEdit *editaddress;
	TEdit *editcontact;
	TEdit *editzhanhao;
	TEdit *edityijie;
	TEdit *editweijie;
	TEdit *edityue;
	TGroupBox *GroupBox5;
	TSpeedButton *spselectClient;
	TLabel *Label15;
	TLabel *Label16;
	TCheckBox *chclient;
	TEdit *editjianshuo;
	TComboBox *cbdanwei;
	TDateTimePicker *dtpend;
	TDateTimePicker *dtpbegin;
	TCheckBox *chstart;
	TCheckBox *chend;
	TCheckBox *chstate;
	TCheckBox *chfapiao;
	TComboBox *cbstate;
	TComboBox *cbfapiao;
	TEdit *edtclient;
	TCheckBox *ch1;
	TCheckBox *ch3;
	TCheckBox *ch2;
	TCheckBox *chjiekuan;
	TComboBox *cbjiekuanstate;
	TCheckBox *chfapiaohao;
	TEdit *edfapiaohao;
	TCheckBox *chshiyang;
	TEdit *edmin;
	TEdit *edmax;
	TDBGrid *dg;
	TDBGrid *dg2;
	TDataSource *ds2;
	TADOQuery *query2;
	TMenuItem *N6;
	TMenuItem *N7;
	TADOStoredProc *adosp;
	TADOQuery *adoquerymain;
	TMenuItem *N8;
	void __fastcall editjianshuoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbdanweiSelect(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall BtnPrintPreviewClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall BtnPropertiesClick(TObject *Sender);
	void __fastcall BtnNextRecordClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall cbstateChange(TObject *Sender);
	void __fastcall cbjiekuanstateChange(TObject *Sender);
	void __fastcall cbfapiaoChange(TObject *Sender);
	void __fastcall dtpbeginChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall edfapiaohaoChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall edtclientChange(TObject *Sender);
	void __fastcall cbdanweiChange(TObject *Sender);
	void __fastcall edminKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edminChange(TObject *Sender);
	void __fastcall queryAfterPost(TDataSet *DataSet);
	void __fastcall dgMouseLeave(TObject *Sender);
	void __fastcall dgTitleClick(TColumn *Column);
	void __fastcall dgDblClick(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);

	void __fastcall N7Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
private:	// User declarations
   LandInfo  userInfo;
   int Client,ClientID,stgid;
   String format;
   bool ChangeDisplay;
   bool ButtonType1,ButtonType2,ButtonType3;
   AnsiString sql;
   AnsiString StorageName;
public:		// User declarations
	__fastcall Tfrmwanglaizhang(TComponent* Owner,int type);
	void init(LandInfo* li);
	void GetClientInfor(AnsiString KeyWord);
	void GetClientDetail(int vendor);
	void Print(int type,int print);
	void ancode();
	void ClientView();
	bool DbgridToExcel(TDBGrid* dbg);
		void __fastcall dgDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmwanglaizhang *frmwanglaizhang;
//---------------------------------------------------------------------------
#endif
