//---------------------------------------------------------------------------

#ifndef UnitClientyouxianjiH
#define UnitClientyouxianjiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmClientyouxianji : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzButton *RzButton1;
	TADOQuery *aq1;
	TDataSource *ds1;
	TDataSource *ds2;
	TADOQuery *aq2;
	TADOConnection *con;
	TDBGrid *dbg1;
	TDBGrid *dbg2;
	TRzButton *RzButton2;
	TRzButton *RzButton3;
	TLabel *Label1;
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton3Click(TObject *Sender);



private:	// User declarations
public:		// User declarations
	__fastcall TfrmClientyouxianji(TComponent* Owner,TADOConnection *cn,int stgid);
	int fstgid,type;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmClientyouxianji *frmClientyouxianji;
//---------------------------------------------------------------------------
#endif
