//---------------------------------------------------------------------------

#ifndef backdatabaseH
#define backdatabaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzShellDialogs.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class TBakDatabase : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *quBakDatabase;
	TSaveDialog *SavedlgBakPath;
	TPanel *Panel1;
	TLabel *Label1;
	TRzEdit *edBakPath;
	TButton *SelectPath;
	TImageList *ImageList1;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	void __fastcall SelectPathClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
private:	// User declarations
	AnsiString CheckPath;
public:		// User declarations
	__fastcall TBakDatabase(TComponent* Owner,TADOConnection *cn);
};
//---------------------------------------------------------------------------
extern PACKAGE TBakDatabase *BakDatabase;
//---------------------------------------------------------------------------
#endif
