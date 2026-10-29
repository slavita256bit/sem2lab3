#pragma once
#include "CargoVehicle.h"

class DumpTruck : public CargoVehicle
{
private:
    double body_volume = 0;   // Объём кузова, м3

public:
    DumpTruck() : DumpTruck(String("Без марки"), 2020, 1.0, 1.0) {}
    DumpTruck(const String& brand, int year, double payload, double body_volume)
        : CargoVehicle(brand, year, payload), body_volume(body_volume)
    {
        std::cout << "+ DumpTruck [" << this->get_brand() << "]" << '\n';
    }

    ~DumpTruck() override
    {
        std::cout << "- DumpTruck [" << this->get_brand() << "]" << '\n';
    }

    double get_body_volume() const;                                                  // Получение объёма кузова
    void set_body_volume(double value);                                              // Изменение объёма кузова

    void change_field(int field) override;                                           // Изменение выбранного поля
    void read(std::istream& stream) override;                                        // Ввод полей
    void write(std::ostream& stream) const override;                                 // Вывод строки таблицы

    friend std::istream& operator>>(std::istream& stream, DumpTruck& object);        // Ввод объекта
    friend std::ostream& operator<<(std::ostream& stream, const DumpTruck& object);  // Вывод объекта
};
