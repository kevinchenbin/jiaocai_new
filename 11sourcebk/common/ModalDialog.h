//---------------------------------------------------------------------------

#ifndef ModalDialogH
#define ModalDialogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include "pdtypes.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmModalDialog : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel2;
	TRzButton *btnOk;
	TRzButton *btnCancel;
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
	void __fastcall OnHotKey(TMessage&);
protected:
	TApplication* m_app;
	TADOConnection* m_con;
	int m_userID;
	int m_storageID;
public:		// User declarations
	__fastcall TfrmModalDialog(TComponent* Owner);
	virtual void Init(TApplication* app, TADOConnection* con);
	virtual void Init(LandInfo* li);
	BEGIN_MESSAGE_MAP
	MESSAGE_HANDLER(WM_HOTKEY,TMessage,OnHotKey)
	END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmModalDialog *frmModalDialog;
//---------------------------------------------------------------------------
#endif
