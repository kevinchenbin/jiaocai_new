//---------------------------------------------------------------------------

#ifndef SupplierH
#define SupplierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
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
#include <ImgList.hpp>
#include <Mask.hpp>
#include "pdtypes.h"
#include <DBClient.hpp>
//---------------------------------------------------------------------------
class TfrmSupplierinfo : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *rtbmodify;
	TRzToolButton *rtbadd;
	TRzToolButton *rtbdel;
	TRzToolButton *rtbexit;
	TRzToolButton *rtbsave;
	TRzToolButton *rtblocal;
	TRzGroupBox *rzgb;
	TRzLabel *RzLabel2;
	TRzLabel *RzLabel3;
	TRzLabel *RzLabel4;
	TRzLabel *RzLabel5;
	TRzLabel *RzLabel6;
	TRzLabel *RzLabel11;
	TRzLabel *RzLabel8;
	TLabel *Label1;
	TComboBox *cbcustomertype;
	TRzDBGrid *dbGridCust;
	TDataSource *ds1;
	TImageList *ImageListCustomer;
	TADOQuery *aqsupplier;
	TComboBox *cblocal;
	TADOConnection *ADOConnection1;
	TClientDataSet *ClientDataSet1;
	TEdit *edtcompany;
	TEdit *edtaddress;
	TEdit *edtphone;
	TEdit *edtcontact;
	TEdit *edtcode;
	TEdit *edtfax;
	TLabel *sale;
	TComboBox *cbsale;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall rtbdelClick(TObject *Sender);
	void __fastcall rtbaddClick(TObject *Sender);
	void __fastcall rtbmodifyClick(TObject *Sender);
	void __fastcall rtbsaveClick(TObject *Sender);
	void __fastcall dbGridCustCellClick(TColumn *Column);
	void __fastcall rtbexitClick(TObject *Sender);
private:	// User declarations
	int Ftype;
	 TADOConnection *cn;
	 AnsiString Title;
public:		// User declarations
	__fastcall TfrmSupplierinfo(TComponent* Owner,int Type);
	int ExecSQL(String sqlstr);
	void Init(LandInfo* li);
	void ReadyData();
	void GetCDS(String SQLstr,TADOQuery *aqury);
	void EnableEdit(BOOL value);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSupplierinfo *frmSupplierinfo;
//---------------------------------------------------------------------------
#endif
