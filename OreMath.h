//
//  OreMath.h
//  TestApp
//
//  Created by Sophie Peters on 3/29/14.
//  Copyright (c) 2014 Pixoodles. All rights reserved.
//

#ifndef OreMath_h
#define OreMath_h
float ABS(float a)
{
    if(a < 0)
        return -1*a;
    else
        return a;
}

void chartohex(char value, char &ln, char &rn)
{
    char left, right;
    left = value/16;
    right = value - (left*16);
    if (left > 9)
        left += 55;
    else
        left += 48;
    if (right > 9)
        right += 55;
    else
        right += 48;
    ln = left;
    rn = right;
}


#endif
