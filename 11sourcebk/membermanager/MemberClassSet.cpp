//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberClassSet.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmmemclassmg *frmmemclassmg;
//---------------------------------------------------------------------------
__fastcall Tfrmmemclassmg::Tfrmmemclassmg(TComponent* Owner,TADOConnection *cnn)
	: TForm(Owner)
{
	Root = tvMemberType->Items->Item[0];
	quMemberType->Connection = cnn;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmmemclassmg::FormShow(TObject *Sender)
{
	AnsiString sql;
	sql = "select IDType,Type as T,discount from cust_membertype order by discount desc ";
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	while(!quMemberType->Eof )
	{
	  AnsiString idtypename =  quMemberType->FieldByName("T")->AsAnsiString.Trim()  +  "(" + quMemberType->FieldByName("discount")->AsAnsiString + "%)";
	  tvMemberType->Items->AddChild(Root,idtypename);
	  quMemberType->Next();
	}
	tvMemberType->AutoExpand = true;
	edTypeName->Enabled = false;
	edTypeDiscount->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::BtnAddClick(TObject *Sender)
{
	savemodle = 1; //1为添加
	edTypeName->Text = "";
	edTypeName->Enabled = true;
	edTypeDiscount->Text = "100";
	edTypeDiscount->Enabled = true;
	edTypeName->SetFocus();
	BtnChangeOptions->Enabled = false;
	BtnSave->Enabled = true;
	AnsiString sql;
	sql = "select MAX(IDType) as IDType from CUST_MemberType";
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	int memberid = quMemberType->FieldByName("IDType")->AsInteger + 1;
	edMemberID->Text = IntToStr(memberid);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::BtnDeleteClick(TObject *Sender)
{
	if (tvMemberType->Selected->Level != 1){
		MessageBox(0,"请选择一条会员类型！","没有选择" ,MB_OK);
	}
	else
	{
        AnsiString idtypename =  tvMemberType->Selected->Text;
		idtypename = idtypename.SubString(0,idtypename.Pos("(")-1 );
		if (idtypename == "默认会员") {
			MessageBox(0,"默认会员不能删除！","系统提示" ,MB_OK);
			return;
		}
		AnsiString sql,sdf ;
		sql = "select * from CUST_MemberInfo where CUST_MemberInfo.MemberType = (select IDType from CUST_MemberType where Type = '" + idtypename + "')";
		quMemberType->Close();
		quMemberType->SQL->Clear();
		quMemberType->SQL->Add(sql);
		quMemberType->Open();
		if (!quMemberType->IsEmpty()) {
			MessageBox(0,"该会员类型的会员信息存在，不能删除该会员类型！","删除错误" ,MB_OK);
		}
		else
		{
			sql = "delete from CUST_MemberType where Type = '" + idtypename + "'";
			sdf = "确认删除会员类型："+Trim(tvMemberType->Selected->Text)+"吗？";
			if (MessageBox(0,sdf.c_str() ,"删除确认" ,MB_OKCANCEL)==1) {
				try {
					quMemberType->Close();
					quMemberType->SQL->Clear();
					quMemberType->SQL->Add(sql);
					quMemberType->ExecSQL();
					tvMemberType->Selected->Delete();
					edTypeName->Text = "";
					edTypeDiscount->Text = "";
				} catch (Exception &E) {
					MessageBox(0,"该数据跟系统其他数据有关联，不能删除！","删除错误" ,MB_OK);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::tvMemberTypeClick(TObject *Sender)
{
	AnsiString sql;
	BtnAdd->Enabled = true;
	BtnChangeOptions->Enabled = true;
	BtnSave->Enabled = false;
	edTypeName->Enabled = false;
	edTypeDiscount->Enabled = false;
	AnsiString idtypename =  tvMemberType->Selected->Text;
	idtypename = idtypename.SubString(0,idtypename.Pos("(")-1 );
	sql = "select * from CUST_MemberType where Type = '" + idtypename + "'";
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	if (tvMemberType->Selected->Level == 1) {
		edTypeDiscount->Text =  quMemberType->FieldByName("Discount")->AsString;
		edMemberID->Text = quMemberType->FieldByName("IDType")->AsString ;
		edTypeName->Text = idtypename;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::BtnChangeOptionsClick(TObject *Sender)
{
	BtnAdd->Enabled = false;
	BtnSave->Enabled = true;
	if (savemodle == 1 && edTypeName->Enabled) {
		MessageBox(0,"现在为添加状态，不能修改！","修改错误" ,MB_OK);
	}
	else
	{
		edTypeName->Enabled = true;
		edTypeDiscount->Enabled = true;
	}
	savemodle = 2; //2为修改
	edTypeName->SetFocus();
	if (tvMemberType->Selected->Level != 1){
		MessageBox(0,"请选择一条会员类型！","没有选择" ,MB_OK);
	}
	else
	{
		AnsiString idtypename =  tvMemberType->Selected->Text;
		idtypename = idtypename.SubString(0,idtypename.Pos("(")-1 );
		if (idtypename == "默认会员") {
			edTypeName->Enabled = false;
            edTypeDiscount->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::edTypeDiscountClick(TObject *Sender)
{
	AnsiString IDiscount = edTypeDiscount->Text;
	int len = IDiscount.Pos("%")-1;
	if (IDiscount.Pos("%")!= 0 ) {
    	IDiscount = IDiscount.SubString(0,len);
	}
	edTypeDiscount->Text = IDiscount;
}
//---------------------------------------------------------------------------

//添加保存函数
void __fastcall Tfrmmemclassmg::Addsave()
{
	AnsiString sql,sdf,IDiscount = edTypeDiscount->Text;
	int len = IDiscount.Pos("%")-1 ;
	if (IDiscount.Pos("%")!=0 ) {
		IDiscount =  IDiscount.SubString(0,len);
	}
	sql = "select * from CUST_MemberType where Type = '" + edTypeName->Text + "'" ;
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	if (edTypeName->Text == "") {
		MessageBox(0,"类型名称不能为空！","错误确认" ,MB_OK);
	}
	else
	{
		if (edTypeDiscount->Text == "") {
			MessageBox(0,"折扣不能为空！","错误确认" ,MB_OK);
		}
		else
		{
			if (!quMemberType->IsEmpty() ) {
				MessageBox(0,"该会员类型已添加！","错误确认" ,MB_OK);
			}
			else
			{
				sdf =  "确认添加会员类型："+edTypeName->Text+"吗？";
				if (MessageBox(0,sdf.c_str() ,"添加确认" ,MB_OKCANCEL)==1) {
					if (quMemberType->State != dsInsert) {
						quMemberType->Append();
					}
					if (quMemberType->State == dsInsert) {
						quMemberType->FieldByName("Type")->AsString = edTypeName->Text;
						quMemberType->FieldByName("Discount")->AsFloat = StrToFloat(IDiscount);
						quMemberType->Post();
						AnsiString addname = edTypeName->Text.Trim() + "(" + edTypeDiscount->Text.Trim() + "%)";
						tvMemberType->Items->AddChild(Root,addname);
						edTypeName->Enabled = false;
						edTypeDiscount->Enabled = false;
						BtnAdd->Enabled = true;
						BtnChangeOptions->Enabled = true;
						BtnSave->Enabled = false;
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

//修改保存函数
void __fastcall Tfrmmemclassmg::Changesave()
{
	savemodle = 2; //2为修改
	edTypeName->Enabled = true;
	edTypeDiscount->Enabled = true;
	AnsiString IDiscount = edTypeDiscount->Text;
	int len = IDiscount.Pos("%")-1 ;
	if (IDiscount.Pos("%")!=0 ) {
		IDiscount =  IDiscount.SubString(0,len);
	}
	if (tvMemberType->Selected->Level != 1){
		MessageBox(0,"请选择一条会员类型！","没有选择" ,MB_OK);
	}
	else
	{
		AnsiString sql,sdf ;
		AnsiString idtypename =  tvMemberType->Selected->Text.Trim() ;
		idtypename = idtypename.SubString(0,idtypename.Pos("(")-1 );
		/*sql = "select * from CUST_MemberInfo where CUST_MemberInfo.MemberType = (select IDType from CUST_MemberType where Type = '" + idtypename + "')";
		quMemberType->Close();
		quMemberType->SQL->Clear();
		quMemberType->SQL->Add(sql);
		quMemberType->Open();
		if (!quMemberType->IsEmpty()) {
			MessageBox(0,"该会员类型的会员信息存在，不能修改该会员类型！","修改错误" ,MB_OK);
		}
		else
		{ */
			sql = "update CUST_MemberType set Type = '" + Trim(edTypeName->Text)+"',Discount = " +IDiscount+"where Type = '" + idtypename + "'";
			sdf = "确认修改会员类型："+idtypename+"吗？";
			if (MessageBox(0,sdf.c_str() ,"修改确认" ,MB_OKCANCEL)==1) {
				try {
					quMemberType->Close();
					quMemberType->SQL->Clear();
					quMemberType->SQL->Add(sql);
					quMemberType->ExecSQL();
					AnsiString addname = edTypeName->Text.Trim() + "(" + edTypeDiscount->Text.Trim() + "%)";
					tvMemberType->Selected->Text = addname;
					edTypeName->Enabled = false;
					edTypeDiscount->Enabled = false;
					BtnAdd->Enabled = true;
					BtnChangeOptions->Enabled = true;
					BtnSave->Enabled = false;
				} catch (Exception &E) {
					MessageBox(0,"该数据跟系统其他数据有关联，不能修改！","修改错误" ,MB_OK);
				}
			}
		//}
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmmemclassmg::BtnSaveClick(TObject *Sender)
{
    if (edTypeName->Text == "") {
		MessageBox(0,"会员类型名称不能为空！","错误提示" ,MB_OK);
		return;
	}
	if (edTypeDiscount->Text == "") {
		MessageBox(0,"会员类型折扣不能为空！","错误提示" ,MB_OK);
		return;
	}
	int discount;
	discount = StrToInt(edTypeDiscount->Text.Trim() );
	if (discount > 100) {
    	MessageBox(0,"会员类型折扣不能大于100！","错误提示" ,MB_OK);
		return;
	}
	if (savemodle == 1) {
		Addsave();
	}
	else if (savemodle == 2) {
		Changesave();
	}
	else
	{}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::edTypeNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		//BtnSave->Click();
		edTypeDiscount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::edTypeDiscountKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if (Key == VK_RETURN) {
    	BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {
		 BtnAdd->Click();
	   }
		if (Key == VK_F3) {
		 BtnChangeOptions->Click();
	   }

		if (Key == VK_F4) {
		 BtnSave->Click();
	   }
		if (Key == VK_F5) {
		 BtnDelete->Click();
	   }
		if (Shift.Contains(ssCtrl)&& Key ==81  ) {
			BtnExit->Click();
		}

}
//---------------------------------------------------------------------------

