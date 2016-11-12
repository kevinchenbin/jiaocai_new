//---------------------------------------------------------------------------

#ifndef UnitWSSetH
#define UnitWSSetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class Tfrmwsset : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPageControl *pc;
	TTabSheet *TS1;
	TTabSheet *TS3;
	TTabSheet *TS2;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *editclientname;
	TSpeedButton *spsearch;
	TDBGrid *DBGrid1;
	TLabel *Label2;
	TEdit *editalarmcredit;
	TLabel *Label3;
	TEdit *editlockcredit;
	TLabel *Label4;
	TDateTimePicker *cridetbegin;
	TLabel *Label5;
	TDateTimePicker *creditend;
	TGroupBox *GroupBox2;
	TCheckBox *cbbalance;
	TSpeedButton *creditsave;
	TGroupBox *GroupBox3;
	TTabSheet *TS4;
	TTabSheet *TS5;
	TLabel *lb;
	TEdit *returnclientname;
	TLabel *Label6;
	TEdit *proreturnrate;
	TLabel *Label7;
	TEdit *localreturnrate;
	TLabel *Label8;
	TDateTimePicker *returnbegin;
	TLabel *Label9;
	TDateTimePicker *returnend;
	TSpeedButton *spclientsearch;
	TGroupBox *GroupBox4;
	TSpeedButton *returnadd;
	TDBGrid *DBGrid3;
	TGroupBox *GroupBox5;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *typereturnrate;
	TLabel *Label12;
	TEdit *localtypereturnrate;
	TLabel *Label13;
	TDateTimePicker *typestart;
	TLabel *Label14;
	TDateTimePicker *typeend;
	TDBGrid *DBGrid4;
	TGroupBox *GroupBox6;
	TSpeedButton *typeadd;
	TGroupBox *GroupBox7;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TEdit *edBarcode;
	TEdit *bookproreturnrate;
	TEdit *localbookreturnrate;
	TDateTimePicker *bookbegin;
	TDateTimePicker *bookend;
	TGroupBox *GroupBox8;
	TSpeedButton *bookadd;
	TDBGrid *DBGrid5;
	TLabel *Label20;
	TEdit *edbookname;
	TLabel *Label21;
	TEdit *edprice;
	TLabel *Label22;
	TEdit *edpress;
	TGroupBox *GroupBox9;
	TLabel *Label23;
	TSpeedButton *SpeedButton4;
	TLabel *Label24;
	TLabel *Label25;
	TEdit *backclientname;
	TEdit *monthbakarate;
	TEdit *yearbackrate;
	TDBGrid *DBGrid2;
	TGroupBox *GroupBox10;
	TSpeedButton *backadd;
	TLabel *Label26;
	TEdit *probackrate;
	TLabel *Label27;
	TEdit *localdeliverybackrate;
	TADOQuery *aq;
	TTabSheet *TS6;
	TGroupBox *GroupBox11;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TLabel *Label31;
	TLabel *Label32;
	TEdit *pressreturnrate;
	TEdit *localpressreturnrate;
	TDateTimePicker *pressstart;
	TDateTimePicker *pressend;
	TDBGrid *DBGrid6;
	TGroupBox *GroupBox12;
	TSpeedButton *pressadd;
	TComboBox *cbpress;
	TSpeedButton *creditenable;
	TSpeedButton *crditadd;
	TDataSource *ds;
	TSpeedButton *backsave;
	TSpeedButton *backactive;
	TSpeedButton *returnsave;
	TSpeedButton *returnactive;
	TSpeedButton *typesave;
	TSpeedButton *typeactive;
	TSpeedButton *booksave;
	TSpeedButton *bookactive;
	TSpeedButton *presssave;
	TSpeedButton *pressactive;
	TLabel *Label33;
	TLabel *Label34;
	TDateTimePicker *dtpbackbegin;
	TDateTimePicker *dtpbackend;
	TComboBox *cbbooktype;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	void __fastcall spsearchClick(TObject *Sender);
	void __fastcall pcChange(TObject *Sender);
	void __fastcall creditsaveClick(TObject *Sender);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall creditenableClick(TObject *Sender);
	void __fastcall crditaddClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall backaddClick(TObject *Sender);
	void __fastcall backsaveClick(TObject *Sender);
	void __fastcall DBGrid2CellClick(TColumn *Column);
	void __fastcall returnaddClick(TObject *Sender);
	void __fastcall spclientsearchClick(TObject *Sender);
	void __fastcall returnsaveClick(TObject *Sender);
	void __fastcall DBGrid3CellClick(TColumn *Column);
	void __fastcall backactiveClick(TObject *Sender);
	void __fastcall returnactiveClick(TObject *Sender);
	void __fastcall cbbooktypeClick(TObject *Sender);
	void __fastcall cbpressClick(TObject *Sender);
	void __fastcall typeaddClick(TObject *Sender);
	void __fastcall typesaveClick(TObject *Sender);
	void __fastcall DBGrid4CellClick(TColumn *Column);
	void __fastcall DBGrid6CellClick(TColumn *Column);
	void __fastcall typeactiveClick(TObject *Sender);
	void __fastcall pressactiveClick(TObject *Sender);
	void __fastcall bookaddClick(TObject *Sender);
	void __fastcall edBarcodeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall booksaveClick(TObject *Sender);
	void __fastcall DBGrid5CellClick(TColumn *Column);
	void __fastcall bookactiveClick(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall presssaveClick(TObject *Sender);
	void __fastcall pressaddClick(TObject *Sender);
	void __fastcall editclientnameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editalarmcreditKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editlockcreditKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cridetbeginKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall creditendKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbbalanceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall backclientnameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall monthbakarateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall yearbackrateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall probackrateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall localdeliverybackrateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtpbackbeginKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtpbackendKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall returnclientnameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall proreturnrateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall localreturnrateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall returnbeginKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall returnendKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbbooktypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall typereturnrateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall localtypereturnrateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall typestartKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall typeendKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall bookproreturnrateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall localbookreturnrateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall bookbeginKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall bookendKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall pressreturnrateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall localpressreturnrateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall pressstartKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall pressendKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall pressreturnrateExit(TObject *Sender);
	void __fastcall localpressreturnrateExit(TObject *Sender);
	void __fastcall localbookreturnrateExit(TObject *Sender);
	void __fastcall bookproreturnrateExit(TObject *Sender);
	void __fastcall typereturnrateExit(TObject *Sender);
	void __fastcall localtypereturnrateExit(TObject *Sender);
	void __fastcall proreturnrateExit(TObject *Sender);
	void __fastcall localreturnrateExit(TObject *Sender);
	void __fastcall monthbakarateExit(TObject *Sender);
	void __fastcall yearbackrateExit(TObject *Sender);
	void __fastcall probackrateExit(TObject *Sender);
	void __fastcall localdeliverybackrateExit(TObject *Sender);
	void __fastcall editalarmcreditExit(TObject *Sender);
	void __fastcall editlockcreditExit(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
  TADOConnection *fcon;
  void Enable(int type);
  void showData(int type);
  int clientID,BookType,PressID,CatalogID;
  AnsiString ClientName;
  void DoInvokClient(TEdit *clientName);
  void RefreshDbGrid(int type ,TDBGrid *dg);
  int type;
  int ID;
public:		// User declarations
	__fastcall Tfrmwsset(TComponent* Owner,TADOConnection *cn,int stgid);
	void __fastcall ReadyData();
	int m_storageID;
	AnsiString  voidClientName();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmwsset *frmwsset;
//---------------------------------------------------------------------------
#endif
