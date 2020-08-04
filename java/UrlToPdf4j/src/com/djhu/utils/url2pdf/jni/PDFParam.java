package com.djhu.utils.url2pdf.jni;

/**
 * @author       Hansen
 * @see          com.djhu.utils.url2pdf.jni.UrlToPdf4j
 * 
 * 用于向UrlToPdf4j转换方法进行传参，mbUrl及mbPdfPath必填，
 * 其余参数选填，当参数为“”时，表示不进行设置
 * 
 */
public class PDFParam
{
	//=====================================================
	//Page
	//HTML输出，URL、绝对路径 或 相对路径
	public String mbUrl = "";
	
	//PDF输出路径
	public String mbPdfPath = "";
	
	//页面标题，Title
	public String mbTitle = "";
	
	//页面大小，A4、A3、B5等
	public String mbPageSize = "";
	
	//页面方向，"Landscape" 或  "Portrait"
	public String mbOrientation = "";
	
	//=====================================================
	//Margin
	//页面间距，2cm等
	public String mbMarginTop = "";
	public String mbMarginBottom = "";
	public String mbMarginLeft = "";
	public String mbMarginRight = "";
	
	//=====================================================
	//Header
	//header内容，text
	//[page] 页码
	//[topage] 页数
	public String mbHeaderLeft = "";
	public String mbHeaderRight = "";
	public String mbHeaderCenter = "";
	
	//hdeader字体及大小
	public String mbHeaderFontName = "";
	public String mbHeaderFontSize = "";
	
	//header的HTML页面
	public String mbHeaderHtml = "";

	//header与页面之间是否要分割线，true" 或   "false
	public String mbHeaderLine = "";
	
	//=====================================================
	//Footer
	//footer内容，text
	//[page]页码
	//[topage]页数
	public String mbFooterLeft = "";
	public String mbFooterRight = "";
	public String mbFooterCenter = "";
	
	//footer 字体及大小
	public String mbFooterFontName = "";
	public String mbFooterFontSize = "";
	
	//footer的HTML页面
	public String mbFooterHtml = "";
	
	//footer与页面之间是否要分割线，true" 或   "false
	public String mbFoolterLine = "";
}
