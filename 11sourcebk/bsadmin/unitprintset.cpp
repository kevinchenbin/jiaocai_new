//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unitprintset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "frxClass"
#pragma link "frxCross"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
Tfrmprintset *frmprintset;
//---------------------------------------------------------------------------
__fastcall Tfrmprintset::Tfrmprintset(TComponent* Owner,TADOConnection *con,int modle,int stgid)
	: TForm(Owner)
{
	fmodle = modle;
	fstgid = stgid;
	Root = tvfangan->Items->Item[0];
	fcon = con;
	query->Connection = con;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	aqdetail->Connection = con;
	aqHeader->Connection = con;
	AnsiString sql;
	sql = "select * from sys_printhead where modle = " + IntToStr(modle) + " and active = 1 and stgid = " + IntToStr(fstgid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	int activetype = aq->FieldByName("id")->AsInteger ;
	eddefault->Text =  aq->FieldByName("typename")->AsAnsiString ;
	sql = "select * from sys_printhead where modle = " + IntToStr(modle) + " and stgid = " + IntToStr(fstgid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		tvfangan->Items->AddChild(Root,aq->FieldByName("typename")->AsAnsiString);
		aq->Next();
	}
	sql = "select * from sys_printdetail where headid = " + IntToStr(activetype) + " order by id asc ";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	sql = "select wsprinttitle,wscontact,wstel,wsaddress,wsprintbk from sys_printtitle where stgid = " + IntToStr(fstgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	pxbk = aq->FieldByName("wsprintbk")->AsAnsiString ;
	printtitle = aq->FieldByName("wsprinttitle")->AsAnsiString ;
	contact = aq->FieldByName("wscontact")->AsAnsiString ;
	tel = aq->FieldByName("wstel")->AsAnsiString ;
	address = aq->FieldByName("wsaddress")->AsAnsiString ;

	sql = "select 1 as xuhao,1 as ID,'23458' AS incode,'9787030265791' as ISBN,'家装新世纪—儿童房.书房' as CatalogName,'科学出版社' as AbbreviatedName,20 as Price,'筑龙网' as Author,'JZXSJETFSF' as UserDefCode,50 as Amount ,100 as Discount,1000 as FixedPrice,1000 as  DiscountedPrice,'2010-09' as Pressdate,'第一版' as PressCount,10 as BookWords, "
			" '室内设计规划教材' as huojiangstate,'本校' as xiaoqu,'建筑学院' as xueyuan,'室内装修' as course,1 as printbag,'默认库位' AS BkstackName ";
	aqdetail->Close();
	aqdetail->SQL->Clear();
	aqdetail->SQL->Add(sql);
	aqdetail->Open();

	sql = "delete from SYS_Printhead where typename is null or typename = '';delete from sys_Printdetail where headid not in(select id from SYS_Printhead)";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();

	sql = "select * from sys_PrintReort where mode = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbreport->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger);
		aq->Next();
	}

	delete aq;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmprintset::BtnNewClick(TObject *Sender)
{
	edname->Enabled = true;
	edname->Text = "";
	edname->SetFocus();

    AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;

	sql = "insert into sys_printhead(modle,type,active,stgid,reportname) "
	" select modle,type,0,stgid,reportname from sys_printhead where active = 1 and stgid = " + IntToStr(fstgid) ;
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = "select max(id) as id from sys_printhead where modle = " + IntToStr(fmodle) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	int newid = aq->FieldByName("id")->AsInteger ;
	sql = "insert into sys_printdetail(headid,[name],[print],[with],columnname) select " + IntToStr(newid) + ",[name],0,[with],columnname from sys_printdetail where headid in (select id from sys_printhead where modle = " + IntToStr(fmodle) + " and active = 1" + " and stgid = " + IntToStr(fstgid) + ")";
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = "select * from sys_printdetail where headid = " + IntToStr(newid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	delete aq;
	DBGridEh1->Enabled = true;
	modle = 1;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmprintset::BtnSelectAllClick(TObject *Sender)
{
	if (tvfangan->Selected == NULL || tvfangan->Selected->Parent == NULL) {
		return;
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "update sys_printhead set active = 1 where typename = '" + tvfangan->Selected->Text + "' and modle = " + IntToStr(fmodle) + " and stgid = " + IntToStr(fstgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = "update sys_printhead set active = 0 where typename <> '" + tvfangan->Selected->Text + "' and modle = " + IntToStr(fmodle) + " and stgid = " + IntToStr(fstgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	eddefault->Text = tvfangan->Selected->Text;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmprintset::BtnSaveClick(TObject *Sender)
{
	if (modle == 1) {    //新增
		if (edname->Text.Trim() == "" ) {
        	MessageBoxA(0,"请输入方案名！","提示",MB_ICONINFORMATION);
			return;
		}
		AnsiString sql;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		sql = "select * from sys_printhead where typename = '" + edname->Text + "' and modle = " + IntToStr(fmodle) + " and stgid = " + IntToStr(fstgid) ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (!aq->IsEmpty() ) {
			MessageBoxA(0,"该方案名已存在，请另输入方案名！","提示",MB_ICONINFORMATION);
			delete aq;
			return;
		}
		sql = "update sys_printhead set typename = '" + edname->Text.Trim() + "' where id = " + query->FieldByName("headid")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
    	query->UpdateBatch(arAll);
		DBGridEh1->Enabled = false;
		tvfangan->Items->AddChild(Root,edname->Text.Trim());
		edname->Text = "";
		edname->Enabled = false;
	}
	else if (modle == 2) {       //修改
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		AnsiString sql = "update sys_printhead set reportname = '" + cbreport->Text.Trim() + "' where id = " + query->FieldByName("headid")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
		query->UpdateBatch(arAll);
		DBGridEh1->Enabled = false;
	}
	modle = 0;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprintset::tvfanganClick(TObject *Sender)
{
	if (tvfangan->Selected->Parent == NULL) {
		return;
	}
	AnsiString sql;
	sql = "select sys_printdetail.* from sys_printdetail join sys_printhead on sys_printdetail.headid = sys_printhead.id where sys_printhead.modle = " + IntToStr(fmodle) + " and sys_printhead.stgid = " + IntToStr(fstgid) + " and sys_printhead.typename = '" + tvfangan->Selected->Text.Trim()  + "' order by id asc ";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	DBGridEh1->Enabled = false;
	edname->Enabled = false;
	modle = 0;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprintset::BtnClearClick(TObject *Sender)
{
	if (tvfangan->Selected == NULL || tvfangan->Selected->Parent == NULL) {
		return;
	}
	DBGridEh1->Enabled = true;
	modle = 2;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprintset::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprintset::BtnDeleteClick(TObject *Sender)
{
    if (tvfangan->Selected == NULL || tvfangan->Selected->Parent == NULL) {
		return;
	}
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = "select * from sys_printhead where typename = '" + tvfangan->Selected->Text.Trim()  + "' and modle = " + IntToStr(fmodle) + " and stgid = " + IntToStr(fstgid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->FieldByName("active")->AsBoolean ) {
    	MessageBoxA(0,"该方案为默认方案，请先设置其他方案为默认方案后在删除此方案！","提示",MB_ICONINFORMATION);
		return;
	}
	int hdid = aq->FieldByName("id")->AsInteger ;
	sql = "delete from sys_printhead where id = " + IntToStr(hdid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = "delete from sys_Printdetail where headid = " + IntToStr(hdid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	tvfangan->Selected->Delete();
	DBGridEh1->Enabled = false;
	edname->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprintset::BtnPrintPreviewClick(TObject *Sender)
{
	if (tvfangan->Selected == NULL || tvfangan->Selected->Parent == NULL) {
		return;
	}
	struct PrintControl1 *item;
	PrintTile = new TStringList(NULL);

	TADOQuery *aptitle = new TADOQuery(NULL);
	aptitle->Connection = fcon ;
	aptitle->Close();
	aptitle->SQL->Clear();
	AnsiString sql;
	sql = "select reportname from SYS_Printhead where modle = " + IntToStr(fmodle) + " and sys_printhead.stgid = " + IntToStr(fstgid) + " and sys_printhead.typename = '" + tvfangan->Selected->Text.Trim() + "'";
    aptitle->Close();
	aptitle->SQL->Clear();
	aptitle->SQL->Add(sql);
	aptitle->Open();
	ps = aptitle->FieldByName("reportname")->AsAnsiString.Trim() + ".fr3"  ;
	sql = "select sys_printdetail.* from sys_printdetail join sys_printhead on sys_printdetail.headid = sys_printhead.id where sys_printdetail.[print] = 1 and sys_printhead.modle = " + IntToStr(fmodle) + " and sys_printhead.stgid = " + IntToStr(fstgid) + " and sys_printhead.typename = '" + tvfangan->Selected->Text.Trim()  + "' order by id asc ";
	aptitle->Close();
	aptitle->SQL->Clear();
	aptitle->SQL->Add(sql);
	aptitle->Open();
	while(!aptitle->Eof)
	{
		item = new PrintControl1();
		item->name = aptitle->FieldByName("name")->AsAnsiString ;
		item->width = aptitle->FieldByName("with")->AsFloat ;
		PrintTile->AddObject(aptitle->FieldByName("columnname")->AsAnsiString ,(TObject*)item);
		aptitle->Next();
	}
	delete aptitle;

	ps = ExtractFilePath(Application->ExeName)+ ps ;
	frxWsale->LoadFromFile(ps);
	frxWsale->PrepareReport(true);
	frxWsale->ShowPreparedReport();
	//frxWsale->Free();
	frxWsale->Clear();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprintset::frxWsaleBeforePrint(TfrxReportComponent *Sender)
{
	TfrxCrossView * Cross;
	int i, j;
	Variant Row,Col,Text;
	AnsiString titlename,sql;
	int totalamount = 0;
	float shiyang = 0.00,mayang = 0.00;
	Cross = dynamic_cast <TfrxCrossView *> (Sender);
	AnsiString tojiTitle[3];

	if(Cross != NULL)
	{
        Cross->Left = 0.5;
		aqdetail->First();
		i = 0;
		while (!aqdetail->Eof)
		{
			for(j = 0; j < aqdetail->Fields->Count; j++)
			{
				Row = i;
				titlename = FindTitleName(aqdetail->Fields->Fields[j]->DisplayLabel);
				if (titlename != "NOTITLE") {
					Col = titlename ;

				if (CompareText(titlename,"码洋")==0){
					Text =   FormatFloat("0.00",aqdetail->Fields->Fields[j]->AsFloat);
					tojiTitle[0]="码洋";
					mayang = mayang + aqdetail->Fields->Fields[j]->AsFloat;

				}else if ((CompareText(titlename,"实洋")==0)) {
						Text =   FormatFloat("0.00",aqdetail->Fields->Fields[j]->AsFloat);
						tojiTitle[1]="实洋";
						shiyang = shiyang + aqdetail->Fields->Fields[j]->AsFloat;
					  }
				else if (CompareText(titlename,"定价")==0) {
						Text =   FormatFloat("0.00",aqdetail->Fields->Fields[j]->AsFloat);
					 }
				else if ((CompareText(titlename,"数量")==0)) {
					   Text =   aqdetail->Fields->Fields[j]->AsAnsiString ;
					   tojiTitle[2]="数量";
					   totalamount = totalamount + aqdetail->Fields->Fields[j]->AsInteger ;
					 }
				else if((CompareText(titlename,"折扣")==0)) {
						Text =   FormatFloat("00%",aqdetail->Fields->Fields[j]->AsFloat);
				}
				else{
					Text = aqdetail->Fields->Fields[j]->AsAnsiString ;
				}

					Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);
				}
			}
			aqdetail->Next();
			i++;
		}
    	//合计
		Row = i;
		Col = "序号";
		Text = "合计";
		Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);
		for (int p = 0 ; p < 3; p++) {
			if (tojiTitle[p] != "") {
				Col = tojiTitle[p];
				if (Col == "数量") {
					Text = IntToStr(totalamount);
				}
				if (Col == "码洋") {
					Text = FormatFloat("0.00",mayang);
				}
				if (Col == "实洋") {
					Text = FormatFloat("0.00",shiyang);
				}
				Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprintset::frxWsaleGetValue(const UnicodeString VarName, Variant &Value)

{
	//传递宽度
	if (CompareText(VarName,"\"xuhao\"")==0  ) {  //序号
		 Value = FindTitlewith("xuhao");
	}
	if (CompareText(VarName,"\"incode\"")==0  ) {  //内部识别码
		 Value = FindTitlewith("incode");
	}
	if (CompareText(VarName,"\"ISBN\"")==0  ) {    //书号
		Value = FindTitlewith("ISBN");
	}
	if (CompareText(VarName,"\"CatalogName\"")==0 ) {   //书名
		Value = FindTitlewith("CatalogName");
	}
	if (CompareText(VarName,"\"Price\"")==0 ) {   //定价
		Value = FindTitlewith("Price");
	}
	if (CompareText(VarName,"\"Author\"")==0 ) {  //作者
		Value = FindTitlewith("Author");
	}
	if (CompareText(VarName,"\"UserDefCode\"")==0 ) {  //自编码
		Value = FindTitlewith("UserDefCode");
	}
	if (CompareText(VarName,"\"AbbreviatedName\"")==0 ) {    //出版社
		Value = FindTitlewith("AbbreviatedName");
	}
	if (CompareText(VarName,"\"Pressdate\"")==0 ) {   //出版日期
		Value = FindTitlewith("Pressdate");
	}
	if (CompareText(VarName,"\"PressCount\"")==0 ) {  //版次
		Value = FindTitlewith("PressCount");
	}
	if (CompareText(VarName,"\"BookWords\"")==0 ) {    //册/包
		Value = FindTitlewith("BookWords");
	}
	if (CompareText(VarName,"\"Amount\"")==0 ) {      //数量
		Value = FindTitlewith("Amount");
	}
	if (CompareText(VarName,"\"Discount\"")==0 ) {     //折扣
		Value = FindTitlewith("Discount");
	}
	if (CompareText(VarName,"\"FixedPrice\"")==0 ) {   //码洋
		Value = FindTitlewith("FixedPrice");
	}
	if (CompareText(VarName,"\"DiscountedPrice\"")==0 ) {        //实洋
		Value = FindTitlewith("DiscountedPrice");
	}
	if (CompareText(VarName,"\"huojiangstate\"")==0 ) {   //获奖情况
		Value = FindTitlewith("huojiangstate");
	}
	if (CompareText(VarName,"\"xiaoqu\"")==0 ) {   //校区
		Value = FindTitlewith("xiaoqu");
	}
	if (CompareText(VarName,"\"xueyuan\"")==0 ) {        //学院
		Value = FindTitlewith("xueyuan");
	}
	if (CompareText(VarName,"\"course\"")==0 ) {   //课程名称
		Value = FindTitlewith("course");
	}
	if (CompareText(VarName,"\"printbag\"")==0 ) {   //册/套
		Value = FindTitlewith("printbag");
	}
	if (CompareText(VarName,"\"BkstackName\"")==0 ) {   //库位
		Value = FindTitlewith("BkstackName");
	}

	//传递参数
	if (CompareText(VarName,"\"title\"")==0 ) {
		Value = printtitle + "发货单";
	}
	if (CompareText(VarName,"\"yingshou\"")==0 ) {
		Value = FormatFloat("￥0.00",1000);
	}
	if (CompareText(VarName,"\"fandian\"")==0 ) {
		Value = FormatFloat("￥0.00",0);
	}
	if (CompareText(VarName,"\"pxbk\"")==0 ) {
		Value = pxbk;
	}
	if (CompareText(VarName,"\"contact\"")==0 ) {
		Value = contact;
	}
	if (CompareText(VarName,"\"tel\"")==0 ) {
		Value = tel;
	}
	if (CompareText(VarName,"\"address\"")==0 ) {
		Value = address;
	}
	if (CompareText(VarName,"\"ClientName\"")==0 ) {
		Value = "普通客户";
	}
	if (CompareText(VarName,"\"heji\"")==0 ) {
		Value = "×仟×佰×拾×万壹仟零佰零拾零元零角零分";
	}
	if (CompareText(VarName,"\"Danhao\"")==0 ) {
		Value = "PX0000000001";
	}
}
//---------------------------------------------------------------------------
AnsiString Tfrmprintset::FindTitleName(AnsiString ColumnName)
{
	int i;
	i =  PrintTile->IndexOf(ColumnName);
	if (i != -1 ) {
		  return ((PrintControl1*)PrintTile->Objects[i])->name ;
	}else return "NOTITLE";
}
//---------------------------------------------------------------------------
float Tfrmprintset::FindTitlewith(AnsiString ColumnName)
{
	int i;
	i =  PrintTile->IndexOf(ColumnName);
	if (i != -1 ) {
		  return ((PrintControl1*)PrintTile->Objects[i])->width ;
	}else return 0;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprintset::FormClose(TObject *Sender, TCloseAction &Action)
{
    AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = "delete from SYS_Printhead where typename is null or typename = '';delete from sys_Printdetail where headid not in(select id from SYS_Printhead)";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}
//---------------------------------------------------------------------------

