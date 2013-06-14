#ifndef WRITER_H
#define WRITER_H

#include <iostream>
#include <mutex>
#include <list>
#include <pthread.h>
#include "../include/Item.h"

using namespace std;

class Writer
{
    public:
        static void Load();
        static void Write(string file, string text);
        static void Terminate();
        static bool isRunning;
    protected:
    private:
        static list<Item> DB;
        static pthread_t thread;
        static void *Exec(void *threadid);
        static std::mutex &data_mut()
        {
            static std::mutex m;
            return m;
        }
};

#endif // WRITER_H
