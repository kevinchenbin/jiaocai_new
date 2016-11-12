//---------------------------------------------------------------------------

#ifndef sendbookselectH
#define sendbookselectH
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
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <DB.hpp>
#include <ADODB.hpp>
//---------------------------------------------------------------------------
class Tfrmsendbookselect : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TPanel *Panel1;
	TRzToolButton *BtnAlignNone;
	TRzToolButton *BtnExit;
	TRzLabel *lblCatalog;
	TRzEdit *edtCatalog;
	TRzDBGrid *dgcatalogselect;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N3;
	TMenuItem *N2;
	TMenuItem *N4;
	TDataSource *ds;
	TADOQuery *aq;
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignNoneClick(TObject *Sender);
	void __fastcall dgcatalogselectDblClick(TObject *Sender);
	void __fastcall dgcatalogselectKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
	int m_catalogSearchMode,m_storageID;
public:		// User declarations
	__fastcall Tfrmsendbookselect(TComponent* Owner,TADOConnection* con,int stgid);
	void ChangeCatalogSearchMode();
	void Query(AnsiString strwhere);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsendbookselect *frmsendbookselect;
//---------------------------------------------------------------------------
#endif
