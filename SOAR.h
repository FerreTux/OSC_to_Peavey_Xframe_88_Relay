//
//  SOAR.h
//  TestApp
//
//  Created by Sophie Peters on 3/26/14.
//  Copyright (c) 2014 Pixoodles. All rights reserved.
//

#ifndef TestApp_SOAR_h
#define TestApp_SOAR_h
//////////Standard Includes
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cstring>
#include "sstream"
////////////////Templating
// Object Reference Index Entry and Numeric Typecast
// ORIENT
//      Reference counting, numeric typecasting, object id assignment
// Scalable Object Array Reference
// SOAR
//      Resizing array
//

template <class varType> class SOAR
{
private:
    varType ** objs;            ///Note would benefit to add customizable resize amount and limit
    int indexSize,arraySize;
public:
    SOAR();
    int add(varType *var);
    int remove(int varIndex);
    varType * get(int varIndex);
    int size();
    
    int replace(int varIndex, varType * var);
    int que(varType *var);
    varType * deque();
    int push(varType *var);
    varType * pop();
};
template <class varType> SOAR<varType>::SOAR()
{
    indexSize = 0;
    arraySize = 0;
    objs = NULL;
}

template <class varType> int SOAR<varType>::add(varType *var)
{
    varType * gset = new varType;
    *gset = *var;
    
    if (objs != NULL)
    {
        for (int a = 0; a < indexSize; a++)
            if (objs[a]  == NULL)
            {
                objs[a] = gset;
                arraySize++;
                return 1;
            }
        varType ** tempP = new varType *[indexSize+1];
        for (int i = 0; i < indexSize; i++)
            tempP[i] = objs[i];
        tempP[indexSize] = gset;
        delete [] objs;
        objs = tempP;
    }
    else
    {
        objs = new varType * [indexSize+1];
        objs[indexSize] = gset;
    }
    indexSize++;
    arraySize++;
    return 0;
}

template <class varType> int SOAR<varType>::remove(int varIndex)
{
    delete objs[varIndex];
    for (int i = varIndex; i < indexSize; i++)
        objs[i] = objs[i+1];
    objs[indexSize-1] = NULL;
    arraySize--;
    return 0;
}
template <class varType> varType * SOAR<varType>::get(int varIndex)
{
    return objs[varIndex];
}
template <class varType> int SOAR<varType>::replace(int varIndex, varType * var)
{
    varType * gset = new varType;
    *gset = *var;
    varType * temp;
    temp = objs[varIndex];
    objs[varIndex] = gset;
    delete temp;
    return 0;
    
}

template <class varType> int  SOAR<varType>::que(varType *var)
{
    varType * gset;
    gset = var;
    
    if (objs != NULL)
    {
        for (int a = 0; a < indexSize; a++)
            if (objs[a]  == NULL)
            {
                for (int i = a; i > 0; i--)
                    objs[i] = objs[i-1];
                objs[0] = gset;
                arraySize++;
                return 1;
            }
        varType ** tempP = new varType *[indexSize+1];
        for (int i = 1; i < indexSize+1; i++)
            tempP[i] = objs[i-1];
        tempP[0] = gset;
        delete [] objs;
        objs = tempP;
    }
    else
    {
        objs = new varType * [indexSize+1];
        objs[0] = gset;
    }
    indexSize++;
    arraySize++;
    return 0;
    
}
template <class varType> varType * SOAR<varType>::deque()
{
    int a;
    varType * ret = NULL;
    for ( a = indexSize-1; a >= 0; a--)
        if (objs[a]  != NULL)
        {
            ret = objs[a];
            objs[a] = NULL;
            break;
        }
    arraySize--;
    return ret;
}

template <class varType> int  SOAR<varType>::push(varType *var)
{
    return que(var);
}
template <class varType> varType *  SOAR<varType>::pop()
{
    int a;
    varType * ret = objs[0];
    for ( a = 1; a < arraySize; a++)
        if (objs[a]  != NULL)
            objs[a-1] = objs[a];
    arraySize--;
    return ret;
}
template <class varType> int SOAR<varType>::size() { return arraySize; }


#endif
