#pragma once
#include "Vehicle.h"
#include <iostream>

#define CARGO_VEHICLE_TABLE_FORMAT "{:<8.8}  "

class CargoVehicle : public Vehicle
{
private:
    double payload = 0;  // Грузоподъёмность, т

public:
    CargoVehicle() : CargoVehicle("NoBrand", 2020, 1.0) {}
    CargoVehicle(const String& brand, int year, double payload) : Vehicle(brand, year), payload(payload)
    {
        this->set_payload(this->payload);
        std::cerr << "+ CargoVehicle [" << this->get_brand() << "]" << '\n';
    }

    CargoVehicle(const CargoVehicle& other) : CargoVehicle(other.get_brand(), other.get_year(), other.get_payload()) {}

    ~CargoVehicle() override
    {
        std::cerr << "- CargoVehicle [" << this->get_brand() << "]" << '\n';
    }

    double get_payload() const;                                              // Получение грузоподъёмности
    void set_payload(double value);                                          // Изменение грузоподъёмности

    void change_field(VehicleField field) override;                          // Изменение выбранного поля
    void print_header(std::ostream& stream) const override = 0;                  // Вывод шапки таблицы

    bool operator==(const CargoVehicle& other) const;                        // Равенство всех полей
    bool operator!=(const CargoVehicle& other) const;                        // Неравенство полей

    friend std::istream& operator>>(std::istream& stream, CargoVehicle& object);
    friend std::ostream& operator<<(std::ostream& stream, const CargoVehicle& object);
};
