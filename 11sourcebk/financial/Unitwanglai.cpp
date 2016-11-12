//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitwanglai.h"
#include "..\bsadmin\UnitSelectClient.h"
#include "Notedetail.h"
#include "unitfapiao.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBSumLst"
#pragma link "RpBase"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpSystem"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "DataDriverEh"
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma resource "*.dfm"
Tfrmwanglaizhang *frmwanglaizhang;
//---------------------------------------------------------------------------
__fastcall Tfrmwanglaizhang::Tfrmwanglaizhang(TComponent* Owner,int type)
	: TForm(Owner)
{
	Client = type;
	if (type == 1) {
		chclient->Caption = "��Ӧ������";
		GroupBox1->Caption = "��Ӧ����Ϣ";
		spselectClient->Visible = false;
		edtclient->Visible = false;
		dg->Columns->Items[2]->Title->Caption = "��Ӧ������";
		dg2->Columns->Items [5]->Title->Caption = "��Ӧ��";
		ch1->Caption = "��        ��";
		ch2->Visible = false;
		this->Caption = "��Ӧ����������";
		N8->Enabled=true;
		dg->ReadOnly=true;
	}
	else
	{
		chclient->Caption = "�ͻ�����";
		GroupBox1->Caption = "�ͻ���Ϣ";
		cbdanwei->Visible = false;
		dg->Columns->Items[2]->Title->Caption = "�ͻ�����";
		dg->Columns->Items[9]->Title->Caption = "��Ӧ��";
		dg2->Columns->Items [5]->Title->Caption = "��Ӧ��";
		ch1->Caption = "��        ��";
		this->Caption = "�ͻ���������";
        N8->Enabled=false;
	}
	dg->OnDrawColumnCell=dgDrawColumnCell;
}
void Tfrmwanglaizhang::init(LandInfo* li)
{
	userInfo.app = li->app ;
	userInfo.con = li->con ;
	userInfo.userID = li->userID ;
	userInfo.storageID = li->storageID ;
	userInfo.UserName = li->UserName;

	fcon = li->con;
	stgid = li->storageID;
	query->Connection = li->con ;
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = fcon  ;
	query2->Connection = fcon;
	adosp->Connection = fcon;
	adoquerymain->Connection = fcon;

	if (Client == 1) {
		sql = "select * from SYS_BSSET where name = 'xiaoshudian'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		format = aq->FieldByName("bk")->AsString ;
	}
	else
	{
		sql = "select * from SYS_BSSET where name = 'salexiaoshudian'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		format = aq->FieldByName("bk")->AsString ;
	}
	sql = "select * from SYS_BSSET where name = 'changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	ChangeDisplay  = aq->FieldByName("value")->AsBoolean ;

	sql = "select Name from SYS_StorageInfo where ID = " + IntToStr(stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	StorageName = aq->FieldByName("name")->AsAnsiString ;

	if (Client == 1) {
		sql = "select ID,Name from cust_customerinfo where Type in (1) and Name <> '' ";
	}
	else
	{
		sql = "select ID,Name from cust_customerinfo where Type in (2,3) and Name <> '' ";
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbdanwei->Items->Clear();
	cbdanwei->Text = "";
	while(!aq->Eof)
	{
		cbdanwei->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
	ButtonType1 = false;
	ButtonType2 = false;
	ButtonType3 = false;
	dtpbegin->Date = Now();
	dtpend->Date = Now();
	aqprint->Connection = userInfo.con ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwanglaizhang::editjianshuoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		GetClientInfor(editjianshuo->Text.Trim());
	}
}
void Tfrmwanglaizhang::GetClientInfor(AnsiString KeyWord)
{
	AnsiString sql;
	if (Client == 1) {
		sql = "select ID,Name from cust_customerinfo where Type in (1) and Name like '%" + KeyWord+"%' and Name <> '' ";
    	TADOQuery *aq = new TADOQuery(NULL);
		aq->Connection = userInfo.con ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbdanwei->Items->Clear();
		cbdanwei->Text = "";
		while(!aq->Eof)
		{
			cbdanwei->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbdanwei->ItemIndex = cbdanwei->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
        cbdanwei->OnSelect (this);
		delete aq;
	}else
	{
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,KeyWord,	userInfo.storageID);
		if (mrOk == frm->ShowModal())
		{
			ClientID = frm->GetSelectID();
			cbdanwei->ItemIndex = cbdanwei->Items->IndexOfObject((TObject*)ClientID);
			ClientView();
			GetClientDetail(ClientID);
		}
		delete frm;
	}
}
void Tfrmwanglaizhang::GetClientDetail(int vendor)
{
   	AnsiString sql,sql1 ;
	if (Client == 1) {//��Ӧ��
		sql = "select sum(Checked) as checked,sum(Nochecked) as nochecked from BS_StorageNoteHeader where supplierid = " + IntToStr(vendor);
	}else
	{
		sql = "select sum(Checked) as checked,sum(Nochecked) as nochecked from BS_WsaleNoteHeader where VendorID in(select ID from GetChild("+IntToStr(vendor)+"))" ;
	}
	sql1 = "select cust_customerinfo.*,CUST_CustomerStartMoney.Balance + CUST_CustomerStartMoney.totalyue as totalyue from cust_customerinfo left join CUST_CustomerStartMoney on CUST_CustomerStartMoney.CustomerID = cust_customerinfo.id where cust_customerinfo.ID = "+ IntToStr(vendor);
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = fcon ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edityijie->Text =  "��" + FormatFloat(format,aq->FieldByName("checked")->AsFloat);
	editweijie->Text = "��" + FormatFloat(format,aq->FieldByName("nochecked")->AsFloat);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql1);
	aq->Open();
	edityue->Text =  "��" + FormatFloat(format,aq->FieldByName("totalyue")->AsFloat);

	editcontact->Text = aq->FieldByName("contact")->AsAnsiString ;
	editzhanhao->Text = aq->FieldByName("bankaccount")->AsAnsiString ;
	edittel->Text = aq->FieldByName("telephone")->AsAnsiString ;
	editfax->Text = aq->FieldByName("fax")->AsAnsiString ;
	editaddress->Text = aq->FieldByName("address")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::cbdanweiSelect(TObject *Sender)
{
	try
	{
		GetClientDetail((int)cbdanwei->Items->Objects[cbdanwei->ItemIndex]);
	}
	catch(...)
	{
		MessageBoxA(0,"��������ȷ�ĵ�λ����!","��ʾ",MB_ICONEXCLAMATION||MB_OK);
	}
}
//---------------------------------------------------------------------------

void  Tfrmwanglaizhang::ancode()
{
	AnsiString Danhao,sqlwhere;
	ButtonType2 = true;
	ButtonType1 = false ;
	if (Client== 1)
	{
		if (ChangeDisplay) {
			sql = "select grouping(A.stgNtCodeStr) as d ,isnull(name,'�ܺϼ�') cusname, case when grouping(A.stgNtCodeStr) = 1 then '�ϼ�' else '��ϸ' end as stype, A.stgNtCodeStr  as CodeStr, "  ;
		} else
		{
			sql = "select grouping(A.stgntcode) as d,isnull(name,'�ܺϼ�') cusname, case when grouping(A.stgntcode) = 1 then '�ϼ�' else '��ϸ' end as stype, cast(A.stgntcode as nvarchar(15))  as CodeStr,  "  ;
		}
		sql = sql +" sum(TotalAmount) as TotalAmount,sum(totalfixedprice) as totalfixedprice,sum(TotalDiscountedPrice) as TotalDiscountedPrice, "
			 " sum(nochecked) as nochecked,sum(checked) as checked,sum(addcosts) as addcosts,A.Remarks,A.State,A.fapiao "
			 " from BS_StorageNoteHeader A join CUST_CustomerInfo B ON A.Supplierid = B.ID ";
		sqlwhere = " where A.stgid = " + IntToStr(stgid);
		if (chstart->Checked) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpbegin->Date) + "',A.Hdtime) >= 0 ";
		}
		if (chend->Checked ) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',A.Hdtime) <= 0 ";
		}
		if (chclient->Checked && cbdanwei->Text != "") {
			try {
				sqlwhere = sqlwhere + " and A.supplierid = " + IntToStr((int)cbdanwei->Items->Objects[cbdanwei->ItemIndex]);
			} catch (...) {
				MessageBoxA(0,"��ѡ����ȷ�ĵ�λ����!","��ʾ",MB_ICONEXCLAMATION||MB_OK);
				return;
			}
		}
		if (chstate->Checked ) {
			sqlwhere = sqlwhere + " and A.State = " + IntToStr(cbstate->ItemIndex);
		}
		if (chfapiao->Checked ) {
			sqlwhere = sqlwhere + " and A.fapiao = " + IntToStr(cbfapiao->ItemIndex);
		}
		sql = sql +  sqlwhere;
		if (ChangeDisplay) {
			sql = sql +	 " group by Name,A.stgNtCodeStr,A.Remarks,A.State,A.fapiao with ROLLUP";
		}else
		{
		   sql = sql +	 " group by Name,A.stgntcode,A.Remarks,A.State,A.fapiao with ROLLUP";
		}
	 }
	 else                    //wsaleNtCodeStr
	 {
		if (ChangeDisplay) {
			Danhao = "wsaleNtCodeStr";
		} else
		{
			Danhao = "wsaleNtCode";
		}
		sql = "select  grouping(A."+Danhao+") as d, isnull(dbo.uf_bs_getclientname(A.vendorID),'�ܺϼ�') cusname, case when grouping(A."+Danhao+") = 1 then '�ϼ�' else '��ϸ' end as stype, cast (A."+Danhao+" as nvarchar(15))  as CodeStr,";
		sql = sql +  " sum(totalAmount) as totalAmount,sum(fixedprice) as totalfixedprice,sum(DiscountedPrice) as TotalDiscountedPrice, "
			 //" sum(totalbackdot) as '����',sum(totalyingshou) as 'Ӧ��', "
			 " sum(nochecked) as nochecked,sum(checked) as checked,sum(addcosts) as addcosts,A.Remarks,A.State,A.fapiao "
			 " from BS_WsaleNoteHeader A join CUST_CustomerInfo B ON A.vendorid = B.ID ";
		sqlwhere = " where A.stgid = " + IntToStr(stgid);
		if (chstart->Checked) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpbegin->Date) + "',A.Hdtime) >= 0 ";
		}
		if (chend->Checked ) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',A.Hdtime) <= 0 ";
		}
		if (chclient->Checked && edtclient->Text != "") {
			sqlwhere = sqlwhere + " and A.vendorID in (select id from dbo.GetChild(" + IntToStr(ClientID) + ")) ";
		}
		if (chstate->Checked ) {
			sqlwhere = sqlwhere + " and A.State = " + IntToStr(cbstate->ItemIndex);
		}
		if (chfapiao->Checked ) {
			sqlwhere = sqlwhere + " and A.fapiao = " + IntToStr(cbfapiao->ItemIndex);
		}
		sql = sql + sqlwhere + " group by Name,A.vendorID,A."+Danhao+",A.Remarks,A.State,A.fapiao with ROLLUP ";
	 }
	//TColumn *column;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	((TFloatField *)query->FieldByName("totalfixedprice"))->DisplayFormat =  "��" + format ;
	((TFloatField *)query->FieldByName("TotalDiscountedPrice"))->DisplayFormat =  "��" + format ;
	((TFloatField *)query->FieldByName("checked"))->DisplayFormat =  "��" + format ;
	((TFloatField *)query->FieldByName("nochecked"))->DisplayFormat =  "��" + format ;
	((TFloatField *)query->FieldByName("addcosts"))->DisplayFormat =  "��" + format ;

	/*TColumn *Col;
	dg->Columns->Clear();
	query->DisableControls();
	for (int i =1; i < query->Fields->Count ; i++) { //ȥ��ID

		Col =  dg->Columns->Add();
		Col->FieldName  = query->Fields->Fields[i]->FieldName  ;
		Col->Title->Alignment = taCenter ;

		if (Col->FieldName == "ͳ������") {
		  Col->Width = 60;
		  Col->Alignment = taLeftJustify ;
		}else
		{
		  Col->Width = 84;
		}
		query->Next();
	}
	if (Client == 1 ) { //��Ӧ��
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;

	} else
	{
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("Ӧ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;
	} */
	query->EnableControls();
   //	ButtonType2 = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::SpeedButton2Click(TObject *Sender)
{
 	ButtonType3 = true;
}
//---------------------------------------------------------------------------


void Tfrmwanglaizhang::Print(int type,int print)
{
	if (query->IsEmpty()  ) {
		return;
	}
	AnsiString sqlprint;
	sqlprint = StringReplace(sql,"���","xuhao",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"����","danhao",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"����","rkqi",TReplaceFlags()<<rfReplaceAll);

	sqlprint = StringReplace(sqlprint,"����","totalamount",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"����","mayang",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"ʵ��","siyang",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"δ��","weijie",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"�ѽ�","yijie",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"���ӷ���","addcost",TReplaceFlags()<<rfReplaceAll);
	//sqlprint = StringReplace(sqlprint,"����","backdot",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"��ע","bk",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"����״̬","cwstate",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"��Ʊ","fapiao",TReplaceFlags()<<rfReplaceAll);
	//sqlprint = StringReplace(sqlprint,"Ӧ��","yingshou",TReplaceFlags()<<rfReplaceAll);

	if (Client == 1) {
		sqlprint = StringReplace(sqlprint,"��Ӧ������","name",TReplaceFlags()<<rfReplaceAll);
	}else
	{
		sqlprint = StringReplace(sqlprint,"�ͻ�����","name",TReplaceFlags()<<rfReplaceAll);
		//sqlprint = StringReplace(sqlprint,"ͳ������","yewutype",TReplaceFlags()<<rfReplaceAll);
		//sqlprint = StringReplace(sqlprint,"�ͻ�","Clientname",TReplaceFlags()<<rfReplaceAll);
		//sqlprint = StringReplace(sqlprint,"��Ӧ��","Clientname",TReplaceFlags()<<rfReplaceAll);

	}
	aqprint->Close();
	aqprint->SQL->Clear();
	aqprint->SQL->Add(sqlprint);
	aqprint->Open();

	RvSystem1->SystemSetups >>ssAllowSetup;
	RvSystem1->SystemSetups >>ssAllowDestPreview;
	RvSystem1->SystemSetups >>ssAllowDestPrinter;
	RvSystem1->SystemSetups >>ssAllowPrinterSetup;
	RvSystem1->SystemSetups >>ssAllowDestFile;
	if (1==print) {
       RvSystem1->DefaultDest = rdPrinter ;
	}else
	{
		RvSystem1->DefaultDest  = rdPreview ;
	}
	RvSystem1->SystemSetups<<ssAllowDestPreview;
	if (type == 1) {      //�ͻ���
	  if (Client == 1) {        //��Ӧ��
		  duizhang->ProjectFile = ExtractFilePath(Application->ExeName) + "DuizhangSupplier.rav";
	  }else
	  {
		  duizhang->ProjectFile = ExtractFilePath(Application->ExeName) + "Duizhang.rav";
	  }
	  duizhang->SetParam("title",StorageName + "���ʵ�");
	  duizhang->SetParam("danwei",cbdanwei->Text);
	  duizhang->SetParam("contact",editcontact->Text);
	  duizhang->SetParam("tel",edittel->Text);
	  duizhang->SetParam("yijie",edityijie->Text);//yijie
	  duizhang->SetParam("weijie",editweijie->Text);
	  duizhang->SetParam("begin",DateToStr(dtpbegin->Date));
	  duizhang->SetParam("end",DateToStr(dtpend->Date));
	}
	if (type == 2) {
	   if (Client == 1) {

	   }else
	   {


	   }
	   duizhang->ProjectFile = ExtractFilePath(Application->ExeName) + "DuizhangAnDan.rav";
	   duizhang->SetParam("title",StorageName + "���ʵ�");
  	   duizhang->SetParam("begin",DateToStr(dtpbegin->Date));
	   duizhang->SetParam("end",DateToStr(dtpend->Date ));
	}

	duizhang->Open();
	duizhang->Execute();
	duizhang->Close();
}

//---------------------------------------------------------------------------



void __fastcall Tfrmwanglaizhang::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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
	if (Key == VK_F7 ) {    //Ԥ��
		BtnPrintPreview->Click();
	}
	if (Key == VK_F8 ) {    //��ӡ
		BtnPrint->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //��ѯ
		BtnView->Click();
	}
	if (Key == VK_F3 ) {    //����
		BtnProperties->Click();
	}
	if (Key == VK_F4 ) {    //��Ʊ
		BtnNextRecord->Click();
	}
	if (Key == VK_F6 ) {    //����
		BtnExport->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::BtnPrintClick(TObject *Sender)
{
	if (ButtonType1) {
		Print(1,1);
	}
	if (ButtonType2) {
		Print(2,1);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::BtnPrintPreviewClick(TObject *Sender)
{
	if (ButtonType1) {
		Print(1,0);
	}
	if (ButtonType2) {
		Print(2,0);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::BtnViewClick(TObject *Sender)
{
	//ancode();
	ButtonType1 = true;
	ButtonType2 = false;
	AnsiString sqlwhere,sqlwhere1;
	AnsiString sql1,sql2;
	if (Client== 1) { //��Ӧ��
		if (ChangeDisplay) {
			sql= " select  distinct A.ID,cast (RANK() OVER(order by A.ID asc) as nvarchar(10)) as '���',B.Name as '��Ӧ������',A.StgNtCode as code,A.StgNtCodeStr as '����',CONVERT(varchar(12),A.Hdtime,111) as  '����'," ;
		}else
		{
			sql= " select distinct A.ID,cast (RANK() OVER(order by A.ID asc) as nvarchar(10)) as '���',B.Name as '��Ӧ������', A.StgNtCode as code,cast(A.StgNtCode as nvarchar(15))as '����',CONVERT(varchar(12),A.Hdtime,111)as '����'," ;
		}
		 sql = sql + " A.TotalAmount as '����',A.TotalFixedPrice as '����',A.TotalDiscountedPrice as 'ʵ��',A.AddCosts as '���ӷ���',A.AddCosts + A.TotalDiscountedPrice as totalyingfu, A.checked  as '�ѽ�',A.nochecked as 'δ��', "
				" A.remarks as '��ע',case A.cwstate when 0 then 'δ����' else '��'  end  as '����״̬', "
				" A.duifangmoney as '�Է�����',A.hongcong as '���',A.cwbk, "
				" case when D.state = 0 and C.thistime > 0 then 'δ���' when abs(A.Checked) >= 0.01 and abs(A.NoChecked) < 0.01 then '�ѽ��' when abs(A.Checked) >= 0.01 and abs(A.NoChecked) >= 0.01 then '�ѽᲿ��' when  abs(A.Checked) < 0.01 and abs(A.NoChecked) >= 0.01 then 'δ���' end as '���״̬', "
				" case A.fapiao when 0 then 'δ��' else '��' end as '��Ʊ',A.fapiaotext, "
				" case when dbo.uf_bs_getjiekuancode(A.id,1) is null and A.Checked > 0 then '�ֳ����' else dbo.uf_bs_getjiekuancode(A.id,1) end as '����' from BS_StorageNoteHeader  A left join CUST_CustomerInfo B on A.supplierid = B.id "
				" left join (select * from FN_CUSEndMoneyDtails where type = 1) C ON C.stgntcode = A.StgNtCode "
				" left join FN_CUSEndMoneyDocuments D ON D.MoneyCode = C.EndMoneyDocumentID ";

	   sqlwhere = " where A.stgid = " + IntToStr(stgid) ;
		if (chstart->Checked) {
			sqlwhere = sqlwhere + " and datediff(day,''" + DateToStr(dtpbegin->Date) + "'',A.Hdtime) >= 0 ";
		}
		if (chend->Checked ) {
			sqlwhere = sqlwhere + " and datediff(day,''" + DateToStr(dtpend->Date) + "'',A.Hdtime) <= 0 ";
		}
		if (chclient->Checked && cbdanwei->Text != "") {
			try {
				sqlwhere = sqlwhere + " and A.supplierid = " + IntToStr((int)cbdanwei->Items->Objects[cbdanwei->ItemIndex]);
			} catch (...) {
				MessageBoxA(0,"��ѡ����ȷ�ĵ�λ����!","��ʾ",MB_ICONEXCLAMATION||MB_OK);
				return;
			}
		}
		if (chstate->Checked ) {
			sqlwhere = sqlwhere + " and A.cwstate = " + IntToStr(cbstate->ItemIndex);
		}
		if (chfapiao->Checked ) {
			sqlwhere = sqlwhere + " and A.fapiao = " + IntToStr(cbfapiao->ItemIndex);
		}
		if (chshiyang->Checked ) {
			if (edmin->Text != "") {
				try {
					float dd = StrToFloat(edmin->Text);
				} catch (...) {
					MessageBox(0,"��������ȷ��ʵ��","��ʾ" ,MB_OK);
					return;
				}
				sqlwhere = sqlwhere + " and A.TotalDiscountedPrice >= " + edmin->Text ;
			}
			if (edmax->Text != "") {
				try {
					float dd = StrToFloat(edmax->Text);
				} catch (...) {
					MessageBox(0,"��������ȷ��ʵ��","��ʾ" ,MB_OK);
					return;
				}
				sqlwhere = sqlwhere + " and A.TotalDiscountedPrice <= " + edmax->Text ;
			}
		}
		if (ch1->Checked && !ch3->Checked  ) {
			sqlwhere = sqlwhere + " and A.StgNtCodeInt > 0 ";
		}
		if (ch1->Checked && ch3->Checked ) {

		}
		if (!ch1->Checked && ch3->Checked ) {
			sqlwhere = sqlwhere + " and A.TStgNtCodeInt > 0 ";
		}
		if (chjiekuan->Checked ) {
			switch (cbjiekuanstate->ItemIndex ) {
				case 0:   //δ���
					sqlwhere = sqlwhere + " and abs(A.NoChecked) >= 0.01 ";
					break;
				case 1:  //�ѽӲ���
					sqlwhere = sqlwhere + " and abs(A.Checked) >= 0.01 and abs(A.NoChecked) >= 0.01 ";
					break;
				case 2:  //δ���
					sqlwhere = sqlwhere + " and D.state = 0 and D.type = 1 and C.thistime > 0 ";
					break;
				case 3:
					sqlwhere = sqlwhere + " and abs(A.Checked) >= 0.01 and abs(A.NoChecked) < 0.01 ";
					break;
			default:
                ;
			}
		}
		if (chfapiaohao->Checked ) {
			sqlwhere = sqlwhere + " and A.fapiaotext like ''%" + edfapiaohao->Text.Trim() + "%''";
		}
		//sql =  sqlwhere;
			sql = "exec BS_GetduizhangInfo '" + sqlwhere+"'";
		sql1 =  "  select sum(A.TotalAmount) as TotalAmount,sum(A.TotalFixedPrice) as TotalFixedPrice,sum(A.TotalDiscountedPrice) as DiscountedPrice,sum(A.checked) as checked,sum(A.AddCosts) as AddCosts,sum(A.AddCosts + A.TotalDiscountedPrice) as totalyingfu,sum(A.nochecked) as " ;
		sql1 = sql1 + " nochecked from BS_StorageNoteHeader A left join (select * from FN_CUSEndMoneyDtails where type = 1) C ON C.stgntcode = A.StgNtCode "
				" left join FN_CUSEndMoneyDocuments D ON D.MoneyCode = C.EndMoneyDocumentID ";
		sql1 = sql1 + sqlwhere;

		sql2 = "select '�ϼ�' as '�ϼ�', sum(CCC.����) as '����',sum(CCC.����) as '����',sum(CCC.ʵ��) as 'ʵ��',sum(CCC.���ӷ���) as '���ӷ���',sum(CCC.totalyingfu) as totalyingfu,sum(CCC.�ѽ�) as '�ѽ�',sum(CCC.δ��) as 'δ��' from (" + sql + ") as CCC";

	}else
	{
		if (ChangeDisplay) {
			sql= " select distinct A.ID,cast (RANK() OVER(order by A.ID asc) as nvarchar(10)) as '���',dbo.uf_bs_getclientname(A.vendorID) as '�ͻ�����',A.wsaleNtCode as code,A.WsaleNtCodeStr as '����',CONVERT(varchar(12),A.Hdtime,111) as  '����'," ;
		}else
		{
			sql= " select distinct A.ID,cast (RANK() OVER(order by A.ID asc) as nvarchar(10)) as '���',dbo.uf_bs_getclientname(A.vendorID) as '�ͻ�����',A.wsaleNtCode as code,cast(A.wsaleNtCode as nvarchar(15)) as '����',CONVERT(varchar(12),A.Hdtime,111) as '����'," ;
		}
		sql = sql + " A.TotalAmount as '����',A.FixedPrice as '����',A.DiscountedPrice as 'ʵ��',A.AddCosts as '���ӷ���',A.AddCosts + A.DiscountedPrice as totalyingfu,A.checked  as '�ѽ�',A.nochecked as 'δ��', "
				" A.remarks as '��ע',case A.cwstate when 0 then 'δ����' else '��'  end  as '����״̬', "
				" A.duifangmoney as '�Է�����',A.hongcong as '���',A.cwbk, "
				" case when D.state = 0 and C.thistime > 0 then 'δ���' when abs(A.Checked) >= 0.01 and abs(A.NoChecked) < 0.01 then '�ѽ��' when abs(A.Checked) >= 0.01 and abs(A.NoChecked) >= 0.01 then '�ѽᲿ��' when  abs(A.Checked) < 0.01 and abs(A.NoChecked) >= 0.01 then 'δ���' end as '���״̬', "
				" case A.fapiao when 0 then 'δ��' else '��' end as '��Ʊ',A.fapiaotext, "
				" case when dbo.uf_bs_getjiekuancode(A.id,2) is null and A.Checked > 0 then '�ֳ����' else dbo.uf_bs_getjiekuancode(A.id,2) end as '����' from BS_WsaleNoteHeader A "
				" left join (select * from FN_CUSEndMoneyDtails where type = 2) C ON C.stgntcode = A.WsaleNtCode "
				" left join FN_CUSEndMoneyDocuments D ON D.MoneyCode = C.EndMoneyDocumentID ";

		sqlwhere = " where A.stgid = " + IntToStr(stgid) ;
		if (chstart->Checked) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpbegin->Date) + "',A.Hdtime) >= 0 ";
		}
		if (chend->Checked ) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',A.Hdtime) <= 0 ";
		}
		if (chclient->Checked && edtclient->Text != "") {
			sqlwhere = sqlwhere + " and A.vendorID in (select id from dbo.GetChild(" + IntToStr(ClientID) + ")) ";
		}
		if (chstate->Checked ) {
			sqlwhere = sqlwhere + " and A.cwstate = " + IntToStr(cbstate->ItemIndex);
		}
		if (chfapiao->Checked ) {
			sqlwhere = sqlwhere + " and A.fapiao = " + IntToStr(cbfapiao->ItemIndex);
		}
		if (chshiyang->Checked ) {
			if (edmin->Text != "") {
				try {
					float dd = StrToFloat(edmin->Text);
				} catch (...) {
					MessageBox(0,"��������ȷ��ʵ��","��ʾ" ,MB_OK);
					return;
				}
				sqlwhere = sqlwhere + " and A.FixedPrice >= " + edmin->Text ;
			}
			if (edmax->Text != "") {
				try {
					float dd = StrToFloat(edmax->Text);
				} catch (...) {
					MessageBox(0,"��������ȷ��ʵ��","��ʾ" ,MB_OK);
					return;
				}
				sqlwhere = sqlwhere + " and A.FixedPrice <= " + edmax->Text ;
			}
		}
		if (ch1->Checked && !ch3->Checked  ) {
			sqlwhere = sqlwhere + " and A.WsaleNtCodeInt > 0 ";
		}
		if (ch1->Checked && ch3->Checked ) {

		}
		if (!ch1->Checked && ch3->Checked ) {
			sqlwhere = sqlwhere + " and A.TWsaleNtCodeInt > 0 ";
		}
		if (ch2->Checked ) {
        	sqlwhere = sqlwhere + " and A.state = 2 ";
		}
		if (chjiekuan->Checked ) {
			switch (cbjiekuanstate->ItemIndex ) {
				case 0:   //δ���
					sqlwhere = sqlwhere + " and abs(A.NoChecked) >= 0.01 ";
					break;
				case 1:  //�ѽӲ���
					sqlwhere = sqlwhere + " and abs(A.Checked) >= 0.01 and abs(A.NoChecked) >= 0.01 ";
					break;
				case 2:  //δ���
					sqlwhere = sqlwhere + " and D.state = 0 and D.type = 2 and C.thistime > 0 ";
					break;
				case 3:
					sqlwhere = sqlwhere + " and abs(A.Checked) >= 0.01 and abs(A.NoChecked) < 0.01 ";
					break;
			default:
                ;
			}
		}
		if (chfapiaohao->Checked ) {
			sqlwhere = sqlwhere + " and A.fapiaotext like '%" + edfapiaohao->Text.Trim() + "%'";
		}

		sql = sql+sqlwhere;
		sql2 = "select '�ϼ�' as '�ϼ�', sum(CCC.����) as '����',sum(CCC.����) as '����',sum(CCC.ʵ��) as 'ʵ��',sum(CCC.���ӷ���) as '���ӷ���',sum(CCC.totalyingfu) as totalyingfu,sum(CCC.�ѽ�) as '�ѽ�',sum(CCC.δ��) as 'δ��' from (" + sql + ") as CCC";

		sql1 = " select sum(A.TotalAmount) as TotalAmount,sum(A.fixedprice) as TotalFixedPrice,sum(A.DiscountedPrice) as DiscountedPrice,sum(A.AddCosts) as AddCosts,sum(A.AddCosts + A.DiscountedPrice) as totalyingfu,sum(A.checked) as checked,sum(A.nochecked) as " ;
		sql1 = sql1 + " nochecked from BS_WsaleNoteHeader A left join (select * from FN_CUSEndMoneyDtails where type = 2) C ON C.stgntcode = A.WsaleNtCode "
				" left join FN_CUSEndMoneyDocuments D ON D.MoneyCode = C.EndMoneyDocumentID " ;
		sql1 = sql1 + sqlwhere;
	}

	if (Client== 1)
	{
	int i;
	AnsiString code;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

  //	adosp->ProcedureName="BS_GetduizhangInfo";
			   //
   //  adosp->Parameters->Refresh();
   //		adosp->Parameters->ParamByName("@wherestr")->Value=sqlwhere;
   //	adosp->ExecProc();
 adoquerymain->Recordset =query->Recordset;
 code = adoquerymain->FieldByName("code")->AsAnsiString;
	query2->Recordset=  query->NextRecordset(i);



	}else
	{
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	query->First();


	query2->Close();
	query2->SQL->Clear();
	query2->SQL->Add(sql2);
	query2->Open();



	}

	if (Client == 1) {
		dg->Columns->Items[2]->Field = query->FieldByName("��Ӧ������");
	}
	else
	{
		dg->Columns->Items[2]->Field = query->FieldByName("�ͻ�����");
	}

	((TFloatField *)query->FieldByName("����"))->DisplayFormat = "###,###,##" + format ;
	((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat = "###,###,##" + format ;
	((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat = "###,###,##" + format ;
	((TFloatField *)query->FieldByName("δ��"))->DisplayFormat = "###,###,##" + format ;
	((TFloatField *)query->FieldByName("���ӷ���"))->DisplayFormat = "###,###,##" + format ;
	((TFloatField *)query->FieldByName("totalyingfu"))->DisplayFormat = "###,###,##" + format ;
	((TFloatField *)query->FieldByName("����"))->DisplayFormat = "###,###,##0" ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",userInfo.storageID);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		cbdanwei->ItemIndex = cbdanwei->Items->IndexOfObject((TObject*)ClientID);
		ClientView();
		GetClientDetail(ClientID);
	}
	delete frm;
}
//---------------------------------------------------------------------------
void Tfrmwanglaizhang::ClientView()
{
	if (ClientID == -1) {
		return;
	}
	AnsiString sql;
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

void __fastcall Tfrmwanglaizhang::N1Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= dg->DataSource->DataSet->RecordCount; i++) {
		dg->DataSource->DataSet->RecNo = i;
		dg->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::N2Click(TObject *Sender)
{
	N2->Checked = true;
	N3->Checked = false;
	BtnNextRecord->Caption = "���ݷ�Ʊ[F4]";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::N3Click(TObject *Sender)
{
	N2->Checked = false;
	N3->Checked = true;
	BtnNextRecord->Caption = "ȡ�����ݷ�Ʊ[F4]";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::N4Click(TObject *Sender)
{
	N4->Checked = true;
	N5->Checked = false;
	BtnProperties->Caption = "����[F3]";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::N5Click(TObject *Sender)
{
	N4->Checked = false;
	N5->Checked = true;
	BtnProperties->Caption = "ȡ������[F3]";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::BtnPropertiesClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
        return;
	}
	AnsiString ids,sql;
	if (dg->SelectedRows->Count == 0)
	{
		ids = ids + query->FieldByName("ID")->AsString;
	}
	else if (dg->SelectedRows->Count > 0)
	{
		query->Bookmark = dg->SelectedRows->Items[0];
		ids = query->FieldByName("ID")->AsString;
		for (int i=1; i < dg->SelectedRows->Count; i++)
		{
			query->Bookmark = dg->SelectedRows->Items[i];
			ids = ids + "," + query->FieldByName("ID")->AsString;
		}
	}
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	if (BtnProperties->Caption == "����[F3]") {
		if (Client == 1) {
			sql = "update BS_StorageNoteHeader set cwstate = 1 where id in(" + ids + ")";
		}
		else
		{
			sql = "update BS_WsaleNoteHeader set cwstate = 1 where id in(" + ids + ")";
		}
	}
	if (BtnProperties->Caption == "ȡ������[F3]") {
		if (Client == 1) {
			sql = "update BS_StorageNoteHeader set cwstate = 0 where id in(" + ids + ")";
		}
		else
		{
			sql = "update BS_WsaleNoteHeader set cwstate = 0 where id in(" + ids + ")";
		}
	}

	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = query->FieldByName("ID")->AsString;

	query->Active = false;
	query->Active = true;
	if (Client == 1 ) { //��Ӧ��
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;

	} else
	{
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;
	}
	query->Locate("ID",str,Opts);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::BtnNextRecordClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	AnsiString ids,sql;
	if (dg->SelectedRows->Count == 0)
	{
		ids = ids + query->FieldByName("ID")->AsString;
	}
	else if (dg->SelectedRows->Count > 0)
	{
		query->Bookmark = dg->SelectedRows->Items[0];
		ids = query->FieldByName("ID")->AsString;
		for (int i=1; i < dg->SelectedRows->Count; i++)
		{
			query->Bookmark = dg->SelectedRows->Items[i];
			ids = ids + "," + query->FieldByName("ID")->AsString;
		}
	}
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	if (BtnNextRecord->Caption == "���ݷ�Ʊ[F4]") {
		if (Client == 1) {
			sql = "update BS_StorageNoteHeader set fapiao = 1 where id in(" + ids + ")";
		}
		else
		{
			sql = "update BS_WsaleNoteHeader set fapiao = 1 where id in(" + ids + ")";
		}
	}
	else{
		if (Client == 1) {
			sql = "update BS_StorageNoteHeader set fapiao = 0 where id in(" + ids + ")";
		}
		else
		{
			sql = "update BS_WsaleNoteHeader set fapiao = 0 where id in(" + ids + ")";
		}
	}

	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = query->FieldByName("ID")->AsString;

	query->Active = false;
	query->Active = true;
	if (Client == 1 ) { //��Ӧ��
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;

	} else
	{
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;
	}
	query->Locate("ID",str,Opts);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::BtnExportClick(TObject *Sender)
{
	DbgridToExcel(dg);
}

//---------------------------------------------------------------------------

//Excel��������
bool Tfrmwanglaizhang::DbgridToExcel(TDBGrid* dbg)
{
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

	int t1= 0;
	for(int q=0;q<dbg->Columns ->Count ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
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
				if (dbg->Columns ->Items [j-1]->FieldName == "����") {
					if (dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString != "") {
						temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
					else
					{
                    	temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
				}
				else
				{
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();

	FileClose(iFileHandle);

	MessageBox(0,"������ϣ�","��ʾ" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmwanglaizhang::cbstateChange(TObject *Sender)
{
	if (cbstate->Text != "") {
		chstate->Checked = true;
	}
	else
	{
    	chstate->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::cbjiekuanstateChange(TObject *Sender)
{
	if (cbjiekuanstate->Text != "") {
		chjiekuan->Checked = true;
	}
	else
	{
    	chjiekuan->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::cbfapiaoChange(TObject *Sender)
{
	if (cbfapiao->Text != "") {
		chfapiao->Checked = true;
	}
	else
	{
		chfapiao->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::dtpbeginChange(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::edfapiaohaoChange(TObject *Sender)
{
	if (edfapiaohao->Text != "") {
		chfapiaohao->Checked = true;
	}
	else
	{
    	chfapiaohao->Checked = false;
	}
}
//---------------------------------------------------------------------------



void __fastcall Tfrmwanglaizhang::FormShow(TObject *Sender)
{
	editjianshuo->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::edtclientChange(TObject *Sender)
{
	if (edtclient->Text != "") {
		chclient->Checked = true;
	}
	else
	{
        chclient->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::cbdanweiChange(TObject *Sender)
{
	if (cbdanwei->Text != "") {
		chclient->Checked = true;
	}
	else
	{
    	chclient->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::edminKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::edminChange(TObject *Sender)
{
	if (edmin->Text != "") {
		chshiyang->Checked = true;
	}
	else if (edmax->Text != "") {
		chshiyang->Checked = true;
	}
	else
	{
		chshiyang->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::queryAfterPost(TDataSet *DataSet)
{
	try {
    	TLocateOptions   Opts;
		Opts.Clear();
		Opts   <<   loPartialKey;
		String   str   = query->FieldByName("ID")->AsAnsiString ;
		query->Active = false;
		query->Active = true;
		query->Locate("ID",str,Opts);
	} catch (...) {
	}
}
//---------------------------------------------------------------------------



void __fastcall Tfrmwanglaizhang::dgMouseLeave(TObject *Sender)
{
	if (!query->IsEmpty()  && query->State == dsEdit ) {
		try {
			query->Post();
		} catch (...) {
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::dgTitleClick(TColumn *Column)
{
	if (query->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (query->Sort == "") {
		query->Sort =  Column->FieldName + " ASC";
	}
	else if (query->Sort == qusort) {
		query->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		query->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::dgDblClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	if (query->RecordCount > 0) {
		AnsiString code;
		code = query->FieldByName("code")->AsAnsiString;
		TfrmNotedetail *frm = new TfrmNotedetail(Application,code,Client,fcon,0,userInfo.userID);
		frm->ShowModal();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::N6Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	Tfrmunitfapiao * frm = new Tfrmunitfapiao(Application);
	if (frm->ShowModal() == mrOk )
	{
		AnsiString ids,sql;
		if (dg->SelectedRows->Count == 0)
		{
			ids = ids + query->FieldByName("ID")->AsString;
		}
		else if (dg->SelectedRows->Count > 0)
		{
			query->Bookmark = dg->SelectedRows->Items[0];
			ids = query->FieldByName("ID")->AsString;
			for (int i=1; i < dg->SelectedRows->Count; i++)
			{
				query->Bookmark = dg->SelectedRows->Items[i];
				ids = ids + "," + query->FieldByName("ID")->AsString;
			}
		}
		TADOQuery * aq = new TADOQuery(NULL);
		aq->Connection = fcon;
		if (Client == 1) {
			sql = "update BS_StorageNoteHeader set fapiaotext = '" + frm->ed->Text.Trim() + "' where id in(" + ids + ")";
		}
		else
		{
			sql = "update BS_WsaleNoteHeader set fapiaotext = '" + frm->ed->Text.Trim() + "' where id in(" + ids + ")";
		}

		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
		TLocateOptions   Opts;
		Opts.Clear();
		Opts   <<   loPartialKey;
		String   str   = query->FieldByName("ID")->AsString;

		query->Active = false;
		query->Active = true;
		if (Client == 1 ) { //��Ӧ��
			((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;

		} else
		{
			((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;
		}
		query->Locate("ID",str,Opts);
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::dgDrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (query->FieldByName("��Ʊ")->AsString  == "��" ) {
		dg->Canvas->FillRect(Rect);
		dg->Canvas->Font->Color  = clRed;
		dg->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
	else if (query->FieldByName("����״̬")->AsString  == "��" ) {
		dg->Canvas->FillRect(Rect);
		dg->Canvas->Font->Color  = clGreen;
		dg->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::N7Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	Tfrmunitfapiao * frm = new Tfrmunitfapiao(Application);
	frm->Caption = "ͳһ�ۿ�";
	frm->Label1->Caption = "�ۿ�";
	if (frm->ShowModal() == mrOk )
	{
		AnsiString ids = "-1",sql;
		if (dg->SelectedRows->Count == 0)
		{
			if (query->FieldByName("����״̬")->AsAnsiString != "��" ) {
				ids = ids + "," + query->FieldByName("ID")->AsString;
			}
		}
		else if (dg->SelectedRows->Count > 0)
		{
			query->Bookmark = dg->SelectedRows->Items[0];
			if (query->FieldByName("����״̬")->AsAnsiString != "��" ) {
				ids = ids + "," + query->FieldByName("ID")->AsString;
			}

			for (int i=1; i < dg->SelectedRows->Count; i++)
			{
				query->Bookmark = dg->SelectedRows->Items[i];
				if (query->FieldByName("����״̬")->AsAnsiString != "��" ) {
					ids = ids + "," + query->FieldByName("ID")->AsString;
				}
			}
		}
		TADOQuery * aq = new TADOQuery(NULL);
		aq->Connection = fcon;
		if (Client == 1) {
			sql = "update BS_StorageNote set Discount = " + frm->ed->Text.Trim() + " where StgNtHeaderID in(" + ids + ")";
		}
		else
		{
			sql = "update BS_WsaleNote set Discount = " + frm->ed->Text.Trim() + " where WsaleNtHeaderID in(" + ids + ")";
		}

		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
		TLocateOptions   Opts;
		Opts.Clear();
		Opts   <<   loPartialKey;
		String   str   = query->FieldByName("ID")->AsString;

		query->Active = false;
		query->Active = true;
		if (Client == 1 ) { //��Ӧ��
			((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;

		} else
		{
			((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;
		}
		query->Locate("ID",str,Opts);
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwanglaizhang::N8Click(TObject *Sender)
{
		if (query->IsEmpty() ) {
		return;
	}
	Tfrmunitfapiao * frm = new Tfrmunitfapiao(Application);
	frm->Caption = "����ע";
	frm->Label1->Caption = "����ע";
	if (frm->ShowModal() == mrOk )
	{
		AnsiString ids = "-1",sql;
		if (dg->SelectedRows->Count == 0)
		{
			ids = ids + "," + query->FieldByName("ID")->AsString;

		}
		else if (dg->SelectedRows->Count > 0)
		{
			query->Bookmark = dg->SelectedRows->Items[0];
				ids = ids + "," + query->FieldByName("ID")->AsString;


			for (int i=1; i < dg->SelectedRows->Count; i++)
			{
				query->Bookmark = dg->SelectedRows->Items[i];
				ids = ids + "," + query->FieldByName("ID")->AsString;

			}
		}
		TADOQuery * aq = new TADOQuery(NULL);
		aq->Connection = fcon;

			sql = "update BS_StorageNoteHeader set cwbk = '" + frm->ed->Text.Trim() + "' where id in(" + ids + ")";


		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
		TLocateOptions   Opts;
		Opts.Clear();
		Opts   <<   loPartialKey;
		String   str   = query->FieldByName("ID")->AsString;


		BtnView->Click();
		if (Client == 1 ) { //��Ӧ��
			((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;

		} else
		{
			((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
			((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;
		}
		query->Locate("ID",str,Opts);
	}
	delete frm;
}
//---------------------------------------------------------------------------
