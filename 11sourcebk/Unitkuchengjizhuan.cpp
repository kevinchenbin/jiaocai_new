//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitkuchengjizhuan.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmkuchenjizhuan *frmkuchenjizhuan;
//---------------------------------------------------------------------------
__fastcall Tfrmkuchenjizhuan::Tfrmkuchenjizhuan(TComponent* Owner,TADOConnection *fcn,int userid,int stgid)
	: TForm(Owner)
{
   aq->Connection = fcn;

     fuserid=userid;
     fstgid= stgid;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmkuchenjizhuan::SpeedButton1Click(TObject *Sender)

{

    AnsiString sql;
       sql = "exec kuchunjizhuan "+IntToStr(fuserid)+","+IntToStr(fstgid)+",'"+membk->Text+"'";
       try
       {

       Screen->Cursor= crHourGlass;
        aq->Close();
        aq->SQL->Clear();
        aq->SQL->Add(sql);
        aq->ExecSQL();
        Screen->Cursor = crDefault;
         MessageBox(0,"����ת�ɹ�!" ,"��������ʾ" ,MB_ICONINFORMATION|MB_OK);


       }catch(...)
       {
          ShowMessage("����תʧ��!������");
       }
}
//---------------------------------------------------------------------------
