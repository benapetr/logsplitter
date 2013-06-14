//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.


#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include "include/Writer.h"
#include "include/Core.h"
#include "include/Configuration.h"

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

string CleanUp(string line)
{
    if ( line.size() > 20 )
    {
       if ( line.substr(0, 15) == "tools-webserver" )
       {
          if ( std::string::npos != line.find("HTTP/") )
          {
             size_t position = line.find("+0000]");
             if ( std::string::npos != position )
             {
                 position = 8 + position;
                 size_t position_of_first = line.find("/", position);
                 size_t position_of_next = line.find("/", position_of_first + 1);
                 size_t last = line.rfind("/");
                 if (last != std::string::npos)
                 {
                     string x = line.substr(0, position_of_next) + " HTTP" + line.substr(last);
                     if (x.substr(0, 15) == "tools-webserver")
                     {
                         return x;
                     }
                 }
             }
          } 
       }
    }
    return "";
}

void Parse(string host)
{
    cin.sync_with_stdio(false);
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
        string user = "local-" + toolname;
        string home = Configuration::DefaultProjectPath + "/" + toolname;
        string line = host + ": " + text;
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
            if (system(string("id " + user).c_str()) == 0)
            {
                Writer::Write(Configuration::MissingPath, text + " [missingdir:" + home + "]");
            }
            else
            {
                Writer::Write(Configuration::OtherPath, text + " [" + toolname + "]");
            }
            // write to global access
        }
        Writer::Write(Configuration::DefaultPublicPath, CleanUp(line));
        Writer::Write(Configuration::DefaultGlobalPath, line);
    }
}

int main(int argc, char *argv[])
{
    Configuration::Load(argc, argv);
    Core::DebugLog("Logsplitter version 1.0");
    Writer::Load();
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    string host(hostname);
    Core::DebugLog("Hostname: " + host);
    Parse(host);
    Writer::Terminate();
    return 0;
}
