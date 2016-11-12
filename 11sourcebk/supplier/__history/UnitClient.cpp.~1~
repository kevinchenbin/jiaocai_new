//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitClient.h"
#include "detailemessage.h"
#include "CoustomerImport.h"
#include "clientquery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmclient *frmclient;
//---------------------------------------------------------------------------
__fastcall Tfrmclient::Tfrmclient(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
   fcon = cn;
   qrybase->Connection = cn;
   aq->Connection = cn;
   query->Connection = cn;
   querywhere = false;
}
void Tfrmclient::ReadyData()
{
	AnsiString sql;
	if (querywhere) {
		sql = " exec USP_BS_Client_View 1,0,'" + sqlwhere + "'";
	}
	else
	{
		sql = "select * from CUST_CustomerInfo where type in (2,3) order by id";
	}
	struct NodeClientdata *ndata = NULL;

	TStringList *tmpstr=NULL;
	TTreeNode  *aNode=NULL;
	TTreeNode  *bNode=NULL;
	TTreeNode  *pNode=NULL;

	TADOQuery *query = new TADOQuery(Application);
	query->Connection = fcon ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->IsEmpty() ) {
        return;
	}

	try
	{

	tmpstr =new TStringList();
   //	tvclient->Items->BeginUpdate();//禁止刷新，提高速度
	//遍历记录集
	for(query->First(); !query->Eof; query->Next())
	{
	  ndata = new NodeClientdata();
	  ndata->Name = query->FieldByName("name")->AsAnsiString ;
	  ndata->PrentID = query->FieldByName("PrentID")->AsInteger ;
	  ndata->ID = query->FieldByName("ID")->AsInteger ;
	  ndata->contact =  query->FieldByName("contact")->AsAnsiString ;
	  ndata->fax = query->FieldByName("fax")->AsAnsiString ;
	  ndata->telephone = query->FieldByName("telephone")->AsAnsiString ;
	  ndata->address  = query->FieldByName("address")->AsAnsiString ;
	  ndata->code = query->FieldByName("code")->AsAnsiString ;
	  ndata->date = query->FieldByName("date")->AsAnsiString ;
	  ndata->saleman =  query->FieldByName("salesman")->AsAnsiString ;
	  ndata->local = query->FieldByName("local")->AsAnsiString ;
	  //生成一个根节点加入TreeView
	  aNode = tvclient->Items->AddObject(NULL,ndata->Name ,ndata);

	  /*if ((query->FieldByName("PrentID")->AsInteger == -1) || (query->FieldByName("PrentID")->AsInteger == 0)) {
		aNode = tvclient->Items->AddObject(NULL,ndata->Name ,ndata);
	  }
	  else
	  {
		try {
        	pNode = (TTreeNode*)(tmpstr->Objects[tmpstr->IndexOf(AnsiString(ndata->PrentID))]);
			aNode = tvclient->Items->AddChildObject(pNode,ndata->Name ,ndata);
		} catch (...) {
			aNode = tvclient->Items->AddObject(NULL,ndata->Name ,ndata);
		}

	  } */

	  //记录id-TreeNode对应关系,便于下面查找
	  tmpstr->AddObject(AnsiString(ndata->ID),aNode);

	}
	aNode->Selected = true;
	aNode->Focused = true;
	aNode->MakeVisible();
	//ShowMessage(BoolToStr(aNode->IsVisible ) );
	query->Close();
	ndata=NULL;

	int idx;
	for(aNode = tvclient->Items->GetFirstNode(); aNode!=NULL ;)
	{
		ndata = (NodeClientdata*)(aNode->Data);
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



	}
	__finally
	{
		delete tmpstr; tmpstr=NULL;
		query->Close();
	   //	tvclient->Items->EndUpdate();
		delete query;
	}


	sql = "SELECT defaultvalue = isnull(e.text,'') FROM syscolumns a left join systypes b on "
		  "a.xusertype=b.xusertype inner join sysobjects d on a.id=d.id  and d.xtype='U' and  d.name <> 'dtproperties' "
		  "left join syscomments e on a.cdefault=e.id where d.name='BS_WsaleNoteHeader' "
		  "and a.name = 'VendorID' order by a.id,a.colorder" ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	AnsiString defaultvallue = aq->FieldByName("defaultvalue")->AsString ;
	defaultvallue =  defaultvallue.SubString(3,defaultvallue.Length()-4);
	sql = "select Name from CUST_CustomerInfo where id = " +  defaultvallue;
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	eddefaultname->Text = aq->FieldByName("Name")->AsAnsiString ;

}
//---------------------------------------------------------------------------
void __fastcall Tfrmclient::FormCreate(TObject *Sender)
{
	 ReadyData();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::tvclientMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ClickNode = tvclient->GetNodeAt(X,Y);

	if (ClickNode != NULL) {
		struct NodeClientdata *ndata = NULL;
		ndata = (NodeClientdata*)(ClickNode->Data);

        if (tvclient->Selected != NULL) {
			String sql = "select * from CUST_CustomerInfo where type in(2,3) and id = " + IntToStr(ndata->ID) ;
			qrybase->Close();
			qrybase->SQL->Clear();
			qrybase->SQL->Add(sql);
			qrybase->Open();
		}


		childNode = ClickNode->getFirstChild();
		lvclient->Clear();
		while(childNode != NULL)
		{
		   AddClient(childNode);
		   childNode = childNode->getNextSibling();
		}
	}
}
void Tfrmclient::AddClient(TTreeNode  *aNode)
{
	struct NodeClientdata *ndata = NULL;
	ndata = (NodeClientdata*)(aNode->Data);
	TListItem *item;
	item = lvclient->Items->Add();
	item->Caption = ndata->Name ;
	item->SubItems->Add(ndata->contact);
	item->SubItems->Add(ndata->telephone);
	item->SubItems->Add(ndata->address);
	item->SubItems->Add(ndata->saleman);
	item->SubItems->Add(ndata->code);
	item->SubItems->Add(ndata->local);
	item->SubItems->Add(ndata->date );
}
//---------------------------------------------------------------------------


void __fastcall Tfrmclient::N1Click(TObject *Sender)
{
	TDetaileForm *frm = new TDetaileForm(Application,2,1,"",fcon);
	struct NodeClientdata *ndata = NULL;
	ndata = (NodeClientdata*)(ClickNode->Data);
	frm->ParentID = ndata->ID  ;
	frm->ShowModal();
	delete frm;
	tvclient->Items->Clear();
	ReadyData();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::N2Click(TObject *Sender)
{
	TDetaileForm *frm = new TDetaileForm(Application,2,1,"",fcon);
	frm->ParentID = -1  ;
	frm->ShowModal();
	delete frm;
	tvclient->Items->Clear();
	ReadyData();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::BtnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::BtnDeleteClick(TObject *Sender)
{
	AnsiString sql ;
	if (ClickNode == NULL) {
		MessageBoxA(0,"请先选择要删除的客户!","提示",MB_ICONASTERISK);
		return;
	}
	struct NodeClientdata *ndata = NULL;
	ndata = (NodeClientdata*)(ClickNode->Data);
	if (ndata->Name == "普通客户") {
		MessageBoxA(0,"普通客户不能删除!","提示",MB_ICONASTERISK);
		return;
	}
	if (MessageBoxA(0,"确认要删除该客户吗？","提示",MB_OKCANCEL|MB_ICONQUESTION)==1 ) {


	 sql = "select count(*) as t from bs_wsalenoteheader where vendorID = " + IntToStr(ndata->ID) ;
	 TADOQuery *aq  = new TADOQuery(Application);
	 aq->Connection = fcon ;
	 aq->SQL->Clear();
	 aq->SQL->Add(sql);
	 aq->Open();
	 if (aq->FieldByName("t")->AsInteger > 0 )
	 {
		MessageBoxA(0,"该客户有业务数据相关不能删除！","提示",MB_ICONASTERISK) ;
		delete aq;
	 }else
	 {
		sql = "delete CUST_CustomerInfo where ID = " + IntToStr(ndata->ID) ;
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		tvclient->Selected->Delete();

		lvclient->Items->Clear();
		MessageBoxA(0,"成功删除该客户！","提示",MB_ICONASTERISK) ;
		delete aq;
	 }
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::N5Click(TObject *Sender)
{
  BtnDelete->Click();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmclient::BtnFinishClick(TObject *Sender)
{
   if (ClickNode == NULL) {
		MessageBoxA(0,"请先选择要修改的客户!","提示",MB_ICONASTERISK);
		return;
   }
	struct NodeClientdata *ndata = NULL;
	ndata = (NodeClientdata*)(ClickNode->Data);
	if (ndata->Name == "普通客户") {
		MessageBoxA(0,"普通客户不能修改!","提示",MB_ICONASTERISK);
		return;
	}
	TDetaileForm *frm = new TDetaileForm(Application,2,2,IntToStr(ndata->ID) ,fcon);
	frm->ParentID = -1  ;
	frm->ShowModal();
	delete frm;
	tvclient->Items->Clear();
	ReadyData();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::BtnNewClick(TObject *Sender)
{
	N2->Click();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::N4Click(TObject *Sender)
{
 BtnFinish->Click();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::BtnAlignClick(TObject *Sender)
{
	if (ClickNode == NULL) {
		MessageBoxA(0,"请先选择要设置的客户!","提示",MB_ICONASTERISK);
		return;
   }
   struct NodeClientdata *ndata = NULL;
   ndata = (NodeClientdata*)(ClickNode->Data);
   AnsiString sql = "ALTER TABLE dbo.BS_WsaleNoteHeader DROP CONSTRAINT DF_BS_WsaleNoteHeader_VendorID ";
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->ExecSQL();
   sql = "ALTER TABLE dbo.BS_WsaleNoteHeader ADD CONSTRAINT DF_BS_WsaleNoteHeader_VendorID DEFAULT ((" + IntToStr(ndata->ID) + ")) FOR VendorID";
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->ExecSQL();
   eddefaultname->Text = ndata->Name;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {     //新单
		BtnNew->Click();
	}
	if (Key == VK_F3) {     //修改
		BtnFinish->Click();
	}
	if (Key == VK_F5) {     //删除
		BtnDelete->Click();
	}
	if (Key == VK_F6) {     //设置为默认开单客户
		BtnAlign->Click();
	}
	if (Key == VK_F7) {     //导入
		BtnImport->Click();
	}
	if (Key == VK_F8) {     //导出
		BtnExport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		BtnView->Click();
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


void __fastcall Tfrmclient::BtnImportClick(TObject *Sender)
{
	AnsiString sql;
	sql = "select * from CUST_CustomerInfo where 1 = 2";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	TFormCousImport *frm = new TFormCousImport(Application,query,2);
	frm->Show();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::N7Click(TObject *Sender)
{
	querywhere = false;
	tvclient->Items->Clear();
	ReadyData();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::BtnViewClick(TObject *Sender)
{
	Tfrmclientquery * frm = new Tfrmclientquery(Application);
	if (mrOk == frm->ShowModal()) {
		querywhere = true;
		sqlwhere = frm->edclientname->Text;
		tvclient->Items->Clear();
		ReadyData();
	}
}
//---------------------------------------------------------------------------
//Excel导出函数
bool Tfrmclient::DbgridToExcel1()
{
	AnsiString temptext,path;

	savedlg->FileName = "客户资料";
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(savedlg->FileName .c_str()  );
		Name = ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
	else
	{
		return false;
	}
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   //iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	temptext = ",,,客户资料";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext  = "\n客户名称,父客户,联系人,地址,电话,邮编,传真,业务员,地区";
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int idx,next;
	AnsiString parentname;

	TTreeNode  *aNode=NULL;
	TTreeNode  *bNode=NULL;
	TTreeNode  *pNode=NULL;
	struct NodeClientdata *ndata = NULL;

	for(aNode = tvclient->Items->GetFirstNode(); aNode!=NULL ;)
	{
		temptext = "\n";
		ndata = (NodeClientdata*)(aNode->Data);
		temptext = temptext + ndata->Name + ",无," + ndata->contact + "," + ndata->address + "," + ndata->telephone + "," + ndata->code + "," + ndata->fax + "," + ndata->saleman + "," + ndata->local;
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

		parentname = ndata->Name ;
		bNode = aNode->getFirstChild();
		while(bNode != NULL)
		{

			temptext = "\n";
			ndata = (NodeClientdata*)(bNode->Data);
			temptext = temptext + ndata->Name + "," + parentname + ndata->contact + "," + ndata->address + "," + ndata->telephone + "," + ndata->code + "," + ndata->fax + "," + ndata->saleman + "," + ndata->local;
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

			bNode = bNode->getNextSibling();
		}
		aNode=aNode->getNextSibling();
	}

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclient::BtnExportClick(TObject *Sender)
{
	DbgridToExcel1();
}
//---------------------------------------------------------------------------


