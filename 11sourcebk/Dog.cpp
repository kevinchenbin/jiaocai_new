//---------------------------------------------------------------------------


#pragma hdrstop
#include "AES.h"
#include "Dog.h"



  
//---------------------------------------------------------------------------
int ReadDog::ReadDevNumber()
{
    return 1128550468;
	 res = LIV_get_hardware_info(pdhandle,&info);
	 if (res) {
		 LIV_close(pdhandle);
		 return 0;
	 }
	 return info.developerNumber ;

}
String ReadDog::ReadDogInfo()
{

	byte pd4[16]={0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

	memset(ciphtext,0X00,16);


	 unsigned char data[512] ="";
		memset(data, 0, 512);


	char a[17];
	res = LIV_read(pdhandle, 0, data);

	if(res) {
	LIV_close(pdhandle);
	return "";
	}
	 byte pd2[16];
	 memset(pd2,0X00,16);
	 for (int i=0; i < 16; i++) {
			 ciphtext[i] =data[i];
	   }


	 AES *pd = new AES(0,pd4);
	 pd->InvCipher(ciphtext,pd2);
	 delete pd;


	   for (int i=0; i < 16; i++) {
			 a[i] =pd2[i];
	   }
	   a[16]='\0';
		return a;

}
int ReadDog::OpenDog()
{
   return 1;
	res =  LIV_open(0x43445044,0,&pdhandle);
	if(res) {
	  // LIV_close(pdhandle);
		return 1;
	}
	res =  LIV_passwd(pdhandle,1,(unsigned char *)"L3gend12");
	if (res) {
		LIV_close(pdhandle);
		return 2;
	}
	return 0;
}

int ReadDog::CloseDog()
{
   return 1;
	res =  LIV_close(pdhandle);
	if(res) {
	   return 0;
	}
      return 1;

}
#pragma package(smart_init)
