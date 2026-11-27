#include "PassengerVehicle.h"
#include "Input.h"
#include <format>

// Получение числа мест
int PassengerVehicle::get_seats() const
{
    return this->seats;
}

// Изменение числа мест
void PassengerVehicle::set_seats(int value)
{
    input::check_int(value, 1, MAX_SEATS, "число мест");
    this->seats = value;
}

// Изменение выбранного поля
void PassengerVehicle::change_field(VehicleField field)
{
    if (field != VehicleField::Seats)
    {
        Vehicle::change_field(field);
        return;
    }

    std::cout << "Новое значение ";
    this->set_seats(input::read_int(std::cin, 1, MAX_SEATS, "число мест"));
}

// Вывод шапки таблицы
void PassengerVehicle::print_header(std::ostream& stream) const
{
    Vehicle::print_header(stream);
    stream << std::format(PASSENGER_VEHICLE_TABLE_FORMAT, "Мест");
}

// Равенство всех полей
bool PassengerVehicle::operator==(const PassengerVehicle& other) const
{
    return Vehicle::operator==(other) && this->seats == other.seats;
}

// Неравенство полей
bool PassengerVehicle::operator!=(const PassengerVehicle& other) const
{
    return !(*this == other);
}

std::istream& operator>>(std::istream& stream, PassengerVehicle& object)
{
    stream >> static_cast<Vehicle&>(object);
    std::cout << "Число мест ";
    object.set_seats(input::read_int(stream, 1, MAX_SEATS, "число мест"));

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const PassengerVehicle& object)
{
    stream << static_cast<const Vehicle&>(object);
    stream << std::format(PASSENGER_VEHICLE_TABLE_FORMAT, object.get_seats());

    return stream;
}
