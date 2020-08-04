package com.djhu.utils.url2pdf.jni;

/**
 * @author      Hansen
 * @see 		PDFParam
 * 
 * 本类为url2pdf.dll的jni封装类,
 * 使用前，必须用 #UrlToPdfInit方法进行初始化
 * 使用后，必须用#UrlToPdfDeInit方法进行反初始化
 * 
 */
public class UrlToPdf4j {
	private static final String MODULE_NAME = "UrlToPdf";
	
    private static native int nativeDjhuPDFInit();
    private static native int nativeDjhuPDFDeInit();
    private static native int nativeDjhuUrlToPdf(String inhttpURL,String outPdfPath);
    private static native int nativeDjhuUrlToPdfParam(PDFParam param);
 
    static{
        try{
            System.loadLibrary(MODULE_NAME);
        }catch(UnsatisfiedLinkError e){
            //nothing to do
            System.out.println("Error: Couldn't load "+MODULE_NAME);
            System.out.println(e.getMessage());
            e.printStackTrace();
        }
    }
    
    //Init
    //初始化
    public static void UrlToPdfInit()
    {
    	nativeDjhuPDFInit();
    }
    
    /**
     * @param  inhttpURL 输入HTML的地址
     * @param  outPdfPath 输出PDF地址
     * @return 0表示成功，其余表示失败
     */
    public static int UrlToPdf(String inhttpURL,String outPdfPath)
    {
    	int ret = nativeDjhuUrlToPdf(inhttpURL, outPdfPath);
        return ret;
    }
    
    /**
     * @param  	param 转换参数
     * @return 	0表示成功，其余表示失败
     * @see 	PDFParam
     */
    public static int UrlToPdfParam(PDFParam param)
    {
    	int ret = nativeDjhuUrlToPdfParam(param);
        return ret;
    }
    
    //DeInit
    //反初始化
    public static void UrlToPdfDeInit()
    {
    	nativeDjhuPDFDeInit();
    }
}
