//---------------------------------------------------------------------------

#ifndef fastcheckH
#define fastcheckH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzEdit.hpp"
#include <Mask.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzDBGrid.hpp"
//---------------------------------------------------------------------------
class Tfrmfastcheck : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TADOConnection *fcn;
	TDBGrid *DBGrid1;
	TADOQuery *query;
	TGroupBox *GroupBox2;
	TDataSource *ds;
	TLabel *Label2;
	TEdit *edmoney;
	TLabel *Label1;
	TLabel *Label3;
	TEdit *edchecked;
	TLabel *Label4;
	TEdit *ednochecked;
	TLabel *Label5;
	TEdit *eddaymoney;
	TLabel *Label6;
	TEdit *edchenkedmoney;
	TRadioGroup *rg;
	TButton *Button1;
	TButton *Button2;
	TGroupBox *GroupBox1;
	TButton *btrefresh;
	TButton *btshengji;
	TButton *btexit;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TLabel *Label7;
	void __fastcall btexitClick(TObject *Sender);
	void __fastcall btrefreshClick(TObject *Sender);
	void __fastcall edmoneyKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btshengjiClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall DBGrid1CellClick(TColumn *Column);

	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
private:	// User declarations
	int fstgid;
	bool ChangeDisplay;
public:		// User declarations
	__fastcall Tfrmfastcheck(TComponent* Owner,TADOConnection *cn,int stgid);
	bool DbgridToExcel(TDBGrid* dbg);
	void TotalView();
		void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
	AnsiString username ;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmfastcheck *frmfastcheck;
//---------------------------------------------------------------------------
#endif
