//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "saletime.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma link "RzRadChk"
#pragma link "RzGrids"
#pragma resource "*.dfm"
Tfrmsaletime *frmsaletime;
//---------------------------------------------------------------------------
__fastcall Tfrmsaletime::Tfrmsaletime(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
  aqday->Connection = cn;
  aqday1->Connection = cn;
  dtpstart->Date = Date();
  dtpend->Date = Date();
  strg->Cells[0][0]="零售总码洋";
  strg->Cells[1][0]="零售总实洋";
  strg->Cells[2][0]="零售总数量";
  strg->Cells[3][0]="零售总成本";
  strg->Cells[4][0]="零售总利润";

  strg->Cells[5][0]="批销总码洋";
  strg->Cells[6][0]="批销总实洋";
  strg->Cells[7][0]="批销总数量";
  strg->Cells[8][0]="批销总成本";
  strg->Cells[9][0]="批销总利润";
  TADOQuery * aq;
  String sql;
  aq = new TADOQuery(this);
  aq->Connection = cn;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add("select * from sys_bsset where name ='retailxiaoshudian'");
  aq->Open();
  retaiformat =  "￥###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
  aq->Open();
  saleformat =  "￥###,###,##" + aq->FieldByName("bk")->AsAnsiString ;

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
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsaletime::BtnViewClick(TObject *Sender)
{
   String  wherestr;

   if (cbstart->Checked && cbend->Checked ) {
	  wherestr = " where Hdtime  between '" + DateToStr(dtpstart->Date) + " 00:00:00' and '" + DateToStr(dtpend->Date) + " 23:59:59'" ;

   }else if (cbstart->Checked && !cbend->Checked) {
		wherestr = " where Hdtime  between '" + DateToStr(dtpstart->Date) + " 00:00:00' and '2100-10-01 23:59:59'" ;
   }else if (!cbstart->Checked && cbend->Checked  ) {
		wherestr = " where Hdtime  between '1990-10-01 00:00:00' and '" + DateToStr(dtpend->Date) + " 23:59:59'" ;
   }else if (!cbstart->Checked && !cbend->Checked ) {
	 wherestr = " where Hdtime  between '1960-10-01 00:00:00' and '2100-10-01 23:59:59'" ;
   }
   if (chstorage->Checked ) {
		int fstgid;
		try {
			fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
		} catch (...) {
			MessageBox(0,"请选择正确的店号!","提示",MB_ICONEXCLAMATION);
			return;
		}
		wherestr = wherestr + " and StgID = " + IntToStr(fstgid);
   }

 Query(wherestr);
}
void Tfrmsaletime::Query(AnsiString sqlstr)
{
   String sql1,sql;
   float Tfix = 0.0,Tdis = 0.0,Tcbprice = 0.0,Tprofite = 0.0;
   int Tamount = 0;
   sql1 = "select sum(FixedPrice) as fix,sum(DiscountedPrice) as dis,sum(A.Amount) as amount,sum(A.Amount*C.Cbprice) AS Cbprice,sum(DiscountedPrice - A.Amount*C.Cbprice) as profite " ;
   sql1 = sql1 + " from (select BS_RetailNote.BkInfoID,BS_RetailNote.Discount,BS_RetailNote.Amount,BS_RetailNote.FixedPrice,BS_RetailNote.DiscountedPrice from BS_RetailNote left join bs_retailnoteheader on  BS_RetailNote.RetailNtHeaderID = bs_retailnoteheader.id " + sqlstr + " ) A left join STK_BookInfo C on A.BkInfoID = C.ID  " ;
   sql = " select sum(FixedPrice) as fix2,sum(DiscountedPrice) as dis2,sum(B.Amount)as amount2,sum(B.Amount*C.Cbprice) AS Cbprice,sum(DiscountedPrice - B.Amount*C.Cbprice) as profite " ;
   sql = sql + " from (select BS_WsaleNote.BkInfoID,BS_WsaleNote.Discount,BS_WsaleNote.Amount,BS_WsaleNote.FixedPrice,BS_WsaleNote.DiscountedPrice from BS_WsaleNote left join BS_WsaleNoteHeader on  BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id  " + sqlstr + " ) B left join STK_BookInfo C on B.BkInfoID = C.ID ";
   aqday->Close();
   aqday->SQL->Clear();
   aqday->SQL->Add(sql);
   aqday->Open();
   aqday->First();
   aqday1->Close();
   aqday1->SQL->Clear();
   aqday1->SQL->Add(sql1);
   aqday1->Open();
   strg->Cells[0][1]= FormatFloat(retaiformat,aqday1->FieldByName("fix")->AsFloat );
   strg->Cells[1][1]= FormatFloat(retaiformat,aqday1->FieldByName("dis")->AsFloat );
   strg->Cells[2][1]= FormatFloat("#,##0",aqday1->FieldByName("amount")->AsFloat );
   strg->Cells[3][1]= FormatFloat(retaiformat,aqday1->FieldByName("Cbprice")->AsFloat );
   strg->Cells[4][1]= FormatFloat(retaiformat,aqday1->FieldByName("profite")->AsFloat );

   strg->Cells[5][1]= FormatFloat(saleformat,aqday->FieldByName("fix2")->AsFloat );
   strg->Cells[6][1]= FormatFloat(saleformat,aqday->FieldByName("dis2")->AsFloat );
   strg->Cells[7][1]= FormatFloat("#,##0",aqday->FieldByName("amount2")->AsFloat );
   strg->Cells[8][1]= FormatFloat(saleformat,aqday->FieldByName("Cbprice")->AsFloat );
   strg->Cells[9][1]= FormatFloat(saleformat,aqday->FieldByName("profite")->AsFloat );
   while(!aqday->Eof)
   {
	 Tfix += aqday1->FieldByName("fix")->AsFloat + aqday->FieldByName("fix2")->AsFloat;
	// Tfix += aqday->FieldByName("fix2")->AsFloat ;

	 Tdis += aqday1->FieldByName("dis")->AsFloat + aqday->FieldByName("dis2")->AsFloat;
	// Tdis += aqday->FieldByName("dis2")->AsFloat ;

	 Tamount += aqday1->FieldByName("amount")->AsFloat + aqday->FieldByName("amount2")->AsFloat  ;
	 Tcbprice += aqday1->FieldByName("Cbprice")->AsFloat + aqday->FieldByName("Cbprice")->AsFloat;
	 Tprofite += aqday1->FieldByName("profite")->AsFloat + aqday->FieldByName("profite")->AsFloat;
	 //Tamount += aqday->FieldByName("amount1")->AsFloat ;

     aqday->Next();
   }
    aqday->First();
	editfix->Text = FormatFloat(retaiformat.c_str() ,Tfix);
	editdis->Text = FormatFloat(retaiformat.c_str() ,Tdis);
	edprice->Text = FormatFloat(retaiformat.c_str() ,Tcbprice);
	edprofite->Text = FormatFloat(retaiformat.c_str() ,Tprofite);
	editamount->Text = IntToStr(Tamount) ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsaletime::BtnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaletime::BtnExportClick(TObject *Sender)
{
	if (aqday->Active && aqday->RecordCount > 0) {
		DbgridToExcel(strg);
	}
}
//---------------------------------------------------------------------------

//Excel导出函数
bool __fastcall Tfrmsaletime::DbgridToExcel(TRzStringGrid* dbg)
{
	AnsiString temptext ;
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	v.OlePropertyGet("Cells",1,3).OlePropertySet("Value","销售时段汇总统计" );
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","开始时间" );
	temptext = "'"+ DateToStr(dtpstart->Date);
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","结束时间" );
	temptext = "'"+ DateToStr(dtpend->Date);
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());


	int t1= 0;
	for(int q=0;q<dbg->ColCount ;++q)
	{
			t1++;
			temptext = "'"+ dbg->Cells[q][0];
			v.OlePropertyGet("Cells",4,(t1)).OlePropertySet("Value",temptext .c_str() );
	}
	t1= 0;
	for(int q=0;q<dbg->ColCount ;++q)
	{
			t1++;
			temptext = "'"+ dbg->Cells[q][1];
			v.OlePropertyGet("Cells",5,(t1)).OlePropertySet("Value",temptext .c_str() );
	}

	v.OlePropertyGet("Cells",7,1).OlePropertySet("Value","合计" );
	v.OlePropertyGet("Cells",7,2).OlePropertySet("Value","总码洋" );
	temptext = "'"+ editfix->Text;
	v.OlePropertyGet("Cells",7,3).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",7,4).OlePropertySet("Value","总实洋" );
	temptext = "'"+ editdis->Text;
	v.OlePropertyGet("Cells",7,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",7,6).OlePropertySet("Value","总数量" );
	temptext = "'"+ editamount->Text;
	v.OlePropertyGet("Cells",7,7).OlePropertySet("Value",temptext .c_str());

	return false;
}
//---------------------------------------------------------------------------



void __fastcall Tfrmsaletime::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaletime::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	     	if (Key == VK_F1) {
		 BtnView->Click();
	   }
		if (Key == VK_F10) {
		 BtnPrint->Click();
	   }

		if (Shift.Contains(ssCtrl)&& Key ==90) {
			WindowState = wsNormal  ;
		}
		if (Shift.Contains(ssCtrl)&& Key ==81  ) {
			BtnExit->Click();
		}
		if (Shift.Contains(ssCtrl)&& Key == 78 ) {
		  BtnAlignBottom->Click();
		}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaletime::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized   ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaletime::dtpstartChange(TObject *Sender)
{
	cbstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaletime::dtpendChange(TObject *Sender)
{
	cbend->Checked = true;
}
//---------------------------------------------------------------------------

