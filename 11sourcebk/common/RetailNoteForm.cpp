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
#pragma resource "*.dfm"
TfrmRetailNote *frmRetailNote;
//---------------------------------------------------------------------------
__fastcall TfrmRetailNote::TfrmRetailNote(TComponent* Owner)
	: TForm(Owner)
{
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
void TfrmRetailNote::Init(TADOConnection* con)
{        //ShowMessage("wesdf");
		con1=con;
		qryRetailNoteName->Connection = con;
		dsretail->Connection=con;
		dsPrint->Connection=con;
	 qryRetailNoteName->SQL->Add("select Name from SYS_StorageInfo");
	 qryRetailNoteName->Open();
	 //-----------------------打印设置-----------------------------
	 dbedtTitle->DataField="RetailNoteTitle";
	 dbedtWelcomeMessage->DataField="RetailNoteWelcomeMessage";
	 dbedtAddress->DataField="RetailNoteAddress";
	 dbedtTel->DataField="RetailNoteTel";
	 dbcbbPort->DataField="RetailNotePort";
	 dbedtRemarks->DataField="RetailNoteRemarks";

	  //------------------------单据列设置----------------------------
	 CHKISBN->DataField="ShowRetailNoteISBN";
	 CHKBookName->DataField="ShowRetailNoteBookName";
	 CHKPrice->DataField="ShowRetailNotePricing";
	 CHKDiscount->DataField="ShowRetailNoteDiscount";

	  qryRetailNoteName->First();

	 while (!qryRetailNoteName->Eof)
	 {
		LBRetailNote->Items->Add(qryRetailNoteName->FieldByName("Name")->AsString);
		 //LBRetailNote->Items->Add(qryRetailNoteName->FieldByName("ID")->AsString) ;
		qryRetailNoteName->Next();
	 }

	 qryRetailNoteName->Close();
	 dsetRetailNote->Connection = con;
	 dsetRetailNote->CommandText = "select * from SYS_StorageInfo";
	 dsetRetailNote->Active = true;
}

void __fastcall TfrmRetailNote::LBRetailNoteClick(TObject *Sender)
{
//dsetStorageNote->RecNo = ListBox1->ItemIndex + 1;
	dsetRetailNote->RecNo=LBRetailNote->ItemIndex+1;
}
//---------------------------------------------------------------------------



void __fastcall TfrmRetailNote::LBRetailNoteDblClick(TObject *Sender)
{
		dsetRetailNote->RecNo=LBRetailNote->ItemIndex+1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailNote::LBRetailNoteKeyPress(TObject *Sender, wchar_t &Key)

{
	dsetRetailNote->RecNo=LBRetailNote->ItemIndex+1;
}
//---------------------------------------------------------------------------





void __fastcall TfrmRetailNote::btn1Click(TObject *Sender)
{
		if (dsetRetailNote->State == dsEdit || dsetRetailNote->State == dsInsert)
	{
		dsetRetailNote->Post();
	}

}
//---------------------------------------------------------------------------


//-----------------小票打印，传入小票单ID和一个con连接实现写一个文本文件然后把文本文件送往并口lpt1打印------------------------------
void   TfrmRetailNote::print(String ID,TADOConnection* con)
{


		 TADODataSet* dsPrint=new TADODataSet(NULL);
		 TADODataSet* dsretail=new TADODataSet(NULL);
		 dsretail->Connection=con;
		dsPrint->Connection=con;

	   if (dsPrint->Active) {
		   dsPrint->Active=false;
	   }
	   dsPrint->CommandText="select RetailNoteTitle,RetailNoteWelcomeMessage,RetailNoteAddress,RetailNoteTel,RetailNoteRemarks,ShowRetailNoteISBN,ShowRetailNoteBookName,ShowRetailNotePricing,ShowRetailNoteDiscount from SYS_StorageInfo";
		 dsPrint->Active=true;
		 if (dsretail->Active) {
		   dsretail->Active=false;
	   }
	   dsretail->CommandText="select len(BS_BookCatalog.Name) as lenthName,len(BS_BookCatalog.Name) as lenth,SYS_UserInfo.Name as operatorName,RecCash+RecCardMoney-TotalDiscountedPrice as backMoney,TotalDiscountedPrice,RecCash,RecCardMoney,BS_BookCatalog.Name as bookName,BS_BookCatalog.ISBN as ISBN,BS_BookCatalog.Price as price ,RetailNtCode,HdTime as Time ,BS_RetailNote.Amount as Amount,DiscountedPrice ,Discount from BS_RetailNote left join BS_RetailNoteHeader on  RetailNtHeaderID=BS_RetailNoteHeader.id left join STK_BookInfo on BkInfoID=STK_BookInfo.id left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join SYS_UserInfo on SYS_UserInfo.id=OperatorID where BS_RetailNoteHeader.ID="+ID+" order by RetailNtCode";
		 dsretail->Active=true;
		 //取得书名 字段最大长度
	   int lenth=0;
		   dsretail->First();
		 while (!dsretail->Eof){
			  if (dsretail->FieldByName("lenthName")->AsInteger>lenth) {

				   lenth=dsretail->FieldByName("lenthName")->AsInteger;
					// ShowMessage(IntToStr(lenth));
			  }
			dsretail->Next();
		 }


		  lenth=2*lenth-3;
    TStrings* ss = new TStringList();
		 dsPrint->First();
	String s="     -----"+dsPrint->FieldByName("RetailNoteWelcomeMessage")->AsString+"-----\n" ;
		  s=s+"    "+dsPrint->FieldByName("RetailNoteTitle")->AsString+"书店 \n\n";
		  s=s+"单号："+dsretail->FieldByName("RetailNtCode")->AsString;
		  s=s+"\n日期："+dsretail->FieldByName("Time")->AsString+"\n收银员："+dsretail->FieldByName("operatorName")->AsString+"\n";
		   s=s+"________________________________\n\n";
		   if (dsPrint->FieldByName("ShowRetailNoteBookName")->AsString==1 ) {
			 s=s+"书名         ";
		   }
			if (dsPrint->FieldByName("ShowRetailNotePricing")->AsString==1 ) {
			 s=s+"定价 ";
		   }
		   s=s+"数量 ";
			if (dsPrint->FieldByName("ShowRetailNoteDiscount")->AsString==1 ) {
			 s=s+"折扣 ";
		   }
		   s=s+"金额 ";
		   if (dsPrint->FieldByName("ShowRetailNoteISBN")->AsString==1 ) {
			 s=s+"ISBN";
		   }
		   s=s+"\n";
		  dsretail->First();
		 String stemp;
		  while (!dsretail->Eof)
			{         String bookname=dsretail->FieldByName("bookName")->AsString;
                    	//控制书名每行输出6个字
						  int len=bookname.Length();
									if (len>48) {
							stemp=bookname.SubString(1,6)+"\n"+bookname.SubString(7,6)+"\n"+bookname.SubString(13,6)+"\n"+bookname.SubString(19,6)+"\n"+bookname.SubString(25,6)+"\n"+bookname.SubString(31,6)+"\n"+bookname.SubString(37,6)+"\n"+bookname.SubString(43,6)+"\n"+bookname.SubString(49,len-48);
						  }
							  else	if (len>42) {
							stemp=bookname.SubString(1,6)+"\n"+bookname.SubString(7,6)+"\n"+bookname.SubString(13,6)+"\n"+bookname.SubString(19,6)+"\n"+bookname.SubString(25,6)+"\n"+bookname.SubString(31,6)+"\n"+bookname.SubString(37,6)+"\n"+bookname.SubString(43,len-42);
						  }
						   else	if (len>36) {
							stemp=bookname.SubString(1,6)+"\n"+bookname.SubString(7,6)+"\n"+bookname.SubString(13,6)+"\n"+bookname.SubString(19,6)+"\n"+bookname.SubString(25,6)+"\n"+bookname.SubString(31,6)+"\n"+bookname.SubString(37,len-36);
						  }
						   else	if (len>30) {
							stemp=bookname.SubString(1,6)+"\n"+bookname.SubString(7,6)+"\n"+bookname.SubString(13,6)+"\n"+bookname.SubString(19,6)+"\n"+bookname.SubString(25,6)+"\n"+bookname.SubString(31,len-30);
						  }
						   else	if (len>24) {
							stemp=bookname.SubString(1,6)+"\n"+bookname.SubString(7,6)+"\n"+bookname.SubString(13,6)+"\n"+bookname.SubString(19,6)+"\n"+bookname.SubString(25,len-24);
						  }
						 else  if (len>18) {
							stemp=bookname.SubString(1,6)+"\n"+bookname.SubString(7,6)+"\n"+bookname.SubString(13,6)+"\n"+bookname.SubString(19,len-18);
						  }
						 else if (len>12) {
							stemp=bookname.SubString(1,6)+"\n"+bookname.SubString(7,6)+"\n"+bookname.SubString(13,len-12);
						  }
						else if (len>6) {
							stemp=bookname.SubString(1,6)+"\n"+bookname.SubString(7,len-6);
						  }
							else if (len<=6) {
							stemp=bookname;
						  }
					 if (dsPrint->FieldByName("ShowRetailNoteBookName")->AsString==1 ) {
					 s=s+stemp;
					 len=len%6 ;
					 if (len) {
                        len=6-len;
					 }
					 for ( ;len >0;len--) {
						  s=s+"  ";
					 }
					 s=s+" ";
						 }
					if (dsPrint->FieldByName("ShowRetailNotePricing")->AsString==1 ) {
					 s=s+dsretail->FieldByName("price")->AsString+" ";
				   }
				   s=s+dsretail->FieldByName("Amount")->AsString+"   ";
					if (dsPrint->FieldByName("ShowRetailNoteDiscount")->AsString==1 ) {
					 s=s+dsretail->FieldByName("Discount")->AsString+"%  ";
				   }
				   s=s+dsretail->FieldByName("DiscountedPrice")->AsString+"   ";
				   if (dsPrint->FieldByName("ShowRetailNoteISBN")->AsString==1 ) {
					 s=s+dsretail->FieldByName("ISBN")->AsString;
				   }
					  s=s+"\n";
					  dsretail->Next();
			}
			dsretail->First();
		   s=s+"\n________________________________\n\n";
		   float total=dsretail->FieldByName("RecCash")->AsFloat+dsretail->FieldByName("RecCardMoney")->AsFloat;

		   s=s+"总应收:"+dsretail->FieldByName("TotalDiscountedPrice")->AsString+"\n";
			s=s+"收款:"+FloatToStr(total);
		   s=s+"\n其中刷卡消费:"+dsretail->FieldByName("RecCardMoney")->AsString+"\n";
		   s=s+"找零:"+dsretail->FieldByName("backMoney")->AsString+"\n";
		   s=s+"\n________________________________\n";
			s=s+"地址:"+dsPrint->FieldByName("RetailNoteAddress")->AsString+"\n";
			s=s+"电话:"+dsPrint->FieldByName("RetailNoteTel")->AsString+"\n";
		   s=s+"备注:"+dsPrint->FieldByName("RetailNoteRemarks")->AsString+"\n\n\n\n\n";

ss->Text=s;

 ss->SaveToFile("C:\\pddata.txt");
delete ss;
   //向并口发送打印小票文件
   String strTxtFile="C:\\pddata.txt" ;
	if (!FileExists(strTxtFile)) return;

	int nLpt = FileOpen(TEXT("LPT1"), fmOpenWrite);
	  //	ShowMessage(IntToStr(nLpt));
	if (nLpt <= 0) return;

    TStringList *lst = new TStringList;
    try
	{
		lst->LoadFromFile(strTxtFile);

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
	}

}
void __fastcall TfrmRetailNote::btn2Click(TObject *Sender)
{

	 this->print("17",this->con1);
}
//---------------------------------------------------------------------------

