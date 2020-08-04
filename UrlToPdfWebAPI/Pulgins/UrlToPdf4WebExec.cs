using System;
using System.Collections.Generic;
using System.Configuration;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Web;
using System.Web.WebPages;
using Newtonsoft.Json;
using UrlToPdf4CS;
using UrlToPdfWebAPI.Models;

namespace UrlToPdfWebAPI.Pulgins
{
    public class UrlToPdf4WebExec
    {
        private static Boolean bInited = false;
        private static Object objLock = new Object();
        private static String exePath = "";
        private static String HeaderSpacing = ConfigurationManager.AppSettings["HeaderSpacing"];
        private static String FooterSpacing = ConfigurationManager.AppSettings["FooterSpacing"];

        public static void InitUrlTOPdf4CS()
        {
            lock (objLock)
            {
                if (!bInited)
                {
                    Assembly ass = Assembly.GetAssembly(typeof(UrlToPdf4WebExec));
                    exePath = ass.CodeBase;
                    exePath = exePath.Replace("file:///", "").Replace("UrlToPdfWebAPI.DLL", "UrlToPdf.exe");
                    Logger.LogEvent("exePath is", exePath);
                    bInited = true;
                }
            }
        }

        public static Web2PDFResponse UrlToPDF(Web2PDFRequest req)
        {
            Logger.LogEvent("UrlToPdf4WebExec.UrlToPDF called:", JsonConvert.SerializeObject(req));

            Web2PDFResponse rsp = new Web2PDFResponse();
            rsp.PDFPath = GetTempPDFFileName();
            try
            {
                System.Diagnostics.Process process = new System.Diagnostics.Process();
                ProcessStartInfo startInfo = new ProcessStartInfo();
                startInfo.FileName = exePath;

                if (!HeaderSpacing.IsEmpty())
                {
                    startInfo.Arguments += " --header-spacing " + HeaderSpacing;
                }

                if (!FooterSpacing.IsEmpty())
                {
                    startInfo.Arguments += " --footer-spacing " + FooterSpacing;
                }

                if (!req.HeaderPath.IsEmpty())
                {
                    startInfo.Arguments += " --header-html " + req.HeaderPath;
                }
                
                if(!req.FooterPath.IsEmpty())
                {
                    startInfo.Arguments += " --footer-html " + req.FooterPath;
                }

                startInfo.Arguments += " " + req.WebURL + " " + rsp.PDFPath;
                
                startInfo.CreateNoWindow = true;
                startInfo.UseShellExecute = false;
                process.StartInfo = startInfo;
                process.Start();
                Boolean bExit = process.WaitForExit(20000);

                if(bExit)
                {
                    if (process.ExitCode == 0 && File.Exists(rsp.PDFPath))
                    {
                        rsp.ErrorCode = 0;
                        rsp.ErrorInfo = "SUCCESS";
                    }
                    else
                    {
                        rsp.ErrorCode = process.ExitCode;
                        rsp.ErrorInfo = "FAILED";
                    }
                }
                else
                {
                    //超时的时候，会引发异常
                    rsp.ErrorCode = 1001;
                    rsp.ErrorInfo = "TIMEOUT";

                    //杀死进程
                    process.Kill();
                }
            }
            catch (Exception ex)
            {
                rsp.ErrorCode = -1;
                rsp.ErrorInfo = ex.Message;
                Logger.LogEvent("UrlToPdf4WebExec Error:", ex.Message);
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