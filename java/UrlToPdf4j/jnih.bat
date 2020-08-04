@echo off
@set JAVA_HOME=C:\Languages\Java\JDK\jdk_x86_1.6.0_34
@set PATH=%PATH%;%JAVA_HOME%/bin
@echo on

cd bin
javah -classpath . -jni com.djhu.utils.url2pdf.jni.UrlToPdf4j
cd ..

pause