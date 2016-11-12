//---------------------------------------------------------------------
#pragma hdrstop

#include "IsbnCode.h"
//---------------------------------------------------------------------
IsbnToCode::IsbnCount(String barcode)
{
   String t;
   int i,k,rs[9];
   t="hello" ;
   //ShowMessage(t);
   k = StringToIsbn(barcode,rs);
   String t1;
   for(i=0;i<9;i++)
   t1 = t1 + IntToStr(rs[i]);
   ShowMessage(t1);
   ShowMessage(k);
   if(k==345)
   {
		t1 = t1+"x";
		dbedtISBN->DataSource ->DataSet ->Edit();
		dbedtISBN->DataSource ->DataSet ->FieldByName("ISBN")->Value = t1;
   }
   else
   {
		t1 = t1 + IntToStr(k);
		dbedtISBN->DataSource ->DataSet ->Edit();
		dbedtISBN->DataSource ->DataSet ->FieldByName("ISBN")->Value = t1;
		//dbedtISBN->Text = t1;//IntToStr(rs[i]);
   }

}

int IsbnToCode::StringToPartIsbn(String str,int rs[])
{
	String str1;
	str1=str;
	int t,s=0;
	int k,a=9;
	k = str.Length();
	//ShowMessage(k);
	for(int i=0;i<k;i++)
	{
		String c;
		// 得到最后一个字符
		c = str.LastChar();
		t = StrToInt(c);
		if(i>0&&i<10)
		{
		//按规则计算isbn代码和
			s = s + t*a--;
		//得到isbn前9位数字
			rs[9-i] = t;
			//ShowMessage(rs[9-i]);
		}
		str.Delete(str.Length(),1 );
	}
	//获取isbn最后一位数字
	a = s%11;
	if(a==10)
	return 345;
	else
	return a;
}

String BuildISBNCode(String barcode)
{

}
