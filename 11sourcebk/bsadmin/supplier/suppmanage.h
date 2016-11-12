//---------------------------------------------------------------------------

#ifndef suppmanageH
#define suppmanageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include "RzCmboBx.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TSuppMana : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnFinish;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnExit;
	TRzGroupBox *RzGroupBox1;
	TRzGroupBox *RzGroupBox2;
	TRzLabel *RzLabel1;
	TRzEdit *etname;
	TLabel *Label1;
	TRzEdit *etcontax;
	TLabel *Label2;
	TLabel *Label3;
	TRzToolButton *BtnView;
	TRzComboBox *CBlocal;
	TRzComboBox *CBsale;
	TADOQuery *aqinit;
	TADOQuery *aqrecord;
	TRzDBGrid *DBGridrecord;
	TDataSource *ds;
	TADOConnection *cn;
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnFinishClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	int type;
public:		// User declarations
	__fastcall TSuppMana(TComponent* Owner,int Type,TADOConnection *cnn);
	void Initsalesman();
	void InitLocalinfo();

};
//---------------------------------------------------------------------------
extern PACKAGE TSuppMana *SuppMana;
//---------------------------------------------------------------------------
#endif
