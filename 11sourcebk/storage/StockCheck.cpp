//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StockCheck.h"
#include "pdtypes.h"
#include "NoteCode.h"
#include "ModalDialog.h"
#include "QryNoteCodeForm.h"
#include "checkselbook.h"
#include "Unitkucunpandian.h"
#include "Unitpanbook.h"
#include "unitcfpandian.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzPrgres"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpBase"
#pragma link "RpSystem"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma resource "*.dfm"
Tfrmcheckstock *frmcheckstock;
//---------------------------------------------------------------------------
__fastcall Tfrmcheckstock::Tfrmcheckstock(TComponent* Owner,TADOConnection* con,LandInfo* li)
	: TForm(Owner)
{
  li->con = con;
  fcon = con;
  checkli = *li;
  dtpstart->Date = Date();
  aquery->Connection = con;
  m_storageID = li->storageID ;
  editusername->Text = li->UserName ;
  atable->Connection = con;
  adosp->Connection = con;
  adocount->Connection = con;
  aqueryupdate->Connection = con;
  aqheader->Connection = con;
  CatalogSearchMode = 1;//
  m_storageID = checkli.storageID ;
  m_local = 0;
  Code = "";
  aquerynotcheckbook->Connection = con;
  connect = con;
  weipanshu = false;

}
void Tfrmcheckstock::ReadData(TADOQuery * aquery)
{
	Store = new TStringList();
	Local = new TStringList();
	AnsiString value;
	AnsiString sql ;
	int LocalID;
	int StorgeID;
	sql = "select SYS_GroupAction.* from SYS_GroupAction join SYS_group on SYS_group.id = SYS_GroupAction.groupid "
			" join SYS_UserGroup on SYS_GroupAction.groupid = SYS_UserGroup.groupid "
			" where  SYS_group.groupname = '系统管理员' and SYS_UserGroup.userid = " + IntToStr(checkli.userID);
    aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (aquery->IsEmpty() ) {
		guanliyuan = 0;
	}
	else
	{
		guanliyuan = 1;
	}

	sql = "select pancount from BS_PandianCount where state = 0 and stgid = " + IntToStr(m_storageID) ;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (aquery->IsEmpty() ) {
		count = 0;
		BtnProperties->Enabled = false;
		BtnChangeOptions->Enabled = false;
		if (guanliyuan == 0) {
			Btninit->Enabled = false;
		}
	}
	else
	{
		count = aquery->FieldByName("pancount")->AsInteger ;
		Btninit->Enabled = false;
		if (guanliyuan == 0) {
			BtnHorizontalTile->Enabled = false;
			BtnChangeOptions->Enabled = false;
		}
	}

	sql = "select ID , Name,StgID ,state from STK_Bookstackinfo";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while(!aquery->Eof)
	{
	   Booklocal *bl = new Booklocal(aquery->FieldByName("name")->AsAnsiString ,aquery->FieldByName("StgID")->AsAnsiString ,aquery->FieldByName("id")->AsAnsiString,aquery->FieldByName("state")->AsAnsiString) ;
	   Local->AddObject(bl->ID , (TObject*)bl);
	   aquery->Next();
	}
	sql = "select ID,Name from SYS_storageinfo";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while(!aquery->Eof)    	//加载店信息
	{
	   Storage  *st = new Storage(aquery->FieldByName("name")->AsAnsiString,aquery->FieldByName("id")->AsAnsiString);
	   Store->AddObject(st->ID ,(TObject*)st);
	   if (m_storageID==st->ID ) {
	   edstorageid->Text = st->ID;
		 edtstore->Text = st->Name ;

	   }
   /*	  if (m_storageID = 0) {        //总店加载所有的店信息
	   cbstore->Items->Add(st->Name);
	  } else
	  {
		if (st->ID == m_storageID) {          //不是总店只加载本店信息
		  StorgeID = StrToInt(st->ID);
		  cbstore->Items->AddObject(st->Name ,(TObject*)StorgeID);
		}

		}  */
	   aquery->Next();
	  }


	//加载库位信息
   for (int i = 0; i < Local->Count ; i++) {

	  if(((Booklocal*)Local->Objects[i])->StgID == m_storageID)
	  {
		LocalID = StrToInt(((Booklocal*)Local->Objects[i])->ID) ;
		cblocal->Items->AddObject(((Booklocal*)Local->Objects[i])->Name,(TObject*)LocalID );
	  }

   }

	 cblocal->ItemIndex = 0;

	}

//---------------------------------------------------------------------------
void __fastcall Tfrmcheckstock::edtcheckinfoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (CatalogSearchMode == 4) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	 }

   if (Key == '\r')                //int m_catalogSearchMode;//1条码 2为自编码 3为书名  4 ISBN 5 作者
   {

	 //检查输入信息
	 if (CatalogSearchMode == 4) {
		try {
			float pice = StrToFloat(edtcheckinfo->Text);
		} catch (...) {
			MessageBox(0,"请录入正确的定价","库存盘点",MB_ICONASTERISK);
			return;
		}

	 }

	 if (cblocal->Text == "") {
		 MessageBox(0,"请选择库位","库存盘点",MB_ICONASTERISK);
		 return;
	 }

	String sql;
	AnsiString sqlwhere;
	bool zerodisplay;
	int icount;
	float discount;
	if (edtcheckinfo->Text == "") {
        return;
	}

	 //1条码 2为自编码 3为书名  4 定价 5 作者

		sql = "select BS_BookCatalog.ID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,STK_BookInfo.Cbprice,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,STK_BookInfo.ID as STK_BookinfoID,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.AbbreviatedName ,STK_BookstackInfo.name LocalName "
			"from STK_BookInfo  join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(m_storageID) + " and STK_BookstackInfo.Name = '" + cblocal->Text.Trim() + "' " ;
		  //	+ " and  STK_BookstackInfo.id = " + IntToStr((int )cblocal->Items->Objects[cblocal->ItemIndex]);

	switch (CatalogSearchMode)
	{
	case 1://条码

		 sqlwhere = sqlwhere +  " and BS_BookCatalog.Unavailable=1 and (BS_BookCatalog.Barcode like '%" + edtcheckinfo->Text.Trim()  + "%' or BS_BookCatalog.ISBN like '%" + edtcheckinfo->Text.Trim() + "%') ";
	//	if (!zerodisplay) {                //查询业务设置库存为0的是否显示

	//	   sql = sql + "and STK_BookInfo.Amount > 0 " ;

   //		}
		break;
	case 2://自编码
		  sqlwhere = sqlwhere +   " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.UserDefCode like '%" + edtcheckinfo->Text.Trim()  + "%'";

	  //	if (!zerodisplay) {

	  //	   sql = sql + "and STK_BookInfo.Amount > 0 " ;

	 //	}
		break;
	case 3://书名

			sqlwhere = sqlwhere + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Name like '%" + edtcheckinfo->Text.Trim()  + "%'";

	 //	if (!zerodisplay) {

	 //	   sql = sql + "and STK_BookInfo.Amount > 0 " ;
	 //		}
		break;
	case 4: //ISBN

		  sqlwhere = sqlwhere	+ " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Price = " + edtcheckinfo->Text.Trim();

	  //	if (!zerodisplay) {

	  //		sql = sql + "and STK_BookInfo.Amount > 0 " ;
	  //		}

		break;
	case 5://作者
		   sqlwhere = sqlwhere 	+ " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Author like '%" + edtcheckinfo->Text.Trim()  + "%'";

	  //	if (!zerodisplay) {

	 //	sql = sql + "and STK_BookInfo.Amount > 0 " ;
	 //	}
		break;
	default:
		break;
	}
	sql = sql + sqlwhere;

   try
   {

		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();

		if (aquery->RecordCount > 1) {   //多条记录

		Tfrmcatalogselect *frm  = new Tfrmcatalogselect(Application, checkli.con , aquery);




		if (mrOk==frm->ShowModal()) {
			//得到目前该书的库位如果是默认库位就没提示，否则就会提示
			if (aquery->FieldByName("BkstackName")->AsAnsiString!=cblocal->Text) {


		   AnsiString sql ;
		   sql = "select * from stk_bookinfo A join STK_BookstackInfo B on A.bkstackid = B.ID ";
		   sql = sql + " where bkcatalogid = " +aquery->FieldByName("ID")->AsAnsiString ;
		   sql = sql + " and B.name <> '默认库位' and  BkstackID <> " + IntToStr((int)cblocal->Items->Objects[cblocal->ItemIndex]);
		   sql = sql + " and B.stgid = " + IntToStr(m_storageID);
		   AnsiString Msg;
		   Msg = " 该书已存放于 \n";
		   TADOQuery * aq =  new TADOQuery(NULL);
		   aq->Connection = checkli.con ;
		   aq->Close();
		   aq->SQL->Clear();
		   aq->SQL->Add(sql);
		   aq->Open();
		   if (aq->RecordCount > 0) {
			  for (int i = 0; i < aq->RecordCount; i++) {
				  Msg = Msg + aq->FieldByName("name")->AsAnsiString + " \n";
				  aq->Next();
			  }
			  Msg = Msg + "\n 是否要盘入本库？";
			 if(MessageBoxA(0,Msg.c_str(),"提示",MB_ICONQUESTION||MB_OKCANCEL)== 1)
			 {

			 }else
			 {
				return;
			 }

			 }

		   }
			   TLocateOptions   Opts;
			   Opts.Clear();
			   Opts   <<   loPartialKey;
			   String   str   = aquery->FieldByName("STK_BookinfoID")->AsAnsiString;
			   if ( aqueryupdate->Locate("STK_bookInfoID",str,Opts))
			   {
					//MessageBoxA(0,"该书已在盘点!","库存盘点管理",MB_ICONASTERISK);
					Tfrmcfpandian *frm1 = new Tfrmcfpandian(Application,fcon);
					frm1->stkbkid = aquery->FieldByName("STK_BookinfoID")->AsInteger ;
					frm1->bendan = 1;
					if (frm1->ShowModal() == mrOk  ) {
                    	aqueryupdate->Edit();
						aqueryupdate->FieldByName("shouldamount")->AsInteger  = aqueryupdate->FieldByName("shouldamount")->AsInteger + frm1->addamount ;
						aqueryupdate->FieldByName("balance")->AsInteger =aqueryupdate->FieldByName("shouldamount")->AsInteger - aqueryupdate->FieldByName("actualamount")->AsInteger;
						aqueryupdate->FieldByName("states")->AsInteger = 0;
						aqueryupdate->FieldByName("Fixedprice")->AsFloat = (aqueryupdate->FieldByName("Price")->AsFloat)*(aqueryupdate->FieldByName("shouldamount")->AsInteger);
						aqueryupdate->FieldByName("Discountprice")->AsFloat  = (aqueryupdate->FieldByName("Discount")->AsFloat)*(aqueryupdate->FieldByName("Fixedprice")->AsFloat)/100;
						edtcheckinfo->Text = "";
					}
					delete frm1;
					try {
						aqueryupdate->UpdateBatch(arCurrent);
					} catch (...) {
					}
					return;
			   }
				TADOQuery *aq = new TADOQuery(this);
				aq->Connection = fcon;
				AnsiString sql;
				sql = "select notecode from STK_StockInventories where stk_bookinfoid = " + str + "and notecode in(select codestr from BS_PandianCount where state = 0)";
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				if (aq->RecordCount > 0) {
					//AnsiString Note;
					//Note = "该书在盘点单" + aq->FieldByName("notecode")->AsAnsiString + "内进行盘点";
					//MessageBoxA(0,Note.c_str() ,"库存盘点管理",MB_ICONASTERISK);
					delete aq;
					Tfrmcfpandian *frm1 = new Tfrmcfpandian(Application,fcon);
					frm1->stkbkid = aquery->FieldByName("STK_BookinfoID")->AsInteger ;
					if (frm1->ShowModal() == mrOk  ) {
						edtcheckinfo->Text = "";
					}
					delete frm1;
					try {
						//aqueryupdate->Refresh();
					} catch (...) {
					}
					return;
				}
				delete aq;


		   aqueryupdate->Active = true;
		   ((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
		   aqueryupdate->Insert();
		   aqueryupdate->Append();

		   aqueryupdate->FieldByName("bkcatalogid")->AsAnsiString =aquery->FieldByName("ID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("Price")->AsFloat  =aquery->FieldByName("Price")->AsFloat ;
		   discount = aquery->FieldByName("Cbprice")->AsFloat/aquery->FieldByName("Price")->AsFloat*100;
		   aqueryupdate->FieldByName("Discount")->AsFloat =discount;
		   aqueryupdate->FieldByName("bklocalname")->AsAnsiString = aquery->FieldByName("BkstackName")->AsAnsiString ;
		   aqueryupdate->FieldByName("BarCode")->AsAnsiString = aquery->FieldByName("BarCode")->AsAnsiString  ;
		   aqueryupdate->FieldByName("suppliername")->AsAnsiString = aquery->FieldByName("SupplierName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("ISBN")->AsAnsiString = aquery->FieldByName("ISBN")->AsAnsiString  ;
		   aqueryupdate->FieldByName("bookname")->AsAnsiString = aquery->FieldByName("name")->AsAnsiString  ;
		   aqueryupdate->FieldByName("AbbreviatedName")->AsAnsiString = aquery->FieldByName("AbbreviatedName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("actualamount")->AsAnsiString = aquery->FieldByName("Amount")->AsAnsiString  ;
		   aqueryupdate->FieldByName("supplierid")->AsAnsiString = aquery->FieldByName("SupplierID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("STK_bookInfoID")->AsAnsiString = aquery->FieldByName("STK_BookinfoID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("NoteCode")->AsAnsiString = Code  ;
		   aqueryupdate->FieldByName("shouldamount")->AsInteger  = 0;
		   edtnumber->SetFocus();
		   //icount  = lcount->Caption.ToInt()  ;
		   //lcount->Caption = IntToStr(++icount);

		}

		}
		if (aquery->RecordCount == 1) {    //只有一条记录

		   /*TADOQuery * aq =  new TADOQuery(NULL);
		   aq->Connection = checkli.con ;
		   sql = "select * from STK_StockInventories where STK_bookInfoID = " +  aquery->FieldByName("STK_BookinfoID")->AsAnsiString ;
		   aq->Close();
		   aq->SQL->Clear();
		   aq->SQL->Add(sql);
		   aq->Open();
		   if (aq->RecordCount > 0) {
			   MessageBoxA(0,"该书已在盘点!","库存盘点管理",MB_ICONASTERISK);
			   return;
		   }		   delete aq;		    */		   TLocateOptions   Opts;			   Opts.Clear();
			   Opts   <<   loPartialKey;
			   String   str   = aquery->FieldByName("STK_BookinfoID")->AsAnsiString;
			   if ( aqueryupdate->Locate("STK_bookInfoID",str,Opts))
			   {
					//MessageBoxA(0,"该书已在盘点!","库存盘点管理",MB_ICONASTERISK);
					Tfrmcfpandian *frm1 = new Tfrmcfpandian(Application,fcon);
					frm1->stkbkid = aquery->FieldByName("STK_BookinfoID")->AsInteger ;
					frm1->bendan = 1;
					if (frm1->ShowModal() == mrOk  ) {
						aqueryupdate->Edit();
						aqueryupdate->FieldByName("shouldamount")->AsInteger  = aqueryupdate->FieldByName("shouldamount")->AsInteger + frm1->addamount ;
						aqueryupdate->FieldByName("balance")->AsInteger =aqueryupdate->FieldByName("shouldamount")->AsInteger - aqueryupdate->FieldByName("actualamount")->AsInteger;
						aqueryupdate->FieldByName("states")->AsInteger = 0;
						aqueryupdate->FieldByName("Fixedprice")->AsFloat = (aqueryupdate->FieldByName("Price")->AsFloat)*(aqueryupdate->FieldByName("shouldamount")->AsInteger);
						aqueryupdate->FieldByName("Discountprice")->AsFloat  = (aqueryupdate->FieldByName("Discount")->AsFloat)*(aqueryupdate->FieldByName("Fixedprice")->AsFloat)/100;
						edtcheckinfo->Text = "";

					}
					delete frm1;
					try {
						aqueryupdate->UpdateBatch(arCurrent);
					} catch (...) {
					}
					return;
			   }				TADOQuery *aq = new TADOQuery(this);				aq->Connection = fcon;
				AnsiString sql;
				sql = "select notecode from STK_StockInventories where stk_bookinfoid = " + str + "and notecode in(select codestr from BS_PandianCount where state = 0)";
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				if (aq->RecordCount > 0) {
					//AnsiString Note;
					//Note = "该书在盘点单" + aq->FieldByName("notecode")->AsAnsiString + "内进行盘点";
					//MessageBoxA(0,Note.c_str() ,"库存盘点管理",MB_ICONASTERISK);
					delete aq;
					Tfrmcfpandian *frm1 = new Tfrmcfpandian(Application,fcon);
					frm1->stkbkid = aquery->FieldByName("STK_BookinfoID")->AsInteger ;
					if (frm1->ShowModal() == mrOk  ) {
						edtcheckinfo->Text = "";
					}
					delete frm1;
					try {
						//aqueryupdate->Refresh();
					} catch (...) {
					}
					return;
				}
				delete aq;
		   aqueryupdate->Active = true;
		   ((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
		   aqueryupdate->Insert();
		   aqueryupdate->Append();
		   aqueryupdate->FieldByName("bkcatalogid")->AsAnsiString =aquery->FieldByName("ID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("bklocalname")->AsAnsiString = aquery->FieldByName("BkstackName")->AsAnsiString ;
		   aqueryupdate->FieldByName("BarCode")->AsAnsiString = aquery->FieldByName("BarCode")->AsAnsiString  ;
		   aqueryupdate->FieldByName("suppliername")->AsAnsiString = aquery->FieldByName("SupplierName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("ISBN")->AsAnsiString = aquery->FieldByName("ISBN")->AsAnsiString  ;
		   aqueryupdate->FieldByName("bookname")->AsAnsiString = aquery->FieldByName("name")->AsAnsiString  ;
		   aqueryupdate->FieldByName("AbbreviatedName")->AsAnsiString = aquery->FieldByName("AbbreviatedName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("actualamount")->AsAnsiString = aquery->FieldByName("Amount")->AsAnsiString  ;
		   aqueryupdate->FieldByName("supplierid")->AsAnsiString = aquery->FieldByName("SupplierID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("STK_bookInfoID")->AsAnsiString = aquery->FieldByName("STK_BookinfoID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("NoteCode")->AsAnsiString = Code   ;
		   aqueryupdate->FieldByName("Price")->AsFloat  =aquery->FieldByName("Price")->AsFloat ;
		   discount = aquery->FieldByName("Cbprice")->AsFloat/aquery->FieldByName("Price")->AsFloat*100;
		   aqueryupdate->FieldByName("Discount")->AsFloat =discount;
		   aqueryupdate->FieldByName("shouldamount")->AsInteger = 0;
		   edtnumber->SetFocus();
		   //icount  = lcount->Caption.ToInt()  ;
		   //lcount->Caption = IntToStr(++icount);
		}
		bool newbook = false;
		if (aquery->RecordCount == 0) {
			sql = "select *,bs_pressinfo.AbbreviatedName from bs_bookcatalog left join bs_pressinfo on bs_bookcatalog.pressid = bs_pressinfo.id where 1= 1 " + sqlwhere;
			aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->Open();
			if (aquery->IsEmpty() ) {
				MessageBoxA(0,"没有该书记录!","库存盘点管理",MB_ICONASTERISK);
			}
			else
			{
				if(MessageBoxA(0,"当前盘点库位无该书，是否盘入该书","提示",MB_ICONQUESTION||MB_OKCANCEL)== 1)
				{
					if (aquery->RecordCount > 1) {
						Tfrmpanbook *frm = new Tfrmpanbook(Application,aquery);
						if (frm->ShowModal() == mrOk ) {
							newbook = true;
						}
					}
					if (aquery->RecordCount == 1) {
						newbook = true;
					}
					if (newbook) {
						sql = "declare @BkInfoID int; "
								" exec USP_BS_Get_BookInfoByBkcatalogID " + IntToStr(m_storageID) + ",0," + aquery->FieldByName("ID")->AsString + ",@BkInfoID output,1," + IntToStr((int)cblocal->Items->Objects[cblocal->ItemIndex])+ "; "
								" select @BkInfoID as BkInfoID" ;
						adocount->Close();
						adocount->SQL->Clear();
						adocount->SQL->Add(sql);
						adocount->Open();
						if (adocount->FieldByName("BkInfoID")->AsInteger > 0 ) {
                        	aqueryupdate->Active = true;
						   ((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
						   aqueryupdate->Insert();
						   aqueryupdate->Append();
						   aqueryupdate->FieldByName("bkcatalogid")->AsAnsiString =aquery->FieldByName("ID")->AsAnsiString  ;
						   aqueryupdate->FieldByName("bklocalname")->AsAnsiString = cblocal->Text ;
						   aqueryupdate->FieldByName("BarCode")->AsAnsiString = aquery->FieldByName("Barcode")->AsAnsiString  ;
						   aqueryupdate->FieldByName("suppliername")->AsAnsiString = "普通供应商";
						   aqueryupdate->FieldByName("ISBN")->AsAnsiString = aquery->FieldByName("ISBN")->AsAnsiString  ;
						   aqueryupdate->FieldByName("bookname")->AsAnsiString = aquery->FieldByName("name")->AsAnsiString  ;
						   aqueryupdate->FieldByName("AbbreviatedName")->AsAnsiString = aquery->FieldByName("AbbreviatedName")->AsAnsiString  ;
						   aqueryupdate->FieldByName("actualamount")->AsAnsiString = "0";
						   aqueryupdate->FieldByName("supplierid")->AsAnsiString = 0;
						   aqueryupdate->FieldByName("STK_bookInfoID")->AsAnsiString = adocount->FieldByName("BkInfoID")->AsInteger  ;
						   aqueryupdate->FieldByName("NoteCode")->AsAnsiString = Code   ;
						   aqueryupdate->FieldByName("Price")->AsFloat  =aquery->FieldByName("Price")->AsFloat ;
						   //discount = aquery->FieldByName("Cbprice")->AsFloat/aquery->FieldByName("Price")->AsFloat*100;
						   aqueryupdate->FieldByName("Discount")->AsFloat =100;
						   aqueryupdate->FieldByName("shouldamount")->AsInteger = 0;
						   edtnumber->SetFocus();
						}
					}
				}
			}


		}
   }

  catch(...)
   {}


	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::N2Click(TObject *Sender)
{
	CatalogSearchMode = 3;
	lbsearch->Caption = "书名";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::N4Click(TObject *Sender)
{
	CatalogSearchMode = 2;
	lbsearch->Caption = "自编码";
	lbsearch->Tag = 2;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::N1Click(TObject *Sender)
{
	CatalogSearchMode = 1;
	lbsearch->Caption = "书号";
	lbsearch->Tag = 1;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcheckstock::N3Click(TObject *Sender)
{
	  CatalogSearchMode= 5;
	  lbsearch->Caption = "作者";
	  lbsearch->Tag = 5;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::FormCreate(TObject *Sender)
{

	 String sql;
	 int stgid,storeid,j,value,count;
	 String StockNum,Note;                     //检查该操作员是否还有没有结束盘点的单子
	 sql = "select checkstocknum,checkstocklocal,checkstore,STK_CheckStockinfo.bk,STK_BookstackInfo.name as stackname from STK_CheckStockinfo left join STK_BookstackInfo "
		   " on STK_CheckStockinfo.checkstocklocal = STK_BookstackInfo.id "
		   " where employ = " + IntToStr(checkli.userID) + " and STK_CheckStockinfo.state = 1" ;
	ReadData(aquery);
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (aquery->RecordCount >0) {
		if (MessageBoxA(0,"还有未结束的盘点单，是否继续盘点？确定继续盘点，取消产生新的盘点单。","库存盘点",MB_ICONQUESTION|MB_OKCANCEL)== 1) {
			if (aquery->RecordCount > 1) {
				Tfrmkucunpandian *frm = new Tfrmkucunpandian(Application,aquery);
				if (frm->ShowModal() ) {

				}
			}
            for (int i=0; i < cblocal->Items->Count ; i++) {
				if ((int )cblocal->Items->Objects[i] ==  aquery->FieldByName("checkstocklocal")->AsInteger ) {
					cblocal->ItemIndex = i;
					cblocal->Enabled = false;
				}
			}
			StockNum = aquery->FieldByName("checkstocknum")->AsString ;
			stgid = aquery->FieldByName("checkstore")->AsInteger ;
			storeid = aquery->FieldByName("checkstocklocal")->AsInteger ;
			Code = StockNum;
			editnum->Text = Code;
			membk->Text = aquery->FieldByName("bk")->AsString;

			j = Store->IndexOf(IntToStr(stgid));
			if (j >=0) {
			   edtstore->Text = ((Storage*)Store->Objects[j])->Name ;
			}

			aqueryupdate->Parameters->ParamByName("stocknum")->Value = StockNum;
			aqueryupdate->Active = true;
			((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";

			sql = "select ID,checkstockNum,totalamount,Fixedprice,Discountprice,checkdate from STK_CheckStockinfo where checkstockNum = '" + StockNum + "'";
			aqheader->Close();
			aqheader->SQL->Clear();
			aqheader->SQL->Add(sql);
			aqheader->Open();
			dtpstart->Date = aqheader->FieldByName("checkdate")->AsDateTime ;
            BtnProperties->Enabled = false;
            BtnViewIcons->Enabled = true;
		}
		else
		{
			sql = "select ID,Name from STK_BookstackInfo where stgid = " + IntToStr(m_storageID) + " and id not in (select checkstocklocal from STK_CheckStockinfo where state = 1 and employ = " + IntToStr(checkli.userID) + " )";
            aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->Open();
			if (aquery->IsEmpty() ) {
                MessageBox(0,"无可盘点的库位!","盘点",MB_ICONASTERISK);
				Close();
			}
			else
			{
				cblocal->Items->Clear();
				while (!aquery->Eof )
				{
					cblocal->AddItem(aquery->FieldByName("Name")->AsString ,(TObject*)aquery->FieldByName("id")->AsInteger );
					aquery->Next();
				}
				aquery->First();
                cblocal->ItemIndex = cblocal->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
			}
		}


		/*value = (int )cblocal->Items->Objects[cblocal->ItemIndex];
		adosp->ProcedureName = "LocalCount";    //最得总记录数
		adosp->Parameters->Clear();
		adosp->Parameters->CreateParameter("@localiD",ftInteger ,pdInput,sizeof(int), &value);
		adosp->Parameters->CreateParameter("@count",ftInteger ,pdOutput,sizeof(int), count);
		adosp->ExecProc();

		adosp->ProcedureName = "localProcessCount";    //已经处理的记录数
		adosp->Parameters->Clear();
		adosp->Parameters->CreateParameter("@NoteCode",ftString ,pdInput,StockNum.Length() , StockNum);
		adosp->Parameters->CreateParameter("@count",ftInteger  ,pdOutput ,sizeof(int), count);
		adosp->ExecProc();
		*/

	  }

	 /*if (Btninit->Enabled ) {
		  BtnViewIcons->Enabled = false ;
		  BtnViewList->Enabled = false;
		  BtnHorizontalTile->Enabled = false;
		  edtcheckinfo->Enabled = false;
		  edtnumber->Enabled = false;
	 }else
	 {
		 BtnViewIcons->Enabled = true ;
		 BtnViewList->Enabled = true;
		 BtnHorizontalTile->Enabled = true;
		 edtcheckinfo->Enabled = true;
		 edtnumber->Enabled = true;
		 editstate->Text = "正在盘点";
		 //memnote->Lines->Add("提示：若盘点正在进行，库位将被锁定，");
		 //memnote->Lines->Add("            任何对该库位的操作都将禁止。");
	 } */
}


void __fastcall Tfrmcheckstock::lbsearchMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
  if (Button == mbLeft ) {
	TPoint  pt;
	 GetCursorPos(&pt);
	 pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcheckstock::edtnumberKeyPress(TObject *Sender, wchar_t &Key)
{
	  if (Key == '\r') {
		//float Discountprice = 0,  Fixedprice = 0
		//Fixedprice = (aqueryupdate->FieldByName("Price")->AsFloat)*StrToInt(edtnumber->Text);
		//Discountprice = Fixedprice*(aqueryupdate->FieldByName("Discount")->AsFloat)/100;
        if (edtnumber->Text == "") {
        	return;
		}
		if (aqueryupdate->IsEmpty() ) {
			return;
		}
		aqueryupdate->Edit();
		aqueryupdate->FieldByName("shouldamount")->AsInteger  = StrToInt(edtnumber->Text);
		aqueryupdate->FieldByName("balance")->AsInteger =aqueryupdate->FieldByName("shouldamount")->AsInteger - aqueryupdate->FieldByName("actualamount")->AsInteger;
		aqueryupdate->FieldByName("states")->AsInteger = 0;
		aqueryupdate->FieldByName("Fixedprice")->AsFloat = (aqueryupdate->FieldByName("Price")->AsFloat)*(aqueryupdate->FieldByName("shouldamount")->AsInteger);
		aqueryupdate->FieldByName("Discountprice")->AsFloat  = (aqueryupdate->FieldByName("Discount")->AsFloat)*(aqueryupdate->FieldByName("Fixedprice")->AsFloat)/100;
		aqueryupdate->UpdateBatch(arCurrent);
		aqueryupdate->Active = false;
		aqueryupdate->Active = true;
		((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
		aqueryupdate->Last();
		edtcheckinfo->Text = "";
		edtnumber->Text = "";
		aqheader->Active = false;
		aqheader->Active = true;
		edtcheckinfo->SetFocus();
   }
   if (Key != '\b') {
	if((Key<'0')||(Key>'9'))
		  Key=NULL;
   }


}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnViewListClick(TObject *Sender)
{
	String sql;

	int STKbookID,shouldamount;
	int value;
	int stgid;
   //更改库
   if (aqueryupdate->State == dsInactive  ) {
	   return;
   }

	aqueryupdate->First();
	aqueryupdate->DisableControls();
	//rprcess->Max  = aqueryupdate->RecordCount ;
	for (int i=0; i < aqueryupdate->RecordCount  ; i++) {
	  if (aqueryupdate->FieldByName("states")->AsInteger !=1 ) {
		STKbookID = aqueryupdate->FieldByName("STK_bookInfoID")->AsInteger;
		shouldamount = aqueryupdate->FieldByName("shouldamount")->AsInteger;
		int bkcatalogid = aqueryupdate->FieldByName("bkcatalogid")->AsInteger ;
		int supplierid = aqueryupdate->FieldByName("Supplierid")->AsInteger;
		int bkstackid = (int )cblocal->Items->Objects[cblocal->ItemIndex];
		int mode=0;
		int siid = aqueryupdate->FieldByName("id")->AsInteger ;
		int harmnum = aqueryupdate->FieldByName("damagenum")->AsInteger ;
		if (aqueryupdate->FieldByName("bklocalname")->AsAnsiString == "默认库位") {
			mode = 1;
		}
		adosp->ProcedureName = "UpdateStockAmount";
		adosp->Parameters->Clear();
		adosp->Parameters->CreateParameter("@STKbookID",ftInteger ,pdInput,sizeof(int), &STKbookID);
		adosp->Parameters->CreateParameter("@ActualAmount",ftInteger ,pdInput,sizeof(int), &shouldamount);
		adosp->Parameters->CreateParameter("@bkstackid",ftInteger,pdInput,sizeof(int),&bkstackid);
		adosp->Parameters->CreateParameter("@bkcatalogid",ftInteger,pdInput,sizeof(int),&bkcatalogid);
		adosp->Parameters->CreateParameter("@Supplierid",ftInteger,pdInput,sizeof(int),&supplierid);
		adosp->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),&mode);
		adosp->Parameters->CreateParameter("@siid",ftInteger,pdInput,sizeof(int),&siid);
		adosp->Parameters->CreateParameter("@harmnum",ftInteger,pdInput,sizeof(int),&harmnum);


		adosp->ExecProc();
		/*aqueryupdate->Edit();
		aqueryupdate->FieldByName("balance")->AsInteger = 0;
		aqueryupdate->FieldByName("ActualAmount")->AsInteger = aqueryupdate->FieldByName("ShouldAmount")->AsInteger;
		aqueryupdate->UpdateBatch(arAll); */
	  }
	  //rprcess->Position ++;

	  aqueryupdate->Next();
	}
	aqueryupdate->EnableControls();

	if (aqueryupdate->RecordCount != 0 ) {
	 MessageBox(0,"盘点修改库量成功!","盘点",MB_ICONASTERISK);
	 aqueryupdate->Active = false;
	 aqueryupdate->Active = true;
	 ((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
	}

	/*
	sql = "insert into STK_CheckStockinfo (checkstockNum ,checkstore,checkstocklocal,checkdate,bk,employ)"
			" values('" + edtchecknum->Text + "'," + IntToStr(m_storageID) + "," + IntToStr(m_local)
		 + ",'" + DateTimeToStr(dtpdate->Date)+"','" + edtbk->Text.Trim()+ "'," + checkli.userID +")";

	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->ExecSQL();

												   //解锁库位
	stgid = (int)cbstore->Items->Objects[cbstore->ItemIndex];
	value =   (int )cblocal->Items->Objects[cblocal->ItemIndex];
	adosp->ProcedureName = "UnLockLocal";
	adosp->Parameters->Clear();
	adosp->Parameters->CreateParameter("@stgid",ftInteger ,pdInput,sizeof(int), &stgid);
	adosp->Parameters->CreateParameter("@localid",ftInteger ,pdInput,sizeof(int), &value);
	adosp->ExecProc();      */

}
//---------------------------------------------------------------------------


void __fastcall Tfrmcheckstock::dgcheckCellClick(TColumn *Column)
{
   int tag;
   tag = lbsearch->Tag ;
   if (aqueryupdate->State == dsInactive ) {
     return;

   }
   edtnumber->Text = aqueryupdate->FieldByName("shouldamount")->AsAnsiString ;
   edsamount->Text = aqueryupdate->FieldByName("damagenum")->AsAnsiString ;
   edbk->Text = aqueryupdate->FieldByName("bk")->AsAnsiString ;

}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnHorizontalTileClick(TObject *Sender)
{
	 AnsiString sql;
	 int localid;
		localid =   (int )cblocal->Items->Objects[cblocal->ItemIndex];
		localid = 0;//////////
	 sql = "select BS_BookCatalog.ID,STK_BookInfo.SupplierID,BS_BookCatalog.Name as bookname,BS_BookCatalog.Barcode,"
			" BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,STK_BookInfo.ID as STK_BookinfoID, "
			" STK_BookInfo.Amount as actualamount,STK_BookstackInfo.Name as LocalName,BS_BookCatalog.Price ,BS_PressInfo.AbbreviatedName "
			" from STK_BookInfo JOIN BS_BookCatalog ON STK_BookInfo.BkcatalogID = BS_BookCatalog.ID "
			" JOIN STK_BookstackInfo ON STK_BookInfo.BkstackID = STK_BookstackInfo.ID "
			" JOIN CUST_CustomerInfo ON STK_BookInfo.SupplierID = CUST_CustomerInfo.ID "
			" LEFT JOIN BS_BookType ON BS_BookCatalog.smallBookTypeID = BS_BookType.ID "
			" LEFT JOIN BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			" where STK_BookInfo.amount <> 0 and STK_BookInfo.bkstackid = " + IntToStr((int )cblocal->Items->Objects[cblocal->ItemIndex]) + " and STK_BookInfo.id not in "
			" (select STK_BookInfoID from STK_StockInventories join BS_PandianCount "
			" on STK_StockInventories.NoteCode = BS_PandianCount.CodeStr where BS_PandianCount.state = 0 and  "
			" BS_PandianCount.stgid = " + IntToStr(m_storageID) + ") ";
	aquerynotcheckbook->Close();
	aquerynotcheckbook->SQL->Clear();
	aquerynotcheckbook->SQL->Add(sql);
	aquerynotcheckbook->Open();
	 int icount;
	//show Not checkbook
	TfrmNotCheckBook *frm = new TfrmNotCheckBook(Application,aquerynotcheckbook);
	if(mrOk  ==frm->ShowModal())
	{
	  if (aqueryupdate->Active == false) {
		aqueryupdate->Active = true;
		((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
	  }
	  aquerynotcheckbook->DisableControls();
	  while(!aquerynotcheckbook->Eof)
	  {

			aqueryupdate->Insert();
			aqueryupdate->Append();
			aqueryupdate->FieldByName("bkcatalogid")->AsAnsiString =aquerynotcheckbook->FieldByName("ID")->AsAnsiString  ;
			aqueryupdate->FieldByName("BarCode")->AsAnsiString = aquerynotcheckbook->FieldByName("BarCode")->AsAnsiString  ;
			aqueryupdate->FieldByName("suppliername")->AsAnsiString = aquerynotcheckbook->FieldByName("SupplierName")->AsAnsiString  ;
			aqueryupdate->FieldByName("ISBN")->AsAnsiString = aquerynotcheckbook->FieldByName("ISBN")->AsAnsiString  ;
			aqueryupdate->FieldByName("bookname")->AsAnsiString = aquerynotcheckbook->FieldByName("bookname")->AsAnsiString  ;
			aqueryupdate->FieldByName("AbbreviatedName")->AsAnsiString = aquerynotcheckbook->FieldByName("AbbreviatedName")->AsAnsiString  ;
			aqueryupdate->FieldByName("actualamount")->AsAnsiString = aquerynotcheckbook->FieldByName("actualamount")->AsAnsiString  ;
			aqueryupdate->FieldByName("supplierid")->AsAnsiString = aquerynotcheckbook->FieldByName("SupplierID")->AsAnsiString  ;
			aqueryupdate->FieldByName("STK_bookInfoID")->AsAnsiString = aquerynotcheckbook->FieldByName("STK_BookinfoID")->AsAnsiString  ;
			aqueryupdate->FieldByName("NoteCode")->AsAnsiString = Code  ;
			aqueryupdate->FieldByName("shouldamount")->AsInteger  = 0;
			aqueryupdate->FieldByName("Balance")->AsAnsiString =  StrToInt(0 - aquerynotcheckbook->FieldByName("actualamount")->AsInteger);
			//aqueryupdate->Post();
			aqueryupdate->UpdateBatch(arCurrent);
			//icount  = lcount->Caption.ToInt()  ;
			//lcount->Caption = IntToStr(++icount);
			aquerynotcheckbook->Next();

	  }
	  aquerynotcheckbook->EnableControls();
	  weipanshu = true;
	  //aqueryupdate->UpdateBatch(arAll);
	  delete frm;
	}
	aqueryupdate->Active = false;
	aqueryupdate->Active = true;
	((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnViewIconsClick(TObject *Sender)
{
	if (editnum->Text == "") {
    	MessageBox(0,"还有盘点数据没有修改库存，请修改库存后结束盘点！","警告" ,MB_OK);
		return;
	}
	int value;
	AnsiString Note;											   //解锁库位
	String sql;
	sql = "select * from STK_StockInventories where states = 0 and NoteCode = '" + Code + "'";
    aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (aquery->RecordCount > 0) {
		MessageBox(0,"还有盘点数据没有修改库存，请修改库存后结束盘点！","警告" ,MB_OK);
		return;
	}
	value = (int )cblocal->Items->Objects[cblocal->ItemIndex];
	adosp->ProcedureName = "UnLockLocal";
	adosp->Parameters->Clear();
	adosp->Parameters->CreateParameter("@stgid",ftInteger ,pdInput,sizeof(int), &m_storageID);
	adosp->Parameters->CreateParameter("@localid",ftInteger ,pdInput,sizeof(int), &value);
	adosp->ExecProc();

								 //更改该操作人员在 STK_CheckStockinfo表中的状态
	sql  =  "update STK_CheckStockinfo set state = 0,checkdate = getdate() where checkstocknum = '"+ Code +"' and employ  = "+ IntToStr(checkli.userID) +"";

	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->ExecSQL();
	//-----------------------------------------------------------------

	//Note =  cblocal->Text +  " 已解锁,可以对该库位进行其它相关操作！";
	//memnote->Lines->Clear();
	//memnote->Lines->Add("提示!");
	//memnote->Lines->Add(Note);
	//memnote->Font->Color = clBlue ;
	Note = "本库存盘点结束，可以进行正常的业务操作！是否导出盘点数据？" ;
	if (MessageBox(0,Note.c_str(),"库存盘点",MB_ICONQUESTION|MB_OKCANCEL)== 1) {
		BtnExport->Click();
	}
	Close();

	/*if (!weipanshu) {
		Note = "是否将未盘书清零？" ;
		if (MessageBox(0,Note.c_str(),"库存盘点",MB_ICONQUESTION|MB_OKCANCEL)== 1) {
			BtnHorizontalTile->Click();
			weipanshu = true;
		}
		else
		{
			Note = "本库存盘点结束，可以进行正常的业务操作！是否导出盘点数据？" ;
			if (MessageBox(0,Note.c_str(),"库存盘点",MB_ICONQUESTION|MB_OKCANCEL)== 1) {
				BtnExport->Click();
			}
			Close();
		}
	}
	else
	{
		Note = "本库存盘点结束，可以进行正常的业务操作！是否导出盘点数据？" ;
		if (MessageBox(0,Note.c_str(),"库存盘点",MB_ICONQUESTION|MB_OKCANCEL)== 1) {
			BtnExport->Click();
		}
		Close();
	} */
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcheckstock::FormClose(TObject *Sender, TCloseAction &Action)
{
   Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnExitClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcheckstock::BtnPrintClick(TObject *Sender)
{
	/* Tfrmstoragecheck *frm = new Tfrmstoragecheck(this,);
	frm->RvSystem1->SystemSetups >>ssAllowSetup;
	frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
	frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
	frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
	frm->RvSystem1->SystemSetups >>ssAllowDestFile;
	frm->RvSystem1->DefaultDest   = rdPrinter ;
	frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;     */


}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnClearClick(TObject *Sender)
{
	String sql;
	String Datestr;
	TADOQuery *aqa = new TADOQuery(this);

	sql = "select Convert(varchar(50),checkdate,111) as d from STK_CheckStockinfo ";
	sql = sql  + " where checkstocknum = '" + Code + "'";
	aqa->Close();
	aqa->SQL->Clear();
	aqa->SQL->Add(sql);
	aqa->Open();
	Datestr = aqa->FieldByName("d")->AsAnsiString ;
    delete aqa;
	RvSystem1->SystemSetups >>ssAllowSetup;
	RvSystem1->SystemSetups >>ssAllowDestPreview;
	RvSystem1->SystemSetups >>ssAllowDestPrinter;
	RvSystem1->SystemSetups >>ssAllowPrinterSetup;
	RvSystem1->SystemSetups >>ssAllowDestFile;
	RvSystem1->DefaultDest  = rdPreview ;
	RvSystem1->SystemSetups<<ssAllowDestPreview;
	RvProject1->ProjectFile = "Project1.rav";
	RvProject1->Open();
   //	RvProject1->SetParam("danhao",Code);
	//RvProject1->SetParam("storage",edtstore->Text);
   //	RvProject1->SetParam("local",cblocal->Text);
   //	RvProject1->SetParam("bk",edtbk->Text);
   //	RvProject1->SetParam("user",edtemploy->Text);
   //	RvProject1->SetParam("date",Datestr);

	RvProject1->Execute();
	RvProject1->Close();

  /*	Tfrmprint1 *frm = new Tfrmprint1(this,connect);
	::ShowWindow(frm->Handle, SW_HIDE);
	 frm->Activeaq(Code);
 // ShowMessage(frm->aqcheckreport->FieldByName("suppliername")->AsAnsiString);

		paramcode = "'" + Code + "'";
		//frm->RvDataSetConnection2->DataSet =
		// frm->RvDataSetConnection2->DoOpen();
	   //	 frm->aqcheckreport->DataSource->DataSet  =  dgcheck->DataSource->DataSet ;




	  //	frm->stockprint->SetParam("danhao",Code);
	   //	frm->stockprint->SetParam("storage",edtstore->Text);
	   //	frm->stockprint->SetParam("local",cblocal->Text);
	  //	frm->stockprint->SetParam("bk",edtbk->Text);
	  //	frm->stockprint->SetParam("user",edtemploy->Text);
	  //	frm->RvDataSetConnection1->DataSet = frm->aqcheckreport;

	  //	ShowMessage(frm->RvDataSetConnection1->DataSet->FieldByName("suppliername")->AsAnsiString) ;
		 frm->Print(0);
   delete frm;   */
}
bool Tfrmcheckstock::DbgridToExcel(TDBGrid* dbg)
{
 	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = "实库盘点-" + cblocal->Text ;
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

	temptext = ",,,实库盘点";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n";
	temptext = temptext + "盘点店,'" + edtstore->Text + ",库位," + cblocal->Text + ",备注," + membk->Text ;
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n\n";

	int t1= 0;
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			//temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			//v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());


	int t2 = dbg->DataSource ->DataSet ->RecordCount ;
	aqueryupdate->DisableControls();
	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					t1++;
					//temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "BookName") {
					t1++;
					AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					//temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + bookname + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "Discount") {
					t1++;
					//temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + "%,";
				}
				else
				{
					t1++;
					//temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	aqueryupdate->EnableControls();
	int h =  aqueryupdate->RecordCount + 4;
    temptext = "\n";
	temptext = temptext + "合计,,,,,,=SUM(G5:G" + IntToStr(h) + "),=SUM(H5:H" + IntToStr(h) + "),=SUM(I5:I" + IntToStr(h) + "),=SUM(J5:J" + IntToStr(h) + "),=SUM(K5:K" + IntToStr(h) + "),=SUM(L5:L" + IntToStr(h) + ")";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcheckstock::BtnExportClick(TObject *Sender)
{
	if (aqueryupdate->Active && aqueryupdate ->RecordCount > 0) {
		DbgridToExcel(dgcheck);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::edtnumberExit(TObject *Sender)
{
  if (edtnumber->Text == "") {
      edtnumber->Text = "0";
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {     //盘点初始化
		Btninit->Click();
	}
	if (Key == VK_F2) {     //开始盘点
		BtnProperties->Click();
	}
	if (Key == VK_F3) {     //盘点修改库存
		BtnViewList->Click();
	}
	if (Key == VK_F4) {     //结束盘点
		BtnViewIcons->Click();
	}
	if (Key == VK_F5) {     //未盘书
		BtnHorizontalTile->Click();
	}
	if (Key == VK_F6) {     //结束本次盘点
		BtnChangeOptions->Click();
	}
	if (Key == VK_F8) {     //导出
		BtnExport->Click();
	}
	if (Key == VK_F11) {     //预览
		BtnClear->Click();
	}
	if (Key == VK_F10) {     //打印
		BtnPrint->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::edsamountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		//float Discountprice = 0,  Fixedprice = 0
		//Fixedprice = (aqueryupdate->FieldByName("Price")->AsFloat)*StrToInt(edtnumber->Text);
		//Discountprice = Fixedprice*(aqueryupdate->FieldByName("Discount")->AsFloat)/100;
		if (edsamount->Text == "") {
        	return;
		}
		if (aqueryupdate->IsEmpty() ) {
			return;
		}
		aqueryupdate->Edit();
		aqueryupdate->FieldByName("damagenum")->AsInteger  = StrToInt(edsamount->Text);
		aqueryupdate->FieldByName("balance")->AsInteger =aqueryupdate->FieldByName("shouldamount")->AsInteger - aqueryupdate->FieldByName("actualamount")->AsInteger-aqueryupdate->FieldByName("damagenum")->AsInteger;
		aqueryupdate->UpdateBatch(arAll);
		aqueryupdate->Active = false;
		aqueryupdate->Active = true;
		((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
		aqueryupdate->Last();
		edsamount->Text = "0";
		aqheader->Active = false;
		aqheader->Active = true;
		edbk->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::edbkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (aqueryupdate->IsEmpty() ) {
			return;
		}
		aqueryupdate->Edit();
		aqueryupdate->FieldByName("bk")->AsString  = edbk->Text;
		aqueryupdate->UpdateBatch(arAll);
		//aqueryupdate->Active = false;
		//aqueryupdate->Active = true;
        edbk->Text = "";
		aqueryupdate->Last();
		aqheader->Active = false;
		aqheader->Active = true;
		edtcheckinfo->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::membkExit(TObject *Sender)
{
	AnsiString sql ;
	if (Code != "") {
		sql  =  "update STK_CheckStockinfo set bk = '" + membk->Text + "' where checkstocknum = '"+ Code +"' and employ  = "+ IntToStr(checkli.userID) +"";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::N5Click(TObject *Sender)
{
	CatalogSearchMode = 4 ;
	lbsearch->Caption = "定价";
	lbsearch->Tag = 4;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnPropertiesClick(TObject *Sender)
{
	if (count == 0) {
		MessageBox(0,"还没进行盘点初始话！","提示" ,MB_OK);
		return;
	}
	int i ;
	int value;
	int stgid;
	String Note,sql;
	String sqlstr;
	int countrecode;
	Btninit->Enabled = false;
	//Note = cblocal->Text + "库位已被锁定,任何对该库位的操作都将禁止！";

	BtnViewIcons->Enabled = true ;
	BtnViewList->Enabled = true;
	if (guanliyuan == 1) {
		BtnHorizontalTile->Enabled = true;
	}
	edtcheckinfo->Enabled = true;
	edtnumber->Enabled = true;

	cblocal->Enabled =  false;

												 //锁定库位
	value =   (int )cblocal->Items->Objects[cblocal->ItemIndex];
	adosp->ProcedureName = "LockLocal";
	adosp->Parameters->Clear();
	adosp->Parameters->CreateParameter("@stgid",ftInteger ,pdInput,sizeof(int), &m_storageID);
	adosp->Parameters->CreateParameter("@localid",ftInteger ,pdInput,sizeof(int), &value);
	adosp->ExecProc();

	adosp->ProcedureName = "LocalCount";    //最得总记录数
	adosp->Parameters->Clear();
	adosp->Parameters->CreateParameter("@localiD",ftInteger ,pdInput,sizeof(int), &value);
	adosp->Parameters->CreateParameter("@count",ftInteger  ,pdOutput ,sizeof(int), &countrecode);
	adosp->ExecProc();

	//lbcount->Caption = "当前库位共有 " + adosp->Parameters->ParamByName("@count")->Value+" 品种";

	if (Code =="") {   //是否有没有盘点完成的单子
					  //新的盘点开始
		Code = NoteCode::BuildCode(aquery,GetDBTime(aquery),m_storageID,"STK_CheckStockinfo","checkstockNum");
		sql = "insert into STK_CheckStockinfo (checkstockNum ,checkstore,checkstocklocal,checkdate,bk,employ,state)"
		" values('" + Code + "'," + IntToStr(m_storageID) + "," + IntToStr((int )cblocal->Items->Objects[cblocal->ItemIndex])
		+ ",'" + DateTimeToStr(Now())+"','" + membk->Text.Trim()+ "'," + checkli.userID +",1)";

		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
		aqueryupdate->Parameters->ParamByName("stocknum")->Value = Code;
		aqueryupdate->Active = true;
		((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";


		sql = "select ID,checkstockNum,totalamount,Fixedprice,Discountprice from STK_CheckStockinfo where checkstockNum = '" + Code + "'";
		aqheader->Close();
		aqheader->SQL->Clear();
		aqheader->SQL->Add(sql);
		aqheader->Open();

		editnum->Text = Code;
	}
	editstate->Text = "正在盘点";
	BtnProperties->Enabled = false;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = " insert into BS_PandianCount(state,pancount,CodeStr,stgid) values (0," + IntToStr(count) + ",'" + Code + "'," + IntToStr(m_storageID) +")";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtninitClick(TObject *Sender)
{
	if (count > 0) {
		MessageBox(0,"盘点已经初始化，若要重新初始化盘点请先结束本次盘点！","提示" ,MB_OK);
		return;
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select max(pancount) + 1 as count from BS_PandianCount where stgid = " + IntToStr(m_storageID) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	if (aq->FieldByName("count")->AsAnsiString == "" ) {
		count = 1;
	}
	else
	{
		count = aq->FieldByName("count")->AsInteger ;
	}
	sql = " insert into BS_PandianCount(state,pancount,stgid) values (0," + IntToStr(count) + "," + IntToStr(m_storageID) + ")";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	BtnProperties->Enabled = true;
	BtnChangeOptions->Enabled = true;
	Btninit->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnChangeOptionsClick(TObject *Sender)
{
	if (count == 0) {
		MessageBox(0,"当前无盘点进行！","提示" ,MB_OK);
		return;
	}
	AnsiString sql;
	sql = "select STK_CheckStockinfo.* from STK_CheckStockinfo join BS_PandianCount "
			 " on STK_CheckStockinfo.checkstockNum = BS_PandianCount.CodeStr "
			 " and STK_CheckStockinfo.state = 1 and BS_PandianCount.stgid = " +  IntToStr(m_storageID);
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (aquery->RecordCount > 0) {
		MessageBox(0,"还有盘点单未结束，请先结束盘点单！","提示" ,MB_OK);
		return;
	}
	if (MessageBox(0,"确定要结束本次盘点？","提示",MB_ICONQUESTION|MB_OKCANCEL)!= 1) {
		return;
	}

	if (!weipanshu) {
		if (MessageBox(0,"是否将未盘书清零？","库存盘点",MB_ICONQUESTION|MB_OKCANCEL)== 1) {
			BtnHorizontalTile->Click();
			weipanshu = true;
		}
		else
		{
        	EndPandian();
		}
	}
	else
	{
		EndPandian();
	}
}
//---------------------------------------------------------------------------
void  Tfrmcheckstock::EndPandian()
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = " update STK_CheckStockinfo set state = 0 where checkstocknum in (select CodeStr from BS_PandianCount where state = 0 and stgid = " + IntToStr(m_storageID) + ") ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = " update BS_PandianCount set state = 1 where state = 0 and stgid = " + IntToStr(m_storageID) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	Close();
}
//---------------------------------------------------------------------------


