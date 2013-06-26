//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "../include/Configuration.h"

//! Verbosity
int Configuration::Verbosity = 0;
//! Root path
string Configuration::DefaultProjectPath = "/data/project";
//! Where the RAW (apache format) logs mixed from all hosts are being written to
string Configuration::DefaultPublicRawPath = DefaultProjectPath + "/.system/logs/public_apache2/global_access_raw.log";
//! Where the private global access logs are being written to
string Configuration::DefaultGlobalPath = DefaultProjectPath + "/.system/logs/apache2/global_access.log";
//! Place to store global access logs prefixed with name of server
//! these logs don't contain the private info
string Configuration::DefaultPublicPath = DefaultProjectPath + "/.system/logs/public_apache2/global_access.log";
//! Missing tools
string Configuration::MissingPath = "/var/log/apache2/lost.log";
//! Unknown data
string Configuration::OtherPath = "/var/log/apache2/access.log";

void Configuration::PrintHelp()
{
    cout << "Usage: logsplitter [hv]" << endl;
    cout << endl;
    cout << "This is a logsplitter service, which is parsing the logs from apache servers" << endl << endl;
    cout << "Parameters:" << endl;
    cout << "    -v: Increase verbosity" << endl;
    cout << "    -h (--help): Display help" << endl;
}

//! Read all the configuration
bool Configuration::Load(int argc, char *argv[])
{
    int current = 0;
    while (current < argc)
    {
        string parameter(argv[current]);
        if (parameter == "--help" || parameter == "-h")
        {
            PrintHelp();
            return true;
        }
        if (parameter.size() > 1 && parameter.substr(0, 1) == "-")
        {
            unsigned int c = 1;
            while (c < parameter.size())
            {
                // verbose
                if ( parameter[c] == 'v' )
                {
                    Configuration::Verbosity++;
                }
                // help
                if ( parameter[c] == 'h' )
                {
                    PrintHelp();
                }
                c++;
            }
        }
        current++;
    }
    return false;
}
