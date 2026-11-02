#include "Bus.h"
#include <format>

// Получение номера маршрута
int Bus::get_route() const
{
    return this->route;
}

// Изменение номера маршрута
void Bus::set_route(int value)
{
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

    int value = 0;
    std::cout << "Новое значение: ";
    std::cin >> value;
    this->set_route(value);
}

// Ввод объекта с подсказкой
Bus& Bus::print_read_info(std::istream& stream)
{
    std::cout << "Автобус (марка, год, количество мест, номер маршрута): ";
    stream >> *this;

    return *this;
}

// Вывод шапки таблицы
void Bus::print_header(std::ostream& stream) const
{
    PassengerVehicle::print_header(stream);
    stream << std::format(BUS_TABLE_FORMAT, "Маршрут");
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
    return !(other < *this);
}

// Сравнение номера маршрута
bool Bus::operator>=(const Bus& other) const
{
    return !(*this < other);
}

// Равенство всех полей
bool Bus::operator==(const Bus& other) const
{
    return static_cast<const PassengerVehicle&>(*this) == static_cast<const PassengerVehicle&>(other) && this->route == other.route;
}

// Неравенство полей
bool Bus::operator!=(const Bus& other) const
{
    return !(*this == other);
}

std::istream& operator>>(std::istream& stream, Bus& object)
{
    stream >> static_cast<PassengerVehicle&>(object) >> object.route;

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Bus& object)
{
    stream << static_cast<const PassengerVehicle&>(object);
    stream << std::format(BUS_TABLE_FORMAT, std::to_string(object.get_route()));

    return stream;
}
