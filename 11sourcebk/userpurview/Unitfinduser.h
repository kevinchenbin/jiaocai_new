//---------------------------------------------------------------------------

#ifndef UnitfinduserH
#define UnitfinduserH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ImgList.hpp>
#include "RzPanel.hpp"
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class Tfrmfinduser : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TListView *lvuserlist;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *editname;
	TEdit *editdescrip;
	TSpeedButton *sbfinduser;
	TADOQuery *aq;
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	void __fastcall sbfinduserClick(TObject *Sender);
	void __fastcall editnameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall lvuserlistDblClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
   TADOConnection *fcon;
   int fstgid;
public:		// User declarations
	__fastcall Tfrmfinduser(TComponent* Owner,TADOConnection *cn,int stgid);
	void finduser(AnsiString descript,AnsiString Username);
	AnsiString SelectUser;
	AnsiString UserDescript;
	int userid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmfinduser *frmfinduser;
//---------------------------------------------------------------------------
#endif
