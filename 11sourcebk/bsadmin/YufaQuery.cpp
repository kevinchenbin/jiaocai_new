//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "YufaQuery.h"
#include "UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmYufaQuery *frmYufaQuery;
//---------------------------------------------------------------------------
__fastcall TfrmYufaQuery::TfrmYufaQuery(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
	fcon = con;
	fstgid = stgid;
	query->Connection = fcon;
	dtpstart->Date = Date();
    dtpend->Date = Date();
}
//---------------------------------------------------------------------------
void __fastcall TfrmYufaQuery::RzButton1Click(TObject *Sender)
{
	AnsiString sqlwhere,sql;
	if (chstart->Checked ) {
		sqlwhere = sqlwhere + "  and datediff(day,'" + DateToStr(dtpstart->Date) + "',headtime) >= 0";
	}
	if (chend->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',headtime) <= 0";
	}
	if (chclient->Checked && edtclient->Text != "") {
		sqlwhere = sqlwhere + " and FahuoClient in (select id from dbo.GetChild("  + IntToStr(ClientID) + ")) ";
	}
	sql = "select distinct BS_Tmpheader.groupid,yufacode,headtime, dbo.UF_BS_GetClientName(BS_Tmporder.FahuoClient) as ClientName from BS_Tmpheader "
			" left join BS_Tmporder on BS_Tmpheader.groupid = BS_Tmporder.groupid "
			" where BS_Tmporder.modle= 0 and BS_Tmpheader.stgid = " + IntToStr(fstgid)  + sqlwhere;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------
void __fastcall TfrmYufaQuery::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",fstgid);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		ClientView();
	}
	delete frm;
}
//---------------------------------------------------------------------------
void TfrmYufaQuery::ClientView()
{
	if (ClientID == -1) {
		return;
	}
	String sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	sql = "exec USP_BS_Client_View 0," + IntToStr(ClientID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edtclient->Text = aq->FieldByName("Name")->AsAnsiString;
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TfrmYufaQuery::DBGrid1DblClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
    ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmYufaQuery::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		if (edclient->Text == "") {
            return;
		}
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edclient->Text,fstgid);
		if (mrOk == frm->ShowModal())
		{
			ClientID = frm->GetSelectID();
			ClientView();
	   }
	   delete frm;
	}
}
//---------------------------------------------------------------------------

