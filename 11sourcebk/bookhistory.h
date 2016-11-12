//---------------------------------------------------------------------------

#ifndef bookhistoryH
#define bookhistoryH
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
class Tfrmbookhistory : public TForm
{
__published:	// IDE-managed Components
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TADOConnection *fcon;
	TDataSource *ds1;
	TADOQuery *aq1;
	TDataSource *ds2;
	TADOQuery *aq2;
	TImageList *ImageList1;
	TSaveDialog *savedlg;
	TPopupMenu *PopupMenu1;
	TPanel *Panel2;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TCheckBox *chstart;
	TDateTimePicker *dtpstart;
	TCheckBox *chend;
	TDateTimePicker *dtpend;
	TRadioGroup *rg;
	TEdit *edamount;
	TDBGridEh *dg1;
	TDBGridEh *dbgridcg;
	TDBGridEh *dbgridrk;
	TDBGridEh *dbgridfh;
	TDBGridEh *dbgridls;
	TDBGridEh *dbgridps;
	TADOQuery *aq6;
	TADOQuery *aq5;
	TADOQuery *aq3;
	TADOQuery *aq4;
	TADOQuery *ADOQuery5;
	TDataSource *DataSource1;
	TDataSource *ds6;
	TDataSource *ds5;
	TDataSource *ds4;
	TDataSource *ds3;
	TADOQuery *aq7;
	TDataSource *ds7;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall rgClick(TObject *Sender);
	void __fastcall dg1TitleClick(TColumnEh *Column);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall dg1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumnEh *Column, Gridseh::TGridDrawState State);
	void __fastcall dbgridcgTitleClick(TColumnEh *Column);
	void __fastcall dbgridfhTitleClick(TColumnEh *Column);
	void __fastcall dbgridlsTitleClick(TColumnEh *Column);
	void __fastcall dbgridpsTitleClick(TColumnEh *Column);
	void __fastcall dbgridrkTitleClick(TColumnEh *Column);

private:	// User declarations
public:		// User declarations

	__fastcall Tfrmbookhistory(TComponent* Owner,TADOConnection *con,int stgid,int catalogid,int userid);

	int m_catalogSearchMode,bkcatalogid,fstgid,fuserid;

	void Query();
	bool ChangeDisplay,rkdiscount,wsdiscount;
	AnsiString bookname;

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmbookhistory *frmbookhistory;
//---------------------------------------------------------------------------
#endif
