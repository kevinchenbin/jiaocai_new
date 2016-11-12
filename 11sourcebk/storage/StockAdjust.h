//---------------------------------------------------------------------------

#ifndef StockAdjustH
#define StockAdjustH
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
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmStockAdjust : public TForm
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
	TRzToolButton *BtnAlignBottom;
	TLabel *Label5;
	TEdit *Edit1;
	TEdit *Edit2;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	TLabel *Label10;
	TEdit *edstate;
	TDBNavigator *DBN;
	TLabel *Label6;
	TLabel *Label7;
	TRzLabel *lblCatalog;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *edtCatalog;
	TEdit *editadjust;
	TEdit *editamount;
	TEdit *edsamount;
	TEdit *edbak;
	TGroupBox *GroupBox1;
	TLabel *Label11;
	TLabel *Label12;
	TMemo *membk;
	TMenuItem *N4;
	TRzToolButton *BtnView;
	TRzToolButton *BtnDelete;
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
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall DBNClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edsamountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edbakExit(TObject *Sender);
	void __fastcall edsamountClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall membkExit(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
private:	// User declarations
	TADOConnection *fcon;
	int UserID,Stgid,username;
	int supplierID,catalogID;
public:		// User declarations
	__fastcall TfrmStockAdjust(TComponent* Owner);
	void AddNote(int supplierID,int CatalogId,int bkinfoid,int amount);
	int m_catalogSearchMode;
	void init(LandInfo *li);
	void ExecSQL(AnsiString sql);
	void RefreshDetail();
	bool DbgridToExcel(TDBGrid* dbg);
	void Deletenote();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStockAdjust *frmStockAdjust;
//---------------------------------------------------------------------------
#endif
