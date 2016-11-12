//---------------------------------------------------------------------------

#ifndef MastersetH
#define MastersetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmMasterset : public TForm
{
__published:	// IDE-managed Components
	TPanel *pan1;
	TDBGridEh *DBGridEh1;
	TRzButton *btok;
	TRzButton *btconcel;
	TADOConnection *cn;
	TDataSource *ds;
	TADOQuery *aq;
	TADOQuery *query;
	void __fastcall btokClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall aqAfterPost(TDataSet *DataSet);
	void __fastcall btconcelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmMasterset(TComponent* Owner,TADOConnection *con);
	int stgid;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMasterset *frmMasterset;
//---------------------------------------------------------------------------
#endif
