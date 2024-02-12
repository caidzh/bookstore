#ifndef _NODE_H
#define _NODE_H

#ifndef ARRAY
#define ARRAY

#include<array>

#endif

#include "book.h"
#include "account.h"

template<class T>
class node{
    public:
        std::array<char,65>name,year;
        T info;
        int quantity,price;
        node(){
            quantity=0;
            price=0;
            name=N;
            year=N;
        }
        node(const std::array<char,65>str,std::array<char,65>year,int quantity=0,int price=0):
            name(str),year(year),quantity(quantity),price(price){}
        node(const node &x){
            name=x.name;
            year=x.year;
            quantity=x.quantity;
            price=x.price;
            info=x.info;
        }
        node &operator=(const node &x){
            if(this==&x)
                return *this;
            name=x.name;
            year=x.year;
            quantity=x.quantity;
            price=x.price;
            info=x.info;
            return *this;
        }
        bool operator>(node &x)const{
            return name>x.name||(name==x.name&&year>=x.year);
        }
        bool compare(node &x,node &y){
            return x.name>y.name||(x.name==y.name&&x.year>=y.year);
        }
};

#endif