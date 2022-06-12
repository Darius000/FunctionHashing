using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildTool
{
    public enum ObjectType
    {
        none,
        @namespace,
        @class,
        @struct,
        property,
        function,
        @enum
    }

    internal interface IObject
    {
        public abstract ObjectType GetObjectType();
    }


    internal class BaseObject : IObject
    {
        public BaseObject(string name, List<MetaData> metadata, AccessModifier accessModifier, BaseObject parent = null)
        {
            Name = name;
            MetaData = metadata;
            AccessModifier_ = accessModifier;
            Parent = parent;
        }

        public virtual ObjectType GetObjectType() { return ObjectType.none; }
 
        public void AddChild(BaseObject child)
        {
            child.Parent = this;
            ChildObjects.Add(child);
        }

        public string GetAbsoluteName()
        {
            if(Parent)
            {
                return Parent.GetAbsoluteName() + "::" + Name;
            }

            return Name;
        }

        public BaseObject Parent { get; set; } = null;

        public List<BaseObject> ChildObjects { get; protected set; } = new List<BaseObject>();

        public string Name { get; set; }

        public AccessModifier AccessModifier_ { get; set; }

        internal static Dictionary<AccessModifier,string> AccessorStringList = new Dictionary<AccessModifier, string>() {
            { AccessModifier.Public , "public_access" }, {AccessModifier.Protected , "protected_access"} ,{AccessModifier.Private, "private_access" }
        };

        public List<MetaData> MetaData = new List<MetaData>();

        string[] GetMetaDataString()
        {
            string[] result = new string[MetaData.Count];
            for(int i = 0; i < result.Length; i++)
            {
                result[i] = MetaData[i].ToString();
            }
            return result;
        }

     
        public override string ToString()
        {
            if(MetaData.Count > 0)
            {
                return "(" + string.Join(",", GetMetaDataString()) + ")\n";
            }

            return "\n";
        }

        public static implicit operator bool(BaseObject value)
        {
            return value != null;
        }

    }
}
