#include <iostream>
#include <string>
#include <cassert>
#include <memory>

template<class T>
class DynamicArray {
private:
    std::unique_ptr<T[]> array;
    std::size_t size;
    std::size_t capacity;
public:
    DynamicArray() : size(0), capacity(1) {
        array = std::make_unique<T[]>(capacity);
    }

    ~DynamicArray() = default;

    explicit DynamicArray(std::size_t capacity) : size(0), capacity(capacity) {
        array = std::make_unique<T[]>(capacity);
    }

    [[nodiscard]] std::size_t getSize() const {
        return size;
    }

    [[nodiscard]] std::size_t getCapacity() const {
        return capacity;
    };

    void resize() {
        auto temp = std::make_unique<T[]>(capacity * 2);
        std::move(array.get(), array.get() + size, temp.get());
        array = std::move(temp);
        capacity *= 2;
    }

    void insertAt(const T &value, std::size_t pos) {
        assert(0 <= pos && pos <= size);
        if (size == capacity) {
            resize();
        }

        if(size != 0){
            for (std::size_t i = size - 1; i >= pos; --i) {
                array[i + 1] = array[i];
            }
        }

        array[pos] = value;
        size++;
    }

    void deleteAt(std::size_t pos) {
        assert(0 <= pos && pos < size);
        size--;
        for (std::size_t i = pos; i < size; i++) {
            array[i] = array[i + 1];
        }
    }

    void append(const T &element) {
        insertAt(element, size);
    }

    T &get(std::size_t pos) {
        return array[pos];
    }

    [[nodiscard]] const T &get(std::size_t pos) const {
        return array[pos];
    }

    void pretty_print() {
        std::cout << "[";
        for (int i = 0; i < size - 1; i++) {
            std::cout << array[i] << ", ";
        }
        if (size) {
            std::cout << array[size - 1];
        }
        std::cout << "]\n";
    }
};

int main() {
    DynamicArray<int> array(1);
    array.append(3);
    array.append(33);
    array.deleteAt(0);
    array.append(-35);
    array.append(5);
    array.append(8);
    array.deleteAt(array.getSize() - 1);
    array.append(8);
    array.pretty_print();

}