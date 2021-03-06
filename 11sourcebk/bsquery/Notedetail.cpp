//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Notedetail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmNotedetail *frmNotedetail;
//---------------------------------------------------------------------------
__fastcall TfrmNotedetail::TfrmNotedetail(TComponent* Owner,String headercode,int Type,TADOConnection *con,int modle,int userid)
	: TForm(Owner)
{
	type = Type;
	String sql;
	aq1->Connection = con;
	if (type == 1) {   //入库
		sql = "select ReadPurview from SYS_GroupAction left join SYS_UserGroup on SYS_GroupAction.GroupID = SYS_UserGroup.GroupID "
			" left join sys_action A1 on SYS_GroupAction.actionid = A1.Code "
			" left join sys_action A2 ON A2.CODE = A1.parent "
			" where A1.ActionName = '折扣查询' "
			" and A2.ActionName = '入库查询' "
			" and SYS_UserGroup.Userid = " + IntToStr(userid);
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->Open();
		if (aq1->FieldByName("ReadPurview")->AsBoolean) {
			DBGrid1->Columns->Items[7]->Visible = true;
			DBGrid1->Columns->Items[9]->Visible = true;
		}
		else
		{
			DBGrid1->Columns->Items[7]->Visible = false;
			DBGrid1->Columns->Items[9]->Visible = false;
		}

		sql = "select A.amount,A.discount,A.DiscountedPrice+at.camount*0.01*A.Discount*BS_BookCatalog.price DiscountedPrice, A.FixedPrice+at.camount*BS_BookCatalog.price as FixedPrice, A.amount +at.camount totalamount, "
			  " at.camount, BS_BookCatalog.ISBN,BS_BookCatalog.Name as bookname,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookType.Name as typename,BS_PressInfo.AbbreviatedName "
			  "from BS_StorageNote A left join STK_BookInfo on A.BkInfoID = STK_BookInfo.ID left join "
			  "BS_StorageNoteHeader ON A.StgNtHeaderID = BS_StorageNoteHeader.ID left join "
			  "BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.id left join "
			  "BS_BookType on BS_BookCatalog.smallBookTypeID = BS_BookType.id left join "
			  " BS_StorageNote_attachment at ON A.ID = at.BS_StorageNoteID left join "
			  "BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id where BS_StorageNoteHeader.StgNtCode = " + headercode;
		DBGrid1->Columns->Items[14]->Visible = false;
		DBGrid1->Columns->Items[10]->Visible = false;
		DBGrid1->Columns->Items[11]->Visible = false;
		DBGrid1->Columns->Items[12]->Visible = false;
		DBGrid1->Columns->Items[13]->Visible = false;
	}
	else if (type == 2)     //发货
	{
		this->Caption = "发货单详细信息";

		sql = "select ReadPurview from SYS_GroupAction left join SYS_UserGroup on SYS_GroupAction.GroupID = SYS_UserGroup.GroupID "
			" left join sys_action A1 on SYS_GroupAction.actionid = A1.Code "
			" left join sys_action A2 ON A2.CODE = A1.parent "
			" where A1.ActionName = '折扣查询' "
			" and A2.ActionName = '发货查询' "
			" and SYS_UserGroup.Userid = " + IntToStr(userid);
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->Open();
		if (aq1->FieldByName("ReadPurview")->AsBoolean) {
			DBGrid1->Columns->Items[7]->Visible = true;
			DBGrid1->Columns->Items[9]->Visible = true;
		}
		else
		{
			DBGrid1->Columns->Items[7]->Visible = false;
			DBGrid1->Columns->Items[9]->Visible = false;
		}

		sql = "select A.*,BS_BookCatalog.ISBN,BS_BookCatalog.Name as bookname,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookType.Name as typename,BS_PressInfo.AbbreviatedName "
			  "from BS_WsaleNote A left join STK_BookInfo on A.BkInfoID = STK_BookInfo.ID left join "
			  "BS_WsaleNoteHeader on A.WsaleNtHeaderID = BS_WsaleNoteHeader.id left join "
			  "BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.id left join "
			  "BS_BookType on BS_BookCatalog.smallBookTypeID = BS_BookType.id left join "
			  "BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id where BS_WsaleNoteHeader.WsaleNtCode = " + headercode;
		DBGrid1->Columns->Items[14]->Visible = false;
		DBGrid1->Columns->Items[10]->Visible = false;
		DBGrid1->Columns->Items[11]->Visible = false;
		DBGrid1->Columns->Items[12]->Visible = false;
		DBGrid1->Columns->Items[13]->Visible = false;
	}
	else if (type == 3) {  //盘点
		this->Caption = "盘点单详细信息";
		if (modle == 0) {        //局部盘点
			sql = "select B.ISBN,B.Name as bookname,B.Price,B.Author,BS_BookType.Name as typename,P.AbbreviatedName,"
				 "A.AdjustAmount as ShouldAmount,A.blanceamount AS Balance,A.bk1 as ActualAmount,B.price*A.blanceamount as BFixedPrice,S.Cbprice*A.blanceamount as BDiscountedPrice "
				 " from STK_stockxuyiDetail A "
				 " left join bs_bookcatalog B On A.bkcatalogID = B.ID "
				 " left join BS_BookType on B.smallBookTypeID = BS_BookType.id "
				 " left join bs_pressinfo P ON B.PressID = P.ID "
				 " left join STK_bookinfo S ON A.bkcatalogID = S.bkcatalogID and A.SupplierID = S.SupplierID "
				 " where A.AdjustHeaderID = " + headercode;
		}
		else       //实库盘点
		{
			sql = "select STK_StockInventories .*,"
				" BS_BookCatalog.UserDefCode,BS_BookCatalog.Author,BS_BookType.Name as typename,BS_PressInfo.AbbreviatedName,STK_StockInventories.Balance*BS_BookCatalog.Price as BFixedPrice,STK_StockInventories.Balance*STK_BookInfo.Cbprice AS BDiscountedPrice from STK_StockInventories "
				" left join STK_BookInfo on STK_StockInventories.STK_BookInfoID= STK_BookInfo.id "
				" left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.id "
				" left join BS_BookType on BS_BookCatalog.smallBookTypeID = BS_BookType.id "
				" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
				" where STK_StockInventories.NoteCode = " + headercode;
		}
		DBGrid1->Columns->Items[9]->Visible = false;
		DBGrid1->Columns->Items[6]->Visible = false;
		DBGrid1->Columns->Items[7]->Visible = false;
		DBGrid1->Columns->Items[8]->Visible = false;
	}
	else if (type == 4)     //订单
	{
		this->Caption = "订单详细信息";
		sql = "select A.*,BS_BookCatalog.ISBN,BS_BookCatalog.Name as bookname,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookType.Name as typename,BS_PressInfo.AbbreviatedName "
			  "from BS_OrderNote A left join BS_OrderNoteHeader on A.OrderNtHeaderID = BS_OrderNoteHeader.id left join "
			  "BS_BookCatalog on A.BkcatalogID = BS_BookCatalog.id left join "
			  "BS_BookType on BS_BookCatalog.smallBookTypeID = BS_BookType.id left join "
			  "BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id where BS_OrderNoteHeader.OrderNtCode = " + headercode;
		DBGrid1->Columns->Items[10]->Title->Caption = "已发数量";
		DBGrid1->Columns->Items[11]->Title->Caption = "未发数量";
		DBGrid1->Columns->Items[12]->Title->Caption = "锁定数量";
		DBGrid1->Columns->Items[13]->Visible = false;
		DBGrid1->Columns->Items[14]->Visible = false;
	}
	else if (type == 5)     //采购
	{
		this->Caption = "采购详细信息";
		sql = "select A.*,BS_BookCatalog.ISBN,BS_BookCatalog.Name as bookname,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookType.Name as typename,BS_PressInfo.AbbreviatedName "
			  "from BS_ProcureNote A left join BS_ProcureNoteHeader on A.ProcureNtHeaderID = BS_ProcureNoteHeader.id left join "
			  "BS_BookCatalog on A.BkcatalogID = BS_BookCatalog.id left join "
			  "BS_BookType on BS_BookCatalog.smallBookTypeID = BS_BookType.id left join "
			  "BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id where BS_ProcureNoteHeader.ProcureNtCode = " + headercode;
		DBGrid1->Columns->Items[10]->Title->Caption = "已到数量";
		DBGrid1->Columns->Items[11]->Title->Caption = "未到数量";
		DBGrid1->Columns->Items[12]->Visible = false;
		DBGrid1->Columns->Items[13]->Visible = false;
		DBGrid1->Columns->Items[14]->Visible = false;
	}
	else if (type == 6)     //配送
	{
		this->Caption = "配送详细信息";
		sql = "select A.*,BS_BookCatalog.ISBN,BS_BookCatalog.Name as bookname,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookType.Name as typename,BS_PressInfo.AbbreviatedName "
			" from BS_ZN_DiaoNote A left join BS_ZN_DiaoNoteHeader on A.DiaoNtHeaderID = BS_ZN_DiaoNoteHeader.id left join "
			" stk_bookinfo on A.Bkinfoid = stk_bookinfo.id left join "
			" BS_BookCatalog on stk_bookinfo.bkcatalogid = BS_BookCatalog.id left join "
			" BS_BookType on BS_BookCatalog.smallBookTypeID = BS_BookType.id left join "
			" BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id where BS_ZN_DiaoNoteHeader.ZNDiaoNtCode = " + headercode;
		DBGrid1->Columns->Items[10]->Title->Caption = "申请数量";
		DBGrid1->Columns->Items[11]->Title->Caption = "确认数量";
		DBGrid1->Columns->Items[12]->Visible = false;
		DBGrid1->Columns->Items[13]->Visible = false;
		DBGrid1->Columns->Items[14]->Visible = false;
	}else if (type == 7) {
          	this->Caption = "订单详细信息";
		sql = "   select A.isbn ,A.price,A.author,'' typename,A.amount ,A.discount,A.fixedprice,A.discountedprice "
			 " ,A.name bookname,A.press AbbreviatedName,A.sended ShouldAmount,A.amount -sended ActualAmount, locknum balance ,0 Bfixedprice, "
			 " 0 Bdiscountedprice,0 camount,0 totalamount from dbo.C_Order_Detail A  left join C_BS_OrderNoteHeader B on A.orderNtHeaderID=B.ID  "
			  " where B.OrderNtCode =" + headercode;
		DBGrid1->Columns->Items[10]->Title->Caption = "已发数量";
		DBGrid1->Columns->Items[11]->Title->Caption = "未发数量";
		DBGrid1->Columns->Items[12]->Title->Caption = "锁定数量";
       	DBGrid1->Columns->Items[6]->Title->Caption = "数量";
		DBGrid1->Columns->Items[13]->Visible = false;
		DBGrid1->Columns->Items[14]->Visible = false;
		DBGrid1->Columns->Items[15]->Visible = false;
		DBGrid1->Columns->Items[16]->Visible = false;
		  }
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (type == 4) {
		DBGrid1->Columns->Items[10]->Field = aq->FieldByName("SendAmount");
		DBGrid1->Columns->Items[11]->Field = aq->FieldByName("UnsendAmount");
		DBGrid1->Columns->Items[12]->Field = aq->FieldByName("localnum");
	}
	if (type == 5) {
		DBGrid1->Columns->Items[10]->Field = aq->FieldByName("RecAmount");
		DBGrid1->Columns->Items[11]->Field = aq->FieldByName("UnrecAmount");
	}
	if (type == 6) {
		DBGrid1->Columns->Items[10]->Field = aq->FieldByName("amountask");
		DBGrid1->Columns->Items[11]->Field = aq->FieldByName("amountbk");
	}
	if (type == 3) {
    	((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("BFixedPrice"))->DisplayFormat = "0.00";
		((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("BDiscountedPrice"))->DisplayFormat = "0.00";
	}
	else
	{
    	((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "0.00";
		((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "0.00";
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmNotedetail::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmNotedetail::BtnExportClick(TObject *Sender)
{
	if (aq->IsEmpty() ) {
    	return;
	}
	AnsiString temptext,path;

	savedlg->FileName = this->Caption ;
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
		path =  DBPath;
	}
	else
	{
		return;
	}
	if(FileExists(path))
	try {
		DeleteFileA(path);
	} catch (...) {
		return ;
	}

	Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",false);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");

	int n=0;

	int t1= 0;
	temptext = "\n";
	for(int q=0;q<DBGrid1->FieldCount-1 ;++q)
	{
		if (DBGrid1->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = DBGrid1->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
		}
	}

	int t2 = DBGrid1->DataSource ->DataSet ->RecordCount ;

	DBGrid1->DataSource ->DataSet ->First();
	DBGrid1->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<DBGrid1->Columns ->Count  ;j++)
		{
			if (DBGrid1->Columns->Items[j-1]->Visible == true) {
				if (DBGrid1->Columns ->Items [j-1]->FieldName == "ISBN") {
                	t1++;
					temptext = "'"+ DBGrid1->DataSource ->DataSet ->FieldByName(DBGrid1->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );
				}
				else
				{
					t1++;
					temptext = DBGrid1->DataSource ->DataSet ->FieldByName(DBGrid1->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
			}
		}
		DBGrid1->DataSource ->DataSet ->Next() ;
	}

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+1,t1)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	DBGrid1->DataSource ->DataSet->EnableControls();

	try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (...) {
	}
}
//---------------------------------------------------------------------------

