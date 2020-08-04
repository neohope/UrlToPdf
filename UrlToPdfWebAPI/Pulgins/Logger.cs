//System

using System;
using System.Configuration;
using System.IO;

//=====================================================================================================================================================================
//��¼��־
//���к������Ǿ�̬����������ͨ������ֱ�ӵ���
//=====================================================================================================================================================================
namespace UrlToPdf4CS
{
	public class Logger
	{
		//=====================================================================================================================================================================
		//ϵͳ��־
		public static void LogEvent(String strUser, String strMsg)
		{
			FileStream fs = null;
			StreamWriter sw = null;
			try
			{
				//��ȡEXE�ļ�λ��
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

				//��Ϣ����
				strMsg = DateTime.Now.Hour.ToString().PadLeft(2, '0') + ":" + DateTime.Now.Minute.ToString().PadLeft(2, '0') + ":" +
					DateTime.Now.Minute.ToString().PadLeft(2, '0') + "	" + strUser + "	" + strMsg;

				//д����־
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
		//SCUͨѶ��־
		public static void LogSCUEvent(String strCalling, String strCalled, String strMsg)
		{
			FileStream fs = null;
			StreamWriter sw = null;

			try
			{
				//��ȡ��־�ļ�λ��
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

				//��¼��־
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
		//������־
		public static void LogOperationEvent(String strUser, String strOperation)
		{
			FileStream fs = null;
			StreamWriter sw = null;

			try
			{
				//��ȡ��־�ļ�λ��
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

				//��¼��־
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