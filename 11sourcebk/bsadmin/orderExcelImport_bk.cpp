//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "orderExcelImport.h"
#include "orderimportselect.h"
#include "pdutil.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma link "ModalDialog"
#pragma link "RzRadChk"
#pragma link "RzRadGrp"
#pragma link "RzShellDialogs"
#pragma link "RzPrgres"
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
TfrmExcelImport *frmExcelImport;
//---------------------------------------------------------------------------
__fastcall TfrmExcelImport::TfrmExcelImport(TComponent* Owner,TADOConnection *con,int headid)
	: TForm(Owner)
{
   Import= true;
   aq->Connection = con;
   aq->Active = false;
   aq->Active = true;
   headerid = headid;
   query->Connection = con;
   comAddcatalog->Connection = con;
}

//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::spselectpathClick(TObject *Sender)
{
	if (opndlgExcelPath->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(opndlgExcelPath->FileName .c_str()  );
		Name = ExtractFileName(opndlgExcelPath->FileName .c_str() );
		DBPath = DBPath + Name;
		edtExcelPath->Text = DBPath;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::BtnImportClick(TObject *Sender)
{
	if(edtExcelPath->Text == "")
		return;
	/*if (!chisbn->Checked && !chname->Checked && !chprice->Checked && !chauthor->Checked && !chpress->Checked && !chpresscount->Checked && !chamount->Checked && !chdiscount->Checked && !chbk->Checked  ) {
		return;
	} */
	if (!chname->Checked ) {
        MessageBoxA(0,"����Ϊ��ѡ�","����",MB_ICONEXCLAMATION);
		return;
	}

	Variant vExcelApp,vSheet,Wb;
	vExcelApp = Variant::CreateObject("Excel.Application");
	AnsiString s = ExtractFilePath(opndlgExcelPath->FileName .c_str());
	s = s + ExtractFileName(opndlgExcelPath->FileName .c_str() );
	vExcelApp.OlePropertyGet("WorkBooks").OleProcedure("Open",s.c_str()   );// opndlgExcelPath->f  FileName .c_str() );
	Wb = vExcelApp.OlePropertyGet("ActiveWorkBook");
	vSheet = Wb.OlePropertyGet("ActiveSheet");
	vSheet.OlePropertySet("name","11");
	Wb.OleProcedure("Save");

	//String sql = "select * from " + ExtractFileName(opndlgExcelPath->FileName .c_str() ) ;
	//EXCEL����
	AnsiString sql = "select * from [11$]";

	AnsiString str = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	//EXCEL����
	str = str + edtExcelPath->Text ;
	str = str + ";Mode=Read;Extended Properties=\"Excel 8.0;HDR=Yes;IMEX=1\";" ;

	//CSV����
	//str = str + ExtractFilePath(opndlgExcelPath->FileName .c_str()) ;
	//str = str + ";Mode=Read;Extended Properties=\"text;HDR=Yes;IMEX=1;FMT=Delimited\";" ;

	con1->ConnectionString = "";
	try
	{
		con1->ConnectionString =  str ;
	}
	catch(...)
	{
		MessageBoxA(0,"�������Ѿ����룡","Excel����",MB_ICONEXCLAMATION);
		Import = true;
		return;
	}
	con1->LoginPrompt = false;
	con1->ConnectOptions = coConnectUnspecified ;
	con1->KeepConnection = true;
	con1->Mode = cmRead;
	try
	{
		 con1->Connected = true;
	}
	catch(...)
	{
		MessageBoxA(0,"����Դ���ô���","Excel����",MB_ICONHAND);
		Import= true;
		return;
	}
	qry->Connection = con1;
	qry->Active = false;
	qry->SQL->Clear();
	qry->SQL ->Add(sql);
	qry->Active = true;
	ds->DataSet = qry;

	//	con1->Connected =false;
	//	vExcelApp.OlePropertyGet("ActiveWorkBook").OleProcedure("Close");
	//	vExcelApp.OleFunction("Quit");

	Import= false;
	Label1->Caption = "���س���¼" + IntToStr(qry->RecordCount) + "��";
	Label2->Visible = true;
	Sleep(10);
	int inportamount = 0;
	int n = 0;
	while (!qry->Eof)
	{
		int bkcatalogid = -1,amount = 0,  pressindex = 2;
		bool newbook = false;
		float discount = 100.00,FixedPrice = 0.0,DiscountedPrice = 0.0,jprice = 0.0,Price = 0.0;
		AnsiString ISBN,ISBN1,Name,PressName,Author,remarks,xuexiao,classname,barcode,Num,xiaoqu,xueyuan,course,incode,teacher,telphone;
		try {
			Name = qry->FieldByName("����")->AsString ;
			Name = Name.Trim();
		} catch (...) {
			MessageBoxA(0,"��ȷ�ϵ����ļ����Ƿ����'����'�У�","�������",MB_ICONEXCLAMATION);
			Import= true;
			Label2->Visible = false;
			qry->Close();
			con1->Connected =false;
			vExcelApp.OleProcedure("Quit");
			vExcelApp = Unassigned;
			return;
		}
		if (chxuexuao->Checked ) {
			try {
				xuexiao = qry->FieldByName("ѧУ���")->AsAnsiString ;
			} catch (...) {
			}
		}
		if (chclass->Checked ) {
			try {
				classname = qry->FieldByName("�༶")->AsAnsiString ;
			} catch (...) {
			}
		}
		if (chisbn->Checked ) {
			try {
				ISBN = qry->FieldByName("ISBN")->AsString.Trim() ;
			} catch (...) {
			}
		}
		if (chprice->Checked ) {
			try {
				Price = qry->FieldByName("����")->AsFloat ;
			} catch (...) {
				Price = 0;
			}
		}
		if (chauthor->Checked ) {
 			try {
				Author = qry->FieldByName("����")->AsAnsiString;
			} catch (...) {
			}
		}
		if (chpress->Checked ) {
			try {
				PressName = qry->FieldByName("������")->AsAnsiString.Trim() ;
			} catch (...) {
			}
		}

		if (chpresscount->Checked ) {
			try {
				Num = qry->FieldByName("���")->AsAnsiString ;
			} catch (...) {
			}
		}
		if (chamount->Checked ) {
			try {
				if (qry->FieldByName("����")->AsAnsiString != "") {
					amount = qry->FieldByName("����")->AsInteger ;
				}
			} catch (...) {
				MessageBoxA(0,"��ȷ�ϵ����ļ����Ƿ����'����'�л������Ƿ���ȷ��","�������",MB_ICONEXCLAMATION);
				Import= true;
				Label2->Visible = false;
				qry->Close();
				con1->Connected =false;
				vExcelApp.OleProcedure("Quit");
				vExcelApp = Unassigned;
				return;
			}
		}
		if (chdiscount->Checked ) {
			try {
				discount = qry->FieldByName("�ۿ�")->AsFloat ;
			} catch (...) {
				discount = 100;
			}
		}
		if (chbk->Checked ) {
			try {
				remarks = qry->FieldByName("��ע")->AsString ;
			} catch (...) {
			}
		}
		if (chxiaoqu->Checked ) {
			try {
				xiaoqu = qry->FieldByName("У��")->AsAnsiString;
			} catch (...) {
			}
		}
		if (chxueyuan->Checked ) {
			try {
				xueyuan = qry->FieldByName("ѧԺ")->AsAnsiString;
			} catch (...) {
			}
		}
		if (chcourse->Checked ) {
			try {
				course = qry->FieldByName("�γ�����")->AsAnsiString;
			} catch (...) {
			}
		}
		if (chincode->Checked ) {
			try {
				incode = qry->FieldByName("�ڲ�ʶ����")->AsAnsiString;
			} catch (...) {

			}
		}
		if (chteacher->Checked ) {
			try {
				teacher = qry->FieldByName("�ον�ʦ")->AsAnsiString;
			} catch (...) {

			}
		}
		if (chtelphone->Checked ) {
			try {
				telphone = qry->FieldByName("��ϵ��ʽ")->AsAnsiString;
			} catch (...) {
			}
		}
		if (Name != "") {
			FixedPrice =  Price*amount;
			DiscountedPrice = Price*amount*discount/100;

			sql = "insert into BS_OrderNote(OrderNtHeaderID,Amount,UnsendAmount,Discount,FixedPrice,DiscountedPrice,bk,xuxiao,class,"
				"xiaoqu,xueyuan,course,incode,teacher,telphone,ISBN,Name,Price,Author,Press,PressCount) values(" + IntToStr(headerid) + "," +
				IntToStr(amount) + "," + IntToStr(amount) + "," + FloatToStr(discount) + "," + FloatToStr(FixedPrice) + "," + FloatToStr(DiscountedPrice) +
				",'" + remarks + "','" + xuexiao + "','" + classname + "','" + xiaoqu + "','" + xueyuan + "','" + course + "','" + incode +
				"','" + teacher + "','telphone" + "','" + ISBN + "','" + Name + "'," + FloatToStr(Price) + ",'" + Author + "','" + PressName + "','" + Num + "')";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			try {
				aq->ExecSQL();
				inportamount = inportamount + 1;
			} catch (...) {
            	try {
					vExcelApp.OlePropertyGet("Cells",2+n,1).OlePropertySet("Value","����ʧ��" );
				} catch (...) {
				}
			}

			/*if (aq->State != dsInsert) {
				aq->Append();
			}
			aq->FieldByName("OrderNtHeaderID")->AsInteger = headerid;
			aq->FieldByName("Amount")->AsInteger =  amount;
			aq->FieldByName("UnsendAmount")->AsInteger = amount;
			aq->FieldByName("Discount")->AsFloat = discount;
			aq->FieldByName("FixedPrice")->AsFloat = FixedPrice ;
			aq->FieldByName("DiscountedPrice")->AsFloat = DiscountedPrice ;
			aq->FieldByName("bk")->AsString = remarks;
			aq->FieldByName("xuxiao")->AsString = xuexiao;
			aq->FieldByName("class")->AsString = classname;
			aq->FieldByName("newbook")->AsBoolean  = newbook;
			aq->FieldByName("xiaoqu")->AsString = xiaoqu;
			aq->FieldByName("xueyuan")->AsString = xueyuan;
			aq->FieldByName("course")->AsString = course;
			aq->FieldByName("incode")->AsString = incode;
			aq->FieldByName("teacher")->AsString = teacher;
			aq->FieldByName("telphone")->AsString = telphone;
			aq->FieldByName("ISBN")->AsAnsiString = ISBN;
			aq->FieldByName("Name")->AsAnsiString = Name;
			aq->FieldByName("Price")->AsAnsiString = jprice;
			aq->FieldByName("Author")->AsAnsiString = Author;
			aq->FieldByName("Press")->AsAnsiString = PressName;
			aq->FieldByName("PressCount")->AsAnsiString = Num;
			try {
				aq->Post();
				inportamount = inportamount + 1;
			} catch (Exception &E) {
				try {
					vExcelApp.OlePropertyGet("Cells",2+n,1).OlePropertySet("Value","����ʧ��" );
				} catch (...) {
				}
			}*/

		}
		qry->Next();
		n = n + 1;
	}
	Label1->Caption = "���س���¼" + IntToStr(qry->RecordCount) + "��������" + IntToStr(inportamount) + "����¼��" ;
	Label2->Visible = false;
	AnsiString message;
	message = "���ݵ���ɹ����ܹ�����" + IntToStr(inportamount) + "����¼��" ;
	MessageBoxA(0,message.c_str(),"Excel����",MB_ICONEXCLAMATION);
	Import= true;

	//Wb.OleProcedure("Save");
	Wb.OleProcedure("Close");
	con1->Connected =false;
	vExcelApp.OleProcedure("Quit");
	vExcelApp = Unassigned;

	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::BtnExitClick(TObject *Sender)
{
  if (Import) {
	  Close();
  }else
  {
	  MessageBoxA(0,"���ڵ����У������˳���","Excel����",MB_ICONASTERISK);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F7) {     //����
		BtnImport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------
AnsiString TfrmExcelImport::GetNum(AnsiString Anstr)
{	AnsiString strnum;	for(int i=1;i<=Anstr.Length();i++)	{		if((Anstr[i] >= '0' && Anstr[i] <= '9') || Anstr[i] == 'X' || Anstr[i] == 'x' )		{		 	strnum = strnum + Anstr[i];		}	}	return strnum;}//---------------------------------------------------------------------------


