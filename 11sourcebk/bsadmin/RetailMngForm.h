//---------------------------------------------------------------------------

#ifndef RetailMngFormH
#define RetailMngFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "RzDBCmbo.hpp"
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzDBLbl.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "pdutil.h"
#include "pdtypes.h"
#include "RzCommon.hpp"
#include "RzDBLook.hpp"
#include <Menus.hpp>
#include "RzRadChk.hpp"
#include <ImgList.hpp>
#include <ComCtrls.hpp>

#define WM_REFRESH_PDDATA WM_USER+101
//---------------------------------------------------------------------------
struct Nodedatamenu
{
  int ID;
  AnsiString Name;
  int state;
};

class TfrmRetailMng : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *tlbtn8;
	TADOStoredProc *spQryNtHeader;
	TADOCommand *cmdUpdateNtHeader;
	TADOStoredProc *spQryNtHeader1;
	TADOCommand *cmdDelNtHeader;
	TADODataSet *dsetNtHeader;
	TDataSource *dsrcNtHeader;
	TDataSource *dsrcNote;
	TADODataSet *dsetNote;
	TADOCommand *cmdAddNote;
	TADOCommand *cmdUpdateNote;
	TADOCommand *cmdDelNote;
	TADOCommand *cmdBatchUpdateNote;
	TADOCommand *cmdBatchDelNote;
	TPopupMenu *pm1;
	TMenuItem *mniBsNote;
	TMenuItem *mniBsNoteSendback;
	TADODataSet *dsetMember;
	TDataSource *dsrcMember;
	TADOCommand *cmdAddNtHeader;
	TADODataSet *dsetBkstack;
	TDataSource *dsrcBkstack;
	TRzToolButton *tlbtn1;
	TRzToolButton *tlbtn2;
	TRzToolButton *tlbtn3;
	TRzToolButton *tlbtn4;
	TRzToolButton *tlbtnRecMoney;
	TRzToolButton *tlbtnMixed;
	TADOCommand *cmdResetNtHeader;
	TRzToolButton *tlbtn7;
	TPopupMenu *pmPrint;
	TMenuItem *mniPrintNtHeader;
	TImageList *ImageList1;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TADODataSet *dsetbear;
	TMenuItem *N4;
	TADOQuery *query;
	TPopupMenu *selectmenu;
	TMenuItem *N5;
	TMenuItem *N6;
	TADOQuery *aquery;
	TRzToolButton *BtnNew;
	TPanel *Panel1;
	TGroupBox *grpbxNtHeader;
	TRzLabel *lbl2;
	TRzLabel *lbl4;
	TRzDBEdit *dbedtRetailNtCode;
	TRzDBLookupComboBox *dblkpcbbMemberID;
	TGroupBox *GroupBox1;
	TRzLabel *lbl10;
	TRzLabel *lbl15;
	TRzLabel *lbl16;
	TRzLabel *lbl6;
	TRzNumericEdit *numedtCheck;
	TRzNumericEdit *numedtDiscountedMoney;
	TRzNumericEdit *numedtRec;
	TRzNumericEdit *numedtTotalAmount;
	TRzDBGrid *dbgrdNote;
	TPanel *pnl1;
	TRzLabel *lbl1;
	TRzLabel *lbl7;
	TRzLabel *lbl3;
	TRzNumericEdit *numedtOdd;
	TRzNumericEdit *numedtPaidinMoney;
	TRzToolButton *BtnFinish;
	TADOQuery *aq;
	TLabel *Label3;
	TRzToolButton *BtnReminder;
	TRzToolButton *BtnAlignClient;
	TRzToolButton *BtnView;
	TRzToolButton *BtnAttachFiles;
	TMenuItem *N7;
	TMenuItem *N8;
	TGroupBox *GroupBox2;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *aq1;
	TRzNumericEdit *dbnbedtReceivableMoney;
	TSpeedButton *RzButton1;
	TRzToolButton *BtnAlignBottom;
	TMenuItem *N9;
	TRzToolButton *BtnUpOneLevel;
	TRzToolButton *BtnPrint;
	TLabel *Label1;
	TRzLabel *lbl5;
	TRzLabel *lbl8;
	TRzLabel *lbl9;
	TRzLabel *lblCatalog;
	TRzLabel *RzLabel1;
	TComboBox *cbbkstackID;
	TRzCheckBox *chckbxSwitch;
	TRzDBNumericEdit *dbnbedtAmount;
	TRzDBNumericEdit *dbnbedtDiscount;
	TRzDBNumericEdit *dbnbedtTotalAmount;
	TRzEdit *edtCatalog;
	TRzButton *RzButton2;
	TRzButton *RzButton3;
	TGroupBox *GroupBox3;
	TLabel *Label4;
	TLabel *Label5;
	TGroupBox *GroupBox4;
	TRzDBNumericEdit *dbnbedt4;
	TRzLabel *lbl14;
	TRzLabel *lbl13;
	TRzLabel *lbl12;
	TRzDBNumericEdit *dbnbedt3;
	TRzDBNumericEdit *dbnbedt2;
	TLabel *Label2;
	TRzDBNumericEdit *dbnbedt5;
	TRzLabel *lblOpName;
	TEdit *edopername;
	TEdit *edstoragename;
	TGroupBox *GroupBox5;
	TRzButton *RzButton4;
	TRzButton *RzButton5;
	TMemo *membk;
	TRzLabel *RzLabel5;
	TEdit *edprice;
	TRzButton *RzButton6;
	TCheckBox *chqikan;
	TEdit *edqikan;
	TRzButton *RzButton7;
	TGroupBox *GroupBox6;
	TLabel *labdiscountstyle;
	TCheckBox *chdingwei;
	TDBNavigator *dbhd;
	TDataSource *dshd;
	TADOQuery *aqhd;
	void __fastcall dsrcNtHeaderDataChange(TObject *Sender, TField *Field);
	void __fastcall dsrcNoteDataChange(TObject *Sender, TField *Field);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall mniBsNoteSendbackClick(TObject *Sender);
	void __fastcall dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall tlbtn4Click(TObject *Sender);
	void __fastcall tlbtnRecMoneyClick(TObject *Sender);
	void __fastcall tlbtnMixedClick(TObject *Sender);
	void __fastcall tlbtn7Click(TObject *Sender);
	void __fastcall numedtPaidinMoneyChange(TObject *Sender);
	void __fastcall numedtPaidinMoneyKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall numedtAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbnbedtAmountExit(TObject *Sender);
	void __fastcall dblkpcbbMemberIDExit(TObject *Sender);
	void __fastcall dsetNoteAfterScroll(TDataSet *DataSet);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall mniPrintNtHeaderClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall tlbtn8Click(TObject *Sender);
	void __fastcall cbbkstackIDExit(TObject *Sender);
	void __fastcall BtnFinishClick(TObject *Sender);
	void __fastcall BtnReminderClick(TObject *Sender);
	void __fastcall BtnAlignClientClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnAttachFilesClick(TObject *Sender);
	void __fastcall tlbtnAddNoteClick(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall rzshoukuanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall BtnUpOneLevelClick(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall RzButton3Click(TObject *Sender);
	void __fastcall membkExit(TObject *Sender);
	void __fastcall RzButton4Click(TObject *Sender);
	void __fastcall RzButton5Click(TObject *Sender);
	void __fastcall RzButton6Click(TObject *Sender);
	void __fastcall dbnbedtDiscountExit(TObject *Sender);
	void __fastcall edpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall chqikanClick(TObject *Sender);
	void __fastcall edqikanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbgrdNoteCellClick(TColumn *Column);
	void __fastcall RzButton7Click(TObject *Sender);
	void __fastcall dbhdClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall dblkpcbbMemberIDKeyPress(TObject *Sender, wchar_t &Key);


private:	// User declarations
	float m_cash; //现金
	float m_card; //储蓄卡
	float m_poscard;  //银行卡
	float m_youhuiquan;  //优惠券
	typedef enum
	{
		OPUnknown = 0,
		OPFind = 1,
		OPAddNtHeader,
		OPDelNtHeader,
		OPAddNote,
		OPDelNote,
		OPSetNotes,
		OPRecCash,
		OPCard
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
	void OnHotKeyPress(DWORD vkCode);
	int IsChecked();//检查当前单据是否已结
	void DelInvalidNtHeader();//删除无用单
	void ResetNtHeader();
	void PrintNtHeader();
	void ReadConfig();
	void WriteConfig();
	int addnotereturnvalue;
	String MaxNote,logmessage;
	bool retaildiscountchange,xiaopiaoprint,findpassword,deletepassword,tuihuopassword,retailbear,guadantishi,huankoupwd,huajiapwd;
	String format;
public:		// User declarations
	__fastcall TfrmRetailMng(TComponent* Owner);
	void QryNtHeader(int id, bool qrybkstack = false);//查询单头
	void Init(LandInfo* li);
	bool AddNote(int supplierID, int catalogID);//添加单
	void FindNote(String code);
	void NtCodeChange();
	void MoneyChange();
	bool retailreturn(int catalogID);
	void ModifyEnable();
	void GetBkStackInfo();
	void __fastcall Addbook();
	void Sendonebook(int catalogid);
	 LandInfo linfo;
	 bool saleenable(int stkid);
	 float shoukuan,mixdiscount;
	 void FormView();
	 void operterview(int operterid);
	 int Amount;
	 bool nobear();
	 int xiaoshubit;
	 double DRound(double  Value,int P);
	 void ShowPrice();
	 bool DiscountEnable(float discount,int catalogid);
	 bool mindiscount,minstorage;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRetailMng *frmRetailMng;
//---------------------------------------------------------------------------
#endif
