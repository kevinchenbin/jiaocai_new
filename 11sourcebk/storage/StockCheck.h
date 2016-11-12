//---------------------------------------------------------------------------

#ifndef StockCheckH
#define StockCheckH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include "pdtypes.h"
#include "pdutil.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include "checkselbook.h"
#include "RzPrgres.hpp"
#include "NotCheckBook.h"
#include "stockcheckprint.h"
#include "print.h"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpBase.hpp"
#include "RpSystem.hpp"
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmcheckstock : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TGroupBox *GroupBox1;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TComboBox *cblocal;
	TLabel *Label7;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TADOQuery *aquery;
	TADOTable *atable;
	TDataSource *ds;
	TADOStoredProc *adosp;
	TMenuItem *N4;
	TADOQuery *aqueryupdate;
	TRzToolButton *BtnPrint;
	TRzToolButton *Btninit;
	TRzToolButton *BtnViewList;
	TRzToolButton *BtnViewIcons;
	TRzToolButton *BtnHorizontalTile;
	TMemo *memnote;
	TEdit *edtstore;
	TADOQuery *adocount;
	TADOQuery *aquerynotcheckbook;
	TLabel *�̵㵥;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnClear;
	TRvProject *RvProject1;
	TRvDataSetConnection *rvt;
	TRvSystem *RvSystem1;
	TRzToolButton *BtnAlignBottom;
	TRzDBNumericEdit *RzDBNumericEdit1;
	TRzDBNumericEdit *RzDBNumericEdit2;
	TRzDBNumericEdit *RzDBNumericEdit4;
	TDataSource *dsheader;
	TADOQuery *aqheader;
	TLabel *Label9;
	TLabel *Label11;
	TLabel *Label12;
	TSaveDialog *savedlg;
	TEdit *edstorageid;
	TMemo *membk;
	TLabel *Label15;
	TLabel *Label16;
	TEdit *editusername;
	TEdit *editstate;
	TLabel *Label17;
	TEdit *editnum;
	TLabel *Label14;
	TEdit *edbk;
	TEdit *edsamount;
	TEdit *edtnumber;
	TEdit *edtcheckinfo;
	TLabel *Label13;
	TLabel *Label1;
	TLabel *lbsearch;
	TDBGrid *dgcheck;
	TGroupBox *GroupBox2;
	TMenuItem *N5;
	TLabel *Label2;
	TDateTimePicker *dtpstart;
	TRzToolButton *BtnProperties;
	TADOConnection *fcon;
	TRzToolButton *BtnChangeOptions;
	void __fastcall edtcheckinfoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall lbsearchMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall edtnumberKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnViewListClick(TObject *Sender);
	void __fastcall dgcheckCellClick(TColumn *Column);
	void __fastcall BtnHorizontalTileClick(TObject *Sender);
	void __fastcall BtnViewIconsClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall edtnumberExit(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edsamountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edbkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall membkExit(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall BtnPropertiesClick(TObject *Sender);
	void __fastcall BtninitClick(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);

private:	// User declarations
	TStringList *Store;
	TStringList *Local;
	String Code;
	int m_storageID;
	LandInfo checkli;
	int CatalogSearchMode;
	int m_local;
	TADOConnection *connect;
public:		// User declarations
	__fastcall Tfrmcheckstock(TComponent* Owner,TADOConnection* con,LandInfo* li);
	void ReadData(TADOQuery * aquery);
	bool DbgridToExcel(TDBGrid* dbg);
	void EndPandian();
	bool weipanshu;
	int count,guanliyuan;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmcheckstock *frmcheckstock;
//---------------------------------------------------------------------------
#endif
