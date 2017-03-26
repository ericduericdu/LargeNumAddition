// Implementation file for the IntList class
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include "IntList.h"

using namespace std;

//*******************************
// constructor that makes sentinel node
//*******************************
IntList::IntList()
{
    head = new ListNode;        //creates sentinel node that points forward and back to itself
    head->forward = head;
    head->back = head;
    head->value = 999;

    count = 0;
}

//*******************************
//destructor to destroy the list when its done
//*******************************
IntList::~IntList()
{
    ListNode *nodePtr;
    ListNode *nextNode;

    nodePtr = head->forward;

    while(nodePtr != head)
    {
        nextNode = nodePtr->forward;

        delete nodePtr;

        nodePtr = nextNode;
    }
    delete nodePtr;
}

//*******************************
//appends a new node to the back of the list
//*******************************
void IntList::appendToBack(int num)
{
    ListNode *newNode;             // A new node
    ListNode *nodePtr;             // To traverse the list

    // Allocate a new node and store countryIn there.
    newNode = new ListNode;     //allocate new node
    newNode->value = num;       //assign it the value
    newNode->forward = head;    //automatically make it point to head, since its the last value
    nodePtr = head->forward;    //traverse starting from after the sentinel

    while(nodePtr->forward != head)
        nodePtr = nodePtr->forward;         //keep going until its the end

    nodePtr->forward = newNode;             //last value points to the new last value
       head->back = newNode;                //make the front point to the back since its circular
    newNode->back = nodePtr;                //make the value back pointer point to the original last value

    count++;                                 //increase the number of node count
}

//*******************************
//appends the new node to the front of the list
//for the sumList
//*******************************
void IntList::appendToFront(int num)
{
    ListNode *newNode;              //new node to add to list
    ListNode *nodePtr;

    newNode = new ListNode;        //allocate new node and assign value
    newNode->value = num;

    nodePtr = head->forward;        //nodePtr preserves the original first value

    head->forward = newNode;        //sentinel points to new value
    newNode->forward = nodePtr;     //new node points to the original first value
    newNode->back = head;           //points back to head
    nodePtr->back = newNode;        //original first value points back to new value

    count++;
}

//*******************************
//traverses and displays the list
//*******************************
void IntList::displayList(ofstream &outputFile) const
{
    ListNode *nodePtr;

    nodePtr = head->forward;        //traverse and skip over sentinel

    while(nodePtr != head)
    {
        outputFile << nodePtr->value;       //display node one by one
        nodePtr = nodePtr->forward;
    }
    outputFile << endl;
}

int IntList::returnValue(int counter)
{
    ListNode *nodePtr;

    nodePtr = head->back;
    for(int i = 0; i < counter; i++)
        nodePtr = nodePtr->back;

    return nodePtr->value;

}
