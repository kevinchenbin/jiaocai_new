//---------------------------------------------------------------------------

#ifndef MemberCardH
#define MemberCardH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmMemberCard : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TImageList *ImageListMemcard;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnSkipBackward;
	TRzToolButton *BtnRewind;
	TRzToolButton *BtnFastForward;
	TRzToolButton *BtnSkipForward;
	TRzToolButton *BtnExit;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmMemberCard(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMemberCard *frmMemberCard;
//---------------------------------------------------------------------------
#endif
