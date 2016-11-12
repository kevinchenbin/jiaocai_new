//---------------------------------------------------------------------------

#ifndef UnitkuchengjizhuanH
#define UnitkuchengjizhuanH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmkuchenjizhuan : public TForm
{
__published:	// IDE-managed Components
	TSpeedButton *SpeedButton1;
	TMemo *membk;
	TLabel *Label1;
	TADOConnection *cn;
	TADOQuery *aq;
	void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
          TADOConnection *acn;
        int fuserid;
        int fstgid;
	__fastcall Tfrmkuchenjizhuan(TComponent* Owner,TADOConnection *fcn,int userid,int stgid);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmkuchenjizhuan *frmkuchenjizhuan;
//---------------------------------------------------------------------------
#endif
