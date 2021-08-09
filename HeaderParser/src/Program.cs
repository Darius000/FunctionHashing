using System;
using System.Collections.Generic;
using System.Linq;

namespace HeaderTool
{
    class Program
    {
        static void Main(string[] args)
        {
            CPPHeaderFileParser parser = new CPPHeaderFileParser();

            //if (args.Length > 0)
            //{
            //    foreach (string st in args)
            //        parser.ParseCPPHeader(st);
            //}

            // parser.ParseCPPHeader("C:\\Users\\Darius Bigbee\\Desktop\\IMG_20200803_210809404.cpp");
            Module TestModule = new Module();
            TestModule.AddPath("D:\\Dev\\Tuts\\Tutorials\\src");

            List<Module> modules = new List<Module>();
            modules.Add(TestModule);

            parser.Parse(modules);

            System.Console.ReadLine();
        }
    }
}
