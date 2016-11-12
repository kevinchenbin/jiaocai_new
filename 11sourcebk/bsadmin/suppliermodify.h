//---------------------------------------------------------------------------

#ifndef suppliermodifyH
#define suppliermodifyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzLabel.hpp"
#include <Buttons.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DB.hpp>
#include <ADODB.hpp>
//---------------------------------------------------------------------------
class Tfrmsuppliermodify : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TPanel *Panel1;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnChangeOptions;
	TGroupBox *GroupBox1;
	TRzComboBox *cbQueryType;
	TEdit *edtQuery;
	TGroupBox *GroupBox2;
	TRzLabel *lblSupplier;
	TComboBox *cbsupplier;
	TSpeedButton *sbnewcustomer;
	TDBGrid *dgdetail;
	TDataSource *ds;
	TADOQuery *aq;
	TADOConnection *con;
	TADOQuery *query;
	TCheckBox *cbheader;
	TEdit *edntheader;
	TCheckBox *cbdetail;
	TRzToolButton *BtnVerticalTile;
	void __fastcall cbQueryTypeClick(TObject *Sender);
	void __fastcall edtQueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall edntheaderKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall cbdetailClick(TObject *Sender);
	void __fastcall cbheaderClick(TObject *Sender);
	void __fastcall BtnVerticalTileClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmsuppliermodify(TComponent* Owner,TADOConnection *cn);
	//void Init(LandInfo* li);
	void __fastcall Query(String condition);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsuppliermodify *frmsuppliermodify;
//---------------------------------------------------------------------------
#endif
