//---------------------------------------------------------------------------

#ifndef QryNoteCodeFormH
#define QryNoteCodeFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include "RzCmboBx.hpp"
#include "RzSpnEdt.hpp"
#include "RzButton.hpp"
#include "ModalDialog.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmQryNoteCode : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TRzLabel *lbl1;
	TRzLabel *lbl2;
	TRzLabel *lbl3;
	TRzDateTimeEdit *dtedtDate;
	TRzComboBox *cbb1;
	TRzSpinEdit *spedtID;
	TRzEdit *edtCode;
	void __fastcall dtedtDateChange(TObject *Sender);
	void __fastcall spedtIDChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	String m_stgNtCode;
public:		// User declarations
	__fastcall TfrmQryNoteCode(TComponent* Owner,int modle);
	String GetNoteCode();
	void SetstgID(int stgid);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmQryNoteCode *frmQryNoteCode;
//---------------------------------------------------------------------------
#endif
