#include <iostream>

using namespace std;

class foo{
private: unsigned num;

public: foo(unsigned i){
        num = i;
        cout << num << endl;
    }
};

