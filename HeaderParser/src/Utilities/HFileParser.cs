using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Text.RegularExpressions;
using System.Diagnostics;
using System.ComponentModel;

namespace BuildTool
{
    namespace Utilities
    {
        static internal class HFileParser
        {
            static public List<BaseObject> Parse(string filename)
            {
 
                if (!File.Exists(filename)) return null;

                Console.WriteLine("Reading file {0}", filename);

                var filecontent = File.ReadAllLines(filename);

                return ReadFileContents(filecontent);

            }


            static private List<BaseObject> ReadFileContents(string[] filecontent)
            {

                List<BaseObject> foundclasses = new List<BaseObject>();

                for(int i = 0; i < filecontent.Length; i++)
                {
                    var line = filecontent[i];

                    if(Regex.Match(line, Macros.namespace_).Success)
                    {
                        var namespace_name = Utilities.StringUtilities.GetName(line, "namespace", " ");
                        var namespace_ =  new Namespace(namespace_name);

                        if(s_CurrentNamespace)
                        {
                            namespace_.Parent = s_CurrentNamespace;
                        }

                        s_CurrentNamespace = namespace_; 
                    }

                    Class class_ = ParseClass<Class>(filecontent, Macros.class_ , "class", ref line, ref i, s_CurrentNamespace);
                    Struct @struct = ParseClass<Struct>(filecontent, Macros.struct_, "struct", ref line, ref i, s_CurrentNamespace);
                    Enum @enum = ParseEnum(filecontent, Macros.enum_, "enum", ref line, ref i, s_CurrentNamespace);

                    if(class_ != null || @struct != null || @enum != null)
                    {
                        if(class_) foundclasses.Add(class_);
                        if (@struct) foundclasses.Add(@struct);
                        if (@enum) foundclasses.Add(@enum);
                    }

                    if(line.Contains("}"))
                    {
  
                        if(s_CurrentNamespace)
                        {
                            s_CurrentNamespace = s_CurrentNamespace.Parent;
                        }
                    }
                }

                return foundclasses;
            }

           
            public static void WriteHeaderFile(string filename, BaseObject obj)
            {
                string content = "REFLECT_INLINE(" + obj.GetAbsoluteName() + ")\n{\n\t" +
                    obj.ToString() + "}\n\n";

                Writer.WriteTo(filename, content);
            }

            static Enum ParseEnum(string[] contents, string pattern, string keyword, ref string line, ref int index, BaseObject parent)
            {
                if(line.Contains(pattern))
                {
                    while (!line.Contains(keyword))
                    {
                        line = contents[index++];
                    }

                    var name = Utilities.StringUtilities.GetName(line, new string[] { "enum class", "enum" }, ":");

                    List<EnumValue> enumvalues = new List<EnumValue>(); 

                    while(index < contents.Length)
                    {
                        line = contents[index++];

                        if(line.Contains("{"))
                        {
                            continue;
                        }

                        if (line.Contains("};"))
                        {
                            break;
                        }

                        string[] values = line.Split(new char[] { '=', ' ' }, StringSplitOptions.RemoveEmptyEntries);
                        string value = Regex.Replace(values[0], "[;,{\t\r}]", "").Trim();

                        enumvalues.Add(new EnumValue(value));
                    }

                    return new Enum(name, enumvalues, s_CurrentNamespace);
                }

                return null;
            }

            static T ParseClass<T>(string[] contents, string pattern, string keyword, ref string line, ref int index, BaseObject parent) where T : Class
            {
               
                if (line.Contains(pattern))
                {
                    var metaData = MetaDataHelper.GetMetaData(line, "ClassMetaData");

                    while (!line.Contains(keyword))
                    {
                        line = contents[index++];
                    }

                    
                    var name = Utilities.StringUtilities.GetName(line, keyword, ":");

                    var parsedClass = (T)Activator.CreateInstance(typeof(T), new object[] { name, metaData, parent });

                    ParseClassContents<T>(contents, ref line, ref index, name, parsedClass);


                    return parsedClass;
                }

                return null;
            }

            static void ParseClassContents<T>(string[] contents, ref string line, ref int index, string classname, T class_) where T : Class
            {
                s_CurrentAccessModifier = class_.GetDefaultModifer();

                while(!StringUtilities.Maches(line, @"^[=};].*$"))
                {
                    line = contents[++index];

                    if(line.Contains(Macros.class_))
                    {
                        Class childclass_ = ParseClass<Class>(contents, Macros.class_, "class", ref line,  ref index, class_);

                        if(childclass_)
                        {
                            class_.AddChild(childclass_);
                        }
                    }

                    if(line.Contains(Macros.struct_))
                    {
                        Struct childstruct_ = ParseClass<Struct>(contents, Macros.struct_, "struct", ref line, ref index, class_);

                        if(childstruct_)
                        {
                            class_.AddChild(childstruct_);
                        }
                    }

                    if (line.Contains(Macros.enum_))
                    {
                        Enum childstruct_ = ParseEnum(contents, Macros.enum_, "enum", ref line, ref index, class_);

                        if (childstruct_)
                        {
                            class_.AddChild(childstruct_);
                        }
                    }

                    if (StringUtilities.Maches(line, @"(?=.*\bpublic\b[\:]).*$"))
                    {
                        s_CurrentAccessModifier = AccessModifier.Public;
                    }

                    if (StringUtilities.Maches(line, @"(?=.*\bprotected\b[\:]).*$"))
                    {
                        s_CurrentAccessModifier = AccessModifier.Protected;
                    }

                    if (StringUtilities.Maches(line, @"(?=.*\bprivate\b[\:]).*$"))
                    {
                        s_CurrentAccessModifier = AccessModifier.Private;
                    }

                    if (StringUtilities.Maches(line, @"(?=.*\b" + classname + @"\b[\(]).*$"))
                    {
                        var constructor = ParseConstructor(line);
                        if(constructor != null)
                        {
                            class_.AddConstructor(constructor);
                        }
                    }

                    if(StringUtilities.Maches(line, @"(?=.*\bPROPERTY\b[\(]).*$"))
                    {
                        var metadata = MetaDataHelper.GetMetaData(line, "PropertyMetaData");

                        line = contents[++index];

                        var property = ParseProperty(line, metadata);
                        if(property != null)
                        {
                            class_.AddProperty(property);
                        }
                    }

                    if (StringUtilities.Maches(line, @"(?=.*\bFUNCTION\b[\(]).*$"))
                    {
                        var metadata = MetaDataHelper.GetMetaData(line , "FunctionMetaData");

                        line = contents[++index];

                        var function = ParseMethod(line, metadata);
                        if(function != null)
                        {
                            class_.AddFunction(function);
                        }
                    }
                }
            }

            static Property ParseProperty(string line, List<MetaData> metaData)
            {
                string[] propertyline = line.Split(new char[] {'=', ' '}, StringSplitOptions.RemoveEmptyEntries);

                if(propertyline.Length > 1)
                {
                    var type = Regex.Replace(propertyline[0], "[;,\t\r]", "").Trim();
                    var name = Regex.Replace(propertyline[1], "[;,\t\r]", "").Trim();

                    return new Property(name, metaData ,type, s_CurrentAccessModifier);
                }

                return null;
            }

           

            static Constructor ParseConstructor(string line)
            {
                var args = ArgumentHelper.GetArgs(line);

                return new Constructor("", new List<MetaData> { }, args, s_CurrentAccessModifier);
            }

            static Function ParseMethod(string line, List<MetaData> metaData)
            {
                var args = ArgumentHelper.GetArgs(line);


                return null;
            }

            static AccessModifier s_CurrentAccessModifier = AccessModifier.Private;
            static BaseObject s_CurrentNamespace = null;

        }
    }
}

