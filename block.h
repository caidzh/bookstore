#ifndef _BLOCK_H
#define _BLOCK_H

#include "node.h"

const int maxsz=400;

template<class T>
class block{
    public:
        node<T> book[maxsz<<1];
        int size,pos;
        block(){
            size=0;
            pos=-1;
        }
        block(const int size,int pos=-1):
            size(size),pos(pos){}
        block(const block &x){
            size=x.size;
            for(int i=0;i<size;i++)
                book[i]=x.book[i];
            pos=x.pos;
        }
        block &operator=(const block &x){
            if(this==&x)
                return *this;
            size=x.size;
            for(int i=0;i<size;i++)
                book[i]=x.book[i];
            pos=x.pos;
            return *this;
        }
};

#endif