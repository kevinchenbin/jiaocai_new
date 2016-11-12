//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitcaigouquery.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmcaigouquery *frmcaigouquery;
//---------------------------------------------------------------------------
__fastcall Tfrmcaigouquery::Tfrmcaigouquery(TComponent* Owner,TADOConnection *con,int stgid,int modle,int tuihuo)
	: TForm(Owner)
{
	fstgid = stgid;
	fcon = con;
	fmodle = modle;
	ftuihuo = tuihuo;
	query->Connection = con;
	dtpstart->Date = Date();
	dtpend->Date = Date();
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	AnsiString sql;
	sql = "select ID,Name from CUST_CustomerInfo where type = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	aq->First();
	cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );

	sql = "select ID,Name from sys_user where stgid = " + IntToStr(fstgid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbuser->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	aq->First();
	cbuser->ItemIndex = cbuser->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );

    sql = "select * from SYS_BSSET where name = 'changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	ChangeDisplay  = aq->FieldByName("value")->AsBoolean ;

	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouquery::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type = 1 and Name like '%" + edclient->Text + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
        cbsupplier->Clear();
		while (!aq->Eof )
		{
			cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcaigouquery::Button2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcaigouquery::Button1Click(TObject *Sender)
{
	AnsiString sql;

	if (fmodle == 1) {
		sql = "select BS_ProcureNoteHeader.ProcureNtCode as NtCode,convert(nvarchar(10),HdTime,120) as HdTime,CUST_CustomerInfo.Name as clientname,BS_ProcureNoteHeader.TotalAmount,BS_ProcureNoteHeader.FixedPrice,BS_ProcureNoteHeader.DiscountedPrice from BS_ProcureNoteHeader left join CUST_CustomerInfo on BS_ProcureNoteHeader.SupplierID = CUST_CustomerInfo.id ";
		sqlwhere = " where BS_ProcureNoteHeader.StgID = " + IntToStr(fstgid);
	}
	else
	{
		if (ChangeDisplay) {
			sql = "select BS_StorageNoteHeader.StgNtCodeStr as NtCode,BS_StorageNoteHeader.StgNtCode,convert(nvarchar(10),HdTime,120) as HdTime,CUST_CustomerInfo.Name as clientname, ";
			sql = sql+	  " BS_StorageNoteHeader.TotalAmount+sum(isnull(at.camount,0)) TotalAmount,  ";
			sql = sql+	  " BS_StorageNoteHeader.TotalFixedPrice as FixedPrice,BS_StorageNoteHeader.TotalDiscountedPrice as DiscountedPrice from BS_StorageNoteHeader left join CUST_CustomerInfo on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.id ";
			sql = sql+	  " left join BS_StorageNote on BS_StorageNoteHeader.id=BS_StorageNote.StgNtHeaderID  ";
			sql = sql+	  " left join BS_StorageNote_attachment at on at.BS_StorageNoteID=BS_StorageNote.id  ";
		   //	sql = sql+	  "	group by BS_StorageNoteHeader.StgNtCodeStr,StgNtCode,hdtime,CUST_CustomerInfo.Name,TotalFixedPrice,TotalDiscountedPrice,TotalAmount ";
		}
		else                                     //StgNtCode
		{
			sql = "select BS_StorageNoteHeader.StgNtCode as NtCode,BS_StorageNoteHeader.StgNtCode,convert(nvarchar(10),HdTime,120) as HdTime,CUST_CustomerInfo.Name as clientname, ";
			sql = sql+	  " BS_StorageNoteHeader.TotalAmount+sum(isnull(at.camount,0)) TotalAmount,  ";
			sql = sql+	  " BS_StorageNoteHeader.TotalFixedPrice as FixedPrice,BS_StorageNoteHeader.TotalDiscountedPrice as DiscountedPrice from BS_StorageNoteHeader left join CUST_CustomerInfo on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.id ";
			sql = sql+	  " left join BS_StorageNote on BS_StorageNoteHeader.id=BS_StorageNote.StgNtHeaderID  ";
			sql = sql+	  " left join BS_StorageNote_attachment at on at.BS_StorageNoteID=BS_StorageNote.id  ";

		   //	sql = "select BS_StorageNoteHeader.StgNtCode as NtCode,convert(nvarchar(10),HdTime,120) as HdTime,CUST_CustomerInfo.Name as clientname,BS_StorageNoteHeader.TotalAmount,BS_StorageNoteHeader.TotalFixedPrice as FixedPrice,BS_StorageNoteHeader.TotalDiscountedPrice as DiscountedPrice from BS_StorageNoteHeader left join CUST_CustomerInfo on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.id ";
		}
		sqlwhere = " where BS_StorageNoteHeader.StgID = " + IntToStr(fstgid);
		if (ftuihuo == 0) {
			sqlwhere = sqlwhere + " and StgNtCodeInt > 0 ";
		}
		else
		{
			sqlwhere = sqlwhere + " and TStgNtCodeInt > 0 ";
		}
	}
	if (chstart->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
	}
	if (chend->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
	}
	if (chclient->Checked && cbsupplier->Text != "") {
		int  supplierid;
		try {
			supplierid = int(cbsupplier->Items->Objects[cbsupplier->ItemIndex]);
		} catch (...) {
			MessageBoxA(0,"请选择正确的供应商！","提示",MB_ICONERROR);
			return;
		}

		sqlwhere = sqlwhere + " and SupplierID = "  + IntToStr(supplierid);
	}
	if (chuser->Checked && cbuser->Text != "") {
		int userid;
		try {
			userid = int(cbuser->Items->Objects[cbuser->ItemIndex]);
		} catch (...) {
			MessageBoxA(0,"请选择正确的操作员！","提示",MB_ICONERROR);
			return;
		}
		sqlwhere = sqlwhere + " and OperatorID = "  + IntToStr(userid);
	}
    if (chcode->Checked && edcode->Text != "") {
    	if (fmodle == 1) {
			sqlwhere = sqlwhere + " and ProcureNtCode = " + edcode->Text ;
		}
		else
		{
			if (ChangeDisplay) {
				sqlwhere = sqlwhere + " and (StgNtCodeInt = " + edcode->Text + " or TStgNtCodeInt = " + edcode->Text + ") ";
			}
			else
			{
				sqlwhere = sqlwhere + " and StgNtCode = " + edcode->Text ;
			}
		}
	}              ///	sql = sql+	  "	 ";
	sql = sql + sqlwhere;
	if (fmodle == 1) {
		sql = sql + " order by ProcureNtCode";
	}
	else {
		sql = sql + " group by BS_StorageNoteHeader.StgNtCodeStr,StgNtCode,hdtime,CUST_CustomerInfo.Name,TotalFixedPrice,TotalDiscountedPrice,TotalAmount order by StgNtCodeStr";
	}
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------
AnsiString Tfrmcaigouquery::GetNoteCode()
{
	AnsiString recode;
	if (!query->IsEmpty() ) {
		if (fmodle == 2 && ChangeDisplay) {
			recode = query->FieldByName("StgNtCode")->AsString ;
		}
		else
		{
			recode = query->FieldByName("NtCode")->AsString ;
		}
	}
	return recode;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcaigouquery::DBGrid1DblClick(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcaigouquery::DBGrid1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
AnsiString Tfrmcaigouquery::GetWhere()
{
	return sqlwhere;
}
void __fastcall Tfrmcaigouquery::dtpstartChange(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouquery::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouquery::cbsupplierChange(TObject *Sender)
{
	if (cbsupplier->Text != "") {
		chclient->Checked = true;
	}
	else
	{
    	chclient->Checked = false;
	}
}
//---------------------------------------------------------------------------

