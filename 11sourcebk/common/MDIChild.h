//---------------------------------------------------------------------------

#ifndef MDIChildH
#define MDIChildH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include "pdtypes.h"
#include <DB.hpp>
//---------------------------------------------------------------------------

class TfrmMDIChild : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *qryUserAuthority;
	TADOQuery *aquerybs;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormDeactivate(TObject *Sender);
   //	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	bool m_allowOperate;//�Ƿ����������ģ��
	String m_oppwd;//��������
	void ReadAuthorityInfo();//��ȡȨ����Ϣ
protected:
	TApplication* m_app;
	TADOConnection* m_con;
	int m_userID;
	int m_storageID;
	ModuleType m_module;//ָʾ����һ��ģ
	String m_opName;//����Ա����
	bool CheckOperateAuthority();//��֤����Ȩ��
public:		// User declarations
	__fastcall TfrmMDIChild(TComponent* Owner);
	__fastcall ~TfrmMDIChild();
	virtual void Init(TApplication* app, TADOConnection* con);
	virtual void Init(LandInfo* li);
  //	virtual void OnHotKeyPress(DWORD vkCode);
  //	virtual void OnHotKeyPress(DWORD vkCode, bool ctrlpress);
	virtual void ShowMsg(AnsiString Texts,AnsiString Captions,int type);
   //	String TfrmMDIChild::

};

//---------------------------------------------------------------------------
extern PACKAGE TfrmMDIChild *frmMDIChild;
//---------------------------------------------------------------------------
#endif
