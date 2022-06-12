using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildTool
{ 
    internal class Arguments
    {
        public Arguments(string[] args)
        {
            m_Args = args;
        }

        private string[] m_Args;

        public override string ToString()
        {
            return string.Join(" , ", m_Args);
        }
    }

    internal static class ArgumentHelper
    {
        /// <summary>
        /// returns a argument object that contains the list of type names
        /// </summary>
        /// <param name="line"> line to parse </param>
        /// <returns></returns>
        public static Arguments GetArgs(string line)
        {
            var meta = Utilities.StringUtilities.GetTextBetween(line, '(', ')');
            var args = meta.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);

            for (int i = 0; i < args.Length; i++)
            {
                args[i] = args[i].Trim();
                int last_space_index = args[i].LastIndexOf(' ');
                if (last_space_index != -1)
                {
                    args[i] = args[i].Substring(0, last_space_index);
                }
            }

            return new Arguments(args);
        }
    }
}
