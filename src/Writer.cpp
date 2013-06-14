//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.


#include <iostream>
#include <list>
#include <unistd.h>
#include <fstream>
#include <mutex>
#include <pthread.h>
#include "../include/Writer.h"
#include "../include/Configuration.h"
#include "../include/Core.h"

using namespace std;

void Writer::Load()
{
    int r = pthread_create(&Writer::thread, NULL, Writer::Exec, (void *)1);
    Core::DebugLog("Initialized the writer thread");
    if (r)
    {
        cout << "Error:unable to create thread," << r << endl;
    }
}

void *Writer::Exec(void *threadid)
{
    while(Writer::isRunning)
    {
        // lock the array and copy it
        Writer::data_mut().lock();
        list<Item> tm (Writer::DB);
        Writer::DB.clear();
        Writer::data_mut().unlock();

        // foreach write every single record
        list<Item>::iterator iter;
        for(iter = tm.begin(); iter != tm.end(); iter++)
        {
            if (Configuration::Verbosity > 1)
            {
                Core::DebugLog( "Writing to " + iter->File );
            }
            fstream filestr;
            filestr.open (iter->File, fstream::in | fstream::out | fstream::app);
            filestr << iter->Text <<endl;
            filestr.close();
        }

        sleep(2);
    }
    pthread_exit(NULL);
}

void Writer::Terminate()
{
    Writer::isRunning = false;
    // check if db is empty
    bool wait = true;
    while (wait)
    {
        Writer::data_mut().lock();
        if (Writer::DB.size() > 0)
        {
            Core::DebugLog("There are still data in memory, waiting for writer to finish");
            sleep(2);
            continue;
        }
        Writer::data_mut().unlock();
        wait = false;
    }
    // grace time for buffer to empty
    sleep(1);
    Core::DebugLog("Terminating writer");
    return;
}

void Writer::Write(string file, string text)
{
    if (text == "")
    {
        Core::DebugLog("Not writing empty text to " + file);
        return;
    }
    // lock array
    std::lock_guard<std::mutex> _(Writer::data_mut());
    // write this line
    DB.push_back(Item(file,text));
}

std::list<Item> Writer::DB;
bool Writer::isRunning = true;
pthread_t Writer::thread;
