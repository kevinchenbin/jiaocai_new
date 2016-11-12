//---------------------------------------------------------------------------

#ifndef UnitFeizhensiH
#define UnitFeizhensiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmfeizhengshicai : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TDataSource *ds1;
	TDataSource *ds2;
	TADOQuery *aq1;
	TADOQuery *aq2;
	TADOConnection *con;
	TPanel *Panel1;
	TRzDBGrid *RzDBGrid1;
	TRzDBGrid *RzDBGrid2;
	TButton *btok;
	TRzDBGrid *RzDBGrid3;
	TDataSource *ds3;
	TADOQuery *aq3;
	TPopupMenu *pm;
	TMenuItem *N1;
	TADOQuery *aq;
	TADOStoredProc *sp;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall RzDBGrid1CellClick(TColumn *Column);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btokClick(TObject *Sender);
	void __fastcall RzDBGrid3CellClick(TColumn *Column);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall RzDBGrid2MouseLeave(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmfeizhengshicai(TComponent* Owner,TADOConnection *cn,int groupid,int stgid,int userid);
	int group ;
	int feizhengshi,SupplierID,fstgid,fuserid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmfeizhengshicai *frmfeizhengshicai;
//---------------------------------------------------------------------------
#endif
