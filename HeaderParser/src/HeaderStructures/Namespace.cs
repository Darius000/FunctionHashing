using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildTool
{
    internal class Namespace : BaseObject
    {
        public Namespace(string name) : base(name, new List<MetaData> { }, AccessModifier.Public)
        {

        }

        public override ObjectType GetObjectType()
        {
            return ObjectType.@namespace;
        }

    }
}
