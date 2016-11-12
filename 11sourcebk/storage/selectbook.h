//---------------------------------------------------------------------------

#ifndef selectbookH
#define selectbookH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ModalDialog.h"
#include "RzButton.hpp"
#include "RzLabel.hpp"
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzEdit.hpp"
#include <Mask.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "UnitDiaobo.h"


//---------------------------------------------------------------------------
class Tfrmfindbook : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TRzDBGrid *dbgrdQry;
	TDataSource *dsrcQry;
	TADOQuery *aquery;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnProperties;
	TRzToolButton *Btnselectall;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnWeekView;
	void __fastcall dbgrdQryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnselectallClick(TObject *Sender);
	void __fastcall BtnPropertiesClick(TObject *Sender);
	void __fastcall dbgrdQryDblClick(TObject *Sender);
	void __fastcall BtnWeekViewClick(TObject *Sender);
	void __fastcall dbgrdQryCellClick(TColumn *Column);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations

	AnsiString SearchCont;


	BOOL MutilSelectModal;//是否为多选模式
public:		// User declarations
	__fastcall Tfrmfindbook(TComponent* Owner,TADOQuery *aq);
	bool SelectAll;
	AnsiString Supplier;
	int DoModalType;//1为调拨
	Tfrmdiaobo *frmdiaobo;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmfindbook *frmfindbook;
//---------------------------------------------------------------------------
#endif
