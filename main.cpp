#include <iostream>
#include "include/Writer.h"
#include "include/Core.h"

using namespace std;

int main()
{
    Core::DebugLog("Logsplitter version 1.0");
    Writer::Load();
    while(true)
    {
        sleep(2);
    }
    return 0;
}
