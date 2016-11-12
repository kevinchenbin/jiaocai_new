//---------------------------------------------------------------------------

#ifndef ZNProcureMngH
#define ZNProcureMngH
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
#include "PwdForm.h"
//---------------------------------------------------------------------------
class TfrmZNProcureMng : public TfrmMDIChild
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
	TDataSource *dsrcStaff;
	TADODataSet *dsetStaff;
	TADODataSet *dsetBkstack;
	TDataSource *dsrcBkstack;
	TRzDBLookupDialog *dblkpdlgVendor;
	TADOCommand *cmdUpdateNtHeader;
	TADOStoredProc *spQryNtHeader;
	TADOStoredProc *spQryNtHeader1;
	TADOCommand *cmdDelNtHeader;
	TADOCommand *cmdAddNote;
	TADOCommand *cmdUpdateNote;
	TADOCommand *cmdDelNote;
	TRzSpacer *RzSpacer1;
	TADOCommand *cmdBatchUpdateNote;
	TADOCommand *cmdBatchDelNote;
	TRzToolButton *tlbtn1;
	TRzSpacer *RzSpacer4;
	TRzToolButton *tlbtnAddNote;
	TRzToolButton *tlbtn2;
	TRzToolButton *tlbtn3;
	TRzSpacer *RzSpacer2;
	TRzToolButton *RzToolButton2;
	TRzToolButton *tlbtn4;
	TRzToolButton *tlbtn5;
	TRzSpacer *RzSpacer3;
	TRzToolButton *tlbtn7;
	TADOCommand *cmdAddNtHeader;
	TRzLabel *lblOpName;
	TADOCommand *cmdResetNtHeader;
	TImageList *ImageList1;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
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
	TRzToolButton *BtnMonthView;
	TPanel *Panel1;
	TLabel *Label2;
	TRzDBGrid *dbgrdNote;
	TGroupBox *GroupBox1;
	TRzLabel *lbl3;
	TRzLabel *lbl4;
	TRzLabel *lbl7;
	TRzLabel *lbl1;
	TLabel *Label3;
	TSpeedButton *Sbutfirst;
	TSpeedButton *Sbutbefore;
	TSpeedButton *Sbutnext;
	TSpeedButton *Sbutend;
	TRzDBDateTimeEdit *dbdtedtHdTime;
	TRzDBEdit *dbedtRemarks;
	TRzDBNumericEdit *dbnbedtAddCosts;
	TRzDBEdit *dbedtWsaleNtCode;
	TComboBox *cbstate;
	TGroupBox *GroupBox2;
	TRzLabel *lblCatalog;
	TRzLabel *lbl8;
	TRzLabel *lbl9;
	TRzLabel *lbl5;
	TLabel *Label1;
	TRzDBNumericEdit *dbnbedtAmount;
	TRzEdit *edtCatalog;
	TRzDBNumericEdit *dbnbedtDiscount;
	TRzDBNumericEdit *dbnbedtTotalAmount;
	TRzCheckBox *chckbxSwitch;
	TRadioGroup *rg;
	TRzToolButton *BtnExport;
	TSpeedButton *SpeedButton1;
	TADOStoredProc *comfenlei;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *mtbbtnAddNtHeader;
	TLabel *Label4;
	TEdit *Edit1;
	TEdit *Edit2;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tlbtn1Click(TObject *Sender);
	void __fastcall tlbtn7Click(TObject *Sender);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall mniBsNoteSendbackClick(TObject *Sender);
	void __fastcall tlbtn4Click(TObject *Sender);
	void __fastcall dblkpcbbBkstackIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbedtRemarksKeyPress(TObject *Sender, wchar_t &Key);
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
	void __fastcall cbstateChange(TObject *Sender);
	void __fastcall SbutfirstClick(TObject *Sender);
	void __fastcall SbutbeforeClick(TObject *Sender);
	void __fastcall SbutnextClick(TObject *Sender);
	void __fastcall SbutendClick(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall BtnMonthViewClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rgClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
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
	int m_catalogSearchMode;//1Ϊ��� 2Ϊ�Ա��� 3Ϊ����
	OPMode m_opmode;//1Ϊ�鵥ģʽ 2Ϊ��ӵ�ͷģʽ 3Ϊɾ����ͷģʽ 4Ϊ��ӵ�ģʽ 5Ϊɾ����ģʽ 6Ϊͳһģʽ 7Ϊ�ֳ��տ�ģʽ
	BSMode m_bsmode;//1Ϊ������ģʽ 2Ϊ�˻���ģʽ
	void ChangeCatalogSearchMode();
	void ChangeBsmode(BSMode bsmode);
	void ChangeOpmode(OPMode opmode);

	void QryNtHeader(String code, bool qrybkstack = false);//��ѯ��ͷ
	void QryNtHeader(bool qrybkstack = false);//��ѯ��ͷ
	void QryNtHeader(int id, bool qrybkstack = false);//��ѯ��ͷ
	void DelNtHeader();//ɾ����ͷ



	void DelNote();//ɾ����
	void BatchSetNotes(int amount, float discount, int mode);
	void QryBkstack();
	void DelInvalidNtHeader();
	void ResetNtHeader();
	int addnotereturnvalue;
	String MaxNote,logmessage;
public:		// User declarations
	__fastcall TfrmZNProcureMng(TComponent* Owner);
	virtual void Init(LandInfo* li);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
		bool AddNote(int supplierID, int catalogID);//��ӵ�
		void FindNote(String code);
		void NtCodeChange();
		void AddNtHeader();//��ӵ�ͷ
		void UpdateNote();//���µ�
		 void UpdateNtHeader();//���µ�ͷ
		 int findagain;
		 bool findpwd,deletepwd;

};

//---------------------------------------------------------------------------
extern PACKAGE TfrmZNProcureMng *frmZNProcureMng;
//---------------------------------------------------------------------------
#endif
