#ifndef _BLOCKLIST_H
#define _BLOCKLIST_H

#include "node.h"

template<class T>
class blocked_list{
    public:
        int size,next,block_pos,pos;
        node<T> head;
        blocked_list(){
            size=0;
            next=-1;
            block_pos=-1;
            pos=-1;
        }
        blocked_list(const int size,int next=-1,int block_pos=-1,int pos=-1):
            size(size),next(next),block_pos(block_pos),pos(pos){}
        blocked_list(const blocked_list &x){
            size=x.size;
            next=x.next;
            block_pos=x.block_pos;
            pos=x.pos;
            head=x.head;
        }
        blocked_list &operator=(const blocked_list &x){
            if(this==&x)
                return *this;
            size=x.size;
            next=x.next;
            block_pos=x.block_pos;
            pos=x.pos;
            head=x.head;
            return *this;
        }
    friend void check_upper();
    friend void check_lower();
    friend void ins(std::array<char,65>&arr,int &year);
    friend void del(std::array<char,65>&arr,int &year);
    friend bool query(std::array<char,65>&arr);
};

#endif