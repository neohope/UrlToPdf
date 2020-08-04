#include "Thirdpart.h"
#include "UrlToPdf.h"
#include "UtilsCharset.h"
#include "DJLogger.h"

PDFPARAMA* PDFPARAMW2PDFPARAMWA(const PDFPARAMW* paramw);
PDFPARAMA* PDFPARAMAAnsi2PDFPARAMWAUtf8(const PDFPARAMA* paramaAnsi);

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}

//call back functions
void progress_changed(wkhtmltopdf_converter* c, int p){
}

void phase_changed(wkhtmltopdf_converter* c){
}

void error(wkhtmltopdf_converter* c, const char* msg){
}

void warning(wkhtmltopdf_converter* c, const char* msg){
}

//Init
int djhuPDFLibInit()
{
	DJLogInit();
	DJLog("wkhtmltopdf_init begin");
	wkhtmltopdf_init(1);
	DJLog("wkhtmltopdf_init end");
	return 0;
}

//DeInit
int djhuPDFLibDeInit()
{
	DJLog("wkhtmltopdf_deinit begin");
	wkhtmltopdf_deinit();
	DJLog("wkhtmltopdf_deinit begin");
	DJLogDeInit();
	return 0;
}

//Covert Url to Pdf
//ANSI vsersion 
int djhuUrlToPdfA(const char* url, const char* pdfpath)
{
	DJLog("djhuUrlToPdfA Called with url=%s, pdfpath=%s", url, pdfpath);

	wkhtmltopdf_global_settings* gs;
	wkhtmltopdf_object_settings* os;
	wkhtmltopdf_converter* converter;
	int ret = DJHU_URLTOPDF_OK;

	//malloc
	char * utf8Url = AnsiToUtf8(url);
	char * utf8Pdfpath = AnsiToUtf8(pdfpath);

	gs = wkhtmltopdf_create_global_settings();
	wkhtmltopdf_set_global_setting(gs, "out", utf8Pdfpath);

	os = wkhtmltopdf_create_object_settings();
	wkhtmltopdf_set_object_setting(os, "page", utf8Url);

	converter = wkhtmltopdf_create_converter(gs);

	/*
	wkhtmltopdf_set_progress_changed_callback(converter, progress_changed);
	wkhtmltopdf_set_phase_changed_callback(converter, phase_changed);
	wkhtmltopdf_set_error_callback(converter, error);
	wkhtmltopdf_set_warning_callback(converter, warning);
	*/
	wkhtmltopdf_add_object(converter, os, NULL);

	int convertRet = wkhtmltopdf_convert(converter);
	if (!convertRet)
	{
		ret = wkhtmltopdf_http_error_code(converter);
		if (ret == 0)ret = -1;
	}

	wkhtmltopdf_destroy_converter(converter);

	//free
	if (utf8Url != NULL){free(utf8Url);utf8Url = NULL;}
	if (utf8Pdfpath!=NULL){free(utf8Pdfpath);utf8Pdfpath = NULL;}

	DJLog("djhuUrlToPdfA Ended");
	return ret;
}

//Covert Url to Pdf
//Unicode version
//just convert the parameters to char* and invoke the ANSI vsersion
int djhuUrlToPdfW(const wchar_t* wUrl, const wchar_t* wPdfpath)
{
	DJLog("djhuUrlToPdfW Called");

	size_t num_of_char_converted = 0;
	int ret = DJHU_URLTOPDF_OK;

	//malloc
	char* awUrl = UnicodeToMultiByte(wUrl, CP_ACP);
	char* awPdfpath = UnicodeToMultiByte(wPdfpath, CP_ACP);

	int nRet = djhuUrlToPdfA(awUrl, awPdfpath);

	//free
	if (awUrl != NULL){ free(awUrl); awUrl = NULL; }
	if (awPdfpath != NULL){ free(awPdfpath); awPdfpath = NULL; }

	DJLog("djhuUrlToPdfW Ended");
	return nRet;
}

//Covert Url to Pdf by Params
//ANSI vsersion 
int djhuUrlToPdfParamA(const PDFPARAMA* parama)
{
	DJLog("djhuUrlToPdfParamA Called with mbUrl=%s, mbPdfPath=%s, mbTitle=%s, mbPageSize=%s, mbOrientation=%s, mbMarginTop=%s, \
		mbMarginBottom=%s, mbMarginLeft=%s, mbMarginRight=%s, mbHeaderLeft=%s, mbHeaderRight=%s, mbHeaderCenter=%s, mbHeaderFontName=%s, \
		mbHeaderFontSize=%s, mbHeaderHtml=%s, mbHeaderLine=%s, mbFooterLeft=%s, mbFooterRight=%s, mbFooterCenter=%s, mbFooterFontName=%s, \
		mbFooterFontSize=%s, mbFooterHtml=%s, mbFoolterLine=%s", parama->mbUrl, parama->mbPdfPath, parama->mbTitle, parama->mbPageSize, \
		parama->mbOrientation, parama->mbMarginTop, parama->mbMarginBottom, parama->mbMarginLeft, parama->mbMarginRight, parama->mbHeaderLeft, \
		parama->mbHeaderRight, parama->mbHeaderCenter, parama->mbHeaderFontName, parama->mbHeaderFontSize, parama->mbHeaderHtml, parama->mbHeaderLine, \
		parama->mbFooterLeft, parama->mbFooterRight, parama->mbFooterCenter, parama->mbFooterFontName, parama->mbFooterFontSize, parama->mbFooterHtml, parama->mbFoolterLine);

	wkhtmltopdf_global_settings* gs;
	wkhtmltopdf_object_settings* os;
	wkhtmltopdf_converter* converter;
	int ret = DJHU_URLTOPDF_OK;

	//ansi to utf-8
	//malloc
	PDFPARAMA* paramaUtf8 = PDFPARAMAAnsi2PDFPARAMWAUtf8(parama);
	//const PDFPARAMA* paramaUtf8 = parama;

	//=========================================================================
	//pdf url
	gs = wkhtmltopdf_create_global_settings();
	wkhtmltopdf_set_global_setting(gs, "out", paramaUtf8->mbPdfPath); 

	//html url
	os = wkhtmltopdf_create_object_settings();
	wkhtmltopdf_set_object_setting(os, "page", paramaUtf8->mbUrl);

	//title
	if (paramaUtf8->mbTitle != NULL && strlen(paramaUtf8->mbTitle)>0)
	{
		wkhtmltopdf_set_global_setting(gs, "documentTitle ", paramaUtf8->mbTitle);
	}

	//pagesize
	if (paramaUtf8->mbPageSize != NULL && strlen(paramaUtf8->mbPageSize)>0)
	{
		wkhtmltopdf_set_global_setting(gs, "size.paperSize", paramaUtf8->mbPageSize);
	}

	//orientation
	if (paramaUtf8->mbOrientation != NULL && strlen(paramaUtf8->mbOrientation)>0)
	{
		wkhtmltopdf_set_global_setting(gs, "orientation", paramaUtf8->mbOrientation);
	}

	//=========================================================================
	//margin top
	if (paramaUtf8->mbMarginTop != NULL && strlen(paramaUtf8->mbMarginTop)>0)
	{
		wkhtmltopdf_set_global_setting(gs, "margin.top", paramaUtf8->mbMarginTop);
	}

	//margin bottom
	if (paramaUtf8->mbMarginBottom != NULL && strlen(paramaUtf8->mbMarginBottom)>0)
	{
		wkhtmltopdf_set_global_setting(gs, "margin.bottom", paramaUtf8->mbMarginBottom);
	}

	//margin left
	if (paramaUtf8->mbMarginLeft != NULL && strlen(paramaUtf8->mbMarginLeft)>0)
	{
		wkhtmltopdf_set_global_setting(gs, "margin.left", paramaUtf8->mbMarginLeft);
	}

	//margin right
	if (paramaUtf8->mbMarginRight != NULL && strlen(paramaUtf8->mbMarginRight)>0)
	{
		wkhtmltopdf_set_global_setting(gs, "margin.right", paramaUtf8->mbMarginRight);
	}

	//=========================================================================
	//header left 
	if (paramaUtf8->mbHeaderLeft != NULL && strlen(paramaUtf8->mbHeaderLeft)>0)
	{
		wkhtmltopdf_set_object_setting(os, "header.left", paramaUtf8->mbHeaderLeft);
	}

	//header center
	if (paramaUtf8->mbHeaderCenter != NULL && strlen(paramaUtf8->mbHeaderCenter)>0)
	{
		wkhtmltopdf_set_object_setting(os, "header.center", paramaUtf8->mbHeaderCenter);
	}

	//header right
	if (paramaUtf8->mbHeaderRight != NULL && strlen(paramaUtf8->mbHeaderRight)>0)
	{
		wkhtmltopdf_set_object_setting(os, "header.right", paramaUtf8->mbHeaderRight);
	}

	//header fontName
	if (paramaUtf8->mbHeaderFontName != NULL && strlen(paramaUtf8->mbHeaderFontName)>0)
	{
		wkhtmltopdf_set_object_setting(os, "header.fontName", paramaUtf8->mbHeaderFontName);
	}

	//header fontSize
	if (paramaUtf8->mbHeaderFontSize != NULL && strlen(paramaUtf8->mbHeaderFontSize)>0)
	{
		wkhtmltopdf_set_object_setting(os, "header.fontSize", paramaUtf8->mbHeaderFontSize);
	}

	//header htmlUrl
	if (paramaUtf8->mbHeaderHtml != NULL && strlen(paramaUtf8->mbHeaderHtml)>0)
	{
		wkhtmltopdf_set_object_setting(os, "header.htmlUrl", paramaUtf8->mbHeaderHtml);
	}

	//header line
	if (paramaUtf8->mbHeaderLine != NULL && strlen(paramaUtf8->mbHeaderLine)>0)
	{
		wkhtmltopdf_set_object_setting(os, "header.line", paramaUtf8->mbHeaderLine);
	}

	//=========================================================================
	//footer left 
	if (paramaUtf8->mbFooterLeft != NULL && strlen(paramaUtf8->mbFooterLeft)>0)
	{
		wkhtmltopdf_set_object_setting(os, "footer.left", paramaUtf8->mbFooterLeft);
	}

	//footer center
	if (paramaUtf8->mbFooterCenter != NULL && strlen(paramaUtf8->mbFooterCenter)>0)
	{
		wkhtmltopdf_set_object_setting(os, "footer.center", paramaUtf8->mbFooterCenter);
	}

	//footer right
	if (paramaUtf8->mbFooterRight != NULL && strlen(paramaUtf8->mbFooterRight)>0)
	{
		wkhtmltopdf_set_object_setting(os, "footer.right", paramaUtf8->mbFooterRight);
	}

	//footer fontName
	if (paramaUtf8->mbFooterFontName != NULL && strlen(paramaUtf8->mbFooterFontName)>0)
	{
		wkhtmltopdf_set_object_setting(os, "footer.fontName", paramaUtf8->mbFooterFontName);
	}

	//footer fontSize
	if (paramaUtf8->mbFooterFontSize != NULL && strlen(paramaUtf8->mbFooterFontSize)>0)
	{
		wkhtmltopdf_set_object_setting(os, "footer.fontSize", paramaUtf8->mbFooterFontSize);
	}

	//footer htmlUrl
	if (paramaUtf8->mbFooterHtml != NULL && strlen(paramaUtf8->mbFooterHtml)>0)
	{
		wkhtmltopdf_set_object_setting(os, "footer.htmlUrl", paramaUtf8->mbFooterHtml);
	}

	//footer line
	if (paramaUtf8->mbFoolterLine != NULL && strlen(paramaUtf8->mbFoolterLine)>0)
	{
		wkhtmltopdf_set_object_setting(os, "footer.line", paramaUtf8->mbFoolterLine);
	}

	//=========================================================================
	converter = wkhtmltopdf_create_converter(gs);

	/*
	wkhtmltopdf_set_progress_changed_callback(converter, progress_changed);
	wkhtmltopdf_set_phase_changed_callback(converter, phase_changed);
	wkhtmltopdf_set_error_callback(converter, error);
	wkhtmltopdf_set_warning_callback(converter, warning);
	*/
	wkhtmltopdf_add_object(converter, os, NULL);

	int convertRet = wkhtmltopdf_convert(converter);
	if (!convertRet)
	{
		ret = wkhtmltopdf_http_error_code(converter);
		if (ret == 0)ret = -1;
	}

	wkhtmltopdf_destroy_converter(converter);

	//free
	releasePDFPARAMABuffer(paramaUtf8);
	if (paramaUtf8 != NULL)free(paramaUtf8); paramaUtf8 = NULL;

	DJLog("djhuUrlToPdfParamA Ended");
	return ret;
}

//Covert Url to Pdf by Params
//Unicode version
//just convert the parameters to char* and invoke the ANSI vsersion
int djhuUrlToPdfParamW(const PDFPARAMW* paramw)
{
	DJLog("djhuUrlToPdfParamW Called");

	//paramw2parama
	//malloc
	PDFPARAMA* parama = PDFPARAMW2PDFPARAMWA(paramw);

	int ret = djhuUrlToPdfParamA(parama);

	//free
	releasePDFPARAMABuffer(parama);
	if (parama != NULL)free(parama); parama = NULL;

	DJLog("djhuUrlToPdfParamW Ended");
	return ret;
}

//convert PDFPARAMW to PDFPARAMWA
//remember to use releasePDFPARAMABuffer
PDFPARAMA* PDFPARAMW2PDFPARAMWA(const PDFPARAMW* paramw)
{
	DJLog("PDFPARAMW2PDFPARAMWA Called");

	if (paramw == NULL)return NULL;

	PDFPARAMA *parama = (PDFPARAMA *)malloc(sizeof(PDFPARAMA));
	memset(parama, 0, sizeof(PDFPARAMA));
	if (paramw->mbUrl != NULL){ parama->mbUrl = UnicodeToMultiByte(paramw->mbUrl, CP_ACP); }
	else{ parama->mbUrl = NULL; }
	if (paramw->mbPdfPath != NULL){ parama->mbPdfPath = UnicodeToMultiByte(paramw->mbPdfPath, CP_ACP); }
	else{ parama->mbPdfPath = NULL; }
	if (paramw->mbTitle != NULL){ parama->mbTitle = UnicodeToMultiByte(paramw->mbTitle, CP_ACP); }
	else{ parama->mbTitle = NULL; }
	if (paramw->mbPageSize != NULL){ parama->mbPageSize = UnicodeToMultiByte(paramw->mbPageSize, CP_ACP); }
	else{ parama->mbPageSize = NULL; }
	if (paramw->mbOrientation != NULL){ parama->mbOrientation = UnicodeToMultiByte(paramw->mbOrientation, CP_ACP); }
	else{ parama->mbOrientation = NULL; }
	if (paramw->mbMarginTop != NULL){ parama->mbMarginTop = UnicodeToMultiByte(paramw->mbMarginTop, CP_ACP); }
	else{ parama->mbMarginTop = NULL; }
	if (paramw->mbMarginBottom != NULL){ parama->mbMarginBottom = UnicodeToMultiByte(paramw->mbMarginBottom, CP_ACP); }
	else{ parama->mbMarginBottom = NULL; }
	if (paramw->mbMarginLeft != NULL){ parama->mbMarginLeft = UnicodeToMultiByte(paramw->mbMarginLeft, CP_ACP); }
	else{ parama->mbMarginLeft = NULL; }
	if (paramw->mbMarginRight != NULL){ parama->mbMarginRight = UnicodeToMultiByte(paramw->mbMarginRight, CP_ACP); }
	else{ parama->mbMarginRight = NULL; }
	if (paramw->mbHeaderLeft != NULL){ parama->mbHeaderLeft = UnicodeToMultiByte(paramw->mbHeaderLeft, CP_ACP); }
	else{ parama->mbHeaderLeft = NULL; }
	if (paramw->mbHeaderRight != NULL){ parama->mbHeaderRight = UnicodeToMultiByte(paramw->mbHeaderRight, CP_ACP); }
	else{ parama->mbHeaderRight = NULL; }
	if (paramw->mbHeaderCenter != NULL){ parama->mbHeaderCenter = UnicodeToMultiByte(paramw->mbHeaderCenter, CP_ACP); }
	else{ parama->mbHeaderCenter = NULL; }
	if (paramw->mbHeaderFontName != NULL){ parama->mbHeaderFontName = UnicodeToMultiByte(paramw->mbHeaderFontName, CP_ACP); }
	else{ parama->mbHeaderFontName = NULL; }
	if (paramw->mbHeaderFontSize != NULL){ parama->mbHeaderFontSize = UnicodeToMultiByte(paramw->mbHeaderFontSize, CP_ACP); }
	else{ parama->mbHeaderFontSize = NULL; }
	if (paramw->mbHeaderHtml != NULL){ parama->mbHeaderHtml = UnicodeToMultiByte(paramw->mbHeaderHtml, CP_ACP); }
	else{ parama->mbHeaderHtml = NULL; }
	if (paramw->mbHeaderLine != NULL){ parama->mbHeaderLine = UnicodeToMultiByte(paramw->mbHeaderLine, CP_ACP); }
	else{ parama->mbHeaderLine = NULL; }
	if (paramw->mbFooterLeft != NULL){ parama->mbFooterLeft = UnicodeToMultiByte(paramw->mbFooterLeft, CP_ACP); }
	else{ parama->mbFooterLeft = NULL; }
	if (paramw->mbFooterRight != NULL){ parama->mbFooterRight = UnicodeToMultiByte(paramw->mbFooterRight, CP_ACP); }
	else{ parama->mbFooterRight = NULL; }
	if (paramw->mbFooterCenter != NULL){ parama->mbFooterCenter = UnicodeToMultiByte(paramw->mbFooterCenter, CP_ACP); }
	else{ parama->mbFooterCenter = NULL; }
	if (paramw->mbFooterFontName != NULL){ parama->mbFooterFontName = UnicodeToMultiByte(paramw->mbFooterFontName, CP_ACP); }
	else{ parama->mbFooterFontName = NULL; }
	if (paramw->mbFooterFontSize != NULL){ parama->mbFooterFontSize = UnicodeToMultiByte(paramw->mbFooterFontSize, CP_ACP); }
	else{ parama->mbFooterFontSize = NULL; }
	if (paramw->mbFooterHtml != NULL){ parama->mbFooterHtml = UnicodeToMultiByte(paramw->mbFooterHtml, CP_ACP); }
	else{ parama->mbFooterHtml = NULL; }
	if (paramw->mbFoolterLine != NULL){ parama->mbFoolterLine = UnicodeToMultiByte(paramw->mbFoolterLine, CP_ACP); }
	else{ parama->mbFoolterLine = NULL; }

	DJLog("PDFPARAMW2PDFPARAMWA Ended");
	return parama;
}

//convet PDFPARAMA char buffet form Ansi to Utf8
//remember to use releasePDFPARAMABuffer
PDFPARAMA* PDFPARAMAAnsi2PDFPARAMWAUtf8(const PDFPARAMA* paramaAnsi)
{
	DJLog("PDFPARAMAAnsi2PDFPARAMWAUtf8 Called");

	PDFPARAMA *paramaUtf8 = (PDFPARAMA *)malloc(sizeof(PDFPARAMA));
	memset(paramaUtf8, 0, sizeof(PDFPARAMA));
	if (paramaAnsi->mbUrl != NULL)paramaUtf8->mbUrl = AnsiToUtf8(paramaAnsi->mbUrl);
	if (paramaAnsi->mbPdfPath != NULL)paramaUtf8->mbPdfPath = AnsiToUtf8(paramaAnsi->mbPdfPath);
	if (paramaAnsi->mbTitle != NULL)paramaUtf8->mbTitle = AnsiToUtf8(paramaAnsi->mbTitle);
	if (paramaAnsi->mbPageSize != NULL)paramaUtf8->mbPageSize = AnsiToUtf8(paramaAnsi->mbPageSize);
	if (paramaAnsi->mbOrientation != NULL)paramaUtf8->mbOrientation = AnsiToUtf8(paramaAnsi->mbOrientation);
	if (paramaAnsi->mbMarginTop != NULL)paramaUtf8->mbMarginTop = AnsiToUtf8(paramaAnsi->mbMarginTop);
	if (paramaAnsi->mbMarginBottom != NULL)paramaUtf8->mbMarginBottom = AnsiToUtf8(paramaAnsi->mbMarginBottom);
	if (paramaAnsi->mbMarginLeft != NULL)paramaUtf8->mbMarginLeft = AnsiToUtf8(paramaAnsi->mbMarginLeft);
	if (paramaAnsi->mbMarginRight != NULL)paramaUtf8->mbMarginRight = AnsiToUtf8(paramaAnsi->mbMarginRight);
	if (paramaAnsi->mbHeaderLeft != NULL)paramaUtf8->mbHeaderLeft = AnsiToUtf8(paramaAnsi->mbHeaderLeft);
	if (paramaAnsi->mbHeaderRight != NULL)paramaUtf8->mbHeaderRight = AnsiToUtf8(paramaAnsi->mbHeaderRight);
	if (paramaAnsi->mbHeaderCenter != NULL)paramaUtf8->mbHeaderCenter = AnsiToUtf8(paramaAnsi->mbHeaderCenter);
	if (paramaAnsi->mbHeaderFontName != NULL)paramaUtf8->mbHeaderFontName = AnsiToUtf8(paramaAnsi->mbHeaderFontName);
	if (paramaAnsi->mbHeaderFontSize != NULL)paramaUtf8->mbHeaderFontSize = AnsiToUtf8(paramaAnsi->mbHeaderFontSize);
	if (paramaAnsi->mbHeaderHtml != NULL)paramaUtf8->mbHeaderHtml = AnsiToUtf8(paramaAnsi->mbHeaderHtml);
	if (paramaAnsi->mbHeaderLine != NULL)paramaUtf8->mbHeaderLine = AnsiToUtf8(paramaAnsi->mbHeaderLine);
	if (paramaAnsi->mbFooterLeft != NULL)paramaUtf8->mbFooterLeft = AnsiToUtf8(paramaAnsi->mbFooterLeft);
	if (paramaAnsi->mbFooterRight != NULL)paramaUtf8->mbFooterRight = AnsiToUtf8(paramaAnsi->mbFooterRight);
	if (paramaAnsi->mbFooterCenter != NULL)paramaUtf8->mbFooterCenter = AnsiToUtf8(paramaAnsi->mbFooterCenter);
	if (paramaAnsi->mbFooterFontName != NULL)paramaUtf8->mbFooterFontName = AnsiToUtf8(paramaAnsi->mbFooterFontName);
	if (paramaAnsi->mbFooterFontSize != NULL)paramaUtf8->mbFooterFontSize = AnsiToUtf8(paramaAnsi->mbFooterFontSize);
	if (paramaAnsi->mbFooterHtml != NULL)paramaUtf8->mbFooterHtml = AnsiToUtf8(paramaAnsi->mbFooterHtml);
	if (paramaAnsi->mbFoolterLine != NULL)paramaUtf8->mbFoolterLine = AnsiToUtf8(paramaAnsi->mbFoolterLine);

	DJLog("PDFPARAMAAnsi2PDFPARAMWAUtf8 Ended");
	return paramaUtf8;
}

//release PDFPARAMA Buffer
void releasePDFPARAMABuffer(PDFPARAMA* parama)
{
	DJLog("releasePDFPARAMABuffer Called");

	if (parama->mbUrl != NULL)free(parama->mbUrl); parama->mbUrl = NULL;
	if (parama->mbPdfPath != NULL)free(parama->mbPdfPath); parama->mbPdfPath = NULL;
	if (parama->mbTitle != NULL)free(parama->mbTitle); parama->mbTitle = NULL;
	if (parama->mbPageSize != NULL)free(parama->mbPageSize); parama->mbPageSize = NULL;
	if (parama->mbOrientation != NULL)free(parama->mbOrientation); parama->mbOrientation = NULL;
	if (parama->mbMarginTop != NULL)free(parama->mbMarginTop); parama->mbMarginTop = NULL;
	if (parama->mbMarginBottom != NULL)free(parama->mbMarginBottom); parama->mbMarginBottom = NULL;
	if (parama->mbMarginLeft != NULL)free(parama->mbMarginLeft); parama->mbMarginLeft = NULL;
	if (parama->mbMarginRight != NULL)free(parama->mbMarginRight); parama->mbMarginRight = NULL;
	if (parama->mbHeaderLeft != NULL)free(parama->mbHeaderLeft); parama->mbHeaderLeft = NULL;
	if (parama->mbHeaderRight != NULL)free(parama->mbHeaderRight); parama->mbHeaderRight = NULL;
	if (parama->mbHeaderCenter != NULL)free(parama->mbHeaderCenter); parama->mbHeaderCenter = NULL;
	if (parama->mbHeaderFontName != NULL)free(parama->mbHeaderFontName); parama->mbHeaderFontName = NULL;
	if (parama->mbHeaderFontSize != NULL)free(parama->mbHeaderFontSize); parama->mbHeaderFontSize = NULL;
	if (parama->mbHeaderHtml != NULL)free(parama->mbHeaderHtml); parama->mbHeaderHtml = NULL;
	if (parama->mbHeaderLine != NULL)free(parama->mbHeaderLine); parama->mbHeaderLine = NULL;
	if (parama->mbFooterLeft != NULL)free(parama->mbFooterLeft); parama->mbFooterLeft = NULL;
	if (parama->mbFooterRight != NULL)free(parama->mbFooterRight); parama->mbFooterRight = NULL;
	if (parama->mbFooterCenter != NULL)free(parama->mbFooterCenter); parama->mbFooterCenter = NULL;
	if (parama->mbFooterFontName != NULL)free(parama->mbFooterFontName); parama->mbFooterFontName = NULL;
	if (parama->mbFooterFontSize != NULL)free(parama->mbFooterFontSize); parama->mbFooterFontSize = NULL;
	if (parama->mbFooterHtml != NULL)free(parama->mbFooterHtml); parama->mbFooterHtml = NULL;
	if (parama->mbFoolterLine != NULL)free(parama->mbFoolterLine); parama->mbFoolterLine = NULL;

	DJLog("releasePDFPARAMABuffer Ended");
}