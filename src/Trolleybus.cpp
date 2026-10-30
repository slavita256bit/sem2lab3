#include "Trolleybus.h"
#include <format>

// Получение ёмкости аккумулятора
double Trolleybus::get_battery_capacity() const
{
    return this->battery_capacity;
}

// Изменение ёмкости аккумулятора
void Trolleybus::set_battery_capacity(double value)
{
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

    double value = 0;
    std::cout << "Новое значение: ";
    std::cin >> value;
    this->set_battery_capacity(value);
}

// Вывод подсказки ввода
Trolleybus& Trolleybus::print_read_info(std::ostream& stream)
{
    stream << "Троллейбус (марка, год, количество мест, ёмкость аккумулятора (кВт·ч)): ";

    return *this;
}

// Вывод шапки таблицы
void Trolleybus::print_header(std::ostream& stream) const
{
    PassengerVehicle::print_header(stream);
    stream << std::format(TROLLEYBUS_TABLE_FORMAT, "АКБ (кВт·ч)");
}

std::istream& operator>>(std::istream& stream, Trolleybus& object)
{
    stream >> static_cast<PassengerVehicle&>(object) >> object.battery_capacity;

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Trolleybus& object)
{
    stream << static_cast<const PassengerVehicle&>(object);
    stream << std::format(TROLLEYBUS_TABLE_FORMAT, std::format("{:.1f}", object.get_battery_capacity()));

    return stream;
}
