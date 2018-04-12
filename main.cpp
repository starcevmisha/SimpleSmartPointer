#include <iostream>

//TODO счетчик ссылок

//template<typename T>
//class smart_pointer {
//    void *p;
//public:
//    smart_pointer(T *p) {
//        smart_pointer::p = p;
//    }
//
//    T *operator->() {
//        return p;
//    }
//
//    T*operator=(std::shared_ptr c){
//
//    }
//
//    ~smart_pointer() {
//        delete p;
//    }
//};
template<typename T>
class shared_ptr {
    T *ptr;
    int* refcount;

public:

    int get_refcount(){
        return *refcount;
    }

    shared_ptr() : ptr(nullptr), refcount(nullptr) {};

    shared_ptr(T *ptr) {
        this->ptr = ptr;
        refcount = new int;
        *refcount = 1;
    }

    shared_ptr(const shared_ptr &copy) {
        ptr = copy.ptr;
        refcount = copy.refcount;
        (*refcount)++;
    }

    shared_ptr &operator=(const shared_ptr &copy) {
        ptr = copy.ptr;
        refcount = copy.refcount;
        (*refcount)++;
        return *this;
    }

    T &operator*() {
        return *ptr;
    }

    T *operator->() {
        return ptr;
    }

    ~shared_ptr() {
        (*refcount)--;
        std::cout << *refcount << std::endl;
        if (*refcount == 0) {
            delete refcount;
            delete ptr;
        }
    }
};

class Sth {
    int v = 0;
public:
    void inc() {
        v++;
    }

    void print() {
        std::cout << v << std::endl;
    }

};

int main() {

    shared_ptr<Sth> a = shared_ptr(new Sth());
    a->inc();
    {
        shared_ptr<Sth> b = a;
        std::cout << a.get_refcount() << std::endl;
    }
    std::cout << a.get_refcount() << std::endl;
    return 0;
}