//---------------------------------------------------------------------------

#ifndef UnitSelectsupplierH
#define UnitSelectsupplierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ImgList.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
struct Nodedata
{
  int ID;
  AnsiString Name;
};
class Tfrmselectsupplier : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TTreeView *tvclient;
	TADOQuery *ADOQuery1;
	TImageList *ImageList1;
	TLabel *Label1;
	TEdit *edsupplier;
	TSpeedButton *sbnewcustomer;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tvclientMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall tvclientDblClick(TObject *Sender);
	void __fastcall edsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sbnewcustomerClick(TObject *Sender);
private:	// User declarations
	TADOConnection *fcon;
	AnsiString SelectClientName;
	int SupplierID;
	TTreeNode *ClickNode; // 保存点中的节点;
public:		// User declarations
	__fastcall Tfrmselectsupplier(TComponent* Owner,TADOConnection *con,AnsiString sqlwhere);
	void ShowClient();
	AnsiString GetSelect();
	AnsiString where;
	int GetSelectID();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmselectsupplier *frmselectsupplier;
//---------------------------------------------------------------------------
#endif
