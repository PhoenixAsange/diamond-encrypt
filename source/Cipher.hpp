#ifndef CIPHER
#define CIPHER

#include <string>

class Cipher {
public:
    virtual void encrypt() = 0;
    virtual std::string decryptFinal() = 0;
    virtual void setMessage(const std::string message) = 0;
    virtual const std::string& getMessage() const = 0;
};

#endif