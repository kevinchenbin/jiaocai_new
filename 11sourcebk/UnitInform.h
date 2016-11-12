//---------------------------------------------------------------------------

#ifndef UnitInformH
#define UnitInformH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "RzBHints.hpp"
#include "RzListVw.hpp"
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmInform : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TTimer *Timer2;
	TRzBalloonHints *RzBalloonHints1;
	TRzDBGrid *dg;
	TADOQuery *aq;
	TDataSource *ds;
	TImageList *ImageList1;
	TTimer *Timer3;
	TADOStoredProc *adosp;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight, bool &Resize);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall dgDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall dgCellClick(TColumn *Column);

private:	// User declarations
	TADOConnection *fcn;
public:		// User declarations
	__fastcall TfrmInform(TComponent* Owner,TADOConnection *cn);
	String GetFormNameAt(TPoint Pos);
	int UserID,StgID;
	void Refresh();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmInform *frmInform;
//---------------------------------------------------------------------------
#endif
