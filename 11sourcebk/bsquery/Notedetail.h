//---------------------------------------------------------------------------

#ifndef NotedetailH
#define NotedetailH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmNotedetail : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *aq;
	TADOConnection *cn;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	TADOQuery *aq1;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
private:	// User declarations
	int type;//1为入库，2为批销 ,3为盘点  ,7C网采购
public:		// User declarations
	__fastcall TfrmNotedetail(TComponent* Owner,String headercode,int Type,TADOConnection *con,int modle,int userid);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNotedetail *frmNotedetail;
//---------------------------------------------------------------------------
#endif
