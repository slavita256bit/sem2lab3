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
void Bus::change_field(int field)
{
    if (field != 6)
    {
        PassengerVehicle::change_field(field);
        return;
    }

    int value = 0;
    std::cout << "Новое значение: ";
    std::cin >> value;
    this->set_route(value);
}

// Ввод полей
void Bus::read(std::istream& stream)
{
    PassengerVehicle::read(stream);
    int new_route = 0;
    stream >> new_route;
    this->set_route(new_route);
}

// Вывод строки таблицы
void Bus::write(std::ostream& stream) const
{
    stream << std::format(VEHICLE_TABLE_FORMAT,
        "Автобус",
        this->get_brand(),
        this->get_year(),
        "", "",
        this->get_seats(),
        std::to_string(this->get_route()),
        "");
}

// Ввод объекта
std::istream& operator>>(std::istream& stream, Bus& object)
{
    object.read(stream);

    return stream;
}

// Вывод объекта
std::ostream& operator<<(std::ostream& stream, const Bus& object)
{
    object.write(stream);

    return stream;
}
