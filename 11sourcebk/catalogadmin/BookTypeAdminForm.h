//---------------------------------------------------------------------------

#ifndef BooKTypeAdminFormH
#define BooKTypeAdminFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzLstBox.hpp"
#include "RzTreeVw.hpp"
#include <ComCtrls.hpp>
#include "RzListVw.hpp"
#include "RzDBList.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "pdutil.h"
#include "MDIChild.h"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmBookTypeAdmin : public TForm//TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr2;
	TRzToolButton *btnExit1;
	TRzToolButton *btnExit2;
	TRzToolButton *btnExit3;
	TRzToolButton *RzToolButton1;
	TPanel *Panel2;
	TRzDBGrid *RzDBGrid1;
	TDataSource *dsource;
	TADODataSet *dsetBookType;
	TImageList *ImageList1;
	TTreeView *tvbookclass;
	TSplitter *Splitter1;
	TPanel *Panel3;
	TLabel *lbl2;
	TRzDBEdit *dbedtCode;
	TRzDBEdit *dbedtTypeName;
	TRzToolButton *rtbmodify;
	TLabel *Label1;
	TEdit *edtback;
	TRzToolButton *BtnSave;
	TADOQuery *aqbookclass;
	TEdit *edtname;
	TADOQuery *aquery;
	TADOStoredProc *dsp;
	TLabel *Label2;
	TEdit *ettypenum;
	TRzToolButton *BtnAlignBottom;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btn6Click(TObject *Sender);
	void __fastcall btnExit1Click(TObject *Sender);
	void __fastcall btnExit2Click(TObject *Sender);
	void __fastcall btnExit3Click(TObject *Sender);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall dbedtCodeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbedtTypeNameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall rtbmodifyClick(TObject *Sender);
	void __fastcall tvbookclassClick(TObject *Sender);
	void __fastcall edtnameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
void OnHotKeyPress(DWORD vkCode);
   int Modal;
   TStringList *ClassType;
public:		// User declarations
	__fastcall TfrmBookTypeAdmin(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);
	void Query(String condition);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBookTypeAdmin *frmBookTypeAdmin;
//---------------------------------------------------------------------------
#endif
