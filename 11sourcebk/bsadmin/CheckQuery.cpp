//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CheckQuery.h"
#include "pdutil.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma link "RzRadChk"
#pragma link "RzDBGrid"
#pragma link "RzDTP"
#pragma link "RzLine"
#pragma link "RzDBEdit"
#pragma link "RzDBCmbo"
#pragma resource "*.dfm"
TfrmCheckQuery *frmCheckQuery;
//---------------------------------------------------------------------------
__fastcall TfrmCheckQuery::TfrmCheckQuery(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	m_module = MTBsqry;
}
//---------------------------------------------------------------------------
void TfrmCheckQuery::Init(TApplication* app, TADOConnection* con)
{
	TfrmMDIChild::Init(app,con);
	qry1->Connection = m_con;
	dsetCheck->Connection = m_con;
	dset1->Connection = m_con;
	qusale->Connection = m_con;
	quhuiyuan->Connection = m_con;
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = m_con;
	sql = "select ID,Name from SYS_StorageInfo where id = " + IntToStr(stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	labstorage->Caption = "当前店：" + aq->FieldByName("Name")->AsString;

	sql = "select * from SYS_BSSET where name = 'retailxiaoshudian'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	format = aq->FieldByName("bk")->AsString ;


	delete aq;
	qry1->Active = true;
	dsetCheck->Active = true;
	sql = "select ID,Name from sys_user where ID in( "
		  "select A.UserID from sys_usergroup A join sys_group B "
		  "ON A.groupID = B.ID WHERE (B.groupname = '零售员') "
		  ") and stgID = " + IntToStr(stgid);
	dset1->CommandText = sql;
	dset1->Active = true;
	dtpstart->Date = Date();
	dtpend->Date = Date();
}
void __fastcall TfrmCheckQuery::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//--------------------------------------------------------------

String TfrmCheckQuery::QueryCom()
{
	String tmpsql="",sql;

//	String date = dtedtEnd->Date.FormatString("yyyy/mm/dd 23:59:59");
//	tmpsql = tmpsql + " (RetailNoteHeaderHdTime <= '" + date + "') ";
//
//	String date = dtedtEnd->Date.FormatString("yyyy/mm/dd 23:59:59");
//	tmpsql = tmpsql + " and (RetailNoteHeaderHdTime <= '" + date + "') ";


	String date1 = dtpstart->Date .FormatString("yyyy-mm-dd") +dtmpckrSetStartTime->Date .FormatString(" hh:mm:ss");//  Date .FormatString("HH/mm//ss") ;//
	tmpsql = tmpsql + " (HdTime >= '" + date1 + "')";
	String date2 = dtpend->Date .FormatString("yyyy-mm-dd") + dtmpckrSetEndTime->Date .FormatString(" hh:mm:ss");//  Date .FormatString("hh/mm//ss");
	tmpsql = tmpsql + " and (HdTime <= '"+ date2 + "')";
	//String sp = cbb1->GetListValue();
	//String amount = cbb1->GetListValue() ;
	tmpsql = tmpsql + "  and (OperatorID = '" + dset1->FieldByName("ID")->AsString + "')";
	sql = "select sum(FixedPrice) as FixedPrice,sum(thistime) as Checked from BS_WsaleNoteHeader inner join BS_WsaleNoteHeader_Attachment on BS_WsaleNoteHeader.id = BS_WsaleNoteHeader_Attachment.wsalentcode where OperatorID = " + dset1->FieldByName("ID")->AsString;
	sql = sql + " and (Time >= '" + date1 + "') and (Time <= '" + date2 + "')";
	qusale->Close();
	qusale->SQL->Clear();
	qusale->SQL->Add(sql);
	qusale->Open();
	return  tmpsql;
}
//---------------------------------


void __fastcall TfrmCheckQuery::btnExit1Click(TObject *Sender)
{

	if (cbb1->Text == "") {
	   MessageBox(0,"请选择当值零售员","提示",MB_ICONEXCLAMATION);
	  return;

	}
	edtReceivedMoney->Text = "";
	edtRecCardMoney->Text = "";
	edtRecCash->Text = "";
	edtposAmount->Text = "";
	edtposTotalDiscountedPrice->Text = "";
	edtposTotalFixedPrice->Text = "";
	edtDiscountedPrice->Text = "";
	edtnegAmount->Text = "";
	edtnegTotalDiscountedPrice->Text = "";
	edtnegTotalFixedPrice->Text = "";
	edtAfterDiscountedMoney->Text = "";
	Query();
	String operatorID = dset1->FieldByName("ID")->AsString;//cbb1->GetListValue() ;

	AnsiString sql;
	String date1 = dtpstart->Date .FormatString("yyyy-mm-dd") +dtmpckrSetStartTime->Date .FormatString(" hh:mm:ss");//  Date .FormatString("HH/mm//ss") ;//
	String date2 = dtpend->Date .FormatString("yyyy-mm-dd") + dtmpckrSetEndTime->Date .FormatString(" hh:mm:ss");//  Date .FormatString("hh/mm//ss");
	sql = "select sum(CorrentVoucher) as voucher from CUST_MemberToprecord where userid = " + operatorID + " and date >= '" + date1 + "' and date <= '" + date2 + "'";
	quhuiyuan->Close();
	quhuiyuan->SQL->Clear();
	quhuiyuan->SQL->Add(sql);
	quhuiyuan->Open();

	int d1;
	float d2,d3,d4,d5,d6 ;
	int t1,t2=0,t3;
	int posAmount=0,negAmount=0;
	float AfterDiscountedMoney=0,RecCardMoney=0,RecCash=0,posTotalFixedPrice=0,negTotalFixedPrice=0,posTotalDiscountedPrice=0,negTotalDiscountedPrice=0,PostCard = 0,Youhuiquan = 0;
	//int d = dbgrdCheck->DataSource ->DataSet ->RecNo;
	//dbgrdCheck->DataSource ->DataSet ->RecNo = dbgrdCheck->DataSource ->DataSet ->RecordCount ;
	//dsetCheck ->RecNo = 1;
	dsetCheck->Active = true;
	if(dsetCheck -> RecordCount != 0)
	{
		while(dsetCheck ->RecNo <= dsetCheck ->RecordCount && t2<= dsetCheck->RecordCount )//
		{
			//设置两个flag
			t1 = dsetCheck->RecordCount ;
			t2 = dsetCheck->RecNo;
			if(t2==t1)
			{
				t2++;
			}
			//数据汇总
			if(dbgrdCheck->DataSource ->DataSet ->FieldByName("OperatorID")->Value == StrToInt(operatorID) )
			{
				d1 = dbgrdCheck ->DataSource ->DataSet ->FieldByName("TotalAmount")->Value ;
				if(d1>0)
				posAmount += d1 ;
				else
				negAmount += d1 ;

				d2 = dbgrdCheck ->DataSource ->DataSet ->FieldByName("TotalDiscountedPrice")->Value ;
				if(d2>0)
				posTotalDiscountedPrice += d2;
				else
				{
					negTotalDiscountedPrice += d2;
					negTotalFixedPrice = negTotalFixedPrice-dbgrdCheck ->DataSource ->DataSet ->FieldByName("TotalFixedPrice")->Value;
				}


				d3 = dbgrdCheck ->DataSource ->DataSet ->FieldByName("TotalFixedPrice")->Value ;
				if(d3>0)
				posTotalFixedPrice += d3;
				//else
				//negTotalFixedPrice += d3;

				d4 = dbgrdCheck ->DataSource ->DataSet ->FieldByName("RecCash")->Value ;

				d5 = dbgrdCheck ->DataSource ->DataSet ->FieldByName("RecCardMoney")->Value ;
				RecCardMoney += d5;
				PostCard = PostCard + dbgrdCheck ->DataSource ->DataSet ->FieldByName("poscard")->Value ;
				Youhuiquan = Youhuiquan + dbgrdCheck ->DataSource ->DataSet ->FieldByName("youhuiquan")->Value ;

				if (d2 > 0)
				{
					float tmp = 0.00;
					if (d4 + d5 >= d2)
						tmp = d2 - d5;
					else
						tmp = d4;
					RecCash += tmp;
				}

				d6 = d4 + d5 - d2;
				if (d6 < 0)
				{
                	AfterDiscountedMoney += d6;
				}
//				d6 = dbgrdCheck->DataSource ->DataSet ->FieldByName("AfterDiscountedMoney")->Value ;
//				AfterDiscountedMoney += d6;
			}
			if(dsetCheck->RecNo < dsetCheck->RecordCount)
			dsetCheck->RecNo ++;
			// 查询完毕，返回第一列
			if(t2 > t1)
			dsetCheck->RecNo = 1;
		 }

		//int y = (posTotalDiscountedPrice-negTotalDiscountedPrice)*10/10;
		edtAfterDiscountedMoney->Text = FormatFloat(format, /*AfterDiscountedMoney*/posTotalDiscountedPrice - negTotalDiscountedPrice - RecCash - RecCardMoney-Youhuiquan);

		edtposAmount->Text = IntToStr(posAmount);
		edtnegAmount->Text = IntToStr(negAmount);
		edtposTotalDiscountedPrice->Text = FormatFloat(format,posTotalDiscountedPrice);//FloatToStr(posTotalDiscountedPrice);
		edtnegTotalDiscountedPrice->Text = FormatFloat(format,negTotalDiscountedPrice);//FloatToStr(negTotalDiscountedPrice);
		edtposTotalFixedPrice->Text = FormatFloat("#,##0.00",posTotalFixedPrice);//FloatToStr(posTotalFixedPrice);
		edtnegTotalFixedPrice->Text = FormatFloat("#,##0.00",negTotalFixedPrice);//FloatToStr(negTotalFixedPrice);
		edtDiscountedPrice->Text = FormatFloat(format,posTotalFixedPrice-posTotalDiscountedPrice);//FloatToStr( posTotalFixedPrice-posTotalDiscountedPrice);
		String x = FormatFloat(format,int(posTotalDiscountedPrice * 10)%10/10.0);
		edtRecCash->Text = FormatFloat(format,RecCash + negTotalDiscountedPrice + qusale->FieldByName("Checked")->AsFloat);
		edtRecCardMoney->Text = FormatFloat(format,RecCardMoney);
		edtRecPostCard->Text = FormatFloat(format,PostCard);
		edtRecYouhuiquan->Text = FormatFloat(format,Youhuiquan);
		edtwsaleTotalFixedPrice->Text = FormatFloat("#,##0.00",qusale->FieldByName("FixedPrice")->AsFloat);
		edtwsaleTotalDiscountedPrice->Text = FormatFloat(format,qusale->FieldByName("Checked")->AsFloat);
		//edtAfterDiscountedMoney->Text = FormatFloat("#,##0.00",AfterDiscountedMoney);


		edtReceivedMoney->Text =  FormatFloat(format,RecCash+RecCardMoney + negTotalDiscountedPrice + qusale->FieldByName("Checked")->AsFloat);
		edhycongzhi->Text = FormatFloat("#,##0.00",quhuiyuan->FieldByName("voucher")->AsFloat );
	}
}
//---------------------------------------------------------------------------
void TfrmCheckQuery::Query()
{
	if (dsetCheck->Active)
	{
		dsetCheck->Active = false;
	}
   //	dsetCheck->Connection = con1;
	m_sql = "select TotalAmount,HdTime, OperatorID, TotalDiscountedPrice, TotalFixedPrice,RecCardMoney,RecCash,poscard,youhuiquan  from BS_RetailNoteHeader where";  // where
	String tmpsql = QueryCom();
	m_sql = m_sql + tmpsql;
	//dsetCheck->Active = false;
	//m_sql =  "select OperatorID,TotalFixedPrice,TotalDiscountedPrice,Amount from UV_CheckQuery where (HdTime >= '2009-08-01 20:17:36') and (HdTime <= '2009-08-01 20:17:36') and (OperatorID = '0')" ;
	dsetCheck->CommandText = m_sql;
	dsetCheck->Active = true;
//	qry1->Active = false;
//	qry1->SQL->Clear();
//	qry1->SQL->Add(m_sql);
//	qry1->Active = true;
}
void __fastcall TfrmCheckQuery::btnExit3Click(TObject *Sender)
{
//Excel导出
	if(dsetCheck->Active && dsetCheck->RecordCount != 0 )
	{
		DbgridToExcel(dbgrdCheck);
	}

}
//---------------------------------------------------------------------------
//Excel导出函数
bool __fastcall TfrmCheckQuery::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext  ;
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
	//v.OlePropertyGet("Cells",1,1).OlePropertySet("Value","指定日期" );
	//temptext = "'"+ DateToStr(dtmpckrSetDate->Date);
	//v.OlePropertyGet("Cells",1,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",1,1).OlePropertySet("Value","起始时间" );
	temptext = "'"+ DateToStr(dtpstart->Date) + " " + DateTimeToStr(dtmpckrSetStartTime->DateTime);
	v.OlePropertyGet("Cells",1,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",2,1).OlePropertySet("Value","结束时间" );
	temptext = "'"+ DateToStr(dtpend->Date) + " " + DateTimeToStr(dtmpckrSetEndTime->DateTime);
	v.OlePropertyGet("Cells",2,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","当值售货员");
	temptext = "'"+ cbb1->Text;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,1).OlePropertySet("Value","零售册数" );
	temptext = "'"+ edtposAmount->Text;
	v.OlePropertyGet("Cells",4,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,4).OlePropertySet("Value","退货册数" );
	temptext = "'"+ edtnegAmount->Text;
	v.OlePropertyGet("Cells",4,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",5,1).OlePropertySet("Value","零售实洋" );
	temptext = "'"+ edtposTotalDiscountedPrice->Text;
	v.OlePropertyGet("Cells",5,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",5,4).OlePropertySet("Value","退货实洋" );
	temptext = "'"+ edtnegTotalDiscountedPrice->Text;
	v.OlePropertyGet("Cells",5,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",6,1).OlePropertySet("Value","零售码洋" );
	temptext = "'"+ edtposTotalFixedPrice->Text;
	v.OlePropertyGet("Cells",6,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",6,4).OlePropertySet("Value","退货码洋" );
	temptext = "'"+ edtnegTotalFixedPrice->Text;
	v.OlePropertyGet("Cells",6,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",7,1).OlePropertySet("Value","折扣金额" );
	temptext = "'"+ edtDiscountedPrice->Text;
	v.OlePropertyGet("Cells",7,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",7,4).OlePropertySet("Value","折扣优惠" );
	temptext = "'"+ edtAfterDiscountedMoney->Text;
	v.OlePropertyGet("Cells",7,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",8,1).OlePropertySet("Value","账面收款" );
	temptext = "'"+ edtReceivedMoney->Text;
	v.OlePropertyGet("Cells",8,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",8,4).OlePropertySet("Value","现金收款" );
	temptext = "'"+ edtRecCash->Text;
	v.OlePropertyGet("Cells",8,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",8,7).OlePropertySet("Value","储值卡收款" );
	temptext = "'"+ edtRecCardMoney->Text;
	v.OlePropertyGet("Cells",8,8).OlePropertySet("Value",temptext .c_str() );

	n=9;

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

void __fastcall TfrmCheckQuery::btnExit2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void TfrmCheckQuery::OnHotKeyPress(DWORD vkCode)
{
	
	if(vkCode == VK_ESCAPE)
	btnExit2Click(NULL);
	if(vkCode == 81)
    btnExit1Click(NULL);
}



void __fastcall TfrmCheckQuery::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{	if (Key == VK_F1) {
		btnExit1->Click();
	}
		if (Key == VK_F6) {
		btnExit3->Click();
	}
		if (Key == VK_F10) {
		btnExit4->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==81  ) {
	   btnExit2->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {
	   BtnAlignBottom->Click();
	}
}

//---------------------------------------------------------------------------

void __fastcall TfrmCheckQuery::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------



void __fastcall TfrmCheckQuery::btnExit4Click(TObject *Sender)
{
	TStrings* ss = new TStringList();

	TADODataSet* dsPrint=new TADODataSet(NULL);
	dsPrint->Connection=m_con ;


	if (dsPrint->Active) {
		dsPrint->Active=false;
	}
	dsPrint->CommandText="select retailprintcom from SYS_StorageInfo where id = " + IntToStr(stgid) ;
	dsPrint->Active=true;

	AnsiString space = "                                                      ";

	String s="起始时间：" + DateToStr(dtpstart->Date) + " " + TimeToStr(dtmpckrSetStartTime->Time);
	s = s + "\n结束时间：" + DateToStr(dtpend->Date) + " " + TimeToStr(dtmpckrSetEndTime->Time);
	s = s + "\n收银员："+cbb1->Text.Trim();
	s=s+"\n________________________________\n\n";
	s = s + "零售册数：" + edtposAmount->Text.Trim() + space.SubString(0,15- edtposAmount->Text.Trim().Length()) + "退换册数：" + edtnegAmount->Text.Trim();
	s = s + "\n零售实洋：" + edtposTotalDiscountedPrice->Text.Trim() + space.SubString(0,15- edtposTotalDiscountedPrice->Text.Trim().Length()) + "退货实洋：" + edtnegTotalDiscountedPrice->Text.Trim();
	s = s + "\n零售码洋：" + edtposTotalFixedPrice->Text.Trim() + space.SubString(0,15- edtposTotalFixedPrice->Text.Trim().Length()) + "退货码洋：" + edtnegTotalFixedPrice->Text.Trim();
	s = s + "\n折扣金额：" + edtDiscountedPrice->Text.Trim() + space.SubString(0,15- edtDiscountedPrice->Text.Trim().Length()) + "折后优惠：" + edtAfterDiscountedMoney->Text.Trim();
	s = s + "\n会员充值：" + edhycongzhi->Text.Trim();
	s = s + "\n账面收款：" + edtReceivedMoney->Text.Trim() + space.SubString(0,15- edtReceivedMoney->Text.Trim().Length()) + "现金收款：" + edtRecCash->Text.Trim();
	s = s + "\n储值卡收款：" + edtRecCardMoney->Text.Trim() + space.SubString(0,13- edtRecCardMoney->Text.Trim().Length()) + "银行卡收款：" + edtRecPostCard->Text.Trim();
	s = s + "\n优惠券收款：" + edtRecYouhuiquan->Text.Trim() ;


	ss->Text=s;

	//ss->SaveToFile("d:\\pddata.txt");

	TStringList *lst = new TStringList;

	DCB dd;
	DWORD dwWrited;
	HANDLE m_hComm;
	LPCTSTR  strCom = dsPrint->FieldByName("retailprintcom")->AsString.t_str();
	COMMTIMEOUTS comtimeout;

	int nLpt  ;
	try
	{
        m_hComm=CreateFile(TEXT(strCom),GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if (m_hComm==INVALID_HANDLE_VALUE)
		{
			MessageBox(0,"此通讯口已被占用或损坏！","提示" ,MB_ICONEXCLAMATION);
			m_hComm=NULL;
			return ;
		}
		comtimeout.ReadIntervalTimeout =10;
		comtimeout.ReadTotalTimeoutConstant =10;
		comtimeout.ReadTotalTimeoutMultiplier =10;
		comtimeout.WriteTotalTimeoutConstant =100;
		comtimeout.WriteTotalTimeoutMultiplier =500;
		SetCommTimeouts(m_hComm,&comtimeout);
		DWORD dwSize = 0;
		lst->AddStrings(ss);
		AnsiString strAnsiLine;

		for (int i = 0; i < lst->Count; i++)
		{
			strAnsiLine = AnsiString(lst->Strings[i]) + AnsiString("\r\n");

			if (!WriteFile(m_hComm,strAnsiLine.c_str(),strAnsiLine.Length() ,&dwSize,NULL))
			{
				FlushFileBuffers(m_hComm);
				CloseHandle(m_hComm);
				return;
			}
		}

		FlushFileBuffers(m_hComm);
		CloseHandle(m_hComm);
	}
	__finally
	{
			//LockWindowUpdate(NULL);
	}
}
//---------------------------------------------------------------------------

