//---------------------------------------------------------------------------

#ifndef UnitSelectClientH
#define UnitSelectClientH
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
//---------------------------------------------------------------------------
struct Nodedata
{
  int ID;
  int PrentID;
  AnsiString Name;
};
class TfrmselectClient : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TTreeView *tvclient;
	TADOQuery *ADOQuery1;
	TImageList *ImageList1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tvclientMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall tvclientDblClick(TObject *Sender);
	void __fastcall tvclientKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
	TADOConnection *fcon;
	AnsiString SelectClientName;
	int ClientID;
	TTreeNode *ClickNode; // ������еĽڵ�;
public:		// User declarations
	__fastcall TfrmselectClient(TComponent* Owner,TADOConnection *con,AnsiString sqlwhere,int stgid);
	void ShowClient();
	AnsiString GetSelect();
	AnsiString where;
	int GetSelectID();
	int fstgid;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmselectClient *frmselectClient;
//---------------------------------------------------------------------------
#endif