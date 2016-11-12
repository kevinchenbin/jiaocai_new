//---------------------------------------------------------------------------

#ifndef MembertypeadddotH
#define MembertypeadddotH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class Tfrmmemberadddot : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TADOConnection *fcon;
	TGroupBox *gb1;
	TDBGrid *dg1;
	TGroupBox *gb2;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *edname1;
	TEdit *eddot1;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *edname;
	TEdit *eddot;
	TLabel *Label7;
	TEdit *edminedit;
	TEdit *edmaxdiscount;
	TLabel *Label8;
	TDataSource *ds1;
	TADOQuery *aq1;
	TRadioGroup *rg;
	TCheckBox *chactive;
	TLabel *Label9;
	TComboBox *cbmembertype;
	TDBGrid *dg2;
	TDataSource *ds2;
	TADOQuery *aq2;
	void __fastcall eddot1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edmineditKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edmaxdiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rgClick(TObject *Sender);
	void __fastcall chactiveClick(TObject *Sender);
	void __fastcall cbmembertypeClick(TObject *Sender);
	void __fastcall dg2CellClick(TColumn *Column);
	void __fastcall dg1CellClick(TColumn *Column);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmmemberadddot(TComponent* Owner,TADOConnection *con,int stgid);
	TTreeNode * Root;
	int fstgid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmmemberadddot *frmmemberadddot;
//---------------------------------------------------------------------------
#endif
