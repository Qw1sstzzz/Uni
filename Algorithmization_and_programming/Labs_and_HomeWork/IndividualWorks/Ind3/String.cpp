#include "String.h"

#include <stdexcept>
#include <cctype>
#include <limits>

int calculateLength(const char* str) {
    if (str == nullptr) return 0;
    
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void CustomString::swapContents(CustomString& other) noexcept {
    std::swap(buffer_, other.buffer_);
    std::swap(buffer_size_, other.buffer_size_);
    std::swap(string_length_, other.string_length_);
}



CustomString::CustomString() : string_length_(0), buffer_size_(INITIAL_CAPACITY) {
    buffer_ = new char[buffer_size_];
    buffer_[0] = '\0';
}

CustomString::CustomString(const char* input_str) {
    if (input_str == nullptr) {
        throw std::invalid_argument("Error: null pointer passed");
    }

    int len = calculateLength(input_str);
    buffer_size_ = (len + 1 > INITIAL_CAPACITY) ? len + 1 : INITIAL_CAPACITY;
    buffer_ = new char[buffer_size_];

    for (int i = 0; i < len; ++i) {
        buffer_[i] = input_str[i];
    }

    string_length_ = len;
    buffer_[string_length_] = '\0';
}

CustomString::CustomString(const CustomString& other) {
    if (other.buffer_ == nullptr) {            
        buffer_size_ = INITIAL_CAPACITY;
        buffer_ = new char[buffer_size_];
        buffer_[0] = '\0';
        string_length_ = 0;
        return;
    }

    if (other.buffer_size_ > INITIAL_CAPACITY) {
        buffer_size_ = other.buffer_size_;
    }
    else {
        buffer_size_ = INITIAL_CAPACITY;
    }

    buffer_ = new char[buffer_size_];

    for (int i = 0; i <= other.string_length_; i++) {
        buffer_[i] = other.buffer_[i];
    }

    string_length_ = other.string_length_;
}

CustomString::CustomString(CustomString&& other) {
    buffer_ = other.buffer_;
    string_length_ = other.string_length_;
    buffer_size_ = other.buffer_size_;
    
    other.buffer_ = nullptr;
    other.string_length_ = 0;
    other.buffer_size_ = 0;
}

CustomString::~CustomString() {
    delete[] buffer_;
    buffer_ = nullptr;
}



CustomString& CustomString::operator=(const char* input_str) {
    if (input_str == nullptr) {
        throw std::invalid_argument("Error: null pointer passed");
    }

    if (this->buffer_ == input_str) {
        return *this;
    }
    
    delete[] buffer_;
    int len = calculateLength(input_str);
    if (len + 1 > INITIAL_CAPACITY) {
        buffer_size_ = len + 1;
    }
    else {
        buffer_size_ = INITIAL_CAPACITY;
    }
    buffer_ = new char[buffer_size_];

    for (int i = 0; i < len; i++) {
        buffer_[i] = input_str[i];
    }

    string_length_ = len;
    buffer_[string_length_] = '\0';

    return *this;
}

CustomString& CustomString::operator=(const CustomString& other) {
    if (this != &other) {
        CustomString temp(other);
        swapContents(temp);
    }
    return *this;
}

CustomString& CustomString::operator=(CustomString&& other) noexcept {
    if (this != &other) {
        swapContents(other);
    }
    return *this;
}



char& CustomString::operator[](int position) {
    if (position < 0 || position >= string_length_) {
        throw std::invalid_argument("Error: invalid index");
    }
    return buffer_[position];
}

const char& CustomString::operator[](int position) const {
    if (position < 0 || position >= string_length_) {
        throw std::invalid_argument("Error: invalid index");
    }
    return buffer_[position];
}



CustomString CustomString::operator+(const CustomString& other) const {
    CustomString result(*this);
    int total_length = result.string_length_ + other.string_length_;
    result.increaseCapacity(total_length + 1);

    for (int i = 0; i <= other.string_length_; i++) {
        result.buffer_[result.string_length_ + i] = other.buffer_[i];
    }

    result.string_length_ = total_length;
    return result;
}

CustomString& CustomString::operator+=(const CustomString& other) {
    int total_length = string_length_ + other.string_length_;
    increaseCapacity(total_length + 1);

    for (int i = 0; i <= other.string_length_; ++i) {
        buffer_[string_length_ + i] = other.buffer_[i];
    }

    string_length_ = total_length;
    return *this;
}

CustomString& CustomString::operator+=(const char* input_str) {
    if (input_str == nullptr) {
        return *this;
    }
    
    int str_len = calculateLength(input_str);
    int total_length = string_length_ + str_len;
    increaseCapacity(total_length + 1);

    for (int i = 0; i <= str_len; ++i) {
        buffer_[string_length_ + i] = input_str[i];
    }

    string_length_ = total_length;
    return *this;
}



bool CustomString::operator==(const CustomString& other) const noexcept {
    if (this == &other) {
        return true;
    }
    if (string_length_ != other.string_length_) {
        return false;        
    }
    for (int i = 0; i < string_length_; ++i) {
        if (buffer_[i] != other.buffer_[i]) {
            return false;
        }
    }
    return true;
}

bool CustomString::operator!=(const CustomString& other) const noexcept {
    return !(*this == other);
}

bool CustomString::operator<(const CustomString& other) const noexcept {
    int min_len = (string_length_ < other.string_length_) ? string_length_ : other.string_length_;
    for (int i = 0; i < min_len; i++) {
        if (buffer_[i] != other.buffer_[i]) {
            return buffer_[i] < other.buffer_[i];
        }
    }

    return string_length_ < other.string_length_;
}

bool CustomString::operator>(const CustomString& other) const noexcept {
    int min_len = (string_length_ < other.string_length_) ? string_length_ : other.string_length_;
    for (int i = 0; i < min_len; ++i) {
        if (buffer_[i] != other.buffer_[i]) {
            return buffer_[i] > other.buffer_[i];
        }
    }

    return string_length_ > other.string_length_;
}



std::istream& operator>>(std::istream& input, CustomString& str) {
    const int BUFFER_SIZE = 256;
    char temp_buffer[BUFFER_SIZE];
    
    if (input.getline(temp_buffer, BUFFER_SIZE)) {
        int len = calculateLength(temp_buffer);
        str.increaseCapacity(len + 1);
        
        for (int i = 0; i <= len; ++i) {
            str.buffer_[i] = temp_buffer[i];
        }
        str.string_length_ = len;
    }
    
    return input;
}

std::ostream& operator<<(std::ostream& output, const CustomString& str) {
    if (str.buffer_ != nullptr) {
        output << str.buffer_;
    }
    return output;
}



int CustomString::getLength() const noexcept {
    return string_length_;
}

bool CustomString::isEmpty() const noexcept {
    return string_length_ == 0;
}

void CustomString::increaseCapacity(int new_size) {  
    if (new_size <= buffer_size_) {
        return;
    }   

    buffer_size_ = new_size;
    char* new_buffer = new char[buffer_size_];
    
    if (buffer_ != nullptr) {
        for (int i = 0; i <= string_length_; ++i) {
            new_buffer[i] = buffer_[i];
        }
        delete[] buffer_;  
    
    buffer_ = new_buffer;
}





CustomString CustomString::replaceCharacters(char target_char, char replacement_char) const {
    CustomString result(*this);
    
    for (int i = 0; i < result.string_length_; ++i) {
        if (result.buffer_[i] == target_char) {
            result.buffer_[i] = replacement_char;
        }
    }
    return result;
}