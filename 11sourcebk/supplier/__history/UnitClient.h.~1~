//---------------------------------------------------------------------------

#ifndef UnitClientH
#define UnitClientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include "RzCmboBx.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>

//---------------------------------------------------------------------------
struct NodeClientdata
{
  int ID;
  int PrentID;
  AnsiString Name;
  AnsiString contact;
  AnsiString address,telephone,code,fax,date,saleman,local;
};
class Tfrmclient : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnFinish;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnExit;
	TADOQuery *aq;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TTreeView *tvclient;
	TImageList *ImageList2;
	TListView *lvclient;
	TDBGrid *DBGrid1;
	TLabel *Label13;
	TLabel *Label1;
	TLabel *Label2;
	TDataSource *dsbase;
	TADOQuery *qrybase;
	TLabel *Label3;
	TEdit *eddefaultname;
	TRzToolButton *BtnAlign;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnImport;
	TADOQuery *query;
	TMenuItem *N6;
	TMenuItem *N7;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tvclientMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall BtnFinishClick(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall BtnAlignClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
private:	// User declarations
	void ReadyData();
	TTreeNode *ClickNode; // 保存点中的节点
	TTreeNode *childNode;
	TADOConnection *fcon;
	void AddClient(TTreeNode  *aNode);
public:		// User declarations
	__fastcall Tfrmclient(TComponent* Owner,TADOConnection *cn);
	bool querywhere;
	AnsiString sqlwhere;
	bool DbgridToExcel1();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmclient *frmclient;
//---------------------------------------------------------------------------
#endif
