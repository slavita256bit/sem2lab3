#include "Vehicle.h"
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
void Vehicle::change_field(int field)
{
    if (field == 1)
    {
        String value;
        std::cout << "Новая марка: ";
        std::cin >> value;
        this->set_brand(value);
    }
    else if (field == 2)
    {
        int value = 0;
        std::cout << "Новое значение: ";
        std::cin >> value;
        this->set_year(value);
    }
    else
        std::cout << "У этого типа транспорта нет такого параметра.\n";
}

// Ввод полей
void Vehicle::read(std::istream& stream)
{
    String new_brand;
    int new_year = 0;
    stream >> new_brand >> new_year;
    this->set_brand(new_brand);
    this->set_year(new_year);
}

// Вывод строки таблицы
void Vehicle::write(std::ostream& stream) const
{
    stream << std::format(VEHICLE_TABLE_FORMAT,
        "Транспорт",
        this->get_brand(),
        this->get_year(),
        "", "", "", "", "");
}

// Вывод шапки таблицы
void Vehicle::print_header(std::ostream& stream)
{
    stream << std::format(VEHICLE_TABLE_FORMAT,
        "Тип",
        "Марка",
        "Год",
        "Груз (т)",
        "Кузов (м3)",
        "Мест",
        "Маршрут",
        "Сеть (В)");
    stream << '\n' << std::string(VEHICLE_TABLE_WIDTH, '-') << '\n';
}

// Вывод таблицы
void Vehicle::print_table(std::ostream& stream, const std::vector<Vehicle*>& objects)
{
    print_header(stream);
    for (const Vehicle* object : objects)
        stream << *object << '\n';
}

// Ввод объекта
std::istream& operator>>(std::istream& stream, Vehicle& object)
{
    object.read(stream);

    return stream;
}

// Вывод объекта
std::ostream& operator<<(std::ostream& stream, const Vehicle& object)
{
    object.write(stream);

    return stream;
}
