#pragma once
#include "PassengerVehicle.h"

#define TROLLEYBUS_TABLE_FORMAT "{:<12}  "

class Trolleybus : virtual public PassengerVehicle
{
private:
    double battery_capacity = 0;  // Ёмкость аккумулятора, кВт·ч

public:
    Trolleybus() : Trolleybus(String("Без марки"), 2020, 1, 60.0) {}
    Trolleybus(const String& brand, int year, int seats, double battery_capacity)
        : PassengerVehicle(brand, year, seats), battery_capacity(battery_capacity)
    {
        std::cout << "+ Trolleybus [" << this->get_brand() << "]" << '\n';
    }

    Trolleybus(const Trolleybus& other) : Trolleybus(other.get_brand(), other.get_year(), other.get_seats(), other.get_battery_capacity()) {}

    ~Trolleybus() override
    {
        std::cout << "- Trolleybus [" << this->get_brand() << "]" << '\n';
    }

    double get_battery_capacity() const;                                                            // Получение ёмкости аккумулятора
    void set_battery_capacity(double value);                                                        // Изменение ёмкости аккумулятора

    void change_field(VehicleField field) override;                                                 // Изменение выбранного поля
    Trolleybus& print_read_info(std::istream& stream) override;                                     // Ввод объекта с подсказкой
    void print_header(std::ostream& stream) const override;                                         // Вывод шапки таблицы

    friend std::istream& operator>>(std::istream& stream, Trolleybus& object);
    friend std::ostream& operator<<(std::ostream& stream, const Trolleybus& object);
};
