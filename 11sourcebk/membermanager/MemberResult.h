//---------------------------------------------------------------------------

#ifndef MemberResultH
#define MemberResultH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzLine.hpp"
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Buttons.hpp>
#include <DBTables.hpp>
#include <DBClient.hpp>
#include "MemberCard.h"
#include "MemberCardaddvalue.h"
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TfrmMemberResult : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *btEsc;
	TImageList *ImageListmember;
	TPanel *Panel1;
	TSplitter *Splitter1;
	TADODataSet *dsMemberInfo;
	TADOQuery *quMemberInfo;
	TDataSource *DataSource1;
	TADOQuery *quType;
	TComboBox *cbMemberType;
	TPanel *Panel2;
	TDBGrid *dgmemlist;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edtcardnum;
	TEdit *edtname;
	TADOQuery *quMemberCard;
	TADOQuery *quMemberRecord;
	TOpenTextFileDialog *OpenTextFileDialog1;
	TRzToolButton *BtnNote;
	TRzToolButton *BtnView;
	TLabel *Label4;
	TRzToolButton *BtnAlignBottom;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btEscClick(TObject *Sender);
	void __fastcall cbMemberTypeSelect(TObject *Sender);
	void __fastcall dgmemlistTitleClick(TColumn *Column);
	void __fastcall edtcardnumKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtnameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnNoteClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);


private:	// User declarations
	TStringList * MemberinfoList;
    TADOConnection *fcon;
public:		// User declarations
	__fastcall TfrmMemberResult(TComponent* Owner,TADOConnection *cn);
	bool __fastcall DbgridToExcel(TDBGrid* dbg);
	int userid,stgid;
};

//---------------------------------------------------------------------------
extern PACKAGE TfrmMemberResult *frmMemberResult;
//---------------------------------------------------------------------------
#endif
