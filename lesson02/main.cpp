#include <iostream>

#include <type_traits>

class Var {
    int value;
 public:
    Var() { value = 0; }
    
    Var(int value): value(value) {
        std::cout << "Var constructor" << std::endl;
    }

    ~Var() { std::cout << "Var is deleted." << std::endl; }

    void dump() const {
        std::cout << "Var.value:" << this->value << std::endl;
    }
};

class Hoge {
    int value;
 public:
    Hoge() { value = 0; }

    // implicit constructorはよくないらしい．
    // https://rules.sonarsource.com/cpp
    explicit Hoge(int value): value(value) {
        std::cout << "Hoge constructor" << std::endl;
    }

    ~Hoge() { std::cout << "Hoge is deleted." << std::endl; }

    Hoge& operator = (int val) {
        value = val;
        return *this;
    }

    void dump() const {
        std::cout << "Hoge.value:" << this->value << std::endl;
    }
};


class Bar {
    Hoge obj;
    Var obj2;
 public:
    Bar() { obj = 0; obj2 = 0; }
    ~Bar() { std::cout << "Bar is deleted." << std::endl; }

    Hoge& operator() (int value) {
        return obj;
    }

    Var& operator() (std::string str) {
        return obj2;
    }

    void dump() const {
        obj.dump();
        obj2.dump();
    }
};

void do_it() {
    // Bar obj;

    // obj(1) = 15;

    // // explicit
    // obj(1) = Hoge(-10);

    // // implicit
    // obj("@") = 1;

    // obj.dump();

    Var test;
    test = Var(10);
    // test = 10;
}

int main() {
    do_it();
    return 0;
}
