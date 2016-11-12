//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectPressForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "PressAdminForm"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzShellDialogs"
#pragma link "RzLine"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma resource "*.dfm"
TfrmSelectPress *frmSelectPress;
//---------------------------------------------------------------------------
__fastcall TfrmSelectPress::TfrmSelectPress(TComponent* Owner)
	: TfrmPressAdmin(Owner)
	, m_id(0)
{
}
//---------------------------------------------------------------------------

int TfrmSelectPress::GetSelectID()
{
	return m_id;
}
String TfrmSelectPress::GetSelectName()
{
    return m_name;
}
void __fastcall TfrmSelectPress::rzdbgrdPressDblClick(TObject *Sender)
{
	//
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectPress::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (dsetPress->Active)
	{
		m_id = StrToInt(dsetPress->FieldByName("PresentNum")->AsString );
		m_name = dsetPress->FieldByName("abbreviatedname")->AsAnsiString ;
	}
	this->ModalResult = mrOk;
	TfrmPressAdmin::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------


void __fastcall TfrmSelectPress::rzdbgrdPressCellClick(TColumn *Column)
{
	if (dsetPress->Active)
	{
		m_id = StrToInt(dsetPress->FieldByName("PresentNum")->AsString) ;
		m_name = dsetPress->FieldByName("abbreviatedname")->AsAnsiString ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectPress::dsetPressMoveComplete(TCustomADODataSet *DataSet,
          const TEventReason Reason, const Error *Error, TEventStatus &EventStatus)

{
	if (DataSet->Active)
	{
		m_id = StrToInt(DataSet->FieldByName("PresentNum")->AsString) ;
		m_name = dsetPress->FieldByName("abbreviatedname")->AsAnsiString ;
	}
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------


void __fastcall TfrmSelectPress::btnExit4Click(TObject *Sender)
{
	//Excel导出
	if (dsetPress->Active && dsetPress->RecordCount > 0) {
		DbgridToExcel(dbgrdPress);
	}
}
//Excel导出函数
bool __fastcall TfrmSelectPress::DbgridToExcel(TRzDBGrid* dbg)
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
	v.OlePropertyGet("Cells",1,4).OlePropertySet("Value","出版社管理" );

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




