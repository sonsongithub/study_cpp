#include <iostream>
#include <vector>
#include <tuple>

void hoge(std::vector<double> a) {
    std::cout << "double" << std::endl;
}

void hoge(std::vector<int> a) {
    std::cout << "int" << std::endl;
}

template <typename... Args>
int do_it_int(Args&&... args) {
    std::vector<int> collected_args{std::forward<Args>(args)...};

    hoge(collected_args);

    return 0;
}

int main() {

    do_it_int(1, 11, 3);

    std::cout << "ok" << std::endl;

    return 0;
}
