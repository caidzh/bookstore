#include<stack>

#ifndef VECTOR
#define VECTOR

#include<vector>

#endif

#include<iomanip>
#include<regex>
#include "database.hpp"
database<account>myaccount;
database<book>myisbn,myname,myauthor,mykeyword;
struct Trade{
    bool type;
    double val;
};
MemoryRiver<Trade,1>finance("finance");
struct account_info{
    account acc;
    bool is_select;
    book select_book;
};
std::stack<account_info>login_account;
std::array<char,65> fsta(const string &s){
    std::array<char,65>arr;
    for(std::string::size_type i=0;i<s.length();i++)
        arr[i]=s[i];
    for(std::string::size_type i=s.length();i<65;i++)
        arr[i]='\0';
    return arr;
}
account create_account(int privilege,bool is_login,std::array<char,65>userid,std::array<char,65>password,std::array<char,65>username){
    account a;
    a.privilege=privilege;
    a.is_login=is_login;
    a.userid=userid;
    a.password=password;
    a.username=username;
    return a;
}
book create_book(int price,double quantity,bool is_constructed,std::array<char,65>isbn,std::array<char,65>bookname,std::array<char,65>author,std::array<char,65>keyword){
    book a;
    a.price=price;
    a.quantity=quantity;
    a.is_constructed=is_constructed;
    a.isbn=isbn;
    a.bookname=bookname;
    a.author=author;
    a.keyword=keyword;
    return a;
}
std::vector<string> sentence_analysis(string all){
    std::vector<string>a;
    string str="";
    for(int i=0;all[i];i++){
        if(all[i]==' '){
            if(str!="")
                a.push_back(str);
            str="";
        }
        else{
            if(all[i]!='|'||(all[i]=='|'&&all[i-1]!=' '&&all[i+1]!=' '))
                str+=all[i];
        }
    }
    if(str!="")
        a.push_back(str);
    return a;
}
std::vector<string>sentence;
int get_privilege(){
    if(login_account.size()==0)
        return -1;
    else
        return login_account.top().acc.privilege;
}
std::vector<string> keyword_analysis(std::array<char,65> all){
    std::vector<string>a;
    string str="";
    for(int i=0;all[i];i++){
        if(all[i]=='|'){
            if(str!="")
                a.push_back(str);
            str="";
        }
        else{
            if(all[i]!='"')
                str+=all[i];
        }
    }
    if(str!="")
        a.push_back(str);
    return a;
}
string equal_analysis(string a){
    bool flg=false;
    string s="";
    for(int i=0;a[i];i++){
        if(flg&&a[i]!='"')
            s+=a[i];
        if(a[i]=='=')
            flg=true;
    }
    return s;
}
string modify_analysis(string a){
    bool flg=true;
    string s="";
    for(int i=0;a[i];i++){
        if(a[i]=='=')
            flg=false;
        if(flg)
            s+=a[i];
    }
    return s;
}
std::vector<string>default_vector;
void insert_book(book a,std::vector<string>keyword){
    myisbn.ins(a.isbn,N,a);
    myname.ins(a.bookname,a.isbn,a);
    myauthor.ins(a.author,a.isbn,a);
    for(std::vector<std::string>::size_type i=0;i<keyword.size();i++)
        mykeyword.ins(fsta(keyword[i]),a.isbn,a);
}
void delete_book(book a,std::vector<string>keyword){
    myisbn.del(a.isbn,N);
    myname.del(a.bookname,a.isbn);
    myauthor.del(a.author,a.isbn);
    for(std::vector<std::string>::size_type i=0;i<keyword.size();i++)
        mykeyword.del(fsta(keyword[i]),a.isbn);
}
int stringToInt(const std::string &str) {
    if(str[0]=='-')
        return -1;
    try {
        return std::stoi(str);
    } catch (const std::exception&) {
        return -1;
    }
}
double stringToDouble(const std::string &str) {
    if(str[0]=='-')
        return -1;
    try {
        return std::stod(str);
    } catch (const std::exception&) {
        return -1.0;
    }
}
void print(book a){
    for(int j=0;a.isbn[j];j++)
        std::cout<<a.isbn[j];
    std::cout<<"\t";
    for(int j=0;a.bookname[j];j++)
        std::cout<<a.bookname[j];
    std::cout<<"\t";
    for(int j=0;a.author[j];j++)
        std::cout<<a.author[j];
    std::cout<<"\t";
    for(int j=0;a.keyword[j];j++)
        std::cout<<a.keyword[j];
    std::cout<<"\t";
    std::cout<<std::fixed<<std::setprecision(2)<<a.price<<"\t";
    std::cout<<a.quantity<<"\n";
}
void printall(){
    int tmp;
    myisbn.mlist.get_info(tmp,1);
    if(tmp==-1){
        std::cout<<"\n";
        return;
    }
    blocked_list<book> p;
    myisbn.mlist.read(p,tmp);
    while(1){
        block<book> b;
        myisbn.mblock.read(b,p.block_pos);
        for(int i=0;i<p.size;i++)
            print(b.book[i].info);
        if(p.next==-1)
            break;
        else
            myisbn.mlist.read(p,p.next);
    }
}
void finance_insert(Trade &a){
    int b;
    finance.get_info(b,1);
    b++;
    finance.write_info(b,1);
    finance.write(a);
}
void finance_init(){
    finance.file.open("finance",std::ios::in|std::ios::out|std::ios::binary);
    if(!finance.file.good()){
        finance.initialise("finance");
        finance.write_info(0,1);
    }
    else
        finance.file.close();
    finance.sizeofT=sizeof(Trade);
}
bool check_call_valid(std::vector<string>&s,int mn,int mx){
    if((int)(s.size())>=mn&&(int)(s.size())<=mx)
        return true;
    return false;
}
void refresh_account_and_book(){
    if(login_account.size()){
        myaccount.find(login_account.top().acc.userid,login_account.top().acc);
        if(login_account.top().is_select)
            myisbn.find(login_account.top().select_book.isbn,login_account.top().select_book);
    }
}
int main(){
    // freopen("1.in","r",stdin);
    // freopen("test.out","w",stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    myaccount.initialise("account");
    myisbn.initialise("isbn");
    myname.initialise("name");
    myauthor.initialise("author");
    mykeyword.initialise("keyword");
    finance_init();
    myaccount.ins(fsta("root"),fsta("sjtu"),create_account(7,false,fsta("root"),fsta("sjtu"),fsta("admin")));
    string s;
    std::getline(std::cin,s);
    while(s!="exit"&&s!="quit"){
        bool can=false;
        sentence=sentence_analysis(s);
        // 仅有空格的指令
        if(sentence.size()==0)
            continue;
        // std::cout<<s<<std::endl;
        //myisbn.printall();
        // # 帐户系统指令
        // {0} su [UserID] ([Password])?
        if(sentence[0]=="su"){
            if(check_call_valid(sentence,2,3)){
                can=true;
                account a;
                if(!myaccount.find(fsta(sentence[1]),a))
                    std::cout<<"Invalid\n";
                else{
                    if((get_privilege()<=a.privilege&&(sentence.size()>2&&fsta(sentence[2])==a.password))||get_privilege()>a.privilege){
                        myaccount.del(a.userid,a.password);
                        a.is_login++;
                        myaccount.ins(a.userid,a.password,a);
                        account_info b;
                        b.acc=a;
                        b.is_select=false;
                        login_account.push(b);
                    }
                    else
                        std::cout<<"Invalid\n";
                }
            }
        }
        // {1} logout
        if(sentence[0]=="logout"){
            if(check_call_valid(sentence,1,1)){
                can=true;
                if(get_privilege()<1||login_account.size()==0)
                    std::cout<<"Invalid\n";
                else{
                    account a=login_account.top().acc;
                    myaccount.find(a.userid,a);
                    a.is_login--;
                    myaccount.del(a.userid,a.password);
                    myaccount.ins(a.userid,a.password,a);
                    login_account.pop();
                }
            }
        }
        // {0} register [UserID] [Password] [Username]
        if(sentence[0]=="register"){
            if(check_call_valid(sentence,4,4)){
                can=true;
                account a;
                if(myaccount.find(fsta(sentence[1]),a))
                    std::cout<<"Invalid\n";
                else
                    myaccount.ins(fsta(sentence[1]),fsta(sentence[2]),create_account(1,false,fsta(sentence[1]),fsta(sentence[2]),fsta(sentence[3])));
            }
        }
        // {1} passwd [UserID] ([CurrentPassword])? [NewPassword]
        if(sentence[0]=="passwd"){
            if(check_call_valid(sentence,3,4)){
                can=true;
                if(get_privilege()<1||(get_privilege()<7&&sentence.size()<4))
                    std::cout<<"Invalid\n";
                else{
                    account a;
                    if(!myaccount.find(fsta(sentence[1]),a))
                        std::cout<<"Invalid\n";
                    else{
                        if(get_privilege()<7&&a.password!=fsta(sentence[2]))
                            std::cout<<"Invalid\n";
                        else{
                            myaccount.del(a.userid,a.password);
                            if(sentence.size()==3)
                                a.password=fsta(sentence[2]);
                            else
                                a.password=fsta(sentence[3]);
                            myaccount.ins(a.userid,a.password,a);
                        }
                    }
                }
            }
        }
        // {3} useradd [UserID] [Password] [Privilege] [Username]
        if(sentence[0]=="useradd"){
            if(check_call_valid(sentence,5,5)){
                can=true;
                if(get_privilege()<3||get_privilege()<=sentence[3][0]-'0')
                    std::cout<<"Invalid\n";
                else{
                    account a;
                    if(myaccount.find(fsta(sentence[1]),a))
                        std::cout<<"Invalid\n";
                    else
                        myaccount.ins(fsta(sentence[1]),fsta(sentence[2]),create_account(sentence[3][0]-'0',false,fsta(sentence[1]),fsta(sentence[2]),fsta(sentence[4])));
                }
            }
        }
        // {7} delete [UserID]
        if(sentence[0]=="delete"){
            if(check_call_valid(sentence,2,2)){
                can=true;
                if(get_privilege()<7)
                    std::cout<<"Invalid\n";
                else{
                    account a;
                    if(!myaccount.find(fsta(sentence[1]),a))
                        std::cout<<"Invalid\n";
                    else{
                        if(a.is_login)
                            std::cout<<"Invalid\n";
                        else
                            myaccount.del(a.userid,a.password);
                    }
                }
            }
        }
        // # 图书系统指令
        // {1} buy [ISBN] [Quantity]
        if(sentence[0]=="buy"){
            if(check_call_valid(sentence,3,3)){
                can=true;
                if(get_privilege()<1)
                    std::cout<<"Invalid\n";
                else{
                    book a;
                    if(!myisbn.find(fsta(sentence[1]),a))
                        std::cout<<"Invalid\n";
                    else{
                        if(stringToInt(sentence[2])<=0)
                            std::cout<<"Invalid\n";
                        else{
                            int num=stringToInt(sentence[2]);
                            if(num>a.quantity)
                                std::cout<<"Invalid\n";
                            else{
                                std::cout<<std::fixed<<std::setprecision(2)<<num*a.price<<"\n";
                                delete_book(a,keyword_analysis(a.keyword));
                                a.quantity-=num;
                                insert_book(a,keyword_analysis(a.keyword));
                                Trade b;
                                b.type=0;
                                b.val=num*a.price;
                                finance_insert(b);
                            }
                        }
                    }
                }
            }
        }
        // {3} select [ISBN]
        if(sentence[0]=="select"){
            if(check_call_valid(sentence,2,2)){
                can=true;
                if(get_privilege()<3)
                    std::cout<<"Invalid\n";
                else{
                    book a;
                    if(!myisbn.find(fsta(sentence[1]),a)){
                        a=create_book(0,0,false,fsta(sentence[1]),N,N,N);
                        insert_book(a,default_vector);
                        login_account.top().is_select=true;
                        login_account.top().select_book=a;
                    }
                    else{
                        login_account.top().is_select=true;
                        login_account.top().select_book=a;
                    }
                }
            }
        }
        // {3} modify (-ISBN=[ISBN] | -name="[BookName]" | -author="[Author]" | -keyword="[Keyword]" | -price=[Price])+
        if(sentence[0]=="modify"){
            if(check_call_valid(sentence,2,6)){
                bool valid=true;
                for(std::vector<std::string>::size_type i=1;i<sentence.size();i++){
                    string call=modify_analysis(sentence[i]);
                    if(call!="-ISBN"&&call!="-name"&&call!="-author"&&call!="-keyword"&&call!="-price")
                        valid=false;
                }
                if(valid){
                    can=true;
                    if(get_privilege()<3||!login_account.top().is_select)
                        std::cout<<"Invalid\n";
                    else{
                        bool is_repeated=false,is_blanked=false;
                        for(std::vector<std::string>::size_type i=1;i<sentence.size();i++)
                            if(sentence[i][sentence[i].size()-1]=='=')
                                is_blanked=true;
                        for(std::vector<std::string>::size_type i=1;i<sentence.size();i++)
                            for(std::vector<std::string>::size_type j=i+1;j<sentence.size();j++)
                                if(sentence[i][1]==sentence[j][1])
                                    is_repeated=true;
                        if(is_repeated||is_blanked)
                            std::cout<<"Invalid\n";
                        else{
                            bool isbn_repeated=false,keyword_repeated=false,is_price_illegal=false;
                            for(std::vector<std::string>::size_type i=1;i<sentence.size();i++)
                                if(sentence[i][1]=='I'){
                                    string val=equal_analysis(sentence[i]);
                                    book a;
                                    if(fsta(val)==login_account.top().select_book.isbn||myisbn.find(fsta(val),a))
                                        isbn_repeated=true;
                                }
                            for(std::vector<std::string>::size_type i=1;i<sentence.size();i++)
                                if(sentence[i][1]=='k'){
                                    string val=equal_analysis(sentence[i]);
                                    std::vector<string>key=keyword_analysis(fsta(val));
                                    for(std::vector<std::string>::size_type j=0;j<key.size();j++)
                                        for(std::vector<std::string>::size_type k=j+1;k<key.size();k++)
                                            if(key[j]==key[k])
                                                keyword_repeated=true;
                                }
                            for(std::vector<std::string>::size_type i=1;i<sentence.size();i++)
                                if(sentence[i][1]=='p'){
                                    string price=equal_analysis(sentence[i]);
                                    double val=stringToDouble(price);
                                    if(val==-1.0)
                                        is_price_illegal=true;
                                }
                            if(isbn_repeated||keyword_repeated||is_price_illegal)
                                std::cout<<"Invalid\n";
                            else{
                                std::vector<string>key=keyword_analysis(login_account.top().select_book.keyword);
                                delete_book(login_account.top().select_book,key);
                                for(std::vector<std::string>::size_type i=1;i<sentence.size();i++){
                                    string what=modify_analysis(sentence[i]),val=equal_analysis(sentence[i]);
                                    if(what[1]=='I')
                                        login_account.top().select_book.isbn=fsta(val);
                                    if(what[1]=='n')
                                        login_account.top().select_book.bookname=fsta(val);
                                    if(what[1]=='a')
                                        login_account.top().select_book.author=fsta(val);
                                    if(what[1]=='k')
                                        login_account.top().select_book.keyword=fsta(val);
                                    if(what[1]=='p')
                                        login_account.top().select_book.price=stringToDouble(val);
                                }
                                key=keyword_analysis(login_account.top().select_book.keyword);
                                insert_book(login_account.top().select_book,key);
                            }
                        }
                    }
                }
            }
        }
        // {3} import [Quantity] [TotalCost]
        if(sentence[0]=="import"){
            if(check_call_valid(sentence,3,3)){
                can=true;
                if(!login_account.top().is_select||get_privilege()<3)
                    std::cout<<"Invalid\n";
                else{
                    if(stringToInt(sentence[1])<=0||stringToDouble(sentence[2])<=0)
                        std::cout<<"Invalid\n";
                    else{
                        int num=stringToInt(sentence[1]);
                        delete_book(login_account.top().select_book,keyword_analysis(login_account.top().select_book.keyword));
                        login_account.top().select_book.quantity+=num;
                        insert_book(login_account.top().select_book,keyword_analysis(login_account.top().select_book.keyword));
                        Trade a;
                        a.type=1;
                        a.val=stringToDouble(sentence[2]);
                        finance_insert(a);
                    }
                }
            }
        }
        if(sentence[0]=="show"){
            // # 日志系统指令
            // {7} show finance ([Count])?
            if(sentence.size()>1&&sentence[1]=="finance"){
                if(check_call_valid(sentence,2,3)){
                    can=true;
                    if(get_privilege()<7)
                        std::cout<<"Invalid\n";
                    else{
                        int las;
                        if(sentence.size()==3)
                            las=stringToInt(sentence[2]);
                        else
                            finance.get_info(las,1);
                        int total;
                        finance.get_info(total,1);
                        if(total<las)
                            std::cout<<"Invalid\n";
                        else{
                            Trade a;
                            double income=0,expenditure=0;
                            for(int i=1;i<=las;i++){
                                finance.file.open("finance",std::ios::in|std::ios::binary);
                                finance.file.seekg(-i*sizeof(Trade),std::ios::end);
                                finance.file.read(reinterpret_cast<char *>(&a),sizeof(Trade));
                                finance.file.close();
                                if(a.type==0)
                                    income+=a.val;
                                else
                                    expenditure+=a.val;
                            }
                            std::cout<<"+ "<<std::fixed<<std::setprecision(2)<<income<<" - "<<std::fixed<<std::setprecision(2)<<expenditure<<"\n";
                        }
                    }
                }
            }
            // {1} show (-ISBN=[ISBN] | -name="[BookName]" | -author="[Author]" | -keyword="[Keyword]")?
            else{
                if(check_call_valid(sentence,1,2)){
                    can=true;
                    if(get_privilege()<1)
                        std::cout<<"Invalid\n";
                    else{
                        if(sentence.size()<2)
                            printall();
                        else{
                            if(sentence[1][sentence[1].size()-1]=='=')
                                std::cout<<"Invalid\n";
                            else{
                                string key=equal_analysis(sentence[1]);
                                string call=modify_analysis(sentence[1]);
                                if(call=="-ISBN"){
                                    book a;
                                    if(!myisbn.find(fsta(key),a))
                                        std::cout<<"\n";
                                    else
                                        print(a);
                                }
                                else if(call=="-name"){
                                    std::vector<book>a;
                                    a=myname.query(fsta(key));
                                    if(a.size()==0)
                                        std::cout<<"\n";
                                    else{
                                        for(std::vector<book>::size_type i=0;i<a.size();i++)
                                            print(a[i]);
                                    }
                                }
                                else if(call=="-author"){
                                    std::vector<book>a;
                                    a=myauthor.query(fsta(key));
                                    if(a.size()==0)
                                        std::cout<<"\n";
                                    else{
                                        for(std::vector<book>::size_type i=0;i<a.size();i++)
                                            print(a[i]);
                                    }
                                }
                                else if(call=="-keyword"){
                                    std::vector<string>key1=keyword_analysis(fsta(key));
                                    if(key1.size()>1)
                                        std::cout<<"Invalid\n";
                                    else{
                                        std::vector<book>a;
                                        a=mykeyword.query(fsta(key));
                                        if(a.size()==0)
                                            std::cout<<"\n";
                                        else{
                                            for(std::vector<book>::size_type i=0;i<a.size();i++){
                                                book b;
                                                myisbn.find(a[i].isbn,b);
                                                print(b);
                                            }
                                        }
                                    }
                                }
                                else
                                    std::cout<<"Invalid\n";
                            }
                        }
                    }
                }
            }
        }
        if(!can)
            std::cout<<"Invalid\n";
        if(!std::getline(std::cin,s))
            break;
        refresh_account_and_book();
    }
    return 0;
}