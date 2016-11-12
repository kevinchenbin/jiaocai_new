//---------------------------------------------------------------------------

#ifndef MixedRecMoneyFormH
#define MixedRecMoneyFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ModalDialog.h"
#include "RzButton.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "RzDBEdit.hpp"
#include "RzLine.hpp"
//---------------------------------------------------------------------------
class TfrmMixedRecMoney : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TRzNumericEdit *numedtMustRecMoney;
	TRzLabel *RzLabel1;
	TLabel *Label1;
	TRzLabel *RzLabel2;
	TRzLabel *RzLabel3;
	TRzLabel *lbl1;
	TRzNumericEdit *numedtCard;
	TRzNumericEdit *numedtCash;
	TRzNumericEdit *numedtRemain;
	TRzLine *RzLine1;
	TRzLabel *RzLabel4;
	TRzNumericEdit *numedtyouhui;
	TRzLabel *RzLabel5;
	TRzNumericEdit *numedtposcard;
	void __fastcall numedtCardKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall numedtCashKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall numedtCardExit(TObject *Sender);
	void __fastcall btnOkClick(TObject *Sender);
	void __fastcall numedtyouhuiKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall numedtposcardKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall numedtyouhuiExit(TObject *Sender);
	void __fastcall numedtposcardExit(TObject *Sender);
	void __fastcall numedtCashClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	float m_mustRec;//应收
	float m_cardRec;//卡
	float m_cashRec;//现金
	float m_cardRemain;//卡内余额
	float m_poscard;  //银行卡
	float m_youhuiquan;  //优惠券
public:		// User declarations
	__fastcall TfrmMixedRecMoney(TComponent* Owner);
	void SetMustRec(float mustrec);
	void SetRecCard(float card);
	void SetRecCash(float cash);
	void SetCardRemain(float remain);
	void GetRecMoney(float& card,float& cash,float& poscard,float& youhuiquan);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMixedRecMoney *frmMixedRecMoney;
//---------------------------------------------------------------------------
#endif
