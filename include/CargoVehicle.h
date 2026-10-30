#pragma once
#include "Vehicle.h"

#define CARGO_VEHICLE_TABLE_FORMAT "{:<8.8}  "

class CargoVehicle : public Vehicle
{
private:
    double payload = 0;  // Грузоподъёмность, т

public:
    CargoVehicle() : CargoVehicle(String("Без марки"), 2020, 1.0) {}
    CargoVehicle(const String& brand, int year, double payload) : Vehicle(brand, year), payload(payload)
    {
        std::cout << "+ CargoVehicle [" << this->get_brand() << "]" << '\n';
    }

    CargoVehicle(const CargoVehicle& other) : CargoVehicle(other.get_brand(), other.get_year(), other.get_payload()) {}

    ~CargoVehicle() override
    {
        std::cout << "- CargoVehicle [" << this->get_brand() << "]" << '\n';
    }

    double get_payload() const;                                                                     // Получение грузоподъёмности
    void set_payload(double value);                                                                 // Изменение грузоподъёмности

    void change_field(VehicleField field) override;                                                 // Изменение выбранного поля
    CargoVehicle& print_read_info(std::istream& stream) override;                                   // Ввод объекта с подсказкой
    void print_header(std::ostream& stream) const override;                                         // Вывод шапки таблицы

    friend std::istream& operator>>(std::istream& stream, CargoVehicle& object);
    friend std::ostream& operator<<(std::ostream& stream, const CargoVehicle& object);
};
