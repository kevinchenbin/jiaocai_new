//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CatalogAdminForm.h"
#include "catalogadmin.h"
#include "PressAdminForm.h"
#include "pdutil.h"
#include "catalogadmin.h"
#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include "MDIChild.h"
#include "ExcelImport.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "MDIChild"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma link "RzDBChk"
#pragma link "RzRadChk"
#pragma link "RzCmboBx"
#pragma link "RzRadGrp"
#pragma link "RzLine"
#pragma link "RzDBCmbo"
#pragma link "RzShellDialogs"
#pragma link "RzSpnEdt"
#pragma link "RzDBDTP"
#pragma link "RzDTP"
#pragma link "RzCommon"
#pragma link "RzLookup"
#pragma link "RzDBLook"
#pragma link "RzDBSpin"
#pragma resource "*.dfm"
TfrmCatalogAdmin *frmCatalogAdmin;
//---------------------------------------------------------------------------
__fastcall TfrmCatalogAdmin::TfrmCatalogAdmin(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	m_module = MTBkcatalog;
	this->WindowState = wsMaximized ;
	
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogAdmin::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------



void __fastcall TfrmCatalogAdmin::btnAddClick(TObject *Sender)
{
	dsetCatlog->Append();
	dsetCatlog->Edit();
	dsetCatlog->FieldByName("bigBookTypeID")->Value = 1;
	//DataSource ->DataSet ->Edit();
	//DataSource ->DataSet ->FieldByName("ISBN")->Value = t1;

}
//---------------------------------------------------------------------------

void TfrmCatalogAdmin::Init(TApplication* app, TADOConnection* con)
{
		TfrmMDIChild::Init(app, con);
	dsetCatlog->Connection = m_con;
	tblPress->Connection = m_con;
	qryPressQuery->Connection = m_con;
	dsetDeleteCatlog->Connection = m_con;
	tblCatalogType->Connection = m_con;
	qryPressQuery->Active = true;
	//dsetCatlog->Active = true;
	tblCatalogType->Active = true;
	tblPress->Active = true;
	dbdtmpckrDate->Date = Date();
	edtPressCount->Value = 1;
	edtQuery->SetFocus();

//	tblPress->Active = true;
//	dsetCatlog->Active = true;

		//dsetCatlog->CommandText = "select * from BS_BookCatalog";
	//dsetCatlog->Active = true;
	//dsetCatlog->First();
	 //BtnNew->Click();
	 manybook = false;
}


void __fastcall TfrmCatalogAdmin::btnExcelExportClick(TObject *Sender)
{
	//DataSetToExcel(dbgrdPress,1);
}
//---------------------------------------------------------------------------



void __fastcall TfrmCatalogAdmin::btnPressAddClick(TObject *Sender)
{
	//ManagePress(TApplication* app, TADOConnection* con)
	//frmPressAdmin->Visible = true;// Active ;//= true;
	//frmPressAdmin->Show();//  Show();//  TfrmPressAdminForm->Show();
	String PressName;
	int id = SelectPress(m_app, m_con, this,PressName);

	qryPressQuery->Active = false;
	qryPressQuery->Active = true;

   //	cbbPressID->DataSource->DataSet->FieldByName("AbbreviatedName")->AsAnsiString = PressName;


	//ShowMessage(IntToStr(id));
}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogAdmin::edtQueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key==VK_RETURN) {
		manybook = false;
		editbookname->Visible = false;
		dbedtName->Visible = true;

		editprice->Visible = false;
		dbedtPrice->Visible = true;
		editauthor->Visible = false;
		dbedtAuthor->Visible = true;
				Query(edtQuery->Text);
		 }
}
//---------------------------------------------------------------------------
int TfrmCatalogAdmin::Query1(String condition)
{
   if (dsetCatlog->Active)
	{
		dsetCatlog->Active = false;
	}

	String sql;
	sql = "select * from UV_PressAndBookCatalogQuery where Barcode like '%" + condition + "%'";
	//sql = "select BS_PressInfo.AbbreviatedName,BS_BookCatalog.ID, BS_BookCatalog.ISBN, BS_BookCatalog.Name, BS_BookCatalog.Price, BS_BookCatalog.Barcode, BS_BookCatalog.UserDefCode, BS_BookCatalog.PressID, BS_BookCatalog.Date, BS_BookCatalog.Author, BS_BookCatalog.PressCount, BS_BookCatalog.Unavailable, BS_BookCatalog.bigBookTypeID, BS_BookCatalog.smallBookTypeID, BS_BookCatalog.TotalAmount, BS_BookCatalog.BkstackID,BS_PressInfo. PresentNum from BS_BookCatalog,BS_PressInfo where BS_PressInfo.PresentNum=BS_BookCatalog.PressID and Barcode like '%" + condition + "%'";
	//"select * from BS_BookCatalog where Barcode like '%" + condition + "%'";
	dsetCatlog->CommandText = sql;
	dsetCatlog->Active = true;
	if(dsetCatlog->RecordCount != 0)
	return 1;
	else return 0;
//	if(dsetCatlog->RecordCount == 0)
//	ShowMessage("hhh");
//	else ShowMessage("xxx"); //DataSource ->DataSet ->First()  //irst();
//	if(dsetCatlog->DataSource ->DataSet ->RecordCount == 0)// ->FieldByName("Barcode")->AsString == "")
//	{
//
//	}
//	else ShowMessage("ju");

}
void TfrmCatalogAdmin::Query(String condition)
{
	if (dsetCatlog->Active)
	{
		dsetCatlog->Active = false;
	}

	String sql;
	if(cbQueryType->Value == 1)
	{
		//condition.SubString()
//		for(int i=1;i<condition.Length();i++ )
//		if(condition.SubString(i,1))
//		continue;
		if(condition.Length() != 13 )
		{
			ShowMessage("位数不正确！");
			return;
		}
		for(int i=1;i<condition.Length();i++ )
		if(condition.SubString(i,1)>='0'&&condition.SubString(i,1)<='9'  )
		continue;
		else
		{
			ShowMessage("请输入数字！");
			return;
		}
		sql = "select * from UV_PressAndBookCatalogQuery where Barcode like '%" + condition + "%'";

		//sql = "select * from BS_PressInfo where PresentNum = 1";
		//sql = "select BS_PressInfo.AbbreviatedName,BS_BookCatalog.ID, BS_BookCatalog.ISBN, BS_BookCatalog.Name, BS_BookCatalog.Price, BS_BookCatalog.Barcode, BS_BookCatalog.UserDefCode, BS_BookCatalog.PressID, BS_BookCatalog.Date, BS_BookCatalog.Author, BS_BookCatalog.PressCount, BS_BookCatalog.Unavailable, BS_BookCatalog.bigBookTypeID, BS_BookCatalog.smallBookTypeID, BS_BookCatalog.TotalAmount, BS_BookCatalog.BkstackID,BS_PressInfo. PresentNum from BS_BookCatalog,BS_PressInfo where BS_PressInfo.PresentNum=BS_BookCatalog.PressID and Barcode like '%" + condition + "%'";
	//sql = "select * from BS_BookCatalog where Barcode = " + condition;
	}
	else if(cbQueryType->Value == 2)
	{
		int i = condition.Length();
		if(i!=13)
		if(i!=10 )
		{
			ShowMessage("查询位数不正确！");
			return;
		}
		for(int i=1;i<condition.Length();i++ )
		if(condition.SubString(i,1)>='0'&&condition.SubString(i,1)<='9'  )
		continue;
		else
		{
			ShowMessage("请输入数字！");
			return;
		}
		sql = "select * from UV_PressAndBookCatalogQuery where ISBN like '%" + condition + "%'";
		//sql = "select * from BS_BookCatalog where ISBN like '%" + condition + "%'";
	}
	else if(cbQueryType->Value == 3)
	{
		//sql = "select BS_PressInfo.AbbreviatedName,BS_BookCatalog.ID, BS_BookCatalog.ISBN, BS_BookCatalog.Name, BS_BookCatalog.Price, BS_BookCatalog.Barcode, BS_BookCatalog.UserDefCode, BS_BookCatalog.PressID, BS_BookCatalog.Date, BS_BookCatalog.Author, BS_BookCatalog.PressCount, BS_BookCatalog.Unavailable, BS_BookCatalog.bigBookTypeID, BS_BookCatalog.smallBookTypeID, BS_BookCatalog.TotalAmount, BS_BookCatalog.BkstackID,BS_PressInfo. PresentNum from BS_BookCatalog,BS_PressInfo where BS_PressInfo.PresentNum=BS_BookCatalog.PressID and UserDefCode like '%" + condition + "%'";
		for(int i=1;i<condition.Length();i++ )
		if(condition.SubString(i,1)>='a'&&condition.SubString(i,1)<='z'||condition.SubString(i,1)>='A'&&condition.SubString(i,1)<='Z'    )
		continue;
		else
		{
			ShowMessage("请输入正确的自编码！");
			return;
		}
		sql = "select * from UV_PressAndBookCatalogQuery where UserDefCode like '%" + condition + "%'";
		//sql = "select * from BS_BookCatalog where UserDefCode like '%" + condition + "%'";
	}
	else if(cbQueryType->Value == 4)
	{
		//sql = "select BS_PressInfo.AbbreviatedName,BS_BookCatalog.ID, BS_BookCatalog.ISBN, BS_BookCatalog.Name, BS_BookCatalog.Price, BS_BookCatalog.Barcode, BS_BookCatalog.UserDefCode, BS_BookCatalog.PressID, BS_BookCatalog.Date, BS_BookCatalog.Author, BS_BookCatalog.PressCount, BS_BookCatalog.Unavailable, BS_BookCatalog.bigBookTypeID, BS_BookCatalog.smallBookTypeID, BS_BookCatalog.TotalAmount, BS_BookCatalog.BkstackID,BS_PressInfo. PresentNum from BS_BookCatalog,BS_PressInfo where BS_PressInfo.PresentNum=BS_BookCatalog.PressID and Name like '%" + condition + "%'";
		sql = "select * from UV_PressAndBookCatalogQuery where Name like '%" + condition + "%'";
		//sql = "select * from BS_BookCatalog where Name like '%" + condition + "%'";
	}
	//String sql2 ;
	//sql2 = "select FullName from BS_PressInfo where PresentNum=BS_BookCatalog.PressID" ;
	dsetCatlog->CommandText = sql;
	//dsetCatlog->CommandText  ->CommandText->

	dsetCatlog->Active = true;
	//edtPressID->Text = sql2;
}

void __fastcall TfrmCatalogAdmin::btnRemoveClick(TObject *Sender)
{
	if(!dsetCatlog->IsEmpty())
	{
		dsetCatlog->Delete();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogAdmin::RzRadioGroup1Click(TObject *Sender)
{   //
	if(RzRadioGroup1->ItemIndex ==0)
	{
		 //if (dsetCatlog->Active)
		//{
			dsetCatlog->Active = false;
		//}
	   //	ShowMessage("hello");
		//String sql;
		//sql = "select * from BS_BookCatalog";
		//dsetCatlog->CommandText = sql;
		//dsetCatlog->Active = true;
	}
	if(RzRadioGroup1->ItemIndex ==1)
	{
		 if (dsetCatlog->Active)
		{
			dsetCatlog->Active = false;
		}
	   //	ShowMessage("hello");
		String sql;
	   //	sql = "select BS_PressInfo.AbbreviatedName,BS_BookCatalog.ID, BS_BookCatalog.ISBN, BS_BookCatalog.Name, BS_BookCatalog.Price, BS_BookCatalog.Barcode, BS_BookCatalog.UserDefCode, BS_BookCatalog.PressID, BS_BookCatalog.Date, BS_BookCatalog.Author, BS_BookCatalog.PressCount, BS_BookCatalog.Unavailable, BS_BookCatalog.bigBookTypeID, BS_BookCatalog.smallBookTypeID, BS_BookCatalog.TotalAmount, BS_BookCatalog.BkstackID,BS_PressInfo. PresentNum from BS_BookCatalog,BS_PressInfo  "; //where BS_PressInfo.PresentNum=BS_BookCatalog.PressID// select * from BS_BookCatalog
		sql = "select * from UV_PressAndBookCatalogQuery ";
		dsetCatlog->CommandText = sql;
		dsetCatlog->Active = true;
	}
	else if(RzRadioGroup1->ItemIndex ==2)
	{
		 if (dsetCatlog->Active)
		{
			dsetCatlog->Active = false;
		}
		//ShowMessage("hello");
		String sql;
		//sql = "select BS_PressInfo.AbbreviatedName,BS_BookCatalog.ID, BS_BookCatalog.ISBN, BS_BookCatalog.Name, BS_BookCatalog.Price, BS_BookCatalog.Barcode, BS_BookCatalog.UserDefCode, BS_BookCatalog.PressID, BS_BookCatalog.Date, BS_BookCatalog.Author, BS_BookCatalog.PressCount, BS_BookCatalog.Unavailable, BS_BookCatalog.bigBookTypeID, BS_BookCatalog.smallBookTypeID, BS_BookCatalog.TotalAmount, BS_BookCatalog.BkstackID,BS_PressInfo. PresentNum from BS_BookCatalog,BS_PressInfo where  Unavailable = 0"; //BS_PressInfo.PresentNum=BS_BookCatalog.PressID and
		sql = "select * from UV_PressAndBookCatalogQuery where Unavailable = 0";
		dsetCatlog->CommandText = sql;
		dsetCatlog->Active = true;
	}
	else if(RzRadioGroup1->ItemIndex ==3)
	{
		 if (dsetCatlog->Active)
		{
			dsetCatlog->Active = false;
		}
		//ShowMessage("hello");
		String sql;
		//sql = "select BS_PressInfo.AbbreviatedName,BS_BookCatalog.ID, BS_BookCatalog.ISBN, BS_BookCatalog.Name, BS_BookCatalog.Price, BS_BookCatalog.Barcode, BS_BookCatalog.UserDefCode, BS_BookCatalog.PressID, BS_BookCatalog.Date, BS_BookCatalog.Author, BS_BookCatalog.PressCount, BS_BookCatalog.Unavailable, BS_BookCatalog.bigBookTypeID, BS_BookCatalog.smallBookTypeID, BS_BookCatalog.TotalAmount, BS_BookCatalog.BkstackID,BS_PressInfo. PresentNum from BS_BookCatalog,BS_PressInfo where Unavailable = 1"; //BS_PressInfo.PresentNum=BS_BookCatalog.PressID and
		sql = "select * from UV_PressAndBookCatalogQuery where Unavailable = 1" ;
		dsetCatlog->CommandText = sql;
		dsetCatlog->Active = true;

	}
}
//---------------------------------------------------------------------------




void __fastcall TfrmCatalogAdmin::edtPriceClick(TObject *Sender)
{
   //RzDBNumericEdit1->
}
//---------------------------------------------------------------------------




void __fastcall TfrmCatalogAdmin::Button1Click(TObject *Sender)
{
	String PressName ;
	int id = SelectPress(m_app, m_con, this,PressName);
	//ShowMessage(IntToStr(id));
	cbbsmallBookTypeID->DataSource->DataSet->FieldByName("smallBookTypeID")->AsAnsiString = id  ;

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::cbb1Click(TObject *Sender)
{
   //	while(!)
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::btn1Click(TObject *Sender)
{
	int id = SelectBookType(m_app, m_con, this);

}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::btn2Click(TObject *Sender)
{
	if (dsetCatlog->State == dsInsert)
	if(edtBarcode->Text == "")
	{
        ShowMessage("错误，条码为空！");
	}
	else
	{
		dbedtISBN->DataSource ->DataSet ->FieldByName("ISBN")->Value =  BuildISBNCode(edtBarcode->Text  );
	//IsbnCount(edtBarcode->Text);
	dbedtName->SetFocus();
	}
	//k=StringToIsbn(edtBarcode->Text,rs) ;
	//ShowMessage(k);
	//int j = IsbnCount(i);

	//ShowMessage(j);
}
//---------------------------------------------------------------------------
void TfrmCatalogAdmin::DBGrid2Excel(TDBGrid *dbg,String strXlsFile)
{
}

//---------------------------------------------------------------------------
int TfrmCatalogAdmin::IsbnCount(String ss)
{
		//long int i = StrToInt64(edtBarcode->Text );
   //	long i = StrToInt64(9788175257665);

   String t;
   int i,k,rs[9];
   t="hello" ;
   //ShowMessage(t);
   k = StringToIsbn(ss,rs);
   String t1;
   for(i=0;i<9;i++)
   t1 = t1 + IntToStr(rs[i]);
   ShowMessage(t1);
   ShowMessage(k);
   //k=345;
   if(k==345)
   {
		t1 = t1+"x";
		dbedtISBN->DataSource ->DataSet ->Edit();
		dbedtISBN->DataSource ->DataSet ->FieldByName("ISBN")->Value = t1;
   }
   else
   {
		t1 = t1 + IntToStr(k);
		dbedtISBN->DataSource ->DataSet ->Edit();
		dbedtISBN->DataSource ->DataSet ->FieldByName("ISBN")->Value = t1;
		//dbedtISBN->Text = t1;//IntToStr(rs[i]);
   }

}

int TfrmCatalogAdmin::StringToIsbn(String str,int rs[])
{
	String str1;
	str1=str;
	int t,s=0;
	int k,a=9;
	k = str.Length();
	//ShowMessage(k);
	for(int i=0;i<k;i++)
	{
		String c;
		// 得到最后一个字符
		c = str.LastChar();
		t = StrToInt(c);
		if(i>0&&i<10)
		{
		//按规则计算isbn代码和
			s = s + t*a--;
		//得到isbn前9位数字
			rs[9-i] = t;
			//ShowMessage(rs[9-i]);
		}
		str.Delete(str.Length(),1 );
	}
	//获取isbn最后一位数字
	a = s%11;
	if(a==10)
	return 345;
	else
	return a;
}



void __fastcall TfrmCatalogAdmin::edtBarcodeKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key==VK_RETURN) //
	{
		//edtPress->Text = "";
		if(chckbxModify->Checked )
		{
			dbedtName->SetFocus();
		}
		else
		{
			String s,ss3;
			s = edtBarcode->Text ;
			if(s.Length() == 0 )
			dbedtISBN->SetFocus();
			else
			if(s.Length()<13&&s.Length()>0 )
			{
				ShowMessage("请输入正确的条码!!");
				edtBarcode->SetFocus();
			}
			else if(s.Length()==13 )
			{
				String ss;


				ss = edtBarcode->Text ;

				for(int i=3;i<=6;i++)
				{
					int j;
					String ss1 = ss.SubString(4,i);
					dbgrdPressQuery->DataSource ->DataSet ->RecNo = 1;
					for(j=1;j<=dbgrdPressQuery->DataSource ->DataSet ->RecordCount ;j++)
					{
						ss1 = ss.SubString(4,i);
						String  ss2; // ,ss3
						ss2 = dbgrdPressQuery->DataSource ->DataSet ->FieldByName("PresentNum")->Value ;
						for(int k=1;k<=6-i;k++)
						ss1 = ss1 + " ";

						if(ss1 == ss2 )
						{
							ss3 = dbgrdPressQuery->DataSource ->DataSet ->FieldByName("AbbreviatedName")->Value ;
							edtPress->Text = ss3;
							dsetCatlog->Active = true;
							//cbbPressID->GetListValue()  = edtPress->Text ;
							//cbbPressID->GetKeyValue() = dbgrdPressQuery->DataSource ->DataSet ->FieldByName("ID")->Value;// KeyValue
							//cbbPressID->  dbgrdPressQuery->DataSource ->DataSet ->FieldByName("ID")->Value ;
							//dsetCatlog->Edit();
							//dsetCatlog->FieldByName("PressID")->Value = dbgrdPressQuery->DataSource ->DataSet ->FieldByName("ID")->Value ;
							//dsetCatlog->Active = false;
							break;
						}
						dbgrdPressQuery->DataSource ->DataSet ->RecNo ++  ;
					}
					if(j<dbgrdPressQuery->DataSource ->DataSet ->RecordCount )
					break;
				}
				//dblkpdlg1->Execute();

			//lkpdlgCatlog->Execute();
			//dsetCatlog-> Active ;
			//if(dsetCatlog->FieldByName("Barcode")-> Value == "")
			//ShowMessage("ok");
			///int i=dsetCatlog->DataSource ->DataSet -> RecNo  ;
			//if(i == 0)
		   //	{
			//}
			//else ShowMessage("hellohello");
				int q = Query1(edtBarcode->Text );
				if(q != 0)
				{
				   manybook = true;


				   editbookname->Visible = true;
				   dbedtName->Visible = false;

				   editprice->Visible = true;
				   dbedtPrice->Visible = false;
				   editauthor->Visible = true;
				   dbedtAuthor->Visible = false;
				   editbookname->SetFocus();
				  /*	if(dblkpdlg1 -> Execute() )   //lkpdlgCatlog
					{
						dbgrdCatlog->DataSource ->DataSet ->RecNo = dbgrdCatlog->DataSource ->DataSet ->RecordCount ;// SelectedRows->Count;
						String s1,s2,s3,s4,s6,s8;
						int s5 = -1,pressID = -1;
						TDateTime s7;
						s1 = edtBarcode->Text ;
						s2 = dbedtName->Text ;
						s3 = dbedtPrice->Text ;
						s4 = dbedtAuthor->Text ;
						if(!cbbsmallBookTypeID->DataSource ->DataSet ->FieldByName("smallBookTypeID") ->Value.IsNull() )
							s5 = cbbsmallBookTypeID->DataSource->DataSet->FieldByName("smallBookTypeID")->AsInteger;//cbbsmallBookTypeID->Text ;
						if (!cbbPressID->DataSource ->DataSet ->FieldByName("PressID")->Value.IsNull())
							pressID = cbbPressID->DataSource ->DataSet ->FieldByName("PressID")->AsInteger;
						//s6 = ss3;//cbbPressID->DataSource ->DataSet ->FieldByName("PressID")->Value ;
						s7 = dbdtmpckrDate->DataSource ->DataSet ->FieldByName("Date")->AsDateTime  ;
						s8 = edtPressCount->Text ;
						dsetCatlog->Append();
						edtBarcode->DataSource ->DataSet ->FieldByName("Barcode")->Value = s1;
						dbedtISBN->DataSource ->DataSet ->FieldByName("ISBN")->Value = s1;//edtBarcode->DataSource ->DataSet ->FieldByName("Barcode")->Value ;
					   //	dbedtPrice->DataSource ->DataSet ->FieldByName("Price")->Value = dbedtPrice->DataSource ->DataSet ->FieldByName("")
						dbedtName->DataSource ->DataSet ->FieldByName("Name")->Value = s2;
						dbedtPrice->DataSource ->DataSet ->FieldByName("Price")->Value = s3;
						dbedtAuthor->DataSource ->DataSet ->FieldByName("Author")->Value = s4;
						if (s5 > 0)
						{
							cbbsmallBookTypeID->DataSource ->DataSet ->FieldByName("smallBookTypeID") ->AsInteger = s5;//StrToInt(s5);
						}
						if (pressID > 0)
						{
							cbbPressID->DataSource ->DataSet ->FieldByName("PressID")->AsInteger = pressID;
						}
						//cbbPressID->DataSource ->DataSet ->FieldByName("PressID")->Value = s6;
						//dsetCatlog->FieldByName("PressID")->Value = ss3;
						dbdtmpckrDate->DataSource ->DataSet ->FieldByName("Date")->Value = s7;
						edtPressCount->IntValue = 1;
						dbedtName->SetFocus();

					} */
				}
				else
				{
					manybook = false;
					editbookname->Visible = false;
					dbedtName->Visible = true;

					editprice->Visible = false;
					dbedtPrice->Visible = true;
					editauthor->Visible = false;
					dbedtAuthor->Visible = true;

					if(dsetCatlog->State == dsInsert )
					{}
					else
					{
						try
						{
							dsetCatlog->Append();
						}
						catch(...)
						{
							if(edtBarcode->Text == "")
							ShowMessage("条码为空，请添加！");
							if(dbedtISBN->Text == "")
							ShowMessage("ISBN为空，请添加！");
							if(dbedtName->Text == "")
							ShowMessage("书名为空，请添加！");
							if(dbedtPrice->Text == "")
							ShowMessage("定价为空，请添加！");

						}
					}
					edtBarcode->DataSource ->DataSet ->FieldByName("Barcode")->Value = s;
					dbedtISBN->DataSource ->DataSet ->FieldByName("ISBN")->Value = edtBarcode->DataSource ->DataSet ->FieldByName("Barcode")->Value ;
					if(ss3 != "")
					//dsetCatlog->FieldByName("PressID")->Value = ss3;//dbgrdPressQuery->DataSource ->DataSet ->FieldByName("ID")->Value ;
					//cbbPressID->DataSource ->DataSet ->FieldByName("PressID")->Value = ss3;
					dsetCatlog->FieldByName("PressID")->Value =  dbgrdPressQuery->DataSource ->DataSet ->FieldByName("ID")->Value;
					dbedtISBN->SetFocus();
				}

			}
	   }
	}

}
		//if(lkpdlgCatlog->Execute() )
		//{
		//dsetCatlog->Append();
		//edtBarcode->SetFocus();
		//if(dblkpdlgCatlog ->Execute()  )
		//{
		 //	 if (dsetCatlog->Active)
		//	{
		//		dsetCatlog->Append();
		//	}

		//}
	   //	edtBarcode->DataSource ->DataSet ->FieldByName("Barcode")->Value = s;
		//dbedtISBN->DataSource ->DataSet ->FieldByName("ISBN")->Value = edtBarcode->DataSource ->DataSet ->FieldByName("Barcode")->Value ;
		//dbedtName->SetFocus();

		//}
		//else
	   //	{
		//dsetCatlog->Append();
		//QueryNull();
	   //	edtBarcode->SetFocus();
	   //	}

		//}
		//else
		//dbedtISBN->SetFocus();


//---------------------------------------------------------------------------

void TfrmCatalogAdmin::QueryNull()
{
    if (dsetCatlog->Active)
	{
		dsetCatlog->Active = false;
	}
		//ShowMessage("hello");
	String sql;
	sql = "select * from BS_BookCatalog where ID = 0";
	dsetCatlog->CommandText = sql;
	dsetCatlog->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::btnExit2Click(TObject *Sender)
{
if(dbedtISBN->Text == "")
return;
  if (MessageBox(0,"确认要删除吗？","图书品目管理",MB_ICONQUESTION|MB_OKCANCEL)==2) {
  return;

  }
if(!dsetCatlog->IsEmpty())
	{   try
		{
		dsetCatlog->RecNo;
		//dsetDeleteCatlog->FieldByName("ID")->Value = dsetCatlog->FieldByName("ID")->Value ;
		dsetDeleteCatlog->Active = true;
		dsetDeleteCatlog->Delete();
		}
		catch(Exception &e)
		{
			MessageBox(0,"不能删除，有相关引用","图书品目管理",MB_ICONWARNING);
        }
	}
	BtnNew->Click();
}
//---------------------------------------------------------------------------




void __fastcall TfrmCatalogAdmin::btnExit3Click(TObject *Sender)
{
   if (dsetCatlog->Active && dsetCatlog->RecordCount > 0) {
		DbgridToExcel(dbgrdCatlog);
   }


}
//Excel导出函数
bool __fastcall TfrmCatalogAdmin::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		MessageBox(0,"没有数据！","错误确认" ,MB_OK);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	v.OlePropertyGet("Cells",1,6).OlePropertySet("Value","图书品目管理" );
	n = 1;

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
		}
	}

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}

	return false;

}
//---------------------------------------------------------------------------
String TfrmCatalogAdmin::FirstLetterFromHZ(String  strKey)
{}

  char   TfrmCatalogAdmin::getpy(String   hzchar)
{}
void __fastcall TfrmCatalogAdmin::dbedtNameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN) //
	{
		  if (editbookname->Visible) {
		  if (editbookname->Text == "") {
			  MessageBoxA(0,"书名是必录项，请添加！","提示",MB_ICONWARNING);
			  	if (dbedtPrice->Visible) {
			  dbedtName->SetFocus();
			  return;
			} else
			{
			  editbookname->SetFocus();
			  return;
			}
		  }
		  else
		  {
			dbedtName->Text =  editbookname->Text;
		  }
	  }



		if(dbedtName->Text == "")
		{
			ShowMsg("书名是必录项!","图书品目管理",0);
			if (dbedtName->Visible) {
			 dbedtName->SetFocus();
			}else
			{
			   editbookname->SetFocus();
			}

		}
		//RzDBEdit4->SetFocus();
		else
		{


		dbedtUserDefCode->DataSource ->DataSet ->Edit();

		//String s1,s;
		//s=FirstLetterFromHZ(dbedtName->Text );
		//s = getpy(dbedtName->Text);
		//s1 = FirstLetterFromHZ(dbedtName->Text );
		//ShowMessage(s);
		//ShowMessage(FirstLetterFromHZ("好"));
		//RzDBEdit4->DataSource ->DataSet ->FieldByName("UserDefCode")->Value = s;//getpy(dbedtName->Text);//FirstLetterFromHZ(dbedtName->Text );//RzDBEdit3->DataSource ->DataSet ->FieldByName("Name")->Value ;
		char* t;
		char t2;
		String t1,t3,t4;
		t1 = dbedtName->Text;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;
		int t5=1,i = dbedtName->Text.Length() ;
		for( int j=1;j<=i;j++)
		{
			//if (j == 9) break;
			t3 = t1.SubString(j,1);
			t = t3.t_str();
			//if(t3 < 160) continue;
			Word k = int (t[0])<<8;
			k = k >> 8;
			if(k<160) continue;
			//if(int(t[0])< 160) continue;
			//if (t3 >= 'a' && t3 <= 'z' || t3 >= 'A' && t3 <= 'Z'|| t3 >= 0 && t3 <= 9||t3 == '!'||t3 == '@'||t3=='#'||t3=='$'||t3=='%') continue;
			t5++;
			if (t5 == 9) break;
			t = t3.t_str();
			t2 = GetPYIndexChar(t);
			t4 = t4 + t2;
			//ShowMessage(t2);
		}
		dbedtUserDefCode->Text = t4;
		editselfcode->Text  = t4;
		if (dbedtName->Visible) {
             dbedtPrice->SetFocus();
			}else
			{
			   editprice->SetFocus();
			}
	   //	edt1->Text
	   //	edt1->Text .TrimRight();

//		t2 = GetPYIndexChar(t);
//		ShowMessage(t2);
//		dbedtUserDefCode->DataSource ->DataSet ->FieldByName("UserDefCode")->Value = "fds";

		//dbedtPrice->DataSource ->DataSet ->Edit();
		//dbedtPrice->DataSource ->DataSet ->FieldByName("Price")->Value = 0;

        }


	}
}
//---------------------------------------------------------------------------
char TfrmCatalogAdmin::GetPYIndexChar(char *str)
{

	Word x = 0;
	Word y = 0;//int y = 0;
	//x = StrToInt()

	 x = (int(str[0]))<<8;
	 y = (int(str[1]))<<8;
	 y = y>>8;
	 x = x + y;//str[1];
	 //y = int(str[1]);
//	 x<<8;
//	 y = (int(str[1]));
	 //x = x + y;//0xD3;//+str[1];
	//ShowMessage(0xBE<<8);
	//ShowMessage(0xD3);
	Word Address[] = { 0xB0C4,0xB2C0,0xB4ED,0xB6E9,0xB7A1,
	0xB8C0,0xB9FD,0xBBF6,0xBFA5,0xC0AB,
	0xC2E7,0xC4C2,0xC5B5,0xC5BD,0xC6D9,
	0xC8BA,0xC8F5,0xCBF9,0xCDD9,0xCEF3,
	0xD188,0xD4D0,0xD7F9 };
	char Rchar[25] = "ABCDEFGHJKLMNOPQRSTWXYZ ";
	int i=0;
	for(;i<24;i++)
	if(Address[i] >= x) break;
	return Rchar[i];
}


//---------------------------------------------------------------------------
char TfrmCatalogAdmin::GetPYChar(String HZ)
{}
  //--------------------------------------------------------------------------
  //取得指定汉字串的拼音首字符串
  AnsiString   TfrmCatalogAdmin::GetPYString(AnsiString   HZString)
  {
	String   sRet="";
	String   s = HZString.Trim();
	if(s.IsEmpty())
	return sRet=" ";
	for(int i=1;i<s.Length();i++){
		if((unsigned   int)s[i]>0xA0&&(unsigned int)s[i+1]>0xA0){
			sRet+= (AnsiString)GetPYChar(s.SubString(i,2));
            i++;
		}
		else   sRet+=(AnsiString)s[i];
	}
    return   sRet;
  }
  //--------------------------------------------------------------------





void __fastcall TfrmCatalogAdmin::btn3Click(TObject *Sender)
{
	TfrmExcelImport* frm = new TfrmExcelImport(Owner,qryPressQuery);
	frm->Init(m_app, m_con);
	if (frm->ShowModal() == mrOk)
	{

	}
	delete frm;
		//dbgrdExcelCatlog         dbgrdExcelCatlog->DataSource ->DataSet ->RecordCount
	//ShowMessage("请确定数据正确位置及格式！");
//	int j= dbgrdExcelCatlog->DataSource ->DataSet ->RecordCount;
//	for(int i=1;i<=2;i++ )
//	{
//
//		dsetCatlog->Active = true;
//		dsetCatlog->Append();
//		dsetCatlog->FieldByName("ISBN")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("ISBN")->Value ;
//		dsetCatlog->FieldByName("Name")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Name")->Value ;
//		dsetCatlog->FieldByName("Barcode")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Barcode")->Value ;
//		dsetCatlog->FieldByName("UserDefCode")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("UserDefCode")->Value ;
//		dsetCatlog->FieldByName("Price")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Price")->Value ;
//		dbgrdExcelCatlog->DataSource->DataSet ->RecNo++;
//	}
//	ShowMessage("快来看啊，数据导完了！");
//	dbgrdExcelCatlog->DataSource->DataSet->RecNo=1;
}
	//	dsetCatlog->FieldByName("AbbreviatedName")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Press")->Value ;
//	dsetCatlog->FieldByName("Date")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName(dbgrdExcelCatlog->Columns ->Items [1]->FieldName  )->AsAnsiString .c_str(); // ->Value ;

	//dsetCatlog->FieldByName("smallBookTypeID")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Type")->Value ;
//	dsetCatlog->FieldByName("Author")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("Author")->Value ;
//	dsetCatlog->FieldByName("PressCount")->Value = dbgrdExcelCatlog->DataSource ->DataSet ->FieldByName("PressCount")->Value ;
	//dsetCatlog->FieldByName("PressID")->Value = 1;
	//dsetCatlog->FieldByName("smallBookTypeID")->Value = 2;
	//dsetCatlog->Append()  ;
//	if(rzlkpdlg1->Execute())
//	{
//		ShowMessage("fdf");
//	}
	//dsetCatlog->Append(); dblkpdlgCatlog
	//dsetCatlog->DataSource ->DataSet ->FieldByName()
//  IsbnToCode(dbedtISBN->Text );

//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::dbedtPriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key==VK_RETURN) //
	{

	  if (editprice->Visible) {
		  if (editprice->Text == "") {
			  MessageBoxA(0,"定价是必录项，请添加！","提示",MB_ICONWARNING);
			  	if (dbedtPrice->Visible) {
			  dbedtPrice->SetFocus();
			  return;
			} else
			{
			  editprice->SetFocus();
			  return;
			}
		  }
	  }



	 if(dbedtPrice->Text == "")
		{
			ShowMessage("定价是必录项，请添加！！");
			if (dbedtPrice->Visible) {
			  dbedtPrice->SetFocus();
			} else
			{
			  editprice->SetFocus();
			}

		}
		//RzDBEdit4->SetFocus();
		else
		{
		//dbedtPrice->DataSource ->DataSet ->Edit();
		if (dbedtPrice->Visible) {
              dbedtAuthor->SetFocus();
			} else
			{
			   editauthor->SetFocus();

			}
//		dbedtUserDefCode->DataSource ->DataSet ->Edit();
//		dbedtUserDefCode->DataSource ->DataSet ->FieldByName("UserDefCode")->Value = "fds";
//		dbedtPrice->SetFocus();
		}
        ((TFloatField *)dbgrdCatlog->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
		editprice->Text = FormatFloat("0.00",dsetCatlog->FieldByName("Price")->AsFloat);
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::dbedtAuthorKeyPress(TObject *Sender, wchar_t &Key)

{
if (Key==VK_RETURN) //
	{
	   cbbsmallBookTypeID->SetFocus();
	   //dbdtmpckrDate->SetFocus();
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::cbbPressIDKeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==VK_RETURN) //
	{

	   edtPressCount->SetFocus();
	 }

}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::cbbsmallBookTypeIDKeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==VK_RETURN) //
	{
	  cbbPressID->SetFocus();

	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::dbdtmpckrDateKeyPress(TObject *Sender, wchar_t &Key)

{
if (Key==VK_RETURN) //
	{
	  if (chckbxModify->Checked == false || manybook)
	 {
		try
		{
			if(chckbxInput->Checked == true)
			{
			  if(MessageBox(0,TEXT("确认产生新书资料？"),MB_OK,1)==1)
			  {
				if (manybook) {
				  //dsetCatlog->Insert();                //一书多号，产生新书

						String s1,s2,s3,s4,s6,s8;

						int s5 = -1,pressID = -1;
						TDateTime s7;
						s1 = edtBarcode->Text ;
						s2 = editbookname->Text ;
						s3 = editprice->Text ;
						s4 = editauthor->Text ;
						if(!cbbsmallBookTypeID->DataSource ->DataSet ->FieldByName("smallBookTypeID") ->Value.IsNull() )
							s5 = cbbsmallBookTypeID->DataSource->DataSet->FieldByName("smallBookTypeID")->AsInteger;//cbbsmallBookTypeID->Text ;
						if (!cbbPressID->DataSource ->DataSet ->FieldByName("PressID")->Value.IsNull())
							pressID = cbbPressID->DataSource ->DataSet ->FieldByName("PressID")->AsInteger;

						s7 = dbdtmpckrDate->DataSource ->DataSet ->FieldByName("Date")->AsDateTime  ;
						s8 = edtPressCount->Text ;

						dsetCatlog->Append();

						dbedtUserDefCode->DataSource->DataSet->FieldByName("UserDefCode")->Value = editselfcode->Text ;
						edtBarcode->DataSource ->DataSet ->FieldByName("Barcode")->Value = s1;
						dbedtISBN->DataSource ->DataSet ->FieldByName("ISBN")->Value = s1;//edtBarcode->DataSource ->DataSet ->FieldByName("Barcode")->Value ;
					   //	dbedtPrice->DataSource ->DataSet ->FieldByName("Price")->Value = dbedtPrice->DataSource ->DataSet ->FieldByName("")
						dbedtName->DataSource ->DataSet ->FieldByName("Name")->Value = s2;
						dbedtPrice->DataSource ->DataSet ->FieldByName("Price")->Value = StrToFloat(s3);
						dbedtAuthor->DataSource ->DataSet ->FieldByName("Author")->Value = s4;
						if (s5 > 0)
						{
							cbbsmallBookTypeID->DataSource ->DataSet ->FieldByName("smallBookTypeID") ->AsInteger = s5;//StrToInt(s5);
						}
						if (pressID > 0)
						{
							cbbPressID->DataSource ->DataSet ->FieldByName("PressID")->AsInteger = pressID;
						}

						dbdtmpckrDate->DataSource ->DataSet ->FieldByName("Date")->Value = s7;
						edtPressCount->IntValue = 1;

						editbookname->SetFocus();
						dsetCatlog->UpdateBatch(arAll);
						dsetCatlog->Append();
						editbookname->Text = "";
						editprice->Text = "";
						editauthor->Text = "";

						//manybook = false;

				}else
				{
				dsetCatlog->FieldByName("PressCount")->Value = StrToInt(edtPressCount->Text);
				dsetCatlog->Post();
				dsetCatlog->Append();
				edtBarcode->SetFocus();
				manybook = false;
				}
			  }
			}
			else
			{

				if(MessageDlg("确认产生新书资料？", mtConfirmation, mbOKCancel,0)==mbOK )
				{

				}
				else
				{
					dsetCatlog->FieldByName("PressCount")->Value = StrToInt(edtPressCount->Text);
					dsetCatlog->Post();
					edtBarcode->SetFocus();

				}

			}
		}
		catch(...)
		{
		}
  /*	edtBarcode->Text = "";
	dbedtISBN->Text = "";
	dbedtName->Text = "";
	dbedtUserDefCode->Text = "";
	dbedtPrice->Text = "";
	dbedtAuthor->Text = "";
	cbbsmallBookTypeID->GetListValue()  = "";
	edtPress->Text = "";
		if(!chckbxInput->Checked )
		{
			edtQuery->SetFocus();
			edtBarcode->ReadOnly = true;
			dbedtISBN->ReadOnly = true;
			dbedtName->ReadOnly = true;
			dbedtUserDefCode->ReadOnly = true;
			dbedtPrice->ReadOnly = true;
			dbedtAuthor->ReadOnly = true;
			cbbsmallBookTypeID->ReadOnly = true;
			edtPress->ReadOnly = true;
			cbbPressID->ReadOnly = true;
		} */
	}


	if(chckbxModify->Checked )
	{
		if (MessageBox(0,"确认修改书目资料？","图书品目管理",MB_OKCANCEL|MB_ICONQUESTION)==1) {

			dsetCatlog->Post();
			edtBarcode->SetFocus();
			rzdbchckbx1->ReadOnly = true;
			chckbxModify->Checked = false;
		}

	}
	}

	}


//---------------------------------------------------------------------------
int TfrmCatalogAdmin::IsbnToCode(String str)
{
	int i,s=0,rs[13];
	//rs[0]=0;
	if(str.Length()== 13 )
	{
	edtBarcode->DataSource ->DataSet ->Edit();
	edtBarcode->DataSource ->DataSet ->FieldByName("Barcode")->Value = dbedtISBN->DataSource ->DataSet ->FieldByName("ISBN")->Value ;
	}
	else if(str.Length()==10 )
	{
		int t,k=str.Length();
		for(i=0;i<k;i++)
		{
			String c;
			c=str.LastChar();
			t = StrToInt(c);
			if(i>0)
			{
				rs[i]=t;
			}
			str.Delete(str.Length(),1  );
		}
		rs[12]=9;
		rs[11]=7;
		rs[10]=8;
		for(i=1;i<13;i=i+2)
		s+=rs[i];
		s*=3;
		for(i=2;i<13;i=i+2)
		s+=rs[i];
		if(s%10==0)
		rs[0]=0;
		else rs[0]=10-s%10;
		String temp="";
		for(i=12;i>=0;i--)
		{
			temp += IntToStr(rs[i]);
		}
		edtBarcode->DataSource ->DataSet ->FieldByName("Barcode")->Value= temp;
	}
	else
	{
		ShowMessage("ISBN号输入有误，请重新输入！！");
		dbedtISBN->SetFocus();
	}
	//	String str1;
//	str1=str;
//	int t,s=0;
//	int k,a=9;
//	k = str.Length();
//	//ShowMessage(k);
//	for(int i=0;i<k;i++)
//	{
//		String c;
//		// 得到最后一个字符
//		c = str.LastChar();
//		t = StrToInt(c);
//		if(i>0&&i<10)
//		{
//		//按规则计算isbn代码和
//			s = s + t*a--;
//		//得到isbn前9位数字
//			rs[9-i] = t;
//			//ShowMessage(rs[9-i]);
//		}
//		str.Delete(str.Length(),1 );
//	}
//	//获取isbn最后一位数字
//	a = s%11;
//	if(a==10)
//	return 345;
//	else
//	return a;
}

void __fastcall TfrmCatalogAdmin::btnExit6Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------



void __fastcall TfrmCatalogAdmin::btnExit5Click(TObject *Sender)
{
	if(chckbxModify->Checked )
	{
		try
		{

			if(edtBarcode->Text == "")
			{
               MessageBox(0,"条码不能为空!","图书品目管理",MB_ICONWARNING);
				 return;
			}

			if(dbedtISBN->Text == "")
			{
				 MessageBox(0,"ISBN不能为空!","图书品目管理",MB_ICONWARNING);
				 return;

			}

			if(dbedtName->Text == "")
			{
				MessageBox(0,"书名不能为空!","图书品目管理",MB_ICONWARNING);
				 return;


			}

			if(dbedtPrice->Text == "")
			{

				MessageBox(0,"定价不能为空!","图书品目管理",MB_ICONWARNING);
				 return;
			}


			  if (MessageBox(0,"确认修改书目资料？","图书品目管理",MB_OKCANCEL|MB_ICONQUESTION)==1) {

			 	if (manybook) {
				  //dsetCatlog->Insert();                //一书多号，产生新书

						String s1,s2,s3,s4,s6,s8;

						int s5 = -1,pressID = -1;
						TDateTime s7;
						s1 = edtBarcode->Text ;
						s2 = editbookname->Text ;
						s3 = editprice->Text ;
						s4 = editauthor->Text ;
						if(!cbbsmallBookTypeID->DataSource ->DataSet ->FieldByName("smallBookTypeID") ->Value.IsNull() )
							s5 = cbbsmallBookTypeID->DataSource->DataSet->FieldByName("smallBookTypeID")->AsInteger;//cbbsmallBookTypeID->Text ;
						if (!cbbPressID->DataSource ->DataSet ->FieldByName("PressID")->Value.IsNull())
							pressID = cbbPressID->DataSource ->DataSet ->FieldByName("PressID")->AsInteger;

						s7 = dbdtmpckrDate->DataSource ->DataSet ->FieldByName("Date")->AsDateTime  ;
						s8 = edtPressCount->Text ;

						dsetCatlog->Append();

						edtBarcode->DataSource ->DataSet ->FieldByName("Barcode")->Value = s1;
						dbedtISBN->DataSource ->DataSet ->FieldByName("ISBN")->Value = s1;//edtBarcode->DataSource ->DataSet ->FieldByName("Barcode")->Value ;
					   //	dbedtPrice->DataSource ->DataSet ->FieldByName("Price")->Value = dbedtPrice->DataSource ->DataSet ->FieldByName("")
						dbedtName->DataSource ->DataSet ->FieldByName("Name")->Value = s2;
						dbedtPrice->DataSource ->DataSet ->FieldByName("Price")->Value = StrToFloat(s3);
						dbedtAuthor->DataSource ->DataSet ->FieldByName("Author")->Value = s4;
						if (s5 > 0)
						{
							cbbsmallBookTypeID->DataSource ->DataSet ->FieldByName("smallBookTypeID") ->AsInteger = s5;//StrToInt(s5);
						}
						if (pressID > 0)
						{
							cbbPressID->DataSource ->DataSet ->FieldByName("PressID")->AsInteger = pressID;
						}

						dbdtmpckrDate->DataSource ->DataSet ->FieldByName("Date")->Value = s7;
						edtPressCount->IntValue = 1;
						editbookname->SetFocus();
						dsetCatlog->Post();
				  }
				   else
				  {
					dsetCatlog->Post();
					edtBarcode->SetFocus();
					rzdbchckbx1->ReadOnly = true;
					chckbxModify->Checked = false;
				  }

			}
		}
		catch(...)
		{

		}

	}
	else if (!chckbxModify->Checked || manybook ) {


	{

		try
		{

			if(edtBarcode->Text == "")
			{
               MessageBox(0,"条码不能为空!","图书品目管理",MB_ICONWARNING);
				 return;
			}

			if(dbedtISBN->Text == "")
			{
				 MessageBox(0,"ISBN不能为空!","图书品目管理",MB_ICONWARNING);
				 return;

			}

			if(dbedtName->Text == "")
			{
				MessageBox(0,"书名不能为空!","图书品目管理",MB_ICONWARNING);
				 return;


			}

			if(dbedtPrice->Text == "")
			{

				MessageBox(0,"定价不能为空!","图书品目管理",MB_ICONWARNING);
				 return;
			}
			if(chckbxInput->Checked == true)
			{
				MessageBox(0,TEXT("确认产生新书资料？"),MB_OK,1);
				dsetCatlog->FieldByName("PressCount")->Value = StrToInt(edtPressCount->Text);
				dsetCatlog->Post();
				dsetCatlog->Append();
				edtBarcode->SetFocus();
			}
			else
			{

				if(MessageDlg("确认产生新书资料？", mtConfirmation, mbOKCancel,0)==mbOK )
				{

					dsetCatlog->FieldByName("PressCount")->Value = StrToInt(edtPressCount->Text);
					dsetCatlog->Post();
					edtBarcode->SetFocus();

				}

			}
		}
		catch(...)
		{
		}
	edtBarcode->Text = "";
	dbedtISBN->Text = "";
	dbedtName->Text = "";
	dbedtUserDefCode->Text = "";
	dbedtPrice->Text = "";
	dbedtAuthor->Text = "";
	cbbsmallBookTypeID->GetListValue()  = "";
	edtPress->Text = "";
		if(!chckbxInput->Checked )
		{
			edtQuery->SetFocus();
			edtBarcode->ReadOnly = true;
			dbedtISBN->ReadOnly = true;
			dbedtName->ReadOnly = true;
			dbedtUserDefCode->ReadOnly = true;
			dbedtPrice->ReadOnly = true;
			dbedtAuthor->ReadOnly = true;
			cbbsmallBookTypeID->ReadOnly = true;
			edtPress->ReadOnly = true;
			cbbPressID->ReadOnly = true;
		}
	}
	   /*	if(dbedtISBN->Text == "")
			return;
		if(dsetCatlog->Active && dsetCatlog->State == dsInsert)
		{

		  dsetCatlog->Post() ;

		if(cbbPressID->Text == "")
		{
			//ShowMessage("数据库没有该出版社，请添加！");
		}
		edtBarcode->Text = "";
		dbedtISBN->Text = "";
		dbedtName->Text = "";
		dbedtUserDefCode->Text = "";
		dbedtPrice->Text = "";
		dbedtAuthor->Text = "";
		cbbsmallBookTypeID->GetListValue() = "";
		edtPress->Text = "";
		if(!chckbxInput->Checked )
		{
			//edtQuery->SetFocus();
			//ShowMessage("新书信息保存成功！");
			edtBarcode->ReadOnly = true;
			dbedtISBN->ReadOnly = true;
			dbedtName->ReadOnly = true;
			dbedtUserDefCode->ReadOnly = true;
			dbedtPrice->ReadOnly = true;
			dbedtAuthor->ReadOnly = true;
			cbbsmallBookTypeID->ReadOnly = true;
			edtPress->ReadOnly = true;
			cbbPressID->ReadOnly = true;
		} else
		{
				btnExit1->Enabled = true;   //add
				btnExit5->Enabled = false;     //save
			btnExit2->Enabled = true;    //del

		}
		} */

	}

  }
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
void TfrmCatalogAdmin::OnHotKeyPress(DWORD vkCode)
{
	if(vkCode == VK_F6)
	{
		BtnNewClick(NULL);
	}
	if(vkCode == VK_DELETE)
	{
		btnExit2Click(NULL);
	}
	if(vkCode == VK_ESCAPE)
	{
    	btnExit6Click(NULL);
	}
}
//-------------
void __fastcall TfrmCatalogAdmin::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	//
	if ((Shift.Contains(ssCtrl) || Shift.Contains(ssAlt)) && Key == 0x53)
	{
		ShowMessage("OK");
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogAdmin::btnModifyClick(TObject *Sender)
{
	//chckbxModify->Checked = true;
   //	chckbxInput->Checked = false;
	if(dbedtName->Text == "" )
	return;
	if(MessageDlg("确认修改书目信息？", mtConfirmation, mbOKCancel,0)==mbOK )
				{

				}
				else
				{   chckbxModify->Checked = true;
					dsetCatlog->Active=true;
					edtBarcode->ReadOnly = false;
					dbedtISBN->ReadOnly = false;
					dbedtName->ReadOnly = false;
					dbedtUserDefCode->ReadOnly = false;
					dbedtPrice->ReadOnly = false;
					dbedtAuthor->ReadOnly = false;
					cbbsmallBookTypeID->ReadOnly = false;
					edtPress->ReadOnly = false;
					cbbPressID->ReadOnly = false;
					edtBarcode->SetFocus();
				}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::dbgrdCatlogCellClick(TColumn *Column)
{
	  if(chckbxModify->Checked )
	  {
      	return;
	  }
	  if (manybook) {
		edtBarcode->ReadOnly = false;
		dbedtISBN->ReadOnly = false;
		dbedtName->ReadOnly = false;
		dbedtUserDefCode->ReadOnly = false;
		dbedtPrice->ReadOnly = false;
		dbedtAuthor->ReadOnly = false;
		cbbsmallBookTypeID->ReadOnly = false;
		edtPress->ReadOnly = false;
		cbbPressID->ReadOnly = false;
		return;
	  }
	  edtBarcode->ReadOnly = true;
	  dbedtISBN->ReadOnly = true;
	  dbedtName->ReadOnly = true;
	  dbedtUserDefCode->ReadOnly = true;
	  dbedtPrice->ReadOnly = true;
	  dbedtAuthor->ReadOnly = true;
	  cbbsmallBookTypeID->ReadOnly = true;
	  edtPress->ReadOnly = true;
	  cbbPressID->ReadOnly = true;

	  //edtBarcode->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogAdmin::dsCatlogDataChange(TObject *Sender, TField *Field)

{
    edtPress->Text = cbbPressID->Text ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::dsetCatlogBeforeScroll(TDataSet *DataSet)
{
	//
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::dbgrdCatlogMouseWheel(TObject *Sender, TShiftState Shift,
		  int WheelDelta, TPoint &MousePos, bool &Handled)
{
	//
	if (dsetCatlog->Active==true && dsetCatlog->State == dsInsert||dsetCatlog->Active == true&&dsetCatlog->State == dsEdit)
	{
		Handled = true;
	}
	if(chckbxModify->Checked )
	{
    	Handled = true;
	}

}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogAdmin::edtQueryClick(TObject *Sender)
{
	edtQuery->Text = "";
	edtQuery->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::BtnJumptoLineClick(TObject *Sender)
{
  btnModify->Click();

  btnExit5->Enabled = true;
  rzdbchckbx1->ReadOnly = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::BtnWarningClick(TObject *Sender)
{
   rzdbchckbx1->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::BtnImportClick(TObject *Sender)
{
   btn3->Click();
}
//---------------------------------------------------------------------------



void __fastcall TfrmCatalogAdmin::dbedtISBNKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key==VK_RETURN)
	{
	Perform(WM_NEXTDLGCTL, 0, 0);

	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmCatalogAdmin::BtnNewClick(TObject *Sender)
{
	   //	BtnNew->Enabled = false;
	btnExit5->Enabled = true;
 //	btnExit2->Enabled = false;
	edtQuery->Text = "";
	edtBarcode->ReadOnly = false;
	dbedtISBN->ReadOnly = false;
	dbedtName->ReadOnly = false;
	dbedtUserDefCode->ReadOnly = false;
	dbedtPrice->ReadOnly = false;
	dbedtAuthor->ReadOnly = false;
	cbbsmallBookTypeID->ReadOnly = false;
	edtPress->ReadOnly = false;
	cbbPressID->ReadOnly = false;
	edtPress->Text = "";


	//一号多书恢复
	manybook = false;

	editselfcode->Text = "";
	 editbookname->Text = "";



	//dbedtPrice->Text = IntToStr(0);
	edtBarcode->SetFocus();
	if (dsetCatlog->Active)
	{
		dsetCatlog->Active = false;
	}
		//ShowMessage("hello");
	String sql;
	sql = "select * from UV_PressAndBookCatalogQuery where ID = 0";
	dsetCatlog->CommandText = sql;
	dsetCatlog->Active = true;

	dsetCatlog->Append();
	//dbedtPrice->Text = IntToStr(0);
	//dsetCatlog->FieldByName("AbbreviatedName")->Value = edtPress->Text ;
	dsetCatlog->FieldByName("Price")->Value = 0.00;//FormatFloat(money,"0.00");
	((TFloatField *)dbgrdCatlog->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
	dsetCatlog->Edit();
	dsetCatlog->FieldByName("bigBookTypeID")->Value = 1;
	dbedtPrice->Text = "0.00";
	dbdtmpckrDate->Date = Date();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::editbooknameKeyPress(TObject *Sender, wchar_t &Key)

{
		if (Key==VK_RETURN)
	{
		char* t;
		char t2;
		String t1,t3,t4;
		t1 = editbookname->Text;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;
		int t5=1,i = editbookname->Text.Length() ;
		for( int j=1;j<=i;j++)
		{
			//if (j == 9) break;
			t3 = t1.SubString(j,1);
			t = t3.t_str();
			//if(t3 < 160) continue;
			Word k = int (t[0])<<8;
			k = k >> 8;
			if(k<160) continue;
			//if(int(t[0])< 160) continue;
			//if (t3 >= 'a' && t3 <= 'z' || t3 >= 'A' && t3 <= 'Z'|| t3 >= 0 && t3 <= 9||t3 == '!'||t3 == '@'||t3=='#'||t3=='$'||t3=='%') continue;
			t5++;
			if (t5 == 9) break;
			t = t3.t_str();
			t2 = GetPYIndexChar(t);
			t4 = t4 + t2;
			//ShowMessage(t2);
		}
		editselfcode->Text  = t4;
        dbedtUserDefCode->Text = t4;
	  editprice->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::editpriceKeyPress(TObject *Sender, wchar_t &Key)

{
  if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')) {
	  Key = NULL;
  }


   if (Key==VK_RETURN)
	{
	  Perform(WM_NEXTDLGCTL, 0, 0);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::editauthorKeyPress(TObject *Sender, wchar_t &Key)

{
		if (Key==VK_RETURN)
	{
    cbbsmallBookTypeID->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::BtnViewDetailsClick(TObject *Sender)
{
 editbookname->Text =  dbgrdCatlog->DataSource->DataSet->FieldByName("name")->AsAnsiString ;
 editprice->Text =  dbgrdCatlog->DataSource->DataSet->FieldByName("price")->AsAnsiString ;
 editauthor->Text =   dbgrdCatlog->DataSource->DataSet->FieldByName("author")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogAdmin::edtPressCountKeyPress(TObject *Sender, wchar_t &Key)

{   	if (Key==VK_RETURN)
	{
	  dbdtmpckrDate->SetFocus();

	}

}
//---------------------------------------------------------------------------


