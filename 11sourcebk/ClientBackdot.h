//---------------------------------------------------------------------------

#ifndef ClientBackdotH
#define ClientBackdotH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmClientBackdot : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TPanel *Panel1;
	TEdit *edname;
	TADOConnection *fcon;
	TADOQuery *aq;
	TGroupBox *GroupBox2;
	TDBGrid *DBGrid1;
	TGroupBox *GroupBox3;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TDataSource *ds1;
	TDataSource *ds2;
	TADOQuery *query1;
	TADOQuery *query2;
	TLabel *Label3;
	TLabel *Label1;
	TEdit *edlow;
	TEdit *edhight;
	TLabel *Label2;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *edbackdot;
	TLabel *Label6;
	TDBGrid *DBGrid2;
	TButton *btquery;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TLabel *Label7;
	TComboBox *cbstorage;
	void __fastcall btqueryClick(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edlowKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edhightKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall DBGrid2CellClick(TColumn *Column);
	void __fastcall ednameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall edbackdotKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbstorageSelect(TObject *Sender);




private:	// User declarations
	int fstgid;
public:		// User declarations
	__fastcall TfrmClientBackdot(TComponent* Owner,TADOConnection *con,int stgid);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmClientBackdot *frmClientBackdot;
//---------------------------------------------------------------------------
#endif
