//---------------------------------------------------------------------------

#ifndef MemberCardH
#define MemberCardH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <ADODB.hpp>
#include "RzCmboBx.hpp"
//---------------------------------------------------------------------------
class TfrmMemberCard : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TImageList *ImageListMemcard;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TLabel *membername;
	TEdit *edtname;
	TLabel *membercardid;
	TEdit *edtcardID;
	TLabel *membersex;
	TLabel *memberbirthday;
	TLabel *membertype;
	TLabel *membertelephone;
	TEdit *edttelephone;
	TLabel *membermobile;
	TEdit *edtmobile;
	TLabel *memberaddress;
	TEdit *edtaddress;
	TLabel *memberpostalcode;
	TEdit *edtpostalcode;
	TADOQuery *quMemberType;
	TADOCommand *ADOCommand1;
	TRzComboBox *cbtype;
	TRzComboBox *cbsex;
	TLabel *Label1;
	TEdit *edtdiscount;
	TDateTimePicker *tdtbirthday;
	TADOQuery *quMemberCard;
	TADOQuery *quMemberInfo;
	TLabel *Label2;
	TEdit *edCardCast;
	TLabel *Label3;
	TEdit *edpassword;
	TRadioGroup *rg;
	TLabel *Label4;
	TEdit *edbircard;


	void __fastcall edtnameChange(TObject *Sender);
	void __fastcall edtcardIDChange(TObject *Sender);
	void __fastcall edtsexChange(TObject *Sender);
	void __fastcall edttelephoneChange(TObject *Sender);
	void __fastcall edtmobileChange(TObject *Sender);
	void __fastcall edtaddressChange(TObject *Sender);
	void __fastcall edtpostalcodeChange(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall edtdiscountChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tdtbirthdayClick(TObject *Sender);
	void __fastcall cbtypeSelect(TObject *Sender);
	void __fastcall edtnameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtcardIDKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbsexKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall tdtbirthdayKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbtypeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edttelephoneKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtmobileKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtpostalcodeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edCardCastKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edpasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edbircardKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);










private:	// User declarations
	AnsiString name,sex,type,birthday,cardID,telephone,mobile,address,postalcode,discount;
	int m_modle,memtype,memsex;
	String *ASMemInfo;


public:		// User declarations
	__fastcall TfrmMemberCard(TComponent* Owner,int modle,String *ASMemberInfo,TADOConnection *cn);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMemberCard *frmMemberCard;
//---------------------------------------------------------------------------
#endif
