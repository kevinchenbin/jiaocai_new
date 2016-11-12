//---------------------------------------------------------------------------

#ifndef SelectMemberFormH
#define SelectMemberFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MemberForm.h"
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzDBCmbo.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <ComCtrls.hpp>
#include "RzDBDTP.hpp"
#include "RzDTP.hpp"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfrmSelectMember : public TfrmMember
{
__published:	// IDE-managed Components
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzDBEdit8KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmSelectMember(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSelectMember *frmSelectMember;
//---------------------------------------------------------------------------
#endif
