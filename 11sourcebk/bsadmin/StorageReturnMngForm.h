//---------------------------------------------------------------------------

#ifndef StorageReturnMngFormH
#define StorageReturnMngFormH
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
#include <Dialogs.hpp>
#include <Graphics.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TfrmStorageReturnMng : public TfrmMDIChild
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
	TPopupMenu *pmBsmode;
	TMenuItem *mniBsNote;
	TMenuItem *mniBsNoteSendback;
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
	TDataSource *dsrcdetail;
	TADOQuery *qudetail;
	TADOQuery *qrystorge;
	TPopupMenu *selectmenu;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
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
	TRzToolButton *BtnChangeOptions;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TRzToolButton *BtnView1;
	TRzToolButton *BtnSave;
	TADOStoredProc *spsave;
	TRzToolButton *BtnReminder;
	TDataSource *DBSource;
	TADOQuery *querydan;
	TGroupBox *grpbxNtHeader;
	TLabel *Label2;
	TRzLabel *lbl1;
	TRzLabel *lblHdTime;
	TRzLabel *lblSupplier;
	TRzLabel *RzLabel3;
	TRzLabel *RzLabel4;
	TRzLabel *RzLabel5;
	TRzLabel *RzLabel6;
	TSpeedButton *sbnewcustomer;
	TRzDBDateTimeEdit *dbdtedtHdTime;
	TRzDBEdit *dbedtStgNtCode;
	TRzDBEdit *dbedtSupplySN;
	TRzDBLookupComboBox *dblkpcbbStaffID;
	TRzDBLookupComboBox *dblkpcbbSupplierID;
	TRzDBNumericEdit *dbnbedtAddCosts;
	TEdit *edStoryNum;
	TRzComboBox *cbstorgename;
	TDateTimePicker *dtpdate;
	TEdit *editdanhao;
	TEdit *edtQrySupplier;
	TDBNavigator *DBNav;
	TRzDBGrid *dbgrdNote;
	TRzDBGrid *dgdetail;
	TEdit *edtotamount;
	TLabel *Label10;
	TRzToolButton *BtnAlignBottom;
	TLabel *Label3;
	TEdit *editbenqi;
	TLabel *Label4;
	TEdit *edityear;
	TADOStoredProc *sptuihuo;
	TSaveDialog *savedlg;
	TADOStoredProc *adospcopy;
	TLabel *Label8;
	TEdit *editshun;
	TADOStoredProc *adospupdatewsaleprice;
	TImage *Image1;
	TMemo *membk;
	TGroupBox *GroupBox1;
	TCheckBox *chfoceset;
	TCheckBox *chfsluru;
	TCheckBox *chfsamount;
	TCheckBox *chfsdiscount;
	TSpeedButton *SpeedButton1;
	TCheckBox *chqikan;
	TEdit *edqikan;
	TMenuItem *N10;
	TMenuItem *N11;
	TLabel *lblock;
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtQrySupplierKeyPress(TObject *Sender, wchar_t &Key);
    void __fastcall dblkpcbbStaffIDKeyPress(TObject *Sender, wchar_t &Key);
  //	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall dbedtSupplySNKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton9Click(TObject *Sender);
	void __fastcall RzToolButton8Click(TObject *Sender);
	void __fastcall dblkpcbbSupplierIDExit(TObject *Sender);
	void __fastcall RzToolButton6Click(TObject *Sender);
	void __fastcall dbnbedtAmountExit(TObject *Sender);
	void __fastcall mniBsNoteSendbackClick(TObject *Sender);

	void __fastcall dsetNoteAfterScroll(TDataSet *DataSet);
	void __fastcall sbnewcustomerClick(TObject *Sender);
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
	void __fastcall dbgrdNoteDblClick(TObject *Sender);
	void __fastcall dbgrdNoteCellClick(TColumn *Column);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall dtpdateChange(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall BtnView1Click(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall dbnbedtAddCostsExit(TObject *Sender);
	void __fastcall dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnReminderClick(TObject *Sender);
	void __fastcall DBNavClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall dbgrdNoteTitleClick(TColumn *Column);
	void __fastcall dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall editshunExit(TObject *Sender);
	void __fastcall editshunKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall membkExit(TObject *Sender);
	void __fastcall membkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall chfsluruClick(TObject *Sender);
	void __fastcall chqikanClick(TObject *Sender);
	void __fastcall edqikanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall cbbkstackIDSelect(TObject *Sender);


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
	void UpdateNtHeader();//更新单头


	void UpdateNote();//更新单
	void UpdateNote1();//更新单不刷新
	void DelNote();//删除单
	void BatchSetNotes(int amount, float discount, int mode);
	void QryBkstack();
	bool IsOverlapCatalog(int headerid, int catalogid, int supplierid);
	void OnHotKeyPress(DWORD vkCode, bool ctrlpress);
	void DelInvalidNtHeader();
	void ResetNtHeader();
	void GetBkStackInfo();
	String MaxNote;
	String format;
		bool blSelect;   //按shift多选
	TBookmark BookMark;
	bool SaveOrNot;
	int supplierDI;
	bool ChangeDisplay,allsupplier,findpassword,deletepassword,tuihuopassword,changepassword,sameid;
public:		// User declarations
	__fastcall TfrmStorageReturnMng(TComponent* Owner);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	void Init(LandInfo* li);
   //	bool AddNote(int id);//添加单
		bool AddNote(int supplierID, int catalogID);//添加单
		bool AddNote(int id);
		void FindNote(String code);
		void historyview();
		void ModifyEnable();
		void changeInputMode();
		bool bsetpixiaodiscount,rktuihuoguanli;
		float pixiaodiscount;
		LandInfo linfo;
		 bool SaveStorage(int mode);
		 AnsiString rkbk,logmessage,beforesuppliername,printtitle,contact,tel,address;
		 bool SaveOK();
		void ChangeSupplier();
		int beforesupplier;
		void FormView();
		void tuihuolv();
		bool stackchange;
		void UpdateWsaleDiscout(int mode);
		void  operterview(int operterid);
                void lock(int type);
                 bool newsupplier;
                 bool  supplier,bookcatalogadd,bcatalogmodify;
                void checknewsupplier();
                void disablenewsupplierornewbook();
                bool dblclicklock;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStorageReturnMng *frmStorageReturnMng;
//---------------------------------------------------------------------------
#endif
