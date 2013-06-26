#ifndef ITEM_H
#define ITEM_H

#include <iostream>

using namespace std;

//! Represen an item (1 line) which needs to be stored
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
