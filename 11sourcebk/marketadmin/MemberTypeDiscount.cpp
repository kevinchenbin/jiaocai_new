//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberTypeDiscount.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TfrmMemberDiscount *frmMemberDiscount;
//---------------------------------------------------------------------------
__fastcall TfrmMemberDiscount::TfrmMemberDiscount(TComponent* Owner,TADOConnection* con,int stgid)
	: TForm(Owner)
{
	fstgid = stgid;
	query->Connection = con;
	aq->Connection = con;
	querydetail->Connection = con;
	String sql ;
	sql = "select ID,Name from SYS_StorageInfo";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	m_catalogSearchMode = 1;
	while (!query->Eof )
	{
		cbstorage->AddItem(query->FieldByName("Name")->AsString,(TObject*)query->FieldByName("ID")->AsInteger );
		query->Next();
	}
	cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)fstgid);

	sql = "select Master from SYS_StorageInfo where id = " + IntToStr(fstgid);
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

	sql = "select IDType,Type from CUST_MemberType";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof )
	{
		cbmembertype->AddItem(query->FieldByName("Type")->AsString ,(TObject*)query->FieldByName("IDType")->AsInteger );
		query->Next();
	}
	query->First();
	cbmembertype->ItemIndex = cbmembertype->Items->IndexOfObject((TObject*)query->FieldByName("IDType")->AsInteger);
	dtpstart->Date = Date();
	dtpend->Date = Date();
	//打折方案初始显示
	sql = "select BS_MemberTypeDiscountInfo.*,convert(varchar(20),BS_MemberTypeDiscountInfo.Endtime,23) as endtime1,CUST_MemberType.Type as typename,BS_BookCatalog.Name,BS_BookCatalog.ISBN,BS_BookCatalog.Price,BS_PressInfo.AbbreviatedName,BS_BookCatalog.Price*BS_MemberTypeDiscountInfo.Discount/100 as dprice "
		  "from BS_MemberTypeDiscountInfo left join BS_BookCatalog on BS_MemberTypeDiscountInfo.BookCatalogID = BS_BookCatalog.ID left join CUST_MemberType on BS_MemberTypeDiscountInfo.MemberType = CUST_MemberType.IDType "
		  "left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id left join STK_BookInfo on BS_MemberTypeDiscountInfo.BookInfoID = STK_BookInfo.ID left join STK_BookstackInfo on STK_BookInfo.BkstackID = STK_BookstackInfo.id where STK_BookstackInfo.StgID = " + IntToStr(stgid);
	querydetail->Close();
	querydetail->SQL->Clear();
	querydetail->SQL->Add(sql);
	querydetail->Open();
	((TFloatField *)querydetail->FieldByName("dprice"))->DisplayFormat = "##0.00";
	((TFloatField *)querydetail->FieldByName("Discount"))->DisplayFormat = "##0.00%";
	disable();
	modify = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemberDiscount::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)

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

void TfrmMemberDiscount::ChangeCatalogSearchMode()
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
		lblCatalog->Caption = "书  名";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "自编码";
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

void TfrmMemberDiscount::Query()
{
	String sql,sql1;
	int stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	sql = "select BS_BookCatalog.ID,STK_BookInfo.ID as BKID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,STK_BookInfo.ID as STK_BookinfoID,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.AbbreviatedName ,STK_BookstackInfo.name LocalName "
			"from STK_BookInfo  join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(stgid);
	sql1 = "select BS_MemberTypeDiscountInfo.*,convert(varchar(20),BS_MemberTypeDiscountInfo.Endtime,23) as endtime1,CUST_MemberType.Type as typename,BS_BookCatalog.Name,BS_BookCatalog.ISBN,BS_BookCatalog.Price,BS_PressInfo.AbbreviatedName,BS_BookCatalog.Price*BS_MemberTypeDiscountInfo.Discount/100 as dprice "
		  "from BS_MemberTypeDiscountInfo left join BS_BookCatalog on BS_MemberTypeDiscountInfo.BookCatalogID = BS_BookCatalog.ID left join CUST_MemberType on BS_MemberTypeDiscountInfo.MemberType = CUST_MemberType.IDType "
		  "left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id left join STK_BookInfo on BS_MemberTypeDiscountInfo.BookInfoID = STK_BookInfo.ID left join STK_BookstackInfo on STK_BookInfo.BkstackID = STK_BookstackInfo.id where STK_BookstackInfo.StgID = " + IntToStr(stgid);
	switch (m_catalogSearchMode) {
		case 1:  //书号
			sql1 = sql1 + " and BS_BookCatalog.Unavailable=1 and (BS_BookCatalog.Barcode='" + edtCatalog->Text.Trim()  + "' or BS_BookCatalog.ISBN = '"+ edtCatalog->Text.Trim() + "')";
			sql = sql + " and BS_BookCatalog.Unavailable=1 and (BS_BookCatalog.Barcode='" + edtCatalog->Text.Trim()  + "' or BS_BookCatalog.ISBN = '"+ edtCatalog->Text.Trim() + "')";
		break;
		case 3:  //自编码
			sql1 = sql1 + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.UserDefCode like '%" + edtCatalog->Text.Trim()  + "%'";
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.UserDefCode like '%" + edtCatalog->Text.Trim()  + "%'";
		break;
		case 2:  //书名
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
void __fastcall TfrmMemberDiscount::disable()
{
	if (querydetail->IsEmpty() ) {
		eddiscount->Text = "" ;
		edprice->Text = "";
		dtpstart->Date = Date();
		dtpend->Date = Date();
	}
	else
	{
		edprice->Text = FormatFloat("##0.00",querydetail->FieldByName("dprice")->AsFloat);
		eddiscount->Text = FormatFloat("##0.00",querydetail->FieldByName("Discount")->AsFloat);
		dtpstart->Date = querydetail->FieldByName("Starttime")->AsDateTime ;
		dtpend->Date = querydetail->FieldByName("Endtime")->AsDateTime ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::BtnSaveClick(TObject *Sender)
{
	if (modify && !querydetail->IsEmpty()) {
		excuit();
	}
	else
	{
		if (aq->IsEmpty() ) {
			return;
		}
		if (eddiscount->Text == "") {
			MessageBox(0,"折扣不能为空！","提示" ,MB_ICONWARNING );
			return;
		}
		float  discount;
		try {
			discount =  StrToFloat(eddiscount->Text);
		} catch (...) {
			MessageBox(0,"请输入正确的折扣！","提示" ,MB_ICONWARNING );
			return;
		}

		if (discount < 0) {
			MessageBox(0,"折扣不能小于0！","提示" ,MB_ICONWARNING );
			return;
		}
		if (discount > 100) {
			MessageBox(0,"折扣不能大于100！","提示" ,MB_ICONWARNING );
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
	((TFloatField *)querydetail->FieldByName("dprice"))->DisplayFormat = "##0.00";
	((TFloatField *)querydetail->FieldByName("Discount"))->DisplayFormat = "##0.00%";
	disable();
}
//---------------------------------------------------------------------------
void TfrmMemberDiscount::excuit()
{
	AnsiString sql;
	int memtype, stgid;
	try {
		memtype = (int)cbmembertype->Items->Objects[cbmembertype->ItemIndex];
	} catch (...) {
		MessageBox(0,"请选择正确的会员类型！","提示" ,MB_ICONWARNING );
		return;
	}
	try {
		stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	} catch (...) {
    	MessageBox(0,"请选择正确的店名！","提示" ,MB_ICONWARNING );
		return;
	}
	if (modify) {
    	sql = "update BS_MemberTypeDiscountInfo set Discount = " + eddiscount->Text +",Starttime = '" + DateToStr(dtpstart->Date) + "',Endtime = '" + DateToStr(dtpend->Date) + " 23:59:59'";
		sql = sql + " where ID = " + querydetail->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		modify = false;
		return;
	}

	sql = "select * from BS_MemberTypeDiscountInfo where BookInfoID = " + aq->FieldByName("BKID")->AsString + " and MemberType = " + IntToStr(memtype) + " and StgID = " + IntToStr(stgid)  ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {    //修改
		sql = "update BS_MemberTypeDiscountInfo set Discount = " + eddiscount->Text +",Starttime = '" + DateToStr(dtpstart->Date) + "',Endtime = '" + DateToStr(dtpend->Date) + " 23:59:59'";
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
		querydetail->FieldByName("StgID")->AsInteger = stgid;
		querydetail->FieldByName("MemberType")->AsInteger = memtype;
		querydetail->FieldByName("Discount")->AsString = eddiscount->Text;
		querydetail->FieldByName("BookCatalogID")->AsInteger = aq->FieldByName("ID")->AsInteger ;
		querydetail->FieldByName("BookInfoID")->AsInteger = aq->FieldByName("BKID")->AsInteger ;
		querydetail->FieldByName("Starttime")->AsString = DateToStr(dtpstart->Date);
		querydetail->FieldByName("Endtime")->AsString = DateToStr(dtpend->Date) + " 23:59:59";
		querydetail->UpdateBatch(arAll);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::DBGrid1CellClick(TColumn *Column)
{
    modify = false;
	if (aq->IsEmpty() ) {
        return;
	}
		int memtype ;
		try {
			memtype = (int)cbmembertype->Items->Objects[cbmembertype->ItemIndex];
		} catch (...) {
			MessageBox(0,"请选择正确的会员类型！","提示" ,MB_ICONWARNING );
			return;
		}
		AnsiString sql;
		sql = "select BS_MemberTypeDiscountInfo.*,Discount*BS_BookCatalog.price/100 as dprice from BS_MemberTypeDiscountInfo "
				" left join BS_BookCatalog on BS_MemberTypeDiscountInfo.bookcatalogid = BS_BookCatalog.id where BookInfoID = " + aq->FieldByName("BKID")->AsString + " and MemberType = " + IntToStr(memtype);
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount > 0) {
				edprice->Text = FormatFloat("##0.00",query->FieldByName("dprice")->AsFloat);
				eddiscount->Text = FormatFloat("##0.00",query->FieldByName("Discount")->AsFloat);
				dtpstart->Date = querydetail->FieldByName("Starttime")->AsDateTime ;
				dtpend->Date = querydetail->FieldByName("Endtime")->AsDateTime ;
			}
			else
			{
				eddiscount->Text = "" ;
                edprice->Text = "";
				dtpstart->Date = Date();
				dtpend->Date = Date();
			}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::N1Click(TObject *Sender)
{
	lblCatalog->Caption = "书 号:";
	m_catalogSearchMode = 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书 名:";
	m_catalogSearchMode = 2;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码:";
	m_catalogSearchMode = 3;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "定 价:";
	m_catalogSearchMode = 4;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::N5Click(TObject *Sender)
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

void __fastcall TfrmMemberDiscount::NdeleteClick(TObject *Sender)
{
	if (querydetail->RecordCount > 0) {
		AnsiString sql;
		sql = "delete from BS_MemberTypeDiscountInfo where id = " + querydetail->FieldByName("ID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		querydetail->Active = false;
		querydetail->Active = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::N6Click(TObject *Sender)
{
	String sql;
	int stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	sql = "select BS_MemberTypeDiscountInfo.*,convert(varchar(20),BS_MemberTypeDiscountInfo.Endtime,23) as endtime1,CUST_MemberType.Type as typename,BS_BookCatalog.Name,BS_BookCatalog.ISBN,BS_BookCatalog.Price,BS_PressInfo.AbbreviatedName,BS_BookCatalog.Price*BS_MemberTypeDiscountInfo.Discount/100 as dprice "
		  "from BS_MemberTypeDiscountInfo left join BS_BookCatalog on BS_MemberTypeDiscountInfo.BookCatalogID = BS_BookCatalog.ID left join CUST_MemberType on BS_MemberTypeDiscountInfo.MemberType = CUST_MemberType.IDType "
		  "left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id left join STK_BookInfo on BS_MemberTypeDiscountInfo.BookInfoID = STK_BookInfo.ID left join STK_BookstackInfo on STK_BookInfo.BkstackID = STK_BookstackInfo.id where STK_BookstackInfo.StgID = " + IntToStr(stgid);
	querydetail->Close();
	querydetail->SQL->Clear();
	querydetail->SQL->Add(sql);
	querydetail->Open();
	((TFloatField *)querydetail->FieldByName("dprice"))->DisplayFormat = "##0.00";
	((TFloatField *)querydetail->FieldByName("Discount"))->DisplayFormat = "##0.00%";
	disable();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::eddiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
	if (Key == '\r') {
		if (modify) {
			if (querydetail->IsEmpty() ) {
				return;
			}
            float discount;
			try {
				discount = StrToFloat(eddiscount->Text);
			} catch (...) {
				return;
			}
			edprice->Text = FormatFloat("##0.00",querydetail->FieldByName("Price")->AsFloat*discount/100);
		}
		else
		{
        	if (aq->IsEmpty() ) {
				return;
			}
			float discount;
			try {
				discount = StrToFloat(eddiscount->Text);
			} catch (...) {
				return;
			}
			edprice->Text = FormatFloat("##0.00",aq->FieldByName("Price")->AsFloat*discount/100);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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

void __fastcall TfrmMemberDiscount::cbstorageSelect(TObject *Sender)
{
	AnsiString sql;
	try {
		fstgid =  (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	} catch (...) {
		MessageBox(0,"请选择正确的店名！","错误" ,MB_OK);
		return;
	}
	sql = "select BS_MemberTypeDiscountInfo.*,convert(varchar(20),BS_MemberTypeDiscountInfo.Endtime,23) as endtime1,CUST_MemberType.Type as typename,BS_BookCatalog.Name,BS_BookCatalog.ISBN,BS_BookCatalog.Price,BS_PressInfo.AbbreviatedName,BS_BookCatalog.Price*BS_MemberTypeDiscountInfo.Discount/100 as dprice "
		  "from BS_MemberTypeDiscountInfo left join BS_BookCatalog on BS_MemberTypeDiscountInfo.BookCatalogID = BS_BookCatalog.ID left join CUST_MemberType on BS_MemberTypeDiscountInfo.MemberType = CUST_MemberType.IDType "
		  "left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id left join STK_BookInfo on BS_MemberTypeDiscountInfo.BookInfoID = STK_BookInfo.ID left join STK_BookstackInfo on STK_BookInfo.BkstackID = STK_BookstackInfo.id where STK_BookstackInfo.StgID = " + IntToStr(fstgid);
	querydetail->Close();
	querydetail->SQL->Clear();
	querydetail->SQL->Add(sql);
	querydetail->Open();
	((TFloatField *)querydetail->FieldByName("dprice"))->DisplayFormat = "##0.00";
	((TFloatField *)querydetail->FieldByName("Discount"))->DisplayFormat = "##0.00%";
	disable();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMemberDiscount::edpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
	if (Key == '\r') {
		if (modify) {
			if (querydetail->IsEmpty() ) {
				return;
			}
			float price;
			try {
				price = StrToFloat(edprice->Text);
			} catch (...) {
				return;
			}
			eddiscount->Text = FormatFloat("##0.00",price*100/querydetail->FieldByName("Price")->AsFloat) ;
		}
		else
		{
        	if (aq->IsEmpty() ) {
				return;
			}
			float price;
			try {
				price = StrToFloat(edprice->Text);
			} catch (...) {
				return;
			}
			eddiscount->Text = FormatFloat("##0.00",price*100/aq->FieldByName("Price")->AsFloat) ;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::dbgdiscountCellClick(TColumn *Column)
{
    modify = true;
	disable();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberDiscount::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

