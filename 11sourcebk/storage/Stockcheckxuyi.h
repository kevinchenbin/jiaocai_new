//---------------------------------------------------------------------------

#ifndef StockcheckxuyiH
#define StockcheckxuyiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
#include "RzLabel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include <DBCtrls.hpp>
#include "RpBase.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpSystem.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmStockcheckxuyi : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *调整单信息;
	TLabel *Label1;
	TEdit *editnum;
	TLabel *Label2;
	TDateTimePicker *dtpdate;
	TLabel *Label3;
	TEdit *editusername;
	TLabel *Label4;
	TDBGrid *dg;
	TPopupMenu *PM;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N6;
	TADOQuery *aqdetail;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnOK;
	TADOQuery *aq;
	TDataSource *ds;
	TADOQuery *aqhead;
	TDataSource *dshead;
	TLabel *Label5;
	TEdit *editstorage;
	TRzToolButton *BtnDelete;
	TADOStoredProc *adostoreaddnote;
	TLabel *Label8;
	TEdit *editstate;
	TRvProject *pandianproject;
	TRvSystem *RvSystem1;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnClear;
	TRvDataSetConnection *Rvstockxuyi;
	TADOQuery *adoprint;
	TRzToolButton *BtnAlignBottom;
	TEdit *edstorageid;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	TDBNavigator *DBN;
	TLabel *Label6;
	TLabel *Label7;
	TRzLabel *lblCatalog;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *edtCatalog;
	TEdit *editadjust;
	TEdit *editamount;
	TEdit *edsamount;
	TEdit *edbak;
	TGroupBox *GroupBox1;
	TMemo *membk;
	TLabel *Label11;
	TMenuItem *N4;
	TRzToolButton *BtnView;
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall dgCellClick(TColumn *Column);
	void __fastcall editadjustKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall DBNClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edsamountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edbakKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
private:	// User declarations
	TADOConnection *fcon;
	int UserID,Stgid,username;
	int supplierID,catalogID;
public:		// User declarations
	__fastcall TfrmStockcheckxuyi(TComponent* Owner);
	void TfrmStockcheckxuyi::AddNote(int supplierID,int CatalogId,int stackid,int stkid);
	int m_catalogSearchMode;
	void init(LandInfo *li);
	void ExecSQL(AnsiString sql);
	void RefreshDetail();
	void ChangeCatalogSearchMode();
	bool DbgridToExcel(TDBGrid* dbg);
	void Deletecode();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStockcheckxuyi *frmStockcheckxuyi;
//---------------------------------------------------------------------------
#endif
