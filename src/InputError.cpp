#include "InputError.h"

// Получение названия поля
const String& InputError::get_field() const noexcept
{
    return this->field;
}
