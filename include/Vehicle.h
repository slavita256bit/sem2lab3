#pragma once
/*
Лабораторная работа 3 | Наследование | Вариант 5
Транспортное средство → грузовое → самосвал.
Транспортное средство → пассажирское → автобус, троллейбус.
Три уровня наследования. Конструкторы, деструкторы с выводом порядка вызовов,
геттеры/сеттеры всех полей, перегрузки ввода/вывода, общая таблица
с отдельной шапкой, выбор изменяемого параметра. Все методы вызываются.
*/
#include "String.h"
#include <vector>

#define VEHICLE_TABLE_FORMAT "{:<13.13}  {:<18.18}  {:<4}  {:<8.8}  {:<10.10}  {:<5}  {:<7.7}  {:<8.8}  "
#define VEHICLE_TABLE_WIDTH 89

class Vehicle
{
private:
    String brand;  // Марка
    int year = 0;  // Год выпуска

public:
    Vehicle() : Vehicle(String("Без марки"), 2020) {}
    Vehicle(const String& brand, int year) : brand(brand), year(year)
    {
        std::cout << "+ Vehicle [" << this->get_brand() << "]" << '\n';
    }

    virtual ~Vehicle()
    {
        std::cout << "- Vehicle [" << this->get_brand() << "]" << '\n';
    }

    const String& get_brand() const;                                                     // Получение марки
    void set_brand(const String& value);                                                 // Изменение марки

    int get_year() const;                                                                // Получение года выпуска
    void set_year(int value);                                                            // Изменение года выпуска

    virtual void change_field(int field);                                                // Изменение выбранного поля
    virtual void read(std::istream& stream);                                             // Ввод полей
    virtual void write(std::ostream& stream) const;                                      // Вывод строки таблицы
    static void print_header(std::ostream& stream);                                      // Вывод шапки таблицы
    static void print_table(std::ostream& stream, const std::vector<Vehicle*>& objects); // Вывод таблицы

    friend std::istream& operator>>(std::istream& stream, Vehicle& object);              // Ввод объекта
    friend std::ostream& operator<<(std::ostream& stream, const Vehicle& object);        // Вывод объекта
};
