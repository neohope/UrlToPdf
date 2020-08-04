#项目wiki地址

    http://58.247.133.187/wiki/doku.php?id=%E6%8A%80%E6%9C%AF%E6%94%AF%E6%8C%81%E7%BB%84:%E5%B9%B3%E5%8F%B0%E7%9B%B8%E5%85%B3%E4%BA%A7%E5%93%81:%E5%B9%B3%E5%8F%B0%E5%BA%94%E7%94%A8:urltopdfwebapi%E5%AE%89%E8%A3%85%E9%83%A8%E7%BD%B2%E6%89%8B%E5%86%8C

#配置说明
配置文件为Web.config

    <add key="TempPDFPath" value="D:\MyProducts\VS2013\UrlToPdf\UrlToPdfWebAPI\PDF\" />
    <add key="HeaderSpacing" value="5" />
    <add key="FooterSpacing" value="0" />

其中，TempPDFPath为临时PDF路径，HeaderSpacing表示Header与正文的间距，FooterSpacing表示Footer与正文的间距。

#请求地址
http://ip:port/api/Url2PDF

##例如：
http://192.168.140.24:8111/api/Url2PDF

#发送内容
    
    {
        "WebURL": "Web地址",
        "HeaderPath": "Header地址",
        "FooterPath": "Footer地址"
    }

##例如：

    {
        "WebURL": "http://192.168.140.24:8080/adverse-web/pdf/export/pdfview.do?eventId=375&eventResultId=null&isView=2&type=submitHistoryList",
        "HeaderPath": "http://192.168.140.24:8080/adverse-web/pngtest/logo.html",
        "FooterPath": "http://192.168.140.24:8080/adverse-web/pngtest/footer.html"
    }

#返回内容

    {
        "ErrorCode":0,
        "ErrorInfo":"SUCCESS",
        "PDFPath":"C:\\IIS\\URL2PDF\\PDF\\1461833772.18.PDF"
    }

ErrorCode为0，则文件已生成，否则生成失败。

##例如:

    {
        "ErrorCode":0,
        "ErrorInfo":"SUCCESS",
        "PDFPath":"C:\\IIS\\URL2PDF\\PDF\\1461833772.18.PDF"
    }

