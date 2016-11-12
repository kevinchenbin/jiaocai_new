//---------------------------------------------------------------------------

#ifndef unitinorderfenfaH
#define unitinorderfenfaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrmunitinorder : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TADOConnection *fcon;
	TDataSource *ds;
	TADOQuery *query;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnLastRecord;
	TADOCommand *cmdAddNote;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	TDateTimePicker *dtp1;
	TDateTimePicker *dtp2;
	TCheckBox *ch1;
	TCheckBox *ch2;
	TRzToolButton *BtnView;

	void __fastcall BtnLastRecordClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmunitinorder(TComponent* Owner,TADOConnection *con,int headerid,AnsiString catalogidlist);
	int stgid,userid,hdid,sgfirsthid;
	AnsiString returncode,sgheaderid,rkcode;
	bool DbgridToExcel(TDBGrid* dbg);
		void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmunitinorder *frmunitinorder;
//---------------------------------------------------------------------------
#endif
