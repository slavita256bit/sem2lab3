#pragma once
#include "Error.h"
#include "String.h"

class InputError : public Error
{
private:
    String field;

public:
    InputError(ErrorCode code, const char* message, const String& field) : Error(code, message), field(field) {}

    String get_field() const;                                                                       // Получение названия поля
};
