using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;

namespace BuildTool
{
    internal static class ParserBackGroundWorker
    {
        public static BackgroundWorker Create()
        {
            s_BackgroundWorker = new BackgroundWorker();
            s_BackgroundWorker.WorkerReportsProgress = true;
            s_BackgroundWorker.WorkerSupportsCancellation = true;
            return s_BackgroundWorker;
        }

        public static BackgroundWorker GetBackgroundWorker() { return s_BackgroundWorker;  }

        public static float GetProgress()
        {
            return s_CurrentProgress;
        }

        public static void ReportProgress(float progress)
        {
            s_CurrentProgress = progress * 100;

            s_BackgroundWorker.ReportProgress((int)s_CurrentProgress);
        }

        static private BackgroundWorker s_BackgroundWorker;

        static private float s_CurrentProgress = 0;
    }
}
