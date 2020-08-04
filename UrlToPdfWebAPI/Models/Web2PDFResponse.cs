using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Newtonsoft.Json;

namespace UrlToPdfWebAPI.Models
{
    public class Web2PDFResponse
    {
        [JsonProperty]
        public int ErrorCode { get; set; }
        [JsonProperty]
        public String ErrorInfo { get; set; }
        [JsonProperty]
        public String PDFPath { get; set; }
    }
}
