//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Dog.h"
#include "LandForm.h"
#include "global.h"
#include "Stockalarm.h"
#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzBmpBtn"
#pragma resource "*.dfm"
TfrmLand *frmLand;
//---------------------------------------------------------------------------
__fastcall TfrmLand::TfrmLand(TComponent* Owner)
	: TForm(Owner)
	, m_user(-1)
	, m_storage(-1)
	, m_master(-1)
{
	AnsiString constr;
	 AnsiString configfile;
	  configfile =  ExtractFilePath(Application->ExeName) + "dbconfig" +  ".INI" ;
	  TIniFile *ini;
	   ini   = new    TIniFile(configfile);
	   dbServer = ini->ReadString("dbserver","Server","4e3");
	   UserName = ini->ReadString("dbserver","Username","sa");
	   Zhangtao = ini->ReadString("dbserver","Zhangtao","默认帐套");
	   pd = ini->ReadString("dbserver","pd","");
	   delete ini;
//read dog

	  AnsiString DogInfo;
	  /* ReadDog *Dog = new ReadDog();
	   if (1== Dog->OpenDog())
	   {
		 MessageBoxA(0,"请安装加密狗！","错误",MB_ICONERROR);

		 //Close();
		 Application->Terminate();
		 return;

	   }
	   if (2== Dog->OpenDog())
	   {
		 MessageBoxA(0,"加密狗没打开或密码错误！","错误",MB_ICONERROR);

		 //Close();
		 Application->Terminate();
		 return;

	   }
	   if (DevNumber != Dog->ReadDevNumber())
	   {
		 MessageBoxA(0,"无效的加密狗！请与管理员联系","错误",MB_ICONERROR);
		 Dog->CloseDog();
		 return;
	   }else
	   {

		 DogInfo =  Dog->ReadDogInfo();
		 Dog->CloseDog();
	   }
	   delete Dog;
		*/
		DogInfo="pdz@c3$9w4!0tb19";
	   constr = "Provider=SQLOLEDB.1;Password=" + DogInfo + ";Persist Security Info=True;User ID="+UserName+";Data Source=";
	   constr = constr +dbServer+";Initial Catalog=pddbinfo;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=LEOMA;Use Encryption for Data=False;Tag with column collation when possible=False";

	  // constr = "Provider=SQLNCLI.1;Password="+DogInfo+";Persist Security Info=False;User ID=sa;Initial Catalog=pddbinfo;Data Source="+dbServer;
	   //constr = "Provider=SQLOLEDB.1;Password=pdz@c3$9w4!0tb19;Persist Security Info=True;User ID="+UserName+";Data Source=";
	//   constr = "Provider=SQLOLEDB.1;Password=pddataabc;Persist Security Info=True;User ID="+UserName+";Data Source=";
   //	   constr = constr +dbServer+";Initial Catalog=pddbinfo;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=LEOMA;Use Encryption for Data=False;Tag with column collation when possible=False";
	  try
	  {
		   conaccount->ConnectionString = constr;
		   if (!conaccount->Connected ) {
			  conaccount->Connected = true;
		   }
	   }
	   catch(...)
	   {
		 MessageBoxA(0,"数据库连接错误！请与管理员联系","错误",MB_ICONERROR);
		 return;
	   }
	   String sqlgetzhangtao = "select * from pdinfo where state = '已启用' and security = '"  + Zhangtao + "'";

	   TADOQuery *aq = new TADOQuery(this);
	   aq->Connection = conaccount ;
	   aq->Close();
	   aq->SQL->Clear();
	   aq->SQL->Add(sqlgetzhangtao);
	   aq->Open();

	   cbzhangtao->Items->Add(aq->FieldByName("name")->AsAnsiString);
	  // cbzhangtao->Items->Add("book");
	   cbzhangtao->ItemIndex = 0;
	   delete aq;    //取得默认帐套

	   char Temp[MAX_PATH]="";
	   char TempName[MAX_PATH] = "";
	try
	 {
	   GetProfileString("DataIntegrity","path","",Temp,MAX_PATH);
	   GetProfileString("DataIntegrity","AccountSetName","",TempName,MAX_PATH);
	   if (!FileExists(AnsiString(Temp) + ".mdf") ) {

		  //如果有安全帐套则显示选择帐套


												  //登录默认帐套
		  LoginConstr = "Provider=SQLOLEDB.1;Password=" + DogInfo + ";Persist Security Info=True;User ID="+UserName+";Data Source=";
		  LoginConstr = LoginConstr +dbServer+";Initial Catalog="+cbzhangtao->Text.Trim() +";Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=LEOMA;Use Encryption for Data=False;Tag with column collation when possible=False";
		//  LoginConstr = "Provider=SQLNCLI.1;Password="+DogInfo+";Persist Security Info=False;User ID=sa;Initial Catalog="+cbzhangtao->Text.Trim() +";Data Source="+dbServer;

		// LoginConstr = "Provider=SQLOLEDB.1;Password=pddataabc;Persist Security Info=True;User ID="+UserName+";Data Source=";
		// LoginConstr = "Provider=SQLOLEDB.1;Password=pdz@c3$9w4!0tb19;Persist Security Info=True;User ID="+UserName+";Data Source=";
		// LoginConstr = LoginConstr +dbServer+";Initial Catalog="+cbzhangtao->Text.Trim() +";Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=LEOMA;Use Encryption for Data=False;Tag with column collation when possible=False";
		conaccount->Connected=false;
		  conLand->ConnectionString = LoginConstr ;
		  try
		  {
			  if (!conLand->Connected ) {
				  conLand->Connected = true;
			  }
		   }
		   catch(...)
		   {
			  MessageBoxA(0,"数据库连接错误！请与管理员联系","错误",MB_ICONERROR);
			  return;
		  //	  lbzhangtao->Visible = false;
		 // cbzhangtao->Visible = false;
		 // sbchangepd->Top = 111;
		  //sblogcancel->Top = 111;
		 // sblogin->Top = 111;
			 // Application->Terminate();

		   }
		   String sql;
		   TADOQuery *aq = new TADOQuery(this);
		   aq->Connection = conLand ;
		   sql = "select ID,Name,Master from SYS_StorageInfo ";
		   aq->Close();
		   aq->SQL->Clear();
		   aq->SQL->Add(sql);
		   aq->Open();
		   cbstorage->Clear();
		   while (!aq->Eof )
		   {
				cbstorage->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger );
				aq->Next();
		   }
		   cbstorage->ItemIndex =  cbstorage->Items->IndexOfObject(0);
		   m_storage = 0;
		   UserView();
	  } else
	  {
		cbzhangtao->Items->Add(AnsiString(TempName));
        cbzhangtao->ItemIndex = -1;
	  }
	}
   catch(...)
   {}
}
//---------------------------------------------------------------------------

int TfrmLand::GetUserID()
{
	return m_user;
}

int TfrmLand::GetStorageID()
{
	return m_storage;
}

bool TfrmLand::GetMaster()
{
	//m_storage = (int)(cbstorage->Items->Objects[cbstorage->ItemIndex]);
	String sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = conLand ;
	sql = "select ID,Master from SYS_StorageInfo where id = " + IntToStr(m_storage);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	m_master = aq->FieldByName("Master")->AsBoolean ;
	delete aq;
	return m_master;

}
AnsiString TfrmLand::GetUserName()
{
	AnsiString sql,username;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = conLand ;
	sql = "select ID,name from sys_user where ID = " + IntToStr(userid) ;//用户名列表
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	username = aq->FieldByName("name")->AsAnsiString ;
	delete aq;
	return  username;
}


void __fastcall TfrmLand::cbNameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		sblogin->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::sbloginClick(TObject *Sender)
{
	if (cbzhangtao->Text == "") {
		MessageBoxA(0,"请选择帐套","提示",MB_ICONASTERISK);
		return;
	}


	if (!Login(cbName->Text, edtPassword->Text, userid, stgid))
		MessageBox(0,"用户名或密码错误！","提示",MB_ICONEXCLAMATION   );
	else
	{
		m_storage = stgid;
		m_user = userid;
		AddEvent(1,"登录窗口",GetUserID(),GetStorageID(),"登录");
		String sql;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = conLand ;
		sql = "select value from sys_bsset where name = 'loginstockalarm'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->FieldByName("value")->AsBoolean  ) {
			Tfrmalarm *frm = new Tfrmalarm(Application,conLand,GetStorageID());
		}
		delete aq;
		ModalResult = mrOk;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::sbchangepdClick(TObject *Sender)
{
	if (cbName->Text == "") {
		MessageBox(0,"请选择一个用户!","提示",MB_ICONWARNING  );
		return;
	}
	edtoldpd->Text = "";
	edtnewpd->Text = "";
	edtconfirmpd->Text = "";
	pchangepd->Visible = false;
	plogin->Visible = true;
	pchangepd->Visible  = true;
	plogin->Visible = False ;
}
//---------------------------------------------------------------------------


void __fastcall TfrmLand::sbokClick(TObject *Sender)
{
	String getuserinfo = "select count(*) as d from sys_user where name = '" + cbName->Text + "' and password = '"+edtoldpd->Text.Trim() +"' and stgID = " + IntToStr(stgid);
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = conLand ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(getuserinfo);

	aq->Open();
	if (aq->FieldByName("d")->AsInteger ==0 ) {
		MessageBox(0,"旧密码错误！","提示",MB_ICONEXCLAMATION );
		return;
	}
	if (edtnewpd->Text != edtconfirmpd->Text) {
		MessageBox(0,"两次输入的密码不相符！","提示",MB_ICONEXCLAMATION );
		return;
	}
	String updatepd  = "update sys_user set password = '" + edtconfirmpd->Text + "' where name = '" + cbName->Text + "' and stgID = " + IntToStr(stgid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(updatepd);
	if (aq->ExecSQL())
	{
		MessageBox(0,"密码更改成功！","提示",MB_ICONEXCLAMATION );
	}else
	{
		MessageBox(0,"密码更改失败！","提示",MB_ICONEXCLAMATION );
		return;
	}
	delete aq;
	pchangepd->Visible = false;
	plogin->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::cbzhangtaoChange(TObject *Sender)
{
	 try
	 {
		  LoginConstr = "Provider=SQLOLEDB.1;Password=pddataabc;Persist Security Info=True;User ID="+UserName+";Data Source=";
		  LoginConstr = LoginConstr +dbServer+";Initial Catalog="+cbzhangtao->Text.Trim() +";Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=LEOMA;Use Encryption for Data=False;Tag with column collation when possible=False";
		  conLand->Connected = false;
		  conLand->ConnectionString = LoginConstr ;
		  try
		  {
			  if (!conLand->Connected ) {
				  conLand->Connected = true;
			  }
		   }
		   catch(...)
		   {

			  MessageBoxA(0,"数据库连接错误！请与管理员联系","错误",MB_ICONERROR);

			  return;
		   }

		   String sql;
		   TADOQuery *aq = new TADOQuery(this);
		   aq->Connection = conLand ;
		   sql = "select ID,Name from SYS_StorageInfo ";
		   aq->Close();
		   aq->SQL->Clear();
		   aq->SQL->Add(sql);
		   aq->Open();
		   cbstorage->Clear();
		   while (!aq->Eof )
		   {
				cbstorage->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger );
				aq->Next();
		   }
		   cbstorage->ItemIndex =  cbstorage->Items->IndexOfObject(0);
		   UserView();
		   }
		  catch(...)
		  {}

}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::sbcancelClick(TObject *Sender)
{
	  pchangepd->Visible = false;
	  plogin->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::sblogcancelClick(TObject *Sender)
{
  	// this->Close();
	ModalResult = mrCancel  ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::edtoldpdKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmLand::edtconfirmpdKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
    	sbok->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::cbstorageChange(TObject *Sender)
{
	if (cbstorage->Text == "") {
		MessageBoxA(0,"请选择店名","错误",MB_ICONERROR);
		return;
	}
	stgid = int(cbstorage->Items->Objects[cbstorage->ItemIndex]);
	UserView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::UserView()
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = conLand ;
	sql = "select ID,name from sys_user where stgID = " + IntToStr(stgid) ;//用户名列表
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbName->Clear();
	while(!aq->Eof)
	{
		cbName->Items->Add(aq->FieldByName("name")->AsAnsiString ) ;
		aq->Next();
	}
	delete aq;
	cbName->ItemIndex =0;
	userid = (int)(cbName->Items->Objects[cbName->ItemIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::cbNameChange(TObject *Sender)
{
	userid = (int)(cbName->Items->Objects[cbName->ItemIndex]);
}
//---------------------------------------------------------------------------

