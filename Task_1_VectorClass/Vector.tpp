#include "Vector.h"
#include <cstddef>


template<typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}


template<typename T>
Vector<T>::Vector(size_t n) : data_(nullptr), size_(n), capacity_(n) {
    try {
        data_ = new T[n];
        for (size_t i = 0; i < n; ++i) {
            data_[i] = T();
        }
    } 
    catch (const std::bad_alloc& e) {
        delete[] data_;
        std::cerr << "Not enough memory for " << n << " elements" << std::endl;
        throw;
    }
}


template<typename T>
Vector<T>::Vector(size_t n, const T& value) : data_(nullptr), size_(n), capacity_(n) {
    try {
        data_ = new T[n];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = value;
        }
    } 
    catch (const std::bad_alloc& e) {
        delete[] data_;
        std::cerr << "Not enough memory for " << n << " elements" << std::endl;
        throw;
    }
}


template<typename T>
Vector<T>::Vector(const Vector& other) : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
    try {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    } 
    catch (const std::bad_alloc& e) {
        delete[] data_;
        std::cerr << "Not enough memory for " << capacity_ << " elements" << std::endl;
        throw;
    }
}


template<typename T>
Vector<T>::Vector(Vector&& other) noexcept 
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}


template<typename T>
Vector<T>::~Vector() {
    delete[] data_;
}


template<typename T>
void Vector<T>::swap(Vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}


template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        Vector<T> t(other);  
        swap(t);   
    }
    return *this;
}


template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        swap(other); 
    }
    return *this;
}


template<typename T>
size_t Vector<T>::size() const {
    return size_;
}

template<typename T>
size_t Vector<T>::capacity() const {
    return capacity_;
}

template<typename T>
bool Vector<T>::empty() const {
    return size_ == 0;
}


template<typename T>
T& Vector<T>::operator[](size_t index) {
    return data_[index];
}

template<typename T>
T& Vector<T>::at(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Vector::at(): index out of range");
    }
    return data_[index];
}

template<typename T>
T& Vector<T>::front() {
    return data_[0];
}

template<typename T>
T& Vector<T>::back() {
    return data_[size_ - 1];
}


template<typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        
        Vector<T> temp;

        try {
            temp.data_ = new T[new_capacity];
            temp.capacity_ = new_capacity;

            for (size_t i = 0; i < size_; ++i) {
                temp.data_[i] = data_[i];
                temp.size_++;
            }
            
            temp.data_[size_] = value;
            temp.size_++;
        }        
        catch (const std::bad_alloc& e) {
            delete[] temp.data_;
            std::cerr << "Memory allocation error in push_back: " << e.what() << std::endl;
            throw;
        }
        catch (const std::exception& e) {
            delete[] temp.data_;
            std::cerr << "Element copy error in push_back: " << e.what() << std::endl;
            throw;
        }
        catch (...) {
            delete[] temp.data_;
            std::cerr << "Unknown error in push_back" << std::endl;
            throw;
        }

        swap(temp);
    }
    else {
        try {
            data_[size_] = value;
            ++size_;
        }
        catch (const std::exception& e) {
            std::cerr << "Element copy error in push_back: " << e.what() << std::endl;
            throw;
        }
    }
}

template <typename T>
void Vector<T>::push_back(T&& value) {
    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        
        Vector<T> temp;

        try {
            temp.data_ = new T[new_capacity];
            temp.capacity_ = new_capacity;

            for (size_t i = 0; i < size_; ++i) {
                temp.data_[i] = std::move(data_[i]);
                temp.size_++;
            }

            temp.data_[size_] = std::move(value);
            temp.size_++;
        }
        catch (const std::bad_alloc& e) {
            delete[] temp.data_;
            std::cerr << "Memory allocation error in push_back: " << e.what() << std::endl;
            throw;
        }
        catch (const std::exception& e) {
            delete[] temp.data_;
            std::cerr << "Element move error in push_back: " << e.what() << std::endl;
            throw;
        }
        catch (...) {
            delete[] temp.data_;
            std::cerr << "Unknown error" << std::endl;
            throw;
        }

        swap(temp);
    }
    else {
        try {
            data_[size_] = std::move(value);
            ++size_;
        }
        catch (const std::exception& e) {
            std::cerr << "Element move error in push_back: " << e.what() << std::endl;
            throw;
        }
    }
}


template <typename T>
void Vector<T>::pop_back() {
    if (size_ > 0) {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            data_[size_ - 1].~T();
        }
        --size_;
    }
}

template <typename T>
void Vector<T>::clear() {
    if constexpr (!std::is_trivially_destructible_v<T>) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
    }
    size_ = 0; 
}


template <typename T>
void Vector<T>::reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    T* new_data = new T[new_capacity];

    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move_if_noexcept(data_[i]);
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

template<class T>
void Vector<T>::shrink_to_fit() {
    if (size_ == capacity_) {
        return;
    }

    T* temp = new T[size_];
    for (size_t i = 0; i < size_; ++i) {
        temp[i] = data_[i];
    }

    delete[] data_;
    data_ = temp;
    capacity_ = size_;
}

template<typename T>
void Vector<T>::resize(size_t new_size) {
    if (new_size < size_) {
        for (size_t i = new_size; i < size_; ++i) {
            data_[i].~T();
        }
        size_ = new_size;
    }
    else if (new_size > size_) {
        if (new_size > capacity_) {
            reserve(new_size);
        }

        for (size_t i = size_; i < new_size; ++i) {
            data_[i] = T();
        }
        size_ = new_size;
    }
}

template<typename T>
void Vector<T>::resize(size_t new_size, const T& value) {
    if (new_size < size_) {
        for (size_t i = new_size; i < size_; ++i) {
            data_[i].~T(); 
        }
        size_ = new_size;
    }
    else if (new_size > size_) {
        if (new_size > capacity_) {
            reserve(new_size);
        }

        for (size_t i = size_; i < new_size; ++i) {
            data_[i] = value;  
        }
        size_ = new_size;
    }
}


template<typename T>
bool Vector<T>::operator==(const Vector& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector& other) const {
    return !(*this == other);
}

template<typename T>
bool Vector<T>::operator<(const Vector& other) const {
    for (size_t i = 0; i < size_ && i < other.size_; ++i) {
        if (data_[i] < other.data_[i]) return true;
        if (other.data_[i] < data_[i]) return false;
    }
    return size_ < other.size_;
}

template<typename T>
bool Vector<T>::operator<=(const Vector& other) const {
    return !(other < *this);
}

template<typename T>
bool Vector<T>::operator>(const Vector& other) const {
    return other < *this;
}

template<typename T>
bool Vector<T>::operator>=(const Vector& other) const {
    return !(*this < other);
}


template <typename T>
void Vector<T>::insert(size_t index, const T& value) {
    if (index > size_) {
        throw std::out_of_range("Vector::insert(): index out of range");    
    }

    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;

        Vector<T> temp;

        try {
            temp.data_ = new T[new_capacity];
            temp.capacity_ = new_capacity;

            for (size_t i = 0; i < index; ++i) {
                temp.data_[i] = data_[i];
                temp.size_++;
            }

            temp.data_[index] = value;
            temp.size_++;

            for (size_t i = index; i < size_; ++i) {
                temp.data_[i + 1] = data_[i];
                temp.size_++;
            }
        }
        catch (const std::bad_alloc& e) {
            delete[] temp.data_;
            std::cerr << "Memory allocation error in insert: " << e.what() << std::endl;
            throw;
        }
        catch (const std::exception& e) {
            delete[] temp.data_;
            std::cerr << "Element copy error in insert: " << e.what() << std::endl;
            throw;
        }
        catch (...) {
            delete[] temp.data_;
            std::cerr << "Unknown error in insert" << std::endl;
            throw;
        }

        swap(temp);
    }
    else {
        try {
            for (size_t i = size_; i > index; --i) {
                data_[i] = std::move_if_noexcept(data_[i - 1]);
            }
            data_[index] = value;
            ++size_;
        }
        catch (const std::exception& e) {
            std::cerr << "Element shift error in insert: " << e.what() << std::endl;
            throw;
        }
    }
}

template <typename T>
void Vector<T>::insert(size_t index, T&& value) {
    if (index > size_) {
        throw std::out_of_range("Vector::insert(): index out of range");    
    }

    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;

        Vector<T> temp;

        try {
            temp.data_ = new T[new_capacity];
            temp.capacity_ = new_capacity;

            for (size_t i = 0; i < index; ++i) {
                temp.data_[i] = std::move(data_[i]);
                temp.size_++;
            }

            temp.data_[index] = std::move(value);
            temp.size_++;

            for (size_t i = index; i < size_; ++i) {
                temp.data_[i + 1] = std::move(data_[i]);
                temp.size_++;
            }
        }
        catch (const std::bad_alloc& e) {
            delete[] temp.data_;
            std::cerr << "Memory allocation error in insert: " << e.what() << std::endl;
            throw;
        }
        catch (const std::exception& e) {
            delete[] temp.data_;
            std::cerr << "Element move error in insert: " << e.what() << std::endl;
            throw;
        }
        catch (...) {
            delete[] temp.data_;
            std::cerr << "Unknown error in insert" << std::endl;
            throw;
        }

        swap(temp);
    }
    else {
        try {
            for (size_t i = size_; i > index; --i) {
                data_[i] = std::move(data_[i - 1]);
            }
            data_[index] = std::move(value);
            ++size_;
        }
        catch (const std::exception& e) {
            std::cerr << "Element shift error in insert: " << e.what() << std::endl;
            throw;
        }
    }
}

template <typename T>
void Vector<T>::erase(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Vector::erase(): index out of range");
    }

    data_[index].~T();

    try {
        for (size_t i = index + 1; i < size_; ++i) {
            data_[i - 1] = std::move_if_noexcept(data_[i]);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Element move error in erase: " << e.what() << std::endl;
        throw;
    }

    --size_;
}

template <typename T>
void Vector<T>::erase(size_t first, size_t last) {
    if (first > last || last > size_) {
        throw std::out_of_range("Vector::erase(): invalid range");
    }

    if (first == last) {
        return;
    }
   
    for (size_t i = first; i < last; ++i) {
        data_[i].~T();
    }

    size_t change = last - first;
    
    try {
        for (size_t i = last; i < size_; ++i) {
            data_[i - change] = std::move_if_noexcept(data_[i]);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Element move error in erase range: " << e.what() << std::endl;
        throw;
    }

    size_ -= change;
}


template<typename T>
void insertionSort(Vector<T>& vec) {
    size_t n = vec.size();

    for (size_t i = 1; i < n; ++i) {
        T temp = vec[i];
        size_t idx = i;

        while (idx > 0 && temp < vec[idx - 1]) {
            vec[idx] = vec[idx - 1];
            --idx;
        }

        vec[idx] = temp;
    }
}