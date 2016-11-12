//---------------------------------------------------------------------------

#ifndef UnithuancardH
#define UnithuancardH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzCmboBx.hpp"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrmhuancard : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *edcard;
	TLabel *Label2;
	TEdit *edname;
	TLabel *Label3;
	TEdit *edtype;
	TLabel *Label4;
	TEdit *edsex;
	TLabel *Label5;
	TEdit *edyue;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnSendtoBack;
	TADOConnection *fcon;
	TLabel *Label6;
	TEdit *edconsumption;
	TLabel *Label7;
	TEdit *edjifen;
	TLabel *Label8;
	TEdit *edpassword;
	TGroupBox *ÐÂ¿¨ÐÅÏ¢;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TLabel *membername;
	TLabel *membercardid;
	TLabel *membersex;
	TLabel *memberbirthday;
	TLabel *membertype;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *edtname;
	TEdit *edtcardID;
	TRzComboBox *cbtype;
	TRzComboBox *cbsex;
	TEdit *edtdiscount;
	TDateTimePicker *tdtbirthday;
	TEdit *edCardCast;
	TEdit *edtpwd;
	TRadioGroup *rg;
	TTabSheet *TabSheet2;
	TLabel *membertelephone;
	TLabel *membermobile;
	TLabel *memberaddress;
	TLabel *memberpostalcode;
	TEdit *edttelephone;
	TEdit *edtmobile;
	TEdit *edtaddress;
	TEdit *edtpostalcode;
	TLabel *Label12;
	TEdit *eddiscount;
	TLabel *Label13;
	TEdit *edbircard;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnSendtoBackClick(TObject *Sender);
	void __fastcall edtcardIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtpwdKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpasswordKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmhuancard(TComponent* Owner,TADOConnection *con,int cardid);
	int ycardid,newcardid,password;
	AnsiString Pwd;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmhuancard *frmhuancard;
//---------------------------------------------------------------------------
#endif
