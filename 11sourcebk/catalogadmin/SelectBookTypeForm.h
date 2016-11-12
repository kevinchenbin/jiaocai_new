//---------------------------------------------------------------------------

#ifndef SelectBookTypeFormH
#define SelectBookTypeFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "BookTypeAdminForm.h"
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
#include <ComCtrls.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmSelectBookType : public TfrmBookTypeAdmin
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	void __fastcall RzDBGrid1DblClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzDBGrid1CellClick(TColumn *Column);
	void __fastcall dsetBookTypeMoveComplete(TCustomADODataSet *DataSet, const TEventReason Reason,
          const Error *Error, TEventStatus &EventStatus);
	void __fastcall btnExit3Click(TObject *Sender);
private:	// User declarations
	int m_id;
public:		// User declarations
	int GetSelectID();
	__fastcall TfrmSelectBookType(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSelectBookType *frmSelectBookType;
//---------------------------------------------------------------------------
#endif
