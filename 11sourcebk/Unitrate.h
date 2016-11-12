//---------------------------------------------------------------------------

#ifndef UnitrateH
#define UnitrateH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class Tfrmrate : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDateTimePicker *dtpstart;
	TCheckBox *chstart;
	TDateTimePicker *dtpend;
	TCheckBox *chend;
	TCheckBox *chisbn;
	TEdit *edisbn;
	TCheckBox *chname;
	TEdit *edname;
	TCheckBox *chpress;
	TEdit *edpress;
	TComboBox *cbpress;
	TCheckBox *chclient;
	TEdit *edtclient;
	TEdit *edclient;
	TSpeedButton *spselectClient;
	TDBGrid *dbg1;
	TADOConnection *con;
	TADOQuery *aq1;
	TADOQuery *aq2;
	TADOQuery *aq3;
	TDataSource *ds1;
	TDataSource *ds2;
	TDataSource *ds3;
	TDBGrid *dbg2;
	TDBGrid *dbg3;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnView;
	TRzToolButton *BtnView1;
	TRzToolButton *BtnView2;
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbg3TitleClick(TColumn *Column);
	void __fastcall dbg2TitleClick(TColumn *Column);
	void __fastcall dbg1TitleClick(TColumn *Column);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnView1Click(TObject *Sender);
	void __fastcall BtnView2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmrate(TComponent* Owner,TADOConnection *cn,int stgid);
	int fstgid,Clientid;
	void ClientView();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmrate *frmrate;
//---------------------------------------------------------------------------
#endif
