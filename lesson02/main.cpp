#include <iostream>

#include <type_traits>

class Hoge {
    int value;
 public:
    Hoge() { value = 0; }

    Hoge& operator = (int val) {
        value = val;
        return *this;
    }

    void dump() const {
        std::cout << this->value << std::endl;
    }
};


class Bar {
    Hoge *obj;
 public:
    Bar() { obj = new Hoge(); }

    Hoge& operator() (int value) {
        return *obj;
    }

    void dump() const {
        obj->dump();
    }
};

int main() {
    Bar obj;

    obj(1) = 11;　 // Hogeを暗黙のconstructorにしたらどうなるかしら

    obj.dump();

    return 0;
}
