//---------------------------------------------------------------------------

#ifndef UnitMyWorkH
#define UnitMyWorkH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
   struct NodeWorkData
{
  int ID;
  int PrentID;
  AnsiString Name;
  int state;

};
class TfrmMyWork : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TTreeView *tvMyWork;
	TADOQuery *aquery;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tvMyWorkMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall tvMyWorkMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);

private:	// User declarations
   TADOConnection *fn;
   int UID;
   bool GetNodeChecked(TTreeNode *ANode);
   void SetNodeChecked(TTreeNode *ANode,bool IsSetToChecked);
   void SetChildChecked(TTreeNode *ANode,bool yn);
	TTreeNode *ClickNode; // 保存点中的节点
	TTreeNode * GroupNode;
	bool NodeChecked; // 保存点中的节点checked
   void	ShowPurViewByGroup(int ID);
   void SavePurview();
   void ExcSQL(AnsiString sql);
public:		// User declarations
	__fastcall TfrmMyWork(TComponent* Owner,TADOConnection *cn,int UserID);

	void GetData();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMyWork *frmMyWork;
//---------------------------------------------------------------------------
#endif
