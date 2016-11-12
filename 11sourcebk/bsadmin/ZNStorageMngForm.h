//---------------------------------------------------------------------------

#ifndef ZNStorageMngFormH
#define ZNStorageMngFormH
//---------------------------------------------------------------------------

#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzDBCmbo.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzDBLbl.hpp"
#include "RzDBSpin.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include "RzSpnEdt.hpp"
#include <ADODB.hpp>
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <DBCtrls.hpp>
#include "RzCommon.hpp"
#include "RzDBLook.hpp"
#include "pdutil.h"
#include "MDIChild.h"
#include "RzRadChk.hpp"
#include <ImgList.hpp>

#include "bsprint.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmZNStorageMng : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzStatusBar *RzStatusBar1;
	TRzLabel *lbl7;
	TRzLabel *lbl8;
	TRzDBNumericEdit *RzDBNumericEdit2;
	TRzLabel *lbl9;
	TRzLabel *lbl10;
	TRzDBNumericEdit *RzDBNumericEdit3;
	TRzDBNumericEdit *RzDBNumericEdit4;
	TRzToolButton *RzToolButton5;
	TRzToolButton *RzToolButton2;
	TRzToolButton *RzToolButton3;
	TDataSource *dsrcSupplier;
	TDataSource *dsrcStaff;
	TRzDBLookupDialog *dblkpdlgCode;
	TADODataSet *dsetSupplier;
	TADODataSet *dsetStaff;
	TADODataSet *dsetCatalog;
	TRzDBLookupDialog *dblkpdlgISBN;
	TRzDBLookupDialog *dblkpdlgName;
	TADODataSet *dsetBkstack;
	TDataSource *dsrcBkstack;
	TADODataSet *dsetLkpSupplier;
	TRzDBLookupDialog *dblkpdlgSupplier;
	TADOStoredProc *spQryNtHeader;
	TADOCommand *cmdUpdateNtHeader;
	TADOStoredProc *spQryNtHeader1;
	TADODataSet *dsetNtHeader;
	TDataSource *dsrcNtHeader;
	TADODataSet *dsetNote;
	TDataSource *dsrcNote;
	TADOCommand *cmdAddNote;
	TADOCommand *cmdUpdateNote;
	TADOCommand *cmdDelNote;
	TADOCommand *cmdDelNtHeader;
	TADOCommand *cmdBatchUpdateNote;
	TADOCommand *cmdBatchDelNote;
	TRzToolButton *RzToolButton6;
	TRzToolButton *RzToolButton8;
	TRzToolButton *RzToolButton9;
	TADOCommand *cmdAddNtHeader;
	TRzLabel *lblOpName;
	TADOCommand *cmdResetNtHeader;
	TImageList *ImageListMenu;
	TPanel *Panel1;
	TLabel *lbcaption;
	TRzToolButton *BtnView;
	TRzToolButton *BtnNew;
	TPopupMenu *PM;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TRzToolButton *BtnClear;
	TADOQuery *query;
	TDataSource *dsrcstorage;
	TEdit *edtQrySupplier;
	TDataSource *dsrcdetail;
	TADOQuery *qudetail;
	TADOQuery *qrystorge;
	TPopupMenu *selectmenu;
	TMenuItem *N4;
	TMenuItem *N5;
	TPopupMenu *pmBsmode;
	TMenuItem *mniBsNote;
	TMenuItem *mniBsNoteSendback;
	TMenuItem *N6;
	TGroupBox *grpbxNtHeader;
	TRzDBDateTimeEdit *dbdtedtHdTime;
	TRzDBEdit *dbedtRemarks;
	TRzDBEdit *dbedtStgNtCode;
	TRzDBEdit *dbedtSupplySN;
	TRzDBLookupComboBox *dblkpcbbStaffID;
	TRzDBLookupComboBox *dblkpcbbSupplierID;
	TRzDBNumericEdit *dbnbedtAddCosts;
	TLabel *Label2;
	TRzLabel *lblHdTime;
	TRzLabel *lblSupplier;
	TRzLabel *RzLabel3;
	TRzLabel *RzLabel4;
	TRzLabel *RzLabel5;
	TRzLabel *RzLabel6;
	TSpeedButton *sbnewcustomer;
	TSpeedButton *Sbutbefore;
	TSpeedButton *Sbutend;
	TSpeedButton *Sbutfirst;
	TSpeedButton *Sbutnext;
	TEdit *edStoryNum;
	TRzComboBox *cbstorgename;
	TGroupBox *grpbxNote;
	TComboBox *cbbkstackID;
	TRzDBLookupComboBox *dblkpcbbBkstackID;
	TRzDBNumericEdit *dbnbedt1;
	TRzDBNumericEdit *dbnbedtAmount;
	TRzDBNumericEdit *dbnbedtDiscount;
	TRzEdit *edtCatalog;
	TLabel *Label1;
	TRzLabel *lbl4;
	TRzLabel *lbl5;
	TRzLabel *lbl6;
	TRzLabel *lblAmount;
	TRzLabel *lblCatalog;
	TSpeedButton *spnewbook;
	TDateTimePicker *dtpdate;
	TLabel *Label3;
	TEdit *editjingjiaprice;
	TLabel *Label4;
	TEdit *editpxprice;
	TLabel *Label6;
	TEdit *editpxdiscount;
	TLabel *Label5;
	TADOStoredProc *adospupdatewsaleprice;
	TLabel *Label7;
	TEdit *editque;
	TLabel *Label8;
	TEdit *editshun;
	TCheckBox *cbreturn;
	TRzToolButton *BtnChangeOptions;
	TADOQuery *aq;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TRzToolButton *BtnView1;
	TRzToolButton *BtnSave;
	TRzEdit *RzEdit1;
	TADOStoredProc *spsave;
	TRzToolButton *BtnReminder;
	TEdit *editdanhao;
	TDBNavigator *DBNav;
	TDataSource *DBSource;
	TADOQuery *querydan;
	TLabel *Label9;
	TRzDBGrid *dbgrdNote;
	TRzDBGrid *dgdetail;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnAlignBottom;
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtQrySupplierKeyPress(TObject *Sender, wchar_t &Key);
    void __fastcall dblkpcbbStaffIDKeyPress(TObject *Sender, wchar_t &Key);
  //	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall dbedtSupplySNKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dblkpcbbBkstackIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton9Click(TObject *Sender);
	void __fastcall RzToolButton8Click(TObject *Sender);
	void __fastcall RzToolButton6Click(TObject *Sender);
	void __fastcall dbnbedtAmountExit(TObject *Sender);

	void __fastcall dsetNoteAfterScroll(TDataSet *DataSet);
	void __fastcall spnewbookClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall RzToolButton2Click(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall dblkpcbbSupplierIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SbutfirstClick(TObject *Sender);
	void __fastcall SbutbeforeClick(TObject *Sender);
	void __fastcall SbutnextClick(TObject *Sender);
	void __fastcall SbutendClick(TObject *Sender);
	void __fastcall dbgrdNoteDblClick(TObject *Sender);
	void __fastcall dbgrdNoteCellClick(TColumn *Column);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall mniBsNoteClick(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall dtpdateChange(TObject *Sender);
	void __fastcall editpxdiscountExit(TObject *Sender);
	void __fastcall dbnbedtDiscountExit(TObject *Sender);
	void __fastcall editjingjiapriceExit(TObject *Sender);
	void __fastcall editjingjiapriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editpxdiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editpxpriceExit(TObject *Sender);
	void __fastcall editpxpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editshunExit(TObject *Sender);
	void __fastcall editqueExit(TObject *Sender);
	void __fastcall editqueKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editshunKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbreturnExit(TObject *Sender);
	void __fastcall cbbkstackIDSelect(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall BtnView1Click(TObject *Sender);
	void __fastcall dbedtSupplySNExit(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall RzEdit1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dblkpcbbSupplierIDExit(TObject *Sender);
	void __fastcall dbnbedtAddCostsExit(TObject *Sender);
	void __fastcall dbedtRemarksExit(TObject *Sender);
	void __fastcall dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnReminderClick(TObject *Sender);
	void __fastcall DBNavClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall BtnImportClick(TObject *Sender);


private:	// User declarations
	typedef enum
	{
		OPUnknown = 0,
		OPFind = 1,
		OPAddNtHeader,
		OPDelNtHeader,
		OPAddNote,
		OPDelNote,
		OPSetNotes,
		OPRecCash
	}OPMode;
	String m_findCode;//将要查询的单号
	int m_catalogSearchMode;//1为书号 2为自编码 3为书名
	OPMode m_opmode;//1为查单模式 2为添加单头模式 3为删除单头模式 4为添加单模式 5为删除单模式 6为统一模式 7为现场收款模式
	BSMode m_bsmode;//1为批销单模式 2为退货单模式
	void ChangeCatalogSearchMode();
	void ChangeBsmode(BSMode bsmode);
	void ChangeOpmode(OPMode opmode);
	void AddNtHeader();//添加单头
	void QryNtHeader(String code, bool qrybkstack = false);//查询单头
	void QryNtHeader(bool qrybkstack = false);//查询单头
	void QryNtHeader(int id, bool qrybkstack = false);//查询单头
	void DelNtHeader();//删除单头




	void DelNote();//删除单
	void BatchSetNotes(int amount, float discount, int mode);
	void QryBkstack();
	bool IsOverlapCatalog(int headerid, int catalogid, int supplierid);
	void OnHotKeyPress(DWORD vkCode, bool ctrlpress);
	void DelInvalidNtHeader();
	void ResetNtHeader();
	void GetBkStackInfo();
	void UpdateWsaleDiscout(int mode);//更新批销折扣，价格等
	void BatchsetWsaleDiscout(float pidiscount); //统一更新批销折扣
	String MaxNote;
	bool stackchange;
	String format;
	bool autologout;
	bool blSelect;   //按shift多选
	TBookmark BookMark;
	bool lastjypxdiscount,addnote;
	AnsiString yjpxkind;
	bool SaveOrNot;
	bool ChangeDisplay,allsupplier,findpassword,deletepassword;
public:		// User declarations
	__fastcall TfrmZNStorageMng(TComponent* Owner);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	void Init(LandInfo* li);
   //	bool AddNote(int id);//添加单
		bool AddNote(int supplierID, int catalogID);//添加单
		bool AddNote(int id);
		void FindNote(String code);
		void NtCodeChange();
		void historyview();
		void addwsalediscount();
		void ModifyEnable();
			void UpdateNote();//更新单
			void  AutologProA(); //自动注销采购记录
			void  AutologProS(int supplier,int BkcatalogID);//自动注销采购记录
			void  AutologPro();
			void  UpdateProHeader();
			void changeInputMode();
            bool bsetpixiaodiscount;
		float pixiaodiscount;
		void lastyjpxdiscount();
		void yjpxdiscount();
		LandInfo linfo;
		bool SaveStorage(int mode);
		AnsiString rkbk;
		bool SaveOK();
		void ChangeSupplier();
		int beforesupplier;
		void UpdateNtHeader();//更新单头

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmZNStorageMng *frmZNStorageMng;
//---------------------------------------------------------------------------
#endif
