//---------------------------------------------------------------------------

#ifndef suppmanageH
#define suppmanageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include "RzCmboBx.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TSuppMana : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnFinish;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnView;
	TADOQuery *aqinit;
	TADOQuery *aqrecord;
	TDataSource *ds;
	TRzToolButton *BtnExport;
	TADOQuery *query;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnAlignBottom;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TRzLabel *RzLabel1;
	TRzComboBox *CBlocal;
	TRzComboBox *CBsale;
	TRzEdit *etcontax;
	TRzComboBox *etname;
	TRzDBGrid *DBGridrecord;
	TEdit *edquery;
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnFinishClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall etcontaxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CBlocalKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CBsaleKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall etnameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edqueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
	int type;
	TADOConnection *cn;

public:		// User declarations
	__fastcall TSuppMana(TComponent* Owner,int Type,TADOConnection *cnn);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	void Initsalesman();
	void InitLocalinfo();
	void Initname();
	int StgID;
        bool add,modify,del;
        void lock();

};
//---------------------------------------------------------------------------
extern PACKAGE TSuppMana *SuppMana;
//---------------------------------------------------------------------------
#endif