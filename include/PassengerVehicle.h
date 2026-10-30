#pragma once
#include "Vehicle.h"

#define PASSENGER_VEHICLE_TABLE_FORMAT "{:<5}  "

class PassengerVehicle : public Vehicle
{
private:
    int seats = 0;  // Количество мест

public:
    PassengerVehicle() : PassengerVehicle(String("Без марки"), 2020, 1) {}
    PassengerVehicle(const String& brand, int year, int seats)
        : Vehicle(brand, year), seats(seats)
    {
        cout << "+ PassengerVehicle [" << this->get_brand() << "]" << '\n';
    }

    PassengerVehicle(const PassengerVehicle& other) : PassengerVehicle(other.get_brand(), other.get_year(), other.get_seats()) {}

    ~PassengerVehicle() override
    {
        cout << "- PassengerVehicle [" << this->get_brand() << "]" << '\n';
    }

    int get_seats() const;                                                                          // Получение числа мест
    void set_seats(int value);                                                                      // Изменение числа мест

    void change_field(VehicleField field) override;                                                 // Изменение выбранного поля
    PassengerVehicle& print_read_info(std::istream& stream) override;                               // Ввод объекта с подсказкой
    void print_header(std::ostream& stream) const override;                                         // Вывод шапки таблицы

    friend std::istream& operator>>(std::istream& stream, PassengerVehicle& object);
    friend std::ostream& operator<<(std::ostream& stream, const PassengerVehicle& object);
};
