//---------------------------------------------------------------------------

#ifndef procuredetailH
#define procuredetailH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "DBCtrlsEh.hpp"
#include <Mask.hpp>
#include <Buttons.hpp>
#include "DBGridEh.hpp"
#include "MDIChild.h"
#include "GridsEh.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "ModalDialog.h"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class Tfrmprocuredetail : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDataSource *ds1;
	TDataSource *ds2;
	TADOQuery *aq1;
	TADOQuery *aq2;
	TADOQuery *aq;
	TPopupMenu *pqpm;
	TMenuItem *N1;
	TSpeedButton *SpeedButton3;
	TDBGrid *DBGrid1;
	TPopupMenu *pm;
	TMenuItem *N2;
	TDBGrid *DBGrid2;
	TDBGridEh *DBGridEh1;
	TDataSource *ds3;
	TADOQuery *aq3;
	TSpeedButton *SpeedButton1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall aq3AfterPost(TDataSet *DataSet);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmprocuredetail(TComponent* Owner);
	LandInfo linfo;
	void Init(LandInfo* li);
	int groupid;
	bool check;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmprocuredetail *frmprocuredetail;
//---------------------------------------------------------------------------
#endif
