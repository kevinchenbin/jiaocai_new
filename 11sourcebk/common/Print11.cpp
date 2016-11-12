//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Print11.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpBase"
#pragma link "RpSystem"
#pragma link "MDIChild"
#pragma link "MDIChild"
#pragma resource "*.dfm"
TfrmPrint11 *frmPrint11;
//---------------------------------------------------------------------------
__fastcall TfrmPrint11::TfrmPrint11(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


//-----------------小票打印，传入小票单ID和一个con连接实现写一个文本文件然后把文本文件送往并口lpt1打印------------------------------
void TfrmPrint11::RetailPrint(String ID,TADOConnection* con,int stgid)
{

	TADODataSet* dsPrint=new TADODataSet(NULL);
	TADODataSet* dsretail=new TADODataSet(NULL);
	dsretail->Connection=con;
	dsPrint->Connection=con;
	aquerybs->Connection = con;

	AnsiString sql = "select * from SYS_BSSET where name = 'retailxiaoshudian'";
	AnsiString fromat;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	fromat = aq->FieldByName("bk")->AsString ;
	int  xiaoshubit;
	AnsiString cc;
	if (aq->FieldByName("bk")->AsString == "0") {
		xiaoshubit = 0;
		cc = "%0.0f";
	}
	else if (aq->FieldByName("bk")->AsString == "0.0") {
		xiaoshubit = 1;
		cc = "%0.1f";
	}
	else if (aq->FieldByName("bk")->AsString == "0.00") {
		xiaoshubit = 2;
		cc = "%0.2f";
	}
	delete aq;

	if (dsPrint->Active) {
		dsPrint->Active=false;
	}
	dsPrint->CommandText="select Name,retailxptype,RetailNoteTitle,RetailNoteWelcomeMessage,RetailNoteAddress,RetailNoteTel,RetailNoteRemarks,ShowRetailNoteISBN,ShowRetailNoteBookName,ShowRetailNotePricing,ShowRetailNoteDiscount,ShowRetailCardRec,ShowRetailtotalhang,ShowRetailAmount,ShowRetaildisprice,retailprintcom,printmayang,printdiscount from SYS_StorageInfo where id = " + IntToStr(stgid) ;
	dsPrint->Active=true;
	if (dsretail->Active) {
		dsretail->Active=false;
	}
	sql = "select rank() over (order by BS_RetailNote.id) as xuhao,len(BS_BookCatalog.Name) as lenthName,len(BS_BookCatalog.Name) as lenth,SYS_User.Name as operatorName,RecCash+RecCardMoney-TotalDiscountedPrice as backMoney,TotalFixedPrice,TotalDiscountedPrice,RecCash,RecCardMoney,poscard,youhuiquan,BS_BookCatalog.Name as bookName,BS_BookCatalog.ISBN as ISBN,BS_BookCatalog.Price as price ,RetailNtCode,HdTime as Time ,BS_RetailNote.Amount as Amount,DiscountedPrice ,FixedPrice,Discount,BS_RetailNoteHeader.TotalAmount from BS_RetailNote left join BS_RetailNoteHeader on  RetailNtHeaderID=BS_RetailNoteHeader.id left join STK_BookInfo on BkInfoID=STK_BookInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join SYS_User on SYS_User.id=OperatorID where BS_RetailNoteHeader.ID="+ID+" order by RetailNtCode";
	dsretail->CommandText= sql;
	//conRVretail->DataSet = dsretail;
	dsretail->Active=true;
	aquerybs->Close();
	aquerybs->SQL->Clear();
	aquerybs->SQL->Add(sql);
	aquerybs->Open();

	if (dsPrint->FieldByName("retailxptype")->AsInteger == 1 ) {


		RvSystem1->SystemSetups >>ssAllowSetup;
		RvSystem1->SystemSetups >>ssAllowDestPreview;
		RvSystem1->SystemSetups >>ssAllowDestPrinter;
		RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		RvSystem1->SystemSetups >>ssAllowDestFile;
		RvSystem1->DefaultDest  = rdPrinter ;
		RvSystem1->SystemSetups<<ssAllowDestPrinter;

		prjretail->ProjectFile = ExtractFilePath(Application->ExeName) + "retail.rav";
		prjretail->Open();
	
		prjretail->SetParam("title",dsPrint->FieldByName("Name")->AsAnsiString+"零售单");
		prjretail->SetParam("danhao",dsretail->FieldByName("RetailNtCode")->AsString);
		prjretail->SetParam("riqi",dsretail->FieldByName("Time")->AsString);
		prjretail->SetParam("shouyingyuan",dsretail->FieldByName("operatorName")->AsString);
		AnsiString bb;
		bb.sprintf(cc.c_str(),dsretail->FieldByName("TotalDiscountedPrice")->AsFloat );
		prjretail->SetParam("zhongyingshou",bb);
		AnsiString total= FormatFloat(fromat,dsretail->FieldByName("RecCash")->AsFloat+dsretail->FieldByName("RecCardMoney")->AsFloat + dsretail->FieldByName("poscard")->AsFloat + dsretail->FieldByName("youhuiquan")->AsFloat);
		prjretail->SetParam("shoukuan",total);
		prjretail->SetParam("zhaoling",FormatFloat(fromat,StrToFloat(total) - StrToFloat(bb)));
		prjretail->SetParam("yuanjiaheji",FormatFloat(fromat,dsretail->FieldByName("TotalFixedPrice")->AsFloat));
		prjretail->SetParam("dizhi","地址:"+dsPrint->FieldByName("RetailNoteAddress")->AsString);
		prjretail->SetParam("dianhua","电话:"+dsPrint->FieldByName("RetailNoteTel")->AsString);
		prjretail->SetParam("beizhu","备注:"+dsPrint->FieldByName("RetailNoteRemarks")->AsString);

		prjretail->Execute();
		prjretail->Close();
	}
	else
	{
		String bookbk = "                                                                       ";
		int n = 0,namelen = 16;
		if (dsPrint->FieldByName("ShowRetailNotePricing")->AsString==1 ) {
			n = n+ 1;
		}
		if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1 ) {
			n = n+ 1;
		}
		if (dsPrint->FieldByName("ShowRetailNoteDiscount")->AsString==1 ) {
			n = n+ 1;
		}
		if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1 ) {
			n = n+ 1;
		}
		TStrings* ss = new TStringList();
		dsPrint->First();
		String s="  -----"+dsPrint->FieldByName("RetailNoteWelcomeMessage")->AsString+"-----\n" ;
		s=s+"单号:"+dsretail->FieldByName("RetailNtCode")->AsString;
		s=s+"\n日期:"+dsretail->FieldByName("Time")->AsString+"\n收银员:"+dsretail->FieldByName("operatorName")->AsString+"\n";
		s=s+"\n";
		if (dsPrint->FieldByName("ShowRetailNoteBookName")->AsString==1 ) {
			namelen = 16-3*n;
			s = s + "书名    " + bookbk.SubString(1,(4-n)*5+2);
		}
		if (dsPrint->FieldByName("ShowRetailNotePricing")->AsString==1 ) {
			s=s+" 定价 ";
		}
		if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1 ) {
			s=s+"数量 ";
		}
		if (dsPrint->FieldByName("ShowRetailNoteDiscount")->AsString==1 ) {
			s=s+"折扣 ";
		}
		if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1 ) {
			s=s+"金额 ";
		}
		s=s+"\n--------------------------------\n\n";
		dsretail->First();
		String stemp;

		bool huanhang = false,first = true;
		while (!dsretail->Eof)
		{
			String bookname=dsretail->FieldByName("bookName")->AsString;
			if ( dsretail->FieldByName("Discount")->AsFloat  == 0 ) {
				bookname = bookname + "(赠品)";
			}
			bookname = bookname.TrimRight();
			//控制书名每行输出6个字
			huanhang = false;
			first = true;
			int len=bookname.Length();
			if (len>48) {
				stemp=bookname.SubString(1,16)+"\n"+bookname.SubString(17,16)+"\n"+bookname.SubString(33,16)+"\n"+bookname.SubString(49,16);
				stemp =  stemp + "\n";
				huanhang = true;
			}
			else if (len>32) {
				stemp=bookname.SubString(1,16)+"\n"+bookname.SubString(17,16)+"\n"+bookname.SubString(33,16);
				stemp =  stemp + "\n";
				huanhang = true;
			}
			else if (len>16) {
				stemp=bookname.SubString(1,16)+"\n"+bookname.SubString(17,16);
				stemp =  stemp + "\n";
				huanhang = true;
			}
			else if (len>namelen) {
				stemp=bookname + "\n";
				huanhang = true;
			}
			else if (len == namelen) {
				stemp=bookname + bookbk.SubString(1,2*((namelen-len))-2);
			}
			else if (len < namelen) {
				stemp=bookname + bookbk.SubString(1,2*(namelen-len));
			}
			if (dsPrint->FieldByName("ShowRetailNoteBookName")->AsString==1 ) {
				s=s+stemp;
			}
			if (dsPrint->FieldByName("ShowRetailNotePricing")->AsString==1 ) {
				AnsiString Price;
				Price = dsretail->FieldByName("price")->AsString;
				Price = bookbk.SubString(1,5-Price.Length()) + Price;
				if (dsPrint->FieldByName("ShowRetailNoteBookName")->AsString==1 && huanhang) {
					s=s+ bookbk.SubString(1,namelen*2+1) + Price;
				}
				else
				{
					s=s+ " " + Price;
				}
				first = false;
			}
			if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1) {
				AnsiString Amount;
				Amount = dsretail->FieldByName("Amount")->AsString;
				if (first) {
					Amount = bookbk.SubString(1,3-Amount.Length()) + Amount;
				}
				else
				{
					Amount = bookbk.SubString(1,4-Amount.Length()) + Amount;
				}
				if (first && huanhang) {
					s=s+ bookbk.SubString(1,namelen*2+1) + Amount;
				}
				else
				{
					s=s+ " " + Amount;
				}
				first = false;
			}

			if (dsPrint->FieldByName("ShowRetailNoteDiscount")->AsString==1 ) {
				AnsiString discountprint;
				discountprint = dsretail->FieldByName("Discount")->AsString;
				discountprint = bookbk.SubString(1,3-discountprint.Length()) + discountprint +"%";
				if (first && huanhang) {
					s=s+ bookbk.SubString(1,namelen*2) + discountprint;
				}
				else if (first) {
					s = s + discountprint;
				}
				else if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1) {
					s = s + "  "+ discountprint;
				}
				else
				{
					s = s + " "+ discountprint;
				}
				first = false;
			}
			if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1) {
				if (first && huanhang) {
					s=s+ "                         " + FormatFloat("0.0",dsretail->FieldByName("DiscountedPrice")->AsFloat);
				}
				else if (first) {
					s=s + FormatFloat("0.0",dsretail->FieldByName("DiscountedPrice")->AsFloat);
				}
				else
				{
					s=s+ " " + FormatFloat("0.0",dsretail->FieldByName("DiscountedPrice")->AsFloat);
				}
			}


			s=s+"\n";
			dsretail->Next();
		}
		dsretail->First();
		if (dsPrint->FieldByName("ShowRetailtotalhang")->AsString==1) {
			s=s+"--------------------------------\n";
			s=s+ "合计:" ;
			if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1 && dsPrint->FieldByName("ShowRetailNotePricing")->AsString==1) {
				AnsiString TotalAmount;
				TotalAmount = dsretail->FieldByName("TotalAmount")->AsString;
				TotalAmount = bookbk.SubString(1,3-TotalAmount.Length()) + TotalAmount;
				s=s +bookbk.SubString(1,(6-n)*5+1) + TotalAmount;
			}
			else if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1) {
				AnsiString TotalAmount;
				TotalAmount = dsretail->FieldByName("TotalAmount")->AsString;
				TotalAmount = bookbk.SubString(1,3-TotalAmount.Length()) + TotalAmount;
				if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1) {
					s=s +bookbk.SubString(1,(5-n)*5) + TotalAmount;
				}
				else
				{
					s=s +bookbk.SubString(1,(5-n)*5+1) + TotalAmount;
				}
			}
			if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1 && dsPrint->FieldByName("ShowRetailAmount")->AsString==1 && dsPrint->FieldByName("ShowRetailNoteDiscount")->AsString==1 ) {
				s = s + "       " + FormatFloat("0.0",dsretail->FieldByName("TotalDiscountedPrice")->AsFloat);
			}
			else if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1 && dsPrint->FieldByName("ShowRetailAmount")->AsString==1) {
				s = s + " " + FormatFloat("0.0",dsretail->FieldByName("TotalDiscountedPrice")->AsFloat);
			}
			else if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1) {
				s = s + bookbk.SubString(1,(5-n)*5+1) + FormatFloat("0.0",dsretail->FieldByName("TotalDiscountedPrice")->AsFloat);
			}
			s = s + "\n";
		}
		s=s+"\n--------------------------------\n";
		AnsiString total= FormatFloat(fromat,dsretail->FieldByName("RecCash")->AsFloat+dsretail->FieldByName("RecCardMoney")->AsFloat + dsretail->FieldByName("poscard")->AsFloat + dsretail->FieldByName("youhuiquan")->AsFloat);

		AnsiString bb;
		bb.sprintf(cc.c_str(),dsretail->FieldByName("TotalDiscountedPrice")->AsFloat );
		s=s+"总应收:"+bb ;
		if (dsPrint->FieldByName("printmayang")->AsString==1) {
			s = s + "      原价合计:" +  FormatFloat(fromat,dsretail->FieldByName("TotalFixedPrice")->AsFloat);
		}
		s=s+ "\n"+ "收款:"+total;
		int len1,len2;
		len1 = bb.Length();
		len2 = total.Length();
		if (dsPrint->FieldByName("printdiscount")->AsString==1) {
			s = s + bookbk.SubString(1,8-len2+len1) + "折扣金额:"+ FormatFloat(fromat,dsretail->FieldByName("TotalFixedPrice")->AsFloat - StrToFloat(bb) );
		}
		if (dsPrint->FieldByName("ShowRetailCardRec")->AsString==1) {
			s=s+"\n其中刷卡消费:"+FormatFloat(fromat,dsretail->FieldByName("RecCardMoney")->AsFloat);
		}
		s=s+"\n找零:"+FormatFloat(fromat,StrToFloat(total) - StrToFloat(bb))+"\n";
		s=s+"--------------------------------\n\n";
		s=s+"地址:"+dsPrint->FieldByName("RetailNoteAddress")->AsString+"\n";
		s=s+"电话:"+dsPrint->FieldByName("RetailNoteTel")->AsString+"\n";
		s=s+"备注:"+dsPrint->FieldByName("RetailNoteRemarks")->AsString+"\n\n\n\n\n";

		ss->Text=s;

        TStringList *lst = new TStringList;

		DCB dd;
		DWORD dwWrited;
		HANDLE m_hComm;
		LPCTSTR  strCom = dsPrint->FieldByName("retailprintcom")->AsString.t_str();
		COMMTIMEOUTS comtimeout;

		int nLpt  ;
		try
		{
			char p[5]= {27,112,0,60,255};

			m_hComm=CreateFile(TEXT(strCom),GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if (m_hComm==INVALID_HANDLE_VALUE)
			{
				MessageBox(0,"此通讯口已被占用或损坏！","零售" ,MB_ICONEXCLAMATION);
				m_hComm=NULL;
				return ;
			}
			comtimeout.ReadIntervalTimeout =10;
			comtimeout.ReadTotalTimeoutConstant =10;
			comtimeout.ReadTotalTimeoutMultiplier =10;
			comtimeout.WriteTotalTimeoutConstant =10;
			comtimeout.WriteTotalTimeoutMultiplier =50;
			SetCommTimeouts(m_hComm,&comtimeout);

			DWORD dwSize = 0;
			if (!WriteFile(m_hComm,p,5 ,&dwSize,NULL))
			{
				FlushFileBuffers(m_hComm);
				CloseHandle(m_hComm);
				return;
			}
			FlushFileBuffers(m_hComm);
			CloseHandle(m_hComm);

			m_hComm=CreateFile(TEXT(strCom),GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if (m_hComm==INVALID_HANDLE_VALUE)
			{
				MessageBox(0,"此通讯口已被占用或损坏！","零售" ,MB_ICONEXCLAMATION);
				m_hComm=NULL;
				return ;
			}
			comtimeout.ReadIntervalTimeout =10;
			comtimeout.ReadTotalTimeoutConstant =10;
			comtimeout.ReadTotalTimeoutMultiplier =10;
			comtimeout.WriteTotalTimeoutConstant =100;
			comtimeout.WriteTotalTimeoutMultiplier =500;
			SetCommTimeouts(m_hComm,&comtimeout);

			dwSize = 0;
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

		}

	}

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TfrmPrint11::RetailjiaojiePrint(String userid,TADOConnection* con,int stgid)
{
		 TADODataSet* dsjiaojiePrint=new TADODataSet(NULL);
		 TADODataSet* dsjiaojieretail=new TADODataSet(NULL);
		 TADODataSet* dsshijian=new TADODataSet(NULL);
		 TADODataSet* dsPrint=new TADODataSet(NULL);
		 dsPrint->Connection=con;
		 AnsiString sql;
		 dsjiaojiePrint->Connection=con;
		 dsjiaojieretail->Connection=con;
		 dsshijian->Connection = con;


		 if (dsPrint->Active) {
			dsPrint->Active=false;
		 }
		 dsPrint->CommandText="select retailxptype,RetailNoteTitle,RetailNoteWelcomeMessage,RetailNoteAddress,RetailNoteTel,RetailNoteRemarks,ShowRetailNoteISBN,ShowRetailNoteBookName,ShowRetailNotePricing,ShowRetailNoteDiscount,ShowRetailCardRec,ShowRetailtotalhang,ShowRetailAmount,ShowRetaildisprice,retailprintcom,printmayang,printdiscount from SYS_StorageInfo where id = " + IntToStr(stgid) ;
		 dsPrint->Active=true;

		 sql = "select Name from SYS_User where id = " + userid;
		 dsjiaojiePrint->Active = false;
		 dsjiaojiePrint->CommandText = sql;
		 dsjiaojiePrint->Active = true;

		 sql = "select top 1 convert(varchar(8),EventDate,114) as EventDate,convert(varchar(8),getdate(),114) as now from Sys_log where EventUser = " + userid + " and EventDate > convert(varchar(10),getdate(),120) ";
		 sql = sql + " and SourceFrom = '登录窗口' and EventDate > ";
		 sql = sql + " (select (case when (select top 1 EventDate from Sys_log where EventUser = " + userid + " and EventDate > convert(varchar(10),getdate(),120) ";
		 sql = sql + " and SourceFrom = '交接' order by EventDate desc) is null then convert(varchar(10),getdate(),120) ";
		 sql = sql + " else (select top 1 EventDate from Sys_log where EventUser = " + userid + " and EventDate > convert(varchar(10),getdate(),120) ";
		 sql = sql + " and SourceFrom = '交接' order by EventDate desc) end )) ";
		 dsshijian->Active = false;
		 dsshijian->CommandText = sql;
		 dsshijian->Active = true;

		 sql = "select sum(TotalAmount) as amount,sum(case when RecCash > TotalDiscountedPrice then TotalDiscountedPrice else RecCash end) as RecCash,"
				"sum(RecCardMoney) as RecCardMoney,sum(TotalFixedPrice) as TotalFixedPrice,"
				"sum(TotalDiscountedPrice) as TotalDiscountedPrice,sum (case when RecCardMoney+RecCash < TotalDiscountedPrice then TotalDiscountedPrice-RecCardMoney-RecCash else 0 end) as zhehouyouhui,"
				"sum(case when RecCardMoney+RecCash < TotalDiscountedPrice then RecCardMoney+RecCash else TotalDiscountedPrice end) as zhangmianshoukuan "
				"from BS_RetailNoteHeader "
				"where Operatorid = " + userid + " and HdTime between '" + DateToStr(Date()) + " " + dsshijian->FieldByName("EventDate")->AsString +
				"' and '" + DateToStr(Date()) + " " + dsshijian->FieldByName("now")->AsString + "'";
		 dsjiaojieretail->Active = false;
		 dsjiaojieretail->CommandText = sql;
		 dsjiaojieretail->Active = true;

		 //取得书名 字段最大长度

		 TStrings* ss = new TStringList();
		 String s="日期："+ DateToStr(Date()) +"\n时间："+dsshijian->FieldByName("EventDate")->AsString+"——" + dsshijian->FieldByName("now")->AsString;
		 s = s + "\n收银员："+dsjiaojiePrint->FieldByName("Name")->AsString+"\n";
		 s=s+"________________________________\n\n";
		 s = s + "零售实洋：" + dsjiaojieretail->FieldByName("TotalFixedPrice")->AsString + "\n";
		 s = s + "零售码洋：" + dsjiaojieretail->FieldByName("TotalDiscountedPrice")->AsString + "\n";
		 s = s + "零售册数：" + dsjiaojieretail->FieldByName("amount")->AsString + "\n";
		 s = s + "折扣优惠：" + dsjiaojieretail->FieldByName("zhehouyouhui")->AsString + "\n";
		 s=s+"\n________________________________\n\n";
		 s = s + "现金收款：" + dsjiaojieretail->FieldByName("RecCash")->AsString + "\n";
		 s = s + "储值卡收款：" + dsjiaojieretail->FieldByName("RecCardMoney")->AsString + "\n";
		 s = s + "账面收款：" + dsjiaojieretail->FieldByName("zhangmianshoukuan")->AsString + "\n";

		 ss->Text=s;

	// ss->SaveToFile("d:\\pddata.txt");
   //	delete ss;
   //向并口发送打印小票文件
//   String strTxtFile="C:\\pddata.txt" ;
//	if (!FileExists(strTxtFile)) return;

	/*int nLpt = FileOpen(TEXT("LPT1"), fmOpenWrite);
	  //	ShowMessage(IntToStr(nLpt));
	if (nLpt <= 0) return;

    TStringList *lst = new TStringList;
	try
	{
	 // lst->LoadFromFile(strTxtFile);
		lst->AddStrings(ss);

		AnsiString strAnsiLine;

        for (int i = 0; i < lst->Count; i++)
        {
            strAnsiLine = AnsiString(lst->Strings[i]) + AnsiString("\r\n");
			FileWrite(nLpt, strAnsiLine.c_str(), strAnsiLine.Length());
		}
    }
    __finally
    {
		delete lst;

		FileClose(nLpt);
	} */


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
			//ShowMessage("此通讯口已被占用或损坏!");
			MessageBox(0,"此通讯口已被占用或损坏！","零售" ,MB_ICONEXCLAMATION);
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






