//
//  SCRP.h
//  TestApp
//
//  Created by Sophie Peters on 3/27/14.
//  Copyright (c) 2014 Pixoodles. All rights reserved.
//

#ifndef TestApp_SCRP_h
#define TestApp_SCRP_h
namespace ORIENT {
    template < typename T > class SCRP
    {
    private:
        T*    pData; // Generic pointer to be stored
        unsigned int id;
    public:
        SCRP()
        {
            pData = NULL;
        }
        ~SCRP()
        {
            delete pData;
        }
        
        T& operator* ()
        {
            return *pData;
        }
        
        T* operator-> ()
        {
            return pData;
        }
        SCRP<T> * operator= ( T * rhs)
        {
            id = orient.inc(rhs);
            pData = rhs;
            return *this;
        }
        void operator delete(void * ptr)
        {
            orient.dinc(ptr);
        }
    };
    
}



#endif
