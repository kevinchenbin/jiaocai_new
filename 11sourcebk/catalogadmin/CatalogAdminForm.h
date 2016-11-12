//---------------------------------------------------------------------------

#ifndef CatalogAdminFormH
#define CatalogAdminFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBChk.hpp"
#include "RzRadChk.hpp"
#include "RzCmboBx.hpp"
#include "RzRadGrp.hpp"
#include "RzLine.hpp"
#include "RzDBCmbo.hpp"
#include <DBCtrls.hpp>
#include "RzShellDialogs.hpp"
#include "RzSpnEdt.hpp"
#include "RzDBDTP.hpp"
#include "RzDTP.hpp"
#include <ComCtrls.hpp>
#include "RzCommon.hpp"
#include "RzLookup.hpp"
#include "MDIChild.h"
#include "RzDBLook.hpp"
#include <DBTables.hpp>
#include "RzDBSpin.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmCatalogAdmin : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzGroupBox *x;
	TRzLabel *RzLabel1;
	TRzLabel *RzLabel2;
	TRzLabel *RzLabel3;
	TRzLabel *RzLabel5;
	TRzLabel *RzLabel6;
	TRzLabel *RzLabel7;
	TRzLabel *RzLabel8;
	TRzLabel *RzLabel9;
	TRzLabel *RzLabel11;
	TRzDBEdit *edtBarcode;
	TRzDBEdit *dbedtISBN;
	TRzDBEdit *dbedtName;
	TRzDBEdit *dbedtUserDefCode;
	TRzDBEdit *dbedtAuthor;
	TADODataSet *dsetCatlog;
	TRzToolbar *rztlbr1;
	TRzLabel *lbl1;
	TRzComboBox *cbQueryType;
	TRzEdit *edtQuery;
	TRzButton *btnPressAdd;
	TDataSource *dsCatlog;
	TLabel *Label1;
	TRzDBCheckBox *rzdbchckbx1;
	TRzGroupBox *RzGroupBox1;
	TRzRadioGroup *RzRadioGroup1;
	TRzLine *rzln1;
	TRzDBLookupComboBox *cbbsmallBookTypeID;
	TRzButton *btn1;
	TADOTable *tblCatalogType;
	TDataSource *dsrcCatalogType;
	TRzButton *btn2;
	TRzDBEdit *dbedtPrice;
	TRzToolButton *btnExit2;
	TRzToolButton *btnExit3;
	TRzToolButton *btnExit5;
	TRzToolButton *btnExit6;
	TRzSaveDialog *svdlgCatlog;
	TRzDBLookupComboBox *cbbPressID;
	TRzSpinEdit *edtPressCount;
	TADOTable *tblPress;
	TDataSource *dsrcPress;
	TRzDBDateTimePicker *dbdtmpckrDate;
	TRzLookupDialog *lkpdlgCatlog;
	TRzLookupDialog *rzlkpdlg1;
	TRzDBLookupDialog *dblkpdlg1;
	TButton *btn3;
	TRzDBGrid *dbgrdPressQuery;
	TADOQuery *qryPressQuery;
	TDataSource *dsPressQuery;
	TRzEdit *edtPress;
	TRzDBGrid *dbgrdCatlog;
	TADODataSet *dsetDeleteCatlog;
	TButton *btnModify;
	TRzCheckBox *chckbxModify;
	TImageList *ImageListcatalog;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnJumptoLine;
	TRzToolButton *BtnWarning;
	TRzCheckBox *chckbxInput;
	TRzToolButton *BtnNew;
	TEdit *editbookname;
	TEdit *editprice;
	TEdit *editauthor;
	TEdit *editselfcode;
	TRzToolButton *BtnViewDetails;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnAddClick(TObject *Sender);
	void __fastcall btnExcelExportClick(TObject *Sender);
	void __fastcall btnPressAddClick(TObject *Sender);
	void __fastcall edtQueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btnRemoveClick(TObject *Sender);
 //	void __fastcall RzDBCheckBox4Click(TObject *Sender);
 //	void __fastcall chckbxShowUnavailableClick(TObject *Sender);
 //	void __fastcall chckbxDShowUnavailableClick(TObject *Sender);
	void __fastcall RzRadioGroup1Click(TObject *Sender);
	void __fastcall edtPriceClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);

	void __fastcall cbb1Click(TObject *Sender);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall btn2Click(TObject *Sender);
	void __fastcall edtBarcodeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btnExit2Click(TObject *Sender);
	void __fastcall btnExit3Click(TObject *Sender);
	void __fastcall dbedtNameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btn3Click(TObject *Sender);
	void __fastcall dbedtPriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbedtAuthorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbbPressIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbbsmallBookTypeIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbdtmpckrDateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btnExit6Click(TObject *Sender);
	void __fastcall btnExit5Click(TObject *Sender);
   //	void __fastcall cbQueryTypeClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btnModifyClick(TObject *Sender);
	void __fastcall dbgrdCatlogCellClick(TColumn *Column);
	void __fastcall dsCatlogDataChange(TObject *Sender, TField *Field);
	void __fastcall dsetCatlogBeforeScroll(TDataSet *DataSet);
	void __fastcall dbgrdCatlogMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta,
          TPoint &MousePos, bool &Handled);
   //	void __fastcall FormShow(TObject *Sender);
	void __fastcall edtQueryClick(TObject *Sender);
	void __fastcall BtnJumptoLineClick(TObject *Sender);
	void __fastcall BtnWarningClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall dbedtISBNKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall editbooknameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editauthorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnViewDetailsClick(TObject *Sender);
	void __fastcall edtPressCountKeyPress(TObject *Sender, wchar_t &Key);





private:	// User declarations
	void OnHotKeyPress(DWORD vkCode);
public:		// User declarations
	__fastcall TfrmCatalogAdmin(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);
	int IsbnCount(String Barcode) ;
	int IsbnToCode(String ISBN);
	String FirstLetterFromHZ(String strKey);
	char getpy(String   hzchar);
	AnsiString GetPYString(AnsiString   HZString);
	char GetPYChar(String HZ);
	 //void DataSetToExcel(TDataSet* DataSet);
	 void Query(String condition);
	 int Query1(String condition);
	 void QueryNull();
	 void DBGrid2Excel(TDBGrid *dbg,String strXlsFile);
	 int TfrmCatalogAdmin::StringToIsbn(String str,int rs[]);
	 char TfrmCatalogAdmin::GetPYIndexChar(char *str);
	 bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	 BOOL manybook;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCatalogAdmin *frmCatalogAdmin;
//---------------------------------------------------------------------------
#endif
