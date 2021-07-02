#include <iostream>
#include <string>
#include <WinSock2.h>

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
    void push_front(const T value) {
        //if we have necessary allocated memory
        if (size != capacity) {
            ++size;
            for (int i = size; i > 0; --i) {
                begin_point[i] = begin_point[i - 1];
            }
            begin_point[0] = value;
        }
        else {
            //if we have not necessary allocated memory 
            capacity += (capacity / 2) + 1;

            T* tmp = new T[capacity];
            ++size;
            for (int i = 0; i < size; ++i) {
                tmp[i + 1] = this->begin_point[i];
            }
            
            tmp[0] = value;
            this->~Small_vector();
            this->begin_point = tmp;
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
    Small_vector<T>& operator= (const Small_vector<T>& another_vector) {
        
        this->~Small_vector();
        size = another_vector.size;
        capacity = another_vector.capacity;
        
        begin_point = new T[capacity];
        for (int i = 0; i < size; ++i) {
            this->begin_point[i] = another_vector.begin_point[i];
        }
        return *this;
    }
    T& operator[](unsigned index) {
        return this->begin_point[index];

        }
    bool operator== (const Small_vector<T>& another_vector) {
        if (size == another_vector.size) {
            for (int i = 0; i < size; ++i) {
                if (begin_point[i] != another_vector.begin_point[i])return false;
            }
            return true;
        }
            return false;  
    }
    ~Small_vector() {
       
            delete[] begin_point;
        
    }
};
template<typename T>
class Test {
public:
    Test<T>& operator=(const Test<T>& v) {
        std::cout << "==========" << std::endl;
        return *this;
    }
};


int main() {
    Small_vector<int> v{ 1, 2, 3 };
    
    for (int i = 0; i < 3; ++i) {
        v.push_front(i);
        v.push_back(i);
    }
    
    
  
  
    v.print();
    return 0;
}