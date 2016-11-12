//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitznfahuoorderselect.h"
#include "UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
Tfrmzinengfahuo *frmzinengfahuo;
//---------------------------------------------------------------------------
__fastcall Tfrmzinengfahuo::Tfrmzinengfahuo(TComponent* Owner,TADOConnection *cn,int stgid,int userid)
	: TForm(Owner)
{
	ClientID = -1;
   fstgid= stgid;
   fuserid=userid;
   fcon=cn;
   dbgrid->OnDrawColumnCell= RzDBGrid1DrawColumnCell;
   DBGrid1->OnDrawColumnCell =DBGrid1DrawColumnCell;
   aq->Connection=fcon;
   adoquery->Connection=fcon;
   sp->Connection =fcon;
   //dbgrid
}
//---------------------------------------------------------------------------
void __fastcall Tfrmzinengfahuo::spselectClientClick(TObject *Sender)
{
TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",fstgid);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		edtclient->SetFocus();
	   //	ClientView();
	}
	delete frm;
}
void Tfrmzinengfahuo::ClientView()
{   	if (ClientID == -1) {
		return;
	}
	String sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	sql = "exec USP_BS_Client_View 0," + IntToStr(ClientID)  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edtclient->Text = aq->FieldByName("Name")->AsAnsiString ;

	 /*
	sql = "select distinct BS_OrderNote.xiaoqu from BS_OrderNote left join BS_OrderNoteHeader "
			" on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id where BS_OrderNoteHeader.VendorID = " + IntToStr(ClientID) + " and xiaoqu is not null and xiaoqu <> '' " ;
	if (chordercode->Checked && edordercode->Text != "") {
		sql = sql + " and BS_OrderNoteHeader.OrderNtCode = " + edordercode->Text ;
	}
	else
	{
		sql = sql +  " union "
			" select distinct name from CUST_CustomerInfo where PrentID = " + IntToStr(ClientID) + " and id <> " + IntToStr(ClientID);
	}

	cbxiaoqu->Clear();
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbxiaoqu->AddItem(aq->FieldByName("xiaoqu")->AsAnsiString ,(TObject*)1);
		aq->Next();
	}
	sql = "select distinct BS_OrderNote.xueyuan from BS_OrderNote left join BS_OrderNoteHeader "
			" on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id where BS_OrderNoteHeader.VendorID = " + IntToStr(ClientID) + " and xueyuan is not null and xueyuan <> '' " ;
	if (chordercode->Checked && edordercode->Text != "") {
		sql = sql + " and BS_OrderNoteHeader.OrderNtCode = " + edordercode->Text ;
	}
	else
	{
		sql = sql +  " union "
			" select distinct name from CUST_CustomerInfo where PrentID = " + IntToStr(ClientID) + " and id <> " + IntToStr(ClientID);
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbxueyuan->Clear();
	while (!aq->Eof)
	{
		cbxueyuan->AddItem(aq->FieldByName("xueyuan")->AsAnsiString ,(TObject*)1);
		aq->Next();
	}  */

	delete aq;

}
//---------------------------------------------------------------------------
void __fastcall Tfrmzinengfahuo::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
if (Key == '\r') {
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edclient->Text,fstgid);
		if (mrOk == frm->ShowModal())
		{
			ClientID = frm->GetSelectID();
			ClientView();
			edtclient->SetFocus();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmzinengfahuo::RzButton1Click(TObject *Sender)
{
  //查询

  AnsiString whereas;
  whereas=" and 1=1 ";
  if (chordercode->Checked) {
		  whereas=whereas+" and OrderNtCode like '%"+Trim(edordercode->Text)+"%'";
  }
   if (chclient->Checked) {
	  whereas=whereas+" and OrderUser like '%"+Trim(edtclient->Text)+"%'";
  }
   if (chstart->Checked) {
			whereas = whereas + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',C_BS_OrderNoteHeader.HdTime) >= 0 " ;
  }
   if (chend->Checked) {
		whereas = whereas + " and datediff(day,'" + DateToStr(dtpend->Date) + "',C_BS_OrderNoteHeader.HdTime) <= 0 " ;
  }

  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add("exec C_OrderKCmazuo :w,:s ");
  aq->Parameters->ParamByName("w")->Value=whereas;
  aq->Parameters->ParamByName("s")->Value=rg->ItemIndex;
  aq->Open();

}
//---------------------------------------------------------------------------
void __fastcall Tfrmzinengfahuo::RzDBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
		 if (aq->FieldByName("mazu")->AsInteger==2) { //部分满足

				dbgrid->Canvas->FillRect(Rect);
				dbgrid->Canvas->Font->Color  = clBlue;
				dbgrid->DefaultDrawColumnCell(Rect,DataCol,Column,State);

		 }
		 if (aq->FieldByName("mazu")->AsInteger==3) { //部分满足

				dbgrid->Canvas->FillRect(Rect);
				dbgrid->Canvas->Font->Color  = clRed;
				dbgrid->DefaultDrawColumnCell(Rect,DataCol,Column,State);

		 }



}
//---------------------------------------------------------------------------

void __fastcall Tfrmzinengfahuo::dbgridCellClick(TColumn *Column)
{
  //获取明细
   AnsiString sql;
   sql = "select *, case when kykc+locknum>=unsendamount then 1 else 2 end mazu from dbo.C_Order_Detail where orderNtHeaderID =:headid ";
   adoquery->Close();
   adoquery->SQL->Clear();
   adoquery->SQL->Add(sql);
   adoquery->Parameters->ParamByName("headid")->Value=  aq->FieldByName("ID")->AsInteger;
   adoquery->Open();



}
//---------------------------------------------------------------------------

void __fastcall Tfrmzinengfahuo::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	   if (adoquery->FieldByName("mazu")->AsInteger==2) { //不满足
			DBGrid1->Canvas->FillRect(Rect);
				DBGrid1->Canvas->Font->Color  = clRed;
				DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);

	   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmzinengfahuo::N1Click(TObject *Sender)
{
	if (aq->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= aq->RecordCount; i++) {
		dbgrid->DataSource->DataSet->RecNo = i;
		dbgrid->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmzinengfahuo::H1Click(TObject *Sender)
{
  AnsiString ids,ReturnCode,msg;
  
  int fengding,WsaleNoteHeaderid;
  fengding = 0;
	   ids="-1";

	if (dbgrid->SelectedRows ->Count == 0) {
		MessageBox(Handle,"请选择需要发货的订单！","提示",MB_OK|MB_ICONINFORMATION);
		Screen->Cursor = crDefault ;
		return;
	}

	for (int i =0; i < dbgrid->SelectedRows->Count ; i++) {
			aq->GotoBookmark(dbgrid->SelectedRows->Items[i]);
			ids = ids + "," + aq->FieldByName("id")->AsAnsiString ;
			if (aq->FieldByName("mazu")->AsInteger!=1) {
                fengding=1;
			}
		}

   if (fengding==1) {
			if(MessageBox(0,"有未满足发货数量的订单，是否要继续发货？！" ,"确认" ,MB_ICONQUESTION|MB_OKCANCEL)==1)
			{
                //开始生成发货单
				fhuo(ids);
			}

   }else
   {
	 fhuo(ids);
   }
}
void Tfrmzinengfahuo::fhuo(AnsiString ids)
{
AnsiString ReturnCode,msg;
int WsaleNoteHeaderid;
		sp->ProcedureName="C_USP_BS_ZNfahuo_Add_Note";
		sp->Parameters->Refresh();
		sp->Parameters->ParamByName("@OperatorID")->Value=fuserid;
		sp->Parameters->ParamByName("@StgID")->Value=fstgid;
		sp->Parameters->ParamByName("@CODEMODE")->Value=0;
		sp->Parameters->ParamByName("@OrderIDstr")->Value=ids;
		sp->Parameters->ParamByName("@ReturnCode")->Value="";
		sp->Parameters->ParamByName("@Returnint")->Value=-1;

		sp->ExecProc();
		ReturnCode= sp->Parameters->ParamByName("@ReturnCode")->Value;
		WsaleNoteHeaderid = sp->Parameters->ParamByName("@Returnint")->Value;
		msg= "成功生成发货单！"+ReturnCode;
		MessageBox(Handle,msg.c_str(),"提示",MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

