//---------------------------------------------------------------------------

#ifndef QryCOderNoteFormH
#define QryCOderNoteFormH
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
class TfrmCQryOderNote : public TfrmMDIChild
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
	TRzPageControl *pgcntrlResult;
	TRzTabSheet *tbshtByNtHeader;
	TRzTabSheet *tbshtByNote;
	TRzTabSheet *tbshtByCustomer;
	TRzTabSheet *tbshtByPress;
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
	TCheckBox *chstaff;
	TComboBox *cbstaff;
	TLabel *Label36;
	TLabel *Label37;
	TCheckBox *chdiscount;
	TEdit *edmaxdiscount;
	TEdit *edmindiscount;
	TRzToolButton *BtnAlignBottom;
	TSaveDialog *savedlg;
	TCheckBox *chactive;
	TCheckBox *chnoactive;
	TSpeedButton *spselectClient;
	TEdit *edtclient;
	TSpeedButton *SpeedButton1;
	TGroupBox *GroupBox4;
	TCheckBox *ch1;
	TCheckBox *ch2;
	TCheckBox *ch3;
	TCheckBox *ch4;
	TCheckBox *ch5;
	TCheckBox *ch6;
	TCheckBox *ch7;
	TCheckBox *ch8;
	TCheckBox *chsendamount;
	TCheckBox *chunsendamount;
	TCheckBox *chunarrive;
	TCheckBox *chbaoxiao;
	TCheckBox *chxiankuan;
	TDBGridEh *dbgrdByNtHeader;
	TDBGridEh *dbgrdByNote;
	TDBGridEh *dbgrdByCustomer;
	TDBGridEh *dbgrdByPress;
	TCheckBox *chconfrim;
	TCheckBox *chlocal;
	TCheckBox *chunconfrim;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TRzCheckBox *chsupplier;
	TRzEdit *edsupplier;
	TComboBox *cbsupplier;
	TComboBox *cbstate;
	TCheckBox *chstate;
	TComboBox *cbusername;
	TADOQuery *aqclient;
	TRzCheckBox *cbbackinfo;
	TRzEdit *editbackinfo;
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
	void __fastcall cbstaffClick(TObject *Sender);
	void __fastcall edmindiscountChange(TObject *Sender);
	void __fastcall edmaxdiscountChange(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall edtclientChange(TObject *Sender);
	void __fastcall edtCustomerKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall ch1Click(TObject *Sender);
	void __fastcall ch2Click(TObject *Sender);
	void __fastcall ch3Click(TObject *Sender);
	void __fastcall ch4Click(TObject *Sender);
	void __fastcall ch5Click(TObject *Sender);
	void __fastcall ch6Click(TObject *Sender);
	void __fastcall ch7Click(TObject *Sender);
	void __fastcall ch8Click(TObject *Sender);
	void __fastcall dbgrdByNtHeaderDblClick(TObject *Sender);
	void __fastcall dbgrdByNtHeaderTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByNoteTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByCustomerTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByBktypeTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByPressTitleClick(TColumnEh *Column);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall edsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbusernameChange(TObject *Sender);

private:	// User declarations
	void Query();
	String QueryDesic();
	String Desic,Desic1;
public:		// User declarations
	__fastcall TfrmCQryOderNote(TComponent* Owner);
	bool __fastcall DbgridToExcel(TDBGridEh* dbg);
	virtual void Init(LandInfo* li);
	int totalsend ,totalunsend,ClientID ;
	TADOConnection *fcon;
	void ClientView();
	 TStringList *st;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCQryOderNote *frmCQryOderNote;
//---------------------------------------------------------------------------
#endif
