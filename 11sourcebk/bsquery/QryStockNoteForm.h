//---------------------------------------------------------------------------

#ifndef QryStockNoteFormH
#define QryStockNoteFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzEdit.hpp"
#include "RzRadChk.hpp"
#include <Mask.hpp>
#include "RzDBCmbo.hpp"
#include "RzLine.hpp"
#include <DBCtrls.hpp>
#include "RzTabs.hpp"
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzCmboBx.hpp"
#include <Buttons.hpp>
#include <ImgList.hpp>
#include <Dialogs.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfrmQryCheckNote : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *tlbtnQry;
	TRzToolButton *tlbtnExport;
	TRzToolButton *tlbtnExit;
	TRzGroupBox *grpbx1;
	TRzCheckBox *chckbxStartTime;
	TRzDateTimeEdit *dtedtStart;
	TRzCheckBox *chckbxEndTime;
	TRzDateTimeEdit *dtedtEnd;
	TLabel *lbl1;
	TLabel *lbl2;
	TRzCheckBox *chckbxBookName;
	TRzCheckBox *chckbxISBN;
	TRzCheckBox *chckbxCustomer;
	TRzCheckBox *chckbxBkstack;
	TRzCheckBox *chckbxUserDefNum;
	TRzCheckBox *chckbxPrice;
	TRzCheckBox *chckbxAuthor;
	TRzCheckBox *chckbxAmount;
	TRzCheckBox *chckbxPress;
	TRzCheckBox *chckbxType;
	TRzCheckBox *chckbxRemarks;
	TRzCheckBox *chckbxStorage;
	TRzEdit *edtBookName;
	TRzEdit *edtISBN;
	TRzEdit *edtUserDefNum;
	TRzEdit *edtAuthor;
	TRzEdit *edtPress;
	TRzEdit *edtRemarks;
	TADODataSet *dsetByNtHeader;
	TDataSource *dsrcByNtHeader;
	TADODataSet *dsetByNote;
	TDataSource *dsrcByNote;
	TADODataSet *dsetByCustomer;
	TDataSource *dsrcByCustomer;
	TADODataSet *dsetByBktype;
	TDataSource *dsrcByBktype;
	TDataSource *dsrcByPress;
	TADOStoredProc *spQryNote;
	TRzEdit *edtCustomer;
	TLabel *lbl3;
	TLabel *lbl4;
	TRzNumericEdit *numedtMinPrice;
	TRzNumericEdit *numedtMinAmount;
	TRzNumericEdit *numedtMaxPrice;
	TRzNumericEdit *numedtMaxAmount;
	TRzDBLookupComboBox *dblkpcbbPress;
	TRzDBLookupComboBox *dblkpcbbCustomer;
	TRzDBLookupComboBox *dblkpcbbStorage;
	TRzDBLookupComboBox *dblkpcbbBookstack;
	TRzDBLookupComboBox *dblkpcbbBookType;
	TADODataSet *dsetCustomer;
	TDataSource *dsrcCustomer;
	TDataSource *dsrcPress;
	TADODataSet *dsetBookType;
	TDataSource *dsrcBookType;
	TDataSource *dsrcStorage;
	TADODataSet *dsetStorage;
	TDataSource *dsrcBookstack;
	TADODataSet *dsetBookstack;

	TADOQuery *qryItems;
	TImageList *ImageList1;
	TADODataSet *dsetPress;
	TADODataSet *dsetByPress;
	TRzPageControl *pgcntrlResult;
	TRzTabSheet *tbshtByNtHeader;
	TRzTabSheet *tbshtByNote;
	TRzTabSheet *tbshtByBktype;
	TRzTabSheet *tbshtByPress;
	TCheckBox *chstaff;
	TComboBox *cbstaff;
	TRzToolButton *BtnAlignBottom;
	TRadioGroup *rgtype;
	TSaveDialog *savedlg;
	TCheckBox *cbdamage;
	TLabel *Label7;
	TLabel *Label8;
	TRzNumericEdit *minnu;
	TRzNumericEdit *maxnu;
	TCheckBox *chchayi;
	TLabel *Label9;
	TLabel *Label10;
	TCheckBox *chyingkui;
	TRzNumericEdit *numykmax;
	TRzNumericEdit *numykmin;
	TDBGridEh *dbgrdByNtHeader;
	TDBGridEh *dbgrdByNote;
	TDBGridEh *dbgrdByBktype;
	TDBGridEh *dbgrdByPress;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	void __fastcall tlbtnQryClick(TObject *Sender);
	void __fastcall chckbxBkstackClick(TObject *Sender);
	void __fastcall tlbtnExportClick(TObject *Sender);
	void __fastcall tlbtnExitClick(TObject *Sender);
	void __fastcall edtPressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edtBookNameChange(TObject *Sender);
	void __fastcall edtUserDefNumChange(TObject *Sender);
	void __fastcall edtISBNChange(TObject *Sender);
	void __fastcall numedtMinPriceChange(TObject *Sender);
	void __fastcall numedtMaxPriceChange(TObject *Sender);
	void __fastcall numedtMinAmountChange(TObject *Sender);
	void __fastcall numedtMaxAmountChange(TObject *Sender);
	void __fastcall edtAuthorChange(TObject *Sender);
	void __fastcall edtRemarksChange(TObject *Sender);
	void __fastcall dblkpcbbPressClick(TObject *Sender);
	void __fastcall dblkpcbbBookstackClick(TObject *Sender);
	void __fastcall dblkpcbbBookTypeClick(TObject *Sender);
	void __fastcall dblkpcbbStorageClick(TObject *Sender);
	void __fastcall dblkpcbbCustomerClick(TObject *Sender);
	void __fastcall dbgrdByNtHeader1TitleClick(TColumn *Column);
	void __fastcall dbgrdByCustomerTitleClick(TColumn *Column);
	void __fastcall cbstaffClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dbgrdByNtHeaderDblClick(TObject *Sender);
	void __fastcall dbgrdByNtHeaderTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByNoteTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByBktypeTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByPressTitleClick(TColumnEh *Column);
	void __fastcall N1Click(TObject *Sender);

private:	// User declarations
	void Query();
	String QueryDesic();
	String Desic,Desic1;
public:		// User declarations
	__fastcall TfrmQryCheckNote(TComponent* Owner);
	bool __fastcall DbgridToExcel(TDBGridEh* dbg);
	virtual void Init(LandInfo* li);

	TADOConnection *fcon;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmQryCheckNote *frmQryCheckNote;
//---------------------------------------------------------------------------
#endif
