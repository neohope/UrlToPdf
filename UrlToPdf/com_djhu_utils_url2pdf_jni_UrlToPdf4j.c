#include "com_djhu_utils_url2pdf_jni_UrlToPdf4j.h"
#include "UrlToPdf.h"
#include "UtilsCharset.h"

JNIEXPORT jint JNICALL Java_com_djhu_utils_url2pdf_jni_UrlToPdf4j_nativeDjhuUrlToPdf(JNIEnv *env, jclass cls, jstring inUrl, jstring outPdf)
{
	const char* url = (*env)->GetStringUTFChars(env, inUrl, 0);
	const char* pdf = (*env)->GetStringUTFChars(env, outPdf, 0);
	return djhuUrlToPdfA(url, pdf);
}

char* getStringFromJObject(JNIEnv *env, jobject jobj, const char* fieldName)
{
	jclass cls = (*env)->GetObjectClass(env, jobj);
	if (cls == NULL)return NULL;

	jfieldID myJid = (*env)->GetFieldID(env, cls, fieldName, "Ljava/lang/String;");
	if (myJid == NULL)return NULL;

	jstring myJstring = (jstring)(*env)->GetObjectField(env, jobj, myJid);
	//that is unicode
	//const char* myChar = (*env)->GetStringChars(env, myJstring, 0);
	//const char* myChar = (*env)->GetStringUTFChars(env, myJstring, 0);

	const jchar* jcstr = (*env)->GetStringChars(env, myJstring, 0);
	if (jcstr == NULL)return NULL;
	//int inlength = (*env)->GetStringLength(env, myJstring);

	//malloc
	//remember to free buffer
	char* ansiBuff = UnicodeToMultiByte((LPCWSTR)jcstr, CP_ACP);

	(*env)->ReleaseStringChars(env, myJstring, jcstr);

	return ansiBuff;
}

JNIEXPORT jint JNICALL Java_com_djhu_utils_url2pdf_jni_UrlToPdf4j_nativeDjhuUrlToPdfParam(JNIEnv *env, jclass cls, jobject jparam)
{
	//Hansen Debug
	//DebugBreak();

	PDFPARAMA *parama = (PDFPARAMA *)malloc(sizeof(PDFPARAMA));
	if (parama == NULL)return -1;

	memset(parama, 0, sizeof(parama));
	parama->mbUrl = getStringFromJObject(env, jparam, "mbUrl");
	parama->mbPdfPath = getStringFromJObject(env, jparam, "mbPdfPath");
	parama->mbTitle = getStringFromJObject(env, jparam, "mbTitle");
	parama->mbPageSize = getStringFromJObject(env, jparam, "mbPageSize");
	parama->mbOrientation = getStringFromJObject(env, jparam, "mbOrientation");
	parama->mbMarginTop = getStringFromJObject(env, jparam, "mbMarginTop");
	parama->mbMarginBottom = getStringFromJObject(env, jparam, "mbMarginBottom");
	parama->mbMarginLeft = getStringFromJObject(env, jparam, "mbMarginLeft");
	parama->mbMarginRight = getStringFromJObject(env, jparam, "mbMarginRight");
	parama->mbHeaderLeft = getStringFromJObject(env, jparam, "mbHeaderLeft");
	parama->mbHeaderRight = getStringFromJObject(env, jparam, "mbHeaderRight");
	parama->mbHeaderCenter = getStringFromJObject(env, jparam, "mbHeaderCenter");
	parama->mbHeaderFontName = getStringFromJObject(env, jparam, "mbHeaderFontName");
	parama->mbHeaderFontSize = getStringFromJObject(env, jparam, "mbHeaderFontSize");
	parama->mbHeaderHtml = getStringFromJObject(env, jparam, "mbHeaderHtml");
	parama->mbHeaderLine = getStringFromJObject(env, jparam, "mbHeaderLine");
	parama->mbFooterLeft = getStringFromJObject(env, jparam, "mbFooterLeft");
	parama->mbFooterRight = getStringFromJObject(env, jparam, "mbFooterRight");
	parama->mbFooterCenter = getStringFromJObject(env, jparam, "mbFooterCenter");
	parama->mbFooterFontName = getStringFromJObject(env, jparam, "mbFooterFontName");
	parama->mbFooterFontSize = getStringFromJObject(env, jparam, "mbFooterFontSize");
	parama->mbFooterHtml = getStringFromJObject(env, jparam, "mbFooterHtml");
	parama->mbFoolterLine = getStringFromJObject(env, jparam, "mbFoolterLine");

	int nRet = djhuUrlToPdfParamA(parama);

	//ÊÍ·ÅÄÚ´æparama
	releasePDFPARAMABuffer(parama);
	free(parama);
	parama = NULL;

	return nRet;
}

JNIEXPORT jint JNICALL Java_com_djhu_utils_url2pdf_jni_UrlToPdf4j_nativeDjhuPDFInit(JNIEnv *env, jclass cls)
{
	return djhuPDFLibInit();
}

JNIEXPORT jint JNICALL Java_com_djhu_utils_url2pdf_jni_UrlToPdf4j_nativeDjhuPDFDeInit(JNIEnv *env, jclass cls)
{
	return djhuPDFLibDeInit();
}
