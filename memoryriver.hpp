#ifndef BPT_MEMORYRIVER_HPP
#define BPT_MEMORYRIVER_HPP

#include <fstream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

template<class T, int info_len = 2>
class MemoryRiver {
public:
    fstream file;
    string file_name;
    int sizeofT;
    MemoryRiver() = default;
    MemoryRiver(const string& file_name) : file_name(file_name) {}
    void initialise(string FN = "") {
        if (FN != "") file_name = FN;
        file.open(file_name, std::ios::out|std::ios::binary);
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }
    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        file.open(file_name,std::ios::in|std::ios::binary);
        file.seekg((n-1)*sizeof(int));
        file.read(reinterpret_cast<char *>(&tmp),sizeof(int));
        file.close();
    }
    void write_info(int tmp, int n) {
        if (n > info_len) return;
        file.open(file_name,std::ios::in|std::ios::out|std::ios::binary);
        file.seekp((n-1)*sizeof(int));
        file.write(reinterpret_cast<char *>(&tmp),sizeof(int));
        file.close();
    }
    int write(T &t) {
        file.open(file_name,std::ios::in|std::ios::out|std::ios::binary);
        file.seekp(0,std::ios::end);
        int lst=file.tellp();
        file.write(reinterpret_cast<char *>(&t),sizeofT);
        file.close();
        return lst;
    }
    int get_end(){
        file.open(file_name,std::ios::in|std::ios::out|std::ios::binary);
        file.seekp(0,std::ios::end);
        int lst=file.tellp();
        file.close();
        return lst;
    }
    void update(T &t, const int index) {
        file.open(file_name,std::ios::in|std::ios::out|std::ios::binary);
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&t),sizeofT);
        file.close();
    }
    void read(T &t, const int index) {
        file.open(file_name,std::ios::in|std::ios::binary);
        file.seekg(index);
        file.read(reinterpret_cast<char *>(&t),sizeofT);
        file.close();
    }
};

#endif //BPT_MEMORYRIVER_HPP