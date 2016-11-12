//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unitinitfahuo.h"
#include "WholesaleMngForm.h"
#include "QryNoteCodeForm.h"
#include "Orderdetail.h"
#include "Unitfahuocode.h"
#include "YufaQuery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrminitfahuo *frminitfahuo;
//---------------------------------------------------------------------------
__fastcall Tfrminitfahuo::Tfrminitfahuo(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void Tfrminitfahuo::Init(LandInfo* li)
{
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	aq1->Connection = li->con;
	aq2->Connection = li->con;
	aq->Connection = li->con ;
	fcon = li->con;
	cmdAddNote->Connection = li->con ;
	dtpdate->Date = Date();
	ShowClient();
}
//---------------------------------------------------------------------------
void __fastcall Tfrminitfahuo::DBGrid1CellClick(TColumn *Column)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	AnsiString  sql;
	sql = "select row_number() OVER(order by AbbreviatedName asc,name asc) as xuhao,BS_Tmporder.id,bs_bookcatalog.id as bkcatalogid,bs_bookcatalog.isbn,bs_bookcatalog.name,bs_bookcatalog.price,bs_bookcatalog.author,bs_bookcatalog.userdefcode,"
			" bs_bookcatalog.presscount,BS_PressInfo.AbbreviatedName,bs_bookcatalog.pressdate,BS_OrderNote.xueyuan,BS_OrderNote.xiaoqu,BS_OrderNote.localnum,Order_lock.usableamount,Order_lock.stkamount,"
			" BS_OrderNote.class,BS_OrderNote.course,BS_OrderNote.incode,BS_Tmporder.amount,BS_Tmporder.discount,BS_OrderNote.UnsendAmount "
			" from BS_Tmporder left join bs_bookcatalog on BS_Tmporder.bkcatalogid = bs_bookcatalog.id "
			" left join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id "
			" left join (select * from Order_lock where stgid = " + IntToStr(linfo.storageID) + ") as Order_lock on BS_Tmporder.bkcatalogid = Order_lock.bkcatalogid "
			" left join BS_PressInfo on bs_bookcatalog.pressid = BS_PressInfo.id "
			" where BS_Tmporder.modle = 0 and BS_Tmporder.groupid = " + IntToStr(fgroupid) + " and FahuoClient = " + aq1->FieldByName("FahuoClient")->AsAnsiString +
			" order by AbbreviatedName ASC,name asc";
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();
	sql = "select sum(amount) as amount,sum(bs_bookcatalog.price*amount) as mayang from BS_Tmporder join bs_bookcatalog on BS_Tmporder.bkcatalogid = bs_bookcatalog.id where BS_Tmporder.modle = 0 and BS_Tmporder.groupid = " + IntToStr(fgroupid) + " and FahuoClient = " + aq1->FieldByName("FahuoClient")->AsAnsiString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edamount->Text = aq->FieldByName("amount")->AsAnsiString ;
	edmayang->Text = aq->FieldByName("mayang")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void Tfrminitfahuo::ShowClient()
{
	if (fgroupid > 0) {
		AnsiString sql;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		sql = "select yufacode,headtime,sys_user.name,BS_Tmpheader.state from BS_Tmpheader left join sys_user on BS_Tmpheader.userid = sys_user.id where BS_Tmpheader.groupid = " + IntToStr(fgroupid);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		edcode->Text = aq->FieldByName("yufacode")->AsString ;
		dtpdate->Date = aq->FieldByName("headtime")->AsDateTime ;
		eduser->Text = aq->FieldByName("name")->AsString ;
		if (aq->FieldByName("state")->AsInteger == 0 ) {
			edstate->Text = "未发货";
		}
		else
		{
			edstate->Text = "已发货";
		}
		delete aq;
		sql = "select distinct DENSE_RANK() over(order by BS_Tmporder.FahuoClient) as xuhao, BS_Tmporder.FahuoClient,dbo.UF_BS_GetClientName(BS_Tmporder.FahuoClient) as ClientName from BS_Tmporder where groupid = " + IntToStr(fgroupid) + " and modle = 0";
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->Open();
		aq2->Active = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::BtnDeleteClick(TObject *Sender)
{
	if (aq2->IsEmpty() ) {
		return;
	}
	if (edstate->Text == "已发货") {
		MessageBoxA(0,"已发货的单子不能删除！","提示",MB_ICONASTERISK);
		return;
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	AnsiString ids;
	if (DBGrid2->SelectedRows->Count == 0) {
		ids = aq2->FieldByName("id")->AsAnsiString;
	}
	else if (DBGrid2->SelectedRows->Count > 0) {
		aq2->Bookmark = DBGrid2->SelectedRows->Items[0];
		ids = aq2->FieldByName("id")->AsAnsiString ;
		for (int i = 1; i < DBGrid2->SelectedRows->Count; i++) {
			aq2->Bookmark = DBGrid2->SelectedRows->Items[i];
			ids = ids + "," + aq2->FieldByName("id")->AsAnsiString ;
		}
	}
	sql = "delete from BS_Tmporder where id in( " + ids + ")" ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	aq2->Active = false;
	aq2->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void Tfrminitfahuo::AddNote()//生成发货单
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sgfirsthid  = -1;
	returncode =  "";
	AnsiString  sql;
	aq1->First();
	while (!aq1->Eof)
	{
		sql = "select * from BS_Tmporder where BS_Tmporder.modle = 0 and BS_Tmporder.groupid = " + IntToStr(fgroupid) + " and FahuoClient = " + aq1->FieldByName("FahuoClient")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount > 0 ) {   //有数据才生成发货单
			sql = "select id,WsaleNtCode,HdTime,Remarks,WsaleNtCodeStr,dbo.UF_BS_GetClientName(BS_WsaleNoteHeader.VendorID) as clientname from BS_WsaleNoteHeader where cwstate <> 1 and VendorID = " + aq1->FieldByName("FahuoClient")->AsAnsiString + " and stgid = " + IntToStr(linfo.storageID) + " order by id desc ";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->IsEmpty() ) {
				cmdAddNote->Parameters->ParamByName("@OperatorID")->Value = linfo.userID;
				cmdAddNote->Parameters->ParamByName("@StgID")->Value = linfo.storageID;
				cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 2;
				cmdAddNote->Parameters->ParamByName("@CODEMODE")->Value = 0;
				cmdAddNote->Parameters->ParamByName("@groupid")->Value = fgroupid;
				cmdAddNote->Parameters->ParamByName("@bkstackID")->Value = 0;
				cmdAddNote->Parameters->ParamByName("@new")->Value = 1;
				cmdAddNote->Parameters->ParamByName("@Clientid")->Value = aq1->FieldByName("FahuoClient")->AsInteger ;
				cmdAddNote->Parameters->ParamByName("@wsheadid")->Value = 0;
				if (chbanji->Checked ) {
					cmdAddNote->Parameters->ParamByName("@qubanji")->Value = 1;
				}
				else
				{
					cmdAddNote->Parameters->ParamByName("@qubanji")->Value = 0;
				}
				cmdAddNote->Execute();

				if (returncode == "") {
					returncode =  cmdAddNote->Parameters->ParamByName("@ReturnCode")->Value ;
				}
				else
				{
					returncode =  returncode + "," + cmdAddNote->Parameters->ParamByName("@ReturnCode")->Value ;
				}
				sgheaderid =  cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
				if (sgfirsthid == -1) {
					sgfirsthid =  cmdAddNote->Parameters->ParamByName("@Returnint")->Value ;
				}
			}
			else
			{
				Tfrmfahuocode *frm = new Tfrmfahuocode(Application,aq);
				if (frm->ShowModal() ==  mrOk ) {
					cmdAddNote->Parameters->ParamByName("@OperatorID")->Value = linfo.userID;
					cmdAddNote->Parameters->ParamByName("@StgID")->Value = linfo.storageID;
					cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 2;
					cmdAddNote->Parameters->ParamByName("@CODEMODE")->Value = 0;
					cmdAddNote->Parameters->ParamByName("@groupid")->Value = fgroupid;
					cmdAddNote->Parameters->ParamByName("@bkstackID")->Value = 0;
					cmdAddNote->Parameters->ParamByName("@new")->Value = frm->newid ;
					cmdAddNote->Parameters->ParamByName("@Clientid")->Value = aq1->FieldByName("FahuoClient")->AsInteger ;
					cmdAddNote->Parameters->ParamByName("@wsheadid")->Value = frm->wsheadid ;
					if (chbanji->Checked ) {
						cmdAddNote->Parameters->ParamByName("@qubanji")->Value = 1;
					}
					else
					{
						cmdAddNote->Parameters->ParamByName("@qubanji")->Value = 0;
					}
					cmdAddNote->Execute();

					if (returncode == "") {
						returncode =  cmdAddNote->Parameters->ParamByName("@ReturnCode")->Value ;
					}
					else
					{
						returncode =  returncode + "," + cmdAddNote->Parameters->ParamByName("@ReturnCode")->Value ;
					}
					sgheaderid =  cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
					if (sgfirsthid == -1) {
						sgfirsthid =  cmdAddNote->Parameters->ParamByName("@Returnint")->Value ;
					}
				}
				delete frm;
			}
		}
		aq1->Next();
	}
	delete aq;
	edstate->Text = "已发货";
	if (sgfirsthid > sgheaderid) {
		int tmp =  sgfirsthid;
		sgfirsthid = sgheaderid;
		sgheaderid = tmp;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::BtnOKClick(TObject *Sender)
{
	if (aq1->IsEmpty() ) {
    	return;
	}
	if (edstate->Text == "已发货") {
		MessageBoxA(0,"该单已发货！","提示",MB_ICONASTERISK);
		return;
	}
	AddNote();
	AnsiString sql;
	returncode = "已生成发货单：\n" + returncode + "\n是否查看？";
	sql = "select * from BS_WsaleNoteHeader where id >= " + IntToStr(sgfirsthid) + " and id <= " + IntToStr(sgheaderid) ;
	if (MessageBoxA(0,returncode.c_str(),"询问",MB_ICONQUESTION|MB_OKCANCEL)==1 )
	{
	//转发货单查询
		TfrmWholesaleMng * frm = new TfrmWholesaleMng(Application,1);
		frm->Init(&linfo);
		frm->QryNtHeader(sgfirsthid);

		//frm->BtnSave->Click();
		frm->editdanhao->Text = frm->dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
		frm->cbclient->ItemIndex = frm->cbclient->Items->IndexOfObject((TObject*)frm->dsetVendor->FieldByName("ID")->AsInteger );
		frm->BtnSave->Click();
		frm->querydan->Connection = linfo.con;
		frm->querydan->Close();
		frm->querydan->SQL->Clear();
		frm->querydan->SQL->Add(sql);
		frm->querydan->Open();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::BtnViewClick(TObject *Sender)
{
	TfrmYufaQuery *frm = new TfrmYufaQuery(Application,fcon,linfo.storageID);
	if (mrOk == frm->ShowModal() ) {
		AnsiString Codestr =  frm->query->FieldByName("yufacode")->AsAnsiString ;
		delete frm;
		try {
			QryNtHeader(Codestr);
		} catch (...) {
		}
	}
}
//---------------------------------------------------------------------------
void Tfrminitfahuo::QryNtHeader(AnsiString code)
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = "select groupid from BS_Tmpheader where yufacode = " + code;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	fgroupid = aq->FieldByName("groupid")->AsInteger ;
	ShowClient();
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::BtnExportClick(TObject *Sender)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	DbgridToExcel();
}
//---------------------------------------------------------------------------

void Tfrminitfahuo::DbgridToExcel()
{
	AnsiString temptext,path,sql;
	String DBPath,Name;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq1->First();
	Name = StringReplace(aq1->FieldByName("ClientName")->AsString ,"\\","-",TReplaceFlags()<<rfReplaceAll);
	savedlg->FileName = Name;
	if (savedlg->Execute() == true)
	{
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
	}
	else
	{
    	return;
	}
	int  iFileHandle;
	int   iFileLength;

    aq1->First();
	aq1->DisableControls();
	while (!aq1->Eof)
	{
		sql = "select row_number() OVER(order by AbbreviatedName asc) as xuhao,BS_Tmporder.id,bs_bookcatalog.id as bkcatalogid,bs_bookcatalog.isbn,bs_bookcatalog.name,bs_bookcatalog.price,bs_bookcatalog.author,bs_bookcatalog.userdefcode,"
			" bs_bookcatalog.presscount,BS_PressInfo.AbbreviatedName,bs_bookcatalog.pressdate,BS_OrderNote.xueyuan,BS_OrderNote.xiaoqu,BS_OrderNote.localnum,Order_lock.usableamount,Order_lock.stkamount,"
			" BS_OrderNote.class,BS_OrderNote.course,BS_OrderNote.incode,BS_Tmporder.amount,BS_Tmporder.discount,BS_OrderNote.UnsendAmount "
			" from BS_Tmporder left join bs_bookcatalog on BS_Tmporder.bkcatalogid = bs_bookcatalog.id "
			" left join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id "
			" left join (select * from Order_lock where stgid = " + IntToStr(linfo.storageID) + ") as Order_lock on BS_Tmporder.bkcatalogid = Order_lock.bkcatalogid "
			" left join BS_PressInfo on bs_bookcatalog.pressid = BS_PressInfo.id "
			" where BS_Tmporder.modle = 0 and BS_Tmporder.groupid = " + IntToStr(fgroupid) + " and FahuoClient = " + aq1->FieldByName("FahuoClient")->AsAnsiString +
			" order by AbbreviatedName ASC";


		/*sql = "select BS_Tmporder.id,bs_bookcatalog.isbn,bs_bookcatalog.name,bs_bookcatalog.price,bs_bookcatalog.author,bs_bookcatalog.userdefcode,"
			" bs_bookcatalog.presscount,BS_PressInfo.AbbreviatedName,bs_bookcatalog.pressdate,BS_OrderNote.xueyuan,BS_OrderNote.xiaoqu,"
			" BS_OrderNote.class,BS_OrderNote.course,BS_OrderNote.incode,BS_Tmporder.amount,BS_Tmporder.discount "
			" from BS_Tmporder left join bs_bookcatalog on BS_Tmporder.bkcatalogid = bs_bookcatalog.id "
			" left join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id "
			" left join Order_lock on BS_Tmporder.bkcatalogid = Order_lock.bkcatalogid "
			" left join BS_PressInfo on bs_bookcatalog.pressid = BS_PressInfo.id "
			" where BS_Tmporder.modle = 0 and BS_Tmporder.groupid = " + IntToStr(fgroupid) + " and FahuoClient = " + aq1->FieldByName("FahuoClient")->AsAnsiString + " and Order_lock.stgid = " + IntToStr(linfo.storageID) ;    */
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount > 0) {
        	Name = StringReplace(aq1->FieldByName("ClientName")->AsString ,"\\","-",TReplaceFlags()<<rfReplaceAll);
			path = DBPath + Name + ".csv";
			if(FileExists(path))
				if (DeleteFileA(path))
					iFileHandle = FileCreate(path.c_str());
			else
				return;
			else
				iFileHandle = FileCreate(path.c_str());

			temptext = "";
			for(int q=0;q<DBGrid2->FieldCount ;++q)    //抬头
			{
				if (DBGrid2->Columns->Items[q]->Visible == true) {
					temptext = temptext + DBGrid2->Columns ->Items [q]->Title ->Caption + ",";
				}
			}
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

			while (!aq->Eof )     //明细
			{
            	temptext = "\n";
				for(int j=1;j<DBGrid2->Columns ->Count+1  ;j++)
				{
					if (DBGrid2->Columns->Items[j-1]->Visible == true) {
						AnsiString bookname;
						int len;
						bookname = aq ->FieldByName(DBGrid2->Columns ->Items [j-1]->FieldName )->AsAnsiString;
						bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
						temptext = temptext + bookname + ",";
					}
				}
				FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
            	aq->Next();
			}
			FileClose(iFileHandle);
		}
		aq1->Next();
	}

	aq1->EnableControls();
	delete aq;

	MessageBox(0,"导出完毕！","提示" ,MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {   //查单
		BtnView->Click();
	}
	if (Key == VK_F5) {   //删除
		BtnDelete->Click();
	}
	if (Key == VK_F8) {   //导出
		BtnExport->Click();
	}
	if (Key == VK_F12) {   //审核本单
		BtnOK->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::aq2BeforePost(TDataSet *DataSet)
{
	if (aq2->FieldByName("amount")->AsInteger > aq2->FieldByName("stkamount")->AsInteger   ) {
    	aq2->Cancel();
		Abort();
		MessageBoxA(0,"库存不足！","提示",MB_ICONASTERISK);
	}
	else if (aq2->FieldByName("amount")->AsInteger > aq2->FieldByName("localnum")->AsInteger + aq2->FieldByName("usableamount")->AsInteger ) {
		aq2->Cancel();
		Abort();
		MessageBoxA(0,"该书锁定给其他客户，双击该记录可查看该书的锁定情况并修改！","提示",MB_ICONASTERISK);
	}
	//ShowMessage(aq2->FieldByName("amount")->AsAnsiString);
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::SpeedButton4Click(TObject *Sender)
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

void __fastcall Tfrminitfahuo::ch0Click(TObject *Sender)
{
	if (ch0->Checked ) {
		DBGrid2->Columns ->Items[1]->Visible = true;
		DBGrid2->Columns ->Items[1]->Width = 50;
	}
	else
	{
		DBGrid2->Columns ->Items[1]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::ch1Click(TObject *Sender)
{
	if (ch1->Checked ) {
		DBGrid2->Columns ->Items[2]->Visible = true;
		DBGrid2->Columns ->Items[2]->Width = 50;
	}
	else
	{
		DBGrid2->Columns ->Items[2]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::ch2Click(TObject *Sender)
{
	if (ch2->Checked ) {
		DBGrid2->Columns ->Items[3]->Visible = true;
		DBGrid2->Columns ->Items[3]->Width = 50;
	}
	else
	{
		DBGrid2->Columns ->Items[3]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::ch3Click(TObject *Sender)
{
	if (ch3->Checked ) {
		DBGrid2->Columns ->Items[4]->Visible = true;
		DBGrid2->Columns ->Items[4]->Width = 50;
	}
	else
	{
		DBGrid2->Columns ->Items[4]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::ch4Click(TObject *Sender)
{
	if (ch4->Checked ) {
		DBGrid2->Columns ->Items[5]->Visible = true;
		DBGrid2->Columns ->Items[5]->Width = 50;
	}
	else
	{
		DBGrid2->Columns ->Items[5]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::aq2PostError(TDataSet *DataSet, EDatabaseError *E,
          TDataAction &Action)
{
	Action = daAbort ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::DBGrid2DblClick(TObject *Sender)
{
	if (aq2->IsEmpty() ) {
		return;
	}
	TfrmOrderdetail *frm = new TfrmOrderdetail(Application,fcon,aq2->FieldByName("bkcatalogid")->AsInteger ,linfo.storageID );
	frm->ShowModal();
	delete frm;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = aq2->FieldByName("id")->AsAnsiString ;
	aq2->Active = false;
	aq2->Active = true;
	aq2->Locate("id",str,Opts);
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::DBGrid2MouseLeave(TObject *Sender)
{
	if (!aq2->IsEmpty() && aq2->State == dsEdit  ) {
		try {
            aq2->Post();
        } catch (...) {
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::N1Click(TObject *Sender)
{
	if (aq2->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= aq2->RecordCount; i++) {
		DBGrid2->DataSource->DataSet->RecNo = i;
		DBGrid2->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminitfahuo::aq2AfterPost(TDataSet *DataSet)
{
	AnsiString sql;
	sql = "select sum(amount) as amount,sum(bs_bookcatalog.price*amount) as mayang from BS_Tmporder join bs_bookcatalog on BS_Tmporder.bkcatalogid = bs_bookcatalog.id where BS_Tmporder.modle = 0 and BS_Tmporder.groupid = " + IntToStr(fgroupid) + " and FahuoClient = " + aq1->FieldByName("FahuoClient")->AsAnsiString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edamount->Text = aq->FieldByName("amount")->AsAnsiString ;
	edmayang->Text = aq->FieldByName("mayang")->AsAnsiString ;
}
//---------------------------------------------------------------------------

