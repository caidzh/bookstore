#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#ifndef ARRAY
#define ARRAY

#include<array>

#endif

#ifndef _BOOK_H
#define _BOOK_H

#include<book.h>

#endif

class account{
    public:
        int privilege;
        bool is_login;
        std::array<char,65>userid,password,username;
        account(){
            privilege=-1;
            is_login=false;
            userid=N;
            password=N;
            username=N;
        }
        account(const int privilege,bool is_login,std::array<char,65>userid,std::array<char,65>password,std::array<char,65>username):
            privilege(privilege),is_login(is_login),userid(userid),password(password),username(username){}
        account(const account &x){
            privilege=x.privilege;
            is_login=x.is_login;
            userid=x.userid;
            password=x.password;
            username=x.username;
        }
        account &operator=(const account &x){
            if(this==(&x))
                return *this;
            privilege=x.privilege;
            is_login=x.is_login;
            userid=x.userid;
            password=x.password;
            username=x.username;
            return (*this);
        }
};

#endif