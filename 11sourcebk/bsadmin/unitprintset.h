//---------------------------------------------------------------------------

#ifndef unitprintsetH
#define unitprintsetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <ComCtrls.hpp>
#include "frxClass.hpp"
#include "frxCross.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------
struct PrintControl1
{
   AnsiString name;
   float width;
};
class Tfrmprintset : public TForm
{
__published:	// IDE-managed Components
	TDataSource *ds;
	TADOQuery *query;
	TADOConnection *fcon;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnSave;
	TPanel *Panel1;
	TLabel *Label1;
	TDBGridEh *DBGridEh1;
	TEdit *edname;
	TLabel *labl2;
	TRzToolButton *BtnSelectAll;
	TTreeView *tvfangan;
	TRzToolButton *BtnClear;
	TRzToolButton *BtnExit;
	TEdit *eddefault;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnPrintPreview;
	TfrxReport *frxWsale;
	TADOQuery *aqdetail;
	TfrxCrossObject *frxCrossObject1;
	TADOQuery *aqHeader;
	TfrxDBDataset *frxDBwsalehead;
	TLabel *Label2;
	TComboBox *cbreport;
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnSelectAllClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall tvfanganClick(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnPrintPreviewClick(TObject *Sender);
	void __fastcall frxWsaleBeforePrint(TfrxReportComponent *Sender);
	void __fastcall frxWsaleGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmprintset(TComponent* Owner,TADOConnection *con,int modle,int stgid);
	int fmodle,fstgid,modle; //1添加 2修改 0无任何操作
	TTreeNode * Root;
	AnsiString ps;
	TStringList * PrintTile;
	AnsiString pxbk,printtitle,contact,tel,address;
	AnsiString FindTitleName(AnsiString ColumnName);
	float FindTitlewith(AnsiString ColumnName);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmprintset *frmprintset;
//---------------------------------------------------------------------------
#endif
