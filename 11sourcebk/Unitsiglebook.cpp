//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitsiglebook.h"
#include "checkselbook.h"
#include "Unitboolslect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmsiglebook *frmsiglebook;
//---------------------------------------------------------------------------
__fastcall Tfrmsiglebook::Tfrmsiglebook(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
	fcon = con;
	fstgid = stgid;
	m_catalogSearchMode = 0;
	dtpstart->Date = Date();
	dtpend->Date = Date();
	aq1->Connection = con;
	aq2->Connection = con;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select * from SYS_BSSET where name = 'changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
        aq3->Connection = fcon;
	ChangeDisplay  = aq->FieldByName("value")->AsBoolean ;
	delete aq;
	bkcatalogid = -2;
	dg1->OnDrawColumnCell=dg3DrawColumnCell;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglebook::N1Click(TObject *Sender)
{
	m_catalogSearchMode = 0;
	Label4->Caption = "书号";
	edquery->MaxLength = 13;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglebook::N2Click(TObject *Sender)
{
	m_catalogSearchMode = 1;
	Label4->Caption = "书名";
	edquery->MaxLength = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglebook::N3Click(TObject *Sender)
{
	m_catalogSearchMode = 2;
	Label4->Caption = "自编码";
	edquery->MaxLength = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglebook::N4Click(TObject *Sender)
{
	m_catalogSearchMode = 3;
	Label4->Caption = "定价";
	edquery->MaxLength = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglebook::N5Click(TObject *Sender)
{
	m_catalogSearchMode = 4;
	Label4->Caption = "作者";
	edquery->MaxLength = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglebook::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (m_catalogSearchMode == 3) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
			Key = NULL;
		}
	}
	if (Key == '\r') {
		if (edquery->Text == "") {
			ChangeCatalogSearchMode();
		}
		else
		{
        	float price;
			if (m_catalogSearchMode == 3) {
				try {
					price = StrToFloat(edquery->Text.Trim());
				} catch (...) {
					MessageBox(0,"请输入正确的定价！","入库" ,MB_ICONEXCLAMATION);
					return;
				}
			}
			AnsiString sql;
			TADOQuery *aq = new TADOQuery(this);
			aq->Connection = fcon;
			sql = "select BS_BookCatalog.id,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.UserDefCode,Price,PressCount,BS_BookCatalog.Author,BS_PressInfo.AbbreviatedName,BS_BookType.Name AS typename,sum(A.amount) as amount "
					 " from BS_BookCatalog left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
					 " left join BS_BookType on BS_BookCatalog.smallBookTypeID = BS_BookType.id "
					 " left join (select * from stk_bookinfo where stgid = " + IntToStr(fstgid) + ")A on BS_BookCatalog.id = A.BkcatalogID "
					 " where BS_BookCatalog.Unavailable = 1 ";

			switch (m_catalogSearchMode) {
				case 0:
					sql = sql + " and (BS_BookCatalog.ISBN like '%" + edquery->Text.Trim()  + "%' or BS_BookCatalog.Barcode like '%" + edquery->Text.Trim()  + "%') " ;
				break;
				case 1:
					sql = sql + " and BS_BookCatalog.Name like '%" + edquery->Text.Trim()  + "%'";
				break;
				case 2:
					sql = sql + " and BS_BookCatalog.UserDefCode like '%" + edquery->Text.Trim()  + "%'";
				break;
				case 3:
					sql = sql + " and BS_BookCatalog.Price = " + edquery->Text ;
				break;
				case 4:
					sql = sql + " and BS_BookCatalog.Author like '%" + edquery->Text.Trim()  + "%'";
				break;
			default:
                ;
			}
			sql = sql + " group by BS_BookCatalog.id,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.UserDefCode,Price,PressCount,BS_BookCatalog.Author,BS_PressInfo.AbbreviatedName,BS_BookType.Name ";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount >1) {
				Tfrmselectbook *frm = new Tfrmselectbook(Application,aq);
				if (frm->ShowModal() == mrOk ) {
                	bkcatalogid = aq->FieldByName("id")->AsInteger ;
					edisbn->Text = aq->FieldByName("ISBN")->AsAnsiString ;
					edname->Text = aq->FieldByName("Name")->AsAnsiString ;
					edprice->Text = aq->FieldByName("Price")->AsAnsiString ;
					edpress->Text = aq->FieldByName("AbbreviatedName")->AsAnsiString ;
					edpresscount->Text = aq->FieldByName("PressCount")->AsAnsiString ;
					edtype->Text = aq->FieldByName("typename")->AsAnsiString ;
					edauthor->Text = aq->FieldByName("Author")->AsAnsiString ;
					dg1->Columns->Items[7]->Footer->ValueType = fvtNon ;
					dg1->Columns->Items[8]->Footer->ValueType = fvtNon ;
					Query();
				}
			}
			else if (aq->RecordCount == 1) {
				bkcatalogid = aq->FieldByName("id")->AsInteger ;
				edisbn->Text = aq->FieldByName("ISBN")->AsAnsiString ;
				edname->Text = aq->FieldByName("Name")->AsAnsiString ;
				edprice->Text = aq->FieldByName("Price")->AsAnsiString ;
				edpress->Text = aq->FieldByName("AbbreviatedName")->AsAnsiString ;
				edpresscount->Text = aq->FieldByName("PressCount")->AsAnsiString ;
				edtype->Text = aq->FieldByName("typename")->AsAnsiString ;
				edauthor->Text = aq->FieldByName("Author")->AsAnsiString ;
				dg1->Columns->Items[7]->Footer->ValueType = fvtNon ;
				dg1->Columns->Items[8]->Footer->ValueType = fvtNon ;
				Query();
			}

			//sql = "select sum(Amount) as amount from STK_bookinfo  where stgid = " + IntToStr(fstgid) + " and BkcatalogID = " + IntToStr(bkcatalogid) ;
			//aq->Close();
			//aq->SQL->Clear();
			//aq->SQL->Add(sql);
			//aq->Open();

			edbkinfo->Text  = aq->FieldByName("amount")->AsString ;

			delete aq;
		}
	}
}
//---------------------------------------------------------------------------
void Tfrmsiglebook::ChangeCatalogSearchMode()
{
	m_catalogSearchMode++;
	if (m_catalogSearchMode >= 5)
	{
		m_catalogSearchMode = 0;
	}

	switch (m_catalogSearchMode)
	{
	case 0:
		edquery->MaxLength = 13;
		Label4->Caption = "书号";
		break;
	case 1:
		edquery->MaxLength = 0;
		Label4->Caption = "书名";
		break;
	case 2:
		edquery->MaxLength = 0;
		Label4->Caption = "自编码";
		break;
	case 3:
		edquery->MaxLength = 0;
		Label4->Caption = "定价";
		break;
	case 4:
		edquery->MaxLength = 0;
		Label4->Caption = "作者";
		break;
	default:
        break;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglebook::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void Tfrmsiglebook::Query()
{
    AnsiString sql;
	switch (rg->ItemIndex ) {
		case 0://订单
			sql = "select distinct A.id, convert (nvarchar(10),B.HdTime,120) as HdTime,B.OrderNtCode AS Code,dbo.UF_BS_GetClientName(B.VendorID) as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,A.SendAmount,A.UnsendAmount,A.state "
					" from BS_OrderNote A left join BS_OrderNoteHeader B on A.OrderNtHeaderID = B.id where A.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0";
			}
			sql=sql+" union all ";
			sql =sql+ " select 1 id, convert (nvarchar(10),HdTime,120) hdtime,OrderNtCode code,orderuser name,"
					" amount, discount, fixedprice,discountedprice,sended,amount-sended unsendamount,0 [state] "
					"  from dbo.C_OrderSearchDetail where catalogid=" + IntToStr(bkcatalogid);
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
			}





			aq1->Close();
			aq1->SQL->Clear();
			aq1->SQL->Add(sql);
			aq1->Open();
			dg1->Columns->Items[0]->Title->Caption = "客户名称";
			dg1->Columns->Items[3]->Title->Caption = "订货数量";
			dg1->Columns->Items[7]->Title->Caption = "已发数量";
			dg1->Columns->Items[8]->Title->Caption = "未发数量";
			dg1->Columns->Items[7]->Field = aq1->FieldByName("SendAmount");
			dg1->Columns->Items[8]->Field = aq1->FieldByName("UnsendAmount");
			dg1->Columns->Items[7]->Footer->FieldName = "SendAmount";
			dg1->Columns->Items[7]->Footer->ValueType = fvtSum ;
			dg1->Columns->Items[8]->Footer->FieldName = "UnsendAmount";
			dg1->Columns->Items[8]->Footer->ValueType = fvtSum ;
			dg1->Columns->Items[7]->Visible = true;
			dg1->Columns->Items[8]->Visible = true;
			dg1->Visible = true;
                        dg3->Visible = false;
			dg2->Visible = false;
		break;
		case 1: //采购
			sql = "select distinct A.id, convert (nvarchar(10),B.HdTime,120) as HdTime,B.ProcureNtCode AS Code,CUST_CustomerInfo.Name as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,A.RecAmount,A.UnrecAmount "
					" from BS_ProcureNote A left join BS_ProcureNoteHeader B on A.ProcureNtHeaderID = B.id "
					" left join CUST_CustomerInfo on B.SupplierID = CUST_CustomerInfo.id where A.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
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
			dg1->Columns->Items[0]->Title->Caption = "供应商名称";
			dg1->Columns->Items[3]->Title->Caption = "采购数量";
			dg1->Columns->Items[7]->Title->Caption = "已到数量";
			dg1->Columns->Items[8]->Title->Caption = "未到数量";
			dg1->Columns->Items[7]->Field = aq1->FieldByName("RecAmount");
			dg1->Columns->Items[8]->Field = aq1->FieldByName("UnrecAmount");
			dg1->Columns->Items[7]->Footer->FieldName = "RecAmount";
			dg1->Columns->Items[7]->Footer->ValueType = fvtSum ;
			dg1->Columns->Items[8]->Footer->FieldName = "UnrecAmount";
			dg1->Columns->Items[8]->Footer->ValueType = fvtSum ;
			dg1->Columns->Items[7]->Visible = true;
			dg1->Columns->Items[8]->Visible = true;
			dg1->Visible = true;
                        dg3->Visible = false;
			dg2->Visible = false;

		break;
		case 2://入库
			if (ChangeDisplay) {
				sql = "select distinct A.id, convert (nvarchar(10),B.HdTime,120) as HdTime,B.StgNtCodeStr AS Code,CUST_CustomerInfo.Name as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice "
					" from BS_StorageNote A left join BS_StorageNoteHeader B on A.StgNtHeaderID = B.id "
					" left join CUST_CustomerInfo on B.SupplierID = CUST_CustomerInfo.id "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
			}
			else
			{
				sql = "select distinct A.id convert (nvarchar(10),B.HdTime,120) as HdTime,B.StgNtCode AS Code,CUST_CustomerInfo.Name as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice "
					" from BS_StorageNote A left join BS_StorageNoteHeader B on A.StgNtHeaderID = B.id "
					" left join CUST_CustomerInfo on B.SupplierID = CUST_CustomerInfo.id "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
			}

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
			dg1->Columns->Items[0]->Title->Caption = "供应商名称";
			dg1->Columns->Items[3]->Title->Caption = "入库数量";
			dg1->Columns->Items[7]->Visible = false;
			dg1->Columns->Items[8]->Visible = false;
			dg1->Visible = true;
                        dg3->Visible = false;
			dg2->Visible = false;
		break;
		case 3://发货
			if (ChangeDisplay) {
				sql = "select distinct A.id, convert (nvarchar(10),B.HdTime,120) as HdTime,B.WsaleNtCodeStr AS Code,dbo.UF_BS_GetClientName(B.VendorID) as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice "
					" from BS_WsaleNote A left join BS_WsaleNoteHeader B on A.WsaleNtHeaderID = B.id "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
			}
			else
			{
				sql = "select distinct A.id, convert (nvarchar(10),B.HdTime,120) as HdTime,B.WsaleNtCode AS Code,dbo.UF_BS_GetClientName(B.VendorID) as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice "
					" from BS_WsaleNote A left join BS_WsaleNoteHeader B on A.WsaleNtHeaderID = B.id "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid) + " and B.StgID = " + IntToStr(fstgid);
			}

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
			dg1->Columns->Items[0]->Title->Caption = "客户名称";
			dg1->Columns->Items[3]->Title->Caption = "发货数量";
			dg1->Columns->Items[7]->Visible = false;
			dg1->Columns->Items[8]->Visible = false;
			dg1->Visible = true;
                        dg3->Visible = false;
			dg2->Visible = false;
		break;
		case 4://零售
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
		break;
		case 5: //盘点
			sql = "select distinct A.id, convert (nvarchar(10),B.checkdate,120) as HdTime,B.checkstockNum AS Code,STK_BookstackInfo.Name as Name,"
					" A.ShouldAmount,A.ActualAmount,A.damagenum,A.Balance,A.Discount,A.Fixedprice,A.Discountprice,A.bk "
					" from STK_StockInventories A left join STK_CheckStockinfo B on A.NoteCode = B.checkstockNum "
					" left join STK_BookstackInfo on B.checkstocklocal = STK_BookstackInfo.ID where A.bkcatalogid = " + IntToStr(bkcatalogid) + " and B.checkstore = " + IntToStr(fstgid);
        	if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.checkdate) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.checkdate) <= 0";
			}
			aq2->Close();
			aq2->SQL->Clear();
			aq2->SQL->Add(sql);
			aq2->Open();
			dg1->Visible = false;
			dg2->Visible = true;
                        dg3->Visible = false;
			dg2->Columns->Items[6]->Visible = true;
			dg2->Columns->Items[7]->Visible = true;
			dg2->Columns->Items[8]->Visible = true;
		break;
		case 6: //库存调整
			sql = "select distinct A.id, convert (nvarchar(10),B.AdjustDate,120) as HdTime,B.AdjustHeaderID AS Code,STK_BookstackInfo.Name as Name,"
					" A.AdjustAmount as ShouldAmount,A.yamount as ActualAmount,A.damagenum,A.AdjustAmount - A.yamount as Balance,0 as Discount,0 as Fixedprice,0 as Discountprice,A.bk "
					" from STK_AdjustDetail A left join STK_AdjustHeader B on A.AdjustHeaderID = B.AdjustHeaderID "
					" left join stk_bookinfo on A.bkinfoid = stk_bookinfo.id "
					" left join STK_BookstackInfo on stk_bookinfo.BkstackID = STK_BookstackInfo.ID where A.bkcatalogid = " + IntToStr(bkcatalogid) + " and B.Stgid = " + IntToStr(fstgid);

			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.adjustDate) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.adjustDate) <= 0";
			}
			aq2->Close();
			aq2->SQL->Clear();
			aq2->SQL->Add(sql);
			aq2->Open();
			dg1->Visible = false;
			dg2->Visible = true;
                        dg3->Visible = false;
			dg2->Columns->Items[6]->Visible = false;
			dg2->Columns->Items[7]->Visible = false;
			dg2->Columns->Items[8]->Visible = false;
		break;
		case 7: //虚拟盘点
			sql = "select distinct A.id, convert (nvarchar(10),B.AdjustDate,120) as HdTime,B.AdjustHeaderID AS Code,STK_BookstackInfo.Name as Name,100 as discount, "
				" A.AdjustAmount as ShouldAmount,A.bk1 as ActualAmount,A.damagenum,A.blanceamount as Balance,A.bk "
				" from STK_stockxuyiDetail A left join STK_stockxuyiHeader B on A.AdjustHeaderID = B.AdjustHeaderID "
				" left join stk_bookinfo on A.bkinfoid = stk_bookinfo.id "
				" left join STK_BookstackInfo on stk_bookinfo.BkstackID = STK_BookstackInfo.id where A.bkcatalogID = " + IntToStr(bkcatalogid) + " and B.stg = " + IntToStr(fstgid);
        	if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.AdjustDate) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.AdjustDate) <= 0";
			}
			aq2->Close();
			aq2->SQL->Clear();
			aq2->SQL->Add(sql);
			aq2->Open();
			dg1->Visible = false;
			dg2->Visible = true;
                        dg3->Visible = false;
			dg2->Columns->Items[6]->Visible = false;
			dg2->Columns->Items[7]->Visible = false;
			dg2->Columns->Items[8]->Visible = false;
		break;
                case 8:    //调拨
                        sql = " select * from Qry_DiaoboQuery where  bkcatalogID = " + IntToStr(bkcatalogid) + " and stgid = " + IntToStr(fstgid);
                        aq3->Close();
			aq3->SQL->Clear();
			aq3->SQL->Add(sql);
			aq3->Open();
                        dg1->Visible = false;
			dg2->Visible = false;
                        dg3->Visible = true;
                break;
    default:
        ;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsiglebook::rgClick(TObject *Sender)
{
    dg1->Columns->Items[7]->Footer->ValueType = fvtNon ;
	dg1->Columns->Items[8]->Footer->ValueType = fvtNon ;
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsiglebook::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsiglebook::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		BtnView->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
	if (Key == VK_F8 ) {    //导出
		BtnExport->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsiglebook::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsiglebook::BtnViewClick(TObject *Sender)
{
	Query();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmsiglebook::Label4MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsiglebook::BtnExportClick(TObject *Sender)
{
	if (aq1->IsEmpty() ) {
        return;
	}
	DbgridToExcel(dg1);
}
//---------------------------------------------------------------------------

//Excel导出函数
bool Tfrmsiglebook::DbgridToExcel(TDBGridEh* dbg)
{
	AnsiString temptext,path  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	//savedlg->FileName = edname->Text + "-" + rg->Items->operator [](rg->ItemIndex) ;
	savedlg->FileName = edname->Text + "-" + rg->Items->Strings[rg->ItemIndex];
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(savedlg->FileName .c_str()  );
		Name = ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
	else
	{
    	return false;
	}
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	temptext = "书号,书名,当前库存,定价,作者,出版社,版次,类别";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n";
	AnsiString bookname;
	bookname = edname->Text;
	bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
	temptext = temptext + edisbn->Text + "," + bookname + "," + edbkinfo->Text + "," + edprice->Text + "," + edauthor->Text + "," + edpress->Text + "," + edpresscount->Text + "," + edtype->Text;
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n";
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();

	while (!dbg->DataSource->DataSet->Eof )
	{
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
			}
		}
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}


    dbg->DataSource ->DataSet->EnableControls();

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsiglebook::dg1TitleClick(TColumnEh *Column)
{
	if (aq1->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aq1->Sort == "") {
		aq1->Sort =  Column->FieldName + " ASC";
	}
	else if (aq1->Sort == qusort) {
		aq1->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aq1->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall Tfrmsiglebook::dg3DrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumnEh *Column,
		  Gridseh::TGridDrawState State)
{       Gridseh::TGridDrawState st;

	if (rg->ItemIndex == 0 && aq1->FieldByName("state")->AsInteger == 1 ) {
		dg1->Canvas->Font->Color = clRed ;
		dg1->Canvas->FillRect(Rect);
		dg1->DefaultDrawColumnCell(Rect,DataCol,Column,st);
	}
	else
	{
		dg1->DefaultDrawColumnCell(Rect,DataCol,Column,st);
	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

