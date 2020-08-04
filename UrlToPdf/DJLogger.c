#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <io.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdarg.h>

#pragma warning( disable : 4996)

//日志分页大小
#define MAXLOGSIZE 20000000
//一行日志最大长度
#define MAXLINSIZE 16000

char logfileA[] = "PDFLog.log";
char logfileT[] = "PDFLog%04d-%02d-%02d.log";
static char logfileB[255];
static char logstr[MAXLINSIZE + 1];
char datestr[16];
char timestr[16];
char mss[4];

FILE *flog;

//关键区，控制并发 
CRITICAL_SECTION cs_log;

/*
* 初始化关键区
*/
void DJLogInit(){
	InitializeCriticalSection(&cs_log);
}

/*
* 反初始化关键区
*/
void DJLogDeInit(){
	DeleteCriticalSection(&cs_log);
}

/*
* 用关键区来控制并发
*/
void Lock(CRITICAL_SECTION *criticalSection) {
	EnterCriticalSection(criticalSection);
}

void Unlock(CRITICAL_SECTION *criticalSection) {
	LeaveCriticalSection(criticalSection);
}

/*
* 写日志
*/
void LogV(const char *pszFmt, va_list argp) {
	struct tm *now;
	struct timeb tb;

	//拼接日志字符串，并写入日志文件
	if (NULL == pszFmt || 0 == pszFmt[0]) return;
	_vsnprintf(logstr, MAXLINSIZE, pszFmt, argp);
	ftime(&tb);
	now = localtime(&tb.time);
	sprintf(datestr, "%04d-%02d-%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	sprintf(timestr, "%02d:%02d:%02d", now->tm_hour, now->tm_min, now->tm_sec);
	sprintf(mss, "%03d", tb.millitm);
	
	//日志输出到CUI
	//printf("%s %s.%s %s\r\n", datestr, timestr, mss, logstr);
	
	//日志追加写入日志文件
	flog = fopen(logfileA, "a");
	if (NULL != flog) {
		fprintf(flog, "%s %s.%s %s\r\n", datestr, timestr, mss, logstr);

		//产生新的日志文件
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
* 记录日志
*/
void DJLog(const char *pszFmt, ...) {
	va_list argp;

	Lock(&cs_log);
	va_start(argp, pszFmt);
	LogV(pszFmt, argp);
	va_end(argp);
	Unlock(&cs_log);
}