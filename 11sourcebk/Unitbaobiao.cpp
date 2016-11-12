//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitbaobiao.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "Series"
#pragma resource "*.dfm"
TfrmBaobiao *frmBaobiao;
//---------------------------------------------------------------------------
__fastcall TfrmBaobiao::TfrmBaobiao(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
	con = cn;
	fstgid = stgid;
	aqrk->Connection = cn;
	aqpx->Connection = cn;
	aqls->Connection = cn;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = cn;
	AnsiString sql;
	sql = "select ID,Name from SYS_StorageInfo";
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
		master = aq->FieldByName("Master")->AsBoolean;
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
	sql = "select  A.Name,sum(TotalAmount) as TotalAmount,sum(TotalFixedPrice) as TotalFixedPrice, "
			" sum(TotalDiscountedPrice) as TotalDiscountedPrice from "
			" (select  CONVERT(varchar(100), HdTime, 23) as Name,sum(BS_StorageNoteHeader.TotalAmount) as TotalAmount,sum(BS_StorageNoteHeader.TotalFixedPrice) as TotalFixedPrice,sum(BS_StorageNoteHeader.TotalDiscountedPrice) as TotalDiscountedPrice "
			" from BS_StorageNoteHeader "
			" where (datediff(d,BS_StorageNoteHeader.HdTime,getdate()) < 7) and BS_StorageNoteHeader.Stgid = " + IntToStr(stgid) +
			" group by  CONVERT(varchar(100), HdTime, 23) union "
			" select convert(char(10),dateadd(day,-number,getdate()),120),0,0,0 "
			" from master..spt_values "
			" where type = 'P' "
			" and number between 0 and 6) as A"
			" GROUP BY A.Name order by A.Name" ;
	aqrk->Close();
	aqrk->SQL->Clear();
	aqrk->SQL->Add(sql);
	aqrk->Open();
	title = "最近一周入库数量按日统计";
	charstorage->Title->Text->Clear();
	charstorage->Title->Text->Add(title);
	charstorage->Series[0]->Clear();
	charstorage->Series[1]->Clear();
	charstorage->Series[2]->Clear();
	charstorage->Series[3]->Clear();
	charstorage->Series[4]->Clear();
	charstorage->Series[5]->Clear();
	for (int i = 1; i <= aqrk->RecordCount ; i++) {
	   charstorage->Series[0]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
	   charstorage->Series[3]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
	   aqrk->Next();
	}

	sql = "select  A.Name,sum(TotalAmount) as TotalAmount,sum(TotalFixedPrice) as TotalFixedPrice,"
			" sum(TotalDiscountedPrice) as TotalDiscountedPrice from "
			" (select  CONVERT(varchar(100), HdTime, 23) as Name,sum(BS_WsaleNoteHeader.TotalAmount) as TotalAmount,sum(BS_WsaleNoteHeader.FixedPrice) as TotalFixedPrice,sum(BS_WsaleNoteHeader.DiscountedPrice) as TotalDiscountedPrice "
			" from BS_WsaleNoteHeader "
			" where (datediff(d,BS_WsaleNoteHeader.HdTime,getdate()) < 7) and BS_WsaleNoteHeader.Stgid = " + IntToStr(stgid) +
			" group by  CONVERT(varchar(100), HdTime, 23) union "
			" select convert(char(10),dateadd(day,-number,getdate()),120),0,0,0 "
			" from master..spt_values "
			" where type = 'P' "
			" and number between 0 and 6) as A"
			" GROUP BY A.Name order by A.Name" ;
	aqpx->Close();
	aqpx->SQL->Clear();
	aqpx->SQL->Add(sql);
	aqpx->Open();
	title = "最近一周批销数量按日统计";
	for (int i = 1; i <= aqpx->RecordCount ; i++) {
	   charstorage->Series[1]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
	   charstorage->Series[4]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
	   aqpx->Next();
	}

	sql = "select  A.Name,sum(TotalAmount) as TotalAmount,sum(TotalFixedPrice) as TotalFixedPrice,"
			" sum(TotalDiscountedPrice) as TotalDiscountedPrice from "
			" (select  CONVERT(varchar(100), HdTime, 23) as Name,sum(BS_RetailNoteHeader.TotalAmount) as TotalAmount,sum(BS_RetailNoteHeader.TotalFixedPrice) as TotalFixedPrice,sum(BS_RetailNoteHeader.TotalDiscountedPrice) as TotalDiscountedPrice "
			" from BS_RetailNoteHeader "
			" where (datediff(d,BS_RetailNoteHeader.HdTime,getdate()) < 7) and BS_RetailNoteHeader.Stgid = " + IntToStr(stgid) +
			" group by  CONVERT(varchar(100), HdTime, 23)union "
			" select convert(char(10),dateadd(day,-number,getdate()),120),0,0,0 "
			" from master..spt_values "
			" where type = 'P' "
			" and number between 0 and 6) as A"
			" GROUP BY A.Name order by A.Name";
	aqls->Close();
	aqls->SQL->Clear();
	aqls->SQL->Add(sql);
	aqls->Open();
	title = "最近一周零售数量按日统计";
	//double f[2] = {100,200};

	for (int i = 1; i <= aqls->RecordCount ; i++) {
	   charstorage->Series[2]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
	   charstorage->Series[5]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
	   aqls->Next();
	}
	charstorage->Series[3]->Visible = false;
	charstorage->Series[4]->Visible = false;
	charstorage->Series[5]->Visible = false;
	charstorage->Series[1]->Visible = false;
	charstorage->Series[2]->Visible = false;

}
//---------------------------------------------------------------------------
void __fastcall TfrmBaobiao::SpeedButton2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBaobiao::SpeedButton1Click(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBaobiao::rg2Click(TObject *Sender)
{
	switch (rg2->ItemIndex ) {
		case 0:
				switch (rg1->ItemIndex ) {
					case 0:
						title = "最近一周入库数量按日统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						break;
					case 1:
						title = "最近七周入库数量按周统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						break;
					case 2:
						title = "最近半年入库数量按月统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						break;
				default:
					;
				}

				charstorage->Series[0]->Clear();
				charstorage->Series[1]->Clear();
				charstorage->Series[2]->Clear();
				charstorage->Series[3]->Clear();
				charstorage->Series[4]->Clear();
				charstorage->Series[5]->Clear();
				aqrk->First();
				for (int i = 1; i <= aqrk->RecordCount ; i++) {
					charstorage->Series[0]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
					charstorage->Series[3]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);

					//charstorage->Series[1]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
					aqrk->Next();
				}

				aqpx->First();
				for (int i = 1; i <= aqpx->RecordCount ; i++) {
					charstorage->Series[1]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
					charstorage->Series[4]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);

					//charpx->Series[1]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clRed);
					aqpx->Next();
				}

				aqls->First();
				for (int i = 1; i <= aqls->RecordCount ; i++) {
					charstorage->Series[2]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
					charstorage->Series[5]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);

					//charls->Series[1]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clRed);
					aqls->Next();
				}

			break;
		case 1:
				switch (rg1->ItemIndex ) {
					case 0:
						title = "最近一周入库码洋按日统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						break;
					case 1:
						title = "最近七周入库码洋按周统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						break;
					case 2:
						title = "最近半年入库码洋按月统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						break;
				default:
					;
				}

				charstorage->Series[0]->Clear();
				charstorage->Series[1]->Clear();
				charstorage->Series[2]->Clear();
				charstorage->Series[3]->Clear();
				charstorage->Series[4]->Clear();
				charstorage->Series[5]->Clear();
				aqrk->First();
				for (int i = 1; i <= aqrk->RecordCount ; i++) {
					charstorage->Series[0]->AddXY(i,aqrk->FieldByName("TotalFixedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
					charstorage->Series[3]->AddXY(i,aqrk->FieldByName("TotalFixedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);

					//charstorage->Series[1]->AddXY(i,aqrk->FieldByName("TotalFixedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
					aqrk->Next();
				}

				aqpx->First();
				for (int i = 1; i <= aqpx->RecordCount ; i++) {
					charstorage->Series[1]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
					charstorage->Series[4]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);

					//charpx->Series[1]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clRed);
					aqpx->Next();
				}

				aqls->First();
				for (int i = 1; i <= aqls->RecordCount ; i++) {
					charstorage->Series[2]->AddXY(i,aqls->FieldByName("TotalFixedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
					charstorage->Series[5]->AddXY(i,aqls->FieldByName("TotalFixedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);

					//charls->Series[1]->AddXY(i,aqls->FieldByName("TotalFixedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clRed);
					aqls->Next();
				}
			break;
		case 2:
				switch (rg1->ItemIndex ) {
					case 0:
						title = "最近一周入库实洋按日统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						break;
					case 1:
						title = "最近七周入库实洋按周统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						break;
					case 2:
						title = "最近半年入库实洋按月统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						break;
				default:
					;
				}

				charstorage->Series[0]->Clear();
				charstorage->Series[1]->Clear();
				charstorage->Series[2]->Clear();
				charstorage->Series[3]->Clear();
				charstorage->Series[4]->Clear();
				charstorage->Series[5]->Clear();
				aqrk->First();
				for (int i = 1; i <= aqrk->RecordCount ; i++) {
					charstorage->Series[0]->AddXY(i,aqrk->FieldByName("TotalDiscountedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
					charstorage->Series[3]->AddXY(i,aqrk->FieldByName("TotalDiscountedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);

					//charstorage->Series[1]->AddXY(i,aqrk->FieldByName("TotalDiscountedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
					aqrk->Next();
				}

				aqpx->First();
				for (int i = 1; i <= aqpx->RecordCount ; i++) {
					charstorage->Series[1]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
					charstorage->Series[4]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);

					//charpx->Series[1]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clRed);
					aqpx->Next();
				}

				aqls->First();
				for (int i = 1; i <= aqls->RecordCount ; i++) {
					charstorage->Series[2]->AddXY(i,aqls->FieldByName("TotalDiscountedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
					charstorage->Series[5]->AddXY(i,aqls->FieldByName("TotalDiscountedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);

					//charls->Series[1]->AddXY(i,aqls->FieldByName("TotalDiscountedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clRed);
					aqls->Next();
				}
			break;
	default:
		;
	}

	/*switch (rgview->ItemIndex ) {
	case 0:
		if (ch1->Checked ) {
			charstorage->Series[0]->Visible = true;
		}
		else
		{
			charstorage->Series[0]->Visible = false;
		}
		if (ch2->Checked ) {
			charstorage->Series[1]->Visible = true;
		}
		else
		{
			charstorage->Series[1]->Visible = false;
		}
		if (ch3->Checked ) {
			charstorage->Series[2]->Visible = true;
		}
		else
		{
			charstorage->Series[2]->Visible = false;
		}
		charstorage->Series[3]->Visible = false;
		charstorage->Series[4]->Visible = false;
		charstorage->Series[5]->Visible = false;
		break;
	case 1:
		charstorage->Series[0]->Visible = false;
		charstorage->Series[1]->Visible = false;
		charstorage->Series[2]->Visible = false;
		if (ch1->Checked ) {
			charstorage->Series[3]->Visible = true;
		}
		else
		{
			charstorage->Series[3]->Visible = false;
		}
		if (ch2->Checked ) {
			charstorage->Series[4]->Visible = true;
		}
		else
		{
			charstorage->Series[4]->Visible = false;
		}
		if (ch3->Checked ) {
			charstorage->Series[5]->Visible = true;
		}
		else
		{
			charstorage->Series[5]->Visible = false;
		}
		break;
	default:
		;
	}   */
}
//---------------------------------------------------------------------------
void __fastcall TfrmBaobiao::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBaobiao::rg1Click(TObject *Sender)
{
	int storageid;
	AnsiString sql;
	try {
		storageid = (int)(cbstorage->Items->Objects[cbstorage->ItemIndex]);
	} catch (...) {
		MessageBox(0,"请选择正确的店名！","警告" ,MB_ICONWARNING);
    	return;
	}

	switch (rg1->ItemIndex ) {
		case 0:
			sql = "select  A.Name,sum(TotalAmount) as TotalAmount,sum(TotalFixedPrice) as TotalFixedPrice,"
					" sum(TotalDiscountedPrice) as TotalDiscountedPrice from "
					" (select  CONVERT(varchar(100), HdTime, 23) as Name,sum(BS_StorageNoteHeader.TotalAmount) as TotalAmount,sum(BS_StorageNoteHeader.TotalFixedPrice) as TotalFixedPrice,sum(BS_StorageNoteHeader.TotalDiscountedPrice) as TotalDiscountedPrice "
					" from BS_StorageNoteHeader "
					" where (datediff(d,BS_StorageNoteHeader.HdTime,getdate()) < 7)";
			if (chstorage->Checked ) {
				sql = sql + " and BS_StorageNoteHeader.Stgid = " + IntToStr(storageid);
			}
			sql = sql + " group by  CONVERT(varchar(100), HdTime, 23) union "
			" select convert(char(10),dateadd(day,-number,getdate()),120),0,0,0 "
			" from master..spt_values "
			" where type = 'P' "
			" and number between 0 and 6) as A"
			" GROUP BY A.Name order by A.Name" ;
			aqrk->Close();
			aqrk->SQL->Clear();
			aqrk->SQL->Add(sql);
			aqrk->Open();
			switch (rg2->ItemIndex ) {
				case 0:
						title = "最近一周入库数量按日统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						charstorage->Series[0]->Clear();
						charstorage->Series[1]->Clear();
						charstorage->Series[2]->Clear();
						charstorage->Series[3]->Clear();
						charstorage->Series[4]->Clear();
						charstorage->Series[5]->Clear();
						for (int i = 1; i <= aqrk->RecordCount ; i++) {
						   charstorage->Series[0]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[3]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);

						   //charstorage->Series[1]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqrk->Next();
						}
					break;
				case 1:
						title = "最近一周入库码洋按日统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						charstorage->Series[0]->Clear();
						charstorage->Series[1]->Clear();
						charstorage->Series[2]->Clear();
						charstorage->Series[3]->Clear();
						charstorage->Series[4]->Clear();
						charstorage->Series[5]->Clear();
						for (int i = 1; i <= aqrk->RecordCount ; i++) {
						   charstorage->Series[0]->AddXY(i,aqrk->FieldByName("TotalFixedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[3]->AddXY(i,aqrk->FieldByName("TotalFixedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);

						   //charstorage->Series[1]->AddXY(i,aqrk->FieldByName("TotalFixedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqrk->Next();
						}
					break;
				case 2:
						title = "最近一周入库实洋按日统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						charstorage->Series[0]->Clear();
						charstorage->Series[1]->Clear();
						charstorage->Series[2]->Clear();
						charstorage->Series[3]->Clear();
						charstorage->Series[4]->Clear();
						charstorage->Series[5]->Clear();
						for (int i = 1; i <= aqrk->RecordCount ; i++) {
						   charstorage->Series[0]->AddXY(i,aqrk->FieldByName("TotalDiscountedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
                           charstorage->Series[3]->AddXY(i,aqrk->FieldByName("TotalDiscountedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);

						   //charstorage->Series[1]->AddXY(i,aqrk->FieldByName("TotalDiscountedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqrk->Next();
						}
					break;
            default:
				;
			}
			/*switch (rgview->ItemIndex ) {
				case 0:
					charstorage->Series[0]->Visible = true;
					charstorage->Series[1]->Visible = true;
					charstorage->Series[2]->Visible = true;
					charstorage->Series[3]->Visible = false;
					charstorage->Series[4]->Visible = false;
					charstorage->Series[5]->Visible = false;
					break;
				case 1:
					charstorage->Series[0]->Visible = false;
					charstorage->Series[1]->Visible = false;
					charstorage->Series[2]->Visible = false;
					charstorage->Series[3]->Visible = true;
					charstorage->Series[4]->Visible = true;
					charstorage->Series[5]->Visible = true;
					break;
            default:
				;
			} */


			sql = "select  A.Name,sum(TotalAmount) as TotalAmount,sum(TotalFixedPrice) as TotalFixedPrice,"
					" sum(TotalDiscountedPrice) as TotalDiscountedPrice from "
					"(select  CONVERT(varchar(100), HdTime, 23) as Name,sum(BS_WsaleNoteHeader.TotalAmount) as TotalAmount,sum(BS_WsaleNoteHeader.FixedPrice) as TotalFixedPrice,sum(BS_WsaleNoteHeader.DiscountedPrice) as TotalDiscountedPrice "
					" from BS_WsaleNoteHeader "
					" where (datediff(d,BS_WsaleNoteHeader.HdTime,getdate()) < 7)";
			if (chstorage->Checked ) {
				sql = sql + " and BS_WsaleNoteHeader.Stgid = " + IntToStr(storageid);
			}
			sql = sql + " group by  CONVERT(varchar(100), HdTime, 23) union "
			" select convert(char(10),dateadd(day,-number,getdate()),120),0,0,0 "
			" from master..spt_values "
			" where type = 'P' "
			" and number between 0 and 6) as A"
			" GROUP BY A.Name order by A.Name" ;
			aqpx->Close();
			aqpx->SQL->Clear();
			aqpx->SQL->Add(sql);
			aqpx->Open();
			switch (rg2->ItemIndex ) {
				case 0:
						for (int i = 1; i <= aqpx->RecordCount ; i++) {
						   charstorage->Series[1]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   charstorage->Series[4]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);

						   //charpx->Series[1]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqpx->Next();
						}
					break;
				case 1:
						for (int i = 1; i <= aqpx->RecordCount ; i++) {
						   charstorage->Series[1]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   charstorage->Series[4]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);

						   //charpx->Series[1]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqpx->Next();
						}
					break;
				case 2:
						for (int i = 1; i <= aqpx->RecordCount ; i++) {
						   charstorage->Series[1]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   charstorage->Series[4]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);

						   //charpx->Series[1]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqpx->Next();
						}
					break;
			default:
				;
			}


			sql = "select  A.Name,sum(TotalAmount) as TotalAmount,sum(TotalFixedPrice) as TotalFixedPrice,"
					" sum(TotalDiscountedPrice) as TotalDiscountedPrice from "
					" (select  CONVERT(varchar(100), HdTime, 23) as Name,sum(BS_RetailNoteHeader.TotalAmount) as TotalAmount,sum(BS_RetailNoteHeader.TotalFixedPrice) as TotalFixedPrice,sum(BS_RetailNoteHeader.TotalDiscountedPrice) as TotalDiscountedPrice "
					" from BS_RetailNoteHeader "
					" where (datediff(d,BS_RetailNoteHeader.HdTime,getdate()) < 7)";
			if (chstorage->Checked ) {
				sql = sql + " and BS_RetailNoteHeader.Stgid = " + IntToStr(storageid);
			}
			sql = sql + " group by  CONVERT(varchar(100), HdTime, 23) union "
			" select convert(char(10),dateadd(day,-number,getdate()),120),0,0,0 "
			" from master..spt_values "
			" where type = 'P' "
			" and number between 0 and 6) as A"
			" GROUP BY A.Name order by A.Name" ;
			aqls->Close();
			aqls->SQL->Clear();
			aqls->SQL->Add(sql);
			aqls->Open();
			switch (rg2->ItemIndex ) {
				case 0:
						for (int i = 1; i <= aqls->RecordCount ; i++) {
						   charstorage->Series[2]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
						   charstorage->Series[5]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);

						   //charls->Series[1]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqls->Next();
						}
					break;
				case 1:
						for (int i = 1; i <= aqls->RecordCount ; i++) {
						   charstorage->Series[2]->AddXY(i,aqls->FieldByName("TotalFixedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
						   charstorage->Series[5]->AddXY(i,aqls->FieldByName("TotalFixedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);

						   //charls->Series[1]->AddXY(i,aqls->FieldByName("TotalFixedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqls->Next();
						}
					break;
				case 2:
						for (int i = 1; i <= aqls->RecordCount ; i++) {
						   charstorage->Series[2]->AddXY(i,aqls->FieldByName("TotalDiscountedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
						   charstorage->Series[5]->AddXY(i,aqls->FieldByName("TotalDiscountedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);

						   //charls->Series[1]->AddXY(i,aqls->FieldByName("TotalDiscountedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqls->Next();
						}
					break;
			default:
				;
			}

			break;
		case 1:
			sql = "select  A.Name,sum(TotalAmount) as TotalAmount,sum(TotalFixedPrice) as TotalFixedPrice,"
					" sum(TotalDiscountedPrice) as TotalDiscountedPrice from "
					"(select  DATEPART(week, HdTime) as Name,sum(BS_StorageNoteHeader.TotalAmount) as TotalAmount,sum(BS_StorageNoteHeader.TotalFixedPrice) as TotalFixedPrice,sum(BS_StorageNoteHeader.TotalDiscountedPrice) as TotalDiscountedPrice "
					" from BS_StorageNoteHeader "
					" where (datediff(week,BS_StorageNoteHeader.HdTime,getdate()) < 7)";
            if (chstorage->Checked ) {
				sql = sql + " and BS_StorageNoteHeader.Stgid = " + IntToStr(storageid);
			}
			sql = sql + " group by  DATEPART(week, HdTime) union "
			" select DATEPART(week,dateadd(week,-number,getdate())),0,0,0 "
			" from master..spt_values "
			" where type = 'P' "
			" and number between 0 and 6) as A"
			" GROUP BY A.Name order by A.Name" ;
			aqrk->Close();
			aqrk->SQL->Clear();
			aqrk->SQL->Add(sql);
			aqrk->Open();
			switch (rg2->ItemIndex ) {
				case 0:
						title = "最近七周入库数量按周统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						charstorage->Series[0]->Clear();
						charstorage->Series[1]->Clear();
						charstorage->Series[2]->Clear();
						charstorage->Series[3]->Clear();
						charstorage->Series[4]->Clear();
						charstorage->Series[5]->Clear();
						for (int i = 1; i <= aqrk->RecordCount ; i++) {
						   charstorage->Series[0]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[3]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);

						   //charstorage->Series[1]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqrk->Next();
						}
					break;
				case 1:
						title = "最近七周入库码洋按周统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						charstorage->Series[0]->Clear();
						charstorage->Series[1]->Clear();
						charstorage->Series[2]->Clear();
						charstorage->Series[3]->Clear();
						charstorage->Series[4]->Clear();
						charstorage->Series[5]->Clear();
						for (int i = 1; i <= aqrk->RecordCount ; i++) {
						   charstorage->Series[0]->AddXY(i,aqrk->FieldByName("TotalFixedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[3]->AddXY(i,aqrk->FieldByName("TotalFixedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);

						   //charstorage->Series[1]->AddXY(i,aqrk->FieldByName("TotalFixedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqrk->Next();
						}
					break;
				case 2:
						title = "最近七周入库实洋按周统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						charstorage->Series[0]->Clear();
						charstorage->Series[1]->Clear();
						charstorage->Series[2]->Clear();
						charstorage->Series[3]->Clear();
						charstorage->Series[4]->Clear();
						charstorage->Series[5]->Clear();
						for (int i = 1; i <= aqrk->RecordCount ; i++) {
						   charstorage->Series[0]->AddXY(i,aqrk->FieldByName("TotalDiscountedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[3]->AddXY(i,aqrk->FieldByName("TotalDiscountedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);

						   //charstorage->Series[1]->AddXY(i,aqrk->FieldByName("TotalDiscountedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqrk->Next();
						}
					break;
            default:
				;
			}
			/*switch (rgview->ItemIndex ) {
				case 0:
					charstorage->Series[0]->Visible = true;
					charstorage->Series[1]->Visible = true;
					charstorage->Series[2]->Visible = true;
					charstorage->Series[3]->Visible = false;
					charstorage->Series[4]->Visible = false;
					charstorage->Series[5]->Visible = false;
					break;
				case 1:
					charstorage->Series[0]->Visible = false;
					charstorage->Series[1]->Visible = false;
					charstorage->Series[2]->Visible = false;
					charstorage->Series[3]->Visible = true;
					charstorage->Series[4]->Visible = true;
					charstorage->Series[5]->Visible = true;
					break;
            default:
				;
			}   */

			sql = "select  A.Name,sum(TotalAmount) as TotalAmount,sum(TotalFixedPrice) as TotalFixedPrice,"
					" sum(TotalDiscountedPrice) as TotalDiscountedPrice from "
					" (select  DATEPART(week, HdTime) as Name,sum(BS_WsaleNoteHeader.TotalAmount) as TotalAmount,sum(BS_WsaleNoteHeader.FixedPrice) as TotalFixedPrice,sum(BS_WsaleNoteHeader.DiscountedPrice) as TotalDiscountedPrice "
					" from BS_WsaleNoteHeader "
					" where (datediff(week,BS_WsaleNoteHeader.HdTime,getdate()) < 7)";
            if (chstorage->Checked ) {
				sql = sql + " and BS_WsaleNoteHeader.Stgid = " + IntToStr(storageid);
			}
			sql = sql + " group by  DATEPART(week, HdTime) union "
			" select DATEPART(week,dateadd(week,-number,getdate())),0,0,0 "
			" from master..spt_values "
			" where type = 'P' "
			" and number between 0 and 6) as A"
			" GROUP BY A.Name order by A.Name" ;
			aqpx->Close();
			aqpx->SQL->Clear();
			aqpx->SQL->Add(sql);
			aqpx->Open();
			switch (rg2->ItemIndex ) {
				case 0:
						for (int i = 1; i <= aqpx->RecordCount ; i++) {
						   charstorage->Series[1]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   charstorage->Series[4]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);

						   //charpx->Series[1]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqpx->Next();
						}
					break;
				case 1:
						for (int i = 1; i <= aqpx->RecordCount ; i++) {
						   charstorage->Series[1]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   charstorage->Series[4]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);

						   //charpx->Series[1]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqpx->Next();
						}
					break;
				case 2:
						for (int i = 1; i <= aqpx->RecordCount ; i++) {
						   charstorage->Series[1]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   charstorage->Series[4]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);

						   //charpx->Series[1]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqpx->Next();
						}
					break;
			default:
				;
			}

			sql = "select  A.Name,sum(TotalAmount) as TotalAmount,sum(TotalFixedPrice) as TotalFixedPrice,"
					" sum(TotalDiscountedPrice) as TotalDiscountedPrice from "
					" (select  DATEPART(week, HdTime) as Name,sum(BS_RetailNoteHeader.TotalAmount) as TotalAmount,sum(BS_RetailNoteHeader.TotalFixedPrice) as TotalFixedPrice,sum(BS_RetailNoteHeader.TotalDiscountedPrice) as TotalDiscountedPrice "
					" from BS_RetailNoteHeader "
					" where (datediff(week,BS_RetailNoteHeader.HdTime,getdate()) < 7)";
            if (chstorage->Checked ) {
				sql = sql + " and BS_RetailNoteHeader.Stgid = " + IntToStr(storageid);
			}
			sql = sql + " group by  DATEPART(week, HdTime) union "
			" select DATEPART(week,dateadd(week,-number,getdate())),0,0,0 "
			" from master..spt_values "
			" where type = 'P' "
			" and number between 0 and 6) as A"
			" GROUP BY A.Name order by A.Name" ;
			aqls->Close();
			aqls->SQL->Clear();
			aqls->SQL->Add(sql);
			aqls->Open();
			switch (rg2->ItemIndex ) {
				case 0:
						for (int i = 1; i <= aqls->RecordCount ; i++) {
						   charstorage->Series[2]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
						   charstorage->Series[5]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);

						   //charls->Series[1]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqls->Next();
						}
					break;
				case 1:
						for (int i = 1; i <= aqls->RecordCount ; i++) {
						   charstorage->Series[2]->AddXY(i,aqls->FieldByName("TotalFixedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
						   charstorage->Series[5]->AddXY(i,aqls->FieldByName("TotalFixedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);

						   //charls->Series[1]->AddXY(i,aqls->FieldByName("TotalFixedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqls->Next();
						}
					break;
				case 2:
						for (int i = 1; i <= aqls->RecordCount ; i++) {
						   charstorage->Series[2]->AddXY(i,aqls->FieldByName("TotalDiscountedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
						   charstorage->Series[5]->AddXY(i,aqls->FieldByName("TotalDiscountedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);

						   //charls->Series[1]->AddXY(i,aqls->FieldByName("TotalDiscountedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqls->Next();
						}
					break;
			default:
				;
			}
			break;
		case 2:
			sql = "select  A.Name,sum(TotalAmount) as TotalAmount,sum(TotalFixedPrice) as TotalFixedPrice,"
					" sum(TotalDiscountedPrice) as TotalDiscountedPrice from "
					" (select  SubString(CONVERT(varchar(100), HdTime, 23),0,8) as Name,sum(BS_StorageNoteHeader.TotalAmount) as TotalAmount,sum(BS_StorageNoteHeader.TotalFixedPrice) as TotalFixedPrice,sum(BS_StorageNoteHeader.TotalDiscountedPrice) as TotalDiscountedPrice "
					" from BS_StorageNoteHeader "
					" where (datediff(m,BS_StorageNoteHeader.HdTime,getdate()) < 6)";
            if (chstorage->Checked ) {
				sql = sql + " and BS_StorageNoteHeader.Stgid = " + IntToStr(storageid);
			}
			sql = sql + " group by  SubString(CONVERT(varchar(100), HdTime, 23),0,8) union "
			" select SubString(CONVERT(varchar(100), dateadd(month,-number,getdate()), 23),0,8),0,0,0 "
			" from master..spt_values "
			" where type = 'P' "
			" and number between 0 and 6) as A"
			" GROUP BY A.Name order by A.Name" ;
			aqrk->Close();
			aqrk->SQL->Clear();
			aqrk->SQL->Add(sql);
			aqrk->Open();
			switch (rg2->ItemIndex ) {
				case 0:
						title = "最近半年入库数量按月统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						charstorage->Series[0]->Clear();
						charstorage->Series[1]->Clear();
						charstorage->Series[2]->Clear();
						charstorage->Series[3]->Clear();
						charstorage->Series[4]->Clear();
						charstorage->Series[5]->Clear();
						for (int i = 1; i <= aqrk->RecordCount ; i++) {
						   charstorage->Series[0]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[3]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);

						   //charstorage->Series[1]->AddXY(i,aqrk->FieldByName("TotalAmount")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqrk->Next();
						}
					break;
				case 1:
						title = "最近半年入库码洋按月统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						charstorage->Series[0]->Clear();
						charstorage->Series[1]->Clear();
						charstorage->Series[2]->Clear();
						charstorage->Series[3]->Clear();
						charstorage->Series[4]->Clear();
						charstorage->Series[5]->Clear();
						for (int i = 1; i <= aqrk->RecordCount ; i++) {
						   charstorage->Series[0]->AddXY(i,aqrk->FieldByName("TotalFixedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[3]->AddXY(i,aqrk->FieldByName("TotalFixedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
						   aqrk->Next();
						}
					break;
				case 2:
						title = "最近半年入库实洋按月统计";
						charstorage->Title->Text->Clear();
						charstorage->Title->Text->Add(title);
						charstorage->Series[0]->Clear();
						charstorage->Series[1]->Clear();
						charstorage->Series[2]->Clear();
						charstorage->Series[3]->Clear();
						charstorage->Series[4]->Clear();
						charstorage->Series[5]->Clear();
						for (int i = 1; i <= aqrk->RecordCount ; i++) {
						   charstorage->Series[0]->AddXY(i,aqrk->FieldByName("TotalDiscountedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[3]->AddXY(i,aqrk->FieldByName("TotalDiscountedPrice")->AsInteger ,aqrk->FieldByName("Name")->AsAnsiString ,clRed);
						   aqrk->Next();
						}
					break;
            default:
				;
			}
			/*switch (rgview->ItemIndex ) {
				case 0:
					charstorage->Series[0]->Visible = true;
					charstorage->Series[1]->Visible = true;
					charstorage->Series[2]->Visible = true;
					charstorage->Series[3]->Visible = false;
					charstorage->Series[4]->Visible = false;
					charstorage->Series[5]->Visible = false;
					break;
				case 1:
					charstorage->Series[0]->Visible = false;
					charstorage->Series[1]->Visible = false;
					charstorage->Series[2]->Visible = false;
					charstorage->Series[3]->Visible = true;
					charstorage->Series[4]->Visible = true;
					charstorage->Series[5]->Visible = true;
					break;
            default:
				;
			}   */

			sql = "select  A.Name,sum(TotalAmount) as TotalAmount,sum(TotalFixedPrice) as TotalFixedPrice,"
					" sum(TotalDiscountedPrice) as TotalDiscountedPrice from "
					" (select  SubString(CONVERT(varchar(100), HdTime, 23),0,8) as Name,sum(BS_WsaleNoteHeader.TotalAmount) as TotalAmount,sum(BS_WsaleNoteHeader.FixedPrice) as TotalFixedPrice,sum(BS_WsaleNoteHeader.DiscountedPrice) as TotalDiscountedPrice "
					" from BS_WsaleNoteHeader "
					" where (datediff(m,BS_WsaleNoteHeader.HdTime,getdate()) < 6)";
			if (chstorage->Checked ) {
				sql = sql + " and BS_WsaleNoteHeader.Stgid = " + IntToStr(storageid);
			}
			sql = sql + " group by  SubString(CONVERT(varchar(100), HdTime, 23),0,8) union "
			" select SubString(CONVERT(varchar(100), dateadd(month,-number,getdate()), 23),0,8),0,0,0 "
			" from master..spt_values "
			" where type = 'P' "
			" and number between 0 and 6) as A"
			" GROUP BY A.Name order by A.Name" ;
			aqpx->Close();
			aqpx->SQL->Clear();
			aqpx->SQL->Add(sql);
			aqpx->Open();
			switch (rg2->ItemIndex ) {
				case 0:
						for (int i = 1; i <= aqpx->RecordCount ; i++) {
						   //charpx->Series[0]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[1]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   charstorage->Series[4]->AddXY(i,aqpx->FieldByName("TotalAmount")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqpx->Next();
						}
					break;
				case 1:
						for (int i = 1; i <= aqpx->RecordCount ; i++) {
						   //charpx->Series[0]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[1]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   charstorage->Series[4]->AddXY(i,aqpx->FieldByName("TotalFixedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqpx->Next();
						}
					break;
				case 2:
						for (int i = 1; i <= aqpx->RecordCount ; i++) {
						   //charpx->Series[0]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[1]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   charstorage->Series[4]->AddXY(i,aqpx->FieldByName("TotalDiscountedPrice")->AsInteger ,aqpx->FieldByName("Name")->AsAnsiString ,clGreen);
						   aqpx->Next();
						}
					break;
			default:
				;
			}

			sql = "select  A.Name,sum(TotalAmount) as TotalAmount,sum(TotalFixedPrice) as TotalFixedPrice,"
					" sum(TotalDiscountedPrice) as TotalDiscountedPrice from "
					" (select  SubString(CONVERT(varchar(100), HdTime, 23),0,8) as Name,sum(BS_RetailNoteHeader.TotalAmount) as TotalAmount,sum(BS_RetailNoteHeader.TotalFixedPrice) as TotalFixedPrice,sum(BS_RetailNoteHeader.TotalDiscountedPrice) as TotalDiscountedPrice "
					" from BS_RetailNoteHeader "
					" where (datediff(m,BS_RetailNoteHeader.HdTime,getdate()) < 6)";
            if (chstorage->Checked ) {
				sql = sql + " and BS_RetailNoteHeader.Stgid = " + IntToStr(storageid);
			}
			sql = sql + " group by  SubString(CONVERT(varchar(100), HdTime, 23),0,8) union "
			" select SubString(CONVERT(varchar(100), dateadd(month,-number,getdate()), 23),0,8),0,0,0 "
			" from master..spt_values "
			" where type = 'P' "
			" and number between 0 and 6) as A"
			" GROUP BY A.Name order by A.Name" ;
			aqls->Close();
			aqls->SQL->Clear();
			aqls->SQL->Add(sql);
			aqls->Open();
			switch (rg2->ItemIndex ) {
				case 0:
						for (int i = 1; i <= aqls->RecordCount ; i++) {
						   //charls->Series[0]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[2]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
						   charstorage->Series[5]->AddXY(i,aqls->FieldByName("TotalAmount")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
						   aqls->Next();
						}
					break;
				case 1:
						for (int i = 1; i <= aqls->RecordCount ; i++) {
						   //charls->Series[0]->AddXY(i,aqls->FieldByName("TotalFixedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[2]->AddXY(i,aqls->FieldByName("TotalFixedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
						   charstorage->Series[5]->AddXY(i,aqls->FieldByName("TotalFixedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
						   aqls->Next();
						}
					break;
				case 2:
						for (int i = 1; i <= aqls->RecordCount ; i++) {
						   //charls->Series[0]->AddXY(i,aqls->FieldByName("TotalDiscountedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clRed);
						   charstorage->Series[2]->AddXY(i,aqls->FieldByName("TotalDiscountedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
						   charstorage->Series[5]->AddXY(i,aqls->FieldByName("TotalDiscountedPrice")->AsInteger ,aqls->FieldByName("Name")->AsAnsiString ,clYellow);
						   aqls->Next();
						}
					break;
			default:
				;
			}
			break;
    default:
		;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmBaobiao::rgviewClick(TObject *Sender)
{
	View();
}
//---------------------------------------------------------------------------

void TfrmBaobiao::View()
{
	switch (rgview->ItemIndex ) {
	case 0:
		if (ch1->Checked ) {
			charstorage->Series[0]->Visible = true;
		}
		else
		{
			charstorage->Series[0]->Visible = false;
		}
		if (ch2->Checked ) {
			charstorage->Series[1]->Visible = true;
		}
		else
		{
			charstorage->Series[1]->Visible = false;
		}
		if (ch3->Checked ) {
			charstorage->Series[2]->Visible = true;
		}
		else
		{
			charstorage->Series[2]->Visible = false;
		}
		charstorage->Series[3]->Visible = false;
		charstorage->Series[4]->Visible = false;
		charstorage->Series[5]->Visible = false;
		break;
	case 1:
		charstorage->Series[0]->Visible = false;
		charstorage->Series[1]->Visible = false;
		charstorage->Series[2]->Visible = false;
		if (ch1->Checked ) {
			charstorage->Series[3]->Visible = true;
		}
		else
		{
			charstorage->Series[3]->Visible = false;
		}
		if (ch2->Checked ) {
			charstorage->Series[4]->Visible = true;
		}
		else
		{
			charstorage->Series[4]->Visible = false;
		}
		if (ch3->Checked ) {
			charstorage->Series[5]->Visible = true;
		}
		else
		{
			charstorage->Series[5]->Visible = false;
		}
		break;
	default:
		;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmBaobiao::ch1Click(TObject *Sender)
{
	View();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBaobiao::ch2Click(TObject *Sender)
{
	View();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBaobiao::ch3Click(TObject *Sender)
{
	View();
}
//---------------------------------------------------------------------------

