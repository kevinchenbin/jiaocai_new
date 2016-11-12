//---------------------------------------------------------------------------

#ifndef UnitreceiverSelectH
#define UnitreceiverSelectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzTreeVw.hpp"
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ImgList.hpp>
class UserNode
{
  public:
  int ID;
  int stgid;
  int PrentID;
  AnsiString Name;
};
//---------------------------------------------------------------------------
class Tfrmuserselect : public TForm
{
__published:	// IDE-managed Components
	TRzTreeView *tvpurview;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TADOQuery *ADOQuery1;
	TImageList *imagestg;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tvpurviewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
	bool  GetNodeChecked(TTreeNode *ANode);
	void  SetNodeChecked(TTreeNode *ANode,bool IsSetToChecked);
	void  SetChildChecked(TTreeNode *ANode,bool yn);
	TADOConnection *fcn;
		 TTreeNode *ClickNode; // 保存点中的节点
	TTreeNode * GroupNode;
	bool NodeChecked; // 保存点中的节点checked
public:		// User declarations
	__fastcall Tfrmuserselect(TComponent* Owner);
	void init(TADOConnection *cn,TStringList *temUser);
	void ReadData();
	TStringList *tempUserA;

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmuserselect *frmuserselect;
//---------------------------------------------------------------------------
#endif
