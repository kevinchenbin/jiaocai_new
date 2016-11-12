//---------------------------------------------------------------------------

#ifndef saleanalysisH
#define saleanalysisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzEdit.hpp"
#include <Buttons.hpp>
#include <Mask.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmsaleanalysis : public TForm
{
__published:	// IDE-managed Components
	TPanel *P;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnExport;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TComboBox *cbstore;
	TRzCheckBox *cbstart;
	TRzCheckBox *cbend;
	TDateTimePicker *dtpstart;
	TDateTimePicker *dtpend;
	TRzToolButton *BtnView;
	TComboBox *cbanalysistype;
	TLabel *Label2;
	TRzToolButton *BtnPrint;
	TADOQuery *aqheader;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TRzDBGrid *dgheadnote;
	TRzDBGrid *dgdetail;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *lcount;
	TDataSource *ds;
	TLabel *Label6;
	TEdit *edtnum;
	TLabel *Label7;
	TEdit *edtmanyang;
	TLabel *Label8;
	TEdit *edtshiyang;
	TADOQuery *aqdetal;
	TDataSource *ds2;
	TRzToolButton *BtnAlignBottom;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TSpeedButton *spselectClient;
	TRzEdit *edtQryVendor;
	TEdit *edtclient;
	TCheckBox *chclient;
	TADOConnection *fcon;
	TLabel *Label5;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *edordermun;
	TEdit *edordermayang;
	TEdit *edordershiyang;
	TSaveDialog *savedlg;
	void __fastcall cbanalysistypeChange(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall dgheadnoteCellClick(TColumn *Column);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall dgheadnoteTitleClick(TColumn *Column);
	void __fastcall dgdetailTitleClick(TColumn *Column);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall edtQryVendorKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
	int SearchModal;
	AnsiString Title;
	String retailformat,saleformat;
	float totalshiyang,totalmayang,ordermayang,ordershiyang;
	int totalnum,ordernum;
public:		// User declarations
   void ReadyData();
   TADOConnection *con;
   void Query();
   void GetTotal(TADOQuery *aq);
   String GetDesic();
   void GetDataForDg(AnsiString SQLstr, TADOQuery *aq,TRzDBGrid * dg);
   __fastcall Tfrmsaleanalysis(TComponent* Owner,TADOConnection * cn,int stgid);
   bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
   int fstgid,ClientID;
   void ClientView();
   bool ToExcel0();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsaleanalysis *frmsaleanalysis;
//---------------------------------------------------------------------------
#endif
