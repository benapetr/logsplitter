//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.


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
