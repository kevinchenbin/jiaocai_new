//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberForm.h"
#include "MemberCardUnuse.h"
#include "MemberCardchange.h"
#include "PwdForm.h"
#include "Unitjifendh.h"
#include "Unithuancard.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzDBGrid"
#pragma link "RzLine"
#pragma resource "*.dfm"
TfrmMember *frmMember;
//---------------------------------------------------------------------------
__fastcall TfrmMember::TfrmMember(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
  quType->Connection = cn;
  quMemberCard->Connection = cn;
  quMemberInfo->Connection = cn;
  quMemberRecord->Connection = cn;
  fcon = cn;
  AnsiString sql;
  int maxid;
  sql = "select max(ID) as id from CUST_MemberInfo";
  quMemberCard->Close();
  quMemberCard->SQL->Clear();
  quMemberCard->SQL->Add(sql);
  quMemberCard->Open();
  maxid = quMemberCard->FieldByName("id")->AsInteger ;
  sql = "select CUST_MemberInfo.ID,CUST_MemberInfo.CardSN,CUST_MemberInfo.CardID,CUST_MemberInfo.Name,CUST_MemberType.Type,CUST_MemberInfo.CardType,CUST_MemberInfo.PassWord,CUST_MemberInfo.bircard,"
		"CUST_MemberInfo.Balance,CUST_MemberInfo.Birthday,CUST_MemberInfo.Sex,case CUST_MemberInfo.Sex when 0 then '男' when 1 then '女' end as Sexname,CUST_MemberInfo.Tel,CUST_MemberInfo.CardCast,"
		"CUST_MemberInfo.Mobile,CUST_MemberInfo.Address,CUST_MemberInfo.PostalCode,CUST_MemberInfo.TotalConsumption,case CUST_MemberInfo.Available  when 0 then '无效'  else '有效' end as aviable,"
		"CUST_MemberInfo.MemberType from CUST_MemberInfo inner join CUST_MemberType on CUST_MemberInfo.MemberType = CUST_MemberType.IDType "
		"where CUST_MemberInfo.ID > " + IntToStr(maxid);
  quMemberInfo->Close();
  quMemberInfo->SQL->Clear();
  quMemberInfo->SQL->Add(sql);
  dtpstart->Date = Date();
  dtpend->Date = Date();
  dgmemlist->OnDrawColumnCell=dgmemlistDrawColumnCell;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMember::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::FormShow(TObject *Sender)
{
	//向会员下拉列表添加类型值
	edtcardnum->SetFocus();
	AnsiString sql;
	TTreeNode * Node,* Root;
	AnsiString Value;
	AnsiString membertype;
	sql = "select IDType,Type as T,Discount from cust_membertype order by discount desc ";
	quType->Close();
	quType->SQL->Clear();
	quType->SQL->Add(sql);
	quType->Open();
	while(!quType->Eof )
	{
		membertype =  quType->FieldByName("T")->AsAnsiString.Trim()+"(" + quType->FieldByName("Discount")->AsAnsiString.Trim() + "%)";
		cbMemberType->AddItem(membertype ,(TObject*)quType->FieldByName("IDType")->AsInteger);
		quType->Next();
	}
	cbMemberType->ItemIndex = 0;
}
//-----------------------指定查询--------------------------------------------

void __fastcall TfrmMember::sbqueryClick(TObject *Sender)
{
	  AnsiString  sql = "select RANK() OVER(order by CUST_MemberInfo.ID ) as xuhao,CUST_MemberInfo.ID,CUST_MemberInfo.CardSN,CUST_MemberInfo.bircard,CUST_MemberInfo.CardID,CUST_MemberInfo.Name,CUST_MemberType.Type,CUST_MemberInfo.Balance, CUST_MemberInfo.Birthday,CUST_MemberInfo.createdate,CUST_MemberInfo.Sex,CUST_MemberInfo.CardType,CUST_MemberInfo.PassWord,case CUST_MemberInfo.Sex when 0 then '男' when 1 then '女' end as Sexname,CUST_MemberInfo.Tel,CUST_MemberInfo.Mobile,CUST_MemberInfo.Address,CUST_MemberInfo.PostalCode,CUST_MemberInfo.TotalConsumption,CUST_MemberInfo.MemberType,CUST_MemberInfo.Memberdot,case CUST_MemberInfo.Available when 0 then '无效'  else '有效' end as aviable,CUST_MemberInfo.CardCast from CUST_MemberInfo inner join CUST_MemberType on CUST_MemberInfo.MemberType = CUST_MemberType.IDType where 1 = 1 ";
	  if (chcard->Checked && edtcardnum->Text != "") {
			sql = sql + " and CardID like '%" + edtcardnum->Text.Trim() + "%'" ;
	  }
	  if (chname->Checked && edtname->Text != "" ) {
			sql = sql + " and name like '%"  + edtname->Text.Trim() + "%'";
	  }
	  if (chsex->Checked) {
			if (cbsex->Text == "男") {
				sql = sql + " and Sex = 0 ";
			}
			if (cbsex->Text == "女") {
				sql = sql + " and Sex = 1 ";
			}
	  }
	  if (chstate->Checked) {
			if (cbstate->Text == "有效") {
				sql = sql + " and Available = 1 ";
			}
			if (cbstate->Text == "无效") {
				sql = sql + " and Available = 0 ";
			}
	  }
	  if (chjifen->Checked ) {
		if (edminjifen->Text != "") {
			sql = sql + " and Memberdot >= " + edminjifen->Text ;
		}
		if (edmaxjifen->Text != "") {
			sql = sql + " and Memberdot <= " + edmaxjifen->Text ;
		}
	  }
	  if (chjine->Checked ) {
		if (edminjine->Text != "") {
			sql = sql + " and Memberdot >= " + edminjine->Text ;
		}
		if (edmaxjine->Text != "") {
			sql = sql + " and Memberdot <= " + edmaxjine->Text ;
		}
	  }
	  if (chtype->Checked && cbMemberType->Text != "") {
		int memtype;
		try {
			memtype = int(cbMemberType->Items->Objects[cbMemberType->ItemIndex]);
		} catch (...) {
			return;
		}
		sql = sql + " and CUST_MemberInfo.MemberType = " + IntToStr(memtype);
	  }
	  if (chstart->Checked) {
		  sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',createdate) >= 0";
	  }
	  if (chend->Checked) {
		  sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',createdate) <= 0";
	  }
	  quMemberInfo->Close();
	  quMemberInfo->SQL->Clear();
	  quMemberInfo->SQL->Add(sql);
	  quMemberInfo->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::btEscClick(TObject *Sender)
{
	Close();
}
//----------------------添加--------------------------------------------------

void __fastcall TfrmMember::btAddClick(TObject *Sender)
{
   int c_add = 1;     //添加会员
   String m_MemberInfo[1];
   quMemberInfo->Active = true;
   TfrmMemberCard * frm = new TfrmMemberCard(Application,c_add,m_MemberInfo,fcon);
   frm->ShowModal();
   delete frm;
   quMemberInfo->Active = false;
   quMemberInfo->Active = true;
}
//---------------------修改---------------------------------------------------

void __fastcall TfrmMember::btUpdateClick(TObject *Sender)
{
   if (quMemberInfo->IsEmpty() ) {
	return;
   }
   int c_update = 2;     //修改会员
   if (quMemberInfo->FieldByName("Name")->AsString == "普通会员") {
		MessageBox(0,"普通会员不能修改！","系统提示" ,MB_OK);
		return;
   }
	if (quMemberInfo->FieldByName("aviable")->AsString == "无效") {
		MessageBox(0,"该会员卡已退卡，不能修改！","系统提示" ,MB_OK);
		return;
   }
   String *m_MemberInfo;
   m_MemberInfo = new String[15];
   m_MemberInfo[0] = quMemberInfo->FieldByName("ID")->AsString; //ID
   m_MemberInfo[1] = quMemberInfo->FieldByName("Name")->AsString; //Name
   m_MemberInfo[2] = quMemberInfo->FieldByName("Birthday")->AsString ; //Birthday
   m_MemberInfo[3] = quMemberInfo->FieldByName("Sexname")->AsString; //Sex
   m_MemberInfo[4] = quMemberInfo->FieldByName("Tel")->AsString; //Tel
   m_MemberInfo[5] = quMemberInfo->FieldByName("Mobile")->AsString; //Mobile
   m_MemberInfo[6] = quMemberInfo->FieldByName("Address")->AsString; //Address
   m_MemberInfo[7] = quMemberInfo->FieldByName("PostalCode")->AsString; //PostalCode
   m_MemberInfo[8] = quMemberInfo->FieldByName("CardID")->AsString; //CardSN
   m_MemberInfo[9] = quMemberInfo->FieldByName("Balance")->AsString; //Balance
   m_MemberInfo[10] = quMemberInfo->FieldByName("TotalConsumption")->AsString; //TotalConsumption
   m_MemberInfo[11] = IntToStr(quMemberInfo->FieldByName("MemberType")->AsInteger); //MemberType
   m_MemberInfo[12] = quMemberInfo->FieldByName("CardCast")->AsString ;
   m_MemberInfo[13] = quMemberInfo->FieldByName("CardType")->AsString ;
   m_MemberInfo[14] = quMemberInfo->FieldByName("bircard")->AsString ;
   TfrmMemberCard * frm = new TfrmMemberCard(Application,c_update,m_MemberInfo,fcon);
   frm->ShowModal();
   delete frm;
   quMemberInfo->Active = false;
   quMemberInfo->Active = true;
}
//-----------------------删除------------------------------------------------

void __fastcall TfrmMember::btDeleteClick(TObject *Sender)
{
	if (quMemberInfo->IsEmpty()) {
    	return;
	}
	if (quMemberInfo->FieldByName("Name")->AsString == "普通会员") {
		MessageBox(0,"普通会员不能删除！","系统提示" ,MB_OK);
		return;
	}
	AnsiString sql ;
	sql = "select count(*) as count from BS_RetailNoteHeader where MemberID = " + quMemberInfo->FieldByName("ID")->AsString ;
	quMemberCard->Close();
	quMemberCard->SQL->Clear();
	quMemberCard->SQL->Add(sql);
	quMemberCard->Open();
	int count = quMemberCard->FieldByName("count")->AsInteger ;
	if (count>0) {
		MessageBox(0,"该会员有销售记录，不能删除！","系统提示" ,MB_OK);
		return;
	}
	AnsiString sqlMemberCard = "delete from CUST_MemberCard where CardID = '",  sqlMemberRecord = "delete from CUST_MemberToprecord where CardID = '";
	sqlMemberCard = sqlMemberCard + quMemberInfo->FieldByName("CardID")->AsString + "'";
	sqlMemberRecord = sqlMemberRecord +  quMemberInfo->FieldByName("CardID")->AsString + "'";
	sql = "delete  from CUST_MemberInfo where CardID = '" +quMemberInfo->FieldByName("CardID")->AsString + "'";;
	if(!quMemberInfo->IsEmpty())
	{
		AnsiString sdf;
		sdf =  "您确认删除会员："+quMemberInfo->FieldByName("CardID")->AsString+"吗？";
		if (MessageBox(0,sdf.c_str() ,"确认删除" ,MB_OKCANCEL)==1) {
			try{
				  quMemberCard->Close();
				  quMemberCard->SQL->Clear();
				  quMemberCard->SQL->Add(sql);
				  quMemberCard->ExecSQL();
				  quMemberInfo->Active = false;
				  quMemberInfo->Active = true;
				  quMemberCard->Close();
				  quMemberCard->SQL->Clear();
				  quMemberCard->SQL->Add(sqlMemberCard);
				  quMemberCard->ExecSQL();
				  quMemberRecord->Close();
				  quMemberRecord->SQL->Clear();
				  quMemberRecord->SQL->Add(sqlMemberRecord);
				  quMemberRecord->ExecSQL();
			}
			catch(Exception &E)
			{
				MessageBox(0,"此数据跟系统其他地方有关联，不能删除！","错误确认" ,MB_OK);
			}
		}
	}

}
//------------------------会员类型查询---------------------------------------

void __fastcall TfrmMember::cbMemberTypeSelect(TObject *Sender)
{
	  /*int memtype;
	  memtype = int(cbMemberType->Items->Objects[cbMemberType->ItemIndex]);
	  AnsiString sql = "select RANK() OVER(order by CUST_MemberInfo.ID ) as xuhao,CUST_MemberInfo.ID,CUST_MemberInfo.CardSN,CUST_MemberInfo.CardID,CUST_MemberInfo.Name,CUST_MemberType.Type,CUST_MemberInfo.Balance,CUST_MemberInfo.Birthday,CUST_MemberInfo.createdate,CUST_MemberInfo.CardType,CUST_MemberInfo.PassWord,CUST_MemberInfo.Sex,case CUST_MemberInfo.Sex when 0 then '男' when 1 then '女' end as Sexname,case CUST_MemberInfo.Available when 0 then '无效'  else  '有效' end as aviable,CUST_MemberInfo.Tel,CUST_MemberInfo.Mobile,CUST_MemberInfo.Address,CUST_MemberInfo.PostalCode,CUST_MemberInfo.TotalConsumption,CUST_MemberInfo.MemberType,CUST_MemberInfo.Memberdot,CUST_MemberInfo.CardCast from CUST_MemberInfo inner join CUST_MemberType on CUST_MemberInfo.MemberType = CUST_MemberType.IDType where MemberType = ";
	  sql = sql + memtype;
	  quMemberInfo->Close();
	  quMemberInfo->SQL->Clear();
	  quMemberInfo->SQL->Add(sql);
	  quMemberInfo->Open();  */
}
//----------------------右键快捷充值-----------------------------------------

void __fastcall TfrmMember::addvalueClick(TObject *Sender)
{
	if (quMemberInfo->RecordCount == 0) {
		return;
	}
	if (quMemberInfo->FieldByName("Name")->AsString == "普通会员") {
		MessageBox(0,"普通会员不能充值！","系统提示" ,MB_OK);
		return;
   }
    if (quMemberInfo->FieldByName("aviable")->AsString == "无效") {
		MessageBox(0,"该会员卡已退卡，不能充值！","系统提示" ,MB_OK);
		return;
	}
	String sql = "select Member from SYS_StorageInfo";
	quType->Close();
	quType->SQL->Clear();
	quType->SQL->Add(sql);
	quType->Open();
	String password = quType->FieldByName("Member")->AsString ;
	TfrmPwd* frm = new TfrmPwd(this);
	if (mrOk == frm->ShowModal())
	{
		if (frm->GetPassword() != password)
		{
			MessageBoxA(0,"密码错误！","警告",MB_ICONASTERISK);
			return;
		}
	}
	else
	{
		return;
	}
	delete frm;
	Tfrmaddvalue * frm1 = new Tfrmaddvalue(Application,quMemberInfo->FieldByName("CardID")->AsString,fcon);
	frm1->userid = userid;
	frm1->fstgid = stgid;
	frm1->ShowModal();
	delete frm1;
	quMemberInfo->Active = false;
    quMemberInfo->Active = true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMember::dgmemlistTitleClick(TColumn *Column)
{
	AnsiString qusort;
	if (quMemberInfo->IsEmpty() ) {
        return;
	}
	qusort =  Column->FieldName + " ASC";
	if (quMemberInfo->Sort == "") {
		quMemberInfo->Sort =  Column->FieldName + " ASC";
	}
	else if (quMemberInfo->Sort == qusort) {
		quMemberInfo->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		quMemberInfo->Sort =  Column->FieldName + " ASC";
	}

}
//---------------------------------------------------------------------------
void __fastcall TfrmMember::edtcardnumKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		sbquery->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edtnameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		sbquery->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::BtnExportClick(TObject *Sender)
{
    if (quMemberInfo->IsEmpty() ) {
        return;
	}
	if (quMemberInfo->RecordCount > 1) {
		DbgridToExcel(dgmemlist);
	}
}
//---------------------------------------------------------------------------
//Excel导出函数
bool __fastcall TfrmMember::DbgridToExcel(TDBGrid* dbg)
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

	v.OlePropertyGet("Cells",1,6).OlePropertySet("Value","会员查询记录" );

	n=1;

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


void __fastcall TfrmMember::BtnImportClick(TObject *Sender)
{
	quMemberInfo->Active = true;
	TFormMemImport * frm = new TFormMemImport(Application,quMemberInfo);
	frm->Show();

}
//---------------------------------------------------------------------------
void __fastcall  TfrmMember::OnMinMaxSize(TMessage& Msg)
{
if (Msg.WParam == SC_MINIMIZE)
{
  // BringWindowToTop(this->Handle);
}

TForm::Dispatch(&Msg);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMember::BtnChangeOptionsClick(TObject *Sender)
{
	if (quMemberInfo->IsEmpty() ) {
        return;
	}
	if (quMemberInfo->FieldByName("Name")->AsString == "普通会员") {
		MessageBox(0,"普通会员不能修改！","系统提示" ,MB_OK);
		return;
	}
	if (quMemberInfo->Active == true && quMemberInfo->RecordCount > 0) {
        if (quMemberInfo->FieldByName("aviable")->AsString == "无效") {
			MessageBox(0,"该会员卡已退卡，不能修改！","系统提示" ,MB_OK);
			return;
		}
		TfrmMemberCardChange *frm = new TfrmMemberCardChange(Application,fcon,quMemberInfo->FieldByName("ID")->AsInteger );
		frm->userid = userid;
		frm->fstgid = stgid;
		frm->ShowModal() ;
		delete frm;
	}
	quMemberInfo->Active = false;
	quMemberInfo->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::BtnErrorClick(TObject *Sender)
{
	if (quMemberInfo->IsEmpty() ) {
        return;
	}
	if (quMemberInfo->FieldByName("Name")->AsString == "普通会员") {
		MessageBox(0,"普通会员不能退卡！","系统提示" ,MB_OK);
		return;
	}
	if (quMemberInfo->Active == true && quMemberInfo->RecordCount > 0) {
    	if (quMemberInfo->FieldByName("aviable")->AsString == "无效") {
			MessageBox(0,"该会员卡已经作废！","系统提示" ,MB_OK);
			return;
		}
		TfrmMemberCardUnuse *frm = new TfrmMemberCardUnuse(Application,fcon,quMemberInfo->FieldByName("ID")->AsInteger );
        frm->userid = userid;
		frm->fstgid = stgid;
		frm->ShowModal() ;
		delete frm;
	}
	quMemberInfo->Active = false;
	quMemberInfo->Active = true;
}
//---------------------------------------------------------------------------



void __fastcall TfrmMember::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {
		 btAdd->Click();
	   }
		if (Key == VK_F3) {
		 btUpdate->Click();
	   }

		if (Key == VK_F7) {
		 btDelete->Click();
	   }
		if (Key == VK_F4) {
		 BtnError->Click();
	   }
			if (Key == VK_F5) {
		 BtnImport->Click();
	   }
			if (Key == VK_F6) {
		 BtnExport->Click();
	   }

		if (Shift.Contains(ssCtrl)&& Key ==90) {
			WindowState = wsNormal  ;
		}
		if (Shift.Contains(ssCtrl)&& Key ==81  ) {
			btEsc->Click();
		}
		if (Shift.Contains(ssCtrl)&& Key == 78 ) {
		  BtnAlignBottom->Click();
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::BtnAlignBottomClick(TObject *Sender)
{
		WindowState = wsMinimized   ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::dgmemlistDrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (dgmemlist->DataSource->DataSet->FieldByName("aviable")->AsAnsiString == "无效" ) {
		  ((TDBGrid*)Sender)->Canvas->Font->Color=clRed;

	 }
	  ((TDBGrid*)Sender)->DefaultDrawColumnCell(Rect,DataCol,Column,State);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edtcardnumChange(TObject *Sender)
{
	if (edtcardnum->Text != "") {
		chcard->Checked = true;
	}
	else
	{
    	chcard->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edtnameChange(TObject *Sender)
{
	if (edtname->Text != "") {
		chname->Checked = true;
	}
	else
	{
    	chname->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::cbsexChange(TObject *Sender)
{
	if (cbsex->Text != "") {
		chsex->Checked = true;
	}
	else
	{
    	chsex->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::cbMemberTypeChange(TObject *Sender)
{
	if (cbMemberType->Text != "") {
		chtype->Checked = true;
	}
	else
	{
    	chtype->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edminjifenChange(TObject *Sender)
{
	if (edminjifen->Text != "") {
		chjifen->Checked = true;
	}
	else if (edmaxjifen->Text != "") {
		chjifen->Checked = true;
	}
	else
	{
    	chjifen->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edminjineChange(TObject *Sender)
{
	if (edminjine->Text != "") {
		chjine->Checked = true;
	}
	else if (edmaxjine->Text != "") {
		chjine->Checked = true;
	}
	else
	{
    	chjine->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::cbstateChange(TObject *Sender)
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

void __fastcall TfrmMember::dtpstartChange(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::cbsexKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        cbMemberType->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edminjifenKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edmaxjifen->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edmaxjifenKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edminjine->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edminjineKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edmaxjine->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::edmaxjineKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        cbstate->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::cbstateKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        dtpstart->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::dtpstartKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        dtpend->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::dtpendKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        sbquery->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::BtnWordWrapClick(TObject *Sender)
{
	if (quMemberInfo->IsEmpty() ) {
		return;
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select * from SYS_Member_jifen_type where Membertype = -1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->IsEmpty() ) {
		MessageBox(0,"没设置积分兑换金额，不能兑换！","提示" ,MB_OK);
		return;
	}
	delete aq;
	Tfrmjifendh *frm = new Tfrmjifendh(Application,fcon);
	frm->memberid = quMemberInfo->FieldByName("ID")->AsInteger;
	frm->userid = userid;
	frm->stgid = stgid;
	frm->edcard->Text = quMemberInfo->FieldByName("CardID")->AsAnsiString ;
	frm->edname->Text = quMemberInfo->FieldByName("Name")->AsAnsiString ;
	frm->edjifen->Text = quMemberInfo->FieldByName("Memberdot")->AsAnsiString ;
	frm->ShowModal() ;
	delete frm;
	quMemberInfo->Active = false;
	quMemberInfo->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::BtnClearClick(TObject *Sender)
{
	if (quMemberInfo->IsEmpty()) {
		return;
	}
	AnsiString sql,idlist = "-1" ;
	sql = "update CUST_MemberInfo set Memberdot = 0 where CardID = '" +quMemberInfo->FieldByName("CardID")->AsString + "'";;
	quMemberInfo->DisableControls();
	if (MessageBox(0,"确认清除会员积分？","确认提示" ,MB_OKCANCEL)==1) {
		try{
			for (int i =0; i < dgmemlist->SelectedRows->Count ; i++) {
				quMemberInfo->GotoBookmark(dgmemlist->SelectedRows->Items[i]);
				idlist = idlist + "," + quMemberInfo->FieldByName("id")->AsAnsiString ;
			}
			sql = "update CUST_MemberInfo set Memberdot = 0 where id in (" + idlist + ")";
			quMemberCard->Close();
			quMemberCard->SQL->Clear();
			quMemberCard->SQL->Add(sql);
			quMemberCard->ExecSQL();
			quMemberInfo->Active = false;
			quMemberInfo->Active = true;
			MessageBox(0,"积分清零完成！","成功" ,MB_OK);
		}
		catch(Exception &E)
		{
			MessageBox(0,"积分清零失败！","错误" ,MB_OK);
		}
	}
	quMemberInfo->EnableControls();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::BtnSendtoBackClick(TObject *Sender)
{
	if (quMemberInfo->IsEmpty() ) {
    	return;
	}
	if (quMemberInfo->FieldByName("aviable")->AsAnsiString == "无效") {
		MessageBox(0,"该会员卡已经作废！","系统提示" ,MB_OK);
		return;
	}
	Tfrmhuancard *frm = new Tfrmhuancard(Application,fcon,quMemberInfo->FieldByName("ID")->AsInteger);
	if (frm->ShowModal() == mrOk ) {
		quMemberInfo->Active = false;
		quMemberInfo->Active = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMember::N5Click(TObject *Sender)
{
	if (quMemberInfo->IsEmpty() ) {
		return;
	}
	quMemberInfo->DisableControls();
	for (int i = 1; i <= quMemberInfo->RecordCount; i++) {
		dgmemlist->DataSource->DataSet->RecNo = i;
		dgmemlist->SelectedRows->CurrentRowSelected = true;
	}
    quMemberInfo->EnableControls();
}
//---------------------------------------------------------------------------

