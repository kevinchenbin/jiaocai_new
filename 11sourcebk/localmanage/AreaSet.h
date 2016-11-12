//---------------------------------------------------------------------------

#ifndef AreaSetH
#define AreaSetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TMemberAreaSet : public TForm
{
__published:	// IDE-managed Components
	TImageList *ilArea;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnChangeOptions;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TTreeView *tvArea;
	TLabel *Label1;
	TEdit *edName;
	TADOQuery *quArea;
	TLabel *Label2;
	TEdit *edAreaId;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnAlignBottom;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall tvAreaClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall Newsava();
	void __fastcall Changesava();
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	TTreeNode * Root;
	int savamodle;
public:		// User declarations
	__fastcall TMemberAreaSet(TComponent* Owner,TADOConnection *cnn);
};
//---------------------------------------------------------------------------
extern PACKAGE TMemberAreaSet *MemberAreaSet;
//---------------------------------------------------------------------------
#endif
