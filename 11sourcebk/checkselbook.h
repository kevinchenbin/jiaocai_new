//---------------------------------------------------------------------------

#ifndef checkselbookH
#define checkselbookH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include "PublicClass.h"
//---------------------------------------------------------------------------
class Tfrmcatalogselect : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnProperties;
	TRzToolButton *BtnChangeOptions;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnWeekView;
	TRzDBGrid *dgcatalogselect;
	TADOQuery *aquery;
	TDataSource *dsselect;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnPropertiesClick(TObject *Sender);
	void __fastcall dgcatalogselectKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgcatalogselectDblClick(TObject *Sender);
private:	// User declarations
   bool zerodisplay;
public:		// User declarations
	 LandInfo* sli;
	__fastcall Tfrmcatalogselect(TComponent* Owner,TADOConnection* con,TADOQuery * aquery);
   //	void QueryBook(int m_storageID, int m_local,AnsiString value);
	int m_searchMode;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmcatalogselect *frmcatalogselect;
//---------------------------------------------------------------------------
#endif
