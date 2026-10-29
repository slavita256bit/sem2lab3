#include "Trolleybus.h"
#include <format>

// Получение напряжения сети
int Trolleybus::get_voltage() const
{
    return this->voltage;
}

// Изменение напряжения сети
void Trolleybus::set_voltage(int value)
{
    this->voltage = value;
}

// Изменение выбранного поля
void Trolleybus::change_field(int field)
{
    if (field != 7)
    {
        PassengerVehicle::change_field(field);
        return;
    }

    int value = 0;
    std::cout << "Новое значение: ";
    std::cin >> value;
    this->set_voltage(value);
}

// Ввод полей
void Trolleybus::read(std::istream& stream)
{
    PassengerVehicle::read(stream);
    int new_voltage = 0;
    stream >> new_voltage;
    this->set_voltage(new_voltage);
}

// Вывод строки таблицы
void Trolleybus::write(std::ostream& stream) const
{
    stream << std::format(VEHICLE_TABLE_FORMAT,
        "Троллейбус",
        this->get_brand(),
        this->get_year(),
        "", "",
        this->get_seats(),
        "",
        std::to_string(this->get_voltage()));
}

// Ввод объекта
std::istream& operator>>(std::istream& stream, Trolleybus& object)
{
    object.read(stream);

    return stream;
}

// Вывод объекта
std::ostream& operator<<(std::ostream& stream, const Trolleybus& object)
{
    object.write(stream);

    return stream;
}
