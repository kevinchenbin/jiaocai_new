//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bsorder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBGrid"
#pragma link "RzRadChk"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "Chart"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma link "Series"
#pragma resource "*.dfm"
Tfrmorder *frmorder;
//---------------------------------------------------------------------------
__fastcall Tfrmorder::Tfrmorder(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
   fcon = con;
   dsp->Connection = con;
   aquery->Connection = con;
   acd->Connection  = con;
   aqdisplay->Connection = con;
   dtpstart->Date = Date();
   dtpend->Date = Date();
   TADOQuery *aq  = new TADOQuery(this);
   aq->Connection = con;
   AnsiString sql;

   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add("select * from sys_bsset where name ='xiaoshudian'");
   aq->Open();
   storageformat =  "￥" + aq->FieldByName("bk")->AsAnsiString ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add("select * from sys_bsset where name ='retailxiaoshudian'");
   aq->Open();
   retaiformat =  "￥" + aq->FieldByName("bk")->AsAnsiString ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
   aq->Open();
   saleformat =  "￥" + aq->FieldByName("bk")->AsAnsiString ;

   sql = "select ID,Name from SYS_StorageInfo";
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   while (!aq->Eof)
   {
		cbstorage->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
   }
   chstorage->Checked = true;
   cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)stgid);
   sql = "select Master from SYS_StorageInfo where id = " + IntToStr(stgid);
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   if (aq->FieldByName("Master")->AsBoolean ) {
	   chstorage->Enabled = true;
	   cbstorage->Enabled = true;
   }
   else
   {
		chstorage->Enabled = false;
		cbstorage->Enabled = false;
   }
   delete aq;

   //dg->Columns->Items[1]->DisplayFormat =  storageformat;
   dg->Columns->Items[2]->DisplayFormat =  storageformat;
   dg->Columns->Items[3]->DisplayFormat =  storageformat;
  // dg->Columns->Items[4]->DisplayFormat =  storageformat;
   dg->Columns->Items[5]->DisplayFormat =  storageformat;
   dg->Columns->Items[6]->DisplayFormat =  storageformat;
  // dg->Columns->Items[7]->DisplayFormat =  saleformat;
   dg->Columns->Items[8]->DisplayFormat =  saleformat;
   dg->Columns->Items[9]->DisplayFormat =  saleformat;
   //dg->Columns->Items[10]->DisplayFormat =  retaiformat;
   dg->Columns->Items[11]->DisplayFormat =  retaiformat;
   dg->Columns->Items[12]->DisplayFormat =  retaiformat;
   //dg->Columns->Items[1]->Footer->DisplayFormat =  storageformat;
   dg->Columns->Items[2]->Footer->DisplayFormat =  storageformat;
   dg->Columns->Items[3]->Footer->DisplayFormat =  storageformat;
   //dg->Columns->Items[4]->Footer->DisplayFormat =  storageformat;
   dg->Columns->Items[5]->Footer->DisplayFormat =  storageformat;
   dg->Columns->Items[6]->Footer->DisplayFormat =  storageformat;
   //dg->Columns->Items[7]->Footer->DisplayFormat =  saleformat;
   dg->Columns->Items[8]->Footer->DisplayFormat =  saleformat;
   dg->Columns->Items[9]->Footer->DisplayFormat =  saleformat;
   //dg->Columns->Items[10]->Footer->DisplayFormat =  retaiformat;
   dg->Columns->Items[11]->Footer->DisplayFormat =  retaiformat;
   dg->Columns->Items[12]->Footer->DisplayFormat =  retaiformat;
}

//---------------------------------------------------------------------------
void Tfrmorder::Query()

{
	AnsiString sql,title;
	sql = "exec USP_yewupaihang " + IntToStr(rgtype->ItemIndex) + ",";
	if (cbstart->Checked) {
		sql = sql + "'" + DateToStr(dtpstart->Date) + "',";
	}
	else
	{
		sql = sql + "NULL,";
	}
	if (cbend->Checked ) {
		sql = sql + "'" + DateToStr(dtpend->Date) + "',";
	}
	else
	{
		sql = sql + "NULL,";
	}
	if (chstorage->Checked) {
		int stgid;
		try {
			stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
		} catch (...) {
			MessageBox(0,"请选择正确的店号！","提示" ,MB_OK);
			return;
		}
		sql = sql + IntToStr(stgid);
	}
	else
	{
		sql = sql + "NULL";
	}
	if (senum->Text == "") {
    	MessageBox(0,"请输入正确的范围！","提示" ,MB_OK);
		return;
	}
	sql = sql + "," + senum->Text + "," + IntToStr(rgkind->ItemIndex) + "," + IntToStr(rgstyle->ItemIndex);
	aqdisplay->Close();
	aqdisplay->SQL->Clear();
	aqdisplay->SQL->Add(sql);
		dg->Columns->Items[0]->Field = NULL;
		dg->Columns->Items[1]->Field = NULL;
		dg->Columns->Items[2]->Field = NULL;
		dg->Columns->Items[3]->Field = NULL;
		dg->Columns->Items[4]->Field = NULL;
		dg->Columns->Items[5]->Field = NULL;
		dg->Columns->Items[6]->Field = NULL;
		dg->Columns->Items[7]->Field = NULL;
		dg->Columns->Items[8]->Field = NULL;
		dg->Columns->Items[9]->Field = NULL;
		dg->Columns->Items[10]->Field = NULL;
		dg->Columns->Items[11]->Field = NULL;
		dg->Columns->Items[12]->Field = NULL;
		dg->Columns->Items[1]->Footer->FieldName = "";
		dg->Columns->Items[2]->Footer->FieldName = "";
		dg->Columns->Items[3]->Footer->FieldName = "";
		dg->Columns->Items[4]->Footer->FieldName = "";
		dg->Columns->Items[5]->Footer->FieldName = "";
		dg->Columns->Items[6]->Footer->FieldName = "";
		dg->Columns->Items[7]->Footer->FieldName = "";
		dg->Columns->Items[8]->Footer->FieldName = "";
		dg->Columns->Items[9]->Footer->FieldName = "";
		dg->Columns->Items[10]->Footer->FieldName = "";
		dg->Columns->Items[11]->Footer->FieldName = "";
		dg->Columns->Items[12]->Footer->FieldName = "";
		dg->Columns->Items[1]->Footer->ValueType = fvtNon ;
		dg->Columns->Items[2]->Footer->ValueType = fvtNon ;
		dg->Columns->Items[3]->Footer->ValueType = fvtNon ;
		dg->Columns->Items[4]->Footer->ValueType = fvtNon ;
		dg->Columns->Items[5]->Footer->ValueType = fvtNon ;
		dg->Columns->Items[6]->Footer->ValueType = fvtNon ;
		dg->Columns->Items[7]->Footer->ValueType = fvtNon ;
		dg->Columns->Items[8]->Footer->ValueType = fvtNon ;
		dg->Columns->Items[9]->Footer->ValueType = fvtNon ;
		dg->Columns->Items[10]->Footer->ValueType = fvtNon ;
		dg->Columns->Items[11]->Footer->ValueType = fvtNon ;
		dg->Columns->Items[12]->Footer->ValueType = fvtNon ;
	aqdisplay->Open();
	switch (rgtype->ItemIndex) {
	case 0:
		if (rgviewstyle->ItemIndex == 0) {
			Chart1->Visible = false;
			dg->Visible = true;
			//dg->Columns->Items[0]->Field = aqdisplay->FieldByName("xuhao");
			dg->Columns->Items[0]->Field = aqdisplay->FieldByName("Name");
			dg->Columns->Items[1]->Field = aqdisplay->FieldByName("BookInfoAmount");
			dg->Columns->Items[2]->Field = aqdisplay->FieldByName("FixedPrice");
			dg->Columns->Items[3]->Field = aqdisplay->FieldByName("Discountprice");
			dg->Columns->Items[4]->Field = aqdisplay->FieldByName("StorgeAmount");
			dg->Columns->Items[5]->Field = aqdisplay->FieldByName("StorageFixedPrice");
			dg->Columns->Items[6]->Field = aqdisplay->FieldByName("StorageDscPrice");
			dg->Columns->Items[7]->Field = aqdisplay->FieldByName("WsaleAmount");
			dg->Columns->Items[8]->Field = aqdisplay->FieldByName("WsaleFixedPrice");
			dg->Columns->Items[9]->Field = aqdisplay->FieldByName("WsaleDscPrice");
			dg->Columns->Items[10]->Field = aqdisplay->FieldByName("RetailAmount");
			dg->Columns->Items[11]->Field = aqdisplay->FieldByName("RetailFixedPrice");
			dg->Columns->Items[12]->Field = aqdisplay->FieldByName("RetailDscPrice");
			dg->Columns->Items[1]->Footer->FieldName ="BookInfoAmount";
			dg->Columns->Items[2]->Footer->FieldName = "FixedPrice";
			dg->Columns->Items[3]->Footer->FieldName = "Discountprice";
			dg->Columns->Items[4]->Footer->FieldName = "StorgeAmount";
			dg->Columns->Items[5]->Footer->FieldName = "StorageFixedPrice";
			dg->Columns->Items[6]->Footer->FieldName = "StorageDscPrice";
			dg->Columns->Items[7]->Footer->FieldName = "WsaleAmount";
			dg->Columns->Items[8]->Footer->FieldName = "WsaleFixedPrice";
			dg->Columns->Items[9]->Footer->FieldName = "WsaleDscPrice";
			dg->Columns->Items[10]->Footer->FieldName = "RetailAmount";
			dg->Columns->Items[11]->Footer->FieldName = "RetailFixedPrice";
			dg->Columns->Items[12]->Footer->FieldName = "RetailDscPrice";
			dg->Columns->Items[1]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[2]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[3]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[4]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[5]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[6]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[7]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[8]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[9]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[10]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[11]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[12]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[0]->Visible = true;
			dg->Columns->Items[1]->Visible = true;
			dg->Columns->Items[2]->Visible = true;
			dg->Columns->Items[3]->Visible = true;
			dg->Columns->Items[4]->Visible = true;
			dg->Columns->Items[5]->Visible = true;
			dg->Columns->Items[6]->Visible = true;
			dg->Columns->Items[7]->Visible = true;
			dg->Columns->Items[8]->Visible = true;
			dg->Columns->Items[9]->Visible = true;
			dg->Columns->Items[10]->Visible = true;
			dg->Columns->Items[11]->Visible = true;
			dg->Columns->Items[12]->Visible = true;
		}
		else
		{
			Chart1->Visible = true;
			dg->Visible = false;
			aqdisplay->First();
			Chart1->Series[0]->Clear();
			switch (rgstyle->ItemIndex ) {
			case 0:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("BookInfoAmount")->AsFloat,aqdisplay->FieldByName("Name")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			case 1:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("StorgeAmount")->AsFloat,aqdisplay->FieldByName("Name")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			case 2:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("RetailAmount")->AsFloat,aqdisplay->FieldByName("Name")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			case 3:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("WsaleAmount")->AsFloat,aqdisplay->FieldByName("Name")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			default:
				;
			}
		}
	break;

	case 1:
		if (rgviewstyle->ItemIndex == 0) {
        	Chart1->Visible = false;
			dg->Visible = true;
			//dg->Columns->Items[0]->Field = aqdisplay->FieldByName("xuhao");
			dg->Columns->Items[0]->Field = aqdisplay->FieldByName("PressName");
			dg->Columns->Items[1]->Field = aqdisplay->FieldByName("BookInfoAmount");
			dg->Columns->Items[2]->Field = aqdisplay->FieldByName("FixedPrice");
			dg->Columns->Items[3]->Field = aqdisplay->FieldByName("Discountprice");
			dg->Columns->Items[4]->Field = aqdisplay->FieldByName("StorgeAmount");
			dg->Columns->Items[5]->Field = aqdisplay->FieldByName("StorageFixedPrice");
			dg->Columns->Items[6]->Field = aqdisplay->FieldByName("StorageDscPrice");
			dg->Columns->Items[7]->Field = aqdisplay->FieldByName("WsaleAmount");
			dg->Columns->Items[8]->Field = aqdisplay->FieldByName("WsaleFixedPrice");
			dg->Columns->Items[9]->Field = aqdisplay->FieldByName("WsaleDscPrice");
			dg->Columns->Items[10]->Field = aqdisplay->FieldByName("RetailAmount");
			dg->Columns->Items[11]->Field = aqdisplay->FieldByName("RetailFixedPrice");
			dg->Columns->Items[12]->Field = aqdisplay->FieldByName("RetailDscPrice");
			dg->Columns->Items[1]->Footer->FieldName ="BookInfoAmount";
			dg->Columns->Items[2]->Footer->FieldName = "FixedPrice";
			dg->Columns->Items[3]->Footer->FieldName = "Discountprice";
			dg->Columns->Items[4]->Footer->FieldName = "StorgeAmount";
			dg->Columns->Items[5]->Footer->FieldName = "StorageFixedPrice";
			dg->Columns->Items[6]->Footer->FieldName = "StorageDscPrice";
			dg->Columns->Items[7]->Footer->FieldName = "WsaleAmount";
			dg->Columns->Items[8]->Footer->FieldName = "WsaleFixedPrice";
			dg->Columns->Items[9]->Footer->FieldName = "WsaleDscPrice";
			dg->Columns->Items[10]->Footer->FieldName = "RetailAmount";
			dg->Columns->Items[11]->Footer->FieldName = "RetailFixedPrice";
			dg->Columns->Items[12]->Footer->FieldName = "RetailDscPrice";
			dg->Columns->Items[1]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[2]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[3]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[4]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[5]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[6]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[7]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[8]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[9]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[10]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[11]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[12]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[0]->Visible = true;
			dg->Columns->Items[1]->Visible = true;
			dg->Columns->Items[2]->Visible = true;
			dg->Columns->Items[3]->Visible = true;
			dg->Columns->Items[4]->Visible = true;
			dg->Columns->Items[5]->Visible = true;
			dg->Columns->Items[6]->Visible = true;
			dg->Columns->Items[7]->Visible = true;
			dg->Columns->Items[8]->Visible = true;
			dg->Columns->Items[9]->Visible = true;
			dg->Columns->Items[10]->Visible = true;
			dg->Columns->Items[11]->Visible = true;
			dg->Columns->Items[12]->Visible = true;
		}
		else
		{
			Chart1->Visible = true;
			dg->Visible = false;
			aqdisplay->First();
			Chart1->Series[0]->Clear();
			switch (rgstyle->ItemIndex ) {
			case 0:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("BookInfoAmount")->AsFloat,aqdisplay->FieldByName("PressName")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			case 1:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("StorgeAmount")->AsFloat,aqdisplay->FieldByName("PressName")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			case 2:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("RetailAmount")->AsFloat,aqdisplay->FieldByName("PressName")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			case 3:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("WsaleAmount")->AsFloat,aqdisplay->FieldByName("PressName")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			default:
				;
			}
		}
	break;

	case 2:
		if (rgviewstyle->ItemIndex == 0) {
			Chart1->Visible = false;
			dg->Visible = true;
			//dg->Columns->Items[0]->Field = aqdisplay->FieldByName("xuhao");
			dg->Columns->Items[0]->Field = aqdisplay->FieldByName("SupplierName");
			dg->Columns->Items[1]->Field = aqdisplay->FieldByName("BookInfoAmount");
			dg->Columns->Items[2]->Field = aqdisplay->FieldByName("FixedPrice");
			dg->Columns->Items[3]->Field = aqdisplay->FieldByName("Discountprice");
			dg->Columns->Items[4]->Field = aqdisplay->FieldByName("StorgeAmount");
			dg->Columns->Items[5]->Field = aqdisplay->FieldByName("StorageFixedPrice");
			dg->Columns->Items[6]->Field = aqdisplay->FieldByName("StorageDscPrice");
			dg->Columns->Items[7]->Field = aqdisplay->FieldByName("WsaleAmount");
			dg->Columns->Items[8]->Field = aqdisplay->FieldByName("WsaleFixedPrice");
			dg->Columns->Items[9]->Field = aqdisplay->FieldByName("WsaleDscPrice");
			dg->Columns->Items[10]->Field = aqdisplay->FieldByName("RetailAmount");
			dg->Columns->Items[11]->Field = aqdisplay->FieldByName("RetailFixedPrice");
			dg->Columns->Items[12]->Field = aqdisplay->FieldByName("RetailDscPrice");
			dg->Columns->Items[1]->Footer->FieldName ="BookInfoAmount";
			dg->Columns->Items[2]->Footer->FieldName = "FixedPrice";
			dg->Columns->Items[3]->Footer->FieldName = "Discountprice";
			dg->Columns->Items[4]->Footer->FieldName = "StorgeAmount";
			dg->Columns->Items[5]->Footer->FieldName = "StorageFixedPrice";
			dg->Columns->Items[6]->Footer->FieldName = "StorageDscPrice";
			dg->Columns->Items[7]->Footer->FieldName = "WsaleAmount";
			dg->Columns->Items[8]->Footer->FieldName = "WsaleFixedPrice";
			dg->Columns->Items[9]->Footer->FieldName = "WsaleDscPrice";
			dg->Columns->Items[10]->Footer->FieldName = "RetailAmount";
			dg->Columns->Items[11]->Footer->FieldName = "RetailFixedPrice";
			dg->Columns->Items[12]->Footer->FieldName = "RetailDscPrice";
			dg->Columns->Items[1]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[2]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[3]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[4]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[5]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[6]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[7]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[8]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[9]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[10]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[11]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[12]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[0]->Visible = true;
			dg->Columns->Items[1]->Visible = true;
			dg->Columns->Items[2]->Visible = true;
			dg->Columns->Items[3]->Visible = true;
			dg->Columns->Items[4]->Visible = true;
			dg->Columns->Items[5]->Visible = true;
			dg->Columns->Items[6]->Visible = true;
			dg->Columns->Items[7]->Visible = true;
			dg->Columns->Items[8]->Visible = true;
			dg->Columns->Items[9]->Visible = true;
			dg->Columns->Items[10]->Visible = true;
			dg->Columns->Items[11]->Visible = true;
			dg->Columns->Items[12]->Visible = true;
		}
		else
		{
			Chart1->Visible = true;
			dg->Visible = false;
			aqdisplay->First();
			Chart1->Series[0]->Clear();
			switch (rgstyle->ItemIndex ) {
			case 0:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("BookInfoAmount")->AsFloat,aqdisplay->FieldByName("SupplierName")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			case 1:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("StorgeAmount")->AsFloat,aqdisplay->FieldByName("SupplierName")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			case 2:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("RetailAmount")->AsFloat,aqdisplay->FieldByName("SupplierName")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			case 3:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("WsaleAmount")->AsFloat,aqdisplay->FieldByName("SupplierName")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			default:
				;
			}
		}
	break;

	case 3:
		if (rgviewstyle->ItemIndex == 0) {
			Chart1->Visible = false;
			dg->Visible = true;
			//dg->Columns->Items[0]->Field = aqdisplay->FieldByName("xuhao");
			dg->Columns->Items[0]->Field = aqdisplay->FieldByName("TypeName");
			dg->Columns->Items[1]->Field = aqdisplay->FieldByName("BookInfoAmount");
			dg->Columns->Items[2]->Field = aqdisplay->FieldByName("FixedPrice");
			dg->Columns->Items[3]->Field = aqdisplay->FieldByName("Discountprice");
			dg->Columns->Items[4]->Field = aqdisplay->FieldByName("StorgeAmount");
			dg->Columns->Items[5]->Field = aqdisplay->FieldByName("StorageFixedPrice");
			dg->Columns->Items[6]->Field = aqdisplay->FieldByName("StorageDscPrice");
			dg->Columns->Items[7]->Field = aqdisplay->FieldByName("WsaleAmount");
			dg->Columns->Items[8]->Field = aqdisplay->FieldByName("WsaleFixedPrice");
			dg->Columns->Items[9]->Field = aqdisplay->FieldByName("WsaleDscPrice");
			dg->Columns->Items[10]->Field = aqdisplay->FieldByName("RetailAmount");
			dg->Columns->Items[11]->Field = aqdisplay->FieldByName("RetailFixedPrice");
			dg->Columns->Items[12]->Field = aqdisplay->FieldByName("RetailDscPrice");
			dg->Columns->Items[1]->Footer->FieldName ="BookInfoAmount";
			dg->Columns->Items[2]->Footer->FieldName = "FixedPrice";
			dg->Columns->Items[3]->Footer->FieldName = "Discountprice";
			dg->Columns->Items[4]->Footer->FieldName = "StorgeAmount";
			dg->Columns->Items[5]->Footer->FieldName = "StorageFixedPrice";
			dg->Columns->Items[6]->Footer->FieldName = "StorageDscPrice";
			dg->Columns->Items[7]->Footer->FieldName = "WsaleAmount";
			dg->Columns->Items[8]->Footer->FieldName = "WsaleFixedPrice";
			dg->Columns->Items[9]->Footer->FieldName = "WsaleDscPrice";
			dg->Columns->Items[10]->Footer->FieldName = "RetailAmount";
			dg->Columns->Items[11]->Footer->FieldName = "RetailFixedPrice";
			dg->Columns->Items[12]->Footer->FieldName = "RetailDscPrice";
			dg->Columns->Items[1]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[2]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[3]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[4]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[5]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[6]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[7]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[8]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[9]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[10]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[11]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[12]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[0]->Visible = true;
			dg->Columns->Items[1]->Visible = true;
			dg->Columns->Items[2]->Visible = true;
			dg->Columns->Items[3]->Visible = true;
			dg->Columns->Items[4]->Visible = true;
			dg->Columns->Items[5]->Visible = true;
			dg->Columns->Items[6]->Visible = true;
			dg->Columns->Items[7]->Visible = true;
			dg->Columns->Items[8]->Visible = true;
			dg->Columns->Items[9]->Visible = true;
			dg->Columns->Items[10]->Visible = true;
			dg->Columns->Items[11]->Visible = true;
			dg->Columns->Items[12]->Visible = true;
		}
		else
		{
			Chart1->Visible = true;
			dg->Visible = false;
			aqdisplay->First();
			Chart1->Series[0]->Clear();
			switch (rgstyle->ItemIndex ) {
			case 0:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("BookInfoAmount")->AsFloat,aqdisplay->FieldByName("TypeName")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			case 1:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("StorgeAmount")->AsFloat,aqdisplay->FieldByName("TypeName")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			case 2:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("RetailAmount")->AsFloat,aqdisplay->FieldByName("TypeName")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			case 3:
				for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
					Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("WsaleAmount")->AsFloat,aqdisplay->FieldByName("TypeName")->AsAnsiString ,clRed);
					aqdisplay->Next();
				}
				break;
			default:
				;
			}
		}
	break;

	case 4:
		if (rgviewstyle->ItemIndex == 0) {
			Chart1->Visible = false;
			dg->Visible = true;
			//dg->Columns->Items[0]->Field = aqdisplay->FieldByName("xuhao");
			dg->Columns->Items[0]->Field = aqdisplay->FieldByName("ClientName");
			dg->Columns->Items[1]->Field = NULL ;
			dg->Columns->Items[2]->Field = NULL ;
			dg->Columns->Items[3]->Field = NULL ;
			dg->Columns->Items[4]->Field = NULL ;
			dg->Columns->Items[5]->Field = NULL ;
			dg->Columns->Items[6]->Field = NULL ;
			dg->Columns->Items[7]->Field = aqdisplay->FieldByName("WsaleAmount");
			dg->Columns->Items[8]->Field = aqdisplay->FieldByName("WsaleFixedPrice");
			dg->Columns->Items[9]->Field = aqdisplay->FieldByName("WsaleDscPrice");
			dg->Columns->Items[10]->Field = NULL ;
			dg->Columns->Items[11]->Field = NULL ;
			dg->Columns->Items[12]->Field = NULL ;
			dg->Columns->Items[7]->Footer->FieldName = "WsaleAmount";
			dg->Columns->Items[8]->Footer->FieldName = "WsaleFixedPrice";
			dg->Columns->Items[9]->Footer->FieldName = "WsaleDscPrice";
			dg->Columns->Items[7]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[8]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[9]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[0]->Visible = true;
			dg->Columns->Items[1]->Visible = false;
			dg->Columns->Items[2]->Visible = false;
			dg->Columns->Items[3]->Visible = false;
			dg->Columns->Items[4]->Visible = false;
			dg->Columns->Items[5]->Visible = false;
			dg->Columns->Items[6]->Visible = false;
			dg->Columns->Items[7]->Visible = true;
			dg->Columns->Items[8]->Visible = true;
			dg->Columns->Items[9]->Visible = true;
			dg->Columns->Items[10]->Visible = false;
			dg->Columns->Items[11]->Visible = false;
			dg->Columns->Items[12]->Visible = false;
		}
		else
		{
			Chart1->Visible = true;
			dg->Visible = false;
			aqdisplay->First();
			Chart1->Series[0]->Clear();
			for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
				Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("WsaleAmount")->AsFloat,aqdisplay->FieldByName("ClientName")->AsAnsiString ,clRed);
				aqdisplay->Next();
			}
		}
	break;

	case 5:
		if (rgviewstyle->ItemIndex == 0) {
			Chart1->Visible = false;
			dg->Visible = true;
			//dg->Columns->Items[0]->Field = aqdisplay->FieldByName("xuhao");
			dg->Columns->Items[0]->Field = aqdisplay->FieldByName("memberName");
			dg->Columns->Items[1]->Field = NULL ;
			dg->Columns->Items[2]->Field = NULL ;
			dg->Columns->Items[3]->Field = NULL ;
			dg->Columns->Items[4]->Field = NULL ;
			dg->Columns->Items[5]->Field = NULL ;
			dg->Columns->Items[6]->Field = NULL ;
			dg->Columns->Items[7]->Field = NULL ;
			dg->Columns->Items[8]->Field = NULL ;
			dg->Columns->Items[9]->Field = NULL ;
			dg->Columns->Items[10]->Field = aqdisplay->FieldByName("RetailAmount");
			dg->Columns->Items[11]->Field = aqdisplay->FieldByName("RetailFixedPrice");
			dg->Columns->Items[12]->Field = aqdisplay->FieldByName("RetailDscPrice");
			dg->Columns->Items[10]->Footer->FieldName = "RetailAmount";
			dg->Columns->Items[11]->Footer->FieldName = "RetailFixedPrice";
			dg->Columns->Items[12]->Footer->FieldName = "RetailDscPrice";
			dg->Columns->Items[10]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[11]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[12]->Footer->ValueType = fvtSum ;
			dg->Columns->Items[0]->Visible = true;
			dg->Columns->Items[1]->Visible = false;
			dg->Columns->Items[2]->Visible = false;
			dg->Columns->Items[3]->Visible = false;
			dg->Columns->Items[4]->Visible = false;
			dg->Columns->Items[5]->Visible = false;
			dg->Columns->Items[6]->Visible = false;
			dg->Columns->Items[7]->Visible = false;
			dg->Columns->Items[8]->Visible = false;
			dg->Columns->Items[9]->Visible = false;
			dg->Columns->Items[10]->Visible = true;
			dg->Columns->Items[11]->Visible = true;
			dg->Columns->Items[12]->Visible = true;
		}
		else
		{
			Chart1->Visible = true;
			dg->Visible = false;
			aqdisplay->First();
			Chart1->Series[0]->Clear();
			for (int i = 1; i <= aqdisplay->RecordCount ; i++) {
				Chart1->Series[0]->AddXY(i,aqdisplay->FieldByName("RetailAmount")->AsFloat,aqdisplay->FieldByName("memberName")->AsAnsiString ,clRed);
				aqdisplay->Next();
			}
		}
	break;

    default:
        ;
	}

}

//---------------------------------------------------------------------------
void __fastcall Tfrmorder::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorder::BtnViewClick(TObject *Sender)
{
//   ShowMessage( IntToStr(rgtype->ItemIndex));
	Query();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmorder::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorder::BtnExportClick(TObject *Sender)
{
	if (aqdisplay->Active && aqdisplay->RecordCount > 0) {
		DbgridToExcel(dg);
	}
}
//---------------------------------------------------------------------------
//Excel导出函数
bool __fastcall Tfrmorder::DbgridToExcel(TDBGridEh* dbg)
{
	AnsiString temptext ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		MessageBox(0,"没有数据！","错误确认" ,MB_OK);
		return false;
	}

    Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");

//  在Excel中成字符串显示

	if (rgtype->ItemIndex == 0) {
		temptext = "单书";
	}
	if (rgtype->ItemIndex == 1) {
		temptext = "出版社";
	}
	if (rgtype->ItemIndex == 2) {
		temptext = "供应商";
	}
	if (rgtype->ItemIndex == 3) {
		temptext = "类别";
	}
	if (rgtype->ItemIndex == 4) {
		temptext = "客户";
	}
	if (rgtype->ItemIndex == 5) {
		temptext = "个人会员";
	}

	if (rgstyle->ItemIndex == 0) {
		temptext = temptext + "按库存";
	}
	if (rgstyle->ItemIndex == 1) {
		temptext = temptext + "按入库";
	}
	if (rgstyle->ItemIndex == 2) {
		temptext = temptext + "按零售";
	}
	if (rgstyle->ItemIndex == 3) {
		temptext = temptext + "按发货";
	}
	temptext = temptext + "业务排行";

	n = 1;
	if (cbstart->Checked ) {
		temptext = temptext + "("+ DateToStr(dtpstart->Date) + "--";
		if (cbend->Checked ) {
			temptext = temptext + DateToStr(dtpend->Date);
		}
		temptext = temptext + ")";
	}
	else
	{
		if (cbend->Checked ) {
			temptext = temptext + "(--" + DateToStr(dtpend->Date) + ")";
		}
	}
	v.OlePropertyGet("Cells",1,4).OlePropertySet("Value",temptext.c_str());

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
		}
	}

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
            	if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
                	t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
				else
				{
                	t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",1,1),vSheet.OlePropertyGet("Cells",t2+n+1,t1)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",1,1),vSheet.OlePropertyGet("Cells",1,t1));
	R.OleProcedure("Merge");
	R.OlePropertySet("HorizontalAlignment",3);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorder::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {
		 BtnView->Click();
	}
		if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorder::dgTitleClick(TColumnEh *Column)
{
	if (aqdisplay->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqdisplay->Sort == "") {
		aqdisplay->Sort =  Column->FieldName + " ASC";
	}
	else if (aqdisplay->Sort == qusort) {
		aqdisplay->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqdisplay->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorder::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorder::dtpstartChange(TObject *Sender)
{
	cbstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorder::dtpendChange(TObject *Sender)
{
	cbend->Checked = true;
}
//---------------------------------------------------------------------------

