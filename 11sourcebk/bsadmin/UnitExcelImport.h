//---------------------------------------------------------------------------

#ifndef UnitExcelImportH
#define UnitExcelImportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>

#include "StorageMngForm.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edtExcelPath;
	TSpeedButton *SpeedButton1;
	TOpenDialog *opndlgExcelPath;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExit;
	TADOConnection *con1;
	TADOQuery *qry1;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
private:	// User declarations
char GetPYIndexChar(char *str);
   TADOConnection *fcon;
   TStringList *press;
   int getpressid(AnsiString name);
	AnsiString GetSelf(AnsiString context);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner,TADOConnection *con);
	TfrmStorageMng *st;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
