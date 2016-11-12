//---------------------------------------------------------------------------

#ifndef SelectCustomerFormH
#define SelectCustomerFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CustomerForm.h"
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzDBCmbo.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzLine.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TfrmSelectCustomer : public TfrmCustomer
{
__published:	// IDE-managed Components
	void __fastcall RzDBEdit10KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmSelectCustomer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSelectCustomer *frmSelectCustomer;
//---------------------------------------------------------------------------
#endif
