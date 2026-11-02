#include "PassengerVehicle.h"
#include <format>

// Получение числа мест
int PassengerVehicle::get_seats() const
{
    return this->seats;
}

// Изменение числа мест
void PassengerVehicle::set_seats(int value)
{
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

    int value = 0;
    std::cout << "Новое значение: ";
    std::cin >> value;
    this->set_seats(value);
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
    return static_cast<const Vehicle&>(*this) == static_cast<const Vehicle&>(other) && this->seats == other.seats;
}

// Неравенство полей
bool PassengerVehicle::operator!=(const PassengerVehicle& other) const
{
    return !(*this == other);
}

std::istream& operator>>(std::istream& stream, PassengerVehicle& object)
{
    stream >> static_cast<Vehicle&>(object) >> object.seats;

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const PassengerVehicle& object)
{
    stream << static_cast<const Vehicle&>(object);
    stream << std::format(PASSENGER_VEHICLE_TABLE_FORMAT, object.get_seats());

    return stream;
}
