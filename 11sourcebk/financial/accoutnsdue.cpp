//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "accoutnsdue.h"
#include "..\bsadmin\UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBGrid"
#pragma link "RzCmboBx"
#pragma link "RpBase"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpSystem"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "DataDriverEh"
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma resource "*.dfm"
TAccountDoe *AccountDoe;
//---------------------------------------------------------------------------
__fastcall TAccountDoe::TAccountDoe(TComponent* Owner,int Type,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
	type = Type;
	fcon = cn;
	aqcustom->Connection = cn;
	aquery->Connection = cn;
	fstgid =stgid;
	if (type == 1) {
	   this->Caption = "Ӧ������";
	   spselectClient->Visible = false;
	   edtclient->Visible = false;
	}
	else
	{
        Label2->Caption = "Ӧ�ջ���";
		cbCusName->Visible = false;
		chhuizong->Visible = true;
		chprofite->Visible = true;
	}
	Disc = "###,###,##0.00";
	DTPstart->Date = Date();
	DTPend->Date = Date();
	ClientID = -1;
}
//---------------------------------------------------------------------------
void __fastcall TAccountDoe::FormShow(TObject *Sender)
{
	cbInOut->Text = "ȫ��";
	cbInOut->Add("ȫ��");
	cbInOut->Add("����");
	cbInOut->Add("�˻�");
	AnsiString sql ;
	if (type == 1) {
		sql = "select ID,Name from CUST_CustomerInfo where Type = 1 and name <> '' order by name";
	}
	else
	{
		sql = "select ID,Name from CUST_CustomerInfo where Type in(2,3) and name <> '' order by name";
	}
	aqcustom->Close();
	aqcustom->SQL->Clear();
	aqcustom->SQL->Add(sql);
	aqcustom->Open();
	aqcustom->First();
	while (!aqcustom->Eof ) {
		cbCusName->AddItem(aqcustom->FieldByName("Name")->AsString ,(TObject*)aqcustom->FieldByName("ID")->AsInteger);
		aqcustom->Next();
	}
	if (type == 1) {
		DBGridtotal->Columns->Items[1]->Title->Caption = "��Ӧ������";
		DBGridtotal->Columns->Items[10]->Visible = false;
		DBGridtotal->Columns->Items[11]->Visible = false;
	}
	else if (type == 2) {
		chname->Caption = "�ͻ�";
		DBGridtotal->Columns->Items[1]->Title->Caption = "�ͻ�����";
		DBGridtotal->Columns->Items[6]->Title->Caption = "��Ӧ��";
		DBGridtotal->Columns->Items[9]->Visible = false;
	}
	edquery->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TAccountDoe::BtnViewClick(TObject *Sender)
{
	AnsiString sql ,sqlwhere,sqladd;
	int clientid;

	if (type == 1) {
		sql = "select cast(rank() over(order by CUST_CustomerInfo.ID) as nvarchar(10)) as xuhao,sum(BS_StorageNoteHeader.TotalFixedPrice) as sumFixedPrice,sum(BS_StorageNoteHeader.TotalDiscountedPrice) as sumDiscountedPrice, "
				" sum(BS_StorageNoteHeader.TotalAmount) as sumTotalAmount,sum(BS_StorageNoteHeader.AddCosts) as sumAddCosts,sum(BS_StorageNoteHeader.AddCosts + BS_StorageNoteHeader.TotalDiscountedPrice) as totalyingfu, "
				" sum(BS_StorageNoteHeader.Checked) as sumChecked,sum(BS_StorageNoteHeader.Nochecked) as sumNochecked, "
				" case when sum(BS_StorageNoteHeader.TotalFixedPrice) <> 0 then sum(BS_StorageNoteHeader.TotalDiscountedPrice)*100/sum(BS_StorageNoteHeader.TotalFixedPrice) else 0 end as discount, "
				" CUST_CustomerInfo.name as clientname,CuST_CustomerInfo.ID,(CUST_CustomerStartMoney.balance + CUST_CustomerStartMoney.totalyue) as totalyue,0 as profite,0 as cbprice  from BS_StorageNoteHeader inner join CUST_CustomerInfo "
				" on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.ID "
				" left join CUST_CustomerStartMoney on BS_StorageNoteHeader.SupplierID = CUST_CustomerStartMoney.CustomerID ";
		 sqlwhere = " where BS_StorageNoteHeader.state <> 2 and CUST_CustomerInfo.Type = 1";
	}
	else
	{
		if (chhuizong->Checked ) {
			sql = "select cast(rank() over(order by CUST_CustomerInfo.PrentID) as nvarchar(10)) as xuhao,CUST_CustomerInfo.PrentID as id ,dbo.uf_bs_getclientname(CuST_CustomerInfo.PrentID) as clientname,";
		}
		else
		{
			sql = "select cast(rank() over(order by CUST_CustomerInfo.ID) as nvarchar(10)) as xuhao,CuST_CustomerInfo.ID ,dbo.uf_bs_getclientname(CuST_CustomerInfo.ID) as clientname,";
		}
		sql = sql + " sum(BS_WsaleNoteHeader.FixedPrice) as sumFixedPrice, "
				" sum(BS_WsaleNoteHeader.DiscountedPrice) as sumDiscountedPrice,sum(BS_WsaleNoteHeader.TotalAmount) as sumTotalAmount, "
				" sum(BS_WsaleNoteHeader.AddCosts) as sumAddCosts,sum(BS_WsaleNoteHeader.AddCosts) + sum(BS_WsaleNoteHeader.DiscountedPrice) as totalyingfu,sum(BS_WsaleNoteHeader.Checked) as sumChecked, "
				" sum(BS_WsaleNoteHeader.Nochecked) as sumNochecked,(CUST_CustomerStartMoney.balance + CUST_CustomerStartMoney.totalyue) as totalyue , ";
		if (chprofite->Checked) {
			sql = sql + " sum(dbo.UF_BS_Getwsaleprofite(BS_WsaleNoteHeader.id)) as profite,sum(BS_WsaleNoteHeader.DiscountedPrice - dbo.UF_BS_Getwsaleprofite(BS_WsaleNoteHeader.id)) as cbprice, ";
		}
		else
		{
			sql = sql + " 0 as profite,0 as cbprice, ";
		}
		sql = sql + " 0 as discount from BS_WsaleNoteHeader inner join CUST_CustomerInfo   on BS_WsaleNoteHeader.VendorID = CUST_CustomerInfo.ID  "
				" left join CUST_CustomerStartMoney on BS_WsaleNoteHeader.VendorID = CUST_CustomerStartMoney.CustomerID  " ;
		sqlwhere = " where BS_WsaleNoteHeader.state <> 2 and CUST_CustomerInfo.Type in(2,3)";
	}
	if (type == 1) {
		if (chname->Checked && cbCusName->Text != "") {
        	try {
				clientid = (int)cbCusName->Items->Objects[cbCusName->ItemIndex];
			} catch (...) {
				MessageBox(0,"��ѡ����ȷ�ĵ�λ��","��ʾ" ,MB_OK);
				return;
			}
			sqlwhere = sqlwhere + " and CUST_CustomerInfo.ID in (select ID from GetChild(" + IntToStr(clientid) + "))";
		}
	}
	else
	{
		if (chname->Checked && edtclient->Text != "") {
			sqlwhere = sqlwhere + " and CUST_CustomerInfo.ID in (select ID from GetChild(" + IntToStr(ClientID) + "))";
		}
	}
	if (type == 1) {
		if (CBstart->Checked ) {
			sqlwhere = sqlwhere + " and BS_StorageNoteHeader.HdTime >='" + DateToStr(DTPstart->Date) + " 0:00:00'";
		}
		if (CBend->Checked ) {
			sqlwhere = sqlwhere + " and BS_StorageNoteHeader.HdTime <='" + DateToStr(DTPend->Date) + " 23:59:59'" ;
		}
		if (cbInOut->Text == "����") {
			sqlwhere = sqlwhere + " and BS_StorageNoteHeader.TotalAmount>=0 ";
		}
		if (cbInOut->Text == "�˻�") {
			sqlwhere = sqlwhere + " and BS_StorageNoteHeader.TotalAmount<0 " ;
		}
	}
	else
	{
		if (CBstart->Checked ) {
			sqlwhere = sqlwhere +   " and BS_WsaleNoteHeader.HdTime >='" + DateToStr(DTPstart->Date) + " 0:00:00'";
		}
		if (CBend->Checked ) {
			sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.HdTime <='" + DateToStr(DTPend->Date) + " 23:59:59'" ;
		}
		if (cbInOut->Text == "����") {
			sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.TotalAmount>=0 ";
		}
		if (cbInOut->Text == "�˻�") {
			sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.TotalAmount<0 " ;
		}
	}
	if (chhuizong->Checked ) {
		sql = sql +  sqlwhere + " group by CUST_CustomerInfo.PrentID,CUST_CustomerStartMoney.balance, CUST_CustomerStartMoney.totalyue ";
	}
	else
	{
		sql = sql +  sqlwhere + " group by CUST_CustomerInfo.name,CUST_CustomerInfo.ID,CUST_CustomerStartMoney.balance, CUST_CustomerStartMoney.totalyue ";
	}
	/*if (type == 1 ) {
		sql = sql + " union "
					" select '�ϼ�',sum(BS_StorageNoteHeader.TotalFixedPrice) as sumFixedPrice,sum(BS_StorageNoteHeader.TotalDiscountedPrice) as sumDiscountedPrice, "
					" sum(BS_StorageNoteHeader.TotalAmount) as sumTotalAmount,sum(BS_StorageNoteHeader.AddCosts) as sumAddCosts,sum(BS_StorageNoteHeader.AddCosts) + sum(BS_StorageNoteHeader.TotalDiscountedPrice) as totalyingfu, "
					" sum(BS_StorageNoteHeader.Checked) as sumChecked,sum(BS_StorageNoteHeader.Nochecked) as sumNochecked, "
					" case when sum(BS_StorageNoteHeader.TotalFixedPrice) <> 0 then sum(BS_StorageNoteHeader.TotalDiscountedPrice)*100/sum(BS_StorageNoteHeader.TotalFixedPrice) else 0 end as discount, "
					" null,999999999,(CUST_CustomerStartMoney.balance + CUST_CustomerStartMoney.totalyue) as totalyue,0 from BS_StorageNoteHeader inner join CUST_CustomerInfo "
					" on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.ID "
					" left join CUST_CustomerStartMoney on BS_StorageNoteHeader.SupplierID = CUST_CustomerStartMoney.CustomerID " ;
	}
	else
	{
		sql = sql + " union "
					" select '�ϼ�',999999999,null,sum(BS_WsaleNoteHeader.FixedPrice) as sumFixedPrice, "
					" sum(BS_WsaleNoteHeader.DiscountedPrice) as sumDiscountedPrice,sum(BS_WsaleNoteHeader.TotalAmount) as sumTotalAmount, "
					" sum(BS_WsaleNoteHeader.AddCosts) as sumAddCosts,sum(BS_WsaleNoteHeader.AddCosts) + sum(BS_WsaleNoteHeader.DiscountedPrice) as totalyinghu,sum(BS_WsaleNoteHeader.Checked) as sumChecked, "
					" sum(BS_WsaleNoteHeader.Nochecked) as sumNochecked,(CUST_CustomerStartMoney.balance + CUST_CustomerStartMoney.totalyue) as totalyue , " ;
		if (chprofite->Checked ) {
			sql = sql + " sum(dbo.UF_BS_Getwsaleprofite(BS_WsaleNoteHeader.id)) as profite,sum(BS_WsaleNoteHeader.DiscountedPrice - dbo.UF_BS_Getwsaleprofite(BS_WsaleNoteHeader.id)) as cbprice ";
			DBGridtotal->Columns->Items[10]->Visible = true;
			DBGridtotal->Columns->Items[11]->Visible = true;
		}
		else
		{
			sql = sql + " 0 as profite,0 as cbprice, ";
			DBGridtotal->Columns->Items[10]->Visible = false;
			DBGridtotal->Columns->Items[11]->Visible = false;
		}
		sql = sql + " 0 from BS_WsaleNoteHeader inner join CUST_CustomerInfo   on BS_WsaleNoteHeader.VendorID = CUST_CustomerInfo.ID "
					" left join CUST_CustomerStartMoney on BS_WsaleNoteHeader.VendorID = CUST_CustomerStartMoney.CustomerID ";
	}   */
	sql = sql + " order by id asc";
	//sql = sql + sqlwhere + " group by CUST_CustomerStartMoney.Balance,CUST_CustomerStartMoney.totalyue order by id asc";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("totalyue"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("sumFixedPrice"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("sumDiscountedPrice"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("totalyingfu"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("sumAddCosts"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("sumChecked"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("sumNochecked"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("sumTotalAmount"))->DisplayFormat = "###,###,##0";
	if (type == 1) {
		((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("discount"))->DisplayFormat = Disc+"%";
	}
	else
	{
		((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("cbprice"))->DisplayFormat = Disc;
		((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("profite"))->DisplayFormat = Disc;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAccountDoe::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------



void __fastcall TAccountDoe::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree ;
}
//---------------------------------------------------------------------------


void __fastcall TAccountDoe::BtnExportClick(TObject *Sender)
{
	if (aquery->IsEmpty() ) {
		return;
	}
	DbgridToExcel(DBGridtotal);
}
//---------------------------------------------------------------------------

bool __fastcall TAccountDoe::DbgridToExcel(TDBGridEh* dbg)
{

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
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	aquery->DisableControls();
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
	aquery->EnableControls();

	FileClose(iFileHandle);

	MessageBox(0,"������ϣ�","��ʾ" ,MB_OK);
	return false;

}
//---------------------------------------------------------------------------


void __fastcall TAccountDoe::BtnPrintClick(TObject *Sender)
{
	if (aquery->IsEmpty() ) {
		return;
	}


	RvSystem1->SystemSetups >>ssAllowSetup;
	RvSystem1->SystemSetups >>ssAllowDestPreview;
	RvSystem1->SystemSetups >>ssAllowDestPrinter;
	RvSystem1->SystemSetups >>ssAllowPrinterSetup;
	RvSystem1->SystemSetups >>ssAllowDestFile;
	RvSystem1->DefaultDest  = rdPrinter ;
	RvSystem1->SystemSetups<<ssAllowDestPreview;
	if (type == 1) {
		RvProject1->ProjectFile = ExtractFilePath(Application->ExeName) + "accoutnsdue.rav";
	}
	else
	{
		RvProject1->ProjectFile = ExtractFilePath(Application->ExeName) + "accoutnsdueclient.rav";
	}
	RvProject1->Open();
	String str =  stogName + this->Caption;
	RvProject1->SetParam("title",str);
	if (type == 1) {
		RvProject1->SetParam("suppliername",cbCusName->Text);
	}
	else
	{
		RvProject1->SetParam("suppliername",edtclient->Text);
	}
	//RvProject1->SetParam("suppliername",cbCusName->Text);
	if (CBstart->Checked) {
		RvProject1->SetParam("starttime",DateToStr(DTPstart->Date));
	}
	if (CBend->Checked) {
		RvProject1->SetParam("endtime",DateToStr(DTPend->Date));
	}
	RvProject1->SetParam("jingchu",cbInOut->Text);
	RvProject1->SetParam("user",username);
	RvProject1->SetParam("Name",DBGridtotal->Columns->Items[0]->Title->Caption);
	RvProject1->Execute();
	RvProject1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TAccountDoe::BtnPrintPreviewClick(TObject *Sender)
{
	if (aquery->IsEmpty() ) {
		return;
	}


	RvSystem1->SystemSetups >>ssAllowSetup;
	RvSystem1->SystemSetups >>ssAllowDestPreview;
	RvSystem1->SystemSetups >>ssAllowDestPrinter;
	RvSystem1->SystemSetups >>ssAllowPrinterSetup;
	RvSystem1->SystemSetups >>ssAllowDestFile;
	RvSystem1->DefaultDest  = rdPreview ;
	RvSystem1->SystemSetups<<ssAllowDestPreview;

	if (type == 1) {
		RvProject1->ProjectFile = ExtractFilePath(Application->ExeName) + "accoutnsdue.rav";
	}
	else
	{
		RvProject1->ProjectFile = ExtractFilePath(Application->ExeName) + "accoutnsdueclient.rav";
	}
	RvProject1->Open();
	AnsiString str =  this->Caption;
	str = stogName + str;
	RvProject1->SetParam("title",str);
	if (type == 1) {
		RvProject1->SetParam("suppliername",cbCusName->Text);
	}
	else
	{
		RvProject1->SetParam("suppliername",edtclient->Text);
	}

	if (CBstart->Checked) {
		RvProject1->SetParam("starttime",DateToStr(DTPstart->Date));
	}
	if (CBend->Checked) {
		RvProject1->SetParam("endtime",DateToStr(DTPend->Date));
	}
	RvProject1->SetParam("jingchu",cbInOut->Text);
	RvProject1->SetParam("user",username);
	RvProject1->SetParam("Name",DBGridtotal->Columns->Items[0]->Title->Caption);
	RvProject1->Execute();
	RvProject1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TAccountDoe::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString sql;
		if (type == 1) {
			sql = "select ID,Name from CUST_CustomerInfo where type = 1 and Name like '%" + edquery->Text + "%' and name <> '' ";
        	aqcustom->Close();
			aqcustom->SQL->Clear();
			aqcustom->SQL->Add(sql);
			aqcustom->Open();
			cbCusName->Clear();
			while (!aqcustom->Eof )
			{
				cbCusName->AddItem(aqcustom->FieldByName("Name")->AsString ,(TObject*)aqcustom->FieldByName("ID")->AsInteger);
				aqcustom->Next();
			}
			aqcustom->First();
			cbCusName->ItemIndex = cbCusName->Items->IndexOfObject((TObject*)aqcustom->FieldByName("ID")->AsInteger);
		}
		else
		{
			TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edquery->Text,fstgid);
			if (mrOk == frm->ShowModal())
			{
				ClientID = frm->GetSelectID();
				cbCusName->ItemIndex = cbCusName->Items->IndexOfObject((TObject*)ClientID);
				ClientView();
			}
			delete frm;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TAccountDoe::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TAccountDoe::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F6 ) {    //����
		BtnExport->Click();
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

void __fastcall TAccountDoe::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",fstgid);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		cbCusName->ItemIndex = cbCusName->Items->IndexOfObject((TObject*)ClientID);
		ClientView();
	}
	delete frm;
}
//---------------------------------------------------------------------------
void TAccountDoe::ClientView()
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

void __fastcall TAccountDoe::DTPstartChange(TObject *Sender)
{
	CBstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TAccountDoe::DTPendChange(TObject *Sender)
{
	CBend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TAccountDoe::DBGridtotalTitleClick(TColumnEh *Column)
{
	if (aquery->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aquery->Sort == "") {
		aquery->Sort =  Column->FieldName + " ASC";
	}
	else if (aquery->Sort == qusort) {
		aquery->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aquery->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

