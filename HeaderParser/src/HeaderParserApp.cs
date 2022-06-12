using System;
using System.Windows.Forms;

namespace BuildTool
{
	class HeaderParserApp
	{
        /// <summary>
        /// main entry point for application
        /// </summary>
        /// <param name="args"></param>
        /// <returns></returns>
        [STAThread]
		static int Main(String[] args)
		{
			var progressform = new GUI.ProgressForm();

			Console.Read();
		
			return 0;
		}
	}
}
