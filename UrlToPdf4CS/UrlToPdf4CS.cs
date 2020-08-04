using System;
using System.Runtime.InteropServices;
using System.Text;

namespace UrlToPdfCsTest
{
    class UrlToPdf4Cs
    {
        /*
        [StructLayout(LayoutKind.Explicit,Size = 23,CharSet = CharSet.Ansi)]
        public struct PDFParamA
        {
            [FieldOffset(0)] public IntPtr mbUrl;
            [FieldOffset(4)] public IntPtr mbPdfPath;
            [FieldOffset(8)] public IntPtr mbTitle;
            [FieldOffset(12)] public IntPtr mbPageSize;
            [FieldOffset(16)] public IntPtr mbOrientation;
            [FieldOffset(20)] public IntPtr mbMarginTop;
            [FieldOffset(24)] public IntPtr mbMarginBottom;
            [FieldOffset(28)] public IntPtr mbMarginLeft;
            [FieldOffset(32)] public IntPtr mbMarginRight;
            [FieldOffset(36)] public IntPtr mbHeaderLeft;
            [FieldOffset(40)] public IntPtr mbHeaderRight;
            [FieldOffset(44)] public IntPtr mbHeaderCenter;
            [FieldOffset(48)] public IntPtr mbHeaderFontName;
            [FieldOffset(52)] public IntPtr mbHeaderFontSize;
            [FieldOffset(56)] public IntPtr mbHeaderHtml;
            [FieldOffset(60)] public IntPtr mbHeaderLine;
            [FieldOffset(64)] public IntPtr mbFooterLeft;
            [FieldOffset(68)] public IntPtr mbFooterRight;
            [FieldOffset(72)] public IntPtr mbFooterCenter;
            [FieldOffset(76)] public IntPtr mbFooterFontName;
            [FieldOffset(80)] public IntPtr mbFooterFontSize;
            [FieldOffset(84)] public IntPtr mbFooterHtml;
            [FieldOffset(88)] public IntPtr mbFoolterLine;
        }
        */

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct PDFParamA
        {
            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbUrl;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbPdfPath;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbTitle;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbPageSize;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbOrientation;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbMarginTop;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbMarginBottom;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbMarginLeft;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbMarginRight;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbHeaderLeft;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbHeaderRight;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbHeaderCenter;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbHeaderFontName;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbHeaderFontSize;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbHeaderHtml;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbHeaderLine;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbFooterLeft;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbFooterRight;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbFooterCenter;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbFooterFontName;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbFooterFontSize;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbFooterHtml;

            [MarshalAsAttribute(UnmanagedType.LPStr)]
            public string mbFoolterLine;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct PDFParamW
        {
            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbUrl;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbPdfPath;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbTitle;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbPageSize;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbOrientation;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbMarginTop;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbMarginBottom;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbMarginLeft;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbMarginRight;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbHeaderLeft;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbHeaderRight;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbHeaderCenter;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbHeaderFontName;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbHeaderFontSize;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbHeaderHtml;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbHeaderLine;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbFooterLeft;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbFooterRight;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbFooterCenter;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbFooterFontName;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbFooterFontSize;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbFooterHtml;

            [MarshalAsAttribute(UnmanagedType.LPWStr)]
            public string mbFoolterLine;
        }

        [DllImport("UrlToPdf.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern int djhuPDFLibInit();

        [DllImport("UrlToPdf.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern int djhuPDFLibDeInit();

        [DllImport("UrlToPdf.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern int djhuUrlToPdfA(string url, string pdfpath);

        [DllImport("UrlToPdf.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int djhuUrlToPdfW(string url, string pdfpath);

        [DllImport("UrlToPdf.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern int djhuUrlToPdfParamA(ref PDFParamA parma);

        [DllImport("UrlToPdf.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int djhuUrlToParamW(IntPtr paramw);
    }
}
