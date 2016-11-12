//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WholesaleMngReturnForm.h"
#include "NoteCode.h"
#include "QryNoteCodeForm.h"
#include "SetNotesForm.h"
#include "mytrace.h"
#include "SelectCustomerForm.h"
#include "RecMoneyForm.h"
#include "Print.h"
//#include "customer\customer.h"
#include "SelectCatalogForm.h"
//#include "bsprint.h"
#include "..\supplier\detailemessage.h"
#include "UnitSelectClient.h"
#include "bookQuery.h"
#include "QueryDanHao.h"
#include "Addsyslog.h"
#include "UnitClient.h"
#include   <math.h>
#include "Unitorderquery.h"
#include "Unitorderquery.h"
#include "bookhistory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzDBCmbo"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzDBGrid"
#pragma link "RzDBLbl"
#pragma link "RzCommon"
#pragma link "RzDBLook"
#pragma link "RzRadGrp"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TfrmWholesaleReturnMng *frmWholesaleReturnMng;
//---------------------------------------------------------------------------
__fastcall TfrmWholesaleReturnMng::TfrmWholesaleReturnMng(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_catalogSearchMode(0)
	, m_bsmode(BSUnknown)
	, m_opmode(OPUnknown)
	, m_supplierID(-1)
{
	m_module = MTWsaleMng;
	this->WindowState = wsMaximized ;
	ClientID = 1;
	changehead = 0;
}
//---------------------------------------------------------------------------
void TfrmWholesaleReturnMng::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = "#,##0.00" ;;
	lblOpName->Caption = m_opName;
	cmdAddNtHeader->Connection = m_con;
	spQryNtHeader->Connection = m_con;
	spQryNtHeader1->Connection = m_con;
	cmdUpdateNtHeader->Connection = m_con;
	cmdAddNote->Connection = m_con;
	cmdUpdateNote->Connection = m_con;
	cmdDelNote->Connection = m_con;
	cmdDelNtHeader->Connection = m_con;
	cmdBatchDelNote->Connection = m_con;
	cmdBatchUpdateNote->Connection = m_con;
	cmdResetNtHeader->Connection = m_con;
	spQryNtHeader1->Connection = m_con;
	cmdDelNote->Connection = m_con;
	dsetVendor->Connection = m_con;
	dsetStaff->Connection = m_con;
	dsetLkpVendor->Connection = m_con;
	dsetBkstack->Connection = m_con;
	qryrecord->Connection = m_con;
	adospcopy->Connection = m_con;
	spcopy->Connection = m_con;
	spsave->Connection = m_con;
	querydan->Connection = m_con;
	dsetBkstack->CommandText = "select ID, Name from STK_BookstackInfo where stgid = " + IntToStr(m_storageID) ;
	dsetBkstack->Active = true;
	dsetVendor->Active = true;
	dsetStaff->Active = true;
	bearsaledataset->Connection = m_con;
	bearsaledataset->Active = true;
	dsetStaff->Connection = m_con;
	sptuihuo1->Connection = m_con;
	query->Connection = m_con;
	ChangeCatalogSearchMode();
	ChangeBsmode(BSNoteSendback);
	//�˻�����
	String sql;
	sql = "select * from SYS_BSSET where name = 'pxtuihuousepassword'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	tuihuo  = query->FieldByName("value")->AsBoolean ;
	if (tuihuo) {
    	if (!CheckOperateAuthority()) {
			Close();
			return;
		}
	}

	ChangeOpmode(OPAddNtHeader);
	addnotereturnvalue = 0;
	dtpdate->Date = dbdtedtHdTime->Date  ;

	//������ʷ��ϸ
	sql = "select * from SYS_BSSET where name = 'wosaleday'" ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("value")->AsBoolean ) {
		dgrecord->Visible = true;
	}
	else
	{
		dgrecord->Visible = false;
	}
	//��ǰ�ͻ���/Ƿ�������ʾ
	sql = "select * from SYS_BSSET where name = 'checkedview'" ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("value")->AsBoolean ) {
		GroupBox3->Visible = true;
	}
	else
	{
		GroupBox3->Visible = false;
	}
	//�����޸��ۿ�
	sql = "select * from SYS_BSSET where name = 'WsalelDiscountChange'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("value")->AsBoolean  ) {
			dbnbedtDiscount->Enabled = true;
	}
	else
	{
		dbnbedtDiscount->Enabled = false;
	}
	//�����˻�����
	sql = "select * from SYS_BSSET where name = 'pxtuihuoqixian'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	pxtuihuo = query->FieldByName("bk")->AsAnsiString ;
	//С��λ��
	sql = "select * from SYS_BSSET where name = 'salexiaoshudian'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	format = "��###,###,##" + query->FieldByName("bk")->AsString ;
	dbnbedt3->DisplayFormat = "��###,###,##0.00";
	dbnbedt4->DisplayFormat = format;
	//�����ֳ��տ�
	sql = "select * from SYS_BSSET where name = 'xianchangrecive'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("value")->AsBoolean  ) {
		RzToolButton2->Enabled = true;
	}
	else
	{
		RzToolButton2->Enabled = false;
	}
	sql = "select ID,Name from SYS_StorageInfo where id  = " + IntToStr(m_storageID) ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	edstorageid->Text = query->FieldByName("ID")->AsString ;
	edstoragename->Text = query->FieldByName("Name")->AsString ;
	GetBkStackInfo();
	dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
	checkedview();
	ReadClient();
	//��ӡ��ע
	sql = "select wsprinttitle,wscontact,wstel,wsaddress,wsprintbk from sys_printtitle where stgid = " + IntToStr(m_storageID);
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	pxbk = query->FieldByName("wsprintbk")->AsAnsiString ;
	printtitle = query->FieldByName("wsprinttitle")->AsAnsiString ;
	contact = query->FieldByName("wscontact")->AsAnsiString ;
	tel = query->FieldByName("wstel")->AsAnsiString ;
	address = query->FieldByName("wsaddress")->AsAnsiString ;

	//������ʾ����
	sql = "select * from SYS_BSSET where name = 'changeDanHaoDisplay'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	ChangeDisplay  = query->FieldByName("value")->AsBoolean ;

	if (ChangeDisplay) {
	  editdanhao->Visible = true;
	  dbedtWsaleNtCode->Visible = false;
	   DBNav->Visible = true;
	   dgrecord->Columns->Items[1]->Visible = true;
	   dgrecord->Columns->Items[0]->Visible = false;
	}else
	{
	  editdanhao->Visible = false;
	  dbedtWsaleNtCode->Visible = true;
		dgrecord->Columns->Items[1]->Visible = false;
		dgrecord->Columns->Items[0]->Visible = true;
	}

	//���пͻ���ʷ��ϸ
	sql = "select * from SYS_BSSET where name = 'pxallclientdetail'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	allclient  = query->FieldByName("value")->AsBoolean ;
	//ɾ������
	sql = "select * from SYS_BSSET where name = 'pxdeleteusepassword'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	deletedetail  = query->FieldByName("value")->AsBoolean ;
	//�鵥����
	sql = "select * from SYS_BSSET where name = 'pxfindusepassword'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	find  = query->FieldByName("value")->AsBoolean ;
	//�޸ĵ�ͷ�����Ƿ�����
	sql = "select * from SYS_BSSET where name = 'pxusechange'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	changepassword  = query->FieldByName("value")->AsBoolean ;
	// �ظ���ʾ
	sql = "select * from sys_bsset where name = 'wsalesametishi'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	sametishi  = query->FieldByName("value")->AsBoolean ;
	FormView();
         if (li->FormatStr=="1") {
            newclient=true;
             RzButton1->Enabled = true;
          }else {newclient = false;
           RzButton1->Enabled = false;}
	printmodle = 0;
        checknewsupplier();
}

void __fastcall TfrmWholesaleReturnMng::FormClose(TObject *Sender, TCloseAction &Action)
{
	DelInvalidNtHeader();
	//SaveWsale(2);
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	dsetStaff->Active = false;
	dsetLkpVendor->Active = false;
	dsetBkstack->Active = false;
	dsetVendor->Active = false;
	TfrmMDIChild::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::tlbtn1Click(TObject *Sender)
{
	//ɾ��
	if (!SaveWsale(1))
	{
		return;
	}
	//DelInvalidNtHeader();
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con)
	{
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::tlbtn7Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::edtQryVendorKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		if (!dsetNtHeader->Active
			|| !dsetNote->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;
		if (!edtclient->Enabled ) {
		   return;
		}
		TfrmselectClient * frm = new TfrmselectClient(Application,m_con,edtQryVendor->Text,linfo.storageID);
	   if (mrOk == frm->ShowModal())
	   {
			//editclientname->Text = frm->GetSelect();
			ClientID = frm->GetSelectID();
			dsetNtHeader->Edit();
			dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
			dsetNtHeader->UpdateRecord();
			dblkpcbbVendorID->KeyValue =  ClientID;
			//cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)ClientID);
			edtclient->SetFocus();
			ClientView();
			edtQryVendor->Text = "";
			UpdateNtHeader();
			checkedview();
	   }
	   delete frm;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmWholesaleReturnMng::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	//
    if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}
	if (Key == '\r')
	{
		if (BtnSave->Enabled) {
			MessageBox(0,"���ȱ��������˻�����","�����˻�" ,MB_ICONEXCLAMATION);
			return;
		}
		if (!dsetNote->Active || !dsetNtHeader->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;

		if (edtCatalog->Text == "")
		{
			ChangeCatalogSearchMode();
		}
		else
		{
            float price;
			if (m_catalogSearchMode == 6) {
				try {
					price = StrToFloat(edtCatalog->Text.Trim());
				} catch (...) {
					MessageBox(0,"��������ȷ�Ķ��ۣ�","�����˻�" ,MB_ICONEXCLAMATION);
					return;
				}
			}

            if (chqikan->Checked && m_catalogSearchMode != 1) {
				edqikan->SetFocus();
				return;
			}
			if (m_catalogSearchMode == 1 && chqikan->Checked) {
				if (edtCatalog->Text.Length() == 15 ) {
					edqikan->Text = edtCatalog->Text.SubString(14,2);
					edtCatalog->Text = edtCatalog->Text.SubString(0,13);
				}
				else
				{
                	edqikan->SetFocus();
					return;
				}
			}


			switch (m_catalogSearchMode)
			{
			case 1:
			 //	if (edtCatalog->Text.Length() != 13)
			  //	{
			   //		ShowMessage("�����������");
			  //		return;
			 //	}
			case 6:
			case 2:
			case 3:
			case 5:
				{
					TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
					LandInfo li;
					li.app = m_app;
					li.con = m_con;
					li.userID = m_userID;
					li.storageID = m_storageID;
					frm->Init(&li);
					frm->DoModalType = 7; //һ�㷢���˻�ģʽ
					frm->WholeReturnfrm = this;
					frm->qikan = chqikan->Checked ;
					frm->qikanhao = edqikan->Text ;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					if (mrOk == frm->ShowModal())
					{
						int supplierID = -1,catalogID = -1;
						if (frm->SelectAll) {
							 for (int i = 0; i < frm->lengthint  ; i++) {
								 cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BKSKid[i]);

								 if (!saleenable(frm->stkbkid[i])) {
									return;
								 }
								 if (AddNote(frm->SupplierID[i],frm->BkcatalogiD[i])) {

									 Key = 0;
									 Perform(WM_NEXTDLGCTL, 0, 0);
									 historyview();

								 }  else
								 {


								 }

							 }

						}else
						{
							frm->GetSelectResult(supplierID, catalogID);
							if (!retailreturn(catalogID)) {
                            	return;
							}
							if (frm->addbkinfo ) {
								supplierID = 0;
							}
							if (supplierID >= 0 && catalogID >= 0)
							{

								if (!frm->addbkinfo) {
                                	cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BSKid);
                                	if (!saleenable(frm->BKinfoid)) {
										return;
									}
								}

                                TLocateOptions   Opts;
								Opts.Clear();
								Opts   <<   loPartialKey;
								String   str   = AnsiString(frm->BKinfoid);
								if ( !dsetNote->Locate("BkInfoID",str,Opts)){
								if (AddNote(supplierID, catalogID))
								{
									if (addnotereturnvalue == -2) {
										 MessageBox(0,"��������������ۣ�","һ�㷢��" ,MB_ICONEXCLAMATION);
										 edtCatalog->Text = "";
                                         addnotereturnvalue = 0;
										} else
										{
											Key=0;
											historyview();
											if (chfoceset->Checked) {
												if (chfsamount->Checked ) {
													dbnbedtAmount->SetFocus();
												}
												else if (chfsdiscount->Checked ) {
													dbnbedtDiscount->SetFocus();
												}
												else if (chfsluru->Checked) {
													edtCatalog->SetFocus();
												}
											}
											else
											{
                                            	dbnbedtAmount->SetFocus();
											}

										 }
											editprice->Text =  FormatFloat("0.00", dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value * 0.01);
								}
								else

									ShowMessage("����޸���!");
								}
								else
								{
									if (sametishi) {
										MessageBox(0,"����ͬ��¼���ʵ��","��ʾ" ,MB_ICONEXCLAMATION);
									}
									dbgrdNote->SelectedRows->CurrentRowSelected = true;
									dbgrdNote->SetFocus();
							   		dbnbedtAmount->SetFocus();
								}
							}
						}
					}
					delete frm;
					edtCatalog->Text = "";
					if (dblkpcbbVendorID->Text == "") {
						dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
					}
				}
				break;
            default:
				;
			}
		}
    }
}
//---------------------------------------------------------------------------

void TfrmWholesaleReturnMng::ChangeCatalogSearchMode()
{
	if (m_catalogSearchMode==3) {
		m_catalogSearchMode=5;
	}else
	{
	m_catalogSearchMode++;  }
	if (m_catalogSearchMode >= 7)
	{
		m_catalogSearchMode = 1;
	}

	switch (m_catalogSearchMode)
	{
	case 1:
    	if (chqikan->Checked ) {
			edtCatalog->MaxLength = 15;
		}
		else
		{
			edtCatalog->MaxLength = 13;
		}
		lblCatalog->Caption = "���";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "�Ա���";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "����";
		break;
	case 5:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "����";
		break;
	case 6:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "����";
		break;
    default:
        break;
	}
}

//---------------------------------------------------------------------------
void TfrmWholesaleReturnMng::ChangeBsmode(BSMode bsmode)
{
	if (bsmode != m_bsmode)
	{
		m_bsmode = bsmode;
    }

	if (m_bsmode == BSNote)
	{
		mniBsNote->Checked = true;
		mniBsNoteSendback->Checked = false;
	}
	else if (m_bsmode == BSNoteSendback)
	{
		mniBsNote->Checked = false;
		mniBsNoteSendback->Checked = true;
	}
}

void TfrmWholesaleReturnMng::ChangeOpmode(OPMode opmode)
{
	if (opmode == m_opmode
		&& (opmode == OPDelNtHeader))
		return;

	//1Ϊ�鵥ģʽ 2Ϊ���ӵ�ͷģʽ 3Ϊɾ����ͷģʽ 4Ϊ���ӵ�ģʽ 5Ϊɾ����ģʽ 6Ϊͳһģʽ 7Ϊ�ֳ��տ�ģʽ
	switch (opmode)
	{
	case OPFind:
		{
			if (!SaveWsale(1))
			{
				return;
			}

            AnsiString sql;

			if (find) {
            	if (!CheckOperateAuthority())
					return;
			}
			DBNav->Enabled = true;

			Tfrmorderquery* frm = new Tfrmorderquery(Application,m_con,m_storageID,2,1,false);
				if (frm->ShowModal() == mrOk)
				{
					DelInvalidNtHeader();
					edtCatalog->Text = "";
					edtQryVendor->Text = "";
					AnsiString code = frm->GetNoteCode();
					AnsiString sqlwhere = frm->GetWhere();
					try
					{
						QryNtHeader(code);
						String sql;
						if (sqlwhere != "") {
							sql = "select * from BS_WsaleNoteHeader " + sqlwhere;
							querydan->Close();
							querydan->SQL->Clear();
							querydan->SQL->Add(sql);
							querydan->Open();
							TLocateOptions Opts;
							Opts.Clear();
							Opts << loPartialKey;
							querydan->Locate("WsaleNtCode", code, Opts);
						}
					}
					__finally
					{

					}
					m_opmode = opmode;
					dtpdate->Date =  dbdtedtHdTime->Date ;//��������
					delete frm;

					edtclient->Enabled = false;
					BtnSave->Enabled = false;
					SaveOrNot = true;
					RzButton1->Enabled = false;
					spselectClient->Enabled = false;
					dbnbedtAddCosts->Enabled = false;
					dblkpcbbStaffID->Enabled = false;
				}

        }
		break;
	case OPAddNtHeader:
		{
			RzToolButton2->Enabled = true;
			edtclient->Enabled = true;


                         if (newclient) {
                  RzButton1->Enabled = true;
                }else RzButton1->Enabled = false;

			spselectClient->Enabled = true;
			//����ϴ�������ģʽ������û�мӽ��κ����ݣ���������
			if (m_opmode == OPAddNtHeader &&
				dsetNote->Active && dsetNote->RecordCount < 1)
				DelInvalidNtHeader();

			if (m_opmode == OPDelNote
				&& dsetNote->Active && dsetNote->RecordCount < 1)
				DelInvalidNtHeader();

			edtCatalog->Text = "";
			edtQryVendor->Text = "";
			editprice->Text = "0.00";
			AddNtHeader();
			m_opmode = opmode;
			edtQryVendor->SetFocus();
			dtpdate->Date = dbdtedtHdTime->Date ;
			//cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)dsetVendor->FieldByName("ID")->AsInteger );
        }
		break;
	case OPDelNtHeader:
		{
			RzToolButton2->Enabled = true;
			if (!CheckOperateAuthority())
				return;

			edtCatalog->Text = "";
			edtQryVendor->Text = "";
//			DelNtHeader();
			m_opmode = opmode;
        }
		break;
	case OPAddNote:
		RzToolButton2->Enabled = true;
    	edtCatalog->Text = "";
		edtCatalog->SetFocus();
		m_opmode = opmode;
		break;
	case OPDelNote:
    	if (dsetNote->IsEmpty() ) {
            	return;
		}
		RzToolButton2->Enabled = true;
		if (deletedetail) {
			if (!CheckOperateAuthority())
				return;
		}
		else
		{
        	if (MessageBoxA(0,"�Ƿ�Ҫɾ��������¼?","ѯ��",MB_ICONQUESTION|MB_OKCANCEL)!=1 )
				return;
		}
		DelNote();

		ResetNtHeader();
    	m_opmode = opmode;
		break;
	case OPSetNotes:
		RzToolButton2->Enabled = true;
    	if (dsetNote->Active && dsetNote->RecordCount >= 1)
		{
			//ͳһģʽ
			if (dbgrdNote->SelectedRows->Count == 0 || dbgrdNote->SelectedRows->Count == 1) {
            	for (int i = 1; i <= dsetNote->RecordCount ; i++) {
					dbgrdNote->DataSource->DataSet->RecNo = i;
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
				}
			}
			TfrmSetNotes* frm = new TfrmSetNotes(this);
			frm->ChangeBsmode(m_bsmode);
			if (frm->ShowModal() == mrOk)
			{
				int amount = 0;
				float discount = 0;
				bool bsetAmount = frm->GetAmount(amount);
				bool bsetDiscount = frm->GetDiscount(discount);
				if (bsetAmount && bsetDiscount)
				{
					BatchSetNotes(amount, discount, 1);
				}
				else if (bsetAmount && !bsetDiscount)
				{
					BatchSetNotes(amount, discount, 2);
				}
				else if (!bsetAmount && bsetDiscount)
				{
                	BatchSetNotes(amount, discount, 3);
				}
				else
				{

                }
			}
			delete frm;
			m_opmode = opmode;
        }
		break;
	case OPRecCash:
		//�ֳ��տ�ģʽ
		if (editdanhao->Text == "") {
			return;
		}
    	if (!SaveWsale(1))
		{
			return;
		}
    	RzToolButton2->Enabled = true;

		if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
		{
			//���Ȱ��޸ĵĸ���һ�¹�
			dbgrdNote->SetFocus();
			//��ΰ���������ˢ��һ�¹�
			QryNtHeader();
			//
			/*String NtHeader = dbedtWsaleNtCode->Text.Trim(),Headerdate;
			if (NtHeader.Length() == 13 ) {
				Headerdate = NtHeader.SubString(0,4)+ "-" + NtHeader.SubString(5,2) + "-" + NtHeader.SubString(7,2);
			}
			else if(NtHeader.Length() == 14)
			{
				Headerdate = NtHeader.SubString(1,4)+ "-" + NtHeader.SubString(6,2) + "-" + NtHeader.SubString(8,2);
			}
			else if (NtHeader.Length() == 15) {
				Headerdate = NtHeader.SubString(2,4)+ "-" + NtHeader.SubString(7,2) + "-" + NtHeader.SubString(9,2);
			}
			if (StrToDate(Headerdate) != Date()) {
				MessageBox(0,"�ֳ��տ�ֻ���յ��յģ�","һ�㷢���˻�" ,MB_OK);
				return;
			}   */
			if (StrToDate(dsetNtHeader->FieldByName("HdTime")->AsAnsiString ) != Date()  ) {
				MessageBox(0,"�ֳ��տ�ֻ���յ��յģ�","һ�㷢���˻�" ,MB_OK);
				return;
			}
			TfrmRecMoney* frm = new TfrmRecMoney(this);
			frm->format = format;
			frm->SetDiscountedPrice(dsetNtHeader->FieldByName("DiscountedPrice")->AsFloat);
			frm->SetChecked(dsetNtHeader->FieldByName("Checked")->AsFloat);
			frm->lbl2->Caption = "�ֳ��տ�";
			frm->RzLabel1->Caption = "Ӧ�ս��";
			if (mrOk == frm->ShowModal())
			{
				if (frm->numedtUnchecked ->Value > 0) {
					if (MessageBox(0,"�㻹��δ����Ƿ������","�ֳ��տ�",MB_ICONQUESTION|MB_OKCANCEL)!=1) {
                        frm->ShowModal();
						return;
					}
				}
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("Checked")->AsFloat =
				dsetNtHeader->FieldByName("Checked")->AsFloat + frm->GetReceived();
				UpdateNtHeader();
				AnsiString Code = NoteCode::BuildCode(query, GetDBTime(query), 0, "FN_CUSEndMoneyDocuments", "MoneyCode");
				AnsiString sql;
				sql = "insert into FN_CUSEndMoneyDocuments (MoneyCode,date,state,type,userid,CustmerName,ClearingType,Clearingstyle,cusid) values ("+Code+",getdate(),1,2," + IntToStr(m_userID) +",'" + edtclient->Text + "','�ֳ��տ�','�ֽ�'," + IntToStr(ClientID) + ")";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
				sql = "insert into FN_CUSEndMoneyDtails(EndMoneyDocumentID,stgntcode,thistime,type,CodeStr) values(" + Code + "," + dsetNtHeader->FieldByName("WsaleNtCode")->AsAnsiString + "," + FloatToStr(frm->GetReceived()) + ",2,'" + dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString + "')";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
			}
			delete frm;
		}
    	m_opmode = opmode;
    	break;
    default:
        break;
	}
}

void TfrmWholesaleReturnMng::BatchSetNotes(int amount, float discount, int mode)
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		String ids = "-1";
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			if (mode != 3) {
				if (tuihuocatch(abs(amount),dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
					ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				}
			}
			else
			{
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
			}
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			if (mode != 3) {
				if (tuihuocatch(abs(amount),dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
					ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				}
			}
			else
			{
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
			}
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				if (mode != 3) {
					if (tuihuocatch(abs(amount),dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
						ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
					}
				}
				else
				{
					ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				}
			}
		}
		else
			return;

		switch(mode)
		{
		case 1://���߾�����
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
            cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 2;
			cmdBatchUpdateNote->Execute();
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
				QryNtHeader();
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			break;
		case 2://ֻ����Amount
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = "";
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 2;
			cmdBatchUpdateNote->Execute();
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
				QryNtHeader();
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			break;
		case 3://ֻ����Discount
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = "";
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 2;
			cmdBatchUpdateNote->Execute();
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
				QryNtHeader();
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			break;
		default:
			break;
		}
	}
}

void __fastcall TfrmWholesaleReturnMng::mniBsNoteSendbackClick(TObject *Sender)
{
	//���ӵ�������
	TMenuItem* item = dynamic_cast<TMenuItem*>(Sender);
	if (item != NULL)
	{
		if (item->Tag == BSNoteSendback && !CheckOperateAuthority())
			return;

		ChangeBsmode(item->Tag);
		ChangeOpmode(OPAddNtHeader);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmWholesaleReturnMng::tlbtn4Click(TObject *Sender)
{
	//Excel����
	//Excel����
	if (!SaveWsale(1))
	{
		return;
	}
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		DbgridToExcel(dbgrdNote);
	}
}
//---------------------------------------------------------------------------
//Excel��������
bool __fastcall TfrmWholesaleReturnMng::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = StringReplace(edtclient->Text+editdanhao->Text ,"\\","-",TReplaceFlags()<<rfReplaceAll) + "�����˻���";
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
		path =  DBPath;
	}
	else
	{
		return false;
	}

	if(FileExists(path))
		try {
			DeleteFileA(path);
		} catch (...) {
			return false;
		}

	/*int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   //iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());*/

    Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");

	int t1= 0;
	temptext = "\n";
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			/*if (printmodle == 0 && (dbg->Columns ->Items [q]->Title ->Caption == "�ۿ�" ||dbg->Columns ->Items [q]->Title ->Caption == "ʵ��")) {

			}
			else
			{
            	temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
			}*/
		}
	}
	//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
                	t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );
					//temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				/*else if (dbg->Columns ->Items [j-1]->FieldName == "CatalogName") {
                	AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					temptext = temptext + bookname + ",";
				}*/
				else if (dbg->Columns ->Items [j-1]->FieldName == "id" || dbg->Columns ->Items [j-1]->FieldName == "backdot"){

				}
				else
				{
					/*if (printmodle == 0 && (dbg->Columns ->Items [j-1]->FieldName == "DiscountedPrice" || dbg->Columns ->Items [j-1]->FieldName == "Discount")) {

					}
					else
					{
						temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					} */
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
			}
		}
		//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
    R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+2,t1)); //ȡ�úϲ�������
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","�ϼ�");
	temptext = dbnbedt2->Text ;
	v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );
	temptext = dbnbedt3->Text ;
	v.OlePropertyGet("Cells",t2+2+n,11).OlePropertySet("Value",temptext .c_str() );
	temptext = dbnbedt4->Text ;
	v.OlePropertyGet("Cells",t2+2+n,12).OlePropertySet("Value",temptext .c_str() );
	dbg->DataSource ->DataSet->EnableControls();

	try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (Exception &E) {
		//ShowMessage(E.Message);
	}

	/*AnsiString pxamount,mayang,shiyang;
	mayang =  dbnbedt3->Text;
	shiyang = dbnbedt4->Text;
	pxamount = dbnbedt2->Text;
	mayang = StringReplace(mayang , ",","",TReplaceFlags()<<rfReplaceAll);
	shiyang = StringReplace(shiyang , ",","",TReplaceFlags()<<rfReplaceAll);
	pxamount = StringReplace(pxamount , ",","",TReplaceFlags()<<rfReplaceAll);
	temptext = "\n";
	if (printmodle == 0) {
		temptext = temptext + "�ϼ�,,,,,,,," + pxamount + ",'" + mayang ;
	}
	else
	{
		temptext = temptext + "�ϼ�,,,,,,,," + pxamount + ",,'" + mayang + ",'" + shiyang ;
	}

	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"������ϣ�","��ʾ" ,MB_OK);   */
	return false;
}
//---------------------------------------------------------------------------}
//---------------------------------------------------------------------------
void TfrmWholesaleReturnMng::QryNtHeader(String code, bool qrybkstack)
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	spQryNtHeader1->Parameters->ParamByName("@NtCode")->Value = code;
	spQryNtHeader1->Parameters->ParamByName("@Bsmode")->Value = 2;
	MYTRACEF(_T("query note header @NtCode=%S"), code.c_str());
	try
	{
		spQryNtHeader1->Active = true;
		dsrcNtHeader->DataSet = NULL;
		dsetNtHeader->Recordset = spQryNtHeader1->Recordset;
		dsrcNtHeader->DataSet = dsetNtHeader;
		dsetNtHeader->Last();
		int count = 0;
		dsrcNote->DataSet = NULL;
		dsetNote->AfterScroll = NULL;
		dsetNote->Recordset = spQryNtHeader1->NextRecordset(count);
		dsrcNote->DataSet = dsetNote;
		dsetNote->Last();
		dbnbedt2->Visible = true;
		dbnbedt3->Visible = true;
		dbnbedt4->Visible = true;

		dsetNote->AfterScroll = dsetNoteAfterScroll;
		ClientID = dsrcNtHeader->DataSet->FieldByName("VendorID")->Value;
		ClientView();
		checkedview();
		if (qrybkstack)
		{
            QryBkstack();
		}
		editdanhao->Text = dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "��###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "��###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "��###,###,##0.00";
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		dtpdate->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 ) {
			grpbxNote->Enabled = false;
			tlbtnAddNote->Enabled = false;
			tlbtn2->Enabled = false;
			tlbtn3->Enabled = false;
			Image1->Visible = true;
		}
		else
		{
			grpbxNote->Enabled = true;
			tlbtnAddNote->Enabled = true;
			tlbtn2->Enabled = true;
			tlbtn3->Enabled = true;
			Image1->Visible = false;
		}

                lock(dsetNtHeader->FieldByName("lock")->AsInteger);
	}
	catch(...)
	{
		//ShowMessage("�õ������ڣ�");
	}
}

void TfrmWholesaleReturnMng::QryNtHeader(bool qrybkstack)
{
	//�����ѯ֮ǰ�ĵ�ǰ���¼ID
	int noteID = 0;
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
        noteID = dsetNote->FieldByName("ID")->AsInteger;
	}
	//��ѯ��ͷ
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		spQryNtHeader1->Active = false;
		spQryNtHeader->Active = false;
		spQryNtHeader->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger;
		spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
		try
		{
			spQryNtHeader->Active = true;
			dsrcNtHeader->DataSet = NULL;
			dsetNtHeader->Recordset = spQryNtHeader->Recordset;
			dsrcNtHeader->DataSet = dsetNtHeader;
			dsetNtHeader->Last();
			int count = 0;
			dsrcNote->DataSet = NULL;
			dsetNote->AfterScroll = NULL;
			dsetNote->Recordset = spQryNtHeader->NextRecordset(count);
			dsrcNote->DataSet = dsetNote;
			if (noteID > 0)//����ǰ��¼��ID���µ�����noteID
			{
                TLocateOptions Opts;
				Opts.Clear();
				Opts << loPartialKey;
				if (!dsetNote->Locate("ID", noteID, Opts))
					dsetNote->Last();
			}
			else
			{
				dsetNote->Last();
			}
			dsetNote->AfterScroll = dsetNoteAfterScroll;
			ClientID = dsrcNtHeader->DataSet->FieldByName("VendorID")->Value;
			ClientView();
			checkedview();
			if (qrybkstack)
			{
				QryBkstack();
			}
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "��###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "��###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "��###,###,##0.00";
			operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
			dtpdate->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
			membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
            if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 ) {
				grpbxNote->Enabled = false;
				tlbtnAddNote->Enabled = false;
				tlbtn2->Enabled = false;
				tlbtn3->Enabled = false;
				Image1->Visible = true;
			}
			else
			{
				grpbxNote->Enabled = true;
				tlbtnAddNote->Enabled = true;
				tlbtn2->Enabled = true;
				tlbtn3->Enabled = true;
				Image1->Visible = false;
			}
                         lock(dsetNtHeader->FieldByName("lock")->AsInteger);
		}
		catch(...)
		{
			//ShowMessage("�õ������ڣ�");
		}
	}
}

void TfrmWholesaleReturnMng::QryNtHeader(int id, bool qrybkstack)
{
	//��ѯ��ͷ
	spQryNtHeader1->Active = false;
	spQryNtHeader->Active = false;
	spQryNtHeader->Parameters->ParamByName("@ID")->Value = id;
	spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
	try
	{
		spQryNtHeader->Active = true;
		dsrcNtHeader->DataSet = NULL;
		dsetNtHeader->Recordset = spQryNtHeader->Recordset;
		dsrcNtHeader->DataSet = dsetNtHeader;
		dsetNtHeader->Last();
		int count = 0;
		dsrcNote->DataSet = NULL;
		dsetNote->AfterScroll = NULL;
		dsetNote->Recordset = spQryNtHeader->NextRecordset(count);
		dsrcNote->DataSet = dsetNote;
		dsetNote->Last();
		dsetNote->AfterScroll = dsetNoteAfterScroll;
		ClientID = dsrcNtHeader->DataSet->FieldByName("VendorID")->Value;
		ClientView();
		checkedview();
		if (qrybkstack)
		{
			QryBkstack();
		}
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "��###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "��###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "��###,###,##0.00";
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		dtpdate->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 ) {
			grpbxNote->Enabled = false;
			tlbtnAddNote->Enabled = false;
			tlbtn2->Enabled = false;
			tlbtn3->Enabled = false;
			Image1->Visible = true;
		}
		else
		{
			grpbxNote->Enabled = true;
			tlbtnAddNote->Enabled = true;
			tlbtn2->Enabled = true;
			tlbtn3->Enabled = true;
			Image1->Visible = false;
		}
                 lock(dsetNtHeader->FieldByName("lock")->AsInteger);
	}
	catch(...)
	{
    	//ShowMessage("�õ������ڣ�");
    }
}

void TfrmWholesaleReturnMng::AddNtHeader()
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
	cmdAddNtHeader->Parameters->ParamByName("@CODEMODE")->Value = 1;
	MYTRACEF(_T("add note header @StgID=%d,@OperatorID=%d,@Bsmode=%d"),m_storageID,m_userID,2);
	cmdAddNtHeader->Execute();
	int id = cmdAddNtHeader->Parameters->ParamByName("@RETURN_VALUE")->Value;
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
		QryNtHeader(id);
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
}

void TfrmWholesaleReturnMng::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0 && dsetNtHeader->FieldByName("WsaleNtCode")->AsInteger == 0)
	{
		DelNtHeader();
    }
}

void TfrmWholesaleReturnMng::DelNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdDelNtHeader->Parameters->ParamByName("@ID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		int id = dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdDelNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
		MYTRACEF(_T("del note header @ID=%d,@Bsmode=%d"), id, 2);
		cmdDelNtHeader->Execute();
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
			//QryNtHeader(id);
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

void TfrmWholesaleReturnMng::UpdateNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdUpdateNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@HdTime")->Value =
			dsetNtHeader->FieldByName("HdTime")->AsDateTime;
		cmdUpdateNtHeader->Parameters->ParamByName("@StgID")->Value =
			dsetNtHeader->FieldByName("StgID")->AsInteger;
		if (dsetNtHeader->FieldByName("StaffID")->AsString != "")
			cmdUpdateNtHeader->Parameters->ParamByName("@StaffID")->Value =
				dsetNtHeader->FieldByName("StaffID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@AddCosts")->Value =
			abs(dsetNtHeader->FieldByName("AddCosts")->AsFloat);
		cmdUpdateNtHeader->Parameters->ParamByName("@Remarks")->Value =
			dsetNtHeader->FieldByName("Remarks")->AsWideString;
		cmdUpdateNtHeader->Parameters->ParamByName("@CustomerID")->Value =
			dsetNtHeader->FieldByName("VendorID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@Cash")->Value =
			dsetNtHeader->FieldByName("Checked")->AsFloat;
		if (dsetNtHeader->FieldByName("DiscountedPrice")->AsFloat > 0 &&
			dsetNtHeader->FieldByName("Checked")->AsFloat >= dsetNtHeader->FieldByName("DiscountedPrice")->AsFloat)
		{
			cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value = 1;
		}
		else if (dsetNtHeader->FieldByName("DiscountedPrice")->AsFloat < 0 &&
			dsetNtHeader->FieldByName("Checked")->AsFloat <= dsetNtHeader->FieldByName("DiscountedPrice")->AsFloat)
		{
			cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value = 1;
		}
		else
		{
			cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value =
				dsetNtHeader->FieldByName("State")->AsInteger;;
		}
//		MYTRACEF(_T("ID=%d,HdTime=%S,StgID=%d,StaffID=%d,AddCosts=%s,Remarks=%S,CustomerID=%d,Cash=%s,State=%d")
//			, dsetNtHeader->FieldByName("ID")->AsInteger
//			, dsetNtHeader->FieldByName("HdTime")->AsString.c_str()
//			, dsetNtHeader->FieldByName("StgID")->AsInteger
//			, dsetNtHeader->FieldByName("StaffID")->AsInteger
//			, FloatToCStr(cmdUpdateNtHeader->Parameters->ParamByName("@AddCosts")->Value.VDouble)
//			, dsetNtHeader->FieldByName("Remarks")->AsWideString.c_str()
//			, dsetNtHeader->FieldByName("VendorID")->AsInteger
//			, FloatToCStr(dsetNtHeader->FieldByName("Checked")->AsFloat)
//			, cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value.VInteger);
		cmdUpdateNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
		cmdUpdateNtHeader->Execute();

		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
			QryNtHeader();
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

bool TfrmWholesaleReturnMng::AddNote(int supplierID, int catalogID)
{
	bool result = false;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		if (pxtuihuo != "" && pxtuihuo != "0") {
        	AnsiString sql;
			sql = "select BS_WsaleNote.* from BS_WsaleNote left join BS_WsaleNoteHeader "
				" on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id "
				" left join stk_bookinfo on BS_WsaleNote.bkinfoid = stk_bookinfo.id "
				" where stk_bookinfo.bkcatalogid = " + IntToStr(catalogID) + " and BS_WsaleNoteHeader.VendorID = " + IntToStr(ClientID) + " and datediff(day,dateadd(month,-" + pxtuihuo + ",getdate()),HdTime) >= 0 ";
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount == 0) {
				MessageBoxA(0,"����û�з��������߸��鷢�����ڳ����˻����ޣ�","��ʾ",MB_ICONEXCLAMATION);
				return false;
			}
		}

		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
			= catalogID;
		cmdAddNote->Parameters->ParamByName("@SupplierID")->Value = supplierID;
		cmdAddNote->Parameters->ParamByName("@bkstackID")->Value = (int)(cbbkstackID->Items->Objects[cbbkstackID->ItemIndex]);
		cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 9;
		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
		if (ret > 0)//����ɹ�
		{
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
				QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "��###,###,##0.00";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "��###,###,##0.00";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "��###,###,##0.00";
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}

			if (dsetNtHeader->FieldByName("printcount")->AsInteger > 0 ) {
				if (ChangeDisplay) {
					logmessage = "����һ�㷢���˻���" + dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
				}
				else
				{
					logmessage = "����һ�㷢���˻���" + dsetNtHeader->FieldByName("WsaleNtCode")->AsAnsiString ;
				}
				logmessage = logmessage + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "��";
				AddEvent(1,"һ�㷢���˻�����",m_userID,m_storageID,logmessage,linfo.con);
			}

			result = true;
		}
		else if (ret == 0)//���޴���
		{

		}
		else if (ret == -1)//��������
		{

		}
		else if (ret == -2) {
				  //addnotereturnvalue = -2;
                        //�����
				  result = true;
		}

	}
	return result;
}
void TfrmWholesaleReturnMng::UpdateNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
        if (dsetNtHeader->FieldByName("printcount")->AsInteger > 0 ) {
			AnsiString sql;
			sql = "select amount,discount from BS_WsaleNote where id = " + dsetNote->FieldByName("ID")->AsAnsiString;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			float discount;
			int amount;
			amount = query->FieldByName("amount")->AsInteger ;
			discount = query->FieldByName("discount")->AsFloat ;
			AnsiString ss;
			if (amount != - abs(dsetNote->FieldByName("Amount")->AsInteger)) {
				ss = "����" + IntToStr(amount) + "Ϊ-" + dsetNote->FieldByName("Amount")->AsAnsiString;
			}
			if (discount != fabs(dsetNote->FieldByName("Discount")->AsFloat)) {
				ss = ss + "�ۿ�" + FloatToStr(discount) + "Ϊ" + dsetNote->FieldByName("Discount")->AsAnsiString;
			}
			if (ss != "") {
            	if (ChangeDisplay) {
					logmessage = "�޸�һ�㷢���˻���" + dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
				}
				else
				{
					logmessage = "�޸�һ�㷢���˻���" + dsetNtHeader->FieldByName("WsaleNtCode")->AsAnsiString ;
				}
				logmessage = logmessage + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "��";
                logmessage = logmessage + ss;
				AddEvent(1,"һ�㷢���˻�����",m_userID,m_storageID,logmessage,linfo.con);
			}
		}

		cmdUpdateNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
			= - abs(dsetNote->FieldByName("Amount")->AsInteger);
		cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
			= fabs(dsetNote->FieldByName("Discount")->AsFloat);
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 2;
		cmdUpdateNote->Execute();
	}
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
		QryNtHeader();
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "��###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "��###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "��###,###,##0.00";
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
}
void TfrmWholesaleReturnMng::DelNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdDelNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
			cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 2;
			if (ChangeDisplay) {
				logmessage = "ɾ��һ�㷢���˻���" + dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "ɾ��һ�㷢���˻���" + dsetNtHeader->FieldByName("WsaleNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "��";
			AddEvent(1,"һ�㷢���˻�����",m_userID,m_storageID,logmessage,linfo.con);
			cmdDelNote->Execute();
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			String ids = "";
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = ids + dsetNote->FieldByName("ID")->AsString;
			if (ChangeDisplay) {
				logmessage = "ɾ��һ�㷢���˻���" + dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "ɾ��һ�㷢���˻���" + dsetNtHeader->FieldByName("WsaleNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "��";
			AddEvent(1,"һ�㷢���˻�����",m_userID,m_storageID,logmessage,linfo.con);
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				if (ChangeDisplay) {
					logmessage = "ɾ��һ�㷢���˻���" + dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
				}
				else
				{
					logmessage = "ɾ��һ�㷢���˻���" + dsetNtHeader->FieldByName("WsaleNtCode")->AsAnsiString ;
				}
				logmessage = logmessage + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "��";
				AddEvent(1,"һ�㷢���˻�����",m_userID,m_storageID,logmessage,linfo.con);
			}
			cmdBatchDelNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchDelNote->Parameters->ParamByName("@Bsmode")->Value = 2;
			cmdBatchDelNote->Execute();
		}
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
			QryNtHeader();
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

void __fastcall TfrmWholesaleReturnMng::dblkpcbbBkstackIDKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		tlbtn1Click(tlbtnAddNote);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmWholesaleReturnMng::dblkpcbbVendorIDKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		if (dsetNote->FieldByName("BkInfoID")->AsString == "") {
        	return;
		}
		Key = 0;
		if (dbnbedtAmount->Text == "") {
			dbnbedtAmount->Text ="0";
		}

		if (tuihuocatch(dbnbedtAmount->IntValue,dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
        	if (chfoceset->Checked) {
				if (chfsdiscount->Checked) {
					Perform(WM_NEXTDLGCTL, 0, 0);
				}
				else if (chfsluru->Checked) {
					edtCatalog->SetFocus();
				}
				else if (chfsamount->Checked) {
					if (!dsetNote->Eof) {
						dbgrdNote->SetFocus();
						dsetNote->Next();
						dbgrdNote->SelectedRows->CurrentRowSelected = true;
						dbnbedtAmount->SetFocus();
					}
				}
			}
			else
			{
				Perform(WM_NEXTDLGCTL, 0, 0);
			}
		}
		else
		{
			MessageBoxA(0,"�˻��������ڷ���������","����",MB_ICONEXCLAMATION);
			dbnbedtAmount->Value = 0;
		}
	}
}
//---------------------------------------------------------------------------

bool TfrmWholesaleReturnMng::tuihuocatch(int amount,int bkcatalogid)
{
	if (bearsaledataset->FieldByName("value")->AsBoolean) {
		AnsiString sql;
		sql = "select sum(BS_WsaleNote.amount) as amount from BS_WsaleNote left join BS_WsaleNoteHeader "
			" on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id "
			" left join stk_bookinfo on BS_WsaleNote.bkinfoid = stk_bookinfo.id "
			" where stk_bookinfo.bkcatalogid = " + IntToStr(bkcatalogid) + " and BS_WsaleNoteHeader.VendorID = " + IntToStr(ClientID) + " and BS_WsaleNote.id <> " + dsetNote->FieldByName("id")->AsAnsiString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (amount > query->FieldByName("amount")->AsInteger) {
        	return false;
		}
		else
		{
        	return true;
		}
	}
	else
	{
		return true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dblkpcbbStaffIDExit(TObject *Sender)
{
	UpdateNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbnbedtAmountExit(TObject *Sender)
{
	UpdateNote();
	historyview();
		editprice->Text =  FormatFloat("0.00", dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value * 0.01);
	if (dblkpcbbVendorID->Text == "") {
		dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
	}
}
//---------------------------------------------------------------------------

void TfrmWholesaleReturnMng::Print(int modle,int type,int printid)//modle 1Ԥ����2��ӡ type 0 Ĭ�Ϸ��� 1 ָ������  prinid ����id
{
	if (!SaveWsale(1))
	{
		return;
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->stgid = m_storageID;
                frm->booltuihuo = true;
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString,0);

		frm->DanhaoChange = ChangeDisplay ;                      //change danhao
		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

		if (modle == 1) {
			frm->RvSystem1->DefaultDest   = rdPreview ;
		}
		else
		{
			frm->RvSystem1->DefaultDest   = rdPrinter ;
		}

		frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;

		frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
		frm->pxbk = pxbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;
		frm->ClientName = edtclient->Text ;
        if (type == 0) {
			frm->printmodle = -1;
		}
		else
		{
			frm->printmodle = printid;
		}
		frm->tuihuo = 1;
		frm->previewprint(modle,2);
		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::tlbtn5Click(TObject *Sender)
{
	Print(0,0,0);
	/*if (!SaveWsale(1))
	{
	  return;
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString);

		frm->DanhaoChange = ChangeDisplay ;                      //change danhao
		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

		frm->RvSystem1->DefaultDest   = rdPrinter ;

		// frm->RvSystem1->SystemSetups<<ssAllowSetup;
		 frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
		// frm->RvSystem1->SystemSetups<<ssAllowPrinterSetup;
		frm->pxbk = pxbk;
		frm->ClientName = edtclient->Text ;
		frm->printmodle = printmodle;
		frm->previewprint(2,1);
		frm->Close();
		delete frm;
	}    */
}
//---------------------------------------------------------------------------


void TfrmWholesaleReturnMng::QryBkstack()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		String sql;
		sql = " SELECT STK_BookstackInfo.ID, STK_BookstackInfo.Name "
			" FROM STK_BookInfo LEFT OUTER JOIN"
			" STK_BookstackInfo ON STK_BookInfo.BkstackID = STK_BookstackInfo.ID"
			" where SupplierID=" + dsetNote->FieldByName("SupplierID")->AsString
			 + " and BkcatalogID=" + dsetNote->FieldByName("BkcatalogID")->AsString
			 + " and STK_BookstackInfo.StgID=" + dsetNtHeader->FieldByName("StgID")->AsString;
		dsetBkstack->Active = false;
		//dblkpcbbBkstackID->ListSource = NULL;
		//dblkpcbbBkstackID->DataSource = NULL;
		dsetBkstack->CommandText = sql;
		dsetBkstack->Active = true;
		//dblkpcbbBkstackID->ListSource = dsrcBkstack;
		//dblkpcbbBkstackID->DataSource = dsrcNote;
		//ShowMessage("OK");
	}
}

void __fastcall TfrmWholesaleReturnMng::dsetNoteAfterScroll(TDataSet *DataSet)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
        QryBkstack();
}
//---------------------------------------------------------------------------

void TfrmWholesaleReturnMng::ResetNtHeader()
{
	//���õ�ͷ
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0)
	{
		cmdResetNtHeader->Parameters->ParamByName("@ID")->Value =
		dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdResetNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
		cmdResetNtHeader->Execute();
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
			QryNtHeader();
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N1Click(TObject *Sender)
{
	lblCatalog->Caption = "���";
	m_catalogSearchMode=1;
	if (chqikan->Checked ) {
		edtCatalog->MaxLength = 15;
	}
	else
	{
		edtCatalog->MaxLength = 13;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "�Ա���";
	m_catalogSearchMode=2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode=3;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N11Click(TObject *Sender)
{
	tlbtn5->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N21Click(TObject *Sender)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString,0);

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

		frm->RvSystem1->DefaultDest    = rdPrinter ;
		// frm->RvSystem1->SystemSetups<<ssAllowSetup;
		 frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
	  //	 frm->RvSystem1->SystemSetups<<ssAllowPrinterSetup;
		if (Label2->Caption == "һ�㷢����")
		{
			frm->previewprint(1,2);
		}else
		{
		   frm->previewprint(2,2);
		}
		  //1,һ�㷢���� 2.һ�㷢���˻��� //1��ӡ��ʽ1 2 ��ӡ��ʽ2
		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmWholesaleReturnMng::BtnClearClick(TObject *Sender)
{
   Print(1,0,0);

}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N22Click(TObject *Sender)
{
	 if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString,0);

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;



		frm->RvSystem1->DefaultDest  = rdPreview ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPreview;
		if (Label2->Caption == "һ�㷢����")
		{
			frm->previewprint(1,2);
		}else
		{
		   frm->previewprint(2,2);
		}
		  //1,һ�㷢���� 2.һ�㷢���˻��� //1��ӡ��ʽ1 2 ��ӡ��ʽ2
		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N12Click(TObject *Sender)
{
  BtnClear->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
	 // Perform(WM_NEXTDLGCTL, 0, 0);
	  edtCatalog->Text = "";

	  if (chfoceset->Checked) {
			if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbnbedtAmount->SetFocus();
				}
			}
			else if (chfsdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbnbedtDiscount->SetFocus();
				}
			}
		}
		else
		{
			edtCatalog->SetFocus();
		}

	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmWholesaleReturnMng::FormResize(TObject *Sender)
{
	//dbgrdNote->Height = 393;
	//dbgrdNote->Width = 700;

}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode=6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbnbedtTotalAmountKeyPress(TObject *Sender, wchar_t &Key)

{
       if (Key == '\r')
	{
	  Perform(WM_NEXTDLGCTL, 0, 0);

	}
}
//---------------------------------------------------------------------------

void  TfrmWholesaleReturnMng::FindNote(String code)
{
	DelInvalidNtHeader();
	edtCatalog->Text = "";
	edtQryVendor->Text = "";
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
		QryNtHeader(code);
		//editclientname->Text = dsetVendor->FieldByName("Name")->AsString ;
		//cbclient->Text =  dsetVendor->FieldByName("Name")->AsString ;

	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
	dtpdate->Date =  dbdtedtHdTime->Date ;//��������
	//cbclient->Enabled = false;
	edtclient->Enabled = false;
	BtnSave->Enabled = false;
	SaveOrNot = true;
}

//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::N6Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= dsetNote->RecordCount; i++) {
		dbgrdNote->DataSource->DataSet->RecNo = i;
		dbgrdNote->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbgrdNoteCellClick(TColumn *Column)
{
	historyview();
	editprice->Text = FormatFloat("0.00",dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value*0.01);
}
//---------------------------------------------------------------------------

void TfrmWholesaleReturnMng::historyview()
{
	String sql;
	if (dsetNote->RecordCount > 0) {
    	sql = "select * from SYS_BSSET where name = 'wosaleday'" ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		int day = query->FieldByName("bk")->AsInteger ;
		DATE datetime = Date();
		datetime = datetime - day;
		sql = "select BS_WsaleNoteHeader.WsaleNtCode,BS_WsaleNoteHeader.WsaleNtCodeStr,BS_WsaleNote.Amount,BS_WsaleNote.Discount,Convert(varchar(20),BS_WsaleNoteHeader.HdTime,111) as HdTime,dbo.UF_BS_GetClientName(BS_WsaleNoteHeader.VendorID) as Name from BS_WsaleNote left join BS_WsaleNoteHeader on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.ID"
			" left join STK_BookInfo on STK_BookInfo.ID = BS_WsaleNote.BkInfoID ";
		sql = sql + " where STK_BookInfo.BkcatalogID = " + dsetNote->FieldByName("BkcatalogID")->AsString ;
		sql = sql + " and BS_WsaleNoteHeader.HdTime >= '" + DateToStr(datetime) + "'";
        if (!allclient) {
			sql = sql + " and BS_WsaleNoteHeader.VendorID in(select id from dbo.GetChild(dbo.UF_BS_GetParentID(" + dsetVendor->FieldByName("ID")->AsString + ")))";
		}

		qryrecord->Close();
		qryrecord->SQL->Clear();
		qryrecord->SQL->Add(sql);
		qryrecord->Open();
		((TFloatField *)dgrecord->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0%";
		int totamount = 0;
		qryrecord->DisableControls();
		qryrecord->First();
		while(!qryrecord->Eof)
		{
			totamount = totamount + qryrecord->FieldByName("Amount")->AsInteger ;
			qryrecord->Next();
		}
		qryrecord->EnableControls();
		edtotamount->Text = IntToStr(totamount);
		ClientTuiHuo();
	}
}
//---------------------------------------------------------------------------

void  TfrmWholesaleReturnMng::checkedview()
{
	String sql;
	sql = "select sum(Checked) as checked,sum(Nochecked) as nochecked from BS_WsaleNoteHeader where VendorID = " + dsetVendor->FieldByName("ID")->AsString ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	edchecked->Text = FormatFloat("0.00",query->FieldByName("checked")->AsFloat);
	ednochecked->Text = FormatFloat("0.00",query->FieldByName("nochecked")->AsFloat);
}
//---------------------------------------------------------------------------

bool TfrmWholesaleReturnMng::retailreturn(int catalogID)
{
    String sql;

	sql = "select * from SYS_BSSET where name = 'wosalereturn'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (!query->FieldByName("value")->AsBoolean) {
		sql = "select count(*) as count from BS_WsaleNote left join BS_WsaleNoteHeader on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id left join STK_BookInfo on BS_WsaleNote.BkInfoID = STK_BookInfo.ID "
		" left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.ID where BS_BookCatalog.ID = " + IntToStr(catalogID) + " and BS_WsaleNoteHeader.VendorID = " + IntToStr(ClientID) ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->FieldByName("count")->AsInteger == 0 ) {
			MessageBox(0,"����û�жԸÿͻ��������������˻���","һ�㷢���˻�" ,MB_OK);
			return false;
		}
	}

	return true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::BtnNewClick(TObject *Sender)
{
	if (!SaveWsale(1))
	{
		return;
	}

	querydan->Active = false;
	querydan->Active = true;
	DBNav->Enabled = false;
    AnsiString sql;

	ChangeBsmode(BSNoteSendback);
	ChangeOpmode(OPAddNtHeader);
	SaveOrNot = false;
	BtnSave->Enabled = true;
	dbnbedtAddCosts->Enabled = true;

	dbnbedt2->Visible = true;
	dbnbedt3->Visible = true;
	dbnbedt4->Visible = true;
	dblkpcbbStaffID->Enabled = true;
	dsetNtHeader->Edit();
	dsrcNtHeader->DataSet->FieldByName("AddCosts")->Value =  0.0;
	dsrcNtHeader->DataSet->FieldByName("Remarks")->Value =  "";
	dsetNtHeader->UpdateRecord();
	membk->Text = "";
	dbnbedtAddCosts->Text = "";
	edtQryVendor->Text = "";
	editdanhao->Text = "";
	dblkpcbbStaffID->KeyValue = -1;
	try {
		qryrecord->Active = false;
	} catch (...) {
	}
}
//---------------------------------------------------------------------------


void  TfrmWholesaleReturnMng::ModifyEnable()
{
    String sql = "select * from SYS_BSSET where name = 'WsalelDiscountChange'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (m_opmode == OPFind) {
		dbnbedtAmount->Enabled = false;
		dbnbedtDiscount->Enabled = false;
		cbbkstackID->Enabled = false;
		if (dsetNote->FieldByName("amount")->AsInteger >= 0 ) {
			Label2->Caption = "һ�㷢���˻���";
		}
		else
		{
			//Label2->Caption = "һ�㷢����";
		}
	}
	else
	{
		Label2->Caption = "һ�㷢���˻���";
		dbnbedtAmount->Enabled = true;
		if (query->FieldByName("value")->AsBoolean  ) {
			dbnbedtDiscount->Enabled = true;
		}
	  //	cbbkstackID->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::cbbkstackIDKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
		tlbtn1Click(tlbtnAddNote);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::cbbkstackIDExit(TObject *Sender)
{
	UpdateNote();
	historyview();
}
//---------------------------------------------------------------------------


void TfrmWholesaleReturnMng::GetBkStackInfo()
{
   AnsiString sql= "select  name, ID from STK_BookstackInfo where StgID = " + IntToStr(m_storageID);
   TADOQuery *aq  = new TADOQuery(Application);
  try
  {

   aq->Connection = m_con ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   while(!aq->Eof)
   {
	 cbbkstackID->AddItem(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger);
	 aq->Next();
   }
   cbbkstackID->ItemIndex = 0;
  }
  __finally
  {
	delete aq;
  }
}

void __fastcall TfrmWholesaleReturnMng::spselectClientClick(TObject *Sender)
{
		TfrmselectClient * frm = new TfrmselectClient(Application,m_con,"",linfo.storageID);
	   if (mrOk == frm->ShowModal())
	   {
			//editclientname->Text = frm->GetSelect();
			ClientID = frm->GetSelectID();
			dsetNtHeader->Edit();
			dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
			dsetNtHeader->UpdateRecord();
			dblkpcbbVendorID->KeyValue =  ClientID;
			//cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)ClientID);
			edtclient->SetFocus();
			ClientView();
			UpdateNtHeader();
	   		checkedview();
	   }
	   delete frm;


}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dtpdateChange(TObject *Sender)
{
dbdtedtHdTime->Date = dtpdate->Date ;
}
//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {   //�鵥
		if (!RzToolButton1->Enabled ) {
			return;
		}
		RzToolButton1->Click();
	}
	if (Key == VK_F2) {   //����
		if (!BtnNew->Enabled ) {
			return;
		}
		BtnNew->Click();
	}
	if (Key == VK_F3) {   //����
		if (!BtnSave->Enabled ) {
			return;
		}
		BtnSave->Click();
	}
	if (Key == VK_F4) {   //�޸ĵ�ͷ
		if (!tlbtnAddNote->Enabled ) {
			return;
		}
		tlbtnAddNote->Click();
	}
	if (Key == VK_F5) {   //ɾ��
		if (!tlbtn2->Enabled ) {
			return;
		}
		tlbtn2->Click();
	}
	if (Key == VK_F6) {    //ͳһ
		if (!tlbtn3->Enabled ) {
			return;
		}
		tlbtn3->Click();
	}
	if (Key == VK_F7) {    //�ֳ��տ�
		if (!RzToolButton2->Enabled ) {
			return;
		}
		RzToolButton2->Click();
	}
	if (Key == VK_F8) {    //����
		if (!tlbtn4->Enabled ) {
			return;
		}
		tlbtn4->Click();
	}
	if (Key == VK_F10) {   //��ӡ
		if (!tlbtn5->Enabled ) {
			return;
		}
		tlbtn5->Click();
	}
	if (Key == VK_F11) {    //Ԥ��
		if (!BtnClear->Enabled ) {
			return;
		}
		BtnClear->Click();
	}

	if (Shift.Contains(ssAlt)&& Key == 88) {    //�ڿ�
		if (chqikan->Checked ) {
			chqikan->Checked = false;
		}
		else
		{
			chqikan->Checked = true;
		}
		chqikan->OnClick ;
	}
	if (Shift.Contains(ssAlt)&& Key == 67) {    //��λ
		SpeedButton1->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==81  ) {
		tlbtn7->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 70 ) {
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------
void TfrmWholesaleReturnMng::ReadClient()
{
  /*AnsiString sql;
  sql = "select ID,name from CUST_CustomerInfo where type =2 or type = 3 order by name";
  TADOQuery *aq = new TADOQuery(NULL);
  aq->Connection = m_con ;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();
  while(!aq->Eof)
  {
	cbclient->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
	aq->Next();
  }
  delete aq;
   cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)1);     */

}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::cbclientKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (cbclient->Text =="") {
			MessageBoxA(0,"�����뵥λ���ƣ�","��ʾ",MB_ICONINFORMATION);
			return;
		}
		try {
			ClientID = (int)(cbclient->Items->Objects[cbclient->ItemIndex]);
		} catch (...) {
			MessageBoxA(0,"��������ȷ��λ���ƣ�","��ʾ",MB_ICONINFORMATION);
			return;
		}

		cbclient->Text = cbclient->Items->operator [](cbclient->ItemIndex);
		if (ClientID == -1) {
			MessageBoxA(0,"��������ȷ��λ���ƣ�","��ʾ",MB_ICONINFORMATION);
			return;
		}
            AnsiString sql = "select Salesman from CUST_CustomerInfo where id = " + IntToStr(ClientID);
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			sql = "select * from SYS_StaffInfo where Name = '" + query->FieldByName("Salesman")->AsString + "' and stgID = " + IntToStr(m_storageID) + " and Career = 2";
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (!query->IsEmpty() ) {
				int staff = query->FieldByName("ID")->AsInteger;
				dblkpcbbStaffID->KeyValue = staff;
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("StaffID")->AsInteger = staff;
				dsetNtHeader->Post();
			}
			dsetNtHeader->Edit();
			dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
			dsetNtHeader->UpdateRecord();
			dblkpcbbVendorID->KeyValue =  ClientID;
			UpdateNtHeader();
			checkedview();
		//dbnbedtAddCosts->SetFocus();
		cbclient->Enabled = false;
		RzButton1->Enabled = false;
		spselectClient->Enabled = false;
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::tlbtnAddNoteClick(TObject *Sender)
{
    if (changepassword) {
		if (!CheckOperateAuthority())
					return;
   	}
	AnsiString sql;
   sql = "select value from sys_bsset where name ='modifypxdanwei'";
   TADOQuery *aq = new TADOQuery(NULL);
   aq->Connection = m_con ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   if (aq->FieldByName("value")->AsBoolean ) {     //��ʾ����
	   if (!CheckOperateAuthority())
				return;
			//cbclient->Enabled = true;
			edtclient->Enabled = true;
			   if (newclient) {
                  RzButton1->Enabled = true;
                }else RzButton1->Enabled = false;
			spselectClient->Enabled = true;
			dbnbedtAddCosts->Enabled = true;
			edtclient->SetFocus();
			BtnSave->Enabled = true;
			dtpdate->Enabled =  true;
			dblkpcbbStaffID->Enabled = true;

   }else //����ʾ��������
   {
			//cbclient->Enabled = true;
			edtclient->Enabled = true;
		   if (newclient) {
                  RzButton1->Enabled = true;
                }else RzButton1->Enabled = false;
			spselectClient->Enabled = true;
			dbnbedtAddCosts->Enabled = true;
			dtpdate->Enabled =  true;
			edtclient->SetFocus();
			BtnSave->Enabled = true;
			dblkpcbbStaffID->Enabled = true;
   }
   SaveOrNot = false;
   delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	  int CurrNo;
  if (Button == mbLeft ) {
	  if (!blSelect) {
		 BookMark = dsetNote->GetBookmark();   //dataset
		 blSelect  = true;
		 return;
	  }
  }
   if (Shift.Contains(ssShift)) {
		  CurrNo = dsetNote->FieldByName("ID")->AsInteger ;
		  dsetNote->DisableControls();
		  dsetNote->GotoBookmark(BookMark);
		  dbgrdNote->SelectedRows->CurrentRowSelected = true;
		  if (CurrNo > dsetNote->FieldByName("ID")->AsInteger) {
			  while(CurrNo > dsetNote->FieldByName("ID")->AsInteger)
			  {
				dbgrdNote->SelectedRows->CurrentRowSelected = true;
				dsetNote->Next();
			  }
		  }
		  if ( CurrNo < dsetNote->FieldByName("ID")->AsInteger ) {
				  while(CurrNo < dsetNote->FieldByName("ID")->AsInteger)
			  {
				dbgrdNote->SelectedRows->CurrentRowSelected = true;
				dsetNote->Prior() ;
			  }
		  }
		  dsetNote->EnableControls();
		  dsetNote->FreeBookmark(BookMark);
		  blSelect = false;
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N8Click(TObject *Sender)
{
	if (dsetNote->IsEmpty()) {
		return;
	}
	AnsiString StgID;
	StgID = "-10";

	dsetNote->DisableControls();

	if (dbgrdNote->SelectedRows->Count > 0) {
		for (int i=0; i < dbgrdNote->SelectedRows->Count; i++)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
			StgID = StgID + "," + dsetNote->FieldByName("ID")->AsString;
		}
	}
	else
	{
		StgID = StgID + "," + dsetNote->FieldByName("ID")->AsString;
	}

	spcopy->ProcedureName = "CopyData";
	spcopy->Parameters->Clear();
	spcopy->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),2);
	spcopy->Parameters->CreateParameter("@ID",ftString,pdInput,StgID.Length(),StgID.c_str());
	spcopy->Parameters->CreateParameter("@userid",ftInteger,pdInput,sizeof(int),linfo.userID );
	spcopy->ExecProc();
	dsetNote->EnableControls();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N9Click(TObject *Sender)
{
	if (BtnSave->Enabled) {
		MessageBoxA(0,"������δ���棬���ȱ��棡","��ʾ",MB_ICONASTERISK);
		return;
	}
	spcopy->ProcedureName = "StickData";
	spcopy->Parameters->Clear();
	spcopy->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),4);
	spcopy->Parameters->CreateParameter("@HeadId",ftInteger,pdInput,sizeof(int),dsetNtHeader->FieldByName("ID")->AsInteger);
	spcopy->Parameters->CreateParameter("@userid",ftInteger,pdInput,sizeof(int),linfo.userID );
	spcopy->ExecProc();
	QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);


	Screen->Cursor = crDefault ;

}
//---------------------------------------------------------------------------

bool  TfrmWholesaleReturnMng::saleenable(int stkid)
{
	AnsiString sql;
	sql = "select * from STK_StockInventories where states = 0 and STK_bookInfoID = " + IntToStr(stkid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {
        MessageBox(0,"���������̵㣬�������ۣ�","��ʾ",MB_ICONWARNING);
		return false;
	}
	else
	{
    	sql = "select * from STK_stockxuyiDetail,STK_stockxuyiHeader where STK_stockxuyiHeader.AdjustHeaderID = STK_stockxuyiDetail.AdjustHeaderID and STK_stockxuyiHeader.state = 0 and STK_stockxuyiDetail.bkinfoid = " + IntToStr(stkid);
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->RecordCount > 0) {
        	MessageBox(0,"���������̵㣬�������ۣ�","��ʾ",MB_ICONWARNING);
			return false;
		}
		else
		{
        	return true;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::BtnViewClick(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,linfo.con,linfo.storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::cbclientExit(TObject *Sender)
{
	//wchar_t Key = '\r';
	//cbclientKeyPress(Sender,Key);
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::BtnSaveClick(TObject *Sender)
{
	/*if (changehead == 1) {
		wchar_t key = '\r';
		cbclientKeyPress(Sender, key);
	}
	try {
			ClientID = (int)(cbclient->Items->Objects[cbclient->ItemIndex]);
	} catch (...) {
			MessageBoxA(0,"��������ȷ��λ���ƣ�","��ʾ",MB_ICONINFORMATION);
			return;
	}
	dsetNtHeader->Edit();
	dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
	dsetNtHeader->UpdateRecord();
	dblkpcbbVendorID->KeyValue =  ClientID;
	UpdateNtHeader();     */
	if (!SaveOK()) {
		return;
	}
	edtCatalog->SetFocus();
}
//---------------------------------------------------------------------------

bool TfrmWholesaleReturnMng::SaveOK()
{
   /* if (cbclient->Enabled) {
        MessageBoxA(0,"���ڵ�λ���ûس���ȷ�Ͽͻ���","��ʾ",MB_ICONASTERISK);
		return false;
  }  */

  	if (dsetNtHeader->RecordCount > 0) {
		AnsiString sql = "update BS_WsaleNoteHeader set HdTime = '" + DateToStr(dtpdate->Date)  + "' where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}

  if (dsetNote->RecordCount > 0) {
		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		//cbclient->Enabled = false;
		edtclient->Enabled = false;
		dblkpcbbStaffID->Enabled = false;
		return true;
  }
  else if (dsetNtHeader->FieldByName("WsaleNtCode")->AsInteger != 0 ) {
		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		//cbclient->Enabled = false;
		edtclient->Enabled = false;
		dblkpcbbStaffID->Enabled = false;
		return true;
  }
	spsave->Parameters->ParamByName("@MODE")->Value = 1;
  spsave->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger ;
  spsave->Parameters->ParamByName("@STGID")->Value = linfo.storageID;
  spsave->Parameters->ParamByName("@TYPE")->Value = 2;
  spsave->Parameters->ParamByName("@CODEMODE")->Value = 1;
  spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
  spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
  spsave->ExecProc() ;



  if (ChangeDisplay) {
	logmessage = "����һ�㷢���˻���" + spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
  }
  else
  {
	logmessage = "����һ�㷢���˻���" + spsave->Parameters->ParamByName("@ReturnCode")->Value ;
  }
  AddEvent(1,"һ�㷢���˻�����",m_userID,m_storageID,logmessage,linfo.con);
  historyview();     //SaveBenDan
  dbedtWsaleNtCode->Text = spsave->Parameters->ParamByName("@ReturnCode")->Value ;
  editdanhao->Text = spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
  SaveOrNot = true;
  BtnSave->Enabled = false;
  dbnbedtAddCosts->Enabled = false;
  //cbclient->Enabled = false;
  edtclient->Enabled = false;
  dtpdate->Enabled =  false;
  dblkpcbbStaffID->Enabled = false;
  QryNtHeader();
  return true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::cbclientDropDown(TObject *Sender)
{
	int i;
   int maxwidth;
	maxwidth = ((TComboBox*)Sender)->Width;
	for (int i=0 ; i < ((TComboBox*)Sender)->Items->Count ; i++) {
	 maxwidth = Math::Max(maxwidth, ((TComboBox*)Sender)->Canvas->TextWidth(((TComboBox*)Sender)->Items->Strings[i])+10);
	((TComboBox*)Sender)->Perform(CB_SETDROPPEDWIDTH,maxwidth,0);
	}
}
//---------------------------------------------------------------------------

 bool TfrmWholesaleReturnMng::SaveWsale(int mode)
{
    if (dsrcNote->DataSet == NULL) {
		return true;
	}
	if (!dbgrdNote->DataSource->DataSet->Active ) {
		return true;
	}
	int recordRN = dbgrdNote->DataSource->DataSet->RecordCount;
	if ((!SaveOrNot)&& (recordRN != 0)) {                      //SaveBenDan
	if (mode == 1) {                      //��ӡ��Ԥ

		MessageBoxA(0,"������δ���棬���ȱ��棡","��ʾ",MB_ICONASTERISK);
		return false;

	}else
	{
		  if( MessageBoxA(0,"������δ���棬�Ƿ���Ҫ���棿","��ʾ",MB_ICONQUESTION||MB_YESNO)==1)
		  {
			  BtnSave->Click();
		  }else
		  {
			spsave->Parameters->ParamByName("@MODE")->Value = 2;
			spsave->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger ;
			spsave->Parameters->ParamByName("@STGID")->Value = 0;
			spsave->Parameters->ParamByName("@TYPE")->Value = 2;
			spsave->Parameters->ParamByName("@CODEMODE")->Value = 1;
			spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
			spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
			spsave->ExecProc() ;
		  }
	  }
	}else return true;

}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbnbedtAddCostsExit(TObject *Sender)
{
	if (dsetNtHeader->RecordCount > 0) {
    	AnsiString sql = "update BS_WsaleNoteHeader set AddCosts = " + FloatToStr(abs(dsetNtHeader->FieldByName("AddCosts")->AsFloat))  + " where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		membk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::DBNavClick(TObject *Sender, TNavigateBtn Button)

{
	AnsiString code ;
	code = querydan->FieldByName("WsaleNtCode")->AsAnsiString ;
	editdanhao->Text = querydan->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
	QryNtHeader(code,false);
	//editclientname->Text = dsetVendor->FieldByName("Name")->AsString ;
	//cbclient->Text =  dsetVendor->FieldByName("Name")->AsString ;
	checkedview();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::RzButton1Click(TObject *Sender)
{
	String ID;
	ID = "";
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
        dsetVendor->Active = false;
		dsetVendor->CommandText = "select ID,Name from CUST_CustomerInfo where   Type in (2,3)  order by ID";
		dsetVendor->Active = true;
		int count1 = dsetVendor->RecordCount;

		/*TDetaileForm * frm = new TDetaileForm(m_app,2,1,ID.c_str() ,m_con);
		frm->ParentID = -1;
		frm->ShowModal();
		delete frm; */

		Tfrmclient * frm = new Tfrmclient(Application,m_con,linfo.storageID);
	   frm->FormStyle = fsNormal ;
	   frm->WindowState = wsNormal ;
	   frm->Visible = false;
	   frm->Position = poMainFormCenter ;
		frm->ShowModal();
	   delete frm;

		dsetVendor->Active = false;
		dsetVendor->Active = true;
		int count2 = dsetVendor->RecordCount;
		if (count2 > count1)
		{
			dsetVendor->Last();
			dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
			//dsetNtHeader->Edit();
			//dsetNtHeader->FieldByName("VendorID"/)->AsInteger = dsetVendor->FieldByName("ID")->AsInteger;
			//cbclient->Items->AddObject(dsetVendor->FieldByName("name")->AsAnsiString,(TObject*)dsetVendor->FieldByName("ID")->AsInteger);
			//cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)dsetVendor->FieldByName("ID")->AsInteger );
			//cbclient->SetFocus();
			//UpdateNtHeader();
			ClientID = dsetVendor->FieldByName("ID")->AsInteger;
			dsetNtHeader->Edit();
			dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
			dsetNtHeader->UpdateRecord();
			ClientView();
			edtclient->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::cbclientClick(TObject *Sender)
{
    try {
			ClientID = (int)(cbclient->Items->Objects[cbclient->ItemIndex]);
	} catch (...) {
			MessageBoxA(0,"��������ȷ��λ���ƣ�","��ʾ",MB_ICONINFORMATION);
			return;
	}
	dsetNtHeader->Edit();
	dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
	dsetNtHeader->UpdateRecord();
	dblkpcbbVendorID->KeyValue =  ClientID;
	UpdateNtHeader();
	checkedview();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbgrdNoteTitleClick(TColumn *Column)
{
	if (dsetNote->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetNote->Sort == "") {
		dsetNote->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetNote->Sort == qusort) {
		dsetNote->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetNote->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void TfrmWholesaleReturnMng::FormView()
{
	AnsiString sql;
	sql = "select * from BS_SYS_Formview where stgid = " + IntToStr(m_storageID) + " and ParentID = 4";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof)
	{
		if (query->FieldByName("Name")->AsAnsiString == "�鵥" ) {
			RzToolButton1->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "����" ) {
			BtnNew->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "����" ) {
			BtnSave->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "�޸ĵ�ͷ" ) {
			tlbtnAddNote->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "ɾ��" ) {
			tlbtn2->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "ͳһ" ) {
			tlbtn3->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "�ֳ��տ�" ) {
			RzToolButton2->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "Excel����" ) {
			tlbtn4->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "Ԥ��" ) {
			BtnClear->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "��ӡ" ) {
			tlbtn5->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "����" ) {
			BtnView->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "��С��" ) {
			BtnAlignBottom->Visible = query->FieldByName("state")->AsBoolean ;
		}
		query->Next();
	}
	sql = "select * from sys_printhead where modle = 1 and stgid = " + IntToStr(m_storageID) ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	while (!query->Eof )
	{
		TMenuItem * item = new TMenuItem(this);
		TMenuItem * item1 = new TMenuItem(this);
		item->Caption = query->FieldByName("typename")->AsAnsiString;
		item->Tag = query->FieldByName("id")->AsInteger ;
		item->OnClick = MyClick;
		pmprint->Items->Add(item);
		item1->Caption = query->FieldByName("typename")->AsAnsiString;
		item1->Tag = query->FieldByName("id")->AsInteger ;
		item1->OnClick = MyClickPreview;
		pmpreview->Items->Add(item1);
		query->Next();
	}
}

//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::MyClick(TObject *Sender)
{
	TMenuItem *item = dynamic_cast<TMenuItem*>(Sender);
	if(item==NULL)
		return;
	Print(2,1,item->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::MyClickPreview(TObject *Sender)
{
	TMenuItem *item = dynamic_cast<TMenuItem*>(Sender);
	if(item==NULL)
		return;
	Print(1,1,item->Tag);
}
//---------------------------------------------------------------------------
void TfrmWholesaleReturnMng::ClientView()
{
	if (ClientID == -1) {
		return;
	}
	String sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = m_con;
	sql = "exec USP_BS_Client_View 0," + IntToStr(ClientID)  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edtclient->Text = aq->FieldByName("Name")->AsAnsiString ;

	sql = "select Salesman from CUST_CustomerInfo where id = " + IntToStr(ClientID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	sql = "select * from SYS_StaffInfo where Name = '" + aq->FieldByName("Salesman")->AsString + "' and stgID = " + IntToStr(m_storageID) + " and Career = 2";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	dblkpcbbStaffID->KeyValue = aq->FieldByName("id")->AsInteger;

	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::edtclientKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (edtclient->Text =="") {
			MessageBoxA(0,"��ѡ��λ���ƣ�","��ʾ",MB_ICONINFORMATION);
			return;
		}

            AnsiString sql = "select Salesman from CUST_CustomerInfo where id = " + IntToStr(ClientID);
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			sql = "select * from SYS_StaffInfo where Name = '" + query->FieldByName("Salesman")->AsString + "' and stgID = " + IntToStr(m_storageID) + " and Career = 2";
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (!query->IsEmpty() ) {
				int staff = query->FieldByName("ID")->AsInteger;
				dblkpcbbStaffID->KeyValue = staff;
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("StaffID")->AsInteger = staff;
				dsetNtHeader->Post();
			}
			dsetNtHeader->Edit();
			dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
			dsetNtHeader->UpdateRecord();
			dblkpcbbVendorID->KeyValue =  ClientID;
			UpdateNtHeader();
			checkedview();
		//dbnbedtAddCosts->SetFocus();
		//cbclient->Enabled = false;
		edtclient->Enabled = false;
		RzButton1->Enabled = false;
		spselectClient->Enabled = false;
		BtnSave->Click();
	}
}
void TfrmWholesaleReturnMng::ClientTuiHuo()
{
 FLOAT yeartuihuo,timetuihuo;
 yeartuihuo =0.00,
 timetuihuo =0.00;
 int totalamountall;
	   sptuihuo1->Parameters->ParamByName("@clientID")->Value =  ClientID;
	   sptuihuo1->Parameters->ParamByName("@timelv")->Value =  0.00;
	   sptuihuo1->Parameters->ParamByName("@yearlv")->Value =  0.00;
	   sptuihuo1->Parameters->ParamByName("@totaltuihuoall")->Value =  0;
	   sptuihuo1->ExecProc();
	   timetuihuo = sptuihuo1->Parameters->ParamByName("@timelv")->Value;
	   yeartuihuo = sptuihuo1->Parameters->ParamByName("@yearlv")->Value;
	   totalamountall = sptuihuo1->Parameters->ParamByName("@totaltuihuoall")->Value;

	   edittuihuo->Text =  IntToStr(totalamountall);
	   editlv1->Text = FormatFloat("0.00",yeartuihuo) + "%" ;
	   editallyear->Text  = FormatFloat("0.00",timetuihuo)+ "%" ;

	   if (yeartuihuo >= 100.00) {
		 editlv1->Color = clRed ;
	   }else
	   {
		editlv1->Color = cl3DLight  ;
	   }

	   if (timetuihuo >= 100.00) {
		  editallyear->Color = clRed;
	   }
	   else
	   {
        editallyear->Color = cl3DLight ;

	   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N10Click(TObject *Sender)
{
	if (N10->Checked ) {
		N13->Checked = false;
		printmodle = 0;
	}
	else
	{
		N13->Checked = true;
		printmodle = 1;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N13Click(TObject *Sender)
{
	if (N13->Checked ) {
		N10->Checked = false;
		printmodle = 1;
	}
	else
	{
		N10->Checked = true;
		printmodle = 0;
	}
}
//---------------------------------------------------------------------------
void  TfrmWholesaleReturnMng::operterview(int operterid)
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = linfo.con ;
	sql = "select name from sys_user where id = " + IntToStr(operterid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	lblOpName->Caption = aq->FieldByName("name")->AsString;
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::membkExit(TObject *Sender)
{
	if (dsetNtHeader->RecordCount > 0) {
    	AnsiString sql = "update BS_WsaleNoteHeader set Remarks = '" + membk->Text + "' where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::membkKeyPress(TObject *Sender, wchar_t &Key)

{
	//
	if (Key == '\r')
	{
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::SpeedButton1Click(TObject *Sender)
{
	if (GroupBox1->Visible) {
		GroupBox1->Visible = false;
	}
	else
	{
    	GroupBox1->Visible = true;
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::chqikanClick(TObject *Sender)
{
	if (chqikan->Checked ) {
		edqikan->Visible = true;
		if (m_catalogSearchMode == 1) {
			edtCatalog->MaxLength = 15;
		}
		else
		{
			edtCatalog->MaxLength = 0;
		}
	}
	else
	{
		edqikan->Visible = false;
		if (m_catalogSearchMode == 1) {
			edtCatalog->MaxLength = 13;
		}
		else
		{
			edtCatalog->MaxLength = 0;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N14Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode=5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::edqikanKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (m_catalogSearchMode == 6) {
        	float price;
				try {
					price = StrToFloat(edtCatalog->Text.Trim());
				} catch (...) {
					MessageBox(0,"��������ȷ�Ķ��ۣ�","�����˻�" ,MB_ICONEXCLAMATION);
					return;
				}
			}

        TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->Init(&li);
		frm->DoModalType = 7; //һ�㷢���˻�ģʽ
		frm->WholeReturnfrm = this;
		frm->qikan = chqikan->Checked ;
		frm->qikanhao = edqikan->Text ;
		frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
		if (mrOk == frm->ShowModal())
		{
			int supplierID = -1,catalogID = -1;
			if (frm->SelectAll) {
				for (int i = 0; i < frm->lengthint  ; i++) {

				if (!saleenable(frm->stkbkid[i])) {
					return;
				}
				cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BKSKid[i]);
				if (AddNote(frm->SupplierID[i],frm->BkcatalogiD[i])) {

					Key = 0;
					Perform(WM_NEXTDLGCTL, 0, 0);
					historyview();

				}
				else
				{
				}

				}

			}else
			{
				frm->GetSelectResult(supplierID, catalogID);
				if (!retailreturn(catalogID)) {
					return;
				}
				if (supplierID >= 0 && catalogID >= 0)
				{
					cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BSKid);

					TLocateOptions   Opts;
					Opts.Clear();
					Opts   <<   loPartialKey;
					String   str   = AnsiString(frm->BKinfoid);

					if ( !dsetNote->Locate("BkInfoID",str,Opts))
					{
						if (!saleenable(frm->BKinfoid)) {
							return;
						}
						if (AddNote(supplierID, catalogID))
						{
							if (addnotereturnvalue == -2) {
								MessageBox(0,"��������������ۣ�","����" ,MB_ICONEXCLAMATION);
								edtCatalog->Text = "";
								edqikan->Text = "";
								addnotereturnvalue = 0;
							}
							else
							{
								Key=0;
								historyview();
								if (chfoceset->Checked) {
									if (chfsamount->Checked ) {
										dbnbedtAmount->SetFocus();
									}
									else if (chfsdiscount->Checked ) {
										dbnbedtDiscount->SetFocus();
									}
									else if (chfsluru->Checked) {
										edtCatalog->SetFocus();
									}
								}
								else
								{
									dbnbedtAmount ->SetFocus();
								}
							}
							editprice->Text =  FormatFloat("0.00", dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value * 0.01);
						}
						else
							ShowMessage("����޸���!");
					}
					else
					{
						dbgrdNote->SelectedRows->CurrentRowSelected = true;
						dbgrdNote->SetFocus();
						dbnbedtAmount->SetFocus();
					}
				}
			}
		}
		delete frm;

		edtCatalog->Text = "";
		edqikan->Text = "";
		if (dblkpcbbVendorID->Text == "") {
			dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::chfsluruClick(TObject *Sender)
{
	if (chfsluru->Checked ) {
		chfoceset->Checked = true;
	}
	else if (chfsamount->Checked ) {
		chfoceset->Checked = true;
	}
	else if (chfsdiscount->Checked ) {
		chfoceset->Checked = true;
	}
	else
	{
		chfoceset->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::editpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (dsetNote->IsEmpty() ) {
			return;
		}
		float fajia;
		float discount;
		try {
			fajia = StrToFloat(editprice->Text);
			discount =  fajia*100/dsetNote->FieldByName("price")->AsFloat;
			dbnbedtDiscount->Value =  discount;

			editprice->Text = FormatFloat("0.00",fajia);
			dsetNote->Edit();
			dsetNote->FieldByName("Discount")->AsFloat = discount;
			dsetNote->Post();
			UpdateNote();

			historyview();
		} catch (...) {
			return;
		}
		edtCatalog->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N15Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
        return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con,m_storageID,dsetNote->FieldByName("BkcatalogID")->AsInteger,m_userID );
	frm->ShowModal();
	delete frm;
}
void TfrmWholesaleReturnMng::lock(int htype)
{

     if (htype) {   //�������˵�
              BtnSave->Enabled = false;
              tlbtn1->Enabled = false;
              tlbtnAddNote->Enabled = false;
              tlbtn2->Enabled = false;
              tlbtn3->Enabled = false;
              RzToolButton2->Enabled = false;
              dbnbedtAmount->Enabled = false;

              dbnbedtDiscount->Enabled = false;
              edtCatalog->Enabled = false;

              chqikan->Enabled = false;
              RzButton1->Enabled = false;

              selectmenu->AutoPopup = false;
            //  imglock->Visible = true;
            lblock->Caption="������";
              membk->Enabled = false;
              editprice->Enabled = false;
              dblkpcbbStaffID->Enabled = false;
              dbnbedtAddCosts->Enabled = false;
              dtpdate->Enabled = false;

       }else
       {  selectmenu->AutoPopup = true;
         membk->Enabled = true;
              editprice->Enabled = true;
              dblkpcbbStaffID->Enabled = true;
              dbnbedtAddCosts->Enabled = true;
              dtpdate->Enabled = true;
         //     BtnSave->Enabled = true;
              tlbtn1->Enabled = true;
              tlbtnAddNote->Enabled = true;
              tlbtn2->Enabled = true;
              tlbtn3->Enabled = true;
              RzToolButton2->Enabled = true;
              dbnbedtAmount->Enabled = true;

              dbnbedtDiscount->Enabled = true;
              edtCatalog->Enabled = true;

              chqikan->Enabled = true;
                 if (newclient) {
                  RzButton1->Enabled = true;
                }else RzButton1->Enabled = false;

              //imglock->Visible = false;
              lblock->Caption="";
             disablenewsupplierornewbook();
       }







}
void TfrmWholesaleReturnMng::checknewsupplier()
{
   AnsiString sql;
   sql = "select * from sys_lock_table where lockname in('bookcatalog','client') and stgid ="+IntToStr(linfo.storageID);
    TADOQuery *aq = new TADOQuery(Application);
    aq->Connection = m_con;
    aq->Close();
    aq->SQL->Clear();
    aq->SQL->Add(sql);
    aq->Open();
    aq->First();
    if (aq->FieldByName("lockname")->AsAnsiString=="bookcatalog") {
        bookcatalogadd=aq->FieldByName("lockadd")->AsBoolean;
        bcatalogmodify=aq->FieldByName("lockmodify")->AsBoolean;
    }else
    {
       client =aq->FieldByName("lockadd")->AsBoolean;
    }

    aq->Next();
    if (aq->FieldByName("lockname")->AsAnsiString=="bookcatalog") {
        bookcatalogadd=aq->FieldByName("lockadd")->AsBoolean;
        bcatalogmodify=aq->FieldByName("lockmodify")->AsBoolean;
    }else
    {
       client =aq->FieldByName("lockadd")->AsBoolean;
    }
    delete aq;
}
void TfrmWholesaleReturnMng::disablenewsupplierornewbook()
{

     //bool  supplier,bookcatalogadd,bcatalogmodify;
     if (client) {
        RzButton1->Enabled = false;
     }

}
//---------------------------------------------------------------------------

