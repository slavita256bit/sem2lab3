#include "Error.h"

// Получение кода ошибки
int Error::get_code() const noexcept
{
    return this->code;
}

// Получение сообщения
const char* Error::get_message() const noexcept
{
    return this->message;
}

