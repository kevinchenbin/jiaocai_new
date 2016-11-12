//---------------------------------------------------------------------------

#ifndef LandFormH
#define LandFormH
#include <ADODB.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "RzBmpBtn.hpp"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class TfrmLand : public TForm
{
__published:	// IDE-managed Components
	TADODataSet *ADODataSet;
	TADOConnection *conLand;
	TPanel *plogin;
	TLabel *Label1;
	TLabel *Label2;
	TComboBox *cbName;
	TEdit *edtPassword;
	TPanel *pchangepd;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *edtoldpd;
	TEdit *edtnewpd;
	TEdit *edtconfirmpd;
	TLabel *lbzhangtao;
	TComboBox *cbzhangtao;
	TADOConnection *conaccount;
	TLabel *Label6;
	TComboBox *cbstorage;
	TImage *Image1;
	TSpeedButton *sblogin;
	TSpeedButton *sblogcancel;
	TSpeedButton *sbchangepd;
	TImage *Image2;
	TSpeedButton *sbcancel;
	TSpeedButton *sbok;
	void __fastcall cbNameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sbloginClick(TObject *Sender);
	void __fastcall sbchangepdClick(TObject *Sender);
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall cbzhangtaoChange(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
	void __fastcall sblogcancelClick(TObject *Sender);
	void __fastcall edtoldpdKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtconfirmpdKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbstorageChange(TObject *Sender);
	void __fastcall cbNameChange(TObject *Sender);

private:	// User declarations
	int m_user,userid;
	int m_storage,stgid;
	bool m_master;
	AnsiString dbServer;
	AnsiString UserName,Zhangtao;
	AnsiString pd;
	AnsiString up;
	AnsiString fullaccount;
	AnsiString LoginConstr;
   //	int MAX_PATH = 100;
public:		// User declarations
	__fastcall TfrmLand(TComponent* Owner);
	int GetUserID();
	int GetStorageID();
	AnsiString GetUserName();
	void __fastcall UserView();
	bool GetMaster();

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmLand *frmLand;
//---------------------------------------------------------------------------
#endif
