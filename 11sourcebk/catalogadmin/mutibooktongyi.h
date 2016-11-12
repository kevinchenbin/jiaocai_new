//---------------------------------------------------------------------------

#ifndef mutibooktongyiH
#define mutibooktongyiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>

#include "RzBtnEdt.hpp"
#include "RzEdit.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include <Mask.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
#include <Grids.hpp>

//---------------------------------------------------------------------------
class Tfrmmutibook : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TGroupBox *gb;
	TCheckBox *chautoname;
	TGroupBox *GroupBox1;
	TCheckBox *chname;
	TCheckBox *chautoisbn;
	TCheckBox *chautoprice;
	TCheckBox *chautoauthor;
	TCheckBox *chautousercode;
	TCheckBox *chautopress;
	TEdit *edname;
	TCheckBox *chisbn;
	TEdit *edisbn;
	TCheckBox *chauthor;
	TEdit *edauthor;
	TCheckBox *chprice;
	TEdit *edprice;
	TCheckBox *chuserdef;
	TEdit *eduserdef;
	TCheckBox *chpress;
	TEdit *edpress;
	TComboBox *cbpress;
	TRzButtonEdit *RzButtonEdit1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnSelectAll;
	TRzToolButton *BtnMove;
	TRzToolButton *BtnCopyAll;
	TADOQuery *query;
	TDataSource *ds;
	TADOConnection *fcon;
	TCheckBox *chautopresscount;
	TADOCommand *comHebingshumu;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	void __fastcall edpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnSelectAllClick(TObject *Sender);
	void __fastcall BtnCopyAllClick(TObject *Sender);
	void __fastcall BtnMoveClick(TObject *Sender);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall edisbnChange(TObject *Sender);
	void __fastcall edauthorChange(TObject *Sender);
	void __fastcall edpriceChange(TObject *Sender);
	void __fastcall eduserdefChange(TObject *Sender);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);

	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall Tfrmmutibook(TComponent* Owner,TADOConnection *con);
	int ybookid,mbookid,userid,stgid,mxuhao;
	AnsiString logmessage,ybookname,mbookname;
	float yprice,mprice;
   	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmmutibook *frmmutibook;
//---------------------------------------------------------------------------
#endif
