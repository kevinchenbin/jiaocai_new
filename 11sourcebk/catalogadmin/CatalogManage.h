//---------------------------------------------------------------------------

#ifndef CatalogManageH
#define CatalogManageH
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
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzLine.hpp"
#include "RzRadChk.hpp"
#include "RzRadGrp.hpp"
#include "RzSpnEdt.hpp"
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TFormCatalogMan : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnClear;
	TRzToolButton *BtnCancel;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnViewDetails;
	TRzGroupBox *x;
	TLabel *Label1;
	TRzComboBox *cbQueryType;
	TRzEdit *edtQuery;
	TRzLine *line;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TRzCheckBox *cbinvailed;
	TRzGroupBox *RzGroupBox1;
	TRzRadioGroup *RzRadioGroup1;
	TRzCheckBox *chckbxInput;
	TRzEdit *edtBarcode;
	TRzEdit *edtname;
	TRzEdit *edtprice;
	TRzComboBox *rcbbooktype;
	TRzSpinEdit *edtpresscount;
	TRzButton *¼Ó;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TRzEdit *edtisbn;
	TRzEdit *edtauthor;
	TRzComboBox *rcbpress;
	TRzDateTimeEdit *rdpressdate;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TRzEdit *edtuserdefcode;
	TRzDBGrid *RzDBGrid1;
	TADOQuery *queryCatlog;
	TDataSource *dsCatlog;
	TADOQuery *qryPressQuery;
	TADOQuery *qryCatalogType;
private:	// User declarations
public:		// User declarations
	__fastcall TFormCatalogMan(TComponent* Owner);
	void Query(String condition);
	void Init(TApplication* app, TADOConnection* con);
	BOOL manybook;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCatalogMan *FormCatalogMan;
//---------------------------------------------------------------------------
#endif
