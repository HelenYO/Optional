#include <iostream>
#include <vector>
#include <cassert>
#include "optional.h"


int x;

struct A {
    A() {
        std::cout << "OY\n";
        x = 1;
    }

    A (A const& other){

    }

    ~A() {
        assert(x == 1);
    }
};

int main() {
    {
        //optional<A> a(A());
        A t = A();
        optional<A> a(t);
    }
    //std::cout << x << "\n";
    assert(x == 1);
    std::cout << "asdf" << std::endl;
    return 0;
}

/*
    optional<int> opt(5);
    optional<int> opt2(10);
    optional<int> opt3;
    if(opt<opt2){
        std::cout << "YES\n";
    }
    if(opt && opt) {
        std::cout << "OY YES\n";
    }
    if(!opt3) {
        std::cout << "O MAMA MIA\n";
    }
    opt2.clear();
    opt2 = opt;
    if(opt == opt2) {
        std::cout << "GOOD WORK\n";
    }

    optional<std::vector<int>> opt_vect(*(new std::vector<int>(1)));

    opt_vect->push_back(6);// + "\n";

    std::cout << "GOD   ";
*/

