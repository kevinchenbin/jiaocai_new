//---------------------------------------------------------------------------

#ifndef MemberClassSetH
#define MemberClassSetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmmemclassmg : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TImageList *imagelistmemcardclass;
	TRzToolButton *BtnAdd;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnExit;
	TTreeView *tvMemberType;
	TSplitter *Splitter1;
	TPanel *Panel2;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edTypeName;
	TEdit *edTypeDiscount;
	TADOQuery *quMemberType;
	TRzToolButton *BtnChangeOptions;
	TRzToolButton *BtnSave;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *edMemberID;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnAddClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall tvMemberTypeClick(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall edTypeDiscountClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall Changesave();
	void __fastcall Addsave();
	void __fastcall edTypeNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edTypeDiscountKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:	// User declarations
	TTreeNode * Root;
	int savemodle;
public:		// User declarations
	__fastcall Tfrmmemclassmg(TComponent* Owner,TADOConnection *cnn);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmmemclassmg *frmmemclassmg;
//---------------------------------------------------------------------------
#endif
