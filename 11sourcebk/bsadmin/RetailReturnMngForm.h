//---------------------------------------------------------------------------

#ifndef RetailReturnMngFormH
#define RetailReturnMngFormH
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

#define WM_REFRESH_PDDATA WM_USER+101
//---------------------------------------------------------------------------
class TfrmRetailReturnMng : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *tlbtn8;
	TPanel *pnl1;
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
	TRzLabel *lbl1;
	TRzLabel *lbl7;
	TRzLabel *lbl3;
	TRzDBNumericEdit *dbnbedtReceivableMoney;
	TRzNumericEdit *numedtOdd;
	TRzNumericEdit *numedtPaidinMoney;
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
	TGroupBox *grpbxNtHeader;
	TRzDBEdit *dbedtRetailNtCode;
	TRzDBLookupComboBox *dblkpcbbMemberID;
	TRzLabel *lbl2;
	TRzLabel *lbl4;
	TGroupBox *GroupBox1;
	TRzLabel *lbl10;
	TRzLabel *lbl15;
	TRzLabel *lbl16;
	TRzLabel *lbl6;
	TRzNumericEdit *numedtCheck;
	TRzNumericEdit *numedtDiscountedMoney;
	TRzNumericEdit *numedtRec;
	TRzNumericEdit *numedtTotalAmount;
	TPanel *Panel1;
	TRzDBGrid *dbgrdNote;
	TLabel *Label3;
	TRzToolButton *BtnView;
	TSpeedButton *RzButton1;
	TRzToolButton *BtnAlignBottom;
	TMenuItem *N7;
	TRzToolButton *BtnUpOneLevel;
	TRzToolButton *BtnPrint;
	TRzButton *mdifdiscount;
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
	TGroupBox *GroupBox2;
	TRzLabel *lbl12;
	TRzDBNumericEdit *dbnbedt2;
	TRzLabel *lbl13;
	TRzDBNumericEdit *dbnbedt3;
	TRzLabel *lbl14;
	TRzDBNumericEdit *dbnbedt4;
	TGroupBox *GroupBox3;
	TRzLabel *lbl11;
	TRzLabel *lblOpName;
	TRzLabel *RzLabel2;
	TEdit *edopername;
	TEdit *edstoragename;
	TMemo *membk;
	TCheckBox *chqikan;
	TRzLabel *RzLabel5;
	TEdit *edprice;
	TRzButton *RzButton6;
	TEdit *edqikan;
	TGroupBox *GroupBox4;
	TCheckBox *chdingwei;
	TDBNavigator *dbhd;
	TDataSource *dshd;
	TADOQuery *aqhd;
	void __fastcall dsrcNtHeaderDataChange(TObject *Sender, TField *Field);
	void __fastcall dsrcNoteDataChange(TObject *Sender, TField *Field);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tlbtn8Click(TObject *Sender);
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
	void __fastcall numedtPaidinMoneyEnter(TObject *Sender);
	void __fastcall mniPrintNtHeaderClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall cbbkstackIDExit(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall BtnUpOneLevelClick(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall mdifdiscountClick(TObject *Sender);
	void __fastcall membkExit(TObject *Sender);
	void __fastcall RzButton6Click(TObject *Sender);
	void __fastcall edpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall chqikanClick(TObject *Sender);
	void __fastcall edqikanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbgrdNoteCellClick(TColumn *Column);
	void __fastcall dblkpcbbMemberIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbnbedtDiscountExit(TObject *Sender);


private:	// User declarations
	float m_cash; //�ֽ�
	float m_card; //���
	float m_poscard;  //���п�
	float m_youhuiquan;  //�Ż�ȯ
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
	int m_catalogSearchMode;//1Ϊ��� 2Ϊ�Ա��� 3Ϊ����
	OPMode m_opmode;//1Ϊ�鵥ģʽ 2Ϊ��ӵ�ͷģʽ 3Ϊɾ����ͷģʽ 4Ϊ��ӵ�ģʽ 5Ϊɾ����ģʽ 6Ϊͳһģʽ 7Ϊ�ֳ��տ�ģʽ
	BSMode m_bsmode;//1Ϊ������ģʽ 2Ϊ�˻���ģʽ
	void ChangeCatalogSearchMode();
	void ChangeBsmode(BSMode bsmode);
	void ChangeOpmode(OPMode opmode);
	void AddNtHeader();//��ӵ�ͷ
	void QryNtHeader(String code, bool qrybkstack = false);//��ѯ��ͷ
	void QryNtHeader(bool qrybkstack = false);//��ѯ��ͷ
	void QryNtHeader(int id, bool qrybkstack = false);//��ѯ��ͷ
	void DelNtHeader();//ɾ����ͷ
	void UpdateNtHeader();//���µ�ͷ

	void UpdateNote();//���µ�
	void DelNote();//ɾ����
	void BatchSetNotes(int amount, float discount, int mode);
	void QryBkstack();
	void OnHotKeyPress(DWORD vkCode);
	int IsChecked();//��鵱ǰ�����Ƿ��ѽ�
	void DelInvalidNtHeader();//ɾ�����õ�
	void ResetNtHeader();
	void PrintNtHeader();
	void ReadConfig();
	void WriteConfig();
	int addnotereturnvalue;
	String MaxNote;
	bool retaildiscountchange,xiaopiaoprint,findpassword,deletepassword,tuihuopassword;
	String format,logmessage;
public:		// User declarations
	__fastcall TfrmRetailReturnMng(TComponent* Owner);
	void Init(LandInfo* li);
	bool AddNote(int supplierID, int catalogID);//��ӵ�
	void FindNote(String code);
	void NtCodeChange();
	void MoneyChange();
	bool retailreturn(int catalogID);
	void ModifyEnable();
	void GetBkStackInfo();
	bool saleenable(int stkid);
	LandInfo linfo;
	void FormView();
	void  operterview(int operterid);
	void  ShowPrice();
	bool DiscountEnable(float discount,int catalogid);
	bool mindiscount,minstorage;
	float mixdiscount;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRetailReturnMng *frmRetailReturnMng;
//---------------------------------------------------------------------------
#endif
