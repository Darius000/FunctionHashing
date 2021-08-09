using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HeaderTool.src
{
    class CheckExtension
    {
        public CheckExtension()
        {

        }

        public bool IsValidExtension(string file)
        {
            int dotpos = file.LastIndexOf('.');

            if (dotpos == -1) return false;

            int length = file.Length;
            int offset = length - dotpos;
            string ext = file.Substring(dotpos, offset);
            if(exts.Contains(ext))
            {
                return true;
            }

            return false;
        }

        private string[] exts = { ".h"};
    }
}
