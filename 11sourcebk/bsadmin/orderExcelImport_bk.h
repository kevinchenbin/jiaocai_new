//---------------------------------------------------------------------------

#ifndef orderExcelImportH
#define orderExcelImportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include "RzRadChk.hpp"
#include "RzRadGrp.hpp"
#include "RzShellDialogs.hpp"
#include "RzPrgres.hpp"
//#include "SelectBookTypeForm.h"
#include <Buttons.hpp>
#include <ImgList.hpp>
#include "RzCmboBx.hpp"
#include "ModalDialog.h"
//---------------------------------------------------------------------------
class TfrmExcelImport : public TForm
{
__published:	// IDE-managed Components
	TRzOpenDialog *opndlgExcelPath;
	TADODataSet *dset;
	TADOConnection *con1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExit;
	TADOQuery *aq;
	TADOQuery *qry;
	TDataSource *ds;
	TADOQuery *query;
	TRzEdit *edtExcelPath;
	TLabel *lbl3;
	TCheckBox *chisbn;
	TSpeedButton *spselectpath;
	TCheckBox *chname;
	TCheckBox *chprice;
	TCheckBox *chpress;
	TCheckBox *chpresscount;
	TCheckBox *chamount;
	TCheckBox *chauthor;
	TCheckBox *chbk;
	TCheckBox *chdiscount;
	TADOCommand *comAddcatalog;
	TPanel *Panel1;
	TCheckBox *chclass;
	TCheckBox *chxuexuao;
	TCheckBox *chxiaoqu;
	TCheckBox *chxueyuan;
	TCheckBox *chcourse;
	TCheckBox *chteacher;
	TCheckBox *chincode;
	TCheckBox *chtelphone;
	TCheckBox *chtishi;
	TLabel *Label1;
	TLabel *Label2;
	void __fastcall spselectpathClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
private:	// User declarations
	bool Import;
	TADOQuery * dsdg;             //
public:		// User declarations
	__fastcall TfrmExcelImport(TComponent* Owner,TADOConnection *con,int headid);
	int headerid;
	int fuserid,fstgid;
	AnsiString GetNum(AnsiString Anstr);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmExcelImport *frmExcelImport;
//---------------------------------------------------------------------------
#endif
