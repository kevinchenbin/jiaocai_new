//---------------------------------------------------------------------------

#ifndef retailbssetH
#define retailbssetH
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
class Tfrmretailbsset : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSpeedButton *sbok;
	TSpeedButton *sbcancel;
	TADOQuery *aquery;
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
	TCheckBox *cbRetailDiscountChange;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *etdot;
	TCheckBox *cbxiaopiaoprint;
	TCheckBox *cblsusefind;
	TCheckBox *cblsusedelete;
	TCheckBox *cblsusetuihuo;
	TEdit *edlsprintbk;
	TCheckBox *cblsprintbk;
	TGroupBox *GroupBox1;
	TCheckBox *chjiaojieprint;
	TCheckBox *chlsdiscount;
	TCheckBox *chretailbear;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox4;
	TCheckBox *chMemberdiscountyouxian;
	TCheckBox *chRetaiview;
	TLabel *Label23;
	TCheckBox *chRetailsingle;
	TCheckBox *chRetaitype;
	TCheckBox *chguadan;
	TCheckBox *chretailtuihuan;
	TCheckBox *chretailprice;
	TCheckBox *chguadantishi;
	TCheckBox *chhuanjiapwd;
	TCheckBox *chhuankoupwd;
	TCheckBox *chminlsdiscount;
	TEdit *edlsdiscount;
	TCheckBox *chstorage;
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
	void __fastcall cbeffect1Click(TObject *Sender);
	void __fastcall cbeffect2Click(TObject *Sender);
	void __fastcall cbeffect3Click(TObject *Sender);
	void __fastcall cbeffect4Click(TObject *Sender);
	void __fastcall cbeffect5Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall chlsdiscountClick(TObject *Sender);
	void __fastcall chguadanClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmretailbsset(TComponent* Owner,TADOConnection* con);
	void Readydata();
	void StyleView();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmretailbsset *frmretailbsset;
//---------------------------------------------------------------------------
#endif
