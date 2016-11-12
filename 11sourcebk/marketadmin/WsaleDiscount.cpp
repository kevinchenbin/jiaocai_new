//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WsaleDiscount.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzRadChk"
#pragma link "RzEdit"
#pragma link "RzDTP"
#pragma link "RzDBGrid"
#pragma link "RzLabel"
#pragma resource "*.dfm"
TFormWsaleDiscount *FormWsaleDiscount;
//---------------------------------------------------------------------------
__fastcall TFormWsaleDiscount::TFormWsaleDiscount(TComponent* Owner,int stgid)
	: TForm(Owner)
{
	m_catalogSearchMode = 1;
	m_storageID = stgid;
	modify = false;
}
//---------------------------------------------------------------------------
void TFormWsaleDiscount::Init(TApplication* app, TADOConnection* con)
{
	query->Connection = con;
	querydetail->Connection = con;
	aq->Connection = con;
	cn = con;
	//画面初期显示
	AnsiString sql;
	dtpstart->Date = Date();
	dtpend->Date = Date();

	sql = "select ID,Name from SYS_StorageInfo";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof )
	{
		cbstorage->AddItem(query->FieldByName("Name")->AsString,(TObject*)query->FieldByName("ID")->AsInteger );
		query->Next();
	}
	cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)m_storageID);
	sql = "select Master from SYS_StorageInfo where id = " + IntToStr(m_storageID);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("Master")->AsBoolean ) {
		cbstorage->Enabled = true;
	}
	else
	{
    	cbstorage->Enabled = false;
	}

	//打折方案初始显示
	sql = "select BS_WSaleDiscountInfo.*,convert(varchar(20),BS_WSaleDiscountInfo.Endtime,23) as endtime1,BS_BookCatalog.Name,BS_BookCatalog.ISBN,BS_BookCatalog.Price,BS_PressInfo.AbbreviatedName "
		  "from BS_WSaleDiscountInfo left join BS_BookCatalog on BS_WSaleDiscountInfo.BookCatalogID = BS_BookCatalog.ID "
		  "left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id left join STK_BookInfo on BS_WSaleDiscountInfo.BookInfoID = STK_BookInfo.ID left join STK_BookstackInfo on STK_BookInfo.BkstackID = STK_BookstackInfo.id where BS_WSaleDiscountInfo.StgID = " + IntToStr(m_storageID);
	querydetail->Close();
	querydetail->SQL->Clear();
	querydetail->SQL->Add(sql);
	querydetail->Open();
	disable();
}

//---------------------------------------------------------------------------
void TFormWsaleDiscount::excuit()
{
	AnsiString sql;
	if (modify) {
        sql = "update BS_WSaleDiscountInfo set Discount = " + eddiscount->Text +",Starttime = '" + DateToStr(dtpstart->Date) + "',Endtime = '" + DateToStr(dtpend->Date) + " 23:59:59'";
		if (cbMonday->Checked ) {
			sql = sql + ",Monday = 1";
		}
		else
		{
			sql = sql + ",Monday = 0";
		}
		if (cbTuesday->Checked ) {
			sql = sql + ",Tuesday = 1";
		}
		else
		{
			sql = sql + ",Tuesday = 0";
		}
		if (cbWednesday->Checked ) {
			sql = sql + ",Wednesday = 1";
		}
		else
		{
			sql = sql + ",Wednesday = 0";
		}
		if (cbThursday->Checked ) {
			sql = sql + ",Thursday = 1";
		}
		else
		{
			sql = sql + ",Thursday = 0";
		}
		if (cbFriday->Checked) {
			sql = sql + ",Friday = 1";
		}
		else
		{
			sql = sql + ",Friday = 0";
		}
		if (cbSaturday->Checked ) {
			sql = sql + ",Saturday = 1";
		}
		else
		{
			sql = sql + ",Saturday = 0";
		}
		if (cbSunday->Checked ) {
			sql = sql + ",Sunday = 1";
		}
		else
		{
			sql = sql + ",Sunday = 0";
		}
		sql = sql + " where ID = " + querydetail->FieldByName("ID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		modify = false;
		return;
	}

	try {
		m_storageID =  (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	} catch (...) {
		MessageBox(0,"请选择正确的店名！","错误" ,MB_OK);
		return;
	}

	sql = "select * from BS_WSaleDiscountInfo where BookInfoID = " + aq->FieldByName("BKID")->AsString + " and StgID = " + IntToStr(m_storageID);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {    //修改
		sql = "update BS_WSaleDiscountInfo set Discount = " + eddiscount->Text +",Starttime = '" + DateToStr(dtpstart->Date) + "',Endtime = '" + DateToStr(dtpend->Date) + " 23:59:59'";
		if (cbMonday->Checked ) {
			sql = sql + ",Monday = 1";
		}
		else
		{
			sql = sql + ",Monday = 0";
		}
		if (cbTuesday->Checked ) {
			sql = sql + ",Tuesday = 1";
		}
		else
		{
			sql = sql + ",Tuesday = 0";
		}
		if (cbWednesday->Checked ) {
			sql = sql + ",Wednesday = 1";
		}
		else
		{
			sql = sql + ",Wednesday = 0";
		}
		if (cbThursday->Checked ) {
			sql = sql + ",Thursday = 1";
		}
		else
		{
			sql = sql + ",Thursday = 0";
		}
		if (cbFriday->Checked) {
			sql = sql + ",Friday = 1";
		}
		else
		{
			sql = sql + ",Friday = 0";
		}
		if (cbSaturday->Checked ) {
			sql = sql + ",Saturday = 1";
		}
		else
		{
			sql = sql + ",Saturday = 0";
		}
		if (cbSunday->Checked ) {
			sql = sql + ",Sunday = 1";
		}
		else
		{
			sql = sql + ",Sunday = 0";
		}
		sql = sql + " where ID = " + query->FieldByName("ID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
	else  //添加
	{
		if (querydetail->State != dsInsert) {
			querydetail->Append();
		}
		querydetail->FieldByName("StgID")->AsInteger = m_storageID;
		querydetail->FieldByName("BookCatalogID")->AsInteger = aq->FieldByName("ID")->AsInteger ;
		querydetail->FieldByName("BookInfoID")->AsInteger = aq->FieldByName("BKID")->AsInteger ;
		querydetail->FieldByName("Discount")->AsFloat =  StrToFloat(eddiscount->Text);
		querydetail->FieldByName("Monday")->Value  = cbMonday->Checked;
		querydetail->FieldByName("Tuesday")->Value  = cbTuesday->Checked;
		querydetail->FieldByName("Wednesday")->Value  = cbWednesday->Checked;
		querydetail->FieldByName("Thursday")->Value  = cbThursday->Checked;
		querydetail->FieldByName("Friday")->Value  = cbFriday->Checked;
		querydetail->FieldByName("Saturday")->Value  = cbSaturday->Checked;
		querydetail->FieldByName("Sunday")->Value  = cbSunday->Checked;
		querydetail->FieldByName("Starttime")->AsString = DateToStr(dtpstart->Date);
		querydetail->FieldByName("Endtime")->AsString = DateToStr(dtpend->Date) + " 23:59:59";
		querydetail->UpdateBatch(arAll);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::dbgdiscountCellClick(TColumn *Column)
{
	modify = true;
	disable();
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::NdeleteClick(TObject *Sender)
{
	if (querydetail->RecordCount > 0) {
		AnsiString sql;
		sql = "delete from BS_WSaleDiscountInfo where id = " + querydetail->FieldByName("ID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		querydetail->Active = false;
		querydetail->Active = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::disable()
{
	if (!querydetail->IsEmpty()) {
		eddiscount->Text = querydetail->FieldByName("Discount")->AsString ;
		cbMonday->Checked =  querydetail->FieldByName("Monday")->Value;
		cbTuesday->Checked = querydetail->FieldByName("Tuesday")->Value;
		cbWednesday->Checked = querydetail->FieldByName("Wednesday")->Value;
		cbThursday->Checked = querydetail->FieldByName("Thursday")->Value;
		cbFriday->Checked = querydetail->FieldByName("Friday")->Value;
		cbSaturday->Checked = querydetail->FieldByName("Saturday")->Value;
		cbSunday->Checked = querydetail->FieldByName("Sunday")->Value;
		dtpstart->Date = querydetail->FieldByName("Starttime")->AsDateTime ;
		dtpend->Date = querydetail->FieldByName("Endtime")->AsDateTime ;
		chall->Checked = true;
	}
	else
	{
    	eddiscount->Text = "" ;
		cbMonday->Checked = false;
		cbTuesday->Checked = false;
		cbWednesday->Checked = false;
		cbThursday->Checked = false;
		cbFriday->Checked = false;
		cbSaturday->Checked = false;
		cbSunday->Checked = false;
		dtpstart->Date = Date();
		dtpend->Date = Date();
	}
}
//---------------------------------------------------------------------------


void __fastcall TFormWsaleDiscount::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
    	if (edtCatalog->Text == "") {
			ChangeCatalogSearchMode();
		}
		else
		{
        	Query();
		}
	}
}
//---------------------------------------------------------------------------

void TFormWsaleDiscount::ChangeCatalogSearchMode()
{

	if (m_catalogSearchMode==4) {
		m_catalogSearchMode=1;
	}else
	{
	m_catalogSearchMode++;  }
	if (m_catalogSearchMode >= 5)
	{
		m_catalogSearchMode = 1;
	}

	switch (m_catalogSearchMode)
	{
	case 1:
		edtCatalog->MaxLength = 13;
		lblCatalog->Caption = "书 号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "自编码";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "书  名";
		break;
	case 4:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "定 价";
		break;
    default:
        break;
	}
}

//---------------------------------------------------------------------------

void TFormWsaleDiscount::Query()
{
	String sql,sql1;
	try {
		m_storageID =  (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	} catch (...) {
		MessageBox(0,"请选择正确的店名！","错误" ,MB_OK);
		return;
	}
	sql = "select BS_BookCatalog.ID,STK_BookInfo.ID as BKID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,STK_BookInfo.ID as STK_BookinfoID,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.AbbreviatedName ,STK_BookstackInfo.name LocalName "
			"from STK_BookInfo  join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(m_storageID);
	sql1 = "select BS_WSaleDiscountInfo.*,convert(varchar(20),BS_WSaleDiscountInfo.Endtime,23) as endtime1,BS_BookCatalog.Name,BS_BookCatalog.ISBN,BS_BookCatalog.Price,BS_PressInfo.AbbreviatedName "
		  "from BS_WSaleDiscountInfo left join BS_BookCatalog on BS_WSaleDiscountInfo.BookCatalogID = BS_BookCatalog.ID "
		  "left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id left join STK_BookInfo on BS_WSaleDiscountInfo.BookInfoID = STK_BookInfo.ID left join STK_BookstackInfo on STK_BookInfo.BkstackID = STK_BookstackInfo.id where BS_WSaleDiscountInfo.StgID = " + IntToStr(m_storageID);
	switch (m_catalogSearchMode) {
		case 1:  //书号
			sql1 = sql1 + " and BS_BookCatalog.Unavailable=1 and (BS_BookCatalog.Barcode='" + edtCatalog->Text.Trim()  + "' or BS_BookCatalog.ISBN = '" + edtCatalog->Text.Trim()  + "')";
			sql = sql + " and BS_BookCatalog.Unavailable=1 and (BS_BookCatalog.Barcode='" + edtCatalog->Text.Trim()  + "' or BS_BookCatalog.ISBN = '" + edtCatalog->Text.Trim()  + "')";
		break;
		case 2:  //自编码
			sql1 = sql1 + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.UserDefCode like '%" + edtCatalog->Text.Trim()  + "%'";
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.UserDefCode like '%" + edtCatalog->Text.Trim()  + "%'";
		break;
		case 3:  //书名
			sql1 = sql1 + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Name like '%" + edtCatalog->Text.Trim()  + "%'";
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Name like '%" + edtCatalog->Text.Trim()  + "%'";
		break;
		case 4:  //定价
			sql1 = sql1 + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Price =" + edtCatalog->Text.Trim();
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Price =" + edtCatalog->Text.Trim();
		break;
    default:
        ;
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	querydetail->Close();
	querydetail->SQL->Clear();
	querydetail->SQL->Add(sql1);
	querydetail->Open();
	disable();
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::DBGrid1CellClick(TColumn *Column)
{
    modify = false;
	if (aq->IsEmpty() ) {
        return;
	}
			AnsiString sql;
			sql = "select * from BS_WSaleDiscountInfo where BookInfoID = " + aq->FieldByName("BKID")->AsString ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount > 0) {
				eddiscount->Text = query->FieldByName("Discount")->AsString ;
				cbMonday->Checked =  querydetail->FieldByName("Monday")->Value;
				cbTuesday->Checked = query->FieldByName("Tuesday")->Value;
				cbWednesday->Checked = query->FieldByName("Wednesday")->Value;
				cbThursday->Checked = query->FieldByName("Thursday")->Value;
				cbFriday->Checked = query->FieldByName("Friday")->Value;
				cbSaturday->Checked = query->FieldByName("Saturday")->Value;
				cbSunday->Checked = query->FieldByName("Sunday")->Value;
				dtpstart->Date = querydetail->FieldByName("Starttime")->AsDateTime ;
				dtpend->Date = querydetail->FieldByName("Endtime")->AsDateTime ;
				chall->Checked = true;
			}
			else
			{
				eddiscount->Text = "" ;
				cbMonday->Checked = false;
				cbTuesday->Checked = false;
				cbWednesday->Checked = false;
				cbThursday->Checked = false;
				cbFriday->Checked = false;
				cbSaturday->Checked = false;
				cbSunday->Checked = false;
				dtpstart->Date = Date();
				dtpend->Date = Date();
				chall->Checked = false;
			}
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::BtnSaveClick(TObject *Sender)
{
	if (modify && !querydetail->IsEmpty() ) {
		excuit();
	}
	else
	{
		if (aq->IsEmpty() ) {
			return;
		}
		if (eddiscount->Text == "") {
			MessageBox(0,"折扣不能为空！","提示" ,MB_ICONWARNING);
			return;
		}
		float discount;
		try {
			discount =  StrToFloat(eddiscount->Text);
		} catch (...) {
			MessageBox(0,"请输入正确的折扣！","提示" ,MB_ICONWARNING );
			return;
		}
		if (discount < 0) {
			MessageBox(0,"折扣不能小于0！","提示" ,MB_ICONWARNING);
			return;
		}
		if (discount > 100) {
			MessageBox(0,"折扣不能大于100！","提示" ,MB_ICONWARNING);
			return;
		}
		int start,end;
		if (dtpstart->Date > dtpend->Date ) {
			MessageBox(0,"结束日期必须大于开始日期！","提示" ,MB_ICONWARNING);
			return;
		}
		if (DBGrid1->SelectedRows->Count == 0) {
			excuit();
		}
		else
		{
			for (int i = 0; i < DBGrid1->SelectedRows->Count ; i++) {
				aq->Bookmark =  DBGrid1->SelectedRows->Items[i];
				excuit();
			}
		}
	}

	querydetail->Active = false;
	querydetail->Active = true;
	disable();
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::N5Click(TObject *Sender)
{
	if (aq->IsEmpty() ) {
        return;
	}
	for (int i = 1; i <= aq->RecordCount; i++) {
		DBGrid1->DataSource->DataSet->RecNo = i;
		DBGrid1->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名:";
	 m_catalogSearchMode = 3;
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "定价:";
	 m_catalogSearchMode = 4;
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码:";
	 m_catalogSearchMode = 2;
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::N1Click(TObject *Sender)
{
	lblCatalog->Caption = "书 号:";
	m_catalogSearchMode = 1;
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::N6Click(TObject *Sender)
{
	String sql;
	sql = "select BS_WSaleDiscountInfo.*,convert(varchar(20),BS_WSaleDiscountInfo.Endtime,23) as endtime1,BS_BookCatalog.Name,BS_BookCatalog.ISBN,BS_BookCatalog.Price,BS_PressInfo.AbbreviatedName "
		  "from BS_WSaleDiscountInfo left join BS_BookCatalog on BS_WSaleDiscountInfo.BookCatalogID = BS_BookCatalog.ID "
		  "left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id left join STK_BookInfo on BS_WSaleDiscountInfo.BookInfoID = STK_BookInfo.ID left join STK_BookstackInfo on STK_BookInfo.BkstackID = STK_BookstackInfo.id where STK_BookstackInfo.StgID = " + IntToStr(m_storageID);
	querydetail->Close();
	querydetail->SQL->Clear();
	querydetail->SQL->Add(sql);
	querydetail->Open();
	disable();
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::eddiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized;
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == 115 ) {    //保存
		BtnSave->Click();
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

void __fastcall TFormWsaleDiscount::cbstorageSelect(TObject *Sender)
{
	AnsiString sql;
	try {
		m_storageID =  (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	} catch (...) {
		MessageBox(0,"请选择正确的店名！","错误" ,MB_OK);
		return;
	}
	sql = "select BS_WSaleDiscountInfo.*,convert(varchar(20),BS_WSaleDiscountInfo.Endtime,23) as endtime1,BS_BookCatalog.Name,BS_BookCatalog.ISBN,BS_BookCatalog.Price,BS_PressInfo.AbbreviatedName "
		  "from BS_WSaleDiscountInfo left join BS_BookCatalog on BS_WSaleDiscountInfo.BookCatalogID = BS_BookCatalog.ID "
		  "left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id left join STK_BookInfo on BS_WSaleDiscountInfo.BookInfoID = STK_BookInfo.ID left join STK_BookstackInfo on STK_BookInfo.BkstackID = STK_BookstackInfo.id where BS_WSaleDiscountInfo.StgID = " + IntToStr(m_storageID);
	querydetail->Close();
	querydetail->SQL->Clear();
	querydetail->SQL->Add(sql);
	querydetail->Open();
	disable();
}
//---------------------------------------------------------------------------

void __fastcall TFormWsaleDiscount::challClick(TObject *Sender)
{
	if (chall->Checked ) {
		cbMonday->Checked = true;
		cbTuesday->Checked = true;
		cbWednesday->Checked = true;
		cbThursday->Checked = true;
		cbFriday->Checked = true;
		cbSaturday->Checked = true;
		cbSunday->Checked = true;
	}
	else
	{
		cbMonday->Checked = false;
		cbTuesday->Checked = false;
		cbWednesday->Checked = false;
		cbThursday->Checked = false;
		cbFriday->Checked = false;
		cbSaturday->Checked = false;
		cbSunday->Checked = false;
	}
}
//---------------------------------------------------------------------------

