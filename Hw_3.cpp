/*
This programs adds two numbers together. Really,
that's all it does is add to numbers together, yet
it is so complicated. =P. Storing digits in linked
lists allows for numbers larger than the max value
for a data type.

 Name: Eric Du
 IDE: Codeblocks
*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include "IntList.h"

using namespace std;

void openFile  (ifstream &inputFile, ofstream &outputFile);
void closeFile (ifstream &inputFile, ofstream &outputFile);
bool firstBigger(string numString1, string numString2);
void appendNum(IntList *numList, string numString);
void displayNum(ofstream &outputFile, IntList *numList1, IntList *numList2);
void addNum(IntList *numList1, IntList *numList2, IntList *sumList);
void displaySum(ofstream &outputFile, IntList *sumList);
void displayLargest(ofstream &outputFile,IntList *numList1);
void calculateSum(IntList *numList1, IntList *numList2, IntList sumList);

int main()
{
    ifstream inputFile;
    ofstream outputFile;                                   //opens file to read from
    openFile(inputFile, outputFile);

    string numString1, numString2;                        //temp string to hold number

    while(getline(inputFile, numString1))                //reads each first number
    {

        IntList *numList1 = new IntList;                //lists to hold first number, second number, and sum
        IntList *numList2 = new IntList;
        IntList *sumList  = new IntList;

        getline(inputFile, numString2);                 //reads the second number

        if(firstBigger(numString1, numString2))         //makes sure that the bigger number is Number 1 and smaller is Number 2
        {
            appendNum(numList1, numString1);
            appendNum(numList2, numString2);
        }
        else
        {
            appendNum(numList1, numString2);
            appendNum(numList2, numString1);
        }

        displayNum(outputFile, numList1, numList2);                  //to display the numbers

        addNum(numList1, numList2, sumList);

        displaySum(outputFile, sumList);                            //displays the sum

        displayLargest(outputFile, numList1);                       //displays the largest number, which is Number 1

        inputFile.ignore(8, '\n');                                    //ignores the extra space

        delete numList1;                                             //deletes to prevent memory heap
        delete numList2;
        delete sumList;
    }
    closeFile(inputFile, outputFile);                               //close files when it's done

    return 0;
}

//*******************************
//compares the two read in lines
//and returns true if the first one is bigger
//than the second one
//*******************************
bool firstBigger(string numString1, string numString2)
{
    if (numString1.length()> numString2.length())               //if the length of the first string is longer,
        return true;                                            //then the value is obviously larger
    else if (numString1.length() <  numString2.length())
        return false;

    char number1[numString1.length()];
    strcpy(number1, numString1.c_str());

    char number2[numString2.length()];                          //if the lengths are equal, use strcmp to see
    strcpy(number2, numString2.c_str());                        //which string comes before the other

    return strcmp(number1, number2) == 1;                       //returns true if the first number comes after the second

}

//*******************************
//uses c string to append the the numList
//to a new list
//*******************************
void appendNum(IntList *numList, string numString)
{
        char number1[numString.length()];                       //declare c-string the size of the string
        strcpy(number1, numString.c_str());                     //copies characters into c-string

        for(int i=0; i < numString.length(); i++)               //one character at a time, it appends it into the node
            numList->appendToBack(number1[i]-48);               //changing its ASCII value to int
}

//*******************************
//simply displays the values of the two numbers
//in an output file
//*******************************
void displayNum(ofstream &outputFile, IntList *numList1, IntList *numList2)
{
    outputFile << "Number 1: ";                                           //displays first number
    numList1->displayList(outputFile);
    outputFile << "Number 2: "
         << setw(numList1->getCount() - numList2->getCount()+1);                //displays second number so it is right align with Number 1
    numList2->displayList(outputFile);                                        //if number of digits differ
}

void addNum(IntList *numList1, IntList *numList2, IntList *sumList)
{
    int counter = 0;
    int previousSum = 0;
    int digSum = 0;

    while(counter < numList2->getCount())
    {
        previousSum = digSum + previousSum/10;
        digSum = numList1->returnValue(counter) + numList2->returnValue(counter);

        sumList->appendToFront(((digSum%10)+(previousSum/10))%10);

        counter++;
    }
    previousSum = digSum;

    while(counter < numList1->getCount())
    {
        sumList->appendToFront(((numList1->returnValue(counter))+(previousSum/10))%10);

        previousSum = (numList1->returnValue(counter))+(previousSum/10);

        counter++;
    }

    if(previousSum >= 10)//if the very front most digit of the large number still carries over a number, append a 1
        sumList->appendToFront(1);

}
//*******************************
//displays the sum of the two numbers into
//an output file
//*******************************
void displaySum(ofstream &outputFile, IntList *sumList)
{
    outputFile << "Sum     : ";       //displays the sumList
    sumList->displayList(outputFile);
}

//*******************************
//displays the largest of the two numbers
//which is already the first number
//*******************************
void displayLargest(ofstream &outputFile, IntList *numList1)
{
    outputFile << "Largest : ";       //displays the largest of the two numbers, which is Number 1
    numList1->displayList(outputFile);
    outputFile << endl;
}

//*******************************
//opens the files of the input and output file
//*******************************
void openFile (ifstream &inputFile, ofstream &outputFile)
{
    inputFile.open("big_ints.txt");                     //opens file and makes sure its the correct one

    if(!inputFile)
    {
        cout << "\ncannot obtain input file\n";
        exit(EXIT_FAILURE);                            //ends if its the incorrect file
    }

    outputFile.open ("big_ints_out.txt");

    if(!inputFile)
    {
        cout << "\ncannot obtain output file\n";
        exit(EXIT_FAILURE);                            //ends if its the incorrect file
    }
}

//*******************************
//makes sure to close the files when done
//*******************************
void closeFile(ifstream &inputFile, ofstream &outputFile)
{
    inputFile.close();                          //closes file when its all done
    outputFile.close();
}

