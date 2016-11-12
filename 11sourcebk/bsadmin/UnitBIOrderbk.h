//---------------------------------------------------------------------------

#ifndef UnitBIOrderbkH
#define UnitBIOrderbkH
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
//---------------------------------------------------------------------------
class TfrmBIorderbk : public TForm
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
	TRzToolButton *BtnUpOneLevel;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnClear;
	TRzSpacer *RzSpacer1;
	TRzSpacer *RzSpacer2;
	TDBNavigator *dbn;
	TRzToolButton *BtnOK;
	TADOQuery *aqupdatehead;
	TLabel *Label15;
	TDBEdit *dbbk;
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
	TEdit *editdetailbk;
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
	TRzDBGrid *dgdetail;
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
	void __fastcall BtnUpOneLevelClick(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgdetailCellClick(TColumn *Column);
private:	// User declarations
	TADOConnection *fcon;
	int UserID;
	AnsiString UserName;
	int StgID;
	AnsiString Danhao;
	int ClientID;
	int m_catalogSearchMode;
	int HeaderRec;
public:		// User declarations
	__fastcall TfrmBIorderbk(TComponent* Owner);
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
	bool __fastcall DbgridToExcel(TDBGrid* dbg,AnsiString Title);
	void ChangeCatalogSearchMode();
	void edclientview();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBIorderbk *frmBIorderbk;
//---------------------------------------------------------------------------
#endif
