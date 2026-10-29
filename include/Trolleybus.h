#pragma once
#include "PassengerVehicle.h"

class Trolleybus : virtual public PassengerVehicle
{
private:
    int voltage = 0;

public:
    Trolleybus() : Trolleybus(String("Без марки"), 2020, 1, 600) {}
    Trolleybus(const String& brand, int year, int seats, int voltage) : PassengerVehicle(brand, year, seats), voltage(voltage)
    {
        std::cout << "+ Trolleybus [" << this->get_brand() << "]" << '\n';
    }

    ~Trolleybus() override
    {
        std::cout << "- Trolleybus [" << this->get_brand() << "]" << '\n';
    }

    int get_voltage() const;                                                          // Получение напряжения сети
    void set_voltage(int value);                                                      // Изменение напряжения сети

    void change_field(int field) override;                                            // Изменение выбранного поля
    void read(std::istream& stream) override;                                         // Ввод полей
    void write(std::ostream& stream) const override;                                  // Вывод строки таблицы

    friend std::istream& operator>>(std::istream& stream, Trolleybus& object);        // Ввод объекта
    friend std::ostream& operator<<(std::ostream& stream, const Trolleybus& object);  // Вывод объекта
};
