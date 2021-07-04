#include <iostream>
#include <algorithm>


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

    //конструктор перемещения (забираем ресурсы у переданного r-value объекта)
    Small_vector(Small_vector<T>&& another_vector) noexcept;

    //оператор присваивания перемещением (забираем ресурсы у переданного r-value объекта)
    Small_vector<T>& operator= (Small_vector<T>&& another_vector) noexcept;

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
    void push_index(const int index, const T value);
     
    //вернуть количество элементов в векторе
    int get_size() const noexcept { return this->size; }
    
    //распечатать вектор
    void print() const noexcept;
    
    //Перегрузка оператораа присваивания
    Small_vector<T>& operator= (const Small_vector<T>& another_vector);
    
    //доступ по индексу
    T& operator[](unsigned index) const noexcept { return this->begin_point[index]; }
 
    //вектора равны, если содержат одинаковую последовательность элементов
    bool operator== (const Small_vector<T>& another_vector) const noexcept;

    //обратный оператор
    bool operator!= (const Small_vector<T>& another_vector)const noexcept { return !this->operator==(another_vector); }

    //удаление указателя на nullptr допустимо
    ~Small_vector() { delete[] begin_point; }

    
private:
    //==========================Класс итератора для нашего Small_vector==========================
    template<typename T>
    class OwnIterator {
        //итератор имеет доступ к приватным полям контейнера
        friend class Small_vector;
    public:
        //стандартизирование названий для интеграции
        // "typedef Iter iterator_type" == "using iterator_type = Iter" - C++11
        using iterator_type = T;
        using iterator_category = std::input_iterator_tag;
        using value_type = iterator_type;
        using difference_type = std::ptrdiff_t;
        using reference = iterator_type&;
        using pointer = iterator_type*;
        
        //указатель на данные в нашем контейнере
        iterator_type* value;
    private:
        //приватный конструктр итератора от указателя
        OwnIterator(iterator_type* point) :value(point) {}
    public:

        //конструктор копирования от другого итератора
        OwnIterator(const OwnIterator& another_iterator) : value(another_iterator.value){}

        //оператор сравнения
        bool operator!=(OwnIterator const& other)const {
            return value != other.value;
        }

        //обратный оператор 
        bool operator==(OwnIterator const& other)const {
            return value == other.value;
        }

        //оператор разыменования
        typename OwnIterator::reference operator*()const { return *value; }

        //префиксный инкремент
        OwnIterator& operator++() {
            ++value;
            return *this;
        }

        //постфиксный инкремент
        const OwnIterator operator++(int) {
            OwnIterator tmp(*this);
            ++value;
            return tmp;
        }

        //префиксный декремент
        OwnIterator& operator--() {
            --value;
            return *this;
        }

        //постфиксный декремент
        const OwnIterator operator--(int) {
            OwnIterator tmp(*this);
            --value;
            return tmp;
        }
    };
public:
    //стандартизирование названий для интеграции
    using iterator = OwnIterator<T>;
    using const_iterator = OwnIterator<const T>;

    //возвращение итератора на первый элемент
    iterator begin() { return iterator(&begin_point[0]); }
    
    //возвращение итератора на элемент за последним
    iterator end() { return iterator(&begin_point[size]); }

    //возвращение константного итератора на первый элемент
    const_iterator begin()const { return const_iterator(begin_point[0]); }
    
    //возвращение константного итератора на элемент за последним
    const_iterator end()const { return const_iterator(begin_point[size]); } 
};

//методы и перегрузки Small_vector:
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
Small_vector<T>::Small_vector(Small_vector<T>&& another_vector) noexcept {
    this->~Small_vector();
    begin_point = another_vector.begin_point;
    another_vector.begin_point = nullptr;
    size = another_vector.size;
    capacity = another_vector.capacity;
    another_vector.size = another_vector.capacity = 0;
}

template<typename T>
Small_vector<T>& Small_vector<T>::operator= (Small_vector<T>&& another_vector) noexcept {
    this->~Small_vector();
    begin_point = another_vector.begin_point;
    another_vector.begin_point = nullptr;
    size = another_vector.size;
    capacity = another_vector.capacity;
    another_vector.size = another_vector.capacity = 0;
    return *this;
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
void Small_vector<T>::push_index(const int index, const T value) {
    //если у нас достаточно выделенной памяти для добавления
    if (size != capacity) {
        ++size;
        for (int i = size; i > index; --i) {
            begin_point[i] = begin_point[i - 1];
        }
        begin_point[index] = value;
    }
    //если для добавления нужно выделить память
    else {
        ++size;
        capacity += (capacity / 2) + 1;
        T* tmp = new T[capacity];
        // сдвигаем всё, что справа от индекса
        for (int i = size; i > index; --i) {
            tmp[i] = begin_point[i - 1];
        }
        //копируем всё, что слева от индекса
        for (int i = 0; i < index; ++i) {
            tmp[i] = begin_point[i];
        }
        tmp[index] = value;
        this->~Small_vector();
        begin_point = tmp;
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
void Small_vector<T>::print() const noexcept {
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
bool Small_vector<T>::operator== (const Small_vector<T>& another_vector) const noexcept {
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
    //тестирование Small_vector:
    Small_vector<int> v;
    const Small_vector<int> v0{ 0, 0, 0 };
    Small_vector<int> v1(v0);
    Small_vector<int> v2(10);
    Small_vector<int> v3(std::move(v1));
    Small_vector<int> v4 = v3;
 
    

    for (int i = 0; i < 10; ++i) {
        v2.push_back(i);
    }
    for (int i = 0; i < 10; ++i) {
        v2.push_front(i);
    }
    for (int i = 0; i < 10; ++i) {
        v2.pop_front();
    }


    for (int i = 0; i < 10; ++i) {
        v4.push_index(2, 100);
    }
    for (int i = 0; i < 10; ++i) {
        v4.pop_index(1);
    }



    v0.print();

    for (auto& it : v2) {
        std::cout << it << '\t';
    }
    std::cout << '\n';

    for (int i = 0; i < v4.get_size(); ++i) {
        std::cout << v4[i] << '\t';
    }
    std::cout << '\n';


    return 0;
}