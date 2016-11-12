//---------------------------------------------------------------------------

#ifndef AddsyslogH
#define AddsyslogH

#include <vcl.h>
#include <ADODB.hpp>



void AddEvent(int type,AnsiString SourceFrom,int user,int Stg,AnsiString Mg,TADOConnection *con);

#endif
