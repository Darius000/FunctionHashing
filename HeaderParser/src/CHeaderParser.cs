using System;
using System.Collections.Generic;

class ModuleFileCache
{
    public ModuleFileCache(List<string> files)
    {
        m_Files = files;
    }

    public List<string> Files { get { return m_Files; } private set { m_Files = value; } }

    private List<string> m_Files = new List<string>();
};