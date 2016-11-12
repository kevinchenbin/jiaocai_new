//---------------------------------------------------------------------------

#ifndef unitBorderH
#define unitBorderH
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
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <Dialogs.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class Tfrmunitorder : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TADOConnection *fcon;
	TDataSource *ds;
	TADOQuery *query;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnView;
	TRzToolButton *BtnZoomIn;
	TRzToolButton *BtnZoomOut;

	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnZoomInClick(TObject *Sender);
	void __fastcall BtnZoomOutClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall Tfrmunitorder(TComponent* Owner,TADOConnection *con,int headerid);
	AnsiString rkcode;
	int headid;
	int ISBNET;
	bool DbgridToExcel(TDBGrid* dbg);
		void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmunitorder *frmunitorder;
//---------------------------------------------------------------------------
#endif