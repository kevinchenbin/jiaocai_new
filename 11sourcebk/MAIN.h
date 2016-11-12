//----------------------------------------------------------------------------
#ifndef MainH
#define MainH
//----------------------------------------------------------------------------
#include "RzGroupBar.hpp"
#include "RzPanel.hpp"
#include "RzSplit.hpp"
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "RzButton.hpp"
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include <Graphics.hpp>
#include <StdCtrls.hpp>


#include <OleCtrls.hpp>
#include "RzCommon.hpp"
#include <ActnList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include "RzAnimtr.hpp"
#include "RzStatus.hpp"
#include "Dog.h"
#include <DBGrids.hpp>
#include <Grids.hpp>

//----------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:
	TImage *imagels;
	TImage *imageui;
	TImage *imagecg;
	TImage *imagekc;
	TImage *imagepx;
	TImage *imagetj;
	TImage *imagewl;
	TActionList *ActionList;
	TAction *rlogin;
	TADOStoredProc *adosp;
	TAction *quit;
	TAction *StogeSet;
	TAction *retailPrint;
	TAction *Printtitle;
	TAction *SalePrint;
	TAction *caigouprint;
	TAction *orderPrint;
	TAction *peishong;
	TAction *OrderControl;
	TAction *StockControl;
	TAction *storagecontrol;
	TAction *SaleControl;
	TAction *RetailControl;
	TAction *PeiShongControl;
	TAction *B2BSet;
	TAction *logSearch;
	TAction *dbback;
	TAction *dbrestore;
	TAction *specialPassWord;
	TAction *DanHaoDisplay;
	TAction *retailclassPromotion;
	TAction *Retailbuy;
	TAction *MemberoneProduct;
	TAction *Memberjifen;
	TAction *SaleOneProduct;
	TAction *SaleAddPoint;
	TAction *SaleNowbackDot;
	TAction *SaleyearBackDot;
	TAction *ClientOrder;
	TAction *SampleStock;
	TAction *smartStock;
	TAction *samplestorage;
	TAction *Smartstorage;
	TAction *storageback;
	TAction *samplesale;
	TAction *smartSale;
	TAction *actionsale;
	TAction *saleback;
	TAction *samplebook;
	TAction *Posretail;
	TAction *retailBack;
	TAction *b2binterface;
	TAction *financestart;
	TAction *supplierduizhang;
	TAction *Supplierjiduanfexie;
	TAction *Supplierjieshuan;
	TAction *SupplierjieShuanSearch;
	TAction *ClientfinanceStart;
	TAction *ClientWanglaiduizhang;
	TAction *Clientjieduanfexie;
	TAction *ClientJieShuan;
	TAction *Dangrijieshuan;
	TAction *BreedManage;
	TAction *catalogMake;
	TAction *pressmanage;
	TAction *breedType;
	TAction *LocalManage;
	TAction *memberclass;
	TAction *StorageInfo;
	TAction *SupplierClass;
	TAction *ClientClass;
	TAction *xuyipandian;
	TAction *shikupandian;
	TAction *storageLocaladjust;
	TAction *onestorageNumberadjust;
	TAction *Storagealarm;
	TAction *OperatorManage;
	TAction *rolemanage;
	TAction *PowerSet;
	TAction *SupplierInfo;
	TAction *ClientInfo;
	TAction *salermanage;
	TAction *creditManage;
	TAction *MemberInfo;
	TAction *Memberchongzhi;
	TAction *MemberchongziSearch;
	TAction *StorageSearch;
	TAction *OrderSearch;
	TAction *stocksearch;
	TAction *rikusearch;
	TAction *salesearch;
	TAction *posretailsearch;
	TAction *storagechecksearch;
	TAction *peishongsearch;
	TAction *manual;
	TAction *systemupdate;
	TAction *about;
	TPopupMenu *PMsystem;
	TMenuItem *N117;
	TMenuItem *N119;
	TMenuItem *N120;
	TMenuItem *N121;
	TMenuItem *N122;
	TMenuItem *N123;
	TMenuItem *N124;
	TMenuItem *N125;
	TMenuItem *N126;
	TMenuItem *N127;
	TMenuItem *N128;
	TMenuItem *N129;
	TMenuItem *N130;
	TMenuItem *N131;
	TMenuItem *N132;
	TMenuItem *N133;
	TMenuItem *B2B1;
	TMenuItem *N134;
	TMenuItem *N135;
	TMenuItem *N136;
	TMenuItem *N137;
	TMenuItem *N138;
	TMenuItem *N139;
	TPopupMenu *PMbusiness;
	TMenuItem *N162;
	TMenuItem *N163;
	TMenuItem *N164;
	TMenuItem *N166;
	TMenuItem *N170;
	TMenuItem *N172;
	TMenuItem *B2B2;
	TImage *imagehead;
	TImage *imageyx;
	TImage *imagesearch;
	TImage *imagecf;
	TPopupMenu *PMbasicData;
	TPopupMenu *PMpower;
	TPopupMenu *PMcatalog;
	TPopupMenu *PMfile;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *N11;
	TMenuItem *N12;
	TMenuItem *N13;
	TMenuItem *N14;
	TMenuItem *N15;
	TMenuItem *N16;
	TPopupMenu *PMwlclient;
	TPopupMenu *PMmember;
	TPopupMenu *PMhelp;
	TMenuItem *N17;
	TMenuItem *N18;
	TMenuItem *N19;
	TMenuItem *N20;
	TMenuItem *N21;
	TMenuItem *N22;
	TMenuItem *N23;
	TMenuItem *N24;
	TMenuItem *N25;
	TLabel *Label1;
	TLabel *Label2;
	TSpeedButton *sbfile;
	TRzMenuController *RzMenuController1;
	TSpeedButton *spsystem;
	TSpeedButton *spbasic;
	TSpeedButton *sbpower;
	TSpeedButton *sbcatalog;
	TSpeedButton *sbclient;
	TSpeedButton *sbmember;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TImage *imagesft;
	TImage *imagext;
	TSpeedButton *sbleftmenu;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SpeedButton5;
	TSpeedButton *SpeedButton6;
	TSpeedButton *SpeedButton7;
	TSpeedButton *SpeedButton8;
	TSpeedButton *SpeedButton9;
	TSpeedButton *SpeedButton10;
	TSpeedButton *SpeedButton11;
	TSpeedButton *SpeedButton12;
	TSpeedButton *SpeedButton13;
	TAction *yihutotal;
	TAction *yingfudetail;
	TAction *yingshouhuizhong;
	TAction *yingshoudetail;
	TAction *Clientjieshuansearch;
	TAction *jiaojieban;
	TAction *netorder;
	TAction *retailandback;
	TAction *saleandback;
	TAction *jingxiaochunfenxie;
	TAction *weidongkuchun;
	TAction *retailhuizhongfengxie;
	TAction *yefupaihangbang;
	TAction *changxiaobook;
	TAction *saletimehuizhong;
	TAction *saletongjireport;
	TAction *renwu;
	TAction *wengdang;
	TAction *jiaoliu;
	TImageList *ImageList1;
	TLabel *lbuser;
	TLabel *lbdate;
	TLabel *msg1;
	TLabel *msg2;
	TLabel *msg3;
	TLabel *msg4;
	TRzGlyphStatus *g1;
	TRzGlyphStatus *g2;
	TRzGlyphStatus *g3;
	TRzGlyphStatus *g4;
	TTimer *GetMessage;
	TMenuItem *jj1;
	TAction *peisong;
	TAction *MyWork;
	TAction *Clientbijiao;
	TAction *Supplierbijiao;
	TAction *tongjibaobiao;
	TAction *FormView;
	TMenuItem *N31;
	TMenuItem *N32;
	TAction *dangrijz;
	TAction *Jxcbijiao;
	TAction *wangshangOrder;
	TAction *catalogneworrec;
	TMenuItem *N35;
	TAction *Ordershenhei;
	TAction *CaigouOrder;
	TAction *bookfenfa;
	TAction *fahuorate;
	TAction *daohuorate;
	TAction *ZuliClass;
	TAction *caigoutixing;
	TAction *ordertixing;
	TMenuItem *N38;
	TAction *Orderaskbook;
	TAction *siglebook;
	TAction *siglebookfenfa;
	TAction *saletongqi;
	TAction *rukutongqi;
	TTimer *Timer1;
	TAction *qikanguanli;
	TMenuItem *N43;
	TAction *StorToStor;
	TMenuItem *N44;
	TMenuItem *N45;
	TMenuItem *N46;
	TMenuItem *N47;
	TMenuItem *N39;
	TMenuItem *N48;
	TMenuItem *N49;
	TMenuItem *N50;
	TMenuItem *N51;
	TMenuItem *N36;
	TMenuItem *N52;
	TMenuItem *N53;
	TMenuItem *N54;
	TMenuItem *N37;
	TMenuItem *N41;
	TMenuItem *N55;
	TMenuItem *N56;
	TMenuItem *N57;
	TMenuItem *N58;
	TMenuItem *N59;
	TMenuItem *N60;
	TMenuItem *POS1;
	TMenuItem *N61;
	TMenuItem *N62;
	TMenuItem *N26;
	TMenuItem *N27;
	TMenuItem *N28;
	TMenuItem *N29;
	TMenuItem *N30;
	TMenuItem *N33;
	TMenuItem *N34;
	TMenuItem *N40;
	TMenuItem *N42;
	TMenuItem *N63;
	TMenuItem *N64;
	TAction *Setyjdiscount;
	TMenuItem *N65;
	TAction *Memberadddot;
	TMenuItem *N66;
	TPopupMenu *pmpeishong;
	TMenuItem *N67;
	TMenuItem *N68;
	TMenuItem *N70;
	TAction *StockAlarmControl;
	TMenuItem *N69;
	TTimer *Timer2;
	TPopupMenu *pmstockalarm;
	TMenuItem *MenuItem1;
	TMenuItem *MenuItem2;
	TMenuItem *MenuItem3;
	TMenuItem *N71;
	TMenuItem *N72;
	TAction *Mutibook;
	TMenuItem *N73;
	TMenuItem *N74;
	TLabel *stgname;
	TDataSource *dsmsg;
	TADOQuery *aqmsg;
	TDBGrid *dgmsg;
	TAction *tongjiyewu;
	TMenuItem *N75;
	TMenuItem *N76;
	TAction *ImpOrder;
	TMenuItem *N77;
	TAction *Clientadddot;
	TMenuItem *N78;
	TAction *calculatstock;
	TMenuItem *N79;
	TMenuItem *N80;
	TAction *SupplierMerge;
	TAction *Cbprice;
	TMenuItem *N81;
	TMenuItem *N82;
	TAction *OrderLocalconfig;
	TMenuItem *N83;
	TMenuItem *N84;
	TMenuItem *N85;
	TMenuItem *N86;
	TMenuItem *N87;
	TMenuItem *N88;
	TPopupMenu *popmorder;
	TMenuItem *B1;
	TMenuItem *C1;
	TMenuItem *N89;
	TMenuItem *C2;
	void __fastcall FileExit1Execute(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall POS1Click(TObject *Sender);
	void __fastcall N26Click(TObject *Sender);
	void __fastcall N42Click(TObject *Sender);
	void __fastcall N47Click(TObject *Sender);
	void __fastcall N58Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall N60Click(TObject *Sender);
	void __fastcall mniN48Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall N71Click(TObject *Sender);
	void __fastcall N73Click(TObject *Sender);
	void __fastcall N74Click(TObject *Sender);
	void __fastcall N44Click(TObject *Sender);
	void __fastcall imagelsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall imageuiClick(TObject *Sender);
	void __fastcall i(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall imagekcMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall imagepxMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall imagetjMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall imagewlMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall imageuiMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall N89Click(TObject *Sender);
	void __fastcall N90Click(TObject *Sender);
	void __fastcall N92Click(TObject *Sender);
	void __fastcall N93Click(TObject *Sender);
	void __fastcall N94Click(TObject *Sender);
	void __fastcall N95Click(TObject *Sender);
	void __fastcall N96Click(TObject *Sender);
	void __fastcall N99Click(TObject *Sender);
	void __fastcall N105Click(TObject *Sender);
	void __fastcall N108Click(TObject *Sender);
	void __fastcall N109Click(TObject *Sender);
	void __fastcall N112Click(TObject *Sender);
	void __fastcall N110Click(TObject *Sender);
	void __fastcall N114Click(TObject *Sender);
	void __fastcall N115Click(TObject *Sender);
	void __fastcall N116Click(TObject *Sender);
	void __fastcall rloginExecute(TObject *Sender);
	void __fastcall quitExecute(TObject *Sender);
	void __fastcall StogeSetExecute(TObject *Sender);
	void __fastcall retailclassPromotionExecute(TObject *Sender);
	void __fastcall RetailbuyExecute(TObject *Sender);
	void __fastcall MemberoneProductExecute(TObject *Sender);
	void __fastcall MemberjifenExecute(TObject *Sender);
	void __fastcall SaleOneProductExecute(TObject *Sender);
	void __fastcall SaleAddPointExecute(TObject *Sender);
	void __fastcall SaleNowbackDotExecute(TObject *Sender);
	void __fastcall SaleyearBackDotExecute(TObject *Sender);
	void __fastcall ClientOrderExecute(TObject *Sender);
	void __fastcall SampleStockExecute(TObject *Sender);
	void __fastcall smartStockExecute(TObject *Sender);
	void __fastcall samplestorageExecute(TObject *Sender);
	void __fastcall storagebackExecute(TObject *Sender);
	void __fastcall samplesaleExecute(TObject *Sender);
	void __fastcall smartSaleExecute(TObject *Sender);
	void __fastcall actionsaleExecute(TObject *Sender);
	void __fastcall salebackExecute(TObject *Sender);
	void __fastcall samplebookExecute(TObject *Sender);
	void __fastcall PosretailExecute(TObject *Sender);
	void __fastcall retailBackExecute(TObject *Sender);
	void __fastcall b2binterfaceExecute(TObject *Sender);
	void __fastcall financestartExecute(TObject *Sender);
	void __fastcall supplierduizhangExecute(TObject *Sender);
	void __fastcall SupplierjiduanfexieExecute(TObject *Sender);
	void __fastcall SupplierjieshuanExecute(TObject *Sender);
	void __fastcall SupplierjieShuanSearchExecute(TObject *Sender);
	void __fastcall ClientfinanceStartExecute(TObject *Sender);
	void __fastcall ClientWanglaiduizhangExecute(TObject *Sender);
	void __fastcall ClientjieduanfexieExecute(TObject *Sender);
	void __fastcall ClientJieShuanExecute(TObject *Sender);
	void __fastcall DangrijieshuanExecute(TObject *Sender);
	void __fastcall BreedManageExecute(TObject *Sender);
	void __fastcall catalogMakeExecute(TObject *Sender);
	void __fastcall pressmanageExecute(TObject *Sender);
	void __fastcall breedTypeExecute(TObject *Sender);
	void __fastcall LocalManageExecute(TObject *Sender);
	void __fastcall memberclassExecute(TObject *Sender);
	void __fastcall StorageInfoExecute(TObject *Sender);
	void __fastcall xuyipandianExecute(TObject *Sender);
	void __fastcall shikupandianExecute(TObject *Sender);
	void __fastcall storageLocaladjustExecute(TObject *Sender);
	void __fastcall onestorageNumberadjustExecute(TObject *Sender);
	void __fastcall StoragealarmExecute(TObject *Sender);
	void __fastcall OperatorManageExecute(TObject *Sender);
	void __fastcall rolemanageExecute(TObject *Sender);
	void __fastcall PowerSetExecute(TObject *Sender);
	void __fastcall SupplierInfoExecute(TObject *Sender);
	void __fastcall ClientInfoExecute(TObject *Sender);
	void __fastcall salermanageExecute(TObject *Sender);
	void __fastcall creditManageExecute(TObject *Sender);
	void __fastcall MemberInfoExecute(TObject *Sender);
	void __fastcall MemberchongzhiExecute(TObject *Sender);
	void __fastcall MemberchongziSearchExecute(TObject *Sender);
	void __fastcall StorageSearchExecute(TObject *Sender);
	void __fastcall OrderSearchExecute(TObject *Sender);
	void __fastcall stocksearchExecute(TObject *Sender);
	void __fastcall rikusearchExecute(TObject *Sender);
	void __fastcall salesearchExecute(TObject *Sender);
	void __fastcall posretailsearchExecute(TObject *Sender);
	void __fastcall storagechecksearchExecute(TObject *Sender);
	void __fastcall Image2Click(TObject *Sender);
	void __fastcall imageheadMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall imageheadMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall sbfileClick(TObject *Sender);
	void __fastcall sbleftmenuClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall imagecgMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall imagecfMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall yihutotalExecute(TObject *Sender);
	void __fastcall yingfudetailExecute(TObject *Sender);
	void __fastcall yingshouhuizhongExecute(TObject *Sender);
	void __fastcall yingshoudetailExecute(TObject *Sender);
	void __fastcall ClientjieshuansearchExecute(TObject *Sender);
	void __fastcall jiaojiebanExecute(TObject *Sender);
	void __fastcall imageyxMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall retailandbackExecute(TObject *Sender);
	void __fastcall saleandbackExecute(TObject *Sender);
	void __fastcall saletimehuizhongExecute(TObject *Sender);
	void __fastcall weidongkuchunExecute(TObject *Sender);
	void __fastcall yefupaihangbangExecute(TObject *Sender);
	void __fastcall saletongjireportExecute(TObject *Sender);
	void __fastcall jingxiaochunfenxieExecute(TObject *Sender);
	void __fastcall changxiaobookExecute(TObject *Sender);
	void __fastcall retailhuizhongfengxieExecute(TObject *Sender);
	void __fastcall imagesearchMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall imagextMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall renwuExecute(TObject *Sender);
	void __fastcall wengdangExecute(TObject *Sender);
	void __fastcall jiaoliuExecute(TObject *Sender);
	void __fastcall msg1Click(TObject *Sender);
	void __fastcall manualExecute(TObject *Sender);
	void __fastcall systemupdateExecute(TObject *Sender);
	void __fastcall aboutExecute(TObject *Sender);
	void __fastcall specialPassWordExecute(TObject *Sender);
	void __fastcall DanHaoDisplayExecute(TObject *Sender);
	void __fastcall B2BSetExecute(TObject *Sender);
	void __fastcall logSearchExecute(TObject *Sender);
	void __fastcall dbbackExecute(TObject *Sender);
	void __fastcall dbrestoreExecute(TObject *Sender);
	void __fastcall OrderControlExecute(TObject *Sender);
	void __fastcall StockControlExecute(TObject *Sender);
	void __fastcall storagecontrolExecute(TObject *Sender);
	void __fastcall SaleControlExecute(TObject *Sender);
	void __fastcall RetailControlExecute(TObject *Sender);
	void __fastcall PeiShongExecute(TObject *Sender);
	void __fastcall SupplierClassExecute(TObject *Sender);
	void __fastcall ClientClassExecute(TObject *Sender);
	void __fastcall SmartstorageExecute(TObject *Sender);
	void __fastcall peisongExecute(TObject *Sender);
	void __fastcall peishongsearchExecute(TObject *Sender);
	void __fastcall MyWorkExecute(TObject *Sender);
	void __fastcall ClientbijiaoExecute(TObject *Sender);
	void __fastcall SupplierbijiaoExecute(TObject *Sender);
	void __fastcall retailPrintExecute(TObject *Sender);
	void __fastcall tongjibaobiaoExecute(TObject *Sender);
	void __fastcall FormViewExecute(TObject *Sender);
	void __fastcall dangrijzExecute(TObject *Sender);
	void __fastcall JxcbijiaoExecute(TObject *Sender);
	void __fastcall wangshangOrderExecute(TObject *Sender);
	void __fastcall catalogneworrecExecute(TObject *Sender);
	void __fastcall OrdershenheiExecute(TObject *Sender);
	void __fastcall CaigouOrderExecute(TObject *Sender);
	void __fastcall bookfenfaExecute(TObject *Sender);
	void __fastcall fahuorateExecute(TObject *Sender);
	void __fastcall daohuorateExecute(TObject *Sender);
	void __fastcall imagesftMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall caigoutixingExecute(TObject *Sender);
	void __fastcall ordertixingExecute(TObject *Sender);
	void __fastcall OrderaskbookExecute(TObject *Sender);
	void __fastcall siglebookExecute(TObject *Sender);
	void __fastcall siglebookfenfaExecute(TObject *Sender);
	void __fastcall saletongqiExecute(TObject *Sender);
	void __fastcall rukutongqiExecute(TObject *Sender);
	void __fastcall qikanguanliExecute(TObject *Sender);
	void __fastcall StorToStorExecute(TObject *Sender);
	void __fastcall SetyjdiscountExecute(TObject *Sender);
	void __fastcall MemberadddotExecute(TObject *Sender);
	void __fastcall StockAlarmControlExecute(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall MenuItem3Click(TObject *Sender);
	void __fastcall MenuItem1Click(TObject *Sender);
	void __fastcall MutibookExecute(TObject *Sender);
	void __fastcall PrinttitleExecute(TObject *Sender);
	void __fastcall dgmsgCellClick(TColumn *Column);
	void __fastcall N28Click(TObject *Sender);
	void __fastcall tongjiyewuExecute(TObject *Sender);
	void __fastcall ZuliClassExecute(TObject *Sender);
	void __fastcall ImpOrderExecute(TObject *Sender);
	void __fastcall ClientadddotExecute(TObject *Sender);
	void __fastcall calculatstockExecute(TObject *Sender);
	void __fastcall SupplierMergeExecute(TObject *Sender);
	void __fastcall CbpriceExecute(TObject *Sender);
	void __fastcall OrderLocalconfigExecute(TObject *Sender);
	void __fastcall N84Click(TObject *Sender);
	void __fastcall N85Click(TObject *Sender);
	void __fastcall N87Click(TObject *Sender);
	void __fastcall N88Click(TObject *Sender);
	void __fastcall B1Click(TObject *Sender);
	void __fastcall C1Click(TObject *Sender);
	void __fastcall C2Click(TObject *Sender);




private:
	String Disc();
	int uix,uiy;
	void LoadPUI();
	TStringList *PanelList;
	void Display(AnsiString PUIName);
	void Disappear(AnsiString PUIName);
	TStringList *PowerList;
	void GetPowerList(int UserID);

	bool   load;
 /*	WideString   wact;
	BSTR   act;
	IAgentCtlCharacterExPtr   numan;
	TVariantInParam   talk,path; */
	void LoadMyWork(int UID);
	void LoadMyMessage();

	void __fastcall ImageClick(TObject   *Sender);

	AnsiString PUIName;
	TStringList *PMmenue;
	TStringList *MessageInfo;
	TStringList *MessagePic;
	//void __fastcall WndProc(TMessage &Msg);    //ΩÿªÒWM_NCHITTESTœ˚œ¢
public:
	virtual __fastcall TfrmMain(TComponent *Owner);
	String Discstr;
	void __fastcall ClientWndProc(TMessage&   Message);
	TFarProc NewClientWndProc;
	TFarProc OriginalClientWndProc;
	BOOL CheckPower(String ModalName);
	void ShowNoPower();
	void StockAlert();
	void Time();
	int jiaojie;

};
/*
long ClientWndProc (HWND hwnd, ULONG msg, WPARAM  mp1, WPARAM  mp2);
long ClientWndProc (HWND hwnd, ULONG msg, WPARAM  mp1, WPARAM  mp2)
{


   switch (msg)
   {
   case WM_NCCALCSIZE:
   {
	   if ((GetWindowLong(hwnd,GWL_STYLE) && (WS_HSCROLL || WS_VSCROLL)) != 0) {
		 SetWindowLong(hwnd,GWL_STYLE,GetWindowLong(hwnd,GWL_STYLE) && !(WS_HSCROLL || WS_VSCROLL));
	   }
   }
	// return WinDefWindowProc (hwnd, msg, mp1, mp2);
	 return DefWindowProc( hwnd, msg, mp1, mp2 );
   }






}   */

//----------------------------------------------------------------------------
extern TfrmMain *frmMain;
//----------------------------------------------------------------------------
#endif    
