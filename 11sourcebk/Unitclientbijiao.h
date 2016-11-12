//---------------------------------------------------------------------------

#ifndef UnitclientbijiaoH
#define UnitclientbijiaoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "DBChart.hpp"
#include "Series.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmbijiao : public TForm
{
__published:	// IDE-managed Components
	TDateTimePicker *DateTimePicker1;
	TDateTimePicker *DateTimePicker2;
	TLabel *lable;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TRzToolButton *Btn;
	TADOQuery *aq;
	TDataSource *ds;
	TChart *Chart1;
	TBarSeries *Series1;
	void __fastcall BtnClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    TADOConnection * fcn;
public:		// User declarations
	__fastcall Tfrmbijiao(TComponent* Owner);
	void init(TADOConnection *cn);
	int type ;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmbijiao *frmbijiao;
//---------------------------------------------------------------------------
#endif
