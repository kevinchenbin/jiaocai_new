//---------------------------------------------------------------------------

#ifndef RetailSummaryFormH
#define RetailSummaryFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzLabel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "Chart.hpp"
#include "DBChart.hpp"
#include "Series.hpp"
#include "TeeData.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmRetailSummary : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton1;
	TADODataSet *dsquery;
	TDataSource *ds1;
	TChartDataSet *ChartDataSet1;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TCheckBox *cbend;
	TDateTimePicker *dtp1;
	TDateTimePicker *dtp2;
	TRadioButton *rb1;
	TRadioButton *rb2;
	TRadioButton *rb4;
	TRadioButton *rb5;
	TCheckBox *cbstart;
	TDBGridEh *DBGridEh1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TComboBox *cbstorage;
	TCheckBox *chstorage;
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall rzdbgrd4TitleClick(TColumn *Column);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
private:	// User declarations
	String format;
public:		// User declarations
	__fastcall TfrmRetailSummary(TComponent* Owner);
		void Init(TApplication* app, TADOConnection* con);
		int stgid;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRetailSummary *frmRetailSummary;
//---------------------------------------------------------------------------
#endif
