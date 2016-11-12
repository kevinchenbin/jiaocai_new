//---------------------------------------------------------------------------

#ifndef unitcfpandianH
#define unitcfpandianH
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
class Tfrmcfpandian : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TEdit *edamount;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TADOConnection *con;
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall edamountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmcfpandian(TComponent* Owner,TADOConnection *cn);
	int stkbkid;
	int bendan,addamount;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmcfpandian *frmcfpandian;
//---------------------------------------------------------------------------
#endif
