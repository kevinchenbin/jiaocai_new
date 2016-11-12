//---------------------------------------------------------------------------

#ifndef AddUserH
#define AddUserH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
//---------------------------------------------------------------------------
class TfrmAddUser : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *query;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TADOQuery *querygroup;
	TADOQuery *aq;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *edaddress;
	TEdit *edbk;
	TEdit *edjob;
	TEdit *edmob;
	TEdit *edname;
	TEdit *edtel;
	TRzComboBox *cbstorge;
	TADOConnection *con;
	TRzToolButton *BtnAlignBottom;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ednameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edjobKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtelKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edmobKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edbkKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);



private:	// User declarations
	int Modle;
	String User,logmessage;
	int fstgid;
public:		// User declarations
	__fastcall TfrmAddUser(TComponent* Owner,TADOConnection *cn,int modle,TADOQuery *aquery,String user,int stgid);
	int userid;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAddUser *frmAddUser;
//---------------------------------------------------------------------------
#endif
