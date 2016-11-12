//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CheckStockForm.h"
#include "NoteCode.h"
 #include "pdutil.h"
  #include "BookstackMngForm.h"
   #include "storageadmin.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma link "RzGrids"
#pragma link "IWBaseControl"
#pragma link "IWBaseHTMLControl"
#pragma link "IWControl32"
#pragma link "IWDBGrids32"
#pragma link "IWGrids32"
#pragma link "IWVCLBaseControl"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "MDIChild"
#pragma resource "*.dfm"
TfrmCheckStock *frmCheckStock;
//---------------------------------------------------------------------------
__fastcall TfrmCheckStock::TfrmCheckStock(TComponent* Owner)
	: TfrmMDIChild(Owner)
{        m_module = MTStore;
    	dtp1->Date=dtp1->Date .CurrentDate();
		dtp2->Date=dtp2->Date .CurrentDate();
}
//---------------------------------------------------------------------------
void TfrmCheckStock::Init(TApplication* app, TADOConnection* con)
{
		app1=app;
	  TfrmMDIChild::Init(app, con);
		this->flag=false;
		   // ShowMessage(cbbNum->Text);
			 con1=con;
		   dsCheckStock->Connection = con;
		   dscheck->Connection=con;
		   cmdCreate->Connection=con;
		   cmd1->Connection=con;
		   dsqryinventory->Connection=con;
		   dsinventory->Connection=con;

		 qryName->Connection = con;
		qryName->SQL->Add("select Name from STK_BookstackInfo");
		qryName->Open();
		qryName->First();
		 // cbbNum->ClearSelection();
	 while (!qryName->Eof)
	 {         cbbNum->Items->Add(qryName->FieldByName("Name")->AsString);
		qryName->Next();
	 }

		 if (qryName->RecNo==1) {
		   ShowMessage("你没有添加库位，请先添加库位！");

	 Application = app;
	TfrmBookstackMng* frm1 = new TfrmBookstackMng(Application);
	frm1->Init(Application, con);

	  }
	 qryName->Close();
			if (dsStore->Active)
	{
		dsStore->Active = false;
	}
		String   sql1;
		dsStore->Connection = con;
	   sql1 = "select top 1 id,name from SYS_StorageInfo";
		dsStore->CommandText = sql1;
		dsStore->Active = true;

		dscheck->Connection=con;
		if (dscheck->Active) {
			dscheck->Active=false;
		}
		dscheck->CommandText="select * from STK_StockInventories_temp order by id desc ";
		  dscheck->Active=true;
		   if (!dscheck->IsEmpty()) {
				edtName1->Text=dscheck->FieldByName("NoteCode")->AsString;

						RzEdit2->Visible=true;


				cbbNum->Visible=false;
				RzEdit2->Text=dscheck->FieldByName("STK_BookstackInfoName")->AsString;
		   }



}




void __fastcall TfrmCheckStock::RzEdit1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN)
	{

	   if(RzEdit2->Visible==true||flag)
		{
		if (dsCheckStock->Active)
			{
			dsCheckStock->Active = false;
			}
			 String sql;

			if (cbbType->Text=="条码") {

			sql = "select STK_BookInfo.id,CUST_CustomerInfo.Name as CUSName,STK_BookInfo.id,Barcode,BS_BookCatalog.Name,ISBN,Author,FullName,PressCount,Amount from STK_BookInfo left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join CUST_CustomerInfo on SupplierID=CUST_CustomerInfo.id where STK_BookInfo.BkstackID=(select id from STK_BookstackInfo  where Name='"+RzEdit2->Text+"') and State=0 and Amount>0 and Barcode like '%"+RzEdit1->Text+"%' order by BS_BookCatalog.Name";
			}
			else if (cbbType->Text=="作者") {
				sql = "select STK_BookInfo.id,CUST_CustomerInfo.Name as CUSName,STK_BookInfo.id,Barcode,BS_BookCatalog.Name,ISBN,Author,FullName,PressCount,Amount from STK_BookInfo left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join CUST_CustomerInfo on SupplierID=CUST_CustomerInfo.id where STK_BookInfo.BkstackID=(select id from STK_BookstackInfo  where Name='"+RzEdit2->Text+"') and State=0 and Amount>0 and Author like '%"+RzEdit1->Text+"%' order by BS_BookCatalog.Name";
				}
				else if (cbbType->Text=="书名") {
				 sql = "select STK_BookInfo.id,CUST_CustomerInfo.Name as CUSName,STK_BookInfo.id,Barcode,BS_BookCatalog.Name,ISBN,Author,FullName,PressCount,Amount from STK_BookInfo left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join CUST_CustomerInfo on SupplierID=CUST_CustomerInfo.id where STK_BookInfo.BkstackID=(select id from STK_BookstackInfo  where Name='"+RzEdit2->Text+"') and State=0 and Amount>0 and BS_BookCatalog.Name like '%"+RzEdit1->Text+"%' order by BS_BookCatalog.Name";
				 }
					else if (cbbType->Text=="ISBN") {
					 sql = "select STK_BookInfo.id,CUST_CustomerInfo.Name as CUSName,STK_BookInfo.id,Barcode,BS_BookCatalog.Name,ISBN,Author,FullName,PressCount,Amount from STK_BookInfo left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join CUST_CustomerInfo on SupplierID=CUST_CustomerInfo.id where STK_BookInfo.BkstackID=(select id from STK_BookstackInfo  where Name='"+RzEdit2->Text+"') and State=0 and Amount>0 and ISBN like '%"+RzEdit1->Text+"%' order by BS_BookCatalog.Name";
					}
					else {
					 sql = "select STK_BookInfo.id,CUST_CustomerInfo.Name as CUSName,STK_BookInfo.id,Barcode,BS_BookCatalog.Name,ISBN,Author,FullName,PressCount,Amount from STK_BookInfo left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join CUST_CustomerInfo on SupplierID=CUST_CustomerInfo.id where STK_BookInfo.BkstackID=(select id from STK_BookstackInfo where Name='"+RzEdit2->Text+"') and Amount>0 order by BS_BookCatalog.Name ";
					}

			dsCheckStock->CommandText = sql;
			dsCheckStock->Active = true;


			if(dsCheckStock->RecordCount==0)
				{ShowMessage("你查找的信息不存在或者没有选择仓号");}

		 if (dsCheckStock->RecordCount>1) {
				 rzgrpbx2->Visible=true;
			 }
		 else if (dsCheckStock->RecordCount==1) {
				this->Check();

			}

	  }
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCheckStock::RzToolButton1Click(TObject *Sender)
{

		   if (rzgrpbx3->Visible==true) {
				   rzgrpbx3->Visible=false;
		   }
		   else{
		  rzgrpbx1->Visible=true;
		  edtName1->ReadOnly=true;


   if (edtnum1->ReadOnly==true&&dscheck->IsEmpty())
			{
				 if(MessageDlg("您确认开始盘点吗？", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
			  {

				 cbbNum->SetFocus();
					int storage = 7;
				String code;
				TADOQuery* qry = new TADOQuery(NULL);
				 qry->Connection=con1;
				code = NoteCode::BuildCode(qry, GetDBTime(qry), m_storageID, "STK_StockInventories", "NoteCode");
				delete qry;
				   Code1=code;
				  edtName1->Text=code;
					edtName1->ReadOnly=true;
				   cbbNum->SetFocus();
					edtnum1->ReadOnly=false;
					flag=true;
				   rzgrpbx3->Visible=false;
				   rzgrpbx1->Visible=true;

		}

  }
  else
  {ShowMessage("你可能正处于盘点中！");}
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TfrmCheckStock::cbbTypeSelect(TObject *Sender)
{
	 RzEdit1->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TfrmCheckStock::edtnum1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN&&flag)
		{
			if(MessageDlg("确认输入的本书是："+edtnum1->Text+"?", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
			{
					 int balance=0;
				 String s;
				 balance=edtnum1->Value-dsCheckStock->FieldByName("Amount")->AsInteger;
				String b=IntToStr(balance);
				if(balance>0)
				{ s="盘盈";}
				  else if(balance<0)
					{ s="盘亏";}
					else
						{ s="平衡";}


				String sql2="update STK_StockInventories_temp set ActualAmount="+edtnum1->Text+",Loss_Or_Leave='"+s+"',Balance="+b+" where id="+dscheck->FieldByName("id")->AsString;

					  sql2=sql2+";update STK_BookInfo  set State=1 where id="+dsCheckStock->FieldByName("id")->AsString;
				cmdCreate->CommandText = sql2;
				cmdCreate->Execute();


				dscheck->Refresh();

				 cbbType->SetFocus();
			}		
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCheckStock::FormClose(TObject *Sender, TCloseAction &Action)
{
	  dsqryinventory->Active=false;
	  dsCheckStock->Active=false;
	  dsStore->Active=false;
	  qryCode->Close();
	  qryName->Close();
	  dscheck->Active=false;
	  dsinventory->Active=false;
	  qryUserAuthority->Active=false;
	 Action = caFree;


}
//---------------------------------------------------------------------------

void __fastcall TfrmCheckStock::RzToolButton3Click(TObject *Sender)
{


	rzgrpbx3->Visible=true;
     	if (dsqryinventory->Active) {
		  dsqryinventory->Active=false;
	}
	String sql="select * from STK_StockInventories where datediff(d,date,'"+dtp1->Date+"')<=0 and datediff(d,date,'"+dtp2->Date+"')>=0 order by NoteCode";
	dsqryinventory->CommandText=sql;
	dsqryinventory->Active=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCheckStock::rzdbgrd2DblClick(TObject *Sender)
{
		 this->Check();

	   rzgrpbx2->Visible=false;
}
//-------------------------------盘点函数--------------------------------------------
 void TfrmCheckStock::Check()
 {

	String s1,s2,s3,s4,s5,s6,s7,s8;
	s1=dsCheckStock->FieldByName("id")->AsString;
	s2=dsCheckStock->FieldByName("Barcode")->AsString;
	s3=dsCheckStock->FieldByName("Name")->AsString;
	s4=dsCheckStock->FieldByName("ISBN")->AsString;
	s5=dsCheckStock->FieldByName("Author")->AsString;
	s6=dsCheckStock->FieldByName("FullName")->AsString;
	s7=dsCheckStock->FieldByName("PressCount")->AsString;
	s8=dsCheckStock->FieldByName("Amount")->AsString;
	if (s1=="") {
        s1="0";
	}
		if (s2=="") {
		s2=" ";
	}
		if (s3=="") {
		s3=" ";
	}
		if (s4=="") {
		s4=" ";
	}
			if (s5=="") {
		s5=" ";
	}
			if (s6=="") {
		s6=" ";
	}
		if (s7=="") {
		s7=" ";
	}
		if (s8=="") {
		s8="0";
	}

	  if (Code1=="") {
			Code1=edtName1->Text;
	  }

		String sql2="insert into STK_StockInventories_temp(STK_BookInfoID,Barcode,BookName,ISBN,Author,Pressname,ShouldAmount,STK_BookstackInfoName,NoteCode)values("+s1+",'"+s2+"','"+s3+"','"+s4+"','"+s5+"','"+s6+"',"+s8+",'"+cbbNum->Text+"',"+Code1+")";
   
	cmdCreate->CommandText = sql2;
	cmdCreate->Execute();
		if (dscheck->Active)
					{
			dscheck->Active = false;
			}
			String sql1="select * from STK_StockInventories_temp order by id desc";
			dscheck->CommandText = sql1;
			dscheck->Active = true;
	   edtnum1->SetFocus();

 }
void __fastcall TfrmCheckStock::cbbNumSelect(TObject *Sender)
{
	  cmd1->CommandText="update STK_BookstackInfo set State=1 where Name='"+cbbNum->Text+"'";
	  cmd1->Execute();
	  cbbType->SetFocus();
	  RzEdit2->Visible=true;
	  RzEdit2->Text=cbbNum->Text;
	  RzEdit2->ReadOnly=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCheckStock::RzToolButton6Click(TObject *Sender)
{       if (CheckOperateAuthority()) {
				if(MessageDlg("确认盘点作废吗?", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
				  {
					String sql="TRUNCATE TABLE STK_StockInventories_temp";
					sql=sql+";update STK_BookInfo  set State=0";
					 cmd1->CommandText = sql;
					 cmd1->Execute();
					 Close();
				  }
		  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCheckStock::RzToolButton5Click(TObject *Sender)
{
		if(MessageDlg("确认保存盘点吗?", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
		 {
			String sql="insert STK_StockInventories (STK_BookInfoID,Barcode,BookName,ISBN,Author,Pressname,PressCount,ShouldAmount,ActualAmount,STK_BookstackInfoName,Loss_Or_Leave,Balance,date,NoteCode)"
			 "select STK_BookInfoID,Barcode,BookName,ISBN,Author,Pressname,PressCount,ShouldAmount,ActualAmount,STK_BookstackInfoName,Loss_Or_Leave,Balance,date,NoteCode from STK_StockInventories_temp;TRUNCATE TABLE STK_StockInventories_temp;update STK_BookstackInfo set State=0 where Name='"+RzEdit2->Text+"'";
			   sql=sql+";update STK_BookInfo  set Amount=0 where State<>1 and BkstackID=(select id from STK_BookstackInfo where Name='"+RzEdit2->Text+"')";
                sql=sql+";update STK_BookInfo  set State=0";
			 cmd1->CommandText = sql;
			cmd1->Execute();
		 }

}
//---------------------------------------------------------------------------

void __fastcall TfrmCheckStock::edtName1Click(TObject *Sender)
{
     edtName1->ReadOnly=true;
}
//---------------------------------------------------------------------------







void __fastcall TfrmCheckStock::RzToolButton2Click(TObject *Sender)
{
	  if (dsinventory->Active) {
		  dsinventory->Active=false;
	  }
	  dsinventory->Connection=con1;
	 dsinventory->CommandText="select * from STK_StockInventories";
      dsinventory->Active=true;

	  //		 rvprjct1->Open();
//		 rvprjct1->SelectReport("rava",false);
//		 rvprjct1->Execute();
//		 rvprjct1->Close();
 }
//---------------------------------------------------------------------------



void __fastcall TfrmCheckStock::RzToolButton4Click(TObject *Sender)
{
	  Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmCheckStock::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	      		if (Key==0x1B) {   //esc
			this->RzToolButton4->Click();

		}

			if (Shift.Contains(ssCtrl)&&Key==65) {   //A
			this->RzToolButton1->Click();

		}
				if (Shift.Contains(ssCtrl)&&Key==68) {   //D
			this->RzToolButton6->Click();

		}
	    		if (Shift.Contains(ssCtrl)&&Key==81) {   //Q
			this->RzToolButton3->Click();

		}
		if (Shift.Contains(ssCtrl)&&Key==83) {  //S
			  this->RzToolButton5->Click();

		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCheckStock::dtp1Change(TObject *Sender)
{
	           this->RzToolButton3->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCheckStock::dtp2Change(TObject *Sender)
{
	      this->RzToolButton3->Click();
}
//---------------------------------------------------------------------------

