//---------------------------------------------------------------------------

#ifndef RecMoneyFormH
#define RecMoneyFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ModalDialog.h"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzLabel.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TfrmRecMoney : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TRzGroupBox *grpbx1;
	TRzLabel *lbl1;
	TRzLabel *lbl2;
	TRzLabel *lbl3;
	TRzNumericEdit *numedtChecked;
	TRzNumericEdit *numedtReceive;
	TRzNumericEdit *numedtUnchecked;
	TRzLabel *RzLabel1;
	TRzNumericEdit *numedtshoud;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall numedtReceiveKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall numedtReceiveChange(TObject *Sender);
	void __fastcall numedtReceiveExit(TObject *Sender);
private:	// User declarations
	float m_checked;//已结
	float m_receive;//收款
	float m_discountedPrice;//总额
public:		// User declarations
	__fastcall TfrmRecMoney(TComponent* Owner);
	void SetChecked(float checked);
	void SetDiscountedPrice(float discountedPrice);
	float GetReceived();
	AnsiString format;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRecMoney *frmRecMoney;
//---------------------------------------------------------------------------
#endif
