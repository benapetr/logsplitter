//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.


#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>

using namespace std;

class Configuration
{
    public:
        static string DefaultProjectPath;
        static string DefaultGlobalPath;
        static string DefaultPublicPath;
        static int Verbosity;
        static string OtherPath;
        static string MissingPath;
        static string DefaultPublicRawPath;
        static void PrintHelp();
        static bool Load(int argc, char *argv[]);
    protected:
    private:
};

#endif // CONFIGURATION_H
