//---------------------------------------------------------------------------

#ifndef CatalogkanliH
#define CatalogkanliH
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
#include "RzEdit.hpp"
#include "RzLine.hpp"
#include <Mask.hpp>
#include "RzRadGrp.hpp"
#include "RzLabel.hpp"
#include <ComCtrls.hpp>
#include "RzSpnEdt.hpp"
#include "StrUtils.hpp"
#include <Dialogs.hpp>
#include <Menus.hpp>
#include "RzDTP.hpp"
//---------------------------------------------------------------------------
class TfrmCatalogkanli : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TRzCheckBox *rzcbinput;
	TADOQuery *aquery;
	TDataSource *ds;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnClear;
	TRzToolButton *BtnCancel;
	TRzLine *RzLine1;
	TRzRadioGroup *radiogroup;
	TADOQuery *query;
	TPanel *Panel2;
	TRzEdit *edtotalmayang;
	TRzEdit *edtotalrecord;
	TLabel *Label9;
	TRzLabel *RzLabel1;
	TPageControl *PageControlBook;
	TTabSheet *tsbase;
	TTabSheet *tsdetail;
	TLabel *Label1;
	TEdit *editcode;
	TLabel *Label2;
	TEdit *editisbn;
	TSpeedButton *SpeedButton1;
	TLabel *Label3;
	TEdit *editbookname;
	TEdit *editbookself;
	TLabel *Label4;
	TEdit *editprice;
	TLabel *Label5;
	TEdit *editauthor;
	TLabel *Label6;
	TLabel *Label7;
	TComboBox *rcbpress;
	TDBGrid *DBGrid1;
	TLabel *Label14;
	TLabel *Label12;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label19;
	TEdit *edISBNtype;
	TEdit *edbook;
	TRzToolButton *BtnView;
	TLabel *Label8;
	TComboBox *cbsaletype;
	TLabel *Label20;
	TEdit *edaffix;
	TLabel *Label11;
	TDateTimePicker *datapressday;
	TLabel *Label13;
	TLabel *Label10;
	TEdit *edyizhe;
	TSpeedButton *btaddtype;
	TSpeedButton *btaddpress;
	TComboBox *cbformat;
	TComboBox *cbbind;
	TLabel *Label18;
	TEdit *edbk;
	TComboBox *rcbtype;
	TRzSpinEdit *edprintcount;
	TLabel *Label23;
	TLabel *Label24;
	TPageControl *pcqikan;
	TTabSheet *»ù±¾ÊôÐÔ;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label31;
	TEdit *editqikanmao;
	TEdit *editqikanname;
	TEdit *editqikanissn;
	TEdit *editqikanself;
	TEdit *editqikanprice;
	TEdit *editqikanqihao;
	TEdit *editqikanfaxing;
	TPageControl *pcwenju;
	TTabSheet *TabSheet1;
	TLabel *Label30;
	TLabel *Label32;
	TLabel *Label33;
	TEdit *editwenjutiaomao;
	TEdit *editwenjuname;
	TEdit *editwenjuprice;
	TDBGrid *dg;
	TADOQuery *aqinsert;
	TEdit *editwenjuself;
	TDataSource *dsinsert;
	TRzToolButton *BtnJumptoLine;
	TEdit *edquery;
	TRzToolButton *BtnAlignBottom;
	TCheckBox *chtaoshu;
	TSaveDialog *savedlg;
	TPopupMenu *pm;
	TMenuItem *N1;
	TEdit *edpresscount;
	TRzToolButton *BtnAlignClient;
	TLabel *Label21;
	TLabel *Label17;
	TRzSpinEdit *spepack;
	TEdit *edhuojiangstate;
	TRzToolButton *BtnUndo;
	TLabel *Label34;
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
	void __fastcall edtQueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall radiogroupClick(TObject *Sender);
	void __fastcall BtnCancelClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall DBGrid1CellClick(TColumn *Column);
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
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall btaddtypeClick(TObject *Sender);
	void __fastcall btaddpressClick(TObject *Sender);
	void __fastcall cbsaletypeChange(TObject *Sender);
	void __fastcall editqikanmaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanqihaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editwenjupriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikannameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanissnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanfaxingKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editwenjutiaomaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editwenjunameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgCellClick(TColumn *Column);
	void __fastcall BtnJumptoLineClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editisbnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall chtaoshuKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editbookselfKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall DBGrid1TitleClick(TColumn *Column);
	void __fastcall BtnAlignClientClick(TObject *Sender);
	void __fastcall edhuojiangstateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spepackKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpresscountKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnUndoClick(TObject *Sender);


private:	// User declarations
	TADOConnection *fcon;
	String ID;
	char GetPYIndexChar(char *str);
	int modle;
	int type;
	void ShowInput(int type);
	AnsiString GetSelf(AnsiString context);
	AnsiString BarCodeToISSN(AnsiString BarCode);
	AnsiString ISSNToBarCode(AnsiString ISSN);

public:		// User declarations
	__fastcall TfrmCatalogkanli(TComponent* Owner,TADOConnection *con,int stgid,int userid);
	void ReadyData();
	String GetID();
	void Query(String condition);
	int __fastcall BrocodeToPress(String brocode);
	bool __fastcall DbgridToExcel(TDBGrid* dbg);
	void Press(int mode);
	int fstgid,fuserid;
	AnsiString logmessage;
         bool  bdel,bookcatalogadd,bcatalogmodify;
                void checknewsupplier();
                void disablenewsupplierornewbook();
                bool add;
                bool del;
                bool mod;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCatalogkanli *frmCatalogkanli;
//---------------------------------------------------------------------------
#endif
