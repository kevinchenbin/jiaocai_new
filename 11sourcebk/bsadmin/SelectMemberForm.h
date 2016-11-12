//---------------------------------------------------------------------------

#ifndef SelectMemberFormH
#define SelectMemberFormH
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
#include "RzLine.hpp"
#include "RzDBEdit.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmSelectMember : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TADODataSet *dsetMember;
	TDataSource *dsrc1;
	TRzLabel *lbl1;
	TRzLine *RzLine1;
	TRzLabel *lbl2;
	TRzLabel *lbl4;
	TRzLabel *lbl5;
	TRzLabel *lbl6;
	TRzEdit *edtMember;
	TRzDBEdit *dbedtCardSN;
	TRzDBEdit *dbedtName;
	TRzDBNumericEdit *dbnbedtDiscount;
	TRzDBNumericEdit *dbnbedtBalance;
	TLabel *Label1;
	TEdit *edpassword;
	TADOQuery *aq;
	void __fastcall edtMemberKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btnCancelClick(TObject *Sender);
	void __fastcall dbedtCardSNKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpasswordKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
	int m_memberID;
	int enterflag;
public:		// User declarations
	__fastcall TfrmSelectMember(TComponent* Owner);
	void Init(LandInfo* li);
	int GetMemberID();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSelectMember *frmSelectMember;
//---------------------------------------------------------------------------
#endif
