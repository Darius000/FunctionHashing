using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.ComponentModel;
using System.Diagnostics;

namespace BuildTool
{
    namespace Utilities
    {
        static internal class ModuleParser
        {
            static public void Parse(List<Module> modules)
            {
                int size = modules.Count;

                for(int i = 0; i < size; i++)
                {
                    ParseModule(modules[i]);
                }
            }

            static void ParseModule(Module module)
            {
                m_CurrentModule = module;

                var file_generated_path = module.TargetGeneratedDir;

                Console.WriteLine("Getting files in directory {0}", module.TargetDir);

                var files = GetFilesInModule(m_CurrentModule);

                Console.WriteLine("Found {0} h files in {1}", files.Length, module.TargetDir);

                List<BaseObject> classes = new List<BaseObject>();

                foreach (var file in files)
                {
                   
                    var filename = Path.GetFileNameWithoutExtension(file) + ".generated.h";

                    var parsedclasses = HFileParser.Parse(file);

                    
                    if (parsedclasses != null && parsedclasses?.Count > 0)
                    {
                        var generated_path = file_generated_path + "\\" + filename;

                        if (File.Exists(generated_path))
                        {
                            File.WriteAllText(generated_path, string.Empty);
                        }

                        Console.WriteLine("Writing to... {0}", generated_path);

                        for(int i = 0; i < parsedclasses.Count; i++)
                        {
                            HFileParser.WriteHeaderFile(generated_path, parsedclasses[i]);
                        }

                        classes.AddRange(parsedclasses);
                    }


                   
                    

                }
            }

            static string[] GetFilesInModule(Module module)
            {
                var files = Directory.GetFiles(module.TargetDir, "*.h", SearchOption.AllDirectories);

                return files;
            }

            static private Module m_CurrentModule;
        }
    }
}

