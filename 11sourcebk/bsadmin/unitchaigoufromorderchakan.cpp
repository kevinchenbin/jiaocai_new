//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include   <FileCtrl.hpp>
#include "unitchaigoufromorderchakan.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzBckgnd"
#pragma link "RzStatus"
#pragma link "RzPrgres"
#pragma resource "*.dfm"
Tfrmdaochu *frmdaochu;
//---------------------------------------------------------------------------
__fastcall Tfrmdaochu::Tfrmdaochu(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaochu::SpeedButton2Click(TObject *Sender)
{
	UnicodeString title;
	title = "ѡ���ļ���";
  //	SelectDirectory(
	if (SelectDirectory(title,"",Path))
	{
		if (Path != "") {
   //	rp->Visible = true;
			ExcelOut();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaochu::SpeedButton1Click(TObject *Sender)
{
	 ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void Tfrmdaochu::ExcelOut()
{
	DanHao = StringReplace(DanHao,":",",",TReplaceFlags()<<rfReplaceAll);
	AnsiString sql,sql1 ;
	Variant xWorkbook,Workbooks,vSheet,R,QueryTables,Table;
	Variant app;
	AnsiString temptext,tableName,tmpordercode,tmpclientname;
	int c,pc;
	try
	{
		TADOQuery *aq = new TADOQuery(Application);
		aq->Connection = fcn;

		sql1 = "select C.Name,sys_user.name as username,sys_user.tel as usertel,C.fax,C.address,C.contact,C.Telephone,procureNtCode,P.Remarks,P.TotalAmount,P.FixedPrice,P.DiscountedPrice,CONVERT(varchar, hdtime, 23 ) as hdtime,fixedprice,discountedprice,remarks,addcosts,totalamount from dbo.BS_ProcureNoteHeader P ";
        sql1 = sql1 + " join sys_user on P.OperatorID = sys_user.id";
		sql1 = sql1 + " join CUST_CustomerInfo C ON P.supplierid = C.ID where ProcureNtCode in(" + DanHao+")";

		TADOQuery *aq1 = new TADOQuery(Application);
		aq1->Connection = fcn;
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql1);
		aq1->Open();
		pc = 0;
		rp->TotalParts = aq1->RecordCount ;;
		float d;
		d =  	100/rp->TotalParts;
		while(!aq1->Eof)
		{
			c = 0;
			c++;
			tableName = aq1->FieldByName("Name")->AsAnsiString.Trim() ;
			if (tableName == "��ͨ��Ӧ��") {
				tableName = tableName + IntToStr(c) ;
			}
			if (!DirectoryExists(Path+"\\" + FormatDateTime("YYYY-mm-dd",Now())+" �ɹ���")) {
				CreateDir(Path+"\\" + FormatDateTime("YYYY-mm-dd",Now())+" �ɹ���");
			}

			tableName = tableName ;
			if (Path.Length() > 3  ) {
				tableName  = Path +"\\"+ FormatDateTime("YYYY-mm-dd",Now())+" �ɹ���"+ "\\" + tableName + aq1->FieldByName("procureNtCode")->AsAnsiString + "�ɹ���.xls";
			}
			else
			{
				tableName  = Path + FormatDateTime("YYYY-mm-dd",Now())+" �ɹ���"+ "\\" + tableName + aq1->FieldByName("procureNtCode")->AsAnsiString + "�ɹ���.xls";
			}

			Variant  v,vSheet,R,xWorkbook;
			v   =Variant::CreateObject("Excel.Application");
			v.OlePropertySet("Visible",true);
			v.OlePropertyGet("WorkBooks").OleFunction("Add");
			xWorkbook = v.OlePropertyGet("ActiveWorkBook");
			vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");

            sql  = "select rank() over(order by D.id) as '���',CA.ISBN,CA.Name as '����',CA.UserDefCode as '�Ա���',Press.AbbreviatedName as '������',CA.presscount as '���',CA.Price as '����',CA.Author as '����',D.Amount as '����',D.Discount as '�ۿ�',D.FixedPrice as '����',D.DiscountedPrice as 'ʵ��',D.ordercode as '������',D.clientname as '������λ' from BS_ProcureNoteHeader P left join CUST_CustomerInfo ";
			sql = sql +  " C on P.supplierid = C.ID join dbo.BS_ProcureNote D on P.ID = D.procureNtHeaderID ";
			sql = sql + " join dbo.BS_BookCatalog CA on D.bkcatalogid = CA.ID left join dbo.BS_PressInfo Press ON CA.PressID = Press.ID where ProcureNtCode = " + aq1->FieldByName("procureNtCode")->AsAnsiString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();

			int t2 = aq ->RecordCount ;

			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",1,1),vSheet.OlePropertyGet("Cells",t2+11,14)); //ȡ�úϲ�������
			R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
			R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

			v.OlePropertyGet("Cells",1,1).OlePropertySet("Value",printtitle .c_str() );

			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",1,1),vSheet.OlePropertyGet("Cells",2,14)); //ȡ�úϲ�������
			R.OleProcedure("Merge");
			R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Bold",true);
			R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Name","����");   //����
			R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("size",16);
			R.OlePropertySet("HorizontalAlignment",3);

			temptext = "��ϵ�ˣ�" + aq1->FieldByName("username")->AsAnsiString;
			v.OlePropertyGet("Cells",3,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,1),vSheet.OlePropertyGet("Cells",3,4)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "�绰��" + aq1->FieldByName("usertel")->AsAnsiString;
			v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,5),vSheet.OlePropertyGet("Cells",3,14)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "��ַ��" + address;
			v.OlePropertyGet("Cells",4,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",4,1),vSheet.OlePropertyGet("Cells",4,14)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "�ɹ����ţ�" + aq1->FieldByName("procureNtCode")->AsAnsiString;
			v.OlePropertyGet("Cells",5,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",5,1),vSheet.OlePropertyGet("Cells",5,4)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "��Ӧ�����ƣ�" + aq1->FieldByName("Name")->AsAnsiString;
			v.OlePropertyGet("Cells",5,5).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",5,5),vSheet.OlePropertyGet("Cells",5,8)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "��ϵ�ˣ�"+ aq1->FieldByName("contact")->AsAnsiString;
			v.OlePropertyGet("Cells",5,9).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",5,9),vSheet.OlePropertyGet("Cells",5,14)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "�ɹ����ڣ�" +  aq1->FieldByName("hdtime")->AsAnsiString;
			v.OlePropertyGet("Cells",6,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",6,1),vSheet.OlePropertyGet("Cells",6,4)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "��Ӧ�̵绰��" + aq1->FieldByName("Telephone")->AsAnsiString;
			v.OlePropertyGet("Cells",6,5).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",6,5),vSheet.OlePropertyGet("Cells",6,8)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "���棺"+ aq1->FieldByName("fax")->AsAnsiString;
			v.OlePropertyGet("Cells",6,9).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",6,9),vSheet.OlePropertyGet("Cells",6,14)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "��ע��" + aq1->FieldByName("Remarks")->AsAnsiString;
			v.OlePropertyGet("Cells",7,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",7,1),vSheet.OlePropertyGet("Cells",7,14)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "��Ӧ�̵�ַ��"+ aq1->FieldByName("address")->AsAnsiString;
			v.OlePropertyGet("Cells",8,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",8,1),vSheet.OlePropertyGet("Cells",8,14)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "��Ʒ�֣�" +  IntToStr(t2) ;
			v.OlePropertyGet("Cells",9,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",9,1),vSheet.OlePropertyGet("Cells",9,4)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "��������" + aq1->FieldByName("TotalAmount")->AsAnsiString;
			v.OlePropertyGet("Cells",9,5).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",9,5),vSheet.OlePropertyGet("Cells",9,8)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "������"+ aq1->FieldByName("FixedPrice")->AsAnsiString;
			v.OlePropertyGet("Cells",9,9).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",9,10),vSheet.OlePropertyGet("Cells",9,14)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,3),vSheet.OlePropertyGet("Cells",t2+10,3)); //ȡ�úϲ�������  ��
			R.OlePropertySet("WrapText", true);//����ָ�����������еĵ�Ԫ���е��ı��Զ�����

			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,14),vSheet.OlePropertyGet("Cells",t2+10,14)); //ȡ�úϲ�������  ��
			R.OlePropertySet("WrapText", true);//����ָ�����������еĵ�Ԫ���е��ı��Զ�����

            QueryTables   =   vSheet.OlePropertyGet("QueryTables");

			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,1),vSheet.OlePropertyGet("Cells",11+t2,14)); //ȡ�úϲ�������
			Table   =   QueryTables.OleFunction("Add",aq->Recordset,R);
			Table.OlePropertySet("FieldNames",   true);
			Table.OleProcedure("Refresh",   true);

			v.OlePropertyGet("Cells",t2+11,1).OlePropertySet("Value","�ϼ�");
			temptext = aq1->FieldByName("TotalAmount")->AsAnsiString;
			v.OlePropertyGet("Cells",t2+11,9).OlePropertySet("Value",temptext .c_str() );
			temptext = aq1->FieldByName("FixedPrice")->AsAnsiString;
			v.OlePropertyGet("Cells",t2+11,11).OlePropertySet("Value",temptext .c_str() );
			temptext = aq1->FieldByName("DiscountedPrice")->AsAnsiString;
			v.OlePropertyGet("Cells",t2+11,12).OlePropertySet("Value",temptext .c_str() );

			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,11),vSheet.OlePropertyGet("Cells",t2+11,12)); //ȡ�úϲ�������  ��
			R.OlePropertySet("NumberFormatLocal", "0.00");//����ָ�������е����е�Ԫ���ʽΪС���ٷֱ�

			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,7),vSheet.OlePropertyGet("Cells",t2+11,7)); //ȡ�úϲ�������  ��
			R.OlePropertySet("NumberFormatLocal", "0.00");//����ָ�������е����е�Ԫ���ʽΪС���ٷֱ�

			temptext = "�Ƶ�Ա��" + aq1->FieldByName("username")->AsAnsiString;
			v.OlePropertyGet("Cells",t2+12,1).OlePropertySet("Value",temptext .c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+12,1),vSheet.OlePropertyGet("Cells",t2+12,14)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "�ջ���ϵ�ˣ�" + shcontact ;
			v.OlePropertyGet("Cells",t2+13,1).OlePropertySet("Value",temptext .c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+13,1),vSheet.OlePropertyGet("Cells",t2+13,14)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "�ջ���ϵ�绰��" + shtel ;
			v.OlePropertyGet("Cells",t2+14,1).OlePropertySet("Value",temptext .c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+14,1),vSheet.OlePropertyGet("Cells",t2+14,14)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			temptext = "�ջ���ַ��" + shaddress ;
			v.OlePropertyGet("Cells",t2+15,1).OlePropertySet("Value",temptext .c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+15,1),vSheet.OlePropertyGet("Cells",t2+15,14)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			v.OlePropertyGet("Cells",t2+16,1).OlePropertySet("Value",printbk .c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+16,1),vSheet.OlePropertyGet("Cells",t2+16,14)); //ȡ�úϲ�������
			R.OleProcedure("Merge");

			if (FileExists(tableName) ) {
				DeleteFileA(tableName);
			}
			try {
				xWorkbook.OleFunction("SaveAs",WideString(tableName));
			} catch (...) {
			}

		v.OleFunction("Quit");
		v = Unassigned;
		aq1->Next();
		pc = pc + d;
		rp->Percent =pc ;
		}

	}
	catch(Exception &e)
	{
		MessageBox(0,e.Message.t_str() ,"����",MB_ICONERROR);
		return;
	}
	rp->Percent = 100;
	MessageBox(0,"�ѳɹ�������","��ʾ",MB_ICONWARNING);
}

void Tfrmdaochu::init(TADOConnection *cn,int stgid)
{
	fcn = cn;
	AnsiString sql;
	TADOQuery *query = new TADOQuery(this);
	query->Connection = cn;
	sql = "select cgprinttitle,cgcontact,cgtel,cgaddress,cgprintbk,shaddress,shcontact,shtel from sys_printtitle where stgid = " + IntToStr(stgid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	printbk = query->FieldByName("cgprintbk")->AsAnsiString ;
	printtitle = query->FieldByName("cgprinttitle")->AsAnsiString ;
	address = query->FieldByName("cgaddress")->AsAnsiString ;
	shaddress = query->FieldByName("shaddress")->AsAnsiString ;
	shtel = query->FieldByName("shtel")->AsAnsiString ;
	shcontact = query->FieldByName("shcontact")->AsAnsiString ;
	delete query;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaochu::FormShow(TObject *Sender)
{
    Memo1->Lines->Add(info);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaochu::SpeedButton3Click(TObject *Sender)
{
	ModalResult = mrCancel ;
}
//---------------------------------------------------------------------------

