#pragma once
#include "PassengerVehicle.h"

class Bus : virtual public PassengerVehicle
{
private:
    int route = 0;  // Номер маршрута

public:
    Bus() : Bus(String("Без марки"), 2020, 1, 1) {}
    Bus(const String& brand, int year, int seats, int route)
        : PassengerVehicle(brand, year, seats), route(route)
    {
        std::cout << "+ Bus [" << this->get_brand() << "]" << '\n';
    }

    ~Bus() override
    {
        std::cout << "- Bus [" << this->get_brand() << "]" << '\n';
    }

    int get_route() const;                                                                          // Получение номера маршрута
    void set_route(int value);                                                                      // Изменение номера маршрута

    void change_field(int field) override;                                                          // Изменение выбранного поля
    void read(std::istream& stream) override;                                                       // Ввод полей
    void write(std::ostream& stream) const override;                                                // Вывод строки таблицы

    friend std::istream& operator>>(std::istream& stream, Bus& object);                             // Ввод объекта
    friend std::ostream& operator<<(std::ostream& stream, const Bus& object);                       // Вывод объекта
};
