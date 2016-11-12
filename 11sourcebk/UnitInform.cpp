//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitInform.h"
#include "bsadmin.h"
#include "pdtypes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzBHints"
#pragma link "RzListVw"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TfrmInform *frmInform;
//---------------------------------------------------------------------------
__fastcall TfrmInform::TfrmInform(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
	fcn = cn;
	aq->Connection = cn;
	adosp->Connection = cn;
}
String TfrmInform::GetFormNameAt(TPoint Pos)
{
 //TWinControl
   TWinControl * w;
   String WindowName;
   w = FindVCLWindow(Pos);
   if (w != NULL) {
	  while (w->Parent != NULL)
	  {
		w = w->Parent ;
	  }
	  WindowName = w->Name  ;

   }else
   {
	  WindowName = "";

   }
   return WindowName;
   /*
    //得到鼠标指针下的VCL可视组件
  w:= FindVclWindow(Pos);
  if (w <> nil) then
  begin
    //当W的上级Parent不为空时就继续往上找
    while w.Parent <> nil do
	  w:= w.Parent;
    //最后返回窗体的名称Name
    Result:= w.Name;
  end
  else
	Result:= '';
	 */
}
//---------------------------------------------------------------------------
void __fastcall TfrmInform::Timer1Timer(TObject *Sender)
{
   int t;
   bool b;
   TPoint ClientPos,Wpos;
  // TPoint  winPos;
   TPoint   *winPos = new TPoint();
   b = false;
   try
   {

	if ( (Left + Width - 1024) >=0 ) {
	   b = true;
	   t = Top;

   }else
   {

	 t =  Top;
   }

   if (b) {
	  GetCursorPos(winPos);
	  if (winPos == NULL) {
		  return;
	  }

	   Wpos.x = winPos->x ;
	   Wpos.y = winPos->y ;
	 ClientPos =  ScreenToClient(Wpos);
	 if (Name == GetFormNameAt(Wpos) ) {
		 Timer2->Enabled = false;
	  //	 frmInform->Top = t;
		 if (t != 0) {
			 Left = 1024 - Width ;
		 }
	 }else
	 {

		Timer2->Enabled = true;
	 }
   }
   }catch(...)
   {
  //	ShowMessage("ffff");
   }
	/*  if b then
  begin
    //得到当前鼠标指针的在屏幕上的坐标
    GetCursorPos(winPos);
    //当鼠标指针下的窗体的Name等于frmMain.name时
    if Form1.Name = GetFormNameAt(winPos) then
    {在此我们可以为frmMain取一个特别的名称，以防有别的窗体名称与它相同}
	begin
	  //停用Timer2
	  Form1.timer2.Enabled:= false;
	  //frmMain的Top与屏幕对齐
	  Form1.Top:= t;
	  if t <> 0 then
		Form1.Left:= Screen.Width - Form1.Width;
	end
	else begin
      Form1.Timer2.Enabled:= true;
    end;
  end; */
}
//---------------------------------------------------------------------------
void __fastcall TfrmInform::Timer2Timer(TObject *Sender)
{
  if ( Top  <= 20) {
	  //frmInform->Top = - (frmInform->Height - 8);
	//  if ( frmInform->Left + frmInform->Width > 1024) {
	 //	  frmInform->Left = 1024 - frmInform->Width ;
	//  }
  }//else
  if ( Left  + Width - 1024 >= -20) {
		Left = 1024 - 15;
		}

/*  // 当 top 距屏幕上侧 20 像素时,自动隐藏
  if Form1.Top <= 20 then
  begin
	//将frmMain向上移，在屏幕上方露出3像素
	Form1.Top:= -(Form1.Height - 3);
	if (Form1.Left + Form1.Width > Screen.Width) then
	  Form1.Left:= Screen.Width - Form1.Width;
  end
  // 当 left 距屏幕下侧 20 像素时,自动隐藏
  else if Form1.Left + Form1.Width - Screen.Width >= -20 then
	//将frmMain向右移，在屏幕右方露出4像素
	Form1.Left:= Screen.Width - 4;
end;

procedure TForm1.FormCanResize(Sender: TObject; var NewWidth,
  NewHeight: Integer; var Resize: Boolean);
begin
  if NewWidth < 170 then
    NewWidth:= 170;
  if NewHeight < 420 then
    NewHeight:= 420;
end;    */
}
//---------------------------------------------------------------------------
void __fastcall TfrmInform::FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight,
          bool &Resize)
{
  if (NewWidth < 170 ) {
	  NewWidth = 170;
  }
  if (NewHeight  < 420) {
	 NewHeight = 420;

  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmInform::Button1Click(TObject *Sender)
{
TPoint   *winPos = new TPoint();
 GetCursorPos(winPos);

//  ShowMessage(IntToStr(frmInform->Left));
  ShowMessage(GetFormNameAt(*winPos));
}
//---------------------------------------------------------------------------
void __fastcall TfrmInform::FormCreate(TObject *Sender)
{
	/*   register int x,y;
   int l,r;
   POINT *a;
   bool bCount,bHeight;
   HRGN WndRgn,TRgn1,TRgn2;
   if((a=(POINT *)malloc(800*4*(sizeof(POINT))))==NULL)
   {
     MessageBox(Handle,"分配内存失败！","信息提示",MB_OK);
     exit(0);
	}
   Width = Image1->Width;
   Height=Image1->Height;
   //重绘窗口，使窗口大小等于图像大小
   Repaint();
   l=0;
   r=Image1->Height*2-1;
   WndRgn=CreateRectRgn(0,0,Image1->Width,Image1->Height);
    //产生轮廓坐标点数组
   for(y=0;y<Image1->Height;y++)
   {
     bCount=true;
     for(x=0;x<Image1->Width;x++)
      if(Image1->Canvas->Pixels[x][y]!=clWhite)
      {
        a[l].x=x+1;
        a[l].y=y;
        bCount=false;
        break;
      }
    if(bCount)
      a[l]=a[l-1];
    l++;
    bHeight=true;
    for(x=Image1->Width-1;x>=0;x--)
    //根据去掉部分的具体颜色而定，此例为白色clWhite
    if(Image1->Canvas->Pixels[x][y]!=clWhite)
    {
      a[r].x=x;
      a[r].y=y;
      bHeight=false;
      break;
    }
    if(bHeight)
      a[r]=a[r+1];
    r--;
  }
  // 抠去图片内凹部分
  r=Image1->Height*2-1;
  for(y=0;y<Image1->Height;y++)
  {
     for(x=a[y].x;x<a[r].x;x++)
     if(Image1->Canvas->Pixels[x][y]==clWhite)
     {
       TRgn2=CreateRectRgn(x,y,x+1,y+1);
       CombineRgn(WndRgn,WndRgn,TRgn2,RGN_XOR);
       DeleteObject(TRgn2);
     }
     r--;
   }
   //将图片外围部分抠去
   TRgn1=CreatePolygonRgn(a,Image1->Height*2,ALTERNATE);
   CombineRgn(WndRgn,WndRgn,TRgn1,RGN_AND);
   DeleteObject(TRgn1);
   free(a);
   //显示不规则窗体
   SetWindowRgn(Handle,WndRgn,true);
   SetWindowPos(Handle,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);     */
}
//---------------------------------------------------------------------------
void __fastcall TfrmInform::dgDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State)
{

    if (State.Contains(gdSelected) || State.Contains(gdFocused)  ) {

		dg->Canvas->Brush->Color  = clSkyBlue;
        dg->Canvas->Font->Color = clRed ;
	 }
	 if (Column->FieldName  == "State") {
		TRect rc = TRect(10,10,10,10);
	   //TRect MyRect = Rect(10,10,100,100);
				  //		  Rectangle(rc,0,0,0,0) ;
	  dg->Canvas->FillRect(Rect);
	  int x = Rect.Left+(Rect.Right-Rect.Left-32)/2;
		Graphics::TBitmap   *p   =   new   Graphics::TBitmap();
	  ImageList1->GetBitmap(0,p);
	 // dg->Canvas->Draw(Rect.Left,Rect.top + 1,p);
	   rc.Right = Rect.Right - 36;
	   rc.Left = Rect.left ;
	   rc.Top = Rect.Top ;
	   rc.Bottom = Rect.Bottom ;
	  dg->Canvas->StretchDraw(rc,p);
	  //dg->Canvas->TextOutA(rc.Left + 20,rc.top ,NULL);

  }else
  {
	dg->DefaultDrawColumnCell(Rect,DataCol,Column,State);
  }

}
//---------------------------------------------------------------------------
void TfrmInform::Refresh()
{
  AnsiString sql;
  sql = "select * from SYS_InforMessage where state <> 0";
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfrmInform::FormShow(TObject *Sender)
{
	Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmInform::dgCellClick(TColumn *Column)
{
  LandInfo li;
  int type =0;
  AnsiString DanHao;
   type = aq->FieldByName("type")->AsInteger ;
   DanHao = aq->FieldByName("value")->AsAnsiString ;
   switch (type) {
	   case 1:

				li.app = Application;
				li.con = fcn ;
				li.userID = UserID ;
				li.FormatStr = "#,##0.00";
				li.storageID =  StgID ;
			  //	if (CheckPower("一般订单") ) {
				BIOrderManageDanHao(&li,DanHao);
				adosp->Parameters->ParamByName("@ID")->Value = aq->FieldByName("ID")->AsInteger;
				adosp->ExecProc();
			 //	}else
			  //	{
			 //	 ShowNoPower();
			//	}
			break;
	   case 2:
		   break;

	   case 3:
			break;
	  default:
			break;
   }
}
//---------------------------------------------------------------------------

