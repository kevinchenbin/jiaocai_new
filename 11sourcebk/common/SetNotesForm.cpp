//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SetNotesForm.h"
#include   <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzRadChk"
#pragma link "RzEdit"
#pragma resource "*.dfm"
TfrmSetNotes *frmSetNotes;
//---------------------------------------------------------------------------
__fastcall TfrmSetNotes::TfrmSetNotes(TComponent* Owner)
	: TfrmModalDialog(Owner)
	, m_amount(0)
	, m_discount(0)
	, m_bsmode(BSUnknown)
{
	numedtDiscount->Text = "100.00";
	edpixiaodiscount->Text = "100.00";
	edlsdiscount->Text = "100.00";
	text =  numedtDiscount->Text ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetNotes::numedtAmountChange(TObject *Sender)
{
	if (m_bsmode == BSNote)
	{
		m_amount = abs(numedtAmount->IntValue);
	}
	else if (m_bsmode == BSNoteSendback)
	{
    	m_amount = -abs(numedtAmount->IntValue);
	}
	else
	{

    }
}
//---------------------------------------------------------------------------
void TfrmSetNotes::ChangeBsmode(BSMode mode)
{
	m_bsmode = mode;
	if (salediscount == 1) {
		chpixiaodiscount->Visible = true;
		edpixiaodiscount->Visible = true;
		chlsdiscount->Visible = true;
		edlsdiscount->Visible = true;
	}
	if (salediscount == 2) {
		chckbxDiscount->Visible = false;
		numedtDiscount->Visible = false;
	}
}

bool TfrmSetNotes::GetAmount(int& amount)
{
	bool ret = false;
	if (chckbxAmount->Checked)
	{
		amount = m_amount;
		ret = true;
	}
	return ret;
}

bool TfrmSetNotes::GetDiscount(float& discount)
{
	bool ret = false;
	if (chckbxDiscount->Checked)
	{
		discount = m_discount;
		ret = true;
	}
	return ret;
}

bool TfrmSetNotes::GetpixiaoDiscount(float& discount)
{
	bool ret = false;
	if (chpixiaodiscount->Checked)
	{
		discount = m_pixiaodiscount;
		ret = true;
	}
	return ret;
}

bool TfrmSetNotes::GetlsDiscount(float& discount)
{
	bool ret = false;
	if (chlsdiscount->Checked)
	{
		discount = m_lsdiscount;
		ret = true;
	}
	return ret;
}

void __fastcall TfrmSetNotes::numedtDiscountChange(TObject *Sender)
{
	if (numedtDiscount->Value > 100) {
    	return;
	}
	m_discount = fabs(numedtDiscount->Value);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetNotes::chckbxAmountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '-') {
		Key = 0;
	}
	if (Key == '\r')
	{

		Key=0;
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetNotes::chckbxAmountClick(TObject *Sender)
{
   if (chckbxAmount->Checked) {
       numedtAmount->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetNotes::chckbxDiscountClick(TObject *Sender)
{
   if (chckbxDiscount->Checked ) {
       numedtDiscount->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetNotes::edpixiaodiscountChange(TObject *Sender)
{
	m_pixiaodiscount = fabs(edpixiaodiscount->Value);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetNotes::numedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{

	if (numedtDiscount->Value > 100.00) {
		Key = 0;
		numedtDiscount->Text = text;
	}
	if (Key == '-') {
		Key = 0;
	}
	if (Key == '\r')
	{
		if (numedtDiscount->Value != 100.00) {
			chckbxDiscount->Checked = true;
		}
		else
		{
			chckbxDiscount->Checked = false;
		}
		if (edpixiaodiscount->Visible ) {
			edpixiaodiscount->SetFocus();
		}
		else
		{
			btnOk->SetFocus();
		}
	}
	text =  numedtDiscount->Text ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetNotes::edlsdiscountChange(TObject *Sender)
{
		m_lsdiscount = fabs(edlsdiscount->Value);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetNotes::numedtAmountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '-') {
		Key = 0;
	}
	if (Key == '\r') {
		if (numedtAmount->Value != 0) {
			chckbxAmount->Checked = true;
		}
		else
		{
			chckbxAmount->Checked = false;
		}
		if (numedtDiscount->Visible ) {
			numedtDiscount->SetFocus();
		}
		else
		{
			btnOk->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetNotes::edpixiaodiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (edpixiaodiscount->Value > 100.00) {
		Key = 0;
		edpixiaodiscount->Text = "100.00";
	}
	if (Key == '-') {
		Key = 0;
	}
	if (Key == '\r')
	{
		if (edpixiaodiscount->Value != 100.00) {
			chpixiaodiscount->Checked = true;
		}
		else
		{
			chpixiaodiscount->Checked = false;
		}
		if (edlsdiscount->Visible ) {
			edlsdiscount->SetFocus();
		}
		else
		{
			btnOk->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetNotes::edlsdiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (edlsdiscount->Value > 100.00) {
		Key = 0;
		edlsdiscount->Text = "100.00";
	}
	if (Key == '-') {
		Key = 0;
	}
	if (Key == '\r')
	{
		if (edlsdiscount->Value != 100.00) {
			chlsdiscount->Checked = true;
		}
		else
		{
			chlsdiscount->Checked = false;
		}
		btnOk->SetFocus();
	}
}
//---------------------------------------------------------------------------

