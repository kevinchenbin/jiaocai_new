//---------------------------------------------------------------------------

#ifndef unitinitfahuoH
#define unitinitfahuoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzButton.hpp"
#include "MDIChild.h"
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrminitfahuo : public TForm
{
__published:	// IDE-managed Components
	TADOConnection *fcon;
	TDataSource *ds1;
	TRzToolbar *RzToolbar1;
	TPanel *Panel1;
	TImageList *ImageList1;
	TDBGrid *DBGrid1;
	TADOQuery *aq1;
	TDBGrid *DBGrid2;
	TDataSource *ds2;
	TADOQuery *aq2;
	TRzToolButton *BtnView;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnOK;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TADOCommand *cmdAddNote;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *edcode;
	TEdit *eduser;
	TDateTimePicker *dtpdate;
	TLabel *Label4;
	TEdit *edstate;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	TSpeedButton *SpeedButton4;
	TGroupBox *GroupBox4;
	TCheckBox *ch0;
	TCheckBox *ch1;
	TCheckBox *ch3;
	TCheckBox *ch4;
	TCheckBox *ch2;
	TCheckBox *chbanji;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TLabel *Label5;
	TEdit *edamount;
	TLabel *Label6;
	TEdit *edmayang;
	TADOQuery *aq;
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall aq2BeforePost(TDataSet *DataSet);
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall ch0Click(TObject *Sender);
	void __fastcall ch1Click(TObject *Sender);
	void __fastcall ch2Click(TObject *Sender);
	void __fastcall ch3Click(TObject *Sender);
	void __fastcall ch4Click(TObject *Sender);
	void __fastcall aq2PostError(TDataSet *DataSet, EDatabaseError *E, TDataAction &Action);
	void __fastcall DBGrid2DblClick(TObject *Sender);
	void __fastcall DBGrid2MouseLeave(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall aq2AfterPost(TDataSet *DataSet);

private:	// User declarations
public:		// User declarations
	__fastcall Tfrminitfahuo(TComponent* Owner);
	int fgroupid;
	void ShowClient();
	LandInfo linfo;
	void AddNote();
	AnsiString returncode;
	int sgfirsthid,sgheaderid;
	void Init(LandInfo* li);
	void QryNtHeader(AnsiString code);
	void DbgridToExcel();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrminitfahuo *frminitfahuo;
//---------------------------------------------------------------------------
#endif
