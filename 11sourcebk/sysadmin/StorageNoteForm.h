//---------------------------------------------------------------------------

#ifndef StorageNoteFormH
#define StorageNoteFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "RzDBList.hpp"
#include "RzLstBox.hpp"
#include "RzChkLst.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBChk.hpp"
#include "RzRadChk.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "MDIChild.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmStorageNote : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzGroupBox *RzGroupBox1;
	TADOQuery *qryStorageName;
	TDataSource *DataSource1;
	TADODataSet *dsetStorageNote;
	TDataSource *dsNotePrint;
	TListBox *ListBox1;
	TRzGroupBox *rzgrpbx1;
	TRzLabel *lbl1;
	TRzDBEdit *edtStorageNoteTitle;
	TRzDBCheckBox *RzDBCheckBox1;
	TRzDBCheckBox *CHKBarcode;
	TRzDBCheckBox *CHKPrice;
	TRzDBCheckBox *CHKBookName;
	TRzDBCheckBox *CHKISBN;
	TRzDBCheckBox *CHKCatalog;
	TRzDBCheckBox *CHKPress;
	TRzDBCheckBox *CHKFixedPrice;
	TRzDBCheckBox *CHKCategory;
	TRzDBCheckBox *CHKPublicDate;
	TRzDBCheckBox *CHKRevision;
	TRzDBCheckBox *CHKAuthor;
	TRzDBCheckBox *CHKDiscountedPrice;
	TButton *btn1;
	TRzButton *btn2;
	
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall dblbStorageNameClick(TObject *Sender);
	void __fastcall dblbStorageNameDblClick(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall ListBox1DblClick(TObject *Sender);
	void __fastcall ListBox1KeyPress(TObject *Sender, char &Key);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall btn2Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmStorageNote(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStorageNote *frmStorageNote;
//---------------------------------------------------------------------------
#endif
