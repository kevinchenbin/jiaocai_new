//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RetailSummaryForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBGrid"
#pragma link "RzLabel"
#pragma link "Chart"
#pragma link "DBChart"
#pragma link "Series"
#pragma link "TeeData"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TfrmRetailSummary *frmRetailSummary;
//---------------------------------------------------------------------------
__fastcall TfrmRetailSummary::TfrmRetailSummary(TComponent* Owner)
	: TfrmMDIChild(Owner)
{              m_module = MTData;
	dtp1->Date=dtp1->Date .CurrentDate();
	dtp2->Date=dtp2->Date .CurrentDate();
}
//---------------------------------------------------------------------------
void TfrmRetailSummary::Init(TApplication* app, TADOConnection* con)
{        TfrmMDIChild::Init(app, con);
	 dsquery->Connection=con;
   //	 rzdbgrd4->Columns->Items[0]->Title->Caption="类别";
		TADOQuery * aq;
		aq = new TADOQuery(this);
		aq->Connection = con;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add("select * from sys_bsset where name ='retailxiaoshudian'");
		aq->Open();
		format =  "￥" + aq->FieldByName("bk")->AsAnsiString ;

		AnsiString sql;
		sql = "select ID,Name  from SYS_StorageInfo";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while (!aq->Eof)
		{
			cbstorage->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger);
        	aq->Next();
		}
		cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)stgid);
		sql = "select Master from SYS_StorageInfo where id = " + IntToStr(stgid);
        aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->FieldByName("Master")->AsBoolean ) {
			cbstorage->Enabled = true;
			chstorage->Enabled = true;
		}
		else
		{
			cbstorage->Enabled = false;
			chstorage->Enabled = false;
		}

		delete aq;
		DBGridEh1->Columns->Items[1]->DisplayFormat = format;
		DBGridEh1->Columns->Items[2]->DisplayFormat = format;
		DBGridEh1->Columns->Items[4]->DisplayFormat = format;
		DBGridEh1->Columns->Items[5]->DisplayFormat = format;
}
void __fastcall TfrmRetailSummary::RzToolButton1Click(TObject *Sender)
{
		String sql;
		if (dsquery->Active) {
			dsquery->Active=false;
		}
		//日
		if (rb5->Checked==true) {
			DBGridEh1->Columns->Items[0]->Title->Caption="日期";
			sql="select CONVERT(varchar(100), HdTime, 23) as Name,sum(BS_RetailNote.DiscountedPrice) as DiscountedPrice , sum(BS_RetailNote.FixedPrice) as FixedPrice,sum(BS_RetailNote.Amount) as TotalAmount,sum(BS_RetailNote.Amount*STK_BookInfo.Cbprice) as Cbprice,sum(BS_RetailNote.DiscountedPrice - BS_RetailNote.Amount*STK_BookInfo.Cbprice) as profite ";
			sql=sql+" FROM  BS_RetailNote left join BS_RetailNoteHeader on BS_RetailNote.RetailNtHeaderID = BS_RetailNoteHeader.id  left join STK_BookInfo on BS_RetailNote.BkInfoID = STK_BookInfo.id where 1 = 1 ";
			if (cbstart->Checked ) {
				sql = sql + " and datediff(d,HdTime,'"+dtp1->Date+"')<=0 ";
			}
			if (!cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,HdTime,'"+dtp2->Date+"')>=0 ";
			}
			if (cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,HdTime,'"+dtp2->Date+"')>=0 ";
			}
			if (chstorage->Checked ) {
				int fstgid;
				try {
					fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
				} catch (...) {
					MessageBox(0,"请选择正确的店号!","提示",MB_ICONEXCLAMATION);
					return;
				}
				sql = sql + " and BS_RetailNoteHeader.StgID = " + IntToStr(fstgid);
			}
			sql=sql+" group by  CONVERT(varchar(100), HdTime, 23)";
		}
	  //月
		if (rb4->Checked==true) {
			DBGridEh1->Columns->Items[0]->Title->Caption="日期";
			sql="select SubString(CONVERT(varchar(100), HdTime, 23),0,8) as Name,sum(BS_RetailNote.DiscountedPrice) as DiscountedPrice , sum(BS_RetailNote.FixedPrice) as FixedPrice,sum(BS_RetailNote.Amount) as TotalAmount,sum(BS_RetailNote.Amount*STK_BookInfo.Cbprice) as Cbprice,sum(BS_RetailNote.DiscountedPrice - BS_RetailNote.Amount*STK_BookInfo.Cbprice) as profite ";
			sql=sql+" FROM  BS_RetailNote left join BS_RetailNoteHeader on BS_RetailNote.RetailNtHeaderID = BS_RetailNoteHeader.id  left join STK_BookInfo on BS_RetailNote.BkInfoID = STK_BookInfo.id where 1 = 1 ";
			if (cbstart->Checked ) {
				sql = sql + " and datediff(d,HdTime,'"+dtp1->Date+"')<=0 ";
			}
			if (!cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,HdTime,'"+dtp2->Date+"')>=0 ";
			}
			if (cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,HdTime,'"+dtp2->Date+"')>=0 ";
			}

			if (chstorage->Checked ) {
				int fstgid;
				try {
					fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
				} catch (...) {
					MessageBox(0,"请选择正确的店号!","提示",MB_ICONEXCLAMATION);
					return;
				}
				sql = sql + " and BS_RetailNoteHeader.StgID = " + IntToStr(fstgid);
			}

			sql=sql+" group by  SubString(CONVERT(varchar(100), HdTime, 23),0,8)";
		}
	   //会员
		if (rb1->Checked==true) {
			DBGridEh1->Columns->Items[0]->Title->Caption="会员";
			sql="select CUST_MemberInfo.Name as Name,sum(BS_RetailNote.DiscountedPrice) as DiscountedPrice , sum(BS_RetailNote.FixedPrice) as FixedPrice,sum(BS_RetailNote.Amount) as TotalAmount,sum(BS_RetailNote.Amount*STK_BookInfo.Cbprice) as Cbprice,sum(BS_RetailNote.DiscountedPrice - BS_RetailNote.Amount*STK_BookInfo.Cbprice) as profite ";
			sql=sql+" FROM  BS_RetailNote left join BS_RetailNoteHeader on BS_RetailNote.RetailNtHeaderID = BS_RetailNoteHeader.id  left join STK_BookInfo on BS_RetailNote.BkInfoID = STK_BookInfo.id left join CUST_MemberInfo on BS_RetailNoteHeader.MemberID=CUST_MemberInfo.id where 1 = 1 ";
			if (cbstart->Checked ) {
				sql = sql + " and datediff(d,HdTime,'"+dtp1->Date+"')<=0 ";
			}
			if (!cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,HdTime,'"+dtp2->Date+"')>=0 ";
			}
			if (cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,HdTime,'"+dtp2->Date+"')>=0 ";
			}

			if (chstorage->Checked ) {
				int fstgid;
				try {
					fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
				} catch (...) {
					MessageBox(0,"请选择正确的店号!","提示",MB_ICONEXCLAMATION);
					return;
				}
				sql = sql + " and BS_RetailNoteHeader.StgID = " + IntToStr(fstgid);
			}

			sql=sql+" GROUP BY Name";
		}
		 //类别
		if (rb2->Checked==true) {
			DBGridEh1->Columns->Items[0]->Title->Caption="类别";
			sql="  SELECT  sum(dbo.BS_RetailNote.Amount) AS TotalAmount, SUM(dbo.BS_RetailNote.DiscountedPrice) AS DiscountedPrice, SUM(dbo.BS_RetailNote.FixedPrice) AS FixedPrice, dbo.BS_BookType.Name as Name,sum(BS_RetailNote.Amount*STK_BookInfo.Cbprice) as Cbprice,sum(BS_RetailNote.DiscountedPrice - BS_RetailNote.Amount*STK_BookInfo.Cbprice) as profite ";
			sql=sql+" 	FROM  dbo.BS_RetailNote LEFT JOIN dbo.BS_RetailNoteHeader ON dbo.BS_RetailNote.RetailNtHeaderID = dbo.BS_RetailNoteHeader.ID left JOIN dbo.STK_BookInfo ON dbo.STK_BookInfo.ID = dbo.BS_RetailNote.BkInfoID left JOIN dbo.BS_BookCatalog ON dbo.STK_BookInfo.BkcatalogID = dbo.BS_BookCatalog.ID left JOIN  dbo.BS_BookType ON dbo.BS_BookCatalog.smallBookTypeID = dbo.BS_BookType.ID where 1 = 1 ";
            if (cbstart->Checked ) {
				sql = sql + " and datediff(d,HdTime,'"+dtp1->Date+"')<=0 ";
			}
			if (!cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,HdTime,'"+dtp2->Date+"')>=0 ";
			}
			if (cbstart->Checked && cbend->Checked ) {
				sql = sql + " and datediff(d,HdTime,'"+dtp2->Date+"')>=0 ";
			}

			if (chstorage->Checked ) {
				int fstgid;
				try {
					fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
				} catch (...) {
					MessageBox(0,"请选择正确的店号!","提示",MB_ICONEXCLAMATION);
					return;
				}
				sql = sql + " and BS_RetailNoteHeader.StgID = " + IntToStr(fstgid);
			}

			sql=sql+" GROUP BY  BS_BookType.Name ";
		}
		dsquery->CommandText=sql;
		dsquery->Active=true;
		((TFloatField *)dsquery->FieldByName("FixedPrice"))->DisplayFormat = format;
		((TFloatField *)dsquery->FieldByName("DiscountedPrice"))->DisplayFormat = format;
	   //((TFloatField *)dsquery->FieldByName("cash"))->DisplayFormat = format;
		((TFloatField *)dsquery->FieldByName("Cbprice"))->DisplayFormat = format;
		((TFloatField *)dsquery->FieldByName("profite"))->DisplayFormat = format;
 }
//---------------------------------------------------------------------------

void __fastcall TfrmRetailSummary::FormClose(TObject *Sender, TCloseAction &Action)

{
	dsquery->Active=false;
    Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailSummary::RzToolButton3Click(TObject *Sender)
{
	 Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmRetailSummary::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		RzToolButton1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		RzToolButton3->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailSummary::rzdbgrd4TitleClick(TColumn *Column)
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

void __fastcall TfrmRetailSummary::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

