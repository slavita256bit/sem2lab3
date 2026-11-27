#include "DumpTruck.h"
#include <iostream>
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
    input::check_positive(value, BODY_VOLUME_FIELD_NAME);
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

    std::cout << BODY_VOLUME_FIELD_NAME << ", м3 ";
    this->set_body_volume(input::read_positive(std::cin, BODY_VOLUME_FIELD_NAME));
}

// Вывод шапки таблицы
void DumpTruck::print_header(std::ostream& stream) const
{
    CargoVehicle::print_header(stream);
    stream << std::format(DUMP_TRUCK_TABLE_FORMAT, "Кузов (м3)");
}

std::istream& operator>>(std::istream& stream, DumpTruck& object)
{
    std::cout << "Введите характеристики самосвала.\n";
    stream >> static_cast<CargoVehicle&>(object);
    std::cout << BODY_VOLUME_FIELD_NAME << " (м3) ";
    object.set_body_volume(input::read_positive(stream, BODY_VOLUME_FIELD_NAME));

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const DumpTruck& object)
{
    stream << static_cast<const CargoVehicle&>(object);
    stream << std::format(DUMP_TRUCK_TABLE_FORMAT, std::format("{:.1f}", object.get_body_volume()));

    return stream;
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
    return other >= *this;
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
