//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitshengji.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmshengji *frmshengji;
//---------------------------------------------------------------------------
__fastcall Tfrmshengji::Tfrmshengji(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall Tfrmshengji::RzButton2Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmshengji::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void Tfrmshengji::picview()
{
	int i,left,top,width,height;
	left = Image2->Left;
	top = Image2->Top;
	width = Image2->Width;
	height = Image2->Height;
	for (i = 0; i <= width; i++){
	//通过图像的坐标选定图像的一部分
		Image2->Left = left + (width - i)/2;
		Image2->Top = top + height/2 - i*height/width/2;
		Image2->Width  = i;
		Image2->Height = i*height/width;
		Image2->Refresh() ;
        Sleep(100);
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmshengji::Button1Click(TObject *Sender)
{
       picview();
}
//---------------------------------------------------------------------------
