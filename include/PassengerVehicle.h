#pragma once
#include "Vehicle.h"
#include <iostream>

#define MAX_SEATS 200
#define PASSENGER_VEHICLE_TABLE_FORMAT "{:<5}  "

class PassengerVehicle : public Vehicle
{
private:
    int seats = 0;  // Количество мест

public:
    PassengerVehicle() : PassengerVehicle("NoBrand", 2020, 1) {}
    PassengerVehicle(const String& brand, int year, int seats)
        : Vehicle(brand, year), seats(seats)
    {
        this->set_seats(this->seats);
        std::cerr << "+ PassengerVehicle [" << this->get_brand() << "]" << '\n';
    }

    PassengerVehicle(const PassengerVehicle& other) : PassengerVehicle(other.get_brand(), other.get_year(), other.get_seats()) {}

    ~PassengerVehicle() override
    {
        std::cerr << "- PassengerVehicle [" << this->get_brand() << "]" << '\n';
    }

    int get_seats() const;                                                      // Получение числа мест
    void set_seats(int value);                                                  // Изменение числа мест

    void change_field(VehicleField field) override;                             // Изменение выбранного поля
    void print_header(std::ostream& stream) const override = 0;                     // Вывод шапки таблицы

    bool operator==(const PassengerVehicle& other) const;                       // Равенство всех полей
    bool operator!=(const PassengerVehicle& other) const;                       // Неравенство полей

    friend std::istream& operator>>(std::istream& stream, PassengerVehicle& object);
    friend std::ostream& operator<<(std::ostream& stream, const PassengerVehicle& object);
};
