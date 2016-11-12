//---------------------------------------------------------------------------

#ifndef UnitDiaoboH
#define UnitDiaoboH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <DBCtrls.hpp>
#include <ComCtrls.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "NoteCode.h"
#include "pdutil.h"
#include <Mask.hpp>
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include <Menus.hpp>
#include "RpBase.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpSystem.hpp"
#include <Dialogs.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------

class Tfrmdiaobo : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TPanel *Panel1;
	TImageList *ImageList1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnSaveAll;
	TRzToolButton *BtnPrintPreview;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnExit;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *diaobocode;
	TRzToolButton *Btn;
	TRzToolButton *Btn1;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TDateTimePicker *dtpdata;
	TComboBox *cboutstorage;
	TComboBox *cbinstorage;
	TComboBox *cbinbkstack;
	TRzToolButton *BtnDelete;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TADOConnection *con;
	TRzDBNumericEdit *dbtotalamount;
	TRzDBNumericEdit *dbtotalmayang;
	TRzDBNumericEdit *dntotalshiyang;
	TADOQuery *aq;
	TLabel *Label17;
	TDataSource *ds;
	TADOQuery *aquery;
	TADOStoredProc *spqryntheader1;
	TADOStoredProc *spqryntheader;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TADOStoredProc *cmdaddnote;
	TADODataSet *dsetNtHeader;
	TDataSource *dsheader;
	TADOCommand *cmdDelNote;
	TADOCommand *cmdBatchDelNote;
	TADOCommand *cmdUpdateNote;
	TADOCommand *cmdshenhe;
	TRzToolButton *BtnJumptoLine;
	TADOCommand *cmdBatchUpdateNote;
	TPopupMenu *selectmenu;
	TMenuItem *N5;
	TMenuItem *N6;
	TRvProject *RvProject1;
	TRvSystem *RvSystem1;
	TRvDataSetConnection *rvdatacondiaobo;
	TDataSource *dshd;
	TADOQuery *aqhd;
	TLabel *Label18;
	TRzDBGrid *DBGrid1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnView1;
	TMenuItem *N7;
	TMenuItem *N8;
	TADOStoredProc *adospcopy;
	TEdit *edopname;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TEdit *edcatalog;
	TRzDBNumericEdit *dbnumamount;
	TRzDBNumericEdit *dbnumdiscount;
	TGroupBox *GroupBox2;
	TMemo *membk;
	TSaveDialog *savedlg;
	TRzToolButton *BtnFinish;
	TEdit *edcheckuser;
	TLabel *Label2;
	TEdit *edstate;
	TLabel *Label6;
	TRzDBNumericEdit *dbamountbk;
	TRzToolButton *BtnCancel;
	TRzToolButton *BtnCancel1;
	TDBNavigator *DBNavigator1;
	TRzToolButton *BtnOK;
	TADOQuery *query;
	TRzToolButton *BtnBullets;
	TADOQuery *aqprint;
	TfrxReport *frxdiaobo;
	TfrxDBDataset *frxDBdiaobo;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnSaveAllClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall edcatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall cbinstorageChange(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall dbnumamountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbnumdiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbnumamount1Exit(TObject *Sender);
	void __fastcall BtnClick(TObject *Sender);
	void __fastcall Btn1Click(TObject *Sender);
	void __fastcall BtnJumptoLineClick(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall Label10MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall BtnPrintPreviewClick(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall DBNavigator1Click(TObject *Sender, TNavigateBtn Button);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnView1Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall cboutstorageChange(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall cbinbkstackClick(TObject *Sender);
	void __fastcall BtnFinishClick(TObject *Sender);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall BtnCancelClick(TObject *Sender);
	void __fastcall BtnCancel1Click(TObject *Sender);
	void __fastcall dbnumamountExit(TObject *Sender);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall dbamountbkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnBulletsClick(TObject *Sender);
	void __fastcall membkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall frxdiaoboGetValue(const UnicodeString VarName, Variant &Value);

private:	// User declarations
public:		// User declarations
	__fastcall Tfrmdiaobo(TComponent* Owner,TADOConnection *cn,int stgid,int userid,int type);

	void ReadData();
	void ReadDateWhenClick(int ins , int outs);
	void ReadinData();
	int fstgid,instorage,fuserid,outstorage;
	void QryNtHeader(String code);
	void QryNtHeader(int id);
	int m_catalogSearchMode;
	void ChangeCatalogSearchMode();
	bool AddNote(int catalogID);
	void DelNote();
	void UpdateNote();
	void QryNtHeader();
	void BatchSetNotes(int amount, float discount, int mode);
	void PrintPreview(int mode);
	AnsiString stogName,username,logmessage;
	void Query(AnsiString Code);
	int ftype;   //1÷˜∂Ø≈‰ÀÕ,2…Í«Î≈‰ÀÕ
	void ExcelExport(TRzDBGrid* dbg);
	int bkchange;
	void UpdateNote1();
	bool sametishi;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmdiaobo *frmdiaobo;
//---------------------------------------------------------------------------
#endif
