//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OrderLock.h"
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
Tfrmorderlock *frmorderlock;
//---------------------------------------------------------------------------
__fastcall Tfrmorderlock::Tfrmorderlock(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	m_module = MTOrder;
	ClientID = -1;
	WindowState = wsMaximized ;
	dgdetail->OnDrawColumnCell=dgdetailDrawColumnCell;
}
//---------------------------------------------------------------------------
void Tfrmorderlock::init(LandInfo* li)
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

AnsiString Tfrmorderlock::GetField(AnsiString sql,AnsiString Field)
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
void Tfrmorderlock::ExecSQL(AnsiString sql)
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

void Tfrmorderlock::RefreshHead(int headerid)
{
	AnsiString sql;
	sql = "select A.*,S.ID,C.Name as Clientname,S.Name as StgName,U.ID,U.name as OpName from BS_OrderNoteHeader A "
			"left join SYS_StorageInfo S ON A.stgID = S.ID "
			"left join SYS_User U ON A.operatorID = U.ID "
			"left join CUST_customerinfo C ON C.ID = A.vendorID where A.id = " + IntToStr(headerid) ;
	aqupdatehead->Close();
	aqupdatehead->SQL->Clear();
	aqupdatehead->SQL->Add(sql);
	aqupdatehead->Open();

	ClientID = aqupdatehead->FieldByName("vendorID")->AsInteger;
	membk->Text =  aqupdatehead->FieldByName("Remarks")->AsString;

	ClientView();
	RefreshDetail();
	if (aqupdatehead->FieldByName("shenheistate")->AsInteger == 1) {
        lab->Visible = true;
		lab->Caption = "�����";
		dgdetail->Columns->Items[24]->ReadOnly = false;
	}
	else if (aqupdatehead->FieldByName("shenheistate")->AsInteger == 2) {
    	lab->Visible = true;
		lab->Caption = "����������ȷ��";
		dgdetail->Columns->Items[24]->ReadOnly = true;
	}
	else
	{
		lab->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::dbnClick(TObject *Sender, TNavigateBtn Button)
{
	RefreshHead(aqhd->FieldByName("ID")->AsInteger );
}
//---------------------------------------------------------------------------

void Tfrmorderlock::RefreshDetail()
{
	AnsiString sql;
	sql = "select RANK() OVER(order by A.ID desc) as xuhao, A.id, A.OrderNtHeaderID,B.ISBN,B.name as bookname,P.AbbreviatedName,B.price,B.pressID,A.amount,A.Discount,A.localnum,A.xuxiao,A.class,A.newbook,"
		" A.FixedPrice,A.Discountedprice,A.bk , A.bkcatalogid,A.SendAmount,A.UnSendAmount,case when A.state = 0 then '��Ч' else '��Ч' end as state1,B.PressCount,B.UserDefCode,B.Author, "
		" A.xiaoqu,A.xueyuan,A.course,A.incode,A.teacher,A.telphone,A.needprocurenum,"
		" A.yamount,A.ylocalnum,case when A.ystate = 0 then '��Ч' when A.ystate = 1 then  '��Ч' else '' end as state2,A.ystate, "
		" C.stkamount as bookamount,C.usableamount, case when A.needprocurenum = 10 then '��' else '' end as prostate "
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

	if (aqorderdetail->RecordCount > 0) {
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "��0.00";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("fixedPrice"))->DisplayFormat = "��###,###,##0.00";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Discountedprice"))->DisplayFormat = "��###,###,##0.00";
	}
}
//---------------------------------------------------------------------------

void Tfrmorderlock::ClientView()
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

void __fastcall Tfrmorderlock::BtnViewClick(TObject *Sender)
{
	Tfrmorderquery *frm = new Tfrmorderquery(Application,fcon,StgID,1,0,false);
	frm->chshenhei->Visible = true;
	frm->sqladd = " and shenheistate >= 1 ";
	if (frm->ShowModal()==mrOk ) {
		dbn->Enabled = true;
		AnsiString code = frm->GetNoteCode();
		AnsiString sqlwhere = frm->GetWhere();
		AnsiString sql;
		if (sqlwhere != "") {
			sql = " select * from BS_OrderNoteHeader " + sqlwhere;
			aqhd->Close();
			aqhd->SQL->Clear();
			aqhd->SQL->Add(sql);
			aqhd->Open();
		}
		AnsiString str =  LeftBStr(code,2);
		if (str == "00") {
			code = AnsiRightStr(code,code.Length()-2) ;
		}else
		{
			str = LeftBStr(code,1);
			if (str == "0") {
				code = AnsiRightStr(code,code.Length()-1) ;
			}
		}
		TLocateOptions Opts;
		Opts.Clear();
		Opts << loPartialKey;
		if(aqhd->Locate("OrderNtCode", Variant(code), Opts))
		{
			RefreshHead(aqhd->FieldByName("ID")->AsInteger );
		}else
		{
			MessageBoxA(0,"��ѯ���Ϊ�գ�","��ʾ",MB_ICONWARNING);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderlock::BtnClearClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	queryorder->Active = false;
	queryorder->Parameters->ParamByName("ID")->Value = aqupdatehead->FieldByName("ID")->AsInteger ;
	queryorder->Active = true;

	frxOrder->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "Orderlocl.fr3");
	frxOrder->PrepareReport(true);
	frxOrder->ShowPreparedReport();
	frxOrder->Free();

	//frxOrder->PrintOptions->ShowDialog = false;
	//frxOrder->Print();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::BtnExportClick(TObject *Sender)
{
	if (aqorderdetail->Active && aqorderdetail->RecordCount >= 1)
	{
		DbgridToExcel2(dgdetail);
	}
}

//---------------------------------------------------------------------------
//Excel��������
bool __fastcall Tfrmorderlock::DbgridToExcel2(TDBGrid* dbg)
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
			if (dbg->Columns ->Items [q]->Title ->Caption == "����") {
				Count[0] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "����") {
				Count[1] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "ʵ��") {
				Count[2] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "�ѷ�����") {
				Count[3] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "δ������") {
				Count[4] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "��������") {
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
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+2,t1)); //ȡ�úϲ�������
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

 void __fastcall Tfrmorderlock::BtnPrintClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	queryorder->Active = false;
	queryorder->Parameters->ParamByName("ID")->Value = aqupdatehead->FieldByName("ID")->AsInteger ;
	queryorder->Active = true;

	frxOrder->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "Orderlocl.fr3");
	frxOrder->PrepareReport(true);
	frxOrder->PrintOptions->ShowDialog = false;
	frxOrder->Print();
	frxOrder->Free();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	//ShowMessage(Key);
	if (Key == VK_F1) {   //�鵥
		if (!BtnView->Enabled ) {
			return;
		}
		BtnView->Click();
	}
	if (Key == VK_F2) {   //����
		if (!BtnNew->Enabled ) {
			return;
		}
		BtnNew->Click();
	}

	if (Key == VK_F8) {   //����
		if (!BtnExport->Enabled ) {
			return;
		}
		BtnExport->Click();
	}
	if (Key == VK_F10) {  //��ӡ
		if (!BtnPrint->Enabled ) {
			return;
		}
		BtnPrint->Click();
	}
	if (Key == VK_F11) {   //Ԥ��
		if (!BtnClear->Enabled ) {
			return;
		}
		BtnClear->Click();
	}
	if (Key == VK_F12) {   //��˱���
		if (!BtnOK1->Enabled ) {
			return;
		}
		BtnOK1->Click();
	}
	if (Key == VK_F9) {   //�����
		if (!BtnCancel->Enabled ) {
			return;
		}
		BtnCancel->Click();
	}

	if (Shift.Contains(ssAlt)&& Key == 68) {    //���������
		SpeedButton4->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
   //	if (Shift.Contains(ssCtrl)&& Key == 70 ) {   //����
  //	   BtnView1->Click();
  //	}
	if (Shift.Contains(ssAlt)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal;
	}
	if (Shift.Contains(ssCtrl)&&Key==70 ) {    //Ctrl + f ����
		Tfrmfindorderbook *frm = new Tfrmfindorderbook(Application);
		frm->aq =aqorderdetail;

		if (mrOk == frm->ShowModal()){  ;    //��ѯ����
			AnsiString type,value;
			type = frm->type ;
			value = frm->value ;

				TLocateOptions   Opts;
				Opts.Clear();
				Opts   <<   loPartialKey;

				if ( !aqorderdetail->Locate(type,value,Opts))
				{
				   MessageBoxA(0,"û���ҵ���ѯ������!","������ѯ",MB_ICONINFORMATION);

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

void __fastcall Tfrmorderlock::BtnView1Click(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,fcon,StgID);
	frm->ShowModal();
	delete frm;
}

//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::dbeditaddcostKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		membk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::dgdetail1DblClick(TObject *Sender)
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

void __fastcall Tfrmorderlock::BtnOK1Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	if (lab->Caption != "�����") {
        return;
	}
	try {
		aqorderdetail->UpdateBatch(arAll);
	} catch (...) {

	}
	AnsiString sql = "update BS_OrderNoteHeader set shenheistate = 2 where id = " + aqupdatehead->FieldByName("ID")->AsString  ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();

	sql = "update BS_OrderNote set ylocalnum = localnum,yamount = Amount,ystate = state where OrderNtHeaderID = " + aqupdatehead->FieldByName("ID")->AsString  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();

	delete aq;
	lab->Caption = "����������ȷ��";
	dgdetail->Columns->Items[15]->ReadOnly = true;
}
//---------------------------------------------------------------------------
   /*
void __fastcall Tfrmorderlock::dgdetailDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State)
{
	if (dgdetail->DataSource->DataSet->FieldByName("state1")->AsString  == "��Ч" ) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
		dgdetail->Canvas->FillRect(Rect);
		dgdetail->Canvas->Font->Color  = clRed;
	   //	DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;  //>>fsBold ;
		dgdetail->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}   */
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::dgdetailCellClick(TColumn *Column)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}

	editdetailbk->Text = aqorderdetail->FieldByName("bk")->AsAnsiString ;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmorderlock::dgdetailDrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (dgdetail->DataSource->DataSet->FieldByName("state1")->AsString  == "��Ч" ) {
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
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::dgdetailTitleClick(TColumn *Column)
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


void __fastcall Tfrmorderlock::BtnCancelClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	if (lab->Caption != "����������ȷ��") {
		return;
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql = "update BS_OrderNoteHeader set shenheistate = 1 where id = " + aqupdatehead->FieldByName("ID")->AsString  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();

	sql = "update BS_OrderNote set ylocalnum = 0 where OrderNtHeaderID = " + aqupdatehead->FieldByName("ID")->AsString  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();

	delete aq;
	lab->Caption = "�����";
	dgdetail->Columns->Items[15]->ReadOnly = false;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmorderlock::SpeedButton4Click(TObject *Sender)
{
	if (GroupBox4->Visible) {
		GroupBox4->Visible = false;
	}
	else
	{
    	GroupBox4->Visible = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::ch1Click(TObject *Sender)
{
	if (ch1->Checked ) {
		dgdetail->Columns->Items[1]->Visible = true;
		dgdetail->Columns->Items[1]->Width = 52;
	}
	else
	{
		dgdetail->Columns->Items[1]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::ch2Click(TObject *Sender)
{
	if (ch2->Checked ) {
		dgdetail->Columns->Items[2]->Visible = true;
		dgdetail->Columns->Items[2]->Width = 57;
	}
	else
	{
		dgdetail->Columns->Items[2]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::ch3Click(TObject *Sender)
{
	if (ch3->Checked ) {
		dgdetail->Columns->Items[3]->Visible = true;
		dgdetail->Columns->Items[3]->Width = 56;
	}
	else
	{
		dgdetail->Columns->Items[3]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::ch4Click(TObject *Sender)
{
	if (ch4->Checked ) {
		dgdetail->Columns->Items[4]->Visible = true;
		dgdetail->Columns->Items[4]->Width = 55;
	}
	else
	{
		dgdetail->Columns->Items[4]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::ch5Click(TObject *Sender)
{
	if (ch5->Checked ) {
		dgdetail->Columns->Items[5]->Visible = true;
		dgdetail->Columns->Items[5]->Width = 57;
	}
	else
	{
		dgdetail->Columns->Items[5]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::ch6Click(TObject *Sender)
{
	if (ch6->Checked ) {
		dgdetail->Columns->Items[6]->Visible = true;
		dgdetail->Columns->Items[6]->Width = 59;
	}
	else
	{
		dgdetail->Columns->Items[6]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::ch7Click(TObject *Sender)
{
	if (ch7->Checked ) {
		dgdetail->Columns->Items[7]->Visible = true;
		dgdetail->Columns->Items[7]->Width = 55;
	}
	else
	{
		dgdetail->Columns->Items[7]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::ch8Click(TObject *Sender)
{
	if (ch8->Checked ) {
		dgdetail->Columns->Items[8]->Visible = true;
		dgdetail->Columns->Items[8]->Width = 56;
	}
	else
	{
		dgdetail->Columns->Items[8]->Visible = false;
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmorderlock::N14Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,fcon,StgID,aqorderdetail->FieldByName("bkcatalogid")->AsInteger,UserID );
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::N17Click(TObject *Sender)
{
	if (aqorderdetail->Active && aqorderdetail->RecordCount >= 1)
	{
		DbgridToExcel2(dgdetail);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::N18Click(TObject *Sender)
{
	if (aqorderdetail->Active && aqorderdetail->RecordCount >= 1)
	{
		DbgridToExcel(dgdetail);
	}
}
//---------------------------------------------------------------------------
//Excel��������
bool Tfrmorderlock::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

    savedlg->FileName = StringReplace(edtclient->Text+dbeditdanhao->Text,"\\","-",TReplaceFlags()<<rfReplaceAll);
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + "����.xls";
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
			if (dbg->Columns ->Items [q]->Title ->Caption == "����") {
				Count[0] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "����") {
				Count[1] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "ʵ��") {
				Count[2] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "�ѷ�����") {
				Count[3] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "δ������") {
				Count[4] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "��������") {
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
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+1,t1)); //ȡ�úϲ�������
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

void __fastcall Tfrmorderlock::SpeedButton5Click(TObject *Sender)
{
	if(aqupdatehead->IsEmpty())
	{
		return;
	}
	else
	{
		if (SpeedButton5->Caption == "��ʾ��Ч") {
			AnsiString sql;
			sql = "select RANK() OVER(order by A.ID desc) as xuhao, A.id, A.OrderNtHeaderID,B.ISBN,B.name as bookname,P.AbbreviatedName,B.price,B.pressID,A.amount,A.Discount,A.localnum,A.xuxiao,A.class,A.newbook,"
				" A.FixedPrice,A.Discountedprice,A.bk , A.bkcatalogid,A.SendAmount,A.UnSendAmount,case when A.state = 0 then '��Ч' else '��Ч' end as state1,B.PressCount,B.UserDefCode,B.Author, "
				" A.xiaoqu,A.xueyuan,A.course,A.incode,A.teacher,A.telphone,A.needprocurenum,"
				" A.yamount,A.ylocalnum,case when A.ystate = 0 then '��Ч' when A.ystate = 1 then  '��Ч' else '' end as state2,A.ystate, "
				" C.stkamount as bookamount,C.usableamount, case when A.needprocurenum = 10 then '��' else '' end as prostate "
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
			SpeedButton5->Caption = "��ʾȫ��";
		}
		else
		{
			AnsiString sql;
			sql = "select RANK() OVER(order by A.ID desc) as xuhao, A.id, A.OrderNtHeaderID,B.ISBN,B.name as bookname,P.AbbreviatedName,B.price,B.pressID,A.amount,A.Discount,A.localnum,A.xuxiao,A.class,A.newbook,"
				" A.FixedPrice,A.Discountedprice,A.bk , A.bkcatalogid,A.SendAmount,A.UnSendAmount,case when A.state = 0 then '��Ч' else '��Ч' end as state1,B.PressCount,B.UserDefCode,B.Author, "
				" A.xiaoqu,A.xueyuan,A.course,A.incode,A.teacher,A.telphone,A.needprocurenum,"
				" A.yamount,A.ylocalnum,case when A.ystate = 0 then '��Ч' when A.ystate = 1 then  '��Ч' else '' end as state2,A.ystate, "
				" C.stkamount as bookamount,C.usableamount, case when A.needprocurenum = 10 then '��' else '' end as prostate "
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
			SpeedButton5->Caption = "��ʾ��Ч";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderlock::frxOrderGetValue(const UnicodeString VarName, Variant &Value)

{
	if (CompareText(VarName,"\"ClientName\"")==0 ) {
		Value = edtclient->Text.Trim() ;
	}
	if (CompareText(VarName,"\"title\"")==0 ) {
		Value = "������������ȷ��";
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

void __fastcall Tfrmorderlock::BtnPostClick(TObject *Sender)
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

void __fastcall Tfrmorderlock::SpeedButton1Click(TObject *Sender)
{
	if(aqupdatehead->IsEmpty())
	{
		return;
	}
	else
	{
		if (SpeedButton1->Caption == "��ʾ����") {
			AnsiString sql;
			sql = "select RANK() OVER(order by A.ID desc) as xuhao, A.id, A.OrderNtHeaderID,B.ISBN,B.name as bookname,P.AbbreviatedName,B.price,B.pressID,A.amount,A.Discount,A.localnum,A.xuxiao,A.class,A.newbook,"
				" A.FixedPrice,A.Discountedprice,A.bk , A.bkcatalogid,A.SendAmount,A.UnSendAmount,case when A.state = 0 then '��Ч' else '��Ч' end as state1,B.PressCount,B.UserDefCode,B.Author, "
				" A.xiaoqu,A.xueyuan,A.course,A.incode,A.teacher,A.telphone,A.needprocurenum,"
				" A.yamount,A.ylocalnum,case when A.ystate = 0 then '��Ч' when A.ystate = 1 then  '��Ч' else '' end as state2,A.ystate, "
				" C.stkamount as bookamount,C.usableamount, case when A.needprocurenum = 10 then '��' else '' end as prostate "
				" from BS_OrderNote A "
				" left join BS_OrderNoteHeader on A.orderNtHeaderID = BS_OrderNoteHeader.id "
				" left join bs_bookcatalog B On A.bkcatalogID = B.ID "
				" left join bs_pressinfo P ON B.pressID = P.ID "
				" left join Order_lock C on A.bkcatalogID = C.BkcatalogID and BS_OrderNoteHeader.stgid = C.stgid "
				" where (A.yamount is null or A.yamount <> A.amount or A.ystate <> A.state or A.localnum <> A.ylocalnum) and A.orderNtHeaderID = " + aqupdatehead->FieldByName("ID")->AsString;

			aqorderdetail->Active = false;
			aqorderdetail->SQL->Clear();
            aqorderdetail->SQL->Add(sql);
			aqorderdetail->Active = true;
			SpeedButton1->Caption = "��ʾȫ��";
		}
		else
		{
			AnsiString sql;
			sql = "select RANK() OVER(order by A.ID desc) as xuhao, A.id, A.OrderNtHeaderID,B.ISBN,B.name as bookname,P.AbbreviatedName,B.price,B.pressID,A.amount,A.Discount,A.localnum,A.xuxiao,A.class,A.newbook,"
				" A.FixedPrice,A.Discountedprice,A.bk , A.bkcatalogid,A.SendAmount,A.UnSendAmount,case when A.state = 0 then '��Ч' else '��Ч' end as state1,B.PressCount,B.UserDefCode,B.Author, "
				" A.xiaoqu,A.xueyuan,A.course,A.incode,A.teacher,A.telphone,A.needprocurenum,"
				" A.yamount,A.ylocalnum,case when A.ystate = 0 then '��Ч' when A.ystate = 1 then  '��Ч' else '' end as state2,A.ystate, "
				" C.stkamount as bookamount,C.usableamount, case when A.needprocurenum = 10 then '��' else '' end as prostate "
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
			SpeedButton1->Caption = "��ʾ����";
		}
	}
}
//---------------------------------------------------------------------------
