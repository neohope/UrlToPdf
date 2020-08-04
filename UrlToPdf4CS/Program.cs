using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace UrlToPdfCsTest
{
    class Program
    {
        static void Main(string[] args)
        {
            //testMultifiles();
            //testParam();

            if (args.Length < 2)
            {
                Console.WriteLine("usage: UrlToPdf4CS URL PDF");
                return;
            }
            UrlToPdf4Cs.djhuPDFLibInit();
            UrlToPdf4Cs.djhuUrlToPdfA(args[0], args[1]);
            UrlToPdf4Cs.djhuPDFLibDeInit();
        }

        static void testMultifiles()
        {
            UrlToPdf4Cs.djhuPDFLibInit();
            //UrlToPdf4Cs.djhuUrlToPdfA("1.htm", "1.pdf");
            //UrlToPdf4Cs.djhuUrlToPdfA("2.htm", "2.pdf");
            //UrlToPdf4Cs.djhuUrlToPdfA("3.htm", "3.pdf");
            UrlToPdf4Cs.djhuPDFLibDeInit();
        }

        static void testParam()
        {
            UrlToPdf4Cs.djhuPDFLibInit();
            UrlToPdf4Cs.PDFParamA parama = new UrlToPdf4Cs.PDFParamA();
            Console.In.ReadLine();

            parama.mbUrl = ("http://www.baidu.com");
            parama.mbHeaderLeft = ("Test不良事件ABC");
            parama.mbHeaderFontName = ("宋体");
            parama.mbFooterFontSize = ("24");
            parama.mbFooterRight = ("[page]/[topage]");
            parama.mbHeaderLine = ("true");
            parama.mbFooterFontSize = ("12");
            parama.mbPdfPath = ((@"D:\MyProducts\VS2013\UrlToPdf\Debug\Baidu.pdf"));
            UrlToPdf4Cs.djhuUrlToPdfParamA(ref parama);

            /*
            parama.mbUrl = Marshal.StringToHGlobalUni("http://www.baidu.com");
            parama.mbHeaderLeft =  Marshal.StringToHGlobalUni("Test不良事件ABC");
            parama.mbHeaderFontName =  Marshal.StringToHGlobalUni("宋体");
            parama.mbFooterFontSize =  Marshal.StringToHGlobalUni("24");
            parama.mbFooterRight =  Marshal.StringToHGlobalUni("[page]/[topage]");
            parama.mbHeaderLine =  Marshal.StringToHGlobalUni("true");
            parama.mbFooterFontSize =  Marshal.StringToHGlobalUni("12");
            parama.mbPdfPath = Marshal.StringToHGlobalUni((@"D:\MyProducts\VS2013\UrlToPdf\Debug\Baidu.pdf"));

            UrlToPdf4Cs.djhuUrlToPdfParamA(ref parama);

            if (parama.mbUrl != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbUrl);
            if (parama.mbPdfPath != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbPdfPath);
            if (parama.mbTitle != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbTitle);
            if (parama.mbPageSize != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbPageSize);
            if (parama.mbOrientation != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbOrientation);
            if (parama.mbMarginTop != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbMarginTop);
            if (parama.mbMarginBottom != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbMarginBottom);
            if (parama.mbMarginLeft != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbMarginLeft);
            if (parama.mbMarginRight != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbMarginRight);
            if (parama.mbHeaderLeft != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbHeaderLeft);
            if (parama.mbHeaderRight != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbHeaderRight);
            if (parama.mbHeaderCenter != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbHeaderCenter);
            if (parama.mbHeaderFontName != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbHeaderFontName);
            if (parama.mbHeaderFontSize != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbHeaderFontSize);
            if (parama.mbHeaderHtml != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbHeaderHtml);
            if (parama.mbHeaderLine != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbHeaderLine);
            if (parama.mbFooterLeft != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbFooterLeft);
            if (parama.mbFooterRight != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbFooterRight);
            if (parama.mbFooterCenter != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbFooterCenter);
            if (parama.mbFooterFontName != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbFooterFontName);
            if (parama.mbFooterFontSize != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbFooterFontSize);
            if (parama.mbFooterHtml != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbFooterHtml);
            if (parama.mbFoolterLine != IntPtr.Zero) Marshal.FreeHGlobal(parama.mbFoolterLine);
            */

            UrlToPdf4Cs.djhuPDFLibDeInit();
        }
    }
}
