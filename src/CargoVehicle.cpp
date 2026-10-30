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
void CargoVehicle::change_field(VehicleField field)
{
    if (field != VehicleField::Payload)
    {
        Vehicle::change_field(field);
        return;
    }

    double value = 0;
    std::cout << "Грузоподъёмность, т: ";
    std::cin >> value;
    this->set_payload(value);
}

// Вывод подсказки ввода
CargoVehicle& CargoVehicle::print_read_info(std::ostream& stream)
{
    stream << "Грузовой (марка, год, грузоподъёмность (т)): ";

    return *this;
}

// Вывод шапки таблицы
void CargoVehicle::print_header(std::ostream& stream) const
{
    Vehicle::print_header(stream);
    stream << std::format(CARGO_VEHICLE_TABLE_FORMAT, "Груз (т)");
}


std::istream& operator>>(std::istream& stream, CargoVehicle& object)
{
    stream >> static_cast<Vehicle&>(object) >> object.payload;

    return stream;
}


std::ostream& operator<<(std::ostream& stream, const CargoVehicle& object)
{
    stream << static_cast<const Vehicle&>(object);
    stream << std::format(CARGO_VEHICLE_TABLE_FORMAT, std::format("{:.1f}", object.get_payload()));

    return stream;
}
