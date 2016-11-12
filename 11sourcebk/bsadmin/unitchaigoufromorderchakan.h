//---------------------------------------------------------------------------

#ifndef unitchaigoufromorderchakanH
#define unitchaigoufromorderchakanH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzBckgnd.hpp"
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzStatus.hpp"
#include "RzPrgres.hpp"
//---------------------------------------------------------------------------
class Tfrmdaochu : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TRzSeparator *RzSeparator1;
	TRzSeparator *RzSeparator2;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TLabel *Label1;
	TSpeedButton *SpeedButton3;
	TADOConnection *condddd;
	TADOQuery *ADOQuery1;
	TRzProgressBar *rp;
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
private:	// User declarations
   TADOConnection *fcn;
	UnicodeString   Path;
public:		// User declarations
	__fastcall Tfrmdaochu(TComponent* Owner);
	void ExcelOut();
	AnsiString DanHao;
	AnsiString info;
	void init(TADOConnection *cn,int stgid);
	AnsiString printtitle,address,printbk,shaddress,shtel,shcontact;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmdaochu *frmdaochu;
//---------------------------------------------------------------------------
#endif
