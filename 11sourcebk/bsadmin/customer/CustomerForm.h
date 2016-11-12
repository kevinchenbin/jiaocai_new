//---------------------------------------------------------------------------

#ifndef CustomerFormH
#define CustomerFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include "RzDBEdit.hpp"
#include "RzLine.hpp"
#include "RzCmboBx.hpp"
#include "RzDBCmbo.hpp"
#include <DBCtrls.hpp>
#include "RzDBNav.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
typedef enum
{
	CT_Supplier = 1,
	CT_Vendor
}CustomerType;

class TfrmCustomer : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *rtbmodify;
	TRzToolButton *rtbadd;
	TRzToolButton *rtbdel;
	TRzToolButton *rtbexit;
	TRzGroupBox *RzGroupBox1;
	TRzDBEdit *dbedtName;
	TRzLabel *RzLabel2;
	TRzLabel *RzLabel3;
	TRzDBEdit *dbeditContact;
	TRzLabel *RzLabel4;
	TRzDBEdit *dbedit;
	TRzLabel *RzLabel5;
	TRzDBEdit *RzDBEdit4;
	TRzLabel *RzLabel6;
	TRzDBGrid *dbGridCust;
	TDataSource *ds1;
	TRzLabel *RzLabel9;
	TRzDBEdit *RzDBEdit5;
	TRzLabel *RzLabel11;
	TRzDBEdit *RzDBEdit1;
	TRzLabel *RzLabel8;
	TADODataSet *dsetCustomer;
	TImageList *ImageListCustomer;
	TRzToolButton *rtbsave;
	TRzToolButton *rtblocal;
	TComboBox *cbcustomertype;
	TLabel *Label1;
	TEdit *edtlocal;
	TComboBox *cbsaler;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall rtbaddClick(TObject *Sender);
	void __fastcall rtbexitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall rtbmodifyClick(TObject *Sender);
	void __fastcall rtbdelClick(TObject *Sender);
private:	// User declarations
	CustomerType m_type;
public:		// User declarations
	__fastcall TfrmCustomer(TComponent* Owner);
	void __fastcall SetCustomerType(int type);
	void Query(String condition, CustomerType type);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCustomer *frmCustomer;
//---------------------------------------------------------------------------
#endif
