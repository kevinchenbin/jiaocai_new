//---------------------------------------------------------------------------

#ifndef salebssetH
#define salebssetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <Buttons.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzCmboBx.hpp"
//---------------------------------------------------------------------------
class Tfrmsalebsset : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *销售业务;
	TCheckBox *cbstorezero;
	TSpeedButton *sbok;
	TSpeedButton *sbcancel;
	TADOQuery *aquery;
	TCheckBox *cbbear;
	TADOQuery *qryretairange;
	TDataSource *dsrcretairange;
	TCheckBox *cbwosalehistory;
	TLabel *Label23;
	TEdit *edwosaleday;
	TCheckBox *cbcheckedview;
	TCheckBox *cbwosalereturn;
	TCheckBox *cblowcostalter;
	TCheckBox *cblownormalalter;
	TCheckBox *cblownormalenable;
	TCheckBox *cblowcostenable;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *etdot;
	TCheckBox *cbpxtuihuocatch;
	TCheckBox *chxianchangrecive;
	TCheckBox *cbpxallclientdetail;
	TCheckBox *cbpxdeleteusepassword;
	TCheckBox *cbpxnobkinfosale;
	TCheckBox *cbpxnobkinfotuihuo;
	TCheckBox *cbpxfindusepassword;
	TCheckBox *cbpxtuihuousepassword;
	TGroupBox *GroupBox1;
	TRadioGroup *RadioGroup1;
	TCheckBox *cbpxdefaultdiscount;
	TCheckBox *cbpxdiscount;
	TCheckBox *cbwsaledisscountchange;
	TEdit *eddefaultdiscount;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TComboBox *cb1;
	TComboBox *cb2;
	TComboBox *cb3;
	TComboBox *cb4;
	TLabel *Label10;
	TGroupBox *GroupBox2;
	TCheckBox *chnokucunpxth;
	TLabel *Label11;
	TEdit *edmonth;
	TLabel *Label12;
	TCheckBox *chpxusechange;
	TCheckBox *chwsalesametishi;
	TGroupBox *GroupBox3;
	TCheckBox *chclientaddyx;
	TLabel *Label13;
	TLabel *Label14;
	TEdit *edpxtuihuoqixian;
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall eddefaultdiscountKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmsalebsset(TComponent* Owner,TADOConnection* con);
	void Readydata();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsalebsset *frmsalebsset;
//---------------------------------------------------------------------------
#endif
