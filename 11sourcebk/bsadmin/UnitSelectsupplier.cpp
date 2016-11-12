//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitSelectsupplier.h"
#include "..\supplier\detailemessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmselectsupplier *frmselectsupplier;
//---------------------------------------------------------------------------
__fastcall Tfrmselectsupplier::Tfrmselectsupplier(TComponent* Owner,TADOConnection *con,AnsiString sqlwhere)
	: TForm(Owner)
{
   fcon = con;
   where = sqlwhere;
}
void Tfrmselectsupplier::ShowClient()
{
  AnsiString sql = " select ID,Name from CUST_CustomerInfo where type = 1 and Name like '%" + edsupplier->Text + "%'";
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
  tvclient->Items->Clear();
	tmpstr =new TStringList();
	tvclient->Items->BeginUpdate();//禁止刷新，提高速度
	//遍历记录集
	for(query->First(); !query->Eof; query->Next())
	{
	  ndata = new Nodedata();
	  ndata->Name = query->FieldByName("Name")->AsAnsiString ;
	  ndata->ID = query->FieldByName("ID")->AsInteger ;
	  //生成一个根节点加入TreeView
	  aNode=tvclient->Items->AddObject(NULL,ndata->Name ,ndata);
	  //记录id-TreeNode对应关系,便于下面查找
	  tmpstr->AddObject(AnsiString(ndata->ID),aNode);
	}

	query->Close();
	ndata=NULL;

   /*int idx;
	for(aNode=tvclient->Items->GetFirstNode(); aNode!=NULL ;)
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
	}  */
	tvclient->FullCollapse();
	tvclient->Items->EndUpdate();

}
//---------------------------------------------------------------------------
AnsiString Tfrmselectsupplier::GetSelect()
{
	return SelectClientName;
}

//---------------------------------------------------------------------------
void __fastcall Tfrmselectsupplier::FormCreate(TObject *Sender)
{
	ShowClient();
}

//---------------------------------------------------------------------------
int Tfrmselectsupplier::GetSelectID()
{
	return SupplierID;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselectsupplier::tvclientMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	ClickNode = tvclient->GetNodeAt(X,Y);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselectsupplier::tvclientDblClick(TObject *Sender)
{
	if (ClickNode!=NULL) {
		struct Nodedata *ndata = NULL;
		ndata = (Nodedata*)(ClickNode->Data);
		SelectClientName = ndata->Name  ;
		SupplierID = ndata->ID ;
		ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselectsupplier::edsupplierKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
    	ShowClient();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmselectsupplier::sbnewcustomerClick(TObject *Sender)
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select max(id) as id,count(1) as count from CUST_CustomerInfo where type = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	int count1 = aq->FieldByName("count")->AsInteger ;
	TDetaileForm * frm = new TDetaileForm(Application,1,1,"" ,fcon);
	frm->ShowModal();
	delete frm;
	sql = "select max(id) as id,count(1) as count from CUST_CustomerInfo where type = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	int count2 = aq->FieldByName("count")->AsInteger ;
	if (count2 > count1) {
    	struct Nodedata *ndata = NULL;
		ndata = new Nodedata();
		sql = "select ID,Name from CUST_CustomerInfo where id = " + aq->FieldByName("id")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		ndata->Name = aq->FieldByName("Name")->AsAnsiString ;
		ndata->ID = aq->FieldByName("ID")->AsInteger ;
		tvclient->Items->AddObject(NULL,ndata->Name ,ndata);
	}
	delete aq;
}
//---------------------------------------------------------------------------

