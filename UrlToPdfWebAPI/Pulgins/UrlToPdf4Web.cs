using System;
using System.Configuration;
using System.Runtime.InteropServices;
using System.Text;
using UrlToPdf4CS;
using UrlToPdfWebAPI.Models;

namespace UrlToPdfCsTest
{
    class UrlToPdf4Web
    {
        private static Boolean bInited = false;
        private static Boolean bDeInited = false;
        private static Object objLock = new Object();

        public static void InitUrlTOPdf4CS()
        {
            lock (objLock)
            {
                if (!bInited && !bDeInited)
                {
                    try
                    {
                        UrlToPdf4CS.djhuPDFLibInit();
                        bInited = true;
                    }
                    catch (Exception ex)
                    {
                        Logger.LogEvent("",ex.Message);
                    }
                }
            }
        }

        public static void DeInitUrlTOPdf4CS()
        {
            lock (objLock)
            {
                if (bInited && !bDeInited)
                {
                    UrlToPdf4CS.djhuPDFLibDeInit();
                    bDeInited = true;
                }
            }
        }

        public static Web2PDFResponse UrlToPDF(Web2PDFRequest req)
        {
            UrlToPdf4CS.PDFParamA parama = new UrlToPdf4CS.PDFParamA();
            parama.mbUrl = req.WebURL;
            parama.mbPdfPath = GetTempPDFFileName();
            parama.mbHeaderHtml = req.HeaderPath;
            parama.mbFooterHtml = req.FooterPath;

            Web2PDFResponse rsp = new Web2PDFResponse();
            rsp.PDFPath = parama.mbPdfPath;
            try
            {
                int nRet = UrlToPdf4CS.djhuUrlToPdfParamA(ref parama);
                
                if (nRet == 0)
                {
                    rsp.ErrorCode = 0;
                    rsp.ErrorInfo = "SUCCESS";
                }
                else
                {
                    rsp.ErrorCode = nRet;
                    rsp.ErrorInfo = "FAILED";
                }
            }
            catch (Exception ex)
            {
                Logger.LogEvent("", ex.Message);
            }

            return rsp;
        }

        private static Random random = new Random();
        private static String GetTempPDFFileName()
        {
            String tmpFileName = ConfigurationManager.AppSettings["TempPDFPath"];
            int nPos = tmpFileName.LastIndexOf("\\");
            if (nPos >= 0)
            {
                tmpFileName = tmpFileName.Substring(0, nPos + 1);
            }
            else
            {
                tmpFileName = tmpFileName + "\\";
            }
            tmpFileName = tmpFileName + GetTimestamp() + "." + random.Next(100) + ".PDF";
            return tmpFileName;
        }

        private static long GetTimestamp()
        {
            System.DateTime startTime = TimeZone.CurrentTimeZone.ToLocalTime(new System.DateTime(1970, 1, 1));
            return (long)(System.DateTime.Now - startTime).TotalSeconds;
        }
    }
}
