//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "retail.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBGrid"
#pragma link "RzRadChk"
#pragma link "RzTabs"
#pragma resource "*.dfm"
Tfrmretail *frmretail;
//---------------------------------------------------------------------------
__fastcall Tfrmretail::Tfrmretail(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
  aqday->Connection = cn;
  aqmonth->Connection = cn;
  dtpstart->Date = Date();
  dtpend->Date = Date();
  TADOQuery * aq;
  String sql;
  aq = new TADOQuery(this);
  aq->Connection = cn;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add("select * from sys_bsset where name ='retailxiaoshudian'");
  aq->Open();
  Disc =  "￥###,###,##" + aq->FieldByName("bk")->AsAnsiString ;

  sql = "select ID,Name  from SYS_StorageInfo";
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();
  while (!aq->Eof)
  {
		cbstorage->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger);
		aq->Next();
  }
  cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)stgid);
  sql = "select Master from SYS_StorageInfo where id = " + IntToStr(stgid);
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();
  if (aq->FieldByName("Master")->AsBoolean ) {
		cbstorage->Enabled = true;
		chstorage->Enabled = true;
  }
  else
  {
  		cbstorage->Enabled = false;
		chstorage->Enabled = false;
  }
  delete aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmretail::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretail::BtnExitClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmretail::BtnViewClick(TObject *Sender)
{
   String  wherestr;
   wherestr = " where 1 = 1 " ;

   if (cbstart->Checked ) {
		wherestr = wherestr + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',Hdtime) >= 0" ;
   }
   if (cbend->Checked) {
		wherestr = wherestr + " and datediff(day,'" + DateToStr(dtpend->Date) + "',Hdtime) <= 0";
   }

   if (chstorage->Checked ) {
		int fstgid;
		try {
			fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
		} catch (...) {
			MessageBox(0,"请选择正确的店号!","提示",MB_ICONEXCLAMATION);
			return;
		}
		wherestr = wherestr + " and bs_retailnoteheader.StgID = " + IntToStr(fstgid);
   }

   if (rbback->Checked) {
	 wherestr = wherestr + " and totalamount < 0 ";

   }else if (rbretail->Checked ) {
		//wherestr = wherestr + " and totalamount > 0 ";
   }
   query = true;
   if (pg->ActivePage == tsday) {
	 Day(wherestr);
   }else
   {
	 Month(wherestr);
   }

}
void Tfrmretail::Day(AnsiString wherestr)
{
	String sqlstr;
	float Tfix,Tdis,Tamount,TCbprice,Tprofite;
	sqlstr = "select cast(year(hdtime) as varchar(4))+'-'+ cast(month(hdtime) as varchar(2))+'-'+ cast(day(hdtime) as varchar(2)) as date ,sum(FixedPrice) fix,sum(DiscountedPrice) dis,sum(A.Amount) amount,sum(A.Amount*B.Cbprice) as Cbprice,sum(DiscountedPrice-A.Amount*B.Cbprice) as profite "
			 " from BS_RetailNote A left join bs_retailnoteheader on  A.RetailNtHeaderID = bs_retailnoteheader.id left join STK_BookInfo B on A.BkInfoID = B.ID " ;
	sqlstr = sqlstr + wherestr + " group by year(hdtime),month(hdtime), day(hdtime)";
	sqlstr = sqlstr + " union select '合计' ,sum(FixedPrice) fix,sum(DiscountedPrice) dis,sum(A.Amount) amount,sum(A.Amount*B.Cbprice) as Cbprice,sum(DiscountedPrice-A.Amount*B.Cbprice) as profite "
			 " from BS_RetailNote A left join bs_retailnoteheader on  A.RetailNtHeaderID = bs_retailnoteheader.id left join STK_BookInfo B on A.BkInfoID = B.ID " ;
	sqlstr = sqlstr + wherestr ;
	aqday->Close();
	aqday->SQL->Clear();
	aqday->SQL->Add(sqlstr);
	aqday->Open();
	aqday->First();
	((TFloatField *)aqday->FieldByName("fix"))->DisplayFormat = Disc;
	((TFloatField *)aqday->FieldByName("dis"))->DisplayFormat = Disc;
	((TFloatField *)aqday->FieldByName("Cbprice"))->DisplayFormat = Disc;
	((TFloatField *)aqday->FieldByName("profite"))->DisplayFormat = Disc;
	((TFloatField *)aqday->FieldByName("amount"))->DisplayFormat = "###,###,##0";
	
}
void Tfrmretail::Month(AnsiString wherestr)
{
    	String sqlstr;
	float Tfix,Tdis,Tamount,TCbprice,Tprofite;

	sqlstr = "select cast(year(hdtime) as varchar(4))+'-'+ cast(month(hdtime) as varchar(2)) as date ,sum(FixedPrice) fix,sum(DiscountedPrice) dis,sum(A.Amount) amount,sum(A.Amount*B.Cbprice) as Cbprice,sum(DiscountedPrice-A.Amount*B.Cbprice) as profite "
			 " from BS_RetailNote A left join bs_retailnoteheader on  A.RetailNtHeaderID = bs_retailnoteheader.id left join STK_BookInfo B on A.BkInfoID = B.ID " ;
	sqlstr = sqlstr + wherestr + " group by year(hdtime),month(hdtime)";
	sqlstr = sqlstr + " union select '合计' ,sum(FixedPrice) fix,sum(DiscountedPrice) dis,sum(A.Amount) amount,sum(A.Amount*B.Cbprice) as Cbprice,sum(DiscountedPrice-A.Amount*B.Cbprice) as profite "
			 " from BS_RetailNote A left join bs_retailnoteheader on  A.RetailNtHeaderID = bs_retailnoteheader.id left join STK_BookInfo B on A.BkInfoID = B.ID " ;
	sqlstr = sqlstr + wherestr ;
	aqmonth->Close();
	aqmonth->SQL->Clear();
	aqmonth->SQL->Add(sqlstr);
	aqmonth->Open();
	aqmonth->First();
	((TFloatField *)aqmonth->FieldByName("fix"))->DisplayFormat = Disc;
	((TFloatField *)aqmonth->FieldByName("dis"))->DisplayFormat = Disc;
	((TFloatField *)aqmonth->FieldByName("Cbprice"))->DisplayFormat = Disc;
	((TFloatField *)aqmonth->FieldByName("profite"))->DisplayFormat = Disc;
	((TFloatField *)aqmonth->FieldByName("amount"))->DisplayFormat = "###,###,##0";


}
//---------------------------------------------------------------------------
void __fastcall Tfrmretail::pgChange(TObject *Sender)
{
	 if (query) {
	   BtnView->Click();
	 }
}
//---------------------------------------------------------------------------
void __fastcall Tfrmretail::BtnPrintClick(TObject *Sender)
{
 /*	if (pg->ActivePage == tsday) {
		if (dgday->DataSource->DataSet->State == dsInactive) {
		return;
	}
	} else if (pg->ActivePage == tsmonth) {
		if (dgmonth->DataSource->DataSet->State == dsInactive) {
		 return;
		}

	}
   Tfrmretailprint *frm = new Tfrmretailprint(this);
   frm->aqdate->Caption = DateToStr(Now());
   frm->qrluser->Caption = "dddd";
   frm->qrcompany->Caption = "四川西南信心书局有限公司";
   if (rbretail->Checked ) {
		if (pg->ActivePage == tsday) {
			frm->aqtitle->Caption = "零售按日统计报表";
			RPGrid(dgday,frm->qrdg);
		}else
		{
			frm->aqtitle->Caption = "零售按月统计报表";
			RPGrid(dgmonth ,frm->qrdg);
		}
   }else
   {
		if (pg->ActivePage == tsday) {
			frm->aqtitle->Caption = "零售退货按日统计报表";
				RPGrid(dgday,frm->qrdg);
		}else
		{
			frm->aqtitle->Caption = "零售退货按月统计报表";
			RPGrid(dgmonth ,frm->qrdg);
		}
   }
   frm->qrstarttime->Caption = DateToStr(dtpstart->Date);
   frm->qrendtime->Caption = DateToStr(dtpend->Date);
   frm->QuickRep1->Preview();
   delete frm;   */
}
/*void Tfrmretail::RPGrid(TRzDBGrid *dg,TQRPGrid *PRdg )
{
   int rows,cols;
   rows = dg->DataSource->DataSet->RecordCount ;
   cols = dg->FieldCount ;
   PRdg->Columns = cols;
   PRdg->Rows = rows+2;
   PRdg->Height = (rows+2) * 20;
   String TempStr;
   float totalmayang=0,totalsiyang=0,totalnum=0;
   dg->DataSource->DataSet->First();
   for (int i = 0; i < cols; i++) {
	   PRdg->Cells[i][0]->Caption = dg->Columns->Items[i]->Title->Caption     ;
   }

   for (int i = 0; i< dg->DataSource->DataSet->RecordCount ; i++) {

		 for (int j = 0; j  <   dg->FieldCount; j++) {
		  PRdg->Cells[j][i+1]->Caption = dg->Fields[j]->AsString ;

		 }
		totalmayang += dg->DataSource->DataSet->FieldByName("fix")->AsFloat ;
		totalsiyang += dg->DataSource->DataSet->FieldByName("dis")->AsFloat ;
		totalnum += dg->DataSource->DataSet->FieldByName("amount")->AsFloat ;
		dg->DataSource->DataSet->Next();
	}

	PRdg->Cells[0][rows+1]->Caption = "合计";

	PRdg->Cells[1][rows+1]->Caption =  	FormatFloat("0.00",totalmayang);
	PRdg->Cells[2][rows+1]->Caption =  	FormatFloat("0.00",totalsiyang);
	PRdg->Cells[3][rows+1]->Caption =  	FormatFloat("0.00",totalnum);
}
    */
//---------------------------------------------------------------------------


void __fastcall Tfrmretail::BtnExportClick(TObject *Sender)
{
	if (pg->ActivePage == tsday) {
		if (aqday->Active && aqday->RecordCount > 0) {
			DbgridToExcel(dgday);
		}
	}
	if (pg->ActivePage == tsmonth) {
		if (aqmonth->Active && aqmonth->RecordCount > 0) {
			DbgridToExcel(dgmonth);
		}
	}
}
//---------------------------------------------------------------------------

//Excel导出函数
bool __fastcall Tfrmretail::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext ;
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
	if (rbretail->Checked) {
		v.OlePropertyGet("Cells",1,3).OlePropertySet("Value","零售" );
	}
	if (rbback->Checked) {
		v.OlePropertyGet("Cells",1,3).OlePropertySet("Value","零售退货" );
	}
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","开始时间" );
	temptext = "'"+ DateToStr(dtpstart->Date);
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","结束时间" );
	temptext = "'"+ DateToStr(dtpend->Date);
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());

	n=3;

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
   

	return false;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmretail::dgmonthTitleClick(TColumn *Column)
{
	if (aqmonth->IsEmpty() ) {
        return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqmonth->Sort == "") {
		aqmonth->Sort =  Column->FieldName + " ASC";
	}
	else if (aqmonth->Sort == qusort) {
		aqmonth->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqmonth->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretail::dgdayTitleClick(TColumn *Column)
{
	if (aqday->IsEmpty()  ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqday->Sort == "") {
		aqday->Sort =  Column->FieldName + " ASC";
	}
	else if (aqday->Sort == qusort) {
		aqday->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqday->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretail::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized   ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretail::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{

	if (Key == VK_F1) {
		 BtnView->Click();
	   }
		if (Key == VK_F10) {
		 BtnPrint->Click();
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

void __fastcall Tfrmretail::dtpstartChange(TObject *Sender)
{
	cbstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretail::dtpendChange(TObject *Sender)
{
	cbend->Checked = true;
}
//---------------------------------------------------------------------------

