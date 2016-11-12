//---------------------------------------------------------------------------

#ifndef UnitcheckqueryH
#define UnitcheckqueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class Tfrmcheck : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnExport;
	TLabel *Label1;
	TDateTimePicker *dtbegin;
	TLabel *Label2;
	TDateTimePicker *dtend;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TADOQuery *queryhead;
	TADOQuery *querydetail;
	TDataSource *dsheader;
	TDataSource *dsdetail;
	TDBGrid *dgdetail;
	TGroupBox *GroupBox4;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TDBGrid *dghead;
	TEdit *edtotalpandian;
	TEdit *edtotalblance;
	TGroupBox *GroupBox5;
	TLabel *Label6;
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall dgheadCellClick(TColumn *Column);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExportClick(TObject *Sender);
private:	// User declarations
	bool DbgridToExcel(TDBGrid* dbg);
public:		// User declarations
	__fastcall Tfrmcheck(TComponent* Owner,TADOConnection *cn);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmcheck *frmcheck;
//---------------------------------------------------------------------------
#endif
