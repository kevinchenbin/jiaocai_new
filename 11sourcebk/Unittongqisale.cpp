		 //---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unittongqisale.h"
#include "UnitSelectClient.h"
#include "DBGridEhImpExp.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "DBCtrlsEh"
#pragma link "RzEdit"
#pragma resource "*.dfm"
Tfrmtongqisale *frmtongqisale;
//---------------------------------------------------------------------------
__fastcall Tfrmtongqisale::Tfrmtongqisale(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
	fcon = con;
	fstgid = stgid;
	query->Connection = con;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	AnsiString sql;
	sql = "select ID,Name from BS_BookType";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbtype->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	sql = "select ID,AbbreviatedName from BS_PressInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}

	sql = "select * from SYS_BSSET where name = 'salexiaoshudian'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	format = "￥" + aq->FieldByName("bk")->AsString ;
	delete aq;
	ClientID = -1;
	//dtpstart1->Date = Date();
	dtpstart4->Date = Date();
	adosp->Connection = con;
	clientAll = false;
	danpingselect = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmtongqisale::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {   //查书
	   BtnView->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmtongqisale::spselectClientClick(TObject *Sender)
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

void Tfrmtongqisale::ClientView()
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
void __fastcall Tfrmtongqisale::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
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

void __fastcall Tfrmtongqisale::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtongqisale::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtongqisale::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtongqisale::BtnViewClick(TObject *Sender)
{
	TColumnEh  *Ecolumn;
	AnsiString ClientIDstr;
	int mode;
	AnsiString sql,sqlwhere;
	switch (rg->ItemIndex) {
		case 0:  //客户
			if (chfenji->Checked ) {
				sql = "select  ID FROM CUST_CustomerInfo WHERE TYPE in(2,3) ";
			}
			else
			{
				sql = "select  ID FROM CUST_CustomerInfo WHERE TYPE in(2) ";
			}

		  if ((clientAll)||(edtclient->Text == "全部客户")) {
					/*ClientIDstr = "-10";
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					while(!query->Eof)
					{
					   ClientIDstr = ClientIDstr + "," + query->FieldByName("ID")->AsAnsiString ;
					   query->Next();
					}*/
					ClientIDstr = "";
		  }else
		  {

			ClientIDstr = IntToStr(ClientID);
		  }


		  mode = 1;

		break;
		case 1:  //类别

			 ClientIDstr = "-1";
			 if ((clientAll)||(cbtype->Text =="全部类别")) {  //全部
				if (cbtype->Items->Count !=0) {

				   for (int i= 0; i < cbtype->Items->Count; i++) {
					 ClientIDstr = ClientIDstr+ "," + IntToStr((int)cbtype->Items->Objects[i]);
				   }

				}


			 }else
			 {
			  if (cbtype->Items->Count !=0) {
					   ClientIDstr = ClientIDstr+ "," + IntToStr((int)cbtype->Items->Objects[cbtype->ItemIndex]);
				   }
			  }
		   mode = 4;
		break;
		case 2:  //出版社
			 ClientIDstr = "-10";
			   if ((clientAll)||(cpress->Text =="全部出版社")) {
				  if (cpress->Items->Count !=0) {
					  for (int i =0 ; i < cpress->Items->Count; i++) {
						 ClientIDstr = ClientIDstr+ "," + IntToStr((int)cpress->Items->Objects[i]);
					  }
				  }
			   }else
			   {
					if (cpress->ItemIndex !=-1) {
					  ClientIDstr = ClientIDstr+"," + IntToStr((int)cpress->Items->Objects[cpress->ItemIndex]);
					}
				}
				mode = 5;
		break;
		case 3:  //单书

			ClientIDstr = "-10";

		  if (edname->Text != "") {
		  switch (danpingselect) {
				 case 0:
					  sql = "select id FROM dbo.BS_BookCatalog where barcode like '%"+edname->Text.Trim()+"%'";
				  break;
				 case 1:
					   sql = "select id FROM dbo.BS_BookCatalog where name like '%"+edname->Text.Trim()+"%'";
				  break;
				 case 2:
					   sql = "select id FROM dbo.BS_BookCatalog where userdefcode like '%"+edname->Text.Trim()+"%'";
				 break;
				  case 3:
					  sql = "select id FROM dbo.BS_BookCatalog where price ="+edname->Text.Trim();
					  break;
				  case 4:
					   sql = "select id FROM dbo.BS_BookCatalog where author like '%"+edname->Text.Trim()+"%'";
					   break;
		  default:
			  ;
		  }
          }
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();

			while(!query->Eof)
			{
			   ClientIDstr = ClientIDstr + "," + query->FieldByName("ID")->AsAnsiString ;
			   query->Next();
			}
			mode = 3;

		break;
	default:
		;
	}
				adods->Recordset = NULL;
				adosp->Active = false;
				adosp->Parameters->ParamByName("@begindate")->Value = "'"+ FormatDateTime("yyyy-MM-dd",dtpstart1->Date)+"'";
				adosp->Parameters->ParamByName("@enddate")->Value =  "'"+ FormatDateTime("yyyy-MM-dd",dtpstart2->Date)+"'";;

				adosp->Parameters->ParamByName("@begindate1")->Value = "'"+ FormatDateTime("yyyy-MM-dd",dtpstart3->Date)+"'";
				adosp->Parameters->ParamByName("@enddate1")->Value =  "'"+ FormatDateTime("yyyy-MM-dd",dtpstart4->Date)+"'";;


				adosp->Parameters->ParamByName("@ID")->Value = ClientIDstr;
				adosp->Parameters->ParamByName("@mode")->Value = mode;
				adosp->Parameters->ParamByName("@stg")->Value = fstgid;
				if (chfenji->Checked ) {
					adosp->Parameters->ParamByName("@fenji")->Value = 1;
				}
				else
				{
					adosp->Parameters->ParamByName("@fenji")->Value = 0;
				}
				try
				{
					//adods->re
					adosp->Open() ;
					adods->Recordset = adosp->Recordset ;
				  }
				  catch(...)
				  {
					clientAll = false;
					return;
				  }



				dg->DataSource->DataSet->DisableControls();
				for (int i=0; i < adods->Fields->Count ; i++) {
				dg->Columns->Items[i]->FieldName = adods->Fields->Fields[i]->FieldName;
				dg->Columns->Items[i]->Title->Caption = adods->Fields->Fields[i]->FieldName;
				dg->Columns->Items[i]->Width = 50;

				if (i == 0) {
				}else
				{
				  switch (i) {
						case 1:
						case 2:
						case 4:
						case 5:
						case 8:
						case 9:
						case 11:
						case 12:
						case 15:
						case 17:
						dg->Columns->Items[i]->DisplayFormat = format;
					   //	dg->Columns->Items[i]->Footer->DisplayFormat = format;
					  //	dg->Columns->Items[i]->Footer->ValueType =fvtSum ;
						break;
						case 7:
						case 14:
						case 16:
						case 18:
						case 20:
						case 22:                      //百分号
							dg->Columns->Items[i]->DisplayFormat = "0.00%";
						break;
						case 3:
						case 6:
						case 10:
						case 13:
						 //	 dg->Columns->Items[i]->Footer->DisplayFormat = format;
						 //	 dg->Columns->Items[i]->Footer->ValueType =fvtSum ;
							 break;
				  default:

					  ;
				  }
			   }
			   adods->Next();
			  }
			 dg->DataSource->DataSet->EnableControls() ;
			 clientAll = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmtongqisale::Button1Click(TObject *Sender)
{
  rg->ItemIndex = 0;
  clientAll = true;
  edtclient->Text = "全部客户";
  BtnView->Click();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmtongqisale::alltypeClick(TObject *Sender)
{
  rg->ItemIndex = 1;
  clientAll = true;
  cbtype->Text = "全部类别";
  BtnView->Click();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtongqisale::Button2Click(TObject *Sender)
{
   rg->ItemIndex = 2;
  clientAll = true;
  cbtype->Text = "全部出版社";
  BtnView->Click();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmtongqisale::BtnExportClick(TObject *Sender)
{
 AnsiString filename;
   if (savefile->Execute() ) {
	   filename = savefile->FileName ;

	 dg->Selection->SelectAll();
	   SaveDBGridEhToExportFile(__classid(TDBGridEhExportAsHTML),dg ,filename,true);
	  dg->Selection->Clear();
   }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmtongqisale::N1Click(TObject *Sender)
{
  int clickint;
  clickint = ((TMenuItem*)(Sender))->Tag ;
  danpingselect = clickint;
  switch (clickint) {
	  case 0:
			editselect->Text = "书号";
			break;
	  case 1:
			editselect->Text = "书名";
			break;
	  case 2:
			editselect->Text = "自编码";
			break;
	  case 3:
			editselect->Text = "定价";
			break;
	  case 4:
			editselect->Text = "作者";
			break;
  default:
	  ;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtongqisale::editselectMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtongqisale::dgTitleClick(TColumnEh *Column)
{
	 if (Column->Title->SortMarker == smUpEh) {
  //  TCustomADODataSet TDGridEh)->
	 //  TCustomADODataSet(TDGridEh(*Sender)->DataSource->DataSet)->Sort = Column->FieldName + " ASC";

	// adods->Sort = Column->FieldName + " ASC";
   }else if (Column->Title->SortMarker == smDownEh) {
	//   adods->Sort = Column->FieldName + " DESC";
	//   dg->DataSource
		 }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtongqisale::Button3Click(TObject *Sender)
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

