//---------------------------------------------------------------------------

#ifndef IsbnToCodeH
#define IsbnToCodeH

#include <vcl.h>

//---------------------------------------------------------------------------
class IsbnToCode
{
public:
	IsbnToCode(String barcode);
	int StringToPartIsbn(String str,int rs[]);
	

private:
	String m_barcode;
};


#endif