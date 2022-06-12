using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildTool
{
    internal class Property : BaseObject
    {
        public string m_Type;

        public Property(string name, List<MetaData> metadata, string type, AccessModifier accessModifier, BaseObject parent = null) 
            : base(name, metadata, accessModifier, parent)
        {
            m_Type = type;
        }

        public override string ToString()
        {
            return ".property(\"" + Name + "\" , &" + Parent.GetAbsoluteName() + "::" + Name + ", registration::" + AccessorStringList[AccessModifier_] + ")" + base.ToString();
        }

        public override ObjectType GetObjectType()
        {
            return ObjectType.property;
        }
    }
}
