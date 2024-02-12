#ifndef _BOOK_H
#define _BOOK_H

#ifndef ARRAY
#define ARRAY

#include<array>

#endif

const std::array<char,65>N=
{'\0','\0','\0','\0','\0','\0','\0','\0','\0',
'\0','\0','\0','\0','\0','\0','\0','\0','\0',
'\0','\0','\0','\0','\0','\0','\0','\0','\0',
'\0','\0','\0','\0','\0','\0','\0','\0','\0',
'\0','\0','\0','\0','\0','\0','\0','\0','\0',
'\0','\0','\0','\0','\0','\0','\0','\0','\0',
'\0','\0','\0','\0','\0','\0','\0','\0','\0',
'\0','\0'};

class book{
    public:
        std::array<char,65>isbn,bookname,author,keyword;
        double price;
        int quantity;
        bool is_constructed;
        book(){
            price=0;
            quantity=0;
            isbn=N;
            bookname=N;
            author=N;
            keyword=N;
            is_constructed=false;
        }
        book(double price,int quantity,bool is_constructed):
            price(price),quantity(quantity),is_constructed(is_constructed){}
        book(const book &x){
            isbn=x.isbn;
            bookname=x.bookname;
            author=x.author;
            keyword=x.keyword;
            quantity=x.quantity;
            price=x.price;
            is_constructed=x.is_constructed;
        }
        book &operator=(const book &x){
            if(this==&x)
                return *this;
            isbn=x.isbn;
            bookname=x.bookname;
            author=x.author;
            keyword=x.keyword;
            price=x.price;
            quantity=x.quantity;
            is_constructed=x.is_constructed;
            return *this;
        }
};

#endif