#include <iostream>

#include <type_traits>

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
 public:
    Bar() { obj = 0; }
    ~Bar() { std::cout << "Bar is deleted." << std::endl; }

    Hoge& operator() (int value) {
        return obj;
    }

    void dump() const {
        obj.dump();
    }
};

void do_it() {
    Bar obj;

    // Hoge a = 1;

    obj(1) = 15;
    obj(1) = Hoge(-10);

    obj.dump();
}

int main() {
    do_it();
    return 0;
}
