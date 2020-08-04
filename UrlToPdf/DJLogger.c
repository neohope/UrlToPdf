#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <io.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdarg.h>

#pragma warning( disable : 4996)

//��־��ҳ��С
#define MAXLOGSIZE 20000000
//һ����־��󳤶�
#define MAXLINSIZE 16000

char logfileA[] = "PDFLog.log";
char logfileT[] = "PDFLog%04d-%02d-%02d.log";
static char logfileB[255];
static char logstr[MAXLINSIZE + 1];
char datestr[16];
char timestr[16];
char mss[4];

FILE *flog;

//�ؼ��������Ʋ��� 
CRITICAL_SECTION cs_log;

/*
* ��ʼ���ؼ���
*/
void DJLogInit(){
	InitializeCriticalSection(&cs_log);
}

/*
* ����ʼ���ؼ���
*/
void DJLogDeInit(){
	DeleteCriticalSection(&cs_log);
}

/*
* �ùؼ��������Ʋ���
*/
void Lock(CRITICAL_SECTION *criticalSection) {
	EnterCriticalSection(criticalSection);
}

void Unlock(CRITICAL_SECTION *criticalSection) {
	LeaveCriticalSection(criticalSection);
}

/*
* д��־
*/
void LogV(const char *pszFmt, va_list argp) {
	struct tm *now;
	struct timeb tb;

	//ƴ����־�ַ�������д����־�ļ�
	if (NULL == pszFmt || 0 == pszFmt[0]) return;
	_vsnprintf(logstr, MAXLINSIZE, pszFmt, argp);
	ftime(&tb);
	now = localtime(&tb.time);
	sprintf(datestr, "%04d-%02d-%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	sprintf(timestr, "%02d:%02d:%02d", now->tm_hour, now->tm_min, now->tm_sec);
	sprintf(mss, "%03d", tb.millitm);
	
	//��־�����CUI
	//printf("%s %s.%s %s\r\n", datestr, timestr, mss, logstr);
	
	//��־׷��д����־�ļ�
	flog = fopen(logfileA, "a");
	if (NULL != flog) {
		fprintf(flog, "%s %s.%s %s\r\n", datestr, timestr, mss, logstr);

		//�����µ���־�ļ�
		if (ftell(flog)>MAXLOGSIZE) {
			fclose(flog);
			sprintf(logfileB, logfileT, now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
			rename(logfileA, logfileB);
		}
		else {
			fclose(flog);
		}
	}
}

/*
* ��¼��־
*/
void DJLog(const char *pszFmt, ...) {
	va_list argp;

	Lock(&cs_log);
	va_start(argp, pszFmt);
	LogV(pszFmt, argp);
	va_end(argp);
	Unlock(&cs_log);
}