package com.djhu.utils.url2pdf.jni;

/**
 * @author      Hansen
 * @see 		PDFParam
 * 
 * ����Ϊurl2pdf.dll��jni��װ��,
 * ʹ��ǰ�������� #UrlToPdfInit�������г�ʼ��
 * ʹ�ú󣬱�����#UrlToPdfDeInit�������з���ʼ��
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
    //��ʼ��
    public static void UrlToPdfInit()
    {
    	nativeDjhuPDFInit();
    }
    
    /**
     * @param  inhttpURL ����HTML�ĵ�ַ
     * @param  outPdfPath ���PDF��ַ
     * @return 0��ʾ�ɹ��������ʾʧ��
     */
    public static int UrlToPdf(String inhttpURL,String outPdfPath)
    {
    	int ret = nativeDjhuUrlToPdf(inhttpURL, outPdfPath);
        return ret;
    }
    
    /**
     * @param  	param ת������
     * @return 	0��ʾ�ɹ��������ʾʧ��
     * @see 	PDFParam
     */
    public static int UrlToPdfParam(PDFParam param)
    {
    	int ret = nativeDjhuUrlToPdfParam(param);
        return ret;
    }
    
    //DeInit
    //����ʼ��
    public static void UrlToPdfDeInit()
    {
    	nativeDjhuPDFDeInit();
    }
}
