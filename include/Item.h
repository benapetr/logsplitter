#ifndef ITEM_H
#define ITEM_H

#include <iostream>

using namespace std;

class Item
{
    public:
        Item(string file, string text);
        virtual ~Item();
        string File;
        string Text;
    protected:
    private:
};

#endif // ITEM_H
