package com.djhu.utils.url2pdf.jni;

/**
 * @author       Hansen
 * @see          com.djhu.utils.url2pdf.jni.UrlToPdf4j
 * 
 * ������UrlToPdf4jת���������д��Σ�mbUrl��mbPdfPath���
 * �������ѡ�������Ϊ����ʱ����ʾ����������
 * 
 */
public class PDFParam
{
	//=====================================================
	//Page
	//HTML�����URL������·�� �� ���·��
	public String mbUrl = "";
	
	//PDF���·��
	public String mbPdfPath = "";
	
	//ҳ����⣬Title
	public String mbTitle = "";
	
	//ҳ���С��A4��A3��B5��
	public String mbPageSize = "";
	
	//ҳ�淽��"Landscape" ��  "Portrait"
	public String mbOrientation = "";
	
	//=====================================================
	//Margin
	//ҳ���࣬2cm��
	public String mbMarginTop = "";
	public String mbMarginBottom = "";
	public String mbMarginLeft = "";
	public String mbMarginRight = "";
	
	//=====================================================
	//Header
	//header���ݣ�text
	//[page] ҳ��
	//[topage] ҳ��
	public String mbHeaderLeft = "";
	public String mbHeaderRight = "";
	public String mbHeaderCenter = "";
	
	//hdeader���弰��С
	public String mbHeaderFontName = "";
	public String mbHeaderFontSize = "";
	
	//header��HTMLҳ��
	public String mbHeaderHtml = "";

	//header��ҳ��֮���Ƿ�Ҫ�ָ��ߣ�true" ��   "false
	public String mbHeaderLine = "";
	
	//=====================================================
	//Footer
	//footer���ݣ�text
	//[page]ҳ��
	//[topage]ҳ��
	public String mbFooterLeft = "";
	public String mbFooterRight = "";
	public String mbFooterCenter = "";
	
	//footer ���弰��С
	public String mbFooterFontName = "";
	public String mbFooterFontSize = "";
	
	//footer��HTMLҳ��
	public String mbFooterHtml = "";
	
	//footer��ҳ��֮���Ƿ�Ҫ�ָ��ߣ�true" ��   "false
	public String mbFoolterLine = "";
}
