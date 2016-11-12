//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormView.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmformview *frmformview;
//---------------------------------------------------------------------------
__fastcall Tfrmformview::Tfrmformview(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
   fcon = cn;
   fstgid = stgid;
   ReadyData();
   SearchMod = 1;

}
//---------------------------------------------------------------------------
void __fastcall Tfrmformview::FormCreate(TObject *Sender)
{
 SetWindowLong(tvpurview->Handle,GWL_STYLE,
 GetWindowLong(tvpurview->Handle,GWL_STYLE) | TVS_CHECKBOXES);
 FirstView();

}

bool  Tfrmformview::GetNodeChecked(TTreeNode *ANode)
{
	  TVITEM tvItem;
	  tvItem.mask = TVIF_HANDLE | TVIF_STATE;
	  tvItem.hItem = ANode->ItemId;
	  tvItem.stateMask = TVIS_STATEIMAGEMASK;
	  TreeView_GetItem(ANode->TreeView->Handle, &tvItem);
	  return ((BOOL)(tvItem.state >> 12) -1);
}
void  Tfrmformview::SetNodeChecked(TTreeNode *ANode,bool IsSetToChecked)
{
	  TVITEM tvItem;
      tvItem.mask = TVIF_HANDLE | TVIF_STATE;
      tvItem.hItem = ANode->ItemId;
      tvItem.stateMask = TVIS_STATEIMAGEMASK;
      tvItem.state = INDEXTOSTATEIMAGEMASK(IsSetToChecked?2:1);
	  TreeView_SetItem(ANode->TreeView->Handle, &tvItem);
}
void  Tfrmformview::SetChildChecked(TTreeNode *ANode,bool yn)
{
	int count=ANode->Count;
	SetNodeChecked(ANode,yn);
	if (count!=0)
	for (int i=0;i<count;i++)    // 递归
	 SetChildChecked(ANode->Item[i],yn);
}
void Tfrmformview::ReadyData()
{
  String sql;
  sql = "select * from BS_SYS_Formview where stgid = " + IntToStr(fstgid) ;


  struct Nodedatamenu *ndata = NULL;

  TStringList *tmpstr=NULL;

  TTreeNode  *aNode=NULL;
  TTreeNode  *bNode=NULL;
  TTreeNode  *pNode=NULL;

  TADOQuery *query = new TADOQuery(Application);
  query->Connection = fcon;
  query->Close();
  query->SQL->Clear();
  query->SQL->Add(sql);
  query->Open();
  try
  {
	tmpstr =new TStringList();
	tvpurview->Items->BeginUpdate();//禁止刷新，提高速度
	//遍历记录集
	for(query->First(); !query->Eof; query->Next())
	{
	  ndata = new Nodedatamenu();
	  ndata->Name = query->FieldByName("Name")->AsAnsiString ;
	  ndata->PrentID = query->FieldByName("ParentID")->AsInteger ;
	  ndata->ID = query->FieldByName("id")->AsInteger ;
	  ndata->state = query->FieldByName("state")->AsBoolean ;
	  //生成一个根节点加入TreeView
	  aNode=tvpurview->Items->AddObject(NULL,ndata->Name ,ndata);
	   //SetNodeChecked(aNode,query->FieldByName("state")->AsBoolean);
	  //记录id-TreeNode对应关系,便于下面查找
	  tmpstr->AddObject(AnsiString(ndata->ID),aNode);
	}

	query->Close();
	ndata=NULL;

   int idx;
	for(aNode=tvpurview->Items->GetFirstNode(); aNode!=NULL ;)
	{
	  ndata = (Nodedatamenu*)(aNode->Data);
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
		//SetNodeChecked(aNode,ndata->state);
	  }
	}
	tvpurview->FullCollapse();
  }
  __finally
  {
	delete tmpstr; tmpstr=NULL;
	query->Close();
	tvpurview->Items->EndUpdate();
	delete query;
  }

		
}
//---------------------------------------------------------------------------
void __fastcall Tfrmformview::tvpurviewMouseDown(TObject *Sender, TMouseButton Button,
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


void __fastcall Tfrmformview::tvpurviewMouseMove(TObject *Sender, TShiftState Shift,
		  int X, int Y)
{
  ClickNode = tvpurview->GetNodeAt(X,Y);
  if (ClickNode!=NULL) // 保存原节点的Checked值
	 NodeChecked = GetNodeChecked(ClickNode);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmformview::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmformview::tvgroupCustomDrawItem(TCustomTreeView *Sender, TTreeNode *Node,
		  TCustomDrawState State, bool &DefaultDraw)
{
	 if (State.Contains(cdsSelected))
	  {
		  Sender->Canvas->Brush->Color   =clBlue ;
	  }
	  DefaultDraw   =   true;
}
//---------------------------------------------------------------------------

void Tfrmformview::SavePurview()
{
	struct Nodedatamenu *ndata = NULL;
	TTreeNode  *aNode=NULL;
	TStringList * ActionList;
	ActionList = new TStringList();
	AnsiString sql,sqlwhere;

  try
  {
       Screen->Cursor = crHourGlass ;
		for(aNode=tvpurview->Items->GetFirstNode() ; aNode!=NULL ;)
		{
		   ndata = (Nodedatamenu*)(aNode->Data);
		   if ((ndata->PrentID != -1) && (GetNodeChecked(aNode))) {
			   ActionList->Add(IntToStr(ndata->ID));
			   if (sqlwhere == "") {
				   sqlwhere = "(" + IntToStr(ndata->ID);
			   }
			   else
			   {
					sqlwhere = sqlwhere + "," + IntToStr(ndata->ID);
			   }
		   }
		   aNode=aNode->GetNext();
		}
		sqlwhere = sqlwhere + ")";

		sql = "update BS_SYS_Formview set state = 1 where id in " + sqlwhere ;
		ExcSQL(sql);
		sql = "update BS_SYS_Formview set state = 0 where id not in " + sqlwhere + " and stgid = " + IntToStr(fstgid) ;
		ExcSQL(sql);

		//ndata = (Nodedatamenu*)(GroupNode->Data);

		/*for (int i = 0 ; i < ActionList->Count ; i++) {
			 sql = "Insert into SYS_GroupAction (ActionID,GroupID,ReadPurview,WritePurview) " ;
			 sql = sql + " values  (" + ActionList->Strings[i] + "," + IntToStr(ndata->ID) + ",1,1)";
			 ExcSQL(sql);
			 Sleep(200);
			 Application->ProcessMessages();
		}*/
		Screen->Cursor = crDefault ;
	   MessageBoxA(0,"保存成功！","提示",MB_ICONWARNING);
	}
  __finally
  {
	 delete ActionList;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmformview::BtnSaveClick(TObject *Sender)
{
	 SavePurview();
}
void Tfrmformview::ExcSQL(AnsiString sql)
{
   TADOQuery *aq = new TADOQuery(Application);
   aq->Connection = fcon ;
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->ExecSQL();
   delete aq;
}

//---------------------------------------------------------------------------


void __fastcall Tfrmformview::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmformview::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F4) {     //保存
		BtnSave->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmformview::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void  Tfrmformview::FirstView()
{
	TTreeNode  *aNode=NULL;
	struct Nodedatamenu *ndata = NULL;
	for(aNode=tvpurview->Items->GetFirstNode() ; aNode!=NULL ;)
	{
		   ndata = (Nodedatamenu*)(aNode->Data);
		   SetNodeChecked(aNode,ndata->state);
		   aNode=aNode->GetNext();
	}
}
//---------------------------------------------------------------------------



