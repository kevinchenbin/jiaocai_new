//---------------------------------------------------------------------------

#ifndef MemberImportH
#define MemberImportH
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
class TFormMemImport : public TForm
{
__published:	// IDE-managed Components
	TLabel *lblExcel;
	TRzOpenDialog *opndlgExcelPath;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExit;
	TADOConnection *con1;
	TADOQuery *qry1;
	TDataSource *ds1;
	TADOQuery *aqdetail;
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
	TRzCheckBox *cbmobile;
	TRzCheckBox *cbtelphone;
	TRzCheckBox *cbsex;
	TRzCheckBox *cbcardid;
	TRzCheckBox *chtotalcons;
	TRzCheckBox *cbbalance;
	TRzCheckBox *cbbirthday;
	TRzCheckBox *cballcheck;
	TEdit *edtExcelPath;
	TRzButton *btselectpath;
	void __fastcall btselectpathClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall cballcheckClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	bool Import;
	TADOQuery * dsdg;
public:		// User declarations
	__fastcall TFormMemImport(TComponent* Owner,TADOQuery * query);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMemImport *FormMemImport;
//---------------------------------------------------------------------------
#endif
