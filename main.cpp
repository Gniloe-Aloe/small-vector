#include <iostream>


template<typename T>
class Small_vector {

    T* begin_point;
    int size;
    int capacity;
public:

    Small_vector() {
        begin_point = nullptr;
        size = 0;
        capacity = 0;
    }
    Small_vector(const int capacity) {
        size = 0;
        this->capacity = capacity;
        begin_point = new T[capacity];
    }
    Small_vector(const Small_vector<T>& another_vector) {
        size = another_vector.size;
        capacity = another_vector.capacity;
        this->~Small_vector();
        begin_point = new T[capacity];
        for (int i = 0; i < size; ++i) {
            this->begin_point[i] = another_vector.begin_point[i];
        }
    }
    Small_vector(const std::initializer_list<T> list) {
        this->~Small_vector();
        this->capacity = this->size = list.size();
        const T* pl = list.begin();
        begin_point = new T[capacity];
        for (int i = 0; i < size; ++i) {
            this->begin_point[i] = *(pl + i);
        }
    }
    void push_back(const T value) {
        if (size != capacity) {
            this->begin_point[size++] = value;
        }
        else {
            capacity += (capacity / 2) + 1;
            T* tmp = new T[capacity];
            for (int i = 0; i < size; ++i) {
                tmp[i] = begin_point[i];
            }
            this->~Small_vector();
            begin_point = tmp;
            this->begin_point[size++] = value;
        }
        
    }
    int get_size() const {
        return this->size;
    }
    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << begin_point[i] << '\t';
        }
        std::cout << '\n';
    }
    T& operator[](unsigned index) {
        return this->begin_point[index];
        }
    ~Small_vector() {
            delete[] begin_point;   
    }
};


int main() {
    Small_vector<int> v(3);
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    Small_vector<int> v1(v);
    
    Small_vector<int> v2{ 1, 2, 3 };
    
    
    v.print();
    v1.print();
    v2.print();

    const Small_vector<int> v3{ 1, 2, 3 };
    v3.print();

    return 1;
