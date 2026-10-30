#include "Vehicle.h"
#include "CargoVehicle.h"
#include "PassengerVehicle.h"
#include "DumpTruck.h"
#include "Bus.h"
#include "Trolleybus.h"
#include <typeinfo>
#include <format>

// Получение марки
const String& Vehicle::get_brand() const
{
    return this->brand;
}

// Изменение марки
void Vehicle::set_brand(const String& value)
{
    this->brand = value;
}

// Получение года выпуска
int Vehicle::get_year() const
{
    return this->year;
}

// Изменение года выпуска
void Vehicle::set_year(int value)
{
    this->year = value;
}

// Изменение выбранного поля
void Vehicle::change_field(VehicleField field)
{
    if (field == VehicleField::Brand)
    {
        String value;
        std::cout << "Новая марка: ";
        std::cin >> value;
        this->set_brand(value);
    }
    else if (field == VehicleField::Year)
    {
        int value = 0;
        std::cout << "Новое значение: ";
        std::cin >> value;
        this->set_year(value);
    }
    else
        std::cout << "У этого типа транспорта нет такого параметра.\n";
}

// Вывод подсказки ввода
Vehicle& Vehicle::print_read_info(std::ostream& stream)
{
    stream << "Транспорт (марка, год выпуска): ";

    return *this;
}

// Вывод шапки таблицы
void Vehicle::print_header(std::ostream& stream) const
{
    stream << std::format(VEHICLE_TABLE_FORMAT, "Марка", "Год");
}

// Вывод таблицы класса
void Vehicle::print_table(std::ostream& stream, Vehicle* const objects[], std::size_t count, const std::type_info& class_type)
{
    bool header_printed = false;
    for (std::size_t i = 0; i < count; i++)
    {
        const Vehicle* object = objects[i];
        if (typeid(*object) != class_type)
            continue;

        if (!header_printed)
        {
            stream << std::format("{:<3}  ", "№");
            object->print_header(stream);
            stream << '\n';
            header_printed = true;
        }

        stream << std::format("{:<3}  ", i + 1);
        if (typeid(*object) == typeid(DumpTruck))
            stream << *dynamic_cast<const DumpTruck*>(object);
        else if (typeid(*object) == typeid(CargoVehicle))
            stream << *dynamic_cast<const CargoVehicle*>(object);
        else if (typeid(*object) == typeid(Bus))
            stream << *dynamic_cast<const Bus*>(object);
        else if (typeid(*object) == typeid(Trolleybus))
            stream << *dynamic_cast<const Trolleybus*>(object);
        else if (typeid(*object) == typeid(PassengerVehicle))
            stream << *dynamic_cast<const PassengerVehicle*>(object);
        else
            stream << *object;

        stream << '\n';
    }

    if (!header_printed)
        stream << "Нет объектов для вывода.\n";
}

std::istream& operator>>(std::istream& stream, Vehicle& object)
{
    stream >> object.brand >> object.year;

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Vehicle& object)
{
    stream << std::format(VEHICLE_TABLE_FORMAT, object.get_brand(), object.get_year());

    return stream;
}
