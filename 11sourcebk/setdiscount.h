//---------------------------------------------------------------------------

#ifndef setdiscountH
#define setdiscountH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmsetdiscount : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TPanel *Panel1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnChangeOptions;
	TRzToolButton *BtnDeleteRecord;
	TRzToolButton *BtnExit;
	TDBGrid *dg;
	TGroupBox *GroupBox1;
	TEdit *edisbn;
	TComboBox *cbtype;
	TEdit *edname;
	TEdit *edpressquery;
	TComboBox *cbpress;
	TEdit *edsupplierquery;
	TComboBox *cbsupplier;
	TADOConnection *fcon;
	TDataSource *ds;
	TADOQuery *query;
	TGroupBox *GroupBox2;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *edpxdiscount;
	TLabel *Label10;
	TEdit *edpxprice;
	TEdit *edlsdiscount;
	TLabel *Label11;
	TEdit *edlsprice;
	TCheckBox *chisbn;
	TCheckBox *chtype;
	TCheckBox *chname;
	TCheckBox *chpress;
	TCheckBox *chsupplier;
	TRzToolButton *BtnSave;
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnDeleteRecordClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edpressqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edsupplierqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edisbnChange(TObject *Sender);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall cbtypeChange(TObject *Sender);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall cbsupplierChange(TObject *Sender);
	void __fastcall edpxdiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpxpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edlsdiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edlspriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall dgCellClick(TColumn *Column);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmsetdiscount(TComponent* Owner,TADOConnection *con,int stgid);
	int fstgid;
	void BatchSetNotes(float pxdiscount,float lsdiscount,bool yjpx,bool yjls);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsetdiscount *frmsetdiscount;
//---------------------------------------------------------------------------
#endif
