#pragma once
/*
Лабораторная работа 3 | Наследование | Вариант 5
Транспортное средство -> грузовое -> самосвал.
Транспортное средство -> пассажирское -> автобус, троллейбус.
Три уровня наследования. Конструкторы, деструкторы с выводом порядка вызовов,
геттеры/сеттеры всех полей, перегрузки ввода/вывода, отдельные таблицы классов
с отдельной шапкой, выбор изменяемого параметра. Все методы вызываются.
*/
#include "String.h"
#include <format>

#define VEHICLE_TABLE_FORMAT "{:<18.18}  {:<4}  "

enum class VehicleField
{
    Brand = 1,                        // Марка
    Year,                             // Год выпуска
    Payload,                          // Грузоподъёмность
    BodyVolume,                       // Объём кузова
    Seats,                            // Количество мест
    Route,                            // Номер маршрута
    BatteryCapacity                   // Ёмкость аккумулятора
};

class Vehicle
{
private:
    String brand;   // Марка
    int year = 0;   // Год выпуска

public:
    Vehicle() : Vehicle(String("Без марки"), 2020) {}
    Vehicle(const String& brand, int year) : brand(brand), year(year)
    {
        std::cout << "+ Vehicle [" << this->get_brand() << "]" << '\n';
    }

    Vehicle(const Vehicle& other) : Vehicle(other.get_brand(), other.get_year()) {}

    virtual ~Vehicle()
    {
        std::cout << "- Vehicle [" << this->get_brand() << "]" << '\n';
    }

    const String& get_brand() const;                                                                // Получение марки
    void set_brand(const String& value);                                                            // Изменение марки

    int get_year() const;                                                                           // Получение года выпуска
    void set_year(int value);                                                                       // Изменение года выпуска

    virtual void change_field(VehicleField field);                                                  // Изменение выбранного поля
    virtual Vehicle& print_read_info(std::istream& stream) = 0;                                     // Ввод объекта с подсказкой
    virtual void print_header(std::ostream& stream) const;                                          // Вывод шапки таблицы

    bool operator<(const Vehicle& other) const;                                                     // Сравнение года выпуска
    bool operator>(const Vehicle& other) const;                                                     // Сравнение года выпуска
    bool operator<=(const Vehicle& other) const;                                                    // Сравнение года выпуска
    bool operator>=(const Vehicle& other) const;                                                    // Сравнение года выпуска
    bool operator==(const Vehicle& other) const;                                                    // Равенство всех полей
    bool operator!=(const Vehicle& other) const;                                                    // Неравенство полей

    friend std::istream& operator>>(std::istream& stream, Vehicle& object);
    friend std::ostream& operator<<(std::ostream& stream, const Vehicle& object);
};
