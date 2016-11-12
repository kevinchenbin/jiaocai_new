//---------------------------------------------------------------------------

#ifndef CoustomerImportH
#define CoustomerImportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzRadChk.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzPrgres.hpp"
#include "RzShellDialogs.hpp"
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TFormCousImport : public TForm
{
__published:	// IDE-managed Components
	TLabel *lblExcel;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *lbnow;
	TLabel *lbsum;
	TRzProgressBar *prgrsbrExcelImport;
	TRzGroupBox *RzGroupBox1;
	TRzCheckBox *cbtype;
	TRzCheckBox *cbname;
	TRzCheckBox *cbaddress;
	TRzCheckBox *cbcode;
	TRzCheckBox *cbtelphone;
	TRzCheckBox *cbfax;
	TRzCheckBox *cbcontex;
	TRzCheckBox *cbdate;
	TRzCheckBox *chsaleman;
	TRzCheckBox *cbbalance;
	TRzCheckBox *cbarea;
	TRzCheckBox *cbBsLessBus;
	TRzCheckBox *cbBusLessBs;
	TRzCheckBox *cballcheck;
	TEdit *edtExcelPath;
	TRzButton *btselectpath;
	TRzOpenDialog *opndlgExcelPath;
	TImageList *ImageList1;
	TADOConnection *con1;
	TADOQuery *qry1;
	TDataSource *ds1;
	TADOQuery *aqdetail;
	TPanel *Panel2;
	TRzToolButton *BtnAlignBottom;
	void __fastcall btselectpathClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall cballcheckClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	bool Import;
	int Type;
	TADOQuery * dsdg;
public:		// User declarations
	__fastcall TFormCousImport(TComponent* Owner,TADOQuery * query,int type);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCousImport *FormCousImport;
//---------------------------------------------------------------------------
#endif
