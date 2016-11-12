//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "NoteCode.h"
 #include "pdutil.h"
#include "CUSPayMentClearForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzLine"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmCUSPayMentClear *frmCUSPayMentClear;
//---------------------------------------------------------------------------
__fastcall TfrmCUSPayMentClear::TfrmCUSPayMentClear(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	m_module = MTFinance;
}

//---------------------------------------------------------------------------
void TfrmCUSPayMentClear::Init(TApplication* app, TADOConnection* con)
{
	TfrmMDIChild::Init(app, con);
		this->Caption="收款结算";
		con1=con;
		  newdocflag=false;
		  flag1=true;
		dsSupplyInit->Connection=con;
		dsPurchase->Connection=con;
		qrySupply->Connection=con;
		cmdState->Connection=con;
		qryTotal->Connection=con;
		dsNewDoc->Connection=con;
		dscheck->Connection=con;
	 cmdcheck->Connection=con;
	 	dsQuery->Connection=con;

		qrySupply->SQL->Add("select id,Name from CUST_CustomerInfo where type=2");
		qrySupply->Open();
		qrySupply->First();
		 while (!qrySupply->Eof)
		 {
			cbbType->Items->Add(qrySupply->FieldByName("Name")->AsString);
			qrySupply->Next();
		 }
		qrySupply->Close();


}
void __fastcall TfrmCUSPayMentClear::cbbTypeSelect(TObject *Sender)
{
	  if (newdocflag)
	   {        String N="update FN_CUSEndMoneyDocuments set CustmerName='"+cbbType->Text+"' where MoneyCode="+code;
			  cmdNewDocuments->CommandText=N;
			   cmdNewDocuments->Execute();
					cbb1->SetFocus();


		//-------------清除lst里面的数据,并初始化lst--------------
			lst->Repaint();
			int count=lst->RowCount;
			for (int i = 0; i < count; i++) {
			   lst->Rows[i]->Clear();
			}
			 lst->RowCount=1;
			lst->Cells[0][0]="发货账单";
			lst->Cells[1][0]="应结金额";

					if(dsSupplyInit->Active)
				{
					  dsSupplyInit->Active=false;
				}
				String sql;
				sql="select BusinessLessBookstore,Balance from  CUST_CustomerInfo where Type=2 and Name='"+cbbType->Text+"'";
				dsSupplyInit->CommandText = sql;
				dsSupplyInit->Active = true;

		 customBalance=dsSupplyInit->FieldByName("Balance")->AsFloat;

					if(dsPurchase->Active)
				{
					  dsPurchase->Active=false;
				}
				String sql1;
				sql1="select CASE State When 0 Then '未结' when 1 then '已结' else '审核中' End AS  State,id,WsaleNtCode,HdTime,FixedPrice as TotalFixedPrice,DiscountedPrice as TotalDiscountedPrice,AddCosts,Checked,NoChecked,Remarks from BS_WsaleNoteHeader where VendorID=(select id from CUST_CustomerInfo where type=2 and Name='"+cbbType->Text+"') and State<>1";
				dsPurchase->CommandText = sql1;
				dsPurchase->Active = true;
		//-----------------计算总应付----------------
				// ShowMessage(cbbType->Text);
				 String sql2="select NoChecked from BS_WsaleNoteHeader where VendorID=(select id from CUST_CustomerInfo where Type=2 and Name='"+cbbType->Text+"')";
				 qryTotal->SQL->Add(sql2);
				qryTotal->Open();
				qryTotal->First();
				float total=0;
				edt1->Text="￥";
				String  total1;

				 while (!qryTotal->Eof)
				 {

				 total=total+qryTotal->FieldByName("NoChecked")->AsFloat;
				 qryTotal->Next();

				 }

				 total=total+dsSupplyInit->FieldByName("BusinessLessBookstore")->AsFloat;
				   total1=FloatToStr(total);
				 edt1->Text=total1;
				   qryTotal->SQL->Clear();
				 qryTotal->Close();


	  }
	else
	 {ShowMessage("请先点添加结款单，生成新的结款单");}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::rzdbgrd1DblClick(TObject *Sender)
{

	if(newdocflag){
		 if (cbb1->Text=="退款付款"||cbb1->Text=="余额结款")
		 {


	  String State=Trim(dsPurchase->FieldByName("State")->AsString);

		if (State=="审核中")
		  {ShowMessage("此单包含在历史结款单中，尚未审核，请审核后再进行付款操作！");}
		 else
		 {
			String s=dsPurchase->FieldByName("WsaleNtCode")->AsString;
			String NoCheched=dsPurchase->FieldByName("NoChecked")->AsString;

			int count=lst->RowCount;
			int i=1;
			for ( ; i <count ; i++) {
				  if(lst->Cells[0][i]==s)
				   {
				   		ShowMessage("该单已经存在！");
						  break;
					 }
				   }
				   if (i>=count) {


					 if (cbb1->Text=="退款付款") {
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
							 String sql="update BS_WsaleNoteHeader set State=2 where WsaleNtCode="+dsPurchase->FieldByName("WsaleNtCode")->AsString+";insert into FN_CUSEndMoneyDtails(WsaleNTHDcode,WsaleEndMoneycode,EntryMoney) values("+dsPurchase->FieldByName("WsaleNtCode")->AsString+","+edtNum->Text+","+dsPurchase->FieldByName("NoChecked")->AsString+")";
							 cmdState->CommandText=sql;
							cmdState->Execute();
							dsPurchase->Next();
							   }

							  else {
								 flag1=false;
								  String sql="update BS_WsaleNoteHeader set State=2 where WsaleNtCode="+dsPurchase->FieldByName("WsaleNtCode")->AsString+";insert into FN_CUSEndMoneyDtails(WsaleNTHDcode,WsaleEndMoneycode,EntryMoney) values("+dsPurchase->FieldByName("WsaleNtCode")->AsString+","+edtNum->Text+","+FloatToStr(customBalance)+")";
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

			dsPurchase->Refresh();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::RzButton1Click(TObject *Sender)
{

	if(newdocflag){
		 if (cbb1->Text=="退款付款"||cbb1->Text=="余额结款")
		 {


	  String State=Trim(dsPurchase->FieldByName("State")->AsString);

		if (State=="审核中")
		  {ShowMessage("此单包含在历史结款单中，尚未审核，请审核后再进行付款操作！");}
		 else
		 {
			String s=dsPurchase->FieldByName("WsaleNtCode")->AsString;
			String NoCheched=dsPurchase->FieldByName("NoChecked")->AsString;

			int count=lst->RowCount;
			int i=1;
			for ( ; i <count ; i++) {
				  if(lst->Cells[0][i]==s)
				   {
				   		ShowMessage("该单已经存在！");
						  break;
					 }
				   }
				   if (i>=count) {


					 if (cbb1->Text=="退款付款") {
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
							 String sql="update BS_WsaleNoteHeader set State=2 where WsaleNtCode="+dsPurchase->FieldByName("WsaleNtCode")->AsString+";insert into FN_CUSEndMoneyDtails(WsaleNTHDcode,WsaleEndMoneycode,EntryMoney) values("+dsPurchase->FieldByName("WsaleNtCode")->AsString+","+edtNum->Text+","+dsPurchase->FieldByName("NoChecked")->AsString+")";
							 cmdState->CommandText=sql;
							cmdState->Execute();
							dsPurchase->Next();
							   }

							  else {
								 flag1=false;
								  String sql="update BS_WsaleNoteHeader set State=2 where WsaleNtCode="+dsPurchase->FieldByName("WsaleNtCode")->AsString+";insert into FN_CUSEndMoneyDtails(WsaleNTHDcode,WsaleEndMoneycode,EntryMoney) values("+dsPurchase->FieldByName("WsaleNtCode")->AsString+","+edtNum->Text+","+FloatToStr(customBalance)+")";
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

			dsPurchase->Refresh();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::RzButton3Click(TObject *Sender)
{
	    if (ARow1>0) {

	  int count= lst->RowCount;
		String sql="delete from FN_CUSEndMoneyDtails where WsaleEndMoneycode="+edtNum->Text+" and WsaleNTHDcode="+lst->Cells[0][ARow1]+";update BS_WsaleNoteHeader set State=0 where  WsaleNtCode="+lst->Cells[0][ARow1];
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

void __fastcall TfrmCUSPayMentClear::lstSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
       		ACol1=ACol;
		ARow1=ARow;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::lstDblClick(TObject *Sender)
{
	 	  if (ARow1>0) {

	  int count= lst->RowCount;
	  int i;
			String sql="update BS_WsaleNoteHeader set State=0 where  WsaleNtCode="+lst->Cells[0][ARow1];
			  cmdState->CommandText=sql;
			  cmdState->Execute();
	   for (i=ARow1;i<count;i++) {
			 lst->Cells[0][i]=lst->Cells[0][i+1];
			 lst->Cells[1][i]=lst->Cells[1][i+1];
				 }


	   lst->Rows[i]->Clear();
	  lst->RowCount=count-1;
	  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::edtMoneyKeyPress(TObject *Sender, wchar_t &Key)

{
         if (Key==VK_RETURN&&cbbType->Text!="选择客户")
	   {	if (cbb1->Text=="退款付款")
			 {


				if(MessageDlg("是否确认输入的金额为："+edtMoney->Text+"?", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
				   {
					   String sql="update BS_WsaleNoteHeader set State=2 where WsaleNtCode="+dsPurchase->FieldByName("WsaleNtCode")->AsString+";insert into FN_CUSEndMoneyDtails(WsaleNTHDcode,WsaleEndMoneycode,EntryMoney) values("+dsPurchase->FieldByName("WsaleNtCode")->AsString+","+edtNum->Text+","+edtMoney->Text+")";
					  cmdState->CommandText=sql;
					  cmdState->Execute();
					  dsPurchase->Next();

				   }
			}
			else  if (cbb1->Text=="预付款")
			 { //方式为预付款
				if(MessageDlg("是否确认预付款金额为："+edtMoney->Text+"?", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
				   {
				   String sql="insert into FN_CUSEndMoneyDtails(WsaleEndMoneycode,EntryMoney) values("+edtNum->Text+","+edtMoney->Text+")";
				   cmdState->CommandText=sql;
				   cmdState->Execute();
				   }
			  }
			  else {
			  ShowMessage("操作错误，请正确操作！");
			  }

	 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::RzButton2Click(TObject *Sender)
{

 if (newdocflag&&edtMoney->Text!=""&&cbbType->Text!="全部供应商"&&!dsPurchase->Eof) {


		  if (cbb1->Text=="预付款") {
              ShowMessage("在预付款方式下此功能不能用!");
		  }
	if (cbb1->Text!="预付款") {


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
							ShowMessage("此客户还有历史结款单没有审核，请审核后再进行结算操作");
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
							String sql="update BS_WsaleNoteHeader set State=2 where WsaleNtCode="+dsPurchase->FieldByName("WsaleNtCode")->AsString+";insert into FN_CUSEndMoneyDtails(WsaleNTHDcode,WsaleEndMoneycode,EntryMoney) values("+dsPurchase->FieldByName("WsaleNtCode")->AsString+","+edtNum->Text+","+dsPurchase->FieldByName("NoChecked")->AsString+")";
							cmdState->CommandText=sql;
							cmdState->Execute();
							 }
							else
							{  break;}
						 dsPurchase->Next();
					  }
					  String sql1;
					  if (money1>0) {
						 sql1="update CUST_CustomerInfo set Balance=Balance+"+FloatToStr(money1)+" where Type=2 and Name='"+cbbType->Text+"'";

						 }
					  else if (money1<0) {
						   sql1="update BS_WsaleNoteHeader set State=2 where WsaleNtCode="+dsPurchase->FieldByName("WsaleNtCode")->AsString+";insert into FN_CUSEndMoneyDtails(WsaleNTHDcode,WsaleEndMoneycode,EntryMoney) values("+dsPurchase->FieldByName("WsaleNtCode")->AsString+","+edtNum->Text+","+FloatToStr(Money)+")";
						   }

					  cmdState->CommandText=sql1;
					  cmdState->Execute();
				   }
				   ShowMessage("结算完毕");
				   dsPurchase->Refresh();
			}
			else {ShowMessage("请查看是否是新结款单！");}

			}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::RzToolButton2Click(TObject *Sender)
{

				int storage = 7;
				   code="";
				   newdocflag=true;
				TADOQuery* qry = new TADOQuery(NULL);
				qry->Connection = con1;
				code = NoteCode::BuildCode(qry, GetDBTime(qry), storage, "FN_CUSEndMoneyDocuments", "MoneyCode");
				delete qry;
				edtNum->Text=code;
            //-------------生成新单-----------------
			 cmdNewDocuments->Connection=con1;
			 String c=code;
			 String s="insert into FN_CUSEndMoneyDtails (MoneyCode) values ("+code+")";
			 cmdNewDocuments->CommandText="insert into FN_CUSEndMoneyDocuments (MoneyCode) values ("+code+")";
			 cmdNewDocuments->Execute();

			  //------------显示新单----------------

			   	if(dsNewDoc->Active)
		{
			  dsNewDoc->Active=false;
		}

			  dsNewDoc->CommandText="select * from FN_CUSEndMoneyDocuments where MoneyCode="+code;
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

void __fastcall TfrmCUSPayMentClear::cbb1Select(TObject *Sender)
{
   if (cbbType->Text!="选择客户") {


	  cmdNewDocuments->CommandText="update FN_CUSEndMoneyDocuments set ClearingType='"+cbb1->Text+"' where MoneyCode="+code;
	  cmdNewDocuments->Execute();
	   cbb2->SetFocus();
	 }
	 else{
	 ShowMessage("请选择客户");
	 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::cbb2Select(TObject *Sender)
{
	if (cbbType->Text!="选择客户")
	{
		ShowMessage("继续添加业务员");
		cmdNewDocuments->CommandText="update FN_CUSEndMoneyDocuments set Clearingstyle='"+cbb2->Text+"' where MoneyCode="+code;
		cmdNewDocuments->Execute();
		edt6->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::FormClose(TObject *Sender, TCloseAction &Action)

{
	     Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::RzToolButton13Click(TObject *Sender)
{
	 Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::edt6KeyPress(TObject *Sender, wchar_t &Key)
{
		if (Key==VK_RETURN)
		   {     if (cbbType->Text!="选择客户"&&edt6->Text!="") {
					 

				cmdNewDocuments->CommandText="update FN_CUSEndMoneyDocuments set Salesman='"+edt6->Text+"' where MoneyCode="+code;
				cmdNewDocuments->Execute();

			   }
			    edt3->SetFocus();
		   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::edt3KeyPress(TObject *Sender, wchar_t &Key)
{
	   if (Key==VK_RETURN)
		   {    if (cbbType->Text!="选择客户") {
				 if (edt3->Text!="") {
					  cmdNewDocuments->CommandText="update FN_CUSEndMoneyDocuments set Remarks='"+edt3->Text+"' where MoneyCode="+code;
					  cmdNewDocuments->Execute();
				 }
				
				if (cbb1->Text=="退款付款") {
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
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::RzToolButton5Click(TObject *Sender)
{
	   	if(dsNewDoc->Active)
		{
			  dsNewDoc->Active=false;
		}

	  dsNewDoc->CommandText="select * from FN_CUSEndMoneyDocuments where State=0";
			  dsNewDoc->Active=true;
	 rzgrpbx7->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::RzButton13Click(TObject *Sender)
{
	  	rzgrpbx7->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::RzButton11Click(TObject *Sender)
{
 this->check();
 this->RzToolButton5->Click();
}
//---------------------------------------------------------------------------
//--------------------反审核-------------------------------------------------------
 void TfrmCUSPayMentClear::turncheck()
 {
		if (dsQuery->FieldByName("State")->AsString==1) {
		   if (dstruncheck->Active)
			  dstruncheck->Active=false;
		   cmdtruncheck->Connection=con1;
		   dstruncheck->Connection=con1;
		   String  MoneyCode=dsQuery->FieldByName("MoneyCode")->AsString;
		   dstruncheck->CommandText="select * from FN_CUSRecord where MoneyCode="+MoneyCode;
		   dstruncheck->Active=true;
		   float totallave=0;
		   float totallave1=0;
		  String ClearingType=dstruncheck->FieldByName("ClearingType")->AsString;

				ClearingType=Trim(ClearingType);
			if (ClearingType=="退款付款") {
				 dstruncheck->First();
				  while (!dstruncheck->Eof){
				  String CheckedBef=dstruncheck->FieldByName("CheckedBef")->AsString;
				  String NoCheckedBef=dstruncheck->FieldByName("NoCheckedBef")->AsString;
				  float lave=dstruncheck->FieldByName("lave")->AsFloat;
				  String StgNtCode=dstruncheck->FieldByName("WsaleNtCode")->AsString;
				  String sql="update FN_CUSEndMoneyDocuments set State=0 where MoneyCode="+MoneyCode;
				  sql=sql+";update BS_WsaleNoteHeader set Checked="+CheckedBef+",NoChecked="+NoCheckedBef+",State=2 where WsaleNtCode="+StgNtCode;

				 cmdtruncheck->CommandText=sql;
				 cmdtruncheck->Execute();
				  totallave=totallave+lave;
				 dstruncheck->Next();
				 }
				 String sql1="update CUST_CustomerInfo set Balance=Balance-"+FloatToStr(totallave)+"where ID=(select VendorID from BS_WsaleNoteHeader where WsaleNtCode="+dstruncheck->FieldByName("WsaleNtCode")->AsString+")";
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

				  String StgNtCode=dstruncheck->FieldByName("WsaleNtCode")->AsString;
				  String sql="update FN_CUSEndMoneyDocuments set State=0 where MoneyCode="+MoneyCode;
				  sql=sql+";update BS_WsaleNoteHeader set Checked="+CheckedBef+",NoChecked="+NoCheckedBef+",State=2 where WsaleNtCode="+StgNtCode;

				 cmdtruncheck->CommandText=sql;
				 cmdtruncheck->Execute();


				 dstruncheck->Next();
				 }

						 String sql1="update CUST_CustomerInfo set Balance=Balance+"+FloatToStr(totallave1)+"where ID=(select VendorID from BS_WsaleNoteHeader where WsaleNtCode="+dstruncheck->FieldByName("WsaleNtCode")->AsString+")";
				 cmdtruncheck->CommandText=sql1;
				 cmdtruncheck->Execute();
				 }
				else if (ClearingType=="预付款")
				{
					String sql="update FN_CUSEndMoneyDocuments set State=0 where MoneyCode="+MoneyCode;
					sql=sql+";update CUST_CustomerInfo set Balance=Balance-"+dstruncheck->FieldByName("EntryMoney")->AsString+"where ID=(select VendorID from BS_WsaleNoteHeader where WsaleNtCode="+dstruncheck->FieldByName("WsaleNtCode")->AsString+")";

				 cmdtruncheck->CommandText=sql;
				 cmdtruncheck->Execute();

				}
			  ShowMessage("反审核完毕！");
			  //dsQuery->Refresh();
		}
		else  {ShowMessage("此单未审核，不能反审核");}

 }
 //--------------------审核-------------------------------------------------------
 void TfrmCUSPayMentClear::check()
 {

			String moneycode;
		 if (rzgrpbx7->Visible==false) {
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

				dscheck->CommandText="select ClearingType,EntryMoney from FN_CUSEndMoneyDtails  left join FN_CUSEndMoneyDocuments on WsaleEndMoneycode=MoneyCode where MoneyCode="+moneycode;
				dscheck->Active=true;
			   String   EntryMoney1=dscheck->FieldByName("EntryMoney")->AsString;
			String sql="update FN_CUSEndMoneyDocuments set State=1,Payment="+EntryMoney1+" where MoneyCode="+moneycode;
				sql=sql+";insert into FN_CUSRecord (ClearingType,MoneyCode,EntryMoney) values('"+ClearingType+"',"+moneycode+","+EntryMoney1+")" ;
				sql=sql+";update CUST_CustomerInfo set Balance=Balance+"+EntryMoney1+" where ID=(select VendorID  from BS_WsaleNoteHeader where WsaleNtCode=(select WsaleNTHDcode from FN_CUSEndMoneyDtails where WsaleEndMoneycode="+moneycode+"))";
			cmdcheck->CommandText=sql;
			 cmdcheck->Execute();
		   }
		   else  if (ClearingType=="退款付款"||ClearingType=="余额付款")


		   {
						if(dscheck->Active)
					{
						  dscheck->Active=false;
					}

				dscheck->CommandText="select ClearingType,WsaleNTHDcode,WsaleEndMoneycode,Checked,NoChecked,EntryMoney from FN_CUSEndMoneyDtails left join BS_WsaleNoteHeader on WsaleNTHDcode=WsaleNtCode left join FN_CUSEndMoneyDocuments on WsaleEndMoneycode=MoneyCode where MoneyCode="+moneycode;
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

					  ClearingType=dscheck->FieldByName("ClearingType")->AsString;
					  EndMoneyDcmID=dscheck->FieldByName("WsaleEndMoneycode")->AsString;
					  Checked=dscheck->FieldByName("Checked")->AsString;
					  StgNtHdcode=dscheck->FieldByName("WsaleNTHDcode")->AsString;
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
						 String sql="update BS_WsaleNoteHeader set Checked="+FloatToStr(CheckedAft)+",NoChecked="+FloatToStr(NoChechedAft)+",State="+StgntState+" where WsaleNtCode="+StgNtHdcode;
								sql=sql+";insert into FN_CUSRecord (WsaleNtCode,MoneyCode,CheckedBef,NoCheckedBef,CheckedAft,NoCheckedAft,EntryMoney,lave,ClearingType) values("+StgNtHdcode+","+EndMoneyDcmID+","+Checked+","+NoCheched+","+FloatToStr(CheckedAft)+","+FloatToStr(NoChechedAft)+","+EntryMoney+","+FloatToStr(lave)+",'"+ClearingType+"')" ;

						 cmdcheck->CommandText=sql;
						 cmdcheck->Execute();
					   dscheck->Next();
					}

				 String sql="update FN_CUSEndMoneyDocuments set State=1,Payment="+FloatToStr(total)+",overage="+FloatToStr(totallave)+" where MoneyCode="+moneycode;
				  if (ClearingType=="余额付款") {
						sql=sql+";update CUST_CustomerInfo set Balance=Balance-"+FloatToStr(totallave)+" where ID=(select VendorID  from BS_WsaleNoteHeader where WsaleNtCode=(select WsaleNTHDcode from FN_CUSEndMoneyDtails where WsaleEndMoneyDcode="+moneycode+"))";
				  }
				  if (ClearingType=="退款付款") {
					  sql=sql+";update CUST_CustomerInfo set Balance=Balance+"+FloatToStr(totallave)+" where ID=(select VendorID  from BS_WsaleNoteHeader where WsaleNtCode=(select WsaleNTHDcode from FN_CUSEndMoneyDtails where WsaleEndMoneycode="+moneycode+"))";
				  }
				 cmdcheck->CommandText=sql;
				 cmdcheck->Execute();
				 ShowMessage("审核完毕！");

			  dsNewDoc->Refresh();
		   }



 }
void __fastcall TfrmCUSPayMentClear::RzToolButton6Click(TObject *Sender)
{
	   if (rzgrpbx7->Visible==true) {
			check();
		ShowMessage("审核完毕");
		 this->RzToolButton5->Click();
	   }
	   else
	   {ShowMessage("请先查看未核单据");}


}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::RzButton12Click(TObject *Sender)
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

void __fastcall TfrmCUSPayMentClear::RzToolButton3Click(TObject *Sender)
{
	  if (CheckOperateAuthority()) {

		   rzgrpbx6->Visible=true;
	  }


}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::edtqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN&&edtquery->Text!="")  {


			  if (dsQuery->Active) {
			   dsQuery->Active =false;
		   }


	 dsQuery->CommandText="select MoneyCode,CustmerName,Payment,ClearingType,Clearingstyle,date,Remarks,overage,Salesman,CASE State When 0 Then '未审核'  else '审核' End AS  State from FN_CUSEndMoneyDocuments  where  MoneyCode like '%"+edtquery->Text+"%'";
	 dsQuery->Active=true;
	 }

}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::RzButton10Click(TObject *Sender)
{
			  rzgrpbx6->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::RzToolButton7Click(TObject *Sender)
{
		 if ( rzgrpbx6->Visible==true) {
      turncheck();
}
else
 {ShowMessage("请先查单");}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayMentClear::RzButton8Click(TObject *Sender)
{
		   if ( rzgrpbx6->Visible==true&&edtquery->Text!="") {
	  turncheck();
}
else
 {ShowMessage("请先查单");}
}
//---------------------------------------------------------------------------


void __fastcall TfrmCUSPayMentClear::RzToolButton4Click(TObject *Sender)
{
		if (rzgrpbx7->Visible==true) {
		 if(MessageDlg("是否确认删除?", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
				 {		cmddel->Connection=con1;
					  String Code=dsNewDoc->FieldByName("MoneyCode")->AsString;
					  String State=dsNewDoc->FieldByName("State")->AsString;
					   dsdel->Connection=con1;

				if (State=="未审核") {

                     	   if (dsdel->Active) {
							 dsdel->Active=false;
					   }
					 dsdel->CommandText="select * from FN_CUSEndMoneyDtails where WsaleEndMoneycode="+Code;
					dsdel->Active=true;
					dsdel->First();
						 while(!dsdel->Eof)
							   {
								   cmddel->CommandText="update BS_WsaleNoteHeader set State=0 where WsaleNtCode="+dsdel->FieldByName("WsaleNTHDcode")->AsString;
								   cmddel->Execute();
								  dsdel->Next();

							   }


					 String sql="delete from FN_CUSEndMoneyDtails where WsaleEndMoneycode="+Code;
						sql=sql+";delete from FN_CUSEndMoneyDocuments where MoneyCode="+Code;
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

void __fastcall TfrmCUSPayMentClear::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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

