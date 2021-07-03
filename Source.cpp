#include <iostream>
#include <string>
#include <WinSock2.h>

template<typename T>
class Small_vector {
private:
    T* begin_point;
    int size;
    int capacity;
public:
    //Конструктор по умолчанию
    Small_vector();

    //Конструктор с зарезервированной памятью
    Small_vector(const int capacity);

    //Конструктор от другого вектора
    Small_vector(const Small_vector<T>& another_vector);

    //Конструктор от списка инициализации {1, 2, 3 ..}
    Small_vector(const std::initializer_list<T> list);

    //добавить элемент в конец
    void push_back(const T value);

    //добавить в начало
    void push_front(const T value);

    //удалить последний
    void pop_back() { --size;}
    
    //удалить первый
    void pop_front();

    //удаление по индексу
    void pop_index(const int index);

    //добавление перед элементом под переданным индексом
    void push_index(const int index) {
        //если у нас достаточно выделенной памяти для добавления
        if (size != capacity) {
            
        }
        //если для добавления нужно выделить память
        else {

        }
    }
    
    //вернуть количество элементов в векторе
    int get_size() const { return this->size; }
    
    //распечатать вектор
    void print() const;
    
    //Перегрузка оператораа присваивания
    Small_vector<T>& operator= (const Small_vector<T>& another_vector);
    
    //доступ по индексу
    T& operator[](unsigned index) const { return this->begin_point[index]; }
 
    //вектора равны, если содержат одинаковую последовательность элементов
    bool operator== (const Small_vector<T>& another_vector) const;

    //удаление указателя на nullptr допустимо
    ~Small_vector() { delete[] begin_point; }
};

template<typename T>
Small_vector<T>::Small_vector() {
    begin_point = nullptr;
    size = 0;
    capacity = 0;
}

template<typename T>
Small_vector<T>::Small_vector(const int capacity) {
    size = 0;
    this->capacity = capacity;
    begin_point = new T[capacity];
}

template<typename T>
Small_vector<T>::Small_vector(const Small_vector<T>& another_vector) {
    size = another_vector.size;
    capacity = another_vector.capacity;
    this->~Small_vector();
    begin_point = new T[capacity];
    for (int i = 0; i < size; ++i) {
        this->begin_point[i] = another_vector.begin_point[i];
    }
}

template<typename T>
Small_vector<T>::Small_vector(const std::initializer_list<T> list) {
    this->capacity = this->size = list.size();
    const T* pl = list.begin();
    begin_point = new T[capacity];
    for (int i = 0; i < size; ++i) {
        this->begin_point[i] = *(pl + i);
    }
}

template<typename T>
void Small_vector<T>::push_back(const T value) {
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

template<typename T>
void Small_vector<T>::push_front(const T value) {
    //if we have necessary allocated memory
    if (size != capacity) {

        for (int i = size; i > 0; --i) {
            begin_point[i] = begin_point[i - 1];
        }
        ++size;
        begin_point[0] = value;
    }
    else {
        //if we have not necessary allocated memory 
        this->capacity += (capacity / 2) + 1;

        T* tmp = new T[capacity];
        for (int i = size; i > 0; --i) {
            tmp[i] = begin_point[i - 1];
        }
        tmp[0] = value;
        ++size;
        this->~Small_vector();
        begin_point = tmp;
    }
}

template<typename T>
void Small_vector<T>::print() const {
    for (int i = 0; i < size; ++i) {
        std::cout << begin_point[i] << '\t';
    }
    std::cout << '\n';
}

template<typename T>
Small_vector<T>& Small_vector<T>::operator= (const Small_vector<T>& another_vector) {

    this->~Small_vector();
    size = another_vector.size;
    capacity = another_vector.capacity;

    begin_point = new T[capacity];
    for (int i = 0; i < size; ++i) {
        this->begin_point[i] = another_vector.begin_point[i];
    }
    return *this;
}

template<typename T>
bool Small_vector<T>::operator== (const Small_vector<T>& another_vector) const {
    if (size == another_vector.size) {
        for (int i = 0; i < size; ++i) {
            if (begin_point[i] != another_vector.begin_point[i])return false;
        }
        return true;
    }
    return false;
}

template<typename T>
void Small_vector<T>::pop_front() {
    for (int i = 0; i < size; ++i) {
        begin_point[i] = begin_point[i + 1];
    }
    --size;
}

template<typename T>
void Small_vector<T>::pop_index(const int index) {
    for (int i = index; i < size; ++i) {
        begin_point[i] = begin_point[i + 1];
    }
    if (index < size)--size;
}


int main() {
   
    
    Small_vector<int> v1{ 1, 2, 3 };
    
    
    for (int i = 0; i < 1000; ++i) {
        v1.push_back(i);
        v1.pop_front();
        v1.push_front(i);
        v1.pop_back();
    }
  
  
    v1.print();
    return 0;
}