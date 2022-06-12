using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildTool
{
    internal struct MetaData
    {
        public MetaData(string key, string value, string specifier)
        {
            Key = key;
            Value = value.Trim();
            Specifier = string.IsNullOrEmpty(specifier) ? "" : specifier + "::";
        }

        public string Key { get; private set; } = "";
        public string Value { get; private set; } = "";

        public string Specifier { get; private set; } = "";

        public override string ToString()
        {
            if(!string.IsNullOrEmpty(Key) && !string.IsNullOrEmpty(Value))
            {
                return "metadata(" + Specifier + Key + " , " + Value + ")";
            }

            return "";
        }

    }

    internal static class MetaDataHelper
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="line">line to parse</param>
        /// <param name="prefix"> used to append to key of meta data, ex EnumClassName::Key</param>
        /// <returns></returns>
        public static List<MetaData> GetMetaData(string line, string prefix)
        {
            List<MetaData> list = new List<MetaData>(0);


            var meta = Utilities.StringUtilities.GetTextBetween(line, '(', ')');
            var data = !string.IsNullOrEmpty(meta) ? meta.Split(',') : new string[0];

            foreach (var item in data)
            {

                if (item.Contains("="))
                {
                    var items = item.Split('=');
                    var key = items[0].Trim();
                    var value = items[1];
                    list.Add(new MetaData(key, value, prefix));
                }
                else
                {
                    list.Add(new MetaData(item.Trim(), "", prefix));
                }
            }

            return list;
        }
    }

}
