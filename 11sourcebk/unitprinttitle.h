//---------------------------------------------------------------------------

#ifndef unitprinttitleH
#define unitprinttitleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrmprinttitle : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TADOConnection *fcon;
	TADOQuery *aq;
	TPageControl *PageControl1;
	TTabSheet *taborder;
	TTabSheet *tabcaigou;
	TTabSheet *rabrk;
	TTabSheet *tabws;
	TGroupBox *GroupBox2;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label4;
	TEdit *edorprintbk;
	TEdit *edorprinttitle;
	TEdit *edoraddress;
	TEdit *edorcontact;
	TEdit *edortel;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label5;
	TLabel *Label10;
	TEdit *edcgprintbk;
	TEdit *edcgprinttitle;
	TEdit *edcgaddress;
	TEdit *edcgcontact;
	TEdit *edcgtel;
	TGroupBox *GroupBox3;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TEdit *edrkprintbk;
	TEdit *edrkprinttitle;
	TEdit *edrkaddress;
	TEdit *edrkcontact;
	TEdit *edrktel;
	TGroupBox *GroupBox4;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TEdit *edwsprinttitle;
	TEdit *edwsaddress;
	TEdit *edwscontact;
	TEdit *edwstel;
	TEdit *edpxprintbk;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TRzButton *RzButton3;
	TRzButton *RzButton4;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TEdit *edshaddress;
	TEdit *edshcontact;
	TEdit *edshtel;
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton3Click(TObject *Sender);
	void __fastcall RzButton4Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmprinttitle(TComponent* Owner,TADOConnection *con,int stgid);
	int fstgid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmprinttitle *frmprinttitle;
//---------------------------------------------------------------------------
#endif
