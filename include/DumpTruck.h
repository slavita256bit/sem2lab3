#pragma once
#include "CargoVehicle.h"

#define DUMP_TRUCK_TABLE_FORMAT "{:<10.10}  "

class DumpTruck : public CargoVehicle
{
private:
    double body_volume = 0;                                                                         // Объём кузова, м3

public:
    DumpTruck() : DumpTruck(String("Без марки"), 2020, 1.0, 1.0) {}
    DumpTruck(const String& brand, int year, double payload, double body_volume)
        : CargoVehicle(brand, year, payload), body_volume(body_volume)
    {
        std::cout << "+ DumpTruck [" << this->get_brand() << "]" << '\n';
    }

    DumpTruck(const DumpTruck& other) : DumpTruck(other.get_brand(), other.get_year(), other.get_payload(), other.get_body_volume()) {}

    ~DumpTruck() override
    {
        std::cout << "- DumpTruck [" << this->get_brand() << "]" << '\n';
    }

    double get_body_volume() const;                                                                 // Получение объёма кузова
    void set_body_volume(double value);                                                             // Изменение объёма кузова

    void change_field(VehicleField field) override;                                                 // Изменение выбранного поля
    DumpTruck& print_read_info(std::ostream& stream) override;                                      // Вывод подсказки ввода
    void print_header(std::ostream& stream) const override;                                         // Вывод шапки таблицы

    friend std::istream& operator>>(std::istream& stream, DumpTruck& object);
    friend std::ostream& operator<<(std::ostream& stream, const DumpTruck& object);
};
