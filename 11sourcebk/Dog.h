//---------------------------------------------------------------------------

#ifndef DogH
#define DogH
#include "living1.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
const int DevNumber  = 1128550468;
const int Max_Length = 16;

class ReadDog
{
  private:
	unsigned char plantext[16];

	unsigned char ciphtext[16];

	LIV_hardware_info info ;
	int res;
	int pdhandle;
	int handlebk;
public:
	int OpenDog();
	int ReadDevNumber();
	String ReadDogInfo();
	int CloseDog();
};
//---------------------------------------------------------------------------
#endif
