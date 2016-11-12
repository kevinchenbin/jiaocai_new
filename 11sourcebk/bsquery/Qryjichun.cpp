//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Qryjichun.h"
#include "DBGridEhImpExp.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBCmbo"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma link "RzRadChk"
#pragma link "RzTabs"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
Tfrmjichun *frmjichun;
//---------------------------------------------------------------------------
__fastcall Tfrmjichun::Tfrmjichun(TComponent* Owner)
	:TfrmMDIChild(Owner)
{


}
//---------------------------------------------------------------------------void Tfrmjichun::Query()
void Tfrmjichun::Init(LandInfo* li)
{
    	TfrmMDIChild::Init(li);
        fcon=li->con;
        fstgid=li->storageID;
        aqandan->Connection =fcon;
        aqdetail->Connection= fcon;
        dtedtStart->Date = Now();
        dtedtEnd->Date = Now();
        readyDate();
}
void Tfrmjichun::readyDate()
{


        //��Ӧ��
        	AnsiString sql;
	sql = "select ID,Name from CUST_CustomerInfo where type = 1";
TADOQuery *aq1=new TADOQuery(Application);
aq1->Connection = fcon;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	while (!aq1->Eof )
	{
		cbsupplier->AddItem(aq1->FieldByName("Name")->AsAnsiString ,(TObject*)aq1->FieldByName("ID")->AsInteger );
		aq1->Next();
	}
	aq1->First();
	cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq1->FieldByName("ID")->AsInteger );

      	sql = "select ID,Name from sys_user where stgid = " + IntToStr(fstgid) ;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	while (!aq1->Eof)
	{
		cbstaff->AddItem(aq1->FieldByName("Name")->AsAnsiString ,(TObject*)aq1->FieldByName("ID")->AsInteger );
		aq1->Next();
	}
	aq1->First();
	cbstaff->ItemIndex = cbstaff->Items->IndexOfObject((TObject*)aq1->FieldByName("ID")->AsInteger );

        sql = "select id,name from dbo.SYS_StorageInfo ";
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	while (!aq1->Eof)
	{
		cbstg->AddItem(aq1->FieldByName("Name")->AsAnsiString ,(TObject*)aq1->FieldByName("ID")->AsInteger );
		aq1->Next();
	}
	aq1->First();
	cbstg->ItemIndex = cbstg->Items->IndexOfObject((TObject*)aq1->FieldByName("ID")->AsInteger );

       //���
          sql = "select id,abbreviatedname from dbo.BS_PressInfo ";
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	while (!aq1->Eof)
	{
		cbpress->AddItem(aq1->FieldByName("abbreviatedname")->AsAnsiString ,(TObject*)aq1->FieldByName("ID")->AsInteger );
		aq1->Next();
	}
	aq1->First();
	cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aq1->FieldByName("ID")->AsInteger );



       delete aq1;



}
void Tfrmjichun::Query()
{
     AnsiString sql;
     sql  = "select danhaostr, convert(varchar(10),jzdatetime,120) as jzdatetime,totalamount,totaldis,totalfix,s.name,f.name as stgname,a.bk "
            " from STK_Bookinfo_jizhuan_head a left join sys_user s on a.userid = s.id "
            " left join SYS_StorageInfo f on a.stgid = f.id where 1=1 ";
     if (chckbxStartTime->Checked) {
        sql = sql + " and datediff(day,'"+DateToStr(dtedtStart->Date)+"',jzdatetime) >=0";
     }
     if (chckbxEndTime->Checked) {
         sql = sql + " and datediff(day,'"+DateToStr(dtedtEnd->Date)+"',jzdatetime) <=0";
     }
     if (chckbxStorage->Checked&&cbstg->Text !="") {
         sql = sql +" and stgid="+IntToStr(int(cbstg->Items->Objects[cbstg->ItemIndex]));
     }
     if (chstaff->Checked&&cbstaff->Text !="") {
          sql = sql +"  and userid = "+IntToStr(int(cbstaff->Items->Objects[cbstaff->ItemIndex]));;
     }

     aqandan->Close();
     aqandan->SQL->Clear();
     aqandan->SQL->Add(sql);
     aqandan->Open();

}
 void Tfrmjichun::Query1()
{
     AnsiString sql;
     sql  = "select rank() over(order by D.id) as xuhao,A.id as bkcatalogid,H.danhaostr,convert(varchar(10),H.jzdatetime,120) as jzdatetime,A.ISBN,A.price,A.name as bookname,A.userdefcode,A.author,A.presscount,convert(varchar(10),A.pressdate,120) as pressdate,A.huojiangstate,A.BookWords,"
			" B.AbbreviatedName,B.id as pressid,C.Name as typename,D.id ,D.stgid,D.amount,D.Cbprice,D.amount*A.price as mayang,D.Cbprice*D.amount as shiyang,D.bkharmnum,D.bkdamnum,"
			" E.name as stackname,F.name as suppliername,G.name as storagename,D.tcbprice as tuihuochenben "
			" from BS_BookCatalog A left join BS_PressInfo B on A.pressid = B.id"
			" left join BS_BookType C on A.smallBookTypeID = C.id"
			" left join stk_bookinfo_jizhuan D on A.id = D.BkcatalogID "
			" left join STK_BookstackInfo E on D.BkstackID = E.id "
		       "  left join CUST_CustomerInfo F on D.Supplierid = F.id"
		       "  left join SYS_StorageInfo G on D.stgid = G.id "
             "  join dbo.STK_Bookinfo_jizhuan_head H on D.jzheadid=H.id "
             "  where 1=1 ";
     if (chckbxStartTime->Checked) {
        sql = sql + " and datediff(day,'"+DateToStr(dtedtStart->Date)+"',H.jzdatetime) >=0";
     }
     if (chckbxEndTime->Checked) {
         sql = sql + " and datediff(day,'"+DateToStr(dtedtEnd->Date)+"',H.jzdatetime) <=0";
     }
     if (chckbxStorage->Checked&&cbstg->Text !="") {
         sql = sql +" and H.stgid="+IntToStr(int(cbstg->Items->Objects[cbstg->ItemIndex]));
     }
     if (chstaff->Checked&&cbstaff->Text !="") {
          sql = sql +"  and H.userid = "+IntToStr(int(cbstaff->Items->Objects[cbstaff->ItemIndex]));;
     }

          //����
     if(ckdanhao->Checked&&editdanhao->Text!="")
     {
         sql = sql +" and H.danhao="+editdanhao->Text.Trim();
     }

     //����
     if (chckbxBookName->Checked&&edtBookName->Text!="") {
         sql = sql +" and  A.name like '%"+edtBookName->Text.Trim()+"%'";
     }
     //���

     if (edtISBN->Text !=""&&chckbxISBN->Checked) {
          sql = sql +" and  A.ISBN like '%"+edtISBN->Text+"%'";
     }
     //
     if (chckbxUserDefNum->Checked&&edtUserDefNum->Text!="") {
         sql = sql +" and A.userdefcode like '%"+edtUserDefNum->Text.Trim()+"%'";
     }
    if (chckbxPress->Checked&&cbpress->Text!="") {
          sql = sql + " and pressid="+IntToStr(int(cbpress->Items->Objects[cbpress->ItemIndex]));

    }
     if (chckbx1->Checked&&cbsupplier->Text !="") {
         sql = sql + " and D.supplierid ="+ IntToStr(int(cbsupplier->Items->Objects[cbsupplier->ItemIndex]));
     }

     if (chckbxRemarks->Checked&&edtRemarks->Text!="") {
        sql = sql + " and H.bk = '"+edtRemarks->Text+"'";
     }

     aqdetail->Close();
     aqdetail->SQL->Clear();
     aqdetail->SQL->Add(sql);
     aqdetail->Open();

}
//---------------------------------------------------------------------------
void __fastcall Tfrmjichun::tlbtnQryClick(TObject *Sender)
{  Screen->Cursor = crHourGlass;
  if (pagecontrol->ActivePageIndex==0) {
        Query();
  }else if (pagecontrol->ActivePageIndex==1 ) {
           Query1();
        }
        Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmjichun::BtnAlignBottomClick(TObject *Sender)

{
WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjichun::tlbtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjichun::cbpressChange(TObject *Sender)
{
if (cbpress->Text !="") {
  chckbxPress->Checked=true;
}

}
//---------------------------------------------------------------------------

void __fastcall Tfrmjichun::cbsupplierChange(TObject *Sender)

{
  if (cbsupplier->Text !="") {
        chckbx1->Checked = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjichun::cbstaffChange(TObject *Sender)
{
  if (cbstaff->Text !="")
  {


  chstaff->Checked = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjichun::edsuplierKeyPress(TObject *Sender,
          wchar_t &Key)
{
  AnsiString sql = "";
  if (Key== VK_RETURN) {
    	sql = "select ID,Name from CUST_CustomerInfo where type = 1 and name like '%"+edsuplier->Text+"%'";
TADOQuery *aq1=new TADOQuery(Application);
aq1->Connection = fcon;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
        cbsupplier->Clear();
	while (!aq1->Eof )
	{
		cbsupplier->AddItem(aq1->FieldByName("Name")->AsAnsiString ,(TObject*)aq1->FieldByName("ID")->AsInteger );
		aq1->Next();
	}
	aq1->First();
	cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq1->FieldByName("ID")->AsInteger );
       delete aq1;
  }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmjichun::edtPressKeyPress(TObject *Sender,
          wchar_t &Key)
{
if (Key== VK_RETURN) {
        TADOQuery *aq1=new TADOQuery(Application);
        aq1->Connection = fcon;
       AnsiString sql = "select id,abbreviatedname from dbo.BS_PressInfo where abbreviatedname like '%"+cbpress->Text+"%'";
        aq1->Close();
        aq1->SQL->Clear();
        aq1->SQL->Add(sql);
        aq1->Open();
        cbpress->Clear();
        while (!aq1->Eof)
        {
            cbpress->AddItem(aq1->FieldByName("abbreviatedname")->AsAnsiString ,(TObject*)aq1->FieldByName("ID")->AsInteger );
            aq1->Next();
        }
        aq1->First();
        cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aq1->FieldByName("ID")->AsInteger );
        delete aq1;

}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjichun::edtISBNChange(TObject *Sender)
{
  if (edtISBN->Text !="") {
     chckbxISBN->Checked=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjichun::edtBookNameChange(TObject *Sender)

{
if (edtBookName->Text !="") {
   chckbxBookName->Checked=true;
}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjichun::edtUserDefNumChange(TObject *Sender)

{
if (edtUserDefNum->Text !="") {
     chckbxUserDefNum->Checked=true;
}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjichun::editdanhaoChange(TObject *Sender)

{
  if (editdanhao->Text !="") {
      ckdanhao->Checked=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjichun::tlbtnExportClick(TObject *Sender)

{

    DbgridToExcel(dbgrid2);


/*
if (savedialog->Execute()) {
     if (savedialog->FileName!="") {
       TDBGridEhExportClass ExpClass;
        ExpClass=__classid(TDBGridEhExportAsHTML);


      Screen->Cursor = crHourGlass;
      try
      {

  if (pagecontrol->ActivePageIndex==0) {
  dbgrid1->Selection->SelectAll();
       SaveDBGridEhToExportFile(ExpClass,dbgrid1,savedialog->FileName,False);
   dbgrid1->Selection->Clear();
  }else if (pagecontrol->ActivePageIndex==1 ) {
  //dbgrid2->Selection->SelectAll();
        SaveDBGridEhToExportFile(ExpClass,dbgrid2,savedialog->FileName,true);
      // dbgrid2->Selection->Clear();

        }
        Screen->Cursor = crDefault;
         AnsiString sMsg="�ļ������ɹ���\r\n\r\n"+savedialog->FileName;
    MessageBox(Handle,sMsg.c_str(),"�����ļ�",MB_OK);

  } catch(...)
  {
    MessageBox(Handle,"�����ļ�ʧ��","�����ļ�",MB_OK);

  }
     }
}     */
//SaveDBGridEhToExportFile(
}
void Tfrmjichun::DbgridToExcel(TDBGridEh* dbg)
{
        AnsiString filename;
	int k = dbg->DataSource ->DataSet ->RecordCount  ;
	if(k == 0)
	{
		ShowMessage("û������");
		return ;
	}
        if (savedialog->Execute()) {
             if (savedialog->FileName!="") {
                     try
                     {
                      filename =savedialog->FileName;
                        Screen->Cursor = crHourGlass;
                        Variant     v,vSheet;
                        v   =Variant::CreateObject("Excel.Application");
                        v.OlePropertySet("Visible",false);
                        v.OlePropertyGet("WorkBooks").OleFunction("Add");
                        vSheet = v.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);
                        for(int q=0;q<dbg->FieldCount ;++q)
                        {
                        if (dbg->Columns ->Items [q]->Visible ) {
                          vSheet.OlePropertyGet("Cells",1,(q+1)).OlePropertySet("Value",dbg->Columns ->Items [q]->Title ->Caption .t_str() );
                        }

                         }
                        int t2 = dbg->DataSource ->DataSet ->RecordCount ;

                        dbg->DataSource ->DataSet ->First();
                        dbg->DataSource->DataSet->DisableControls();
                        for(int   i=2;i< t2+1 ;i++)
                        {
                                for(int j=1;j<dbg->Columns ->Count+1  ;j++)
                                {
                                      if (dbg->Columns ->Items [j-1]->Visible==true ) {


                                        vSheet.OlePropertyGet("Cells",i,j).OlePropertySet("Value",dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString .c_str() );  // AsString .c_str()
                                      }
                                }
                                dbg->DataSource ->DataSet ->Next() ;
                        }
                         dbg->DataSource->DataSet->EnableControls();
                        vSheet.OlePropertyGet("Range","D4").OlePropertySet("NumberFormatLocal","@");
                        v.OlePropertyGet("ActiveWorkbook")
                        .OleFunction("SaveAs", filename.c_str());

                        v.OleFunction("Quit");

                        vSheet = Unassigned;
                        v = Unassigned;
                        AnsiString sMsg="�ļ������ɹ���\r\n\r\n"+filename;
                        MessageBox(Handle,sMsg.c_str(),"�����ļ�",MB_OK);
                        }catch(...)
                        {


                         MessageBox(Handle,"�����ļ�ʧ��","�����ļ�",MB_OK);

                        }

                         Screen->Cursor = crDefault;
                }



        }


}
//---------------------------------------------------------------------------

void __fastcall Tfrmjichun::dbgrid2TitleClick(TColumnEh *Column)

{
	if (aqdetail->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqdetail->Sort == "") {
		aqdetail->Sort =  Column->FieldName + " ASC";
	}
	else if (aqdetail->Sort == qusort) {
		aqdetail->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqdetail->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------
