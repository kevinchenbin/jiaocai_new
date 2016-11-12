//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "storagelocal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmstorelocal *frmstorelocal;
//---------------------------------------------------------------------------
__fastcall Tfrmstorelocal::Tfrmstorelocal(TComponent* Owner,TADOConnection* con,LandInfo* li)
	: TForm(Owner)
{
  aquery->Connection = con;
  aquerylocal->Connection = con;
  userInfo.app = li->app ;
  userInfo.con = li->con ;
  userInfo.userID = li->userID ;
  userInfo.storageID = li->storageID ;
  userInfo.UserName = li->UserName;
  userInfo.FormatStr = li->FormatStr;
  adosp->Connection = con;
  OperModal = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmstorelocal::BtnNewClick(TObject *Sender)
{
  String TableName = "STK_Bookstackinfo";
  int maxid = 0;

  if ((tvlocal->Selected == NULL)||(tvlocal->Selected->Parent != NULL)) {

		MessageBox(0,"没有选择店名","库位管理",MB_ICONASTERISK);

  }else
  {

	BtnNew->Enabled = false;
	Btnmodify->Enabled = false;
	BtnSave->Enabled = true;

	edtbk->Enabled  = True;
	edtname->Enabled = True;

	edtbk->Text = "";
	edtname->Text = "";
	edtcode ->Text = "";
	adosp->ProcedureName = "GetMaxID";    //最大值
	adosp->Parameters->Clear();
	adosp->Parameters->CreateParameter("@TableName",ftString,pdInput,TableName.Length(), TableName);
		adosp->Parameters->CreateParameter("@MaxID",ftInteger ,pdOutput ,sizeof(int),maxid);
	adosp->ExecProc();
	if (adosp->Parameters->ParamByName("@MaxID")->Value != NULL) {
		edtcode->Text =  adosp->Parameters->ParamByName("@MaxID")->Value ;
		OperModal = 1;
		edtname->SetFocus();
		}else
		{
			BtnNew->Enabled = true;
	Btnmodify->Enabled = true;
	BtnSave->Enabled = false;

	edtbk->Enabled  = false;
	edtname->Enabled = false;

		}



  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrmstorelocal::BtnSaveClick(TObject *Sender)
{
	TTreeNode * Node;
	SNodeData *SNode;
	LNodeData *LNode;
	AnsiString sql;
	LNodeData *Ldata;


			edtbk->Enabled = false;
			edtname->Enabled = false;
		  if (OperModal == 2) {        //修改模式
				if ((tvlocal->Selected == NULL)||(tvlocal->Selected->Parent == NULL)) {
				MessageBox(0,"没有选择库位","库位管理",MB_ICONASTERISK);
			 }else
			{
				if (tvlocal->Selected == "默认库位") {

				  MessageBox(0,"不能修改默认库位！","库位管理",MB_ICONASTERISK);
				  return;
				}
				sql = "update STK_Bookstackinfo set type = 1,Name = '" +edtname->Text.Trim() + "',bk='" +edtbk->Text.Trim();
				sql = sql + "' where ID = '" + edtcode->Text.Trim()+ "'" ;
				aquery->Close();
				aquery->SQL->Clear();
				aquery->SQL->Add(sql);
				if (aquery->ExecSQL()==1){
					Node = tvlocal->Selected ;
					Ldata = (LNodeData *)Node->Data;
					Ldata->LName  =	edtname->Text;
					Ldata->LID = StrToInt(edtcode->Text) ;
					Ldata->Lbk = edtbk->Text;
					tvlocal->Selected->Text = edtname->Text;
					BtnSave->Enabled = false;
					BtnNew->Enabled = true;
                    Btnmodify->Enabled = true;
					MessageBoxA(0,"修改成功!","库位管理",MB_ICONASTERISK);
					

				}else
				{
                   	BtnSave->Enabled = false;
					BtnNew->Enabled = true;
                    Btnmodify->Enabled = true;
				   MessageBoxA(0,"修改失败!","库位管理",MB_ICONASTERISK);
				}

			  }

		  }  else if (OperModal == 1)

			{                                   //添加模式

														   //取出结点信息


					 sql = "insert into STK_Bookstackinfo (Name,StgID,state,type,bk)";
					 sql = sql + " values ('" + edtname->Text.Trim() + "','" + userInfo.storageID +"',1,2,'" ;
					 sql = sql +  edtbk->Text.Trim() + "')";

					aquery->Close();                        //保存到数据库
					aquery->SQL->Clear();
					aquery->SQL->Add(sql);
					aquery->ExecSQL() ;                       //添加新的结点

				   //	memset(&LNode,0,sizeof(LNode));
					LNode = new  LNodeData();
					LNode->SID =  userInfo.storageID;
					LNode->LName = edtname->Text.Trim();
					LNode->Lbk =  edtbk->Text.Trim();
					tvlocal->Items->AddChildObjectFirst(tvlocal->Selected ,edtname->Text ,LNode);
					BtnSave->Enabled = false;
					BtnNew->Enabled = true;
		  }



}
//---------------------------------------------------------------------------
void __fastcall Tfrmstorelocal::FormCreate(TObject *Sender)
{
		  // TTreedNode * Note;
	   AnsiString sql,sqllocal ;
	   LNodeData *Ldata ;
	   SNodeData *Sdata;
	   TTreeNode * Node;


	   sql = "select ID,Name from SYS_storageinfo where ID = " + IntToStr(userInfo.storageID)  ;
	   sqllocal = "select ID,name,stgid,bk from STK_Bookstackinfo";
	   aquerylocal->Close();
	   aquerylocal->SQL->Clear();
	   aquerylocal->SQL->Add(sqllocal);
	   aquerylocal->Open();

	   aquery->Close();
	   aquery->SQL->Clear();
	   aquery->SQL->Add(sql);
	   aquery->Open();
	   aquery->First();
	   while(!aquery->Eof )
	   {
		  Sdata = new SNodeData();
		  Sdata->SID =  aquery->FieldByName("ID")->AsInteger ;
		  Sdata->SName = aquery->FieldByName("Name")->AsString ;
		  Node = tvlocal->Items->AddObject(NULL,Sdata->SName,Sdata);
		  aquerylocal->First();
		  while(!aquerylocal->Eof)
		  {
				if (aquerylocal->FieldByName("Stgid")->AsInteger  == Sdata->SID) {
					 Ldata = new LNodeData();
					 Ldata->SID  =aquerylocal->FieldByName("Stgid")->AsInteger ;
					 Ldata->LID = aquerylocal->FieldByName("ID")->AsInteger ;
					 Ldata->LName =  aquerylocal->FieldByName("name")->AsString ;
					 Ldata->Lbk = aquerylocal->FieldByName("bk")->AsString ;
					 tvlocal->Items->AddChildObject(Node,Ldata->LName ,Ldata);
					}
			aquerylocal->Next();
		  }

		 aquery->Next();
	   }

}
//---------------------------------------------------------------------------
void __fastcall Tfrmstorelocal::tvlocalClick(TObject *Sender)
{
   LNodeData *Ldata;
   TTreeNode * Node;              //取出数据
   if ((tvlocal->Selected != NULL)&&(tvlocal->Selected->Parent != NULL)) {
	   Node = tvlocal->Selected ;
	   Ldata = (LNodeData *)Node->Data;
	   edtname->Text = Ldata->LName ;
	   edtcode->Text = Ldata->LID ;
	   edtbk->Text = Ldata->Lbk ;
	   BtnNew->Enabled = true;
	   Btnmodify->Enabled = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstorelocal::BtnmodifyClick(TObject *Sender)
{
  edtbk->Enabled = true;
  edtname->Enabled = true;
  Btnmodify->Enabled = false;
  BtnNew->Enabled = false;
  BtnSave->Enabled = true;
  OperModal = 2;

}
//---------------------------------------------------------------------------

void __fastcall Tfrmstorelocal::BtnDeleteClick(TObject *Sender)
{
  AnsiString sql;
	   if ((tvlocal->Selected != NULL)&&(tvlocal->Selected->Parent != NULL)) {

			if (MessageBoxA(0,"确认要删除吗？","库位管理",MB_OKCANCEL|MB_ICONQUESTION)==1)     //有问题
			{
			if (tvlocal->Selected->Text == "默认库位") {
				 MessageBoxA(0,"默认库位，不能删除!","库位管理",MB_ICONASTERISK);
				return;

			}

			sql = "select value from sys_bsset where name = 'deletestack'";
            aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->Open();
			if (!aquery->FieldByName("value")->AsBoolean ) {
            	sql = "select count (*) as d from STK_BookInfo where bkstackid =  " + edtcode->Text.Trim() ;
				aquery->Close();
				aquery->SQL->Clear();
				aquery->SQL->Add(sql);
				aquery->Open();
				if (aquery->FieldByName("d")->AsInteger > 0 ) {
					MessageBoxA(0,"库位有引用，不能删除!","库位管理",MB_ICONASTERISK);
					return;
				}
			}

			sql = "delete STK_Bookstackinfo where ID= '" + edtcode->Text.Trim() + "'";
			aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->ExecSQL();
			tvlocal->Selected->Delete();
			edtbk->Text = "";
			edtname->Text = "";
			}else
			{

			}

   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstorelocal::BtnExitClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstorelocal::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {     //添单
		BtnNew->Click();
	}
	if (Key == VK_F3) {     //修改
		Btnmodify->Click();
	}
	if (Key == VK_F4) {     //保存
		BtnSave->Click();
	}
	if (Key == VK_F5) {     //删除
		BtnDelete->Click();
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

void __fastcall Tfrmstorelocal::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstorelocal::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

