//---------------------------------------------------------------------------

#ifndef bookQueryH
#define bookQueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include <Menus.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tfrmbookquery : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TPanel *Panel1;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *aq;
	TMenuItem *N5;
	TGroupBox *GroupBox1;
	TCheckBox *chother;
	TSpeedButton *SpeedButton1;
	TCheckBox *chisbn;
	TRzEdit *edisbn;
	TCheckBox *chname;
	TRzEdit *edname;
	TCheckBox *chuserdefcode;
	TRzEdit *eduserdefcode;
	TCheckBox *chauthor;
	TRzEdit *edauthor;
	TCheckBox *chprice;
	TRzEdit *edprice;
	TADOQuery *query;
	TCheckBox *chtype;
	TRzEdit *edtype;
	TCheckBox *chpress;
	TRzEdit *edpress;
	TComboBox *cbtype;
	TComboBox *cbpress;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall edpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edisbnChange(TObject *Sender);
	void __fastcall edisbnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ednameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall eduserdefcodeChange(TObject *Sender);
	void __fastcall eduserdefcodeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpriceChange(TObject *Sender);
	void __fastcall edauthorChange(TObject *Sender);
	void __fastcall edauthorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbtypeChange(TObject *Sender);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall cbpressKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
	int m_catalogSearchMode,m_storageID;
public:		// User declarations
	__fastcall Tfrmbookquery(TComponent* Owner,TADOConnection *cn,int stgid);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmbookquery *frmbookquery;
//---------------------------------------------------------------------------
#endif
