//
//  Orient1.h
//  TestApp
//
//  Created by Sophie Peters on 3/27/14.
//  Copyright (c) 2014 Pixoodles. All rights reserved.
//

#ifndef TestApp_Orient1_h
#define TestApp_Orient1_h
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cstring>
#include "sstream"
namespace ORIENT
{
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
        varType * gset = (varType*)malloc( sizeof(varType) );
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
            varType ** tempP = (varType**) calloc(indexSize+1,sizeof(varType*)); //new varType *[indexSize+1];
            for (int i = 0; i < indexSize; i++)
                tempP[i] = objs[i];
            tempP[indexSize] = gset;
            
            free(objs);//delete [] objs;
            objs = tempP;
        }
        else
        {
            objs = (varType**) calloc(indexSize+1, sizeof(varType*));
            //objs = new varType * [indexSize+1];
            objs[indexSize] = gset;
        }
        indexSize++;
        arraySize++;
        return 0;
    }
    
    template <class varType> int SOAR<varType>::remove(int varIndex)
    {
        free( objs[varIndex] );
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
            varType ** tempP = (varType**) calloc(indexSize+1,sizeof(varType*));// new varType *[indexSize+1];
            for (int i = 1; i < indexSize+1; i++)
                tempP[i] = objs[i-1];
            tempP[0] = gset;
            free(objs);//delete [] objs;
            objs = tempP;
        }
        else
        {
            objs = (varType**) calloc(indexSize+1,sizeof(varType*));//new varType * [indexSize+1];
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
        int a,b;
        bool FIRST = false;
        varType * ret = objs[0];
        for ( a = 1; a < arraySize; a++)
            if (objs[a]  != NULL)
            {
                if (!FIRST)
                    b=a;
                objs[a-1] = objs[a];
            }
        
        
        objs[b] = NULL;
        arraySize--;
        return ret;
    }
    template <class varType> int SOAR<varType>::size() { return arraySize; }
    
    
    struct mem_loc
    {
        void * p;
        unsigned int rc;
        unsigned int id;
    };
    
    class ORIENT
    {
    private:
        SOAR<mem_loc> mem_list;
        unsigned int idCount;
    public:
        ORIENT() { idCount = 1; }
        void * add(size_t num)
        {
            mem_loc * n =(mem_loc*) malloc(sizeof(mem_loc));
            void* ret = malloc(num);
            n->p = ret;
            n->id = idCount++;
            mem_list.push(n);
            return n->p;
        }
        int inc(void * loc)
        {
            for(int i = 0; i < mem_list.size(); i++)
                if (mem_list.get(i)->p == loc)
                {
                    mem_list.get(i)->rc++;
                    return mem_list.get(i)->id;
                }
            return 0;
        }
        
        int dinc(void * loc)
        {
            for(int i = 0; i < mem_list.size(); i++)
                if (mem_list.get(i)->p == loc)
                {
                    mem_list.get(i)->rc--;
                    if (mem_list.get(i)->rc == 0)
                    {
                        free( mem_list.get(i)->p );
                        mem_list.remove(i);
                    }
                    return 0;
                }
            return 1;
        }
        void del (void * loc)
        {
            for(int i = 0; i < mem_list.size(); i++)
                if (mem_list.get(i)->p == loc)
                {
                    free(mem_list.get(i)->p);
                    mem_list.remove(i);
                    break;
                }
        }
        void flush()
        {
            int leak = 0;
            std::cout << std::endl << "Orient Report------------------------------------- " << std::endl;
            int end = mem_list.size();
            for(int i = 0; i < end; i++)
                if (mem_list.get(0))
                {
                    std::cout << "Leak at: " << mem_list.get(0)->p << " With ID: " << mem_list.get(0)->id << std::endl;
                    leak++;
                    free(mem_list.get(0)->p);
                    mem_list.remove(0);
                }
            std::cout << "Total Number of new allocations: " << idCount << std::endl;
            std::cout << "Total Leaks: " << leak << std::endl;
            std::cout << std::endl << "-------------------------------------Report Finished" << std::endl;
        }
        void checkLeak()
        {
            int act = 0;
            std::cout << std::endl << "Orient Quick Report------------------------------------- " << std::endl;
            int end = mem_list.size();
            for(int i = 0; i < end; i++)
                if (mem_list.get(i))
                {
                    std::cout << "Memory Active at: " << mem_list.get(i)->p << " With ID: " << mem_list.get(i)->id  << std::endl;
                    act++;
                }
            std::cout << "Total Number of new allocations: " << idCount << std::endl;
            std::cout << "Total Active Memory : " << act << std::endl;
            std::cout << std::endl << "-------------------------------------Report Finished" << std::endl;
        }
    };
    
    
    
}
ORIENT::ORIENT orient;
void* operator new(size_t num)
{
    return orient.add(num);
}

void operator delete(void *ptr)
{
    orient.del(ptr);
}

#endif
