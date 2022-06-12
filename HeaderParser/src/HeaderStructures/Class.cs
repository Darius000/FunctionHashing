using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildTool
{

    internal class Class : BaseObject
    {
        public Class(string name, List<MetaData> metadata, BaseObject parent = null) : base(name, metadata, AccessModifier.Private, parent)
        {
           
        }

        public virtual AccessModifier GetDefaultModifer() { return AccessModifier.Private;  } 

        public void AddConstructor(Constructor constructor)
        {
            constructor.Parent = this;
            StructureOutput += "\t" + constructor.ToString();
            Constructors.Add(constructor);
        }

        public void AddProperty(Property property)
        {
            property.Parent = this;

            StructureOutput += "\t" + property.ToString();
            Properties.Add(property);
        }

        public void AddFunction(Function function)
        {
            function.Parent = this;

            StructureOutput += "\t" + function.ToString();
            Methods.Add(function);
        }

        public override ObjectType GetObjectType()
        {
            return ObjectType.@class;
        }

        private string StructureOutput;

        protected List<Constructor> Constructors = new List<Constructor>();

        protected List<Property> Properties = new List<Property>();

        protected List<Function> Methods = new List<Function>();

        public override string ToString()
        {
            string ouput = "registration::class_<" + GetAbsoluteName() + ">(\"" + Name + "\")" + base.ToString();
            ouput += StructureOutput + ";\n";

            foreach(var child in ChildObjects)
            {
                ouput += child.ToString();
            }

            return ouput;
        }
    }

}
