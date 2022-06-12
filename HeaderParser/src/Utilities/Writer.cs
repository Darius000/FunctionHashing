using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace BuildTool
{
    internal class Writer
    {
        public static void WriteTo(string filename, string content)
        {
            File.AppendAllText(filename, content);
        }
    }
}
