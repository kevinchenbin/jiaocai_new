//---------------------------------------------------------------------------

#ifndef PressAdminFormH
#define PressAdminFormH
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzDBCmbo.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
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
#include "RzShellDialogs.hpp"
#include "RzLine.hpp"
#include "MDIChild.h"
#include <ImgList.hpp>
//---------------------------------------------------------------------------

class TfrmPressAdmin : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TDataSource *ds1;
	TADODataSet *dsetPress;
	TRzSaveDialog *svdlgExport;
	TRzToolButton *btnExit1;
	TRzToolButton *btnExit2;
	TRzToolButton *btnExit3;
	TRzToolButton *btnExit4;
	TRzToolButton *btnExit5;
	TButton *btn1;
	TRzToolButton *RzToolButton1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TPanel *Panel1;
	TRzDBGrid *dbgrdPress;
	TGroupBox *GroupBox1;
	TRzLabel *RzLabel2;
	TRzLabel *RzLabel3;
	TRzLabel *RzLabel4;
	TRzLabel *RzLabel5;
	TRzLabel *RzLabel6;
	TRzLabel *RzLabel7;
	TRzLabel *RzLabel8;
	TRzLabel *RzLabel9;
	TRzLabel *RzLabel10;
	TRzLabel *RzLabel11;
	TRzLabel *RzLabel12;
	TRzDBEdit *RzDBEdit2;
	TRzDBEdit *RzDBEdit3;
	TRzDBEdit *RzDBEdit4;
	TRzDBEdit *RzDBEdit5;
	TRzDBEdit *RzDBEdit6;
	TRzDBEdit *RzDBEdit7;
	TRzDBEdit *RzDBEdit8;
	TRzDBEdit *RzDBEdit9;
	TRzDBEdit *RzDBEdit10;
	TRzDBEdit *RzDBEdit11;
	TRzDBEdit *RzDBEdit12;
	TGroupBox *GroupBox2;
	TRzLabel *RzLabel1;
	TRzEdit *edtQuery;
	TRzComboBox *cbQueryType;
	TRzToolButton *BtnChangeOptions;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall RzToolButton4Click(TObject *Sender);
	void __fastcall RzToolButton2Click(TObject *Sender);
	void __fastcall btnAddClick(TObject *Sender);
	void __fastcall btnDeleteClick(TObject *Sender);
	void __fastcall frmExportClick(TObject *Sender);
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall edtQueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall RzDBEdit2KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit3KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit4KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit5KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit6KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit7KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit8KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit9KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit10KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit11KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit12KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btnExit1Click(TObject *Sender);
	void __fastcall btnExit2Click(TObject *Sender);
	void __fastcall btnExit3Click(TObject *Sender);
	void __fastcall btnExit4Click(TObject *Sender);
	void __fastcall btnExit5Click(TObject *Sender);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall dbgrdPressCellClick(TColumn *Column);




private:	// User declarations
void OnHotKeyPress(DWORD vkCode);

public:		// User declarations
	__fastcall TfrmPressAdmin(TComponent* Owner);
	 void Init(TApplication* app, TADOConnection* con);
	// void Query(int i);
	 void Query(String condition);
	 //void DBGrid2Excel(rzdbgrdPress, strXlsFile)
	 void DBGrid2Excel(TDBGrid *dbg, String strXlsFile);
	 void grid2excel();
	 void DBGridToExcel(TDBGrid *DBGrid,AnsiString  strPath);
	 bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPressAdmin *frmPressAdmin;
//---------------------------------------------------------------------------
#endif
