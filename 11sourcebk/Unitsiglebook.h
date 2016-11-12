//---------------------------------------------------------------------------

#ifndef UnitsiglebookH
#define UnitsiglebookH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmsiglebook : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel2;
	TLabel *Label4;
	TEdit *edquery;
	TLabel *isbn;
	TEdit *edisbn;
	TLabel *Label1;
	TEdit *edname;
	TLabel *Label2;
	TEdit *edprice;
	TLabel *Label3;
	TEdit *edpress;
	TLabel *Label5;
	TEdit *edpresscount;
	TLabel *Label6;
	TEdit *edtype;
	TGroupBox *GroupBox1;
	TCheckBox *chstart;
	TDateTimePicker *dtpstart;
	TCheckBox *chend;
	TDateTimePicker *dtpend;
	TRadioGroup *rg;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TADOConnection *fcon;
	TDataSource *ds1;
	TADOQuery *aq1;
	TDataSource *ds2;
	TADOQuery *aq2;
	TDBGridEh *dg2;
	TDBGridEh *dg1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnView;
	TLabel *Label7;
	TEdit *edauthor;
	TLabel *Label8;
	TEdit *edbkinfo;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	TDBGridEh *dg3;
	TDataSource *ds3;
	TADOQuery *aq3;
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall rgClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall Label4MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall dg1TitleClick(TColumnEh *Column);

	


private:	// User declarations
public:		// User declarations
	__fastcall Tfrmsiglebook(TComponent* Owner,TADOConnection *con,int stgid);
	int m_catalogSearchMode,bkcatalogid,fstgid;
	void ChangeCatalogSearchMode();
	void Query();
	bool ChangeDisplay;
	bool DbgridToExcel(TDBGridEh* dbg);
	void __fastcall dg3DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumnEh *Column, Gridseh::TGridDrawState State);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsiglebook *frmsiglebook;
//---------------------------------------------------------------------------
#endif
