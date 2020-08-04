#功能
本工程，是对wkhtmltopdf进行了再次封装，封装语言为c、c#、java。其底层原理为利用Chrome内核对网页进行渲染，然后转换为PDF。

当前wkhtmltox版本为201604013的master，然后打了字符集的补丁，VS2013 MT编译。

#约定
- 编译时，要么所有项目都使用Multi-Byte字符集，要么都使用Unicode字符集，不允许重叠
- dll本身已经对字符集（ANSI/Unicode）做了兼容处理
- 用MD/MDd选项编译本项目，不要使用MT/MTd
- 为保证兼容性，尽量用c语法，而不是c++语法
- 为保证兼容性，用VS2013进行编译
- 一定不可以把Debug版本，发给其他人用，尤其是JNI

#如何调试
- 调试UrlToPdf.dll、UrlToPdfTest.exe、UrlToPdfCsTest.exe，直接用VS调试就好了
- 调试UrlToPdf4j，直接用ecplise调试该项目就好了，但dll必须是Release版本的才可以
- 调试jni调用UrlToPdf.dll的话，需要用附加到java.exe进程的方法，但dll必须是Release版本的才可以

#使用方法说明
- 一定要包含着两个dll：UrlToPdf.dll wkhtmltox.dll
- c直接使用UrlToPdf.h头文件及UrlToPdf.lib进行链接
- c#，直接使用UrlToPdf4CS.cs
- java，使用UrlToPdf4j.java，并需要用jvm参数-Djava.library.path指定dll路径，JVM与dll位数必须一致

#注意事项
- EXE、DLL、JVM位数必须一致
- JNI不可以调用Debug版本的DLL
- 非IE核心，不兼容ActiveX控件

#问题排查
- 如果UrlToPdfTest.exe测试程序无法运行，需要安装VS2013的vcredist.msi
- 如果UrlToPdfCsTest.exe测试程序无法运行，需要安装.netFramework4.0
- 如果java测试程序无法运行，确认你可以在CMD下执行Java，并且JVM与DLL的位数是一样的，并且UrlToPdfTest.exe可以运行

#已知问题
- 发现JNI版本，用于Tomcat时，很不稳定。在我的电脑上，发现只有apache-tomcat-6.0.35会比较稳定，但其他电脑上感觉很不稳定。
- 同样的C#版本，用于IIS时，也不是很稳定
- 虽然采用了Chrome内核，但网页渲染结果与Chrome有一定区别，可以尝试修改css布局
- PDF文件乱码时，尝试将文件另存为utf-8格式，可以解决部分问题（是文件编码，不是HTML编码！）

#TO DO
- 暂无
