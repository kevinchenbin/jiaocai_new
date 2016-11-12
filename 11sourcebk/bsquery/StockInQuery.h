//---------------------------------------------------------------------------

#ifndef StockInQueryH
#define StockInQueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzRadChk.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include "RzDBDTP.hpp"
#include "RzDTP.hpp"
#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBCmbo.hpp"
#include <DBCtrls.hpp>
#include <ImgList.hpp>

#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <Dialogs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfrmStockInQuery : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *btnExit1;
	TRzToolButton *btnExit2;
	TRzToolButton *btnExit3;
	TRzToolButton *btnExit4;
	TRzGroupBox *rzgrpbx4;
	TLabel *lbl1;
	TLabel *lbl2;
	TRzCheckBox *chckbxBookName;
	TRzCheckBox *chckbxISBN;
	TRzCheckBox *chckbxSupplier;
	TRzCheckBox *chckbxUserDefNum;
	TRzCheckBox *chckbxPrice;
	TRzCheckBox *chckbxAuthor;
	TRzCheckBox *chckbxAmount;
	TRzCheckBox *chckbxPressCount;
	TRzCheckBox *chckbxType;
	TRzCheckBox *chckbxShopNum;
	TRzEdit *edtBookName;
	TRzEdit *edtISBN;
	TRzEdit *edtSupplier1;
	TRzEdit *edtUserDefNum;
	TRzEdit *edtPrice;
	TRzEdit *edtAuthor;
	TRzEdit *edtAmountHigh;
	TRzEdit *edtPressCount1;
	TRzEdit *edtType1;
	TADOQuery *qry1;
	TDataSource *ds1;
	TADOTable *tbl2supplier;
	TADOTable *tbl1supplier;
	TDataSource *ds2supplier;
	TDataSource *ds3supplier;
	TRzDBLookupComboBox *edtSupplier;
	TADODataSet *dsetCatlog;
	TADOTable *tblPress;
	TADOTable *tblCatalogType;
	TDataSource *dsrcPress;
	TDataSource *dsCatlog;
	TDataSource *dsrcCatalogType;
	TADOQuery *aquery;
	TADOTable *tblStore;
	TDataSource *dsstore;
	TRzDBLookupComboBox *edtstore;
	TRzCheckBox *rzlocal;
	TADOTable *tbllocal;
	TDataSource *dslocal;
	TRzDBLookupComboBox *edtlocal;
	TImageList *ImageList1;
	TDBGridEh *DBGridEh1;
	TRzToolButton *BtnAlignBottom;
	TRzDBLookupComboBox *edtPressCount;
	TRzDBLookupComboBox *edtType;
	TADOQuery *aq1supplier;
	TADOQuery *aqpress;
	TSaveDialog *savedlg;
	TCheckBox *chmutisupplier;
	TCheckBox *chlocal;
	TCheckBox *chharm;
	TCheckBox *chdam;
	TADOStoredProc *adospcopy;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TEdit *edtAmountLow;
	TMenuItem *N2;
	TCheckBox *chother;
	TMenuItem *N3;
	TCheckBox *chzero;
	TMenuItem *N4;
	TMenuItem *N5;
	TRzToolButton *BtnOK;
	TDBGridEh *DBGridEh2;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnExit4Click(TObject *Sender);
	void __fastcall btnExit1Click(TObject *Sender);
	void __fastcall edtISBNKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtAmountHighKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btnExit2Click(TObject *Sender);
	void __fastcall edtBookNameChange(TObject *Sender);
	void __fastcall edtPriceChange(TObject *Sender);
	void __fastcall edtPressCountClick(TObject *Sender);
	void __fastcall edtstoreClick(TObject *Sender);
	void __fastcall edtISBNChange(TObject *Sender);
	void __fastcall edtAuthorChange(TObject *Sender);
	void __fastcall edtAmountHighChange(TObject *Sender);
	void __fastcall edtlocalClick(TObject *Sender);
	void __fastcall edtSupplierClick(TObject *Sender);
	void __fastcall edtTypeClick(TObject *Sender);
	void __fastcall edtUserDefNumChange(TObject *Sender);
	void __fastcall DBGridEh1TitleClick(TColumnEh *Column);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtSupplier1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtPressCount1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall DBGridEh1DblClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall DBGridEh1CellClick(TColumnEh *Column);
	void __fastcall edtAmountLowChange(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);

	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall DBGridEh1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumnEh *Column, Gridseh::TGridDrawState State);

private:	// User declarations
	String m_sql;
	void OnHotKeyPress(DWORD vkCode);
public:		// User declarations
	__fastcall TfrmStockInQuery(TComponent* Owner);
	void Init(LandInfo* li);
   	bool GetID(String str);
	String QueryDesic();
	String Desic;
	bool msupplier;
        int fuserid;
    //	void  RPGrid(TRzDBGrid *dg,TQRPGrid *PRdg );
	bool __fastcall DbgridToExcel(TDBGridEh* dbg);

	AnsiString sbkinfoid;
	TStringList *strlist;
	 TStringList *st;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStockInQuery *frmStockInQuery;
//---------------------------------------------------------------------------
#endif
