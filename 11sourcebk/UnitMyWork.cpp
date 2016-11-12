//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMyWork.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMyWork *frmMyWork;
//---------------------------------------------------------------------------
__fastcall TfrmMyWork::TfrmMyWork(TComponent* Owner,TADOConnection *cn,int UserID)
	: TForm(Owner)
{
  fn = cn;
  UID = UserID;
  aquery->Connection = fn ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMyWork::FormCreate(TObject *Sender)
{
	SetWindowLong(tvMyWork->Handle,GWL_STYLE,
			GetWindowLong(tvMyWork->Handle,GWL_STYLE) | TVS_CHECKBOXES);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMyWork::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree ;
}
void TfrmMyWork::GetData()
{
String sql;
  sql = "select * from sys_myworkaction ";


  struct NodeWorkData *ndata = NULL;

  TStringList *tmpstr=NULL;

  TTreeNode  *aNode=NULL;
  TTreeNode  *bNode=NULL;
  TTreeNode  *pNode=NULL;

  TADOQuery *query = new TADOQuery(Application);
  query->Connection = fn;
  query->Close();
  query->SQL->Clear();
  query->SQL->Add(sql);
  query->Open();

  try
  {
	tmpstr =new TStringList();
	tvMyWork->Items->BeginUpdate();//禁止刷新，提高速度
	//遍历记录集
	for(query->First(); !query->Eof; query->Next())
	{
	  ndata = new NodeWorkData();
	  ndata->Name = query->FieldByName("DisplayName")->AsAnsiString ;
	  ndata->PrentID = query->FieldByName("parent")->AsInteger ;
	  ndata->ID = query->FieldByName("ID")->AsInteger ;
	  //生成一个根节点加入TreeView
	  aNode=tvMyWork->Items->AddObject(NULL,ndata->Name ,ndata);
	  //记录id-TreeNode对应关系,便于下面查找
	  tmpstr->AddObject(AnsiString(ndata->ID),aNode);
	}

	query->Close();
	ndata=NULL;

   int idx;
	for(aNode=tvMyWork->Items->GetFirstNode(); aNode!=NULL ;)
	{
	  ndata = (NodeWorkData*)(aNode->Data);
	  if(-1==(idx=tmpstr->IndexOf(AnsiString(ndata->PrentID))))
	  {
		aNode=aNode->getNextSibling();
		continue;
	  }
	  else
      {
		pNode = (TTreeNode*)(tmpstr->Objects[idx]);
        bNode=aNode;
		aNode=aNode->getNextSibling();
        bNode->MoveTo(pNode,naAddChild);
	  }
	}
	tvMyWork->FullCollapse();
  }
  __finally
  {
	delete tmpstr; tmpstr=NULL;
	query->Close();
	tvMyWork->Items->EndUpdate();
	delete query;
  }


}
//---------------------------------------------------------------------------
void __fastcall TfrmMyWork::FormShow(TObject *Sender)
{
GetData();
ShowPurViewByGroup(UID);
}

bool  TfrmMyWork::GetNodeChecked(TTreeNode *ANode)
{
	  TVITEM tvItem;
	  tvItem.mask = TVIF_HANDLE | TVIF_STATE;
	  tvItem.hItem = ANode->ItemId;
	  tvItem.stateMask = TVIS_STATEIMAGEMASK;
	  TreeView_GetItem(ANode->TreeView->Handle, &tvItem);
	  return ((BOOL)(tvItem.state >> 12) -1);
}
void  TfrmMyWork::SetNodeChecked(TTreeNode *ANode,bool IsSetToChecked)
{
	  TVITEM tvItem;
	  tvItem.mask = TVIF_HANDLE | TVIF_STATE;
      tvItem.hItem = ANode->ItemId;
      tvItem.stateMask = TVIS_STATEIMAGEMASK;
      tvItem.state = INDEXTOSTATEIMAGEMASK(IsSetToChecked?2:1);
	  TreeView_SetItem(ANode->TreeView->Handle, &tvItem);
}
void  TfrmMyWork::SetChildChecked(TTreeNode *ANode,bool yn)
{
	int count=ANode->Count;
	SetNodeChecked(ANode,yn);
	if (count!=0)
	for (int i=0;i<count;i++)    // 递归
	 SetChildChecked(ANode->Item[i],yn);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMyWork::tvMyWorkMouseDown(TObject *Sender, TMouseButton Button,
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
void __fastcall TfrmMyWork::tvMyWorkMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	 ClickNode = tvMyWork->GetNodeAt(X,Y);
  if (ClickNode!=NULL) // 保存原节点的Checked值
	 NodeChecked = GetNodeChecked(ClickNode);
}

void TfrmMyWork::ShowPurViewByGroup(int ID)
{
	String sql;
	TTreeNode  *aNode=NULL;
	struct NodeWorkData *ndata = NULL;
	sql = "select B.ID,DisplayName from Sys_Mywork A join sys_myworkaction B";
	sql = sql + " ON A.MyWorkActionID = B.ID where A.useriD = " + IntToStr(ID);
	TADOQuery *aq = new TADOQuery(Application);
	aq->Connection = fn ;
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	for(aNode =  tvMyWork->Items->GetFirstNode() ; aNode!=NULL ;)
	{
	   ndata = (NodeWorkData*)(aNode->Data);
	   SetNodeChecked(aNode,false);
	   if (ndata->PrentID != -1)  {
		aq->First();
		while(!aq->Eof)
		{
			 if (ndata->ID == aq->FieldByName("ID")->AsInteger  ) {
			   SetNodeChecked(aNode,true);
			 }
		   aq->Next();
		 }
	   }
	   aNode=aNode->GetNext();

	}
}
void TfrmMyWork::SavePurview()
{
	struct NodeWorkData *ndata = NULL;
	TTreeNode  *aNode=NULL;
	TStringList * ActionList;
	ActionList = new TStringList();


  try
  {
       Screen->Cursor = crHourGlass ;
		for(aNode=tvMyWork->Items->GetFirstNode() ; aNode!=NULL ;)
		{
		   ndata = (NodeWorkData*)(aNode->Data);
		   if ((ndata->PrentID != -1) && (GetNodeChecked(aNode))) {
			   ActionList->Add(IntToStr(ndata->ID));
		   }
		   aNode=aNode->GetNext();
		}
		String sql;
		sql = "delete Sys_Mywork where UserID = " + IntToStr(UID);

		ExcSQL(sql);

		for (int i = 0 ; i < ActionList->Count ; i++) {
			 sql = "insert into Sys_Mywork(UserID,MyWorkActionID) " ;
			 sql = sql + " values  ("+ IntToStr(UID)+"," + ActionList->Strings[i] + ")";
			 ExcSQL(sql);
			 Sleep(100);
			 Application->ProcessMessages();
		}
		Screen->Cursor = crDefault ;
	   MessageBoxA(0,"我的工作平台保存成功！","提示",MB_ICONWARNING);
	}
  __finally
  {
	 delete ActionList;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMyWork::SpeedButton1Click(TObject *Sender)
{
	  SavePurview();
      ModalResult = mrOk ;
}
void TfrmMyWork::ExcSQL(AnsiString sql)
{
   TADOQuery *aq = new TADOQuery(Application);
   aq->Connection = fn ;
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->ExecSQL();
   delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMyWork::SpeedButton2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

