//---------------------------------------------------------------------------

#ifndef unitsupplierH
#define unitsupplierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ImgList.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmsupplierunit : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnTile;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TLabel *Label1;
	TComboBox *cbsupplierbefore;
	TLabel *Label2;
	TComboBox *cbsupplierafter;
	TADOQuery *aq;
	TADOQuery *query;
	void __fastcall BtnTileClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmsupplierunit(TComponent* Owner,TADOConnection *cn);
	void BtnChange(TADOQuery *aq,int supplier);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsupplierunit *frmsupplierunit;
//---------------------------------------------------------------------------
#endif
