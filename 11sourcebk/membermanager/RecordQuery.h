//---------------------------------------------------------------------------

#ifndef RecordQueryH
#define RecordQueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IWImageList.hpp"
#include "RzDBGrid.hpp"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include "RzCmboBx.hpp"
#include "RzRadChk.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormRecordQuery : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TGroupBox *GroupBox1;
	TEdit *edname;
	TDateTimePicker *dtStartData;
	TDateTimePicker *dtEndData;
	TDBGrid *dgRecord;
	TDataSource *DataSource1;
	TADOQuery *quRecordMessage;
	TRzToolButton *BtnFind;
	TRzToolButton *BtnExit;
	TImageList *ImageList1;
	TRzCheckBox *cbstarttime;
	TRzCheckBox *cbendtime;
	TRzToolButton *BtnExport;
	TRzLabel *RzLabel1;
	TRzEdit *edtotalblance;
	TRzLabel *RzLabel2;
	TRzEdit *edtotalcons;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnRefresh;
	TADOConnection *fcon;
	TCheckBox *chname;
	TEdit *edcard;
	TCheckBox *chcard;
	TCheckBox *chtype;
	TComboBox *cbtype;
	TSaveDialog *savedlg;
	TRzEdit *edtotalvalue;
	TRzLabel *l1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnFindClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall ednameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dgRecordTitleClick(TColumn *Column);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnRefreshClick(TObject *Sender);
	void __fastcall dtStartDataChange(TObject *Sender);
	void __fastcall dtEndDataChange(TObject *Sender);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall edcardChange(TObject *Sender);
	void __fastcall cbtypeChange(TObject *Sender);
	void __fastcall edcardKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dtStartDataKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dtEndDataKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:	// User declarations
public:		// User declarations
	__fastcall TFormRecordQuery(TComponent* Owner,TADOConnection *cn,int userid,int stgid);
	int fuserid,fstgid;
	bool __fastcall DbgridToExcel(TDBGrid* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormRecordQuery *FormRecordQuery;
//---------------------------------------------------------------------------
#endif
