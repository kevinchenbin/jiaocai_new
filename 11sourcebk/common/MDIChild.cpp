//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MDIChild.h"
#include "PwdForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMDIChild *frmMDIChild;
//---------------------------------------------------------------------------
//键盘钩子     封锁   windows   热键

HHOOK OldHook = NULL;
TfrmMDIChild* g_mdichild = NULL;
/*
long CALLBACK KeyProc(int code, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *pkbhs;
	if (code < 0)
		return CallNextHookEx(OldHook, code, wParam, lParam);

	pkbhs = (KBDLLHOOKSTRUCT*)lParam;
	//拦截到hook
  //	if (g_mdichild != NULL)
 //	{
  //		g_mdichild->OnHotKeyPress(pkbhs->vkCode);
 //	}

	return CallNextHookEx(OldHook, code, wParam, lParam);
}   */


__fastcall TfrmMDIChild::TfrmMDIChild(TComponent* Owner)
	: TForm(Owner)
	, m_app(NULL)
	, m_con(NULL)
	, m_userID(-1)
	, m_storageID(-1)
	, m_allowOperate(false)
	, m_module(MTUnknown)
	, m_oppwd("")
	, m_opName("")
{
  //	OldHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyProc, HInstance, 0);
}

__fastcall TfrmMDIChild::~TfrmMDIChild()
{
	//销毁钩子
   //	UnhookWindowsHookEx(OldHook);
  //	OldHook = NULL;
}
//---------------------------------------------------------------------------

void TfrmMDIChild::Init(TApplication* app, TADOConnection* con)
{
	m_app = app;
	m_con = con;
	m_userID = 0;
	m_storageID = 0;
	ReadAuthorityInfo();
  //	if (!m_allowOperate)
  //	{
  //  	::ShowWindow(Handle, SW_HIDE);
  //  	ShowMessage("您没有权限操作该模块!");
  //		Close();
  //	}
}

void TfrmMDIChild::Init(LandInfo* li)
{
	m_app = li->app;
	m_con = li->con;
	m_userID = li->userID;
	m_storageID = li->storageID;
	ReadAuthorityInfo();
  //	if (!m_allowOperate)
  //	{
  //  	::ShowWindow(Handle, SW_HIDE);
  //  	ShowMessage("您没有权限操作该模块!");
	//	Close();
   // }
}

void __fastcall TfrmMDIChild::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------

void TfrmMDIChild::ReadAuthorityInfo()
{
	qryUserAuthority->Connection = m_con;
	qryUserAuthority->Active = false;
	qryUserAuthority->SQL->Clear();
	String sql;
	sql = "select ";
	switch(m_module)
	{
		case MTUnknown:
			sql = sql + " specialpassword as OpPassword ";
			break;
		case MTStorageMng:
			sql = sql + " Storage as OpPassword";
			break;
		case MTWsaleMng:
			sql = sql + " Wholesale as OpPassword";
			break;
		case MTRetailMng:
			sql = sql + " Retail as OpPassword";
			break;
		case MTFinance:
			sql = sql + " Accounts as OpPassword";
			break;
		case MTOrder:
			sql = sql + " Orders as OpPassword";
			break;
		case MTPur:
			sql = sql + " Procurement as OpPassword";
			break;
		default:
		   sql = sql + " specialpassword as OpPassword ";
			break;
	}
	sql = sql + " from SYS_StorageInfo where id = " + IntToStr(m_storageID) ;
	qryUserAuthority->SQL->Add(sql);
	qryUserAuthority->Active = true;
	if (qryUserAuthority->RecordCount == 1)
	{
		m_oppwd = qryUserAuthority->FieldByName("OpPassword")->AsString.Trim();

	}
	qryUserAuthority->Active = false;
}

bool TfrmMDIChild::CheckOperateAuthority()
{
	bool ret = false;
	TfrmPwd* frm = new TfrmPwd(this);
	if (mrOk == frm->ShowModal())
	{
		if (frm->GetPassword() == m_oppwd)
			ret = true;
		else
		   MessageBoxA(0,"密码错误！","警告",MB_ICONASTERISK);
	}
	return ret;
}



void __fastcall TfrmMDIChild::FormActivate(TObject *Sender)
{
	g_mdichild = this;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMDIChild::FormDeactivate(TObject *Sender)
{
	g_mdichild = NULL;
}
void  TfrmMDIChild::ShowMsg(AnsiString Texts,AnsiString Captions,int type)
{
	switch(type)
	{
	  case 0:
		 MessageBox(0,Texts.c_str() ,Captions.c_str() ,MB_ICONWARNING);  //警告
		 break;
	  case 1:
		 MessageBox(0,Texts.c_str() ,Captions.c_str() ,MB_ICONQUESTION);  //询问
		 break;
	  case 2:
		 MessageBox(0,Texts.c_str() ,Captions.c_str() ,MB_ICONERROR);  //错误
		 break;
	  case 3:
		 MessageBox(0,Texts.c_str() ,Captions.c_str() ,MB_ICONASTERISK);  //提示
		 break;
	}

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

