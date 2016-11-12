//---------------------------------------------------------------------------

#ifndef UnittongqisaleH
#define UnittongqisaleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ComCtrls.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include <Buttons.hpp>
#include "DBCtrlsEh.hpp"
#include <Mask.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzEdit.hpp"
#include <Dialogs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmtongqisale : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExit;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TRadioGroup *rg;
	TEdit *edname;
	TComboBox *cbtype;
	TComboBox *cpress;
	TSpeedButton *spselectClient;
	TEdit *edclient;
	TEdit *edtclient;
	TLabel *Label2;
	TADOConnection *fcon;
	TRzToolButton *BtnAlignBottom;
	TDataSource *ds;
	TADOQuery *query;
	TDateTimePicker *dtpstart1;
	TDateTimePicker *dtpstart2;
	TADOStoredProc *adosp;
	TDataSource *DataSource1;
	TADODataSet *adods;
	TLabel *Label4;
	TButton *Button1;
	TDateTimePicker *dtpstart3;
	TDateTimePicker *dtpstart4;
	TLabel *Label3;
	TLabel *Label5;
	TBitBtn *alltype;
	TButton *Button2;
	TRzToolButton *BtnExport;
	TSaveDialog *savefile;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TEdit *editselect;
	TDBGridEh *dg;
	TButton *Button3;
	TCheckBox *chfenji;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall alltypeClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall editselectMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall dgTitleClick(TColumnEh *Column);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmtongqisale(TComponent* Owner,TADOConnection *con,int stgid);
	int fstgid,ClientID;
	int danpingselect;
	void ClientView();
	String format;
	bool clientAll ;

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmtongqisale *frmtongqisale;
//---------------------------------------------------------------------------
#endif
