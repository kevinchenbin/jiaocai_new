//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitlock.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmlock *frmlock;
//---------------------------------------------------------------------------
__fastcall Tfrmlock::Tfrmlock(TComponent* Owner,TADOConnection *fcn,int fstgid)
	: TForm(Owner)
{
 aq->Connection =fcn ;
 stgid = fstgid;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmlock::FormShow(TObject *Sender)
{
//
   AnsiString sql = "select * from sys_lock_table";
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   while(!aq->Eof)
   {
      if (aq->FieldByName("lockname")->AsAnsiString == "supplier") {
           sadd->Checked =  aq->FieldByName("lockadd")->AsBoolean;
           smodify->Checked = aq->FieldByName("lockmodify")->AsBoolean;
           sdel->Checked =  aq->FieldByName("lockdel")->AsBoolean;

      }
      if (aq->FieldByName("lockname")->AsAnsiString == "client") {
                cadd->Checked =  aq->FieldByName("lockadd")->AsBoolean;
                cmodify->Checked =  aq->FieldByName("lockmodify")->AsBoolean;
                cdel->Checked = aq->FieldByName("lockdel")->AsBoolean;
      }
       if (aq->FieldByName("lockname")->AsAnsiString == "bookcatalog") {
                badd->Checked =  aq->FieldByName("lockadd")->AsBoolean;
                bmodify->Checked= aq->FieldByName("lockmodify")->AsBoolean;
                bdel->Checked=  aq->FieldByName("lockdel")->AsBoolean;
      }
     aq->Next();
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrmlock::SpeedButton2Click(TObject *Sender)
{
   //
   AnsiString sql1,sql2,sql3;
   AnsiString v1,v2,v3;
   v1="0";
   v2="0";
   v3="0";

   if (sadd->Checked) {
     v1="1";
   }
   if (smodify->Checked) {
     v2="1";
   }
   if (sdel->Checked) {
     v3="1";
   }
     sql1 =Format("update sys_lock_table set lockadd=%s,lockmodify=%s,lockdel=%s where lockname='%s' and stgid = %d",
     ARRAYOFCONST((v1.c_str(), v2.c_str(), v3.c_str(), "supplier",stgid)));

    v1="0";
   v2="0";
   v3="0";
   if (cadd->Checked) {
     v1="1";
   }
   if (cmodify->Checked) {
     v2="1";
   }
   if (cdel->Checked) {
     v3="1";
   }
   sql2 =Format("update sys_lock_table set lockadd=%s,lockmodify=%s,lockdel=%s where lockname='%s' and stgid = %d",
      ARRAYOFCONST((v1.c_str(), v2.c_str(), v3.c_str(), "client",stgid)));
    v1="0";
   v2="0";
   v3="0";
   if (badd->Checked) {
     v1="1";
   }
   if (bmodify->Checked) {
     v2="1";
   }
   if (bdel->Checked) {
     v3="1";
   }
    sql3 =Format("update sys_lock_table set lockadd=%s,lockmodify=%s,lockdel=%s where lockname='%s' and stgid = %d",
    ARRAYOFCONST((v1.c_str(), v2.c_str(), v3.c_str(), "bookcatalog",stgid)));


        try
        {
               aq->Close();
               aq->SQL->Clear();
               aq->SQL->Add(sql1);
               aq->SQL->Add(sql2);
               aq->SQL->Add(sql3);
               aq->ExecSQL();
               ShowMessage("±£´æ³É¹¦!");
      }
      catch(...)
      {
      }

}
//---------------------------------------------------------------------------
void __fastcall Tfrmlock::SpeedButton1Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmlock::FormClose(TObject *Sender, TCloseAction &Action)
{
   Action = caFree;
}
//---------------------------------------------------------------------------

