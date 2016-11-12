//---------------------------------------------------------------------------

#ifndef OrderdetailH
#define OrderdetailH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class TfrmOrderdetail : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *aq;
	TRzButton *RzButton1;
	TADOConnection *fcon;
	void __fastcall RzButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmOrderdetail(TComponent* Owner,TADOConnection *cn,int bkcatalogid,int stgid);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOrderdetail *frmOrderdetail;
//---------------------------------------------------------------------------
#endif
