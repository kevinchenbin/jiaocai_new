//---------------------------------------------------------------------------

#ifndef UnitbalanceH
#define UnitbalanceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include <ImgList.hpp>
#include "RzCmboBx.hpp"
#include "RzDBGrid.hpp"
#include <Buttons.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "NoteCode.h"
#include "pdutil.h"
#include "Unitweishenhe.h"
#include "common\QryNoteCodeForm1.h"
#include <ComCtrls.hpp>
#include "RzEdit.hpp"
#include <Mask.hpp>
#include <DBCtrls.hpp>
#include "RpBase.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpSystem.hpp"
#include "RpRave.hpp"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmbalance : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TPanel *Panel1;
	TImageList *ImageList1;
	TRzToolButton *search;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnDelete;
	TRzToolButton *Btn;
	TRzToolButton *BtnOK;
	TRzToolButton *BtnCancel;
	TPanel *Panel3;
	TLabel *Label11;
	TADOQuery *aquery;
	TADOQuery *aqdg;
	TDataSource *ds;
	TLabel *Label13;
	TEdit *editmayang;
	TLabel *Label14;
	TEdit *editshiyang;
	TEdit *editthistime;
	TLabel *Label16;
	TEdit *editaddcost;
	TLabel *Label17;
	TEdit *edityijie;
	TLabel *Label18;
	TEdit *editweijie;
	TLabel *Label19;
	TADOQuery *aquerytotal;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnAlignBottom;
	TSpeedButton *spselectClient;
	TLabel *lablename;
	TLabel *Label21;
	TGroupBox *GroupBox1;
	TLabel *Label3;
	TEdit *editnum;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label20;
	TRzComboBox *cbjieshuantype;
	TRzComboBox *cbmethod;
	TEdit *editstate;
	TEdit *edithukuan;
	TDateTimePicker *dtp;
	TEdit *Edit1;
	TEdit *Edit2;
	TLabel *Label22;
	TEdit *edemploy;
	TLabel *Label23;
	TEdit *edjspz;
	TDBNavigator *dbnv;
	TEdit *edtclient;
	TRzComboBox *cbselect;
	TRzEdit *edtQryVendor;
	TRzDBGrid *dg;
	TMemo *membk;
	TLabel *Label10;
	TEdit *editmoney;
	TGroupBox *GroupBox3;
	TRzButton *spselect;
	TRzButton *sbautojieshuan;
	TLabel *Label1;
	TEdit *edityu;
	TLabel *Label12;
	TEdit *edityuhu;
	TLabel *Label2;
	TLabel *Label15;
	TEdit *edityinghu;
	TEdit *editweijiedan;
	TDataSource *dshd;
	TADOQuery *aqhd;
	TRzButton *autobt;
	TRvSystem *RvSystem1;
	TRvDataSetConnection *rvconfance;
	TRvProject *RvProject1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnPrint;
	TLabel *Label24;
	TEdit *edzryuhu;
	TLabel *Label25;
	TEdit *edduicong;
	TRzButton *btduicong;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TADOQuery *aqdg1;
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall editmoneyKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnClick(TObject *Sender);
	void __fastcall searchClick(TObject *Sender);
	void __fastcall BtnCancelClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall cbjieshuantypeChange(TObject *Sender);
	void __fastcall dgCellClick(TColumn *Column);
	void __fastcall cbselectSelect(TObject *Sender);
	void __fastcall cbselectKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtQryVendorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall spselectClick(TObject *Sender);
	void __fastcall sbautojieshuanClick(TObject *Sender);
	void __fastcall cbjieshuantypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbmethodKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edjspzKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbnvClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall dgDblClick(TObject *Sender);
	void __fastcall autobtClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall cbjieshuantypeExit(TObject *Sender);
	void __fastcall btduicongClick(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall edtQryVendorExit(TObject *Sender);

private:	// User declarations
   TADOConnection *fcon;
   BOOL AddNew;
   int Type;
   String Code;
   BOOL save;
   bool ChangeDisplay;

public:		// User declarations
   String Disc;
   void ReadyData();
   void Enable(BOOL var);
   void Excute(String sql);
   void GetdgData(String ID);
   void shenhe();
	__fastcall Tfrmbalance(TComponent* Owner,TADOConnection *cn,int userid,int type,int stgid,bool master);
	TStringList *selectID;
   void DisplayDetail();
   int fstgid,fuserid;
   bool fmaster;
   int ClientID;
   void ClientView();
   void Displaytotal(String documentid);
   void QryNthead(String code);
   int xiaoshubit;
   AnsiString cc,supshenheipwd,supfanshenpwd,clishenheipwd,clifanshenpwd;
   void Print(int modle);
   int hc,ts;
	bool AddEnable(int type,AnsiString code);
	void DisplayDetail(String Danhao);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmbalance *frmbalance;
//---------------------------------------------------------------------------
#endif
