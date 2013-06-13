// this file contains various functions that are usefull everywhere

#include "../include/Core.h"
#include "../include/Configuration.h"

void Core::DebugLog(string text, int verbosity)
{
    if (Configuration::Verbosity >= verbosity)
    {
        cout << text << endl;
    }
}
