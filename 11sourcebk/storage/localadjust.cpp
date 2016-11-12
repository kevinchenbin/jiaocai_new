//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "localadjust.h"
#include "QryNoteCodeForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmadjust *frmadjust;
//---------------------------------------------------------------------------
__fastcall Tfrmadjust::Tfrmadjust(TComponent* Owner,TADOConnection* con,LandInfo* li)
	: TForm(Owner)
{
	li->con = con;
	fcon = con;
	checkli = *li;
	aquery->Connection = con;
	m_storageID = li->storageID ;
	edtemploy->Text = li->UserName ;
	atable->Connection = con;
	adosp->Connection = con;
	aqueryupdate->Connection = con;
	aqheader->Connection = con;
	CatalogSearchMode = 4;//
	m_storageID = checkli.storageID ;
	dtpdate->Date = Date();
	edstorageid->Text = IntToStr(m_storageID);
	AnsiString sql;
	sql = "select * from STK_stackAdjustHead ";
	aqheader->Close();
	aqheader->SQL->Clear();
	aqheader->SQL->Add(sql);
	aqheader->Open();
}
void Tfrmadjust::readyData(TADOQuery * aquery)
{
    Store = new TStringList();
	Local = new TStringList();
	AnsiString value;
	AnsiString sql ;
	AnsiString Note="";

	int LocalID;
	int StorgeID;
	sql = "select A.ID,A.Name,A.Stgid,A.state,B.Name as StgName from STK_Bookstackinfo A left join SYS_StorageInfo B on A.stgid = B.id where B.id = " + IntToStr(m_storageID) ;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while(!aquery->Eof)
	{
	   Booklocal *bl = new Booklocal(aquery->FieldByName("name")->AsAnsiString ,aquery->FieldByName("StgID")->AsAnsiString ,aquery->FieldByName("id")->AsAnsiString,aquery->FieldByName("state")->AsAnsiString) ;
	   if (m_storageID==bl->StgID ) {
		 Local->AddObject(bl->ID , (TObject*)bl);    //���ص�ǰ������п�λ
	   }
	   if ((edtstg->Text =="")&&(bl->StgID ==aquery->FieldByName("stgid")->AsInteger)) {

		   edtstg->Text = aquery->FieldByName("StgName")->AsString ;
		   edtstg->ReadOnly = true;

	   }
	   if (aquery->FieldByName("state")->AsInteger==1) {

		   Note = Note + aquery->FieldByName("Name")->AsAnsiString  + " " ;
		   LockLocalID = LockLocalID +  aquery->FieldByName("Name")->AsAnsiString +",";
	   }
	   aquery->Next();
	}


	/*if (Note != "") {
	   memnote->Lines->Add("��ʾ");
	   Note = Note +  "�ѱ�����!";
	   memnote->Lines->Add(Note);
	   memnote->Font->Color = clRed ;
	}  */
	if (LockLocalID == "") {
		LockLocalID = LockLocalID.SubString(0,LockLocalID.Length()-1 );
	}
  /*	sql = "select ID,Name from SYS_storageinfo";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while(!aquery->Eof)    	//���ص���Ϣ
	{
	   Storage  *st = new Storage(aquery->FieldByName("name")->AsAnsiString,aquery->FieldByName("id")->AsAnsiString);
	   Store->AddObject(st->ID ,(TObject*)st);
	  if (m_storageID = 0) {        //�ܵ�������еĵ���Ϣ
	   cbstore->Items->Add(st->Name);
	  } else
	  {
		if (st->ID == m_storageID) {          //�����ܵ�ֻ���ر�����Ϣ
		  StorgeID = StrToInt(st->ID);
		  cbstore->Items->AddObject(st->Name ,(TObject*)StorgeID);
		}

		}
	   aquery->Next();
	  }

	  cbstore->ItemIndex = 0;   */





	//���ؿ�λ��Ϣ
   for (int i = 0; i < Local->Count ; i++) {

	  if(((Booklocal*)Local->Objects[i])->StgID == m_storageID)
	  {
		LocalID = StrToInt(((Booklocal*)Local->Objects[i])->ID) ;
		cblocalin->Items->AddObject(((Booklocal*)Local->Objects[i])->Name,(TObject*)LocalID );

	  }

   }

	 cblocalin->ItemIndex = 0;




}
//---------------------------------------------------------------------------
void __fastcall Tfrmadjust::edtcheckinfoKeyPress(TObject *Sender, wchar_t &Key)
{
	 if (Key == '\r')                //int m_catalogSearchMode;//1���� 2Ϊ�Ա��� 3Ϊ����  4 ISBN 5 ����
	 {

	 //���������Ϣ
	 if (edtnum->Text =="") {
		 MessageBox(0,"������ӿ�λ������","��λ����",MB_ICONASTERISK);
		 return;
	 }

	 if (cblocalin->Text == "") {
		 MessageBox(0,"��ѡ���λ","��λ����",MB_ICONASTERISK);
		 return;
	 }
/*	 if (cbstore->Text == "") {
		 MessageBox(0,"��ѡ�����","��λ����",MB_ICONASTERISK);
		 return;
	 }    */




	String sql;
	bool zerodisplay;
	AnsiString NowLocal;
	int localnum,adjust;

	 //1���� 2Ϊ�Ա��� 3Ϊ����  4 ISBN 5 ����



		sql = "select STK_BookInfo.id as bkinfoid,BS_BookCatalog.ID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,BS_BookCatalog.ID  as STK_BookinfoID,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.AbbreviatedName ,STK_BookstackInfo.name LocalName, "
			" STK_BookInfo.Maxstock,STK_BookInfo.MinStock,STK_BookInfo.BKstackID "
			"from STK_BookInfo left join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(m_storageID);
		   //	+ " and  STK_BookstackInfo.id = " + IntToStr(m_local);



	switch (CatalogSearchMode)
	{
	/*case 1://����


		 sql = sql +	" and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Barcode='" + edtcheckinfo->Text.Trim()  + "'";
		if (!zerodisplay) {                //��ѯҵ�����ÿ��Ϊ0���Ƿ���ʾ

		   sql = sql + "and STK_BookInfo.Amount > 0 " ;

		}
		break;*/
	case 2://�Ա���
		  sql = sql +   " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.UserDefCode like '%" + edtcheckinfo->Text.Trim()  + "%'";

		if (!zerodisplay) {

		   sql = sql + "and STK_BookInfo.Amount > 0 " ;

		}
		break;
	case 3://����

			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Name like '%" + edtcheckinfo->Text.Trim()  + "%'";

		if (!zerodisplay) {

		   sql = sql + "and STK_BookInfo.Amount > 0 " ;
			}
		break;
	case 4: //ISBN

		  sql = sql	+ " and BS_BookCatalog.Unavailable=1 and (BS_BookCatalog.ISBN like '%" + edtcheckinfo->Text.Trim()  + "%' or BS_BookCatalog.Barcode like '%" + edtcheckinfo->Text.Trim() + "%')";

		if (!zerodisplay) {

			sql = sql + "and STK_BookInfo.Amount > 0 " ;
			}

		break;
	case 5://����
		   sql = sql 	+ " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Author like '%" + edtcheckinfo->Text.Trim()  + "%'";

		if (!zerodisplay) {

		sql = sql + "and STK_BookInfo.Amount > 0 " ;
		}
		break;
	default:
		break;
	}

	try
	{
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	try {
		aquery->Open();
	} catch (...) {
    	MessageBoxA(0,"������������Ƿ���ȷ!","��ʾ",MB_ICONASTERISK);
		return;
	}

	if (aquery->State == dsInactive ) {
	   MessageBoxA(0,"û�и����¼!","����������",MB_ICONASTERISK);
		return;
	}
	 if (aquery->RecordCount > 1) {   //������¼

	   Tfrmcatalogselect *frm  = new Tfrmcatalogselect(Application, checkli.con , aquery);

	  if (mrOk==frm->ShowModal()) {
		   NowLocal = aquery->FieldByName("BkstackName")->AsString ;

		   /*if (LockLocalID.Pos(NowLocal) == 0 )
		   {
				NowLocal =  aquery->FieldByName("BkstackName")->AsAnsiString   + " �ѱ����������ܲ���!";
				MessageBoxA(0,NowLocal.c_str()  ,"����������",MB_ICONASTERISK);
				edtcheckinfo->Text = "";
				edtnumber->Text = "";
				edtcheckinfo->SetFocus();
				return;
		   }   */
		   TADOQuery * aq =  new TADOQuery(NULL);
		   aq->Connection = fcon;
		   sql = "select * from STK_StockInventories where states = 0 and STK_bookInfoID = " +  aquery->FieldByName("bkinfoid")->AsAnsiString ;
		   aq->Close();
		   aq->SQL->Clear();
		   aq->SQL->Add(sql);
		   aq->Open();
		   if (aq->RecordCount > 0) {
			   MessageBoxA(0,"���������̵�!","����������",MB_ICONASTERISK);
			   return;
		   }		   delete aq;

		   //aqueryupdate->Parameters->ParamByName("code")->Value = edtnum->Text ;
		   //aqueryupdate->Active = true;
		   if (!aqueryupdate->Active ) {
			   return;
		   }
		   aqueryupdate->Insert();
		   aqueryupdate->Append();
		   aqueryupdate->FieldByName("supplier")->AsAnsiString = aquery->FieldByName("SupplierName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("ISBN")->AsAnsiString = aquery->FieldByName("ISBN")->AsAnsiString  ;
		   aqueryupdate->FieldByName("localname")->AsAnsiString = aquery->FieldByName("BkstackName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("bookname")->AsAnsiString = aquery->FieldByName("name")->AsAnsiString  ;
		   aqueryupdate->FieldByName("AbbreviatedName")->AsAnsiString = aquery->FieldByName("AbbreviatedName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("actualamount")->AsAnsiString = aquery->FieldByName("Amount")->AsAnsiString  ;
		   aqueryupdate->FieldByName("supplierid")->AsAnsiString = aquery->FieldByName("SupplierID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("STK_bookInfoID")->AsAnsiString = aquery->FieldByName("STK_BookinfoID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("local")->AsInteger = aquery->FieldByName("BKstackID")->AsInteger  ;
		   aqueryupdate->FieldByName("Price")->AsInteger = aquery->FieldByName("Price")->AsFloat ;
		   aqueryupdate->FieldByName("NoteCode")->AsAnsiString = edtnum->Text   ;
				   //�ϼ�
		   localnum =  StrToInt(ltotal->Caption);
		   localnum = localnum + aqueryupdate->FieldByName("actualamount")->AsInteger ;
		   ltotal->Caption = IntToStr(localnum);
		   edtnumber->SetFocus();
		}

	 }
	  if (aquery->RecordCount == 1) {    //ֻ��һ����¼
			NowLocal = aquery->FieldByName("BkstackName")->AsString ;

			/*if (LockLocalID.Pos(NowLocal) == 0 )
			{
				NowLocal =  aquery->FieldByName("BkstackName")->AsAnsiString   + " �ѱ����������ܲ���!";
				MessageBoxA(0,NowLocal.c_str()  ,"����������",MB_ICONASTERISK);
				edtcheckinfo->Text = "";
				edtnumber->Text = "";
				edtcheckinfo->SetFocus();
				return;
			}  */

	  	   TADOQuery * aq =  new TADOQuery(NULL);
		   aq->Connection = fcon ;
		   sql = "select * from STK_StockInventories where states = 0 and STK_bookInfoID = " +  aquery->FieldByName("bkinfoid")->AsAnsiString ;
		   aq->Close();
		   aq->SQL->Clear();
		   aq->SQL->Add(sql);
		   aq->Open();
		   if (aq->RecordCount > 0) {
			   MessageBoxA(0,"���������̵�!","����������",MB_ICONASTERISK);
			   return;
		   }		   delete aq;

		   if (!aqueryupdate->Active ) {
			   return;
		   }
		   aqueryupdate->Insert();
		   aqueryupdate->Append();

		   aqueryupdate->FieldByName("supplier")->AsAnsiString = aquery->FieldByName("SupplierName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("ISBN")->AsAnsiString = aquery->FieldByName("ISBN")->AsAnsiString  ;
		   aqueryupdate->FieldByName("bookname")->AsAnsiString = aquery->FieldByName("name")->AsAnsiString  ;
		   aqueryupdate->FieldByName("localname")->AsAnsiString = aquery->FieldByName("BkstackName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("AbbreviatedName")->AsAnsiString = aquery->FieldByName("AbbreviatedName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("actualamount")->AsAnsiString = aquery->FieldByName("Amount")->AsAnsiString  ;
		   aqueryupdate->FieldByName("STK_bookInfoID")->AsAnsiString = aquery->FieldByName("STK_BookinfoID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("supplierid")->AsAnsiString = aquery->FieldByName("SupplierID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("local")->AsAnsiString = aquery->FieldByName("BK_stackID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("Price")->AsInteger = aquery->FieldByName("Price")->AsFloat ;
		   aqueryupdate->FieldByName("NoteCode")->AsAnsiString = edtnum->Text   ;
		   //�ϼ�
			localnum =  StrToInt(ltotal->Caption);
			localnum = localnum + aqueryupdate->FieldByName("actualamount")->AsInteger ;
			ltotal->Caption = IntToStr(localnum);

		   edtnumber->SetFocus();


	 }
	 if (aquery->RecordCount == 0) {
			MessageBoxA(0,"û�и����¼!","����������",MB_ICONASTERISK);
			}


	 }
	catch(...)
	{}

   }}

//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::N4Click(TObject *Sender)
{
	CatalogSearchMode = 2;
	lbsearch->Caption = "�Ա���";
}
//---------------------------------------------------------------------------


void __fastcall Tfrmadjust::N2Click(TObject *Sender)
{
	CatalogSearchMode = 3;
	lbsearch->Caption = "����";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::N3Click(TObject *Sender)
{
	  CatalogSearchMode= 5;
	  lbsearch->Caption = "����";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::ISBN1Click(TObject *Sender)
{
	  CatalogSearchMode = 4 ;
	  lbsearch->Caption = "���";
}
//---------------------------------------------------------------------------


void __fastcall Tfrmadjust::BtnNewClick(TObject *Sender)
{
	BtnNew->Enabled = false;
	BtnSave->Enabled = true;
	DBNavigator1->Enabled = false;
	AnsiString sql;
	Code = NoteCode::BuildCode(aquery,GetDBTime(aquery),m_storageID,"STK_stackAdjustHead","number");
	sql = "insert into STK_stackAdjustHead(number,adjustdate,employ)"
		 " values("+ Code +",'" + DateTimeToStr(dtpdate->DateTime )+"','"
		  + checkli.userID + "')";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->ExecSQL();

	membk->Text = "";
	edstate->Text = "δȷ�ϵ���";
	dtpdate->Date = Date();
	edtnum->Text = Code;

	aqueryupdate->Parameters->ParamByName("code")->Value = edtnum->Text;
	aqueryupdate->Active = false;
	aqueryupdate->Active = true;
	aqheader->Active = false;
	aqheader->Active = true;

	DisableInput(1);
	//edtcheckinfo->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::BtnSaveClick(TObject *Sender)
{
	if (edtnum->Text == "") {
		return;
	}
	BtnSave->Enabled = false;

	String sql;
   //	localin =   (int )cblocalin->Items->Objects[cblocalin->ItemIndex];

																		   //������
	sql = "update STK_stackAdjustHead set adjustdate = '" + DateTimeToStr(dtpdate->DateTime )
			+ "',bk = '" + membk->Text  + "' where Number = " + edtnum->Text ;

	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->ExecSQL();

}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::FormCreate(TObject *Sender)
{
	   readyData(aquery);
	   BtnNew->Click();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::BtnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::edtnumberKeyPress(TObject *Sender, wchar_t &Key)
{
   int actualamount;
   	int InputLocalID;
	String InputLocalName;
	int adjustnum;
	try {
		InputLocalID = (int)cblocalin->Items->Objects[cblocalin->ItemIndex];
	} catch (...) {
		MessageBox(0,"��ѡ����ȷ�Ŀ�λ��" ,"��ʾ",MB_ICONWARNING);
		return;
	}
	InputLocalName = cblocalin->Text ;
   if (Key == '\r')
   {
		if (edtnumber->Text == "") {
			MessageBox(0,"���������������" ,"��ʾ",MB_ICONWARNING);
			return;
		}
		if (aqueryupdate->FieldByName("local")->AsInteger == InputLocalID) {
			MessageBox(0,"������ͬ��λ�е�����" ,"������",MB_ICONWARNING);
			aqueryupdate->Delete();
			edtcheckinfo->Text = "";
			edtnumber->Text = "";
			edtcheckinfo->SetFocus();
			return;
		}
		if (StrToInt(edtnumber->Text)<0) {
			MessageBox(0,"�������븺ֵ��" ,"������",MB_ICONWARNING) ;

			edtnumber->Text = "";
			edtnumber->SetFocus();
			return;
		}
		actualamount =   aqueryupdate->FieldByName("actualamount")->AsInteger;
		if (actualamount-StrToInt(edtnumber->Text) < 0) {

			MessageBox(0,"�����������뵱ǰ�������" ,"������",MB_ICONWARNING) ;
			edtnumber->Text = "";
			edtnumber->SetFocus();
			return;
		}

        aqueryupdate->Edit();
		aqueryupdate->FieldByName("inputlocal")->AsInteger = InputLocalID;
		aqueryupdate->FieldByName("inputlocalname")->AsAnsiString = InputLocalName ;

		adjustnum =	StrToInt(ltotaladjust->Caption) ;
		adjustnum = adjustnum + StrToInt(edtnumber->Text);
		ltotaladjust->Caption = IntToStr(adjustnum);

		//aqueryupdate->Edit();
		aqueryupdate->FieldByName("amount")->AsInteger  = StrToInt(edtnumber->Text);
		aqueryupdate->UpdateBatch(arAll);
		aqueryupdate->Active = false;
		aqueryupdate->Active = true;
		aqueryupdate->Last();

		edtcheckinfo->Text = "";
		edtnumber->Text = "";
        edtcheckinfo->SetFocus();
   }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::lbsearchMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	   if (Button == mbLeft ) {
	TPoint  pt;
	 GetCursorPos(&pt);
	 pm->Popup(pt.x,pt.y);

  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::BtnDeleteClick(TObject *Sender)
{
	if (MessageBox(0,"ȷ��Ҫɾ����","��λ����",MB_ICONQUESTION|MB_OKCANCEL)== 1){
		aqueryupdate->Delete();
	}
}
void Tfrmadjust::DisableInput(int Modal)
{
	if (Modal == 0) {
		membk->Enabled = false;
		edtcheckinfo->Enabled = false;
		edtnumber->Enabled = false;
		cblocalin->Enabled = false;
		BtnDelete->Enabled = false;
		BtnOK->Enabled = false;
	}  else if (Modal == 1) {
		membk->Enabled = true;
		edtcheckinfo->Enabled = true;
		edtnumber->Enabled = true;
		cblocalin->Enabled = true;
		BtnDelete->Enabled = true;
		BtnOK->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree ;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmadjust::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {     //�鵥
		BtnView->Click();
	}
	if (Key == VK_F2) {     //��
		BtnNew->Click();
	}
	if (Key == VK_F3) {     //����
		BtnSave->Click();
	}
	if (Key == VK_F5) {     //ɾ��
		BtnDelete->Click();
	}
	if (Key == VK_F7) {     //ȷ��
		BtnOK->Click();
	}
	/*if (Key == VK_F8) {     //����
		BtnDelete->Click();
	}
	if (Key == VK_F10) {     //��ӡ
		BtnDelete->Click();
	} */
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


void __fastcall Tfrmadjust::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------



void __fastcall Tfrmadjust::BtnOKClick(TObject *Sender)
{
	if (edtnum->Text == "") {
		return;
	}
	int stgid,localin,localout,Supplierid,Bookid,booknum;


	String sql;
	if (aqueryupdate->State == dsInactive ) {
		return;
	}

   //	localin =   (int )cblocalin->Items->Objects[cblocalin->ItemIndex];

																		   //������
	sql = "update STK_stackAdjustHead set state = 1 where Number = " + edtnum->Text ;

	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->ExecSQL();

   //���µ�������
	sql = "select * from STK_stackAdjustNote where NoteCode ='" + edtnum->Text +"'";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();

	aquery->First();
	while(!aquery->Eof) {

	   if (aquery->FieldByName("amount")->AsInteger !=0 ) {

			Bookid = aquery->FieldByName("STK_bookInfoID")->AsInteger ;
			Supplierid = aquery->FieldByName("supplierid")->AsInteger;
			localout = aquery->FieldByName("local")->AsInteger;
			localin =  aquery->FieldByName("inputlocal")->AsInteger;
			booknum = aquery->FieldByName("amount")->AsInteger ;

			adosp->ProcedureName = "updateadjust";
			adosp->Parameters->Clear();
			adosp->Parameters->CreateParameter("@supplier",ftInteger ,pdInput,sizeof(int), &Supplierid);
			adosp->Parameters->CreateParameter("@outlocal",ftInteger ,pdInput,sizeof(int), &localout);
			adosp->Parameters->CreateParameter("@inlocal",ftInteger ,pdInput,sizeof(int), &localin);
			adosp->Parameters->CreateParameter("@amount",ftInteger ,pdInput,sizeof(int), &booknum);
			adosp->Parameters->CreateParameter("@Bookid",ftInteger ,pdInput,sizeof(int), &Bookid);
			adosp->ExecProc();
	   }
	   aquery->Next();
   }
   AnsiString Note;
   Note = "��λ�����ɹ������ɵ���:" + edtnum->Text;
   MessageBox(0, Note.c_str(),"��λ����",MB_ICONASTERISK);

   BtnOK->Enabled = false;
   edstate->Text = "��ȷ�ϵ���";

   DisableInput(0);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::DBNavigator1Click(TObject *Sender, TNavigateBtn Button)

{
    DelNtHeader();
	if (aqheader->FieldByName("state")->AsInteger == 1 ) {
		edstate->Text = "��ȷ�ϵ���";
		DisableInput(0);
	}
	else
	{
		edstate->Text = "δȷ�ϵ���";
		DisableInput(1);
	}
	edtnum->Text = aqheader->FieldByName("number")->AsAnsiString ;
	dtpdate->Date = aqheader->FieldByName("adjustDate")->AsDateTime ;

	aqueryupdate->Parameters->ParamByName("code")->Value = edtnum->Text;
	aqueryupdate->Active = false;
	aqueryupdate->Active = true;
	BtnNew->Enabled = true;
}
//---------------------------------------------------------------------------

void Tfrmadjust::DelNtHeader()
{
	if (aqueryupdate->IsEmpty() && edtnum->Text != "" ) {
		AnsiString sql;
		sql = "delete from  STK_stackAdjustHead where Number = " + edtnum->Text + " and Number not in(select NoteCode from STK_stackAdjustNote)";

		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmadjust::BtnViewClick(TObject *Sender)
{

	TfrmQryNoteCode *frm = new TfrmQryNoteCode(Application,0);
	frm->SetstgID(m_storageID);

	if (frm->ShowModal() == mrOk) {
		DBNavigator1->Enabled = true;
		DelNtHeader();

		AnsiString Code = frm->GetNoteCode();
		delete frm;

		AnsiString sql;
		sql = "select * from STK_stackAdjustHead where Number = " + Code;
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->IsEmpty() ) {
			return;
		}

		TLocateOptions Opts;
		Opts.Clear();
		Opts << loPartialKey;
		aqheader->Locate("id", aquery->FieldByName("id")->AsAnsiString, Opts);

		if (aquery->FieldByName("state")->AsInteger == 1 ) {
			edstate->Text = "��ȷ�Ͽ��";
			DisableInput(0);
		}
		else
		{
			edstate->Text = "δȷ�Ͽ��";
			DisableInput(1);
		}
		edtnum->Text = aquery->FieldByName("number")->AsAnsiString ;
		dtpdate->Date = aquery->FieldByName("adjustDate")->AsDateTime ;

		aqueryupdate->Parameters->ParamByName("code")->Value = edtnum->Text;
		aqueryupdate->Active = false;
		aqueryupdate->Active = true;
		BtnNew->Enabled = true;
	}

}
//---------------------------------------------------------------------------

