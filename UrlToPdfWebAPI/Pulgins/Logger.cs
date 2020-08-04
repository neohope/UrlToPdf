//System

using System;
using System.Configuration;
using System.IO;

//=====================================================================================================================================================================
//记录日志
//所有函数都是静态函数，可以通过类名直接调用
//=====================================================================================================================================================================
namespace UrlToPdf4CS
{
	public class Logger
	{
		//=====================================================================================================================================================================
		//系统日志
		public static void LogEvent(String strUser, String strMsg)
		{
			FileStream fs = null;
			StreamWriter sw = null;
			try
			{
				//获取EXE文件位置
				String strLog = ConfigurationManager.AppSettings["TempPDFPath"];
				int nPos = strLog.LastIndexOf("\\");
				if (nPos >= 0)
				{
					strLog = strLog.Substring(0, nPos + 1);
				}
				else
				{
					strLog = strLog + "\\";
				}

				strLog += "Log";
				if (Directory.Exists(strLog) == false)
				{
					Directory.CreateDirectory(strLog);
				}

				strLog += "\\" + DateTime.Now.Year.ToString().PadLeft(4, '0') + DateTime.Now.Month.ToString().PadLeft(2, '0') + DateTime.Now.Day.ToString().PadLeft(2, '0');
				if (Directory.Exists(strLog) == false)
				{
					Directory.CreateDirectory(strLog);
				}

				strLog += "\\Event.log";

				//消息内容
				strMsg = DateTime.Now.Hour.ToString().PadLeft(2, '0') + ":" + DateTime.Now.Minute.ToString().PadLeft(2, '0') + ":" +
					DateTime.Now.Minute.ToString().PadLeft(2, '0') + "	" + strUser + "	" + strMsg;

				//写入日志
				if (File.Exists(strLog) == false)
				{
					fs = new FileStream(strLog, FileMode.Create);
				}
				else
				{
					fs = new FileStream(strLog, FileMode.Append);
				}

				sw = new StreamWriter(fs);
				sw.WriteLine(strMsg);
				sw.Flush();
			}
			catch
			{
			}
			finally
			{
				if (sw != null) sw.Close();
				if (fs != null) fs.Close();
			}
		}

		//=====================================================================================================================================================================
		//SCU通讯日志
		public static void LogSCUEvent(String strCalling, String strCalled, String strMsg)
		{
			FileStream fs = null;
			StreamWriter sw = null;

			try
			{
				//获取日志文件位置
				String strLog = System.Reflection.Assembly.GetExecutingAssembly().Location;
				int nPos = strLog.LastIndexOf("\\");
				if (nPos >= 0)
				{
					strLog = strLog.Substring(0, nPos + 1);
				}
				else
				{
					strLog = strLog + "\\";
				}

				strLog += "Log";
				if (Directory.Exists(strLog) == false)
				{
					Directory.CreateDirectory(strLog);
				}

				strLog += "\\" + DateTime.Now.Year.ToString().PadLeft(4, '0') + DateTime.Now.Month.ToString().PadLeft(2, '0') + DateTime.Now.Day.ToString().PadLeft(2, '0');
				if (Directory.Exists(strLog) == false)
				{
					Directory.CreateDirectory(strLog);
				}

				strLog += "\\SCU.log";

				strMsg = DateTime.Now.Hour.ToString().PadLeft(2, '0') + ":" + DateTime.Now.Minute.ToString().PadLeft(2, '0') + ":" +
					DateTime.Now.Minute.ToString().PadLeft(2, '0') + "	" + strCalling + "	" + strCalled + "	" + strMsg;

				//记录日志
				if (File.Exists(strLog) == false)
				{
					fs = new FileStream(strLog, FileMode.Create);
				}
				else
				{
					fs = new FileStream(strLog, FileMode.Append);
				}
				sw = new StreamWriter(fs);
				sw.WriteLine(strMsg);
				sw.Flush();
			}
			catch
			{
			}
			finally
			{
				if (sw != null) sw.Close();
				if (fs != null) fs.Close();
			}

		}

		//=====================================================================================================================================================================
		//操作日志
		public static void LogOperationEvent(String strUser, String strOperation)
		{
			FileStream fs = null;
			StreamWriter sw = null;

			try
			{
				//获取日志文件位置
				String strLog = System.Reflection.Assembly.GetExecutingAssembly().Location;
				int nPos = strLog.LastIndexOf("\\");
				if (nPos >= 0)
				{
					strLog = strLog.Substring(0, nPos + 1);
				}
				else
				{
					strLog = strLog + "\\";
				}

				strLog += "Log";
				if (Directory.Exists(strLog) == false)
				{
					Directory.CreateDirectory(strLog);
				}

				strLog += "\\" + DateTime.Now.Year.ToString().PadLeft(4, '0') + DateTime.Now.Month.ToString().PadLeft(2, '0') + DateTime.Now.Day.ToString().PadLeft(2, '0');
				if (Directory.Exists(strLog) == false)
				{
					Directory.CreateDirectory(strLog);
				}

				strLog += "\\Operation.log";

				strOperation = DateTime.Now.Hour.ToString().PadLeft(2, '0') + ":" + DateTime.Now.Minute.ToString().PadLeft(2, '0') + ":" +
					DateTime.Now.Minute.ToString().PadLeft(2, '0') + "	" + strUser + "	" + strOperation;

				//记录日志
				if (File.Exists(strLog) == false)
				{
					fs = new FileStream(strLog, FileMode.Create);
				}
				else
				{
					fs = new FileStream(strLog, FileMode.Append);
				}
				sw = new StreamWriter(fs);
				sw.WriteLine(strOperation);
				sw.Flush();
			}
			catch
			{
			}
			finally
			{
				if (sw != null) sw.Close();
				if (fs != null) fs.Close();
			}
		}
	}
}