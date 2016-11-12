//---------------------------------------------------------------------------

#ifndef SelectCatalogFormH
#define SelectCatalogFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ModalDialog.h"
#include "RzButton.hpp"
#include "RzLabel.hpp"
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzEdit.hpp"
#include <Mask.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
 #include "RetailMngForm.h"
#include "WholesaleMngForm.h"
 #include "StorageMngForm.h"
#include "ProcureMng.h"
#include "WholesaleMngReturnForm.h"
#include "RetailReturnMngForm.h"
#include "StorageReturnMngForm.h"
#include "StockAdjust.h"
#include "Stockcheckxuyi.h"
#include "UnitBIOrder.h"
#include "ZNStorageMngForm.h"
#include "Ysbooksale.h"

//---------------------------------------------------------------------------
class TfrmSelectCatalog : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TRzDBGrid *dbgrdQry;
	TDataSource *dsrcQry;
	TADODataSet *dsetQry;
	TADOQuery *aquery;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnProperties;
	TRzToolButton *Btnselectall;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnWeekView;
	TEdit *kcmin;
	TCheckBox *chkucun;
	TLabel *Label1;
	TEdit *kcmax;
	TEdit *edpricemin;
	TCheckBox *chprice;
	TLabel *Label2;
	TEdit *edpricemax;
	TEdit *edquery;
	TCheckBox *chpress;
	TComboBox *cbpress;
	TADOConnection *fcon;
	TCheckBox *chauthor;
	TEdit *edauthor;
	TRzToolButton *BtnView;
	void __fastcall dbgrdQryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dsetQryAfterScroll(TDataSet *DataSet);
	void __fastcall dsetQryAfterOpen(TDataSet *DataSet);
	void __fastcall edtSearchKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnselectallClick(TObject *Sender);
	void __fastcall BtnPropertiesClick(TObject *Sender);
	void __fastcall dbgrdQryDblClick(TObject *Sender);
	void __fastcall BtnWeekViewClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall kcminChange(TObject *Sender);
	void __fastcall edpriceminChange(TObject *Sender);
	void __fastcall kcminKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpriceminKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall edauthorChange(TObject *Sender);
	void __fastcall edauthorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall dbgrdQryTitleClick(TColumn *Column);
private:	// User declarations
	int m_supplierID;
	int m_catalogID;
	int m_searchMode;

	void QryBkInfo();
	AnsiString SearchCont;


	BOOL MutilSelectModal;//是否为多选模式
public:		// User declarations
	__fastcall TfrmSelectCatalog(TComponent* Owner,TADOConnection* con);
	void SetSearchMode(int searchMode, String text);
	void Init(LandInfo* li);
	void GetSelectResult(int& SupplierID, int& BkcatalogID);
	int *SupplierID, *BkcatalogiD, *BKSKid,*stkbkid,*skAmount;
	bool SelectAll;
	int lengthint;
	bool findbook;
	AnsiString Supplier;
	int DoModalType;//1为零售调用 2.批销调用3入库调用
	TfrmRetailMng *Retailfrm;
    TfrmStorageReturnMng * StorageReturnfrm;
  	TfrmStorageMng * Storagefrm;
	TfrmWholesaleMng *Wholefrm;
	TfrmProcureMng *Procurefrm;
	TfrmWholesaleReturnMng *WholeReturnfrm;
	TfrmRetailReturnMng *RetailReturnfrm;
	TfrmStockAdjust *StockAdjust;
	TfrmBIorder *order;
	TfrmStockcheckxuyi *stockcheckxuyi;
	TfrmZNStorageMng *ZNStorageMng;
	TfrmYsbooksale *Ysbooksale;
	bool m_ok,nobkinforsale,addbkinfo,nokucpxth;
	int BSKid;
	int BKinfoid;
	int Amount;
	AnsiString sql1,sql2;
	void Qry();
	void Filter();
	bool qikan;
	AnsiString qikanhao;

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSelectCatalog *frmSelectCatalog;
//---------------------------------------------------------------------------
#endif
