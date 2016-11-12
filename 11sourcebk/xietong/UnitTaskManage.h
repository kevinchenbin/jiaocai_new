//---------------------------------------------------------------------------

#ifndef UnitTaskManageH
#define UnitTaskManageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmtaskmanagea : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TPanel *Panel1;
	TRzToolButton *RzToolButton1;
	TImageList *ImageList1;
	TRzToolButton *Btn;
	TRzToolButton *Btn1;
	TRzDBGrid *rzdb;
	TRzToolButton *Btn2;
	TADOQuery *aq;
	TDataSource *ds;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnAlignBottom;
	void __fastcall BtnClick(TObject *Sender);
	void __fastcall Btn1Click(TObject *Sender);
	void __fastcall Btn2Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall rzdbDblClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
   TADOConnection *fcon;
   int fuserid;
   int fstgid;
public:		// User declarations
	__fastcall Tfrmtaskmanagea(TComponent* Owner);
	void init(TADOConnection *con,int userid,int stgid);
	void readdata(int type);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmtaskmanagea *frmtaskmanagea;
//---------------------------------------------------------------------------
#endif
