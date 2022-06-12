using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
using System.Diagnostics;
using System.ComponentModel;
using System.Reflection;
using System.Threading;

namespace BuildTool.GUI
{
    internal class ProgressForm
    {
        public ProgressForm()
        {
            InitializeWorker();
        }

        private void InitializeWorker()
        {

            var backgroundworker = ParserBackGroundWorker.Create();
            backgroundworker.DoWork += BackgroundWorker_DoWork;
            backgroundworker.ProgressChanged += BackgroundWorker_ProgressChanged;
            backgroundworker.RunWorkerCompleted += BackgroundWorker_RunWorkerCompleted;

            backgroundworker.RunWorkerAsync();
        }

        private void BackgroundWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            Console.WriteLine("Completed");
        }

        private void BackgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            Console.WriteLine("Started Parsing...");

            var modules = GetModules();

            Utilities.ModuleParser.Parse(modules);

        }

        private void BackgroundWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            Console.WriteLine("{0}%", e.ProgressPercentage);
        }


        private void OnWrite(object sender, Log.DebugEventArgs e)
        {
            Console.WriteLine(e.m_Message);
        }


        private List<Module> GetModules()
        {
            List<Module> modules = new List<Module>();

            Assembly asm = typeof(Module).Assembly;
            foreach (Type type in asm.GetTypes())
            {
                if (type.IsSubclassOf(typeof(Module)))
                {
                    Module module = (Module)Activator.CreateInstance(type);
                    modules.Add(module);
                }
            }

            return modules;
        }
    }
}
