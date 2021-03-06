//---------------------------------------------------------------------------

#ifndef WholesaleMngFormH
#define WholesaleMngFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzDBCmbo.hpp"
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <Buttons.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
#include "RzDBGrid.hpp"
#include "RzDBLbl.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBAdapt.hpp>
#include <WebAdapt.hpp>
#include <WebComp.hpp>
#include <FMTBcd.hpp>
#include <SqlExpr.hpp>
#include "RzCommon.hpp"
#include "RzDBLook.hpp"
#include "RzRadGrp.hpp"
#include "pdutil.h"
#include "RzRadChk.hpp"
#include <ImgList.hpp>
#include "bsadmin.h"
#include "bsprint.h"
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <Graphics.hpp>
#include <pngimage.hpp>
#include<iostream>
#include<stdio.h>
//---------------------------------------------------------------------------
class TfrmWholesaleMng : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton1;
	TPopupMenu *pm1;
	TMenuItem *mniBsNote;
	TMenuItem *mniBsNoteSendback;
	TRzStatusBar *RzStatusBar1;
	TRzLabel *lbl11;
	TRzLabel *lbl12;
	TRzLabel *lbl13;
	TRzLabel *lbl14;
	TRzDBNumericEdit *dbnbedt2;
	TRzDBNumericEdit *dbnbedt3;
	TRzDBNumericEdit *dbnbedt4;
	TDataSource *dsrcNtHeader;
	TADODataSet *dsetNtHeader;
	TDataSource *dsrcNote;
	TADODataSet *dsetNote;
	TADODataSet *dsetVendor;
	TDataSource *dsrcVendor;
	TDataSource *dsrcStaff;
	TADODataSet *dsetStaff;
	TADODataSet *dsetBkstack;
	TDataSource *dsrcBkstack;
	TRzDBLookupDialog *dblkpdlgVendor;
	TADODataSet *dsetLkpVendor;
	TADOCommand *cmdUpdateNtHeader;
	TADOStoredProc *spQryNtHeader;
	TADOStoredProc *spQryNtHeader1;
	TADOCommand *cmdDelNtHeader;
	TADOCommand *cmdAddNote;
	TADOCommand *cmdUpdateNote;
	TADOCommand *cmdDelNote;
	TADOCommand *cmdBatchUpdateNote;
	TADOCommand *cmdBatchDelNote;
	TRzToolButton *tlbtn1;
	TRzToolButton *tlbtnAddNote;
	TRzToolButton *tlbtn2;
	TRzToolButton *tlbtn3;
	TRzToolButton *RzToolButton2;
	TRzToolButton *tlbtn4;
	TRzToolButton *tlbtn5;
	TRzToolButton *tlbtn7;
	TADOCommand *cmdAddNtHeader;
	TRzLabel *lblOpName;
	TADOCommand *cmdResetNtHeader;
	TImageList *ImageList1;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TLabel *Label2;
	TPopupMenu *PopupMenu1;
	TMenuItem *N11;
	TMenuItem *N21;
	TRzToolButton *BtnClear;
	TPopupMenu *PopupMenu2;
	TMenuItem *N12;
	TMenuItem *N22;
	TADODataSet *bearsaledataset;
	TMenuItem *N4;
	TADOQuery *query;
	TPopupMenu *selectmenu;
	TMenuItem *N5;
	TMenuItem *N6;
	TGroupBox *GroupBox1;
	TDataSource *dsrcrecord;
	TADOQuery *qryrecord;
	TRzToolButton *BtnNew;
	TGroupBox *GroupBox3;
	TEdit *edchecked;
	TEdit *ednochecked;
	TLabel *Label3;
	TLabel *Label4;
	TGroupBox *grpbxNote;
	TComboBox *cbbkstackID;
	TRzDBNumericEdit *dbnbedtAmount;
	TRzDBNumericEdit *dbnbedtDiscount;
	TRzDBNumericEdit *dbnbedtTotalAmount;
	TRzEdit *edtCatalog;
	TLabel *Label1;
	TRzLabel *lbl10;
	TRzLabel *lbl5;
	TRzLabel *lbl8;
	TRzLabel *lbl9;
	TRzLabel *lblCatalog;
	TGroupBox *grpbxNtHeader;
	TRzDBDateTimeEdit *dbdtedtHdTime;
	TRzDBEdit *dbedtWsaleNtCode;
	TRzDBLookupComboBox *dblkpcbbStaffID;
	TRzDBLookupComboBox *dblkpcbbVendorID;
	TRzDBNumericEdit *dbnbedtAddCosts;
	TRzEdit *edtQryVendor;
	TRzLabel *lbl1;
	TRzLabel *lbl2;
	TRzLabel *lbl3;
	TRzLabel *lbl4;
	TRzLabel *lbl6;
	TRzLabel *lbl7;
	TRzButton *RzButton1;
	TSpeedButton *spselectClient;
	TDateTimePicker *dtpdate;
	TLabel *Label5;
	TEdit *editprice;
	TComboBox *cbclient;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TRzToolButton *BtnView;
	TRzToolButton *BtnSave;
	TADOStoredProc *spsave;
	TLabel *Label6;
	TEdit *edstorageid;
	TEdit *edstoragename;
	TLabel *Label7;
	TRzDBNumericEdit *dbnbedt5;
	TLabel *Label8;
	TRzDBNumericEdit *dbnbedt6;
	TDBNavigator *DBNav;
	TDataSource *DBSource;
	TADOQuery *querydan;
	TPanel *Panel1;
	TSpeedButton *spnew;
	TRzDBGrid *dbgrdNote;
	TEdit *editdanhao;
	TEdit *edtotamount;
	TLabel *Label10;
	TRzToolButton *BtnAlignBottom;
	TLabel *Label9;
	TRzDBNumericEdit *RzDBNumericEdit1;
	TPopupMenu *pmprint;
	TMenuItem *N10;
	TMenuItem *N13;
	TSaveDialog *savedlg;
	TEdit *edtclient;
	TADOStoredProc *adospcopy;
	TADOStoredProc *spcopy;
	TImage *Image1;
	TMemo *membk;
	TGroupBox *GroupBox2;
	TCheckBox *chfoceset;
	TCheckBox *chfsluru;
	TCheckBox *chfsamount;
	TCheckBox *chfsdiscount;
	TSpeedButton *SpeedButton1;
	TCheckBox *chqikan;
	TEdit *edqikan;
	TMenuItem *N14;
	TSpeedButton *SpeedButton4;
	TRzDBGrid *dgrecord;
	TGroupBox *GroupBox4;
	TCheckBox *ch1;
	TCheckBox *ch2;
	TCheckBox *ch3;
	TCheckBox *ch4;
	TRzToolButton *BtnViewList;
	TPopupMenu *pmpreview;
	TRzToolButton *BtnBringtoFront;
	TPopupMenu *pmprintbag;
	TMenuItem *N15;
	TMenuItem *N16;
	TMenuItem *N17;
	TMenuItem *N18;
	TMenuItem *N19;
	TADOStoredProc *sphunhedabao;
	TADOQuery *aqhunhedabao;
	TSpeedButton *SpeedButton2;
	TMenuItem *N20;
	TMenuItem *N23;
	TCheckBox *ch5;
	TLabel *lblock;
	TMenuItem *N54;
	TMenuItem *N24;
	TMenuItem *N25;
	TMenuItem *N26;
	TMenuItem *N27;
	TMenuItem *N28;
	TMenuItem *N29;
	TMenuItem *A51;
	TMenuItem *A52;
	TComboBox *cborder;
	TLabel *lbeclientname;
	TSpeedButton *sbsureorder;
	TADOStoredProc *sp;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tlbtn1Click(TObject *Sender);
	void __fastcall tlbtn7Click(TObject *Sender);
	void __fastcall edtQryVendorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall mniBsNoteSendbackClick(TObject *Sender);
	void __fastcall tlbtn4Click(TObject *Sender);
	void __fastcall dblkpcbbBkstackIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbl(TObject *Sender, wchar_t &Key);
	void __fastcall dblkpcbbStaffIDExit(TObject *Sender);
	void __fastcall dbnbedtAmountExit(TObject *Sender);
	void __fastcall tlbtn5Click(TObject *Sender);
	void __fastcall dsetNoteAfterScroll(TDataSet *DataSet);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall N21Click(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall N22Click(TObject *Sender);
	void __fastcall N12Click(TObject *Sender);
	void __fastcall dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall dbnbedtTotalAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall dbgrdNoteCellClick(TColumn *Column);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall cbbkstackIDExit(TObject *Sender);
	void __fastcall cbbkstackIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall dtpdateChange(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall tlbtnAddNoteClick(TObject *Sender);
	void __fastcall dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall cbclientExit(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall cbclientDropDown(TObject *Sender);
	void __fastcall dbnbedtAddCostsExit(TObject *Sender);
	void __fastcall dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall DBNavClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall dbnbedtDiscountExit(TObject *Sender);
	void __fastcall spnewClick(TObject *Sender);
	void __fastcall cbclientClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall dbgrdNoteTitleClick(TColumn *Column);
	void __fastcall edtclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall membkExit(TObject *Sender);
	void __fastcall membkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall chqikanClick(TObject *Sender);
	void __fastcall N14Click(TObject *Sender);
	void __fastcall edqikanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall chfsluruClick(TObject *Sender);
	void __fastcall editpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall ch1Click(TObject *Sender);
	void __fastcall ch2Click(TObject *Sender);
	void __fastcall ch3Click(TObject *Sender);
	void __fastcall ch4Click(TObject *Sender);
	void __fastcall BtnViewListClick(TObject *Sender);
	void __fastcall dbgrdNoteDblClick(TObject *Sender);
	void __fastcall BtnBringtoFrontClick(TObject *Sender);
	void __fastcall N19Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall N20Click(TObject *Sender);
	void __fastcall N23Click(TObject *Sender);
	void __fastcall ch5Click(TObject *Sender);
	void __fastcall N54Click(TObject *Sender);
	void __fastcall sbsureorderClick(TObject *Sender);


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
	int m_supplierID;
	int m_catalogSearchMode;//1为书号 2为自编码 3为书名
	OPMode m_opmode;//1为查单模式 2为添加单头模式 3为删除单头模式 4为添加单模式 5为删除单模式 6为统一模式 7为现场收款模式
	BSMode m_bsmode;//1为批销单模式 2为退货单模式
	void ChangeCatalogSearchMode();
	void ChangeBsmode(BSMode bsmode);
	void ChangeOpmode(OPMode opmode);
	void AddNtHeader();//添加单头
	void QryNtHeader(String code, bool qrybkstack = false);//查询单头
	void QryNtHeader(bool qrybkstack = false);//查询单头

	void DelNtHeader();//删除单头
	void UpdateNtHeader();//更新单头

	void UpdateNote();//更新单
	void DelNote();//删除单
	void BatchSetNotes(int amount, float discount, int mode);
	void QryBkstack();
	void DelInvalidNtHeader();
	void ResetNtHeader();
	int addnotereturnvalue;
	String MaxNote;
	int ClientID;
	int Type;//1为批销员调用，2为零售员调用
	String format;
	bool blSelect;   //按shift多选
	TBookmark BookMark;
	bool SaveOrNot;
	bool SaveWsale(int mode);
	float bakdot;
	bool ChangeDisplay,master;
	bool allclient,deletedetail,find,changepassword,sametishi;
public:		// User declarations
	__fastcall TfrmWholesaleMng(TComponent* Owner,int type);
	virtual void Init(LandInfo* li);
	void QryNtHeader(int id, bool qrybkstack = false);//查询单头
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	bool AddNote(int supplierID, int catalogID);//添加单
	void FindNote(String code);
	void historyview();
	void checkedview();
	bool retailreturn(int catalogID);
	void ModifyEnable();
	void GetBkStackInfo();
	void ReadClient();
	bool bsetpixiaodiscount,localstack;
	bool saleenable(int stkid);
	float pixiaodiscount;
	bool  discountcatch(int stkid);
	LandInfo linfo;
	void Backdot(float discount);
	int huanhuo;
	AnsiString pxbk,logmessage,printtitle,contact,tel,address;
	bool tuihuo;
	bool SaveOK();
	int changehead,printmodle;  // printmodle 为0学校，1书店模式
	void FormView();
	void ClientView();
	void localnum(int amount);
	void  operterview(int operterid);
	void __fastcall MyClick(TObject *Sender);
	void __fastcall MyClickPreview(TObject *Sender);
	void  Print(int modle,int type,int printid);
	void hunhedabao();
	int printbagtype;
	void PrintAdd();
        void lock(bool islock);
        bool newclient;
         bool  client,bookcatalogadd,bcatalogmodify;
                void checknewsupplier();
				void disablenewsupplierornewbook();
	void muilprint(AnsiString HeaderID,int type,bool xiaopiao);
    void getOrder();

	};

//---------------------------------------------------------------------------
extern PACKAGE TfrmWholesaleMng *frmWholesaleMng;
//---------------------------------------------------------------------------
#endif
