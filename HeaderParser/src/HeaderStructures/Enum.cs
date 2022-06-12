using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildTool
{
    internal class EnumValue : BaseObject
    {
        public EnumValue(string name) : base(name, new List<MetaData> { }, AccessModifier.Public, null)
        {
           
        }


        public override string ToString()
        {
            return "value(\"" + Name + "\" , " + GetAbsoluteName() + ")";
        }
    }

    internal class Enum : BaseObject
    {
        public Enum(string name , List<EnumValue> values, BaseObject parent = null) : base(name, new List<MetaData> { }, AccessModifier.Public, parent)
        {
            Values = values;
            Name = name;

            foreach (EnumValue v in values)
            {
                AddChild(v);
            }

            CacheListToString(values);

            
        }

        public override ObjectType GetObjectType()
        {
            return ObjectType.@enum;
        }

        private void CacheListToString(List<EnumValue> values)
        {
            for (int i = 0; i < values.Count; i++)
            {
                ValueOutput += "\t\t" + values[i].ToString();

                if (i != values.Count - 1)
                {
                    ValueOutput += ",\n";
                }
                else
                {
                    ValueOutput += "\n";
                }
            }
        }

        private List<EnumValue> Values { get; set; }

        private string ValueOutput = "";

        public override string ToString()
        {
            return "registration::enumeration<" + GetAbsoluteName() + ">(\"" + GetAbsoluteName() + "\")\n" +
                "\t(\n" + ValueOutput  + "\t);\n";
        }
    }
}
