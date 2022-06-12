using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildTool
{
    internal class Constructor : BaseObject
    {
        public Arguments m_Args;

        public Constructor(string name, List<MetaData> metadata, Arguments args,
            AccessModifier accessModifier, BaseObject parent = null) :
            base(name, metadata, accessModifier, parent)
        {
            m_Args = args;
        }

        public override string ToString()
        {

            return ".constructor<" + m_Args.ToString() + ">(registration::" + AccessorStringList[AccessModifier_] + ")(policy::ctor::as_raw_ptr)" + base.ToString();
        }
    }
}
