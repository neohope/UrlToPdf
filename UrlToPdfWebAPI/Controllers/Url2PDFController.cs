using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Web.Helpers;
using System.Web.Http;
using Newtonsoft.Json;
using UrlToPdfCsTest;
using UrlToPdfWebAPI.Models;
using UrlToPdfWebAPI.Pulgins;

namespace UrlToPdfWebAPI.Controllers
{
    public class Url2PDFController : ApiController
    {
        public HttpResponseMessage Get()
        {
            Web2PDFRequest req = new Web2PDFRequest();
            req.WebURL = "webURL";
            req.HeaderPath = "headerPath";
            req.FooterPath = "footerPath";

            String jsonString = JsonConvert.SerializeObject(req);
            HttpResponseMessage result = new HttpResponseMessage { Content = new StringContent(jsonString, Encoding.GetEncoding("UTF-8"), "application/json") };
            return result;
        }

        // GET
        public HttpResponseMessage Get(String WebURL, String HeaderPath, String FooterPath)
        {
            //UrlToPdf4Web.InitUrlTOPdf4CS();
            UrlToPdf4WebExec.InitUrlTOPdf4CS();

            Web2PDFRequest req = new Web2PDFRequest();
            req.WebURL = WebURL;
            req.HeaderPath = HeaderPath;
            req.FooterPath = FooterPath;
            //Web2PDFResponse rsp = UrlToPdf4Web.UrlToPDF(req);
            Web2PDFResponse rsp = UrlToPdf4WebExec.UrlToPDF(req);
            
            String jsonString = JsonConvert.SerializeObject(rsp);
            HttpResponseMessage result = new HttpResponseMessage { Content = new StringContent(jsonString, Encoding.GetEncoding("UTF-8"), "application/json") };
            return result;
        }

        // POST
        public HttpResponseMessage Post(Web2PDFRequest req)
        {
            //UrlToPdf4Web.InitUrlTOPdf4CS();
            UrlToPdf4WebExec.InitUrlTOPdf4CS();

            //Web2PDFResponse rsp = UrlToPdf4Web.UrlToPDF(req);
            Web2PDFResponse rsp = UrlToPdf4WebExec.UrlToPDF(req);

            String jsonString = JsonConvert.SerializeObject(rsp);
            HttpResponseMessage result = new HttpResponseMessage { Content = new StringContent(jsonString, Encoding.GetEncoding("UTF-8"), "application/json") };
            return result;
        }
    }
}