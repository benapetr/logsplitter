#include "../include/Writer.h"
#include "../include/Core.h"
#include <iostream>
#include <list>
#include <fstream>
#include <mutex>
#include <pthread.h>

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
            fstream filestr;
            filestr.open (iter->File, fstream::in | fstream::out | fstream::app);
            filestr << iter->Text <<endl;
            filestr.close();
        }

        sleep(2);
    }
    pthread_exit(NULL);
}

void Writer::Write(string file, string text)
{
    // lock array
    std::lock_guard<std::mutex> _(Writer::data_mut());
    // write this line
    DB.push_back(Item(file,text));
}

std::list<Item> Writer::DB;
bool Writer::isRunning = true;
pthread_t Writer::thread;
