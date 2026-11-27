#include "Trolleybus.h"
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
    input::check_positive(value, "ёмкость аккумулятора");
    this->battery_capacity = value;
}

// Изменение выбранного поля
void Trolleybus::change_field(VehicleField field)
{
    if (field != VehicleField::BatteryCapacity)
    {
        PassengerVehicle::change_field(field);
        return;
    }

    std::cout << "Новое значение (десятичная точка): ";
    this->set_battery_capacity(input::read_positive(std::cin, "ёмкость аккумулятора"));
}

// Ввод объекта с подсказкой
Trolleybus& Trolleybus::print_read_info(std::istream& stream)
{
    std::cout << "Троллейбус. Вводите по одному полю на строку. Для дробных чисел используйте точку.\n";
    stream >> *this;

    return *this;
}

// Вывод шапки таблицы
void Trolleybus::print_header(std::ostream& stream) const
{
    PassengerVehicle::print_header(stream);
    stream << std::format(TROLLEYBUS_TABLE_FORMAT, "АКБ (кВт·ч)");
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
    return !(other < *this);
}

// Сравнение ёмкости аккумулятора
bool Trolleybus::operator>=(const Trolleybus& other) const
{
    return !(*this < other);
}

// Равенство всех полей
bool Trolleybus::operator==(const Trolleybus& other) const
{
    return static_cast<const PassengerVehicle&>(*this) == static_cast<const PassengerVehicle&>(other) && this->battery_capacity == other.battery_capacity;
}

// Неравенство полей
bool Trolleybus::operator!=(const Trolleybus& other) const
{
    return !(*this == other);
}

std::istream& operator>>(std::istream& stream, Trolleybus& object)
{
    stream >> static_cast<PassengerVehicle&>(object);
    std::cout << "Ёмкость аккумулятора (кВт·ч): ";
    object.set_battery_capacity(input::read_positive(stream, "ёмкость аккумулятора"));

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Trolleybus& object)
{
    stream << static_cast<const PassengerVehicle&>(object);
    stream << std::format(TROLLEYBUS_TABLE_FORMAT, std::format("{:.1f}", object.get_battery_capacity()));

    return stream;
}
