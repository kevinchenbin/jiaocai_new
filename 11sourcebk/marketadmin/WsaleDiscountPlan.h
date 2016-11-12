//---------------------------------------------------------------------------

#ifndef WsaleDiscountPlanH
#define WsaleDiscountPlanH
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
class TfrmWsaleDiscount : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TDataSource *ds;
	TADOQuery *query;
	TADOQuery *aq;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TDBGrid *DBGrid1;
	TLabel *Label1;
	TRzComboBox *cbstgid;
	TGroupBox *GroupBox2;
	TRadioButton *rbtotal;
	TRadioButton *rbpress;
	TRadioButton *rbtype;
	TRadioButton *rbsupplier;
	TCheckBox *cbcorrent;
	TGroupBox *GroupBox3;
	TLabel *Labelname;
	TLabel *Label4;
	TLabel *Label2;
	TRzComboBox *cbtype;
	TEdit *eddiscount;
	TRzToolButton *BtnSave;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall rbtotalClick(TObject *Sender);
	void __fastcall rbpressClick(TObject *Sender);
	void __fastcall rbtypeClick(TObject *Sender);
	void __fastcall rbsupplierClick(TObject *Sender);
	void __fastcall cbtypeSelect(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall cbcorrentClick(TObject *Sender);
	void __fastcall eddiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbstgidSelect(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);

private:	// User declarations
	int correntdiscount;
	int type;
	int fstgid;
public:		// User declarations
	__fastcall TfrmWsaleDiscount(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con,int stgid);
	TADOConnection *cn;
	void View(int tag);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWsaleDiscount *frmWsaleDiscount;
//---------------------------------------------------------------------------
#endif
