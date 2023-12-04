#include "objPosArrayList.h"
#include <iostream>

using namespace std;

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];  // 200 elements on heap
    listSize = 0;                       // no valid element in the list at start
    arrayCapacity = ARRAY_MAX_CAP;      // array capacity set to maximum

}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; // delete every elements in the array aList

}

int objPosArrayList::getSize()
{
    return listSize;

}

void objPosArrayList::insertHead(objPos thisPos)
{
    // to do: still need to check if the listSize == arrayCapacity, if true, don't insert.
    if (listSize == arrayCapacity)
    {
        cout << "Insert head failed, array is Full!" << endl;

    }

    else
    {
        for (int i = listSize; i > 0; i --)
        {
            aList[i].setObjPos(aList[i - 1]); // with the copy constructor in objPos.cpp,
                                            // shuffle the last element in the array back to the next pos, 
                                            // i.e. [i - 1] to [i], 
                                            // then second last element, [(i - 1) - 1] to [i - 1], and so on, 
                                            // untill [0] is placed to [1] and left empty

        }

        aList[0].setObjPos(thisPos); // write the element passed in to the head of the array with the copy constructor
        listSize ++;

    }

}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize == arrayCapacity)
    {
        cout << "Insert tail failed, array is Full!" << endl;

    }
    
    else
    {
        aList[listSize].setObjPos(thisPos);
        listSize ++;

    }

}

void objPosArrayList::removeHead()
{   
    if (listSize == 0)
    {
        cout << "Remove head failed, array is empty!" << endl;

    }

    else
    {
        for (int i = 1; i < listSize - 1; i ++)
        {
            aList[i - 1].setObjPos(aList[i]); 

        }

        listSize --;

    }

}

void objPosArrayList::removeTail()
{
    if (listSize == 0)
    {
        cout << "Remove tail failed, array is empty!" << endl;

    }

    else
    {
        listSize --;

    }

}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);

}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize - 1]);

}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);

}