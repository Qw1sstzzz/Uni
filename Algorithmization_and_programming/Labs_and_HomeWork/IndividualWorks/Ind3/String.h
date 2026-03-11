#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H

#include <iostream>

const int INITIAL_CAPACITY = 16;

class CustomString {
private:
    char* buffer_;
    int buffer_size_;
    int string_length_;

    void swapContents(CustomString& other) noexcept;
public:
    CustomString();
    CustomString(const char* input_str);
    CustomString(const CustomString& other);
    CustomString(CustomString&& other);
    ~CustomString();

    CustomString& operator=(const char* input_str);
    CustomString& operator=(CustomString&& other) noexcept;
    CustomString& operator=(const CustomString& other);
    
    char& operator[](int position);
    const char& operator[](int position) const;
    
    CustomString operator+(const CustomString& other) const;
    CustomString& operator+=(const CustomString& other);
    CustomString& operator+=(const char* input_str);
    
    bool operator==(const CustomString& other) const noexcept;
    bool operator!=(const CustomString& other) const noexcept;
    bool operator<(const CustomString& other) const noexcept;
    bool operator>(const CustomString& other) const noexcept;

    friend std::istream& operator>>(std::istream& input, CustomString& str);
    friend std::ostream& operator<<(std::ostream& output, const CustomString& str);
    
    int getLength() const noexcept;
    bool isEmpty() const noexcept;
    void increaseCapacity(int new_size);
    
    CustomString replaceCharacters(char target_char, char replacement_char) const;
};

int calculateLength(const char* str);

#endif