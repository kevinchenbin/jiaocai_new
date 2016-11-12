//---------------------------------------------------------------------------

#ifndef bsprintH
#define bsprintH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RpCon.hpp"
#include "RpConBDE.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RpBase.hpp"
#include "RpSystem.hpp"
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include "frxCross.hpp"
#include "frxRich.hpp"
#include "frxBarcode.hpp"
//---------------------------------------------------------------------------
struct PrintControl
{
   AnsiString name;
   float width;
};
class Tfrmwsaleprinta : public TForm
{
__published:	// IDE-managed Components
	TRvProject *wholesale;
	TADOQuery *aqHeader;
	TRvDataSetConnection *RvDataSetConnection1;
	TADOQuery *aqdetail;
	TRvDataSetConnection *RvDataSetConnection2;
	TADOQuery *aqtotalnum;
	TRvDataSetConnection *RvDataSetConnection3;
	TRvSystem *RvSystem1;
	TRvDataSetConnection *rvstorage1;
	TRvDataSetConnection *rvstorage2;
	TADOQuery *aqrvstoragedetail;
	TADOQuery *aqhead;
	TADOQuery *aqorderhead;
	TADOQuery *aqorderdetail;
	TRvDataSetConnection *rvorderdetail;
	TRvDataSetConnection *rvorderhead;
	TADOQuery *aqProcureHeader;
	TADOQuery *aqProcureDetail;
	TRvDataSetConnection *rvProcureDetail;
	TRvDataSetConnection *rvProcureHead;
	TRvDataSetConnection *rvstoragechashu;
	TADOQuery *aqstoragechashu;
	TADOConnection *fcon;
	TfrxReport *frxProcure;
	TfrxDBDataset *frxdbprohead;
	TfrxDBDataset *frxdbprodetail;
	TfrxDBDataset *frxDBwsalehead;
	TfrxCrossObject *frxCrossObject1;
	TfrxRichObject *frxRichObject1;
	TfrxReport *frxOrder;
	TfrxDBDataset *frxDBorddetail;
	TfrxDBDataset *frxDBordhead;
	TfrxReport *frxstorage;
	TfrxDBDataset *frxDBstohead;
	TfrxDBDataset *frxDBstodetail;
	TfrxBarCodeObject *frxBarCodeObject1;
	TfrxReport *frxWsale;
	TfrxReport *frxretail;
	TfrxReport *frxReport1;
	TfrxReport *frxWsalemuilprint;
	TADOQuery *queryA5;
	TADOQuery *queryA4;
	TfrxReport *frxReportA5;
	TADOQuery *aqmuildetail;
	TADOQuery *aqmuilprinthead;
	TfrxDBDataset *frxmutildetail;
	TfrxDBDataset *frxdbwsalemuilprint;
	TADOQuery *adoqueryjianhuo;
	TfrxReport *frxreportjianhuo;
	TfrxDBDataset *frxDBDatasetjianhuo;
	TfrxDBDataset *frxDBDatasetmiandan;
	TADOQuery *adomiandan;
	TfrxDBDataset *frxDBDatasetxiaopiao;
	TADOQuery *adoxiaopiao;
	void __fastcall frxProcureGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall frxWsaleBeforePrint(TfrxReportComponent *Sender);
	void __fastcall frxWsaleGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall frxOrderGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall frxstorageGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall frxWsalemuilprintGetValue(const UnicodeString VarName, Variant &Value);


private:	// User declarations
public:		// User declarations
	__fastcall Tfrmwsaleprinta(TComponent* Owner,TADOConnection *cn);
	TStringList * PrintTile;
	void InputPara(AnsiString ID,int mode);
	void previewprint(int type , int simple);
	void PrintStorage(int ID);
	void PrintStoragechashu(int ID);
	void PrintStorageExe(int type);
	void PrintStorageExe();
	int PrintType,printmodle,tuihuo;
	bool DanhaoChange,mayang;
	float yingshou,fandian;
	String Maker,num;
	AnsiString pxbk,rkbk,ClientName,supplycode,printtitle,contact,tel,address,shaddress,shtel,shcontact;
	int stgid,ordertype;
	AnsiString Touppnum(AnsiString ychar);
	AnsiString Doubletostring(double num);
	AnsiString FindTitleName(AnsiString ColumnName);
	float FindTitlewith(AnsiString ColumnName);
	void wsalemuilPrint(AnsiString ID,int type,bool xiaopiao);
		bool booltuihuo;
		 bool pixiaoortuihuo;
	void jianhuodanprint(AnsiString ID,boolean isprint);
	void miandanprint(AnsiString ID,boolean isprint);
	void xiaopiaoliandaprint(AnsiString ID,boolean isprint);
	void miandanprintA5(AnsiString ID,boolean isprint);
};

//---------------------------------------------------------------------------
extern PACKAGE Tfrmwsaleprinta *frmwsaleprinta;
#endif
