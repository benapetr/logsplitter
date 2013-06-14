//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "../include/Configuration.h"

int Configuration::Verbosity = 0;
string Configuration::DefaultProjectPath = "/data/project";
string Configuration::DefaultPublicRawPath = "/data/project/.system/logs/public_apache2/global_access_raw.log";
string Configuration::DefaultGlobalPath = "/data/project/.system/logs/apache2/global_access.log";
string Configuration::DefaultPublicPath = "/data/project/.system/logs/public_apache2/global_access.log";
string Configuration::MissingPath = "/var/log/apache2/lost.log";
string Configuration::OtherPath = "/var/log/apache2/access.log";

void Configuration::Load(int argc, char *argv[])
{
    int current = 0;
    while (current < argc)
    {
        string parameter(argv[current]);
        if (parameter.size() >= 2)
        {
            if (parameter.substr(0, 2) == "-v")
            {
                Configuration::Verbosity++;
                unsigned int x = 2;
                while (x < parameter.size())
                {
                    if (parameter[x] != 'v')
                    {
                        break;
                    }
                    Configuration::Verbosity++;
                    x++;
                }
            }
        }
        current++;
    }
}
