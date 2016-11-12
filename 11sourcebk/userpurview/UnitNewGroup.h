//---------------------------------------------------------------------------

#ifndef UnitNewGroupH
#define UnitNewGroupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzListVw.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzPanel.hpp"
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class Tfrmnewgroup : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *editgroupname;
	TLabel *Label2;
	TEdit *editdescript;
	TLabel *Label3;
	TGroupBox *GroupBox1;
	TSpeedButton *sbaddgroup;
	TSpeedButton *sbdelgroup;
	TSpeedButton *sbcreategroup;
	TSpeedButton *spclose;
	TImageList *ImageList1;
	TListView *listviewuser;
	TADOQuery *aqinsert;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	void __fastcall sbaddgroupClick(TObject *Sender);
	void __fastcall sbdelgroupClick(TObject *Sender);
	void __fastcall sbcreategroupClick(TObject *Sender);
	void __fastcall spcloseClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	TADOConnection *fcon ;
	int fstgid;
public:		// User declarations
	__fastcall Tfrmnewgroup(TComponent* Owner,TADOConnection *cn,int stgid);
	void ExcSQL(AnsiString SQL);
	int Type;//1Ìí¼Ó 2ÊôÐÔ£¨ÐÞ¸Ä)
	void ReadyGroupData(int groupID);
	int GroupID;
	int userid;
	AnsiString logmessage;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmnewgroup *frmnewgroup;
//---------------------------------------------------------------------------
#endif
