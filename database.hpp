#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#ifndef IOSTREAM
#define IOSTREAM

#include <iostream>

#endif

#ifndef ARRAY
#define ARRAY

#include <array>

#endif

#ifndef VECTOR
#define VECTOR

#include<vector>

#endif

#include "memoryriver.hpp"
#include "node.h"
#include "block.h"
#include "blocklist.h"

template<class T>
class database{
    public:
        string s;
        MemoryRiver<blocked_list<T>,1>mlist;
        MemoryRiver<block<T>,0>mblock;
        void initialise(string s){
            mlist.file_name=s+"1";
            mblock.file_name=s+"2";
            mlist.file.open(s+"1",std::ios::in|std::ios::out|std::ios::binary);
            if(!mlist.file.good()){
                mlist.initialise(s+"1");
                mblock.initialise(s+"2");
                mlist.write_info(-1,1);
            }
            else
                mlist.file.close();
            mlist.sizeofT=sizeof(blocked_list<T>);
            mblock.sizeofT=sizeof(block<T>);
        }

        void print(node<T> a){
            std::cout<<"bookname=";
            for(int i=0;a.name[i];i++)
                std::cout<<a.name[i];
            std::cout<<"\n";
            std::cout<<"bookyear=";
            for(int i=0;a.year[i];i++)
                std::cout<<a.year[i];
            std::cout<<"\n";
        }
        void printall(){
            std::cout<<std::endl;
            int tmp;
            mlist.get_info(tmp,1);
            std::cout<<"head of block is "<<tmp<<std::endl;
            if(tmp==-1){
                std::cout<<"all deleted"<<std::endl;
                return;
            }
            blocked_list<T> p;
            mlist.read(p,tmp);
            int o=0;
            while(1){
                block<T> b;
                mblock.read(b,p.block_pos);
                std::cout<<"block "<<++o<<" size = "<<p.size<<std::endl<<"-----------"<<std::endl;
                for(int i=0;i<p.size;i++)
                    print(b.book[i]);
                std::cout<<"-----------"<<std::endl;
                if(p.next==-1)
                    break;
                else
                    mlist.read(p,p.next);
            }
            std::cout<<std::endl;
        }
        void check_upper(){
            int tmp;
            mlist.get_info(tmp,1);
            if(tmp==-1)
                return;
            blocked_list<T> u;
            mlist.read(u,tmp);
            while(u.size<(maxsz<<1)){
                if(u.next!=-1)
                    mlist.read(u,u.next);
                else
                    break;
            }
            if(u.size==(maxsz<<1)){
                block<T> p;
                mblock.read(p,u.block_pos);
                p.size=maxsz;
                u.size=maxsz;
                mblock.update(p,p.pos);
                blocked_list<T> *q1=new blocked_list<T>;
                q1->size=maxsz;
                q1->next=u.next;
                q1->head=p.book[maxsz];
                q1->block_pos=mblock.get_end();
                q1->pos=mlist.get_end();
                mlist.write(*q1);
                block<T> *q2=new block<T>;
                q2->size=maxsz;
                for(int i=0;i<maxsz;i++)
                    q2->book[i]=p.book[i+maxsz];
                q2->pos=mblock.get_end();
                mblock.write(*q2);
                u.next=q1->pos;
                mlist.update(u,u.pos);
                delete q1;
                delete q2;
            }
        }

        void check_lower(){
            int tmp;
            mlist.get_info(tmp,1);
            if(tmp==-1)
                return;
            blocked_list<T> u,v;
            mlist.read(u,tmp);
            if(u.size==0){
                mlist.write_info(u.next,1);
                return;
            }
            while(u.size){
                v=u;
                if(u.next!=-1)
                    mlist.read(u,u.next);
                else
                    break;
            }
            if(!u.size){
                v.next=u.next;
                mlist.update(v,v.pos);
            }
        }
        void ins(std::array<char,65>arr,std::array<char,65>year,T info){
            node<T> *q=new node<T>;
            q->name=arr;
            q->year=year;
            q->info=info;
            int tmp;
            mlist.get_info(tmp,1);
            if(tmp==-1){
                blocked_list<T> *p=new blocked_list<T>;
                block<T> *p1=new block<T>;
                p1->book[0]=*q;
                p1->pos=mblock.get_end();
                p1->size=1;
                mblock.write(*p1);
                p->block_pos=p1->pos;
                p->head=*q;
                p->size=1;
                p->pos=mlist.get_end();
                mlist.write(*p);
                mlist.write_info(p->pos,1);
                delete p;
                delete p1;
            }
            else{
                blocked_list<T> p,prev;
                mlist.read(p,tmp);
                prev=p;
                while((*q)>p.head){
                    prev=p;
                    if(p.next!=-1)
                        mlist.read(p,p.next);
                    else
                        break;
                }
                prev.size++;
                block<T> b;
                mblock.read(b,prev.block_pos);
                bool flg=false;
                if(!((*q)>b.book[0])){
                    for(int j=b.size;j>0;j--)
                        b.book[j]=b.book[j-1];
                    b.book[0]=*q;
                    prev.head=b.book[0];
                    flg=true;
                }
                else{
                    for(int i=1;i<b.size;i++)
                        if(!((*q)>b.book[i])){
                            for(int j=b.size;j>i;j--)
                                b.book[j]=b.book[j-1];
                            b.book[i]=*q;
                            flg=true;
                            break;
                        }
                }
                b.size++;
                if(!flg)
                    b.book[b.size-1]=*q;
                mblock.update(b,b.pos);
                mlist.update(prev,prev.pos);
            }
            delete q;
            check_upper();
        }

        void del(std::array<char,65>arr,std::array<char,65>year){
            int tmp;
            mlist.get_info(tmp,1);
            if(tmp==-1)
                return;
            blocked_list<T> p,prev;
            mlist.read(p,tmp);
            prev=p;
            node<T> d;
            d.name=arr;
            d.year=year;
            while(d>p.head){
                prev=p;
                if(p.next!=-1)
                    mlist.read(p,p.next);
                else
                    break;
            }
            block<T> b;
            mblock.read(b,prev.block_pos);
            if(b.book[0].name==arr&&b.book[0].year==year){
                for(int j=0;j<prev.size-1;j++)
                    b.book[j]=b.book[j+1];
                b.size--;
                mblock.update(b,b.pos);
                prev.size--;
                if(prev.size)
                    prev.head=b.book[0];
                mlist.update(prev,prev.pos);
            }
            else{
                for(int i=1;i<prev.size;i++)
                    if(b.book[i].name==arr&&b.book[i].year==year){
                        for(int j=i;j<prev.size-1;j++)
                            b.book[j]=b.book[j+1];
                        b.size--;
                        mblock.update(b,b.pos);
                        prev.size--;
                        mlist.update(prev,prev.pos);
                        break;
                    }
            }
            check_lower();
        }

        std::vector<T> query(std::array<char,65>arr){
            std::vector<T>a;
            a.clear();
            int tmp;
            mlist.get_info(tmp,1);
            if(tmp==-1)
                return a;
            blocked_list<T> p,prev;
            mlist.read(p,tmp);
            prev=p;
            while(p.next!=-1){
                prev=p;
                mlist.read(p,p.next);
                if(p.head.name>=arr)
                    break;
            }
            bool up_bound=true;
            block<T> b;
            while(up_bound){
                mblock.read(b,prev.block_pos);
                for(int i=0;i<b.size;i++)
                    if(arr==b.book[i].name)
                        a.push_back(b.book[i].info);
                    else
                        if(b.book[i].name>arr){
                            up_bound=false;
                            break;
                        }
                if(prev.next==-1)
                    break;
                mlist.read(prev,prev.next);
            }
            return a;
        }

        bool find(std::array<char,65>arr,T &a){
            int tmp;
            mlist.get_info(tmp,1);
            if(tmp==-1)
                return false;
            blocked_list<T> p,prev;
            mlist.read(p,tmp);
            prev=p;
            while(p.next!=-1){
                prev=p;
                mlist.read(p,p.next);
                if(p.head.name>=arr)
                    break;
            }
            bool can_find=false,up_bound=true;
            block<T> b;
            while(up_bound){
                mblock.read(b,prev.block_pos);
                for(int i=0;i<b.size;i++)
                    if(arr==b.book[i].name){
                        can_find=true;
                        a=b.book[i].info;
                        return can_find;
                    }
                    else
                        if(b.book[i].name>arr){
                            up_bound=false;
                            break;
                        }
                if(prev.next==-1)
                    break;
                mlist.read(prev,prev.next);
            }
            return can_find;
        }
};

#endif