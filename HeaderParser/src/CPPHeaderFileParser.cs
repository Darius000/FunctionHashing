using HeaderTool.src;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace HeaderTool
{
    public enum AttributeType  {Class, Property }
    public struct Attributes
    {
        public AttributeType attributeType;
        public string type;
        public string name;
        public string defualtValue;
        public bool hasValue;
    }

    public class CPPHeaderFileParser
    {
        public CPPHeaderFileParser()
        {
            
        }

        public void Parse(List<Module> modules)
        {
            foreach(Module module in modules)
            {
                foreach(string path in module.GetModules())
                {
                    if (!Directory.Exists(path)) break;

                    string[] files = Directory.GetFiles(path);

                    foreach (string file in files)
                    {
                        if (CheckFile(file))
                        {
                            Attributes[] attribues = ParseFileContents(file);
                        }
                    }
                }
            }
        }

        private bool CheckFile(string file)
        {
            return ExtChecker.IsValidExtension(file);
        }

        private Attributes[] ParseFileContents(string file)
        {
            Attributes[] attributes = { };
            string[] lines = System.IO.File.ReadAllLines(file);
            for (int i = 0; i < lines.Length; i++)
            {
                string line = lines[i];


            }

            return attributes;
        }

        private void GenerateFile(string file, Attributes[] attribues)
        {

        }

        private CheckExtension ExtChecker = new CheckExtension();
    }
}