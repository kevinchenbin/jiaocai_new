//---------------------------------------------------------------------------

#ifndef NewBookinputH
#define NewBookinputH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzCmboBx.hpp"
#include "RzDBGrid.hpp"
#include "RzRadChk.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "pdutil.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tfrmnewbook : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *editcode;
	TLabel *Label2;
	TEdit *editisbn;
	TLabel *Label3;
	TEdit *editbookname;
	TLabel *Label4;
	TEdit *editbookself;
	TEdit *editprice;
	TLabel *Label5;
	TEdit *editauthor;
	TLabel *Label6;
	TRzComboBox *rcbtype;
	TLabel *Label7;
	TRzComboBox *rcbpress;
	TRzDBGrid *RzDBGrid1;
	TRzCheckBox *rzcbinput;
	TADOQuery *aquery;
	TDataSource *ds;
	TSpeedButton *SpeedButton1;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall editcodeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall editbooknameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editauthorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rcbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rcbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall RzDBGrid1CellClick(TColumn *Column);
private:	// User declarations
	TADOConnection *fcon;
	String ID;
	char GetPYIndexChar(char *str);
public:		// User declarations
	__fastcall Tfrmnewbook(TComponent* Owner,TADOConnection *con);
	void ReadyData();
	String GetID();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmnewbook *frmnewbook;
//---------------------------------------------------------------------------
#endif
