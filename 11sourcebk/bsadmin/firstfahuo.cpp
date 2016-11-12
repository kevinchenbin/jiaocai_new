//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "firstfahuo.h"
#include "unitfahuoclient.h"
#include "unitinitfahuo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmfirstfahuo *frmfirstfahuo;
//---------------------------------------------------------------------------
__fastcall Tfrmfirstfahuo::Tfrmfirstfahuo(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void Tfrmfirstfahuo::Init(LandInfo* li)
{
	aq->Connection = li->con;
	aq1->Connection = li->con ;
	aq2->Connection = li->con ;
	fcon = li->con ;
	query->Connection = fcon;
	modresult = 0;
	AnsiString sql;
	sql = "select BS_Tmporder.id,dbo.UF_BS_GetClientName(BS_Tmporder.clientid) as ClientName,bs_bookcatalog.isbn,bs_bookcatalog.name,bs_bookcatalog.price, "
			" bs_bookcatalog.author,bs_bookcatalog.userdefcode,bs_bookcatalog.presscount,BS_PressInfo.AbbreviatedName,bs_bookcatalog.pressdate,BS_Tmporder.ordernoteid,  "
			" BS_OrderNote.xueyuan,BS_OrderNote.xiaoqu,BS_OrderNote.class,BS_OrderNote.course,BS_OrderNote.incode,BS_OrderNote.Amount as orderamount,BS_OrderNote.localnum,BS_OrderNote.SendAmount,BS_OrderNote.UnsendAmount,Order_lock.usableamount,BS_Tmporder.amount,BS_Tmporder.discount "
			" from BS_Tmporder left join bs_bookcatalog on BS_Tmporder.bkcatalogid = bs_bookcatalog.id "
			" left join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id "
			" left join Order_lock on BS_Tmporder.bkcatalogid = Order_lock.bkcatalogid "
			" left join BS_PressInfo on bs_bookcatalog.pressid = BS_PressInfo.id "
			" where BS_Tmporder.groupid = " + IntToStr(groupid) + " and modle = 0 and Order_lock.stgid = " + IntToStr(li->storageID) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfirstfahuo::SpeedButton1Click(TObject *Sender)
{
	if (!aq->IsEmpty() ) {
		Createyufacode();
		ModalResult = mrOk ;
	}
	else
	{
    	Close();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfirstfahuo::FormClose(TObject *Sender, TCloseAction &Action)
{
	/*if (!aq->IsEmpty() && modresult != 1) {
		AnsiString sql;
		sql = "delete from BS_Tmpheader where groupid = " + IntToStr(groupid);
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		sql = "delete from BS_Tmporder where groupid = " + IntToStr(groupid) + " and modle = 0";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	} */
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfirstfahuo::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfirstfahuo::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfirstfahuo::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{

	if (Shift.Contains(ssCtrl)&& Key == 78 ) {
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfirstfahuo::BtnDeleteClick(TObject *Sender)
{
	if (aq->IsEmpty() ) {
		return;
	}
	AnsiString sql;
	sql = "update BS_OrderNote set yufa = 0 where id = " + aq->FieldByName("ordernoteid")->AsString ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
	sql = "delete from BS_Tmporder where id = " + aq->FieldByName("id")->AsString ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
	aq->Active = false;
	aq->Active = true;
}
//---------------------------------------------------------------------------

void Tfrmfirstfahuo::Createyufacode()
{
	if (aq->IsEmpty() ) {
		return;
	}
	AnsiString sql,sqlorder,Message;
	int mode = 1,fclient,parentid;
	sql = "select distinct dbo.UF_BS_GetClientName(BS_Tmporder.clientid) as ClientName,";
	sqlorder = " clientid";
	if (chxiaoqu->Checked ) {
		sqlorder = sqlorder + ",BS_OrderNote.xiaoqu" ;
		mode = 2;
	}
	if (chxueyuan->Checked ) {
		sqlorder = sqlorder + ",BS_OrderNote.xueyuan" ;
		mode = 3;
	}
	if (chclass->Checked ) {
		sqlorder = sqlorder + ",BS_OrderNote.class" ;
		mode = 4;
	}
	sql = sql + sqlorder + " from BS_Tmporder left join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where modle = 0 and groupid = " + IntToStr(groupid) + " group by " + sqlorder ;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	if (mode == 1) {
		sql = " update BS_Tmporder set FahuoClient = clientid where modle = 0 and groupid = " + IntToStr(groupid);
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
	else
	{
		while (!aq1->Eof )
		{
            fclient = -1;
			if (mode == 2) {
				sql = "select id from CUST_CustomerInfo where PrentID = " + aq1->FieldByName("clientid")->AsString + " and Name = '" + aq1->FieldByName("xiaoqu")->AsAnsiString + "'";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->Open();
				if (query->IsEmpty() ) {
					Message = "客户名称:" + aq1->FieldByName("clientname")->AsString + ", 校区:" + aq1->FieldByName("xiaoqu")->AsAnsiString ;
					Tfrmfahuoclient *frm = new Tfrmfahuoclient(Application,fcon);
					frm->Label1->Caption = Message;
					frm->prentid = aq1->FieldByName("clientid")->AsInteger ;
					frm->mode = 1;
					frm->xiaoqu = aq1->FieldByName("xiaoqu")->AsString ;
					if (frm->ShowModal() == mrOk ) {
						fclient = frm->ClientID ;
						sql = " update BS_Tmporder set FahuoClient = " + IntToStr(fclient) + " from BS_Tmporder join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where modle = 0 and groupid id = " + IntToStr(groupid) + " and BS_OrderNote.xiaoqu = '" + aq1->FieldByName("xiaoqu")->AsAnsiString + "'";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->ExecSQL();
					}
				}
				else
				{
					sql = "update BS_Tmporder set FahuoClient = " + query->FieldByName("id")->AsString + " from BS_Tmporder join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where modle = 0 and groupid = " + IntToStr(groupid) + " and BS_OrderNote.xiaoqu = '" + aq1->FieldByName("xiaoqu")->AsAnsiString + "'";
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->ExecSQL();
				}
			}
			else if (mode == 3) {
				if (chxiaoqu->Checked ) {
					sql = "select id from CUST_CustomerInfo where PrentID = " + aq1->FieldByName("clientid")->AsString + " and Name = '" + aq1->FieldByName("xiaoqu")->AsAnsiString + "'";
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					if (query->IsEmpty() ) {
						Message = "客户名称:" + aq1->FieldByName("clientname")->AsString + ", 校区:" + aq1->FieldByName("xiaoqu")->AsAnsiString + ", 学院:" + aq1->FieldByName("xueyuan")->AsAnsiString ;
						Tfrmfahuoclient *frm = new Tfrmfahuoclient(Application,fcon);
						frm->Label1->Caption = Message;
						frm->prentid = aq1->FieldByName("clientid")->AsInteger ;
						frm->mode = 2;
						frm->xiaoqu = aq1->FieldByName("xiaoqu")->AsString ;
						frm->xueyuan = aq1->FieldByName("xueyuan")->AsString ;
						if (frm->ShowModal() == mrOk ) {
							fclient = frm->ClientID ;
						}
					}
					else
					{
						parentid =  query->FieldByName("id")->AsInteger;
						sql = "select id from CUST_CustomerInfo where PrentID = " + IntToStr(parentid) + " and Name = '" + aq1->FieldByName("xueyuan")->AsAnsiString + "'";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->Open();
						if (query->IsEmpty() ) {
							Message = "客户名称:" + aq1->FieldByName("clientname")->AsString + ", 校区:" + aq1->FieldByName("xiaoqu")->AsAnsiString + ", 学院:" + aq1->FieldByName("xueyuan")->AsAnsiString ;
							Tfrmfahuoclient *frm = new Tfrmfahuoclient(Application,fcon);
							frm->Label1->Caption = Message;
							frm->prentid = parentid ;
							frm->mode = 1;
							frm->xiaoqu = aq1->FieldByName("xueyuan")->AsString ;
							if (frm->ShowModal() == mrOk ) {
								fclient = frm->ClientID ;
							}
						}
						else
						{
							fclient = query->FieldByName("id")->AsInteger ;
						}
					}
					if (fclient > -1) {
						sql = "update BS_Tmporder set FahuoClient = " + IntToStr(fclient) + " from BS_Tmporder join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where modle = 0 and groupid = " + IntToStr(groupid) + " and BS_OrderNote.xueyuan = '" + aq1->FieldByName("xueyuan")->AsAnsiString + "' and BS_OrderNote.xiaoqu = '" + aq1->FieldByName("xiaoqu")->AsAnsiString + "'";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->ExecSQL();
					}
				}
				else
				{
					sql = "select id from CUST_CustomerInfo where PrentID = " + aq1->FieldByName("clientid")->AsString + " and Name = '" + aq1->FieldByName("xueyuan")->AsAnsiString + "'";
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					if (query->IsEmpty() ) {
						Message = "客户名称:" + aq1->FieldByName("clientname")->AsString + ", 学院:" + aq1->FieldByName("xueyuan")->AsAnsiString ;
						Tfrmfahuoclient *frm = new Tfrmfahuoclient(Application,fcon);
						frm->Label1->Caption = Message;
						frm->prentid = aq1->FieldByName("clientid")->AsInteger ;
						frm->mode = 1;
						frm->xiaoqu = aq1->FieldByName("xueyuan")->AsString ;
						if (frm->ShowModal() == mrOk ) {
							fclient = frm->ClientID ;
							sql = " update BS_Tmporder set FahuoClient = " + IntToStr(fclient) + " from BS_Tmporder join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where modle = 0 and groupid = " + IntToStr(groupid) + " and BS_OrderNote.xueyuan = '" + aq1->FieldByName("xueyuan")->AsAnsiString + "'";
							query->Close();
							query->SQL->Clear();
							query->SQL->Add(sql);
							query->ExecSQL();
						}
					}
					else
					{
						sql = "update BS_Tmporder set FahuoClient = " + query->FieldByName("id")->AsString + " from BS_Tmporder join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where modle = 0 and groupid = " + IntToStr(groupid) + " and BS_OrderNote.xueyuan = '" + aq1->FieldByName("xueyuan")->AsAnsiString + "'";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->ExecSQL();
					}
				}
			}
			else if (mode == 4) {
				if (chxiaoqu->Checked && chxueyuan->Checked ) {
                	sql = "select id from CUST_CustomerInfo where PrentID = " + aq1->FieldByName("clientid")->AsString + " and Name = '" + aq1->FieldByName("xiaoqu")->AsAnsiString + "'";
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					if (query->IsEmpty() ) {
						Message = "客户名称:" + aq1->FieldByName("clientname")->AsString + ", 校区:" + aq1->FieldByName("xiaoqu")->AsAnsiString + ", 学院:" + aq1->FieldByName("xueyuan")->AsAnsiString + ", 班级:" + aq1->FieldByName("class")->AsAnsiString;
						Tfrmfahuoclient *frm = new Tfrmfahuoclient(Application,fcon);
						frm->Label1->Caption = Message;
						frm->prentid = aq1->FieldByName("clientid")->AsInteger ;
						frm->mode = 3;
						frm->xiaoqu = aq1->FieldByName("xiaoqu")->AsString ;
						frm->xueyuan = aq1->FieldByName("xueyuan")->AsString ;
						frm->classname = aq1->FieldByName("class")->AsString ;
						if (frm->ShowModal() == mrOk ) {
							fclient = frm->ClientID ;
						}
					}
					else
					{
						parentid =  query->FieldByName("id")->AsInteger;
						sql = "select id from CUST_CustomerInfo where PrentID = " + IntToStr(parentid) + " and Name = '" + aq1->FieldByName("xueyuan")->AsAnsiString + "'";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->Open();
						if (query->IsEmpty() ) {
							Message = "客户名称:" + aq1->FieldByName("clientname")->AsString + ", 校区:" + aq1->FieldByName("xiaoqu")->AsAnsiString + ", 学院:" + aq1->FieldByName("xueyuan")->AsAnsiString + ", 班级:" + aq1->FieldByName("class")->AsAnsiString;
							Tfrmfahuoclient *frm = new Tfrmfahuoclient(Application,fcon);
							frm->Label1->Caption = Message;
							frm->prentid = parentid ;
							frm->mode = 2;
							frm->xiaoqu = aq1->FieldByName("xueyuan")->AsString ;
							frm->xueyuan = aq1->FieldByName("class")->AsString ;
							if (frm->ShowModal() == mrOk ) {
								fclient = frm->ClientID ;
							}
						}
						else
						{
                        	parentid =  query->FieldByName("id")->AsInteger;
							sql = "select id from CUST_CustomerInfo where PrentID = " + IntToStr(parentid) + " and Name = '" + aq1->FieldByName("class")->AsAnsiString + "'";
							query->Close();
							query->SQL->Clear();
							query->SQL->Add(sql);
							query->Open();
							if (query->IsEmpty() ) {
								Message = "客户名称: " + aq1->FieldByName("clientname")->AsString + ", 校区:" + aq1->FieldByName("xiaoqu")->AsAnsiString + ", 学院:" + aq1->FieldByName("xueyuan")->AsAnsiString + ", 班级:" + aq1->FieldByName("class")->AsAnsiString;
								Tfrmfahuoclient *frm = new Tfrmfahuoclient(Application,fcon);
								frm->Label1->Caption = Message;
								frm->prentid = parentid ;
								frm->mode = 1;
								frm->xiaoqu = aq1->FieldByName("class")->AsString ;
								if (frm->ShowModal() == mrOk ) {
									fclient = frm->ClientID ;
								}
							}
							else
							{
								fclient = query->FieldByName("id")->AsInteger ;
							}
						}
					}
                    if (fclient > -1) {
						sql = "update BS_Tmporder set FahuoClient = " + IntToStr(fclient) + " from BS_Tmporder join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where modle = 0 and groupid = " + IntToStr(groupid) + " and BS_OrderNote.xueyuan = '" + aq1->FieldByName("xueyuan")->AsAnsiString + "' and BS_OrderNote.xiaoqu = '" + aq1->FieldByName("xiaoqu")->AsAnsiString + "' and BS_OrderNote.class = '" + aq1->FieldByName("class")->AsAnsiString + "'";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->ExecSQL();
					}
				}
				if (chxiaoqu->Checked && !chxueyuan->Checked ) {
                    sql = "select id from CUST_CustomerInfo where PrentID = " + aq1->FieldByName("clientid")->AsString + " and Name = '" + aq1->FieldByName("xiaoqu")->AsAnsiString + "'";
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					if (query->IsEmpty() ) {
						Message = "客户名称:" + aq1->FieldByName("clientname")->AsString + ", 校区:" + aq1->FieldByName("xiaoqu")->AsAnsiString + ", 班级:" + aq1->FieldByName("class")->AsAnsiString ;
						Tfrmfahuoclient *frm = new Tfrmfahuoclient(Application,fcon);
						frm->Label1->Caption = Message;
						frm->prentid = aq1->FieldByName("clientid")->AsInteger ;
						frm->mode = 2;
						frm->xiaoqu = aq1->FieldByName("xiaoqu")->AsString ;
						frm->xueyuan = aq1->FieldByName("class")->AsString ;
						if (frm->ShowModal() == mrOk ) {
							fclient = frm->ClientID ;
						}
					}
					else
					{
						parentid =  query->FieldByName("id")->AsInteger;
						sql = "select id from CUST_CustomerInfo where PrentID = " + IntToStr(parentid) + " and Name = '" + aq1->FieldByName("class")->AsAnsiString + "'";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->Open();
						if (query->IsEmpty() ) {
							Message = "客户名称:" + aq1->FieldByName("clientname")->AsString + ", 校区:" + aq1->FieldByName("xiaoqu")->AsAnsiString + ", 班级:" + aq1->FieldByName("class")->AsAnsiString ;
							Tfrmfahuoclient *frm = new Tfrmfahuoclient(Application,fcon);
							frm->Label1->Caption = Message;
							frm->prentid = parentid ;
							frm->mode = 1;
							frm->xiaoqu = aq1->FieldByName("class")->AsString ;
							if (frm->ShowModal() == mrOk ) {
								fclient = frm->ClientID ;
							}
						}
						else
						{
							fclient = query->FieldByName("id")->AsInteger ;
						}
					}
					if (fclient > -1) {
						sql = "update BS_Tmporder set FahuoClient = " + IntToStr(fclient) + " from BS_Tmporder join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where modle = 0 and groupid = " + IntToStr(groupid) + " and BS_OrderNote.xueyuan = '" + aq1->FieldByName("xueyuan")->AsAnsiString + "' and BS_OrderNote.xiaoqu = '" + aq1->FieldByName("xiaoqu")->AsAnsiString + "'";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->ExecSQL();
					}
				}
				if (chxueyuan->Checked && !chxiaoqu->Checked ) {
                    sql = "select id from CUST_CustomerInfo where PrentID = " + aq1->FieldByName("clientid")->AsString + " and Name = '" + aq1->FieldByName("xueyuan")->AsAnsiString + "'";
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					if (query->IsEmpty() ) {
						Message = "客户名称:" + aq1->FieldByName("clientname")->AsString + ", 学院:" + aq1->FieldByName("xueyuan")->AsAnsiString + ", 班级:" + aq1->FieldByName("class")->AsAnsiString ;
						Tfrmfahuoclient *frm = new Tfrmfahuoclient(Application,fcon);
						frm->Label1->Caption = Message;
						frm->prentid = aq1->FieldByName("clientid")->AsInteger ;
						frm->mode = 2;
						frm->xiaoqu = aq1->FieldByName("xueyuan")->AsString ;
						frm->xueyuan = aq1->FieldByName("class")->AsString ;
						if (frm->ShowModal() == mrOk ) {
							fclient = frm->ClientID ;
						}
					}
					else
					{
						parentid =  query->FieldByName("id")->AsInteger;
						sql = "select id from CUST_CustomerInfo where PrentID = " + IntToStr(parentid) + " and Name = '" + aq1->FieldByName("class")->AsAnsiString + "'";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->Open();
						if (query->IsEmpty() ) {
							Message = "客户名称:" + aq1->FieldByName("clientname")->AsString + ", 学院:" + aq1->FieldByName("xueyuan")->AsAnsiString + ", 班级:" + aq1->FieldByName("class")->AsAnsiString ;
							Tfrmfahuoclient *frm = new Tfrmfahuoclient(Application,fcon);
							frm->Label1->Caption = Message;
							frm->prentid = parentid ;
							frm->mode = 1;
							frm->xiaoqu = aq1->FieldByName("class")->AsString ;
							if (frm->ShowModal() == mrOk ) {
								fclient = frm->ClientID ;
							}
						}
						else
						{
							fclient = query->FieldByName("id")->AsInteger ;
						}
					}
					if (fclient > -1) {
						sql = "update BS_Tmporder set FahuoClient = " + IntToStr(fclient) + " from BS_Tmporder join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where modle = 0 and groupid = " + IntToStr(groupid) + " and BS_OrderNote.xueyuan = '" + aq1->FieldByName("xueyuan")->AsAnsiString + "' and BS_OrderNote.xiaoqu = '" + aq1->FieldByName("xiaoqu")->AsAnsiString + "'";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->ExecSQL();
					}
				}
				if (!chxiaoqu->Checked && !chxueyuan->Checked ) {
					sql = "select id from CUST_CustomerInfo where PrentID = " + aq1->FieldByName("clientid")->AsString + " and Name = '" + aq1->FieldByName("class")->AsAnsiString + "'";
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					if (query->IsEmpty() ) {
						Message = "客户名称:" + aq1->FieldByName("clientname")->AsString + ", 班级:" + aq1->FieldByName("class")->AsAnsiString ;
						Tfrmfahuoclient *frm = new Tfrmfahuoclient(Application,fcon);
						frm->Label1->Caption = Message;
						frm->prentid = aq1->FieldByName("clientid")->AsInteger ;
						frm->mode = 1;
						frm->xiaoqu = aq1->FieldByName("class")->AsString ;
						if (frm->ShowModal() == mrOk ) {
							fclient = frm->ClientID ;
							sql = " update BS_Tmporder set FahuoClient = " + IntToStr(fclient) + " from BS_Tmporder join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where modle = 0 and groupid = " + IntToStr(groupid) + " and BS_OrderNote.class = '" + aq1->FieldByName("class")->AsAnsiString + "'";
							query->Close();
							query->SQL->Clear();
							query->SQL->Add(sql);
							query->ExecSQL();
						}
					}
					else
					{
						sql = "update BS_Tmporder set FahuoClient = " + query->FieldByName("id")->AsString + " from BS_Tmporder join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where modle = 0 and groupid = " + IntToStr(groupid) + " and BS_OrderNote.class = '" + aq1->FieldByName("class")->AsAnsiString + "'";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->ExecSQL();
					}
				}
			}
			aq1->Next();
		}
	}
	/*
	sql = "update BS_Tmporder set amount = T.amount from BS_Tmporder join BS_Tmpheader on BS_Tmporder.groupid = BS_Tmpheader.groupid join "
			" (select * from BS_Tmporder where groupid = " + IntToStr(groupid) + ") T on BS_Tmporder.bkcatalogid = T.bkcatalogid and BS_Tmporder.FahuoClient = T.FahuoClient "
			" where BS_Tmpheader.state = 0";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
	sql = "delete from BS_Tmporder where id in (select BS_Tmporder.id from  BS_Tmporder join BS_Tmpheader on BS_Tmporder.groupid = BS_Tmpheader.groupid join "
			" (select min(BS_Tmporder.id) as id,bkcatalogid,fahuoclient from BS_Tmporder join BS_Tmpheader on BS_Tmporder.groupid = BS_Tmpheader.groupid where  BS_Tmpheader.state = 0 "
			" group by bkcatalogid,fahuoclient "
			" having count(bkcatalogid) > 1 and count(fahuoclient) > 1) "
			" T on BS_Tmporder.bkcatalogid =T.bkcatalogid AND BS_Tmporder.fahuoclient =T.fahuoclient  AND BS_Tmporder.ID <> T.ID "
			" where BS_Tmpheader.state = 0)";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
	sql = "select * from BS_Tmporder where groupid = " +  IntToStr(groupid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->IsEmpty() ) {
    	sql = "select * from BS_Tmporder where groupid = " +  IntToStr(groupid);
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}   */
	modresult = 1;
}
//---------------------------------------------------------------------------


