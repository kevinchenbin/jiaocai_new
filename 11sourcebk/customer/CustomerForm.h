//---------------------------------------------------------------------------

#ifndef CustomerFormH
#define CustomerFormH
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
#include <Classes.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>
#include <MDIChild.h>
#include <ImgList.hpp>

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
typedef enum
{
	CT_Supplier = 1,
	CT_Vendor=2
}CustomerType;

class TfrmCustomer : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzGroupBox *RzGroupBox1;
	TRzDBEdit *dbedtName;
	TRzLabel *RzLabel2;
	TRzLabel *RzLabel3;
	TRzDBEdit *dbeditContact;
	TRzLabel *RzLabel4;
	TRzDBEdit *dbedit;
	TRzLabel *RzLabel5;
	TRzDBEdit *edtcode;
	TRzDBGrid *dbGridCust;
	TDataSource *ds1;
	TRzLabel *RzLabel9;
	TRzDBEdit *edtfax;
	TRzLabel *RzLabel11;
	TRzDBEdit *edtphone;
	TRzLabel *RzLabel8;
	TImageList *ImageListCustomer;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnFinish;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnExit;
	TComboBox *cbsaler;
	TLabel *Label1;
	TComboBox *cblocal;
	TADOQuery *aqsupplier;
	TADOQuery *aqinit;
	void __fastcall rtbaddClick(TObject *Sender);
	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall rtbdelClick(TObject *Sender);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);

private:	// User declarations
	CustomerType m_type;
	TStringList * salesman;
	TStringList * local;

public:		// User declarations
	__fastcall TfrmCustomer(TComponent* Owner);
	void __fastcall SetCustomerType(int type);
	void Query(String condition, CustomerType type);
	void ShowData();
	void Initsalesman();
	void InitLocalinfo();
	void UpdateSupplier();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCustomer *frmCustomer;
//---------------------------------------------------------------------------
#endif
