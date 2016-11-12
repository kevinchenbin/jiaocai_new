﻿//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RetailReturnMngForm.h"
#include "QryNoteCodeForm.h"
#include "SetNotesForm.h"
#include "mytrace.h"
#include "customer\customer.h"
#include "SelectCustomerForm.h"
#include "MixedRecMoneyForm.h"
#include "SelectMemberForm.h"
#include "..\common\Print.h"
#include "SelectCatalogForm.h"
#include "..\membermanager\MemberCard.h"
#include "bookQuery.h"
#include "Math.h"
#include "Addsyslog.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBCmbo"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzDBGrid"
#pragma link "RzDBLbl"
#pragma link "RzCommon"
#pragma link "RzDBLook"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TfrmRetailReturnMng *frmRetailReturnMng;
//---------------------------------------------------------------------------


__fastcall TfrmRetailReturnMng::TfrmRetailReturnMng(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_catalogSearchMode(0)
	, m_bsmode(0)
	, m_opmode(0)
	, m_supplierID(-1)
	, m_cash(0)
	, m_card(0)
{
	m_module = MTRetailMng;
	retaildiscountchange = true;
	//dblkpcbbBkstackID->Enabled = false;
}
//---------------------------------------------------------------------------

void TfrmRetailReturnMng::BatchSetNotes(int amount, float discount, int mode)
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
    	String ids = "";
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			ids = ids + dsetNote->FieldByName("ID")->AsString;
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = dsetNote->FieldByName("ID")->AsString;
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
			}
		}
		else
			return;

		switch(mode)
		{
		case 1://两者均更新
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
            cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 3;
			cmdBatchUpdateNote->Execute();
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader();
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			break;
		case 2://只更新Amount
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = "";
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 3;
			cmdBatchUpdateNote->Execute();
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader();
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			break;
		case 3://只更新Discount
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = "";
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 3;
			cmdBatchUpdateNote->Execute();
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
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

void TfrmRetailReturnMng::QryNtHeader(String code, bool qrybkstack)
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	spQryNtHeader1->Parameters->ParamByName("@NtCode")->Value = code;
	spQryNtHeader1->Parameters->ParamByName("@Bsmode")->Value = 3;
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
		dsetNote->AfterScroll = dsetNoteAfterScroll;
		if (qrybkstack)
		{
            QryBkstack();
		}
		if (dsetNtHeader->FieldByName("State")->AsInteger == 1 ) {
			dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat ;
		}
		else
		{
			dbnbedtReceivableMoney->Value =  dsetNtHeader->FieldByName("nochecked")->AsFloat ;
		}
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		membk->Text = dsetNtHeader->FieldByName("Remarks")->AsAnsiString ;
		ShowPrice();
	}
	catch(...)
	{
		//ShowMessage("该单不存在！");
	}
}

void TfrmRetailReturnMng::QryNtHeader(bool qrybkstack)
{
	//保存查询之前的当前活动记录ID
	int noteID = 0;
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
        noteID = dsetNote->FieldByName("ID")->AsInteger;
	}
	//查询单头
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		spQryNtHeader1->Active = false;
		spQryNtHeader->Active = false;
		spQryNtHeader->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger;
		spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 3;
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
			if (noteID > 0)//将当前记录的ID重新调整至noteID
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
			if (qrybkstack)
			{
				QryBkstack();
			}
			if (dsetNtHeader->FieldByName("State")->AsInteger == 1 ) {
				dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat ;
			}
			else
			{
				dbnbedtReceivableMoney->Value =  dsetNtHeader->FieldByName("nochecked")->AsFloat ;
			}
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
			operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
			membk->Text = dsetNtHeader->FieldByName("Remarks")->AsAnsiString ;
			ShowPrice();
		}
		catch(...)
		{
			//ShowMessage("该单不存在！");
		}
	}
}

void TfrmRetailReturnMng::QryNtHeader(int id, bool qrybkstack)
{
	//查询单头
	spQryNtHeader1->Active = false;
	spQryNtHeader->Active = false;
	spQryNtHeader->Parameters->ParamByName("@ID")->Value = id;
	spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 3;
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
		if (qrybkstack)
		{
			QryBkstack();
		}
		if (dsetNtHeader->FieldByName("State")->AsInteger == 1 ) {
			dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat ;
		}
		else
		{
        	dbnbedtReceivableMoney->Value =  dsetNtHeader->FieldByName("nochecked")->AsFloat ;
		}
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		membk->Text = dsetNtHeader->FieldByName("Remarks")->AsAnsiString ;
		ShowPrice();
	}
	catch(...)
	{
    	//ShowMessage("该单不存在！");
    }
}

void TfrmRetailReturnMng::AddNtHeader()
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 3;
	cmdAddNtHeader->Execute();
	int id = cmdAddNtHeader->Parameters->ParamByName("@RETURN_VALUE")->Value;
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader(id);
		logmessage = "添加零售退货单" + dsetNtHeader->FieldByName("RetailNtCode")->AsString ;
		AddEvent(1,"POS零售退货",m_userID,m_storageID,logmessage,linfo.con);
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
}

void TfrmRetailReturnMng::DelNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdDelNtHeader->Parameters->ParamByName("@ID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		int id = dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdDelNtHeader->Parameters->ParamByName("@Bsmode")->Value = 3;
		cmdDelNtHeader->Execute();
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader(id);
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

void TfrmRetailReturnMng::UpdateNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdUpdateNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@HdTime")->Value =
			dsetNtHeader->FieldByName("HdTime")->AsDateTime;
		cmdUpdateNtHeader->Parameters->ParamByName("@StgID")->Value =
			dsetNtHeader->FieldByName("StgID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@CustomerID")->Value =
			dsetNtHeader->FieldByName("MemberID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@Cash")->Value =
			dsetNtHeader->FieldByName("RecCash")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@CardMoney")->Value =
			dsetNtHeader->FieldByName("RecCardMoney")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@Remarks")->Value =
			dsetNtHeader->FieldByName("Remarks")->AsWideString;
		cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value =
			dsetNtHeader->FieldByName("State")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@Bsmode")->Value = 3;
		cmdUpdateNtHeader->Execute();
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

bool TfrmRetailReturnMng::AddNote(int supplierID, int catalogID)
{
	bool result = false;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
        	= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
        	= catalogID;
		cmdAddNote->Parameters->ParamByName("@SupplierID")->Value
			= supplierID;
		cmdAddNote->Parameters->ParamByName("@bkstackID")->Value = (int)(cbbkstackID->Items->Objects[cbbkstackID->ItemIndex]);
		if (m_bsmode == BSNote)
		{
        	cmdAddNote->Parameters->ParamByName("@NoteMode")->Value = 1;
        }
		else if (m_bsmode == BSNoteSendback)
		{
        	cmdAddNote->Parameters->ParamByName("@NoteMode")->Value = 2;
		}
		cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 3;
		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
		if (ret > 0)//插入成功
		{
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			result = true;
		}
		else if (ret == 0)//查无此书
		{

		}
		else if (ret == -1)//库存出错了
		{

		}
		else if (ret == -2) {

				   addnotereturnvalue = -2;

					result = true;

        }
	}
	return result;
}
void TfrmRetailReturnMng::UpdateNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{

		cmdUpdateNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		if (m_bsmode == BSNote)
		{
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= abs(dsetNote->FieldByName("Amount")->AsInteger);
		}
		else
		{
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= - abs(dsetNote->FieldByName("Amount")->AsInteger);
		}
		cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
			= fabs(dsetNote->FieldByName("Discount")->AsFloat);
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 3;
		cmdUpdateNote->Execute();
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}

	}
}
void TfrmRetailReturnMng::DelNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdDelNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
			cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 3;
			cmdDelNote->Execute();
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			String ids = "";
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = ids + dsetNote->FieldByName("ID")->AsString;
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
			}
			cmdBatchDelNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchDelNote->Parameters->ParamByName("@Bsmode")->Value = 3;
			cmdBatchDelNote->Execute();

		}
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}
void __fastcall TfrmRetailReturnMng::dsrcNtHeaderDataChange(TObject *Sender, TField *Field)
{
	//更新数据
	//UpdateNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::dsrcNoteDataChange(TObject *Sender, TField *Field)
{
	//更新数据
	//UpdateNote();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}
	if (Key == '\r')
	{
		if (!dsetNote->Active || !dsetNtHeader->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;

		if (IsChecked() == 1)
		{
			MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
			return;
		}

		if (edtCatalog->Text == "")
		{
			ChangeCatalogSearchMode();
		}
		else
		{
			switch (m_catalogSearchMode)
			{
			case 1:
			case 6:
            case 5:
			case 2:
			case 3:
				{
					if (m_catalogSearchMode==6) {
					  FLOAT price;
					  try
					  {
						price = StrToFloat(edtCatalog->Text);
					   }
					   catch(...)
					   {
						  MessageBox(0,"请输入正确的价格！","提示",MB_ICONWARNING);
						  return ;
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

					TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
					LandInfo li;
					li.app = m_app;
					li.con = m_con;
					li.userID = m_userID;
					li.storageID = m_storageID;
					frm->Init(&li);
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					frm->DoModalType = 6;//零售退货模式
					frm->RetailReturnfrm = this;
					frm->qikan = chqikan->Checked ;
					frm->qikanhao = edqikan->Text ;
					if (mrOk == frm->ShowModal())
					{
						int supplierID = -1,catalogID = -1;
						frm->GetSelectResult(supplierID, catalogID);
						if (!retailreturn(catalogID)) {
                        	return;
						}
						if (supplierID >= 0 && catalogID >= 0)
						{
							if (frm->SelectAll) {
						 for (int i = 0; i < frm->lengthint; i++) {
							cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BKSKid[i]);
                            if (!saleenable(frm->stkbkid[i])) {
								return;
							}
							if (AddNote(frm->SupplierID[i],frm->BkcatalogiD[i])) {

										Key=0;
								edtCatalog->Text = "";
								edqikan->Text = "";

								 }  else
								 {


								 }

							 }
						}else
						{
                            cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BSKid);
                            if (!saleenable(frm->BKinfoid)) {
								return;
							}
							if (AddNote(supplierID, catalogID))
							{
							 if (addnotereturnvalue == -2) {   	
							    addnotereturnvalue = 0; 
								//MessageBox(0,"不允许负库存销售！","批销" ,MB_ICONEXCLAMATION);
							
							 } else
							 {
								Key=0;
								edtCatalog->Text = "";
								edqikan->Text = "";
							  //	Perform(WM_NEXTDLGCTL, 0, 0);
                             }
							}
							else
								MessageBox(0,"库存无该书！","错误提示" ,MB_OK);
						}     }
					}
						Key=0;
						edtCatalog->Text = "";
						edqikan->Text = "";
					delete frm;
                }
				break;
			default:
				;
			}
		}
		//MoneyChange();
	}
}
//---------------------------------------------------------------------------

void TfrmRetailReturnMng::ChangeCatalogSearchMode()
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
		lblCatalog->Caption = "书号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "自编码";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "书名";
		break;
	case 5:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "作者";
		break;
	case 6:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "定价";
		break;
    default:
        break;
	}
}

void TfrmRetailReturnMng::ChangeBsmode(BSMode bsmode)
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

void TfrmRetailReturnMng::ChangeOpmode(OPMode opmode)
{
	if (opmode == m_opmode
		&& (opmode == OPDelNtHeader))
		return;

	//1为查单模式 2为添加单头模式 3为删除单头模式 4为添加单模式 5为删除单模式 6为统一模式 7为现场收款模式
	switch (opmode)
	{
	case OPFind:
		{
			if (IsChecked() == 0)
			{
				MessageBox(0,"您有未接单据,不能查询！","错误提示" ,MB_OK);
				numedtPaidinMoney->Enabled = true;
				return;
			}

			if (findpassword) {
            	if (!CheckOperateAuthority())
					return;
			}
			TfrmQryNoteCode* frm = new TfrmQryNoteCode(this,0);
			LandInfo li;
			li.app = m_app;
			li.con = m_con;
			li.userID = m_userID;
			li.storageID = m_storageID;
			frm->Init(&li);
			if (frm->ShowModal() == mrOk)
			{
				DelInvalidNtHeader();
				edtCatalog->Text = "";
				String code = frm->GetNoteCode();
				try
				{
					//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
					QryNtHeader(code);

					AnsiString riqi,sql ;
					riqi = DateToStr(frm->dtedtDate->Date);

					sql = "select * from BS_RetailNoteHeader where stgid = " + IntToStr(m_storageID) + " and datediff(day,'" + riqi + "',HdTime) = 0 and TotalDiscountedPrice <= 0";
					aqhd->Close();
					aqhd->SQL->Clear();
					aqhd->SQL->Add(sql);
					aqhd->Open();
					dbhd->Enabled = true;

					/*String sql,codetmp;
					codetmp = code;
					if (codetmp != "") {
						codetmp = codetmp.SubString(0,10);
						int codenext = StrToInt(codetmp) + 1;
						sql = "select RetailNtCode from BS_RetailNoteHeader where RetailNtCode >= " +  codetmp + "00000 and RetailNtCode < " + IntToStr(codenext) + "00000";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->Open();
						query->Last();
						codetmp = query->FieldByName("RetailNtCode")->AsString ;
					}
					MaxNote = codetmp; */
				}
				__finally
				{
					LockWindowUpdate(NULL);
				}
				if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
				{
					m_card = dsetNtHeader->FieldByName("RecCardMoney")->AsFloat;
					m_cash = dsetNtHeader->FieldByName("RecCash")->AsFloat;
					m_poscard = dsetNtHeader->FieldByName("poscard")->AsFloat;
					m_youhuiquan = dsetNtHeader->FieldByName("youhuiquan")->AsFloat;
					numedtPaidinMoney->Value = m_card + m_cash + m_poscard + m_youhuiquan;
					numedtOdd->Value = (m_card + m_cash + m_poscard + m_youhuiquan)
						- dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;
				}
			}
			m_opmode = opmode;
			delete frm;
		}
		break;
	case OPAddNtHeader:
		{
			//如果上次是添加模式，并且没有加进任何数据，则不能添加
			if (m_opmode == OPAddNtHeader &&
				dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			if (m_opmode == OPDelNote
				&& dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			if (IsChecked() == 0)
			{
				MessageBox(0,"您有未接单据,不能添加！","错误提示" ,MB_OK);
				numedtPaidinMoney->Enabled = true;
				return;
			}

			m_cash = 0;
			m_card = 0;
			m_poscard = 0;
			m_youhuiquan = 0;
			edtCatalog->Text = "";
			edprice->Text = "0.00";
			numedtPaidinMoney->Value = 0;
			numedtOdd->Value = 0;

			AddNtHeader();
			dbhd->Enabled = false;
            dblkpcbbMemberID->Enabled = true;
			dblkpcbbMemberID->SetFocus();
			m_opmode = opmode;
		}
		break;
	case OPDelNtHeader:
		{
			if (IsChecked() == 0)
			{
				MessageBox(0,"您有未接单据,不能删除！","错误提示" ,MB_OK);
				return;
			}

			if (!CheckOperateAuthority())
				return;

			edtCatalog->Text = "";
			if (IsChecked() == 1)
			{
				MessageBox(0,"已结单据不能删除！","错误提示" ,MB_OK);
				return;
			}
			//DelNtHeader();
			m_opmode = opmode;
        }
		break;
	case OPAddNote:
		edtCatalog->Text = "";
		edtCatalog->SetFocus();
		m_opmode = opmode;
		break;
	case OPDelNote:
		numedtPaidinMoney->Enabled = true;

		if (IsChecked() == 1)
		{
			MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
			return;
		}
        if (deletepassword) {
            if (!CheckOperateAuthority())
				return;
		}
		else
		{
			if (MessageBoxA(0,"是否要删除该条记录?","询问",MB_ICONQUESTION|MB_OKCANCEL)!=1 )
				return;
		}

		DelNote();
		logmessage = "删除零售退货单" + dsetNtHeader->FieldByName("RetailNtCode")->AsString + "的书目《" + dsetNote->FieldByName("CatalogName")->AsString + "》";
		AddEvent(1,"POS零售退货",m_userID,m_storageID,logmessage,linfo.con);
		ResetNtHeader();
		numedtOdd->Value = 	fabs(dbnbedtReceivableMoney->Value)  ;//找零与应找一样
    	m_opmode = opmode;
		break;
	case OPSetNotes:
    	if (IsChecked() == 1)
		{
			MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
			return;
		}

    	if (dsetNote->Active && dsetNote->RecordCount >= 1)
		{
			//统一模式
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
		numedtOdd->Value = 	fabs(dbnbedtReceivableMoney->Value)  ;//与找零售一样
		break;
	case OPRecCash:
    	//现场收款模式
    	m_opmode = opmode;
		break;
    default:
        break;
	}
	ModifyEnable();
	try {
		NtCodeChange();
	} catch (...) {
	}
}

int TfrmRetailReturnMng::IsChecked()
{
	int ret = -1;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0)//未结
	{
        ret = 0;
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1
		&& dsetNtHeader->FieldByName("State")->AsInteger != 0)//已结
	{
    	ret = 1;
	}
	return ret;
}

void TfrmRetailReturnMng::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0
		&& dsetNtHeader->FieldByName("RetailNtCode")->AsAnsiString == "0")//此单无任何记录
	{
		DelNtHeader();
	}
}


void __fastcall TfrmRetailReturnMng::FormClose(TObject *Sender, TCloseAction &Action)
{
	DelInvalidNtHeader();

	if (IsChecked() == 0) //处于未结帐状态，不允许退出
	{
		MessageBox(0,"有单未结算，请结单后退出！","错误提示" ,MB_OK);
		Action = caNone;
		return;
	}

	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	dsetBkstack->Active = false;
	dsetMember->Active = false;
	TfrmMDIChild::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::tlbtn8Click(TObject *Sender)
{	//删除
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con)
	{
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::mniBsNoteSendbackClick(TObject *Sender)
{
	//添加单据类型
	if (IsChecked() == 0)
	{
		MessageBox(0,"您有未接单据,不能添加！","错误提示" ,MB_OK);
		return;
	}

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
void TfrmRetailReturnMng::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	//
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
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
	cmdDelNote->Connection = m_con;
	dsetMember->Connection = m_con;
	dsetBkstack->Connection = m_con;
	dsetbear->Connection = m_con;
	query->Connection = m_con;
	aquery->Connection = m_con;
    dsetbear->Active = true;
	dsetMember->Active = true;
	ChangeCatalogSearchMode();
	chckbxSwitch->Checked = false;
	ChangeBsmode(BSNoteSendback);
	if (IsChecked() == 0)
	{
		MessageBox(0,"您有未接单据,不能添加！","错误提示" ,MB_OK);
		Close();
	}
	//退货密码
	String sql;
	sql = "select * from SYS_BSSET where name = 'lsusetuihuo'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	tuihuopassword = query->FieldByName("value")->AsBoolean ;
	if (tuihuopassword) {
    	if (!CheckOperateAuthority()) {
			Close();
		}
	}
	ChangeOpmode(OPAddNtHeader);
	addnotereturnvalue = 0;
	ReadConfig();

	GetBkStackInfo();

	sql = "select * from SYS_BSSET where name = 'RetailDiscountChange'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (!query->FieldByName("value")->AsBoolean  ) {
		dbnbedtDiscount->Enabled = false;
		retaildiscountchange = false;
	}
	sql = "select * from SYS_BSSET where name = 'retailxiaoshudian'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	format = "￥" + query->FieldByName("bk")->AsString ;
	//小票打印
	sql = "select * from SYS_BSSET where name = 'xiaopiaoprint'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	xiaopiaoprint = query->FieldByName("value")->AsBoolean ;
	//查单密码
	sql = "select * from SYS_BSSET where name = 'lsusefind'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	findpassword = query->FieldByName("value")->AsBoolean ;
	//删单密码
	sql = "select * from SYS_BSSET where name = 'lsusedelete'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	deletepassword = query->FieldByName("value")->AsBoolean ;

	//店面显示
	sql = "select id,Name from SYS_StorageInfo where ID = " + IntToStr(li->storageID) ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	edstoragename->Text = query->FieldByName("id")->AsString + query->FieldByName("Name")->AsString  ;
	//最低折扣
	sql = "select * from SYS_BSSET where name = 'minlsdiscount'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	mindiscount = query->FieldByName("value")->AsBoolean ;
	if (query->FieldByName("bk")->AsAnsiString == "1" ) {
		minstorage = true;
	}
	else
	{
    	minstorage = false;
	}
	mixdiscount = query->FieldByName("boundmix")->AsFloat ;

	mniPrintNtHeader->Checked = xiaopiaoprint;
	//dbnbedt3->DisplayFormat = format;
	dbnbedt4->DisplayFormat = format;
	numedtDiscountedMoney->DisplayFormat = format;
	dbnbedtReceivableMoney->DisplayFormat = format;
	numedtOdd->DisplayFormat = format;
	numedtCheck->DisplayFormat = format;
	numedtPaidinMoney->DisplayFormat =  format;
	numedtRec->DisplayFormat = format;

	/*sql = "select catalogmodle from BS_Fastelurustyle where Name = '零售' and stgid = " + IntToStr(li->storageID);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {
		m_catalogSearchMode = query->FieldByName("catalogmodle")->AsInteger;
		switch (m_catalogSearchMode) {
			case 1:
				lblCatalog->Caption = "书  号";
				break;
			case 2:
				lblCatalog->Caption = "自编码";
				break;
			case 3:
				lblCatalog->Caption = "书  名";
				break;
			case 5:
				lblCatalog->Caption = "作  者";
				break;
			case 6:
				lblCatalog->Caption = "定  价";
				break;
		default:
			;
		}
	}  */

	FormView();
}


void __fastcall TfrmRetailReturnMng::dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{


		Key = 0;

		   if (dbnbedtAmount->Text == "") {
			 dbnbedtAmount->Text  = "0";

		   }


			if ((StrToInt(ReplaceStr(dbnbedtAmount->Text,",",""))-StrToInt(ReplaceStr(dbnbedtTotalAmount->Text,",","")))>0) {
		   if (!dsetbear->FieldByName("value")->AsBoolean) {     //false 不能销售空库存
			 MessageBoxA(0,"销售数据大于当前库存数量！","警告",MB_ICONASTERISK);
			 dbnbedtAmount->Text =  dbnbedtTotalAmount->Text ;
		   }else
		   {
			if (chdingwei->Checked && !dsetNote->Eof ) {
				dbgrdNote->SetFocus();
				dsetNote->Next();
				dbgrdNote->SelectedRows->CurrentRowSelected = true;
				dbnbedtAmount->SetFocus();
			}
			else
			{
				Perform(WM_NEXTDLGCTL, 0, 0);
			}


		   }
		}else
		{
			if (chdingwei->Checked && !dsetNote->Eof ) {
				dbgrdNote->SetFocus();
				dsetNote->Next();
				dbgrdNote->SelectedRows->CurrentRowSelected = true;
				dbnbedtAmount->SetFocus();
			}
			else
			{
				Perform(WM_NEXTDLGCTL, 0, 0);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::tlbtn4Click(TObject *Sender)
{
	if (IsChecked() == 1)
	{
		MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
		return;
	}

	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		TfrmSelectMember* frm = new TfrmSelectMember(Application);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->Init(&li);
		if (mrOk == frm->ShowModal())
		{
			int id = frm->GetMemberID();
			if (id > 0)
			{
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("MemberID")->AsInteger = id;
				UpdateNtHeader();
			}
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::tlbtnRecMoneyClick(TObject *Sender)
{
	//收款
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)
	{
    	//首先把修改的更新一下哈
		dbgrdNote->SetFocus();
		//其次把最新数据刷新一下哈
		QryNtHeader();
		if (IsChecked() == 1)
		{
			MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
			return;
		}
		if (dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat > 0)
		{
			m_card = 0;
			m_cash = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;
			numedtPaidinMoney->Value = m_card + m_cash;
		}
		else
		{
			numedtPaidinMoney->Value = 0;
			numedtOdd->Value = (m_card + m_cash)
				- dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;
		}
		numedtPaidinMoney->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::tlbtnMixedClick(TObject *Sender)
{
	//混合收款
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)
	{
    	//首先把修改的更新一下哈
		dbgrdNote->SetFocus();
		//其次把最新数据刷新一下哈
		QryNtHeader();
		if (IsChecked() == 1)
		{
			MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
		}
		else if (dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat > 0)
		{
			TfrmMixedRecMoney* frm = new TfrmMixedRecMoney(this);
			frm->SetMustRec(dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat);
			frm->SetRecCard(m_card);
			frm->SetRecCash(m_cash);
			frm->SetCardRemain(dsetNtHeader->FieldByName("Balance")->AsFloat);
			if (mrOk == frm->ShowModal())
			{
				frm->GetRecMoney(m_card, m_cash,m_poscard,m_youhuiquan);
				numedtPaidinMoney->Value = m_card + m_cash + m_poscard + m_youhuiquan;
			}
			delete frm;
			numedtPaidinMoney->SetFocus();
		}
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmRetailReturnMng::tlbtn7Click(TObject *Sender)
{
	//
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRetailReturnMng::numedtPaidinMoneyChange(TObject *Sender)
{
  //	MoneyChange();
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		if (dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat >= 0)
		{
			if ((numedtPaidinMoney->Value <= m_card) &&  (numedtPaidinMoney->Value != 0))
			{
				numedtPaidinMoney->Value = m_card;
				m_cash = 0;
			}
			else
			{
				m_cash = numedtPaidinMoney->Value - m_card - m_poscard - m_youhuiquan;
				numedtOdd->Value = (m_card + m_cash + m_poscard + m_youhuiquan)
					- dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;
			}
		}
		else//供应商问题
		{
			m_card = 0;
			m_cash = 0;
			m_poscard = 0;
			m_youhuiquan = 0;
			numedtPaidinMoney->Value = 0;
			numedtOdd->Value = (m_card + m_cash)
				- dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::numedtPaidinMoneyKeyPress(TObject *Sender, wchar_t &Key)
{
	String sql;
	if (Key == '\r')
	{
		if (IsChecked() == 1)
		{
			MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
			return;
		}

		//其次把最新数据刷新一下哈
        QryNtHeader();

		if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
			&& dsetNote->Active && dsetNote->RecordCount >= 1)
		{
			/*if (lbtitle->Caption == "零售单") {
            	float price = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;

				sql = "select * from SYS_BSSET where name = 'retairangge' and value = 'True'";
				aquery->Close();
				aquery->SQL->Clear();
				aquery->SQL->Add(sql);
				aquery->Open();
				while (!aquery->Eof)
				{
					if (aquery->FieldByName("boundmix")->AsFloat < price && price <= aquery->FieldByName("boundmax")->AsFloat ) {
						break;
					}
					aquery->Next();
				}
				float retairange;
				if (aquery->FieldByName("boundmix")->AsFloat < price && price <= aquery->FieldByName("boundmax")->AsFloat) {
					retairange = aquery->FieldByName("bk")->AsFloat ;
				}
				else
				{
					retairange = 0.0;
				}
				retairange = 0-retairange;
				if (numedtOdd->Value < retairange) {
					MessageBox(0,"你的余额不足！","结款" ,MB_OK);
				}
				else if (numedtOdd->Value >= 0) {
					numedtDiscountedMoney->Value = dbnbedtReceivableMoney->Value;
					numedtTotalAmount->IntValue = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
					numedtCheck->Value = numedtOdd->Value;
					numedtRec->Value = numedtPaidinMoney->Value;
					dsetNtHeader->Edit();
					dsetNtHeader->FieldByName("RecCash")->AsFloat = m_cash;
					dsetNtHeader->Edit();
					dsetNtHeader->FieldByName("RecCardMoney")->AsFloat = m_card;
					dsetNtHeader->Edit();
					dsetNtHeader->FieldByName("State")->AsInteger = 1;
					UpdateNtHeader();
					///更新会员表，总消费
					 if (m_card != 0) {
						 String sql = "update CUST_MemberInfo set totalconsumption = totalconsumption + " + FloatToStr(m_card) ;
								 sql = sql + " where id =  " + dsetNtHeader->FieldByName("memberid")->AsAnsiString  ;
						 TADOQuery * aq = new TADOQuery(this);
						 aq->Connection  = m_con ;
						 aq->Close();
						 aq->SQL->Clear();
						 aq->SQL->Add(sql);
						 aq->ExecSQL();
						 delete aq;

					 }
					PrintNtHeader();
					mniPrintNtHeader->Checked = xiaopiaoprint;
					tlbtn8Click(BtnNew);
				}
				else
				{
            		TMsgDlgButtons btns;
					btns << mbOK << mbCancel;
					if (MessageBox(0,"你输入的金额不足，是否继续？","结款",MB_ICONQUESTION|MB_OKCANCEL)==1) {
						numedtDiscountedMoney->Value = dbnbedtReceivableMoney->Value;
						numedtTotalAmount->IntValue = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
						numedtCheck->Value = numedtOdd->Value;
						numedtRec->Value = numedtPaidinMoney->Value;
						dsetNtHeader->Edit();
						dsetNtHeader->FieldByName("RecCash")->AsFloat = m_cash;
						dsetNtHeader->Edit();
						dsetNtHeader->FieldByName("RecCardMoney")->AsFloat = m_card;
						dsetNtHeader->Edit();
						dsetNtHeader->FieldByName("State")->AsInteger = 1;
						UpdateNtHeader();
						PrintNtHeader();
						mniPrintNtHeader->Checked = xiaopiaoprint;
							///更新会员表，总消费
					 if (m_card != 0) {
						 String sql = "update CUST_MemberInfo set totalconsumption = totalconsumption + " + FloatToStr(m_card) ;
								 sql = sql + " where id =  " + dsetNtHeader->FieldByName("memberid")->AsAnsiString  ;
						 TADOQuery * aq = new TADOQuery(this);
						 aq->Connection  = m_con ;
						 aq->Close();
						 aq->SQL->Clear();
						 aq->SQL->Add(sql);
						 aq->ExecSQL();
						 delete aq;

					 }
						tlbtn8Click(BtnNew);
					}
				}
			} */

			//如果最后是整元，或者整5角
			/*if (price >=0 && price <=50.49)//0~50元之内最多只能少4毛9
			{
				if (numedtOdd->Value <= -0.49)
				{
					MessageBox(0,"你的余额不足！","结款" ,MB_OK);
				}
				else if (numedtOdd->Value >= 0)
				{
					numedtDiscountedMoney->Value = dbnbedtReceivableMoney->Value;
					numedtTotalAmount->IntValue = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
					numedtCheck->Value = numedtOdd->Value;
					numedtRec->Value = numedtPaidinMoney->Value;
					dsetNtHeader->Edit();
					dsetNtHeader->FieldByName("RecCash")->AsFloat = m_cash;
					dsetNtHeader->Edit();
					dsetNtHeader->FieldByName("RecCardMoney")->AsFloat = m_card;
					dsetNtHeader->Edit();
					dsetNtHeader->FieldByName("State")->AsInteger = 1;
					UpdateNtHeader();
					///更新会员表，总消费
					 if (m_card != 0) {
						 String sql = "update CUST_MemberInfo set totalconsumption = totalconsumption + " + FloatToStr(m_card) ;
								 sql = sql + " where id =  " + dsetNtHeader->FieldByName("memberid")->AsAnsiString  ;
						 TADOQuery * aq = new TADOQuery(this);
						 aq->Connection  = m_con ;
						 aq->Close();
						 aq->SQL->Clear();
						 aq->SQL->Add(sql);
						 aq->ExecSQL();
						 delete aq;

					 }
					PrintNtHeader();
					tlbtn8Click(mtbbtnAddNtHeader);

				}
				else
				{
					TMsgDlgButtons btns;
					btns << mbOK << mbCancel;
					if (MessageBox(0,"你输入的金额不足，是否继续？","结款",MB_ICONQUESTION|MB_OKCANCEL)==1) {
						numedtDiscountedMoney->Value = dbnbedtReceivableMoney->Value;
						numedtTotalAmount->IntValue = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
						numedtCheck->Value = numedtOdd->Value;
						numedtRec->Value = numedtPaidinMoney->Value;
						dsetNtHeader->Edit();
						dsetNtHeader->FieldByName("RecCash")->AsFloat = m_cash;
						dsetNtHeader->Edit();
						dsetNtHeader->FieldByName("RecCardMoney")->AsFloat = m_card;
						dsetNtHeader->Edit();
						dsetNtHeader->FieldByName("State")->AsInteger = 1;
						UpdateNtHeader();
						PrintNtHeader();
							///更新会员表，总消费
					 if (m_card != 0) {
						 String sql = "update CUST_MemberInfo set totalconsumption = totalconsumption + " + FloatToStr(m_card) ;
								 sql = sql + " where id =  " + dsetNtHeader->FieldByName("memberid")->AsAnsiString  ;
						 TADOQuery * aq = new TADOQuery(this);
						 aq->Connection  = m_con ;
						 aq->Close();
						 aq->SQL->Clear();
						 aq->SQL->Add(sql);
						 aq->ExecSQL();
						 delete aq;

					 }

						tlbtn8Click(mtbbtnAddNtHeader);
					}
				}
			}
			else if (price > 50.49)//50元以上最多只能少9毛9
			{
				if (numedtOdd->Value <= -0.99)
				{
					MessageBox(0,"你的余额不足！","结款" ,MB_OK);
				}
				else if (numedtOdd->Value >= 0)
				{
					numedtDiscountedMoney->Value = dbnbedtReceivableMoney->Value;
					numedtTotalAmount->IntValue = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
					numedtCheck->Value = numedtOdd->Value;
					numedtRec->Value = numedtPaidinMoney->Value;
					dsetNtHeader->Edit();
					dsetNtHeader->FieldByName("RecCash")->AsFloat = m_cash;
					dsetNtHeader->Edit();
					dsetNtHeader->FieldByName("RecCardMoney")->AsFloat = m_card;
					dsetNtHeader->Edit();
					dsetNtHeader->FieldByName("State")->AsInteger = 1;
					UpdateNtHeader();

					PrintNtHeader();
						///更新会员表，总消费
					 if (m_card != 0) {
						 String sql = "update CUST_MemberInfo set totalconsumption = totalconsumption + " + FloatToStr(m_card) ;
								 sql = sql + " where id =  " + dsetNtHeader->FieldByName("memberid")->AsAnsiString  ;
						 TADOQuery * aq = new TADOQuery(this);
						 aq->Connection  = m_con ;
						 aq->Close();
						 aq->SQL->Clear();
						 aq->SQL->Add(sql);
						 aq->ExecSQL();
						 delete aq;

					 }
					tlbtn8Click(mtbbtnAddNtHeader);
				}
				else
				{
					TMsgDlgButtons btns;
					btns << mbOK << mbCancel;
					if (MessageBox(0,"你输入的金额不足，是否继续？","结款",MB_ICONQUESTION|MB_OKCANCEL)==1) {
						numedtDiscountedMoney->Value = dbnbedtReceivableMoney->Value;
						numedtTotalAmount->IntValue = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
						numedtCheck->Value = numedtOdd->Value;
						numedtRec->Value = numedtPaidinMoney->Value;
						dsetNtHeader->Edit();
						dsetNtHeader->FieldByName("RecCash")->AsFloat = m_cash;
						dsetNtHeader->Edit();
						dsetNtHeader->FieldByName("RecCardMoney")->AsFloat = m_card;
						dsetNtHeader->Edit();
						dsetNtHeader->FieldByName("State")->AsInteger = 1;
						UpdateNtHeader();
						PrintNtHeader();
							///更新会员表，总消费
					 if (m_card != 0) {
						 String sql = "update CUST_MemberInfo set totalconsumption = totalconsumption + " + FloatToStr(m_card) ;
								 sql = sql +" where id =  " + dsetNtHeader->FieldByName("memberid")->AsAnsiString  ;
						 TADOQuery * aq = new TADOQuery(this);
						 aq->Connection  = m_con ;
						 aq->Close();
						 aq->SQL->Clear();
						 aq->SQL->Add(sql);
						 aq->ExecSQL();
						 delete aq;

					 }
						tlbtn8Click(mtbbtnAddNtHeader);
					}
				}
			} */
			//else//退货的情况
			//{
				numedtDiscountedMoney->Value = dbnbedtReceivableMoney->Value;
				numedtTotalAmount->IntValue = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
				numedtCheck->Value = numedtOdd->Value;
				numedtRec->Value = numedtPaidinMoney->Value;
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("RecCash")->AsFloat = m_cash;
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("RecCardMoney")->AsFloat = m_card;
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("State")->AsInteger = 1;
				UpdateNtHeader();
				PrintNtHeader();
					///更新会员表，总消费
					 if (m_card != 0) {
						 String sql = "update CUST_MemberInfo set totalconsumption = totalconsumption - " + FloatToStr(m_card) ;
								 sql = sql + " where id =  " + dsetNtHeader->FieldByName("memberid")->AsAnsiString  ;
						 TADOQuery * aq = new TADOQuery(this);
						 aq->Connection  = m_con ;
						 aq->Close();
						 aq->SQL->Clear();
						 aq->SQL->Add(sql);
						 aq->ExecSQL();
						 delete aq;

					 }
				//mniBsNoteSendbackClick(mniBsNote);
				ChangeBsmode(BSNoteSendback);
				ChangeOpmode(OPAddNtHeader);
			  //	tlbtn8Click(mtbbtnAddNtHeader);

		   //	}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmRetailReturnMng::numedtAmountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmRetailReturnMng::dbnbedtAmountExit(TObject *Sender)
{
	//
	if (IsChecked() == 1)
	{
		MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
		return;
	}
	UpdateNote();
	if (numedtPaidinMoney->Value != 0.0) {
    	MoneyChange();
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::dblkpcbbMemberIDExit(TObject *Sender)
{
	//
	if (IsChecked() == 1)
	{
		MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
		return;
	}
	UpdateNtHeader();
}

void TfrmRetailReturnMng::OnHotKeyPress(DWORD vkCode)
{
	if (vkCode == VK_F12)
	{
		tlbtnRecMoneyClick(NULL);
	}
}

void TfrmRetailReturnMng::QryBkstack()
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

void __fastcall TfrmRetailReturnMng::dsetNoteAfterScroll(TDataSet *DataSet)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
        QryBkstack();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == VK_F1) {   // 查单
		tlbtn8->Click();
	}
	if (Key == VK_F2) {   // 增单
		BtnNew->Click();
	}
	if (Key == VK_F3) {   // 钱箱
		BtnUpOneLevel->Click();
	}
	if (Key == VK_F4) {   // 会员卡
		tlbtn4->Click();
	}
	if (Key == VK_F5) {   // 删行
		tlbtn2->Click();
	}
	if (Key == VK_F6) {   // 统一
		tlbtn3->Click();
	}
	if (Key == VK_F8) {   // 混合收款
		tlbtnMixed->Click();
	}
	if (Key == VK_F9) {   // 删单
		tlbtn1->Click();
	}
	if (Key == VK_F10) {  // 打印
		BtnPrint->Click();
	}
	if (Key == VK_F12) {   //快捷收款
		tlbtnRecMoney->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==83) {    //数量
		dbnbedtAmount->SetFocus();
	}
	if (Shift.Contains(ssAlt)&& Key ==68) {   //折扣
		dbnbedtDiscount->SetFocus();
	}

	if (Shift.Contains(ssAlt)&& Key ==81  ) {
		tlbtn7->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==78  ) {
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==70  ) {
		BtnView->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {
		WindowState = wsNormal  ;
	}
	if (Shift.Contains(ssAlt)&& Key ==71) {
		mdifdiscount->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==66) {   //换价
		RzButton6->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 88) {    //期刊
		if (chqikan->Checked ) {
			chqikan->Checked = false;
		}
		else
		{
			chqikan->Checked = true;
		}
		chqikan->OnClick ;
	}
	if (Shift.Contains(ssAlt)&& Key == 67) {    //定位
		if (chdingwei->Checked ) {
			chdingwei->Checked = false;
		}
		else
		{
			chdingwei->Checked = true;
		}
	}
}
//---------------------------------------------------------------------------

void TfrmRetailReturnMng::ResetNtHeader()
{
	//重置单头
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0)
	{
		cmdResetNtHeader->Parameters->ParamByName("@ID")->Value =
		dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdResetNtHeader->Parameters->ParamByName("@Bsmode")->Value = 3;
		cmdResetNtHeader->Execute();
		try
		{
			LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
		}
		__finally
		{
			LockWindowUpdate(NULL);
		}
	}
}

void __fastcall TfrmRetailReturnMng::numedtPaidinMoneyEnter(TObject *Sender)
{
	//
	QryNtHeader();
}
//---------------------------------------------------------------------------


void TfrmRetailReturnMng::PrintNtHeader()
{
	//
	if (mniPrintNtHeader->Checked)
	{
    	BtnPrintClick(NULL);
	}
	else
	{
		if (MessageBox(0,"是否打印小票？","提示",MB_ICONQUESTION|MB_YESNO+MB_DEFBUTTON2)== 6){
			BtnPrintClick(NULL);
		}
	}
}
void __fastcall TfrmRetailReturnMng::mniPrintNtHeaderClick(TObject *Sender)
{
	WriteConfig();
}
//---------------------------------------------------------------------------

void TfrmRetailReturnMng::ReadConfig()
{
	String inipath = ExtractFilePath(Application->ExeName) + "/config.ini";
	if (FileExists(inipath))
	{
    	TIniFile* file = new TIniFile(inipath);
		try
		{
        	bool print = false;
			file->ReadBool("Retail","PrintOnRetail",print);
            mniPrintNtHeader->Checked = print;
		}
		catch(...)
		{
        	file->WriteBool("Retail","PrintOnRetail",mniPrintNtHeader->Checked);
		}
		delete file;
	}
	else
	{
    	TIniFile* file = new TIniFile(inipath);
		try
		{
			file->WriteBool("Retail","PrintOnRetail",mniPrintNtHeader->Checked);

		}
		catch(...)
		{

		}
		delete file;
    }
}

void TfrmRetailReturnMng::WriteConfig()
{
	//写ini文件
	String inipath = ExtractFilePath(Application->ExeName) + "/config.ini";
	TIniFile* file = new TIniFile(inipath);
	try
	{
		file->WriteBool("Retail","PrintOnRetail",mniPrintNtHeader->Checked);
	}
	catch(...)
	{

	}
	delete file;
}
void __fastcall TfrmRetailReturnMng::N1Click(TObject *Sender)
{
   lblCatalog->Caption = "书号";
   m_catalogSearchMode = 1;
   if (chqikan->Checked ) {
	   edtCatalog->MaxLength = 15;
   }
   else
   {
    	edtCatalog->MaxLength = 13;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::N2Click(TObject *Sender)
{
	 lblCatalog->Caption = "自编码";
	 m_catalogSearchMode = 2;
	 edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::N3Click(TObject *Sender)
{
	  lblCatalog->Caption = "书名";
	  m_catalogSearchMode  = 3;
	  edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{  if (Key == '\r')
	{
    	if (chdingwei->Checked && !dsetNote->Eof ) {
			dbgrdNote->SetFocus();
			dsetNote->Next();
			dbgrdNote->SelectedRows->CurrentRowSelected = true;
			dbnbedtDiscount->SetFocus();
		}
		else
		{
        	Perform(WM_NEXTDLGCTL, 0, 0);
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	 m_catalogSearchMode  = 6;
	 edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------





void  TfrmRetailReturnMng::FindNote(String code)
{


	DelInvalidNtHeader();
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader(code);
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		m_card = dsetNtHeader->FieldByName("RecCardMoney")->AsFloat;
		m_cash = dsetNtHeader->FieldByName("RecCash")->AsFloat;
		numedtPaidinMoney->Value = m_card + m_cash;
		numedtOdd->Value = (m_card + m_cash)
				- dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;
	}

}

//---------------------------------------------------------------------------

void TfrmRetailReturnMng::NtCodeChange()
{
	
}

void __fastcall TfrmRetailReturnMng::N6Click(TObject *Sender)
{
	for (int i = 1; i <= dsetNote->RecordCount ; i++) {
		dbgrdNote->DataSource->DataSet->RecNo = i;
		dbgrdNote->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void TfrmRetailReturnMng::MoneyChange()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		if (dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat >= 0)
		{
			if ((numedtPaidinMoney->Value <= m_card) &&  (numedtPaidinMoney->Value != 0))
			{
				numedtPaidinMoney->Value = m_card;
				m_cash = 0;
			}
			else
			{
				m_cash = numedtPaidinMoney->Value - m_card;
				numedtOdd->Value = (m_card + m_cash)
					- dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;
			}
		}
		else//供应商问题
		{
			m_card = 0;
			m_cash = 0;
			numedtPaidinMoney->Value = 0;
			numedtOdd->Value = (m_card + m_cash)
				- dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;
        }
	}
}
//---------------------------------------------------------------------------


bool TfrmRetailReturnMng::retailreturn(int catalogID)
{

	String sql;
	sql = "select value from SYS_BSSET where name = 'nosalereturn'";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (!aquery->FieldByName("value")->AsBoolean) {
		sql = "select count(*) as count from BS_RetailNote left join STK_BookInfo on BS_RetailNote.BkInfoID = STK_BookInfo.ID "
		" left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.ID where BS_BookCatalog.ID = " + IntToStr(catalogID);
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		int count = aquery->FieldByName("count")->AsInteger ;
		if (count == 0) {
			MessageBox(0,"该书没有销售过，不能退货！","零售退货" ,MB_OK);
			return false;
		}
	}

	return true;
}
//---------------------------------------------------------------------------

void TfrmRetailReturnMng::ModifyEnable()
{
	if (m_opmode == OPFind) {
		dbnbedtAmount->Enabled = false;
		dbnbedtDiscount->Enabled = false;
		numedtPaidinMoney->Enabled = false;
		cbbkstackID->Enabled = false;




	}
	else
	{

		dbnbedtAmount->Enabled = true;
		if (retaildiscountchange) {
			dbnbedtDiscount->Enabled = true;
		}
		numedtPaidinMoney->Enabled = true;
	   //	cbbkstackID->Enabled = true;
	}
}
//---------------------------------------------------------------------------






void __fastcall TfrmRetailReturnMng::cbbkstackIDExit(TObject *Sender)
{
	if (IsChecked() == 1)
	{
		MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
		return;
	}
	UpdateNote();
	MoneyChange();
}
//---------------------------------------------------------------------------


void TfrmRetailReturnMng::GetBkStackInfo()
{
   AnsiString sql= "select  CAST(stgid as varchar(10)) + ' 店 ' + name  as name, ID from STK_BookstackInfo where StgID = " + IntToStr(m_storageID);
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
//---------------------------------------------------------------------------

bool  TfrmRetailReturnMng::saleenable(int stkid)
{
	AnsiString sql;
	sql = "select * from STK_StockInventories where states = 0 and STK_bookInfoID = " + IntToStr(stkid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {
		MessageBox(0,"该书正在盘点，不能退货！","提示",MB_ICONWARNING);
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
        	MessageBox(0,"该书正在盘点，不能销售！","提示",MB_ICONWARNING);
			return false;
		}
		else
		{
        	return true;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmRetailReturnMng::BtnViewClick(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,linfo.con,linfo.storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------


void __fastcall TfrmRetailReturnMng::RzButton1Click(TObject *Sender)
{
  	String *ID;
   //	ID = "";
	if (IsChecked() == 1)
	{
		MessageBoxA(0,"已结单据不能修改!","零售",MB_ICONEXCLAMATION);
		return;
	}
   TfrmMemberCard * frm = new TfrmMemberCard(m_app,1,ID ,m_con);
   frm->ShowModal();
   delete frm;

	int count1 = dsetMember->RecordCount;
	dsetMember->Active = false;
	dsetMember->Active = true;
	int count2 = dsetMember->RecordCount;
	if (count2 > count1)
	{
		dsetMember->Last();
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("MemberID")->AsInteger = dsetMember->FieldByName("ID")->AsInteger;
		UpdateNtHeader();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------


void TfrmRetailReturnMng::FormView()
{
	AnsiString sql;
	sql = "select * from BS_SYS_Formview where stgid = " + IntToStr(m_storageID) + " and ParentID = 2";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while (!aquery->Eof)
	{
		if (aquery->FieldByName("Name")->AsAnsiString == "查单" ) {
			tlbtn8->Visible = aquery->FieldByName("state")->AsBoolean ;
		}
		if (aquery->FieldByName("Name")->AsAnsiString == "增单" ) {
			BtnNew->Visible = aquery->FieldByName("state")->AsBoolean ;
		}
		if (aquery->FieldByName("Name")->AsAnsiString == "删单" ) {
			tlbtn1->Visible = aquery->FieldByName("state")->AsBoolean ;
		}
		if (aquery->FieldByName("Name")->AsAnsiString == "删行" ) {
			tlbtn2->Visible = aquery->FieldByName("state")->AsBoolean ;
		}
		if (aquery->FieldByName("Name")->AsAnsiString == "统一" ) {
			tlbtn3->Visible = aquery->FieldByName("state")->AsBoolean ;
		}
		if (aquery->FieldByName("Name")->AsAnsiString == "会员卡" ) {
			tlbtn4->Visible = aquery->FieldByName("state")->AsBoolean ;
		}
		if (aquery->FieldByName("Name")->AsAnsiString == "直接收款" ) {
			tlbtnRecMoney->Visible = aquery->FieldByName("state")->AsBoolean ;
		}
		if (aquery->FieldByName("Name")->AsAnsiString == "混合收款" ) {
			tlbtnMixed->Visible = aquery->FieldByName("state")->AsBoolean ;
		}
		if (aquery->FieldByName("Name")->AsAnsiString == "打印" ) {
			BtnPrint->Visible = aquery->FieldByName("state")->AsBoolean ;
		}
		if (aquery->FieldByName("Name")->AsAnsiString == "查书" ) {
			BtnView->Visible = aquery->FieldByName("state")->AsBoolean ;
		}
		if (aquery->FieldByName("Name")->AsAnsiString == "最小化" ) {
			BtnAlignBottom->Visible = aquery->FieldByName("state")->AsBoolean ;
		}
		if (aquery->FieldByName("Name")->AsAnsiString == "钱箱" ) {
			BtnUpOneLevel->Visible = aquery->FieldByName("state")->AsBoolean ;
		}
		aquery->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::N7Click(TObject *Sender)
{
	lblCatalog->Caption = "作者";
	m_catalogSearchMode  = 5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::BtnUpOneLevelClick(TObject *Sender)
{
	int nLpt  ;
	char p[5]= {27,112,0,60,255};
	nLpt = FileOpen(TEXT("LPT1"), fmOpenWrite);
	try {
    	if (nLpt <= 0) return;
		FileWrite(nLpt, p , 5);
	}
	__finally
	{
		FileClose(nLpt);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::BtnPrintClick(TObject *Sender)
{
	//打印
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		try
		{
			TfrmPrint * frm = new TfrmPrint(Application);
			frm->RetailPrint(dsetNtHeader->FieldByName("ID")->AsString, m_con,m_storageID);
			delete frm;
			//TfrmPrint::RetailPrint(dsetNtHeader->FieldByName("ID")->AsString, m_con);
		}
		catch(...)
		{
			MessageBox(0,"打印失败！","错误提示" ,MB_OK);
        }
	}
}
//---------------------------------------------------------------------------
void  TfrmRetailReturnMng::operterview(int operterid)
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
	edopername->Text = aq->FieldByName("name")->AsString;
	delete aq;
}
//---------------------------------------------------------------------------


void __fastcall TfrmRetailReturnMng::mdifdiscountClick(TObject *Sender)
{
	if (dbnbedtDiscount->Enabled) {
    	return;
	}
	if (!CheckOperateAuthority())
		return;
	dbnbedtDiscount->Enabled = true;
	dbnbedtDiscount->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::membkExit(TObject *Sender)
{
	if (IsChecked() == 1)
	{
		MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
		return;
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("Remarks")->AsString = membk->Text ;
		dsetNtHeader->UpdateBatch(arAll);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmRetailReturnMng::RzButton6Click(TObject *Sender)
{
	edprice->Enabled = true;
	edprice->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::edpriceKeyPress(TObject *Sender, wchar_t &Key)

{
    if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
		Key = NULL;
	}
	if (Key == '\r') {
    	if (dsetNote->IsEmpty() ) {
			return;
		}
		if (IsChecked() == 1)
		{
			MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
			return;
		}

		try {
			float discount;
			discount =  StrToFloat(edprice->Text)*100/dsetNote->FieldByName("Price")->AsFloat;
            if (!DiscountEnable(discount,dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
				MessageBox(0,"低于最低折扣！","错误提示" ,MB_OK);
				return;
			}

			if (StrToFloat(edprice->Text) > dsetNote->FieldByName("Price")->AsFloat ) {
            	MessageBox(0,"售价不能大于该书定价！","错误提示" ,MB_OK);
				return;
			}

			dbnbedtDiscount->Value = discount;

			edprice->Text = FormatFloat("0.00",StrToFloat(edprice->Text));

			dsetNote->Edit();
			dsetNote->FieldByName("Discount")->AsFloat = discount;
			dsetNote->Post();
			UpdateNote();
			if (numedtPaidinMoney->Value != 0.00) {
				MoneyChange();
			}

		} catch (...) {
		}
		edtCatalog->SetFocus();
        edprice->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::chqikanClick(TObject *Sender)
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

void __fastcall TfrmRetailReturnMng::edqikanKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        if (!dsetNote->Active || !dsetNtHeader->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;

		if (IsChecked() == 1)
		{
			MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
			return;
		}

		if (edtCatalog->Text == "")
		{
			//ChangeCatalogSearchMode();
		}
		else
		{
			switch (m_catalogSearchMode)
			{
			case 1:
			  //	if (edtCatalog->Text.Length() != 13)
			  //	{
			  //		ShowMessage("条码输入错误！");
			  //		return;
			  //	}
			case 6:
            case 5:
			case 2:
			case 3:
				{
					if (m_catalogSearchMode==6) {
					  FLOAT price;
					  try
					  {
						price = StrToFloat(edtCatalog->Text);
					   }
					   catch(...)
					   {
						  MessageBox(0,"请输入正确的价格！","提示",MB_ICONWARNING);
						  return ;
					   }

					}



					TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
					LandInfo li;
					li.app = m_app;
					li.con = m_con;
					li.userID = m_userID;
					li.storageID = m_storageID;
					frm->Init(&li);
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					frm->DoModalType = 6;//零售退货模式
					frm->RetailReturnfrm = this;
					frm->qikan = chqikan->Checked ;
					frm->qikanhao = edqikan->Text ;
					if (mrOk == frm->ShowModal())
					{
						int supplierID = -1,catalogID = -1;
						frm->GetSelectResult(supplierID, catalogID);
						if (!retailreturn(catalogID)) {
                        	return;
						}
						if (supplierID >= 0 && catalogID >= 0)
						{
							if (frm->SelectAll) {
						 for (int i = 0; i < frm->lengthint; i++) {
							cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BKSKid[i]);
                            if (!saleenable(frm->stkbkid[i])) {
								return;
							}
							if (AddNote(frm->SupplierID[i],frm->BkcatalogiD[i])) {

										Key=0;
								edtCatalog->Text = "";
								edqikan->Text = "";

								 }  else
								 {


								 }

							 }
						}else
						{
                            cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BSKid);
                            if (!saleenable(frm->BKinfoid)) {
								return;
							}
							if (AddNote(supplierID, catalogID))
							{
							 if (addnotereturnvalue == -2) {
							    addnotereturnvalue = 0;
								MessageBox(0,"不允许负库存销售！","批销" ,MB_ICONEXCLAMATION);

							 } else
							 {
								Key=0;
								edtCatalog->Text = "";
								edqikan->Text = "";
							  //	Perform(WM_NEXTDLGCTL, 0, 0);
                             }
							}
							else
								MessageBox(0,"库存无该书！","错误提示" ,MB_OK);
						}     }
					}
					else
					{
                    	edtCatalog->SetFocus();
					}
						Key=0;
						edtCatalog->Text = "";
						edqikan->Text = "";
					delete frm;
                }
				break;
			default:
				;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::dbgrdNoteCellClick(TColumn *Column)
{
	ShowPrice();
}
//---------------------------------------------------------------------------
void TfrmRetailReturnMng::ShowPrice()
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	try {
		edprice->Text = FormatFloat("0.00",dsetNote->FieldByName("Price")->AsFloat *dsetNote->FieldByName("Discount")->AsFloat * 0.01);
	} catch (...) {
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailReturnMng::dblkpcbbMemberIDKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (dsetNtHeader->IsEmpty() ) {
			return;
		}
		if (dsetNtHeader->FieldByName("RetailNtCode")->AsAnsiString != "0" ) {
			return;
		}
		AnsiString sql;
		sql = "update BS_RetailNoteHeader set RetailNtCode = dbo.UF_BS_BuildNtCode(" + IntToStr(m_storageID) + ", getdate(), 3,0) where id = " + dsetNtHeader->FieldByName("id")->AsAnsiString ;
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
		try {
        	QryNtHeader();
        } catch (...) {
		}
		edtCatalog->SetFocus();
	}
}
//---------------------------------------------------------------------------
bool TfrmRetailReturnMng::DiscountEnable(float discount,int catalogid)
{
	if (mindiscount) {
		if (minstorage) {
			AnsiString sql;
			sql = "select case when sum(FixedPrice) <> 0 then sum(DiscountedPrice)/sum(FixedPrice) else 0 end as discount from BS_StorageNote "
				" join stk_bookinfo on BS_StorageNote.BkInfoID = stk_bookinfo.id "
				" join BS_BookCatalog on stk_bookinfo.BkcatalogID = BS_BookCatalog.id where BS_BookCatalog.id = " + IntToStr(catalogid);
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->FieldByName("discount")->AsFloat == 0.00 ) {
				if (discount >= mixdiscount) {
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (discount >= query->FieldByName("discount")->AsFloat  ) {
					return true;
				}
				else
				{
                	return false;
				}
			}
		}
		else
		{
			if (discount >= mixdiscount) {
				return true;
			}
			else
			{
            	return false;
			}
		}
	}
	else
	{
		return true;
	}
}

//---------------------------------------------------------------------------


void __fastcall TfrmRetailReturnMng::dbnbedtDiscountExit(TObject *Sender)
{
	if (IsChecked() == 1)
	{
		MessageBox(0,"已结单据不能修改！","错误提示" ,MB_OK);
		return;
	}
	float discount =  dsetNote->FieldByName("DiscountedPrice")->AsFloat*100/dsetNote->FieldByName("FixedPrice")->AsFloat;
	if (!DiscountEnable(dbnbedtDiscount->Value,dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
		MessageBox(0,"低于最低折扣！","错误提示" ,MB_OK);

		dsetNote->Edit();
		dsetNote->FieldByName("discount")->AsFloat = discount;
		dsetNote->Post();
		return;
	}
	UpdateNote();
	if (numedtPaidinMoney->Value != 0.0) {
    	MoneyChange();
	}
}
//---------------------------------------------------------------------------

