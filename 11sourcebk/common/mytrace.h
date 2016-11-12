  #ifndef mytraceH
  #define mytraceH

  #include   <assert.h>
  #include <stdio.h >
  #include <tchar.h>
  #include <string>
  #include <Windows.h>
  const _TCHAR* FloatToCStr(double value)
  {
	static _TCHAR buffer[256];
	memset(buffer, 0, sizeof(buffer));
	#ifdef _UNICODE
    	swprintf(buffer, L"%.2f", value);
	#else
    	sprintf(buffer, "%f", value);
	#endif
    return buffer;
  }

  template   <class   T>   
  class   TMyDebugHlpr   
  {   
  public:   
      static   void   __cdecl   TRACE_HLPR(T*   szFormat,   ...);   
  };   
    
  template   <class   T>   
  void   __cdecl   TMyDebugHlpr<T>::TRACE_HLPR(T*   szFormat,   ...)   
  {
	  va_list   args;
	  va_start(args,   szFormat);
	  int bufSize;

	  #ifdef _UNICODE
		std::wstring tmp(szFormat);
	  #else
		std::string tmp(szFormat);
	  #endif
	  _TCHAR szBuffer[_MAX_PATH*2];
	  //memset(szBuffer, 0, sizeof(szBuffer));
	  if(sizeof(szBuffer)<(tmp.length()-20))
		tmp=tmp.substr(1,sizeof(szBuffer)-20);
	  tmp = _T("[MyDebug]   <") + tmp + _T(">         ");
	  wvsprintf(szBuffer, tmp.c_str(), args);
	  ::OutputDebugString(szBuffer);
	  va_end(args);

//	  int       bufSize;
//	  _TCHAR   szBuffer[_MAX_PATH*2];
//	  String   tmp(szFormat);
//	  if(sizeof(szBuffer)<(tmp.Length()-20))
//		  tmp=tmp.SubString(1,sizeof(szBuffer)-20);
//
//	  tmp=_T("[MyDebug]   <") + tmp + _T(">         ");
//
//	  bufSize = wvsprintf(szBuffer,   tmp.c_str(),   args);
//	  assert(bufSize < sizeof(szBuffer));
//	  ::OutputDebugString(szBuffer);
//	  va_end(args);
  }   
    
    
  #if   !defined(MYTRACEF)   
  #define   MYTRACEF     TMyDebugHlpr<TCHAR>::TRACE_HLPR   
  #endif   
    
  #if   !defined(MYTRACE)   
  #define   MYTRACE(MSG)     TMyDebugHlpr<TCHAR>::TRACE_HLPR(String(MSG).c_str());   
  #endif

  #endif
