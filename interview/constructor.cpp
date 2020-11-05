#include <iostream>

// g++ -o test -std=c++11 -g -Wall constructor.cpp 
// 只调用一次构造函数, g++ 做了底层优化
// 禁用g++ 优化 g++ -fno-elide-constructors -o test -std=c++11 -g -Wall constructor.cpp
// 1次构造函数, 2次拷贝构造函数 

class T {
public:
    T() {
        std::cout << "conductor" << std::endl;
    }

    T(const T& t) {
        std::cout << "copy conductor" << std::endl;
    }

protected:
    int a;
};

T get_object() {
    return T();
}

int main() {
    T t1 = get_object();
    (void)t1;
    return 0;
}

