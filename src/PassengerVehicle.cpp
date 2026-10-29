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
void PassengerVehicle::change_field(int field)
{
    if (field != 5)
    {
        Vehicle::change_field(field);
        return;
    }

    int value = 0;
    std::cout << "Новое значение: ";
    std::cin >> value;
    this->set_seats(value);
}

// Ввод полей
void PassengerVehicle::read(std::istream& stream)
{
    Vehicle::read(stream);
    int new_seats = 0;
    stream >> new_seats;
    this->set_seats(new_seats);
}

// Вывод строки таблицы
void PassengerVehicle::write(std::ostream& stream) const
{
    stream << std::format(VEHICLE_TABLE_FORMAT,
        "Пассажирский",
        this->get_brand(),
        this->get_year(),
        "", "",
        this->get_seats(),
        "", "");
}

// Ввод объекта
std::istream& operator>>(std::istream& stream, PassengerVehicle& object)
{
    object.read(stream);

    return stream;
}

// Вывод объекта
std::ostream& operator<<(std::ostream& stream, const PassengerVehicle& object)
{
    object.write(stream);

    return stream;
}
