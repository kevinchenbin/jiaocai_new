//---------------------------------------------------------------------------

#ifndef SpecialPasswordFormH
#define SpecialPasswordFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmSpecialPassword : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TLabel *lbl8;
	TADOCommand *cmd;
	TRzButton *btn2;
	TRzButton *btn1;
	TEdit *edt7;
	TEdit *edt6;
	TEdit *edt5;
	TEdit *edt4;
	TEdit *edt3;
	TEdit *edt2;
	TEdit *edt1;
	TLabel *lbl7;
	TLabel *lbl6;
	TLabel *lbl5;
	TLabel *lbl4;
	TLabel *lbl3;
	TLabel *lbl2;
	TLabel *lbl1;
	TPanel *panel;
	TLabel *Label1;
	TEdit *edmember;
	TADOConnection *con;
	TImageList *ImageList1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *edclishenpwd;
	TEdit *edsupfanshenpwd;
	TEdit *edsupshenpwd;
	TEdit *edclifanshenpwd;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btn2Click(TObject *Sender);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
private:	// User declarations
	int stgid,userid;
public:		// User declarations
	__fastcall TfrmSpecialPassword(TComponent* Owner);
		void Init(LandInfo* li);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSpecialPassword *frmSpecialPassword;
//---------------------------------------------------------------------------
#endif
