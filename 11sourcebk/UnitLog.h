//---------------------------------------------------------------------------

#ifndef UnitLogH
#define UnitLogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzListVw.hpp"
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzCmboBx.hpp"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmLog : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TADOQuery *aq;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TDateTimePicker *dtpstart;
	TComboBox *cbuser;
	TComboBox *cbstorage;
	TCheckBox *chstarttime;
	TCheckBox *chuser;
	TCheckBox *chstorage;
	TDateTimePicker *dtpend;
	TCheckBox *chendtime;
	TCheckBox *chsourcefrom;
	TRzComboBox *cbsuorefrom;
	TCheckBox *chtype;
	TRzComboBox *cbtype;
	TCheckBox *chneirong;
	TEdit *edneirong;
	TADOConnection *con;
	TDataSource *ds;
	TADOQuery *query;
	TEdit *edquery;
	TListView *lv;
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall lvData(TObject *Sender, TListItem *Item);
	void __fastcall ListView1Data(TObject *Sender, TListItem *Item);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmLog(TComponent* Owner,TADOConnection *cn,int userid,int stgid);
	void ReadData();
	int fuserid,fstgid;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmLog *frmLog;
//---------------------------------------------------------------------------
#endif
