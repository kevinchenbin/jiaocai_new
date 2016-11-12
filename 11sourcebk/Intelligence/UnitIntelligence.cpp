//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitIntelligence.h"
#include "UnitSelectCondition.h"
//#include "Unitbidetail.h"
//#include "UnitSelectOrder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmIntelligence *frmIntelligence;
//---------------------------------------------------------------------------
__fastcall TfrmIntelligence::TfrmIntelligence(TComponent* Owner,LandInfo *li)
	: TForm(Owner)
{
   ID = -1;
   fcon = li->con ;
   m_stogeID = li->storageID ;
   StoreSelect->Connection = fcon;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIntelligence::sbselectClick(TObject *Sender)
{
  Tfrmselectcondition * frm  = new Tfrmselectcondition(Application);
  if (ID != -1) {
	  String sql = "select * from bsi_procure where ID = " + IntToStr(ID) ;
	  TADOQuery *aq = new TADOQuery(Application);
	  aq->Connection = fcon ;
	  aq->Close();
	  aq->SQL->Clear();
	  aq->SQL->Add(sql);
	  aq->Open();
	  frm->cbclient->Checked = aq->FieldByName("ClientOrder")->AsBoolean ;
	  frm->cbinside->Checked = aq->FieldByName("InsideOrder")->AsBoolean ;
	  frm->cbnet->Checked =  aq->FieldByName("NetOrder")->AsBoolean ;
	  frm->cbsale->Checked = aq->FieldByName("sale")->AsBoolean ;
	  if (frm->cbsale->Checked ) {
		  frm->cbtime->ItemIndex =  aq->FieldByName("time")->AsInteger  ;
	  }else
	  {

         frm->cbtime->Enabled = false;

	  }
	  delete aq;
  }
  if ( mbOK == frm->ShowModal())
  {
	   
		StoreSelect->Parameters->ParamByName("@ClientOrder")->Value = (byte)frm->cbclient->Checked ;
		StoreSelect->Parameters->ParamByName("@NetOrder")->Value = (byte)frm->cbnet->Checked ;
		StoreSelect->Parameters->ParamByName("@InsideOrder")->Value = (byte)frm->cbinside->Checked ;
		StoreSelect->Parameters->ParamByName("@sale")->Value = (byte)frm->cbsale->Checked ;
		if (frm->cbtime->Enabled ) {
		 StoreSelect->Parameters->ParamByName("@time")->Value = frm->cbtime->ItemIndex  ;
		}
		if (ID == -1) {

			StoreSelect->Parameters->ParamByName("@mode")->Value = 1 ;  //ÐÂÌí¼Ó
			StoreSelect->ExecProc(); 
			ID = StoreSelect->Parameters->ParamByName("@RETURN_VALUE")->Value  ;
		
		}else
		{
			StoreSelect->Parameters->ParamByName("@mode")->Value = 0 ;
			StoreSelect->Parameters->ParamByName("@ID")->Value = ID;
		    StoreSelect->ExecProc();
		
		}

  }
  delete frm;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIntelligence::SpeedButton1Click(TObject *Sender)
{

	  // Tfrmselectorder * frma = new Tfrmselectorder(Application,fcon);
	  // frma->ShowModal();
	  // delete frma;

	  // return;
	  // Tfrmbidetail *frm =new Tfrmbidetail(Application,fcon);
	  // frm->ShowData();
	  // frm->ShowModal();
	  // delete frm;
}
//---------------------------------------------------------------------------

