//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bsprint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RpCon"
#pragma link "RpConBDE"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpBase"
#pragma link "RpSystem"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma link "frxCross"
#pragma link "frxRich"
#pragma link "frxBarcode"
#pragma resource "*.dfm"
Tfrmwsaleprinta *frmwsaleprinta;
//---------------------------------------------------------------------------
__fastcall Tfrmwsaleprinta::Tfrmwsaleprinta(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
	Rpdefine::DataID = IntToStr((int)HInstance);
	aqdetail->Connection = cn;
	aqHeader->Connection = cn;
	aqtotalnum->Connection = cn;
	aqhead->Connection = cn;
	aqrvstoragedetail->Connection = cn;
	aqorderdetail->Connection = cn;
	aqorderhead->Connection = cn;
	aqProcureDetail->Connection = cn;
	aqProcureHeader ->Connection = cn;
	aqstoragechashu->Connection = cn;
	adoxiaopiao->Connection = cn;
	     aqmuildetail->Connection = cn;
        aqmuilprinthead->Connection = cn;
        queryA5->Connection=cn;
		queryA4->Connection =cn;
		adomiandan->Connection =cn;
		adoqueryjianhuo->Connection =cn;
	PrintType = 0;
	fcon = cn;
	mayang = false;
}
void Tfrmwsaleprinta::PrintStorage(int ID)
{
	   aqhead->Parameters->ParamByName("ID")->Value =ID ;
	   aqrvstoragedetail->Parameters->ParamByName("ID")->Value = ID;
	   aqhead->Active = true;
	   aqrvstoragedetail->Active = true;
}
void Tfrmwsaleprinta::PrintStoragechashu(int ID)
{
	   aqhead->Parameters->ParamByName("headID")->Value =ID ;
	   aqstoragechashu->Parameters->ParamByName("ID")->Value = ID;
	   aqhead->Active = true;
	   aqstoragechashu->Active = true;
}
void Tfrmwsaleprinta::PrintStorageExe(int type)
{
	frxstorage->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "storage.fr3");
	frxstorage->PrepareReport(true);
	if (type == 0) {
		frxstorage->PrintOptions->ShowDialog = false;
		frxstorage->Print();
	}
	else
	{
		frxstorage->ShowPreparedReport();
	}
	frxstorage->Free();
    return;


	int prientcount;
	String num;
	if (type == 1) {
		wholesale->ProjectFile  = ExtractFilePath(Application->ExeName) + "simplestorage.rav";
			wholesale->SetParam("title",printtitle+"入库单");
			wholesale->SetParam("bk",aqhead->FieldByName("remarks")->AsAnsiString);  //单号
			if (DanhaoChange) {
			 wholesale->SetParam("Danhao",aqhead->FieldByName("stgntcodestr")->AsAnsiString);
			}else                               //change danhao
			{
			  wholesale->SetParam("Danhao",aqhead->FieldByName("Stgntcode")->AsAnsiString);
			}
	}
	else
   	{
	  wholesale->ProjectFile  =ExtractFilePath(Application->ExeName)+ "simplestoragechuku.rav";
	  wholesale->SetParam("title",printtitle+"入库退货单");
	  wholesale->SetParam("bk",aqhead->FieldByName("remarks")->AsAnsiString);
	  if (DanhaoChange) {
			 wholesale->SetParam("Danhao",aqhead->FieldByName("stgntcodestr")->AsAnsiString);
	  }else                               //change danhao
	  {
		  wholesale->SetParam("Danhao",aqhead->FieldByName("Stgntcode")->AsAnsiString);
	  }
   }
   aqrvstoragedetail->Last();
	num = aqrvstoragedetail->FieldByName("xuhao")->AsAnsiString;
	 aqrvstoragedetail->First();

	wholesale->Open();
	wholesale->SetParam("num",num);
	wholesale->SetParam("rkbk",rkbk);
	  wholesale->SetParam("operator",Maker) ;
	  wholesale->SetParam("supplycode",supplycode) ;

	 

	wholesale->Execute();
	wholesale->Close();
}

void Tfrmwsaleprinta::PrintStorageExe()
{
	int prientcount;
   int num = 0;
   float totalfixedprice = 0.0,totaldiscountprice = 0.0;
   wholesale->ProjectFile  = ExtractFilePath(Application->ExeName)+"chashustorage.rav";
			wholesale->SetParam("title",printtitle+"入库单异常");
			wholesale->SetParam("bk",aqhead->FieldByName("remarks")->AsAnsiString);  //单号
			if (DanhaoChange) {
			 wholesale->SetParam("Danhao",aqhead->FieldByName("stgntcodestr")->AsAnsiString);
			}else                               //change danhao
			{
			  wholesale->SetParam("Danhao",aqhead->FieldByName("Stgntcode")->AsAnsiString);
			}
   aqstoragechashu->First() ;
	while (!aqstoragechashu->Eof)
	{
		num = num + aqstoragechashu->FieldByName("amount")->AsInteger ;
		totalfixedprice = totalfixedprice + (aqstoragechashu->FieldByName("amount")->AsInteger)*(aqstoragechashu->FieldByName("price")->AsFloat) ;
		totaldiscountprice = totaldiscountprice + (aqstoragechashu->FieldByName("amount")->AsInteger)*(aqstoragechashu->FieldByName("price")->AsFloat)*(aqstoragechashu->FieldByName("discount")->AsFloat)/100 ;
		aqstoragechashu->Next();
	}

	wholesale->Open();
	wholesale->SetParam("num",num);
	wholesale->SetParam("totalfixedprice",totalfixedprice);
	wholesale->SetParam("totaldiscountprice",totaldiscountprice);
	wholesale->SetParam("rkbk",rkbk);
	  wholesale->SetParam("operator",Maker) ;

	  /*TRavePage *RavePage;
		TRaveRegion *RaveRegion;
		double top,hight;
		RavePage = (TRavePage *)wholesale->ProjMan->FindRaveComponent("Report1.Page1",NULL);
		RaveRegion = (TRaveRegion *)wholesale->ProjMan->FindRaveComponent("Region1",RavePage);
		prientcount = aqstoragechashu->RecordCount ;
		aqstoragechashu->First();
		while (!aqstoragechashu->Eof )
		{
			if (aqstoragechashu->FieldByName("Name")->AsAnsiString.Length() > 72  ) {
				prientcount = prientcount + 2;
			}
			else if (aqstoragechashu->FieldByName("Name")->AsAnsiString.Length() > 36  ) {
				prientcount++;
			}
			aqstoragechashu->Next();
		}
		//aqrvstoragedetail->First();

		hight = 0.18*prientcount;

		if (rkbk == "") {
			RavePage->PageHeight = hight + 2.96;
			//RavePage->PageWidth = 8;
			RaveRegion->Height = hight + 2.95;
		}
		else
		{
			RavePage->PageHeight = hight + 3.16;
			//RavePage->PageWidth = 8;
			RaveRegion->Height = hight + 3.15;
		}
		   */

	wholesale->Execute();
	wholesale->Close();
}
void Tfrmwsaleprinta::miandanprint(AnsiString ID,boolean isprint)
{
  AnsiString sql,ps;
	sql="exec C_GetMianDanData :ID";
		adomiandan->Close();
			adomiandan->SQL->Clear();
		adomiandan->SQL->Add(sql);
		adomiandan->Parameters->ParamByName("ID")->Value=ID;
		adomiandan->Open();
		ps = ExtractFilePath(Application->ExeName) + "wsalemiandan.fr3";
		frxreportjianhuo->LoadFromFile(ps);
		frxreportjianhuo->PrepareReport(true);
		if (isprint) {
			frxreportjianhuo->PrintOptions->ShowDialog = false;
			frxreportjianhuo->Print();
		}
		else
		{
			frxreportjianhuo->ShowPreparedReport();
		}


}
void Tfrmwsaleprinta::miandanprintA5(AnsiString ID,boolean isprint)
{
    AnsiString sql,ps;
	sql="exec C_GetMianDanData :ID";
		adomiandan->Close();
			adomiandan->SQL->Clear();
		adomiandan->SQL->Add(sql);
		adomiandan->Parameters->ParamByName("ID")->Value=ID;
		adomiandan->Open();
		ps = ExtractFilePath(Application->ExeName) + "wsalemiandanA5.fr3";
		frxreportjianhuo->LoadFromFile(ps);
		frxreportjianhuo->PrepareReport(true);
		if (isprint) {
			frxreportjianhuo->PrintOptions->ShowDialog = false;
			frxreportjianhuo->Print();
		}
		else
		{
			frxreportjianhuo->ShowPreparedReport();
		}






}
 void Tfrmwsaleprinta::jianhuodanprint(AnsiString ID,boolean isprint)
 {
   //检货单
	AnsiString sql,ps;
	sql="exec C_GetJianHuoDetail :ID";
		adoqueryjianhuo->Close();
		adoqueryjianhuo->SQL->Clear();
        adoqueryjianhuo->SQL->Add(sql);
		adoqueryjianhuo->Parameters->ParamByName("ID")->Value=ID;
		adoqueryjianhuo->Open();
		ps = ExtractFilePath(Application->ExeName) + "wsalejianhuo.fr3";
		frxreportjianhuo->LoadFromFile(ps);
	  	frxreportjianhuo->PrepareReport(true);
		if (isprint) {
			frxreportjianhuo->PrintOptions->ShowDialog = false;
			frxreportjianhuo->Print();
		}
		else
		{
			frxreportjianhuo->ShowPreparedReport();
		}

 }
void Tfrmwsaleprinta::InputPara(AnsiString ID,int mode)
{
	AnsiString sql;
	ordertype = mode;
	if (PrintType ==1 ) {      //订单
		if (mode == 0) {
			sql = "select RANK() OVER(order by A.ID asc) as xuhao,rtrim(C.ISBN) as ISBN,rtrim(C.Name) as Name,rtrim(C.UserDefCode) as UserDefCode,rtrim(C.PressCount) as PressCount,rtrim(E.abbreviatedname) as abbreviatedname,rtrim(C.author) as author,rtrim(C.price) as price,"
				" A.amount,A.discount,A.fixedprice,discountedprice "
				" from bs_ordernote A "
				" left join BS_BookCatalog C on A.bkcatalogID = C.ID "
				" left join BS_PressInfo E on E.ID = C.pressID "
				" where A.OrderNtHeaderID = " + ID + " and A.state = 0 "
				" order by A.id asc ";
			aqorderdetail->Close();
			aqorderdetail->SQL->Clear();
			aqorderdetail->SQL->Add(sql);
			aqorderdetail->Open();
			aqorderhead->Parameters->ParamByName("ID")->Value = ID;
			aqorderhead->Active = true;
			wholesale->SetParam("title",aqorderhead->FieldByName("name")->AsAnsiString+ "拣货单" );
		}
		else
		{
			sql = "select RANK() OVER(order by A.ID asc) as xuhao,rtrim(C.ISBN) as ISBN,rtrim(C.Name) as Name,rtrim(C.UserDefCode) as UserDefCode,rtrim(C.PressCount) as PressCount,rtrim(E.abbreviatedname) as abbreviatedname,rtrim(C.author) as author,rtrim(C.price) as price,"
				" A.amount,A.localnum,A.discount,A.fixedprice,discountedprice "
				" from bs_ordernote A "
				" left join BS_BookCatalog C on A.bkcatalogID = C.ID "
				" left join BS_PressInfo E on E.ID = C.pressID "
				" where A.OrderNtHeaderID = " + ID + " and A.state = 0 and A.localnum > 0 "
				" order by A.id asc ";
			aqorderdetail->Close();
			aqorderdetail->SQL->Clear();
			aqorderdetail->SQL->Add(sql);
			aqorderdetail->Open();
			aqorderhead->Parameters->ParamByName("ID")->Value = ID;
			aqorderhead->Active = true;
		}

	}else if (PrintType == 2) {            //采购
		aqProcureDetail->Parameters->ParamByName("ID")->Value = ID;
		aqProcureHeader->Parameters->ParamByName("ID")->Value = ID;
		aqProcureDetail->Active = true;
		aqProcureHeader->Active = true;
	}
	else
	{
		aqtotalnum->Parameters->ParamByName("headID")->Value =ID ;
		//aqdetail->Parameters->ParamByName("headID")->Value = ID;
		aqHeader->Parameters->ParamByName("ID")->Value = ID;


			//" group by C.ID,C.ISBN,C.Name,C.UserDefCode,E.abbreviatedname,C.author,C.price,C.PressCount,A.discount,c.huojiangstate,A.xiaoqu,A.xueyuan,A.course,C.BookWords,C.Pressdate,A.incode,A.class "
				if (booltuihuo) {
                	sql = "select RANK() OVER(order by A.ID asc) xuhao,A.ID,rtrim(A.incode) AS incode,rtrim(C.ISBN) as ISBN,rtrim(C.Name) as CatalogName,rtrim(E.AbbreviatedName) as AbbreviatedName,C.Price,rtrim(C.Author) as Author,rtrim(C.UserDefCode) as UserDefCode,A.amount ,A.Discount,A.FixedPrice ,A.DiscountedPrice ,left(convert(nvarchar(100),C.Pressdate,120),7) as Pressdate,C.PressCount,C.BookWords, "
			" rtrim(c.huojiangstate) as huojiangstate,A.xiaoqu,A.xueyuan,A.course,A.class"
			" from BS_WsaleNote A "
			" left join STK_BookInfo B on A.bkinfoid = B.ID "
			" left join BS_BookCatalog C on B.bkcatalogID = C.ID "
			" left join BS_PressInfo E on E.ID = C.pressID "
			" where A.wsalentheaderid= " + ID +
                        " ORDER BY xuhao";
				} else
                {                                       //order by E.AbbreviatedName asc,C.name asc
					sql = "select RANK() OVER(order by A.ID asc) xuhao,A.ID,rtrim(A.incode) AS incode,rtrim(C.ISBN) as ISBN,rtrim(C.Name) as CatalogName,rtrim(E.AbbreviatedName) as AbbreviatedName,C.Price,rtrim(C.Author) as Author,rtrim(C.UserDefCode) as UserDefCode,A.amount ,A.Discount,A.FixedPrice ,A.DiscountedPrice ,left(convert(nvarchar(100),C.Pressdate,120),7) as Pressdate,C.PressCount,C.BookWords, "
			" rtrim(c.huojiangstate) as huojiangstate,A.xiaoqu,A.xueyuan,A.course,A.class"
			" from BS_WsaleNote A "
			" left join STK_BookInfo B on A.bkinfoid = B.ID "
			" left join BS_BookCatalog C on B.bkcatalogID = C.ID "
			" left join BS_PressInfo E on E.ID = C.pressID "
			" where A.wsalentheaderid= " + ID +
						 " ORDER BY xuhao";
		      //  " ORDER BY E.AbbreviatedName asc,C.name asc "  ;
                }
		aqdetail->Close();
		aqdetail->SQL->Clear();
		aqdetail->SQL->Add(sql);
		aqdetail->Open();
		//aqdetail->Active = true;
		aqHeader->Active = true;
		aqtotalnum->Active = true;
	}
}
void Tfrmwsaleprinta::previewprint(int type , int simple)         //type=0 打印,=1预览
{

	int prientcount;
	if (simple == 1 || simple == 2) {                            //1,批销单 2.批销退货单 //1打印格式1 2 打印格式2

		struct PrintControl *item;
		PrintTile = new TStringList(NULL);
		// PrintTile->AddObject();
		AnsiString ps;

		TADOQuery *aptitle = new TADOQuery(NULL);
		aptitle->Connection = fcon ;
		aptitle->Close();
		aptitle->SQL->Clear();
		AnsiString sql;
		if (printmodle > -1) {
			sql = "select reportname from sys_printhead where id = " + IntToStr(printmodle);
			aptitle->Close();
			aptitle->SQL->Clear();
			aptitle->SQL->Add(sql);
			aptitle->Open();
			ps = aptitle->FieldByName("reportname")->AsAnsiString.Trim() + ".fr3"  ;
			aptitle->Close();
			aptitle->SQL->Clear();
			sql = "select sys_printdetail.*,sys_printhead.typename from sys_printdetail left join sys_printhead on sys_printdetail.headid = sys_printhead.id where sys_printdetail.[print] = 1 and sys_printdetail.headid = "  + IntToStr(printmodle) + " order by sys_printdetail.id";
		}
		else
		{
            sql = "select reportname from sys_printhead where modle = 1 and sys_printhead.active = 1 and sys_printhead.stgid = " + IntToStr(stgid) ;
			aptitle->Close();
			aptitle->SQL->Clear();
			aptitle->SQL->Add(sql);
			aptitle->Open();
			ps = aptitle->FieldByName("reportname")->AsAnsiString.Trim() + ".fr3"  ;
			aptitle->Close();
			aptitle->SQL->Clear();
			sql = "select sys_printdetail.*,sys_printhead.typename from sys_printdetail left join sys_printhead on sys_printdetail.headid = sys_printhead.id where sys_printdetail.[print] = 1 and sys_printhead.modle = 1 and sys_printhead.active = 1 and sys_printhead.stgid = " + IntToStr(stgid) + " order by sys_printdetail.id";
		}
		aptitle->SQL->Add(sql);
		aptitle->Open();
		while(!aptitle->Eof)
		{
			item = new PrintControl();
			item->name = aptitle->FieldByName("name")->AsAnsiString ;
			item->width = aptitle->FieldByName("with")->AsFloat ;
			PrintTile->AddObject(aptitle->FieldByName("columnname")->AsAnsiString ,(TObject*)item);
			aptitle->Next();
		}
		ps = ExtractFilePath(Application->ExeName) + ps;
		if (aptitle->FieldByName("typename")->AsAnsiString == "针对学校" ) {
			ps = ExtractFilePath(Application->ExeName)+"wsalexx.fr3" ;
			mayang = true;
		}
		else
		{
			ps = ExtractFilePath(Application->ExeName)+"wsale.fr3" ;
		}

		frxWsale->LoadFromFile(ps);
		frxWsale->PrepareReport(true);
		if (type == 0) {          //
			frxWsale->PrintOptions->ShowDialog = false;
			frxWsale->Print();
		}
		else
		{
			frxWsale->ShowPreparedReport();
		}
		frxWsale->Free();
		return;




		wholesale->ProjectFile  = ExtractFilePath(Application->ExeName)+"wsaletest.rav";
		wholesale->Open();


		if (simple == 1) {
			wholesale->SetParam("title",printtitle+"发货单");
		}
		else
		{
			wholesale->SetParam("title",printtitle+"退货单");
		}
		wholesale->SetParam("bk",aqHeader->FieldByName("Remarks")->AsAnsiString);
		wholesale->SetParam("yingshou",FormatFloat("￥0.00",yingshou) );
		wholesale->SetParam("fandian",FormatFloat("￥0.00",fandian));
		wholesale->SetParam("pxbk",pxbk);
		wholesale->SetParam("contact",contact);
		wholesale->SetParam("tel",tel);
		wholesale->SetParam("address",address);
		wholesale->SetParam("ClientName",ClientName);
		wholesale->SetParam("heji",Doubletostring(aqHeader->FieldByName("discountedprice")->AsFloat));
		if (DanhaoChange) {
			wholesale->SetParam("Danhao",aqHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString);
		}else                               //change danhao
		{
			wholesale->SetParam("Danhao",aqHeader->FieldByName("WsaleNtCode")->AsAnsiString);
		}

		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		//AnsiString sql;
		if (printmodle == 1) {
			sql = "select * from sys_printdetail where headid = "  + IntToStr(type);
		}
		else
		{
			sql = "select sys_printdetail.* from sys_printdetail left join sys_printhead on sys_printdetail.headid = sys_printhead.id where sys_printdetail.[print] = 1 and sys_printhead.modle = 1 and sys_printhead.active = 1 and sys_printhead.stgid = " + IntToStr(stgid);
		}
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->IsEmpty() ) {
			return;
		}
		TRavePage *RavePage;
		TRaveDataView *DataView,*DataView1;
		TRaveMemo *RaveMemo[18];
		TRaveDataMemo *DataMemo[18];
		TRaveDataText *Dataamount,*Datafixed,*Datadiscont;

		RavePage = (TRavePage *)wholesale->ProjMan->FindRaveComponent("Report1.Page1",NULL);
		DataView = (TRaveDataView *)wholesale->ProjMan->FindRaveComponent("DataView2",NULL);
		DataView1 = (TRaveDataView *)wholesale->ProjMan->FindRaveComponent("DataView1",NULL);
		int n = 1;
		float left = 0.2;
		AnsiString memo = "",DMemo = "";
		while (!aq->Eof && n <= 18)
		{
			memo = "Memo" + IntToStr(n);
			DMemo = "DataMemo" + IntToStr(n);
			RaveMemo[n] = (TRaveMemo *)wholesale->ProjMan->FindRaveComponent(memo,RavePage);
			RaveMemo[n]->Left = left;
			RaveMemo[n]->Width = aq->FieldByName("with")->AsFloat;
			RaveMemo[n]->Text = aq->FieldByName("name")->AsAnsiString ;

			DataMemo[n] = (TRaveDataMemo *)wholesale->ProjMan->FindRaveComponent(DMemo,RavePage);
			DataMemo[n]->Left = left;
			DataMemo[n]->Width = aq->FieldByName("with")->AsFloat;
			DataMemo[n]->DataView = DataView;
			DataMemo[n]->DataField = aq->FieldByName("columnname")->AsAnsiString ;
			if (aq->FieldByName("name")->AsAnsiString == "数量" ) {
				Dataamount = (TRaveDataText *)wholesale->ProjMan->FindRaveComponent("DataText30",RavePage);
				Dataamount->Left = left;
				Dataamount->Width = aq->FieldByName("with")->AsFloat;
				Dataamount->DataView = DataView1;
				Dataamount->DataField = "totalamount" ;
			}
			if (aq->FieldByName("name")->AsAnsiString == "码洋" ) {
				Datafixed = (TRaveDataText *)wholesale->ProjMan->FindRaveComponent("DataText31",RavePage);
				Datafixed->Left = left;
				Datafixed->Width = aq->FieldByName("with")->AsFloat;
				Datafixed->DataView = DataView1;
				Datafixed->DataField = "fixedprice" ;
			}
			if (aq->FieldByName("name")->AsAnsiString == "实洋" ) {
				Datadiscont = (TRaveDataText *)wholesale->ProjMan->FindRaveComponent("DataText32",RavePage);
				Datadiscont->Left = left;
				Datadiscont->Width = aq->FieldByName("with")->AsFloat;
				Datadiscont->DataView = DataView1;
				Datadiscont->DataField = "discountedprice" ;
			}

			n = n + 1;
			left = left + aq->FieldByName("with")->AsFloat ;
			aq->Next();
		}

		delete aq;

   /*	if (type == 1) {
		if (printmodle == 0) {
			wholesale->ProjectFile  = ExtractFilePath(Application->ExeName)+"bswholesalexx.rav";
		}
		else
		{
			wholesale->ProjectFile  = ExtractFilePath(Application->ExeName)+"bswholesale.rav";
		}
		wholesale->Open();
			wholesale->SetParam("title",aqHeader->FieldByName("name")->AsAnsiString+"发货单");
			wholesale->SetParam("bk",aqHeader->FieldByName("Remarks")->AsAnsiString);
			wholesale->SetParam("yingshou",FormatFloat("￥0.00",yingshou) );
			wholesale->SetParam("fandian",FormatFloat("￥0.00",fandian));
			wholesale->SetParam("pxbk",pxbk);
			wholesale->SetParam("ClientName",ClientName);
			if (DanhaoChange) {
				wholesale->SetParam("Danhao",aqHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString);
			}else                               //change danhao
			{
				wholesale->SetParam("Danhao",aqHeader->FieldByName("WsaleNtCode")->AsAnsiString);
			}

	}else if (type == 2) {
			if (printmodle == 0) {
				wholesale->ProjectFile  = ExtractFilePath(Application->ExeName)+ "bswholesaletuihuoxx.rav";
			}
			else
			{
				wholesale->ProjectFile  = ExtractFilePath(Application->ExeName)+ "bswholesaletuihuo.rav";
			}

			wholesale->Open();
			wholesale->SetParam("title",aqHeader->FieldByName("name")->AsAnsiString+"发货退货单");
			wholesale->SetParam("bk",aqHeader->FieldByName("Remarks")->AsAnsiString);
			wholesale->SetParam("time",aqHeader->FieldByName("maketime")->AsAnsiString);
			wholesale->SetParam("pxtime",aqHeader->FieldByName("maketime")->AsAnsiString);
			wholesale->SetParam("pxbk",pxbk);
			wholesale->SetParam("ClientName",ClientName);
			if (DanhaoChange) {
				wholesale->SetParam("Danhao",aqHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString);
			}else                               //change danhao
			{
				wholesale->SetParam("Danhao",aqHeader->FieldByName("WsaleNtCode")->AsAnsiString);
			}


	}  */
	}else if (simple == 2) {
		/*if (type == 1) {
		wholesale->ProjectFile  = ExtractFilePath(Application->ExeName)+"simplebswholesale.rav";
		wholesale->Open();
	}else if (type == 2) {
		wholesale->ProjectFile  = ExtractFilePath(Application->ExeName)+"simplebswholesaletuihuo.rav";
		wholesale->Open();
	}   */
	}else if (simple == 3) { //订单打印

		/*wholesale->ProjectFile  = ExtractFilePath(Application->ExeName) + "Order.rav";
		wholesale->Open();
		aqorderdetail->Last();
		String num;
		num = aqorderdetail->FieldByName("xuhao")->AsString  ;
		aqorderdetail->First();
		wholesale->SetParam("num",num);
		wholesale->SetParam("ClientName",ClientName);
		wholesale->SetParam("title",printtitle+"收订单");
		wholesale->SetParam("printbk",pxbk);
		wholesale->SetParam("contact",contact);
		wholesale->SetParam("tel",tel);
		wholesale->SetParam("address",address);*/

		if (ordertype == 0) {
			frxOrder->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "Order.fr3");
			printtitle = printtitle + "收订单";
		}
		else
		{
        	frxOrder->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "Orderlocl.fr3");
        	printtitle = printtitle + "拣货单";
		}


		frxOrder->PrepareReport(true);
		if (type == 0) {
			frxOrder->PrintOptions->ShowDialog = false;
			frxOrder->Print();
		}
		else
		{
			frxOrder->ShowPreparedReport();
		}
		frxOrder->Free();

	}else if (simple == 4) {//采购打印
		 /*olesale->ProjectFile = ExtractFilePath(Application->ExeName) + "Procure.rav";
         wholesale->Open() ;
		 aqProcureDetail->Last();
		 String num ;
		 num = aqProcureDetail->FieldByName("xuhao")->AsAnsiString ;
		 wholesale->SetParam("num",num);
		 wholesale->SetParam("title",printtitle+"采购单");
		wholesale->SetParam("printbk",pxbk);
		wholesale->SetParam("contact",contact);
		wholesale->SetParam("tel",tel);
		wholesale->SetParam("address",address);

		wholesale->SetParam("shcontact",shcontact);
		wholesale->SetParam("shtel",shtel);
		wholesale->SetParam("shaddress",shaddress);   */
		if (aqProcureHeader->FieldByName("inorder")->AsInteger == 1 ) {
			frxProcure->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "Procurein.fr3");
		}
		else
		{
			frxProcure->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "Procure.fr3");
		}

		frxProcure->PrepareReport(true);
		if (type == 0) {
			frxProcure->PrintOptions->ShowDialog = false;
			frxProcure->Print();
		}
		else
		{
			frxProcure->ShowPreparedReport();
		}
		frxProcure->Free();
	}

	//wholesale->Execute();
	//wholesale->Close();
	//wholesale->Destroying();
	//wholesale->Free();
}
//---------------------------------------------------------------------------

AnsiString Tfrmwsaleprinta::Doubletostring(double num)
{
	AnsiString outnum,ychar,outstring;
	outnum = FormatFloat("0.00",num);
	outnum = outnum.SubString(0,outnum.Pos(".")-1) + outnum.SubString(outnum.Pos(".")+1,2);

	AnsiString danwei[10] = {"仟","佰","拾","万","仟","佰","拾","元","角","分"};
	int len = outnum.Length() ;
	for (int i = 0; i < 10; i++) {
		if (len < 10-i) {
			outstring = outstring + "×" + danwei[i];
		}
		else
		{
			outstring = outstring + Touppnum(outnum.SubString(len-9 + i,1)) + danwei[i];
		}
	}
	return  outstring;
}
//---- -----------------------------------------------------------------------
AnsiString Tfrmwsaleprinta::Touppnum(AnsiString ychar)
{
	AnsiString mchar;
	if (ychar == "") {
    	return " ";
	}
	int i;
	try {
		i = StrToInt(ychar);
	} catch (...) {
		return " ";
	}
	switch (i) {
		case 0:
			mchar = "零";
		break;
		case 1:
			mchar = "壹";
		break;
		case 2:
			mchar = "贰";
		break;
		case 3:
			mchar = "叁";
		break;
		case 4:
			mchar = "肆";
		break;
		case 5:
			mchar = "伍";
		break;
		case 6:
			mchar = "陆";
		break;
		case 7:
			mchar = "柒";
		break;
		case 8:
			mchar = "捌";
		break;
		case 9:
			mchar = "玖";
		break;
    default:
		;
	}
	return mchar;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmwsaleprinta::frxProcureGetValue(const UnicodeString VarName, Variant &Value)

{
	if (CompareText(VarName,"\"num\"")==0 ) {
		  Value = num;
	}
	if (CompareText(VarName,"\"Name\"")==0 ) {
		  Value = printtitle;
	}
	if (CompareText(VarName,"\"printbk\"")==0 ) {
		  Value = pxbk;
	}
	if (CompareText(VarName,"\"contact\"")==0 ) {
		  Value = contact;
	}
	if (CompareText(VarName,"\"tel\"")==0 ) {
		  Value = tel;
	}
	if (CompareText(VarName,"\"address\"")==0 ) {
		  Value = address;
	}
	if (CompareText(VarName,"\"shcontact\"")==0 ) {
		  Value = shcontact;
	}
	if (CompareText(VarName,"\"shtel\"")==0 ) {
		  Value = shtel;
	}
	if (CompareText(VarName,"\"shaddress\"")==0 ) {
		  Value = shaddress;
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmwsaleprinta::frxWsaleBeforePrint(TfrxReportComponent *Sender)
{
	TfrxCrossView * Cross;
	int i, j;
	Variant Row,Col,Text;
	AnsiString titlename;
	int totalamount = 0;
	float shiyang = 0.00,mayang = 0.00;
	Cross = dynamic_cast <TfrxCrossView *> (Sender);
	AnsiString tojiTitle[3];
	if(Cross != NULL)
	{
		Cross->Left = 0.5;

		aqdetail->First();
		i = 0;
		while (!aqdetail->Eof)
		{
			for(j = 0; j < aqdetail->Fields->Count; j++)
			{
				Row = i;
				titlename = FindTitleName(aqdetail->Fields->Fields[j]->DisplayLabel);
				if (titlename != "NOTITLE") {
					Col = titlename ;

				if (CompareText(titlename,"码洋")==0){
					Text =   FormatFloat("0.00",aqdetail->Fields->Fields[j]->AsFloat);
					tojiTitle[0]="码洋";
					mayang = mayang + aqdetail->Fields->Fields[j]->AsFloat;

				}else if ((CompareText(titlename,"实洋")==0)) {
						Text =   FormatFloat("0.00",aqdetail->Fields->Fields[j]->AsFloat);
						tojiTitle[1]="实洋";
						shiyang = shiyang + aqdetail->Fields->Fields[j]->AsFloat;
					  }
				else if (CompareText(titlename,"定价")==0) {
						Text =   FormatFloat("0.00",aqdetail->Fields->Fields[j]->AsFloat);
					 }
				else if ((CompareText(titlename,"数量")==0)) {
					   Text =   aqdetail->Fields->Fields[j]->AsAnsiString ;
					   tojiTitle[2]="数量";
					   totalamount = totalamount + aqdetail->Fields->Fields[j]->AsInteger ;
					 }
				else if((CompareText(titlename,"折扣")==0)) {
						Text =   FormatFloat("00%",aqdetail->Fields->Fields[j]->AsFloat);
				}
				else{
					Text = aqdetail->Fields->Fields[j]->AsAnsiString ;
				}
					//Text = aqdetail->Fields->Fields[j]->AsAnsiString ;

					Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);
				}
			}
			aqdetail->Next();
			i++;
		}
    	//合计
		Row = i;
		Col = "序号";
		Text = "合计";
		Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);
		for (int p = 0 ; p < 3; p++) {
			if (tojiTitle[p] != "") {
				Col = tojiTitle[p];
				if (Col == "数量") {
					Text = IntToStr(totalamount);
				}
				if (Col == "码洋") {
					Text = FormatFloat("0.00",mayang);
				}
				if (Col == "实洋") {
					Text = FormatFloat("0.00",shiyang);
				}
				Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsaleprinta::frxWsaleGetValue(const UnicodeString VarName, Variant &Value)

{
	//传递宽度
	if (CompareText(VarName,"\"xuhao\"")==0  ) {  //序号
		 Value = FindTitlewith("xuhao");
	}
	if (CompareText(VarName,"\"incode\"")==0  ) {  //内部识别码
		 Value = FindTitlewith("incode");
	}
	if (CompareText(VarName,"\"ISBN\"")==0  ) {    //书号
		Value = FindTitlewith("ISBN");
	}
	if (CompareText(VarName,"\"CatalogName\"")==0 ) {   //书名
		Value = FindTitlewith("CatalogName");
	}
	if (CompareText(VarName,"\"AbbreviatedName\"")==0 ) {    //出版社
		Value = FindTitlewith("AbbreviatedName");
	}
	if (CompareText(VarName,"\"Price\"")==0 ) {   //定价
		Value = FindTitlewith("Price");
	}
	if (CompareText(VarName,"\"Author\"")==0 ) {  //作者
		Value = FindTitlewith("Author");
	}
	if (CompareText(VarName,"\"UserDefCode\"")==0 ) {  //自编码
		Value = FindTitlewith("UserDefCode");
	}
	if (CompareText(VarName,"\"Amount\"")==0 ) {      //数量
		Value = FindTitlewith("Amount");
	}
	if (CompareText(VarName,"\"Discount\"")==0 ) {     //折扣
		Value = FindTitlewith("Discount");
	}
	if (CompareText(VarName,"\"FixedPrice\"")==0 ) {   //码洋
		Value = FindTitlewith("FixedPrice");
	}
	if (CompareText(VarName,"\"DiscountedPrice\"")==0 ) {        //实洋
		Value = FindTitlewith("DiscountedPrice");
	}
	if (CompareText(VarName,"\"Pressdate\"")==0 ) {   //出版日期
		Value = FindTitlewith("Pressdate");
	}
	if (CompareText(VarName,"\"PressCount\"")==0 ) {  //版次
		Value = FindTitlewith("PressCount");
	}
	if (CompareText(VarName,"\"BookWords\"")==0 ) {    //册/包
		Value = FindTitlewith("BookWords");
	}

	if (CompareText(VarName,"\"huojiangstate\"")==0 ) {   //获奖情况
		Value = FindTitlewith("huojiangstate");
	}
	if (CompareText(VarName,"\"xiaoqu\"")==0 ) {   //校区
		Value = FindTitlewith("xiaoqu");
	}
	if (CompareText(VarName,"\"xueyuan\"")==0 ) {        //学院
		Value = FindTitlewith("xueyuan");
	}
	if (CompareText(VarName,"\"course\"")==0 ) {   //课程名称
		Value = FindTitlewith("course");
	}
	if (CompareText(VarName,"\"class\"")==0 ) {   //课程名称
		Value = FindTitlewith("class");
	}

	//传递参数
	if (CompareText(VarName,"\"title\"")==0 ) {
		if (tuihuo == 1) {
			Value = printtitle + "发货退货单";
		}
		else
		{
			Value = printtitle + "发货单";
		}
	}
	if (CompareText(VarName,"\"yingshou\"")==0 ) {
		  Value = FormatFloat("￥0.00",yingshou);
	}
	if (CompareText(VarName,"\"fandian\"")==0 ) {
		  Value = FormatFloat("￥0.00",fandian);
	}
	if (CompareText(VarName,"\"pxbk\"")==0 ) {
		  Value = pxbk;
	}
	if (CompareText(VarName,"\"contact\"")==0 ) {
		  Value = contact;
	}
	if (CompareText(VarName,"\"tel\"")==0 ) {
		  Value = tel;
	}
	if (CompareText(VarName,"\"address\"")==0 ) {
		  Value = address;
	}
	if (CompareText(VarName,"\"ClientName\"")==0 ) {
		  Value = ClientName;
	}
	if (CompareText(VarName,"\"heji\"")==0 ) {
		if (mayang ) {
			Value = Doubletostring(aqHeader->FieldByName("fixedprice")->AsFloat);
		}
		else
		{
			Value = Doubletostring(aqHeader->FieldByName("discountedprice")->AsFloat);
		}
	}
	if (CompareText(VarName,"\"Danhao\"")==0 ) {
		if (DanhaoChange) {
			Value = aqHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString;
		}else                               //change danhao
		{
			Value = aqHeader->FieldByName("WsaleNtCode")->AsAnsiString;
		}
	}
}
//---------------------------------------------------------------------------

AnsiString Tfrmwsaleprinta::FindTitleName(AnsiString ColumnName)
{
	int i;
	i =  PrintTile->IndexOf(ColumnName);
	if (i != -1 ) {
		  return ((PrintControl*)PrintTile->Objects[i])->name ;
	}else return "NOTITLE";
}
//---------------------------------------------------------------------------
float Tfrmwsaleprinta::FindTitlewith(AnsiString ColumnName)
{
	int i;
	i =  PrintTile->IndexOf(ColumnName);
	if (i != -1 ) {
		  return ((PrintControl*)PrintTile->Objects[i])->width ;
	}else return 0;
}
void __fastcall Tfrmwsaleprinta::frxOrderGetValue(const UnicodeString VarName, Variant &Value)

{
	if (CompareText(VarName,"\"ClientName\"")==0 ) {
		  Value = ClientName;
	}
	if (CompareText(VarName,"\"title\"")==0 ) {
		  Value = printtitle;

	}
	if (CompareText(VarName,"\"printbk\"")==0 ) {
		  Value = pxbk;
	}
	if (CompareText(VarName,"\"contact\"")==0 ) {
		  Value = contact;
	}
	if (CompareText(VarName,"\"tel\"")==0 ) {
		  Value = tel;
	}
	if (CompareText(VarName,"\"address\"")==0 ) {
		  Value = address;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsaleprinta::frxstorageGetValue(const UnicodeString VarName, Variant &Value)

{
	if (CompareText(VarName,"\"title\"")==0 ) {
		if (tuihuo == 1) {
			Value = printtitle + "入库退货单";
		}
		else
		{
			Value = printtitle + "入库单";
		}
	}
	if (CompareText(VarName,"\"rkbk\"")==0 ) {
		  Value = rkbk;
	}
	if (CompareText(VarName,"\"supplycode\"")==0 ) {
		  Value = supplycode;
	}
	if (CompareText(VarName,"\"Danhao\"")==0 ) {
		if (DanhaoChange) {
			Value = aqhead->FieldByName("stgntcodestr")->AsAnsiString;
		}else                               //change danhao
		{
			Value = aqhead->FieldByName("Stgntcode")->AsAnsiString;
		}
	}
	if (CompareText(VarName,"\"contact\"")==0 ) {
		  Value = contact;
	}
	if (CompareText(VarName,"\"telephone\"")==0 ) {
		  Value = tel;
	}
	if (CompareText(VarName,"\"address\"")==0 ) {
		  Value = address;
	}
}

void Tfrmwsaleprinta::wsalemuilPrint(AnsiString ID,int type,bool xiaopiao)
{
  ///A5打印
    TStringList *IDStr = new TStringList(NULL);
     AnsiString ps;
    IDStr->DelimitedText=ID;
    IDStr->Delimiter=',';
    if (IDStr->Count>1) {
         //lianxueprint=true;
         ID=ID+"-1";
    }
    if ((!xiaopiao)&&(type==3)) { //A5连续打印

       try
       {
       AnsiString sql;
       if (!pixiaoortuihuo) {
         sql = "select A.Remarks,U.wsprinttitle+'发货退货单' as printName,";
       }else
        sql = "select A.Remarks,U.wsprinttitle+'发货单' as printName,";

        sql = sql+" U.wscontact,U.wstel,U.wsaddress,U.wsprintbk,F.name as clientname,";
        sql = sql+" A.WsaleNtCodeStr,A.hdtime ,A.hdtime  as maketime ,A.fixedprice,A.discountedprice";
        sql = sql+" ,A.addcosts,C.name as maker ,W.amount amount,W.discount discount,Z.name as bookname,Z.price,A.totalamount from BS_WsaleNoteHeader A";
        sql = sql+" left join sys_staffinfo B on A.staffid = B.ID ";
        sql = sql+" left join sys_user C on A.operatorid = C.ID";
		sql = sql+" left join SYS_StorageInfo D on A.stgID = D.ID";
		sql = sql+" left join CUST_CustomerInfo F on A.vendorid = F.ID";
		sql = sql+" left join dbo.BS_WsaleNote W on W.WsaleNtheaderID=A.ID ";
		sql = sql +" left join stk_bookinfo K on W.bkinfoid = K.id ";
		sql = sql+" left join dbo.BS_BookCatalog Z on K.bkcatalogid =Z.ID ";
        sql = sql+" left join sys_printtitle U on D.id=U.stgid";
        sql = sql+" where A.id in("+ID+") order by A.WsaleNtCodeStr ";
	   /*
          if (!pixiaoortuihuo) {
          sql = sql + " group by U.wsprinttitle+'发货退货单' ,U.wscontact,U.wstel,U.wsaddress,U.wsprintbk,";
    }else  sql = sql + " group by U.wsprinttitle+'发货单' ,U.wscontact,U.wstel,U.wsaddress,U.wsprintbk,";


        sql = sql + "  A.WsaleNtCodeStr ,  A.hdtime,A.totalamount,A.fixedprice,A.discountedprice,";
        sql = sql + " A.addcosts,  C.name  ,Z.id ,Z.name ,Z.price,Z.isbn,A.remarks,BS_WsaleNote.amount ";
       */queryA5->Close();
       queryA5->SQL->Clear();
	   queryA5->SQL->Add(sql);
       queryA5->Open();

        ps = ExtractFilePath(Application->ExeName) +"wsaleA5.fr3";

        frxReportA5->LoadFromFile(ps);

        frxReportA5->PrepareReport(true);
        frxReportA5->PrintOptions->ShowDialog = false;
       frxReportA5->Print();
	   // frxReportA5->ShowPreparedReport();
        }catch(...)
        {


        }

    }else //
    {


       for (int i=0; i < IDStr->Count; i++) {


            if ((IDStr->Strings[i]!="-1")&&(IDStr->Strings[i]!="")) {




						aqmuilprinthead->Active = false;
                        aqmuilprinthead->Parameters->ParamByName("id")->Value = StrToInt(IDStr->Strings[i]);
                        aqmuilprinthead->Active = true;

						AnsiString sql = "select  a.amount amount,c.price,c.name,a.discount discount,DiscountedPrice from dbo.BS_WsaleNote a  join stk_bookinfo b on a.bkinfoid=b.id left join dbo.BS_BookCatalog c on b.bkcatalogid = c.id ";
                        sql = sql +"  where a.WsaleNtHeaderID="+aqmuilprinthead->FieldByName("id")->AsAnsiString;

						if (pixiaoortuihuo) {
                       // sql = sql +" and a.amount >=0 ";
                        }else
						{
                        sql = sql +" and a.amount <=0 ";
                        }
						//sql = sql + "  group by a.BkcatalogID,b.price,b.name";
                        aqmuildetail->Close();
                        aqmuildetail->SQL->Clear();
                        aqmuildetail->SQL->Add(sql);
                        aqmuildetail->Open();

                        AnsiString psyizhang;
                        if (xiaopiao) {
							ps = ExtractFilePath(Application->ExeName) +"wsalexiaopiao.fr3";
                        } else
                         ps = ExtractFilePath(Application->ExeName) +"wsaleA5danda.fr3";
                         psyizhang  = ExtractFilePath(Application->ExeName) +"wsaleA5dandayizhang.fr3";
                frxWsalemuilprint->LoadFromFile(ps);    //计算分页

                frxWsalemuilprint->PrepareReport(true);


                if (frxWsalemuilprint->Engine->TotalPages==1) {//如果超过1衣开始分页打印
                     frxWsalemuilprint->Clear();
                    frxWsalemuilprint->LoadFromFile(psyizhang);

				frxWsalemuilprint->PrepareReport(true);
                }
	   if (type == 0) {          //
			frxWsalemuilprint->PrintOptions->ShowDialog = false;
		       	frxWsalemuilprint->Print();
                      //frxWsalemuilprint->ShowPreparedReport();
		}
		else
		{
			frxWsalemuilprint->ShowPreparedReport();
		}
            }
    }
	}





}
//---------------------------------------------------------------------------


void __fastcall Tfrmwsaleprinta::frxWsalemuilprintGetValue(const UnicodeString VarName,
          Variant &Value)
{
 	if (CompareText(VarName,"\"Title\"")==0 ) {
        if (tuihuo==1) {
              Value = printtitle+"发货退货单";
        }else  Value = printtitle+"发货单";

	}
        if (CompareText(VarName,"\"TotalAmount\"")==0 ) {
        Value = aqmuilprinthead->FieldByName("totalamount")->AsAnsiString;
        }
        if (CompareText(VarName,"\"TotalM\"")==0 ) {
        Value = aqmuilprinthead->FieldByName("fixedprice")->AsAnsiString ;
        }
         if (CompareText(VarName,"\"TotalS\"")==0 ) {
        Value = aqmuilprinthead->FieldByName("discountedprice")->AsAnsiString ;;
        }
        if (CompareText(VarName,"\"Contact\"")==0 ) {
        Value = contact;
        }
        if (CompareText(VarName,"\"Tel\"")==0 ) {
        Value = tel;
        }
        if (CompareText(VarName,"\"Address\"")==0 ) {
        Value = address;
        }
          if (CompareText(VarName,"\"bk\"")==0 ) {
        Value = pxbk+aqmuilprinthead->FieldByName("remarks")->AsAnsiString;
        }
        if (CompareText(VarName,"\"addcosts\"")==0 ) {
        Value = aqmuilprinthead->FieldByName("addcosts")->AsAnsiString ;;
        }
         if (CompareText(VarName,"\"Totalyingshou\"")==0 ) {
        Value = FloatToStr(aqmuilprinthead->FieldByName("discountedprice")->AsFloat+aqmuilprinthead->FieldByName("addcosts")->AsFloat);
        }
}
//---------------------------------------------------------------------------
void Tfrmwsaleprinta::xiaopiaoliandaprint(AnsiString ID,boolean isprint)
{
     AnsiString sql,ps;
	sql="exec C_Getxiaopiao :ID";
		adoxiaopiao->Close();
			adoxiaopiao->SQL->Clear();
		adoxiaopiao->SQL->Add(sql);
		adoxiaopiao->Parameters->ParamByName("ID")->Value=ID;
		adoxiaopiao->Open();


		ps = ExtractFilePath(Application->ExeName) + "wsalexiaopiao.fr3";
		frxreportjianhuo->LoadFromFile(ps);
		frxreportjianhuo->PrepareReport(true);
		if (isprint) {
			frxreportjianhuo->PrintOptions->ShowDialog = false;
			frxreportjianhuo->Print();
		}
		else
		{
			frxreportjianhuo->ShowPreparedReport();
		}




}

