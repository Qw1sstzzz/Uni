#ifndef ERRORS_H
#define ERRORS_H

#include <iostream>
#include <string>
#include <stdexcept>


class DictionaryError : public std::runtime_error {
public:
    DictionaryError(const std::string& message) : std::runtime_error(message) {}
} ;

class ValidationError : public DictionaryError {
public:
    ValidationError(const std::string& message) : DictionaryError(message) {}
} ;

class KeyNotFoundException : public DictionaryError {
public:
    KeyNotFoundException(const std::string& message) : DictionaryError(message) {}
} ;

class DuplicateKeyException : public DictionaryError {
public:
    DuplicateKeyException(const std::string& message) : DictionaryError(message) {}
} ;

class DuplicateTranslationException : public DictionaryError {
public:
    DuplicateTranslationException(const std::string& message) : DictionaryError(message) {}
} ;


#endif //ERRORS_H
