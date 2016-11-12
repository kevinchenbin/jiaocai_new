//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RecMoneyForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzLabel"
#pragma link "RzEdit"
#pragma resource "*.dfm"
TfrmRecMoney *frmRecMoney;
//---------------------------------------------------------------------------
__fastcall TfrmRecMoney::TfrmRecMoney(TComponent* Owner)
	: TfrmModalDialog(Owner)
	, m_checked(0)
	, m_receive(0)
	, m_discountedPrice(0)
{
}
//---------------------------------------------------------------------------
void TfrmRecMoney::SetChecked(float checked)
{
	m_checked = checked;
}
//---------------------------------------------------------------------------
void TfrmRecMoney::SetDiscountedPrice(float discountedPrice)
{
	m_discountedPrice = discountedPrice;
}

//---------------------------------------------------------------------------
void __fastcall TfrmRecMoney::FormShow(TObject *Sender)
{
	numedtChecked->Value = m_checked;
	numedtReceive->Value = m_receive;
	numedtUnchecked->Value = m_discountedPrice - m_checked - m_receive;
	numedtshoud->Value =  m_discountedPrice;
	numedtshoud->DisplayFormat = format;
	numedtChecked->DisplayFormat = format;
	numedtReceive->DisplayFormat = format;
	numedtUnchecked->DisplayFormat = format;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecMoney::numedtReceiveKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		btnOk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecMoney::numedtReceiveChange(TObject *Sender)
{
	//
	if (numedtReceive->Value > m_discountedPrice - m_checked)
	{
		numedtReceive->Value = m_discountedPrice - m_checked;
	}
    numedtUnchecked->Value = m_discountedPrice - m_checked - numedtReceive->Value;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecMoney::numedtReceiveExit(TObject *Sender)
{
	//
    m_receive = numedtReceive->Value;
}
//---------------------------------------------------------------------------

float TfrmRecMoney::GetReceived()
{
 	return m_receive;
}








