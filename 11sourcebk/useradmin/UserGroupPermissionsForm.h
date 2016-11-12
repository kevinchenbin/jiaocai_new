//---------------------------------------------------------------------------

#ifndef UserGroupPermissionsFormH
#define UserGroupPermissionsFormH
#include "addForm.h"
#include "adduserForm.h"
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include "RzTreeVw.hpp"
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include "RzDBChk.hpp"
#include "RzRadChk.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmUserGroupPermissions : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzGroupBox *rzgrpbx1;
	TRzTreeView *tvUserGroup;
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton5;
	TRzToolButton *RzToolButton1;
	TRzToolButton *RzToolButton3;
	TADODataSet *dsUserGroup;
	TDataSource *ds1;
	TRzGroupBox *rzgrpbx2;
	TRzDBCheckBox *rzdb1;
	TRzDBCheckBox *rzdb2;
	TRzDBCheckBox *rzdb3;
	TRzDBCheckBox *rzdb4;
	TRzDBCheckBox *rzdb5;
	TRzDBCheckBox *rzdb6;
	TRzDBCheckBox *rzdb7;
	TRzDBCheckBox *rzdb8;
	TRzDBCheckBox *rzdb9;
	TRzDBCheckBox *rzdb10;
	TDataSource *ds2;
	TADODataSet *dsuser;
	TRzToolButton *RzToolButton2;
	TRzToolButton *RzToolButton4;
	TRzToolButton *RzToolButton6;
	TADOCommand *cmd;
	TRzDBCheckBox *rzdbBusinessManage;
	TRzDBCheckBox *rzdbBusinessManage1;
	TRzDBCheckBox *rzdbBusinessManage2;
	TRzDBCheckBox *rzdbBusinessManage3;
	TImageList *ImageList1;
	TRzButton *btn1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall tvUserGroupClick(TObject *Sender);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall RzToolButton4Click(TObject *Sender);
	void __fastcall RzToolButton2Click(TObject *Sender);
	void __fastcall RzToolButton6Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


public:		// User declarations
	__fastcall TfrmUserGroupPermissions(TComponent* Owner);
	void Init(LandInfo* li);
	void deal();
	 TTreeNode	*Node1;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmUserGroupPermissions *frmUserGroupPermissions;
//---------------------------------------------------------------------------
#endif
