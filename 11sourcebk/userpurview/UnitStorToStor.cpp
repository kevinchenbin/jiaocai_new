//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitStorToStor.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmStorToStor *frmStorToStor;
//---------------------------------------------------------------------------
__fastcall TfrmStorToStor::TfrmStorToStor(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
	fcon = cn;
	ReadyGroup();
	tvgroup->AutoExpand = false;
   	SearchMod = 1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorToStor::FormCreate(TObject *Sender)
{
	SetWindowLong(tvpurview->Handle,GWL_STYLE,
			GetWindowLong(tvpurview->Handle,GWL_STYLE) | TVS_CHECKBOXES);

}

bool  TfrmStorToStor::GetNodeChecked(TTreeNode *ANode)
{
	  TVITEM tvItem;
	  tvItem.mask = TVIF_HANDLE | TVIF_STATE;
	  tvItem.hItem = ANode->ItemId;
	  tvItem.stateMask = TVIS_STATEIMAGEMASK;
	  TreeView_GetItem(ANode->TreeView->Handle, &tvItem);
	  return ((BOOL)(tvItem.state >> 12) -1);
}
void  TfrmStorToStor::SetNodeChecked(TTreeNode *ANode,bool IsSetToChecked)
{
	  TVITEM tvItem;
      tvItem.mask = TVIF_HANDLE | TVIF_STATE;
      tvItem.hItem = ANode->ItemId;
      tvItem.stateMask = TVIS_STATEIMAGEMASK;
      tvItem.state = INDEXTOSTATEIMAGEMASK(IsSetToChecked?2:1);
	  TreeView_SetItem(ANode->TreeView->Handle, &tvItem);
}
void  TfrmStorToStor::SetChildChecked(TTreeNode *ANode,bool yn)
{
	int count=ANode->Count;
	SetNodeChecked(ANode,yn);
	if (count!=0)
	for (int i=0;i<count;i++)    // �ݹ�
	SetChildChecked(ANode->Item[i],yn);
}

//---------------------------------------------------------------------------
void __fastcall TfrmStorToStor::tvpurviewMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if (ClickNode!=NULL)
	if (GetNodeChecked(ClickNode)!=NodeChecked)
	{ // ���������ﶼ�ó�һ��
	    NodeChecked=!NodeChecked; // ������
		SetChildChecked(ClickNode,NodeChecked);
	}
}
//---------------------------------------------------------------------------
void TfrmStorToStor::ReadyGroup()
{
	TStringList *tmpstr=NULL;
	TADOQuery *query = new TADOQuery(Application);
	AnsiString sql;
	sql = "select ID,Name from SYS_StorageInfo ";

	struct Nodedt *ndata = NULL;
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
		tvgroup->Items->BeginUpdate();//��ֹˢ�£�����ٶ�
	//������¼��
		for(query->First(); !query->Eof; query->Next())      //����Ϣ
		{
			ndata = new Nodedt();
			ndata->Name = query->FieldByName("Name")->AsAnsiString ;
			ndata->ID = query->FieldByName("ID")->AsInteger ;

			aNode = tvgroup->Items->AddObject(NULL,ndata->Name ,ndata);

		}
   		tvgroup->Items->Item[0]->Expand(True);
	}
	__finally
	{
		delete tmpstr; tmpstr=NULL;
		query->Close();
		tvgroup->Items->EndUpdate();
		//tvgroup->Items->Item[0]->ImageIndex = -1;
		delete query;
	}
}

void __fastcall TfrmStorToStor::tvpurviewMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
  ClickNode = tvpurview->GetNodeAt(X,Y);
  if (ClickNode!=NULL) // ����ԭ�ڵ��Checkedֵ
	 NodeChecked = GetNodeChecked(ClickNode);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorToStor::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorToStor::tvgroupCustomDrawItem(TCustomTreeView *Sender, TTreeNode *Node,
          TCustomDrawState State, bool &DefaultDraw)
{
	 if (State.Contains(cdsSelected))
      {
		  Sender->Canvas->Brush->Color   =clBlue ;
	  }
	  DefaultDraw   =   true;
}
//---------------------------------------------------------------------------

void TfrmStorToStor::SavePurview()
{
	String sql;
	if (GroupNode == NULL) {
		return;
	}
	struct Nodedt *nda = NULL;
	nda = (Nodedt*)(GroupNode->Data);
	int ID = nda->ID;
	TTreeNode  *aNode=NULL;
	TTreeNode  *bNode=NULL;
	struct NodeStordata *ndata = NULL;
	TADOQuery *aq = new TADOQuery(Application);
	aq->Connection = fcon ;
	TADOQuery *aq1 = new TADOQuery(Application);
	aq1->Connection = fcon ;

    try
	{
		tvpurview->Items->BeginUpdate();//��ֹˢ�£�����ٶ�
		
		ndata=NULL;
		struct NodeStordata *ndata1 = NULL;
		for(aNode = tvpurview->Items->GetFirstNode(); aNode!=NULL ;)
		{
			ndata = (NodeStordata*)(aNode->Data);
			sql = "select * from BS_StoToSto where ystgid = " + IntToStr(ID) + " and mstgid = " + IntToStr(ndata->mstgid);
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				sql = "update BS_StoToSto set ";
				for (bNode = aNode->getFirstChild(); bNode!= NULL ;)
				{
					ndata1 = (NodeStordata*)(bNode->Data);
					sql = sql + "[" + ndata1->name + "] = " + BoolToStr(GetNodeChecked(bNode)) + ",";
					bNode = bNode->getNextSibling();
				}
				sql = sql.SubString(1,sql.Length()-1);
				sql = sql + " where ystgid = " + IntToStr(ID) + " and mstgid = " + IntToStr(ndata->mstgid);
				ExcSQL(sql);
			}
			else
			{
				sql = "insert into BS_StoToSto(ystgid,mstgid,stkbook,[order],procure,storage,wsale,retail,pandian,diaobo) values (" +
						IntToStr(ID) + "," + IntToStr(ndata->mstgid) ;
                for (bNode = aNode->getFirstChild(); bNode!= NULL ;)
				{
					ndata1 = (NodeStordata*)(bNode->Data);
					sql = sql + "," + BoolToStr(GetNodeChecked(bNode)) ;
					bNode = bNode->getNextSibling();
				}
				sql = sql + ")";
				ExcSQL(sql);
			}

			aNode=aNode->getNextSibling();
		}
		MessageBoxA(0,"Ȩ����Ϣ����ɹ���","��ʾ",MB_ICONWARNING);
	}
	__finally
	{
		aq->Close();
		aq1->Close();
		tvpurview->Items->EndUpdate();
		delete aq;
		delete aq1;
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmStorToStor::BtnSaveClick(TObject *Sender)
{
	 SavePurview();
}
//---------------------------------------------------------------------------
void TfrmStorToStor::ExcSQL(AnsiString sql)
{
   TADOQuery *aq = new TADOQuery(Application);
   aq->Connection = fcon ;
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->ExecSQL();
   delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorToStor::tvgroupMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	GroupNode = tvgroup->GetNodeAt(X,Y);
	if (GroupNode != NULL) {
		struct Nodedt *ndata = NULL;
		ndata = (Nodedt*)(GroupNode->Data);
		SearchMod = 1;
		ShowPurViewByGroup(ndata->ID);
	}
}
void TfrmStorToStor::ShowPurViewByGroup(int ID)
{
	String sql;
	TTreeNode  *aNode=NULL;
	TTreeNode  *bNode=NULL;
	TTreeNode  *pNode=NULL;
	struct NodeStordata *ndata = NULL;
	sql = "select * from SYS_StorageInfo where id <> " + IntToStr(ID);
	TADOQuery *aq = new TADOQuery(Application);
	aq->Connection = fcon ;
	TADOQuery *aq1 = new TADOQuery(Application);
	aq1->Connection = fcon ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	tvpurview->Items->Clear();
    try
	{
		tvpurview->Items->BeginUpdate();//��ֹˢ�£�����ٶ�
		//������¼��
		for(aq->First(); !aq->Eof; aq->Next())
		{
			ndata = new NodeStordata();

			ndata->ystgid = ID ;
			ndata->mstgid = aq->FieldByName("ID")->AsInteger ;
			ndata->ViewName = aq->FieldByName("Name")->AsString ;
			ndata->name =  "" ;
			ndata->parentid = 0 ;
			ndata->use = 0 ;

			//����һ�����ڵ����TreeView
			aNode = tvpurview->Items->AddObject(NULL,ndata->ViewName ,ndata);
			//��¼id-TreeNode��Ӧ��ϵ,�����������
		}

		aq->Close();
		ndata=NULL;
		struct NodeStordata *ndata1 = NULL;
		for(aNode = tvpurview->Items->GetFirstNode(); aNode!=NULL ;)
		{
			ndata = (NodeStordata*)(aNode->Data);
			sql = "select * from BS_StoToSto where ystgid = " + IntToStr(ID) + " and mstgid = " + IntToStr(ndata->mstgid);
			aq1->Close();
			aq1->SQL->Clear();
			aq1->SQL->Add(sql);
			aq1->Open();

			ndata1 = new NodeStordata();
			ndata1->ystgid = ID ;
			ndata1->mstgid = ndata->mstgid ;
			ndata1->ViewName = "����ѯ" ;
			ndata1->name =  "stkbook" ;
			ndata1->parentid = 1 ;
			ndata1->use = aq1->FieldByName("stkbook")->AsBoolean ;
			bNode = tvpurview->Items->AddChildObject(aNode,ndata1->ViewName,ndata1);
			SetNodeChecked(bNode,aq1->FieldByName("stkbook")->AsBoolean);

			ndata1 = new NodeStordata();
			ndata1->ystgid = ID ;
			ndata1->mstgid = ndata->mstgid ;
			ndata1->ViewName = "������ѯ" ;
			ndata1->name =  "order" ;
			ndata1->parentid = 1 ;
			ndata1->use = aq1->FieldByName("order")->AsBoolean ;
			bNode = tvpurview->Items->AddChildObject(aNode,ndata1->ViewName,ndata1);
			SetNodeChecked(bNode,aq1->FieldByName("order")->AsBoolean);


			ndata1 = new NodeStordata();
			ndata1->ystgid = ID ;
			ndata1->mstgid = ndata->mstgid ;
			ndata1->ViewName = "�ɹ���ѯ" ;
			ndata1->name =  "procure" ;
			ndata1->parentid = 1 ;
			ndata1->use = aq1->FieldByName("procure")->AsBoolean ;
			bNode = tvpurview->Items->AddChildObject(aNode,ndata1->ViewName,ndata1);
			SetNodeChecked(bNode,aq1->FieldByName("procure")->AsBoolean);

			ndata1 = new NodeStordata();
			ndata1->ystgid = ID ;
			ndata1->mstgid = ndata->mstgid ;
			ndata1->ViewName = "����ѯ" ;
			ndata1->name =  "storage" ;
			ndata1->parentid = 1 ;
			ndata1->use = aq1->FieldByName("storage")->AsBoolean ;
			bNode = tvpurview->Items->AddChildObject(aNode,ndata1->ViewName,ndata1);
			SetNodeChecked(bNode,aq1->FieldByName("storage")->AsBoolean);

			ndata1 = new NodeStordata();
			ndata1->ystgid = ID ;
			ndata1->mstgid = ndata->mstgid ;
			ndata1->ViewName = "������ѯ" ;
			ndata1->name =  "wsale" ;
			ndata1->parentid = 1 ;
			ndata1->use = aq1->FieldByName("wsale")->AsBoolean ;
			bNode = tvpurview->Items->AddChildObject(aNode,ndata1->ViewName,ndata1);
			SetNodeChecked(bNode,aq1->FieldByName("wsale")->AsBoolean);

			ndata1 = new NodeStordata();
			ndata1->ystgid = ID ;
			ndata1->mstgid = ndata->mstgid ;
			ndata1->ViewName = "���۲�ѯ" ;
			ndata1->name =  "retail" ;
			ndata1->parentid = 1 ;
			ndata1->use = aq1->FieldByName("retail")->AsBoolean ;
			bNode = tvpurview->Items->AddChildObject(aNode,ndata1->ViewName,ndata1);
			SetNodeChecked(bNode,aq1->FieldByName("retail")->AsBoolean);

			ndata1 = new NodeStordata();
			ndata1->ystgid = ID ;
			ndata1->mstgid = ndata->mstgid ;
			ndata1->ViewName = "�̵��ѯ" ;
			ndata1->name =  "pandian" ;
			ndata1->parentid = 1 ;
			ndata1->use = aq1->FieldByName("pandian")->AsBoolean ;
			bNode = tvpurview->Items->AddChildObject(aNode,ndata1->ViewName,ndata1);
			SetNodeChecked(bNode,aq1->FieldByName("pandian")->AsBoolean);

			ndata1 = new NodeStordata();
			ndata1->ystgid = ID ;
			ndata1->mstgid = ndata->mstgid ;
			ndata1->ViewName = "���Ͳ�ѯ" ;
			ndata1->name =  "diaobo" ;
			ndata1->parentid = 1 ;
			ndata1->use = aq1->FieldByName("diaobo")->AsBoolean ;
			bNode = tvpurview->Items->AddChildObject(aNode,ndata1->ViewName,ndata1);
			SetNodeChecked(bNode,aq1->FieldByName("diaobo")->AsBoolean);

			aNode=aNode->getNextSibling();
		}
	}
	__finally
	{
		aq1->Close();
		tvpurview->Items->EndUpdate();
		delete aq;
		delete aq1;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorToStor::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorToStor::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F4) {     //����
		BtnSave->Click();
	}
	if (Key == VK_F1) {     //�鿴Ȩ��
		BtnReplace->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorToStor::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorToStor::FormShow(TObject *Sender)
{
	tvpurview->AutoExpand = true;
}
//---------------------------------------------------------------------------

