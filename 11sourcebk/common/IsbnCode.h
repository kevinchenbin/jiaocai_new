//---------------------------------------------------------------------------

#ifndef IsbnCodeH
#define IsbnCodeH

#include <vcl.h>

//---------------------------------------------------------------------------
class IsbnToCode
{
public:
	IsbnCode(String barcode);
	int StringToPartIsbn(String str,int rs[]);
	

private:
	String m_barcode;
};

String BuildISBNCode(String barcode);

#endif