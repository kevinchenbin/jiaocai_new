//---------------------------------------------------------------------------

#ifndef detailemessageH
#define detailemessageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Mask.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzCmboBx.hpp"
//---------------------------------------------------------------------------
class TDetaileForm : public TForm
{
__published:	// IDE-managed Components
	TRzGroupBox *RzGroupBox1;
	TRzLabel *RzLabel2;
	TRzLabel *RzLabel3;
	TRzLabel *RzLabel4;
	TRzLabel *RzLabel5;
	TRzLabel *RzLabel9;
	TRzLabel *RzLabel11;
	TRzLabel *RzLabel8;
	TLabel *Label1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TADOQuery *aqinit;
	TADOQuery *aqdetail;
	TRzComboBox *CBlocal;
	TRzComboBox *CBsale;
	TRzEdit *dbedtName;
	TRzEdit *dbedit;
	TRzEdit *dbeditContact;
	TEdit *edtphone;
	TEdit *edtcode;
	TEdit *edtfax;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
private:	// User declarations
	int modsave,Type;
	String ID;
public:		// User declarations
	__fastcall TDetaileForm(TComponent* Owner,int type,int savamod,String id,TADOConnection *cnn);
	void Initsalesman();
	void InitLocalinfo();
};
//---------------------------------------------------------------------------
extern PACKAGE TDetaileForm *DetaileForm;
//---------------------------------------------------------------------------
#endif
