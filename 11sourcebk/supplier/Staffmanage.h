//---------------------------------------------------------------------------

#ifndef StaffmanageH
#define StaffmanageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include "RzCmboBx.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmStaff : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnFinish;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnView;
	TADOQuery *aqinit;
	TADOQuery *aqrecord;
	TDataSource *ds;
	TRzToolButton *BtnExport;
	TADOQuery *query;
	TRzToolButton *BtnAlignBottom;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TRzLabel *RzLabel1;
	TEdit *etname;
	TRzDBGrid *DBGridrecord;
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnFinishClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall etnameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
	TADOConnection *cn;
	int fstgid;
public:		// User declarations
	__fastcall TfrmStaff(TComponent* Owner,TADOConnection *cnn,int stgid);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	void Initsalesman();
	void InitLocalinfo();
	void Initname();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStaff *frmStaff;
//---------------------------------------------------------------------------
#endif
