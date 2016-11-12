//---------------------------------------------------------------------------

#ifndef SelectCustomerFormH
#define SelectCustomerFormH
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
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmSelectCustomer : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TRzLabel *RzLabel1;
	TRzEdit *edtName;
	TRzDBGrid *dbgrdCustomer;
	TADOQuery *qryCustomer;
	TDataSource *dsrcCustomer;
	void __fastcall edtNameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbgrdCustomerCellClick(TColumn *Column);
	void __fastcall dbgrdCustomerDblClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	int m_type;
	int m_id;
	void QryCustomer();
public:		// User declarations
	__fastcall TfrmSelectCustomer(TComponent* Owner);
	virtual void Init(LandInfo* li);
	void SetCustomerType(int type);
	int GetCustomerID();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSelectCustomer *frmSelectCustomer;
//---------------------------------------------------------------------------
#endif
