#include <tchar.h>
#include <iostream>
#include "../UrlToPdf/UrlToPdf.h"

#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib,"../x64/Debug/UrlToPdf.lib")
#else
#pragma comment(lib,"../x64/Release/UrlToPdf.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib,"../Win32/Debug/UrlToPdf.lib")
#else
#pragma comment(lib,"../Win32/Release/UrlToPdf.lib")
#endif
#endif



void testURL2PDF ()
{
	djhuPDFLibInit();

	//ANSI
	/*
	char buff[1024];
	for (int i = 0; i < 100;i++)
	{
		memset(buff,0x00,1024);
		sprintf_s(buff, 1024, "D:\\MyProducts\\VS2013\\UrlToPdf\\Debug\\png%d.pdf", i);
		djhuUrlToPdfA("D:\\MyProducts\\VS2013\\UrlToPdf\\test\\pngtest\\logo.html", buff);
	}
	*/
	
	//djhuUrlToPdfA("D:\\MyProducts\\VS2013\\UrlToPdf\\test\\1.html", "D:\\MyProducts\\VS2013\\UrlToPdf\\test\\baidu.pdf");
	//djhuUrlToPdfA("http://baidu.com", "D:\\MyProducts\\VS2013\\UrlToPdf\\Debug\\testA.pdf");
	//djhuUrlToPdfA("D:\\MyProducts\\VS2013\\UrlToPdf\\test\\1.html", "testd.pdf");
	//djhuUrlToPdfA("D:\\MyProducts\\VS2013\\UrlToPdf\\test\\1.html", "D:\\MyProducts\\VS2013\\UrlToPdf\\myA.pdf");
	//djhuUrlToPdfA("D:\\MyProducts\\VS2013\\UrlToPdf\\test\\1.html", "\"D:\\MyProducts\\VS2013\\UrlToPdf\\Debug\\testA.pdf\"");
	//djhuUrlToPdfA("http://baidu.com", "'D:\\MyProducts\\VS2013\\UrlToPdf\\Debug\\testA.pdf'");
	//djhuUrlToPdfA("http://baidu.com", "file:///D:/MyProducts/VS2013/UrlToPdf/Debug/testB.pdf");
	//djhuUrlToPdfA("http://baidu.com", "testC.pdf");
	//djhuUrlToPdfA("http://qq.com", "-");
	//djhuUrlToPdfA("http://neohope.com", "testA.pdf");

	//UNICODE
	//djhuUrlToPdfW(L"file:///D:/DiskE/ForHansen/Downloads/A/A.htm", L"testU.pdf");


	djhuUrlToPdfA("http://docs.spring.io/spring/docs/5.0.0.BUILD-SNAPSHOT/spring-framework-reference/htmlsingle", "D:\\MyProducts\\VS2013\\UrlToPdf\\Spring.pdf");
	djhuPDFLibDeInit();
}

//无法一次生成多个pdf文件测试
void testMultifiles()
{
	djhuPDFLibInit();
	djhuUrlToPdfA("D:\\MyProducts\\VS2013\\UrlToPdf\\test\\pngtest\\logo.html", "D:\\MyProducts\\VS2013\\UrlToPdf\\Debug\\png.pdf");
	//djhuUrlToPdfA("D:\\MyProducts\\VS2013\\UrlToPdf\\Debug\\1.html", "D:\\MyProducts\\VS2013\\Projects\\UrlToPdf\\Debug\\1.pdf");
	//djhuUrlToPdfA("D:\\MyProducts\\VS2013\\UrlToPdf\\Debug\\2.htm", "2.pdf");
	//djhuUrlToPdfA("D:\\MyProducts\\VS2013\\UrlToPdf\\Debug\\3.htm", "3.pdf");
	djhuPDFLibDeInit();
}

//传参生成pdf文件测试
void testParam()
{
	djhuPDFLibInit();

	PDFPARAMA parama;
	//parama.mbUrl = "http://www.baidu.com";
	//parama.mbPdfPath = "D:\\MyProducts\\VS2013\\UrlToPdf\\test\\baidu.pdf";
	//parama.mbUrl = "D:\\MyProducts\\VS2013\\UrlToPdf\\test\\headerfooter\\body.html";
	//parama.mbPdfPath = "D:\\MyProducts\\VS2013\\UrlToPdf\\test\\testHF.pdf";
	parama.mbUrl = "1.html";
	parama.mbPdfPath = "1.pdf";
	parama.mbTitle = "";
	parama.mbPageSize = "";
	parama.mbOrientation = "";

	parama.mbMarginTop = "";
	parama.mbMarginBottom = "";
	parama.mbMarginLeft = "";
	parama.mbMarginRight = "";

	//parama.mbHeaderLeft = "不良事件";
	//parama.mbHeaderLeft = "Test%E4%B8%8D%E8%89%AF%E4%BA%8B%E4%BB%B6";
	parama.mbHeaderLeft = "";
	parama.mbHeaderRight = "";
	parama.mbHeaderCenter = "";
	parama.mbHeaderFontName = "";
	parama.mbHeaderFontSize = "";
	parama.mbHeaderHtml = "";
	//parama.mbHeaderHtml = "D:\\MyProducts\\VS2013\\UrlToPdf\\test\\headerfooter\\header.html";
	parama.mbHeaderLine = "";

	parama.mbFooterLeft = "";
	parama.mbFooterRight = "";
	parama.mbFooterCenter = "";
	parama.mbFooterFontName = "";
	parama.mbFooterFontSize = "";
	parama.mbFooterHtml = "";
	//parama.mbFooterHtml = "D:\\MyProducts\\VS2013\\UrlToPdf\\test\\headerfooter\\footer.html";
	parama.mbFoolterLine = "";

	djhuUrlToPdfParamA(&parama);

	djhuPDFLibDeInit();
}

int _tmain(int argc, TCHAR** argv)
{
	//testParam();
	//testMultifiles();
	testURL2PDF();

	//参数示例
	//file:///D:/DiskE/ForHansen/Downloads/A/A.htm cpp.pdf

	if (argc < 3)
	{
		std::cout << "usage: UrlToPdfTest URL PDF" << std::endl;
		return 0;
	}
	djhuPDFLibInit();
	djhuUrlToPdf(argv[1], argv[2]);
	djhuPDFLibDeInit();

	return 0;
}