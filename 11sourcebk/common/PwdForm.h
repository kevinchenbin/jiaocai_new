//---------------------------------------------------------------------------

#ifndef PwdFormH
#define PwdFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ModalDialog.h"
#include "RzButton.hpp"
#include "RzLabel.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmPwd : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TRzLabel *lbl1;
	TRzEdit *edtPwd;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall edtPwdKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtPwdChange(TObject *Sender);
private:	// User declarations
	String m_password;
public:		// User declarations
	__fastcall TfrmPwd(TComponent* Owner);
	String GetPassword();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPwd *frmPwd;
//---------------------------------------------------------------------------
#endif
