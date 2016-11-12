//---------------------------------------------------------------------------

#ifndef bssetH
#define bssetH
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
//---------------------------------------------------------------------------
class Tfrmbsset : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *销售业务;
	TCheckBox *cbstorezero;
	TSpeedButton *sbok;
	TSpeedButton *sbcancel;
	TADOQuery *aquery;
	TGroupBox *GroupBox1;
	TCheckBox *cbsameid;
	TCheckBox *cborder;
	TCheckBox *cbauto;
	TCheckBox *cbtrace;
	TCheckBox *cbbear;
	TLabel *Label1;
	TEdit *etdot;
	TLabel *Label2;
	TCheckBox *cbpxdiscount;
	TCheckBox *CheckBox2;
	TGroupBox *GroupBox2;
	TCheckBox *cbnosalereturn;
	TLabel *Label3;
	TEdit *edmin1;
	TLabel *Label4;
	TEdit *edmax1;
	TLabel *Label5;
	TEdit *edlost1;
	TLabel *Label6;
	TEdit *edlost2;
	TEdit *edmax2;
	TEdit *edmin2;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *edlost3;
	TEdit *edmax3;
	TEdit *edmin3;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TEdit *edlost4;
	TEdit *edmax4;
	TEdit *edmin4;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TEdit *edlost5;
	TEdit *edmax5;
	TEdit *edmin5;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TADOQuery *qryretairange;
	TDataSource *dsrcretairange;
	TCheckBox *cbeffect1;
	TCheckBox *cbeffect2;
	TCheckBox *cbeffect3;
	TCheckBox *cbeffect4;
	TCheckBox *cbeffect5;
	TCheckBox *cbstoragehistory;
	TLabel *进退货明细;
	TEdit *edstorageday;
	TCheckBox *cbwosalehistory;
	TLabel *Label23;
	TEdit *edwosaleday;
	TCheckBox *cbcheckedview;
	TCheckBox *cbwosalereturn;
	TGroupBox *GroupBox3;
	TCheckBox *cbautolocalstockbyOrder;
	TCheckBox *cbalarmcredit;
	TCheckBox *cbforbidcredit;
	TCheckBox *cbforbidbackrate;
	TCheckBox *cbalarmbackrate;
	TCheckBox *cbRetailDiscountChange;
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
	void __fastcall cbeffect1Click(TObject *Sender);
	void __fastcall cbeffect2Click(TObject *Sender);
	void __fastcall cbeffect3Click(TObject *Sender);
	void __fastcall cbeffect4Click(TObject *Sender);
	void __fastcall cbeffect5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmbsset(TComponent* Owner,TADOConnection* con);
	void Readydata();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmbsset *frmbsset;
//---------------------------------------------------------------------------
#endif
