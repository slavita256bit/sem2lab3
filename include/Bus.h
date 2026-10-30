#pragma once
#include "PassengerVehicle.h"

#define BUS_TABLE_FORMAT "{:<7.7}  "

class Bus : virtual public PassengerVehicle
{
private:
    int route = 0;                                                                                  // Номер маршрута

public:
    Bus() : Bus(String("Без марки"), 2020, 1, 1) {}
    Bus(const String& brand, int year, int seats, int route)
        : PassengerVehicle(brand, year, seats), route(route)
    {
        std::cout << "+ Bus [" << this->get_brand() << "]" << '\n';
    }

    Bus(const Bus& other) : Bus(other.get_brand(), other.get_year(), other.get_seats(), other.get_route()) {}

    ~Bus() override
    {
        std::cout << "- Bus [" << this->get_brand() << "]" << '\n';
    }

    int get_route() const;                                                                          // Получение номера маршрута
    void set_route(int value);                                                                      // Изменение номера маршрута

    void change_field(VehicleField field) override;                                                 // Изменение выбранного поля
    Bus& print_read_info(std::istream& stream) override;                                            // Ввод объекта с подсказкой
    void print_header(std::ostream& stream) const override;                                         // Вывод шапки таблицы

    friend std::istream& operator>>(std::istream& stream, Bus& object);
    friend std::ostream& operator<<(std::ostream& stream, const Bus& object);
};
