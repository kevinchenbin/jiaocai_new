//---------------------------------------------------------------------------

#ifndef UnitjifendhH
#define UnitjifendhH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmjifendh : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edcard;
	TLabel *Label2;
	TEdit *edname;
	TLabel *Label3;
	TEdit *edjifen;
	TComboBox *cbtype;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TLabel *Label4;
	TGroupBox *GroupBox1;
	TLabel *Label5;
	TEdit *edyouhui;
	TLabel *Label6;
	TADOConnection *fcon;
	void __fastcall cbtypeClick(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmjifendh(TComponent* Owner,TADOConnection *con);
	int userid,stgid,memberid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmjifendh *frmjifendh;
//---------------------------------------------------------------------------
#endif
