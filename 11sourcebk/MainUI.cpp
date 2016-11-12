//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUI.h"
#include "math.h"
#include "Main.h"
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
#include "shlwapi.h"
#include "storagelocal.h"
#include "StockCheck.h"
#include "Stockalarm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmUI *frmUI;
TStringList *PanelList;
//---------------------------------------------------------------------------
__fastcall TfrmUI::TfrmUI(TComponent* Owner)
	: TForm(Owner)
{
}
void __fastcall TfrmUI::CreateParams(Controls::TCreateParams & Params)
{
	 TCustomForm::CreateParams(Params);
	 Params.Style^= WS_CAPTION;

}
//---------------------------------------------------------------------------
void __fastcall TfrmUI::pcDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect,
          bool Active)
{
Byte Red0,Red1,Green0,Green1,Blue0,Blue1;

		  /*
Control->Canvas->TextOut( Rect.Left +offset + (Rect.Right - Rect.Left - Control->Canvas->TextWidth(str)) / 2,

							Rect.Top + (Rect.Bottom - Rect.Top - Control->Canvas->TextHeight(str)) / 2,

							str);
									*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmUI::pcChange(TObject *Sender)
{
	  /*	Graphics::TBitmap *bmp = (Graphics::TBitmap *)ImageList->Items[pc->ActivePageIndex];

	 TControlCanvas * pcon;
	  pcon = new TControlCanvas();
	  pcon->Control  = pc->ActivePage  ;

	 pcon->Draw(0,0,bmp);

	  delete pcon;   */
}
//---------------------------------------------------------------------------
void __fastcall TfrmUI::FormCreate(TObject *Sender)
{
	/* int i ;

   ImageList = new TList();
	for (i = 0; i < 4; i++) {
	   Graphics::TBitmap * bmp = new Graphics::TBitmap;
		bmp->LoadFromFile("c:\\temp\\" + IntToStr(i)+".bmp");
		ImageList->Add(bmp);


	}

		  */

	
}
//---------------------------------------------------------------------------
void __fastcall TfrmUI::FormResize(TObject *Sender)
{
		/* TControlCanvas * pcon;
	  pcon = new TControlCanvas();
	  pcon->Control  = pc->ActivePage  ;
	 Graphics::TBitmap *bmp = (Graphics::TBitmap *)ImageList->Items[0];
	 pcon->Draw(0,0,bmp);

	  delete pcon;  */
}
//---------------------------------------------------------------------------
void __fastcall TfrmUI::FormPaint(TObject *Sender)
{
	/* TControlCanvas * pcon;
	  pcon = new TControlCanvas();
	  pcon->Control  = pc->ActivePage  ;
	 Graphics::TBitmap *bmp = (Graphics::TBitmap *)ImageList->Items[0];
	 pcon->Draw(0,0,bmp);

	  delete pcon; */
}
//---------------------------------------------------------------------------



void __fastcall TfrmUI::sbsaleMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
  TSpeedButton * sp;
  sp = (TSpeedButton *)Sender;
  sp->Cursor = crHandPoint ;


}
//---------------------------------------------------------------------------
void TfrmUI::LoadPUI()
{
		PanelList = new TStringList();


		for   (int   i=0; i < frmUI->ComponentCount-1 ; i++)
	   {
		 TImage*   temp = dynamic_cast<TImage*>(Components[i]);
		 if (temp != NULL) {
		   if (temp->Tag >= 100) {
		   if (temp->Name != "imageui") {
			 temp->Visible = false;
			 temp->Align = TAlign::alClient ;
		   }

		   PanelList->AddObject(temp->Name , temp);

		 }
		 }

	   }



}
void TfrmUI::Display(AnsiString PUIName)
{
  int j,i;
  j = PanelList->IndexOf(PUIName);    //取出要显示的panel

  for (i = 0; i < PanelList->Count; i++) {      //设置要显示的panel visible为true

	 TImage * pvisable = (TImage *)PanelList->Objects[i];
	 if (i==j) {
		 pvisable->Visible = True;
		// pvisable->Align = TAlign::alClient ;
	 } else
	 {

		 pvisable->Visible = false;


	 }

  }



  }


void __fastcall TfrmUI::FormShow(TObject *Sender)
{
      LoadPUI();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::spsalemanClick(TObject *Sender)
{
		Display("psale");
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::spstoreClick(TObject *Sender)
{

	Display("Pstorage");
	Tfrmalarm *frm = new Tfrmalarm(Application);
	frm->aquery->Connection = frmLand->conLand ;
	frm->aquery->Close();
	frm->aquery->Open();
	if (frm->aquery->RecordCount > 0) {
    	frm->Show();
	}else
	{
	delete frm;
	}


}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::sbpsaleClick(TObject *Sender)
{
	//批销管理
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	ManageMarketing(&li);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::sbsaleClick(TObject *Sender)
{
	//POS零售管理
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	ManageRetail(&li);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::sbjiezhangClick(TObject *Sender)
{
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	CheckQuery(&li);
}
//---------------------------------------------------------------------------


void __fastcall TfrmUI::spinputClick(TObject *Sender)
{
 	//入库管理
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	ManageStorage(&li);
}
//---------------------------------------------------------------------------


void __fastcall TfrmUI::sppandianClick(TObject *Sender)
{
	LandInfo li;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.storageID = 0;
	Tfrmcheckstock *frm = new Tfrmcheckstock(Application,frmLand->conLand,&li);
  //	frm->Visible = false;
	frm->Show();
  //	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::sbClick(TObject *Sender)
{
    LandInfo li;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.storageID = 0;
	Tfrmadjust *frm = new Tfrmadjust(Application,frmLand->conLand,&li);
	frm->Show();

}
//---------------------------------------------------------------------------







void __fastcall TfrmUI::sbbuymanageClick(TObject *Sender)
{
Display("pbuy");
}
//---------------------------------------------------------------------------


void __fastcall TfrmUI::SpeedButton8Click(TObject *Sender)
{
frmMain->N21->Click();//品目管理
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton9Click(TObject *Sender)
{
   frmMain->N20->Click();//图书类型管理
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton10Click(TObject *Sender)
{
frmMain->N19->Click();//版别管理
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton11Click(TObject *Sender)
{
	   frmMain->N32->Click(); //库位管理
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton12Click(TObject *Sender)
{
frmMain->N2->Click();  //供应商管理
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton13Click(TObject *Sender)
{
frmMain->N71->Click(); //区域管理
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton15Click(TObject *Sender)
{
 	//入库管理
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	ManageStorage(&li);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton16Click(TObject *Sender)
{
   frmMain->N55->Click(); //供应商阶段结算分析
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton17Click(TObject *Sender)
{
  frmMain->N39->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton14Click(TObject *Sender)
{
   frmMain->mniN49->Click();//入库查询
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton18Click(TObject *Sender)
{
frmMain->N32->Click();//库位管理
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton19Click(TObject *Sender)
{
 frmMain->N33->Click();//库存预警
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton2Click(TObject *Sender)
{
  frmMain->N30->Click();//盘点
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton20Click(TObject *Sender)
{
	frmMain->N31->Click();//库位调整
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton22Click(TObject *Sender)
{
	frmMain->N3->Click();//客户管理
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton23Click(TObject *Sender)
{
   frmMain->N71->Click();//区哉管理
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton24Click(TObject *Sender)
{
    frmMain->N11->Click();//业务控制
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton25Click(TObject *Sender)
{
 frmMain->mniN50->Click();//批销业务查询
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton27Click(TObject *Sender)
{
  frmMain->N44->Click();//收款结算
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton26Click(TObject *Sender)
{
	frmMain->N23->Click();//会员信息
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton28Click(TObject *Sender)
{
	 frmMain->N24->Click();//会员类型
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton29Click(TObject *Sender)
{
	 frmMain->N72->Click();//充值查询
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton30Click(TObject *Sender)
{
   frmMain->N26->Click();//折扣控件
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton31Click(TObject *Sender)
{
 frmMain->mniN51->Click();//零售查询
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton32Click(TObject *Sender)
{
   frmMain->N53->Click();//零售查询
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton3Click(TObject *Sender)
{
    Display("pwanglai");
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton33Click(TObject *Sender)
{
   frmMain->N38->Click();//供应商往来期初
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton34Click(TObject *Sender)
{
	frmMain->N43->Click();//客户往来期初
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton35Click(TObject *Sender)
{
   frmMain->N40->Click();//应付回总
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton38Click(TObject *Sender)
{
frmMain->N41->Click();//应付明细
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton36Click(TObject *Sender)
{
   frmMain->N39->Click();//付款结算
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton37Click(TObject *Sender)
{   frmMain->N42->Click();//付款单查询

}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton40Click(TObject *Sender)
{
	  frmMain->N44->Click();//收款结算
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton39Click(TObject *Sender)
{
	  frmMain->N45->Click();//应收回总
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton41Click(TObject *Sender)
{
	  frmMain->N46->Click();//应收明细
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton42Click(TObject *Sender)
{
   frmMain->N47->Click();//收款单查询
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton7Click(TObject *Sender)
{
  Display("ptongji");
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton46Click(TObject *Sender)
{
  frmMain->N49->Click();//销售统计报表
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton44Click(TObject *Sender)
{
	frmMain->N61->Click();//业务排行榜
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton47Click(TObject *Sender)
{
  frmMain->stock->Click();//库存分析
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton49Click(TObject *Sender)
{
	frmMain->N62->Click();//零售与退货
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton48Click(TObject *Sender)
{
    frmMain->N63->Click();//批销与退货
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton43Click(TObject *Sender)
{
frmMain->N64->Click();////销售时段汇总统计
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::SpeedButton6Click(TObject *Sender)
{
Display("Pstorage");
}
//---------------------------------------------------------------------------


void __fastcall TfrmUI::SpeedButton5Click(TObject *Sender)
{
Display("pbssale");
}
//---------------------------------------------------------------------------




void __fastcall TfrmUI::imageuiMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	 Label1->Caption = IntToStr(X);
	 uix = X;
	 uiy = Y;
	 Label2->Caption = IntToStr(Y);

	   if (uix >208 && uix < 271 && uiy >13 && uiy < 32) {     //库位管理
				Screen->Cursor =  crHandPoint ;
		  }else
		  {
			Screen->Cursor =  crDefault  ;
		  }
			  if (uix >486 && uix < 530 && uiy >246 && uiy < 324) {    //库存盘点
				Screen->Cursor =  crHandPoint ;
		 }

			  if (uix >322 && uix < 366 && uiy >181 && uiy < 236) {        //库位调整
			  Screen->Cursor =  crHandPoint ;
		  }

			  if (uix >204 && uix < 267 && uiy >571 && uiy < 589) {        //盘点查询
			  Screen->Cursor =  crHandPoint ;
		  }
			  if (uix >321 && uix < 395 && uiy >571 && uiy < 589) {        //库存预警查询
			  Screen->Cursor =  crHandPoint ;
		  }


}
								   //---------------------------------------------------------------------------


void __fastcall TfrmUI::imageuiClick(TObject *Sender)
{
	  Screen->Cursor =  crDefault  ;
	  if (uix > 6 && uix < 154 ) {
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

	}
   //}
	  if (((TImage*)(Sender))->Name == "imagecg") {

		  if (uix >451 && uix < 489 && uiy >242 && uiy < 293) {     //入库单

			 frmMain->N29->Click();
		  }
			  if (uix >609 && uix < 653 && uiy >260 && uiy < 320) {    //供商阶段分析
			  frmMain->N55->Click();

		  }

			  if (uix >761 && uix < 822 && uiy >244 && uiy < 310) {        //付款结算
			  frmMain->N39->Click();

		  }

			   if (uix >202 && uix < 264 && uiy >15 && uiy < 29) {        //品目管理
			  frmMain->N21->Click();

		  }

			  if (uix >284 && uix < 345 && uiy >15 && uiy < 29) {        //类别管理
			  frmMain->N20->Click();

		  }

			  if (uix >368 && uix <447 && uiy >15 && uiy < 29) {         //供应商
			  frmMain->N2->Click();

		  }

			  if (uix >473 && uix < 532 && uiy >15 && uiy < 29) {          //区域
			  frmMain->N71->Click();

		  }

			if (uix >319 && uix < 381 && uiy >593 && uiy < 605) {          //入库查询
			  frmMain->mniN49->Click();

		  }

			if (uix >646 && uix < 710 && uiy >15 && uiy < 29) {          //库位
			frmMain->N32->Click();

		  }
			  if (uix >556 && uix < 619 && uiy >15 && uiy < 29) {          //版别
			  frmMain->N19->Click();

		  }

	  }
   if (((TImage*)(Sender))->Name == "imagetj") {
			Screen->Cursor =  crDefault  ;
	  if (uix >479 && uix < 539 && uiy >126 && uiy < 200) {          //业务排行榜
			  frmMain->N61->Click();

		  }
		  if (uix >342 && uix < 395 && uiy >188 && uiy < 266) {          //销售统计
			  frmMain->N49->Click();

		  }


		  if (uix >324 && uix < 384 && uiy >331 && uiy < 390) {          //销售时段汇总统计
			  frmMain->N64->Click();

		  }
		  if (uix >479 && uix < 536 && uiy >420 && uiy < 477) {          //批销与退货
			  frmMain->N63->Click();

		  }
		  if (uix >630 && uix < 679 && uiy >350 && uiy < 406) {          //零售与退货
			  frmMain->N62->Click();

		  }
			  if (uix >624 && uix < 676 && uiy >193 && uiy < 248) {          //库存分析X
			  frmMain->stock->Click();

		  }
	 }
	 if (((TImage*)(Sender))->Name == "imagewl") {
	   Screen->Cursor =  crDefault  ;
	   if (uix >275 && uix < 332 && uiy >88 && uiy < 160) {          //供应商往来期初
			  frmMain->N38->Click();

		  }
		  if (uix >278 && uix < 328 && uiy >176 && uiy < 248) {          //应付汇总
			   frmMain->N40->Click();

		  }


		  if (uix >276 && uix < 329 && uiy >266 && uiy < 345) {          //应付明细
				frmMain->N41->Click();

		  }
		  if (uix >437 && uix < 497 && uiy >173 && uiy < 241) {          //付款结算
			   frmMain->N39->Click();

		  }
		  if (uix >577 && uix < 627 && uiy >177 && uiy < 239) {          //付款查询
			 frmMain->N42->Click();

		  }
			  if (uix >517 && uix < 571 && uiy >305 && uiy < 361) {          //客户往来期初
			  frmMain->N43->Click();

		  }
			  if (uix >519 && uix < 570 && uiy >394 && uiy < 448) {          //应收汇总
				frmMain->N45->Click();

		  }
				  if (uix >516 && uix < 575 && uiy >486 && uiy < 562) {          //应收明细
					  frmMain->N46->Click();

		  }
				  if (uix >676 && uix < 732 && uiy >392 && uiy < 469) {          //收款结算
			  frmMain->N44->Click();

		  }

				  if (uix >815 && uix < 865 && uiy >396 && uiy < 472) {          //收款查询
			   frmMain->N47->Click();

		  }
	   }
	 if (((TImage*)(Sender))->Name == "imagels") {
	  Screen->Cursor =  crDefault  ;
    	if (uix >207 && uix < 299 && uiy >15 && uiy < 30) {          //会员信息
	 frmMain->N23->Click();

	}
		if (uix >319 && uix < 387 && uiy >16 && uiy < 30) {          //会员类型
		 frmMain->N24->Click();

	}
		if (uix >436 && uix < 532 && uiy >16 && uiy < 30) {          //零售促销方案
		 frmMain->N27->Click();

	}
		if (uix >341 && uix < 403 && uiy >159 && uiy < 247) {          //pos 零售
		   frmMain->sss1Click(NULL);

			}
		if (uix >538 && uix < 588 && uiy >164 && uiy < 223) {          //当日结账统计
		frmMain->N58->Click();

	}

		if (uix >219 && uix < 281 && uiy >569 && uiy < 587) {          //零售查询
			frmMain->mniN51->Click();

	}
			if (uix >374 && uix < 531 && uiy >577 && uiy < 593) {          //销书排
			frmMain->N53->Click();

	}
		if (uix > 219 && uix < 339 && uiy > 609 && uiy < 626) {       //会员充值记录查询
          frmMain->N72->Click();

		}
		if (uix > 555 && uix < 619 && uiy > 14 && uiy < 31) {      //会员充值
          frmMain->N66->Click();
		}

   }
	   if (((TImage*)(Sender))->Name == "imagekc") {
   	   if (uix >208 && uix < 271 && uiy >13 && uiy < 32) {     //库位管理
				frmMain->N32->Click();
		  }
			  if (uix >486 && uix < 530 && uiy >246 && uiy < 324) {    //库存盘点
					frmMain->N30->Click();
		 }

			  if (uix >322 && uix < 366 && uiy >181 && uiy < 236) {        //库位调整
			  frmMain->N31->Click();
		  }

			  if (uix >204 && uix < 267 && uiy >571 && uiy < 589) {        //盘点查询
			   frmMain->N65->Click();
		  }
			  if (uix >321 && uix < 395 && uiy >571 && uiy < 589) {        //库存预警查询
			 frmMain->N33->Click();
		  }
		}

		   if (((TImage*)(Sender))->Name == "imagepx") {
			if (uix >208 && uix < 273 && uiy >18 && uiy < 30) {          //客户管理
		frmMain->N3->Click();

	}
		if (uix >324 && uix < 390 && uiy >18 && uiy < 30) {          //区哉管理
		frmMain->N71->Click();

	}
		if (uix >601 && uix < 660 && uiy >240 && uiy < 299) {          //客户结算分析
		Screen->Cursor =  crHandPoint ;

	}
		if (uix >769 && uix < 831 && uiy >241 && uiy < 305) {          //收款结算
			frmMain->N44->Click();


	}
		if (uix >415 && uix < 471 && uiy >147 && uiy < 202) {          //一般发货
		frmMain->N14->Click();
	}
	if (uix >355 && uix < 420 && uiy >577 && uiy < 596) {          //批销查询
		frmMain->mniN50->Click();

	}
		if (uix >428 && uix < 521 && uiy >15 && uiy < 31) {          //批销业务控制
		 frmMain->N11->Click();

	}

   }
}
//---------------------------------------------------------------------------


void __fastcall TfrmUI::imagetjMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	 uix = X;
	 uiy = Y;
	   if (((TImage*)(Sender))->Name == "imagetj") {

	  if (uix >479 && uix < 539 && uiy >126 && uiy < 200) {          //业务排行榜
			  Screen->Cursor =  crHandPoint ;

		  }else
		  {
			 Screen->Cursor =  crDefault  ;
		  }
		  if (uix >342 && uix < 395 && uiy >188 && uiy < 266) {          //销售统计
			   Screen->Cursor =  crHandPoint ;

		  }


		  if (uix >324 && uix < 384 && uiy >331 && uiy < 390) {          //销售时段汇总统计
				Screen->Cursor =  crHandPoint ;

		  }
		  if (uix >479 && uix < 536 && uiy >420 && uiy < 477) {          //批销与退货
			   Screen->Cursor =  crHandPoint ;

		  }
		  if (uix >630 && uix < 679 && uiy >350 && uiy < 406) {          //零售与退货
			  Screen->Cursor =  crHandPoint ;

		  }
			  if (uix >624 && uix < 676 && uiy >193 && uiy < 248) {          //库存分析X
			   Screen->Cursor =  crHandPoint ;

		  }
	 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::imagewlMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	 uix = X;
	 uiy = Y;


	  if (uix >275 && uix < 332 && uiy >88 && uiy < 160) {          //供应商往来期初
			  Screen->Cursor =  crHandPoint ;

		  }else
		  {
			 Screen->Cursor =  crDefault  ;
		  }
		  if (uix >278 && uix < 328 && uiy >176 && uiy < 248) {          //应付汇总
			   Screen->Cursor =  crHandPoint ;

		  }


		  if (uix >276 && uix < 329 && uiy >266 && uiy < 345) {          //应付明细
				Screen->Cursor =  crHandPoint ;

		  }
		  if (uix >437 && uix < 497 && uiy >173 && uiy < 241) {          //付款结算
			   Screen->Cursor =  crHandPoint ;

		  }
		  if (uix >577 && uix < 627 && uiy >177 && uiy < 239) {          //付款查询
			  Screen->Cursor =  crHandPoint ;

		  }
			  if (uix >517 && uix < 571 && uiy >305 && uiy < 361) {          //客户往来期初
			   Screen->Cursor =  crHandPoint ;

		  }
			  if (uix >519 && uix < 570 && uiy >394 && uiy < 448) {          //应付汇总
			   Screen->Cursor =  crHandPoint ;

		  }
				  if (uix >516 && uix < 575 && uiy >486 && uiy < 562) {          //应付明细
			   Screen->Cursor =  crHandPoint ;

		  }
				  if (uix >676 && uix < 732 && uiy >392 && uiy < 469) {          //收款结算
			   Screen->Cursor =  crHandPoint ;

		  }

				  if (uix >815 && uix < 865 && uiy >396 && uiy < 472) {          //收款查询
			   Screen->Cursor =  crHandPoint ;

		  }

}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::imagelsMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	uix = X;
	uiy = Y;
		 Label1 ->Caption = IntToStr(uix);
	 Label2->Caption = IntToStr(uiy);
	if (uix >207 && uix < 299 && uiy >15 && uiy < 30) {          //会员信息
		Screen->Cursor =  crHandPoint ;

	}else
	{
	  Screen->Cursor = crDefault ;
	}
		if (uix >319 && uix < 387 && uiy >16 && uiy < 30) {          //会员类型
		Screen->Cursor =  crHandPoint ;

	}
		if (uix >436 && uix < 532 && uiy >16 && uiy < 30) {          //零售促销方案
		Screen->Cursor =  crHandPoint ;

	}
		if (uix >341 && uix < 403 && uiy >159 && uiy < 247) {          //pos 零售
		Screen->Cursor =  crHandPoint ;

	}
		if (uix >538 && uix < 588 && uiy >164 && uiy < 223) {          //当日结账统计
		Screen->Cursor =  crHandPoint ;

	}
		if (uix >219 && uix < 281 && uiy >569 && uiy < 587) {          //零售查询
		Screen->Cursor =  crHandPoint ;

	}
		if (uix >374 && uix < 531 && uiy >577 && uiy < 593) {          //销书排
		Screen->Cursor =  crHandPoint ;

	}
	if (uix > 219 && uix < 339 && uiy > 609 && uiy < 626) {          //会员充值记录查询
			Screen->Cursor =  crHandPoint ;
	}
		if (uix > 555 && uix < 619 && uiy > 14 && uiy < 31) {      //会员充值
				Screen->Cursor =  crHandPoint ;
		}


}
//---------------------------------------------------------------------------

void __fastcall TfrmUI::imagepxMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	uix = X;
	uiy = Y;
	Label1->Caption = IntToStr(X);
	Label2->Caption = IntToStr(Y);
	if (uix >208 && uix < 273 && uiy >18 && uiy < 30) {          //客户管理
		Screen->Cursor =  crHandPoint ;

	}else
	{
		Screen->Cursor  = crDefault  ;
	}
		if (uix >324 && uix < 390 && uiy >18 && uiy < 30) {          //区哉管理
		Screen->Cursor =  crHandPoint ;

	}
		if (uix >601 && uix < 660 && uiy >240 && uiy < 299) {          //客户结算分析
		Screen->Cursor =  crHandPoint ;

	}
		if (uix >769 && uix < 831 && uiy >241 && uiy < 305) {          //收款结算
		Screen->Cursor =  crHandPoint ;

	}
		if (uix >415 && uix < 471 && uiy >147 && uiy < 202) {          //一般发货
		Screen->Cursor =  crHandPoint ;

	}
		if (uix >355 && uix < 420 && uiy >577 && uiy < 596) {          //批销查询
		Screen->Cursor =  crHandPoint ;

	}
		if (uix >428 && uix < 521 && uiy >15 && uiy < 31) {          //批销业务控制
		Screen->Cursor =  crHandPoint ;

	}

}
//---------------------------------------------------------------------------

