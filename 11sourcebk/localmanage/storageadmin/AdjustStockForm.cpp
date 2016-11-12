//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AdjustStockForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzDBGrid"
#pragma link "MDIChild"
#pragma resource "*.dfm"
TfrmAdjustStock *frmAdjustStock;
//---------------------------------------------------------------------------
__fastcall TfrmAdjustStock::TfrmAdjustStock(TComponent* Owner)
	: TfrmMDIChild(Owner)
{    m_module = MTStore;
}
//---------------------------------------------------------------------------
void TfrmAdjustStock::Init(TApplication* app, TADOConnection* con)
{
     TfrmMDIChild::Init(app, con);
			app1=app;
           con1=con;
		cmdwhole->Connection=con;

	   this->Caption="库位调整";

	if (dsStoreName->Active)
	{
		dsStoreName->Active = false;
	}
		String   sql;
		dsStoreName->Connection = con;
	   sql = "select top 1 id,name from SYS_StorageInfo";
		dsStoreName->CommandText = sql;
		dsStoreName->Active = true;

		 qryName->Connection = con;
		qryName->SQL->Add("select Name from STK_BookstackInfo");
		qryName->Open();
		qryName->First();
		  cbbNum->ClearSelection();
			cbbNum->Clear();
			 cbbNum1->Clear();
	 while (!qryName->Eof)
	 {         cbbNum->Items->Add(qryName->FieldByName("Name")->AsString);
				cbbNum1->Items->Add(qryName->FieldByName("Name")->AsString);
		qryName->Next();
	 }
	 qryName->Close();

		dsAdjustStock->Connection = con;



}

void __fastcall TfrmAdjustStock::RzEditInforKeyPress(TObject *Sender, wchar_t &Key)

{
		if (Key==VK_RETURN)
	{
		  Query();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmAdjustStock::cbbTypeSelect(TObject *Sender)
{
				   RzEditInfor->SetFocus();

}
//---------------------------------------------------------------------------
void TfrmAdjustStock::Query()
{
		if (dsAdjustStock->Active)
	{
		dsAdjustStock->Active = false;
	}
	String sql;

	if (cbbType->Text=="库位编码") {

		   sql="select STK_BookstackInfo.id,BkcatalogID,STK_BookInfo.ID as bkid,STK_BookInfo.BkstackID as BkstackID,ISBN,BS_BookCatalog.Name as BookName,STK_BookstackInfo.Name as BsINforName,StgID,BS_BookType.Name as BookTypeName,Amount,Price,FullName from STK_BookInfo left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_BookType on smallBookTypeID=BS_BookType.id left join BS_PressInfo on PressID=BS_PressInfo.id where Amount>0 and StgID like '%"+RzEditInfor->Text+"%'";
	}
		else if (cbbType->Text=="类别")
		{
			sql="select STK_BookstackInfo.id,BkcatalogID,STK_BookInfo.ID as bkid,STK_BookInfo.BkstackID as BkstackID,ISBN,BS_BookCatalog.Name as BookName,STK_BookstackInfo.Name as BsINforName,StgID,BS_BookType.Name as BookTypeName,Amount,Price,FullName from STK_BookInfo left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_BookType on smallBookTypeID=BS_BookType.id left join BS_PressInfo on PressID=BS_PressInfo.id  where Amount>0 and BS_BookType.Name like '%"+RzEditInfor->Text+"%'";
		 }
			else if (cbbType->Text=="出版社")
				{
				sql="select STK_BookstackInfo.id,BkcatalogID,STK_BookInfo.ID as bkid,STK_BookInfo.BkstackID as BkstackID,ISBN,BS_BookCatalog.Name as BookName,STK_BookstackInfo.Name as BsINforName,StgID,BS_BookType.Name as BookTypeName,Amount,Price,FullName from STK_BookInfo left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_BookType on smallBookTypeID=BS_BookType.id left join BS_PressInfo on PressID=BS_PressInfo.id  where Amount>0 and FullName like '%"+RzEditInfor->Text+"%'";
				}
				 else if (cbbType->Text=="单品")
				{
				 sql="select STK_BookstackInfo.id,BkcatalogID,STK_BookInfo.ID as bkid,STK_BookInfo.BkstackID as BkstackID,ISBN,BS_BookCatalog.Name as BookName,STK_BookstackInfo.Name as BsINforName,StgID,BS_BookType.Name as BookTypeName,Amount,Price,FullName from STK_BookInfo left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_BookType on smallBookTypeID=BS_BookType.id left join BS_PressInfo on PressID=BS_PressInfo.id  where Amount>0 and BS_BookCatalog.Name like '%"+RzEditInfor->Text+"%'";
				}
					else
					 {
					sql="select STK_BookstackInfo.id,BkcatalogID,STK_BookInfo.ID as bkid,STK_BookInfo.BkstackID as BkstackID,ISBN,BS_BookCatalog.Name as BookName,STK_BookstackInfo.Name as BsINforName,StgID,BS_BookType.Name as BookTypeName,Amount,Price,FullName from STK_BookInfo left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_BookType on smallBookTypeID=BS_BookType.id left join BS_PressInfo on PressID=BS_PressInfo.id  where Amount>0";
					}
	dsAdjustStock->CommandText = sql;
	dsAdjustStock->Active = true;
	if(!dsAdjustStock->IsEmpty())
            cbbNum1->SetFocus();

}
void __fastcall TfrmAdjustStock::cbb2Select(TObject *Sender)
{
       cbbNum1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAdjustStock::cbbNum1Select(TObject *Sender)
{


	   if(MessageDlg("您确认要移动到"+cbbNum1->Text+"库吗？", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
	   {
			if(!dsAdjustStock->IsEmpty())
			{
				  dsAdjustStock->First();
				 while (!dsAdjustStock->Eof){
				String sql="update STK_BookInfo set BkstackID=(select id from STK_BookstackInfo where Name='"+cbbNum1->Text+"') where STK_BookInfo.ID="+dsAdjustStock->FieldByName("bkid")->AsString+";declare @id1 int;"
					"set @id1=(select top 1 id from STK_BookInfo);insert into STK_BkstackAdjustNote (FromID,ToID,Amount,Remark) values ("+dsAdjustStock->FieldByName("bkid")->AsString+",@id1,"+dsAdjustStock->FieldByName("Amount")->AsString+",'整体移动到库:"+dsAdjustStock->FieldByName("Amount")->AsString+"，类型为："+cbbType->Text+",条件为："+RzEditInfor->Text+"')";

				 cmdwhole->CommandText = sql;
				cmdwhole->Execute();
				 dsAdjustStock->Next();
				 }
				  Query();
				ShowMessage("恭喜你！成功调整到"+cbbNum1->Text+"库");
				RzEditInfor->Clear();
				edtSingle->Clear();
				cbbNum->Text="选择库位";
				cbbNum1->Text="选择库位";

			}
			else
			ShowMessage("温馨提示！操作不成功！");

	   }

}
//---------------------------------------------------------------------------


void __fastcall TfrmAdjustStock::cbbNumSelect(TObject *Sender)
{        int id=dsAdjustStock->FieldByName("bkid")->AsInteger;
		String s3=dsAdjustStock->FieldByName("bkid")->AsString;

	  if (id==0) {
				edtSingle->Visible=true;
				lbl6->Visible=true;
			  edtSingle->SetFocus();
		}
		else
		{
            		 if(MessageDlg("您确认要移动到"+cbbNum->Text+"库吗？", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
			 {
				if (cbbNum->Text!="选择库位")
				{


					if(!dsAdjustStock->IsEmpty())
				{
				//-------------- 得到所选仓名的id-------------------
						if (dsetID->Active)
								{
							dsetID->Active = false;
								}
						String   sq;
						dsetID->Connection = con1;
					sq = "select id from STK_BookstackInfo where Name='"+cbbNum->Text+"'";
					dsetID->CommandText = sq;
					dsetID->Active = true;
				   String sql="update STK_BookInfo set BkstackID=(select id from STK_BookstackInfo where Name='"+cbbNum->Text+"') where STK_BookInfo.ID="+dsAdjustStock->FieldByName("bkid")->AsString+";declare @id1 int;"
					"set @id1=(select top 1 id from STK_BookInfo);insert into STK_BkstackAdjustNote (FromID,ToID,Amount,Remark) values ("+dsAdjustStock->FieldByName("bkid")->AsString+",@id1,"+dsAdjustStock->FieldByName("Amount")->AsString+",'整体移动到库:"+cbbNum1->Text+"，类型为："+cbbType->Text+",条件为："+RzEditInfor->Text+"')";
				 cmdwhole->CommandText = sql;
					cmdwhole->Execute();
						  Query();
					ShowMessage("恭喜你！成功调整到"+cbbNum->Text+"库");
					 RzEditInfor->Clear();
					 edtSingle->Clear();
					 cbbNum->Text="选择库位";
					  cbbNum1->Text="选择库位";


					}

				}
			   else
				  ShowMessage("温馨提示：操作不成功，请查看是否选择了库位！");
			}

		}


}
//---------------------------------------------------------------------------

void __fastcall TfrmAdjustStock::edtSingleKeyPress(TObject *Sender, wchar_t &Key)

{
         	if (Key==VK_RETURN)
	{
		 int count=edtSingle->Value;
		 int Amount1=dsAdjustStock->FieldByName("Amount")->AsInteger;
		  if(count>0&&count<=Amount1)
		   {
			   Amount1=Amount1-count;
			   String s1=IntToStr(Amount1);
				 // ShowMessage(s1);
			 if(MessageDlg("您确认要移动到"+cbbNum->Text+"库吗？", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
			 {
				if (cbbNum->Text!="选择库位")
				{


					if(!dsAdjustStock->IsEmpty())
				{
				//-------------- 得到所选仓名的id-------------------
						if (dsetID->Active)
								{
							dsetID->Active = false;
								}
						String   sq;
						dsetID->Connection = con1;
					sq = "select id from STK_BookstackInfo where Name='"+cbbNum->Text+"'";
					dsetID->CommandText = sq;
					dsetID->Active = true;
					//  ShowMessage(cbbNum->Text);
				   //	 ShowMessage(dsetID->FieldByName("id")->AsString);

					String sql="update STK_BookInfo set Amount= "+s1+"where id="+dsAdjustStock->FieldByName("ID")->AsString+"; insert into STK_BookInfo (Amount,BkcatalogID,BkstackID)values("+edtSingle->Text+","+dsAdjustStock->FieldByName("BkcatalogID")->AsString+","+dsetID->FieldByName("id")->AsString+")";
					cmdwhole->CommandText = sql;
					cmdwhole->Execute();
					sql="declare @id1 int;"
					"set @id1=(select top 1 id from STK_BookInfo);"
					"insert into STK_BkstackAdjustNote (FromID,ToID,Amount) values ("+dsAdjustStock->FieldByName("ID")->AsString+",@id1,"+edtSingle->Text+")";
					 cmdwhole->CommandText = sql;
					 Query();
					cmdwhole->Execute();
					ShowMessage("恭喜你！成功调整到"+cbbNum->Text+"库");
					 RzEditInfor->Clear();
					 edtSingle->Clear();
					 cbbNum->Text="选择库位";
					  cbbNum1->Text="选择库位";


					}

				}
			   else
				  ShowMessage("温馨提示：操作不成功，请查看是否选择了库位！");
			}
	   }
	   else
		 ShowMessage("温馨提示：你输入的数字必须大于0，且不能多于库存数量，请检查！");

		 
	}
	
}
//---------------------------------------------------------------------------

void __fastcall TfrmAdjustStock::RzToolButton10Click(TObject *Sender)
{
	 Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAdjustStock::FormClose(TObject *Sender, TCloseAction &Action)

{
		 dsAdjustStock->Active=false;
		 dsStoreName->Active=false;
		 dsetwhole->Active=false;
		 qryName->Close();
		 dsetID->Active=false;
		Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAdjustStock::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
			if (Key==0x1B) {   //esc
			this->RzToolButton10->Click();

		}
}
//---------------------------------------------------------------------------

