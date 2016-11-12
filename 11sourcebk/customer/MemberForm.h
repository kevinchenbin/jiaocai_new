//---------------------------------------------------------------------------

#ifndef MemberFormH
#define MemberFormH
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzLine.hpp"
#include "RzPanel.hpp"
#include <Classes.hpp>
#include <Controls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <StdCtrls.hpp>
#include "RzCmboBx.hpp"
#include "RzDBCmbo.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <FMTBcd.hpp>
#include <SqlExpr.hpp>
#include   <stdlib.h>
#include <ComCtrls.hpp>
#include "RzDBDTP.hpp"
#include "RzDTP.hpp"
#include <Menus.hpp>
#include <MDIChild.h>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TfrmMember : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzGroupBox *RzGroupBox1;
	TRzLabel *RzLabel2;
	TRzDBEdit *dbedtName;
	TRzLabel *RzLabel1;
	TRzDBEdit *dbedtName1;
	TRzDBGrid *RzDBGrid1;
	TRzGroupBox *RzGroupBox2;
	TRzSpacer *RzSpacer1;
	TRzToolButton *RzToolButton3;
	TRzEdit *RzEditInfor;
	TRzLabel *RzLabel4;
	TRzLabel *RzLabel3;
	TRzToolButton *RzToolButton4;
	TRzToolButton *RzToolButton5;
	TRzLabel *RzLabel6;
	TRzLabel *RzLabel7;
	TRzLabel *RzLabel8;
	TRzLabel *RzLabel9;
	TRzLabel *RzLabel10;
	TRzLabel *RzLabel11;
	TRzLabel *RzLabel12;
	TRzLabel *RzLabel13;
	TRzDBGrid *RzDBGrid;
	TRzLabel *RzLabel5;
	TRzLabel *RzLabel14;
	TRzLabel *RzLabel15;
	TRzDBComboBox *MemberType;
	TDataSource *ds1;
	TRzDBEdit *edtName;
	TRzDBEdit *edtName1;
	TRzDBComboBox *Sex;
	TRzDBEdit *edtName2;
	TRzDBEdit *RzDBEdit3;
	TRzDBEdit *RzDBEdit4;
	TRzDBEdit *RzDBEdit5;
	TRzDBEdit *RzDBEdit8;
	TRzDBEdit *RzDBEdit9;
	TRzDBEdit *RzDBEdit12;
	TADODataSet *dsetMemberLevel;
	TDataSource *ds2;
	TADOQuery *qryMemberSettings;
	TDataSource *ds3;
	TRzToolButton *RzToolButton1;
	TRzToolButton *RzToolButton2;
	TRzToolButton *RzToolButton7;
	TADODataSet *dsetMemberSettings;
	TComboBox *cbbType;
	TRzToolButton *RzToolButton6;
	TRzLabel *lblTop;
	TRzLabel *lbl1;
	TRzLabel *lblcancel;
	TRzNumericEdit *edtTop;
	TADOCommand *cmdDelMember;
	TADOCommand *cmdTop;
	TADOCommand *cmdTopRecord;
	TRzToolButton *RzToolButton8;
	TRzToolButton *RzToolButton9;
	TRzDBDateTimePicker *edtName3;
	TRzToolButton *RzToolButton10;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall RzToolButton2Click(TObject *Sender);
	void __fastcall RzToolButton4Click(TObject *Sender);
	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall dsetMemberSettingsMoveComplete(TCustomADODataSet *DataSet, const TEventReason Reason,
          const Error *Error, TEventStatus &EventStatus);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall RzToolButton7Click(TObject *Sender);
	void __fastcall lblcancelClick(TObject *Sender);
	void __fastcall RzToolButton6Click(TObject *Sender);
	void __fastcall RzEditInforKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtTopKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtNameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit4KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SexKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtName2KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit3KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtName1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtName3KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall MemberTypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit8KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbedtNameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbbTypeSelect(TObject *Sender);
	void __fastcall RzToolButton9Click(TObject *Sender);
	void __fastcall RzToolButton8Click(TObject *Sender);
	void __fastcall dbedtName1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBEdit5KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtName3Change(TObject *Sender);


private:	// User declarations
	void Query();
	void AddTop();
	TObject *Sender1;
	String Type;
	int Type1;

public:		// User declarations
	__fastcall TfrmMember(TComponent* Owner);
	virtual void Init(TApplication* app, TADOConnection* con);
		//void Query(String condition, CustomerType type);
		TApplication* app1;
		TADOConnection* con1;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMember *frmMember;
//---------------------------------------------------------------------------
#endif
