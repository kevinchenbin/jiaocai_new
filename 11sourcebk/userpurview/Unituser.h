//---------------------------------------------------------------------------

#ifndef UnituserH
#define UnituserH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmuser : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnDelete;
	TPanel *Panel1;
	TRzDBGrid *RzDBGrid1;
	TADOQuery *aquery;
	TDataSource *ds;
	TRzToolButton *BtnChangeOptions;
	TADOConnection *cnn;
	TRzToolButton *BtnExit;
	TADOQuery *query;
	TRzToolButton *BtnAlignBottom;
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	String User,logmessage;
	int fstgid,userid;
public:		// User declarations
	__fastcall Tfrmuser(TComponent* Owner,TADOConnection *cn,String user,int stgid,int sid);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmuser *frmuser;
//---------------------------------------------------------------------------
#endif
