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

// Вывод подсказки ввода
Bus& Bus::print_read_info(std::ostream& stream)
{
    stream << "Автобус (марка, год, количество мест, номер маршрута): ";

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
    stream >> static_cast<PassengerVehicle&>(object) >> object.route;

    return stream;
}


std::ostream& operator<<(std::ostream& stream, const Bus& object)
{
    stream << static_cast<const PassengerVehicle&>(object);
    stream << std::format(BUS_TABLE_FORMAT, std::to_string(object.get_route()));

    return stream;
}
