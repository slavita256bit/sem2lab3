#include "DumpTruck.h"
#include <format>

// Получение объёма кузова
double DumpTruck::get_body_volume() const
{
    return this->body_volume;
}

// Изменение объёма кузова
void DumpTruck::set_body_volume(double value)
{
    this->body_volume = value;
}

// Изменение выбранного поля
void DumpTruck::change_field(int field)
{
    if (field != 4)
    {
        CargoVehicle::change_field(field);
        return;
    }

    double value = 0;
    std::cout << "Объём кузова, м3: ";
    std::cin >> value;
    this->set_body_volume(value);
}

// Ввод полей
void DumpTruck::read(std::istream& stream)
{
    CargoVehicle::read(stream);
    double new_body_volume = 0;
    stream >> new_body_volume;
    this->set_body_volume(new_body_volume);
}

// Вывод строки таблицы
void DumpTruck::write(std::ostream& stream) const
{
    stream << std::format(VEHICLE_TABLE_FORMAT,
        "Самосвал",
        this->get_brand(),
        this->get_year(),
        std::format("{:.1f}", this->get_payload()),
        std::format("{:.1f}", this->get_body_volume()),
        "", "", "");
}

// Ввод объекта
std::istream& operator>>(std::istream& stream, DumpTruck& object)
{
    object.read(stream);

    return stream;
}

// Вывод объекта
std::ostream& operator<<(std::ostream& stream, const DumpTruck& object)
{
    object.write(stream);

    return stream;
}
