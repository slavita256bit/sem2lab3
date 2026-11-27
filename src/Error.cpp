#include "Error.h"

// Получение кода ошибки
int Error::get_code() const
{
    return this->code;
}

// Получение сообщения
const char* Error::get_message() const
{
    return this->message;
}

