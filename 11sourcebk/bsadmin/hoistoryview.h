//---------------------------------------------------------------------------

#ifndef hoistoryviewH
#define hoistoryviewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class Tfrmhistoryview : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TADOQuery *aq;
	TDataSource *ds;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExit;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmhistoryview(TComponent* Owner,TADOConnection *con,int bkid);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmhistoryview *frmhistoryview;
//---------------------------------------------------------------------------
#endif
