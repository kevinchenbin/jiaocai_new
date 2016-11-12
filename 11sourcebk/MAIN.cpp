//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "shlwapi.h"
#include "LandForm.h"
#include "customer\customer.h"
#include "sysadmin\sysadmin.h"
#include "bsadmin\bsadmin.h"
#include "catalogadmin\catalogadmin.h"
#include "marketadmin\marketadmin.h"
#include "storageadmin\storageadmin.h"
#include "financeadmin\financeadmin.h"
#include "bsquery\bsquery.h"
#include "dataanalysis\dataanalysis.h"
#include "useradmin\useradmin.h"
#include "tchar.h"
#include "Unitbslock.h"
#include "Unitlock.h"
#include "winnt.h"
#include "bsset.h"
#include "bsadmin\Supplier.h"
#include "saleanalysis\saleanalysis.h"
#include "saleanalysis\Stockanalysis.h"
#include "saleanalysis\retail.h"
#include "saleanalysis\Wsale.h"
#include "saleanalysis\saletime.h"
#include "financial\Unitestartsupclient.h"
#include "localmanage\AreaSet.h"
#include "financial\Unitbalance.h"
#include "membermanager\MemberForm.h"
#include "membermanager\MemberClassSet.h"
#include "membermanager\RecordQuery.h"
#include "membermanager\MemberResult.h"
#include "dbmanage\ResStore.h"
#include "dbmanage\backdatabase.h"
#include "financial\accountdetail.h"
#include "financial\accountquery.h"
#include "financial\accoutnsdue.h"
#include "supplier\suppmanage.h"
#include "supplier\detailemessage.h"
#include "StockCheck.h"
#include "localadjust.h"
#include "storagelocal.h"
#include "Storage\StockalarmSet.h"
#include "userpurview\UnitpurviewManage.h"
#include "ProcureMng.h"
#include "UnitGroup.h"
#include "Unituser.h"
#include "SpecialPasswordForm.h"
#include "UnitClient.h"
#include "Intelligence\UnitIntelligence.h"
#include "MemberJifenMng.h"
#include "Moneydiscount.h"
#include "retailbsset.h"
#include "orderbsset.h"
#include "storagebsset.h"
#include "salebsset.h"
#include "Unitcheckquery.h"
#include "UnitWSSet.h"
#include "CustomertypeSet.h"
#include "ClientBackdot.h"
#include "Staffmanage.h"
#include "systemset.h"
#include "PwdForm.h"
#include "diaoboset.h"
#include "common\Print.h"
#include "UnitMyWork.h"
#include "procureset.h"
#include "UnitLog.h"
#include "Unitclientbijiao.h"
#include "Unitabout.h"
#include "Unitshengji.h"
#include "Unitbaobiao.h"
#include "UnitFormView.h"
#include "Unitjxcbijiao.h"
#include "UnitTaskManage.h"
#include "Unit1orderyuji.h"
#include "Unit1caigouyuji.h"
#include "Unitrate.h"
#include "Unitdaohuorate.h"
#include "Unitsiglebook.h"
#include "Unittongqisale.h"
#include "Unittongqiruku.h"
#include "global.h"
#include "UnitStorToStor.h"
#include "setdiscount.h"
#include "Stockalarm.h"
#include "stockalarmbsset.h"
#include "unitprinttitle.h"
#include "Unitwanglai.h"
#include "clientadddot.h"
#include "UnitSupplierMerge.h"
#include "UnitCbprice.h"
#include "Unitkuchengjizhuan.h"
#include <winuser.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "RzGroupBar"
#pragma link "RzPanel"
#pragma link "RzSplit"
#pragma link "RzButton"
#pragma link "RzCommon"
#pragma link "RzAnimtr"
#pragma link "RzStatus"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------


__fastcall TfrmMain::TfrmMain(TComponent *Owner)
	: TForm(Owner)
{
	OriginalClientWndProc = 0;
	jiaojie = 0;
	NewClientWndProc = (FARPROC)MakeObjectInstance(ClientWndProc);
	OriginalClientWndProc=reinterpret_cast<void*>(SetWindowLong(ClientHandle ,GWL_WNDPROC,reinterpret_cast<LONG>(NewClientWndProc)));


}
//---------------------------------------------------------------------------
String TfrmMain::Disc()
{
	String Bk;
   TADOQuery * aq;
   aq = new TADOQuery(this);
   aq->Connection = frmLand->conLand  ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add("select bk from sys_bsset where name ='xiaoshudian'");
   aq->Open();
   Bk =  aq->FieldByName("bk")->AsAnsiString ;
   delete aq;
   return Bk ;

}
void __fastcall TfrmMain::FileExit1Execute(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N8Click(TObject *Sender)
{
	//入库单格式

	ManagePrint(Application, frmLand->conLand, 1,frmLand->GetStorageID());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N9Click(TObject *Sender)
{
	//批销单格式
	ManagePrint(Application, frmLand->conLand, 2,frmLand->GetStorageID());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N10Click(TObject *Sender)
{
	//零售小票格式
	if (CheckPower("打印管理")) {
		ManagePrint(Application, frmLand->conLand, 3,frmLand->GetStorageID());
	}
	else
	{
    	ShowNoPower();
	}

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::N11Click(TObject *Sender)
{
	//业务设置
  /*	if (CheckPower("业务设置")) {
		frmbsset = new Tfrmbsset(Application,frmLand->conLand);
		frmbsset->ShowModal();
		delete frmbsset;
	}
	else
	{
		ShowNoPower();
	}      */

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::POS1Click(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N26Click(TObject *Sender)
{
	//折扣控制
	ControlDiscount(Application, frmLand->conLand);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N42Click(TObject *Sender)
{
   //供应商付款单查询

   if (CheckPower("付款查询")) {
		TAccQuery * frm = new TAccQuery(Application,1,frmLand->conLand,frmLand->GetStorageID(),frmLand->GetMaster());
		frm->Show();
   }
   else
   {
		ShowNoPower();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N47Click(TObject *Sender)
{
	//客户付款单查询

	if (CheckPower("收款查询")) {
		TAccQuery * frm = new TAccQuery(Application,2,frmLand->conLand,frmLand->GetStorageID(),frmLand->GetMaster());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N58Click(TObject *Sender)
{
	// 当日结账

	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("当日结账统计")) {
		CheckQuery(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void ErrorExit(LPTSTR lpszFunction)
{
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;

    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR));
    wsprintf((LPTSTR)lpDisplayBuf,
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw);
}
void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	//将子窗体全部关闭
	HWND hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);
	while (hWnd != NULL)
	{

		if(MessageBox(0,"有未关闭窗口，是否退出？,确认将关闭整个系统！" ,"确认" ,MB_ICONQUESTION|MB_OKCANCEL)==1)
		{
			::SendMessage(hWnd, WM_CLOSE, 0, 0);
			Application->ProcessMessages();
			hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
		}
		else
		{
			Action = caNone;
			return;
		}
	}
	//检测是否含有未关闭的子窗体
	bool allclose = false;
	hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);
	TCHAR buf[MAX_PATH+1];
	while (hWnd != NULL)
	{
		::ZeroMemory(buf, sizeof(buf));
		if (::GetClassName(hWnd, buf, MAX_PATH) > 0)
		{
			if (StrCmp(_T("TfrmRetailMng"), buf) == 0)
			{
				allclose = true;
				break;
			}
		}
		hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
	}
	//如果有则不能关闭主窗体
	if (allclose)
	{
		Action = caNone;
	}
}

void __fastcall TfrmMain::FormPaint(TObject *Sender)
{
//	Canvas->StretchDraw(ClientRect,imgMainbkg->Picture->Graphic);
	//  	  Graphics::TBitmap   *   pBitmap=new   Graphics::TBitmap();
	//  pBitmap->LoadFromFile("D:\\ui.bmp");
	 // Image1->Picture->Assign(pBitmap);
	 // Canvas->Draw(0,0,Image1->Picture->Graphic);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormResize(TObject *Sender)
{
//	::InvalidateRect(ClientHandle,NULL,FALSE);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N60Click(TObject *Sender)
{
	//用户组权限设置

	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	SetAuthority(&li);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniN48Click(TObject *Sender)
{
	//特俗口令设置

	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("特殊口令设置")) {
    	TfrmSpecialPassword *frm = new TfrmSpecialPassword(Application);
		frm->Init(&li);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------






void __fastcall TfrmMain::FormShow(TObject *Sender)
{
   Timer1->Enabled = true;

 //  GetMessage->Enabled = true;;
  //	Image1->Picture->LoadFromFile("D:\\1.jpg");
  //	Discstr = Disc();
  //	statebar->Panels->Items[1]->Text = frmLand->GetUserName();

	if (frmLand->GetStorageID()==3) {
     	frmMain->Caption="先行者wise 书业智管平台--------墨嘉C网专业版";

	}



	LoadPUI();
	PUIName= "imageui";
	GetPowerList(frmLand->GetUserID());
	stgname->Caption = IntToStr(frmLand->GetStorageID()) + "-" + frmLand->cbstorage->Text ;
	lbuser->Caption = frmLand->GetUserName();
	lbdate->Caption = DateToStr(Now());

	MessageInfo = new TStringList();
	MessageInfo->AddObject("msg1",msg1);
	MessageInfo->AddObject("msg2",msg2);
	MessageInfo->AddObject("msg3",msg3);
	MessageInfo->AddObject("msg4",msg4);
	MessagePic = new TStringList();
	MessagePic->AddObject("g1",g1) ;
	MessagePic->AddObject("g2",g2) ;
	MessagePic->AddObject("g3",g3) ;
	MessagePic->AddObject("g4",g4) ;
	aqmsg->Connection = frmLand->conLand ;
	LoadMyMessage();
	Time();
	LoadMyWork(frmLand->GetUserID());

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N71Click(TObject *Sender)
{        //区域设置

}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N73Click(TObject *Sender)
{
  //数据备份

  if (CheckPower("数据备份")) {
  	TBakDatabase *frm = new TBakDatabase(Application,frmLand->conLand);
	frm->ShowModal() ;
	delete frm;
  }
  else
  {
	ShowNoPower();
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N74Click(TObject *Sender)
{
  //数据恢复

  if (CheckPower("数据恢复")) {
  	TResDatabase *frm = new TResDatabase(Application , frmLand->conLand );
	frm->ShowModal();
	delete frm;
  }
  else
  {
	ShowNoPower();
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N44Click(TObject *Sender)
{          //客户收款结算


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientWndProc(TMessage&   Message)
{

	 //不显示滚动条
		ShowScrollBar(frmMain->ClientHandle,SB_BOTH,false);

        //   Then   call   the   original   WndProc()   for   the   other   messages
        if(OriginalClientWndProc   !=   0)
        {
              Message.Result
                =   CallWindowProc(reinterpret_cast<FARPROC>(OriginalClientWndProc),
                                                  ClientHandle,
												  Message.Msg,
                                                  Message.WParam,
                                                  Message.LParam);
        }
}
//---------------------------------------------------------------------------

void TfrmMain::LoadPUI()
{
		PanelList = new TStringList();
		for   (int   i=0; i < frmMain->ComponentCount-1 ; i++)
	   {
		 TImage*   temp = dynamic_cast<TImage*>(Components[i]);
		 if (temp != NULL) {
		   if (temp->Tag >= 100 && temp->Tag <= 200) {
		   if (temp->Name != "imageui") {
			 temp->Visible = false;
			 temp->Align = TAlign::alClient;
		   }
		   PanelList->AddObject(temp->Name , temp);
		 }
		 }
	   }
}
void TfrmMain::Display(AnsiString PUIName)
{
  int j,i;
  j = PanelList->IndexOf(PUIName);    //取出要显示的panel

   TImage * pvisable = (TImage *)PanelList->Objects[j];
   pvisable->Visible  = true;
 //  imageui->Canvas->StretchDraw(Rect(0,42,1012 ,549),pvisable->Picture->Graphic);
 //  Rect(
   //	Graphics::TBitmap   *   pBitmap=new   Graphics::TBitmap();
  //pBitmap->
  //Image1->Picture->Assign(pBitmap);
   return;


  for (i = 0; i < PanelList->Count; i++) {      //设置要显示的panel visible为true

	 TImage * pvisable = (TImage *)PanelList->Objects[i];
	 if (i==j) {
		 pvisable->Visible = True;
		// pvisable->Align = TAlign::alTop ;
	 } else
	 {

		 pvisable->Visible = false;


	 }

  }


}
void TfrmMain::Disappear(AnsiString PUIName)
{

   int j,i;
  j = PanelList->IndexOf(PUIName);    //取出要显示的panel

   TImage * pvisable = (TImage *)PanelList->Objects[j];
   pvisable->Visible  = false;


}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::imagelsMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{


     	uix = X;
	uiy = Y;
	if (uix >212 && uix < 265 && uiy >17 && uiy < 30) {          //会员资料
		Screen->Cursor =  Controls::crHandPoint;

	} else
		  {
			Screen->Cursor =  Controls::crDefault  ;
		  }
		if (uix >310 && uix < 361 && uiy >17 && uiy < 30) {          //会员充值
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >402 && uix < 479 && uiy >17 && uiy < 30) {          //会员充值查询
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >351 && uix < 411 && uiy >174 && uiy < 219) {          //POS 零售
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >351 && uix < 412 && uiy >310 && uiy < 351) {          //pos 零售退货
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >540 && uix < 592 && uiy >241 && uiy < 283) {          //零售员交接班
		Screen->Cursor =  Controls::crHandPoint ;

	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imageuiClick(TObject *Sender)
{
	Screen->Cursor =  Controls::crDefault   ;
	/*  if (uix > 6 && uix < 154 ) {
	  if (uiy >103 && uiy < 130) {  //采购管理

		Display("imagecg");
	  }
	  if (uiy > 170 && uiy < 196) {    //批销
		 Display("imagepx");
	  }
	  if (uiy > 137 && uiy < 163) { //库存
		   Display("imagekc");
	  }
	  if (uiy > 204 && uiy < 229) {     //零售
			 Display("imagels");
	  }
	  if (uiy > 236 && uiy < 261) {   //往来
	  Display("imagewl");

	  }
	  if (uiy > 271 && uiy < 296) {    //统计
	  Display("imagetj");

	  }

	}*/
   //}
   if  ((((TImage*)(Sender))->Name == "imagext")) {
	Screen->Cursor = Controls:: crDefault  ;
		   if (uix >350 && uix < 407 && uiy >239 && uiy < 296) {          //任务管理
			  renwu->Execute()  ;

		  }

		  if (uix >516 && uix < 576 && uiy >243 && uiy < 294) {          //文档管理
			   wengdang->Execute()  ;

		  }
		  if (uix >689 && uix < 741 && uiy >245	&& uiy < 307) {          //在线交流
			  jiaoliu->Execute()  ;

		  }
   }

   //商务通
	if  ((((TImage*)(Sender))->Name == "imagesft")) {
		Screen->Cursor = Controls:: crDefault  ;
	if (uix >405 && uix < 485 && uiy >119 && uiy < 151) {     //未发货超期提醒
			ordertixing->Execute();
		}
		if (uix >661 && uix < 736 && uiy >111 && uiy < 173) {          //未到货超期提醒
		//  wengdang->Execute()  ;
			caigoutixing->Execute();
		}
		  if (uix >407 && uix < 484 && uiy >239 && uiy < 288) {          //发货比率分析
		//wengdang->Execute()  ;
			fahuorate->Execute();
		}
		  if (uix >662 && uix < 733 && uiy >239 && uiy < 280) {          //到货比率分析
		//wengdang->Execute()  ;
			daohuorate->Execute();
		}
		  if (uix >407 && uix < 477 && uiy >371 && uiy < 410) {          //销售同期比较
		//wengdang->Execute()  ;
			saletongqi->Execute();
		}
		  if (uix >668 && uix < 740 && uiy >372 && uiy < 416) {          //供货同期比较
	  //	wengdang->Execute()  ;
			//Supplierbijiao->Execute();
			rukutongqi->Execute();
		}
   }






   if  ((((TImage*)(Sender))->Name == "imagesearch")) {
	Screen->Cursor = Controls:: crDefault  ;
		 if (uix >324 && uix < 385 && uiy >164 && uiy < 214) {          //库存查询
			   StorageSearch->Execute()  ;

		  }
		  if (uix >480 && uix < 541 && uiy >165 && uiy < 217) {      //订单查询
			   popmorder->Popup(600,310);

		  }
		  if (uix >642 && uix < 699 && uiy >170 && uiy < 213) {          //采购查询
			   stocksearch->Execute()  ;

		  }
		  if (uix >784 && uix < 850 && uiy >172 && uiy < 217) {          //入库查询
			   rikusearch->Execute()  ;

		  }

		  if (uix >323 && uix < 386 && uiy >330 && uiy < 381) {              //发货查询
			   salesearch->Execute()  ;

		  }
		  if (uix >473 && uix < 543 && uiy >327 && uiy < 377) {          //POS零售查询
			  posretailsearch->Execute()  ;

		  }

		  if (uix >634 && uix < 707 && uiy >325 && uiy < 384) {          //盘点查询
			  storagechecksearch->Execute()  ;

		  }
		  if (uix >776 && uix < 851 && uiy >332 && uiy < 377) {          //配送查询
			   peishongsearch->Execute()  ;

		  }
   }
   if ((((TImage*)(Sender))->Name == "imagetj")) {
	Screen->Cursor = Controls:: crDefault  ;
		  if (uix >288 && uix < 356 && uiy >107 && uiy < 153) {          //零售与退货
			 retailandback->Execute()  ;

		  }else
		  {
			 Screen->Cursor =  Controls::crDefault  ;
		  }
		  if (uix >436 && uix < 511 && uiy >109 && uiy < 157) {          //批销与退货
			   saleandback->Execute()  ;

		  }


		  if (uix >662 && uix < 729 && uiy >114 && uiy < 160) {          //进销存分析
				jingxiaochunfenxie->Execute()  ;

		  }
		  if (uix >812 && uix < 880 && uiy >111 && uiy < 162) {          //未动库存分析
			  weidongkuchun->Execute()  ;

		  }
		  if (uix >821 && uix < 874 && uiy >256 && uiy < 307) {          //供应商阶段结算分析
			Supplierjiduanfexie->Execute()  ;

		  }
			  if (uix >669 && uix < 732 && uiy >251 && uiy < 308) {          //客户阶段结算分析
			   Clientjieduanfexie->Execute()  ;

		  }
					  if (uix >434 && uix < 497 && uiy >258 && uiy < 310) {          //零售汇总分析
			   retailhuizhongfengxie->Execute()  ;

		  }
			if (uix >438 && uix < 487 && uiy >400 && uiy < 451) {          //业务排行榜
			 yefupaihangbang->Execute()  ;

		  }
			if (uix >820 && uix < 875 && uiy >404 && uiy < 450) {          //销售书排行与毛利分析
			   changxiaobook->Execute()  ;

		  }
		  if (uix >669 && uix < 732 && uiy >404 && uiy < 450) {          // 单品分析
			   siglebook->Execute();
		  }
			if (uix >288 && uix < 342 && uiy >255 && uiy < 311) {          //销售时段汇总统计
			 saletimehuizhong->Execute()  ;

		  }
			if (uix >289 && uix < 341 && uiy >399 && uiy < 451) {          //销售统计报表
			   saletongjireport->Execute()  ;

		  }
   }
   if  (((TImage*)(Sender))->Name == "imagewl") {
	Screen->Cursor = Controls:: crDefault  ;
        if (uix >321 && uix < 387 && uiy >156 && uiy < 215) {          //供应商资料
			  SupplierInfo->Execute();

		  }
		  if (uix >487 && uix < 542 && uiy >167 && uiy < 213) {          //客户资料
			   ClientInfo->Execute();

		  }


		  if (uix >645 && uix < 707 && uiy >169 && uiy < 216) {          //业务员管理
			salermanage->Execute();

		  }
		  if (uix >788 && uix < 838 && uiy >167 && uiy < 214) {          //信用管理
			  creditManage->Execute();

		  }
		  if (uix >318 && uix < 381 && uiy >321 && uiy < 381) {          //会员资料
			  MemberInfo->Execute();

		  }
			  if (uix >487 && uix < 554 && uiy >326 && uiy < 383) {          //会员充值
			   Memberchongzhi->Execute();

		  }
			  if (uix >643 && uix < 714 && uiy >327 && uiy < 381) {          //会员充值查询
			   MemberchongziSearch->Execute();

		  }
   }
   if (((TImage*)(Sender))->Name == "imagecf") {
	Screen->Cursor = Controls:: crDefault  ;
		 if (uix >316 && uix < 373 && uiy >75 && uiy < 115) {     //供应商往来期初
			financestart->Execute();
		  }
			  if (uix >446 && uix < 507 && uiy >71 && uiy < 119) {    //应付汇总
				yihutotal->Execute();
		 }

			  if (uix >317 && uix < 373 && uiy >180 && uiy < 228) {        //供应商往来对帐
			  supplierduizhang->Execute();
		  }

			  if (uix >445 && uix < 505 && uiy >181 && uiy < 321) {        //应付明细
			   yingfudetail->Execute();
		  }
			  if (uix >646 && uix < 703 && uiy >136 && uiy < 173) {        //供应商结算
			  Supplierjieshuan->Execute();
		  }
				  if (uix >803 && uix < 860 && uiy >141 && uiy < 177) {        //供应商结算查询
			  SupplierjieShuanSearch->Execute();
		  }
				  if (uix >312 && uix < 368 && uiy >330 && uiy < 375) {        //客户往来期初
			  ClientfinanceStart->Execute();
		  }
			  if (uix >454 && uix < 502 && uiy >329 && uiy < 375) {        //应收汇总
			 yingshouhuizhong->Execute();
		  }

			  if (uix >311 && uix < 366 && uiy >440 && uiy < 486) {        //客户往来对帐
			  ClientWanglaiduizhang->Execute();
		  }

			  if (uix >454 && uix < 502 && uiy >444 && uiy < 485) {        //应收明细
			 yingshoudetail->Execute();
		  }

			  if (uix >657 && uix < 703 && uiy >378 && uiy < 420) {        //客户结算
			 ClientJieShuan->Execute();
		  }
			if (uix >804 && uix < 855 && uiy >380 && uiy < 422) {        //客户结算查询
				Clientjieshuansearch->Execute();
			}

   }
	  if (((TImage*)(Sender))->Name == "imagecg") {
			  Screen->Cursor = Controls:: crDefault  ;
			 if (uix >195 && uix < 248 && uiy >15 && uiy < 27) {     //品目管理
			BreedManage->Execute();
		  }
			  if (uix >278 && uix < 331 && uiy >15 && uiy < 27) {    //品目类别管理                                                                别管理
				breedType->Execute();
		 }
		 if (uix >367 && uix < 429 && uiy >15 && uiy < 27) {    //品目类别管理                                                                别管理
				pressmanage->Execute();
		 }

			  if (uix >461 && uix < 526 && uiy >15 && uiy < 27) {        //供应商资料
				SupplierInfo->Execute();
		  }

			  if (uix >562 && uix < 619 && uiy >15 && uiy < 27) {        //区域管理
				LocalManage->Execute();
		  }
			  if (uix >648 && uix < 707 && uiy >15 && uiy < 27) {        //库位资料
				StorageInfo->Execute();
		  }
				  if (uix >289 && uix < 341 && uiy >165 && uiy < 208) {        //一般采购单
				SampleStock->Execute();
		  }
				  if (uix >463 && uix < 527 && uiy >120 && uiy < 161) {        //一般入库
					samplestorage->Execute();
		  }
			  if (uix >473 && uix < 528 && uiy >233 && uiy < 280) {        //入库退货
				storageback->Execute();
		  }

			  if (uix >289 && uix < 342 && uiy >300 && uiy < 340) {        //智能采购
					smartStock->Execute();
		  }

			  if (uix >475 && uix < 528 && uiy >354 && uiy < 399) {        //智能入库
					Smartstorage->Execute();
		  }

			  if (uix >661 && uix < 712 && uiy >233 && uiy < 281) {        //供应商阶段结算分析
					Supplierjiduanfexie->Execute();
		  }
			if (uix >827 && uix < 874 && uiy >234 && uiy < 279) {        //付款结算
					Supplierjieshuan->Execute();
			}

	  }


	 if (((TImage*)(Sender))->Name == "imagels") {
	  Screen->Cursor = Controls:: crDefault  ;
		if (uix >212 && uix < 265 && uiy >17 && uiy < 30) {          //会员资料
		MemberInfo->Execute();

	}
		if (uix >310 && uix < 361 && uiy >17 && uiy < 30) {          //会员充值
		Memberchongzhi->Execute();

	}
		if (uix >402 && uix < 479 && uiy >17 && uiy < 30) {          //会员充值查询
		MemberchongziSearch->Execute();

	}
		if (uix >351 && uix < 411 && uiy >174 && uiy < 219) {          //POS零售
		Posretail->Execute();

	}
		if (uix >351 && uix < 412 && uiy >310 && uiy < 351) {          //pos零售退货
		retailBack->Execute();

	}
		if (uix >540 && uix < 592 && uiy >241 && uiy < 283) {          //零售员交接班
		jiaojieban->Execute();

	}


   }
	   if (((TImage*)(Sender))->Name == "imagekc") {
		Screen->Cursor = Controls:: crDefault  ;
	   if (uix >211 && uix < 262 && uiy >14 && uiy < 27) {     //库位资料

		   StorageInfo->Execute();

		  }
			  if (uix >307 && uix < 358 && uiy >17 && uiy < 27) {    //盘点查询
				 storagechecksearch->Execute()  ;
		 }

			  if (uix >505 && uix < 559 && uiy >230 && uiy < 274) {        //库存预警
				TPoint p;
				TPoint pt;
				p.x = 560;
				p.y= 310;
				pt = ClientToScreen(p);
				pmstockalarm->Popup(pt.x,pt.y);
		  }

			  if (uix >661 && uix < 708 && uiy >326 && uiy < 366) {        //单品库存量调整
			 onestorageNumberadjust->Execute();
		  }
			  if (uix >351 && uix < 403 && uiy >321 && uiy < 368) {        //实库盘点
			  shikupandian->Execute();
		  }
				  if (uix >654 && uix < 708 && uiy >142 && uiy < 185) {        //库位调整
			  storageLocaladjust->Execute();
		  }
				  if (uix >347 && uix < 398 && uiy >142 && uiy < 184) {        //局部盘点
			  xuyipandian->Execute();
		  }

		}

		   if (((TImage*)(Sender))->Name == "imagepx") {
			Screen->Cursor = Controls:: crDefault  ;
		if (uix >209 && uix < 263 && uiy >20 && uiy < 30) {          //客户资料
		 ClientInfo->Execute();

	 }
		if (uix >305 && uix < 356 && uiy >20 && uiy < 30) {          //区域管理
	LocalManage->Execute();

	}
		if (uix >400 && uix < 453 && uiy >20 && uiy < 30) {          //客户类型
		ClientClass->Execute();

	}
		if (uix >491 && uix < 559 && uiy >20 && uiy < 30) {          //业务员管理
		salermanage->Execute();

	}
		if (uix >609 && uix < 662 && uiy >20 && uiy < 30) {          //信用管理
	creditManage->Execute();

	}
		if (uix >273 && uix < 325 && uiy >150 && uiy < 197) {          //客户订单
		ClientOrder->Execute();

	}
		if (uix >276 && uix < 337 && uiy >339 && uiy < 378) {          //网上订单
		wangshangOrder->Execute();

	}

		if (uix >461 && uix < 522 && uiy >121 && uiy < 161) {          //一般发货
		samplesale->Execute();

	}
		if (uix >617 && uix < 697 && uiy >130 && uiy < 166) {          //发货退货
		saleback->Execute();

	}
		if (uix >798 && uix < 851 && uiy >125 && uiy < 168) {           //当日发货快捷结算
		Dangrijieshuan->Execute();

	}
		if (uix >536 && uix < 602 && uiy >254 && uiy < 293) {           //智能发货
		smartSale->Execute();

	}
		if (uix >456 && uix < 519 && uiy >398 && uiy < 438) {           //连锁配送
		TPoint p;
		TPoint pt;
		p.x = 520;
		p.y= 438;
		pt = ClientToScreen(p);
		pmpeishong->Popup(pt.x,pt.y);
	   //	peisong->Execute();

	}
		if (uix >612 && uix < 675 && uiy >400 && uiy < 438) {           //样/赠书处理
		samplebook->Execute();

	}
		if (uix >797 && uix < 859 && uiy >264 && uiy < 303) {           //客户阶段结算分析
		Clientjieduanfexie->Execute();

	}
		if (uix >798 && uix < 857 && uiy >401 && uiy < 440) {           //收款结算
		ClientJieShuan->Execute();

	}

   }

	if (((TImage*)(Sender))->Name == "imageyx") {
	 Screen->Cursor = Controls:: crDefault  ;             //营销
		 if (uix >304 && uix < 358 && uiy >144 && uiy < 192) {     //零售类别促销
			retailclassPromotion->Execute();
		  }

			  if (uix >459 && uix < 520 && uiy >153 && uiy < 200) {    //零售购物金额促销
				Retailbuy->Execute();
		 }

			  if (uix >618 && uix < 679 && uiy >154 && uiy < 195) {        //会员类型单品促销
			 MemberoneProduct->Execute();
		  }

			  if (uix >775 && uix < 819 && uiy >157 && uiy < 192) {        //会员积分管理
			 Memberjifen->Execute();
		  }
			  if (uix >314 && uix < 364 && uiy >334 && uiy < 381) {        //批销单品折扣
			  SaleOneProduct->Execute();
		  }
				  if (uix >462 && uix < 522 && uiy >339 && uiy < 384) {        //批销附加折扣
			  SaleAddPoint->Execute();
		  }
				  if (uix >618 && uix < 682 && uiy >338 && uiy < 387) {        //批销现场返点
			  SaleNowbackDot->Execute();
		  }
			  if (uix >770 && uix < 837 && uiy >335 && uiy < 386) {        //批销年度返点
			  SaleyearBackDot->Execute();
		  }

    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::i(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	 uix = X;
	 uiy = Y;


	   if (((TImage*)(Sender))->Name == "imagecg") {

		  if (uix >451 && uix < 489 && uiy >220 && uiy < 290) {     //入库单
				Screen->Cursor =  Controls::crHandPoint ;
		  }else
		  {
			Screen->Cursor =  Controls::crDefault  ;
		  }
			 if (uix > 451 && uix < 489 && uiy > 305 && uiy < 360) {   //入库退货单
				Screen->Cursor =  Controls::crHandPoint ;
			 }
			 if (uix >609 && uix < 653 && uiy >260 && uiy < 320)  {    //供商阶段分析
				Screen->Cursor =  Controls::crHandPoint ;
		 }

			  if (uix >761 && uix < 822 && uiy >244 && uiy < 310) {        //付款结算
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >202 && uix < 264 && uiy >15 && uiy < 29) {        //品目管理
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >284 && uix < 345 && uiy >15 && uiy < 29)  {        //类别管理
			 Screen->Cursor =  Controls::crHandPoint ;
		  }

			if (uix >368 && uix <447 && uiy >15 && uiy < 29){         //供应商
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			 if (uix >473 && uix < 532 && uiy >15 && uiy < 29){          //区域
			 Screen->Cursor =  Controls::crHandPoint ;
		  }

			if (uix >213 && uix < 274 && uiy >588 && uiy < 603) {          //入库查询
			 Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >646 && uix < 710 && uiy >15 && uiy < 29) {          //库位
			 Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >556 && uix < 619 && uiy >15 && uiy < 29) {          //版别
			 Screen->Cursor =  Controls::crHandPoint ;
		  }
			 if (uix > 285 && uix < 340 && uix >257 && uiy <337) {     //一般采购
				Screen->Cursor =  Controls::crHandPoint ;
			 }

	  }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagekcMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	 uix = X;
	 uiy = Y;

	   if (uix >211 && uix < 262 && uiy >14 && uiy < 27) {     //库位资料
			Screen->Cursor =  Controls::crHandPoint ;
		  }else
		  {
			Screen->Cursor =  Controls::crDefault  ;
		  }
			  if (uix >307 && uix < 358 && uiy >17 && uiy < 27) {    //盘点查询
				Screen->Cursor =  Controls::crHandPoint ;
		 }

			  if (uix >505 && uix < 559 && uiy >230 && uiy < 274) {        //库存预警
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >661 && uix < 708 && uiy >326 && uiy < 366) {        //单品库存量调整
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >351 && uix < 403 && uiy >321 && uiy < 368) {        //实库盘点
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >654 && uix < 708 && uiy >142 && uiy < 185) {        //库位调整
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >347 && uix < 398 && uiy >142 && uiy < 184) {        //局部盘点
			  Screen->Cursor =  Controls::crHandPoint ;
		  }


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagepxMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	uix = X;
	uiy = Y;

	//			Label1->Caption = IntToStr(X);
	//	Label2->Caption = IntToStr(Y);
	if (uix >209 && uix < 263 && uiy >20 && uiy < 30) {          //客户资料
		Screen->Cursor =  Controls::crHandPoint ;

	}else
	{
		Screen->Cursor  = Controls::crDefault  ;
	}
		if (uix >305 && uix < 356 && uiy >20 && uiy < 30) {          //区域管理
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >400 && uix < 453 && uiy >20 && uiy < 30) {          //客户类型
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >491 && uix < 559 && uiy >20 && uiy < 30) {          //业务员管理
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >609 && uix < 662 && uiy >20 && uiy < 30) {          //信用管理
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >273 && uix < 325 && uiy >150 && uiy < 197) {          //客户订单
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >276 && uix < 337 && uiy >339 && uiy < 378) {          //网上订单
		Screen->Cursor =  Controls::crHandPoint ;

	}

		if (uix >461 && uix < 522 && uiy >121 && uiy < 161) {          //一般发货
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >617 && uix < 697 && uiy >130 && uiy < 166) {          //发货退货
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >798 && uix < 851 && uiy >125 && uiy < 168) {           //当日发货快捷结算
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >536 && uix < 602 && uiy >254 && uiy < 293) {           //智能发货
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >456 && uix < 519 && uiy >398 && uiy < 438) {           //主动配货
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >612 && uix < 675 && uiy >400 && uiy < 438) {           //样/赠书处理
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >797 && uix < 859 && uiy >264 && uiy < 303) {           //客户阶段结算分析
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >798 && uix < 857 && uiy >401 && uiy < 440) {           //收款结算
		Screen->Cursor =  Controls::crHandPoint ;

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagetjMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	 uix = X;
	 uiy = Y;
	  //Label1 ->Caption = IntToStr(uix);
	 //Label2->Caption = IntToStr(uiy);


	  if (uix >288 && uix < 356 && uiy >107 && uiy < 153) {          //零售与退货
			  Screen->Cursor =  Controls::crHandPoint ;

		  }else
		  {
			 Screen->Cursor =  Controls::crDefault  ;
		  }
		  if (uix >436 && uix < 511 && uiy >109 && uiy < 157) {          //批销与退货
			   Screen->Cursor =  Controls::crHandPoint ;

		  }


		  if (uix >662 && uix < 729 && uiy >114 && uiy < 160) {          //进销存分析
				Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >812 && uix < 880 && uiy >111 && uiy < 162) {          //未动库存分析
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >821 && uix < 874 && uiy >256 && uiy < 307) {          //供应商阶段结算分析
			  Screen->Cursor =  Controls::crHandPoint ;

		  }
			  if (uix >669 && uix < 732 && uiy >251 && uiy < 308) {          //客户阶段结算分析
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
					  if (uix >434 && uix < 497 && uiy >258 && uiy < 310) {          //零售汇总分析
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
			if (uix >438 && uix < 487 && uiy >400 && uiy < 451) {          //业务排行榜
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
			if (uix >820 && uix < 875 && uiy >404 && uiy < 450) {          //销售书排行与毛利分析
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >669 && uix < 732 && uiy >404 && uiy < 450) {          // 单品分析
			   Screen->Cursor =  Controls::crHandPoint ;
		  }
		  if (uix >288 && uix < 342 && uiy >255 && uiy < 311) {          //销售时段汇总统计
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
			if (uix >289 && uix < 341 && uiy >399 && uiy < 451) {          //销售统计报表
			   Screen->Cursor =  Controls::crHandPoint ;

		  }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagewlMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	 uix = X;
	 uiy = Y;
	 //	 Label1->Caption = IntToStr(X);
	// Label2->Caption = IntToStr(Y);

	  if (uix >321 && uix < 387 && uiy >156 && uiy < 215) {          //供应商资料
			  Screen->Cursor =  Controls::crHandPoint ;

		  }else
		  {
			Screen->Cursor =  Controls::crDefault  ;

		  }
		  if (uix >487 && uix < 542 && uiy >167 && uiy < 213) {          //客户资料
			   Screen->Cursor =  Controls::crHandPoint ;

		  }


		  if (uix >645 && uix < 707 && uiy >169 && uiy < 216) {          //业务员管理
				Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >788 && uix < 838 && uiy >167 && uiy < 214) {          //信用管理
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >318 && uix < 381 && uiy >321 && uiy < 381) {          //会员资料
			  Screen->Cursor =  Controls::crHandPoint ;

		  }
			  if (uix >487 && uix < 554 && uiy >326 && uiy < 383) {          //会员充值
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
			  if (uix >643 && uix < 714 && uiy >327 && uiy < 381) {          //会员充值查询
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
				

}
//---------------------------------------------------------------------------


void TfrmMain::GetPowerList(int UserID)
{
   String sql;
   sql = "select D.ActionName from sys_usergroup A join SYS_group B On A.GroupID = B.ID "
		 " join SYS_GroupAction C on B.ID = C.GroupID "
		 " join sys_action D on C.ActionID = D.Code "
		 " where A.UserID  =" + IntToStr(UserID);
   PowerList = new TStringList();

   TADOQuery *aq = new TADOQuery(Application);
   aq->Connection = frmLand->conLand ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   while(!aq->Eof)
   {

	 PowerList->AddObject(aq->FieldByName("ActionName")->AsAnsiString.Trim() ,(TObject*)1);
	 aq->Next();
   }
   delete aq;
}
BOOL TfrmMain::CheckPower(String ModalName)
{

  int i = PowerList->IndexOf(ModalName);
  if (i<0) {
	  return false;
  }else
  {
	 return true;
  }

}
void TfrmMain::ShowNoPower()
{
   MessageBoxA(0,"无权限操作此模块,请与管理员联系!","警告",MB_ICONASTERISK);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imageuiMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{

	 uix = X;
	 uiy = Y;

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N89Click(TObject *Sender)
{

	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.UserName = frmLand->cbName->Text;
	Saleduibi(&li);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N90Click(TObject *Sender)
{
	//会员积分管理

	if (CheckPower("会员积分管理")) {
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		TfrmMemberjifen *frm = new TfrmMemberjifen(Application,li.con) ;
		frm->stgid = li.storageID ;
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N92Click(TObject *Sender)
{
	//入库业务设置

	if (CheckPower("入库业务设置")) {
		Tfrmstoragebsset *frm = new Tfrmstoragebsset(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N93Click(TObject *Sender)
{
	//零售业务设置

	if (CheckPower("零售业务设置")) {
		Tfrmretailbsset *frm = new Tfrmretailbsset(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N94Click(TObject *Sender)
{
	//批销业务设置

	if (CheckPower("批销业务设置")) {
		Tfrmsalebsset *frm = new Tfrmsalebsset(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N95Click(TObject *Sender)
{
	//订单业务设置

	if (CheckPower("订单业务设置")) {
		Tfrmorderbsset *frm = new Tfrmorderbsset(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TfrmMain::N96Click(TObject *Sender)
{
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("入库供应商修改")) {
		SupplierModify(&li);
	}
	else
	{
    	ShowNoPower();
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N99Click(TObject *Sender)
{

	if (CheckPower("会员类别打折")) {
		MemberDiscount(Application, frmLand->conLand,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N105Click(TObject *Sender)
{
	//供应商类型

	if (CheckPower("供应商类型")) {
		Tfrmcustomertype *frm = new Tfrmcustomertype(Application,frmLand->conLand,1);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N108Click(TObject *Sender)
{
	//系统设置

	if (CheckPower("系统设置")) {
		AnsiString pwd;
		TADOQuery * aq;
		aq = new TADOQuery(this);
		aq->Connection = frmLand->conLand  ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add("select bk from sys_bsset where name ='changeDanHaoDisplay'");
		aq->Open();
		pwd =  aq->FieldByName("bk")->AsAnsiString ;
		delete aq;
		TfrmPwd *frm1 = new TfrmPwd(Application);
		if (mrOk == frm1->ShowModal() ) {
			if (pwd == frm1->GetPassword()) {
				Tfrmsystemset *frm = new Tfrmsystemset(Application,frmLand->conLand);
				frm->Show();
			}
			else
			{
				MessageBoxA(0,"密码输入错误!","提示",MB_ICONASTERISK);
			}
		}
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N109Click(TObject *Sender)
{
	//库存调拨

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N112Click(TObject *Sender)
{
	//客户往来对账

}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N110Click(TObject *Sender)
{
	//调拨业务设置

}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::N114Click(TObject *Sender)
{


	//TfrmPrint::RetailjiaojiePrint(frmLand->GetUserID(), frmLand->conLand);
   //	N113->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N115Click(TObject *Sender)
{
	//客户类型

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N116Click(TObject *Sender)
{
  TfrmMyWork * frm = new TfrmMyWork(Application,frmLand->conLand,frmLand->GetUserID());
  frm->Show();
}
void TfrmMain::LoadMyWork(int UID)
{
   	   AnsiString sql;
   TImage *ImageMyWork;
   int w=0;
   int sleft,stop,swidth,sheight,sendleft;
   AnsiString SpeedName;
   sleft = 688;
   stop = 616;
   swidth = 60;
   sheight = 36;
   sendleft = 688;
   sql = "select top 10 A.ID,B.ActionName,B.DisplayName from Sys_Mywork A join sys_myworkaction B ";
   sql = sql + " ON A.MyWorkActionID = B.ID where A.useriD = "+ IntToStr(UID);
   TADOQuery *aq = new TADOQuery(NULL);
   aq->Connection =  frmLand->conLand;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   String caption,cap1,cap2;
  for (int i =0 ; i < aq->RecordCount ; i++) {

		SpeedName = "MyWork" + IntToStr(i);
		TSpeedButton * speed = new TSpeedButton(this);
		speed->Parent = this;
			speed->Width = swidth;
			speed->Height = sheight;
			speed->Name = SpeedName;

		speed->Cursor = Controls::crHandPoint ;
		speed->Flat = true;
		speed->Caption = aq->FieldByName("DisplayName")->AsAnsiString ;

		if (4-i >= 0 ) {
			speed->Left = sleft ;
			speed->Top = stop ;
			sleft = sleft + swidth + 6;

			/*caption =  aq->FieldByName("DisplayName")->AsAnsiString;
			int len,len1,len2;
			len = caption.Length();
			len1 = len/2;
			cap1 = caption.SubString(0,len1);
			cap2 = caption.SubString(len1+1,len-len1);
			speed->Caption = cap1 + "\n" + cap2 ;  */

		}else
		{
			speed->Left = sendleft ;
			speed->Top = stop + sheight +10 ;
			sendleft = sendleft + swidth + 6;

			/*caption =  aq->FieldByName("DisplayName")->AsAnsiString;
			int len,len1,len2;
			len = caption.Length();
			len1 = len/2;
			cap1 = caption.SubString(0,len1);
			cap2 = caption.SubString(len1+1,len-len1);
			speed->Caption = cap1 + "\n" + cap2 ;  */

		}


		for (int i = 0; i < ActionList->ActionCount ; i++) {
		  if ( ActionList->Actions[i]->Name == aq->FieldByName("ActionName")->AsAnsiString)
		  {
			speed->Action = ActionList->Actions[i] ;
			break;

		  }
		  }
	 /*	w = i * 82;
		//load image from db and display it
		TBlobField * pField=(TBlobField *)aq->FieldByName("image");
		TADOBlobStream*   pmem=new   TADOBlobStream(pField,bmRead);
		pmem->Seek(0,soFromBeginning);
		Graphics::TBitmap * pBitmap = new Graphics::TBitmap();
		pBitmap->LoadFromStream(pmem);
		ImageMyWork = new TImage(this);
		ImageMyWork->Parent = this;
		ImageMyWork->Name = "Image"+aq->FieldByName("ActionName")->AsAnsiString ;
		ImageMyWork->Hint = aq->FieldByName("ActionName")->AsAnsiString ;
		ImageMyWork->OnClick = ImageClick;
		ImageMyWork->Width = 62;
		ImageMyWork->Height =60;
		ImageMyWork->Top = 46;
		ImageMyWork->Left = 296 + w ;
		ImageMyWork->Picture->Assign(pBitmap);
		delete   pBitmap;
		delete   pmem;
					 */

		aq->Next();
   }
}
void TfrmMain::LoadMyMessage()
{
  AnsiString sql;
  AnsiString MsgName,MsgPic;
  int j,k,l,p;


   //all msg visible = false;
  for (int i = 0; i < MessageInfo->Count ; i++) {
		TLabel * MsgLabel = (TLabel *)MessageInfo->Objects[i];
		MsgLabel->Visible  = false;
		TRzGlyphStatus * MsgImage = (TRzGlyphStatus *)MessagePic->Objects[i];
		MsgImage->Visible = false;
  }
   sql = "select top 4 SYS_InforMessage.* from SYS_InforMessage left join sys_user on SYS_InforMessage.stgid = SYS_User.stgid "
			" left join SYS_UserGroup on SYS_UserGroup.userid = SYS_User.id "
			" left join SYS_GroupAction on SYS_GroupAction.groupid = SYS_UserGroup.groupid "
			" left join SYS_Action on SYS_GroupAction.actionid = sys_action.code "
			" where  ((sys_action.actionname = '连锁配送'  and SYS_InforMessage.type  in(2,3)) "
			" or ((sys_action.actionname = '客户订单' or sys_action.actionname = '一般采购') and SYS_InforMessage.type = 1)) "
			" and sys_user.id = " + IntToStr(frmLand->GetUserID()) + " and SYS_InforMessage.state <> 0 and SYS_InforMessage.stgid = " + IntToStr(frmLand->GetStorageID());

   /*aqmsg->Close();
   aqmsg->SQL->Clear();
   aqmsg->SQL->Add(sql);
   aqmsg->Open(); */
   TADOQuery *aq = new TADOQuery(NULL);
   aq->Connection =  frmLand->conLand;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   for (int i =0 ; i < aq->RecordCount ; i++)
   {
		MsgName = "msg" + IntToStr(i+1);
		MsgPic = "g" + IntToStr(i+1);
		j = MessageInfo->IndexOf(MsgName);    //取出要显示的panel
		TLabel * MsgLabel = (TLabel *)MessageInfo->Objects[j];
		MsgLabel->Visible  = true;
		MsgLabel->Caption = aq->FieldByName("Message")->AsAnsiString ;
		MsgLabel->Hint = aq->FieldByName("value")->AsAnsiString;
		MsgLabel->Tag = aq->FieldByName("type")->AsInteger ;
		MsgLabel->HelpContext =aq->FieldByName("id")->AsInteger ;
		k = MessagePic->IndexOf(MsgPic);
		TRzGlyphStatus * MsgImage = (TRzGlyphStatus *)MessagePic->Objects[j];
		MsgImage->Visible = true;

	 	aq->Next();
   }
   delete aq;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::ImageClick(TObject   *Sender)
{
	TImage * img = dynamic_cast<TImage*>(Sender);
	if(!img)return;
		for (int i=0 ; i < 87; i++) {
	}
}

//---------------------------------------------------------------------------

void __fastcall TfrmMain::rloginExecute(TObject *Sender)
{
    HWND hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);
	while (hWnd != NULL)
	{
        MessageBox(0,"有未关闭的子窗口，请关闭后重试！","提示",MB_ICONWARNING);
		return;
	}
	frmLand->edtPassword->Text = "";
	if (jiaojie == 1) {
		frmLand->Caption = "零售员交接班";
	}
	else
	{
    	frmLand->Caption = "登陆";
	}
	jiaojie = 0;
	if( frmLand->ShowModal() == mrOk)
	{
		Discstr = Disc();
		//statebar->Panels->Items[1]->Text = frmLand->GetUserName();

		PowerList->Clear();
		GetPowerList(frmLand->GetUserID());

		lbuser->Caption = frmLand->GetUserName();
		lbdate->Caption = DateToStr(Now());
		AnsiString sname = IntToStr(frmLand->GetStorageID()) + "-" + frmLand->cbstorage->Text ;
		stgname->Caption = sname;
		LoadMyMessage();
		Time();
		Disappear(PUIName);
		PUIName = "imageui";
		Display("imageui");
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::quitExecute(TObject *Sender)
{
   if (MessageBoxA(0,"是否退出系统？","提示",MB_ICONQUESTION|MB_OKCANCEL )==1 ) {


   Application->Terminate();

   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StogeSetExecute(TObject *Sender)
{
	//店仓信息设置
	if (!FindDog()) {
        return;
	}
	if (CheckPower("店仓管理")) {
		SetUpStorageInfo(Application, frmLand->conLand,frmLand->GetUserID(),frmLand->GetStorageID(),frmLand->GetMaster());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::retailclassPromotionExecute(TObject *Sender)
{
	//零售类别促销
	//ManageRetailSales(Application, frmLand->conLand);
	if (!FindDog()) {
        return;
	}
	if (CheckPower("零售类别促销")) {
		DiscountSales(Application, frmLand->conLand,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RetailbuyExecute(TObject *Sender)
{
	//零售购物金额促销
	if (!FindDog()) {
        return;
	}
	if (CheckPower("零售购物金额促销")) {
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		TfrmMonerydiscount *frm = new TfrmMonerydiscount(Application,li.con,li.storageID) ;
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberoneProductExecute(TObject *Sender)
{
    if (!FindDog()) {
        return;
	}
	if (CheckPower("会员类型单品促销")) {
		MemberDiscount(Application, frmLand->conLand,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberjifenExecute(TObject *Sender)
{
	//会员积分管理
	if (!FindDog()) {
        return;
	}
	if (!frmLand->GetMaster() ) {
		MessageBoxA(0,"只有总店才有权限操作此模块!","提示",MB_ICONASTERISK);
		return;
	}
	if (CheckPower("会员积分管理")) {
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		TfrmMemberjifen *frm = new TfrmMemberjifen(Application,li.con) ;
		frm->stgid = li.storageID ;
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SaleOneProductExecute(TObject *Sender)
{
    if (!FindDog()) {
        return;
	}
	if (CheckPower("批销单品折扣")) {
		WsaleDiscount(Application, frmLand->conLand,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SaleAddPointExecute(TObject *Sender)
{
    if (!FindDog()) {
        return;
	}
	if (CheckPower("批销附加折扣")) {
		WsaleDiscountSales(Application, frmLand->conLand,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SaleNowbackDotExecute(TObject *Sender)
{
	//批销现场返点
    if (!FindDog()) {
        return;
	}
	if (CheckPower("批销现场返点")) {
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		TfrmClientBackdot *frm = new TfrmClientBackdot(Application,li.con,li.storageID) ;
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SaleyearBackDotExecute(TObject *Sender)
{
//	批销年度返点
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientOrderExecute(TObject *Sender)
{
	//订单管理
    if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
		li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID() ;


          if (CheckPower("客户资料添加")) {      //权限控制
             li.FormatStr = "1";
         }else li.FormatStr = "0";


	if (CheckPower("客户订单") ) {
		BIOrderManage(&li,0);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SampleStockExecute(TObject *Sender)
{
	//采购管理
    if (!FindDog()) {
        return;
	}
	if (CheckPower("一般采购") ) {
		LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID  = frmLand->GetStorageID();
		li.FormatStr = "#,##0.00";

                  if (CheckPower("供应商资料添加")) {      //权限控制
             li.FormatStr = "1";
         }else li.FormatStr = "0";


	ProcureManage(&li);
	}else
	{
	   ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::smartStockExecute(TObject *Sender)
{
	//智能采购
    if (!FindDog()) {
        return;
	}
	if (CheckPower("智能采购") ) {
		LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();
	//ZNProcureManage(&li);
	CaigoufromOrder(&li);
	}else
	{
	   ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::samplestorageExecute(TObject *Sender)
{
	//入库管理
    if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;

	li.storageID = frmLand->GetStorageID();

         if (CheckPower("供应商资料添加")) {      //权限控制
             li.FormatStr = "1";
         }else li.FormatStr = "0";

               if (CheckPower("书目添加") ) {
               li.FormatStr = li.FormatStr+"1";
              }else  li.FormatStr = li.FormatStr+"0";
           if (CheckPower("书目修改") ) {
               li.FormatStr = li.FormatStr+"1";
              }else  li.FormatStr = li.FormatStr+"0";
         
        
	if (CheckPower("一般入库")) {
		ManageStorage(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::storagebackExecute(TObject *Sender)
{
	//入库退货管理
    if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;

	li.storageID = frmLand->GetStorageID();

         if (CheckPower("供应商资料添加")) {      //权限控制
             li.FormatStr = "1";
         }else li.FormatStr = "0";

	if (CheckPower("入库退货")) {
		ManageReturnStorage(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::samplesaleExecute(TObject *Sender)
{
	//批销管理
    if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";


          if (CheckPower("客户资料添加")) {      //权限控制
             li.FormatStr = "1";
         }else li.FormatStr = "0";


	if (CheckPower("一般发货")) {
		ManageMarketing(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::smartSaleExecute(TObject *Sender)
{
//8．	智能发货
	//智能发货
	//MessageBoxA(0,"试用版不提供此功能!","提示",MB_ICONASTERISK);
		//return;
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("智能发货")) {
		ZNWsale(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actionsaleExecute(TObject *Sender)
{
//8．  主动发货
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::salebackExecute(TObject *Sender)
{
	//批销退货管理
    if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
         if (CheckPower("客户资料添加")) {      //权限控制
             li.FormatStr = "1";
         }else li.FormatStr = "0";

		if (CheckPower("发货退货")) {
			ManageReturnMarketing(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::samplebookExecute(TObject *Sender)
{
//样子处理
	//样/赠书处理
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text;
		li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID() ;
	if (CheckPower("样/赠书处理") ) {
		Ysbooksale(&li);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::PosretailExecute(TObject *Sender)
{
	//POS零售管理
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("POS零售")) {
		ManageRetail(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::retailBackExecute(TObject *Sender)
{
	//零售退货
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("零售退货")) {
		ManageReturnRetail(&li);
	}
	else
	{
		ShowNoPower();
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::b2binterfaceExecute(TObject *Sender)
{
//b2b 接入
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::financestartExecute(TObject *Sender)
{
   //  单位往来期初
	if (!FindDog()) {
        return;
	}
	if (CheckPower("供应商期初帐单")) {
		Tfrmsupplierandclient * frm = new Tfrmsupplierandclient(Application,frmLand->conLand,1);
		frm->Show();
		return;
	}
	else
	{
		ShowNoPower();
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::supplierduizhangExecute(TObject *Sender)
{
	//供应商往来对账   0
	if (!FindDog()) {
        return;
	}
	if (CheckPower("供应商往来对帐")) {
		Tfrmwanglaizhang * frm = new Tfrmwanglaizhang(Application,1);      //供应商往来
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		frm->init(&li);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierjiduanfexieExecute(TObject *Sender)
{
	// 供应商阶段结算分析
	if (!FindDog()) {
        return;
	}
	if (CheckPower("供应商阶段结算分析")) {
		SupplierStageClearing(Application, frmLand->conLand,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierjieshuanExecute(TObject *Sender)
{
	//付款结算
	if (!FindDog()) {
        return;
	}
	int userid ;
	userid =frmLand->GetUserID();
	if (CheckPower("供应商结算")) {
		Tfrmbalance *frm = new Tfrmbalance(Application,frmLand->conLand,userid,1,frmLand->GetStorageID(),frmLand->GetMaster());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierjieShuanSearchExecute(TObject *Sender)
{
//	5．	供应商结算查询
	if (!FindDog()) {
        return;
	}
	if (CheckPower("供应商结算查询")) {
   		TAccQuery * frm = new TAccQuery(Application,1,frmLand->conLand,frmLand->GetStorageID(),frmLand->GetMaster());
		frm->Show();
   }
   else
   {
		ShowNoPower();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientfinanceStartExecute(TObject *Sender)
{
	//  客户往来期初
	if (!FindDog()) {
        return;
	}
	if (CheckPower("客户期初帐单")) {
		Tfrmsupplierandclient * frm = new Tfrmsupplierandclient(Application,frmLand->conLand,2);
		frm->Show();
		return;
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientWanglaiduizhangExecute(TObject *Sender)
{
	//客户往来对账
	if (!FindDog()) {
        return;
	}
	if (CheckPower("客户住来对帐")) {
		Tfrmwanglaizhang * frm = new Tfrmwanglaizhang(Application,2);      //客户往来
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		frm->init(&li);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientjieduanfexieExecute(TObject *Sender)
{
	// 客户阶段结算分析
	if (!FindDog()) {
        return;
	}
	if (CheckPower("客户阶段结算分析")) {
		ClientStageClearing(Application, frmLand->conLand,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientJieShuanExecute(TObject *Sender)
{
	int userid ;
	if (!FindDog()) {
        return;
	}
	userid =frmLand->GetUserID();
	if (CheckPower("客户结算")) {
		Tfrmbalance *frm = new Tfrmbalance(Application,frmLand->conLand,userid,2,frmLand->GetStorageID(),frmLand->GetMaster());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DangrijieshuanExecute(TObject *Sender)
{
	//当日快捷结款
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("当日发货快捷结算")) {
		fastcheck(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::BreedManageExecute(TObject *Sender)
{
	//图书品目管理
  //	ManageBookCatalog(Application, frmLand->conLand);
        bool add;
        bool del;
        bool mod;
	if (!FindDog()) {
        return;
	}

        //书目添加


	if (CheckPower("图书目录管理") ) {
           if (CheckPower("书目添加") ) {
              add=true;
              }else add=false;
           if (CheckPower("书目修改") ) {
               mod=true;
              }else  mod=false;
           if (CheckPower("书目删除") ) {
               del=true;
              }else del=false;




		CatalogKan(Application, frmLand->conLand,frmLand->GetStorageID(),frmLand->GetUserID(),add,del,mod );
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::catalogMakeExecute(TObject *Sender)
{
//catalog make
	//目录制作
	if (!FindDog()) {
        return;
	}
	if (CheckPower("目录制作") ) {
		Catalogbuilt(Application, frmLand->conLand);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pressmanageExecute(TObject *Sender)
{
	//出版社管理
	if (!FindDog()) {
        return;
	}
	if (CheckPower("出版社管理")) {
		ManagePress(Application, frmLand->conLand);
	}else
	{
	   ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::breedTypeExecute(TObject *Sender)
{
	//图书类别管理
	if (!FindDog()) {
        return;
	}
	if (CheckPower("品目类别管理")) {
		ManageBookType(Application, frmLand->conLand);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::LocalManageExecute(TObject *Sender)
{
    if (!FindDog()) {
        return;
	}
	if (CheckPower("区域管理")) {
		TMemberAreaSet * frm = new TMemberAreaSet(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::memberclassExecute(TObject *Sender)
{
	//会员类型
    if (!FindDog()) {
        return;
	}
	if (CheckPower("会员类型")) {
		Tfrmmemclassmg *frm = new Tfrmmemclassmg(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StorageInfoExecute(TObject *Sender)
{
	//库位管理
	if (!FindDog()) {
        return;
	}
	if (CheckPower("库位资料") ) {
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.FormatStr = "#,##0.00";
		li.storageID = frmLand->GetStorageID();
		Tfrmstorelocal *frm = new Tfrmstorelocal(Application,frmLand->conLand,&li);
		frm->Show();
	}
	else
	{
	   ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::xuyipandianExecute(TObject *Sender)
{
	//虚拟盘点
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.UserName = frmLand->GetUserNameA();
	if (CheckPower("局部盘点")) {
		Stockxuyi(&li);
	}
	else
	{
		ShowNoPower();
	}
}

//--------------------------------------------------------------------------

void __fastcall TfrmMain::shikupandianExecute(TObject *Sender)
{
	//库存盘点
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->GetUserNameA();
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("实库盘点")) {
		Tfrmcheckstock * frm = new Tfrmcheckstock(Application,frmLand->conLand ,&li);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::storageLocaladjustExecute(TObject *Sender)
{
	//库存调整
	if (!FindDog()) {
        return;
	}
   //	AdjustStock(Application, frmLand->conLand);
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.FormatStr = "#,##0.00";
	li.UserName = frmLand->GetUserNameA();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("库位调整")) {
		Tfrmadjust *frm = new Tfrmadjust(Application,frmLand->conLand,&li);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::onestorageNumberadjustExecute(TObject *Sender)
{
    if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.UserName = frmLand->cbName->Text;
	if (CheckPower("库存调整")) {
		StockAdjust(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StoragealarmExecute(TObject *Sender)
{
	//库存预警
	//WarnStock(Application, frmLand->conLand);
	if (!FindDog()) {
        return;
	}
	if (CheckPower("库存预警")) {
		TfrmalarmSet *frm = new TfrmalarmSet(Application,frmLand->conLand,frmLand->GetStorageID(),frmLand->GetUserID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::OperatorManageExecute(TObject *Sender)
{
  //操作员管理
  	if (!FindDog()) {
        return;
	}
	if (CheckPower("操作员管理")) {
		Tfrmuser * frm = new Tfrmuser(Application,frmLand->conLand,frmLand->cbName->Text,frmLand->GetStorageID(),frmLand->GetUserID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::rolemanageExecute(TObject *Sender)
{
 //角色管理
 	if (!FindDog()) {
        return;
	}
	if (CheckPower("角色管理")) {
		Tfrmgroup * frm = new Tfrmgroup(Application,frmLand->conLand,frmLand->GetStorageID(),frmLand->GetUserID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::PowerSetExecute(TObject *Sender)
{
   //权限管理
	if (!FindDog()) {
        return;
	}
	if (CheckPower("权限设置")) {
		Tfrmpurview * frm  = new Tfrmpurview(Application,frmLand->conLand , frmLand->GetStorageID(),frmLand->GetUserID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierInfoExecute(TObject *Sender)
{
	//供应商设置
	if (!FindDog()) {
        return;
	}
	if (CheckPower("供应商资料")) {
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		li.FormatStr = "#,##0.00";
		//1为供应商
		TSuppMana * frm = new TSuppMana(Application,1,frmLand->conLand);
	   	//	frm->StgID = li.storageID ;

                if (CheckPower("供应商资料添加")) {
                   frm->add=1;
                }else  frm->add=0;

                 if (CheckPower("供应商资料修改")) {
                   frm->modify=1;
                }else frm->modify=0;

                 if (CheckPower("供应商资料删除")) {
                  frm->del=1;
                }else frm->del=0;

                frm->lock();
		frm->Show();
	}
	else
	{
		ShowNoPower();
   	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientInfoExecute(TObject *Sender)
{
	//客户资料
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	 //1为供应商
	  //	TSuppMana * frm = new TSuppMana(Application,2,frmLand->conLand);
	//frm->Show();
	if (CheckPower("客户资料") ) {
	   Tfrmclient *frm = new Tfrmclient(Application,frmLand->conLand,li.storageID);
			  if (CheckPower("客户资料添加")) {
                   frm->add=1;
                }else  frm->add=0;

                 if (CheckPower("客户资料修改")) {
                   frm->modify=1;
                }else frm->modify=0;

                 if (CheckPower("客户资料删除")) {
                  frm->del=1;
                }else frm->del=0;



           frm->lock();
	   frm->Show() ;
	}else
	{
	   ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::salermanageExecute(TObject *Sender)
{
    if (!FindDog()) {
        return;
	}
	if (CheckPower("业务员管理(资料)")) {
		TfrmStaff *frm = new TfrmStaff(Application,frmLand->conLand,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::creditManageExecute(TObject *Sender)
{
    if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("信用管理")) {
		Tfrmwsset * frm = new Tfrmwsset(li.app,li.con,li.storageID) ;
		frm->m_storageID = li.storageID;
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberInfoExecute(TObject *Sender)
{
  //会员管理
	if (!FindDog()) {
        return;
	}
	if (CheckPower("会员资料")) {
		TfrmMember *frm = new TfrmMember(Application,frmLand->conLand);
		frm->userid = frmLand->GetUserID();
		frm->stgid = frmLand->GetStorageID();
		frm->Show();
	}
	else
	{
		ShowNoPower();
  	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberchongzhiExecute(TObject *Sender)
{
  //会员充值
  	if (!FindDog()) {
        return;
	}
	if (CheckPower("会员充值")) {
		TfrmMemberResult *frm = new TfrmMemberResult(Application,frmLand->conLand);
		frm->userid = frmLand->GetUserID();
		frm->stgid = frmLand->GetStorageID();
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberchongziSearchExecute(TObject *Sender)
{
  	//充值记录查询
	if (!FindDog()) {
        return;
	}
	if (CheckPower("会员充值查询")) {
		TFormRecordQuery *frm = new TFormRecordQuery(Application,frmLand->conLand,frmLand->GetUserID(),frmLand->GetStorageID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
  	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StorageSearchExecute(TObject *Sender)
{
	//业务查询
	/*TMenuItem* item = dynamic_cast<TMenuItem*>(Sender);
	if (item != NULL)
	{   if (item->Tag == 3) {
			if (CheckPower("库存查询")) {
				BusinessQuery(Application, frmLand->conLand, item->Tag);
			}
			else
			{
				  ShowNoPower();
			}
		}

	} */
	if (!FindDog()) {
        return;
	}
	if (CheckPower("库存查询")) {
    	LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		BusinessQuery(Application, &li, 3);
	}
	else
	{
		  ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::OrderSearchExecute(TObject *Sender)
{
	//订单查询
	if (!FindDog()) {
		return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("订单查询")) {
		QryOderNote(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::stocksearchExecute(TObject *Sender)
{
	//采购查询
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("采购查询")) {
		QryProcureNote(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::rikusearchExecute(TObject *Sender)
{
	//入库查询
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("入库查询")) {
		QueryStorageNote(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::salesearchExecute(TObject *Sender)
{
	//批销查询
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("发货查询")) {
		QueryWsaleNote(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::posretailsearchExecute(TObject *Sender)
{
	//零售查询
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("POS零售查询")) {
		QueryRetailNote(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::storagechecksearchExecute(TObject *Sender)
{
	if (!FindDog()) {
        return;
	}
	  if (CheckPower("盘点查询")) {
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		QryCheckNote(&li);
	  }else
		{
			ShowNoPower();
		}
}
//---------------------------------------------------------------------------






void __fastcall TfrmMain::Image2Click(TObject *Sender)
{
 ShowMessage("dd");
}

void __fastcall TfrmMain::imageheadMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
 /*	if (Button == mbLeft ) {
	if (Y >= 19 && Y <= 31) {


		if (X >= 366 && X <= 396) {

		   TPoint p;
		   TPoint pt;
		   p.x = 366;
		   p.y= 31 ;
		  pt = ClientToScreen(p);
		  PMfile->Popup(pt.x,pt.y);
		}

	}



	}  */
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imageheadMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
  //	Label1->Caption = IntToStr(X);
   //	Label2->Caption = IntToStr(Y);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::sbfileClick(TObject *Sender)
{
	TPoint p;
	TPoint pt;
   switch (((TSpeedButton*)Sender)->Tag) {
		 case 0:
				p.x = 366;
				p.y= 31 ;
				pt = ClientToScreen(p);
				PMfile->Popup(pt.x,pt.y);
			break;
		 case 1:
				p.x = 408;
				p.y= 31 ;
				pt = ClientToScreen(p);
				PMsystem->Popup(pt.x,pt.y);
			break;
		  case 2:
				p.x = 482;
				p.y= 31 ;
				pt = ClientToScreen(p);
				PMbasicData->Popup(pt.x,pt.y);

			break;
			case 3:
				p.x = 559;
				p.y= 31 ;
				pt = ClientToScreen(p);
				PMpower->Popup(pt.x,pt.y);

			break;
			case 4:
				p.x = 633;
				p.y= 31 ;
				pt = ClientToScreen(p);
				PMcatalog->Popup(pt.x,pt.y);

			break;
			case 5:
				p.x = 703;
				p.y= 31 ;
				pt = ClientToScreen(p);
				PMwlclient->Popup(pt.x,pt.y);

			break;
			 case 6:
				p.x = 780;
				p.y= 31 ;
				pt = ClientToScreen(p);
				PMmember->Popup(pt.x,pt.y);

			break;
			case 7:
				p.x = 857;
				p.y= 31 ;
				pt = ClientToScreen(p);
				PMbusiness->Popup(pt.x,pt.y);

			break;
			case 8:
				p.x = 931;
				p.y= 31 ;
				pt = ClientToScreen(p);
				PMhelp->Popup(pt.x,pt.y);

			break;

   default:
	   ;
   }

}
//void __fastcall TfrmMain::WMNchitTest(TMessage &Message)
//{
 // if(GetAsyncKeyState(VK_LBUTTON)< 0)
  //	Message.Result=HTCAPTION;
 // else
  //  Message.Result=HTCLIENT;
//}
//---------------------------------------------------------------------------





void __fastcall TfrmMain::sbleftmenuClick(TObject *Sender)
{
   //
	//
	switch (((TSpeedButton*)Sender)->Tag) {
		case 300:
			 Disappear(PUIName);        //采购
			 PUIName = "imagecg";
			 Display("imagecg");
		break;
		case 301:                        //发货
			 Disappear(PUIName);
			 PUIName = "imagepx";
			 Display("imagepx");
		break;

		case 302:                        //零售
			Disappear(PUIName);
			PUIName = "imagels";
			Display("imagels");
		break;

		case 303:                        //库存管理
			Disappear(PUIName);
			PUIName = "imagekc";
			Display("imagekc");
			StockAlert();
		break;

		case 304:
			Disappear(PUIName);  //财务
			PUIName = "imagecf";
			Display("imagecf");
		break;
		case 305:
			Disappear(PUIName);  //营销
			PUIName = "imageyx";
			Display("imageyx");
		break;
		case 306:
			Disappear(PUIName);  //往来
			PUIName = "imagewl";
			Display("imagewl");
		break;
		case 307:
			Disappear(PUIName);  //业务查询
			PUIName = "imagesearch";
			Display("imagesearch");
		break;
		case 308:
			Disappear(PUIName);  //统计分析
			PUIName = "imagetj";
			Display("imagetj");
		break;
		case 309:
			Disappear(PUIName);  //商务协同
			PUIName = "imagext";
			Display("imagext");
		break;
		case 400:
			//MessageBoxA(0,"试用版暂无此功能!","提示",MB_ICONASTERISK);
			//return;
			Disappear(PUIName);  //商务通
			PUIName = "imagesft";
			Display("imagesft");
		break;
	}

}
//---------------------------------------------------------------------------
void TfrmMain::StockAlert()
{
	TADOQuery *aq = new TADOQuery(NULL);
	AnsiString sql;
	aq->Connection = frmLand->conLand;
	sql = "select value from sys_bsset where name = 'kucunstockalarm'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->FieldByName("value")->AsBoolean  ) {
		Tfrmalarm *frm = new Tfrmalarm(Application,frmLand->conLand,frmLand->GetStorageID());
	}
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
//

}
//---------------------------------------------------------------------------





void __fastcall TfrmMain::imagecgMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
		uix = X;
		uiy = Y;
	  //			Label1->Caption = IntToStr(X);
	 //	Label2->Caption = IntToStr(Y);

		 if (uix >195 && uix < 248 && uiy >15 && uiy < 27) {     //品目管理
			Screen->Cursor =  Controls::crHandPoint ;
		  }else
		  {
			Screen->Cursor =  Controls::crDefault ;
		  }
			  if (uix >278 && uix < 331 && uiy >15 && uiy < 27) {    //类别管理
				Screen->Cursor =  Controls::crHandPoint ;
		 }
		 if (uix >367 && uix < 429 && uiy >15 && uiy < 27) {    //出版社管理
				Screen->Cursor =  Controls::crHandPoint ;
		 }

			  if (uix >461 && uix < 526 && uiy >15 && uiy < 27) {        //供应商资料
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >562 && uix < 619 && uiy >15 && uiy < 27) {        //区域管理
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >648 && uix < 707 && uiy >15 && uiy < 27) {        //库位资料
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >289 && uix < 341 && uiy >165 && uiy < 208) {        //一般采购单
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >463 && uix < 527 && uiy >120 && uiy < 161) {        //一般入库
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >473 && uix < 528 && uiy >233 && uiy < 280) {        //入库退货
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >289 && uix < 342 && uiy >300 && uiy < 340) {        //智能采购
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >475 && uix < 528 && uiy >354 && uiy < 399) {        //智能入库
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >661 && uix < 712 && uiy >233 && uiy < 281) {        //供应商阶段结算分析
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			if (uix >827 && uix < 874 && uiy >234 && uiy < 279) {        //付款结算
				Screen->Cursor =  Controls::crHandPoint ;
			}





}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagecfMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
   uix = X;
   uiy = Y;

          //			Label1->Caption = IntToStr(X);
	 //	Label2->Caption = IntToStr(Y);
		 if (uix >316 && uix < 373 && uiy >75 && uiy < 115) {     //供应商往来期初
			Screen->Cursor =  Controls::crHandPoint ;
		  }else
		  {
			Screen->Cursor =  Controls::crDefault ;
		  }
			  if (uix >446 && uix < 507 && uiy >71 && uiy < 119) {    //应付汇总
				Screen->Cursor =  Controls::crHandPoint ;
		 }

			  if (uix >317 && uix < 373 && uiy >180 && uiy < 228) {        //供应商往来对帐
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >445 && uix < 505 && uiy >181 && uiy < 321) {        //应付明细
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >646 && uix < 703 && uiy >136 && uiy < 173) {        //供应商结算
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >803 && uix < 860 && uiy >141 && uiy < 177) {        //供应商结算查询
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >312 && uix < 368 && uiy >330 && uiy < 375) {        //客户往来期初
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >454 && uix < 502 && uiy >329 && uiy < 375) {        //应收汇总
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >311 && uix < 366 && uiy >440 && uiy < 486) {        //客户往来对帐
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >454 && uix < 502 && uiy >444 && uiy < 485) {        //应收明细
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >657 && uix < 703 && uiy >378 && uiy < 420) {        //客户结算
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			if (uix >804 && uix < 855 && uiy >380 && uiy < 422) {        //客户结算查询
				Screen->Cursor =  Controls::crHandPoint ;
			}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::yihutotalExecute(TObject *Sender)
{
	  //应付汇总
	if (!FindDog()) {
        return;
	}
	if (CheckPower("应付汇总")) {
		TAccountDoe *frm = new TAccountDoe(Application,1,frmLand->conLand,frmLand->GetStorageID());
		frm->username = frmLand->GetUserNameA();
		frm->stogName = frmLand->cbstorage ->Text ;
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::yingfudetailExecute(TObject *Sender)
{
   //供应商应收明细
	if (!FindDog()) {
        return;
	}
	if (CheckPower("应付明细")) {
		TAccDetail *frm = new TAccDetail(Application,1,frmLand->conLand,frmLand->GetStorageID());
		frm->stogName = frmLand->cbstorage ->Text ;
		frm->Maker = frmLand->cbName->Text ;
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::yingshouhuizhongExecute(TObject *Sender)
{
   //应收汇总
	if (!FindDog()) {
        return;
	}
   if (CheckPower("应收汇总")) {
		TAccountDoe *frm = new TAccountDoe(Application,2,frmLand->conLand,frmLand->GetStorageID());
		frm->username = frmLand->GetUserNameA();
		frm->stogName = frmLand->cbstorage ->Text ;
		frm->Show();
   }
   else
   {
		ShowNoPower();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::yingshoudetailExecute(TObject *Sender)
{
	  //客户应收明细
	if (!FindDog()) {
		return;
	}
	if (CheckPower("应收明细")) {
		TAccDetail *frm = new TAccDetail(Application,2,frmLand->conLand,frmLand->GetStorageID());
		frm->stogName = frmLand->cbstorage ->Text ;
		frm->Maker = frmLand->cbName->Text ;
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientjieshuansearchExecute(TObject *Sender)
{
 //客户结算查询
 	if (!FindDog()) {
        return;
	}
	if (CheckPower("客户结算查询")) {
    	TAccQuery * frm = new TAccQuery(Application,2,frmLand->conLand,frmLand->GetStorageID(),frmLand->GetMaster());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::jiaojiebanExecute(TObject *Sender)
{
//jiaojieban 零售员交接班
	if (!FindDog()) {
        return;
	}
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = frmLand->conLand ;
	AnsiString sql;
	sql = "select value from sys_bsset where Name = 'jiaojieprint'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->FieldByName("value")->AsBoolean ) {
		TfrmPrint *frm  = new TfrmPrint(Application);
		frm->RetailjiaojiePrint(frmLand->GetUserID(), frmLand->conLand,frmLand->GetStorageID());
		delete frm;
		//TfrmPrint::RetailjiaojiePrint(frmLand->GetUserID(), frmLand->conLand);
	}
	sql = "insert into sys_log (EventType,SourceFrom,EventDate,EventUser,EventMessage,stgName) values('信息','交接',getdate()," + IntToStr(frmLand->GetUserID()) + ",'收银员交接'," + IntToStr(frmLand->GetStorageID()) + ")" ;

	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	jiaojie = 1;
	rlogin->Execute();
	//jiaojiebanExecute(Application);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imageyxMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
 
	 uix = X;
	 uiy = Y;
		 if (uix >304 && uix < 358 && uiy >144 && uiy < 192) {     //零售类别促销
			Screen->Cursor =  Controls::crHandPoint ;
		  }else
		  {
			Screen->Cursor =  Controls::crDefault  ;
		  }
			  if (uix >459 && uix < 520 && uiy >153 && uiy < 200) {    //零售购物金额促销
				Screen->Cursor =  Controls::crHandPoint ;
		 }

			  if (uix >618 && uix < 679 && uiy >154 && uiy < 195) {        //会员类型单品促销
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >775 && uix < 819 && uiy >157 && uiy < 192) {        //会员积分管理
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >314 && uix < 364 && uiy >334 && uiy < 381) {        //批销单品折扣
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >462 && uix < 522 && uiy >339 && uiy < 384) {        //批销附加折扣
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >618 && uix < 682 && uiy >338 && uiy < 387) {        //批销现场返点
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >770 && uix < 837 && uiy >335 && uiy < 386) {        //批销年度返点
			  Screen->Cursor =  Controls::crHandPoint ;
		  }


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::retailandbackExecute(TObject *Sender)
{
	//零售与退货
	if (!FindDog()) {
        return;
	}
	if (CheckPower("零售与退货")) {
		Tfrmretail *frm = new Tfrmretail(Application,frmLand->conLand,frmLand->GetStorageID());
		//frm->Disc = Discstr ;
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::saleandbackExecute(TObject *Sender)
{
	  //批销与退货
	if (!FindDog()) {
        return;
	}
	  if (CheckPower("批销与退货")) {
			TfrmWsale *frm = new TfrmWsale(Application,frmLand->conLand,frmLand->GetStorageID());
			//frm->Disc = Discstr;
			frm->Show();
	  }
	  else
	  {
			ShowNoPower();
	  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::saletimehuizhongExecute(TObject *Sender)
{
  //销售时段汇总统计
	if (!FindDog()) {
        return;
	}
   if (CheckPower("销售时段汇总统计")) {
		Tfrmsaletime *frm = new Tfrmsaletime(Application,frmLand->conLand,frmLand->GetStorageID());
		//frm->Disc = Discstr;
		frm->Show();
   }
   else
   {
		ShowNoPower();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::weidongkuchunExecute(TObject *Sender)
{
   //库存分析
	if (!FindDog()) {
        return;
	}
   if (CheckPower("未动库存分析")) {
		Tfrmstockanalysis * frm  = new Tfrmstockanalysis(Application,frmLand->conLand,frmLand->GetStorageID());
		frm->Show();
   }
   else
   {
		ShowNoPower();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::yefupaihangbangExecute(TObject *Sender)
{
   //业务排行旁
	if (!FindDog()) {
        return;
	}
   if (CheckPower("业务排行榜")) {
		Yewupaihang(Application,frmLand->conLand,frmLand->GetStorageID());
   }
   else
   {
		ShowNoPower();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::saletongjireportExecute(TObject *Sender)
{
	 //销售统计报表
	if (!FindDog()) {
        return;
	}
	 if (CheckPower("销售统计报表")) {
		Tfrmsaleanalysis *frm = new Tfrmsaleanalysis(Application,frmLand->conLand,frmLand->GetStorageID());
		frm->Show();
	 }
	 else
	 {
		ShowNoPower();
	 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::jingxiaochunfenxieExecute(TObject *Sender)
{
	//进销存分析
	if (!FindDog()) {
        return;
	}
	if (CheckPower("进销存分析")) {
		PurchaseSalesInventoryAnalysis(Application, frmLand->conLand,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::changxiaobookExecute(TObject *Sender)
{
	//销售书排行与毛利分析
	if (!FindDog()) {
        return;
	}
	if (CheckPower("销售书排行与毛利分析")) {
		SalesAnalysis(Application, frmLand->conLand,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::retailhuizhongfengxieExecute(TObject *Sender)
{
	//零售汇总分析
	if (!FindDog()) {
        return;
	}
	if (CheckPower("零售汇总分析")) {
		RetailSummary(Application, frmLand->conLand,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagesearchMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	 uix = X;
	 uiy = Y;
   	 // Label1 ->Caption = IntToStr(uix);
	// Label2->Caption = IntToStr(uiy);


	  if (uix >324 && uix < 385 && uiy >164 && uiy < 214) {          //库存查询
			  Screen->Cursor =  Controls::crHandPoint ;

		  }else
		  {
			 Screen->Cursor =  Controls::crDefault  ;
		  }
		  if (uix >480 && uix < 541 && uiy >165 && uiy < 217) {      //订单查询
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >642 && uix < 699 && uiy >170 && uiy < 213) {          //采购查询
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >784 && uix < 850 && uiy >172 && uiy < 217) {          //入库查询
			   Screen->Cursor =  Controls::crHandPoint ;

		  }

		  if (uix >323 && uix < 386 && uiy >330 && uiy < 381) {          //发货查询
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >473 && uix < 543 && uiy >327 && uiy < 377) {          //POS零售查询
			   Screen->Cursor =  Controls::crHandPoint ;

		  }

		  if (uix >634 && uix < 707 && uiy >325 && uiy < 384) {          //盘点查询
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >776 && uix < 851 && uiy >332 && uiy < 377) {          //配送查询
			   Screen->Cursor =  Controls::crHandPoint ;

		  }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagextMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
		 uix = X;
	 uiy = Y;

			  if (uix >350 && uix < 407 && uiy >239 && uiy < 296) {          //任务管理
			   Screen->Cursor =  Controls::crHandPoint ;

		  }else
		  {
			Screen->Cursor =  Controls::crDefault  ;
		  }

		  if (uix >516 && uix < 576 && uiy >243 && uiy < 294) {          //文档管理
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >689 && uix < 741 && uiy >245	&& uiy < 307) {          //在线交流
			   Screen->Cursor =  Controls::crHandPoint ;

		  }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::renwuExecute(TObject *Sender)
{
	//任务管理
	if (!FindDog()) {
        return;
	}
	if (CheckPower("任务管理")) {
		Tfrmtaskmanagea * frm = new Tfrmtaskmanagea(Application);
		frm->init(frmLand->conLand,frmLand->GetUserID(),frmLand->GetStorageID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::wengdangExecute(TObject *Sender)
{
//文档
	if (!FindDog()) {
        return;
	}
	MessageBoxA(0,"此功能为增强版所有!","提示",MB_ICONASTERISK);
	return;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::jiaoliuExecute(TObject *Sender)
{
//交流
	if (!FindDog()) {
        return;
	}
	MessageBoxA(0,"此功能为增强版所有!","提示",MB_ICONASTERISK);
	return;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::msg1Click(TObject *Sender)
{
	LandInfo li;
	int type =0;
	int ID;
	type = 2;
	AnsiString DanHao;
	type =	((TLabel*)(Sender))->Tag ;
	ID = ((TLabel*)(Sender))->HelpContext ;
	DanHao = ((TLabel*)(Sender))->Hint;
	adosp->Connection = frmLand->conLand;
	try
	{
	   switch (type) {
		   case 1:
				li.app = Application;
				li.con = frmLand->conLand  ;
				li.userID = frmLand->GetUserID()  ;
				li.FormatStr = "#,##0.00";
				li.storageID =  frmLand->GetStorageID()  ;
				adosp->Parameters->ParamByName("@ID")->Value =ID;
				adosp->ExecProc();
				BIOrderManageDanHao(&li,DanHao);

				break;
		   case 2:
		   case 3:
            	HWND hWnd;
				hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);
				TCHAR buf[MAX_PATH+1];
				while (hWnd != NULL)
				{
					::ZeroMemory(buf, sizeof(buf));
					if (::GetClassName(hWnd, buf, MAX_PATH) > 0)
					{
						if (StrCmp(_T("Tfrmdiaobo"), buf) == 0)
						{
							MessageBox(0,"为了保证连锁店库存的真实有效性\n一个用户同时只允许打开一个主动配送或请求配送模块！","提示" ,MB_OK|MB_ICONASTERISK);
							return;
						}
					}
					hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
				}

				LandInfo li;
				li.app = Application;
				li.con =  frmLand->conLand ;
				li.userID =   frmLand->GetUserID();
				li.storageID =  frmLand->GetStorageID();
				li.UserName = frmLand->GetUserNameA();
				DiaoBo(&li,2,DanHao);
				adosp->Parameters->ParamByName("@ID")->Value = ID;
				adosp->ExecProc();
			   break;
		 }
   }catch(...)
   {

   }
	LoadMyMessage();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::manualExecute(TObject *Sender)
{
	//用户手册
	AnsiString path;
	path =  ExtractFilePath(Application->ExeName);
	path = path + "help.doc";
	ShellExecute(NULL,"open",path.c_str() ,"","",SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::systemupdateExecute(TObject *Sender)
{
	//系统更新
	Tfrmshengji * frm = new Tfrmshengji(Application);
	frm->ShowModal();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::aboutExecute(TObject *Sender)
{
	//关于本软件
	TfrmAboutsoftware *frm = new TfrmAboutsoftware(Application);
	frm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::specialPassWordExecute(TObject *Sender)
{
   //特殊口令
    if (!FindDog()) {
        return;
	}
    LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("特殊口令")) {
    	TfrmSpecialPassword *frm = new TfrmSpecialPassword(Application);
		frm->Init(&li);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DanHaoDisplayExecute(TObject *Sender)
{
	//单号显示规则
	if (!FindDog()) {
        return;
	}
	if (CheckPower("单号显示规则")) {
		AnsiString pwd;
		TADOQuery * aq;
		aq = new TADOQuery(this);
		aq->Connection = frmLand->conLand  ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add("select bk from sys_bsset where name ='changeDanHaoDisplay'");
		aq->Open();
		pwd =  aq->FieldByName("bk")->AsAnsiString ;
		delete aq;
		TfrmPwd *frm1 = new TfrmPwd(Application);
		if (mrOk == frm1->ShowModal() ) {
			if (pwd == frm1->GetPassword()) {
				Tfrmsystemset *frm = new Tfrmsystemset(Application,frmLand->conLand);
				frm->userid = frmLand->GetUserID();
				frm->storageid = frmLand->GetStorageID();
				frm->Show();
			}
			else
			{
				MessageBoxA(0,"密码输入错误!","提示",MB_ICONASTERISK);
			}
		}
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::B2BSetExecute(TObject *Sender)
{
//B2B接口设置
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::logSearchExecute(TObject *Sender)
{
//日志查询
	//MessageBoxA(0,"试用版不提供此功能!","提示",MB_ICONASTERISK);
	  //	return;
	if (!FindDog()) {
        return;
	}
	if (CheckPower("日志查询")) {
		TfrmLog *frm = new TfrmLog(Application,frmLand->conLand,frmLand->GetUserID(),frmLand->GetStorageID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::dbbackExecute(TObject *Sender)
{
   //数据备份
	if (!FindDog()) {
        return;
	}
	if (CheckPower("数据备份")) {
	TBakDatabase *frm = new TBakDatabase(Application,frmLand->conLand);
	frm->ShowModal();
	delete frm;
	}
	else
	{
		ShowNoPower();
  	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::dbrestoreExecute(TObject *Sender)
{
//数据恢复
	if (!FindDog()) {
        return;
	}
	if (CheckPower("数据恢复")) {
  	TResDatabase *frm = new TResDatabase(Application , frmLand->conLand );
	frm->ShowModal();
		delete frm;
	}
	else
	{
		ShowNoPower();
  	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::OrderControlExecute(TObject *Sender)
{
	//定单业务控制
	if (!FindDog()) {
        return;
	}
	if (CheckPower("订单业务控制")) {
		Tfrmorderbsset *frm = new Tfrmorderbsset(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StockControlExecute(TObject *Sender)
{
	//采购业务控制
	if (!FindDog()) {
        return;
	}
	if (CheckPower("采购业务控制")) {
		Tfrmprocureset *frm = new Tfrmprocureset(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::storagecontrolExecute(TObject *Sender)
{
	//入库业务控制
	if (!FindDog()) {
        return;
	}
	if (CheckPower("入库业务控制")) {
		Tfrmstoragebsset *frm = new Tfrmstoragebsset(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SaleControlExecute(TObject *Sender)
{
	//批销业务控制
	if (!FindDog()) {
        return;
	}
	if (CheckPower("批销业务控制")) {
		Tfrmsalebsset *frm = new Tfrmsalebsset(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RetailControlExecute(TObject *Sender)
{
	//零售业务控制
	if (!FindDog()) {
        return;
	}
	if (CheckPower("零售业务控制")) {
		Tfrmretailbsset *frm = new Tfrmretailbsset(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::PeiShongExecute(TObject *Sender)
{
		//配送业务控制
	if (!FindDog()) {
        return;
	}
		if (CheckPower("配送业务控制")) {
		Tfrmdiaoboset *frm = new Tfrmdiaoboset(Application,frmLand->conLand);
			frm->Show();
		}
		else
		{
			ShowNoPower();
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierClassExecute(TObject *Sender)
{
	//供应商类别
	if (!FindDog()) {
        return;
	}
	if (CheckPower("供应商分类")) {
		Tfrmcustomertype *frm = new Tfrmcustomertype(Application,frmLand->conLand,1);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientClassExecute(TObject *Sender)
{
	//客户类别
	if (!FindDog()) {
        return;
	}
	if (CheckPower("客户分类")) {
		Tfrmcustomertype *frm = new Tfrmcustomertype(Application,frmLand->conLand,2);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SmartstorageExecute(TObject *Sender)
{
	//智能入库
   //	MessageBoxA(0,"试用版不提供此功能!","提示",MB_ICONASTERISK);
		//return;
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("智能入库")) {
		ZNStorage(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::peisongExecute(TObject *Sender)
{

	//连锁配送
	if (!FindDog()) {
        return;
	}
	if (CheckPower("连锁配送")) {
		HWND hWnd;
		hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);
		TCHAR buf[MAX_PATH+1];
		while (hWnd != NULL)
		{
			::ZeroMemory(buf, sizeof(buf));
			if (::GetClassName(hWnd, buf, MAX_PATH) > 0)
			{
				if (StrCmp(_T("Tfrmdiaobo"), buf) == 0)
				{
					MessageBox(0,"为了保证连锁店库存的真实有效性\n一个用户同时只允许打开一个主动配送或请求配送模块！","提示" ,MB_OK|MB_ICONASTERISK);
					return;
				}
			}
			hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
		}

		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand ;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		li.UserName = frmLand->GetUserNameA();

		if (((TMenuItem*)Sender)->Tag ==1)   //主动配送
		{
			DiaoBo(&li,1,"");
		}else if (((TMenuItem*)Sender)->Tag ==0) {
			DiaoBo(&li,0,"");
		}else if (((TMenuItem*)Sender)->Tag ==2) {    //配送单处理

		}
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::peishongsearchExecute(TObject *Sender)
{
	//配送查询
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("配送查询")) {
		QryPeisongNote(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MyWorkExecute(TObject *Sender)
{
	//我的工作平台
	TfrmMyWork * frm = new TfrmMyWork(Application,frmLand->conLand ,frmLand->GetUserID());
	if (frm->ShowModal() == mrOk ) {
		//LoadMyWork(frmLand->GetUserID());
	}
	//frm->Show();
	//LoadMyWork(frmLand->GetUserID());
	/*if (CheckPower("我的工作平台")) {
		TfrmMyWork * frm = new TfrmMyWork(Application,frmLand->conLand ,frmLand->GetUserID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}  */
}
//---------------------------------------------------------------------------





void __fastcall TfrmMain::ClientbijiaoExecute(TObject *Sender)
{
	//客户比较
    if (!FindDog()) {
        return;
	}
	if (CheckPower("客户比较")) {
		Tfrmbijiao * frm = new Tfrmbijiao(Application);
		frm->type = 1;
		frm->init(frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierbijiaoExecute(TObject *Sender)
{
	//供应商
    if (!FindDog()) {
        return;
	}
	if (CheckPower("供应商比较")) {
		Tfrmbijiao * frm = new Tfrmbijiao(Application);
		frm->type = 2;
		frm->init(frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::retailPrintExecute(TObject *Sender)
{
	//零售打印
	if (!FindDog()) {
        return;
	}
	if (CheckPower("零售打印")) {
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		ManagePrint(Application, frmLand->conLand, 3,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::tongjibaobiaoExecute(TObject *Sender)
{
	//统计报表
    if (!FindDog()) {
        return;
	}
	if (CheckPower("统计报表")) {
		TfrmBaobiao * frm = new TfrmBaobiao(Application,frmLand->conLand,frmLand->GetStorageID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormViewExecute(TObject *Sender)
{
	//画面显示设置
	if (!FindDog()) {
        return;
	}
	if (CheckPower("工具栏选项管理")) {
		Tfrmformview *frm = new Tfrmformview(Application,frmLand->conLand,frmLand->GetStorageID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::dangrijzExecute(TObject *Sender)
{
	//单日结账
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("零售结账查询")) {
		CheckQuery(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::JxcbijiaoExecute(TObject *Sender)
{
	//进销存比较
    if (!FindDog()) {
        return;
	}
	if (CheckPower("进销存比较")) {
		Tfrmjxcbijiao * frm = new Tfrmjxcbijiao(Application,frmLand->conLand,frmLand->GetStorageID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::wangshangOrderExecute(TObject *Sender)
{
	//订单管理
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
		li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID() ;
    if (CheckPower("C网订单") ) {
		COrder(&li);
	}else
	{
		ShowNoPower();
	}    // */
  //	MessageBox(0,"此功能结合B2B网上订单系统一起使用！","提示",MB_ICONASTERISK|MB_OK);
	//	return;

  /*	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
		li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID() ;
	if (CheckPower("客户订单") ) {
		BIOrderManage(&li,2);
	}else
	{
		ShowNoPower();
	}     */
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::catalogneworrecExecute(TObject *Sender)
{
	//新荐书目
	if (!FindDog()) {
        return;
	}
	if (CheckPower("新荐书目") ) {
		Catalogneworrec(Application, frmLand->conLand);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::OrdershenheiExecute(TObject *Sender)
{
	//订单审核
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("订单审核") ) {
		OrdereShenhei(&li);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::CaigouOrderExecute(TObject *Sender)
{
	//智能采购
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("智能采购") ) {
		CaigoufromOrder(&li);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::bookfenfaExecute(TObject *Sender)
{
	//到货分发
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("到货分发") ) {
		daohuofenfa(&li);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::fahuorateExecute(TObject *Sender)
{
	//发货比例分析
	if (!FindDog()) {
        return;
	}
	if (CheckPower("发货比例分析") ) {
		Tfrmrate *frm = new Tfrmrate(Application,frmLand->conLand,frmLand->GetStorageID());
		frm->Show();
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::daohuorateExecute(TObject *Sender)
{
	//到货比例分析
	if (!FindDog()) {
        return;
	}
	if (CheckPower("到货比例分析") ) {
		Tfrmdaohuorate *frm = new Tfrmdaohuorate(Application,frmLand->conLand,frmLand->GetStorageID());
		frm->Show();
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::imagesftMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
		uix = X;
		uiy = Y;

		  //	Label1->Caption = IntToStr(X);
	  //	Label2->Caption = IntToStr(Y);

		if (uix >405 && uix < 485 && uiy >119 && uiy < 151) {     //未发货超期提醒
		Screen->Cursor =  Controls::crHandPoint ;
		}else
		{
		Screen->Cursor =  Controls::crDefault ;
		}
		if (uix >661 && uix < 736 && uiy >111 && uiy < 173) {          //未到货超期提醒
			Screen->Cursor =  Controls::crHandPoint ;
		}
		  if (uix >407 && uix < 484 && uiy >239 && uiy < 288) {          //发货比率分析
			Screen->Cursor =  Controls::crHandPoint ;

		}
		  if (uix >662 && uix < 733 && uiy >239 && uiy < 280) {          //到货比率分析
		   Screen->Cursor =  Controls::crHandPoint ;
		}
		  if (uix >407 && uix < 477 && uiy >371 && uiy < 410) {          //销售同期比较
			Screen->Cursor =  Controls::crHandPoint ;

		}
		  if (uix >668 && uix < 740 && uiy >372 && uiy < 416) {          //供货同期比较
		 Screen->Cursor =  Controls::crHandPoint ;

		}

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::caigoutixingExecute(TObject *Sender)
{
	//超期未到货提醒
	if (!FindDog()) {
        return;
	}
	if (CheckPower("超期未到货提醒") ) {
		Tfrmcaigouyuji *frma = new Tfrmcaigouyuji(Application,frmLand->conLand ,frmLand->GetStorageID());
		frma->Show();
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ordertixingExecute(TObject *Sender)
{
	//超期未发货提醒
	if (!FindDog()) {
        return;
	}
	if (CheckPower("超期未发货提醒") ) {
		Tfrmorderyuji *frm = new Tfrmorderyuji(Application,frmLand->conLand ,frmLand->GetStorageID());
		frm->Show();
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::OrderaskbookExecute(TObject *Sender)
{
	//询书
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("订单询书") ) {
		orderask(&li);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::siglebookExecute(TObject *Sender)
{
    if (!FindDog()) {
        return;
	}
	if (CheckPower("单品分析") ) {
		Tfrmsiglebook *frm = new Tfrmsiglebook(Application,frmLand->conLand ,frmLand->GetStorageID());
		frm->Show();
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::siglebookfenfaExecute(TObject *Sender)
{
	//单书分发
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("单书分发") ) {
		siglefenfa(&li);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::saletongqiExecute(TObject *Sender)
{
	//销售同期比较
	if (!FindDog()) {
        return;
	}
	if (CheckPower("销售同期比较") ) {
		Tfrmtongqisale *frm = new Tfrmtongqisale(Application,frmLand->conLand,frmLand->GetStorageID());
		frm->Show();
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::rukutongqiExecute(TObject *Sender)
{
	//供货同期比较
	if (!FindDog()) {
        return;
	}
	if (CheckPower("供货同期比较") ) {
		Tfrmtongqiruku *frm = new Tfrmtongqiruku(Application,frmLand->conLand,frmLand->GetStorageID());
		frm->Show();
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::qikanguanliExecute(TObject *Sender)
{
	//期刊管理
	if (!FindDog()) {
        return;
	}
	if (CheckPower("期刊目录管理") ) {
		QiKanguanli(Application, frmLand->conLand);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StorToStorExecute(TObject *Sender)
{
	if (!FindDog()) {
		return;
	}
	if (!frmLand->GetMaster() ) {
		MessageBoxA(0,"只有总店相关人员才能进行该项设置！","提示",MB_ICONWARNING);
		return;
	}
	if (CheckPower("各店互访权限管理")) {
		TfrmStorToStor *frm = new TfrmStorToStor(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::SetyjdiscountExecute(TObject *Sender)
{
	if (!FindDog()) {
		return;
	}
	if (CheckPower("预计折扣管理")) {
		Tfrmsetdiscount *frm = new Tfrmsetdiscount(Application,frmLand->conLand,frmLand->GetStorageID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberadddotExecute(TObject *Sender)
{
	if (!FindDog()) {
		return;
	}
	if (CheckPower("会员类型与预计折扣")) {
		Memtypeadd(Application,frmLand->conLand,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StockAlarmControlExecute(TObject *Sender)
{
	//配送业务控制
	if (!FindDog()) {
		return;
	}
	if (CheckPower("库存预警设置")) {
		Tfrmstockalarmbsset *frm = new Tfrmstockalarmbsset(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}

//---------------------------------------------------------------------------

void __fastcall TfrmMain::Timer1Timer(TObject *Sender)
{
	LoadMyMessage();
}
//---------------------------------------------------------------------------

void TfrmMain::Time()
{
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = frmLand->conLand ;
	AnsiString sql,settime,timecha;
	DATE set,now;
	sql = "select value,bk from sys_bsset where name = 'timestockalarm'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->FieldByName("value")->AsBoolean  )
	{
		settime = DateToStr(Date());
		if (aq->FieldByName("bk")->AsString .Length()> 2  ) {
			settime = settime + " " + aq->FieldByName("bk")->AsAnsiString + ":00";
		}
		else
		{
			settime = settime + " " + aq->FieldByName("bk")->AsAnsiString + ":00:00";
		}

		set = StrToDateTime(settime);
		now = Now();

		DateTimeToStr(set);
		timecha = DateTimeToStr(now-set);
		AnsiString houer,min,second;
		houer = timecha.SubString(timecha.Pos(":")-2 ,2);

		min = timecha.SubString(timecha.Pos(":")+1,2);

		second = timecha.SubString(timecha.Pos(":")+4,2);
		int totalmin;

		if ( StrToInt(houer) == 0 && StrToInt(min) == 0 ) {
			Tfrmalarm *frm = new Tfrmalarm(Application,frmLand->conLand,frmLand->GetStorageID());
		}
		else
		{
			if (now <= set ) {
				totalmin = StrToInt(houer)*60 + StrToInt(min);
				Timer2->Interval = totalmin*60000 + StrToInt(second)*1000;
				Timer2->Enabled = true;
			}
			else
			{
				Timer2->Enabled = false;
			}
		}
	}
	else
	{
		Timer2->Enabled = false;
	}
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Timer2Timer(TObject *Sender)
{
	Time();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MenuItem3Click(TObject *Sender)
{
	Storagealarm->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MenuItem1Click(TObject *Sender)
{
	Tfrmalarm *frm = new Tfrmalarm(Application,frmLand->conLand,frmLand->GetStorageID());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MutibookExecute(TObject *Sender)
{
	//重书合并
	if (!FindDog()) {
		return;
	}
	if (CheckPower("重书合并")) {
		Multibook(Application,frmLand->conLand ,frmLand->GetStorageID(),frmLand->GetUserID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------




void __fastcall TfrmMain::PrinttitleExecute(TObject *Sender)
{
	//单据抬头
	if (!FindDog()) {
		return;
	}
	if (CheckPower("打印信息设置")) {
		Tfrmprinttitle *frm = new Tfrmprinttitle(Application,frmLand->conLand,frmLand->GetStorageID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::dgmsgCellClick(TColumn *Column)
{
	if (aqmsg->IsEmpty() ) {
		return;
	}
	LandInfo li;
	int type =0;
	int ID;
	type = 2;
	AnsiString DanHao;
	type =	aqmsg->FieldByName("Type")->AsInteger ;
	ID = aqmsg->FieldByName("ID")->AsInteger ;
	DanHao = aqmsg->FieldByName("Value")->AsAnsiString ;
	adosp->Connection = frmLand->conLand;
	try
	{
	   switch (type) {
		   case 1:
				li.app = Application;
				li.con = frmLand->conLand  ;
				li.userID = frmLand->GetUserID()  ;
				li.FormatStr = "#,##0.00";
				li.storageID =  frmLand->GetStorageID()  ;
				adosp->Parameters->ParamByName("@ID")->Value =ID;
				adosp->ExecProc();
				BIOrderManageDanHao(&li,DanHao);

				break;
		   case 2:
		   case 3:
            	HWND hWnd;
				hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);
				TCHAR buf[MAX_PATH+1];
				while (hWnd != NULL)
				{
					::ZeroMemory(buf, sizeof(buf));
					if (::GetClassName(hWnd, buf, MAX_PATH) > 0)
					{
						if (StrCmp(_T("Tfrmdiaobo"), buf) == 0)
						{
							MessageBox(0,"为了保证连锁店库存的真实有效性\n一个用户同时只允许打开一个主动配送或请求配送模块！","提示" ,MB_OK|MB_ICONASTERISK);
							return;
						}
					}
					hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
				}

				LandInfo li;
				li.app = Application;
				li.con =  frmLand->conLand ;
				li.userID =   frmLand->GetUserID();
				li.storageID =  frmLand->GetStorageID();
				li.UserName = frmLand->GetUserNameA();
				DiaoBo(&li,2,DanHao);
				adosp->Parameters->ParamByName("@ID")->Value = ID;
				adosp->ExecProc();
			   break;
		 }
   }catch(...)
   {

   }
	LoadMyMessage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N28Click(TObject *Sender)
{
	//连锁配送
	if (!FindDog()) {
        return;
	}
	if (CheckPower("连锁配送")) {
		HWND hWnd;
		hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);
		TCHAR buf[MAX_PATH+1];
		while (hWnd != NULL)
		{
			::ZeroMemory(buf, sizeof(buf));
			if (::GetClassName(hWnd, buf, MAX_PATH) > 0)
			{
				if (StrCmp(_T("Tfrmdiaobo"), buf) == 0)
				{
					MessageBox(0,"为了保证连锁店库存的真实有效性\n一个用户同时只允许打开一个主动配送或请求配送模块！","提示" ,MB_OK|MB_ICONASTERISK);
					return;
				}
			}
			hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
		}

		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand ;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		li.UserName = frmLand->GetUserNameA();

		DiaoBo(&li,1,"");
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tongjiyewuExecute(TObject *Sender)
{
	//业务统计
	if (!FindDog()) {
		return;
	}
	if (CheckPower("业务统计")) {
		YuTongji(Application, frmLand->conLand,frmLand->GetStorageID());
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ZuliClassExecute(TObject *Sender)
{
	//租赁类别管理
	if (!FindDog()) {
        return;
	}
	if (CheckPower("租赁类别管理")) {
		BigBookType(Application, frmLand->conLand);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ImpOrderExecute(TObject *Sender)
{
	//订单管理
    /*if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
		li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID() ;
	if (CheckPower("客户订单") ) {
		ImpBIOrderManage(&li,0);
	}else
	{
		ShowNoPower();
	}  */
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientadddotExecute(TObject *Sender)
{
	if (!FindDog()) {
		return;
	}

	Tfrmclientadddot *frm = new Tfrmclientadddot(Application,frmLand->conLand,frmLand->GetStorageID());
	frm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::calculatstockExecute(TObject *Sender)
{
	if (!FindDog()) {
		return;
	}
	if (CheckPower("库存重算")) {
		if (MessageBoxA(0,"确定要重新计算库存？","提示",MB_ICONQUESTION|MB_OKCANCEL)==1)
		{
			TADOQuery *aq = new TADOQuery(NULL);
			aq->Connection = frmLand->conLand ;
			AnsiString sql;
			sql = " exec Stack_Amount_Calculation " +IntToStr(frmLand->GetStorageID() );
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			delete aq;
			MessageBox(0,"库存已重新计算！","提示" ,MB_OK|MB_ICONASTERISK);
		}
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierMergeExecute(TObject *Sender)
{
	if (!FindDog()) {
		return;
	}
	if (CheckPower("合并供应商")) {
		TfrmSupplierMerge *frm = new TfrmSupplierMerge(Application,frmLand->conLand);
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::CbpriceExecute(TObject *Sender)
{
	if (!FindDog()) {
		return;
	}
	if (CheckPower("计算成本")) {
		TfrmCbprice *frm = new TfrmCbprice(Application,frmLand->conLand,frmLand->GetStorageID());
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------
/*void __fastcall TfrmMain::WndProc(TMessage &Msg)
{
	//不显示滚动条
		ShowScrollBar(frmMain->ClientHandle,SB_BOTH,false);

        //   Then   call   the   original   WndProc()   for   the   other   messages
        if(OriginalClientWndProc   !=   0)
        {
              Message.Result
                =   CallWindowProc(reinterpret_cast<FARPROC>(OriginalClientWndProc),
                                                  ClientHandle,
												  Message.Msg,
                                                  Message.WParam,
                                                  Message.LParam);
		}
}  */

//---------------------------------------------------------------------------





void __fastcall TfrmMain::OrderLocalconfigExecute(TObject *Sender)
{
	//订单锁定数量确认
	if (!FindDog()) {
		return;
	}

	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID() ;
	if (CheckPower("订单锁定数量确认") ) {
		OrderLock(&li);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N84Click(TObject *Sender)
{
                if (!FindDog()) {
                    return;
                }                  //CheckPower("计算成本")
        	if (CheckPower("业务数据锁定")) {
                   Tfrmbslock * frm = new Tfrmbslock(Application,frmLand->conLand,frmLand->GetStorageID());
                    frm->Show();
                }else ShowNoPower();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N85Click(TObject *Sender)
{
            if (!FindDog()) {
                return;
            }                  //CheckPower("计算成本")
            if (CheckPower("单位资料锁定")) {
                Tfrmlock * frm = new Tfrmlock(Application,frmLand->conLand,frmLand->GetStorageID());
                frm->Show();
            }else ShowNoPower();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N87Click(TObject *Sender)
{
            if (!FindDog()) {
               return;
            }                  //CheckPower("计算成本")
            if (CheckPower("库存结转查询")) {
                LandInfo li;
                li.app = Application;
                li.con = frmLand->conLand;
                li.userID = frmLand->GetUserID();
                li.FormatStr = "#,##0.00";
                li.storageID = frmLand->GetStorageID() ;
                QryJiechun(&li);
            }else ShowNoPower();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N88Click(TObject *Sender)
{
      if (!FindDog()) {
               return;
            }                  //CheckPower("计算成本")
            if (CheckPower("库存结转")) {
                LandInfo li;
                li.app = Application;
                li.con = frmLand->conLand;
                li.userID = frmLand->GetUserID();
                li.FormatStr = "#,##0.00";
                li.storageID = frmLand->GetStorageID() ;
                 Tfrmkuchenjizhuan * frm = new Tfrmkuchenjizhuan(Application,frmLand->conLand,frmLand->GetUserID(),frmLand->GetStorageID());
                frm->Show();
            }else ShowNoPower();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::B1Click(TObject *Sender)
{
   //	B网订单查询
   OrderSearch->Execute()  ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::C1Click(TObject *Sender)
{
//  C网订单查询
	//订单查询
	if (!FindDog()) {
		return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	//if (CheckPower("订单查询")) {
		QryCOderNote(&li);
   //	}
  //	else
   //	{
   //		ShowNoPower();
   //	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::C2Click(TObject *Sender)
{
//
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID() ;
   //	if (CheckPower("订单锁定数量确认") ) {
		COrderLock(&li);
   //	}else
   //	{
   //		ShowNoPower();
  //	}
}
//---------------------------------------------------------------------------

