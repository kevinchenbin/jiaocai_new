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
   Title = "销售统计";
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
	 retailformat =  "￥" + aq->FieldByName("bk")->AsAnsiString ;
	 aq->Close();
	 aq->SQL->Clear();
	 aq->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
	 aq->Open();
	 saleformat =  "￥" + aq->FieldByName("bk")->AsAnsiString ;
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
	 return "￥" + aq->FieldByName("bk")->AsAnsiString ;
	 delete aq;

  }
//---------------------------------------------------------------------------
void __fastcall Tfrmsaleanalysis::cbanalysistypeChange(TObject *Sender)
{
	/*
		批销按单明细表
		批销按单汇总表
		批销业务员汇总表
		批销按单位统计
		批销按单退货明细表
		零售操作员汇总表
		零售按单汇总表
		销售时段汇总报表
		会员消费统计报表
	*/
   // SearchModal = cbanalysistype->ItemIndex ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsaleanalysis::BtnViewClick(TObject *Sender)
{
   if (cbstore->Text =="") {


	  MessageBox(0,"请选择店号!",Title.c_str(),MB_ICONEXCLAMATION);
	  return;

   }
   if (cbanalysistype->Text == "") {

	 MessageBox(0,"请选择查询类型!",Title.c_str(),MB_ICONEXCLAMATION);
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
		  case 0:            //批销按单明细表
			  sqlstr = "select A.ID,wsaleNtCode as '单号', dbo.UF_BS_GetClientName(A.VenDorID) as '客户名称',totalamount as '数量',fixedprice as '码洋',discountedprice as '实洋',C.Name as '业务员',convert(varchar(10),A.Hdtime,111) as '日期' from BS_WsaleNoteHeader A "
					   " left join CUST_CustomerInfo B on  A.VenDorID = B.ID "
					   " left join SYS_StaffInfo C on A.staffid = C.ID";
			  sqlstr = sqlstr + strwhere + sqlclient;
			  sqlstr = sqlstr + " and A.WsaleNtCode <> 0 ";
			  GetDataForDg(sqlstr,aqheader,dgheadnote );  //生成dbgrid标题
			  GetTotal(aqheader);     //计算合计
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
		  case 1:     //  批销按单汇总表
				sqlstr = "select A.ID,wsaleNtCode as '单号', dbo.UF_BS_GetClientName(A.VenDorID) as '客户名称',totalamount as '数量',fixedprice as '码洋',discountedprice as '实洋',C.Name as '业务员',convert(varchar(10),A.Hdtime,111) as '日期' from BS_WsaleNoteHeader A "
				   " left join CUST_CustomerInfo B on  A.VenDorID = B.ID "
				   " left join SYS_StaffInfo C on A.staffid = C.ID";
				sqlstr = sqlstr + strwhere + sqlclient;
				sqlstr = sqlstr + " and A.WsaleNtCode <> 0 ";
			GetDataForDg(sqlstr,aqheader,dgheadnote );  //生成dbgrid标题
			GetTotal(aqheader);     //计算合计
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
		  case 2: //  批销按单位统计
			 /*sqlstr = "select B.name as N,dbo.UF_BS_GetClientName(A.VenDorID) as '客户名称',B.Address as '地址',B.Contact as '联系人',B.local as '区域',sum(totalamount) as '总数量',sum(fixedprice) as '总码洋',sum(discountedprice) as '总实洋'"
					  " from BS_WsaleNoteHeader A "
					  " left join CUST_CustomerInfo B on  A.VenDorID = B.ID "
					  " left join SYS_StaffInfo C on A.staffid = C.ID " ;

			 sqlstr = sqlstr + strwhere+ sqlclient + " group by B.Name,B.Contact,B.local,B.Address,A.VenDorID ";*/


			 sqlstr = "select BS_WsaleNoteHeader.VendorID as N,dbo.UF_BS_GetClientName(BS_WsaleNoteHeader.VendorID) as '客户名称',"
						" dbo.UF_BS_Getorderamount(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '订货数量',"
						" dbo.UF_BS_Getorderfixedprice(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '订货码洋',"
						" dbo.UF_BS_GetorderDiscountedPrice(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '订货实洋',"
						" dbo.UF_BS_Getwsaleamount(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '发货数量',"
						" dbo.UF_BS_GetwsaleFixedPrice(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '发货码洋',"
						" dbo.UF_BS_GetwsaleDiscountedPrice(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '发货实洋',"
						" dbo.UF_BS_GetTwsaleamount(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '退货数量',"
						" dbo.UF_BS_GetTwsaleFixedPrice(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '退货码洋',"
						" dbo.UF_BS_GetTwsaleDiscountedPrice(BS_WsaleNoteHeader.VendorID,'" + strattime + "','" + endtime + "'," + IntToStr(fstgid) + ") as '退货实洋'"
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
		  case 3: //	批销业务员汇总表
			 sqlstr = "select C.ID , C.Name as '业务员',sum(totalamount) as '总数量', sum(fixedprice) as '总码洋',sum(discountedprice) as '总实洋'"
					  " FROM BS_WSALENOTEHEADER A "
					  " LEFT JOIN SYS_STAFFINFO C ON A.STAFFID = C.ID ";

			 sqlstr = sqlstr + strwhere + sqlclient + " Group by C.ID,C.Name";
			GetDataForDg(sqlstr,aqheader,dgheadnote );  //生成dbgrid标题
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
		 case 4:  //批销按单退货明细表
			sqlstr = "select A.ID,wsaleNtCode as '单号',dbo.UF_BS_GetClientName(A.VenDorID) as '客户名称',totalamount as '数量',fixedprice as '码洋',discountedprice as '实洋',C.Name as '业务员',convert(varchar(10),A.Hdtime,111) as '日期' from BS_WsaleNoteHeader A "
				   " left join CUST_CustomerInfo B on  A.VenDorID = B.ID "
				   " left join SYS_StaffInfo C on A.staffid = C.ID";
			sqlstr = sqlstr + strwhere + sqlclient + " and totalamount < 0";
			GetDataForDg(sqlstr,aqheader,dgheadnote );  //生成dbgrid标题
			GetTotal(aqheader);     //计算合计
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
		 case 5: //零售操作员汇总表
			  sqlstr = "select E.ID,E.零售员,G.总数量,E.零售码洋,E.零售实洋,F.退货码洋,F.退货实洋,G.现金收款 FROM "
					   "(select B.ID,sum(TotalAmount) as '总数量',sum((case when TotalDiscountedPrice >(RecCash+RecCardMoney) then (RecCash+RecCardMoney) else TotalDiscountedPrice end)) as '现金收款' from BS_RetailNoteHeader as A  left join SYS_User B on A.operatorID = B.ID ";
			  sqlstr = sqlstr + strwhere;
			  sqlstr = sqlstr + " group by operatorID,B.name,B.ID ) AS G FULL JOIN ";
			  sqlstr = sqlstr + " (select B.ID,B.Name as '零售员', sum(TotalFixedprice) as '零售码洋',sum(TotalDiscountedprice) as '零售实洋' from BS_RetailNoteHeader as A  left join SYS_User B on A.operatorID = B.ID ";
			  sqlstr = sqlstr + strwhere;
			  sqlstr = sqlstr + " and TotalAmount >= 0 group by operatorID,B.name,B.ID ) AS E ON G.ID = E.ID FULL JOIN ";
			  sqlstr = sqlstr + " (select B.ID, sum(TotalFixedprice) as '退货码洋',sum(TotalDiscountedprice) as '退货实洋' from BS_RetailNoteHeader as A  left join SYS_User B on A.operatorID = B.ID ";
			  sqlstr = sqlstr + strwhere;
			  sqlstr = sqlstr + " and TotalAmount < 0 group by operatorID,B.name,B.ID ) AS F ON F.ID = G.ID ";
			GetDataForDg(sqlstr,aqheader,dgheadnote);  //生成dbgrid标题
			GetTotal(aqheader);     //计算合计
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
		 case 6://零售按单汇总表

			 sqlstr = "select A.RetailNtcode,A.RetailNtCode as '零售单号',A.TotalAmount as '总数量',A.TotalFixedprice as '总码洋',A.TotalDiscountedprice as '总实洋', "
					  " A.RecCash as '现金收入',A.RecCardMoney as '会员卡收入',B.Name as '操作员',convert(varchar(10),A.Hdtime,111) as '日期' from BS_RetailNoteHeader A "
					  " left join SYS_User B on A.operatorID = B.ID ";
			 sqlstr = sqlstr +  strwhere;
			GetDataForDg(sqlstr,aqheader,dgheadnote );  //生成dbgrid标题
			GetTotal(aqheader);     //计算合计
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
		case 7: //零售按单明细表
				sqlstr = "select A.ID ,A.RetailNtCode as '零售单号',A.TotalAmount as '数量',A.TotalFixedprice as '码洋',A.TotalDiscountedprice as '实洋', "
				" A.RecCash as '现金收入',A.RecCardMoney as '会员卡收入',B.Name as '操作员',convert(varchar(10),A.Hdtime,111) as '日期' from BS_RetailNoteHeader A "
				" left join SYS_User B on A.operatorID = B.ID ";
				sqlstr = sqlstr +  strwhere;
				GetDataForDg(sqlstr,aqheader,dgheadnote );  //生成dbgrid标题
				GetTotal(aqheader);     //计算合计
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
		case 8:// 销售时段汇总报表

		 break;
		case 9://会员消费统计报表

			 sqlstr = "select C.Name ,C.Name as '会员名称',sum(A.TotalAmount) as '总数量',sum(A.TotalFixedprice) as '总码洋',sum(A.TotalDiscountedprice) as '总实洋',"
				   " sum(A.RecCash) as '现金收入',sum(A.RecCardMoney) as '会员卡收入'"
				   " from BS_RetailNoteHeader A "
				   " left join SYS_User B on A.operatorID = B.ID "
				   " left join Cust_memberinfo C on A.MemberID = C.ID ";
			 sqlstr = sqlstr +  strwhere + " group by C.Name";
			GetDataForDg(sqlstr,aqheader,dgheadnote );  //生成dbgrid标题
			GetTotal(aqheader);     //计算合计
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
			((TFloatField *)aq->FieldByName("发货码洋"))->DisplayFormat = saleformat;//"0.00";
			((TFloatField *)aq->FieldByName("发货实洋"))->DisplayFormat = saleformat;//"0.00";
			((TFloatField *)aq->FieldByName("订货码洋"))->DisplayFormat = saleformat;//"0.00";
			((TFloatField *)aq->FieldByName("订货实洋"))->DisplayFormat = saleformat;//"0.00";
			break;
		  case 3:
			((TFloatField *)aq->FieldByName("总码洋"))->DisplayFormat = saleformat;//"0.00";
			((TFloatField *)aq->FieldByName("总实洋"))->DisplayFormat = saleformat;//"0.00";
			break;
		  case 6:
		  case 9:
			((TFloatField *)aq->FieldByName("总码洋"))->DisplayFormat = retailformat;//"0.00";
			((TFloatField *)aq->FieldByName("总实洋"))->DisplayFormat = retailformat;//"0.00";
			break;
		  case 5:
			((TFloatField *)aq->FieldByName("零售码洋"))->DisplayFormat = retailformat;//"0.00";
			((TFloatField *)aq->FieldByName("零售实洋"))->DisplayFormat = retailformat;
			((TFloatField *)aq->FieldByName("退货码洋"))->DisplayFormat = retailformat;//"0.00";
			((TFloatField *)aq->FieldByName("退货实洋"))->DisplayFormat = retailformat;
			((TFloatField *)aq->FieldByName("现金收款"))->DisplayFormat = retailformat;
			break;
		  case -7:
			((TFloatField *)aq->FieldByName("总码洋"))->DisplayFormat = retailformat;//"0.00";
			((TFloatField *)aq->FieldByName("总实洋"))->DisplayFormat = retailformat;//"0.00";
			break;
	 default:
			((TFloatField *)aq->FieldByName("码洋"))->DisplayFormat = saleformat;//"0.00";
			((TFloatField *)aq->FieldByName("实洋"))->DisplayFormat = saleformat;//"0.00";
		 ;
	 }
	 aq->DisableControls();
	 for (int i = 1; i < aq->Fields->Count ; i++) { //去悼ID

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
				totalmayang +=  aq->FieldByName("发货码洋")->AsFloat ;
				totalshiyang += aq->FieldByName("发货实洋")->AsFloat ;
				totalnum += aq->FieldByName("发货数量")->AsFloat;
				ordermayang +=  aq->FieldByName("订货码洋")->AsFloat ;
				ordershiyang += aq->FieldByName("订货实洋")->AsFloat ;
				ordernum += aq->FieldByName("订货数量")->AsFloat;
				aq->Next();
			}
			aq->EnableControls();
	   case 3:
	   case 6:
	   case 9:
			aq->DisableControls();
        	while(!aq->Eof){
				totalmayang +=  aq->FieldByName("总码洋")->AsFloat ;
				totalshiyang += aq->FieldByName("总实洋")->AsFloat ;
				totalnum += aq->FieldByName("总数量")->AsFloat;
				aq->Next();
			}
			aq->EnableControls();
	   break;
	   case 5:
			aq->DisableControls();
        	while(!aq->Eof){
				totalmayang +=  aq->FieldByName("零售码洋")->AsFloat + aq->FieldByName("退货码洋")->AsFloat;
				totalshiyang += aq->FieldByName("零售实洋")->AsFloat + aq->FieldByName("退货实洋")->AsFloat;
				totalnum += aq->FieldByName("总数量")->AsFloat;
				aq->Next();
			}
			aq->EnableControls();
	   case -7:
			aq->DisableControls();
			while(!aq->Eof){
				totalmayang +=  aq->FieldByName("总码洋")->AsFloat ;
				totalshiyang += aq->FieldByName("总实洋")->AsFloat ;
				totalnum += aq->FieldByName("总数量")->AsFloat;
				aq->Next();
			}
			aq->EnableControls();
	   break;
   default:
		aq->DisableControls();
		while(!aq->Eof){
			totalmayang +=  aq->FieldByName("码洋")->AsFloat ;
			totalshiyang += aq->FieldByName("实洋")->AsFloat ;
			totalnum += aq->FieldByName("数量")->AsFloat;
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
	sql = "select C.Barcode,C.Barcode as '条码',C.Name as '书名',C.price as '单价',B.Cbprice as '成本',discount as '折扣',D.abbreviatedname as '出版社',E.name as '供应商', "
			" sum(A.fixedprice) as '码洋',sum(discountedprice) as '实洋',sum(A.amount) as '数量',F.Name as '库位' from BS_WsaleNote A "
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
		   lcount->Caption = "共有" + IntToStr(aqdetal->RecordCount) + " 条记录";
		  break;
		case 7:
		   sql = "select C.Barcode ID,C.Barcode as '条码',C.Name as '书名',C.price as '单价',B.Cbprice as '成本',A.discount as '折扣',D.abbreviatedname as '出版社',"
				 " E.name as '供应商',"
				 " sum(A.fixedprice) as '码洋',sum(discountedprice) as '实洋',sum(A.amount) as '数量',F.Name as '库位' from BS_RetailNote A "
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
			lcount->Caption = "共有" + IntToStr(aqdetal->RecordCount) + " 条记录";
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

//Excel导出函数
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
		MessageBox(0,"没有数据！","错误确认" ,MB_OK);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	v.OlePropertyGet("Cells",1,3).OlePropertySet("Value","销售统计表" );

	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","店号" );
	temptext = "'"+ cbstore->Text;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","开始时间" );
	temptext = "'"+ DateToStr(dtpstart->Date);
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",3,7).OlePropertySet("Value","结束时间" );
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

	temptext = ",,,销售统计表";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n";
	if (chclient->Checked && edtclient->Text != "") {
    	temptext = temptext + "客户名称," + edtclient->Text + ",";
	}
	if (cbstart->Checked ) {
		temptext = temptext + "开始时间," + DateToStr(dtpstart->Date) + ",";
	}
	if (cbend->Checked ) {
		temptext = temptext + "结束时间," + DateToStr(dtpend->Date) + ",";
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
			if (dbg->Columns ->Items [j-1]->FieldName == "单号") {
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
	temptext = temptext + "合计,总数量,"+ IntToStr(totalnum) + ",总码洋," + FloatToStr(totalmayang) + ",总实洋," + FloatToStr(totalshiyang) ;
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);

	/*v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","合计" );
	v.OlePropertyGet("Cells",t2+2+n,2).OlePropertySet("Value","总数量" );
	temptext = "'"+ edtnum->Text;
	v.OlePropertyGet("Cells",t2+2+n,3).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",t2+2+n,4).OlePropertySet("Value","总码洋" );
	temptext = "'"+ edtmanyang->Text;
	v.OlePropertyGet("Cells",t2+2+n,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value","总实洋" );
	temptext = "'"+ edtshiyang->Text;
	v.OlePropertyGet("Cells",t2+2+n,7).OlePropertySet("Value",temptext .c_str());   */

	return false;
}
//---------------------------------------------------------------------------  ]

//---------------------------------------------------------------------------

//Excel导出函数
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

	temptext = ",,,销售统计表";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n";
	if (chclient->Checked && edtclient->Text != "") {
    	temptext = temptext + "客户名称," + edtclient->Text + ",";
	}
	if (cbstart->Checked ) {
		temptext = temptext + "开始时间," + DateToStr(dtpstart->Date) + ",";
	}
	if (cbend->Checked ) {
		temptext = temptext + "结束时间," + DateToStr(dtpend->Date) + ",";
	}
	if (temptext != "") {
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		temptext = "\n";
	}
	if (edordermun->Visible ) {
		temptext = temptext + "订货总数量," + edordermun->Text + ",订货总码洋," + edordermayang->Text + ",订货总实洋," + edordershiyang->Text ;
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		temptext = "\n";
	}
		temptext = temptext + "发货总数量," + edtnum->Text + ",发货总码洋," + edtmanyang->Text + ",发货总实洋," + edtshiyang->Text ;
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
		temptext = temptext + "单号,客户名称,数量,码洋,实洋,业务员,日期";
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

		//明细
		sql = "select C.Barcode,C.Barcode as '条码',C.Name as '书名',C.price as '单价',B.Cbprice as '成本',discount as '折扣',D.abbreviatedname as '出版社',E.name as '供应商', "
			" sum(A.fixedprice) as '码洋',sum(discountedprice) as '实洋',sum(A.amount) as '数量' from BS_WsaleNote A "
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
			temptext = temptext + "条码,书名,单价,成本,折扣,出版社,供应商,码洋,实洋,数量";
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

	MessageBox(0,"导出完毕！","提示" ,MB_OK);
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

