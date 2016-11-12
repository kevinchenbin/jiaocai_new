//---------------------------------------------------------------------------

#ifndef CheckQueryH
#define CheckQueryH
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
#include "RzDTP.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzRadChk.hpp"
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include "RzDBGrid.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TCheckInQuery : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExit;
	TRzLabel *RzLabel1;
	TRzLabel *RzLabel2;
	TRzCheckBox *CBstarttime;
	TRzCheckBox *CBendtime;
	TRzEdit *edtstore;
	TRzComboBox *cblocal;
	TRzDateTimePicker *DTPstarttime;
	TRzDateTimePicker *DTPendtime;
	TRzDBGrid *DBGridbase;
	TADOQuery *Querybase;
	TADOQuery *Querymingxi;
	TDataSource *ds1;
	TDataSource *ds2;
	TRzLabel *Labelselect;
	TRzEdit *condition;
	TPopupMenu *PM;
	TMenuItem *useselfcode;
	TMenuItem *bencno;
	TMenuItem *bookname;
	TMenuItem *author;
	TMenuItem *ISBN;
	TADOQuery *Querylocal;
	TRzDBGrid *DBGridmingxi;
	TRzLabel *Labelrecord;
	void __fastcall LabelselectMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall useselfcodeClick(TObject *Sender);
	void __fastcall bencnoClick(TObject *Sender);
	void __fastcall booknameClick(TObject *Sender);
	void __fastcall authorClick(TObject *Sender);
	void __fastcall ISBNClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall DBGridbaseCellClick(TColumn *Column);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall CBstarttimeClick(TObject *Sender);
	void __fastcall CBendtimeClick(TObject *Sender);


private:	// User declarations
	int serchModle;
public:		// User declarations
	__fastcall TCheckInQuery(TComponent* Owner,TADOConnection *cn);
};
//---------------------------------------------------------------------------
extern PACKAGE TCheckInQuery *CheckInQuery;
//---------------------------------------------------------------------------
#endif
