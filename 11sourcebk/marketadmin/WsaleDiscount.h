//---------------------------------------------------------------------------

#ifndef WsaleDiscountH
#define WsaleDiscountH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzCmboBx.hpp"
#include "RzRadChk.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzDTP.hpp"
#include <ComCtrls.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
#include "RzLabel.hpp"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormWsaleDiscount : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TRzGroupBox *rgbdiscountplan;
	TRzGroupBox *rgbdiscountset;
	TLabel *Label4;
	TRzGroupBox *rgbdiscountview;
	TRzDBGrid *dbgdiscount;
	TDataSource *ds1;
	TADOQuery *querydetail;
	TADOQuery *query;
	TLabel *Label9;
	TRzCheckBox *cbMonday;
	TRzCheckBox *cbTuesday;
	TRzCheckBox *cbWednesday;
	TRzCheckBox *cbThursday;
	TRzCheckBox *cbFriday;
	TRzCheckBox *cbSaturday;
	TRzCheckBox *cbSunday;
	TEdit *eddiscount;
	TPopupMenu *PopupMenu;
	TMenuItem *Ndelete;
	TLabel *Label2;
	TLabel *Label3;
	TDateTimePicker *dtpstart;
	TDateTimePicker *dtpend;
	TRzToolButton *BtnSave;
	TRzLabel *lblCatalog;
	TRzEdit *edtCatalog;
	TPopupMenu *pm;
	TMenuItem *N3;
	TMenuItem *N2;
	TMenuItem *N1;
	TMenuItem *N4;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *aq;
	TPopupMenu *pm1;
	TMenuItem *N5;
	TMenuItem *N6;
	TRzToolButton *BtnAlignBottom;
	TLabel *Label1;
	TComboBox *cbstorage;
	TCheckBox *chall;
	void __fastcall dbgdiscountCellClick(TColumn *Column);
	void __fastcall NdeleteClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall eddiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbstorageSelect(TObject *Sender);
	void __fastcall challClick(TObject *Sender);

private:	// User declarations
	int correntdiscount;
	int type;
	int m_catalogSearchMode,m_storageID;
public:		// User declarations
	__fastcall TFormWsaleDiscount(TComponent* Owner,int stgid);
	void Init(TApplication* app, TADOConnection* con);
	void excuit();
	TADOConnection *cn;
	void __fastcall disable();
	void ChangeCatalogSearchMode();
	void Query();
    bool modify;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormWsaleDiscount *FormWsaleDiscount;
//---------------------------------------------------------------------------
#endif
