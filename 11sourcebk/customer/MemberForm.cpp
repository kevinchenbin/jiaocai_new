//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberForm.h"
#include <SysUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzLine"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RzDBDTP"
#pragma link "MDIChild"
#pragma link "RzDTP"
#pragma resource "*.dfm"
TfrmMember *frmMember;
//---------------------------------------------------------------------------
__fastcall TfrmMember::TfrmMember(TComponent* Owner)
	: TfrmMDIChild(Owner)
{          m_module = MTCustom;
}


//---------------------------------------------------------------------------
void __fastcall TfrmMember::FormClose(TObject *Sender, TCloseAction &Action)
{


		qryMemberSettings->Close();
		qryUserAuthority->Close();
		dsetMemberSettings->Active=false;
		dsetMemberLevel->Active=false;
	Action = caFree;	
}
//---------------------------------------------------------------------------

void TfrmMember::Init(TApplication* app, TADOConnection* con)
{
   TfrmMDIChild::Init(app, con);

	 this->app1=app;
	 this->con1=con;

	//---------------会员信息设置---------------------
	if (dsetMemberSettings->Active)
	{
		dsetMemberSettings->Active = false;
	}
		String   sql;
		dsetMemberSettings->Connection = con;
		sql = "select *  from CUST_MemberInfo LEFT join CUST_MemberType on MemberType=IDType where CUST_MemberInfo.id<0";
		dsetMemberSettings->CommandText = sql;
		dsetMemberSettings->Active = true;

		//---------------------会员类型设置----------------------
	  if (dsetMemberLevel->Active)
	{
		dsetMemberLevel->Active = false;
	}
		String   sql1;
		dsetMemberLevel->Connection = con;
		sql1 = "select* from CUST_MemberType order by idType desc";
		dsetMemberLevel->CommandText = sql1;
		dsetMemberLevel->Active = true;

		//-----------------------向会员类型下拉列表添加会员类型--------------------
		qryMemberSettings->Connection = con;
		qryMemberSettings->SQL->Add("select* from CUST_MemberType");
		qryMemberSettings->Open();
		qryMemberSettings->First();
		MemberType->ClearItemsValues();
	 while (!qryMemberSettings->Eof)
	 {
		  MemberType->AddItemValue(qryMemberSettings->FieldByName("Type")->AsString,qryMemberSettings->FieldByName("IDType")->AsString);
		qryMemberSettings->Next();
	 }


	cmdDelMember->Connection = con;
	cmdTop->Connection=con;
	cmdTopRecord->Connection=con;
	qryMemberSettings->First() ;
	 MemberType->Text=qryMemberSettings->FieldByName("Type")->AsString;
	 Type=qryMemberSettings->FieldByName("Type")->AsString;
	 Type1=qryMemberSettings->FieldByName("IDType")->AsInteger;
	   qryMemberSettings->Close();
}





void __fastcall TfrmMember::RzToolButton1Click(TObject *Sender)
{        dbedtName->SetFocus();
		   dbedtName->ReadOnly=false;
		   dbedtName1->ReadOnly=false;
	   if (dsetMemberLevel->State == dsInsert&&dbedtName->Text!= "")
	{

		dsetMemberLevel->Post();
		dsetMemberLevel->Refresh();
	}
	 dsetMemberLevel->Append();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::RzToolButton2Click(TObject *Sender)
{

	if(!dsetMemberLevel->IsEmpty())
	{
		if (dsetMemberLevel->RecordCount>1) {
				 try{

					  dsetMemberLevel->Delete();
					dsetMemberLevel->Refresh();

				   }
				 catch(Exception &E)
				 {
						ShowMessage("此数据更系统其他地方有关联，不能删除！");
				 }



			  }
			  else
			  {
				  ShowMessage("为了保证业务正常，系统至少要有一个会员级别");
			  }

	}

}

//---------------------------------------------------------------------------

void __fastcall TfrmMember::RzToolButton4Click(TObject *Sender)
{
			this->Sender1=Sender;
		edtName->SetFocus();
		  edtName->ReadOnly=false;
		  edtName3->ReadOnly=false;
		  Sex->ReadOnly=false;
            edtName2->ReadOnly=false;
		  RzDBEdit3->ReadOnly=false;
		  edtName->ReadOnly=false;
		  RzDBEdit4->ReadOnly=false;
		  edtName1->ReadOnly=false;
		  RzDBEdit5->ReadOnly=false;
		  MemberType->ReadOnly=false;
		  RzDBEdit8->ReadOnly=false;
		  edtName3->ReadOnly=false;




	  if (dsetMemberSettings->State == dsInsert&&dbedtName->Text!= "")
		{
		dsetMemberSettings->FieldByName("Name")->AsString = edtName->Text;
		dsetMemberSettings->FieldByName("Birthday")->AsString = edtName3->Date;
		dsetMemberSettings->FieldByName("Sex")->AsString = Sex->Value;
		dsetMemberSettings->FieldByName("Tel")->AsString = edtName2->Text;
		dsetMemberSettings->FieldByName("Mobile")->AsString = RzDBEdit3->Text;
		dsetMemberSettings->FieldByName("Address")->AsString = RzDBEdit8->Text;

			if (MemberType->Value!="") {
			//ShowMessage(MemberType->Value);
				Type1=StrToInt(MemberType->Value);
			}

		dsetMemberSettings->FieldByName("PostalCode")->AsString = edtName1->Text;
		dsetMemberSettings->FieldByName("CardSN")->AsString = RzDBEdit4->Text;
		dsetMemberSettings->FieldByName("Balance")->AsString = RzDBEdit5->Text;
		dsetMemberSettings->FieldByName("MemberType")->AsString = IntToStr(Type1);

		dsetMemberSettings->Post();
		//dsetMemberSettings->Refresh();
	}
	  MemberType->Text=Type;
	dsetMemberSettings->Append();

  
}
//---------------------------------------------------------------------------


void __fastcall TfrmMember::RzToolButton5Click(TObject *Sender)
{
	if(!dsetMemberSettings->IsEmpty() && dsetMemberSettings->FieldByName("ID")->AsString != "")
	{
			if (dsetMemberSettings->RecordCount>1) {
				   try{
							String sql = "delete CUST_MemberInfo where ID = " + dsetMemberSettings->FieldByName("ID")->AsString;
								cmdDelMember->CommandText = sql;
								cmdDelMember->Execute();
								this->Query();
					 }
					 catch(Exception &E)
					 {
							ShowMessage("此数据更系统其他地方有关联，不能删除！");
					 }
			  }
			  else
			  {
				  ShowMessage("为了保证业务正常，系统至少要有一个会员");
			  }


	
	   }

}
//---------------------------------------------------------------------------


void __fastcall TfrmMember::dsetMemberSettingsMoveComplete(TCustomADODataSet *DataSet,
          const TEventReason Reason, const Error *Error, TEventStatus &EventStatus)

{
	 //ShowMessage(dsetMemberSettings->GetIndexNames("id"));

}
//----------------------------------------------------------------


void __fastcall TfrmMember::RzToolButton3Click(TObject *Sender)
{        cbbType->SetFocus();
		Query();
}
//------------------------------查询--------------------------------------------
void TfrmMember::Query()
{
       edtName3->ReadOnly=false;
	if (dsetMemberSettings->Active)
	{
		dsetMemberSettings->Active = false;
	}
	String sql;
	if (cbbType->Text=="会员号") {
		   sql="select *  from CUST_MemberInfo LEFT join CUST_MemberType on MemberType=IDType where id like '%"+RzEditInfor->Text+"%'";
	}
		else if (cbbType->Text=="会员姓名")
		{
			 sql="select *  from CUST_MemberInfo LEFT join CUST_MemberType on MemberType=IDType where Name like '%"+RzEditInfor->Text+"%'";
		 }
			else if (cbbType->Text=="会员卡号")
				{
				 sql="select *  from CUST_MemberInfo LEFT join CUST_MemberType on MemberType=IDType where CardSN like '%"+RzEditInfor->Text+"%'";
				}
				 else
					 {
						sql="select *  from CUST_MemberInfo LEFT join CUST_MemberType on MemberType=IDType" ;
					}
	dsetMemberSettings->CommandText = sql;
	dsetMemberSettings->Active = true;
	RzEditInfor->Text="";
}

//--------------------------------------------------------
void __fastcall TfrmMember::RzToolButton7Click(TObject *Sender)
{
		 AddTop();


}

//--------------------------------取消充值-------------------------------------------

void __fastcall TfrmMember::lblcancelClick(TObject *Sender)
{
	edtTop->Clear();
	lblTop->Visible=false;
	edtTop->Visible=false;
	lblcancel->Visible=false;
	lbl1->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::RzToolButton6Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::RzEditInforKeyPress(TObject *Sender, wchar_t &Key)
{
		   if (Key==VK_RETURN) {
				Query();
		 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edtTopKeyPress(TObject *Sender, wchar_t &Key)
{
        if (Key==VK_RETURN) {
				AddTop();
		 }
}
//---------------------------充值------------------------------------------------
  void TfrmMember::AddTop()
  {
		 if(lblTop->Visible==false)
			{
						lblTop->Visible=true;
			   edtTop->Visible=true;
			   lblcancel->Visible=true;
			   lbl1->Visible=true;

			}
			if(edtTop->Text!=""&&edtTop->IntValue>0)
			{
				 if(!dsetMemberSettings->IsEmpty() && dsetMemberSettings->FieldByName("ID")->AsString != "")
					{     String s1,s2,s3,s4,s5;

						   s1=dsetMemberSettings->FieldByName("CardSN")->AsString;
							s2=dsetMemberSettings->FieldByName("ID")->AsString;
						   s3=dsetMemberSettings->FieldByName("IDType")->AsString;
						   s4=dsetMemberSettings->FieldByName("Name")->AsString;
						   s5=dsetMemberSettings->FieldByName("Type")->AsString;
							int NowCash=0;

						    String   SNowCash;
							String sql;
							String sql1;
				 if(MessageDlg("您确认对会员："+s4+"充值"+edtTop->Text+"元吗？", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true)
					 {
					  String BeforCash=dsetMemberSettings->FieldByName("Balance")->AsString;
							if (BeforCash=="") {
								BeforCash="0";
							}
							if (dsetMemberSettings->FieldByName("Balance")->AsString=="") {
							   NowCash=edtTop->IntValue;
							}
							else
						  {	NowCash=dsetMemberSettings->FieldByName("Balance")->AsInteger+edtTop->IntValue; }

						SNowCash=IntToStr(NowCash);

						sql = "update CUST_MemberInfo set Balance="+SNowCash+" where id=" + dsetMemberSettings->FieldByName("ID")->AsString;
						cmdTop->CommandText = sql;
						cmdTop->Execute();


						  sql1="insert into CUST_MemberToprecord(BeforeVoucherAmount,VoucherAmount ,AfterVoucherAmount,CardNumber,MIid,MTid,MIName,MIType) values ("+BeforCash+","+edtTop->Text+","+SNowCash+",'"+s1+"',"+s2+","+s3+",'"+s4+"','"+s5+"')";
						cmdTopRecord->CommandText = sql1;
                        	if (s5=="") {
								ShowMessage("该会员类型不明确，请先为他（她）添加会员类型");
						}else
					   {	cmdTopRecord->Execute();

						s1=  "恭喜您！会员"+s4+"充值成功！本次充值："+edtTop->Text+"￥！充值前余额："+BeforCash+"￥！当前金额："+SNowCash+"￥" ;
						ShowMessage(s1);
								}

					 edtTop->Clear();
					lblTop->Visible=false;
					edtTop->Visible=false;
					lblcancel->Visible=false;
					lbl1->Visible=false;
					  //	this->Init(this->app1,this->con1) ;
					  this->Query();
					 }
				}
		   }
  }
void __fastcall TfrmMember::edtNameKeyPress(TObject *Sender, wchar_t &Key)
{
		  if (Key==VK_RETURN) {

					  if (edtName->Text=="") {
						   ShowMessage("会员名不能为空");
					  }
					  else
						   {
						   	RzDBEdit4->SetFocus();
						   }
			   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::RzDBEdit4KeyPress(TObject *Sender, wchar_t &Key)
{
		if (Key==VK_RETURN)
		 {
			   String s=RzDBEdit4->Text;
			   s=Trim(s);
			   int lenth=s.Length();
			   if (lenth!=13) {
					ShowMessage("会员卡号必须是13位");
					RzDBEdit4->SetFocus();
			   }
			   else{
				Sex->SetFocus();
			   }
		  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::SexKeyPress(TObject *Sender, wchar_t &Key)
{
       if (Key==VK_RETURN) {

				edtName2->SetFocus();
			   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edtName2KeyPress(TObject *Sender, wchar_t &Key)
{
	 if (Key==VK_RETURN) {

				RzDBEdit3->SetFocus();
			   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::RzDBEdit3KeyPress(TObject *Sender, wchar_t &Key)
{
		 if (Key==VK_RETURN) {

				edtName1->SetFocus();
			   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edtName1KeyPress(TObject *Sender, wchar_t &Key)
{
	   if (Key==VK_RETURN) {

				edtName3->SetFocus();
			   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edtName3KeyPress(TObject *Sender, wchar_t &Key)
{
		 if (Key==VK_RETURN) {

				MemberType->SetFocus();
			   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::MemberTypeKeyPress(TObject *Sender, wchar_t &Key)
{
          if (Key==VK_RETURN) {
				if (MemberType->Text=="") {
					ShowMessage("会员类型不能为空");
				}
				else
				{ RzDBEdit8->SetFocus();}
			   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::RzDBEdit8KeyPress(TObject *Sender, wchar_t &Key)
{
		  if (Key==VK_RETURN) {
				this->RzToolButton4Click(this->Sender1);
			ShowMessage("信息已保存！");
			   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::dbedtNameKeyPress(TObject *Sender, wchar_t &Key)
{
			 if (Key==VK_RETURN) {
					 dbedtName1->SetFocus();

			   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::cbbTypeSelect(TObject *Sender)
{
	switch (cbbType->ItemIndex)
	{
	case 0:
        RzEditInfor->MaxLength = 13;
		break;
	case 1:
		RzEditInfor->MaxLength = 0;
		break;
	case 2:
        RzEditInfor->MaxLength = 0;
		break;
	default:
    	break;
	}
	RzEditInfor->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMember::RzToolButton9Click(TObject *Sender)
{
		 edtName->SetFocus();
		  edtName->ReadOnly=false;
		  //edtName3->ReadOnly=false;
		  Sex->ReadOnly=false;
           edtName2->ReadOnly=false;
		  RzDBEdit3->ReadOnly=false;
		  edtName->ReadOnly=false;
		  RzDBEdit4->ReadOnly=false;
		  edtName1->ReadOnly=false;
		  RzDBEdit5->ReadOnly=false;
		  MemberType->ReadOnly=false;
		  RzDBEdit8->ReadOnly=false;
		   edtName3->ReadOnly=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::RzToolButton8Click(TObject *Sender)
{
	 		dbedtName->SetFocus();
		   dbedtName->ReadOnly=false;
		   dbedtName1->ReadOnly=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::dbedtName1KeyPress(TObject *Sender, wchar_t &Key)
{
			 if (Key==VK_RETURN) {
			 	   if (dsetMemberLevel->State == dsInsert&&dbedtName->Text!= "")
					{

						dsetMemberLevel->Post();
						dsetMemberLevel->Refresh();
						ShowMessage("信息已自动保存！");
					}


			   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::RzDBEdit5KeyPress(TObject *Sender, wchar_t &Key)
{
           if (Key==VK_RETURN) {
					 RzDBEdit8->SetFocus();

			   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
				if (Shift.Contains(ssCtrl)&&Key==81) {  //Q键
				  this->RzToolButton3->Click();
			}
		if (Key==0x1B) {       //esc 键
				  this->RzToolButton6->Click();
			}
					if (Shift.Contains(ssCtrl)&&Key==83) {       //S键
				  this->RzToolButton4->Click();
			}
					if (Shift.Contains(ssCtrl)&&Key==68) {       //D键
				  this->RzToolButton5->Click();
			}
		if (Shift.Contains(ssCtrl)&&Key==69) {  //E键
				  this->RzToolButton9->Click();
			}
		if (Shift.Contains(ssCtrl)&&Key==90) {       //Z 键
				  this->RzToolButton1->Click();
			}
					if (Shift.Contains(ssCtrl)&&Key==88) {       //X键
				  this->RzToolButton2->Click();
			}
					if (Shift.Contains(ssCtrl)&&Key==67) {       //C键
				  this->RzToolButton8->Click();
			}
			if (Shift.Contains(ssCtrl)&&Key==84) {       //T键
				  this->RzToolButton7->Click();
			}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edtName3Change(TObject *Sender)
{
	           MemberType->SetFocus();
}
//---------------------------------------------------------------------------

