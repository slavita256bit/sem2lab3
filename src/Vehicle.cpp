#include "Vehicle.h"
#include <format>

// Получение марки
const String& Vehicle::get_brand() const
{
    return this->brand;
}

// Изменение марки
void Vehicle::set_brand(const String& value)
{
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
    this->year = value;
}

// Изменение выбранного поля
void Vehicle::change_field(VehicleField field)
{
    if (field == VehicleField::Brand)
    {
        String value;
        std::cout << "Новая марка: ";
        std::cin >> value;
        this->set_brand(value);
    }
    else if (field == VehicleField::Year)
    {
        int value = 0;
        std::cout << "Новое значение: ";
        std::cin >> value;
        this->set_year(value);
    }
    else
        std::cout << "У этого типа транспорта нет такого параметра.\n";
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
    stream >> object.brand >> object.year;

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Vehicle& object)
{
    stream << std::format(VEHICLE_TABLE_FORMAT, object.get_brand(), object.get_year());

    return stream;
}
