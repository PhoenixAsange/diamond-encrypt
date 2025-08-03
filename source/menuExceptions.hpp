#include <stdexcept>
#include <string>

/*Custom exceptions that ensure the program is contiuous*/

class InvalidMessageException : public std::invalid_argument {
    public:
        InvalidMessageException(const std::string& message)
        : std::invalid_argument("Invalid message: " + message) {}
};

class InvalidRoundsException : public std::invalid_argument {
    public:
        InvalidRoundsException(const std::string& message)
        : std::invalid_argument("Invalid rounds: " + message) {}
};

class InvalidMenuOptionException : public std::invalid_argument {
    public:
        InvalidMenuOptionException(const std::string& message)
        : std::invalid_argument("Invalid menu option: " + message) {}
};

class InvalidGridSizeException : public std::invalid_argument {
    public:
        InvalidGridSizeException(const std::string& message)
        : std::invalid_argument("Invalid grid size: " + message) {}
};

class EmptyGridException : public std::runtime_error {
    public:
        EmptyGridException(const std::string& message)
        : std::runtime_error("Grid is empty: " + message) {}
};

class UndefinedMessageException : public std::runtime_error {
    public:
        UndefinedMessageException(const std::string& message)
        : std::runtime_error("Message is undefined: " + message) {}
};

class UndefinedRoundsException : public std::runtime_error {
    public:
        UndefinedRoundsException(const std::string& message)
        : std::runtime_error("Rounds is undefined: " + message) {}
};

class InvalidCipheringStateException : public std::runtime_error {
    public:
        InvalidCipheringStateException(const std::string& message)
        : std::runtime_error("Operation already completed: " + message) {}
};