#pragma once
#include "Error.h"

class ContainerError : public Error
{
private:
    int number = 0;

public:
    ContainerError(ErrorCode code, const char* message, int number) : Error(code, message), number(number) {}

    int get_number() const;                                                                         // Получение номера объекта
};
