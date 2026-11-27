#pragma once
#include "Error.h"
#include "String.h"

class InputError : public Error
{
private:
    String field;

public:
    InputError(ErrorCode code, const char* message, const char* field) : Error(code, message), field(field) {}

    const String& get_field() const noexcept;     // Получение названия поля
};
