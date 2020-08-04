#include <windows.h>

//always remember to free buffer
wchar_t * MultiByteToUnicode(const char* multiByteIn, UINT codePage);
char* UnicodeToMultiByte(const wchar_t* unicodeIn, UINT codePage);
char * AnsiToUtf8(const char* ansiArray);
