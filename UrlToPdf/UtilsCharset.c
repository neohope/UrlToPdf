#include "UtilsCharset.h"

//remember to free
wchar_t * MultiByteToUnicode(const char* multiByteIn, UINT codePage)
{
	if (multiByteIn == NULL)return NULL;

	int outLength = MultiByteToWideChar(codePage, 0, multiByteIn, -1, NULL, 0);
	wchar_t *wbuffOut = (wchar_t *)malloc((outLength + 1)*sizeof(wchar_t));
	memset(wbuffOut, 0, (outLength + 1)*sizeof(wchar_t));
	outLength = MultiByteToWideChar(codePage, 0, multiByteIn, -1, wbuffOut, outLength);

	return wbuffOut;
}

//remember to free
char* UnicodeToMultiByte(const wchar_t* unicodeIn, UINT codePage)
{
	if (unicodeIn == NULL)return NULL;

	int outLength = WideCharToMultiByte(codePage, 0, unicodeIn, -1, NULL, 0, NULL, NULL);
	char* mbuffOut = (char *)malloc(outLength + 1);
	memset(mbuffOut, 0, outLength + 1);
	outLength = WideCharToMultiByte(codePage, 0, unicodeIn, -1, mbuffOut, outLength, NULL, NULL);

	return mbuffOut;
}

//remember to free
char * AnsiToUtf8(const char* ansiArray)
{
	if (ansiArray == NULL)return NULL;

	wchar_t * unicodeBuff = MultiByteToUnicode(ansiArray, CP_ACP);
	char *utf8Buff = UnicodeToMultiByte(unicodeBuff, CP_UTF8);

	free(unicodeBuff);
	return utf8Buff;
}