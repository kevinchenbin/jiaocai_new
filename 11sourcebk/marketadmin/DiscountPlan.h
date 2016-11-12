//---------------------------------------------------------------------------

#ifndef DiscountPlanH
#define DiscountPlanH
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
//---------------------------------------------------------------------------
class TFormDiscount : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TDataSource *ds1;
	TADOQuery *querydetail;
	TADOQuery *query;
	TPopupMenu *PopupMenu;
	TMenuItem *Ndelete;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnSave;
	TLabel *Label10;
	TRzComboBox *cbstgid;
	TGroupBox *GroupBox1;
	TLabel *Labelname;
	TLabel *Label4;
	TLabel *Label9;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label5;
	TRzComboBox *cbtype;
	TEdit *eddiscount;
	TRzCheckBox *rcbMember;
	TDateTimePicker *dtpstart;
	TDateTimePicker *dtpend;
	TComboBox *cbmembertype;
	TRzCheckBox *cbMonday;
	TRzCheckBox *cbWednesday;
	TRzCheckBox *cbThursday;
	TRzCheckBox *cbFriday;
	TRzCheckBox *cbSaturday;
	TRzCheckBox *cbSunday;
	TRzCheckBox *cbTuesday;
	TRzDBGrid *dbgdiscount;
	TCheckBox *cball;
	void __fastcall cbstgidSelect(TObject *Sender);
	void __fastcall dbgdiscountCellClick(TColumn *Column);
	void __fastcall NdeleteClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall cbtypeChange(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall eddiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall cballClick(TObject *Sender);

private:	// User declarations
	int correntdiscount;
	int type;
	int fstgid;
public:		// User declarations
	__fastcall TFormDiscount(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con,int stgid);
	TADOConnection *cn;
	void __fastcall disable();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDiscount *FormDiscount;
//---------------------------------------------------------------------------
#endif
