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
    protected:
    private:
};

#endif // CONFIGURATION_H