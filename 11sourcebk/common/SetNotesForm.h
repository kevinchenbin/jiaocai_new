//---------------------------------------------------------------------------

#ifndef SetNotesFormH
#define SetNotesFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ModalDialog.h"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzRadChk.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "pdutil.h"
//---------------------------------------------------------------------------
class TfrmSetNotes : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TRzGroupBox *grpbx1;
	TRzCheckBox *chckbxAmount;
	TRzCheckBox *chckbxDiscount;
	TRzNumericEdit *numedtDiscount;
	TRzNumericEdit *numedtAmount;
	TCheckBox *chpixiaodiscount;
	TRzNumericEdit *edpixiaodiscount;
	TCheckBox *chlsdiscount;
	TRzNumericEdit *edlsdiscount;
	void __fastcall numedtAmountChange(TObject *Sender);
	void __fastcall numedtDiscountChange(TObject *Sender);
	void __fastcall chckbxAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall chckbxAmountClick(TObject *Sender);
	void __fastcall chckbxDiscountClick(TObject *Sender);
	void __fastcall edpixiaodiscountChange(TObject *Sender);
	void __fastcall numedtDiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edlsdiscountChange(TObject *Sender);
	void __fastcall numedtAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpixiaodiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edlsdiscountKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
	int m_amount;
	float m_discount,m_pixiaodiscount,m_lsdiscount;
	BSMode m_bsmode;
public:		// User declarations
	__fastcall TfrmSetNotes(TComponent* Owner);
	void ChangeBsmode(BSMode mode);
	bool GetAmount(int& amount);
	bool GetDiscount(float& discount);
	bool GetpixiaoDiscount(float& discount);
	bool GetlsDiscount(float& discount);
	int salediscount;
	AnsiString text;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSetNotes *frmSetNotes;
//---------------------------------------------------------------------------
#endif
