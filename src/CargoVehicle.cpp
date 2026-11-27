#include "CargoVehicle.h"
#include "Input.h"
#include <format>

// Получение грузоподъёмности
double CargoVehicle::get_payload() const
{
    return this->payload;
}

// Изменение грузоподъёмности
void CargoVehicle::set_payload(double value)
{
    input::check_positive(value, "грузоподъёмность");
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

    std::cout << "Грузоподъёмность, т ";
    this->set_payload(input::read_positive(std::cin, "грузоподъёмность"));
}

// Вывод шапки таблицы
void CargoVehicle::print_header(std::ostream& stream) const
{
    Vehicle::print_header(stream);
    stream << std::format(CARGO_VEHICLE_TABLE_FORMAT, "Груз (т)");
}


// Равенство всех полей
bool CargoVehicle::operator==(const CargoVehicle& other) const
{
    return Vehicle::operator==(other) && this->payload == other.payload;
}

// Неравенство полей
bool CargoVehicle::operator!=(const CargoVehicle& other) const
{
    return !(*this == other);
}

std::istream& operator>>(std::istream& stream, CargoVehicle& object)
{
    stream >> static_cast<Vehicle&>(object);
    std::cout << "Грузоподъёмность (т) ";
    object.set_payload(input::read_positive(stream, "грузоподъёмность"));

    return stream;
}


std::ostream& operator<<(std::ostream& stream, const CargoVehicle& object)
{
    stream << static_cast<const Vehicle&>(object);
    stream << std::format(CARGO_VEHICLE_TABLE_FORMAT, std::format("{:.1f}", object.get_payload()));

    return stream;
}
