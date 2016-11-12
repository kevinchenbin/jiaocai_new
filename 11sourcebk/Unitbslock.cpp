//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitbslock.h"
#include "UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmbslock *frmbslock;
//---------------------------------------------------------------------------
__fastcall Tfrmbslock::Tfrmbslock(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{

   	fcon = con;
	fstgid = stgid;
		dtpstart->Date = Date();
	dtpend->Date = Date();
        aq->Connection = con;






        //供应商
        	AnsiString sql;
	sql = "select ID,Name from CUST_CustomerInfo where type = 1";
TADOQuery *aq1=new TADOQuery(Application);
aq1->Connection = fcon;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	while (!aq1->Eof )
	{
		cbsupplier->AddItem(aq1->FieldByName("Name")->AsAnsiString ,(TObject*)aq1->FieldByName("ID")->AsInteger );
		aq1->Next();
	}
	aq1->First();
	cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq1->FieldByName("ID")->AsInteger );

      	sql = "select ID,Name from sys_user where stgid = " + IntToStr(fstgid) ;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	while (!aq1->Eof)
	{
		cbuser->AddItem(aq1->FieldByName("Name")->AsAnsiString ,(TObject*)aq1->FieldByName("ID")->AsInteger );
		aq1->Next();
	}
	aq1->First();
	cbuser->ItemIndex = cbuser->Items->IndexOfObject((TObject*)aq1->FieldByName("ID")->AsInteger );


       delete aq1;


}
void Tfrmbslock::query()
{
     AnsiString sql;
       try
       {
        dg1->DataSource->DataSet->DisableControls();
	switch (rg->ItemIndex ) {
		case 0://订单
			sql = "select * from view_order_lock  where orderntcode<>0 and  StgID = " + IntToStr(fstgid);
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
			}

                        if (chclient->Checked&&edtclient->Text !="")
                        {
                          sql = sql +" and VendorID in (select id from dbo.GetChild(" + IntToStr(ClientID) + "))";

                        }
                        if (chuser->Checked && cbuser->Text != "") {
                        int userid;
                        try {
                        userid = int(cbuser->Items->Objects[cbuser->ItemIndex]);
                        } catch (...) {
                        MessageBoxA(0,"请选择正确的操作员！","提示",MB_ICONERROR);
                        return;
                        }
                        sql = sql + " and OperatorID = "  + IntToStr(userid);
                        }
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			dg1->Columns->Items[0]->Title->Caption = "客户名称";
			dg1->Columns->Items[1]->Title->Caption = "单号";
			dg1->Columns->Items[2]->Title->Caption = "数量";
			dg1->Columns->Items[3]->Title->Caption = "码洋";
                        dg1->Columns->Items[4]->Title->Caption = "实洋";
                        dg1->Columns->Items[5]->Title->Caption = "日期";
			dg1->Columns->Items[6]->Title->Caption = "状态";
			dg1->Columns->Items[7]->Title->Caption = "锁定";
			dg1->Columns->Items[8]->Title->Caption = "操作员";
                        dg1->Columns->Items[9]->Title->Caption = "备注";
                        dg1->Columns->Items[10]->Title->Caption = "id";


                        dg1->Columns->Items[0]->Field = aq->FieldByName("name");
                        dg1->Columns->Items[1]->Field = aq->FieldByName("code");
                        dg1->Columns->Items[2]->Field = aq->FieldByName("totalamount");
                        dg1->Columns->Items[3]->Field = aq->FieldByName("fixedprice");
                        dg1->Columns->Items[4]->Field = aq->FieldByName("discountedprice");
                        dg1->Columns->Items[5]->Field = aq->FieldByName("hdtime");
                        dg1->Columns->Items[6]->Field = aq->FieldByName("shenhestate");
                        dg1->Columns->Items[7]->Field = aq->FieldByName("lockstate");
                        dg1->Columns->Items[8]->Field = aq->FieldByName("operatorname");
                        dg1->Columns->Items[9]->Field = aq->FieldByName("remarks");
                        dg1->Columns->Items[10]->Field = aq->FieldByName("id");

                        

			dg1->Columns->Items[10]->Visible = false;

		
		break;
		case 1: //采购
			sql = "select * from view_caigou_lock where procurentcode <> 0 and StgID = " + IntToStr(fstgid);
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
			}
                           if (cksupplier->Checked&&editsupplier->Text !="")
                        {
                                 int supplierid;
                           	try {
		                 	supplierid = int(cbsupplier->Items->Objects[cbsupplier->ItemIndex]);
                                   sql = sql + " and supplierid="+IntToStr(supplierid);
                                    } catch (...) {
                                            MessageBoxA(0,"请选择正确的供应商！","提示",MB_ICONERROR);
                                            return;
		                            }



                        }

                          if (chuser->Checked && cbuser->Text != "") {
                        int userid;
                        try {
                        userid = int(cbuser->Items->Objects[cbuser->ItemIndex]);
                        } catch (...) {
                        MessageBoxA(0,"请选择正确的操作员！","提示",MB_ICONERROR);
                        return;
                        }
                        sql = sql + " and OperatorID = "  + IntToStr(userid);
                        }
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			dg1->Columns->Items[0]->Title->Caption = "供应商名称";
			dg1->Columns->Items[1]->Title->Caption = "单号";
			dg1->Columns->Items[2]->Title->Caption = "日期";
			dg1->Columns->Items[3]->Title->Caption = "数量";
                        dg1->Columns->Items[4]->Title->Caption = "码洋";
                        dg1->Columns->Items[5]->Title->Caption = "实洋";
                        dg1->Columns->Items[6]->Title->Caption = "状态";
                        dg1->Columns->Items[7]->Title->Caption = "锁定";
                        dg1->Columns->Items[8]->Title->Caption = "操作员";
                        dg1->Columns->Items[9]->Title->Caption = "备注";

                        dg1->Columns->Items[0]->Field = aq->FieldByName("suppliername");
                        dg1->Columns->Items[1]->Field = aq->FieldByName("Code");
                        dg1->Columns->Items[2]->Field = aq->FieldByName("hdtime");
                        dg1->Columns->Items[3]->Field = aq->FieldByName("totalamount");
                        dg1->Columns->Items[4]->Field = aq->FieldByName("FixedPrice");
                        dg1->Columns->Items[5]->Field = aq->FieldByName("DiscountedPrice");

                        dg1->Columns->Items[6]->Field = aq->FieldByName("state");
                        dg1->Columns->Items[7]->Field = aq->FieldByName("lockstate");
                        dg1->Columns->Items[8]->Field = aq->FieldByName("username");
                        dg1->Columns->Items[9]->Field = aq->FieldByName("remarks");



			dg1->Columns->Items[10]->Visible = false;

		break;
                case 3://入库退货
		case 2://入库

                        sql = " select * from  view_storage_lock where stgntcode <> 0 and StgID = " + IntToStr(fstgid);
                        if (rg->ItemIndex==3) {
                                       sql = sql + " and totalamount<0 ";
                        }else if (rg->ItemIndex==2) {
                                     sql = sql + " and totalamount>=0 ";
                        }
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
			}

                         if (cksupplier->Checked&&editsupplier->Text !="")
                        {
                                 int supplierid;
                           	try {
		                 	supplierid = int(cbsupplier->Items->Objects[cbsupplier->ItemIndex]);
                                   sql = sql + " and supplierid="+IntToStr(supplierid);
                                    } catch (...) {
                                            MessageBoxA(0,"请选择正确的供应商！","提示",MB_ICONERROR);
                                            return;
		                            }



                        }

                          if (chuser->Checked && cbuser->Text != "") {
                        int userid;
                        try {
                        userid = int(cbuser->Items->Objects[cbuser->ItemIndex]);
                        } catch (...) {
                        MessageBoxA(0,"请选择正确的操作员！","提示",MB_ICONERROR);
                        return;
                        }
                        sql = sql + " and OperatorID = "  + IntToStr(userid);
                        }
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();

                        	dg1->Columns->Items[0]->Title->Caption = "供应商名称";
			dg1->Columns->Items[1]->Title->Caption = "单号";
			dg1->Columns->Items[2]->Title->Caption = "日期";
			dg1->Columns->Items[3]->Title->Caption = "数量";
                        dg1->Columns->Items[4]->Title->Caption = "码洋";
                        dg1->Columns->Items[5]->Title->Caption = "实洋";
                        dg1->Columns->Items[6]->Title->Caption = "已结";
                        dg1->Columns->Items[7]->Title->Caption = "未结";
                        dg1->Columns->Items[8]->Title->Caption = "锁定";
                        dg1->Columns->Items[9]->Title->Caption = "操作员";
                        dg1->Columns->Items[10]->Title->Caption = "备注";


                        dg1->Columns->Items[0]->Field = aq->FieldByName("suppliername");
                        dg1->Columns->Items[1]->Field = aq->FieldByName("Code");
                        dg1->Columns->Items[2]->Field = aq->FieldByName("hdtime");
                        dg1->Columns->Items[3]->Field = aq->FieldByName("totalamount");
                        dg1->Columns->Items[4]->Field = aq->FieldByName("FixedPrice");
                        dg1->Columns->Items[5]->Field = aq->FieldByName("DiscountedPrice");

                          dg1->Columns->Items[6]->Field = aq->FieldByName("Checked");
                        dg1->Columns->Items[7]->Field = aq->FieldByName("NoChecked");

                        dg1->Columns->Items[8]->Field = aq->FieldByName("lockstate");
                        dg1->Columns->Items[9]->Field = aq->FieldByName("username");
                        dg1->Columns->Items[10]->Field = aq->FieldByName("remarks");




                        

		break;
                case 5://发货退货
		case 4://发货

				sql = "select * from view_wsale_lock where wsalentcode<>0 and StgID = " + IntToStr(fstgid);
                         if (rg->ItemIndex==5) {
                             sql = sql +" and totalamount<0 ";
                         }else if (rg->ItemIndex==4) {
                              sql = sql +" and totalamount>=0 ";
                         }


			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
			}
                          if (chclient->Checked&&edtclient->Text !="")
                        {
                          sql = sql +" and VendorID in (select id from dbo.GetChild(" + IntToStr(ClientID) + "))";

                        }
                          if (chuser->Checked && cbuser->Text != "") {
                        int userid;
                        try {
                        userid = int(cbuser->Items->Objects[cbuser->ItemIndex]);
                        } catch (...) {
                        MessageBoxA(0,"请选择正确的操作员！","提示",MB_ICONERROR);
                        return;
                        }
                        sql = sql + " and OperatorID = "  + IntToStr(userid);
                        }

                        	aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();

                       dg1->Columns->Items[0]->Title->Caption = "客户名称";
			dg1->Columns->Items[1]->Title->Caption = "单号";
                        dg1->Columns->Items[2]->Title->Caption = "日期";
			dg1->Columns->Items[3]->Title->Caption = "数量";
			dg1->Columns->Items[4]->Title->Caption = "码洋";
                        dg1->Columns->Items[5]->Title->Caption = "实洋";

			dg1->Columns->Items[6]->Title->Caption = "已结";
			dg1->Columns->Items[7]->Title->Caption = "未结";
			dg1->Columns->Items[8]->Title->Caption = "锁定";
                        dg1->Columns->Items[9]->Title->Caption = "操作员";
                        dg1->Columns->Items[10]->Title->Caption = "备注";


                        dg1->Columns->Items[0]->Field = aq->FieldByName("customername");
                        dg1->Columns->Items[1]->Field = aq->FieldByName("wsalentcodestr");
                        dg1->Columns->Items[2]->Field = aq->FieldByName("hdtime");
                        dg1->Columns->Items[3]->Field = aq->FieldByName("totalamount");
                        dg1->Columns->Items[4]->Field = aq->FieldByName("fixedprice");
                        dg1->Columns->Items[5]->Field = aq->FieldByName("discountedprice");

                        dg1->Columns->Items[6]->Field = aq->FieldByName("checked");
                        dg1->Columns->Items[7]->Field = aq->FieldByName("nochecked");
                        dg1->Columns->Items[8]->Field = aq->FieldByName("lockstate");
                        dg1->Columns->Items[9]->Field = aq->FieldByName("operatorname");
                        dg1->Columns->Items[10]->Field = aq->FieldByName("remarks");




		
		break;
	       /*	case 4://零售
			sql = "select distinct A.id, convert (nvarchar(10),B.HdTime,120) as HdTime,B.RetailNtCode AS Code,CUST_MemberInfo.Name as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice "
					" from BS_RetailNote A left join BS_RetailNoteHeader B on A.RetailNtHeaderID = B.id "
					" left join CUST_MemberInfo on B.MemberID = CUST_MemberInfo.ID "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0";
			}
			aq1->Close();
			aq1->SQL->Clear();
			aq1->SQL->Add(sql);
			aq1->Open();
			dg1->Columns->Items[0]->Title->Caption = "会员名称";
			dg1->Columns->Items[3]->Title->Caption = "零售数量";
			dg1->Columns->Items[7]->Visible = false;
			dg1->Columns->Items[8]->Visible = false;
			dg1->Visible = true;
                        dg3->Visible = false;
			dg2->Visible = false;
		break;       */
    default:
        ;
	}

        }catch(...)
        {

          ShowMessage("失败！");
        }
   dg1->DataSource->DataSet->EnableControls();;









}
//---------------------------------------------------------------------------
void __fastcall Tfrmbslock::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edclient->Text,fstgid);
		if (mrOk == frm->ShowModal())
		{
			ClientID = frm->GetSelectID();
			ClientView();
			edtclient->SetFocus();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbslock::edtclientChange(TObject *Sender)
{
	if (edtclient->Text != "") {
		chclient->Checked = true;
	}
	else
	{
    	chclient->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbslock::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",fstgid);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		edtclient->SetFocus();
		ClientView();
	}
	delete frm;
}
void Tfrmbslock::ClientView()
{
	if (ClientID == -1) {
		return;
	}
	String sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	sql = "exec USP_BS_Client_View 0," + IntToStr(ClientID)  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edtclient->Text = aq->FieldByName("Name")->AsAnsiString ;
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbslock::editsupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TADOQuery *aq1 = new TADOQuery(this);
		aq1->Connection = fcon;
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type = 1 and Name like '%" + editsupplier->Text + "%'";
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->Open();
        cbsupplier->Clear();
		while (!aq1->Eof )
		{
			cbsupplier->AddItem(aq1->FieldByName("Name")->AsAnsiString ,(TObject*)aq1->FieldByName("ID")->AsInteger );
			aq1->Next();
		}
		aq1->First();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq1->FieldByName("ID")->AsInteger );
		delete aq1;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbslock::cbsupplierChange(TObject *Sender)
{
	if (editsupplier->Text != "") {
		cksupplier->Checked = true;
	}
	else
	{
    	cksupplier->Checked = false;
	}
}
//---------------------------------------------------------------------------

void Tfrmbslock::lock(int type)
 {


     AnsiString idstr,sql;
  AnsiString bkcatalogid;
  sql="update BS_OrderNoteHeader set lock=1 where id = -1";
   	if (aq->IsEmpty() ) {
		return;
	}
         idstr="(-1";
        aq->DisableControls();

        if (dg1->SelectedRows->Count > 1) {
    	for (int i=0; i < dg1->SelectedRows->Count; i++)
		{
			aq->Bookmark = dg1->SelectedRows->Items[i];
			idstr = idstr + "," + aq->FieldByName("ID")->AsString;
		}
	}
	else
	{
		idstr = idstr + "," + aq->FieldByName("ID")->AsString;
	}
       aq->EnableControls();
       idstr=idstr+",-1)";



   switch(rg->ItemIndex)
   {
   case 0:  //订单
          sql = " update BS_OrderNoteHeader set lock="+IntToStr(type)+" where id in "+idstr;
   break;
   case 1:
         sql = " update BS_ProcureNoteHeader set lock="+IntToStr(type)+" where id in "+idstr;
   break;
   case 3:  //入库
   case 2:
       sql = " update BS_StorageNoteHeader set lock="+IntToStr(type)+" where id in "+idstr;
   break;
   case 4:
   case 5:
       sql = " update BS_WsaleNoteHeader set lock="+IntToStr(type)+" where id in "+idstr;
   break;
   }
   TADOQuery *aq1=new TADOQuery(Application);
   aq1->Connection = fcon;
   aq1->SQL->Clear();
   aq1->SQL->Add(sql);
   aq1->ExecSQL();
   delete aq1;

   query();//刷新




 }
//---------------------------------------------------------------------------

void __fastcall Tfrmbslock::dg1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
     	if (aq->IsEmpty() ) {
    	return;
	}
     if (!Shift.Contains(ssShift)) {

      oldrec= dg1->DataSource->DataSet->RecNo;

        }

      if (Shift.Contains(ssShift)) {
        currrec = dg1->DataSource->DataSet->RecNo;

        dg1->DataSource->DataSet->DisableControls();
        if (currrec>oldrec) {
           while(oldrec<dg1->DataSource->DataSet->RecNo  )
           {
              dg1->SelectedRows->CurrentRowSelected = true;
              dg1->DataSource->DataSet->Prior();
           }


        }else{

            while(oldrec>dg1->DataSource->DataSet->RecNo  )
           {
              dg1->SelectedRows->CurrentRowSelected = true;
              dg1->DataSource->DataSet->Next();
           }


        }
        dg1->SelectedRows->CurrentRowSelected = true;
       dg1->DataSource->DataSet->EnableControls();
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbslock::Q1Click(TObject *Sender)
{
if (!aq->Active) {
   return;
}
 	if (dg1->SelectedRows->Count == 1) {
            	for (int i = 1; i <= aq->RecordCount ; i++) {
					dg1->DataSource->DataSet->RecNo = i;
					dg1->SelectedRows->CurrentRowSelected = true;
				}
        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbslock::BtnViewClick(TObject *Sender)
{
query();
}
//---------------------------------------------------------------------------



void __fastcall Tfrmbslock::BtnAlignBottomClick(TObject *Sender)
{
lock(1);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbslock::RzToolButton1Click(TObject *Sender)
{
lock(0);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbslock::BtnExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

