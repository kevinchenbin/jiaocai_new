//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PayMentClearForm.h"
#include "NoteCode.h"
 #include "pdutil.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzSpnEdt"
#pragma link "RzLine"
#pragma resource "*.dfm"
TfrmPayMentCle *frmPayMentCle;
//---------------------------------------------------------------------------
__fastcall TfrmPayMentCle::TfrmPayMentCle(TComponent* Owner)
	: TfrmMDIChild(Owner)
{  	m_module = MTFinance;
}
//---------------------------------------------------------------------------
void TfrmPayMentCle::Init(TApplication* app, TADOConnection* con)
{
		TfrmMDIChild::Init(app, con);
		this->Caption="付款结算";
		con1=con;
		  newdocflag=false;
		  flag1=true;
		dsSupplyInit->Connection=con;
		dsPurchase->Connection=con;
		qrySupply->Connection=con;
		cmdState->Connection=con;
		qryTotal->Connection=con;
		dsNewDoc->Connection=con;
		dsQuery->Connection=con;
		 dscheck->Connection=con;
		 cmdcheck->Connection=con;

		qrySupply->SQL->Add("select id,Name from CUST_CustomerInfo where type=1");
		qrySupply->Open();
		qrySupply->First();
		 while (!qrySupply->Eof)
		 {
			cbbType->Items->Add(qrySupply->FieldByName("Name")->AsString);
			qrySupply->Next();
		 }
		qrySupply->Close();

}


void __fastcall TfrmPayMentCle::cbbTypeSelect(TObject *Sender)
{
	  if (newdocflag)
	   {
			  cmdNewDocuments->CommandText="update FN_EndMoneyDocuments set CustmerName='"+cbbType->Text+"' where MoneyCode="+code;
			   cmdNewDocuments->Execute();
					cbb1->SetFocus();


		//-------------清除lst里面的数据,并初始化lst--------------
			lst->Repaint();
			int count=lst->RowCount;
			for (int i = 0; i < count; i++) {
			   lst->Rows[i]->Clear();
			}
			 lst->RowCount=1;
			lst->Cells[0][0]="进货账单";
			lst->Cells[1][0]="应结金额";

					if(dsSupplyInit->Active)
				{
					  dsSupplyInit->Active=false;
				}
				String sql;
				sql="select BookstoreLessBusiness,Balance from  CUST_CustomerInfo where Type=1 and Name='"+cbbType->Text+"'";
				dsSupplyInit->CommandText = sql;
				dsSupplyInit->Active = true;
				  customBalance=dsSupplyInit->FieldByName("Balance")->AsFloat;
					if(dsPurchase->Active)
				{
					  dsPurchase->Active=false;
				}
				String sql1;
				sql1="select CASE State When 0 Then '未结' when 1 then '已结' else '审核中' End AS  State,id,StgNtCode,HdTime,TotalFixedPrice,TotalDiscountedPrice,AddCosts,Checked,NoChecked,Remarks from BS_StorageNoteHeader where SupplierID=(select id from CUST_CustomerInfo where type=1 and Name='"+cbbType->Text+"') and State<>1";
				dsPurchase->CommandText = sql1;
				dsPurchase->Active = true;
		//-----------------计算总应付----------------
				// ShowMessage(cbbType->Text);
				 String sql2="select NoChecked from BS_StorageNoteHeader where SupplierID=(select id from CUST_CustomerInfo where Type=1 and Name='"+cbbType->Text+"')";
				 qryTotal->SQL->Add(sql2);
				qryTotal->Open();
				qryTotal->First();
				float total=0;
				edt1->Text="￥";
				String   total1;

				 while (!qryTotal->Eof)
				 {

				 total=total+qryTotal->FieldByName("NoChecked")->AsFloat;
				 qryTotal->Next();

				 }

				 total=total+dsSupplyInit->FieldByName("BookstoreLessBusiness")->AsFloat;
				   total1=FloatToStr(total);
				 edt1->Text=total1;
				   qryTotal->SQL->Clear();
				 qryTotal->Close();


	  }
	else
	 {ShowMessage("请先点添加结款单，生成新的结款单");}
}
//---------------------------------------------------------------------------
 //select StgNtCode,HdTime,sum(BS_StorageNote.Amount) as total,sum(Price*BS_StorageNote.Amount) as amount from BS_StorageNoteHeader left join BS_StorageNote on StgNtHeaderID=BS_StorageNoteHeader.id left join STK_BookInfo on STK_BookInfo.id=BkInfoID left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join CUST_CustomerInfo on CUST_CustomerInfo.id=BS_StorageNoteHeader.SupplierID where Type=1 group by StgNtCode

void __fastcall TfrmPayMentCle::rzdbgrd1DblClick(TObject *Sender)
{
 if(newdocflag){
	 if (cbb1->Text=="付款退款"||cbb1->Text=="余额结款")
	 {


	  String State=Trim(dsPurchase->FieldByName("State")->AsString);

		if (State=="审核中")
		  {ShowMessage("此单包含在历史结款单中，尚未审核，请审核后再进行付款操作！");}
		 else
		 {
			String s=dsPurchase->FieldByName("StgNtCode")->AsString;
			String NoCheched=dsPurchase->FieldByName("NoChecked")->AsString;

			int count=lst->RowCount;
			int i=1;
			for ( ; i <count ; i++) {
				  if(lst->Cells[0][i]==s)
				   {ShowMessage("该单已经存在！");
					  break;
					 }
				   }
				   if (i>=count) {


					 if (cbb1->Text=="付款退款") {
						  edtMoney->SetFocus();
						 lst->RowCount=count+1;
						 lst->Cells[0][i]=s;
						 lst->Cells[1][i]=NoCheched;
						 lst->Refresh();
						 }
					 else if (cbb1->Text=="余额结款"&&flag1) {
						   float balance=customBalance-dsPurchase->FieldByName("NoChecked")->AsFloat;

							 if (balance>=0) {

							  customBalance=balance;
							 String sql="update BS_StorageNoteHeader set State=2 where StgNtCode="+dsPurchase->FieldByName("StgNtCode")->AsString+";insert into FN_EndMoneyDetails(StgNtHdcode,EndMoneyDcmcode,EntryMoney) values("+dsPurchase->FieldByName("StgNtCode")->AsString+","+edtNum->Text+","+dsPurchase->FieldByName("NoChecked")->AsString+")";
                                	cmdState->CommandText=sql;
							cmdState->Execute();
							dsPurchase->Next();
							   }

							  else {
								 flag1=false;
                                  String sql="update BS_StorageNoteHeader set State=2 where StgNtCode="+dsPurchase->FieldByName("StgNtCode")->AsString+";insert into FN_EndMoneyDetails(StgNtHdcode,EndMoneyDcmcode,EntryMoney) values("+dsPurchase->FieldByName("StgNtCode")->AsString+","+edtNum->Text+","+FloatToStr(customBalance)+")";
                                  	cmdState->CommandText=sql;
								cmdState->Execute();
								dsPurchase->Next();
							  ShowMessage("对不起，你的余额已不足！");

							 }

							 lst->RowCount=count+1;
							 lst->Cells[0][i]=s;
							 lst->Cells[1][i]=NoCheched;
							 lst->Refresh();


						  }


					}
						this->cbbType->OnSelect;
		 }

	}
else if (cbb1->Text=="预付款")

			{ShowMessage("对不起，你的结款类型是预付款，此操作不能用！");}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::RzButton1Click(TObject *Sender)
{
   if(newdocflag){
	 if (cbb1->Text=="付款退款"||cbb1->Text=="余额结款")
	 {


	  String State=Trim(dsPurchase->FieldByName("State")->AsString);

		if (State=="审核中")
		  {ShowMessage("此单包含在历史结款单中，尚未审核，请审核后再进行付款操作！");}
		 else
		 {
			String s=dsPurchase->FieldByName("StgNtCode")->AsString;
			String NoCheched=dsPurchase->FieldByName("NoChecked")->AsString;

			int count=lst->RowCount;
			int i=1;
			for ( ; i <count ; i++) {
				  if(lst->Cells[0][i]==s)
				   {ShowMessage("该单已经存在！");
					  break;
					 }
				   }
				   if (i>=count) {


					 if (cbb1->Text=="付款退款") {
						  edtMoney->SetFocus();
						 lst->RowCount=count+1;
						 lst->Cells[0][i]=s;
						 lst->Cells[1][i]=NoCheched;
						 lst->Refresh();
						 }
					 else if (cbb1->Text=="余额结款"&&flag1) {
						   float balance=customBalance-dsPurchase->FieldByName("NoChecked")->AsFloat;

							 if (balance>=0) {

							  customBalance=balance;
							 String sql="update BS_StorageNoteHeader set State=2 where StgNtCode="+dsPurchase->FieldByName("StgNtCode")->AsString+";insert into FN_EndMoneyDetails(StgNtHdcode,EndMoneyDcmcode,EntryMoney) values("+dsPurchase->FieldByName("StgNtCode")->AsString+","+edtNum->Text+","+dsPurchase->FieldByName("NoChecked")->AsString+")";
                                	cmdState->CommandText=sql;
							cmdState->Execute();
							dsPurchase->Next();
							   }

							  else {
								 flag1=false;
                                  String sql="update BS_StorageNoteHeader set State=2 where StgNtCode="+dsPurchase->FieldByName("StgNtCode")->AsString+";insert into FN_EndMoneyDetails(StgNtHdcode,EndMoneyDcmcode,EntryMoney) values("+dsPurchase->FieldByName("StgNtCode")->AsString+","+edtNum->Text+","+FloatToStr(customBalance)+")";
                                  	cmdState->CommandText=sql;
								cmdState->Execute();
								dsPurchase->Next();
							  ShowMessage("对不起，你的余额已不足！");

							 }

							 lst->RowCount=count+1;
							 lst->Cells[0][i]=s;
							 lst->Cells[1][i]=NoCheched;
							 lst->Refresh();

							 
						  }


					}
					this->cbbType->OnSelect;
		 }

	}
else if (cbb1->Text=="预付款")

			{ShowMessage("对不起，你的结款类型是预付款，此操作不能用！");}
	}
 }
//---------------------------------------------------------------------------


void __fastcall TfrmPayMentCle::RzButton3Click(TObject *Sender)
{

	  if (ARow1>0) {

	  int count= lst->RowCount;
		String sql="delete from FN_EndMoneyDetails where EndMoneyDcmcode="+edtNum->Text+" and StgNtHdcode="+lst->Cells[0][ARow1]+";update BS_StorageNoteHeader set State=0 where  StgNtCode="+lst->Cells[0][ARow1];
			  cmdState->CommandText=sql;
			  cmdState->Execute();
	  int i;
	   for (i=ARow1;i<count;i++) {
			 lst->Cells[0][i]=lst->Cells[0][i+1];
			 lst->Cells[1][i]=lst->Cells[1][i+1];
	   }

	   lst->Rows[i]->Clear();
	  lst->RowCount=count-1;
	  }

}
//---------------------------------------------------------------------------


void __fastcall TfrmPayMentCle::lstSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
		ACol1=ACol;
		ARow1=ARow;

}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::lstDblClick(TObject *Sender)
{
			  if (ARow1>0) {

	  int count= lst->RowCount;
		String sql="delete from FN_EndMoneyDetails where EndMoneyDcmcode="+edtNum->Text+" and StgNtHdcode="+lst->Cells[0][ARow1]+";update BS_StorageNoteHeader set State=0 where  StgNtCode="+lst->Cells[0][ARow1];
			  cmdState->CommandText=sql;
			  cmdState->Execute();
	  int i;
	   for (i=ARow1;i<count;i++) {
			 lst->Cells[0][i]=lst->Cells[0][i+1];
			 lst->Cells[1][i]=lst->Cells[1][i+1];
	   }

	   lst->Rows[i]->Clear();
	  lst->RowCount=count-1;
	  }

}
//---------------------------------------------------------------------------




void __fastcall TfrmPayMentCle::edtMoneyKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN&&edtNum->Text!="")
	   {   if (cbbType->Text!="全部供应商") {
				if (cbb1->Text=="付款退款")
			 {


				if(MessageDlg("是否确认输入的金额为："+edtMoney->Text+"?", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
				   {
					   String sql="update BS_StorageNoteHeader set State=2 where StgNtCode="+dsPurchase->FieldByName("StgNtCode")->AsString+";insert into FN_EndMoneyDetails(StgNtHdcode,EndMoneyDcmcode,EntryMoney) values("+dsPurchase->FieldByName("StgNtCode")->AsString+","+edtNum->Text+","+edtMoney->Text+")";
					  cmdState->CommandText=sql;
					  cmdState->Execute();
					  dsPurchase->Next();
					  edtMoney->Text="";
				   }
			}
			else  if (cbb1->Text=="预付款")
			 { //方式为预付款
				if(MessageDlg("是否确认预付款金额为："+edtMoney->Text+"?", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
				   {
				   String sql="insert into FN_EndMoneyDetails(EndMoneyDcmcode,EntryMoney) values("+edtNum->Text+","+edtMoney->Text+")";
				   cmdState->CommandText=sql;
				   cmdState->Execute();
					edtMoney->Text="";
				   }
			  }
			  else {
              ShowMessage("操作错误，请正确操作！");
			  }
       }
	 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::RzButton2Click(TObject *Sender)
{
  if (newdocflag&&edtMoney->Text!=""&&cbbType->Text!="全部供应商"&&!dsPurchase->Eof) {


				  String Mon=edtMoney->Text;
				  float Money=StrToFloat(Mon);
				  float money1=0;
				  flag=true;
				  dsPurchase->First();
				  String state;
				  while (!dsPurchase->Eof){
						state=dsPurchase->FieldByName("State")->AsString;
						state=Trim(state);
						if (state=="审核中") {
							ShowMessage("此供应商还有历史结款单没有审核，请审核后再进行结算操作");
							 flag=false;
							 break;
						}
						dsPurchase->Next();
					}
				if (flag)  //如果系统中还有包含此供应商的结款单没有审核，则不进行结算flag为true表示没有此供应商的历史借款单，可以操作
				  {
					  dsPurchase->First();
					  while (!dsPurchase->Eof)
					  {     	money1=Money-dsPurchase->FieldByName("NoChecked")->AsFloat;

							if (money1>0) {
								   Money=Money-dsPurchase->FieldByName("NoChecked")->AsFloat;
							String sql="update BS_StorageNoteHeader set State=2 where StgNtCode="+dsPurchase->FieldByName("StgNtCode")->AsString+";insert into FN_EndMoneyDetails(StgNtHdcode,EndMoneyDcmcode,EntryMoney) values("+dsPurchase->FieldByName("StgNtCode")->AsString+","+edtNum->Text+","+dsPurchase->FieldByName("NoChecked")->AsString+")";
							cmdState->CommandText=sql;
							cmdState->Execute();
							 }
							else
							{  break;}
						 dsPurchase->Next();
					  }
					  String sql1;
					  if (money1>0) {
						 sql1="update CUST_CustomerInfo set Balance=Balance+"+FloatToStr(money1)+" where Type=1 and Name='"+cbbType->Text+"'";

						 }
					  else if (money1<0) {
						   sql1="update BS_StorageNoteHeader set State=2 where StgNtCode="+dsPurchase->FieldByName("StgNtCode")->AsString+";insert into FN_EndMoneyDetails(StgNtHdcode,EndMoneyDcmcode,EntryMoney) values("+dsPurchase->FieldByName("StgNtCode")->AsString+","+edtNum->Text+","+FloatToStr(Money)+")";
						   }
					  cmdState->CommandText=sql1;
						cmdState->Execute();
				   }
				   ShowMessage("结算完毕");
			}
 }
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::RzToolButton2Click(TObject *Sender)
{

				int storage = 7;
				   code="";
				   newdocflag=true;
				TADOQuery* qry = new TADOQuery(NULL);
				qry->Connection = con1;
				code = NoteCode::BuildCode(qry, GetDBTime(qry), storage, "FN_EndMoneyDocuments", "MoneyCode");
				delete qry;
				edtNum->Text=code;
            //-------------生成新单-----------------
			 cmdNewDocuments->Connection=con1;
			 cmdNewDocuments->CommandText="insert into FN_EndMoneyDocuments (MoneyCode) values ("+code+")";
			 cmdNewDocuments->Execute();

			  //------------显示新单----------------

			   	if(dsNewDoc->Active)
		{
			  dsNewDoc->Active=false;
		}

			  dsNewDoc->CommandText="select * from FN_EndMoneyDocuments where MoneyCode="+code;
			  dsNewDoc->Active=true;
				  String date=dsNewDoc->FieldByName("date")->AsString;
				  int State=dsNewDoc->FieldByName("State")->AsInteger;
			  edt5->Text=date;
			  if (State==0) {
				   edt4->Text="未审核";
			  }
			  else
                edt4->Text="审核";
		  cbbType->SetFocus();


}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::cbb1Select(TObject *Sender)
{
	if (cbbType->Text!="全部供应商") {


	  cmdNewDocuments->CommandText="update FN_EndMoneyDocuments set ClearingType='"+cbb1->Text+"' where MoneyCode="+code;
	  cmdNewDocuments->Execute();
	   cbb2->SetFocus();
		}
		else  {ShowMessage("请先选择供应商!");}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::cbb2Select(TObject *Sender)
{   if (cbbType->Text!="全部供应商") {
			 cmdNewDocuments->CommandText="update FN_EndMoneyDocuments set Clearingstyle='"+cbb2->Text+"' where MoneyCode="+code;
			cmdNewDocuments->Execute();
	  		 edt6->SetFocus();

           	}
	else  {ShowMessage("请先选择供应商!");}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::FormClose(TObject *Sender, TCloseAction &Action)
{
	 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::RzToolButton13Click(TObject *Sender)
{
	       Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::edt6KeyPress(TObject *Sender, wchar_t &Key)
{
		   if (Key==VK_RETURN)
		   {
				 if (edt6->Text!="") {


			if (cbbType->Text!="全部供应商") {
				cmdNewDocuments->CommandText="update FN_EndMoneyDocuments set Salesman='"+edt6->Text+"' where MoneyCode="+code;
				cmdNewDocuments->Execute();
				edt3->SetFocus();
				ShowMessage("继续添加备注");
			  }
		   }
		   else
		   {  	ShowMessage("请添加业务员");}
		  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::edt3KeyPress(TObject *Sender, wchar_t &Key)
{
		if (Key==VK_RETURN)
		   {   if (edt3->Text!="") {
                    if (cbbType->Text!="全部供应商") {
				cmdNewDocuments->CommandText="update FN_EndMoneyDocuments set Remarks='"+edt3->Text+"' where MoneyCode="+code;
				cmdNewDocuments->Execute();

			   }
				  }
				  if (cbb1->Text=="付款退款") {
						ShowMessage("信息已经保存,请添加进货单据！");
				}
				  else	if (cbb1->Text=="预付款") {
						ShowMessage("信息已经保存,请输入预付款金额！");
						edtMoney->SetFocus();
				}
				  else	if (cbb1->Text=="余额结款") {
						ShowMessage("信息已经保存,请添加进货单据！");
						edtMoney->Visible=false;
				}



		   }
}
//---------------------------------------------------------------------------


void __fastcall TfrmPayMentCle::RzToolButton5Click(TObject *Sender)
{

			if(dsNewDoc->Active)
		{
			  dsNewDoc->Active=false;
		}

		  dsNewDoc->CommandText="select * from FN_EndMoneyDocuments  where State=0";
			  dsNewDoc->Active=true;
	 rzgrpbx4->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::RzButton6Click(TObject *Sender)
{
		rzgrpbx4->Visible=false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmPayMentCle::RzButton4Click(TObject *Sender)
{
   //this->check();
   this->check();
		  ShowMessage("审核完毕");
		  this->RzToolButton5->Click();
}
//--------------------反审核-------------------------------------------------------
 void TfrmPayMentCle::turncheck()
 {
		if (!dsQuery->IsEmpty()&&dsQuery->FieldByName("State")->AsString==1) {
		   if (dstruncheck->Active)
			  dstruncheck->Active=false;
			  cmdtruncheck->Connection=con1;
		   dstruncheck->Connection=con1;
		   String  MoneyCode=dsQuery->FieldByName("MoneyCode")->AsString;
		   dstruncheck->CommandText="select * from FN_SupplyRecord where MoneyCode="+MoneyCode;
		   dstruncheck->Active=true;
		   float totallave=0;
		   float totallave1=0;
		  String ClearingType=dstruncheck->FieldByName("ClearingType")->AsString;
			   ClearingType=Trim(ClearingType);
			if (ClearingType=="付款退款") {
				 dstruncheck->First();
				 while (!dstruncheck->Eof){
				  String CheckedBef=dstruncheck->FieldByName("CheckedBef")->AsString;
				  String NoCheckedBef=dstruncheck->FieldByName("NoCheckedBef")->AsString;
				  float lave=dstruncheck->FieldByName("lave")->AsFloat;
				  String StgNtCode=dstruncheck->FieldByName("StgNtCode")->AsString;
				  String sql="update FN_EndMoneyDocuments set State=0 where MoneyCode="+MoneyCode;
				  sql=sql+";update BS_StorageNoteHeader set Checked="+CheckedBef+",NoChecked="+NoCheckedBef+",State=2 where StgNtCode="+StgNtCode;

				 cmdtruncheck->CommandText=sql;
				 cmdtruncheck->Execute();
				  totallave=totallave+lave;

				 dstruncheck->Next();
				 }
				 String sql1="update CUST_CustomerInfo set Balance=Balance-"+FloatToStr(totallave)+"where ID=(select SupplierID from BS_StorageNoteHeader where StgNtCode="+dstruncheck->FieldByName("StgNtCode")->AsString+")";
				 cmdtruncheck->CommandText=sql1;
				 cmdtruncheck->Execute();
			}
			else if (ClearingType=="余额结款")
				{
				   dstruncheck->First();
					while (!dstruncheck->Eof)
					{
					totallave1=totallave1+dstruncheck->FieldByName("EntryMoney")->AsFloat;
				  String CheckedBef=dstruncheck->FieldByName("CheckedBef")->AsString;
				  String NoCheckedBef=dstruncheck->FieldByName("NoCheckedBef")->AsString;

				  String StgNtCode=dstruncheck->FieldByName("StgNtCode")->AsString;
				  String sql="update FN_EndMoneyDocuments set State=0 where MoneyCode="+MoneyCode;
				  sql=sql+";update BS_StorageNoteHeader set Checked="+CheckedBef+",NoChecked="+NoCheckedBef+",State=2 where StgNtCode="+StgNtCode;

				 cmdtruncheck->CommandText=sql;
				 cmdtruncheck->Execute();


				 dstruncheck->Next();
				 }

						 String sql1="update CUST_CustomerInfo set Balance=Balance+"+FloatToStr(totallave1)+"where ID=(select SupplierID from BS_StorageNoteHeader where StgNtCode="+dstruncheck->FieldByName("StgNtCode")->AsString+")";
				 cmdtruncheck->CommandText=sql1;
				 cmdtruncheck->Execute();
				 }
				else if (ClearingType=="预付款")
				{
					String sql="update FN_EndMoneyDocuments set State=0 where MoneyCode="+MoneyCode;
					sql=sql+";update CUST_CustomerInfo set Balance=Balance-"+dstruncheck->FieldByName("EntryMoney")->AsString+"where ID=(select SupplierID from BS_StorageNoteHeader where StgNtCode="+dstruncheck->FieldByName("StgNtCode")->AsString+")";

				 cmdtruncheck->CommandText=sql;
				 cmdtruncheck->Execute();

				}
		  ShowMessage("反审核完成");
		}
		else  {ShowMessage("此单未审核，不能反审核");}
   dsQuery->Refresh();
 }
 //--------------------审核-------------------------------------------------------
 void TfrmPayMentCle::check()
 {
			String moneycode;
 if (rzgrpbx4->Visible==false) {
 	moneycode=edtNum->Text;
				  }
 else {  moneycode=dsNewDoc->FieldByName("MoneyCode")->AsString; }


	  //-------------获取数据--------------------
	  String ClearingType=dsNewDoc->FieldByName("ClearingType")->AsString;
		 ClearingType=Trim(ClearingType);


	   if (ClearingType=="预付款") {
								if(dscheck->Active)
					{
						  dscheck->Active=false;
					}

				dscheck->CommandText="select ClearingType,EntryMoney from FN_EndMoneyDetails  left join FN_EndMoneyDocuments on EndMoneyDcmcode=MoneyCode where MoneyCode="+moneycode;
				dscheck->Active=true;
			   String   EntryMoney1=dscheck->FieldByName("EntryMoney")->AsString;
			String sql="update FN_EndMoneyDocuments set State=1,Payment="+EntryMoney1+" where MoneyCode="+moneycode;
				sql=sql+";insert into FN_SupplyRecord (ClearingType,MoneyCode,EntryMoney) values('"+ClearingType+"',"+moneycode+","+EntryMoney1+")" ;
				sql=sql+";update CUST_CustomerInfo set Balance=Balance+"+EntryMoney1+" where Name=(select CustmerName from FN_EndMoneyDocuments where MoneyCode="+moneycode+")";
			cmdcheck->CommandText=sql;
		 cmdcheck->Execute();
	   }
	   else  if (ClearingType=="付款退款"||ClearingType=="余额付款")


	   {
						if(dscheck->Active)
					{
						  dscheck->Active=false;
					}

				dscheck->CommandText="select ClearingType,StgNtHdcode,EndMoneyDcmcode,Checked,NoChecked,EntryMoney from FN_EndMoneyDetails left join BS_StorageNoteHeader on StgNtHdcode=StgNtCode left join FN_EndMoneyDocuments on EndMoneyDcmcode=MoneyCode where MoneyCode="+moneycode;
				dscheck->Active=true;

				String StgNtHdcode,EndMoneyDcmID="0";
				String Checked,NoCheched,EntryMoney,StgntState;


			   float    CheckedBef;
			   float    NoChechedBef;
			   float	  EntryMoneyInt;
			   float   totallave;
			   float   total;
			   float   lave;
			   float   CheckedAft;
			   float   NoChechedAft;

		  
						totallave=0;
						total=0;

						//---------------计算-------------
						dscheck->First();
					while (!dscheck->Eof)
					  {



					  EndMoneyDcmID=dscheck->FieldByName("EndMoneyDcmcode")->AsString;
					  Checked=dscheck->FieldByName("Checked")->AsString;
					  StgNtHdcode=dscheck->FieldByName("StgNtHdcode")->AsString;
					  NoCheched=dscheck->FieldByName("NoChecked")->AsString;
					  EntryMoney=dscheck->FieldByName("EntryMoney")->AsString;
					  if (Checked=="") {

						  Checked="0";
							CheckedBef=0;
					  }
					  else
					  { CheckedBef=StrToFloat(Checked); }

					  NoChechedBef=StrToFloat(NoCheched);
					  EntryMoneyInt=StrToFloat(EntryMoney);
						lave=0;
						lave=NoChechedBef-EntryMoneyInt;

						if (lave>=0) {
						   CheckedAft=CheckedBef+EntryMoneyInt;
						   NoChechedAft=lave ;
						   total=total+EntryMoneyInt;
						   StgntState="0";
						   lave=0;
						}
						 else
						 {
							lave=EntryMoneyInt-NoChechedBef;
							totallave=totallave+lave;
							 CheckedAft=CheckedBef+NoChechedBef;
							 NoChechedAft=0;
							 total=total+NoChechedBef;
							StgntState="1";

						 }
						 String sql="update BS_StorageNoteHeader set Checked="+FloatToStr(CheckedAft)+",NoChecked="+FloatToStr(NoChechedAft)+",State="+StgntState+" where StgNtCode="+StgNtHdcode;
								sql=sql+";insert into FN_SupplyRecord (StgNtCode,MoneyCode,CheckedBef,NoCheckedBef,CheckedAft,NoCheckedAft,EntryMoney,lave,ClearingType) values("+StgNtHdcode+","+EndMoneyDcmID+","+Checked+","+NoCheched+","+FloatToStr(CheckedAft)+","+FloatToStr(NoChechedAft)+","+EntryMoney+","+FloatToStr(lave)+",'"+ClearingType+"')" ;

						 cmdcheck->CommandText=sql;
						 cmdcheck->Execute();
					   dscheck->Next();
					}

				 String sql="update FN_EndMoneyDocuments set State=1,Payment="+FloatToStr(total)+",overage="+FloatToStr(totallave)+" where MoneyCode="+EndMoneyDcmID;
				  //ShowMessage(ClearingType);
				   ClearingType=Trim(ClearingType);
				  if (ClearingType=="余额付款") {

						sql=sql+";update CUST_CustomerInfo set Balance=Balance-"+FloatToStr(total)+" where ID=(select SupplierID  from BS_StorageNoteHeader where StgNtCode=(select StgNtHdcode from FN_EndMoneyDetails where EndMoneyDcmcode="+moneycode+"))";
				  }

				  if (ClearingType=="付款退款") {
					  sql=sql+";update CUST_CustomerInfo set Balance=Balance+"+FloatToStr(totallave)+" where ID=(select SupplierID  from BS_StorageNoteHeader where StgNtCode=(select StgNtHdcode from FN_EndMoneyDetails where EndMoneyDcmcode="+moneycode+"))";
				  }
				 cmdcheck->CommandText=sql;
				 cmdcheck->Execute();

		   }

	   dsNewDoc->Refresh();

 }
void __fastcall TfrmPayMentCle::RzToolButton6Click(TObject *Sender)
{     if (rzgrpbx4->Visible==true||cbbType->Text!="全部供应商")
		{   if (rzgrpbx4->Visible==true) {


			  check();
			ShowMessage("审核完毕");
			 this->RzToolButton5->Click();
			}
			else
			{ShowMessage("请先查看未核单据");}
		 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::RzButton5Click(TObject *Sender)
{

	  if (!dsNewDoc->Eof) {
			  dsNewDoc->First();
		while (!dsNewDoc->Eof) {
				 check();
				 dsNewDoc->Next();

		}
			  ShowMessage("审核完毕");
			   this->RzToolButton5->Click();
		}


}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::RzToolButton3Click(TObject *Sender)
{
	if (CheckOperateAuthority())
	 {
		rzgrpbx5->Visible=true;

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::edtqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN&&edtquery->Text!="")  {
		  if (dsQuery->Active) {
		   dsQuery->Active =false;
	   }

		String sql="select MoneyCode,CustmerName,Payment,ClearingType,Clearingstyle,date,Remarks,overage,Salesman,CASE State When 0 Then '未审核'  else '审核' End AS  State  from FN_EndMoneyDocuments  where MoneyCode like '%"+edtquery->Text+"%'";
	 dsQuery->CommandText=sql;
	 dsQuery->Active=true;
	 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::RzButton9Click(TObject *Sender)
{
		  rzgrpbx5->Visible=false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmPayMentCle::RzToolButton7Click(TObject *Sender)
{
if ( rzgrpbx5->Visible==true) {
      turncheck();
}
else
 {ShowMessage("请先查单");}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::RzButton7Click(TObject *Sender)
{
	 if ( rzgrpbx5->Visible==true&&edtquery->Text!="") {
	  turncheck();
}
else
 {ShowMessage("请先查单");}
}
//---------------------------------------------------------------------------



void __fastcall TfrmPayMentCle::RzToolButton4Click(TObject *Sender)
{
	if (rzgrpbx4->Visible==true) {
		 if(MessageDlg("是否确认删除?", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
				 {		cmddel->Connection=con1;
					  String Code=dsNewDoc->FieldByName("MoneyCode")->AsString;
					   dsdel->Connection=con1;
						 String State=dsNewDoc->FieldByName("State")->AsString;
				   if (State=="未审核") {
									   if (dsdel->Active) {
											 dsdel->Active=false;
									   }
									 dsdel->CommandText="select * from FN_EndMoneyDetails where EndMoneyDcmcode="+Code;
									dsdel->Active=true;
									dsdel->First();
										 while(!dsdel->Eof)
											   {
												   cmddel->CommandText="update BS_StorageNoteHeader set State=0 where StgNtCode="+dsdel->FieldByName("StgNtHdcode")->AsString;
												   cmddel->Execute();
												  dsdel->Next();

											   }


									 String sql="delete from FN_EndMoneyDetails where EndMoneyDcmcode="+Code;
										sql=sql+";delete from FN_EndMoneyDocuments where MoneyCode="+Code;
									 cmddel->CommandText=sql;
									 cmddel->Execute();

							 // dsNewDoc->Refresh();
							 ShowMessage("成功删除");
				}
				else
				{
                   ShowMessage("此单已经审核不能删除，要删除本单必须先反审核!");

				}

			 }
	 }
	else
	{  ShowMessage("请先查看未核单据"); }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPayMentCle::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	     				if (Key==0x1B) {   //esc
			this->RzToolButton13->Click();

		}

			if (Shift.Contains(ssCtrl)&&Key==65) {   //A
			this->RzToolButton2->Click();

		}
					if (Shift.Contains(ssCtrl)&&Key==81) {   //Q
			this->RzToolButton3->Click();

		}
					if (Shift.Contains(ssCtrl)&&Key==68) {   //D
			this->RzToolButton4->Click();

		}
				if (Key==0x70) {   //F1
			this->RzToolButton5->Click();

		}		if (Key==0x71) {   //F2
			this->RzToolButton6->Click();

		}		if (Key==0x72) {   //F3
			this->RzToolButton7->Click();

		}
}
//---------------------------------------------------------------------------

