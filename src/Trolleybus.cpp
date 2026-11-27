#include "Trolleybus.h"
#include <iostream>
#include "Input.h"
#include <format>

// Получение ёмкости аккумулятора
double Trolleybus::get_battery_capacity() const
{
    return this->battery_capacity;
}

// Изменение ёмкости аккумулятора
void Trolleybus::set_battery_capacity(double value)
{
    input::check_positive(value, BATTERY_CAPACITY_FIELD_NAME);
    this->battery_capacity = value;
}

// Ввод ёмкости аккумулятора
void Trolleybus::read_battery_capacity(std::istream& stream)
{
    this->set_battery_capacity(input::read_positive(stream, BATTERY_CAPACITY_FIELD_NAME));
}

// Изменение выбранного поля
void Trolleybus::change_field(VehicleField field)
{
    if (field != VehicleField::BatteryCapacity)
    {
        PassengerVehicle::change_field(field);
        return;
    }

    std::cout << "Новое значение ";
    this->read_battery_capacity(std::cin);
}

// Вывод шапки таблицы
void Trolleybus::print_header(std::ostream& stream) const
{
    PassengerVehicle::print_header(stream);
    stream << std::format(TROLLEYBUS_TABLE_FORMAT, "АКБ (кВт·ч)");
}

std::istream& operator>>(std::istream& stream, Trolleybus& object)
{
    std::cout << "Введите характеристики троллейбуса.\n";
    stream >> static_cast<PassengerVehicle&>(object);
    std::cout << BATTERY_CAPACITY_FIELD_NAME << " (кВт·ч) ";
    object.read_battery_capacity(stream);

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Trolleybus& object)
{
    stream << static_cast<const PassengerVehicle&>(object);
    stream << std::format(TROLLEYBUS_TABLE_FORMAT, std::format("{:.1f}", object.get_battery_capacity()));

    return stream;
}

// Сравнение ёмкости аккумулятора
bool Trolleybus::operator<(const Trolleybus& other) const
{
    return this->battery_capacity < other.battery_capacity;
}

// Сравнение ёмкости аккумулятора
bool Trolleybus::operator>(const Trolleybus& other) const
{
    return other < *this;
}

// Сравнение ёмкости аккумулятора
bool Trolleybus::operator<=(const Trolleybus& other) const
{
    return other >= *this;
}

// Сравнение ёмкости аккумулятора
bool Trolleybus::operator>=(const Trolleybus& other) const
{
    return !(*this < other);
}

// Равенство всех полей
bool Trolleybus::operator==(const Trolleybus& other) const
{
    return PassengerVehicle::operator==(other) && this->battery_capacity == other.battery_capacity;
}

// Неравенство полей
bool Trolleybus::operator!=(const Trolleybus& other) const
{
    return !(*this == other);
}
