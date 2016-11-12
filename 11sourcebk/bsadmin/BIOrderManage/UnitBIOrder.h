//---------------------------------------------------------------------------

#ifndef UnitBIOrderH
#define UnitBIOrderH
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
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include "RzLabel.hpp"
#include <Menus.hpp>
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzDBGrid.hpp"
#include <Dialogs.hpp>
#include <Graphics.hpp>
#include "MDIChild.h"
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <pngimage.hpp>
//---------------------------------------------------------------------------

class TfrmBIorder : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TImageList *ImageList1;
	TGroupBox *GroupBox1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TComboBox *cbvendor;
	TDateTimePicker *dtpdate;
	TDBEdit *dbeditdanhao;
	TLabel *label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TDateTimePicker *dtpfahuo;
	TLabel *Label9;
	TDBEdit *dbeditaddcost;
	TGroupBox *GroupBox2;
	TEdit *edtCatalog;
	TLabel *Label11;
	TEdit *editamount;
	TLabel *Label12;
	TEdit *editdiscount;
	TLabel *Label13;
	TLabel *Label14;
	TEdit *editstockamount;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnChangeOptions;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnClear;
	TRzToolButton *BtnOK;
	TADOQuery *aqupdatehead;
	TLabel *Label15;
	TADOStoredProc *adospaddhead;
	TDataSource *dshead;
	TSpeedButton *SpeedButton2;
	TComboBox *cbstate;
	TComboBox *cbtype;
	TRzLabel *lblCatalog;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TADOQuery *aqorderdetail;
	TDataSource *dsdetail;
	TLabel *Label10;
	TRzToolButton *BtnView;
	TComboBox *cbclient;
	TEdit *edclient;
	TLabel *Label1;
	TRzStatusBar *RzStatusBar1;
	TLabel *Label16;
	TLabel *Label17;
	TRzDBNumericEdit *RzDBNumericEdit1;
	TLabel *Label18;
	TRzDBNumericEdit *RzDBNumericEdit2;
	TLabel *Label19;
	TRzDBNumericEdit *RzDBNumericEdit3;
	TDataSource *dshd;
	TADOQuery *aqhd;
	TRzToolButton *BtnAlignBottom;
	TPopupMenu *pm1;
	TMenuItem *N5;
	TLabel *Label20;
	TLabel *Label21;
	TEdit *Edit1;
	TEdit *Edit3;
	TEdit *Edit2;
	TRzToolButton *BtnView1;
	TADOQuery *query;
	TSpeedButton *spnewbook;
	TSpeedButton *spselectClient;
	TEdit *edtclient;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TRzToolButton *BtnOK1;
	TMenuItem *N9;
	TMenuItem *N10;
	TSaveDialog *savedlg;
	TLabel *Label22;
	TRzDBNumericEdit *RzDBNumericEdit4;
	TSpeedButton *SpeedButton1;
	TMenuItem *N11;
	TMenuItem *N12;
	TLabel *Label23;
	TADOQuery *querypress;
	TEdit *edpress;
	TADOStoredProc *adospcopy;
	TADOQuery *aquery;
	TRzToolButton *BtnProperties;
	TRzLabel *lbl11;
	TRzLabel *lblOpName;
	TDBNavigator *dbn;
	TMemo *membk;
	TSpeedButton *SpeedButton3;
	TGroupBox *GroupBox3;
	TCheckBox *chfsluru;
	TCheckBox *chfsamount;
	TCheckBox *chfsdiscount;
	TCheckBox *chqikan;
	TEdit *edqikan;
	TMenuItem *N13;
	TGroupBox *GroupBox4;
	TCheckBox *ch1;
	TCheckBox *ch2;
	TCheckBox *ch3;
	TCheckBox *chfoceset;
	TCheckBox *ch4;
	TCheckBox *ch5;
	TCheckBox *ch6;
	TCheckBox *ch7;
	TCheckBox *ch8;
	TRzToolButton *BtnFinish;
	TMenuItem *N14;
	TSpeedButton *SpeedButton4;
	TRzToolButton *BtnLastRecord;
	TMenuItem *N15;
	TMenuItem *N16;
	TDBGridEh *dgdetail;
	TLabel *Label24;
	TEdit *edituseamount;
	TRadioGroup *rg;
	TEdit *editdetailbk;
	TLabel *Label25;
	TEdit *edclientbk;
	TPopupMenu *pmprview;
	TMenuItem *N17;
	TPopupMenu *pmshenhei;
	TMenuItem *N18;
	TLabel *labstate;
	TPopupMenu *pmprint;
	TMenuItem *N20;
	TImage *imagelock;
	TLabel *lblock;
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall dbnClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editamountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editdiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editdetailbkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgdetail1CellClick(TColumn *Column);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbclientClick(TObject *Sender);
	void __fastcall BtnView1Click(TObject *Sender);
	void __fastcall dbeditaddcostKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spnewbookClick(TObject *Sender);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall edtclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgdetail1DblClick(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall BtnOK1Click(TObject *Sender);
	void __fastcall N12Click(TObject *Sender);
	void __fastcall BtnPropertiesClick(TObject *Sender);
	void __fastcall membkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall chqikanClick(TObject *Sender);
	void __fastcall edqikanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall chfsluruClick(TObject *Sender);
	void __fastcall cbtypeChange(TObject *Sender);
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall ch1Click(TObject *Sender);
	void __fastcall ch2Click(TObject *Sender);
	void __fastcall ch3Click(TObject *Sender);
	void __fastcall ch4Click(TObject *Sender);
	void __fastcall ch5Click(TObject *Sender);
	void __fastcall ch6Click(TObject *Sender);
	void __fastcall ch7Click(TObject *Sender);
	void __fastcall ch8Click(TObject *Sender);
	void __fastcall BtnFinishClick(TObject *Sender);
	void __fastcall N14Click(TObject *Sender);
	void __fastcall BtnLastRecordClick(TObject *Sender);
	void __fastcall N15Click(TObject *Sender);
	void __fastcall N16Click(TObject *Sender);
	void __fastcall dgdetailCellClick(TColumnEh *Column);

	void __fastcall dgdetailTitleClick(TColumnEh *Column);
	void __fastcall dgdetailMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall edclientbkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rgClick(TObject *Sender);
	void __fastcall N17Click(TObject *Sender);
	void __fastcall N18Click(TObject *Sender);
	void __fastcall N20Click(TObject *Sender);
	void __fastcall dgdetailDblClick(TObject *Sender);

private:	// User declarations
	TADOConnection *fcon;
	int UserID;
	AnsiString UserName;
	int StgID;
	AnsiString Danhao,logmessage;
	int ClientID;
	int m_catalogSearchMode;
	int HeaderRec;
public:		// User declarations
	__fastcall TfrmBIorder(TComponent* Owner);
	void init(LandInfo* li);
	void init(LandInfo*li,AnsiString Danhao);
	void ReadyDate();
	void AddNewHead();
	AnsiString GetField(AnsiString sql,AnsiString Field);
	void ExecSQL(AnsiString sql);
	BOOL UpdateHead();
	void RefreshHead();
	void AddNote(int SupplierID,int CatalogID);
	void RefreshDetail();
	void BatchSetNotes(int amount, float discount, int mode);
	bool __fastcall DbgridToExcel2(TDBGridEh* dbg);
	void ChangeCatalogSearchMode();
	void edclientview();
	void RefreshHead(int headerid);
	void RefreshHead(AnsiString headerCode);//采购时调用的
	void DelInvalidNtHeader();
	void DelNtHeader();
	void ClientView();
	bool chongfutishi(int catalogid);
	int headid,type;
	bool lastdiscount,ordertishi,orderfind,orderchange,orderviewclass;
	AnsiString month,printtitle,contact,tel,address,printbk;
	bool Master;
	void detailClick();
        void lock(int type);
         bool newclient;
         bool  client,bookcatalogadd,bcatalogmodify;
                void checknewsupplier();
                void disablenewsupplierornewbook();
         bool  dblclicklock;
	void __fastcall dgdetailDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumnEh *Column, Gridseh::TGridDrawState State);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBIorder *frmBIorder;
//---------------------------------------------------------------------------
#endif
