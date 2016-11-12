//---------------------------------------------------------------------------

#ifndef orderimportselectH
#define orderimportselectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmorderimportselect : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edbook;
	TDBGrid *DBGrid1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TADOQuery *query;
	TDataSource *ds;
	TLabel *Label2;
	TEdit *edpress;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TButton *buhebing;
	TADOCommand *comHebingshumu;
	TADOConnection *fcon;
	TLabel *Label3;
	TEdit *edisbn;
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall buhebingClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmorderimportselect(TComponent* Owner,TADOQuery *aq);
	bool newbook;
	AnsiString orderbook,orderpress,logmessage,ybookname,mbookname,orderisbn;
	void showorderbook();
	int ybookid,mbookid;
	int userid,stgid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmorderimportselect *frmorderimportselect;
//---------------------------------------------------------------------------
#endif
