//---------------------------------------------------------------------------

#ifndef UnitTaskdetailH
#define UnitTaskdetailH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include "RzShellDialogs.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmnewtask : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *edituser;
	TLabel *Label2;
	TEdit *editreceiver;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TMemo *memcontent;
	TLabel *Label6;
	TEdit *editattchment;
	TSpeedButton *SpeedButton1;
	TLabel *Label7;
	TEdit *edittitle;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TRzOpenDialog *openfile;
	TADOQuery *aq;
	TSpeedButton *SpeedButton4;
	TDateTimePicker *DateTimePicker1;
	TDateTimePicker *DateTimePicker2;
	TADOStoredProc *newtask;
	TADOStoredProc *SendMsgReceiver;
	TComboBox *cbstate;
	TLabel *Label8;
	TSaveDialog *savefile;
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
private:	// User declarations
	 TADOConnection *fcn;
	 int intuserid;
	 TStringList *tempstr;

public:		// User declarations
	__fastcall Tfrmnewtask(TComponent* Owner);
	void init(TADOConnection *cn,int userid);
	void RefreshData();
	AnsiString  TaskID;
	int checkUserID;//点保存时，检查改任务是不是改用户自己所建
	int Model;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmnewtask *frmnewtask;
//---------------------------------------------------------------------------
#endif
