#include <iostream>
#include "include/Writer.h"
#include "include/Core.h"
#include "include/Configuration.h"
#include <sys/stat.h>
#include <dirent.h>

using namespace std;

bool Exists( string pzPath )
{
    struct stat st;
    if(stat(pzPath.c_str(),&st) == 0)
    {
        return true;
    }

    return false;
}

void Parse(string host)
{
    while(cin)
    {
        string toolname;
        string text;
        cin >> toolname;
        getline(cin, text);
        if (text.size() > 0)
        {
            text = text.substr(1);
        }
        string logfile;
        //string user = "local-" + toolname;
        string user = toolname;
        string home = Configuration::DefaultProjectPath + "/" + toolname;
        string line = host + ": " + text;
        if (system(string("id " + user).c_str()) == 0)
        {
            // now we check if the tool has a home
            if (Exists(home))
            {
                // if it does we use it as a target for a log
                logfile = home + "/access.log";
                // now we check if the access.log exist in that home
                if (!Exists(logfile))
                {
                    string s;
                    s = "touch \"" + logfile + "\"";
                    system(s.c_str());
                    s = "chmod 0640 \"" + logfile + "\"";
                    system(s.c_str());
                    s = "chown " + user + ":" + user + " \"" + logfile + "\"";
                    system(s.c_str());
                }
                // write to a tool home
                Writer::Write(logfile, text);
            } else
            {
                Writer::Write(Configuration::MissingPath, text + " [missingdir:" + home + "]");
            }
            // write to global access
            Writer::Write(Configuration::DefaultGlobalPath, line);
        }
        else
        {
            Writer::Write(Configuration::OtherPath, text + " [" + toolname + "]");
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "You need to provide at least 1 parameter. Usage: logsplitter hostname" << endl;
        return 2;
    }
    Core::DebugLog("Logsplitter version 1.0");
    Writer::Load();
    Parse(argv[1]);
    return 0;
}
