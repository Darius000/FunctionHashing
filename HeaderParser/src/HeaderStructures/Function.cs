using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildTool
{

    internal class Function : BaseObject
    {
        public string m_ReturnType;
        public Arguments m_Args;

        public Function(string name, List<MetaData> metadata, string returnType, Arguments args, AccessModifier accessModifier, BaseObject parent = null)
            : base(name, metadata, accessModifier, parent)
        {
            m_ReturnType = returnType;
            m_Args = args;
        }

        public override ObjectType GetObjectType()
        {
            return ObjectType.function;
        }
    }
}
