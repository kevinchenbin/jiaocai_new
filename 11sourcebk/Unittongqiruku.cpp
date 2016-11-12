//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unittongqiruku.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "DBCtrlsEh"
#pragma link "RzEdit"
#pragma resource "*.dfm"
Tfrmtongqiruku *frmtongqiruku;
//---------------------------------------------------------------------------
__fastcall Tfrmtongqiruku::Tfrmtongqiruku(TComponent* Owner,TADOConnection *con,int stgid)
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
	sql = "select ID,Name from CUST_CustomerInfo where type = 1";
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbsupplier->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}

	sql = "select * from SYS_BSSET where name = 'xiaoshudian'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	format = "￥" + aq->FieldByName("bk")->AsString ;
	delete aq;
	dtpstart->Date = Date();
	dtpend->Date = Date();
	dg->Columns->Items[2]->DisplayFormat = format;
	dg->Columns->Items[3]->DisplayFormat = format;
	dg->Columns->Items[5]->DisplayFormat = format;
	dg->Columns->Items[6]->DisplayFormat = format;
	aq1->Connection = fcon;
	aq1->Active = false;
	aq1->Active = true;
	adosp->Connection = fcon;
	clientAll = false;
	danpingselect = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmtongqiruku::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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
void __fastcall Tfrmtongqiruku::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
    	TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		cbsupplier->Clear();
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type = 1";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while (!aq->Eof)
		{
			cbsupplier->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtongqiruku::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtongqiruku::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtongqiruku::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtongqiruku::BtnViewClick(TObject *Sender)
{
	int mode;
	AnsiString sql,sqlwhere,ClientIDstr;



	switch (rg->ItemIndex) {
		case 0:  //供应商
		  sql = "select  ID FROM CUST_CustomerInfo WHERE TYPE = 1 ";
		  if ((clientAll)||(cbsupplier->Text == "全部供应商")) {
					ClientIDstr = "-10";
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					while(!query->Eof)
					{
					   ClientIDstr = ClientIDstr + "," + query->FieldByName("ID")->AsAnsiString ;
					   query->Next();
					}
		  }else
		  {
			if (cbsupplier->ItemIndex == -1 ) {
			  MessageBoxA(NULL,"请选择供应商！","提示",MB_ICONINFORMATION);
			  return;
			}else
			{
				ClientIDstr = ClientIDstr + IntToStr((int)cbsupplier->Items->Objects[cbsupplier->ItemIndex]);
			}
		  }
			mode = 12;
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
			mode = 14;
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
		  mode = 16;

		break;
		case 3:  //单书
			 if (edname->Text == "") {
				 return;
			 }
			sql = "select ID from bs_bookcatalog where name like '%" + edname->Text + "%'" ;
			ClientIDstr = "-10";
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			while(!query->Eof)
			{
				ClientIDstr = ClientIDstr + "," + query->FieldByName("ID")->AsAnsiString ;
				query->Next();
			}

		  mode = 15;
		break;
	default:
		;
	}
				adods->Recordset = NULL;
				adosp->Active = false;
				adosp->Parameters->ParamByName("@begindate")->Value = "'"+ FormatDateTime("yyyy-MM-dd",dtpstart->Date)+"'";
				adosp->Parameters->ParamByName("@enddate")->Value =  "'"+ FormatDateTime("yyyy-MM-dd",dtpend->Date)+"'";;
				adosp->Parameters->ParamByName("@begindate1")->Value = "'"+ FormatDateTime("yyyy-MM-dd",dtpstart3->Date)+"'";
				adosp->Parameters->ParamByName("@enddate1")->Value =  "'"+ FormatDateTime("yyyy-MM-dd",dtpstart4->Date)+"'";;


				adosp->Parameters->ParamByName("@ID")->Value = ClientIDstr;
				adosp->Parameters->ParamByName("@mode")->Value = mode;
				adosp->Parameters->ParamByName("@stg")->Value = fstgid;

				try
				{
					adosp->Open();
					adods->Recordset = adosp->Recordset ;
				}catch(...)
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
				 //		dg->Columns->Items[i]->DisplayFormat ="#######0";
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

void __fastcall Tfrmtongqiruku::BitBtn1Click(TObject *Sender)
{
  int i;

  i = ((TBitBtn*)Sender)->Tag ;
  switch (i) {
		 case 0:
				rg->ItemIndex = 0;
				clientAll = true;
				cbsupplier->Text = "全部供应商";
		   break;
		 case 1:
				rg->ItemIndex = 1;
				clientAll = true;
				cbtype->Text = "全部类别";
		   break;
		 case 2:
				rg->ItemIndex = 2;
				clientAll = true;
				cpress->Text = "全部出版社";
		   break;
  default:
      ;
  }
  BtnView->Click();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtongqiruku::N1Click(TObject *Sender)
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

void __fastcall Tfrmtongqiruku::editselectMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
		if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

