using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace BuildTool
{
    namespace Utilities
    {
        static internal class StringUtilities
        {
            private static readonly Regex sWhiteSpace = new Regex(@"\s+");

            public static string ReplaceWhiteSpace(string input, string replacement)
            {
                return sWhiteSpace.Replace(input, replacement);
            }

            public static bool Maches(string s, string matchtofind)
            {
                return Regex.IsMatch(s, matchtofind);
            }

            public static string GetTextBetween(string s, char a, char b)
            {
                var firstParenthesis = s.IndexOf(a);
                var lastParenthesis = s.LastIndexOf(b);

                if (firstParenthesis == -1 || lastParenthesis == -1) return "";

                return s.Substring(firstParenthesis + 1, lastParenthesis - 1 - firstParenthesis);
            }

            /// <summary>
            /// finds a string within the keyword and seperator
            /// </summary>
            /// <param name="line"> line to parse</param>
            /// <param name="start"> string to find at beginning</param>
            /// <param name="end">string to find at end</param>
            /// <returns></returns>
            public static string GetName(string line, string[] start, string end)
            {
                var newline = line.Replace("\t", "");
                var keyword_length = 0;

                var keyword     = newline.IndexOfAny(ref keyword_length, start);
                var accessor    = newline.IndexOf(end);
                var length      = newline.Length - (accessor != -1 ? accessor : keyword_length);
                var name        = newline.Substring(keyword + keyword_length, length).Trim();

                return name ;
            }

            public static string GetName(string line, string start, string end)
            {
                var newline = line.Replace("\t", "");
                var keyword_length = start.Length;

                var keyword = newline.IndexOf(start);
                var accessor = newline.IndexOf(end);
                var length = newline.Length - (accessor != -1 ? accessor : keyword_length);
                var name = newline.Substring(keyword + keyword_length, length).Trim();

                return name;
            }

            public static int GetStringlength(string[] s)
            {
                int length = 0;

                foreach(var item in s)
                {
                    length += item.Length;
                }

                return length;
            }

            public static int IndexOfAny(this string value, ref int length, params string[] targets)
            {
                var index = -1;
                if (targets == null || targets.Length == 0) return index;

                foreach(var target in targets)
                {
                    var targetIndex = value.IndexOf(target, 0 , index > -1 ? index + target.Length - 1 : value.Length);

                    if(targetIndex >= 0 && (index == -1 || targetIndex < index))
                    {
                        index = targetIndex;
                        if(index == 0)
                        {
                            length = target.Length;
                            break;
                        }
                    }
                }

                return index;
            }


        }
    }
}
