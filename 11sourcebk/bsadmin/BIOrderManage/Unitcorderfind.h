//---------------------------------------------------------------------------

#ifndef UnitcorderfindH
#define UnitcorderfindH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmcorderfind : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDateTimePicker *dtpstart;
	TCheckBox *chstart;
	TDateTimePicker *dtpend;
	TCheckBox *chend;
	TCheckBox *chclient;
	TEdit *edtclient;
	TCheckBox *chcode;
	TEdit *edcode;
	TDBGrid *DBGrid1;
	TButton *Button1;
	TButton *Button2;
	TCheckBox *chinorder;
	TComboBox *cbzt;
	TCheckBox *shouhuo;
	TEdit *editaddress;
	TCheckBox *tel;
	TEdit *edittel;
	TCheckBox *danhao;
	TEdit *Edit3;
	TADOQuery *aqfind;
	TDataSource *ds;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edtclientChange(TObject *Sender);
	void __fastcall edcodeChange(TObject *Sender);
	void __fastcall edittelChange(TObject *Sender);
	void __fastcall editaddressChange(TObject *Sender);
	void __fastcall Edit3Change(TObject *Sender);
private:	// User declarations
	TADOConnection *fcon;
	int fUserID;
	AnsiString UserName;
	int fStgID;
	AnsiString wheres;
public:		// User declarations
	__fastcall Tfrmcorderfind(TComponent* Owner,TADOConnection *con,int stgid,int UserID);
	AnsiString GetWhere();
	AnsiString GetSelectDH();

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmcorderfind *frmcorderfind;
//---------------------------------------------------------------------------
#endif