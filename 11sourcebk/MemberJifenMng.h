//---------------------------------------------------------------------------

#ifndef MemberJifenMngH
#define MemberJifenMngH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfrmMemberjifen : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TPanel *Panel1;
	TADOQuery *aq;
	TGroupBox *GroupBox1;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *query;
	TADOConnection *fcon;
	TGroupBox *GroupBox2;
	TComboBox *cbmembertype;
	TEdit *eddot;
	TEdit *eddotset;
	TEdit *edmoney;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TButton *btsave;
	TPopupMenu *pm;
	TMenuItem *N1;
	TADOQuery *aq1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TLabel *labjifen;
	TEdit *edjifen;
	TLabel *Label6;
	TEdit *edyouhui;
	TLabel *Label7;
	TButton *Button1;
	TGroupBox *GroupBox3;
	TDBGrid *DBGrid2;
	TDataSource *ds1;
	TADOQuery *query1;
	TButton *Button2;
	void __fastcall btsaveClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall DBGrid2CellClick(TColumn *Column);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmMemberjifen(TComponent* Owner,TADOConnection *con);
	int stgid;
	int currentmax;
	void __fastcall MaxMin();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMemberjifen *frmMemberjifen;
//---------------------------------------------------------------------------
#endif
