using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HeaderTool
{
    public class Module
    {
        public Module() 
        {
            modules = new List<string>();
        }
        public void AddPath(string path)
        {
            modules.Add(path);
        }

        public List<string> GetModules()
        {
            return modules;
        }

        private List<string> modules;
    }
}
