using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace BuildTool.Log
{
    public class DebugEventArgs : EventArgs
    {
        public string m_Message { get; set; }
    }

    internal class ParserTraceListener : TraceListener
    {
        public event EventHandler<DebugEventArgs> OnWrite;

        public delegate void OnWriteLine(string message);

        public override void Write(string message)
        {
            DebugEventArgs args = new DebugEventArgs();
            args.m_Message = message;
            OnWriteEvent(args);
        }

        public override void WriteLine(string message)
        {
            DebugEventArgs args = new DebugEventArgs();
            args.m_Message = message;
            OnWriteEvent(args);
        }

        protected virtual void OnWriteEvent(DebugEventArgs e)
        {
            var handler = OnWrite;

            if(handler != null)
            {
                handler(this, e);
                
            }
        }
    }
}
