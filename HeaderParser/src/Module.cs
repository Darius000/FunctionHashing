using System;
using System.Collections.Generic;

namespace BuildTool
{
    public class Module
    {
        public Module() { }

        public List<string> PublicDependencyModuleNames = new List<string>();

        public List<string> PrivateDependencyModuleNames = new List<string>();

        public string TargetGeneratedDir = "Generated";

        public string TargetDir = "Src";
    }
}