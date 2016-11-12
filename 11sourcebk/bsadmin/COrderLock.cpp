//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "COrderLock.h"
#include "UnitSelectClient.h"
#include "SelectCatalogForm.h"
#include "SetNotesForm.h"
#include "UnitClient.h"
#include "QryNoteCodeForm.h"
#include "..\..\supplier\detailemessage.h"
#include "Addsyslog.h"
#include "NewBookinput.h"
#include "bookQuery.h"
#include "UnitSelectClient.h"
#include "orderExcelImport.h"
#include "UnitClient.h"
#include "NewBookModify.h"
#include "Ordermodify.h"
#include "Unitchongfuorder.h"
#include "Unitorderquery.h"
#include "Unitfindbook.h"
#include "Unitgenhuanselect.h"
#include "NewBookinput1.h"
#include "retailbookup.h"
#include "bookhistory.h"
#include "settypress.h"
#include "Unitclasscode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzLabel"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzDBGrid"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
TfrmCnetorderlock *frmCnetorderlock;
//---------------------------------------------------------------------------
__fastcall TfrmCnetorderlock::TfrmCnetorderlock(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	m_module = MTOrder;
	ClientID = -1;
	WindowState = wsMaximized ;
	dgdetail->OnDrawColumnCell=dgdetailDrawColumnCell;
}
//---------------------------------------------------------------------------
void TfrmCnetorderlock::init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	UserID = li->userID ;
	UserName =  li->UserName ;
	StgID = li->storageID ;
	fcon = li->con ;
	query->Connection = li->con;
	querypress->Connection = fcon;
	queryorder->Connection = fcon;
	aqorderdetail->Connection = fcon;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	AnsiString sql;

	sql = "select orprinttitle,orcontact,ortel,oraddress,orprintbk from sys_printtitle where stgid = " + IntToStr(m_storageID);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	printbk = query->FieldByName("orprintbk")->AsAnsiString ;
	printtitle = query->FieldByName("orprinttitle")->AsAnsiString ;
	contact = query->FieldByName("orcontact")->AsAnsiString ;
	tel = query->FieldByName("ortel")->AsAnsiString ;
	address = query->FieldByName("oraddress")->AsAnsiString ;

	delete aq;
	aqupdatehead->Connection = fcon;
	try
	{
		aqhd->Connection = fcon;
		aqhd->Active = false;
		aqhd->Parameters->ParamByName("stgid")->Value = StgID;
		aqhd->Parameters->ParamByName("type")->Value = type;
		aqhd->Active = true;
	}
	catch(Exception &E)
	{
	  	ShowMessage(E.Message);
	}
}
//---------------------------------------------------------------------------

AnsiString TfrmCnetorderlock::GetField(AnsiString sql,AnsiString Field)
{
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	return	aq->FieldByName(Field)->AsAnsiString ;
	delete aq;
}
//---------------------------------------------------------------------------
void TfrmCnetorderlock::ExecSQL(AnsiString sql)
{
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}

//---------------------------------------------------------------------------

void TfrmCnetorderlock::RefreshHead(int headerid)
{
	AnsiString sql;
	sql = "select A.*,S.ID,OrderUser as Clientname,S.Name as StgName "
			" from C_BS_OrderNoteHeader A left join SYS_StorageInfo S ON A.stgID = S.ID  "
			" where A.id = " + IntToStr(headerid) ;
	aqupdatehead->Close();
	aqupdatehead->SQL->Clear();
	aqupdatehead->SQL->Add(sql);
	aqupdatehead->Open();

  //	ClientID = aqupdatehead->FieldByName("vendorID")->AsInteger;
	membk->Text =  aqupdatehead->FieldByName("Remarks")->AsString;
	edtclient->Text= aqupdatehead->FieldByName("Clientname")->AsString;
	//ClientView();
	RefreshDetail();                  //已锁定库存
	if (aqupdatehead->FieldByName("clientsure")->AsInteger == 1){
		lab->Visible = true;
		lab->Caption = "";
	   //	dgdetail->Columns->Items[24]->ReadOnly = false;
	}
	else if (aqupdatehead->FieldByName("clientsure")->AsInteger == 2) {
    	lab->Visible = true;
		lab->Caption = "锁定数量已确认";
	  //	dgdetail->Columns->Items[24]->ReadOnly = true;
	}
	else
	{
		lab->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::dbnClick(TObject *Sender, TNavigateBtn Button)
{
	RefreshHead(aqhd->FieldByName("ID")->AsInteger );
}
//---------------------------------------------------------------------------

void TfrmCnetorderlock::RefreshDetail()
{
	AnsiString sql;
   /*	sql = "select RANK() OVER(order by A.ID desc) as xuhao, A.id, A.OrderNtHeaderID,B.ISBN,B.name as bookname,P.AbbreviatedName,B.price,B.pressID,A.amount,A.Discount,A.localnum,A.xuxiao,A.class,A.newbook,"
		" A.FixedPrice,A.Discountedprice,A.bk , A.bkcatalogid,A.SendAmount,A.UnSendAmount,case when A.state = 0 then '有效' else '无效' end as state1,B.PressCount,B.UserDefCode,B.Author, "
		" A.xiaoqu,A.xueyuan,A.course,A.incode,A.teacher,A.telphone,A.needprocurenum,"
		" A.yamount,A.ylocalnum,case when A.ystate = 0 then '有效' when A.ystate = 1 then  '无效' else '' end as state2,A.ystate, "
		" C.stkamount as bookamount,C.usableamount, case when A.needprocurenum = 10 then '√' else '' end as prostate "
		" from BS_OrderNote A "
		" left join BS_OrderNoteHeader on A.orderNtHeaderID = BS_OrderNoteHeader.id "
		" left join bs_bookcatalog B On A.bkcatalogID = B.ID "
		" left join bs_pressinfo P ON B.pressID = P.ID "
		" left join Order_lock C on A.bkcatalogID = C.BkcatalogID and BS_OrderNoteHeader.stgid = C.stgid "
		" where A.orderNtHeaderID = " + aqupdatehead->FieldByName("ID")->AsString;
       */


	  sql = 	"  select RANK() OVER(order by corderid desc) as xuhao,corderid id,  "
		"  orderntheaderid,isbn,name bookname,press AbbreviatedName, "
		"  price,pressinfoid pressid,amount,discount,locknum,  "
		"  FixedPrice,Discountedprice,backinfo,Orderdetailbk,bk,catalogid bkcatalogid, "
		"  sended sendamount,UnSendAmount,presscount,Author, "
		"  needprocurenum,kykc from C_Order_Detail "
		"  where orderntheaderid = " + aqupdatehead->FieldByName("ID")->AsString;

	aqorderdetail->Active = false;
	aqorderdetail->SQL->Clear();
	aqorderdetail->SQL->Add(sql);
	aqorderdetail->Active = true;

	if (aqorderdetail->RecordCount > 0) {
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "￥0.00";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("fixedPrice"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Discountedprice"))->DisplayFormat = "￥###,###,##0.00";
	}
}
//---------------------------------------------------------------------------

void TfrmCnetorderlock::ClientView()
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

void __fastcall TfrmCnetorderlock::BtnViewClick(TObject *Sender)
{
	Tfrmorderquery *frm = new Tfrmorderquery(Application,fcon,StgID,1,0,false);
    frm->fmodle=101;
	frm->chshenhei->Visible = false;

	if (frm->ShowModal()==mrOk ) {
		dbn->Enabled = true;
		AnsiString code = frm->GetNoteCode();
		AnsiString sqlwhere = frm->GetWhere();
		AnsiString sql;
		if (sqlwhere != "") {
			sql = " select * from C_BS_OrderNoteHeader where 1=1 " + sqlwhere;
			aqhd->Close();
			aqhd->SQL->Clear();
			aqhd->SQL->Add(sql);
			aqhd->Open();
		}

		TLocateOptions Opts;
		Opts.Clear();
		Opts << loPartialKey;
		if(aqhd->Locate("orderntcode", Variant(code), Opts))
		{
			RefreshHead(aqhd->FieldByName("ID")->AsInteger );
		}else
		{
			MessageBoxA(0,"查询结果为空！","提示",MB_ICONWARNING);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCnetorderlock::BtnClearClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	queryorder->Active = false;
	queryorder->Parameters->ParamByName("ID")->Value = aqupdatehead->FieldByName("ID")->AsInteger ;
	queryorder->Active = true;

	frxOrder->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "COrderLock.fr3");
	frxOrder->PrepareReport(true);
	frxOrder->ShowPreparedReport();
	frxOrder->Free();

	//frxOrder->PrintOptions->ShowDialog = false;
	//frxOrder->Print();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::BtnExportClick(TObject *Sender)
{
	if (aqorderdetail->Active && aqorderdetail->RecordCount >= 1)
	{
		DbgridToExcel2(dgdetail);
	}
}

//---------------------------------------------------------------------------
//Excel导出函数
bool __fastcall TfrmCnetorderlock::DbgridToExcel2(TDBGrid* dbg)
{
	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

    savedlg->FileName = StringReplace(edtclient->Text+dbeditdanhao->Text,"\\","-",TReplaceFlags()<<rfReplaceAll);
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
    	return false;
	}

	if(FileExists(path))
	try {
		DeleteFileA(path);
	} catch (...) {
		return false;
	}

	Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");

	int *Count;
	Count = new int[6];

	int t1= 0;
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			if (dbg->Columns ->Items [q]->Title ->Caption == "数量") {
				Count[0] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "码洋") {
				Count[1] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "实洋") {
				Count[2] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "已发数量") {
				Count[3] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "未发数量") {
				Count[4] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "锁定数量") {
				Count[5] = t1;
			}
		}
	}

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;
	aqorderdetail->DisableControls();
	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					//temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				/*else if (dbg->Columns ->Items [j-1]->FieldName == "bookname") {
					t1++;
					AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					//temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + bookname + ",";
				} */
				else if (dbg->Columns ->Items [j-1]->FieldName == "Discount") {
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					//temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + "%,";
				}
				else
				{
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					//temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		//iFileLength   =   FileSeek(iFileHandle,0,2);
		//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+2,t1)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);


	aqorderdetail->EnableControls();

	try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (Exception &E) {

	}
	return false;
}

//---------------------------------------------------------------------------

 void __fastcall TfrmCnetorderlock::BtnPrintClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	queryorder->Active = false;
	queryorder->Parameters->ParamByName("ID")->Value = aqupdatehead->FieldByName("ID")->AsInteger ;
	queryorder->Active = true;

	frxOrder->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "COrderlocl.fr3");
	frxOrder->PrepareReport(true);
	frxOrder->PrintOptions->ShowDialog = false;
	frxOrder->Print();
	frxOrder->Free();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	//ShowMessage(Key);
	if (Key == VK_F1) {   //查单
		if (!BtnView->Enabled ) {
			return;
		}
		BtnView->Click();
	}
	if (Key == VK_F2) {   //添单
		if (!BtnNew->Enabled ) {
			return;
		}
		BtnNew->Click();
	}

	if (Key == VK_F8) {   //导出
		if (!BtnExport->Enabled ) {
			return;
		}
		BtnExport->Click();
	}
	if (Key == VK_F10) {  //打印
		if (!BtnPrint->Enabled ) {
			return;
		}
		BtnPrint->Click();
	}
	if (Key == VK_F11) {   //预览
		if (!BtnClear->Enabled ) {
			return;
		}
		BtnClear->Click();
	}
	if (Key == VK_F12) {   //审核本单
		if (!BtnOK1->Enabled ) {
			return;
		}
		BtnOK1->Click();
	}
	if (Key == VK_F9) {   //反审核
		if (!BtnCancel->Enabled ) {
			return;
		}
		BtnCancel->Click();
	}

	if (Shift.Contains(ssAlt)&& Key == 68) {    //浏览区设置
		SpeedButton4->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
   //	if (Shift.Contains(ssCtrl)&& Key == 70 ) {   //查书
  //	   BtnView1->Click();
  //	}
	if (Shift.Contains(ssAlt)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal;
	}
	if (Shift.Contains(ssCtrl)&&Key==70 ) {    //Ctrl + f 查书
		Tfrmfindorderbook *frm = new Tfrmfindorderbook(Application);
		frm->aq =aqorderdetail;

		if (mrOk == frm->ShowModal()){  ;    //查询条件
			AnsiString type,value;
			type = frm->type ;
			value = frm->value ;

				TLocateOptions   Opts;
				Opts.Clear();
				Opts   <<   loPartialKey;

				if ( !aqorderdetail->Locate(type,value,Opts))
				{
				   MessageBoxA(0,"没有找到查询的数据!","订单查询",MB_ICONINFORMATION);

				}else
				{
					dgdetail->SelectedRows->Clear();
					dgdetail->SelectedRows->CurrentRowSelected = true;
				}
		   }
		 delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::BtnView1Click(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,fcon,StgID);
	frm->ShowModal();
	delete frm;
}

//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::dbeditaddcostKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		membk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::dgdetail1DblClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
		TfrmNewBookModify * frm = new TfrmNewBookModify(Application,fcon,aqorderdetail->FieldByName("bkcatalogid")->AsInteger,m_storageID,m_userID);
		frm->ShowModal();
		delete frm;
		RefreshDetail();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::BtnOK1Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	if (lab->Caption == "锁定数量已确认") {
		return;
	}


	AnsiString sql = "update C_BS_OrderNoteHeader set clientsure = 2 where id = " + aqupdatehead->FieldByName("ID")->AsString  ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();       //已锁定库存

	//调用存储过程
	sql = "exec C_RukuRedoLockOrder :headerid,:sure ";

	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Parameters->ParamByName("headerid")->Value= aqupdatehead->FieldByName("ID")->AsInteger;
	aq->Parameters->ParamByName("sure")->Value= 1;

	aq->ExecSQL();

	delete aq;
	lab->Caption = "锁定数量已确认";
    RefreshHead(aqhd->FieldByName("ID")->AsInteger );




   //	dgdetail->Columns->Items[15]->ReadOnly = true;
}
//---------------------------------------------------------------------------
   /*
void __fastcall Tfrmorderlock::dgdetailDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State)
{
	if (dgdetail->DataSource->DataSet->FieldByName("state1")->AsString  == "无效" ) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
		dgdetail->Canvas->FillRect(Rect);
		dgdetail->Canvas->Font->Color  = clRed;
	   //	DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;  //>>fsBold ;
		dgdetail->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}   */
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::dgdetailCellClick(TColumn *Column)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}

	editdetailbk->Text = aqorderdetail->FieldByName("bk")->AsAnsiString ;
}
//---------------------------------------------------------------------------


void __fastcall TfrmCnetorderlock::dgdetailDrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
  /*	if (dgdetail->DataSource->DataSet->FieldByName("state1")->AsString  == "无效" ) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
		dgdetail->Canvas->FillRect(Rect);
		dgdetail->Canvas->Font->Color  = clRed;
	   //	DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;  //>>fsBold ;
		dgdetail->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
	if (dgdetail->DataSource->DataSet->FieldByName("newbook")->AsBoolean  == true ) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
		dgdetail->Canvas->FillRect(Rect);
		dgdetail->Canvas->Font->Color  = clPurple ;
	   //	DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;  //>>fsBold ;
		dgdetail->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}  */
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::dgdetailTitleClick(TColumn *Column)
{
	if (aqorderdetail->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqorderdetail->Sort == "") {
		aqorderdetail->Sort =  Column->FieldName + " ASC";
	}
	else if (aqorderdetail->Sort == qusort) {
		aqorderdetail->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqorderdetail->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmCnetorderlock::BtnCancelClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	if (lab->Caption != "锁定数量已确认") {
		return;
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql = "update C_BS_OrderNoteHeader set clientsure = 1 where id =  " + aqupdatehead->FieldByName("ID")->AsString  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();

	sql = "exec C_RukuRedoLockOrder :headerid,:sure ";

	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Parameters->ParamByName("headerid")->Value= aqupdatehead->FieldByName("ID")->AsInteger;
	aq->Parameters->ParamByName("sure")->Value= 0;
	aq->ExecSQL();

	delete aq;
	lab->Caption = "未锁定";
	//dgdetail->Columns->Items[15]->ReadOnly = false;

	RefreshHead(aqhd->FieldByName("ID")->AsInteger );


}
//---------------------------------------------------------------------------


void __fastcall TfrmCnetorderlock::SpeedButton4Click(TObject *Sender)
{
  //	if (GroupBox4->Visible) {
  // /		GroupBox4->Visible = false;
 //	}
  //	else
  //	{
 //   	GroupBox4->Visible = true;
  //	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::ch1Click(TObject *Sender)
{
  /*	if (ch1->Checked ) {
		dgdetail->Columns->Items[1]->Visible = true;
		dgdetail->Columns->Items[1]->Width = 52;
	}
	else
	{
		dgdetail->Columns->Items[1]->Visible = false;
	}   */
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::ch2Click(TObject *Sender)
{
  /*	if (ch2->Checked ) {
		dgdetail->Columns->Items[2]->Visible = true;
		dgdetail->Columns->Items[2]->Width = 57;
	}
	else
	{
		dgdetail->Columns->Items[2]->Visible = false;
	} */
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::ch3Click(TObject *Sender)
{
   /*	if (ch3->Checked ) {
		dgdetail->Columns->Items[3]->Visible = true;
		dgdetail->Columns->Items[3]->Width = 56;
	}
	else
	{
		dgdetail->Columns->Items[3]->Visible = false;
	}  */
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::ch4Click(TObject *Sender)
{
   /*	if (ch4->Checked ) {
		dgdetail->Columns->Items[4]->Visible = true;
		dgdetail->Columns->Items[4]->Width = 55;
	}
	else
	{
		dgdetail->Columns->Items[4]->Visible = false;
	}  */
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::ch5Click(TObject *Sender)
{
   /*	if (ch5->Checked ) {
		dgdetail->Columns->Items[5]->Visible = true;
		dgdetail->Columns->Items[5]->Width = 57;
	}
	else
	{
		dgdetail->Columns->Items[5]->Visible = false;
	}   */
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::ch6Click(TObject *Sender)
{
  /*	if (ch6->Checked ) {
		dgdetail->Columns->Items[6]->Visible = true;
		dgdetail->Columns->Items[6]->Width = 59;
	}
	else
	{
		dgdetail->Columns->Items[6]->Visible = false;
	}    */
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::ch7Click(TObject *Sender)
{
  /*	if (ch7->Checked ) {
		dgdetail->Columns->Items[7]->Visible = true;
		dgdetail->Columns->Items[7]->Width = 55;
	}
	else
	{
		dgdetail->Columns->Items[7]->Visible = false;
	} */
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::ch8Click(TObject *Sender)
{
   /*	if (ch8->Checked ) {
		dgdetail->Columns->Items[8]->Visible = true;
		dgdetail->Columns->Items[8]->Width = 56;
	}
	else
	{
		dgdetail->Columns->Items[8]->Visible = false;
	}   */
}
//---------------------------------------------------------------------------


void __fastcall TfrmCnetorderlock::N14Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,fcon,StgID,aqorderdetail->FieldByName("bkcatalogid")->AsInteger,UserID );
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::N17Click(TObject *Sender)
{
	if (aqorderdetail->Active && aqorderdetail->RecordCount >= 1)
	{
		DbgridToExcel2(dgdetail);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::N18Click(TObject *Sender)
{
	if (aqorderdetail->Active && aqorderdetail->RecordCount >= 1)
	{
		DbgridToExcel(dgdetail);
	}
}
//---------------------------------------------------------------------------
//Excel导出函数
bool TfrmCnetorderlock::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

    savedlg->FileName = StringReplace(edtclient->Text+dbeditdanhao->Text,"\\","-",TReplaceFlags()<<rfReplaceAll);
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + "锁定.xls";
		path =  DBPath;
	}
	else
	{
    	return false;
	}

	if(FileExists(path))
	try {
		DeleteFileA(path);
	} catch (...) {
		return false;
	}

	Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",false);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");

	int *Count;
	Count = new int[6];

	int t1= 0;
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			if (dbg->Columns ->Items [q]->Title ->Caption == "数量") {
				Count[0] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "码洋") {
				Count[1] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "实洋") {
				Count[2] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "已发数量") {
				Count[3] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "未发数量") {
				Count[4] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "锁定数量") {
				Count[5] = t1;
			}
		}
	}

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;
	aqorderdetail->DisableControls();
	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true && aqorderdetail->FieldByName("localnum")->AsInteger > 0 ) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "Discount") {
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
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
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+1,t1)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	aqorderdetail->EnableControls();

	try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (Exception &E) {

	}
	return false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::SpeedButton5Click(TObject *Sender)
{
	if(aqupdatehead->IsEmpty())
	{
		return;
	}
	else
	{
		if (SpeedButton5->Caption == "显示有效") {
			AnsiString sql;
			sql = "select RANK() OVER(order by A.ID desc) as xuhao, A.id, A.OrderNtHeaderID,B.ISBN,B.name as bookname,P.AbbreviatedName,B.price,B.pressID,A.amount,A.Discount,A.localnum,A.xuxiao,A.class,A.newbook,"
				" A.FixedPrice,A.Discountedprice,A.bk , A.bkcatalogid,A.SendAmount,A.UnSendAmount,case when A.state = 0 then '有效' else '无效' end as state1,B.PressCount,B.UserDefCode,B.Author, "
				" A.xiaoqu,A.xueyuan,A.course,A.incode,A.teacher,A.telphone,A.needprocurenum,"
				" A.yamount,A.ylocalnum,case when A.ystate = 0 then '有效' when A.ystate = 1 then  '无效' else '' end as state2,A.ystate, "
				" C.stkamount as bookamount,C.usableamount, case when A.needprocurenum = 10 then '√' else '' end as prostate "
				" from BS_OrderNote A "
				" left join BS_OrderNoteHeader on A.orderNtHeaderID = BS_OrderNoteHeader.id "
				" left join bs_bookcatalog B On A.bkcatalogID = B.ID "
				" left join bs_pressinfo P ON B.pressID = P.ID "
				" left join Order_lock C on A.bkcatalogID = C.BkcatalogID and BS_OrderNoteHeader.stgid = C.stgid "
				" where A.state = 0 and A.orderNtHeaderID = " + aqupdatehead->FieldByName("ID")->AsString;

			aqorderdetail->Active = false;
			aqorderdetail->SQL->Clear();
			aqorderdetail->SQL->Add(sql);
			aqorderdetail->Active = true;
			SpeedButton5->Caption = "显示全部";
		}
		else
		{
			AnsiString sql;
			sql = "select RANK() OVER(order by A.ID desc) as xuhao, A.id, A.OrderNtHeaderID,B.ISBN,B.name as bookname,P.AbbreviatedName,B.price,B.pressID,A.amount,A.Discount,A.localnum,A.xuxiao,A.class,A.newbook,"
				" A.FixedPrice,A.Discountedprice,A.bk , A.bkcatalogid,A.SendAmount,A.UnSendAmount,case when A.state = 0 then '有效' else '无效' end as state1,B.PressCount,B.UserDefCode,B.Author, "
				" A.xiaoqu,A.xueyuan,A.course,A.incode,A.teacher,A.telphone,A.needprocurenum,"
				" A.yamount,A.ylocalnum,case when A.ystate = 0 then '有效' when A.ystate = 1 then  '无效' else '' end as state2,A.ystate, "
				" C.stkamount as bookamount,C.usableamount, case when A.needprocurenum = 10 then '√' else '' end as prostate "
				" from BS_OrderNote A "
				" left join BS_OrderNoteHeader on A.orderNtHeaderID = BS_OrderNoteHeader.id "
				" left join bs_bookcatalog B On A.bkcatalogID = B.ID "
				" left join bs_pressinfo P ON B.pressID = P.ID "
				" left join Order_lock C on A.bkcatalogID = C.BkcatalogID and BS_OrderNoteHeader.stgid = C.stgid "
				" where A.orderNtHeaderID = " + aqupdatehead->FieldByName("ID")->AsString;

			aqorderdetail->Active = false;
			aqorderdetail->SQL->Clear();
			aqorderdetail->SQL->Add(sql);
			aqorderdetail->Active = true;
			SpeedButton5->Caption = "显示有效";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::frxOrderGetValue(const UnicodeString VarName, Variant &Value)

{
	if (CompareText(VarName,"\"ClientName\"")==0 ) {
		Value = edtclient->Text.Trim() ;
	}
	if (CompareText(VarName,"\"title\"")==0 ) {
		Value = "订单锁定数量确认";
	}
	if (CompareText(VarName,"\"remarks\"")==0 ) {
		Value = membk->Text.Trim();
	}
	if (CompareText(VarName,"\"OrderNtCode\"")==0 ) {
		Value = dbeditdanhao->Text.Trim();
	}
	if (CompareText(VarName,"\"hdtime\"")==0 ) {
		Value = aqhd->FieldByName("HdTime")->AsAnsiString ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::BtnPostClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
    	return;
	}
	try {
		aqorderdetail->UpdateBatch(arAll);
	} catch (...) {

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCnetorderlock::SpeedButton1Click(TObject *Sender)
{
	if(aqupdatehead->IsEmpty())
	{
		return;
	}
	else
	{
		if (SpeedButton1->Caption == "显示差异") {
			AnsiString sql;


		sql = 	"  select RANK() OVER(order by corderid desc) as xuhao,corderid id,  "
		"  orderntheaderid,isbn,name bookname,press AbbreviatedName, "
		"  price,pressinfoid pressid,amount,discount,locknum,  "
		"  FixedPrice,Discountedprice,backinfo,Orderdetailbk,bk,catalogid bkcatalogid, "
		"  sended sendamount,UnSendAmount,presscount,Author, "
		"  needprocurenum,kykc from C_Order_Detail "
		"  where amount<>locknum and orderntheaderid = " + aqupdatehead->FieldByName("ID")->AsString;



			aqorderdetail->Active = false;
			aqorderdetail->SQL->Clear();
			aqorderdetail->SQL->Add(sql);
			aqorderdetail->Active = true;
			SpeedButton1->Caption = "显示全部";
		}
		else
		{
			AnsiString sql;
			sql = 	"  select RANK() OVER(order by corderid desc) as xuhao,corderid id,  "
		"  orderntheaderid,isbn,name bookname,press AbbreviatedName, "
		"  price,pressinfoid pressid,amount,discount,locknum,  "
		"  FixedPrice,Discountedprice,backinfo,Orderdetailbk,bk,catalogid bkcatalogid, "
		"  sended sendamount,UnSendAmount,presscount,Author, "
		"  needprocurenum,kykc from C_Order_Detail "
		"  where  orderntheaderid = " + aqupdatehead->FieldByName("ID")->AsString;


			aqorderdetail->Active = false;
			aqorderdetail->SQL->Clear();
            aqorderdetail->SQL->Add(sql);
			aqorderdetail->Active = true;
			SpeedButton1->Caption = "显示差异";
		}
	}
}
//---------------------------------------------------------------------------


