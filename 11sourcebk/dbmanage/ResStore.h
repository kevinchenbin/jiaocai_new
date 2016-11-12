//---------------------------------------------------------------------------

#ifndef ResStoreH
#define ResStoreH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class TResDatabase : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edResPath;
	TButton *Button1;
	TOpenDialog *OpendlgResPath;
	TADOQuery *quResDatabase;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TResDatabase(TComponent* Owner,TADOConnection *cn);
};
//---------------------------------------------------------------------------
extern PACKAGE TResDatabase *ResDatabase;
//---------------------------------------------------------------------------
#endif
