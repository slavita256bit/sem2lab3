#include "Vehicle.h"
#include "Input.h"
#include "InputError.h"
#include <format>

// Получение марки
const String& Vehicle::get_brand() const
{
    return this->brand;
}

// Изменение марки
void Vehicle::set_brand(const String& value)
{
    input::check_brand(value);
    this->brand = value;
}

// Получение года выпуска
int Vehicle::get_year() const
{
    return this->year;
}

// Изменение года выпуска
void Vehicle::set_year(int value)
{
    input::check_int(value, MIN_YEAR, CURRENT_YEAR, YEAR_FIELD_NAME);
    this->year = value;
}

// Изменение выбранного поля
void Vehicle::change_field(VehicleField field)
{
    if (field == VehicleField::Brand)
    {
        std::cout << "Новая " << BRAND_FIELD_NAME << ' ';
        this->set_brand(input::read_brand(std::cin));
    }
    else if (field == VehicleField::Year)
    {
        std::cout << "Новое значение ";
        this->set_year(input::read_int(std::cin, MIN_YEAR, CURRENT_YEAR, YEAR_FIELD_NAME));
    }
    else
        throw InputError(ErrorCode::InvalidField, "У транспорта нет такого параметра", "параметр");
}

// Вывод шапки таблицы
void Vehicle::print_header(std::ostream& stream) const
{
    stream << std::format(VEHICLE_TABLE_FORMAT, "Марка", "Год");
}

// Сравнение года выпуска
bool Vehicle::operator<(const Vehicle& other) const
{
    return this->year < other.year;
}

// Сравнение года выпуска
bool Vehicle::operator>(const Vehicle& other) const
{
    return other < *this;
}

// Сравнение года выпуска
bool Vehicle::operator<=(const Vehicle& other) const
{
    return !(other < *this);
}

// Сравнение года выпуска
bool Vehicle::operator>=(const Vehicle& other) const
{
    return !(*this < other);
}

// Равенство всех полей
bool Vehicle::operator==(const Vehicle& other) const
{
    return this->brand == other.brand && this->year == other.year;
}

// Неравенство полей
bool Vehicle::operator!=(const Vehicle& other) const
{
    return !(*this == other);
}

std::istream& operator>>(std::istream& stream, Vehicle& object)
{
    std::cout << BRAND_FIELD_NAME << ' ';
    object.set_brand(input::read_brand(stream));
    std::cout << YEAR_FIELD_NAME << " выпуска ";
    object.set_year(input::read_int(stream, MIN_YEAR, CURRENT_YEAR, YEAR_FIELD_NAME));

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Vehicle& object)
{
    stream << std::format(VEHICLE_TABLE_FORMAT, object.get_brand(), object.get_year());

    return stream;
}
