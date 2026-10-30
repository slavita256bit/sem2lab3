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
void DumpTruck::change_field(VehicleField field)
{
    if (field != VehicleField::BodyVolume)
    {
        CargoVehicle::change_field(field);
        return;
    }

    double value = 0;
    std::cout << "Объём кузова, м3: ";
    std::cin >> value;
    this->set_body_volume(value);
}

// Вывод подсказки ввода
DumpTruck& DumpTruck::print_read_info(std::ostream& stream)
{
    stream << "Самосвал (марка, год, грузоподъёмность (т), объём кузова (м3)): ";

    return *this;
}

// Вывод шапки таблицы
void DumpTruck::print_header(std::ostream& stream) const
{
    CargoVehicle::print_header(stream);
    stream << std::format(DUMP_TRUCK_TABLE_FORMAT, "Кузов (м3)");
}


std::istream& operator>>(std::istream& stream, DumpTruck& object)
{
    stream >> static_cast<CargoVehicle&>(object) >> object.body_volume;

    return stream;
}


std::ostream& operator<<(std::ostream& stream, const DumpTruck& object)
{
    stream << static_cast<const CargoVehicle&>(object);
    stream << std::format(DUMP_TRUCK_TABLE_FORMAT, std::format("{:.1f}", object.get_body_volume()));

    return stream;
}
