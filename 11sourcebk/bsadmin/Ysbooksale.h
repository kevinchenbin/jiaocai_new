//---------------------------------------------------------------------------

#ifndef YsbooksaleH
#define YsbooksaleH
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
#include "RpBase.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpSystem.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
//---------------------------------------------------------------------------
class TfrmYsbooksale : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TImageList *ImageList1;
	TGroupBox *GroupBox1;
	TLabel *Label2;
	TLabel *Label3;
	TComboBox *cbvendor;
	TDBEdit *dbeditdanhao;
	TLabel *label5;
	TLabel *Label9;
	TDBEdit *dbeditaddcost;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnChangeOptions;
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
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TADOQuery *aqorderdetail;
	TDataSource *dsdetail;
	TRzToolButton *BtnView;
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
	TDateTimePicker *dtpdate;
	TRzLabel *lbl3;
	TLabel *Label6;
	TEdit *edstorageid;
	TEdit *edstoragename;
	TDBEdit *dbeCodeStr;
	TADOStoredProc *spsave;
	TADOQuery *aq;
	TDataSource *dshd;
	TADOQuery *aqhd;
	TPopupMenu *Popmenu;
	TMenuItem *N5;
	TRvSystem *RvSystem1;
	TRvProject *RvProject1;
	TRvDataSetConnection *dscon;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnView1;
	TSpeedButton *spselectClient;
	TEdit *edtclient;
	TMenuItem *N6;
	TMenuItem *N7;
	TADOStoredProc *spcopy;
	TRzToolButton *BtnChange;
	TLabel *Label4;
	TEdit *edopname;
	TDBNavigator *dbn;
	TLabel *Label11;
	TLabel *Label14;
	TRzLabel *lblCatalog;
	TEdit *edtCatalog;
	TEdit *editamount;
	TEdit *editstockamount;
	TMemo *membk;
	TCheckBox *chqikan;
	TEdit *edqikan;
	TMenuItem *N8;
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
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgdetailCellClick(TColumn *Column);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnView1Click(TObject *Sender);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall edtclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbeditaddcostKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall BtnChangeClick(TObject *Sender);
	void __fastcall dgdetailTitleClick(TColumn *Column);
	void __fastcall membkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall chqikanClick(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall edqikanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgdetailKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
	TADOConnection *fcon;
	int UserID;
	AnsiString UserName;
	int StgID;
	AnsiString Danhao;
	int ClientID;
	int m_catalogSearchMode;
	int HeaderRec;
	int stackid;
public:		// User declarations
	__fastcall TfrmYsbooksale(TComponent* Owner);
	void init(LandInfo* li);
	void init(LandInfo*li,AnsiString Danhao);
	void ReadyDate();
	void AddNewHead();
	AnsiString GetField(AnsiString sql,AnsiString Field);
	void ExecSQL(AnsiString sql);
	BOOL UpdateHead();
	void RefreshHead();
	void RefreshHead(int headid);
	void AddNote(int bkinfoid);
	void RefreshDetail();
	void BatchSetNotes(int amount);
	bool __fastcall DbgridToExcel(TDBGrid* dbg,AnsiString Title);
	void ChangeCatalogSearchMode();
	void Printorview(int type);
	void edclientview();
	void DelInvalidNtHeader();
	int headerid;
	bool ChangeDisplay;
	void ClientView();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmYsbooksale *frmYsbooksale;
//---------------------------------------------------------------------------
#endif
