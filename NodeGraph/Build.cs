using System;
using System.IO;
using BuildTool;

public class NodeGraphModule : Module
{
    public NodeGraphModule() : base()
    {
        string currentDirectory = "C:\\Users\\dariu\\Documents\\GitHub\\FunctionHashing\\NodeGraph\\";
        TargetDir = currentDirectory + "src";
        TargetGeneratedDir = currentDirectory + "Generated";
    }
}