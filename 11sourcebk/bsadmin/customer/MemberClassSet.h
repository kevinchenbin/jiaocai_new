//---------------------------------------------------------------------------

#ifndef MemberClassSetH
#define MemberClassSetH
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
class Tfrmmemclassmg : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TImageList *imagelistmemcardclass;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnExit;
	TTreeView *TreeView1;
	TSplitter *Splitter1;
	TPanel *Panel2;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit1;
	TEdit *Edit2;
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmmemclassmg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmmemclassmg *frmmemclassmg;
//---------------------------------------------------------------------------
#endif
