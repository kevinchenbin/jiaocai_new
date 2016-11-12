//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SalesAnalysisForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TfrmSalesAnalysis *frmSalesAnalysis;
//---------------------------------------------------------------------------
__fastcall TfrmSalesAnalysis::TfrmSalesAnalysis(TComponent* Owner)
	: TfrmMDIChild(Owner)
{        m_module = MTData;
	dtp1->Date=dtp1->Date .CurrentDate();
	dtp2->Date=dtp2->Date .CurrentDate();
}
//---------------------------------------------------------------------------

void TfrmSalesAnalysis::Init(TApplication* app, TADOConnection* con)
{           TfrmMDIChild::Init(app, con);
		dsquery->Connection=con;
        TADOQuery * aq;
		String sql;
		aq = new TADOQuery(this);
		aq->Connection = con;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add("select * from sys_bsset where name ='xiaoshudian'");
		aq->Open();
		storageformat =  "��" + aq->FieldByName("bk")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add("select * from sys_bsset where name ='retailxiaoshudian'");
		aq->Open();
		retaiformat =  "��" + aq->FieldByName("bk")->AsAnsiString ;

        sql = "select ID,Name from SYS_StorageInfo ";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while (!aq->Eof )
		{
			cbstorage->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)stgid);
		sql = "select Master from SYS_StorageInfo where id = " + IntToStr(stgid);
        aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->FieldByName("Master")->AsBoolean ) {
			chstorage->Enabled = true;
			cbstorage->Enabled = true;
		}
		else
		{
			chstorage->Enabled = false;
			cbstorage->Enabled = false;
		}

		delete aq;
}
void __fastcall TfrmSalesAnalysis::FormClose(TObject *Sender, TCloseAction &Action)

{        dsquery->Active=false;
	    Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSalesAnalysis::RzToolButton3Click(TObject *Sender)
{
	    Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSalesAnalysis::RzToolButton1Click(TObject *Sender)
{        String sql;
		  if (rb5->Checked==true) {      //��Ʒ����
			DBGridEh1->Columns->Items[1]->Title->Caption = "����";
			DBGridEh1->Columns->Items[0]->Visible = true;
			DBGridEh1->Columns->Items[2]->Visible = true;
			//DBGridEh1->Columns->Items[1]->Footers->Items[0]->Value = "";
			DBGridEh1->Columns->Items[0]->Footer->Value = "�ϼ�";
			DBGridEh1->Columns->Items[0]->Footer->ValueType = fvtStaticText ;
			DBGridEh1->Columns->Items[1]->Footer->Value = "";
			DBGridEh1->Columns->Items[1]->Footer->ValueType = fvtStaticText;
				sql="select Price,ISBN,BookName as Name, sum(Cbprice*amount) as chengben,sum(Price*amount) as rukumayang,sum(amount) as WsaleAmount,sum(Price*amount) as salemayang,"
					"sum(DiscountedPrice) as WsaleDscPrice,sum(DiscountedPrice)-sum(Cbprice*amount) as Profit";
				sql=sql+" from DataQryAnalys ";
			sql = sql + " where bktype = " + IntToStr(RadioGroup1->ItemIndex);

			int fstgid;
			if (chstorage->Checked) {
				try {
					fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
				} catch (...) {
					MessageBox(0,"��ѡ����ȷ�ĵ��!","��ʾ",MB_ICONEXCLAMATION);
					return;
				}
				sql = sql + " and StgID = " + IntToStr(fstgid);
			}

			if (cbstart->Checked ) {
				sql = sql + " and datediff(d,WsaleTime,'" + dtp1->Date+"')<=0";
			}
			if (!cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,WsaleTime,'" + dtp2->Date+"')>=0";
			}
			if (cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,WsaleTime,'" + dtp2->Date+"')>=0";
			}

			sql = sql + " group by BookName,Price,ISBN";
		  }
		  if (rb1->Checked==true) {    //���
			DBGridEh1->Columns->Items[1]->Title->Caption = "���";
			DBGridEh1->Columns->Items[0]->Visible = false;
			DBGridEh1->Columns->Items[2]->Visible = false;
			DBGridEh1->Columns->Items[1]->Footer->Value = "�ϼ�";
			DBGridEh1->Columns->Items[1]->Footer->ValueType = fvtStaticText ;
				sql="select TypeName as Name, sum(Cbprice*amount) as chengben,sum(Price*amount) as rukumayang,sum(amount) as WsaleAmount,sum(Price*amount) as salemayang,"
					"sum(DiscountedPrice) as WsaleDscPrice,sum(DiscountedPrice)-sum(Cbprice*amount) as Profit";
				sql=sql+" from DataQryAnalys ";
			sql = sql + " where bktype = " + IntToStr(RadioGroup1->ItemIndex);

			int fstgid;
			if (chstorage->Checked) {
				try {
					fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
				} catch (...) {
					MessageBox(0,"��ѡ����ȷ�ĵ��!","��ʾ",MB_ICONEXCLAMATION);
					return;
				}
				sql = sql + " and StgID = " + IntToStr(fstgid);
			}

			if (cbstart->Checked ) {
				sql = sql + " and datediff(d,WsaleTime,'" + dtp1->Date+"')<=0";
			}
			if (!cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,WsaleTime,'" + dtp2->Date+"')>=0";
			}
			if (cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,WsaleTime,'" + dtp2->Date+"')>=0";
			}
			sql = sql + " group by TypeName";
		  }
		  if (rb2->Checked==true) {     //������
			DBGridEh1->Columns->Items[1]->Title->Caption = "������";
			DBGridEh1->Columns->Items[0]->Visible = false;
			DBGridEh1->Columns->Items[2]->Visible = false;
			DBGridEh1->Columns->Items[1]->Footer->Value = "�ϼ�";
			DBGridEh1->Columns->Items[1]->Footer->ValueType = fvtStaticText ;
			sql="select PressName as Name, sum(Cbprice*amount) as chengben,sum(Price*amount) as rukumayang,sum(amount) as WsaleAmount,sum(Price*amount) as salemayang,"
					"sum(DiscountedPrice) as WsaleDscPrice,sum(DiscountedPrice)-sum(Cbprice*amount) as Profit";
				sql=sql+" from DataQryAnalys ";
			sql = sql + " where bktype = " + IntToStr(RadioGroup1->ItemIndex);

			int fstgid;
			if (chstorage->Checked) {
				try {
					fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
				} catch (...) {
					MessageBox(0,"��ѡ����ȷ�ĵ��!","��ʾ",MB_ICONEXCLAMATION);
					return;
				}
				sql = sql + " and StgID = " + IntToStr(fstgid);
			}

          	if (cbstart->Checked ) {
				sql = sql + " and datediff(d,WsaleTime,'" + dtp1->Date+"')<=0";
			}
			if (!cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,WsaleTime,'" + dtp2->Date+"')>=0";
			}
			if (cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,WsaleTime,'" + dtp2->Date+"')>=0";
			}
			sql = sql + " group by PressName ";
		  }
		  if (rb4->Checked==true) {  //  ��Ӧ��
			DBGridEh1->Columns->Items[1]->Title->Caption = "��Ӧ��";
			DBGridEh1->Columns->Items[0]->Visible = false;
			DBGridEh1->Columns->Items[2]->Visible = false;
			DBGridEh1->Columns->Items[1]->Footer->Value = "�ϼ�";
			DBGridEh1->Columns->Items[1]->Footer->ValueType = fvtStaticText ;
			sql="select suppliername as Name, sum(Cbprice*amount) as chengben,sum(Price*amount) as rukumayang,sum(amount) as WsaleAmount,sum(Price*amount) as salemayang,"
					"sum(DiscountedPrice) as WsaleDscPrice,sum(DiscountedPrice)-sum(Cbprice*amount) as Profit";
				sql=sql+" from DataQryAnalys ";
			sql = sql + " where bktype = " + IntToStr(RadioGroup1->ItemIndex);

			int fstgid;
			if (chstorage->Checked) {
				try {
					fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
				} catch (...) {
					MessageBox(0,"��ѡ����ȷ�ĵ��!","��ʾ",MB_ICONEXCLAMATION);
					return;
				}
				sql = sql + " and StgID = " + IntToStr(fstgid);
			}

			if (cbstart->Checked ) {
				sql = sql + " and datediff(d,WsaleTime,'" + dtp1->Date+"')<=0";
			}
			if (!cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,WsaleTime,'" + dtp2->Date+"')>=0";
			}
			if (cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,WsaleTime,'" + dtp2->Date+"')>=0";
			}
			sql = sql + " group by suppliername ";
		  }

		if (rb5->Checked==false&&rb1->Checked==false&&rb2->Checked==false&&rb4->Checked==false) {
		   ShowMessage("��ѡ�����");
		}
		else
			{   if (dsquery->Active) {
				   dsquery->Active=false;
			   }

			   dsquery->CommandText=sql;
			   dsquery->Active=true;
			   if (rb5->Checked ) {
					((TFloatField *)dsquery->FieldByName("Price"))->DisplayFormat = storageformat;
			   }
			   ((TFloatField *)dsquery->FieldByName("chengben"))->DisplayFormat = storageformat;
			   ((TFloatField *)dsquery->FieldByName("salemayang"))->DisplayFormat = retaiformat;
			   ((TFloatField *)dsquery->FieldByName("WsaleDscPrice"))->DisplayFormat = retaiformat;
			   ((TFloatField *)dsquery->FieldByName("Profit"))->DisplayFormat = retaiformat;
	   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSalesAnalysis::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F6 ) {    //����
		BtnExport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //��ѯ
		RzToolButton1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		RzToolButton3->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSalesAnalysis::BtnExportClick(TObject *Sender)
{
	if (dsquery->IsEmpty() ) {
        return;
	}
	DbgridToExcel(DBGridEh1);
}
//---------------------------------------------------------------------------

//Excel��������
bool __fastcall TfrmSalesAnalysis::DbgridToExcel(TDBGridEh* dbg)
{
	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	/*if(k == 0)
	{
		MessageBox(0,"û�����ݣ�","����ȷ��" ,MB_OK);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  ��Excel�г��ַ�����ʾ
	v.OlePropertyGet("Cells",1,5).OlePropertySet("Value","������������ë������" );


	n=1;   */
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(savedlg->FileName .c_str()  );
		Name = ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	else
		iFileHandle = FileCreate(path.c_str());

	temptext = ",,,,������������ë������";
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t1= 0;
	temptext = "\n";
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			/*t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );  */
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				/*t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()  */
				temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet->Next();
	}
    dbg->DataSource ->DataSet->EnableControls();
	t1 = 0;
	temptext = "\n";
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			/*t1++;
			temptext = "'"+ dbg->GetFooterValue(0,dbg->Columns->Items[q]);
			v.OlePropertyGet("Cells",t2+2+n,t1).OlePropertySet("Value",temptext .c_str() ); */
			temptext = temptext + dbg->GetFooterValue(0,dbg->Columns->Items[q]) + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);
	MessageBox(0,"������ϣ�","��ʾ" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSalesAnalysis::DBGridEh1TitleClick(TColumnEh *Column)
{
	if (dsquery->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsquery->Sort == "") {
		dsquery->Sort =  Column->FieldName + " ASC";
	}
	else if (dsquery->Sort == qusort) {
		dsquery->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsquery->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSalesAnalysis::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

