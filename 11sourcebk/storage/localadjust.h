//---------------------------------------------------------------------------

#ifndef localadjustH
#define localadjustH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzDBGrid.hpp"
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <Menus.hpp>
#include "pdtypes.h"
#include "NoteCode.h"
#include "checkselbook.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include "pdutil.h"
#include <DBCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrmadjust : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnExit;
	TLabel *Label1;
	TGroupBox *GroupBox1;
	TPopupMenu *pm;
	TMenuItem *N4;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *ISBN1;
	TLabel *Label6;
	TEdit *edtnum;
	TLabel *Label7;
	TDateTimePicker *dtpdate;
	TLabel *Label8;
	TLabel *Label11;
	TADOQuery *aquery;
	TADOStoredProc *adosp;
	TADOTable *atable;
	TDataSource *ds;
	TRzToolButton *BtnPreviewNextPage;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnDelete;
	TADOQuery *aqueryupdate;
	TEdit *edtstg;
	TRzToolButton *BtnAlignBottom;
	TRzDBGrid *dgbook;
	TEdit *edstorageid;
	TLabel *lbsearch;
	TLabel *Label10;
	TLabel *Label3;
	TEdit *edtcheckinfo;
	TComboBox *cblocalin;
	TEdit *edtnumber;
	TMemo *memnote;
	TLabel *Label4;
	TLabel *ltotal;
	TLabel *ltotaladjust;
	TLabel *Label5;
	TLabel *Label9;
	TLabel *Label2;
	TEdit *edtemploy;
	TGroupBox *GroupBox2;
	TRzToolButton *BtnOK;
	TLabel *Label12;
	TEdit *edstate;
	TDBNavigator *DBNavigator1;
	TDataSource *dsheader;
	TADOQuery *aqheader;
	TMemo *membk;
	TRzToolButton *BtnView;
	void __fastcall edtcheckinfoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall ISBN1Click(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall edtnumberKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall lbsearchMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall DBNavigator1Click(TObject *Sender, TNavigateBtn Button);
	void __fastcall BtnViewClick(TObject *Sender);

private:	// User declarations
	TStringList *Store;
	TStringList *Local;
	String Code;
	int m_storageID;
	LandInfo checkli;
	int CatalogSearchMode;
	int m_local;
	AnsiString LockLocalID;    //被销售的库位ID列表
	void DisableInput(int Modal);
	TADOConnection *fcon;
public:		// User declarations
	__fastcall Tfrmadjust(TComponent* Owner,TADOConnection* con,LandInfo* li);
	void readyData(TADOQuery * aquery);
	void DelNtHeader();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmadjust *frmadjust;
//---------------------------------------------------------------------------
#endif
