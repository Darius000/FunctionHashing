using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildTool
{
    internal class Struct  : Class
    {
        public Struct(string name, List<MetaData> metadata, BaseObject parent = null) : base(name, metadata, parent)
        {

        }

        public override AccessModifier GetDefaultModifer() { return AccessModifier.Public; }

        public override ObjectType GetObjectType()
        {
            return ObjectType.@struct;
        }
    }
}
