#include "CargoVehicle.h"
#include <format>

// Получение грузоподъёмности
double CargoVehicle::get_payload() const
{
    return this->payload;
}

// Изменение грузоподъёмности
void CargoVehicle::set_payload(double value)
{
    this->payload = value;
}

// Изменение выбранного поля
void CargoVehicle::change_field(int field)
{
    if (field != 3)
    {
        Vehicle::change_field(field);
        return;
    }

    double value = 0;
    std::cout << "Грузоподъёмность, т: ";
    std::cin >> value;
    this->set_payload(value);
}

// Ввод полей
void CargoVehicle::read(std::istream& stream)
{
    Vehicle::read(stream);
    double new_payload = 0;
    stream >> new_payload;
    this->set_payload(new_payload);
}

// Вывод строки таблицы
void CargoVehicle::write(std::ostream& stream) const
{
    stream << std::format(VEHICLE_TABLE_FORMAT,
        "Грузовой",
        this->get_brand(),
        this->get_year(),
        std::format("{:.1f}", this->get_payload()),
        "", "", "", "");
}

// Ввод объекта
std::istream& operator>>(std::istream& stream, CargoVehicle& object)
{
    object.read(stream);

    return stream;
}

// Вывод объекта
std::ostream& operator<<(std::ostream& stream, const CargoVehicle& object)
{
    object.write(stream);

    return stream;
}
