#pragma once
#include "Vehicle.h"

class PassengerVehicle : public Vehicle
{
private:
    int seats = 0;                                                                                  // Количество мест

public:
    PassengerVehicle() : PassengerVehicle(String("Без марки"), 2020, 1) {}
    PassengerVehicle(const String& brand, int year, int seats)
        : Vehicle(brand, year), seats(seats)
    {
        std::cout << "+ PassengerVehicle [" << this->get_brand() << "]" << '\n';
    }

    ~PassengerVehicle() override
    {
        std::cout << "- PassengerVehicle [" << this->get_brand() << "]" << '\n';
    }

    int get_seats() const;                                                                 // Получение числа мест
    void set_seats(int value);                                                             // Изменение числа мест

    void change_field(int field) override;                                                 // Изменение выбранного поля
    void read(std::istream& stream) override;                                              // Ввод полей
    void write(std::ostream& stream) const override;                                       // Вывод строки таблицы

    friend std::istream& operator>>(std::istream& stream, PassengerVehicle& object);       // Ввод объекта
    friend std::ostream& operator<<(std::ostream& stream, const PassengerVehicle& object); // Вывод объекта
};
