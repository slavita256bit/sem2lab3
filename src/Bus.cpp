#include "Bus.h"
#include <iostream>
#include "Input.h"
#include <format>

// Получение номера маршрута
int Bus::get_route() const
{
    return this->route;
}

// Изменение номера маршрута
void Bus::set_route(int value)
{
    input::check_int(value, 1, MAX_ROUTE, ROUTE_FIELD_NAME);
    this->route = value;
}

// Изменение выбранного поля
void Bus::change_field(VehicleField field)
{
    if (field != VehicleField::Route)
    {
        PassengerVehicle::change_field(field);
        return;
    }

    std::cout << "Новое значение ";
    this->set_route(input::read_int(std::cin, 1, MAX_ROUTE, ROUTE_FIELD_NAME));
}

// Ввод объекта с подсказкой
Bus& Bus::print_read_info(std::istream& stream)
{
    std::cout << "Автобус. Вводите по одному полю на строку.\n";
    stream >> *this;

    return *this;
}

// Вывод шапки таблицы
void Bus::print_header(std::ostream& stream) const
{
    PassengerVehicle::print_header(stream);
    stream << std::format(BUS_TABLE_FORMAT, "Маршрут");
}

std::istream& operator>>(std::istream& stream, Bus& object)
{
    stream >> static_cast<PassengerVehicle&>(object);
    std::cout << ROUTE_FIELD_NAME << ' ';
    object.set_route(input::read_int(stream, 1, MAX_ROUTE, ROUTE_FIELD_NAME));

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Bus& object)
{
    stream << static_cast<const PassengerVehicle&>(object);
    stream << std::format(BUS_TABLE_FORMAT, object.get_route());

    return stream;
}

// Сравнение номера маршрута
bool Bus::operator<(const Bus& other) const
{
    return this->route < other.route;
}

// Сравнение номера маршрута
bool Bus::operator>(const Bus& other) const
{
    return other < *this;
}

// Сравнение номера маршрута
bool Bus::operator<=(const Bus& other) const
{
    return other >= *this;
}

// Сравнение номера маршрута
bool Bus::operator>=(const Bus& other) const
{
    return !(*this < other);
}

// Равенство всех полей
bool Bus::operator==(const Bus& other) const
{
    return PassengerVehicle::operator==(other) && this->route == other.route;
}

// Неравенство полей
bool Bus::operator!=(const Bus& other) const
{
    return !(*this == other);
}
