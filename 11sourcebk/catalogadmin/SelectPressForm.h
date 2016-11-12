//---------------------------------------------------------------------------

#ifndef SelectPressFormH
#define SelectPressFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "PressAdminForm.h"
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include "RzShellDialogs.hpp"
#include "RzLine.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmSelectPress : public TfrmPressAdmin
{
__published:	// IDE-managed Components
	void __fastcall rzdbgrdPressDblClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall rzdbgrdPressCellClick(TColumn *Column);
	void __fastcall dsetPressMoveComplete(TCustomADODataSet *DataSet, const TEventReason Reason,
		  const Error *Error, TEventStatus &EventStatus);
	void __fastcall btnExit4Click(TObject *Sender);
   //	void __fastcall btn1Click(TObject *Sender);

private:	// User declarations
	int m_id;
	AnsiString m_name;
public:		// User declarations
	int GetSelectID();
	String GetSelectName();
	__fastcall TfrmSelectPress(TComponent* Owner);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSelectPress *frmSelectPress;
//---------------------------------------------------------------------------
#endif
