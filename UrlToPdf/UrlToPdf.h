//Hansen 2014-05-05
//Covert Url to Pdf using wkhtmltopdf(chrome kernel)
//Good for Html+Css
//Bad for IE ActiveX controls

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_PATH_LEGTH_IN_CHAR (1023)

	//Parameters
	typedef struct pdfparama {
		//page
		char* mbUrl;
		char* mbPdfPath;
		char* mbTitle;
		char* mbPageSize;
		char* mbOrientation;

		//margin
		char* mbMarginTop;
		char* mbMarginBottom;
		char* mbMarginLeft;
		char* mbMarginRight;

		//header
		char* mbHeaderLeft;
		char* mbHeaderRight;
		char* mbHeaderCenter;
		char* mbHeaderFontName;
		char* mbHeaderFontSize;
		char* mbHeaderHtml;
		char* mbHeaderLine;

		//footer
		char* mbFooterLeft;
		char* mbFooterRight;
		char* mbFooterCenter;
		char* mbFooterFontName;
		char* mbFooterFontSize;
		char* mbFooterHtml;
		char* mbFoolterLine;

	} PDFPARAMA;

	//Parameters
	typedef struct pdfparamw {
		//page
		wchar_t* mbUrl;
		wchar_t* mbPdfPath;
		wchar_t* mbTitle;
		wchar_t* mbPageSize;
		wchar_t* mbOrientation;

		//margin
		wchar_t* mbMarginTop;
		wchar_t* mbMarginBottom;
		wchar_t* mbMarginLeft;
		wchar_t* mbMarginRight;

		//header
		wchar_t* mbHeaderLeft;
		wchar_t* mbHeaderRight;
		wchar_t* mbHeaderCenter;
		wchar_t* mbHeaderFontName;
		wchar_t* mbHeaderFontSize;
		wchar_t* mbHeaderHtml;
		wchar_t* mbHeaderLine;

		//footer
		wchar_t* mbFooterLeft;
		wchar_t* mbFooterRight;
		wchar_t* mbFooterCenter;
		wchar_t* mbFooterFontName;
		wchar_t* mbFooterFontSize;
		wchar_t* mbFooterHtml;
		wchar_t* mbFoolterLine;
	} PDFPARAMW;

//release PDFPARAMA buffer
void releasePDFPARAMABuffer(PDFPARAMA* parama);

//Init
int djhuPDFLibInit();

//DeInit
int djhuPDFLibDeInit();

//Covert Url to Pdf
//ANSI vsersion 
int djhuUrlToPdfA(const char* url, const char* pdfpath);
//Covert Url to Pdf by Params
//ANSI vsersion 
int djhuUrlToPdfParamA(const PDFPARAMA* parama);

//Covert Url to Pdf
//Unicode version
//just convert the parameters to char* and invoke the ANSI vsersion
int djhuUrlToPdfW(const wchar_t* url, const wchar_t* pdfpath);
//Covert Url to Pdf by Params
//Unicode version
//just convert the parameters to char* and invoke the ANSI vsersion
int djhuUrlToPdfParamW(const PDFPARAMW* paramw);

#ifdef _UNICODE
#define djhuUrlToPdf	djhuUrlToPdfW
#define djhuUrlToPdfParam	djhuUrlToPdfParamW
#else
#define djhuUrlToPdf	djhuUrlToPdfA
#define djhuUrlToPdfParam	djhuUrlToPdfParamA
#endif

#define DJHU_URLTOPDF_OK (0)

#ifdef __cplusplus
}
#endif