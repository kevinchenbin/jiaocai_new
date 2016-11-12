//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>



#include "WarnStockForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpBase"
#pragma link "RpSystem"
#pragma link "RpRender"
#pragma link "RpRenderCanvas"
#pragma link "RpRenderPreview"
#pragma link "MDIChild"
#pragma resource "*.dfm"
TfrmWarnStock *frmWarnStock;
//---------------------------------------------------------------------------
__fastcall TfrmWarnStock::TfrmWarnStock(TComponent* Owner)
	: TfrmMDIChild(Owner)
{    m_module = MTStore;
}
//---------------------------------------------------------------------------
void TfrmWarnStock::Init(TApplication* app, TADOConnection* con)
{

        TfrmMDIChild::Init(app, con);
 dsWarnStock->Connection=con;
		qryName->Connection=con;
		qrySupply->Connection=con;
		cmdSetWarn->Connection=con;

		con1=con;

		this->Caption="库存预警";

}
void __fastcall TfrmWarnStock::FormClose(TObject *Sender, TCloseAction &Action)
{
	 qryName->Close();
	 qrySupply->Close();
	  dsWarnStock->Active=false;


	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWarnStock::RzToolButton3Click(TObject *Sender)
{
		   Close();
}
//---------------------------------------------------------------------------



void __fastcall TfrmWarnStock::RzToolButton5Click(TObject *Sender)
{
	edtnum1->ReadOnly=false;
	RzNumericEdit1->ReadOnly=false;
	cbbType->SetFocus();

	if (dsWarnStock->Active)
	{
		dsWarnStock->Active = false;
	}
		String   sql1;
	sql1 = "select STK_BookInfo.id,ISBN,BS_BookCatalog.Name as BookName,Price,Amount,MaxStock,MinStock,Barcode,BS_BookType.Name as TypeName,CUST_CustomerInfo.Name as SupplyName from STK_BookInfo  left join STK_BookstackInfo on BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join BS_BookType on BS_BookType.id=smallBookTypeID left join CUST_CustomerInfo on CUST_CustomerInfo.id=SupplierID where CUST_CustomerInfo.Type=1  and Amount>0 ";
	dsWarnStock->CommandText = sql1;
	dsWarnStock->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWarnStock::cbbTypeSelect(TObject *Sender)
{
	   if (cbbType->Text=="类别")
		{      RzEdtInfor->Visible=false;
               cbb1->Visible=true;
			qryName->SQL->Add("select Name from BS_BookType where id>1");
			qryName->Open();
			qryName->First();
              cbb1->Clear();
			 while (!qryName->Eof)
			 {
			cbb1->Items->Add(qryName->FieldByName("Name")->AsString);
			qryName->Next();
			 }
			 qryName->Close();
			cbb1->SetFocus();
	   }
	   else
	   {
			RzEdtInfor->Visible=true;
			cbb1->Visible=false;
			RzEdtInfor->SetFocus();
	   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmWarnStock::RzToolButton1Click(TObject *Sender)
{
			  lbl3->Visible=true;
			  cbbSupply->Visible=true;
			  chk1->Visible=true;
			  chk2->Visible=true;
			  btn2->Visible=true;

			qrySupply->SQL->Add("select Name from CUST_CustomerInfo where Type=1");
			qrySupply->Open();
			qrySupply->First();
			   cbbSupply->Clear();
			 while (!qrySupply->Eof)
			 {
				cbbSupply->Items->Add(qrySupply->FieldByName("Name")->AsString);
				qrySupply->Next();
			 }
		 qrySupply->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWarnStock::RzEdtInforKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN&&RzEdtInfor->Text!="")
	 {
		  String sql;
			if (dsWarnStock->Active)
			{
			dsWarnStock->Active = false;
			}
		 if (cbbType->Text=="条码") {
			  sql="select STK_BookInfo.id,ISBN,BS_BookCatalog.Name as BookName,Price,Amount,MaxStock,MinStock,Barcode,BS_BookType.Name as TypeName,CUST_CustomerInfo.Name as SupplyName from STK_BookInfo  left join STK_BookstackInfo on BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join BS_BookType on BS_BookType.id=smallBookTypeID left join CUST_CustomerInfo on CUST_CustomerInfo.id=SupplierID where CUST_CustomerInfo.Type=1  and Amount>0 and Barcode like '%"+RzEdtInfor->Text+"%'";
			 }
		 else if (cbbType->Text=="书名") {
			  sql="select STK_BookInfo.id,ISBN,BS_BookCatalog.Name as BookName,Price,Amount,MaxStock,MinStock,Barcode,BS_BookType.Name as TypeName,CUST_CustomerInfo.Name as SupplyName from STK_BookInfo  left join STK_BookstackInfo on BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join BS_BookType on BS_BookType.id=smallBookTypeID left join CUST_CustomerInfo on CUST_CustomerInfo.id=SupplierID where CUST_CustomerInfo.Type=1  and Amount>0 and BS_BookCatalog.Name like '%"+RzEdtInfor->Text+"%'";
			  }
		 else if (cbbType->Text=="ISBN") {
			  sql="select STK_BookInfo.id,ISBN,BS_BookCatalog.Name as BookName,Price,Amount,MaxStock,MinStock,Barcode,BS_BookType.Name as TypeName,CUST_CustomerInfo.Name as SupplyName from STK_BookInfo  left join STK_BookstackInfo on BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join BS_BookType on BS_BookType.id=smallBookTypeID left join CUST_CustomerInfo on CUST_CustomerInfo.id=SupplierID where CUST_CustomerInfo.Type=1  and Amount>0 and ISBN like '%"+RzEdtInfor->Text+"%'";
			  }
		 else
		   {
			 sql="select STK_BookInfo.id,ISBN,BS_BookCatalog.Name as BookName,Price,Amount,MaxStock,MinStock,Barcode,BS_BookType.Name as TypeName,CUST_CustomerInfo.Name as SupplyName from STK_BookInfo  left join STK_BookstackInfo on BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join BS_BookType on BS_BookType.id=smallBookTypeID left join CUST_CustomerInfo on CUST_CustomerInfo.id=SupplierID where CUST_CustomerInfo.Type=1 and Amount>0 ";
		   }
		 dsWarnStock->CommandText = sql;
		 dsWarnStock->Active = true;

      edtnum1->SetFocus();
//      this->RzToolButton5->Click();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmWarnStock::cbb1Select(TObject *Sender)
{
	if (dsWarnStock->Active)
		{
		dsWarnStock->Active = false;
		}
	   String sql="select STK_BookInfo.id,ISBN,BS_BookCatalog.Name as BookName,Price,Amount,MaxStock,MinStock,Barcode,BS_BookType.Name as TypeName,CUST_CustomerInfo.Name as SupplyName from STK_BookInfo  left join STK_BookstackInfo on BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join BS_BookType on BS_BookType.id=smallBookTypeID left join CUST_CustomerInfo on CUST_CustomerInfo.id=SupplierID where CUST_CustomerInfo.Type=1 and Amount>0 and BS_BookType.Name like '%"+cbb1->Text+"%'";

	dsWarnStock->CommandText = sql;
	dsWarnStock->Active = true;
     edtnum1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWarnStock::cbbSupplySelect(TObject *Sender)
{
 
	chk1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWarnStock::btn1Click(TObject *Sender)
{

	   if (edtnum1->Value>0&&RzNumericEdit1->Value>=0&&!dsWarnStock->Eof) {
				 if (edtnum1->Value>RzNumericEdit1->Value)
				 {

						   String sql,max,min;
						   max=IntToStr(edtnum1->IntValue);
						   min=IntToStr(RzNumericEdit1->IntValue);


						  if (rb1->Checked==true) {
							 if(MessageDlg("您确认设置以下所有的预警上限："+max+"预警下限为："+min+"吗？", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
								{

								  dsWarnStock->First();
									 while (!dsWarnStock->Eof){

									sql="update STK_BookInfo set MaxStock="+max+",MinStock="+min+" where id="+dsWarnStock->FieldByName("id")->AsString;
									  cmdSetWarn->CommandText = sql;
									cmdSetWarn->Execute();
									 dsWarnStock->Next();

									 }

							  }

						  }
						  else
						   {
									 if(MessageDlg("您确认设置:"+dsWarnStock->FieldByName("BookName")->AsString+"的预警上限："+max+"预警下限为："+min+"吗？", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )

								  {

									sql="update STK_BookInfo set MaxStock="+max+",MinStock="+min+" where id="+dsWarnStock->FieldByName("id")->AsString;
									cmdSetWarn->CommandText = sql;
									cmdSetWarn->Execute();
								  }
						  }
						   rb1->Checked=false;
						  cbbType->SetFocus();
						  if (cbbType->Text=="选择类型") {
                                    this->RzToolButton5->Click();
						  }  else if (cbbType->Text!="类别") {
								this->RzEdtInfor->OnKeyPress;
						  }
						  else
						  {this->cbb1->OnSelect;}

						  RzEdtInfor->Clear();
						  edtnum1->Clear();
						  RzNumericEdit1->Clear();


				 }
				 else
				 { ShowMessage("预警上限不能小于预警下限！请检查！");}

  }
  else
   {
		 ShowMessage("请正确输入，预警上限和预警下限不能小于0！请检查！");
		edtnum1->SetFocus();
   }



}
//---------------------------------------------------------------------------

void __fastcall TfrmWarnStock::btn2Click(TObject *Sender)
{
	   String sql;
       if (dsWarnStock->Active)
		{
		dsWarnStock->Active = false;
		}
	   if (chk1->Checked==false) {
		   if (chk2->Checked==false) {
			   ShowMessage("请选择条件!");
			   sql="";
		   }
		   else
		   {   sql="select STK_BookInfo.id,ISBN,BS_BookCatalog.Name as BookName,Price,Amount,MaxStock,MinStock,Barcode,BS_BookType.Name as TypeName,CUST_CustomerInfo.Name as SupplyName from STK_BookInfo  left join STK_BookstackInfo on BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join BS_BookType on BS_BookType.id=smallBookTypeID left join CUST_CustomerInfo on CUST_CustomerInfo.id=SupplierID where CUST_CustomerInfo.Type=1  and Amount>0 and Amount<MinStock and CUST_CustomerInfo.Name='"+cbbSupply->Text+"'";
               		dsWarnStock->CommandText = sql;
				dsWarnStock->Active = true;

			}



	   }
	   else  if (chk2->Checked==false) {
				   sql="select STK_BookInfo.id,ISBN,BS_BookCatalog.Name as BookName,Price,Amount,MaxStock,MinStock,Barcode,BS_BookType.Name as TypeName,CUST_CustomerInfo.Name as SupplyName from STK_BookInfo  left join STK_BookstackInfo on BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join BS_BookType on BS_BookType.id=smallBookTypeID left join CUST_CustomerInfo on CUST_CustomerInfo.id=SupplierID where CUST_CustomerInfo.Type=1  and Amount>0 and Amount>MaxStock and CUST_CustomerInfo.Name='"+cbbSupply->Text+"'";
              		dsWarnStock->CommandText = sql;
				dsWarnStock->Active = true;

		   }
		   else
		   {  sql="select STK_BookInfo.id,ISBN,BS_BookCatalog.Name as BookName,Price,Amount,MaxStock,MinStock,Barcode,BS_BookType.Name as TypeName,CUST_CustomerInfo.Name as SupplyName from STK_BookInfo  left join STK_BookstackInfo on BkstackID=STK_BookstackInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo on PressID=BS_PressInfo.id left join BS_BookType on BS_BookType.id=smallBookTypeID left join CUST_CustomerInfo on CUST_CustomerInfo.id=SupplierID where CUST_CustomerInfo.Type=1 and Amount>0  and (Amount>MaxStock or Amount<MinStock) and CUST_CustomerInfo.Name='"+cbbSupply->Text+"'";
                		dsWarnStock->CommandText = sql;
					dsWarnStock->Active = true;

		   }


}
//---------------------------------------------------------------------------

void __fastcall TfrmWarnStock::edtnum1KeyPress(TObject *Sender, wchar_t &Key)
{
		     if (Key==VK_RETURN) //
	{
			 RzNumericEdit1->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWarnStock::RzNumericEdit1KeyPress(TObject *Sender, wchar_t &Key)

{
	   		     if (Key==VK_RETURN) //
	{

			 rb1->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWarnStock::rb1Click(TObject *Sender)
{
	  btn1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWarnStock::chk1Click(TObject *Sender)
{
	  chk2->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWarnStock::chk2Click(TObject *Sender)
{
	btn2->SetFocus();
}
//---------------------------------------------------------------------------











void __fastcall TfrmWarnStock::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{       		if (Key==0x1B) {   //esc
			this->RzToolButton3->Click();

		}

			if (Shift.Contains(ssCtrl)&&Key==65) {   //A
			this->RzToolButton5->Click();

		}
            		if (Shift.Contains(ssCtrl)&&Key==81) {   //Q
			this->RzToolButton1->Click();

		}
}
//---------------------------------------------------------------------------

