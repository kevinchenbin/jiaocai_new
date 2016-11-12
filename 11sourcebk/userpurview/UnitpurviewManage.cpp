//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitpurviewManage.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmpurview *frmpurview;
//---------------------------------------------------------------------------
__fastcall Tfrmpurview::Tfrmpurview(TComponent* Owner,TADOConnection *cn,int stgid,int sid)
	: TForm(Owner)
{
   fcon = cn;
   fstgid = stgid;
   ReadyGroup();
   tvgroup->AutoExpand = false;
   ReadyData();
   SearchMod = 1;
   userid = sid;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpurview::FormCreate(TObject *Sender)
{
	SetWindowLong(tvpurview->Handle,GWL_STYLE,
			GetWindowLong(tvpurview->Handle,GWL_STYLE) | TVS_CHECKBOXES);

}

bool  Tfrmpurview::GetNodeChecked(TTreeNode *ANode)
{
	  TVITEM tvItem;
	  tvItem.mask = TVIF_HANDLE | TVIF_STATE;
	  tvItem.hItem = ANode->ItemId;
	  tvItem.stateMask = TVIS_STATEIMAGEMASK;
	  TreeView_GetItem(ANode->TreeView->Handle, &tvItem);
	  return ((BOOL)(tvItem.state >> 12) -1);
}
void  Tfrmpurview::SetNodeChecked(TTreeNode *ANode,bool IsSetToChecked)
{
	  TVITEM tvItem;
      tvItem.mask = TVIF_HANDLE | TVIF_STATE;
      tvItem.hItem = ANode->ItemId;
      tvItem.stateMask = TVIS_STATEIMAGEMASK;
      tvItem.state = INDEXTOSTATEIMAGEMASK(IsSetToChecked?2:1);
	  TreeView_SetItem(ANode->TreeView->Handle, &tvItem);
}
void  Tfrmpurview::SetChildChecked(TTreeNode *ANode,bool yn)
{
	int count=ANode->Count;
	SetNodeChecked(ANode,yn);
	if (count!=0)
	for (int i=0;i<count;i++)    // 递归
	 SetChildChecked(ANode->Item[i],yn);
}
void Tfrmpurview::ReadyData()
{
  String sql;
  sql = "select * from SYS_Action ";


  struct Nodedata *ndata = NULL;

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
	  ndata = new Nodedata();
	  ndata->Name = query->FieldByName("actionname")->AsAnsiString ;
	  ndata->PrentID = query->FieldByName("parent")->AsInteger ;
	  ndata->ID = query->FieldByName("code")->AsInteger ;
	  //生成一个根节点加入TreeView
	  aNode=tvpurview->Items->AddObject(NULL,ndata->Name ,ndata);
	  //记录id-TreeNode对应关系,便于下面查找
	  tmpstr->AddObject(AnsiString(ndata->ID),aNode);
	}

	query->Close();
	ndata=NULL;

   int idx;
	for(aNode=tvpurview->Items->GetFirstNode(); aNode!=NULL ;)
	{
	  ndata = (Nodedata*)(aNode->Data);
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
void __fastcall Tfrmpurview::tvpurviewMouseDown(TObject *Sender, TMouseButton Button,
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
void Tfrmpurview::ReadyGroup()
{
		TStringList *tmpstr=NULL;
		TADOQuery *query = new TADOQuery(Application);
		AnsiString sql;
		sql = "select stgid,name from sys_Group A left join SYS_StorageInfo B on B.ID = stgid group by stgid ,name "
		" having stgid = " + IntToStr(fstgid);

		struct Nodedata *ndata = NULL;
		TTreeNode  *aNode=NULL;
		TTreeNode  *bNode=NULL;
		TTreeNode  *pNode=NULL;
  try
  {
		query->Connection = fcon;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();

	tmpstr =new TStringList();
	tvgroup->Items->BeginUpdate();//禁止刷新，提高速度
	//遍历记录集
	for(query->First(); !query->Eof; query->Next())      //店信息
	{
		ndata = new Nodedata();
		ndata->Name = query->FieldByName("name")->AsAnsiString ;
		ndata->PrentID = -1;
		ndata->ID = query->FieldByName("stgid")->AsInteger ;

		aNode = tvgroup->Items->AddObject(NULL,ndata->Name ,ndata);

	}

	query->Close();
	ndata=NULL;

	sql = "select * from sys_Group where stgid =" + IntToStr(fstgid);                    //组信息
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

  // 	tvgroup->Items->BeginUpdate();//禁止刷新，提高速度
	//遍历记录集
	aNode = tvgroup->Items->GetFirstNode();
  //	tvgroup->Items->Item[0]->ImageIndex = -1;

	for(query->First(); !query->Eof; query->Next())      //店信息
	{
		ndata = new Nodedata();
		ndata->Name = query->FieldByName("groupname")->AsAnsiString ;
		ndata->PrentID = -1;
		ndata->ID = query->FieldByName("ID")->AsInteger ;
		tvgroup->Items->AddChildObject(aNode,ndata->Name ,ndata);

	// tvgroup->Items->AddObject(NULL,ndata->Name ,ndata);

	}
   tvgroup->Items->Item[0]->Expand(True);
  }
  __finally
  {
	delete tmpstr; tmpstr=NULL;
	query->Close();
	tvgroup->Items->EndUpdate();
	tvgroup->Items->Item[0]->ImageIndex = -1;
	delete query;

  }


}

void __fastcall Tfrmpurview::tvpurviewMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
  ClickNode = tvpurview->GetNodeAt(X,Y);
  if (ClickNode!=NULL) // 保存原节点的Checked值
	 NodeChecked = GetNodeChecked(ClickNode);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpurview::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpurview::tvgroupCustomDrawItem(TCustomTreeView *Sender, TTreeNode *Node,
          TCustomDrawState State, bool &DefaultDraw)
{
	 if (State.Contains(cdsSelected))
      {
		  Sender->Canvas->Brush->Color   =clBlue ;
	  }
	  DefaultDraw   =   true;
}
//---------------------------------------------------------------------------

void Tfrmpurview::SavePurview()
{
	struct Nodedata *ndata = NULL;
	TTreeNode  *aNode=NULL;
	TStringList * ActionList;
	ActionList = new TStringList();

  if (GroupNode == NULL) {
	  return;
  }
  try
  {
       Screen->Cursor = crHourGlass ;
		for(aNode=tvpurview->Items->GetFirstNode() ; aNode!=NULL ;)
		{
		   ndata = (Nodedata*)(aNode->Data);
		   if ((ndata->PrentID != -1) && (GetNodeChecked(aNode))) {
			   ActionList->Add(IntToStr(ndata->ID));
		   }
		   aNode=aNode->GetNext();
		}
		ndata = (Nodedata*)(GroupNode->Data);

		String sql;
		sql = "delete SYS_GroupAction where GroupID = " + IntToStr(ndata->ID);

		ExcSQL(sql);

		for (int i = 0 ; i < ActionList->Count ; i++) {
			 sql = "Insert into SYS_GroupAction (ActionID,GroupID,ReadPurview,WritePurview) " ;
			 sql = sql + " values  (" + ActionList->Strings[i] + "," + IntToStr(ndata->ID) + ",1,1)";
			 ExcSQL(sql);
			 Sleep(10);
			 Application->ProcessMessages();
		}
		AddEvent(1,"权限设置窗口",userid,fstgid,"权限设置",fcon);
		Screen->Cursor = crDefault ;
	   MessageBoxA(0,"权限信息保存成功！","提示",MB_ICONWARNING);
	}
  __finally
  {
	 delete ActionList;
  }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmpurview::BtnSaveClick(TObject *Sender)
{
	 SavePurview();
}
void Tfrmpurview::ExcSQL(AnsiString sql)
{
   TADOQuery *aq = new TADOQuery(Application);
   aq->Connection = fcon ;
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->ExecSQL();
   delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpurview::tvgroupMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	  GroupNode = tvgroup->GetNodeAt(X,Y);
	  if (SearchMod == 1) {
		 if (GroupNode != NULL) {
		struct Nodedata *ndata = NULL;
		ndata = (Nodedata*)(GroupNode->Data);
        SearchMod = 1;
		ShowPurViewByGroup(ndata->ID);
	  }
	  } else if (SearchMod == 2) {
         BtnFind->Click();
		}
	
}
void Tfrmpurview::ShowPurViewByGroup(int ID)
{
	String sql;
	TTreeNode  *aNode=NULL;
	struct Nodedata *ndata = NULL;
	sql = "select * from SYS_GroupAction where GroupID =" + IntToStr(ID);
	TADOQuery *aq = new TADOQuery(Application);
	aq->Connection = fcon ;
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	for(aNode =  tvpurview->Items->GetFirstNode() ; aNode!=NULL ;)
	{
	   ndata = (Nodedata*)(aNode->Data);
	   SetNodeChecked(aNode,false);
	   if (ndata->PrentID != -1)  {
		aq->First();
		while(!aq->Eof)
		{
			 if (ndata->ID == aq->FieldByName("ActionID")->AsInteger  ) {
			   SetNodeChecked(aNode,true);
			 }
		   aq->Next();
		 }
	   }
	   aNode=aNode->GetNext();

	}
}
//---------------------------------------------------------------------------
void Tfrmpurview::ShowUsers(int ID)
{
   	String sql;
	TTreeNode  *aNode=NULL;
	struct Nodedata *ndata = NULL;
	TColumn *Col;
	sql = "select name ,tel ,mob ,job ,address ,bk  from  sys_user A ";
	sql = sql +" inner join sys_usergroup B on A.ID = B.UserID where B.GroupID =" + IntToStr(ID);

	aquserlist->Connection = fcon ;
	aquserlist->SQL->Clear();
	aquserlist->SQL->Add(sql);
	aquserlist->Open();
}

void __fastcall Tfrmpurview::BtnFindClick(TObject *Sender)
{
	if (GroupNode != NULL) {
		struct Nodedata *ndata = NULL;
		ndata = (Nodedata*)(GroupNode->Data);
        SearchMod = 2;
		ShowUsers(ndata->ID);
        tvpurview->Visible = false;
		dguserlist->Visible = true;

	}else
	{

	   MessageBoxA(0,"请先选择用户角色!","提示",MB_ICONWARNING );
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpurview::BtnReplaceClick(TObject *Sender)
{
	if (GroupNode != NULL) {
		struct Nodedata *ndata = NULL;
		ndata = (Nodedata*)(GroupNode->Data);
        SearchMod = 1;
		ShowPurViewByGroup(ndata->ID);
		dguserlist->Visible = false;
        tvpurview->Visible = true;
	}else
	{
		MessageBoxA(0,"请先选择用户角色!","提示",MB_ICONWARNING );
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpurview::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpurview::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F4) {     //保存
		BtnSave->Click();
	}
	if (Key == VK_F1) {     //查看权限
		BtnReplace->Click();
	}
	if (Key == VK_F2) {     //查看用户
		BtnFind->Click();
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

void __fastcall Tfrmpurview::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

