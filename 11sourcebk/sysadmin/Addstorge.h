//---------------------------------------------------------------------------

#ifndef AddstorgeH
#define AddstorgeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmAddstorge : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TADOQuery *query;
	TADOQuery *querymod;
	TADOConnection *con;
	TPanel *Panel1;
	TRzGroupBox *RzGroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *edname;
	TEdit *edcontact;
	TEdit *edtel;
	TEdit *edaddress;
	TLabel *Label5;
	TEdit *edprinttitle;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ednameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtelKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edcontactKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:	// User declarations
	int Modle;
public:		// User declarations
	__fastcall TfrmAddstorge(TComponent* Owner,TADOQuery *aquery,int modle);
	int userid;
	int storageid;
	AnsiString logmessage;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAddstorge *frmAddstorge;
//---------------------------------------------------------------------------
#endif
