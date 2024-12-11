#include <iostream>
#include <sstream>
#include <string>

class Array {
private:
    int* data;
    size_t size;

public:
    Array(size_t size) : size(size) {
        data = new int[size];
    }

    ~Array() {
        delete[] data;
    }

    int& operator[](size_t index) {
        if (index < size) {
            return data[index];
        }
        else {
            throw std::out_of_range("Index out of bounds");
        }
    }

    void operator()(int value) {
        for (size_t i = 0; i < size; ++i) {
            data[i] += value;
        }
    }

    operator int() const {
        int sum = 0;
        for (size_t i = 0; i < size; ++i) {
            sum += data[i];
        }
        return sum;
    }

    operator std::string() const {
        std::ostringstream oss;
        for (size_t i = 0; i < size; ++i) {
            oss << data[i] << ' ';
        }
        return oss.str();
    }
};

int main() {
    Array arr(5);

    for (size_t i = 0; i < 5; ++i) {
        arr[i] = i + 1;
    }

    for (size_t i = 0; i < 5; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;

    arr(10);

    for (size_t i = 0; i < 5; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;

    int sum = arr;
    std::cout << "Sum of array elements: " << sum << std::endl;

    std::string str = arr;
    std::cout << "Array elements as a string: " << str << std::endl;

    return 0;
}
