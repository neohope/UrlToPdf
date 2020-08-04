using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Newtonsoft.Json;

namespace UrlToPdfWebAPI.Models
{
    public class Web2PDFRequest
    {
        [JsonProperty]
        public String WebURL { get; set; }
        [JsonProperty]
        public String HeaderPath { get; set; }
        [JsonProperty]
        public String FooterPath { get; set; }
    }
}