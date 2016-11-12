//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitCNetOrder.h"
#include "Unitcorderfind.h"
#include "bookQuery.h"
#include "bookhistory.h"
#include "Unitgenhuanselect.h"
#include "NewBookModify.h"
#include "Addsyslog.h"
#include <IdURI.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma resource "*.dfm"
TfrmCNetOrder *frmCNetOrder;
//---------------------------------------------------------------------------
__fastcall TfrmCNetOrder::TfrmCNetOrder(TComponent* Owner)
	: TForm(Owner)
{
  DBGrid1->OnDrawColumnCell=DBGrid1DrawColumnCell;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCNetOrder::BtnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCNetOrder::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCNetOrder::BtnView1Click(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,fcon,StgID);
	frm->ShowModal();
	delete frm;
}
void TfrmCNetOrder::RefashHead(AnsiString wheres)
{
  AnsiString sql;
  sql="select *,nullif(dotime,'') yjdotime,discountedprice-paynum as jiacha from dbo.C_BS_OrderNoteHeader "+wheres;
  aqhd->Close();
  aqhd->SQL->Clear();
  aqhd->SQL->Add(sql);
  aqhd->Open();
}
void TfrmCNetOrder::RefashOrderDetail(int HeaderID)
{
	AnsiString sql;
	sql=" select row_number() over (order by corderid) as xuhao,* from dbo.C_Order_Detail where OrderNtHeaderID= "+IntToStr(HeaderID);

	aqdetail->Close();
	aqdetail->SQL->Clear();
	aqdetail->SQL->Add(sql);
	aqdetail->Open();

	if (DBEdit5->Text=="已出库") {
	   DBGrid1->ReadOnly=true;
	}else  DBGrid1->ReadOnly=false;

}
void TfrmCNetOrder::init(LandInfo* li)
{
	UserID = li->userID ;
	UserName =  li->UserName ;
	StgID = li->storageID ;
	fcon = li->con ;
	aqhd->Connection = li->con;
	aqdetail->Connection=li->con;
	aquery->Connection = li->con;
	sp->Connection=li->con;
	spexec->Connection=li->con;

}
//---------------------------------------------------------------------------
void __fastcall TfrmCNetOrder::BtnViewClick(TObject *Sender)
{
   //
   Tfrmcorderfind * frm = new Tfrmcorderfind(Application,fcon,StgID,UserID);

	if (frm->ShowModal()==mrOk )
	{
		AnsiString code = frm->GetSelectDH();
		   AnsiString sqlwhere = frm->GetWhere();
		   AnsiString sql;
		   sql ="select *,nullif(dotime,'') yjdotime ,discountedprice-paynum as jiacha from C_OrderHeader  ";

			  aqhd->Close();
			  aqhd->SQL->Clear();
			  aqhd->SQL->Add(sql+sqlwhere);
			  aqhd->Open();


		   TLocateOptions Opts;
			Opts.Clear();
			Opts << loPartialKey;
		   if(aqhd->Locate("OrderNtCode", Variant(code), Opts))
		   {
			RefashOrderDetail(aqhd->FieldByName("ID")->AsInteger );
		   }else
		   {

			 MessageBoxA(0,"查询结果为空！","提示",MB_ICONWARNING);
		   }



	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCNetOrder::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCNetOrder::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	//不满足库存的，显示为红色
		  //可用库存+锁定数量小于订单数量, 则显示为红色
	if ( (aqdetail->FieldByName("kykc")->AsInteger+aqdetail->FieldByName("locknum")->AsInteger<aqdetail->FieldByName("amount")->AsInteger)&&(DBEdit5->Text!="已出库")) {
		DBGrid1->Canvas->FillRect(Rect);
	   //	DBGrid1->Canvas->Font->Color  = clRed;
		DBGrid1->Canvas->Font->Style = TFontStyles()<<fsBold;
		DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmCNetOrder::DBGrid1CellClick(TColumn *Column)
{
   editbackinfo->Text=aqdetail->FieldByName("Orderdetailbk")->AsAnsiString;
   editclient->Text=aqdetail->FieldByName("backInfo")->AsAnsiString;



}
//---------------------------------------------------------------------------

void __fastcall TfrmCNetOrder::DBMemo1Change(TObject *Sender)
{
   if (DBMemo1->Text!="") {


   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCNetOrder::DBMemo1KeyPress(TObject *Sender, wchar_t &Key)
{
  if  (Key == '\r') {
  if (!aqdetail->IsEmpty()) {
	aqhd->Edit();
	 aqhd->FieldByName("Remarks")->AsAnsiString=DBMemo1->Text;
	 aqhd->Post();
	 //同步订单备注
	 String st;
	 String strEncode;
	 if (DBMemo1->Text!="") {
	  strEncode = TIdURI::PathEncode(DBMemo1->Text);
	 spexec->ProcedureName="C_synOrderRemark";
	 spexec->Parameters->Refresh();
	 spexec->Parameters->ParamByName("@remark")->Value=strEncode;
	 spexec->Parameters->ParamByName("@ordernum")->Value=Trim(DBEdit1->Text);
	 spexec->ExecProc();
	 }


  }
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCNetOrder::DBNavigator1Click(TObject *Sender, TNavigateBtn Button)

{
   //
   	RefashOrderDetail(aqhd->FieldByName("ID")->AsInteger );
}
//---------------------------------------------------------------------------


void __fastcall TfrmCNetOrder::editclientKeyPress(TObject *Sender, wchar_t &Key)
{
if (Key == VK_RETURN) {
		if (aqdetail->IsEmpty() ) {
			return;
		}
	 try
	 {

	 sp->ProcedureName="C_UpdateCOrderbk";
	 sp->Parameters->Refresh();
	 sp->Parameters->ParamByName("@catalogbk")->Value="";
	 sp->Parameters->ParamByName("@clientbk")->Value=Trim(editclient->Text);
	 sp->Parameters->ParamByName("@corderid")->Value=aqdetail->FieldByName("corderid")->AsInteger;
	 sp->ExecProc();
	 RefashOrderDetail(aqhd->FieldByName("ID")->AsInteger );
	 }
	 catch (Exception &E) {
												//+AnsiString(E.Message)
			MessageBox(Handle,"订单回告失败!详细信息","同步提示",MB_ICONWARNING);
		}

}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCNetOrder::editbackinfoKeyPress(TObject *Sender, wchar_t &Key)
{
 if (Key == VK_RETURN) {
		if (aqdetail->IsEmpty() ) {
			return;
		}
	 try
	 {

	 sp->ProcedureName="C_UpdateCOrderbk";
	 sp->Parameters->Refresh();
	 sp->Parameters->ParamByName("@catalogbk")->Value=Trim(editbackinfo->Text);
	 sp->Parameters->ParamByName("@clientbk")->Value="";
	 sp->Parameters->ParamByName("@corderid")->Value=aqdetail->FieldByName("corderid")->AsInteger;
	 sp->ExecProc();
	 RefashOrderDetail(aqhd->FieldByName("ID")->AsInteger );
	 }
	 catch (Exception &E) {
												//+AnsiString(E.Message)
			MessageBox(Handle,"订单回告失败!详细信息","同步提示",MB_ICONWARNING);
		}

}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCNetOrder::N14Click(TObject *Sender)
{
  //
	if (aqdetail->IsEmpty() ) {
        return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,fcon,StgID,aqdetail->FieldByName("bookid")->AsInteger,UserID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------


void __fastcall TfrmCNetOrder::BtnExportClick(TObject *Sender)
{
  AnsiString st;
 if (MessageBoxA(0,"确认要取消订单吗？","提示",MB_ICONQUESTION)==1) {
 if (DBEdit1->Text !="") {


	  sp->ProcedureName="C_Invok_ChangeStatus";
	 sp->Parameters->Refresh();
	 sp->Parameters->ParamByName("@Order")->Value=DBEdit1->Text;
	 sp->Parameters->ParamByName("@state")->Value=5;
	 sp->Parameters->ParamByName("@rsponse")->Value="";
	 sp->ExecProc();
	st = sp->Parameters->ParamByName("@rsponse")->Value;
	if (st=="ok") {
	   MessageBox(Handle,"订单状态同步成功!","同步提示",MB_ICONWARNING);
	}else
	{
	  MessageBox(Handle,"订单状态同步失败!","同步提示",MB_ICONWARNING);

	}
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCNetOrder::N2Click(TObject *Sender)
{
//更换书目
int newcatalogid;
AnsiString strEncode;
newcatalogid=-1;
	if (aqdetail->IsEmpty() ) {
		return;
	}
	else
	{
		if (aqdetail->FieldByName("locknum")->AsInteger > 0 ) {
			if(MessageBoxA(0,"该书有库存锁定数量，是否继续更换？","提示",MB_ICONQUESTION|MB_OKCANCEL)!=1)
			{
				return;
			}
		}
         	AnsiString sql;
		int newcatalogid = -1;
		sql = "select BS_BookCatalog.ID,ISBN,Name,UserDefCode,Price,PressCount,Author,AbbreviatedName from BS_BookCatalog left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id where BS_BookCatalog.Name like '%" + aqdetail->FieldByName("name")->AsString + "%' and AbbreviatedName = '" + aqdetail->FieldByName("press")->AsString + "'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();

       	if (aquery->RecordCount > 1) {
			Tfrmchangeselect *frm = new Tfrmchangeselect(Application,aquery);
			if (frm->ShowModal() == mrOk  ) {
				if (frm->continuechange == 1) {
					delete frm;
					TfrmNewBookModify * frm1 = new TfrmNewBookModify(Application,fcon,aqdetail->FieldByName("bookid")->AsInteger,StgID,UserID);
					frm1->newbook = 1;
					if (frm1->ShowModal() == mrOk) {
						newcatalogid = frm1->newcatalogid ;
					}
					delete frm1;
				}
				else
				{
					newcatalogid = aquery->FieldByName("ID")->AsInteger ;
					delete frm;
				}
			}
			else
			{
				delete frm;
			}
		}

		else
		{
			TfrmNewBookModify * frm2 = new TfrmNewBookModify(Application,fcon,aqdetail->FieldByName("bookid")->AsInteger,StgID,UserID);
			frm2->newbook = 1;
			if (frm2->ShowModal() == mrOk) {
				newcatalogid = frm2->newcatalogid ;
			}
			delete frm2;
		}

		if (newcatalogid > -1) {
			AnsiString ss;             //Press //PressCount price
			ss = aqdetail->FieldByName("name")->AsString+" 定价:"+aqdetail->FieldByName("price")->AsString+" 版别:"+aqdetail->FieldByName("Press")->AsString ;
		   ss=ss+"  版次:" +aqdetail->FieldByName("PressCount")->AsString;
		   //	sql = "该书由《"+ss+"》更换而来 " ;


		  /*	sql = "select price from bs_bookcatalog where id = " + IntToStr(newcatalogid);
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			float yprice = query->FieldByName("price")->AsFloat ;

			if (aqdetail->FieldByName("cgid")->AsString !="" ) {
				if(MessageBoxA(0,"该书已经做过采购，是否重新采购？","提示",MB_ICONQUESTION|MB_OKCANCEL)==1)
				{
					sql = "insert into BS_OrderNote(OrderNtHeaderID,Amount,Discount,FixedPrice,DiscountedPrice,SendAmount,UnsendAmount,BkcatalogID,bk,yprice) select OrderNtHeaderID,Amount,Discount,FixedPrice,DiscountedPrice,SendAmount,UnsendAmount," + IntToStr(newcatalogid) + ",'由《" + aqorderdetail->FieldByName("bookname")->AsString + "》换书而来'," + FloatToStr(yprice) + " from BS_OrderNote where id = " + aqorderdetail->FieldByName("id")->AsString ;
				}
				else
				{
					sql = "insert into BS_OrderNote(OrderNtHeaderID,Amount,Discount,FixedPrice,DiscountedPrice,SendAmount,UnsendAmount,needprocurenum,BkcatalogID,bk,yprice) select OrderNtHeaderID,Amount,Discount,FixedPrice,DiscountedPrice,SendAmount,UnsendAmount,needprocurenum," + IntToStr(newcatalogid) + ",'由《" + aqorderdetail->FieldByName("bookname")->AsString + "》换书而来'," + FloatToStr(yprice) + " from BS_OrderNote where id = " + aqorderdetail->FieldByName("id")->AsString ;
				}
			}  */
			sql="";
		 /*	TADOQuery *aq = new TADOQuery(this);
			aq->Connection = fcon;
			aq->Close();

			aq->SQL->Clear();
			aq->SQL->Add("exec C_changeBookidforC :orderid,:netbkcatalogid,:bk");
			aq->Parameters->ParamByName("orderid")->Value=aqdetail->FieldByName("corderid")->AsInteger;
			aq->Parameters->ParamByName("netbkcatalogid")->Value=newcatalogid;
			aq->Parameters->ParamByName("bk")->Value=ss;
			aq->ExecSQL() ;  */
			Screen->Cursor=crHourGlass;
	   strEncode = TIdURI::PathEncode(ss);
	 String st;
	 spexec->ProcedureName="C_changeBookidforC";
	 spexec->Parameters->Refresh();
	 spexec->Parameters->ParamByName("@orderid")->Value=aqdetail->FieldByName("corderid")->AsInteger;;
	 spexec->Parameters->ParamByName("@orderHeaderCode")->Value=Trim(DBEdit1->Text);

	 spexec->Parameters->ParamByName("@netbkcatalogid")->Value=newcatalogid;
	 spexec->Parameters->ParamByName("@bk")->Value=ss;
	 spexec->Parameters->ParamByName("@zmbk")->Value=strEncode;
	 spexec->Parameters->ParamByName("@respon")->Value="";
	 spexec->ExecProc();
	 st = spexec->Parameters->ParamByName("@respon")->Value;

	if (st=="ok") {
		MessageBox(Handle,"替换书目同步成功!","同步提示",MB_ICONWARNING);
		String	logmessage = "更换订单" + DBEdit1->Text + "书目《" + ss + "》为《" + aqdetail->FieldByName("name")->AsString + "》";
			AddEvent(1,"一般订单窗口",UserID,StgID,logmessage,fcon);
          //  MessageBox(Handle,"更换完成!","提示",MB_ICONWARNING);
			RefashOrderDetail(aqhd->FieldByName("ID")->AsInteger );

	}else
	{
	   AnsiString Errorinfo;
		Errorinfo="替换书目同步失败!"+st;
		MessageBox(Handle,Errorinfo.c_str(),"同步提示",MB_ICONWARNING);

	}

   Screen->Cursor=crDefault;


			//RefreshDetail();
		 //	RefashHead(" where OrderNtCode ='"+DBEdit1->Text+"'");



		}





    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCNetOrder::N4Click(TObject *Sender)
{
String logmessage,bookinfo;
	if(MessageBoxA(0,"确定要删除此书目吗？","提示",MB_ICONQUESTION|MB_OKCANCEL)!=2)
	{

	  int corderid  = aqdetail->FieldByName("corderid")->AsInteger;
	 bookinfo=aqdetail->FieldByName("name")->AsAnsiString+"版别"+ aqdetail->FieldByName("press")->AsAnsiString;
	 bookinfo=bookinfo+"定价:"+aqdetail->FieldByName("price")->AsAnsiString+"作者:"+ aqdetail->FieldByName("Author")->AsAnsiString;
	  // 	sql="";
		  /*	TADOQuery *aq = new TADOQuery(this);
			aq->Connection = fcon;
			aq->Close();

			aq->SQL->Clear();
			aq->SQL->Add("delete C_BS_OrderNote where id =:id ");
			aq->Parameters->ParamByName("id")->Value=corderid ;

			aq->ExecSQL() ;

			delete aq; */
	  Screen->Cursor=crHourGlass;

			 String st;
	 spexec->ProcedureName="C_AddDelSyncCOrderDetail";
	 spexec->Parameters->Refresh();
	// spexec->Parameters->ParamByName("@orderid")->Value=aqdetail->FieldByName("corderid")->AsInteger;;
	 spexec->Parameters->ParamByName("@OrderNtCode")->Value=Trim(DBEdit1->Text);

	 spexec->Parameters->ParamByName("@atype")->Value=2;
	 spexec->Parameters->ParamByName("@newcatalogid")->Value=corderid;
	 spexec->Parameters->ParamByName("@amount")->Value=0;
	 spexec->Parameters->ParamByName("@backinfo")->Value="";
	spexec->Parameters->ParamByName("@backinfo")->Value="";
	 spexec->ExecProc();
	 st = spexec->Parameters->ParamByName("@backinfo")->Value;

	if (st=="删除成功!") {
			logmessage = "删除C网订单" + DBEdit1->Text + "书目:" + bookinfo ;
		AddEvent(1,"一般订单窗口",UserID,StgID,logmessage,fcon);
		MessageBox(Handle,"删除书目同步成功!","同步提示",MB_ICONWARNING);
	}else
	{
	   AnsiString Errorinfo;
		Errorinfo="删除书目同步失败!"+st;
		MessageBox(Handle,Errorinfo.c_str(),"同步提示",MB_ICONWARNING);

	}
	Screen->Cursor=crDefault;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCNetOrder::pm1Popup(TObject *Sender)
{
  if( DBEdit5->Text=="已出库")
  {

	N14->Enabled =false;
	N4->Enabled =false;
	N2->Enabled =false;
  }else
  {

	N14->Enabled =true;
	N4->Enabled =true;
	N2->Enabled =true;


  }
}
//---------------------------------------------------------------------------

