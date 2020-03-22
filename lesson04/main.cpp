#include <iostream>
#include <vector>
#include <tuple>

struct Element {
    int value;
    int index;
    Element(int _value, int _index) : value(_value), index(_index) {};
};

std::ostream &operator<<(std::ostream& os, const Element& element) {
    os << "[" << element.index << "] " << element.value;
    return os;
}

std::vector<Element> conquer(
    std::vector<Element>::const_iterator begin, 
    std::vector<Element>::const_iterator mid,
    std::vector<Element>::const_iterator end
) {

    std::vector<Element> merged = {};

    std::vector<Element>::const_iterator lhs = begin;
    std::vector<Element>::const_iterator rhs = mid;
    
    while(lhs != mid && rhs != end) {
        if ((*lhs).value < (*rhs).value) {
            merged.push_back((*lhs++));
        } else {
            merged.push_back((*rhs++));
        }
    }

    merged.insert(merged.end(), lhs, mid);    
    merged.insert(merged.end(), rhs, end);

    return std::move(merged);
} 

void merge_divide(std::vector<Element>::iterator begin, std::vector<Element>::iterator end) {
    int remains_length = std::distance(begin, end);

    if (remains_length < 2) {
        return ;
    }

    int step = remains_length / 2;

    const std::vector<Element>::iterator next_begin = begin;
    const std::vector<Element>::iterator next_mid = begin + step;
    const std::vector<Element>::iterator next_end = end;

    // divide
    merge_divide(next_begin, next_mid);
    merge_divide(next_mid, next_end);

    // conquer
    std::vector<Element> merged = conquer(next_begin, next_mid, next_end);

    std::cout << "-----------------" << std::endl;
    for (auto p = merged.begin(); p != merged.end(); p++) {
        std::cout << (*p).value << std::endl;
    }

    std::move(merged.begin(), merged.end(), next_begin);
}

std::vector<Element>::iterator find_nearest_less_or_equal_number(
    std::vector<Element>::iterator begin,
    std::vector<Element>::iterator end,
    int target
) {

    if (target < begin->value)
        throw -1;

    const int length = std::distance(begin, end);

    if (length == 1) {
        return begin;
    }
    
    const int step = length / 2;

    const std::vector<Element>::iterator next_begin = begin;
    const std::vector<Element>::iterator next_mid = begin + step;
    const std::vector<Element>::iterator next_end = end;

    if (next_begin->value == target)
        return next_begin;
    if (next_mid->value == target)
        return next_mid;
    if (next_end->value == target)
        return next_end;

    if (target < next_mid->value) {
        return find_nearest_less_or_equal_number(next_begin, next_mid, target);
    } else {
        return find_nearest_less_or_equal_number(next_mid, next_end, target);
    }
}

int main() {
    std::vector<int> data = {9, 1, 16, 7, 11, 6, 15};
    int target = 28;

    std::vector<Element> array = {};

    for (auto p = data.begin(); p != data.end(); p++) {
        array.push_back(Element(*p, array.size()));
    }

    merge_divide(array.begin(), array.end());

    std::vector<Element>::iterator it = array.end();

    try {
        while (1) {
            auto search_end = find_nearest_less_or_equal_number(array.begin(), it, target);

            if (search_end == array.begin()) {
                break;
            }

            std::cout << "search_end - " <<  *search_end << std::endl;
            if (search_end->value == target)
                throw -1;

            auto ans = find_nearest_less_or_equal_number(array.begin(), search_end, target - search_end->value);
            std::cout << "ans - " <<  *ans << std::endl;

            if (ans->value == target - search_end->value) {
                std::cout << *ans << std::endl;
                break;
            } else {
                if (it == array.begin()) {
                    throw -1;
                }
                it--;
            }
        }
    } catch (int code) {
        std::cout << "execption " << code << std::endl;
        // not found less or equal number
    }

    return 0;
}
