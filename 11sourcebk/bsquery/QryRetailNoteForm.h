//---------------------------------------------------------------------------

#ifndef QryRetailNoteFormH
#define QryRetailNoteFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "QryStorageNoteForm.h"
#include "RzButton.hpp"
#include "RzDBCmbo.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLine.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include "RzTabs.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <ImgList.hpp>
#include <Dialogs.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <Menus.hpp>
#include "DBGridEhImpExp.hpp"
//---------------------------------------------------------------------------
class TfrmQryRetailNote : public TfrmQryStorageNote
{
__published:	// IDE-managed Components
	TRzCheckBox *chckbx1;
	TRzDBLookupComboBox *dblkpcbbSupplierID;
	TEdit *edsuplier;
	void __fastcall tlbtnQryClick(TObject *Sender);
	void __fastcall edtPressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall tlbtnExportClick(TObject *Sender);
	void __fastcall edsuplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtCustomerKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbgrdByNtHeaderTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByNoteTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByCustomerTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByBktypeTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByPressTitleClick(TColumnEh *Column);
	void __fastcall N1Click(TObject *Sender);

private:	// User declarations
	void Query();
	String QueryDesic();
	String Desic,Desic1;
public:		// User declarations
	__fastcall TfrmQryRetailNote(TComponent* Owner);
	bool __fastcall DbgridToExcel(TDBGridEh* dbg);
	void Init(LandInfo* li);
	void View();
	bool cbpr,prf;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmQryRetailNote *frmQryRetailNote;
//---------------------------------------------------------------------------
#endif