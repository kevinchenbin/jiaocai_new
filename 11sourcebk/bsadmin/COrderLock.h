//---------------------------------------------------------------------------

#ifndef COrderLockH
#define COrderLockH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include "RzLabel.hpp"
#include <Menus.hpp>
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzDBGrid.hpp"
#include <Dialogs.hpp>
#include <Graphics.hpp>
#include "MDIChild.h"
#include "frxClass.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------

class TfrmCnetorderlock : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TImageList *ImageList1;
	TGroupBox *GroupBox1;
	TLabel *Label2;
	TDBEdit *dbeditdanhao;
	TLabel *label5;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnClear;
	TADOQuery *aqupdatehead;
	TLabel *Label15;
	TADOStoredProc *adospaddhead;
	TDataSource *dshead;
	TADOQuery *aqorderdetail;
	TDataSource *dsdetail;
	TRzToolButton *BtnView;
	TLabel *Label1;
	TLabel *Label17;
	TDataSource *dshd;
	TADOQuery *aqhd;
	TRzToolButton *BtnAlignBottom;
	TPopupMenu *pm1;
	TRzToolButton *BtnView1;
	TADOQuery *query;
	TEdit *edtclient;
	TRzToolButton *BtnOK1;
	TSaveDialog *savedlg;
	TDBGrid *dgdetail;
	TADOQuery *querypress;
	TADOStoredProc *adospcopy;
	TADOQuery *aquery;
	TDBNavigator *dbn;
	TMemo *membk;
	TRzToolButton *BtnCancel;
	TMenuItem *N14;
	TPopupMenu *pmexport;
	TMenuItem *N17;
	TMenuItem *N18;
	TEdit *editdetailbk;
	TLabel *Label10;
	TSpeedButton *SpeedButton5;
	TSpeedButton *SpeedButton4;
	TLabel *lab;
	TfrxReport *frxOrder;
	TfrxDBDataset *frxDBorddetail;
	TADOQuery *queryorder;
	TRzToolButton *BtnPost;
	TSpeedButton *SpeedButton1;
	void __fastcall dbnClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnView1Click(TObject *Sender);
	void __fastcall dbeditaddcostKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgdetail1DblClick(TObject *Sender);
	void __fastcall BtnOK1Click(TObject *Sender);

	void __fastcall dgdetailCellClick(TColumn *Column);

	void __fastcall dgdetailTitleClick(TColumn *Column);
	void __fastcall BtnCancelClick(TObject *Sender);
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall ch1Click(TObject *Sender);
	void __fastcall ch2Click(TObject *Sender);
	void __fastcall ch3Click(TObject *Sender);
	void __fastcall ch4Click(TObject *Sender);
	void __fastcall ch5Click(TObject *Sender);
	void __fastcall ch6Click(TObject *Sender);
	void __fastcall ch7Click(TObject *Sender);
	void __fastcall ch8Click(TObject *Sender);
	void __fastcall N14Click(TObject *Sender);
	void __fastcall N17Click(TObject *Sender);
	void __fastcall N18Click(TObject *Sender);
	void __fastcall SpeedButton5Click(TObject *Sender);
	void __fastcall frxOrderGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall BtnPostClick(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
	TADOConnection *fcon;
	int UserID;
	AnsiString UserName;
	int StgID;
	AnsiString Danhao,logmessage;
	int ClientID;
	int m_catalogSearchMode;
	int HeaderRec;
public:		// User declarations
	__fastcall TfrmCnetorderlock(TComponent* Owner);
	void init(LandInfo* li);
	AnsiString GetField(AnsiString sql,AnsiString Field);
	void ExecSQL(AnsiString sql);
	void RefreshDetail();
	bool __fastcall DbgridToExcel2(TDBGrid* dbg);
	void RefreshHead(int headerid);
	void ClientView();
	int headid,type;
	bool lastdiscount,ordertishi,orderfind,orderchange,orderviewclass;
	AnsiString month,printtitle,contact,tel,address,printbk;
	bool Master;
	bool DbgridToExcel(TDBGrid* dbg);
		void __fastcall dgdetailDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCnetorderlock *frmCnetorderlock;
//---------------------------------------------------------------------------
#endif
