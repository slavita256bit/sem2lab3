#include "DumpTruck.h"
#include "Input.h"
#include <format>

// Получение объёма кузова
double DumpTruck::get_body_volume() const
{
    return this->body_volume;
}

// Изменение объёма кузова
void DumpTruck::set_body_volume(double value)
{
    input::check_positive(value, "объём кузова");
    this->body_volume = value;
}

// Изменение выбранного поля
void DumpTruck::change_field(VehicleField field)
{
    if (field != VehicleField::BodyVolume)
    {
        CargoVehicle::change_field(field);
        return;
    }

    std::cout << "Объём кузова, м3 ";
    this->set_body_volume(input::read_positive(std::cin, "объём кузова"));
}

// Ввод объекта с подсказкой
DumpTruck& DumpTruck::print_read_info(std::istream& stream)
{
    std::cout << "Самосвал. Вводите по одному полю на строку.\n";
    stream >> *this;

    return *this;
}

// Вывод шапки таблицы
void DumpTruck::print_header(std::ostream& stream) const
{
    CargoVehicle::print_header(stream);
    stream << std::format(DUMP_TRUCK_TABLE_FORMAT, "Кузов (м3)");
}

// Сравнение объёма кузова
bool DumpTruck::operator<(const DumpTruck& other) const
{
    return this->body_volume < other.body_volume;
}

// Сравнение объёма кузова
bool DumpTruck::operator>(const DumpTruck& other) const
{
    return other < *this;
}

// Сравнение объёма кузова
bool DumpTruck::operator<=(const DumpTruck& other) const
{
    return !(other < *this);
}

// Сравнение объёма кузова
bool DumpTruck::operator>=(const DumpTruck& other) const
{
    return !(*this < other);
}

// Равенство всех полей
bool DumpTruck::operator==(const DumpTruck& other) const
{
    return CargoVehicle::operator==(other) && this->body_volume == other.body_volume;
}

// Неравенство полей
bool DumpTruck::operator!=(const DumpTruck& other) const
{
    return !(*this == other);
}

std::istream& operator>>(std::istream& stream, DumpTruck& object)
{
    stream >> static_cast<CargoVehicle&>(object);
    std::cout << "Объём кузова (м3) ";
    object.set_body_volume(input::read_positive(stream, "объём кузова"));

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const DumpTruck& object)
{
    stream << static_cast<const CargoVehicle&>(object);
    stream << std::format(DUMP_TRUCK_TABLE_FORMAT, std::format("{:.1f}", object.get_body_volume()));

    return stream;
}
