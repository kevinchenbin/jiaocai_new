//---------------------------------------------------------------------------

#ifndef UnitweishenheH
#define UnitweishenheH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmweishenhe : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TRzDBGrid *dg;
	TDataSource *ds;
	TADOQuery *aqdg;
	TRzToolButton *BtnAlignBottom;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall dgDblClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	bool ChangeDisplay;
public:		// User declarations
    int Type;
	__fastcall Tfrmweishenhe(TComponent* Owner,TADOConnection *cn,int type);
	void Createdg(TADOQuery *aq,TRzDBGrid *dg);
	String Danhao;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmweishenhe *frmweishenhe;
//---------------------------------------------------------------------------
#endif
