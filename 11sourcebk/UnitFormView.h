//---------------------------------------------------------------------------

#ifndef UnitFormViewH
#define UnitFormViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
struct Nodedatamenu
{
  int ID;
  int PrentID;
  AnsiString Name;
  bool state;
};
class Tfrmformview : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TPanel *Panel1;
	TImageList *ImageList1;
	TRzToolButton *BtnSave;
	TTreeView *tvpurview;
	TADOQuery *aq;
	TADOQuery *aquserlist;
	TDataSource *ds;
	TImageList *ImageList2;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tvpurviewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall tvpurviewMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tvgroupCustomDrawItem(TCustomTreeView *Sender, TTreeNode *Node,
          TCustomDrawState State, bool &DefaultDraw);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnExitClick(TObject *Sender);



private:	// User declarations
	bool  GetNodeChecked(TTreeNode *ANode);
	void  SetNodeChecked(TTreeNode *ANode,bool IsSetToChecked);
	void  SetChildChecked(TTreeNode *ANode,bool yn);
	TADOConnection *fcon;
	int fstgid;
public:		// User declarations
	__fastcall Tfrmformview(TComponent* Owner,TADOConnection *cn,int stgid);
	void ReadyData();
	TTreeNode *ClickNode; // 保存点中的节点
	TTreeNode * GroupNode;
	bool NodeChecked; // 保存点中的节点checked
	void SavePurview();
	void ExcSQL(AnsiString sql);
	void ShowUsers(int ID);
	int SearchMod;//1为查看权限2为查看用户
	void  Tfrmformview::FirstView();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmformview *frmformview;
//---------------------------------------------------------------------------
#endif
