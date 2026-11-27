#pragma once
#include <algorithm>
#include <cstring>

#define ERROR_MESSAGE_LENGTH 80

enum class ErrorCode
{
    InvalidNumber = 1, NumberOverflow, TrailingCharacters, ValueOutOfRange,
    InvalidBrand, TextTooLong, EndOfInput, StreamFailure, InvalidField,
    InvalidIndex = 201, NullObject, ObjectNotFound
};

class Error
{
private:
    int code = 0;
    char message[ERROR_MESSAGE_LENGTH]{};

public:
    Error(ErrorCode code, const char* message) : code(static_cast<int>(code))
    {
        auto length = std::strlen(message);
        if (length >= sizeof(this->message))
        {
            std::copy_n("Сообщение слишком длинное", sizeof("Сообщение слишком длинное"), this->message);
            return;
        }

        std::copy_n(message, length + 1, this->message);
    }

    int get_code() const;                                                                           // Получение кода ошибки
    const char* get_message() const;                                                                // Получение сообщения
};
