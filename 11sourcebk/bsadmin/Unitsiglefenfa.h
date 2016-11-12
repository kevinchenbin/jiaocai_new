//---------------------------------------------------------------------------

#ifndef UnitsiglefenfaH
#define UnitsiglefenfaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class Tfrmsiglefenfa : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel2;
	TLabel *Label4;
	TEdit *edquery;
	TLabel * È∫≈;
	TEdit *edisbn;
	TLabel *Label1;
	TEdit *edname;
	TLabel *Label2;
	TEdit *edprice;
	TLabel *Label3;
	TEdit *edpress;
	TLabel *Label5;
	TEdit *edpresscount;
	TLabel *Label6;
	TEdit *edtype;
	TGroupBox *GroupBox1;
	TCheckBox *chstart;
	TDateTimePicker *dtpstart;
	TCheckBox *chend;
	TDateTimePicker *dtpend;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TADOConnection *fcon;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnView;
	TADOQuery *aq;
	TDataSource *ds;
	TDBGrid *DBGrid1;
	TLabel *Label7;
	TEdit *edauthor;
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall aqAfterPost(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmsiglefenfa(TComponent* Owner,TADOConnection *con,int stgid);
	int m_catalogSearchMode,bkcatalogid,fstgid;
	void ChangeCatalogSearchMode();
	void Query();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsiglefenfa *frmsiglefenfa;
//---------------------------------------------------------------------------
#endif
