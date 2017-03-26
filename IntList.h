// Specification file for the CountryList class
#ifndef INTLIST_H
#define INTLIST_H

#include <string>
#include <cstring>
using namespace std;

class IntList
{
private:

    struct ListNode
    {
        int value;
        ListNode *forward;
        ListNode *back;
    };
    ListNode *head;
    int count;

public:
    IntList();
   ~IntList();

    int getCount() const
    { return count; }

    void appendToBack(int);
    void appendToFront(int);
    void displayList(ofstream &outputFile) const;
    int returnValue(int counter);

};
#endif
