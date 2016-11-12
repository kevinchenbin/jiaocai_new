//---------------------------------------------------------------------------

#ifndef MemberVoucherFormH
#define MemberVoucherFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzDBCmbo.hpp"
#include "MDIChild.h"
#include <DB.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmMemberVoucher : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzGroupBox *会员充值记录查询;
	TRzLabel *lblInfor;
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton1;
	TRzToolButton *RzToolButton5;
	TADODataSet *dsetMemberVoucher;
	TDataSource *ds1;
	TComboBox *cbbType;
	TRzDBGrid *rzdbgrd1;
	TRzEdit *RzEditInfor;
	TDateTimePicker *dtp1;
	TDateTimePicker *dtp2;
	TLabel *lbl1;
	TLabel *lbl2;

	void __fastcall btnTopClick(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall RzEditInforKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall cbbTypeSelect(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	TApplication* m_app;
	TADOConnection* m_con;
		void Query();
public:		// User declarations
	__fastcall TfrmMemberVoucher(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMemberVoucher *frmMemberVoucher;
//---------------------------------------------------------------------------
#endif
