//---------------------------------------------------------------------------

#ifndef UnitprintbagH
#define UnitprintbagH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <Buttons.hpp>
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpBase.hpp"
#include "RpSystem.hpp"
#include "frxClass.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------
class Tfrmprintbag : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TADOConnection *fcon;
	TDBGrid *DBGrid1;
	TImageList *ImageList1;
	TADOQuery *query;
	TDataSource *ds;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TRzButton *RzButton3;
	TRzButton *RzButton4;
	TADOStoredProc *spdabao;
	TRvProject *rp;
	TRvDataSetConnection *rv;
	TADOQuery *querydabao;
	TRvSystem *rs;
	TfrxReport *frxpbag1;
	TfrxDBDataset *frxdbpbag;
	TfrxReport *frxpbag;
	TRzButton *RzButton5;
	TRzButton *RzButton6;
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton3Click(TObject *Sender);
	void __fastcall RzButton5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	AnsiString xuhao;
	int stgid;
	int userid;
	int headid;
	AnsiString bkcatalogid,wsids;
	__fastcall Tfrmprintbag(TComponent* Owner,TADOConnection *con,AnsiString ids);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmprintbag *frmprintbag;
//---------------------------------------------------------------------------
#endif
