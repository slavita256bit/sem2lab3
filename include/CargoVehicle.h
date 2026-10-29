#pragma once
#include "Vehicle.h"

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

    ~CargoVehicle() override
    {
        std::cout << "- CargoVehicle [" << this->get_brand() << "]" << '\n';
    }

    double get_payload() const;                                                        // Получение грузоподъёмности
    void set_payload(double value);                                                    // Изменение грузоподъёмности

    void change_field(int field) override;                                             // Изменение выбранного поля
    void read(std::istream& stream) override;                                          // Ввод полей
    void write(std::ostream& stream) const override;                                   // Вывод строки таблицы

    friend std::istream& operator>>(std::istream& stream, CargoVehicle& object);       // Ввод объекта
    friend std::ostream& operator<<(std::ostream& stream, const CargoVehicle& object); // Вывод объекта
};
