//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RecordQuery.h"
#include "Unitchangeaddvalue.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IWImageList"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzRadChk"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma resource "*.dfm"
TFormRecordQuery *FormRecordQuery;
//---------------------------------------------------------------------------
__fastcall TFormRecordQuery::TFormRecordQuery(TComponent* Owner,TADOConnection *cn,int userid,int stgid)
	: TForm(Owner)
{
   quRecordMessage->Connection = cn;
   fcon = cn;
   fuserid = userid;
   fstgid = stgid;
   AnsiString sql;
   TADOQuery *aq = new TADOQuery(this);
   aq->Connection = cn;
   sql = "select IDType,Type from CUST_MemberType";
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   while (!aq->Eof)
   {
		cbtype->AddItem(aq->FieldByName("Type")->AsString ,(TObject*)aq->FieldByName("IDType")->AsInteger );
		aq->Next();
   }
   delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TFormRecordQuery::FormShow(TObject *Sender)
{
	dtEndData->Date = Date();
	dtStartData->Date= Date();
}
//---------------------------------------------------------------------------


void __fastcall TFormRecordQuery::BtnFindClick(TObject *Sender)
{
	float totalvalue = 0.00;
	AnsiString sqlwhere;
	AnsiString sql = "select rank() over( order by CUST_MemberToprecord.Tid) as xuhao,CUST_MemberToprecord.Tid,CUST_MemberToprecord.MIName,CUST_MemberToprecord.MIid,CUST_MemberToprecord.CardID,"
		"Convert(varchar(20),CUST_MemberToprecord.date,111) as date,CUST_MemberToprecord.CorrentVoucher,CUST_MemberToprecord.BeforeVoucherAmount,sum(CUST_MemberToprecord.CorrentVoucher) as totalVoucher,"
		"CUST_MemberToprecord.AfterVoucherAmount,CUST_MemberToprecord.MIType,cast (CUST_MemberType.Discount as varchar)+'%' as Discount,CUST_MemberInfo.Balance,CUST_MemberInfo.TotalConsumption "
		"from CUST_MemberToprecord inner join CUST_MemberInfo on CUST_MemberInfo.CardID = CUST_MemberToprecord.CardID "
		"inner join CUST_MemberType on CUST_MemberInfo.MemberType = CUST_MemberType.IDType " ;
	sqlwhere = " where 1 = 1 ";
	if (cbstarttime->Checked ) {
		sqlwhere = sqlwhere + " and CUST_MemberToprecord.date >= cast('" + DateToStr(dtStartData->Date) + " 0:00:00' as datetime) ";
	}
	if (cbendtime->Checked ) {
		sqlwhere = sqlwhere + " and CUST_MemberToprecord.date <= cast('" + DateToStr(dtEndData->Date) + " 23:59:59' as datetime) ";
	}
	if (chname->Checked && edname->Text != "") {
		sqlwhere = sqlwhere + " and CUST_MemberToprecord.MIName like '%" + edname->Text.Trim() + "%'";
	}
	if (chcard->Checked && edcard->Text != "") {
		sqlwhere = sqlwhere + " and CUST_MemberToprecord.CardID like '%" + edcard->Text.Trim() + "%'";
	}
	if (chtype->Checked && cbtype->Text != "") {
		sqlwhere = sqlwhere + " and CUST_MemberType.Type like '%" + cbtype->Text.Trim() + "%'";
	}
	sql = sql + sqlwhere;
	sql = sql + " group by CUST_MemberToprecord.Tid,CUST_MemberToprecord.MIName,CUST_MemberToprecord.MIid,CUST_MemberToprecord.CardID,"
		"CUST_MemberToprecord.date,CUST_MemberToprecord.CorrentVoucher,CUST_MemberToprecord.BeforeVoucherAmount,"
		"CUST_MemberToprecord.AfterVoucherAmount,CUST_MemberToprecord.MIType,CUST_MemberType.Discount,CUST_MemberInfo.Balance,CUST_MemberInfo.TotalConsumption ";
	quRecordMessage->Close();
	quRecordMessage->SQL->Clear();
	quRecordMessage->SQL->Add(sql);
	quRecordMessage->Open();
	if (quRecordMessage->IsEmpty() ) {
		MessageBox(0,"你所查找的记录不存在！","查询结果" ,MB_OK);
	}
	while(!quRecordMessage->Eof ) {
		totalvalue = totalvalue + quRecordMessage->FieldByName("CorrentVoucher")->AsFloat ;
		quRecordMessage->Next();
	}

	sql = "select sum(A.Balance) AS Balance,sum(A.TotalConsumption) as TotalConsumption "
			" from (SELECT distinct CUST_MemberInfo.Balance,CUST_MemberInfo.TotalConsumption "
			" from CUST_MemberToprecord inner join CUST_MemberInfo on CUST_MemberInfo.CardID = CUST_MemberToprecord.CardID "
			" inner join CUST_MemberType on CUST_MemberInfo.MemberType = CUST_MemberType.IDType " + sqlwhere + ") A";
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edtotalblance->Text = FormatFloat("0.00",aq->FieldByName("Balance")->AsFloat );
	edtotalcons->Text = FormatFloat("0.00",aq->FieldByName("TotalConsumption")->AsFloat);
	edtotalvalue->Text = FormatFloat("0.00",totalvalue);
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::ednameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key==VK_RETURN) {
		edcard->SetFocus();
	}
}

//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::dgRecordTitleClick(TColumn *Column)
{
	AnsiString qusort;
	if (quRecordMessage->IsEmpty() ) {
		return;
	}
	qusort =  Column->FieldName + " ASC";
	if (quRecordMessage->Sort == "") {
		quRecordMessage->Sort =  Column->FieldName + " ASC";
	}
	else if (quRecordMessage->Sort == qusort) {
		quRecordMessage->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		quRecordMessage->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------



void __fastcall TFormRecordQuery::BtnExportClick(TObject *Sender)
{
	if (!quRecordMessage->IsEmpty() ) {
		DbgridToExcel(dgRecord);
	}
}
//---------------------------------------------------------------------------

//Excel导出函数
bool __fastcall TFormRecordQuery::DbgridToExcel(TDBGrid* dbg)
{
	/*AnsiString temptext ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		MessageBox(0,"没有数据！","错误确认" ,MB_OK);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示

	v.OlePropertyGet("Cells",1,6).OlePropertySet("Value","会员充值查询记录" );

	v.OlePropertyGet("Cells",2,1).OlePropertySet("Value","会员信息" );
	temptext = "'"+ MemberClass->Text;
	v.OlePropertyGet("Cells",2,2).OlePropertySet("Value",temptext .c_str() );
	temptext = "'"+ Message->Text;
	v.OlePropertyGet("Cells",2,3).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",2,5).OlePropertySet("Value","起始时间" );
	if (cbstarttime->Checked ) {
		temptext = "'"+ DateToStr(dtStartData->Date);
	}
	else
	{
    	temptext = "'";
	}
	v.OlePropertyGet("Cells",2,6).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",2,8).OlePropertySet("Value","结束时间" );
	if (cbendtime->Checked ) {
		temptext = "'"+ DateToStr(dtEndData->Date);
	}
	else
	{
    	temptext = "'";
	}
	v.OlePropertyGet("Cells",2,9).OlePropertySet("Value",temptext .c_str());

	n=2;

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
				t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}

	return false;  */


	if (dbg->DataSource ->DataSet->IsEmpty() ) {
        return false;
	}
	AnsiString temptext,path;

	savedlg->FileName = this->Caption;
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

	for(int q=0;q<dbg->Columns ->Count ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			temptext = temptext + dbg->Columns ->Items [q]->FieldName + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	dbg->DataSource ->DataSet->DisableControls();
	dbg->DataSource ->DataSet ->First();
	while(!dbg->DataSource ->DataSet->Eof)
	{
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{    	if (Key == VK_F1) {
		 BtnFind->Click();
	   }
		if (Key == VK_F6) {
		 BtnExport->Click();
	   }
		if (Shift.Contains(ssCtrl)&& Key ==90) {
			WindowState = wsNormal  ;
		}
		if (Shift.Contains(ssCtrl)&& Key ==81  ) {
			BtnExit->Click();
		}
		if (Shift.Contains(ssCtrl)&& Key == 78 ) {
		  BtnAlignBottom->Click();
		}

}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized   ;
}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::BtnRefreshClick(TObject *Sender)
{
	if (quRecordMessage->IsEmpty() ) {
		return;
	}
	float beforechange,afterchange;
	AnsiString logmessage,sql;
	beforechange =  quRecordMessage->FieldByName("CorrentVoucher")->AsFloat ;
	Tfrmchangeaddvalue *frm = new Tfrmchangeaddvalue(Application);
	frm->edname->Text = quRecordMessage->FieldByName("MIName")->AsString ;
	frm->edcard->Text = quRecordMessage->FieldByName("CardID")->AsString ;
	frm->edyuan->Text = quRecordMessage->FieldByName("CorrentVoucher")->AsString ;
	frm->edyue->Text = quRecordMessage->FieldByName("Balance")->AsString ;
	if (frm->ShowModal() == mrOk  ) {
		afterchange = frm->getValue();
		sql = "update CUST_MemberToprecord set CorrentVoucher = " + FloatToStr(afterchange) + ",AfterVoucherAmount = AfterVoucherAmount - " + FloatToStr(beforechange) + " + " + FloatToStr(afterchange) +
				",VoucherAmount = VoucherAmount - " + FloatToStr(beforechange) + " + " + FloatToStr(afterchange) + " where Tid = " + quRecordMessage->FieldByName("Tid")->AsString ;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		sql = "update CUST_MemberInfo set Balance = Balance - " + FloatToStr(beforechange) + " + " + FloatToStr(afterchange) + " where CardID = '" + quRecordMessage->FieldByName("CardID")->AsString + "'";
        aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		logmessage = "修改会员卡" + quRecordMessage->FieldByName("CardID")->AsString + "的充值金额" + quRecordMessage->FieldByName("CorrentVoucher")->AsString + "为" + FloatToStr(afterchange) + "元";
		AddEvent(1,"会员卡充值窗口",fuserid,fstgid,logmessage,fcon);
	}
	delete frm;
	quRecordMessage->Active = false;
	quRecordMessage->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::dtStartDataChange(TObject *Sender)
{
	cbstarttime->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::dtEndDataChange(TObject *Sender)
{
	cbendtime->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::ednameChange(TObject *Sender)
{
	if (edname->Text != "") {
		chname->Checked = true;
	}
	else
	{
    	chname->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::edcardChange(TObject *Sender)
{
	if (edcard->Text != "") {
		chcard->Checked = true;
	}
	else
	{
    	chcard->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::cbtypeChange(TObject *Sender)
{
	if (cbtype->Text != "") {
		chtype->Checked = true;
	}
	else
	{
    	chtype->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::edcardKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == '\r') {
        dtStartData->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::dtStartDataKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == '\r') {
        dtEndData->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormRecordQuery::dtEndDataKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == '\r') {
        cbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

