//---------------------------------------------------------------------------

#ifndef UnitorderqueryH
#define UnitorderqueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmorderquery : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDateTimePicker *dtpstart;
	TCheckBox *chstart;
	TDateTimePicker *dtpend;
	TCheckBox *chend;
	TCheckBox *chclient;
	TSpeedButton *spselectClient;
	TEdit *edclient;
	TEdit *edtclient;
	TCheckBox *chcode;
	TEdit *edcode;
	TADOConnection *fcon;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *query;
	TButton *Button1;
	TButton *Button2;
	TCheckBox *chinorder;
	TCheckBox *chuser;
	TComboBox *cbuser;
	TCheckBox *chshenhei;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall DBGrid1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall edtclientChange(TObject *Sender);
	void __fastcall edcodeChange(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmorderquery(TComponent* Owner,TADOConnection *con,int stgid,int modle,int tuihuo,boolean aisprint);
	int fstgid,ftuihuo,fmodle; //1Ϊ������2Ϊ������
	int  ClientID;
	AnsiString GetNoteCode();
	TBookmark bm;
	void ClientView();
	bool ChangeDisplay;
	AnsiString sqlwhere,sqladd;
	AnsiString GetWhere();
	boolean printnow;
	AnsiString  headerid;
	boolean isprint;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmorderquery *frmorderquery;
//---------------------------------------------------------------------------
#endif