//---------------------------------------------------------------------------

#ifndef MemberTypeDiscountH
#define MemberTypeDiscountH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzRadChk.hpp"
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmMemberDiscount : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnSave;
	TImageList *ImageList1;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N3;
	TMenuItem *N2;
	TMenuItem *N4;
	TPopupMenu *pm1;
	TMenuItem *N5;
	TPopupMenu *PopupMenu;
	TMenuItem *N6;
	TMenuItem *Ndelete;
	TRzGroupBox *rgbdiscountplan;
	TRzLabel *lblCatalog;
	TRzEdit *edtCatalog;
	TDBGrid *DBGrid1;
	TRzGroupBox *rgbdiscountview;
	TRzDBGrid *dbgdiscount;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TComboBox *cbstorage;
	TLabel *Label5;
	TComboBox *cbmembertype;
	TDataSource *ds1;
	TADOQuery *aq;
	TDataSource *ds2;
	TADOQuery *querydetail;
	TADOQuery *query;
	TRzToolButton *BtnAlignBottom;
	TGroupBox *GroupBox2;
	TLabel *Label4;
	TLabel *Label9;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *eddiscount;
	TDateTimePicker *dtpstart;
	TDateTimePicker *dtpend;
	TLabel *Label6;
	TEdit *edprice;
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall NdeleteClick(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall eddiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbstorageSelect(TObject *Sender);
	void __fastcall edpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbgdiscountCellClick(TColumn *Column);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
private:	// User declarations
	int m_catalogSearchMode;
	int fstgid;
public:		// User declarations
	__fastcall TfrmMemberDiscount(TComponent* Owner,TADOConnection* con,int stgid);
	void ChangeCatalogSearchMode();
	void Query();
	void __fastcall disable();
	void excuit();
	bool modify;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMemberDiscount *frmMemberDiscount;
//---------------------------------------------------------------------------
#endif
