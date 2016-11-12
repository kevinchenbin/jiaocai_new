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
	//��ⵥ��ʽ

	ManagePrint(Application, frmLand->conLand, 1,frmLand->GetStorageID());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N9Click(TObject *Sender)
{
	//��������ʽ
	ManagePrint(Application, frmLand->conLand, 2,frmLand->GetStorageID());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N10Click(TObject *Sender)
{
	//����СƱ��ʽ
	if (CheckPower("��ӡ����")) {
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
	//ҵ������
  /*	if (CheckPower("ҵ������")) {
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
	//�ۿۿ���
	ControlDiscount(Application, frmLand->conLand);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N42Click(TObject *Sender)
{
   //��Ӧ�̸����ѯ

   if (CheckPower("�����ѯ")) {
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
	//�ͻ������ѯ

	if (CheckPower("�տ��ѯ")) {
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
	// ���ս���

	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("���ս���ͳ��")) {
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
	//���Ӵ���ȫ���ر�
	HWND hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);
	while (hWnd != NULL)
	{

		if(MessageBox(0,"��δ�رմ��ڣ��Ƿ��˳���,ȷ�Ͻ��ر�����ϵͳ��" ,"ȷ��" ,MB_ICONQUESTION|MB_OKCANCEL)==1)
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
	//����Ƿ���δ�رյ��Ӵ���
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
	//��������ܹر�������
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
	//�û���Ȩ������

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
	//���׿�������

	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("�����������")) {
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
     	frmMain->Caption="������wise ��ҵ�ǹ�ƽ̨--------ī��C��רҵ��";

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
{        //��������

}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N73Click(TObject *Sender)
{
  //���ݱ���

  if (CheckPower("���ݱ���")) {
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
  //���ݻָ�

  if (CheckPower("���ݻָ�")) {
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
{          //�ͻ��տ����


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientWndProc(TMessage&   Message)
{

	 //����ʾ������
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
  j = PanelList->IndexOf(PUIName);    //ȡ��Ҫ��ʾ��panel

   TImage * pvisable = (TImage *)PanelList->Objects[j];
   pvisable->Visible  = true;
 //  imageui->Canvas->StretchDraw(Rect(0,42,1012 ,549),pvisable->Picture->Graphic);
 //  Rect(
   //	Graphics::TBitmap   *   pBitmap=new   Graphics::TBitmap();
  //pBitmap->
  //Image1->Picture->Assign(pBitmap);
   return;


  for (i = 0; i < PanelList->Count; i++) {      //����Ҫ��ʾ��panel visibleΪtrue

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
  j = PanelList->IndexOf(PUIName);    //ȡ��Ҫ��ʾ��panel

   TImage * pvisable = (TImage *)PanelList->Objects[j];
   pvisable->Visible  = false;


}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::imagelsMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{


     	uix = X;
	uiy = Y;
	if (uix >212 && uix < 265 && uiy >17 && uiy < 30) {          //��Ա����
		Screen->Cursor =  Controls::crHandPoint;

	} else
		  {
			Screen->Cursor =  Controls::crDefault  ;
		  }
		if (uix >310 && uix < 361 && uiy >17 && uiy < 30) {          //��Ա��ֵ
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >402 && uix < 479 && uiy >17 && uiy < 30) {          //��Ա��ֵ��ѯ
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >351 && uix < 411 && uiy >174 && uiy < 219) {          //POS ����
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >351 && uix < 412 && uiy >310 && uiy < 351) {          //pos �����˻�
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >540 && uix < 592 && uiy >241 && uiy < 283) {          //����Ա���Ӱ�
		Screen->Cursor =  Controls::crHandPoint ;

	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imageuiClick(TObject *Sender)
{
	Screen->Cursor =  Controls::crDefault   ;
	/*  if (uix > 6 && uix < 154 ) {
	  if (uiy >103 && uiy < 130) {  //�ɹ�����

		Display("imagecg");
	  }
	  if (uiy > 170 && uiy < 196) {    //����
		 Display("imagepx");
	  }
	  if (uiy > 137 && uiy < 163) { //���
		   Display("imagekc");
	  }
	  if (uiy > 204 && uiy < 229) {     //����
			 Display("imagels");
	  }
	  if (uiy > 236 && uiy < 261) {   //����
	  Display("imagewl");

	  }
	  if (uiy > 271 && uiy < 296) {    //ͳ��
	  Display("imagetj");

	  }

	}*/
   //}
   if  ((((TImage*)(Sender))->Name == "imagext")) {
	Screen->Cursor = Controls:: crDefault  ;
		   if (uix >350 && uix < 407 && uiy >239 && uiy < 296) {          //�������
			  renwu->Execute()  ;

		  }

		  if (uix >516 && uix < 576 && uiy >243 && uiy < 294) {          //�ĵ�����
			   wengdang->Execute()  ;

		  }
		  if (uix >689 && uix < 741 && uiy >245	&& uiy < 307) {          //���߽���
			  jiaoliu->Execute()  ;

		  }
   }

   //����ͨ
	if  ((((TImage*)(Sender))->Name == "imagesft")) {
		Screen->Cursor = Controls:: crDefault  ;
	if (uix >405 && uix < 485 && uiy >119 && uiy < 151) {     //δ������������
			ordertixing->Execute();
		}
		if (uix >661 && uix < 736 && uiy >111 && uiy < 173) {          //δ������������
		//  wengdang->Execute()  ;
			caigoutixing->Execute();
		}
		  if (uix >407 && uix < 484 && uiy >239 && uiy < 288) {          //�������ʷ���
		//wengdang->Execute()  ;
			fahuorate->Execute();
		}
		  if (uix >662 && uix < 733 && uiy >239 && uiy < 280) {          //�������ʷ���
		//wengdang->Execute()  ;
			daohuorate->Execute();
		}
		  if (uix >407 && uix < 477 && uiy >371 && uiy < 410) {          //����ͬ�ڱȽ�
		//wengdang->Execute()  ;
			saletongqi->Execute();
		}
		  if (uix >668 && uix < 740 && uiy >372 && uiy < 416) {          //����ͬ�ڱȽ�
	  //	wengdang->Execute()  ;
			//Supplierbijiao->Execute();
			rukutongqi->Execute();
		}
   }






   if  ((((TImage*)(Sender))->Name == "imagesearch")) {
	Screen->Cursor = Controls:: crDefault  ;
		 if (uix >324 && uix < 385 && uiy >164 && uiy < 214) {          //����ѯ
			   StorageSearch->Execute()  ;

		  }
		  if (uix >480 && uix < 541 && uiy >165 && uiy < 217) {      //������ѯ
			   popmorder->Popup(600,310);

		  }
		  if (uix >642 && uix < 699 && uiy >170 && uiy < 213) {          //�ɹ���ѯ
			   stocksearch->Execute()  ;

		  }
		  if (uix >784 && uix < 850 && uiy >172 && uiy < 217) {          //����ѯ
			   rikusearch->Execute()  ;

		  }

		  if (uix >323 && uix < 386 && uiy >330 && uiy < 381) {              //������ѯ
			   salesearch->Execute()  ;

		  }
		  if (uix >473 && uix < 543 && uiy >327 && uiy < 377) {          //POS���۲�ѯ
			  posretailsearch->Execute()  ;

		  }

		  if (uix >634 && uix < 707 && uiy >325 && uiy < 384) {          //�̵��ѯ
			  storagechecksearch->Execute()  ;

		  }
		  if (uix >776 && uix < 851 && uiy >332 && uiy < 377) {          //���Ͳ�ѯ
			   peishongsearch->Execute()  ;

		  }
   }
   if ((((TImage*)(Sender))->Name == "imagetj")) {
	Screen->Cursor = Controls:: crDefault  ;
		  if (uix >288 && uix < 356 && uiy >107 && uiy < 153) {          //�������˻�
			 retailandback->Execute()  ;

		  }else
		  {
			 Screen->Cursor =  Controls::crDefault  ;
		  }
		  if (uix >436 && uix < 511 && uiy >109 && uiy < 157) {          //�������˻�
			   saleandback->Execute()  ;

		  }


		  if (uix >662 && uix < 729 && uiy >114 && uiy < 160) {          //���������
				jingxiaochunfenxie->Execute()  ;

		  }
		  if (uix >812 && uix < 880 && uiy >111 && uiy < 162) {          //δ��������
			  weidongkuchun->Execute()  ;

		  }
		  if (uix >821 && uix < 874 && uiy >256 && uiy < 307) {          //��Ӧ�̽׶ν������
			Supplierjiduanfexie->Execute()  ;

		  }
			  if (uix >669 && uix < 732 && uiy >251 && uiy < 308) {          //�ͻ��׶ν������
			   Clientjieduanfexie->Execute()  ;

		  }
					  if (uix >434 && uix < 497 && uiy >258 && uiy < 310) {          //���ۻ��ܷ���
			   retailhuizhongfengxie->Execute()  ;

		  }
			if (uix >438 && uix < 487 && uiy >400 && uiy < 451) {          //ҵ�����а�
			 yefupaihangbang->Execute()  ;

		  }
			if (uix >820 && uix < 875 && uiy >404 && uiy < 450) {          //������������ë������
			   changxiaobook->Execute()  ;

		  }
		  if (uix >669 && uix < 732 && uiy >404 && uiy < 450) {          // ��Ʒ����
			   siglebook->Execute();
		  }
			if (uix >288 && uix < 342 && uiy >255 && uiy < 311) {          //����ʱ�λ���ͳ��
			 saletimehuizhong->Execute()  ;

		  }
			if (uix >289 && uix < 341 && uiy >399 && uiy < 451) {          //����ͳ�Ʊ���
			   saletongjireport->Execute()  ;

		  }
   }
   if  (((TImage*)(Sender))->Name == "imagewl") {
	Screen->Cursor = Controls:: crDefault  ;
        if (uix >321 && uix < 387 && uiy >156 && uiy < 215) {          //��Ӧ������
			  SupplierInfo->Execute();

		  }
		  if (uix >487 && uix < 542 && uiy >167 && uiy < 213) {          //�ͻ�����
			   ClientInfo->Execute();

		  }


		  if (uix >645 && uix < 707 && uiy >169 && uiy < 216) {          //ҵ��Ա����
			salermanage->Execute();

		  }
		  if (uix >788 && uix < 838 && uiy >167 && uiy < 214) {          //���ù���
			  creditManage->Execute();

		  }
		  if (uix >318 && uix < 381 && uiy >321 && uiy < 381) {          //��Ա����
			  MemberInfo->Execute();

		  }
			  if (uix >487 && uix < 554 && uiy >326 && uiy < 383) {          //��Ա��ֵ
			   Memberchongzhi->Execute();

		  }
			  if (uix >643 && uix < 714 && uiy >327 && uiy < 381) {          //��Ա��ֵ��ѯ
			   MemberchongziSearch->Execute();

		  }
   }
   if (((TImage*)(Sender))->Name == "imagecf") {
	Screen->Cursor = Controls:: crDefault  ;
		 if (uix >316 && uix < 373 && uiy >75 && uiy < 115) {     //��Ӧ�������ڳ�
			financestart->Execute();
		  }
			  if (uix >446 && uix < 507 && uiy >71 && uiy < 119) {    //Ӧ������
				yihutotal->Execute();
		 }

			  if (uix >317 && uix < 373 && uiy >180 && uiy < 228) {        //��Ӧ����������
			  supplierduizhang->Execute();
		  }

			  if (uix >445 && uix < 505 && uiy >181 && uiy < 321) {        //Ӧ����ϸ
			   yingfudetail->Execute();
		  }
			  if (uix >646 && uix < 703 && uiy >136 && uiy < 173) {        //��Ӧ�̽���
			  Supplierjieshuan->Execute();
		  }
				  if (uix >803 && uix < 860 && uiy >141 && uiy < 177) {        //��Ӧ�̽����ѯ
			  SupplierjieShuanSearch->Execute();
		  }
				  if (uix >312 && uix < 368 && uiy >330 && uiy < 375) {        //�ͻ������ڳ�
			  ClientfinanceStart->Execute();
		  }
			  if (uix >454 && uix < 502 && uiy >329 && uiy < 375) {        //Ӧ�ջ���
			 yingshouhuizhong->Execute();
		  }

			  if (uix >311 && uix < 366 && uiy >440 && uiy < 486) {        //�ͻ���������
			  ClientWanglaiduizhang->Execute();
		  }

			  if (uix >454 && uix < 502 && uiy >444 && uiy < 485) {        //Ӧ����ϸ
			 yingshoudetail->Execute();
		  }

			  if (uix >657 && uix < 703 && uiy >378 && uiy < 420) {        //�ͻ�����
			 ClientJieShuan->Execute();
		  }
			if (uix >804 && uix < 855 && uiy >380 && uiy < 422) {        //�ͻ������ѯ
				Clientjieshuansearch->Execute();
			}

   }
	  if (((TImage*)(Sender))->Name == "imagecg") {
			  Screen->Cursor = Controls:: crDefault  ;
			 if (uix >195 && uix < 248 && uiy >15 && uiy < 27) {     //ƷĿ����
			BreedManage->Execute();
		  }
			  if (uix >278 && uix < 331 && uiy >15 && uiy < 27) {    //ƷĿ������                                                                �����
				breedType->Execute();
		 }
		 if (uix >367 && uix < 429 && uiy >15 && uiy < 27) {    //ƷĿ������                                                                �����
				pressmanage->Execute();
		 }

			  if (uix >461 && uix < 526 && uiy >15 && uiy < 27) {        //��Ӧ������
				SupplierInfo->Execute();
		  }

			  if (uix >562 && uix < 619 && uiy >15 && uiy < 27) {        //�������
				LocalManage->Execute();
		  }
			  if (uix >648 && uix < 707 && uiy >15 && uiy < 27) {        //��λ����
				StorageInfo->Execute();
		  }
				  if (uix >289 && uix < 341 && uiy >165 && uiy < 208) {        //һ��ɹ���
				SampleStock->Execute();
		  }
				  if (uix >463 && uix < 527 && uiy >120 && uiy < 161) {        //һ�����
					samplestorage->Execute();
		  }
			  if (uix >473 && uix < 528 && uiy >233 && uiy < 280) {        //����˻�
				storageback->Execute();
		  }

			  if (uix >289 && uix < 342 && uiy >300 && uiy < 340) {        //���ܲɹ�
					smartStock->Execute();
		  }

			  if (uix >475 && uix < 528 && uiy >354 && uiy < 399) {        //�������
					Smartstorage->Execute();
		  }

			  if (uix >661 && uix < 712 && uiy >233 && uiy < 281) {        //��Ӧ�̽׶ν������
					Supplierjiduanfexie->Execute();
		  }
			if (uix >827 && uix < 874 && uiy >234 && uiy < 279) {        //�������
					Supplierjieshuan->Execute();
			}

	  }


	 if (((TImage*)(Sender))->Name == "imagels") {
	  Screen->Cursor = Controls:: crDefault  ;
		if (uix >212 && uix < 265 && uiy >17 && uiy < 30) {          //��Ա����
		MemberInfo->Execute();

	}
		if (uix >310 && uix < 361 && uiy >17 && uiy < 30) {          //��Ա��ֵ
		Memberchongzhi->Execute();

	}
		if (uix >402 && uix < 479 && uiy >17 && uiy < 30) {          //��Ա��ֵ��ѯ
		MemberchongziSearch->Execute();

	}
		if (uix >351 && uix < 411 && uiy >174 && uiy < 219) {          //POS����
		Posretail->Execute();

	}
		if (uix >351 && uix < 412 && uiy >310 && uiy < 351) {          //pos�����˻�
		retailBack->Execute();

	}
		if (uix >540 && uix < 592 && uiy >241 && uiy < 283) {          //����Ա���Ӱ�
		jiaojieban->Execute();

	}


   }
	   if (((TImage*)(Sender))->Name == "imagekc") {
		Screen->Cursor = Controls:: crDefault  ;
	   if (uix >211 && uix < 262 && uiy >14 && uiy < 27) {     //��λ����

		   StorageInfo->Execute();

		  }
			  if (uix >307 && uix < 358 && uiy >17 && uiy < 27) {    //�̵��ѯ
				 storagechecksearch->Execute()  ;
		 }

			  if (uix >505 && uix < 559 && uiy >230 && uiy < 274) {        //���Ԥ��
				TPoint p;
				TPoint pt;
				p.x = 560;
				p.y= 310;
				pt = ClientToScreen(p);
				pmstockalarm->Popup(pt.x,pt.y);
		  }

			  if (uix >661 && uix < 708 && uiy >326 && uiy < 366) {        //��Ʒ���������
			 onestorageNumberadjust->Execute();
		  }
			  if (uix >351 && uix < 403 && uiy >321 && uiy < 368) {        //ʵ���̵�
			  shikupandian->Execute();
		  }
				  if (uix >654 && uix < 708 && uiy >142 && uiy < 185) {        //��λ����
			  storageLocaladjust->Execute();
		  }
				  if (uix >347 && uix < 398 && uiy >142 && uiy < 184) {        //�ֲ��̵�
			  xuyipandian->Execute();
		  }

		}

		   if (((TImage*)(Sender))->Name == "imagepx") {
			Screen->Cursor = Controls:: crDefault  ;
		if (uix >209 && uix < 263 && uiy >20 && uiy < 30) {          //�ͻ�����
		 ClientInfo->Execute();

	 }
		if (uix >305 && uix < 356 && uiy >20 && uiy < 30) {          //�������
	LocalManage->Execute();

	}
		if (uix >400 && uix < 453 && uiy >20 && uiy < 30) {          //�ͻ�����
		ClientClass->Execute();

	}
		if (uix >491 && uix < 559 && uiy >20 && uiy < 30) {          //ҵ��Ա����
		salermanage->Execute();

	}
		if (uix >609 && uix < 662 && uiy >20 && uiy < 30) {          //���ù���
	creditManage->Execute();

	}
		if (uix >273 && uix < 325 && uiy >150 && uiy < 197) {          //�ͻ�����
		ClientOrder->Execute();

	}
		if (uix >276 && uix < 337 && uiy >339 && uiy < 378) {          //���϶���
		wangshangOrder->Execute();

	}

		if (uix >461 && uix < 522 && uiy >121 && uiy < 161) {          //һ�㷢��
		samplesale->Execute();

	}
		if (uix >617 && uix < 697 && uiy >130 && uiy < 166) {          //�����˻�
		saleback->Execute();

	}
		if (uix >798 && uix < 851 && uiy >125 && uiy < 168) {           //���շ�����ݽ���
		Dangrijieshuan->Execute();

	}
		if (uix >536 && uix < 602 && uiy >254 && uiy < 293) {           //���ܷ���
		smartSale->Execute();

	}
		if (uix >456 && uix < 519 && uiy >398 && uiy < 438) {           //��������
		TPoint p;
		TPoint pt;
		p.x = 520;
		p.y= 438;
		pt = ClientToScreen(p);
		pmpeishong->Popup(pt.x,pt.y);
	   //	peisong->Execute();

	}
		if (uix >612 && uix < 675 && uiy >400 && uiy < 438) {           //��/���鴦��
		samplebook->Execute();

	}
		if (uix >797 && uix < 859 && uiy >264 && uiy < 303) {           //�ͻ��׶ν������
		Clientjieduanfexie->Execute();

	}
		if (uix >798 && uix < 857 && uiy >401 && uiy < 440) {           //�տ����
		ClientJieShuan->Execute();

	}

   }

	if (((TImage*)(Sender))->Name == "imageyx") {
	 Screen->Cursor = Controls:: crDefault  ;             //Ӫ��
		 if (uix >304 && uix < 358 && uiy >144 && uiy < 192) {     //����������
			retailclassPromotion->Execute();
		  }

			  if (uix >459 && uix < 520 && uiy >153 && uiy < 200) {    //���۹��������
				Retailbuy->Execute();
		 }

			  if (uix >618 && uix < 679 && uiy >154 && uiy < 195) {        //��Ա���͵�Ʒ����
			 MemberoneProduct->Execute();
		  }

			  if (uix >775 && uix < 819 && uiy >157 && uiy < 192) {        //��Ա���ֹ���
			 Memberjifen->Execute();
		  }
			  if (uix >314 && uix < 364 && uiy >334 && uiy < 381) {        //������Ʒ�ۿ�
			  SaleOneProduct->Execute();
		  }
				  if (uix >462 && uix < 522 && uiy >339 && uiy < 384) {        //���������ۿ�
			  SaleAddPoint->Execute();
		  }
				  if (uix >618 && uix < 682 && uiy >338 && uiy < 387) {        //�����ֳ�����
			  SaleNowbackDot->Execute();
		  }
			  if (uix >770 && uix < 837 && uiy >335 && uiy < 386) {        //������ȷ���
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

		  if (uix >451 && uix < 489 && uiy >220 && uiy < 290) {     //��ⵥ
				Screen->Cursor =  Controls::crHandPoint ;
		  }else
		  {
			Screen->Cursor =  Controls::crDefault  ;
		  }
			 if (uix > 451 && uix < 489 && uiy > 305 && uiy < 360) {   //����˻���
				Screen->Cursor =  Controls::crHandPoint ;
			 }
			 if (uix >609 && uix < 653 && uiy >260 && uiy < 320)  {    //���̽׶η���
				Screen->Cursor =  Controls::crHandPoint ;
		 }

			  if (uix >761 && uix < 822 && uiy >244 && uiy < 310) {        //�������
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >202 && uix < 264 && uiy >15 && uiy < 29) {        //ƷĿ����
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >284 && uix < 345 && uiy >15 && uiy < 29)  {        //������
			 Screen->Cursor =  Controls::crHandPoint ;
		  }

			if (uix >368 && uix <447 && uiy >15 && uiy < 29){         //��Ӧ��
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			 if (uix >473 && uix < 532 && uiy >15 && uiy < 29){          //����
			 Screen->Cursor =  Controls::crHandPoint ;
		  }

			if (uix >213 && uix < 274 && uiy >588 && uiy < 603) {          //����ѯ
			 Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >646 && uix < 710 && uiy >15 && uiy < 29) {          //��λ
			 Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >556 && uix < 619 && uiy >15 && uiy < 29) {          //���
			 Screen->Cursor =  Controls::crHandPoint ;
		  }
			 if (uix > 285 && uix < 340 && uix >257 && uiy <337) {     //һ��ɹ�
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

	   if (uix >211 && uix < 262 && uiy >14 && uiy < 27) {     //��λ����
			Screen->Cursor =  Controls::crHandPoint ;
		  }else
		  {
			Screen->Cursor =  Controls::crDefault  ;
		  }
			  if (uix >307 && uix < 358 && uiy >17 && uiy < 27) {    //�̵��ѯ
				Screen->Cursor =  Controls::crHandPoint ;
		 }

			  if (uix >505 && uix < 559 && uiy >230 && uiy < 274) {        //���Ԥ��
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >661 && uix < 708 && uiy >326 && uiy < 366) {        //��Ʒ���������
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >351 && uix < 403 && uiy >321 && uiy < 368) {        //ʵ���̵�
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >654 && uix < 708 && uiy >142 && uiy < 185) {        //��λ����
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >347 && uix < 398 && uiy >142 && uiy < 184) {        //�ֲ��̵�
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
	if (uix >209 && uix < 263 && uiy >20 && uiy < 30) {          //�ͻ�����
		Screen->Cursor =  Controls::crHandPoint ;

	}else
	{
		Screen->Cursor  = Controls::crDefault  ;
	}
		if (uix >305 && uix < 356 && uiy >20 && uiy < 30) {          //�������
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >400 && uix < 453 && uiy >20 && uiy < 30) {          //�ͻ�����
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >491 && uix < 559 && uiy >20 && uiy < 30) {          //ҵ��Ա����
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >609 && uix < 662 && uiy >20 && uiy < 30) {          //���ù���
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >273 && uix < 325 && uiy >150 && uiy < 197) {          //�ͻ�����
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >276 && uix < 337 && uiy >339 && uiy < 378) {          //���϶���
		Screen->Cursor =  Controls::crHandPoint ;

	}

		if (uix >461 && uix < 522 && uiy >121 && uiy < 161) {          //һ�㷢��
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >617 && uix < 697 && uiy >130 && uiy < 166) {          //�����˻�
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >798 && uix < 851 && uiy >125 && uiy < 168) {           //���շ�����ݽ���
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >536 && uix < 602 && uiy >254 && uiy < 293) {           //���ܷ���
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >456 && uix < 519 && uiy >398 && uiy < 438) {           //�������
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >612 && uix < 675 && uiy >400 && uiy < 438) {           //��/���鴦��
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >797 && uix < 859 && uiy >264 && uiy < 303) {           //�ͻ��׶ν������
		Screen->Cursor =  Controls::crHandPoint ;

	}
		if (uix >798 && uix < 857 && uiy >401 && uiy < 440) {           //�տ����
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


	  if (uix >288 && uix < 356 && uiy >107 && uiy < 153) {          //�������˻�
			  Screen->Cursor =  Controls::crHandPoint ;

		  }else
		  {
			 Screen->Cursor =  Controls::crDefault  ;
		  }
		  if (uix >436 && uix < 511 && uiy >109 && uiy < 157) {          //�������˻�
			   Screen->Cursor =  Controls::crHandPoint ;

		  }


		  if (uix >662 && uix < 729 && uiy >114 && uiy < 160) {          //���������
				Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >812 && uix < 880 && uiy >111 && uiy < 162) {          //δ��������
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >821 && uix < 874 && uiy >256 && uiy < 307) {          //��Ӧ�̽׶ν������
			  Screen->Cursor =  Controls::crHandPoint ;

		  }
			  if (uix >669 && uix < 732 && uiy >251 && uiy < 308) {          //�ͻ��׶ν������
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
					  if (uix >434 && uix < 497 && uiy >258 && uiy < 310) {          //���ۻ��ܷ���
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
			if (uix >438 && uix < 487 && uiy >400 && uiy < 451) {          //ҵ�����а�
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
			if (uix >820 && uix < 875 && uiy >404 && uiy < 450) {          //������������ë������
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >669 && uix < 732 && uiy >404 && uiy < 450) {          // ��Ʒ����
			   Screen->Cursor =  Controls::crHandPoint ;
		  }
		  if (uix >288 && uix < 342 && uiy >255 && uiy < 311) {          //����ʱ�λ���ͳ��
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
			if (uix >289 && uix < 341 && uiy >399 && uiy < 451) {          //����ͳ�Ʊ���
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

	  if (uix >321 && uix < 387 && uiy >156 && uiy < 215) {          //��Ӧ������
			  Screen->Cursor =  Controls::crHandPoint ;

		  }else
		  {
			Screen->Cursor =  Controls::crDefault  ;

		  }
		  if (uix >487 && uix < 542 && uiy >167 && uiy < 213) {          //�ͻ�����
			   Screen->Cursor =  Controls::crHandPoint ;

		  }


		  if (uix >645 && uix < 707 && uiy >169 && uiy < 216) {          //ҵ��Ա����
				Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >788 && uix < 838 && uiy >167 && uiy < 214) {          //���ù���
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >318 && uix < 381 && uiy >321 && uiy < 381) {          //��Ա����
			  Screen->Cursor =  Controls::crHandPoint ;

		  }
			  if (uix >487 && uix < 554 && uiy >326 && uiy < 383) {          //��Ա��ֵ
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
			  if (uix >643 && uix < 714 && uiy >327 && uiy < 381) {          //��Ա��ֵ��ѯ
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
   MessageBoxA(0,"��Ȩ�޲�����ģ��,�������Ա��ϵ!","����",MB_ICONASTERISK);
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
	//��Ա���ֹ���

	if (CheckPower("��Ա���ֹ���")) {
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
	//���ҵ������

	if (CheckPower("���ҵ������")) {
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
	//����ҵ������

	if (CheckPower("����ҵ������")) {
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
	//����ҵ������

	if (CheckPower("����ҵ������")) {
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
	//����ҵ������

	if (CheckPower("����ҵ������")) {
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
	if (CheckPower("��⹩Ӧ���޸�")) {
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

	if (CheckPower("��Ա������")) {
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
	//��Ӧ������

	if (CheckPower("��Ӧ������")) {
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
	//ϵͳ����

	if (CheckPower("ϵͳ����")) {
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
				MessageBoxA(0,"�����������!","��ʾ",MB_ICONASTERISK);
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
	//������

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N112Click(TObject *Sender)
{
	//�ͻ���������

}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N110Click(TObject *Sender)
{
	//����ҵ������

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
	//�ͻ�����

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
			" where  ((sys_action.actionname = '��������'  and SYS_InforMessage.type  in(2,3)) "
			" or ((sys_action.actionname = '�ͻ�����' or sys_action.actionname = 'һ��ɹ�') and SYS_InforMessage.type = 1)) "
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
		j = MessageInfo->IndexOf(MsgName);    //ȡ��Ҫ��ʾ��panel
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
        MessageBox(0,"��δ�رյ��Ӵ��ڣ���رպ����ԣ�","��ʾ",MB_ICONWARNING);
		return;
	}
	frmLand->edtPassword->Text = "";
	if (jiaojie == 1) {
		frmLand->Caption = "����Ա���Ӱ�";
	}
	else
	{
    	frmLand->Caption = "��½";
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
   if (MessageBoxA(0,"�Ƿ��˳�ϵͳ��","��ʾ",MB_ICONQUESTION|MB_OKCANCEL )==1 ) {


   Application->Terminate();

   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StogeSetExecute(TObject *Sender)
{
	//�����Ϣ����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("��ֹ���")) {
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
	//����������
	//ManageRetailSales(Application, frmLand->conLand);
	if (!FindDog()) {
        return;
	}
	if (CheckPower("����������")) {
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
	//���۹��������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("���۹��������")) {
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
	if (CheckPower("��Ա���͵�Ʒ����")) {
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
	//��Ա���ֹ���
	if (!FindDog()) {
        return;
	}
	if (!frmLand->GetMaster() ) {
		MessageBoxA(0,"ֻ���ܵ����Ȩ�޲�����ģ��!","��ʾ",MB_ICONASTERISK);
		return;
	}
	if (CheckPower("��Ա���ֹ���")) {
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
	if (CheckPower("������Ʒ�ۿ�")) {
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
	if (CheckPower("���������ۿ�")) {
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
	//�����ֳ�����
    if (!FindDog()) {
        return;
	}
	if (CheckPower("�����ֳ�����")) {
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
//	������ȷ���
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientOrderExecute(TObject *Sender)
{
	//��������
    if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
		li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID() ;


          if (CheckPower("�ͻ��������")) {      //Ȩ�޿���
             li.FormatStr = "1";
         }else li.FormatStr = "0";


	if (CheckPower("�ͻ�����") ) {
		BIOrderManage(&li,0);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SampleStockExecute(TObject *Sender)
{
	//�ɹ�����
    if (!FindDog()) {
        return;
	}
	if (CheckPower("һ��ɹ�") ) {
		LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID  = frmLand->GetStorageID();
		li.FormatStr = "#,##0.00";

                  if (CheckPower("��Ӧ���������")) {      //Ȩ�޿���
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
	//���ܲɹ�
    if (!FindDog()) {
        return;
	}
	if (CheckPower("���ܲɹ�") ) {
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
	//������
    if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;

	li.storageID = frmLand->GetStorageID();

         if (CheckPower("��Ӧ���������")) {      //Ȩ�޿���
             li.FormatStr = "1";
         }else li.FormatStr = "0";

               if (CheckPower("��Ŀ���") ) {
               li.FormatStr = li.FormatStr+"1";
              }else  li.FormatStr = li.FormatStr+"0";
           if (CheckPower("��Ŀ�޸�") ) {
               li.FormatStr = li.FormatStr+"1";
              }else  li.FormatStr = li.FormatStr+"0";
         
        
	if (CheckPower("һ�����")) {
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
	//����˻�����
    if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;

	li.storageID = frmLand->GetStorageID();

         if (CheckPower("��Ӧ���������")) {      //Ȩ�޿���
             li.FormatStr = "1";
         }else li.FormatStr = "0";

	if (CheckPower("����˻�")) {
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
	//��������
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


          if (CheckPower("�ͻ��������")) {      //Ȩ�޿���
             li.FormatStr = "1";
         }else li.FormatStr = "0";


	if (CheckPower("һ�㷢��")) {
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
//8��	���ܷ���
	//���ܷ���
	//MessageBoxA(0,"���ð治�ṩ�˹���!","��ʾ",MB_ICONASTERISK);
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
	if (CheckPower("���ܷ���")) {
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
//8��  ��������
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::salebackExecute(TObject *Sender)
{
	//�����˻�����
    if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
         if (CheckPower("�ͻ��������")) {      //Ȩ�޿���
             li.FormatStr = "1";
         }else li.FormatStr = "0";

		if (CheckPower("�����˻�")) {
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
//���Ӵ���
	//��/���鴦��
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
	if (CheckPower("��/���鴦��") ) {
		Ysbooksale(&li);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::PosretailExecute(TObject *Sender)
{
	//POS���۹���
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("POS����")) {
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
	//�����˻�
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("�����˻�")) {
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
//b2b ����
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::financestartExecute(TObject *Sender)
{
   //  ��λ�����ڳ�
	if (!FindDog()) {
        return;
	}
	if (CheckPower("��Ӧ���ڳ��ʵ�")) {
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
	//��Ӧ����������   0
	if (!FindDog()) {
        return;
	}
	if (CheckPower("��Ӧ����������")) {
		Tfrmwanglaizhang * frm = new Tfrmwanglaizhang(Application,1);      //��Ӧ������
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
	// ��Ӧ�̽׶ν������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("��Ӧ�̽׶ν������")) {
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
	//�������
	if (!FindDog()) {
        return;
	}
	int userid ;
	userid =frmLand->GetUserID();
	if (CheckPower("��Ӧ�̽���")) {
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
//	5��	��Ӧ�̽����ѯ
	if (!FindDog()) {
        return;
	}
	if (CheckPower("��Ӧ�̽����ѯ")) {
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
	//  �ͻ������ڳ�
	if (!FindDog()) {
        return;
	}
	if (CheckPower("�ͻ��ڳ��ʵ�")) {
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
	//�ͻ���������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("�ͻ�ס������")) {
		Tfrmwanglaizhang * frm = new Tfrmwanglaizhang(Application,2);      //�ͻ�����
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
	// �ͻ��׶ν������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("�ͻ��׶ν������")) {
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
	if (CheckPower("�ͻ�����")) {
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
	//���տ�ݽ��
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
	if (CheckPower("���շ�����ݽ���")) {
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
	//ͼ��ƷĿ����
  //	ManageBookCatalog(Application, frmLand->conLand);
        bool add;
        bool del;
        bool mod;
	if (!FindDog()) {
        return;
	}

        //��Ŀ���


	if (CheckPower("ͼ��Ŀ¼����") ) {
           if (CheckPower("��Ŀ���") ) {
              add=true;
              }else add=false;
           if (CheckPower("��Ŀ�޸�") ) {
               mod=true;
              }else  mod=false;
           if (CheckPower("��Ŀɾ��") ) {
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
	//Ŀ¼����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("Ŀ¼����") ) {
		Catalogbuilt(Application, frmLand->conLand);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pressmanageExecute(TObject *Sender)
{
	//���������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("���������")) {
		ManagePress(Application, frmLand->conLand);
	}else
	{
	   ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::breedTypeExecute(TObject *Sender)
{
	//ͼ��������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("ƷĿ������")) {
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
	if (CheckPower("�������")) {
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
	//��Ա����
    if (!FindDog()) {
        return;
	}
	if (CheckPower("��Ա����")) {
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
	//��λ����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("��λ����") ) {
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
	//�����̵�
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.UserName = frmLand->GetUserNameA();
	if (CheckPower("�ֲ��̵�")) {
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
	//����̵�
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
	if (CheckPower("ʵ���̵�")) {
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
	//������
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
	if (CheckPower("��λ����")) {
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
	if (CheckPower("������")) {
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
	//���Ԥ��
	//WarnStock(Application, frmLand->conLand);
	if (!FindDog()) {
        return;
	}
	if (CheckPower("���Ԥ��")) {
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
  //����Ա����
  	if (!FindDog()) {
        return;
	}
	if (CheckPower("����Ա����")) {
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
 //��ɫ����
 	if (!FindDog()) {
        return;
	}
	if (CheckPower("��ɫ����")) {
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
   //Ȩ�޹���
	if (!FindDog()) {
        return;
	}
	if (CheckPower("Ȩ������")) {
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
	//��Ӧ������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("��Ӧ������")) {
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		li.FormatStr = "#,##0.00";
		//1Ϊ��Ӧ��
		TSuppMana * frm = new TSuppMana(Application,1,frmLand->conLand);
	   	//	frm->StgID = li.storageID ;

                if (CheckPower("��Ӧ���������")) {
                   frm->add=1;
                }else  frm->add=0;

                 if (CheckPower("��Ӧ�������޸�")) {
                   frm->modify=1;
                }else frm->modify=0;

                 if (CheckPower("��Ӧ������ɾ��")) {
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
	//�ͻ�����
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	 //1Ϊ��Ӧ��
	  //	TSuppMana * frm = new TSuppMana(Application,2,frmLand->conLand);
	//frm->Show();
	if (CheckPower("�ͻ�����") ) {
	   Tfrmclient *frm = new Tfrmclient(Application,frmLand->conLand,li.storageID);
			  if (CheckPower("�ͻ��������")) {
                   frm->add=1;
                }else  frm->add=0;

                 if (CheckPower("�ͻ������޸�")) {
                   frm->modify=1;
                }else frm->modify=0;

                 if (CheckPower("�ͻ�����ɾ��")) {
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
	if (CheckPower("ҵ��Ա����(����)")) {
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
	if (CheckPower("���ù���")) {
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
  //��Ա����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("��Ա����")) {
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
  //��Ա��ֵ
  	if (!FindDog()) {
        return;
	}
	if (CheckPower("��Ա��ֵ")) {
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
  	//��ֵ��¼��ѯ
	if (!FindDog()) {
        return;
	}
	if (CheckPower("��Ա��ֵ��ѯ")) {
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
	//ҵ���ѯ
	/*TMenuItem* item = dynamic_cast<TMenuItem*>(Sender);
	if (item != NULL)
	{   if (item->Tag == 3) {
			if (CheckPower("����ѯ")) {
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
	if (CheckPower("����ѯ")) {
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
	//������ѯ
	if (!FindDog()) {
		return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("������ѯ")) {
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
	//�ɹ���ѯ
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("�ɹ���ѯ")) {
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
	//����ѯ
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("����ѯ")) {
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
	//������ѯ
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("������ѯ")) {
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
	//���۲�ѯ
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("POS���۲�ѯ")) {
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
	  if (CheckPower("�̵��ѯ")) {
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
			 Disappear(PUIName);        //�ɹ�
			 PUIName = "imagecg";
			 Display("imagecg");
		break;
		case 301:                        //����
			 Disappear(PUIName);
			 PUIName = "imagepx";
			 Display("imagepx");
		break;

		case 302:                        //����
			Disappear(PUIName);
			PUIName = "imagels";
			Display("imagels");
		break;

		case 303:                        //������
			Disappear(PUIName);
			PUIName = "imagekc";
			Display("imagekc");
			StockAlert();
		break;

		case 304:
			Disappear(PUIName);  //����
			PUIName = "imagecf";
			Display("imagecf");
		break;
		case 305:
			Disappear(PUIName);  //Ӫ��
			PUIName = "imageyx";
			Display("imageyx");
		break;
		case 306:
			Disappear(PUIName);  //����
			PUIName = "imagewl";
			Display("imagewl");
		break;
		case 307:
			Disappear(PUIName);  //ҵ���ѯ
			PUIName = "imagesearch";
			Display("imagesearch");
		break;
		case 308:
			Disappear(PUIName);  //ͳ�Ʒ���
			PUIName = "imagetj";
			Display("imagetj");
		break;
		case 309:
			Disappear(PUIName);  //����Эͬ
			PUIName = "imagext";
			Display("imagext");
		break;
		case 400:
			//MessageBoxA(0,"���ð����޴˹���!","��ʾ",MB_ICONASTERISK);
			//return;
			Disappear(PUIName);  //����ͨ
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

		 if (uix >195 && uix < 248 && uiy >15 && uiy < 27) {     //ƷĿ����
			Screen->Cursor =  Controls::crHandPoint ;
		  }else
		  {
			Screen->Cursor =  Controls::crDefault ;
		  }
			  if (uix >278 && uix < 331 && uiy >15 && uiy < 27) {    //������
				Screen->Cursor =  Controls::crHandPoint ;
		 }
		 if (uix >367 && uix < 429 && uiy >15 && uiy < 27) {    //���������
				Screen->Cursor =  Controls::crHandPoint ;
		 }

			  if (uix >461 && uix < 526 && uiy >15 && uiy < 27) {        //��Ӧ������
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >562 && uix < 619 && uiy >15 && uiy < 27) {        //�������
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >648 && uix < 707 && uiy >15 && uiy < 27) {        //��λ����
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >289 && uix < 341 && uiy >165 && uiy < 208) {        //һ��ɹ���
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >463 && uix < 527 && uiy >120 && uiy < 161) {        //һ�����
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >473 && uix < 528 && uiy >233 && uiy < 280) {        //����˻�
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >289 && uix < 342 && uiy >300 && uiy < 340) {        //���ܲɹ�
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >475 && uix < 528 && uiy >354 && uiy < 399) {        //�������
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >661 && uix < 712 && uiy >233 && uiy < 281) {        //��Ӧ�̽׶ν������
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			if (uix >827 && uix < 874 && uiy >234 && uiy < 279) {        //�������
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
		 if (uix >316 && uix < 373 && uiy >75 && uiy < 115) {     //��Ӧ�������ڳ�
			Screen->Cursor =  Controls::crHandPoint ;
		  }else
		  {
			Screen->Cursor =  Controls::crDefault ;
		  }
			  if (uix >446 && uix < 507 && uiy >71 && uiy < 119) {    //Ӧ������
				Screen->Cursor =  Controls::crHandPoint ;
		 }

			  if (uix >317 && uix < 373 && uiy >180 && uiy < 228) {        //��Ӧ����������
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >445 && uix < 505 && uiy >181 && uiy < 321) {        //Ӧ����ϸ
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >646 && uix < 703 && uiy >136 && uiy < 173) {        //��Ӧ�̽���
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >803 && uix < 860 && uiy >141 && uiy < 177) {        //��Ӧ�̽����ѯ
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >312 && uix < 368 && uiy >330 && uiy < 375) {        //�ͻ������ڳ�
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >454 && uix < 502 && uiy >329 && uiy < 375) {        //Ӧ�ջ���
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >311 && uix < 366 && uiy >440 && uiy < 486) {        //�ͻ���������
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >454 && uix < 502 && uiy >444 && uiy < 485) {        //Ӧ����ϸ
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >657 && uix < 703 && uiy >378 && uiy < 420) {        //�ͻ�����
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			if (uix >804 && uix < 855 && uiy >380 && uiy < 422) {        //�ͻ������ѯ
				Screen->Cursor =  Controls::crHandPoint ;
			}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::yihutotalExecute(TObject *Sender)
{
	  //Ӧ������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("Ӧ������")) {
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
   //��Ӧ��Ӧ����ϸ
	if (!FindDog()) {
        return;
	}
	if (CheckPower("Ӧ����ϸ")) {
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
   //Ӧ�ջ���
	if (!FindDog()) {
        return;
	}
   if (CheckPower("Ӧ�ջ���")) {
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
	  //�ͻ�Ӧ����ϸ
	if (!FindDog()) {
		return;
	}
	if (CheckPower("Ӧ����ϸ")) {
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
 //�ͻ������ѯ
 	if (!FindDog()) {
        return;
	}
	if (CheckPower("�ͻ������ѯ")) {
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
//jiaojieban ����Ա���Ӱ�
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
	sql = "insert into sys_log (EventType,SourceFrom,EventDate,EventUser,EventMessage,stgName) values('��Ϣ','����',getdate()," + IntToStr(frmLand->GetUserID()) + ",'����Ա����'," + IntToStr(frmLand->GetStorageID()) + ")" ;

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
		 if (uix >304 && uix < 358 && uiy >144 && uiy < 192) {     //����������
			Screen->Cursor =  Controls::crHandPoint ;
		  }else
		  {
			Screen->Cursor =  Controls::crDefault  ;
		  }
			  if (uix >459 && uix < 520 && uiy >153 && uiy < 200) {    //���۹��������
				Screen->Cursor =  Controls::crHandPoint ;
		 }

			  if (uix >618 && uix < 679 && uiy >154 && uiy < 195) {        //��Ա���͵�Ʒ����
			  Screen->Cursor =  Controls::crHandPoint ;
		  }

			  if (uix >775 && uix < 819 && uiy >157 && uiy < 192) {        //��Ա���ֹ���
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >314 && uix < 364 && uiy >334 && uiy < 381) {        //������Ʒ�ۿ�
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >462 && uix < 522 && uiy >339 && uiy < 384) {        //���������ۿ�
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
				  if (uix >618 && uix < 682 && uiy >338 && uiy < 387) {        //�����ֳ�����
			  Screen->Cursor =  Controls::crHandPoint ;
		  }
			  if (uix >770 && uix < 837 && uiy >335 && uiy < 386) {        //������ȷ���
			  Screen->Cursor =  Controls::crHandPoint ;
		  }


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::retailandbackExecute(TObject *Sender)
{
	//�������˻�
	if (!FindDog()) {
        return;
	}
	if (CheckPower("�������˻�")) {
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
	  //�������˻�
	if (!FindDog()) {
        return;
	}
	  if (CheckPower("�������˻�")) {
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
  //����ʱ�λ���ͳ��
	if (!FindDog()) {
        return;
	}
   if (CheckPower("����ʱ�λ���ͳ��")) {
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
   //������
	if (!FindDog()) {
        return;
	}
   if (CheckPower("δ��������")) {
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
   //ҵ��������
	if (!FindDog()) {
        return;
	}
   if (CheckPower("ҵ�����а�")) {
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
	 //����ͳ�Ʊ���
	if (!FindDog()) {
        return;
	}
	 if (CheckPower("����ͳ�Ʊ���")) {
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
	//���������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("���������")) {
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
	//������������ë������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("������������ë������")) {
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
	//���ۻ��ܷ���
	if (!FindDog()) {
        return;
	}
	if (CheckPower("���ۻ��ܷ���")) {
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


	  if (uix >324 && uix < 385 && uiy >164 && uiy < 214) {          //����ѯ
			  Screen->Cursor =  Controls::crHandPoint ;

		  }else
		  {
			 Screen->Cursor =  Controls::crDefault  ;
		  }
		  if (uix >480 && uix < 541 && uiy >165 && uiy < 217) {      //������ѯ
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >642 && uix < 699 && uiy >170 && uiy < 213) {          //�ɹ���ѯ
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >784 && uix < 850 && uiy >172 && uiy < 217) {          //����ѯ
			   Screen->Cursor =  Controls::crHandPoint ;

		  }

		  if (uix >323 && uix < 386 && uiy >330 && uiy < 381) {          //������ѯ
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >473 && uix < 543 && uiy >327 && uiy < 377) {          //POS���۲�ѯ
			   Screen->Cursor =  Controls::crHandPoint ;

		  }

		  if (uix >634 && uix < 707 && uiy >325 && uiy < 384) {          //�̵��ѯ
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >776 && uix < 851 && uiy >332 && uiy < 377) {          //���Ͳ�ѯ
			   Screen->Cursor =  Controls::crHandPoint ;

		  }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagextMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
		 uix = X;
	 uiy = Y;

			  if (uix >350 && uix < 407 && uiy >239 && uiy < 296) {          //�������
			   Screen->Cursor =  Controls::crHandPoint ;

		  }else
		  {
			Screen->Cursor =  Controls::crDefault  ;
		  }

		  if (uix >516 && uix < 576 && uiy >243 && uiy < 294) {          //�ĵ�����
			   Screen->Cursor =  Controls::crHandPoint ;

		  }
		  if (uix >689 && uix < 741 && uiy >245	&& uiy < 307) {          //���߽���
			   Screen->Cursor =  Controls::crHandPoint ;

		  }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::renwuExecute(TObject *Sender)
{
	//�������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("�������")) {
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
//�ĵ�
	if (!FindDog()) {
        return;
	}
	MessageBoxA(0,"�˹���Ϊ��ǿ������!","��ʾ",MB_ICONASTERISK);
	return;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::jiaoliuExecute(TObject *Sender)
{
//����
	if (!FindDog()) {
        return;
	}
	MessageBoxA(0,"�˹���Ϊ��ǿ������!","��ʾ",MB_ICONASTERISK);
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
							MessageBox(0,"Ϊ�˱�֤�����������ʵ��Ч��\nһ���û�ͬʱֻ�����һ���������ͻ���������ģ�飡","��ʾ" ,MB_OK|MB_ICONASTERISK);
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
	//�û��ֲ�
	AnsiString path;
	path =  ExtractFilePath(Application->ExeName);
	path = path + "help.doc";
	ShellExecute(NULL,"open",path.c_str() ,"","",SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::systemupdateExecute(TObject *Sender)
{
	//ϵͳ����
	Tfrmshengji * frm = new Tfrmshengji(Application);
	frm->ShowModal();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::aboutExecute(TObject *Sender)
{
	//���ڱ����
	TfrmAboutsoftware *frm = new TfrmAboutsoftware(Application);
	frm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::specialPassWordExecute(TObject *Sender)
{
   //�������
    if (!FindDog()) {
        return;
	}
    LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("�������")) {
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
	//������ʾ����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("������ʾ����")) {
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
				MessageBoxA(0,"�����������!","��ʾ",MB_ICONASTERISK);
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
//B2B�ӿ�����
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::logSearchExecute(TObject *Sender)
{
//��־��ѯ
	//MessageBoxA(0,"���ð治�ṩ�˹���!","��ʾ",MB_ICONASTERISK);
	  //	return;
	if (!FindDog()) {
        return;
	}
	if (CheckPower("��־��ѯ")) {
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
   //���ݱ���
	if (!FindDog()) {
        return;
	}
	if (CheckPower("���ݱ���")) {
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
//���ݻָ�
	if (!FindDog()) {
        return;
	}
	if (CheckPower("���ݻָ�")) {
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
	//����ҵ�����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("����ҵ�����")) {
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
	//�ɹ�ҵ�����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("�ɹ�ҵ�����")) {
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
	//���ҵ�����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("���ҵ�����")) {
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
	//����ҵ�����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("����ҵ�����")) {
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
	//����ҵ�����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("����ҵ�����")) {
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
		//����ҵ�����
	if (!FindDog()) {
        return;
	}
		if (CheckPower("����ҵ�����")) {
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
	//��Ӧ�����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("��Ӧ�̷���")) {
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
	//�ͻ����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("�ͻ�����")) {
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
	//�������
   //	MessageBoxA(0,"���ð治�ṩ�˹���!","��ʾ",MB_ICONASTERISK);
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
	if (CheckPower("�������")) {
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

	//��������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("��������")) {
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
					MessageBox(0,"Ϊ�˱�֤�����������ʵ��Ч��\nһ���û�ͬʱֻ�����һ���������ͻ���������ģ�飡","��ʾ" ,MB_OK|MB_ICONASTERISK);
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

		if (((TMenuItem*)Sender)->Tag ==1)   //��������
		{
			DiaoBo(&li,1,"");
		}else if (((TMenuItem*)Sender)->Tag ==0) {
			DiaoBo(&li,0,"");
		}else if (((TMenuItem*)Sender)->Tag ==2) {    //���͵�����

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
	//���Ͳ�ѯ
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("���Ͳ�ѯ")) {
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
	//�ҵĹ���ƽ̨
	TfrmMyWork * frm = new TfrmMyWork(Application,frmLand->conLand ,frmLand->GetUserID());
	if (frm->ShowModal() == mrOk ) {
		//LoadMyWork(frmLand->GetUserID());
	}
	//frm->Show();
	//LoadMyWork(frmLand->GetUserID());
	/*if (CheckPower("�ҵĹ���ƽ̨")) {
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
	//�ͻ��Ƚ�
    if (!FindDog()) {
        return;
	}
	if (CheckPower("�ͻ��Ƚ�")) {
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
	//��Ӧ��
    if (!FindDog()) {
        return;
	}
	if (CheckPower("��Ӧ�̱Ƚ�")) {
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
	//���۴�ӡ
	if (!FindDog()) {
        return;
	}
	if (CheckPower("���۴�ӡ")) {
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
	//ͳ�Ʊ���
    if (!FindDog()) {
        return;
	}
	if (CheckPower("ͳ�Ʊ���")) {
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
	//������ʾ����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("������ѡ�����")) {
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
	//���ս���
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
	if (CheckPower("���۽��˲�ѯ")) {
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
	//������Ƚ�
    if (!FindDog()) {
        return;
	}
	if (CheckPower("������Ƚ�")) {
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
	//��������
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
		li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID() ;
    if (CheckPower("C������") ) {
		COrder(&li);
	}else
	{
		ShowNoPower();
	}    // */
  //	MessageBox(0,"�˹��ܽ��B2B���϶���ϵͳһ��ʹ�ã�","��ʾ",MB_ICONASTERISK|MB_OK);
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
	if (CheckPower("�ͻ�����") ) {
		BIOrderManage(&li,2);
	}else
	{
		ShowNoPower();
	}     */
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::catalogneworrecExecute(TObject *Sender)
{
	//�¼���Ŀ
	if (!FindDog()) {
        return;
	}
	if (CheckPower("�¼���Ŀ") ) {
		Catalogneworrec(Application, frmLand->conLand);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::OrdershenheiExecute(TObject *Sender)
{
	//�������
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
	if (CheckPower("�������") ) {
		OrdereShenhei(&li);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::CaigouOrderExecute(TObject *Sender)
{
	//���ܲɹ�
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
	if (CheckPower("���ܲɹ�") ) {
		CaigoufromOrder(&li);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::bookfenfaExecute(TObject *Sender)
{
	//�����ַ�
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
	if (CheckPower("�����ַ�") ) {
		daohuofenfa(&li);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::fahuorateExecute(TObject *Sender)
{
	//������������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("������������") ) {
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
	//������������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("������������") ) {
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

		if (uix >405 && uix < 485 && uiy >119 && uiy < 151) {     //δ������������
		Screen->Cursor =  Controls::crHandPoint ;
		}else
		{
		Screen->Cursor =  Controls::crDefault ;
		}
		if (uix >661 && uix < 736 && uiy >111 && uiy < 173) {          //δ������������
			Screen->Cursor =  Controls::crHandPoint ;
		}
		  if (uix >407 && uix < 484 && uiy >239 && uiy < 288) {          //�������ʷ���
			Screen->Cursor =  Controls::crHandPoint ;

		}
		  if (uix >662 && uix < 733 && uiy >239 && uiy < 280) {          //�������ʷ���
		   Screen->Cursor =  Controls::crHandPoint ;
		}
		  if (uix >407 && uix < 477 && uiy >371 && uiy < 410) {          //����ͬ�ڱȽ�
			Screen->Cursor =  Controls::crHandPoint ;

		}
		  if (uix >668 && uix < 740 && uiy >372 && uiy < 416) {          //����ͬ�ڱȽ�
		 Screen->Cursor =  Controls::crHandPoint ;

		}

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::caigoutixingExecute(TObject *Sender)
{
	//����δ��������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("����δ��������") ) {
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
	//����δ��������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("����δ��������") ) {
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
	//ѯ��
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
	if (CheckPower("����ѯ��") ) {
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
	if (CheckPower("��Ʒ����") ) {
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
	//����ַ�
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
	if (CheckPower("����ַ�") ) {
		siglefenfa(&li);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::saletongqiExecute(TObject *Sender)
{
	//����ͬ�ڱȽ�
	if (!FindDog()) {
        return;
	}
	if (CheckPower("����ͬ�ڱȽ�") ) {
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
	//����ͬ�ڱȽ�
	if (!FindDog()) {
        return;
	}
	if (CheckPower("����ͬ�ڱȽ�") ) {
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
	//�ڿ�����
	if (!FindDog()) {
        return;
	}
	if (CheckPower("�ڿ�Ŀ¼����") ) {
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
		MessageBoxA(0,"ֻ���ܵ������Ա���ܽ��и������ã�","��ʾ",MB_ICONWARNING);
		return;
	}
	if (CheckPower("���껥��Ȩ�޹���")) {
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
	if (CheckPower("Ԥ���ۿ۹���")) {
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
	if (CheckPower("��Ա������Ԥ���ۿ�")) {
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
	//����ҵ�����
	if (!FindDog()) {
		return;
	}
	if (CheckPower("���Ԥ������")) {
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
	//����ϲ�
	if (!FindDog()) {
		return;
	}
	if (CheckPower("����ϲ�")) {
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
	//����̧ͷ
	if (!FindDog()) {
		return;
	}
	if (CheckPower("��ӡ��Ϣ����")) {
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
							MessageBox(0,"Ϊ�˱�֤�����������ʵ��Ч��\nһ���û�ͬʱֻ�����һ���������ͻ���������ģ�飡","��ʾ" ,MB_OK|MB_ICONASTERISK);
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
	//��������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("��������")) {
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
					MessageBox(0,"Ϊ�˱�֤�����������ʵ��Ч��\nһ���û�ͬʱֻ�����һ���������ͻ���������ģ�飡","��ʾ" ,MB_OK|MB_ICONASTERISK);
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
	//ҵ��ͳ��
	if (!FindDog()) {
		return;
	}
	if (CheckPower("ҵ��ͳ��")) {
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
	//����������
	if (!FindDog()) {
        return;
	}
	if (CheckPower("����������")) {
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
	//��������
    /*if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
		li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID() ;
	if (CheckPower("�ͻ�����") ) {
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
	if (CheckPower("�������")) {
		if (MessageBoxA(0,"ȷ��Ҫ���¼����棿","��ʾ",MB_ICONQUESTION|MB_OKCANCEL)==1)
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
			MessageBox(0,"��������¼��㣡","��ʾ" ,MB_OK|MB_ICONASTERISK);
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
	if (CheckPower("�ϲ���Ӧ��")) {
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
	if (CheckPower("����ɱ�")) {
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
	//����ʾ������
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
	//������������ȷ��
	if (!FindDog()) {
		return;
	}

	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID() ;
	if (CheckPower("������������ȷ��") ) {
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
                }                  //CheckPower("����ɱ�")
        	if (CheckPower("ҵ����������")) {
                   Tfrmbslock * frm = new Tfrmbslock(Application,frmLand->conLand,frmLand->GetStorageID());
                    frm->Show();
                }else ShowNoPower();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N85Click(TObject *Sender)
{
            if (!FindDog()) {
                return;
            }                  //CheckPower("����ɱ�")
            if (CheckPower("��λ��������")) {
                Tfrmlock * frm = new Tfrmlock(Application,frmLand->conLand,frmLand->GetStorageID());
                frm->Show();
            }else ShowNoPower();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N87Click(TObject *Sender)
{
            if (!FindDog()) {
               return;
            }                  //CheckPower("����ɱ�")
            if (CheckPower("����ת��ѯ")) {
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
            }                  //CheckPower("����ɱ�")
            if (CheckPower("����ת")) {
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
   //	B��������ѯ
   OrderSearch->Execute()  ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::C1Click(TObject *Sender)
{
//  C��������ѯ
	//������ѯ
	if (!FindDog()) {
		return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	//if (CheckPower("������ѯ")) {
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
   //	if (CheckPower("������������ȷ��") ) {
		COrderLock(&li);
   //	}else
   //	{
   //		ShowNoPower();
  //	}
}
//---------------------------------------------------------------------------

