//---------------------------------------------------------------------------

#ifndef storagelocalH
#define storagelocalH
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
#include "pdtypes.h"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmstorelocal : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TTreeView *tvlocal;
	TPanel *Panel2;
	TImageList *ImageList1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TADOQuery *aquery;
	TADOQuery *aquerylocal;
	TLabel *Label1;
	TEdit *edtcode;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *edtname;
	TEdit *edtbk;
	TLabel *Label4;
	TRzToolButton *Btnmodify;
	TADOStoredProc *adosp;
	TRzToolButton *BtnAlignBottom;
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tvlocalClick(TObject *Sender);
	void __fastcall BtnmodifyClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	LandInfo  userInfo;
	int OperModal;
public:		// User declarations
	__fastcall Tfrmstorelocal(TComponent* Owner,TADOConnection* con,LandInfo* li);
};
typedef struct NodeData
{
   int SID;
   int LID;
   AnsiString LName,Lbk;
}LNodeData;

typedef struct TNodeData
{
   int SID;
   AnsiString SName;
}SNodeData;

//---------------------------------------------------------------------------
extern PACKAGE Tfrmstorelocal *frmstorelocal;
//---------------------------------------------------------------------------
#endif
