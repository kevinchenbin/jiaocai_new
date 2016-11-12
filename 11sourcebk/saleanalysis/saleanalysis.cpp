//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "saleanalysis.h"
#include "UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzRadChk"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma resource "*.dfm"
Tfrmsaleanalysis *frmsaleanalysis;
//---------------------------------------------------------------------------
__fastcall Tfrmsaleanalysis::Tfrmsaleanalysis(TComponent* Owner,TADOConnection * cn,int stgid)
	: TForm(Owner)
{
   con = cn;
   Title = "����ͳ��";
   aqheader ->Connection = con;
   aqdetal->Connection = con;
   dtpstart->Date = Date();
   dtpend->Date = Date();
   fstgid = stgid;
   fcon = con;
   ClientID = -1;
}
void Tfrmsaleanalysis::ReadyData()
{
	TADOQuery * aq;
	String sql;
	sql = "select ID,Name from SYS_StorageInfo";
	aq = new TADOQuery(this);
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
	   cbstore->Items->AddObject(aq->FieldByName("name")->AsAnsiString,(TObject*)aq->FieldByName("ID")->AsInteger);
	   aq->Next();
	}

	cbstore->ItemIndex = cbstore->Items->IndexOfObject((TObject*)fstgid);
		sql = "select Master from SYS_StorageInfo where id = " + IntToStr(fstgid);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->FieldByName("Master")->AsBoolean ) {
			cbstore->Enabled = true;
		}
		else
		{
			cbstore->Enabled = false;
		}

	 aq->Close();
	 aq->SQL->Clear();
	 aq->SQL->Add("select * from sys_bsset where name ='retailxiaoshudian'");
	 aq->Open();
	 retailformat =  "��" + aq->FieldByName("bk")->AsAnsiString ;
	 aq->Close();
	 aq->SQL->Clear();
	 aq->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
	 aq->Open();
	 saleformat =  "��" + aq->FieldByName("bk")->AsAnsiString ;
	 delete aq;
 }
  String Tfrmsaleanalysis::GetDesic()
  {
	 TADOQuery *aq;
	 aq = new TADOQuery(this);
	 aq->Connection = con ;
	 aq->Close();
	 aq->SQL->Clear();
	 aq->SQL->Add("select * from sys_bsset where name ='xiaoshudian'");
	 aq->Open();
	 return "��" + aq->FieldByName("bk")->AsAnsiString ;
	 delete aq;

  }
//---------------------------------------------------------------------------
void __fastcall Tfrmsaleanalysis::cbanalysistypeChange(TObject *Sender)
{
	/*
		����������ϸ��
		�����������ܱ�
		����ҵ��Ա���ܱ�
		��������λͳ��
		���������˻���ϸ��
		���۲���Ա���ܱ�
		���۰������ܱ�
		����ʱ�λ��ܱ���
		��Ա����ͳ�Ʊ���
	*/
   // SearchModal = cbanalysistype->ItemIndex ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsaleanalysis::BtnViewClick(TObject *Sender)
{
   if (cbstore->Text =="") {


	  MessageBox(0,"��ѡ����!",Title.c_str(),MB_ICONEXCLAMATION);
	  return;

   }
   if (cbanalysistype->Text == "") {

	 MessageBox(0,"��ѡ���ѯ����!",Title.c_str(),MB_ICONEXCLAMATION);
	 return;
   }
   if (Panel1->Visible) {
	   Panel1->Visible = false;
	   //Height = 635;
   }
   //SearchModal = cbanalysistype->ItemIndex ;
   //Query();
}
void Tfrmsaleanalysis::Query()
{
	  String StartDate,EndDate;
	  String sqlstr, strwhere,sqlclient;
	  totalshiyang = 0.0;
	  totalmayang  =0.0;
	  totalnum = 0;

	 strwhere = " where A.stgid = " + IntToStr((int)(cbstore->Items->Objects[cbstore->ItemIndex]));

	  if (cbstart->Checked ) {

		 StartDate = DateToStr(dtpstart->Date ) + " 00:00:00";

	  }else StartDate = "1911-01-01";

	  if (cbend->Checked ) {

		 EndDate = DateToStr(dtpend->Date) + " 23:59:59";
	  } else
	  {
		 EndDate = "2080-01-01";
	  }

	strwhere = strwhere + " and (Hdtime between '"+ StartDate + "' and '";
	strwhere = strwhere +  EndDate + "')";
	if (chclient->Checked && edtclient->Text != "") {
		sqlclient =  " and A.VendorID in (select ID from GetChild("+ IntToStr(ClientID) +")) ";
	}

	  AnsiString strattime = "2009-01-01",endtime = "2100-12-31";
	  if (cbstart->Checked ) {
		strattime = DateToStr(dtpstart->Date);
	 }
	 if (cbend->Checked ) {
		endtime = DateToStr(dtpend->Date);
	 }
	 TADOQuery *aq = new TADOQuery(this);
	 aq->Connection = fcon;
	 AnsiString sql;
	  switch (SearchModal) {
		  case 0:            //����������ϸ��
			  sqlstr = "select A.ID,wsaleNtCode as '����', dbo.UF_BS_GetClientName(A.VenDorID) as '�ͻ�����',totalamount as '����',fixedprice as '����',discountedprice as 'ʵ��',C.Name as 'ҵ��Ա',convert(varchar(10),A.Hdtime,111) as '����' from BS_WsaleNoteHeader A "
					   " left join CUST_CustomerInfo B on  A.VenDorID = B.ID "
					   " left join SYS_StaffInfo C on A.staffid = C.ID";
			  sqlstr = sqlstr + strwhere + sqlclient;
			  sqlstr = sqlstr + " and A.WsaleNtCode <> 0 ";
			  GetDataForDg(sqlstr,aqheader,dgheadnote );  //����dbgrid����
			  GetTotal(aqheader);     //����ϼ�
				Panel1->Visible = true;
				edtmanyang->Text = FormatFloat(saleformat,totalmayang);
				 edtshiyang ->Text = FormatFloat(saleformat,totalshiyang);
				 Panel1->Visible = true;
				 aqdetal->Active = false;
				 if (chclient->Checked && edtclient->Text != "") {
					edordermun->Visible = true;
					edordermayang->Visible = true;
					edordershiyang->Visible = true;
					Label5->Visible = true;
					Label9->Visible = true;
					Label10->Visible = true;
					sql = "select dbo.UF_BS_Getorderamount(" + IntToStr(ClientID) + ",'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as ordernum ";
					aq->Close();
					aq->SQL->Clear();
					aq->SQL->Add(sql);
					aq->Open();
					edordermun->Text = aq->FieldByName("ordernum")->AsAnsiString ;
					sql = "select dbo.UF_BS_Getorderfixedprice(" + IntToStr(ClientID) + ",'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as ordermayang ";
					aq->Close();
					aq->SQL->Clear();
					aq->SQL->Add(sql);
					aq->Open();
					ordermayang = aq->FieldByName("ordermayang")->AsFloat ;
                    edordermayang->Text = FormatFloat(saleformat,ordermayang);

					sql = "select dbo.UF_BS_GetorderDiscountedPrice(" + IntToStr(ClientID) + ",'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as ordershiyang ";
					aq->Close();
					aq->SQL->Clear();
					aq->SQL->Add(sql);
					aq->Open();
					ordershiyang = aq->FieldByName("ordershiyang")->AsFloat ;
					edordershiyang ->Text = FormatFloat(saleformat,ordershiyang);
				}
				else
				{
					edordermun->Visible = false;
					edordermayang->Visible = false;
					edordershiyang->Visible = false;
					Label5->Visible = false;
					Label9->Visible = false;
					Label10->Visible = false;
				}
				//Height = 570;
		  break;
		  case 1:     //  �����������ܱ�
				sqlstr = "select A.ID,wsaleNtCode as '����', dbo.UF_BS_GetClientName(A.VenDorID) as '�ͻ�����',totalamount as '����',fixedprice as '����',discountedprice as 'ʵ��',C.Name as 'ҵ��Ա',convert(varchar(10),A.Hdtime,111) as '����' from BS_WsaleNoteHeader A "
				   " left join CUST_CustomerInfo B on  A.VenDorID = B.ID "
				   " left join SYS_StaffInfo C on A.staffid = C.ID";
				sqlstr = sqlstr + strwhere + sqlclient;
				sqlstr = sqlstr + " and A.WsaleNtCode <> 0 ";
			GetDataForDg(sqlstr,aqheader,dgheadnote );  //����dbgrid����
			GetTotal(aqheader);     //����ϼ�
			edtmanyang->Text = FormatFloat(saleformat,totalmayang);
			edtshiyang ->Text = FormatFloat(saleformat,totalshiyang);
			Panel1->Visible = false;
			edordermun->Visible = false;
			edordermayang->Visible = false;
			edordershiyang->Visible = false;
			Label5->Visible = false;
			Label9->Visible = false;
			Label10->Visible = false;
		  break;
		  case 2: //  ��������λͳ��
			 /*sqlstr = "select B.name as N,dbo.UF_BS_GetClientName(A.VenDorID) as '�ͻ�����',B.Address as '��ַ',B.Contact as '��ϵ��',B.local as '����',sum(totalamount) as '������',sum(fixedprice) as '������',sum(discountedprice) as '��ʵ��'"
					  " from BS_WsaleNoteHeader A "
					  " left join CUST_CustomerInfo B on  A.VenDorID = B.ID "
					  " left join SYS_StaffInfo C on A.staffid = C.ID " ;

			 sqlstr = sqlstr + strwhere+ sqlclient + " group by B.Name,B.Contact,B.local,B.Address,A.VenDorID ";*/


			 sqlstr = "select BS_WsaleNoteHeader.VendorID as N,dbo.UF_BS_GetClientName(BS_WsaleNoteHeader.VendorID) as '�ͻ�����',"
						" dbo.UF_BS_Getorderamount(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '��������',"
						" dbo.UF_BS_Getorderfixedprice(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '��������',"
						" dbo.UF_BS_GetorderDiscountedPrice(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '����ʵ��',"
						" dbo.UF_BS_Getwsaleamount(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '��������',"
						" dbo.UF_BS_GetwsaleFixedPrice(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '��������',"
						" dbo.UF_BS_GetwsaleDiscountedPrice(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '����ʵ��',"
						" dbo.UF_BS_GetTwsaleamount(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '�˻�����',"
						" dbo.UF_BS_GetTwsaleFixedPrice(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '�˻�����',"
						" dbo.UF_BS_GetTwsaleDiscountedPrice(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '�˻�ʵ��'"
						" from  BS_WsaleNoteHeader where datediff(day,BS_WsaleNoteHeader.HdTime,'" + strattime + "') <= 0 and datediff(day,BS_WsaleNoteHeader.HdTime,'" + endtime + "') >= 0 and BS_WsaleNoteHeader.StgID = " + IntToStr(fstgid) ;
						if (chclient->Checked && edtclient->Text != "") {
							sqlstr = sqlstr+ " and BS_WsaleNoteHeader.VendorID in (select id from dbo.GetChild(" + IntToStr(ClientID) + ")) ";
						}
						sqlstr = sqlstr + " group by BS_WsaleNoteHeader.VendorID";

			GetDataForDg(sqlstr,aqheader,dgheadnote );
			GetTotal(aqheader);
			edtmanyang->Text = FormatFloat(saleformat,totalmayang);
			edtshiyang ->Text = FormatFloat(saleformat,totalshiyang);
			edordermun->Text = IntToStr(ordernum);
			edordermayang->Text = FormatFloat(saleformat,ordermayang);
			edordershiyang ->Text = FormatFloat(saleformat,ordershiyang);
			Panel1->Visible = false;
			edordermun->Visible = true;
			edordermayang->Visible = true;
			edordershiyang->Visible = true;
			Label5->Visible = true;
			Label9->Visible = true;
			Label10->Visible = true;
		  break;
		  case 3: //	����ҵ��Ա���ܱ�
			 sqlstr = "select C.ID , C.Name as 'ҵ��Ա',sum(totalamount) as '������', sum(fixedprice) as '������',sum(discountedprice) as '��ʵ��'"
					  " FROM BS_WSALENOTEHEADER A "
					  " LEFT JOIN SYS_STAFFINFO C ON A.STAFFID = C.ID ";

			 sqlstr = sqlstr + strwhere + sqlclient + " Group by C.ID,C.Name";
			GetDataForDg(sqlstr,aqheader,dgheadnote );  //����dbgrid����
			GetTotal(aqheader);
			edtmanyang->Text = FormatFloat(saleformat,totalmayang);
			edtshiyang ->Text = FormatFloat(saleformat,totalshiyang);
			Panel1->Visible = false;
			edordermun->Visible = false;
			edordermayang->Visible = false;
			edordershiyang->Visible = false;
			Label5->Visible = false;
			Label9->Visible = false;
			Label10->Visible = false;
		  break;
		 case 4:  //���������˻���ϸ��
			sqlstr = "select A.ID,wsaleNtCode as '����',dbo.UF_BS_GetClientName(A.VenDorID) as '�ͻ�����',totalamount as '����',fixedprice as '����',discountedprice as 'ʵ��',C.Name as 'ҵ��Ա',convert(varchar(10),A.Hdtime,111) as '����' from BS_WsaleNoteHeader A "
				   " left join CUST_CustomerInfo B on  A.VenDorID = B.ID "
				   " left join SYS_StaffInfo C on A.staffid = C.ID";
			sqlstr = sqlstr + strwhere + sqlclient + " and totalamount < 0";
			GetDataForDg(sqlstr,aqheader,dgheadnote );  //����dbgrid����
			GetTotal(aqheader);     //����ϼ�
			Panel1->Visible = true;
			edtmanyang->Text = FormatFloat(saleformat,totalmayang);
			edtshiyang ->Text = FormatFloat(saleformat,totalshiyang);
			Panel1->Visible = true;
			aqdetal->Active = false;
			edordermun->Visible = false;
			edordermayang->Visible = false;
			edordershiyang->Visible = false;
			Label5->Visible = false;
			Label9->Visible = false;
			Label10->Visible = false;
			//Height = 570;

		 break;
		 case 5: //���۲���Ա���ܱ�
			  sqlstr = "select E.ID,E.����Ա,G.������,E.��������,E.����ʵ��,F.�˻�����,F.�˻�ʵ��,G.�ֽ��տ� FROM "
					   "(select B.ID,sum(TotalAmount) as '������',sum((case when TotalDiscountedPrice >(RecCash+RecCardMoney) then (RecCash+RecCardMoney) else TotalDiscountedPrice end)) as '�ֽ��տ�' from BS_RetailNoteHeader as A  left join SYS_User B on A.operatorID = B.ID ";
			  sqlstr = sqlstr + strwhere;
			  sqlstr = sqlstr + " group by operatorID,B.name,B.ID ) AS G FULL JOIN ";
			  sqlstr = sqlstr + " (select B.ID,B.Name as '����Ա', sum(TotalFixedprice) as '��������',sum(TotalDiscountedprice) as '����ʵ��' from BS_RetailNoteHeader as A  left join SYS_User B on A.operatorID = B.ID ";
			  sqlstr = sqlstr + strwhere;
			  sqlstr = sqlstr + " and TotalAmount >= 0 group by operatorID,B.name,B.ID ) AS E ON G.ID = E.ID FULL JOIN ";
			  sqlstr = sqlstr + " (select B.ID, sum(TotalFixedprice) as '�˻�����',sum(TotalDiscountedprice) as '�˻�ʵ��' from BS_RetailNoteHeader as A  left join SYS_User B on A.operatorID = B.ID ";
			  sqlstr = sqlstr + strwhere;
			  sqlstr = sqlstr + " and TotalAmount < 0 group by operatorID,B.name,B.ID ) AS F ON F.ID = G.ID ";
			GetDataForDg(sqlstr,aqheader,dgheadnote);  //����dbgrid����
			GetTotal(aqheader);     //����ϼ�
			edtmanyang->Text = FormatFloat(retailformat,totalmayang);
			edtshiyang ->Text = FormatFloat(retailformat,totalshiyang);
			Panel1->Visible = false;
			edordermun->Visible = false;
			edordermayang->Visible = false;
			edordershiyang->Visible = false;
			Label5->Visible = false;
			Label9->Visible = false;
			Label10->Visible = false;
		 break;
		 case 6://���۰������ܱ�

			 sqlstr = "select A.RetailNtcode,A.RetailNtCode as '���۵���',A.TotalAmount as '������',A.TotalFixedprice as '������',A.TotalDiscountedprice as '��ʵ��', "
					  " A.RecCash as '�ֽ�����',A.RecCardMoney as '��Ա������',B.Name as '����Ա',convert(varchar(10),A.Hdtime,111) as '����' from BS_RetailNoteHeader A "
					  " left join SYS_User B on A.operatorID = B.ID ";
			 sqlstr = sqlstr +  strwhere;
			GetDataForDg(sqlstr,aqheader,dgheadnote );  //����dbgrid����
			GetTotal(aqheader);     //����ϼ�
			edtmanyang->Text = FormatFloat(retailformat,totalmayang);
			edtshiyang ->Text = FormatFloat(retailformat,totalshiyang);
			Panel1->Visible = false;
			edordermun->Visible = false;
			edordermayang->Visible = false;
			edordershiyang->Visible = false;
			Label5->Visible = false;
			Label9->Visible = false;
			Label10->Visible = false;
		 break;
		case 7: //���۰�����ϸ��
				sqlstr = "select A.ID ,A.RetailNtCode as '���۵���',A.TotalAmount as '����',A.TotalFixedprice as '����',A.TotalDiscountedprice as 'ʵ��', "
				" A.RecCash as '�ֽ�����',A.RecCardMoney as '��Ա������',B.Name as '����Ա',convert(varchar(10),A.Hdtime,111) as '����' from BS_RetailNoteHeader A "
				" left join SYS_User B on A.operatorID = B.ID ";
				sqlstr = sqlstr +  strwhere;
				GetDataForDg(sqlstr,aqheader,dgheadnote );  //����dbgrid����
				GetTotal(aqheader);     //����ϼ�
				Panel1->Visible = true;
				edtmanyang->Text = FormatFloat(retailformat,totalmayang);
				edtshiyang ->Text = FormatFloat(retailformat,totalshiyang);
				Panel1->Visible = true;
				aqdetal->Active = false;
				edordermun->Visible = false;
			edordermayang->Visible = false;
			edordershiyang->Visible = false;
			Label5->Visible = false;
			Label9->Visible = false;
			Label10->Visible = false;
		     	//Height = 570;
		 break;
		case 8:// ����ʱ�λ��ܱ���

		 break;
		case 9://��Ա����ͳ�Ʊ���

			 sqlstr = "select C.Name ,C.Name as '��Ա����',sum(A.TotalAmount) as '������',sum(A.TotalFixedprice) as '������',sum(A.TotalDiscountedprice) as '��ʵ��',"
				   " sum(A.RecCash) as '�ֽ�����',sum(A.RecCardMoney) as '��Ա������'"
				   " from BS_RetailNoteHeader A "
				   " left join SYS_User B on A.operatorID = B.ID "
				   " left join Cust_memberinfo C on A.MemberID = C.ID ";
			 sqlstr = sqlstr +  strwhere + " group by C.Name";
			GetDataForDg(sqlstr,aqheader,dgheadnote );  //����dbgrid����
			GetTotal(aqheader);     //����ϼ�
			edtmanyang->Text = FormatFloat(retailformat,totalmayang);
			edtshiyang ->Text = FormatFloat(retailformat,totalshiyang);
			Panel1->Visible = false;
			edordermun->Visible = false;
			edordermayang->Visible = false;
			edordershiyang->Visible = false;
			Label5->Visible = false;
			Label9->Visible = false;
			Label10->Visible = false;
		break;
	  default:
		  ;
	  }
	 delete aq;
	 edtnum->Text = IntToStr(totalnum);

}
void Tfrmsaleanalysis::GetDataForDg(AnsiString SQLstr, TADOQuery *aq,TRzDBGrid * dg)
{
	 aq->Close();
	 aq->SQL->Clear();
	 aq->SQL->Add(SQLstr);
	 aq->Open();
	 TColumn *Col;

	 dg->Columns->Clear();

	 switch (SearchModal) {
		  case 2:
			((TFloatField *)aq->FieldByName("��������"))->DisplayFormat = saleformat;//"0.00";
			((TFloatField *)aq->FieldByName("����ʵ��"))->DisplayFormat = saleformat;//"0.00";
			((TFloatField *)aq->FieldByName("��������"))->DisplayFormat = saleformat;//"0.00";
			((TFloatField *)aq->FieldByName("����ʵ��"))->DisplayFormat = saleformat;//"0.00";
			break;
		  case 3:
			((TFloatField *)aq->FieldByName("������"))->DisplayFormat = saleformat;//"0.00";
			((TFloatField *)aq->FieldByName("��ʵ��"))->DisplayFormat = saleformat;//"0.00";
			break;
		  case 6:
		  case 9:
			((TFloatField *)aq->FieldByName("������"))->DisplayFormat = retailformat;//"0.00";
			((TFloatField *)aq->FieldByName("��ʵ��"))->DisplayFormat = retailformat;//"0.00";
			break;
		  case 5:
			((TFloatField *)aq->FieldByName("��������"))->DisplayFormat = retailformat;//"0.00";
			((TFloatField *)aq->FieldByName("����ʵ��"))->DisplayFormat = retailformat;
			((TFloatField *)aq->FieldByName("�˻�����"))->DisplayFormat = retailformat;//"0.00";
			((TFloatField *)aq->FieldByName("�˻�ʵ��"))->DisplayFormat = retailformat;
			((TFloatField *)aq->FieldByName("�ֽ��տ�"))->DisplayFormat = retailformat;
			break;
		  case -7:
			((TFloatField *)aq->FieldByName("������"))->DisplayFormat = retailformat;//"0.00";
			((TFloatField *)aq->FieldByName("��ʵ��"))->DisplayFormat = retailformat;//"0.00";
			break;
	 default:
			((TFloatField *)aq->FieldByName("����"))->DisplayFormat = saleformat;//"0.00";
			((TFloatField *)aq->FieldByName("ʵ��"))->DisplayFormat = saleformat;//"0.00";
		 ;
	 }
	 aq->DisableControls();
	 for (int i = 1; i < aq->Fields->Count ; i++) { //ȥ��ID

		Col =  dg->Columns->Add();
		Col->FieldName  = aq->Fields->Fields[i]->FieldName  ;
		Col->Width = 80;
		aq->Next();
	 }
	 aq->EnableControls();
}
 void Tfrmsaleanalysis::GetTotal(TADOQuery *aq)
 {
   totalmayang = 0.0;
   totalshiyang = 0.0;
   ordermayang = 0.0;
   ordershiyang = 0.0;
   ordernum = 0;
   totalnum = 0;
   aq->First();
   switch (SearchModal) {
	   case 2:
        	aq->DisableControls();
        	while(!aq->Eof){
				totalmayang +=  aq->FieldByName("��������")->AsFloat ;
				totalshiyang += aq->FieldByName("����ʵ��")->AsFloat ;
				totalnum += aq->FieldByName("��������")->AsFloat;
				ordermayang +=  aq->FieldByName("��������")->AsFloat ;
				ordershiyang += aq->FieldByName("����ʵ��")->AsFloat ;
				ordernum += aq->FieldByName("��������")->AsFloat;
				aq->Next();
			}
			aq->EnableControls();
	   case 3:
	   case 6:
	   case 9:
			aq->DisableControls();
        	while(!aq->Eof){
				totalmayang +=  aq->FieldByName("������")->AsFloat ;
				totalshiyang += aq->FieldByName("��ʵ��")->AsFloat ;
				totalnum += aq->FieldByName("������")->AsFloat;
				aq->Next();
			}
			aq->EnableControls();
	   break;
	   case 5:
			aq->DisableControls();
        	while(!aq->Eof){
				totalmayang +=  aq->FieldByName("��������")->AsFloat + aq->FieldByName("�˻�����")->AsFloat;
				totalshiyang += aq->FieldByName("����ʵ��")->AsFloat + aq->FieldByName("�˻�ʵ��")->AsFloat;
				totalnum += aq->FieldByName("������")->AsFloat;
				aq->Next();
			}
			aq->EnableControls();
	   case -7:
			aq->DisableControls();
			while(!aq->Eof){
				totalmayang +=  aq->FieldByName("������")->AsFloat ;
				totalshiyang += aq->FieldByName("��ʵ��")->AsFloat ;
				totalnum += aq->FieldByName("������")->AsFloat;
				aq->Next();
			}
			aq->EnableControls();
	   break;
   default:
		aq->DisableControls();
		while(!aq->Eof){
			totalmayang +=  aq->FieldByName("����")->AsFloat ;
			totalshiyang += aq->FieldByName("ʵ��")->AsFloat ;
			totalnum += aq->FieldByName("����")->AsFloat;
			aq->Next();
		}
		aq->EnableControls();
	   break;
   }


 }
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::FormClose(TObject *Sender, TCloseAction &Action)

{
   Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::FormShow(TObject *Sender)
{
	   ReadyData();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::dgheadnoteCellClick(TColumn *Column)
{
   String sql;
	sql = "select C.Barcode,C.Barcode as '����',C.Name as '����',C.price as '����',B.Cbprice as '�ɱ�',discount as '�ۿ�',D.abbreviatedname as '������',E.name as '��Ӧ��', "
			" sum(A.fixedprice) as '����',sum(discountedprice) as 'ʵ��',sum(A.amount) as '����',F.Name as '��λ' from BS_WsaleNote A "
			" left join STK_BookInfo B on A.bkinfoid = B.ID "
			" left join BS_BookCatalog C on B.Bkcatalogid = C.ID "
			" left join BS_Pressinfo D on C.PressID = D.ID "
			" left join CUST_CustomerInfo E on b.supplierID = E.ID "
			" left join STK_BookstackInfo F on B.bkstackID = F.ID ";
   switch (SearchModal ) {
		case 0:
		case 4:
		   sql = sql + " where wsalentheaderid ='" + aqheader->FieldByName("ID")->AsAnsiString + "'";
		   sql = sql + " group by C.Barcode , c.name,c.price,A.discount,D.abbreviatedname "
					   " ,E.name,A.fixedprice,discountedprice,A.amount,F.name,B.Cbprice ";
			GetDataForDg(sql,aqdetal ,dgdetail);
		   lcount->Caption = "����" + IntToStr(aqdetal->RecordCount) + " ����¼";
		  break;
		case 7:
		   sql = "select C.Barcode ID,C.Barcode as '����',C.Name as '����',C.price as '����',B.Cbprice as '�ɱ�',A.discount as '�ۿ�',D.abbreviatedname as '������',"
				 " E.name as '��Ӧ��',"
				 " sum(A.fixedprice) as '����',sum(discountedprice) as 'ʵ��',sum(A.amount) as '����',F.Name as '��λ' from BS_RetailNote A "
				 " left join STK_BookInfo B on A.bkinfoid = B.ID "
				 " left join BS_BookCatalog C on B.Bkcatalogid = C.ID "
				 " left join BS_Pressinfo D on C.PressID = D.ID "
				 " left join CUST_CustomerInfo E on b.supplierID = E.ID "
				 " left join STK_BookstackInfo F on B.bkstackID = F.ID ";
			sql = sql + " where RetailNtheaderID ='" + aqheader->FieldByName("ID")->AsAnsiString + "'";
			sql = sql + " group by C.Barcode , c.name,c.price,A.discount,D.abbreviatedname "
			" ,E.name,A.fixedprice,discountedprice,A.amount,F.name,B.Cbprice ";
		   //	SearchModal = -2;
			GetDataForDg(sql,aqdetal ,dgdetail);
			lcount->Caption = "����" + IntToStr(aqdetal->RecordCount) + " ����¼";
		break;
   default:
	   ;
   }



}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::BtnExportClick(TObject *Sender)
{
	if (aqheader->Active && aqheader->RecordCount > 0) {
		if (SearchModal == 0 || SearchModal == 4 ) {
        	ToExcel0();
		}
		else
		{
			DbgridToExcel(dgheadnote);
		}
	}

}
//---------------------------------------------------------------------------

//Excel��������
bool __fastcall Tfrmsaleanalysis::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path;
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(savedlg->FileName .c_str()  );
		Name = ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
	else
	{
		return false;
	}
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
	v.OlePropertyGet("Cells",1,3).OlePropertySet("Value","����ͳ�Ʊ�" );

	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","���" );
	temptext = "'"+ cbstore->Text;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","��ʼʱ��" );
	temptext = "'"+ DateToStr(dtpstart->Date);
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",3,7).OlePropertySet("Value","����ʱ��" );
	temptext = "'"+ DateToStr(dtpend->Date);
	v.OlePropertyGet("Cells",3,8).OlePropertySet("Value",temptext .c_str() );

	n=4; */
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   //iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	temptext = ",,,����ͳ�Ʊ�";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n";
	if (chclient->Checked && edtclient->Text != "") {
    	temptext = temptext + "�ͻ�����," + edtclient->Text + ",";
	}
	if (cbstart->Checked ) {
		temptext = temptext + "��ʼʱ��," + DateToStr(dtpstart->Date) + ",";
	}
	if (cbend->Checked ) {
		temptext = temptext + "����ʱ��," + DateToStr(dtpend->Date) + ",";
	}
	if (temptext != "") {
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		temptext = "\n";
	}

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			//temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			//v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			temptext =  temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns ->Items [j-1]->FieldName == "����") {
				t1++;
				//temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				temptext = temptext + "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
			}
			else
			{
            	temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}

	temptext = "\n\n";
	temptext = temptext + "�ϼ�,������,"+ IntToStr(totalnum) + ",������," + FloatToStr(totalmayang) + ",��ʵ��," + FloatToStr(totalshiyang) ;
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"������ϣ�","��ʾ" ,MB_OK);

	/*v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","�ϼ�" );
	v.OlePropertyGet("Cells",t2+2+n,2).OlePropertySet("Value","������" );
	temptext = "'"+ edtnum->Text;
	v.OlePropertyGet("Cells",t2+2+n,3).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",t2+2+n,4).OlePropertySet("Value","������" );
	temptext = "'"+ edtmanyang->Text;
	v.OlePropertyGet("Cells",t2+2+n,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value","��ʵ��" );
	temptext = "'"+ edtshiyang->Text;
	v.OlePropertyGet("Cells",t2+2+n,7).OlePropertySet("Value",temptext .c_str());   */

	return false;
}
//---------------------------------------------------------------------------  ]

//---------------------------------------------------------------------------

//Excel��������
bool Tfrmsaleanalysis::ToExcel0()
{
	if (aqheader->IsEmpty() ) {
    	return false;
	}
	AnsiString temptext,path;
	savedlg->FileName = StringReplace(edtclient->Text,"\\","-",TReplaceFlags()<<rfReplaceAll);
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(savedlg->FileName .c_str()  );
		Name = ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
	else
	{
		return false;
	}
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   //iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	temptext = ",,,����ͳ�Ʊ�";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n";
	if (chclient->Checked && edtclient->Text != "") {
    	temptext = temptext + "�ͻ�����," + edtclient->Text + ",";
	}
	if (cbstart->Checked ) {
		temptext = temptext + "��ʼʱ��," + DateToStr(dtpstart->Date) + ",";
	}
	if (cbend->Checked ) {
		temptext = temptext + "����ʱ��," + DateToStr(dtpend->Date) + ",";
	}
	if (temptext != "") {
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		temptext = "\n";
	}
	if (edordermun->Visible ) {
		temptext = temptext + "����������," + edordermun->Text + ",����������," + edordermayang->Text + ",������ʵ��," + edordershiyang->Text ;
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		temptext = "\n";
	}
		temptext = temptext + "����������," + edtnum->Text + ",����������," + edtmanyang->Text + ",������ʵ��," + edtshiyang->Text ;
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		temptext = "\n";

	int t1= 0;

	int t2 = aqheader ->RecordCount ;
	aqheader->DisableControls();
	aqheader ->First();
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	while (!aqheader->Eof )
	{
		temptext = "\n\n";
		temptext = temptext + "����,�ͻ�����,����,����,ʵ��,ҵ��Ա,����";
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

		t1=0;
		temptext = "\n";
		for(int j=1;j<8  ;j++)
		{
				if (j == 1) {
					temptext = temptext + "'" + aqheader ->Fields->Fields[j] ->AsAnsiString + ",";
				}
				else
				{
					temptext = temptext + aqheader ->Fields->Fields[j] ->AsAnsiString + ",";
				}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

		//��ϸ
		sql = "select C.Barcode,C.Barcode as '����',C.Name as '����',C.price as '����',B.Cbprice as '�ɱ�',discount as '�ۿ�',D.abbreviatedname as '������',E.name as '��Ӧ��', "
			" sum(A.fixedprice) as '����',sum(discountedprice) as 'ʵ��',sum(A.amount) as '����' from BS_WsaleNote A "
			" left join STK_BookInfo B on A.bkinfoid = B.ID "
			" left join BS_BookCatalog C on B.Bkcatalogid = C.ID "
			" left join BS_Pressinfo D on C.pressCount = D.ID "
			" left join CUST_CustomerInfo E on b.supplierID = E.ID "
			" left join STK_BookstackInfo F on B.bkstackID = F.ID ";
		   sql = sql + " where wsalentheaderid ='" + aqheader->FieldByName("ID")->AsAnsiString + "'";
		   sql = sql + " group by C.Barcode , c.name,c.price,A.discount,D.abbreviatedname "
					   " ,E.name,A.fixedprice,discountedprice,A.amount,F.name,B.Cbprice ";
        	aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();

			temptext = "\n";
			temptext = temptext + "����,����,����,�ɱ�,�ۿ�,������,��Ӧ��,����,ʵ��,����";
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

			aq->First();
			while (!aq->Eof )
			{
				temptext = "\n";
				for(int i=1;i<11  ;i++)
				{
					if (i == 1) {
						temptext = temptext + "'" + aq->Fields->Fields[i]->AsAnsiString + ",";
					}
					else
					{
						temptext = temptext + aq->Fields->Fields[i]->AsAnsiString + ",";
					}

				}
				iFileLength   =   FileSeek(iFileHandle,0,2);
				FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
				aq->Next();
			}

		aqheader ->Next() ;
	}
	aqheader->EnableControls();

	delete aq;

	FileClose(iFileHandle);

	MessageBox(0,"������ϣ�","��ʾ" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------



void __fastcall Tfrmsaleanalysis::dgheadnoteTitleClick(TColumn *Column)
{
	if (aqheader->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqheader->Sort == "") {
		aqheader->Sort =  Column->FieldName + " ASC";
	}
	else if (aqheader->Sort == qusort) {
		aqheader->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqheader->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::dgdetailTitleClick(TColumn *Column)
{
	if (aqdetal->IsEmpty() ) {
        return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqdetal->Sort == "") {
		aqdetal->Sort =  Column->FieldName + " ASC";
	}
	else if (aqdetal->Sort == qusort) {
		aqdetal->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqdetal->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
		if (Key == VK_F10) {
		 BtnPrint->Click();
	   }
			if (Key == VK_F1) {
		 BtnView->Click();
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

void __fastcall Tfrmsaleanalysis::BtnAlignBottomClick(TObject *Sender)
{
	 WindowState = wsMinimized   ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::Button1Click(TObject *Sender)
{
	SearchModal = 0 ;
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::Button2Click(TObject *Sender)
{
	SearchModal = 1 ;
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::Button3Click(TObject *Sender)
{
	SearchModal = 2 ;
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::Button4Click(TObject *Sender)
{
	SearchModal = 3 ;
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::Button5Click(TObject *Sender)
{
	SearchModal = 4 ;
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::Button6Click(TObject *Sender)
{
	SearchModal = 5 ;
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::Button7Click(TObject *Sender)
{
	SearchModal = 6 ;
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::Button8Click(TObject *Sender)
{
	SearchModal = 7 ;
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::Button9Click(TObject *Sender)
{
	SearchModal = 9 ;
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::spselectClientClick(TObject *Sender)
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
void Tfrmsaleanalysis::ClientView()
{
	if (ClientID == -1) {
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
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaleanalysis::edtQryVendorKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edtQryVendor->Text,fstgid);
		if (mrOk == frm->ShowModal())
		{
			ClientID = frm->GetSelectID();
			ClientView();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------
