//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <Printers.hpp>



#include "RetailNoteForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzChkLst"
#pragma link "RzDBEdit"
#pragma link "RzDBList"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzLstBox"
#pragma link "RzPanel"
#pragma link "RzLine"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RzButton"
#pragma link "RzDBChk"
#pragma link "RzRadChk"
#pragma link "MDIChild"
#pragma resource "*.dfm"
TfrmRetailNote *frmRetailNote;
//---------------------------------------------------------------------------
__fastcall TfrmRetailNote::TfrmRetailNote(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	m_module = MTSysadmin;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRetailNote::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (dsetRetailNote->State == dsEdit || dsetRetailNote->State == dsInsert)
	{
		dsetRetailNote->Post();
	}
	dsetRetailNote->Active = false;
	Action = caFree;
}
//--------------------------------------------------------------------------
void TfrmRetailNote::Init(TApplication* app, TADOConnection* cn)
{        //ShowMessage("wesdf");
	TfrmMDIChild::Init(app, cn);
		qryRetailNoteName->Connection = m_con;
		dsretail->Connection=m_con;
		dsPrint->Connection=m_con;
		con = cn ;
	 qryRetailNoteName->SQL->Add("select id,Name from SYS_StorageInfo where id = " + IntToStr(stgid) );
	 qryRetailNoteName->Open();
	 labstorage->Caption = "��ǰ�꣺" + qryRetailNoteName->FieldByName("Name")->AsString;
	 //-----------------------��ӡ����-----------------------------
	 dbedtWelcomeMessage->DataField="RetailNoteWelcomeMessage";
	 dbedtAddress->DataField="RetailNoteAddress";
	 dbedtTel->DataField="RetailNoteTel";
	 //dbcbbPort->DataField="RetailNotePort";
	 dbedtRemarks->DataField="RetailNoteRemarks";
	 chprintmayang->DataField = "printmayang";
	 chprintdiscount->DataField = "printdiscount";

	  //------------------------����������----------------------------
	 CHKBookName->DataField="ShowRetailNoteBookName";
	 CHKPrice->DataField="ShowRetailNotePricing";
	 CHKDiscount->DataField="ShowRetailNoteDiscount";
	 CHKtotalamount->DataField = "ShowRetailAmount";
	 CHKjine->DataField = "ShowRetaildisprice";
	 CHKCardrec->DataField = "ShowRetailCardRec";
	 CHKtotalhang->DataField = "ShowRetailtotalhang";
	 chkpostcard->DataField = "printposcard";
	 chkyouhuiquan->DataField = "printyouhuiquan";


	 qryRetailNoteName->Close();
	 dsetRetailNote->Connection = m_con;
	 dsetRetailNote->CommandText = "select * from SYS_StorageInfo where id = " + IntToStr(stgid) ;
	 dsetRetailNote->Active = true;
	 dbcbbPort->Text =  dsetRetailNote->FieldByName("retailprintcom")->AsAnsiString.Trim();
	 rgtype->ItemIndex = dsetRetailNote->FieldByName("retailxptype")->AsInteger ;
}
//--------------------------------------------------------------------------

void __fastcall TfrmRetailNote::btn1Click(TObject *Sender)
{
	//if (dsetRetailNote->State == dsEdit || dsetRetailNote->State == dsInsert)
	//{
		if (dbcbbPort->Text == "") {
			MessageBox(0,"��ѡ���ӡ�˿ڣ�","���۴�ӡ����" ,MB_ICONEXCLAMATION);
			return;
		}
		AnsiString sql;
		sql = "update SYS_StorageInfo set retailprintcom = '" + dbcbbPort->Text + "',retailxptype = " + IntToStr(rgtype->ItemIndex) + " where id = " + IntToStr(stgid);
		TADOQuery *aq = new  TADOQuery(this);
		aq->Connection = con;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
		try {
			dsetRetailNote->Post();
		} catch (...) {
		}
		MessageBox(0,"����ɹ���","���۴�ӡ����" ,MB_ICONEXCLAMATION);
	//}
}
//---------------------------------------------------------------------------


//-----------------СƱ��ӡ������СƱ��ID��һ��con����ʵ��дһ���ı��ļ�Ȼ����ı��ļ���������lpt1��ӡ------------------------------
void   TfrmRetailNote::print()
{

		AnsiString sql;

	   if (dsPrint->Active) {
		   dsPrint->Active=false;
	   }
	   sql = "select RetailNoteTitle,RetailNoteWelcomeMessage,RetailNoteAddress,RetailNoteTel,RetailNoteRemarks,ShowRetailNoteISBN,ShowRetailNoteBookName,ShowRetailNotePricing,ShowRetailNoteDiscount,ShowRetailCardRec,printdiscount,printmayang,ShowRetailtotalhang,ShowRetailAmount,ShowRetaildisprice,printposcard,printyouhuiquan from SYS_StorageInfo where id = " + IntToStr(stgid) ;
	   dsPrint->CommandText = sql;
	   dsPrint->Active = true;


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
	String s="\n  -----"+dsPrint->FieldByName("RetailNoteWelcomeMessage")->AsString+"-----\n" ;
		  s=s+"����:"+"2010052000005";
		  s=s+"\n����:"+ DateTimeToStr(Date()) +"\n����Ա:"+ "Admin"+"\n";
		   s=s+"--------------------------------\n";
		   if (dsPrint->FieldByName("ShowRetailNoteBookName")->AsString==1 ) {
				namelen = 16-3*n;
				s = s + "����    " + bookbk.SubString(1,(4-n)*5+2);
		   }
			if (dsPrint->FieldByName("ShowRetailNotePricing")->AsString==1 ) {
			 s=s+" ���� ";
		   }
		   if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1 ) {
			 s=s+"���� ";
		   }
			if (dsPrint->FieldByName("ShowRetailNoteDiscount")->AsString==1 ) {
			 s=s+"�ۿ� ";
		   }
		   if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1 ) {
			 s=s+"��� ";
		   }
		   s=s+"\n";
		 String stemp;

		 bool huanhang = false,first = true;
		   String bookname="��è����3000�ʿɰ���̫����(��ӡ����)";

					 bookname = bookname.TrimRight();
						//��������ÿ�����6����
						  huanhang = false;
						  first = true;
						  int len=bookname.Length();
						if (len>48) {
							stemp=bookname.SubString(1,16)+"\n"+bookname.SubString(17,16)+"\n"+bookname.SubString(33,16)+"\n"+bookname.SubString(49,16);
							stemp =  stemp + "\n";
							huanhang = true;
						  }
						  else	if (len>32) {
							stemp=bookname.SubString(1,16)+"\n"+bookname.SubString(17,16)+"\n"+bookname.SubString(33,16);

							stemp =  stemp + "\n";
							huanhang = true;
						  }
						   else	if (len>16) {
							stemp=bookname.SubString(1,16)+"\n"+bookname.SubString(17,16);
							stemp =  stemp + "\n";
							huanhang = true;
						  }
						   else	if (len>namelen) {
							stemp=bookname + "\n";
							huanhang = true;
						  }
						   else	if (len == namelen) {
							stemp=bookname + bookbk.SubString(1,2*((namelen-len))-2);
						  }
						  else	if (len < namelen) {
							stemp=bookname + bookbk.SubString(1,2*(namelen-len));
						  }
					 if (dsPrint->FieldByName("ShowRetailNoteBookName")->AsString==1 ) {
						s=s+stemp;
					}
					if (dsPrint->FieldByName("ShowRetailNotePricing")->AsString==1 ) {
						AnsiString Price;
						Price = "5.8";
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
						Amount = "1";
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
						discountprint = "100";
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
							s=s+ "                         " + "5.8";
						}
						else if (first) {
							s=s + "5.8";
						}
						else
						{
							s=s+ " " + "5.8";
						}
				   }

			if (dsPrint->FieldByName("ShowRetailtotalhang")->AsString==1) {
				s=s+"\n--------------------------------\n";
				s=s+ "�ϼ�:" ;
				if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1 && dsPrint->FieldByName("ShowRetailNotePricing")->AsString==1) {
					AnsiString TotalAmount;
					TotalAmount = "1";
					TotalAmount = bookbk.SubString(1,3-TotalAmount.Length()) + TotalAmount;
					s=s +bookbk.SubString(1,(6-n)*5+1) + TotalAmount;
				}
				else if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1) {
					AnsiString TotalAmount;
					TotalAmount = "1";
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
					s = s + "       " + "5.8";
				}
				else if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1 && dsPrint->FieldByName("ShowRetailAmount")->AsString==1) {
					s = s + " " + "5.8";
				}
				else if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1) {
					s = s + bookbk.SubString(1,(5-n)*5+1) + "5.8";
				}
				s = s + "\n";

			}
		   s=s+"\n--------------------------------\n";
		   float total= 6;

		   s=s+"��Ӧ��:"+"5.8";
		   if (dsPrint->FieldByName("printmayang")->AsString==1) {
				s = s + "      ԭ�ۺϼ�:5.8";
		   }
			s=s+"\n�տ�:"+FloatToStr(total);
			if (dsPrint->FieldByName("printdiscount")->AsString==1) {
				s = s + bookbk.SubString(1,10) + "�ۿ۽��:0.0";
			}
			if (dsPrint->FieldByName("ShowRetailCardRec")->AsString==1) {
				s=s+"\n���л�Ա������:0";
			}
			if (dsPrint->FieldByName("printposcard")->AsString==1) {
				s=s+"\n�������п�����:0";
			}
			if (dsPrint->FieldByName("printyouhuiquan")->AsString==1) {
				s=s+"\n�����Ż�ȯ����:0";
			}

		   s=s+"\n����:"+ "0.2" +"\n";
		   s=s+"--------------------------------\n";
			s=s+"��ַ:"+dsPrint->FieldByName("RetailNoteAddress")->AsString+"\n";
			s=s+"�绰:"+dsPrint->FieldByName("RetailNoteTel")->AsString+"\n";
		   s=s+"��ע:"+dsPrint->FieldByName("RetailNoteRemarks")->AsString+"\n\n\n\n\n";

	ss->Text=s;

	// ss->SaveToFile("d:\\pddata.txt");

	TStringList *lst = new TStringList;

	DCB dd;
	DWORD dwWrited;
	HANDLE m_hComm;
	LPCTSTR  strCom = dbcbbPort->Text.t_str() ;
	COMMTIMEOUTS comtimeout;

	int nLpt  ;
	try
	{

		m_hComm=CreateFile(TEXT(strCom),GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if (m_hComm==INVALID_HANDLE_VALUE)
		{
			MessageBox(0,"��ͨѶ���ѱ�ռ�û��𻵣�","���۴�ӡ����" ,MB_ICONEXCLAMATION);
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

   /*	String   LogPath,nowtime;
   int  iFileHandle;
   Sysutils::TBytes ByteOrderMark = TEncoding::Unicode->GetPreamble();
   LogPath=ExtractFilePath(Application->ExeName)+"CDRFTP.Log";
   if(FileExists(LogPath))
   {
      iFileHandle=FileOpen(LogPath,fmOpenWrite);
   }
   else
   {
      iFileHandle=FileCreate(LogPath);
   }
   FileSeek(iFileHandle,0,2);
   nowtime = Now().FormatString("YYYY-MM-DD HH:mm:SS");
   //FileWrite( iFileHandle,&UnicodeBytes[0], UnicodeBytes.Length );
   String WriteStr=nowtime+" "+"111"+"\r\n" ;
   FileWrite(iFileHandle,WriteStr.c_str(),WriteStr.Length());
   FileClose(iFileHandle);*/



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
	}      */
}
//---------------------------------------------------------------------------
void __fastcall TfrmRetailNote::btn2Cick(TObject *Sender)
{
     print();
	 //ShowMessage("ϵͳ���ڡ�d:\\pddata.txt�������ĵ���ע��鿴��ʽ�� ");
}

void __fastcall TfrmRetailNote::btn3Click(TObject *Sender)
{
          Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailNote::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
				if (Shift.Contains(ssCtrl)&&Key==90) {   //Z
			this->btn2->Click();

		}
				if (Shift.Contains(ssCtrl)&&Key==83) {   //S
			this->btn1->Click() ;

		}
				if (Key==0x1B) {   //esc
				this->btn3->Click();

		}

}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailNote::Button1Click(TObject *Sender)
{
	int nLpt = FileOpen(TEXT("LPT1"), fmOpenWrite);
	  //	ShowMessage(IntToStr(nLpt));
	if (nLpt <= 0) return;
	try
	{
		String strAnsiLine;
		char p[5]= {27,112,0,60,255};
		FileWrite(nLpt, p , 5);
	}
	__finally
	{
		FileClose(nLpt);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailNote::Button2Click(TObject *Sender)
{
	int nLpt = FileOpen(TEXT("LPT1"), fmOpenWrite);
	  //	ShowMessage(IntToStr(nLpt));
	if (nLpt <= 0) return;
	try
	{
		String strAnsiLine;
		char p[5]= {27,112,1,60,255};
		FileWrite(nLpt, p , 5);
	}
	__finally
	{
		FileClose(nLpt);
	}
}
//---------------------------------------------------------------------------

