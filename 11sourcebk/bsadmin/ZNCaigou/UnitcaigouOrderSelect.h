//---------------------------------------------------------------------------

#ifndef UnitcaigouOrderSelectH
#define UnitcaigouOrderSelectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "RzButton.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include <Menus.hpp>
#include "RzDBCmbo.hpp"
#include <DBCtrls.hpp>
#include "RzDTP.hpp"
#include "RzSpnEdt.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class Tfrmcaigouorderselect : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TSpeedButton *spselectClient;
	TCheckBox *chordercode;
	TEdit *edordercode;
	TCheckBox *chclient;
	TEdit *edclient;
	TCheckBox *chdate;
	TEdit *edtclient;
	TDataSource *ds;
	TADOQuery *query;
	TADOConnection *con;
	TDBGrid *DBGrid2;
	TDataSource *ds2;
	TADOQuery *query2;
	TRzButton *RzButton2;
	TComboBox *cbstg;
	TLabel *Label1;
	TGroupBox *GroupBox2;
	TRzLabel *lblCatalog;
	TRzEdit *edtCatalog;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N14;
	TCheckBox *chtype;
	TCheckBox *chpress;
	TCheckBox *chbook;
	TEdit *editindex;
	TComboBox *cbtype;
	TDataSource *dssupplier;
	TDataSource *dspress;
	TADOQuery *aq;
	TComboBox *cbpress;
	TCheckBox *cbenddate;
	TPopupMenu *pmselect;
	TMenuItem *S1;
	TMenuItem *C1;
	TRzButton *RzButton1;
	TCheckBox *chshiji;
	TRzDateTimePicker *dtpdate;
	TRzDateTimePicker *dtenddate;
	TRzDateTimeEdit *dtedtDate;
	TRzSpinEdit *spedtID;
	TCheckBox *chuser;
	TComboBox *cbuser;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TCheckBox *cbclient;
	TEdit *editclient;
	TCheckBox *cbordernum;
	TEdit *editordernum;
	TADOStoredProc *sp;
	TRadioGroup *rg;
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall editindexsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editindexKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall DBGrid2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall S1Click(TObject *Sender);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall cbsupplierChange(TObject *Sender);
	void __fastcall edtclientChange(TObject *Sender);
	void __fastcall edordercodeChange(TObject *Sender);
	void __fastcall dtedtDateChange(TObject *Sender);
	void __fastcall spedtIDChange(TObject *Sender);
	void __fastcall cbstgClick(TObject *Sender);
	void __fastcall cbuserChange(TObject *Sender);
	void __fastcall DBGrid2TitleClick(TColumn *Column);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall editclientChange(TObject *Sender);
	void __fastcall editordernumChange(TObject *Sender);
private:	// User declarations
	bool blSelect;
	 TBookmark BookMark;
public:		// User declarations
	__fastcall Tfrmcaigouorderselect(TComponent* Owner,TADOConnection *cn,int stgid,int hgid,int gid,int userid);
	int fstgid,fuserid;
	void bandData();
	int ClientID,groupid,hgroupid;
    int SelectIndex;
	void ClientView();
	void IntoTmporder();

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmcaigouorderselect *frmcaigouorderselect;
//---------------------------------------------------------------------------
#endif