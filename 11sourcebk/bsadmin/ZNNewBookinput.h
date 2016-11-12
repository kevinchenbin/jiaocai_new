//---------------------------------------------------------------------------

#ifndef ZNNewBookinputH
#define ZNNewBookinputH
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
#include "StorageMngForm.h"
#include <ComCtrls.hpp>
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include "RzLine.hpp"
//---------------------------------------------------------------------------
class Tfrmnewbook : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TADOQuery *aquery;
	TDataSource *ds;
	TPanel *Panel1;
	TRzDBGrid *RzDBGrid1;
	TRzCheckBox *rzcbinput;
	TPageControl *PageControlBook;
	TTabSheet *tsbase;
	TLabel *Label8;
	TLabel *Label9;
	TSpeedButton *SpeedButton2;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label21;
	TLabel *Label22;
	TEdit *editcode;
	TEdit *editisbn;
	TEdit *editbookname;
	TEdit *editbookself;
	TEdit *editprice;
	TEdit *editauthor;
	TComboBox *rcbtype;
	TComboBox *rcbpress;
	TDateTimePicker *datapressday;
	TRzSpinEdit *sedpresscount;
	TTabSheet *tsdetail;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label23;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TEdit *edwords;
	TEdit *edISBNtype;
	TEdit *edbook;
	TEdit *edaffix;
	TEdit *edyizhe;
	TComboBox *cbformat;
	TComboBox *cbbind;
	TEdit *edbk;
	TRzSpinEdit *edprintcount;
	TLabel *Label1;
	TComboBox *cbsaletype;
	TRzLine *RzLine1;
	TPageControl *pcwenju;
	TTabSheet *TabSheet1;
	TLabel *Label30;
	TLabel *Label32;
	TLabel *Label33;
	TEdit *editwenjutiaomao;
	TEdit *editwenjuname;
	TEdit *editwenjuself;
	TEdit *editwenjuprice;
	TPageControl *pcqikan;
	TTabSheet *TabSheet2;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label31;
	TEdit *editqikanmao;
	TEdit *editqikanname;
	TEdit *editqikanissn;
	TEdit *editqikanself;
	TEdit *editqikanprice;
	TEdit *editqikanqihao;
	TEdit *editqikanfaxing;
	TDBGrid *dg;
	TADOQuery *aqinsert;
	TDataSource *dsinsert;
	TEdit *edquery;
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
	void __fastcall datapressdayKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sedpresscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edISBNtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edyizheKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edprintcountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edaffixKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbformatKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbbindKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edbookKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edwordsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edbkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbsaletypeChange(TObject *Sender);
	void __fastcall editqikanqihaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editwenjupriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanmaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanissnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikannameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanfaxingKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editwenjutiaomaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editwenjunameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgCellClick(TColumn *Column);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editisbnKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
	TADOConnection *fcon;
	String ID;
	char GetPYIndexChar(char *str);
	TfrmStorageMng *from;
	int BrocodeToPress(String brocode);
	int type;
		void ShowInput(int type);
	AnsiString GetSelf(AnsiString context);
	AnsiString BarCodeToISSN(AnsiString BarCode);
	AnsiString ISSNToBarCode(AnsiString ISSN);
public:		// User declarations
	__fastcall Tfrmnewbook(TComponent* Owner,TADOConnection *con,TfrmStorageMng *frm);
	void ReadyData();
	String GetID();
	void Press(int mode);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmnewbook *frmnewbook;
//---------------------------------------------------------------------------
#endif
