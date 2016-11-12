//---------------------------------------------------------------------------

#ifndef UnitOrdertofahuoH
#define UnitOrdertofahuoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "RzButton.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfrmOrdertoFahuo : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TSpeedButton *spselectClient;
	TCheckBox *chordercode;
	TEdit *edordercode;
	TCheckBox *chclient;
	TEdit *edclient;
	TEdit *edtclient;
	TRzButton *RzButton1;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *query;
	TADOConnection *con;
	TDataSource *ds2;
	TADOQuery *query2;
	TRzButton *RzButton3;
	TCheckBox *chxiaoqu;
	TComboBox *cbxiaoqu;
	TCheckBox *chxueyuan;
	TComboBox *cbxueyuan;
	TCheckBox *chclass;
	TComboBox *cbclass;
	TCheckBox *chstart;
	TDateTimePicker *dtpstart;
	TCheckBox *chend;
	TDateTimePicker *dtpend;
	TRzDateTimeEdit *dtedtDate;
	TRzSpinEdit *spedtID;
	TCheckBox *chall;
	TRzButton *RzButton2;
	TPopupMenu *pm;
	TMenuItem *N1;
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton3Click(TObject *Sender);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall cbclassChange(TObject *Sender);
	void __fastcall cbxueyuanChange(TObject *Sender);
	void __fastcall cbxiaoquChange(TObject *Sender);
	void __fastcall edtclientChange(TObject *Sender);
	void __fastcall dtedtDateChange(TObject *Sender);
	void __fastcall spedtIDChange(TObject *Sender);
	void __fastcall edordercodeChange(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall DBGrid1TitleClick(TColumn *Column);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmOrdertoFahuo(TComponent* Owner,TADOConnection *cn,int stgid,int userid,int gid);
	int fstgid,fuserid;
	int ClientID,groupid,hgroupid;
	void ClientView();
	void IntoTmporder();
	AnsiString sqlwhere;
	void AddTmporder(int id);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOrdertoFahuo *frmOrdertoFahuo;
//---------------------------------------------------------------------------
#endif
