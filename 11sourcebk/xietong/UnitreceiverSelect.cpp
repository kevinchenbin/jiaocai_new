//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitreceiverSelect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzTreeVw"
#pragma resource "*.dfm"
Tfrmuserselect *frmuserselect;
//---------------------------------------------------------------------------
__fastcall Tfrmuserselect::Tfrmuserselect(TComponent* Owner)
	: TForm(Owner)
{

}
bool  Tfrmuserselect::GetNodeChecked(TTreeNode *ANode)
{
   	  TVITEM tvItem;
	  tvItem.mask = TVIF_HANDLE | TVIF_STATE;
	  tvItem.hItem = ANode->ItemId;
	  tvItem.stateMask = TVIS_STATEIMAGEMASK;
	  TreeView_GetItem(ANode->TreeView->Handle, &tvItem);
	  return ((BOOL)(tvItem.state >> 12) -1);
}
void  Tfrmuserselect::SetNodeChecked(TTreeNode *ANode,bool IsSetToChecked)
{
	  TVITEM tvItem;
      tvItem.mask = TVIF_HANDLE | TVIF_STATE;
      tvItem.hItem = ANode->ItemId;
      tvItem.stateMask = TVIS_STATEIMAGEMASK;
      tvItem.state = INDEXTOSTATEIMAGEMASK(IsSetToChecked?2:1);
	  TreeView_SetItem(ANode->TreeView->Handle, &tvItem);
}
void  Tfrmuserselect::SetChildChecked(TTreeNode *ANode,bool yn)
{
	int count=ANode->Count;
	SetNodeChecked(ANode,yn);
	if (count!=0)
	for (int i=0;i<count;i++)    // 递归
	 SetChildChecked(ANode->Item[i],yn);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmuserselect::FormCreate(TObject *Sender)
{
	SetWindowLong(tvpurview->Handle,GWL_STYLE,
	GetWindowLong(tvpurview->Handle,GWL_STYLE) | TVS_CHECKBOXES);
}
void Tfrmuserselect::init(TADOConnection *cn,TStringList *temUser)
{
   fcn = cn;
  tempUserA = temUser;

}
void Tfrmuserselect::ReadData()
{
  AnsiString sql,sql1;
  sql = "select ID,Name from SYS_StorageInfo";
  sql1 = "select ID,Name,stgid from sys_user";
  TTreeNode *Node;
  UserNode *ndata ;
  UserNode *ndatab ;
  TStringList *tmpstr=NULL;
  tmpstr = new TStringList();
  TADOQuery *aq = new TADOQuery(NULL);
  aq->Connection = fcn;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql1);
  aq->Open();
  while(!aq->Eof)
  {
	ndata = new UserNode();
	ndata->ID = aq->FieldByName("ID")->AsInteger ;
	ndata->stgid = aq->FieldByName("stgid")->AsInteger ;
	ndata->PrentID = 0;
	ndata->Name = aq->FieldByName("name")->AsAnsiString ;
	tmpstr->AddObject(aq->FieldByName("stgid")->AsAnsiString ,(TObject *)ndata) ;

	aq->Next();
  }
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();

  while(!aq->Eof)
  {
	ndata = new UserNode();
	ndata->ID = aq->FieldByName("ID")->AsInteger ;
	ndata->stgid = aq->FieldByName("ID")->AsInteger ;
	ndata->PrentID = -1;
   Node = 	tvpurview->Items->AddObject(NULL,aq->FieldByName("Name")->AsAnsiString,ndata);
   //	Node = tvpurview->Items->Add(NULL,aq->FieldByName("Name")->AsAnsiString);

	 for (int i =0; i < tmpstr->Count ; i++) {
	   ndatab = (struct UserNode*)tmpstr->Objects[i];
	   if (aq->FieldByName("ID")->AsAnsiString == ndatab->stgid ) {
		  tvpurview->Items->AddChildObject(Node,ndatab->Name,ndatab);
	 }
	 }
	 aq->Next();
  }


}
//---------------------------------------------------------------------------

void __fastcall Tfrmuserselect::FormShow(TObject *Sender)
{
   ReadData();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmuserselect::tvpurviewMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (ClickNode!=NULL)
	if (GetNodeChecked(ClickNode)!=NodeChecked)
	{ // 把它的子孙都置成一样
	    NodeChecked=!NodeChecked; // 更新它
		SetChildChecked(ClickNode,NodeChecked);
    }
}
//---------------------------------------------------------------------------


void __fastcall Tfrmuserselect::SpeedButton1Click(TObject *Sender)
{
//保存
	   TTreeNode *aNode;
	   UserNode *ndata ;
	  for(aNode=tvpurview->Items->GetFirstNode() ; aNode!=NULL ;)
		{
		   ndata = (struct UserNode*)(aNode->Data);
		   if ((ndata->PrentID != -1) && (GetNodeChecked(aNode))) {
			   tempUserA->AddObject(ndata->Name ,(TObject*)ndata->ID);
		   }
		   aNode=aNode->GetNext();
		}
	   ModalResult = mrOk;
}
//---------------------------------------------------------------------------

