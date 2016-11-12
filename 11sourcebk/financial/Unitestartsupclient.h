//---------------------------------------------------------------------------

#ifndef UnitestartsupclientH
#define UnitestartsupclientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmsupplierandclient : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TLabel *labeltitle;
	TEdit *editmoney;
	TLabel *Label3;
	TEdit *edityu;
	TLabel *Label4;
	TRzComboBox *cbselect;
	TADOQuery *aquery;
	TDataSource *ds;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TRzToolButton *BtnAlignBottom;
	TEdit *edquery;
	TSpeedButton *spselectClient;
	TEdit *edtclient;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExport;
	TDBGrid *dg;
	TSaveDialog *savedlg;
	TLabel *Label1;
	TEdit *edqichuyue;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall editmoneyKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall labeltitleMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall cbselectSelect(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall dgCellClick(TColumn *Column);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall dgDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);

private:	// User declarations
	TADOConnection *fcon;
	String Disc;
public:		// User declarations
	__fastcall Tfrmsupplierandclient(TComponent* Owner,TADOConnection *cn,int type);
	void ReadyData(int type);
	int ClientID;
	void ClientView();
	int Type;
	void Query();
	bool DbgridToExcel(TDBGrid* dbg);
	String storageformat,saleformat;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsupplierandclient *frmsupplierandclient;
//---------------------------------------------------------------------------
#endif
