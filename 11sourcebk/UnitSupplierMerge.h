//---------------------------------------------------------------------------

#ifndef UnitSupplierMergeH
#define UnitSupplierMergeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmSupplierMerge : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnOK;
	TRzToolButton *BtnCancel;
	TRzToolButton *Btn;
	TLabel *Label1;
	TEdit *edbaoliu;
	TLabel *Label2;
	TEdit *edzuofei;
	TEdit *edquery;
	TRzButton *RzButton1;
	TLabel *Label3;
	TADOQuery *query;
	TDBGrid *DBGrid1;
	TADOConnection *fcon;
	TDataSource *ds;
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall BtnCancelClick(TObject *Sender);
	void __fastcall BtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmSupplierMerge(TComponent* Owner,TADOConnection *con);
	int ysupplierid,msupplierid;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSupplierMerge *frmSupplierMerge;
//---------------------------------------------------------------------------
#endif
