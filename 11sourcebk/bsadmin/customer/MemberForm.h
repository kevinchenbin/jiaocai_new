//---------------------------------------------------------------------------

#ifndef MemberFormH
#define MemberFormH
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
//---------------------------------------------------------------------------
class TfrmMember : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton4;
	TRzToolButton *RzToolButton5;
	TRzToolButton *RzToolButton7;
	TRzToolButton *RzToolButton8;
	TImageList *ImageListmember;
	TPanel *Panel1;
	TSplitter *Splitter1;
	TTreeView *tvclass;
	TPanel *Panel2;
	TDBGrid *dgmemlist;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *edtcardnum;
	TLabel *Label2;
	TEdit *edtname;
	TSpeedButton *sbquery;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	TStringList * MemberinfoList;
public:		// User declarations
	__fastcall TfrmMember(TComponent* Owner);

};

//---------------------------------------------------------------------------
extern PACKAGE TfrmMember *frmMember;
//---------------------------------------------------------------------------
#endif
