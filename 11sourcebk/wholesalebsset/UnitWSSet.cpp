//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitWSSet.h"
#include "UnitSelectClient.h"
#include "checkselbook.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmwsset *frmwsset;
//---------------------------------------------------------------------------
__fastcall Tfrmwsset::Tfrmwsset(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
   fcon = cn;
   type = 1;
   aq->Connection = fcon;
   m_storageID=stgid;
}
void Tfrmwsset::DoInvokClient(TEdit *clientName)
{

	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",m_storageID);
	if (mrOk == frm->ShowModal() ) {
	   clientID  = frm->GetSelectID();
	   ClientName = frm->GetSelect();
	   clientName->Text = voidClientName();
	}
	delete frm;


}
void Tfrmwsset::Enable(int type)
{
  String sql;
  TADOQuery *aqexe = new TADOQuery(NULL);
  aqexe->Connection = fcon;
  TADOQuery *aquery = new TADOQuery(NULL);
  aquery->Connection = fcon;
  switch (type) {
	 case 1:               //�ͻ����ö������
		if (editclientname->Text == "") {
        	MessageBoxA(0,"��ѡ��ͻ�!","��������",MB_ICONASTERISK);
			return;
		}
		sql = "select * from BS_Wsaleset where SetType = 1 and ClientID = " + IntToStr(clientID);
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->RecordCount > 0) {
			//�޸�
			sql = "update BS_Wsaleset set proCredit = " + editalarmcredit->Text + ",LocalDeliveryCredit = " + editlockcredit->Text + ",Creditstartdate = '" + DateToStr(cridetbegin->Date) + "',Creditenddate = '" + DateToStr(creditend->Date) + "'";
			if (cbbalance->Checked ) {
				sql = sql + ",Containclientblance = 1";
			}
			else
			{
				sql = sql + ",Containclientblance = 0";
			}
			sql = sql + " where id = " + aquery->FieldByName("ID")->AsString ;
			aqexe->Close();
			aqexe->SQL->Clear();
			aqexe->SQL->Add(sql);
			aqexe->ExecSQL();
		}
		else
		{
			//����
			sql = "insert into BS_Wsaleset(SetType,ClientID,proCredit,LocalDeliveryCredit,Creditstartdate,Creditenddate,Containclientblance) values(1," + IntToStr(clientID) + "," + editalarmcredit->Text +
				  "," + editlockcredit->Text + ",'" + DateToStr(cridetbegin->Date) + "','" + DateToStr(creditend->Date) + "'";
			if (cbbalance->Checked ) {
				sql = sql + ",1)";
			}
			else
			{
				sql = sql + ",0)";
			}
			aqexe->Close();
			aqexe->SQL->Clear();
			aqexe->SQL->Add(sql);
			aqexe->ExecSQL();
		}
	 break;
	 case 2:                         //�ؿ�������
		if (backclientname->Text == "") {
			MessageBoxA(0,"��ѡ��ͻ�!","��������",MB_ICONASTERISK);
			return;
		}
		sql = "select * from BS_Wsaleset where SetType = 2 and ClientID = " + IntToStr(clientID);
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->RecordCount > 0) {
			//�޸�
			sql = "update BS_Wsaleset set monthbackrate = " + monthbakarate->Text + ",yearbackrate = " + yearbackrate->Text + ",probackrate = " + probackrate->Text + ",localDeliverybackrate = " + localdeliverybackrate->Text + ",backratestartdate = '" + DateToStr(dtpbackbegin->Date) + "',backrateenddate = '" + DateToStr(dtpbackend->Date) + "'";
			sql = sql + " where id = " + aquery->FieldByName("ID")->AsString ;
			aqexe->Close();
			aqexe->SQL->Clear();
			aqexe->SQL->Add(sql);
			aqexe->ExecSQL();
		}
		else
		{
			//����
			sql = "insert into BS_Wsaleset(SetType,ClientID,monthbackrate,yearbackrate,probackrate,localDeliverybackrate,backratestartdate,backrateenddate) values(2," + IntToStr(clientID) + "," + monthbakarate->Text +
				  "," + yearbackrate->Text + "," + probackrate->Text + ","+ localdeliverybackrate->Text + ",'" + DateToStr(dtpbackbegin->Date) + "','" + DateToStr(dtpbackend->Date) + "')";
			aqexe->Close();
			aqexe->SQL->Clear();
			aqexe->SQL->Add(sql);
			aqexe->ExecSQL();
		}
	 break;
	 case 3:                      //�˻��ʰ��ͻ�����
		if (returnclientname->Text == "") {
			MessageBoxA(0,"��ѡ��ͻ�!","��������",MB_ICONASTERISK);
			return;
		}
     	sql = "select * from BS_Wsaleset where SetType = 3 and ClientID = " + IntToStr(clientID);
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->RecordCount > 0) {
			//�޸�
			sql = "update BS_Wsaleset set proreturnrate = " + proreturnrate->Text + ",localreturnrate = " + localreturnrate->Text + ",returnratestartdate = '" + DateToStr(returnbegin->Date) + "',returnrateenddate = '" + DateToStr(returnend->Date) + "'";
			sql = sql + " where id = " + aquery->FieldByName("ID")->AsString ;
			aqexe->Close();
			aqexe->SQL->Clear();
			aqexe->SQL->Add(sql);
			aqexe->ExecSQL();
		}
		else
		{
			//����
			sql = "insert into BS_Wsaleset(SetType,ClientID,proreturnrate,localreturnrate,returnratestartdate,returnrateenddate) values(3," + IntToStr(clientID) + "," + proreturnrate->Text +
				  "," + localreturnrate->Text + ",'" + DateToStr(returnbegin->Date) + "','" + DateToStr(returnend->Date) + "')";
			aqexe->Close();
			aqexe->SQL->Clear();
			aqexe->SQL->Add(sql);
			aqexe->ExecSQL();
		}
	 break;
	 case 4:                       //�˻��ʰ��������
		if (cbbooktype->Text == "") {
			MessageBoxA(0,"��ѡ��ͼ�����!","��������",MB_ICONASTERISK);
			return;
		}
		sql = "select * from BS_Wsaleset where SetType = 4 and BookType = " + IntToStr(BookType);
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->RecordCount > 0) {
			//�޸�
			sql = "update BS_Wsaleset set protypereturnrate = " + typereturnrate->Text + ",localtypereturnrate = " + localtypereturnrate->Text + ",typereturnstaetdate = '" + DateToStr(typestart->Date) + "',typereturnenddate = '" + DateToStr(typeend->Date) + "'";
			sql = sql + " where id = " + aquery->FieldByName("ID")->AsString ;
			aqexe->Close();
			aqexe->SQL->Clear();
			aqexe->SQL->Add(sql);
			aqexe->ExecSQL();
		}
		else
		{
			//����
			sql = "insert into BS_Wsaleset(SetType,BookType,protypereturnrate,localtypereturnrate,typereturnstaetdate,typereturnenddate) values(4," + IntToStr(BookType) + "," + typereturnrate->Text +
				  "," + localtypereturnrate->Text + ",'" + DateToStr(typestart->Date) + "','" + DateToStr(typeend->Date) + "')";
			aqexe->Close();
			aqexe->SQL->Clear();
			aqexe->SQL->Add(sql);
			aqexe->ExecSQL();
		}
	 break;
	 case 5:                        //�˻��ʰ���Ʒ
		if (edbookname->Text == "") {
			MessageBoxA(0,"��ѡ����Ŀ!","��������",MB_ICONASTERISK);
			return;
		}
		sql = "select * from BS_Wsaleset where SetType = 5 and BookCatalogID = " + IntToStr(CatalogID);
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->RecordCount > 0) {
			//�޸�
			sql = "update BS_Wsaleset set probookreturnrate = " + bookproreturnrate->Text + ",localbookreturnrate = " + localbookreturnrate->Text + ",bookreturnstartdate = '" + DateToStr(bookbegin->Date) + "',bookreturnenddate = '" + DateToStr(bookend->Date) + "'";
			sql = sql + " where id = " + aquery->FieldByName("ID")->AsString ;
			aqexe->Close();
			aqexe->SQL->Clear();
			aqexe->SQL->Add(sql);
			aqexe->ExecSQL();
		}
		else
		{
			//����
			sql = "insert into BS_Wsaleset(SetType,BookCatalogID,probookreturnrate,localbookreturnrate,bookreturnstartdate,bookreturnenddate) values(5," + IntToStr(CatalogID) + "," + bookproreturnrate->Text +
				  "," + localbookreturnrate->Text + ",'" + DateToStr(bookbegin->Date) + "','" + DateToStr(bookend->Date) + "')";
			aqexe->Close();
			aqexe->SQL->Clear();
			aqexe->SQL->Add(sql);
			aqexe->ExecSQL();
		}
	 break;

	 case 6:                         //�˻��ʰ����
		if (cbpress->Text == "") {
			MessageBoxA(0,"��ѡ�������!","��������",MB_ICONASTERISK);
			return;
		}
		sql = "select * from BS_Wsaleset where SetType = 6 and PressID = " + IntToStr(PressID);
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->RecordCount > 0) {
			//�޸�
			sql = "update BS_Wsaleset set propressreturnrate = " + pressreturnrate->Text + ",localpressreturnrate = " + localpressreturnrate->Text + ",pressreturnstartdate = '" + DateToStr(pressstart->Date) + "',pressreturnenddate = '" + DateToStr(pressend->Date) + "'";
			sql = sql + " where id = " + aquery->FieldByName("ID")->AsString ;
			aqexe->Close();
			aqexe->SQL->Clear();
			aqexe->SQL->Add(sql);
			aqexe->ExecSQL();
		}
		else
		{
			//����
			sql = "insert into BS_Wsaleset(SetType,PressID,propressreturnrate,localpressreturnrate,pressreturnstartdate,pressreturnenddate) values(6," + IntToStr(PressID) + "," + pressreturnrate->Text +
				  "," + localpressreturnrate->Text + ",'" + DateToStr(pressstart->Date) + "','" + DateToStr(pressend->Date) + "')";
			aqexe->Close();
			aqexe->SQL->Clear();
			aqexe->SQL->Add(sql);
			aqexe->ExecSQL();
		}
	 break;

  default:
	  ;
  }
  delete aquery;
  delete aqexe;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsset::spsearchClick(TObject *Sender)
{
	   DoInvokClient(editclientname);
	   //editclientname->Text = ClientName;
}
 void Tfrmwsset::RefreshDbGrid(int type ,TDBGrid *dg)
 {
   AnsiString sql;
   switch (type) {
		case 1:   //���ö��
			sql = "select BS_Wsaleset.*,CUST_CustomerInfo.Name,(case BS_Wsaleset.Containclientblance when 1 then '��' else '��' end) as clientblance,(case BS_Wsaleset.Creditactive when 1 then '��Ч' else '��Ч' end) as active from BS_Wsaleset left join CUST_CustomerInfo on BS_Wsaleset.ClientID = CUST_CustomerInfo.id where SetType = 1";
			break;
		case 2:   //�ؿ���
			sql = "select BS_Wsaleset.*,CUST_CustomerInfo.Name,(case BS_Wsaleset.backrateactive when 1 then '��Ч' else '��Ч' end) as active from BS_Wsaleset left join CUST_CustomerInfo on BS_Wsaleset.ClientID = CUST_CustomerInfo.id where SetType = 2";
			break;
		case 3:   //�˻���
			sql = "select BS_Wsaleset.*,CUST_CustomerInfo.Name,(case BS_Wsaleset.returnrateactive when 1 then '��Ч' else '��Ч' end) as active from BS_Wsaleset left join CUST_CustomerInfo on BS_Wsaleset.ClientID = CUST_CustomerInfo.id where SetType = 3" ;
			break;
		case 4:     //���
			sql = "select BS_Wsaleset.*,BS_BookType.Name,(case BS_Wsaleset.typereturnrateactive when 1 then '��Ч' else '��Ч' end) as active from BS_Wsaleset left join BS_BookType on BS_Wsaleset.BookType = BS_BookType.id where SetType = 4" ;
			break;
		case 5:     //��Ʒ
			sql = "select BS_Wsaleset.*,BS_BookCatalog.Name,BS_BookCatalog.Barcode,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookCatalog.ISBN,BS_PressInfo.AbbreviatedName,(case BS_Wsaleset.bookreturnrateactive when 1 then '��Ч' else '��Ч' end) as active from BS_Wsaleset left join BS_BookCatalog on BS_Wsaleset.BookCatalogID = BS_BookCatalog.id left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id where SetType = 5" ;
			break;
		case 6:     //���
			sql = "select BS_Wsaleset.*,BS_PressInfo.AbbreviatedName,(case BS_Wsaleset.pressreturnactive when 1 then '��Ч' else '��Ч' end) as active from BS_Wsaleset left join BS_PressInfo on BS_Wsaleset.PressID = BS_PressInfo.id where SetType = 6" ;
			break;
   default:
	   ;
   }
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   dg->DataSource = ds ;
   aq->Open();
 }
//---------------------------------------------------------------------------
void __fastcall Tfrmwsset::pcChange(TObject *Sender)
{
   int i ;
	i =  ((TPageControl *)(Sender))->ActivePage->Tag ;
	switch (i) {
		case 1:
			RefreshDbGrid(i,DBGrid1);
		break;
		case 2:
			RefreshDbGrid(i,DBGrid2);
		break;
		case 3:
			RefreshDbGrid(i,DBGrid3);
		break;
		case 4:
			RefreshDbGrid(i,DBGrid4);
		break;
		case 5:
			RefreshDbGrid(i,DBGrid5);
		break;
		case 6:
			RefreshDbGrid(i,DBGrid6);
		break;

	default:
		;
	}
	type = i;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsset::creditsaveClick(TObject *Sender)
{
  Enable(type);      //����
  RefreshDbGrid(1,DBGrid1);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsset::DBGrid1CellClick(TColumn *Column)
{
  if (aq->IsEmpty() ) {
      return;
  }
  ID = aq->FieldByName("ID")->AsInteger ;
  clientID = aq->FieldByName("ClientID")->AsInteger ;
  editclientname->Text = aq->FieldByName("Name")->AsString ;
  editalarmcredit->Text = aq->FieldByName("proCredit")->AsString ;
  editlockcredit->Text = aq->FieldByName("LocalDeliveryCredit")->AsString ;
  cridetbegin->Date = aq->FieldByName("Creditstartdate")->AsDateTime ;
  creditend->Date = aq->FieldByName("Creditenddate")->AsDateTime ;
  cbbalance->Checked = aq->FieldByName("Containclientblance")->AsBoolean ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::creditenableClick(TObject *Sender)
{
   if (aq->IsEmpty() ) {
       return;
   }
   AnsiString sql;
   sql = "update BS_Wsaleset set Creditactive = 1 where ID = " + aq->FieldByName("ID")->AsString;
   TADOQuery *aqexe = new TADOQuery(NULL);
   aqexe->Connection = fcon;
   aqexe->Close();
   aqexe->SQL->Add(sql);
   aqexe->ExecSQL();
   delete aqexe;
   RefreshDbGrid(1,DBGrid1);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsset::crditaddClick(TObject *Sender)
{
  editclientname->Text = "";
  editalarmcredit->Text = "0";
  editlockcredit->Text = "0";
  cridetbegin->Date = Now();
  creditend->Date = Now();
  cbbalance->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::FormShow(TObject *Sender)
{
  cridetbegin->Date = Now();
  creditend->Date = Now();
  dtpbackbegin->Date = Now();
  dtpbackend->Date = Now();
  returnbegin->Date = Now();
  returnend->Date = Now();
  typestart->Date = Now();
  typeend->Date = Now();
  bookbegin->Date = Now();
  bookend->Date = Now();
  pressstart->Date = Now();
  pressend->Date = Now();
  RefreshDbGrid(1,DBGrid1);
  ReadyData();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsset::SpeedButton4Click(TObject *Sender)
{
	DoInvokClient(backclientname);
	//backclientname->Text = ClientName;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::backaddClick(TObject *Sender)
{
	backclientname->Text = "";
	monthbakarate->Text = "0";
	yearbackrate->Text = "0";
	probackrate->Text = "0";
	localdeliverybackrate->Text = "0";
	dtpbackbegin->Date = Now();
	dtpbackend->Date = Now();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmwsset::backsaveClick(TObject *Sender)
{
	Enable(type);      //����
	RefreshDbGrid(2,DBGrid2);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::DBGrid2CellClick(TColumn *Column)
{
	if (aq->IsEmpty() ) {
        return;
	}
	ID = aq->FieldByName("ID")->AsInteger ;
	clientID = aq->FieldByName("ClientID")->AsInteger ;
	backclientname->Text = aq->FieldByName("Name")->AsString ;
	monthbakarate->Text = aq->FieldByName("monthbackrate")->AsString ;
	yearbackrate->Text = aq->FieldByName("yearbackrate")->AsString ;
	probackrate->Text = aq->FieldByName("probackrate")->AsString ;
	localdeliverybackrate->Text = aq->FieldByName("localDeliverybackrate")->AsString ;
	dtpbackbegin->Date = aq->FieldByName("backratestartdate")->AsDateTime ;
	dtpbackend->Date = aq->FieldByName("backrateenddate")->AsDateTime ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::returnaddClick(TObject *Sender)
{
	returnclientname->Text = "";
	proreturnrate->Text = "0";
	localreturnrate->Text = "0";
	returnbegin->Date = Now();
	returnend->Date = Now();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::spclientsearchClick(TObject *Sender)
{
	DoInvokClient(returnclientname);
	//returnclientname->Text = ClientName;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::returnsaveClick(TObject *Sender)
{
	Enable(type);      //����
	RefreshDbGrid(3,DBGrid3);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::DBGrid3CellClick(TColumn *Column)
{
	if (aq->IsEmpty() ) {
		return;
	}
	ID = aq->FieldByName("ID")->AsInteger ;
	clientID = aq->FieldByName("ClientID")->AsInteger ;
	returnclientname->Text = aq->FieldByName("Name")->AsString ;
	proreturnrate->Text = aq->FieldByName("proreturnrate")->AsString ;
	localreturnrate->Text = aq->FieldByName("localreturnrate")->AsString ;
	returnbegin->Date = aq->FieldByName("returnratestartdate")->AsDateTime ;
	returnend->Date = aq->FieldByName("returnrateenddate")->AsDateTime ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::backactiveClick(TObject *Sender)
{
	if (aq->IsEmpty() ) {
        return;
	}
	AnsiString sql;
   sql = "update BS_Wsaleset set backrateactive = 1 where ID = " + aq->FieldByName("ID")->AsString;
   TADOQuery *aqexe = new TADOQuery(NULL);
   aqexe->Connection = fcon;
   aqexe->Close();
   aqexe->SQL->Add(sql);
   aqexe->ExecSQL();
   delete aqexe;
   RefreshDbGrid(2,DBGrid2);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::returnactiveClick(TObject *Sender)
{
	if (aq->IsEmpty() ) {
        return;
	}
	AnsiString sql;
   sql = "update BS_Wsaleset set returnrateactive = 1 where ID = " + aq->FieldByName("ID")->AsString;
   TADOQuery *aqexe = new TADOQuery(NULL);
   aqexe->Connection = fcon;
   aqexe->Close();
   aqexe->SQL->Add(sql);
   aqexe->ExecSQL();
   delete aqexe;
   RefreshDbGrid(3,DBGrid3);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsset::ReadyData()
{
	AnsiString sql;
	TADOQuery *aquery = new TADOQuery(NULL);
	aquery->Connection = fcon;
   sql = "select ID,Name from BS_BookType";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->Open() ;
   while (!aquery->Eof )
   {
		cbbooktype->AddItem(aquery->FieldByName("ID")->AsString + aquery->FieldByName("Name")->AsString ,(TObject*)aquery->FieldByName("ID")->AsInteger );
		aquery->Next();
   }
   sql = "select ID,PresentNum,AbbreviatedName from BS_PressInfo";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->Open() ;
   while (!aquery->Eof )
   {
		cbpress->AddItem(aquery->FieldByName("PresentNum")->AsString + aquery->FieldByName("AbbreviatedName")->AsString ,(TObject*)aquery->FieldByName("ID")->AsInteger );
		aquery->Next();
   }
   delete aquery;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmwsset::cbbooktypeClick(TObject *Sender)
{
	BookType = int(cbbooktype->Items->Objects[cbbooktype->ItemIndex]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::cbpressClick(TObject *Sender)
{
	PressID = int(cbpress->Items->Objects[cbpress->ItemIndex]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::typeaddClick(TObject *Sender)
{
	cbbooktype->Text = "";
	typereturnrate->Text = "0";
	localtypereturnrate->Text = "0";
	typestart->Date = Now();
	typeend->Date = Now();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::typesaveClick(TObject *Sender)
{
	Enable(4);      //����
	RefreshDbGrid(4,DBGrid4);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::DBGrid4CellClick(TColumn *Column)
{
	if (aq->IsEmpty() ) {
        return;
	}
	ID = aq->FieldByName("ID")->AsInteger ;
	BookType = aq->FieldByName("BookType")->AsInteger ;
	cbbooktype->Text = aq->FieldByName("Name")->AsString ;
	typereturnrate->Text = aq->FieldByName("protypereturnrate")->AsString ;
	localtypereturnrate->Text = aq->FieldByName("localtypereturnrate")->AsString ;
	typestart->Date = aq->FieldByName("typereturnstaetdate")->AsDateTime ;
	typeend->Date = aq->FieldByName("typereturnenddate")->AsDateTime ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::DBGrid6CellClick(TColumn *Column)
{
	if (aq->IsEmpty()  ) {
    	return;
	}
	ID = aq->FieldByName("ID")->AsInteger ;
	PressID = aq->FieldByName("PressID")->AsInteger ;
	cbpress->Text = aq->FieldByName("AbbreviatedName")->AsString ;
	pressreturnrate->Text = aq->FieldByName("propressreturnrate")->AsString ;
	localpressreturnrate->Text = aq->FieldByName("localpressreturnrate")->AsString ;
	pressstart->Date = aq->FieldByName("pressreturnstartdate")->AsDateTime ;
	pressend->Date = aq->FieldByName("pressreturnenddate")->AsDateTime ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::typeactiveClick(TObject *Sender)
{
	if (aq->IsEmpty() ) {
        return;
	}
	AnsiString sql;
   sql = "update BS_Wsaleset set typereturnrateactive = 1 where ID = " + aq->FieldByName("ID")->AsString;
   TADOQuery *aqexe = new TADOQuery(NULL);
   aqexe->Connection = fcon;
   aqexe->Close();
   aqexe->SQL->Add(sql);
   aqexe->ExecSQL();
   delete aqexe;
   RefreshDbGrid(4,DBGrid4);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::pressactiveClick(TObject *Sender)
{
	if (aq->IsEmpty() ) {
		return;
	}
	AnsiString sql;
   sql = "update BS_Wsaleset set pressreturnactive = 1 where ID = " + aq->FieldByName("ID")->AsString;
   TADOQuery *aqexe = new TADOQuery(NULL);
   aqexe->Connection = fcon;
   aqexe->Close();
   aqexe->SQL->Add(sql);
   aqexe->ExecSQL();
   delete aqexe;
   RefreshDbGrid(6,DBGrid6);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::bookaddClick(TObject *Sender)
{
	edBarcode->Text = "";
	edprice->Text = "";
	edpress->Text = "";
	edbookname->Text = "";
	bookproreturnrate->Text = "0";
	localbookreturnrate->Text = "0";
	bookbegin->Date = Now();
	bookend->Date = Now();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::edBarcodeKeyPress(TObject *Sender, wchar_t &Key)
{
	AnsiString sql;
	TADOQuery *aquery = new TADOQuery(NULL);
	aquery->Connection = fcon;
	if (Key == '\r') {
		sql = "select BS_BookCatalog.ID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,STK_BookInfo.ID as STK_BookinfoID,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.AbbreviatedName ,STK_BookstackInfo.name LocalName "
			"from STK_BookInfo  join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(m_storageID) + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Barcode='" + edBarcode->Text + "'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->RecordCount == 1) {
			CatalogID = aquery->FieldByName("ID")->AsInteger ;
			edprice->Text = aquery->FieldByName("Price")->AsString ;
			edpress->Text = aquery->FieldByName("AbbreviatedName")->AsString ;
			edbookname->Text = aquery->FieldByName("Name")->AsString ;
		}
		else if (aquery->RecordCount > 0) {
			Tfrmcatalogselect *frm  = new Tfrmcatalogselect(Application,fcon, aquery);
			frm->BtnChangeOptions->Visible = false;
			frm->BtnWeekView->Visible = false;
			if (mrOk==frm->ShowModal()) {
				CatalogID = aquery->FieldByName("ID")->AsInteger ;
				CatalogID = aquery->FieldByName("ID")->AsInteger ;
				edprice->Text = aquery->FieldByName("Price")->AsString ;
				edpress->Text = aquery->FieldByName("AbbreviatedName")->AsString ;
				edbookname->Text = aquery->FieldByName("Name")->AsString ;
			}
		}
		else
		{
			MessageBoxA(0,"û�и����¼!","��������",MB_ICONASTERISK);
			return;
		}
		bookproreturnrate->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::booksaveClick(TObject *Sender)
{
	Enable(5);      //����
	RefreshDbGrid(5,DBGrid5);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::DBGrid5CellClick(TColumn *Column)
{
	if (aq->IsEmpty() ) {
        return;
	}
	ID = aq->FieldByName("ID")->AsInteger ;
	CatalogID = aq->FieldByName("BookCatalogID")->AsInteger ;
	edBarcode->Text = aq->FieldByName("Barcode")->AsString ;
	edprice->Text = aq->FieldByName("Price")->AsString ;
	edpress->Text = aq->FieldByName("AbbreviatedName")->AsString ;
	edbookname->Text = aq->FieldByName("Name")->AsString ;
	bookproreturnrate->Text = aq->FieldByName("probookreturnrate")->AsString ;
	localbookreturnrate->Text = aq->FieldByName("localbookreturnrate")->AsString ;
	bookbegin->Date = aq->FieldByName("bookreturnstartdate")->AsDateTime ;
	bookend->Date = aq->FieldByName("bookreturnenddate")->AsDateTime ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::bookactiveClick(TObject *Sender)
{
	if (aq->IsEmpty() ) {
        return;
	}
	AnsiString sql;
   sql = "update BS_Wsaleset set bookreturnrateactive = 1 where ID = " + aq->FieldByName("ID")->AsString;
   TADOQuery *aqexe = new TADOQuery(NULL);
   aqexe->Connection = fcon;
   aqexe->Close();
   aqexe->SQL->Add(sql);
   aqexe->ExecSQL();
   delete aqexe;
   RefreshDbGrid(5,DBGrid5);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::N2Click(TObject *Sender)
{
	if (aq->Active &&aq->RecordCount > 0) {
		AnsiString sql;
		sql = "delete from BS_Wsaleset where ID = " + aq->FieldByName("ID")->AsString ;
		TADOQuery *aqexe = new TADOQuery(NULL);
		aqexe->Connection = fcon;
		aqexe->Close();
		aqexe->SQL->Add(sql);
		aqexe->ExecSQL();
		delete aqexe;
	}
	aq->Active = false;
	aq->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::N1Click(TObject *Sender)
{
	AnsiString sql;
	if (aq->Active &&aq->RecordCount > 0) {
		switch (type) {
			case 1:
				sql = "update BS_Wsaleset set Creditactive = 0 where id = " + aq->FieldByName("ID")->AsString;
			break;
			case 2:
				sql = "update BS_Wsaleset set backrateactive = 0 where id = " + aq->FieldByName("ID")->AsString;
			break;
			case 3:
				sql = "update BS_Wsaleset set returnrateactive = 0 where id = " + aq->FieldByName("ID")->AsString;
			break;
			case 4:
				sql = "update BS_Wsaleset set typereturnrateactive = 0 where id = " + aq->FieldByName("ID")->AsString;
			break;
			case 5:
				sql = "update BS_Wsaleset set bookreturnrateactive = 0 where id = " + aq->FieldByName("ID")->AsString;
			break;
			case 6:
				sql = "update BS_Wsaleset set pressreturnactive = 0 where id = " + aq->FieldByName("ID")->AsString;
			break;
		default:
            ;
		}
		TADOQuery *aqexe = new TADOQuery(NULL);
		aqexe->Connection = fcon;
		aqexe->Close();
		aqexe->SQL->Add(sql);
		aqexe->ExecSQL();
		delete aqexe;
		aq->Active = false;
		aq->Active = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::presssaveClick(TObject *Sender)
{
	Enable(6);      //����
	RefreshDbGrid(6,DBGrid6);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::pressaddClick(TObject *Sender)
{
	cbpress->Text = "";
	pressreturnrate->Text = "0";
	localpressreturnrate->Text = "0";
	pressstart->Date = Now();
	pressend->Date = Now();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::editclientnameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,editclientname->Text,m_storageID);
		if (mrOk == frm->ShowModal() ) {
		   clientID  = frm->GetSelectID();
		   ClientName = frm->GetSelect();
		   editclientname->Text = voidClientName();
		   editalarmcredit->SetFocus();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------


AnsiString  Tfrmwsset::voidClientName()
{
	if (clientID == -1) {
		return "";
	}
	String sql,Name;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	sql = "exec USP_BS_Client_View 0," + IntToStr(clientID)  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	Name = aq->FieldByName("Name")->AsAnsiString ;
	delete aq;
	return Name;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::editalarmcreditKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        editlockcredit->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::editlockcreditKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        cridetbegin->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::cridetbeginKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        creditend->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::creditendKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        cbbalance->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::cbbalanceKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        creditsave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::backclientnameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,backclientname->Text,m_storageID);
		if (mrOk == frm->ShowModal() ) {
		   clientID  = frm->GetSelectID();
		   ClientName = frm->GetSelect();
		   backclientname->Text = voidClientName();
		   monthbakarate->SetFocus();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::monthbakarateKeyPress(TObject *Sender, wchar_t &Key)
{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        yearbackrate->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::yearbackrateKeyPress(TObject *Sender, wchar_t &Key)
{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        probackrate->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::probackrateKeyPress(TObject *Sender, wchar_t &Key)
{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        localdeliverybackrate->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::localdeliverybackrateKeyPress(TObject *Sender, wchar_t &Key)

{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        dtpbackbegin->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::dtpbackbeginKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        dtpbackend->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::dtpbackendKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        backsave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::returnclientnameKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,returnclientname->Text,m_storageID);
		if (mrOk == frm->ShowModal() ) {
		   clientID  = frm->GetSelectID();
		   ClientName = frm->GetSelect();
		   returnclientname->Text = voidClientName();
		   proreturnrate->SetFocus();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::proreturnrateKeyPress(TObject *Sender, wchar_t &Key)
{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        localreturnrate->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::localreturnrateKeyPress(TObject *Sender, wchar_t &Key)

{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        returnbegin->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::returnbeginKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        returnend->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::returnendKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        returnsave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::cbbooktypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		typereturnrate->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::typereturnrateKeyPress(TObject *Sender, wchar_t &Key)
{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        localtypereturnrate->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::localtypereturnrateKeyPress(TObject *Sender, wchar_t &Key)

{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        typestart->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::typestartKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        typeend->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::typeendKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        typesave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::bookproreturnrateKeyPress(TObject *Sender, wchar_t &Key)

{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        localbookreturnrate->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::localbookreturnrateKeyPress(TObject *Sender, wchar_t &Key)

{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        bookbegin->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::bookbeginKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        bookend->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::bookendKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        booksave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::cbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
    	pressreturnrate->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::pressreturnrateKeyPress(TObject *Sender, wchar_t &Key)

{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        localpressreturnrate->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::localpressreturnrateKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}
	if (Key == VK_RETURN) {
        pressstart->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::pressstartKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        pressend->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::pressendKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
    	presssave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::pressreturnrateExit(TObject *Sender)
{
	if (pressreturnrate->Text == "") {
		pressreturnrate->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::localpressreturnrateExit(TObject *Sender)
{
	if (localpressreturnrate->Text == "") {
    	localpressreturnrate->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::localbookreturnrateExit(TObject *Sender)
{
	if (localbookreturnrate->Text == "") {
    	localbookreturnrate->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::bookproreturnrateExit(TObject *Sender)
{
	if (bookproreturnrate->Text == "") {
    	bookproreturnrate->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::typereturnrateExit(TObject *Sender)
{
	if (typereturnrate->Text == "") {
    	typereturnrate->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::localtypereturnrateExit(TObject *Sender)
{
	if (localtypereturnrate->Text == "") {
    	localtypereturnrate->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::proreturnrateExit(TObject *Sender)
{
	if (proreturnrate->Text == "") {
    	proreturnrate->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::localreturnrateExit(TObject *Sender)
{
	if (localreturnrate->Text == "") {
    	localreturnrate->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::monthbakarateExit(TObject *Sender)
{
	if (monthbakarate->Text == "") {
    	monthbakarate->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::yearbackrateExit(TObject *Sender)
{
	if (yearbackrate->Text == "") {
    	yearbackrate->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::probackrateExit(TObject *Sender)
{
	if (probackrate->Text == "") {
    	probackrate->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::localdeliverybackrateExit(TObject *Sender)
{
	if (localdeliverybackrate->Text == "") {
    	localdeliverybackrate->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::editalarmcreditExit(TObject *Sender)
{
	if (editalarmcredit->Text == "") {
    	editalarmcredit->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::editlockcreditExit(TObject *Sender)
{
	if (editlockcredit->Text == "") {
    	editlockcredit->Text = "0";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsset::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
