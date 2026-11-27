#pragma once
#include "Vehicle.h"
#include "Input.h"
#include "InputError.h"
#include "ContainerError.h"

// Выполнение действия меню
template<typename T>
void Interaction<T>::run(int action)
{
    if (action == 1)
    {
        this->print_table();
        return;
    }

    if (action == 2)
        this->add_object();
    else
    {
        this->print_table();
        int count = this->tree.size();
        if (count == 0)
            return;

        std::cout << "Номер объекта ";
        int number = input::read_int(std::cin, 0, count - 1, "номер объекта");
        if (action == 3)
            this->edit_object(number);
        else
            this->remove_object(number);
    }

    std::cout << '\n';
    this->print_table();
}

// Вывод таблицы
template<typename T>
void Interaction<T>::print_table() const
{
    this->tree.print_header(std::cout);
    std::cout << this->tree;
}

// Ввод и добавление объекта
template<typename T>
void Interaction<T>::add_object()
{
    T* object = new T;
    try
    {
        object->print_read_info(std::cin);
        this->tree.add(object);
    }
    catch (...)
    {
        delete object;
        throw;
    }
}

// Изменение объекта
template<typename T>
void Interaction<T>::edit_object(int number)
{
    T* object = new T(this->tree[number]);
    BinaryTree<T>* original = nullptr;
    try
    {
        original = &this->find_object(*object, number);
        edit_field(*object);
        this->tree.add(object);
    }
    catch (...)
    {
        delete object;
        throw;
    }

    original->remove();
}

// Удаление объекта
template<typename T>
void Interaction<T>::remove_object(int number)
{
    T object = this->tree[number];
    this->find_object(object, number).remove();
}

// Поиск узла выбранного объекта
template<typename T>
BinaryTree<T>& Interaction<T>::find_object(const T& object, int number)
{
    auto* node = this->tree.find(object);
    if (!node)
        throw ContainerError(ErrorCode::ObjectNotFound, "Объект не найден", number);

    return *node;
}

// Выбор и ввод поля
template<typename T>
void Interaction<T>::edit_field(T& object)
{
    std::cout << static_cast<int>(VehicleField::Brand) << " - марка\n";
    std::cout << static_cast<int>(VehicleField::Year) << " - год\n";
    std::cout << static_cast<int>(VehicleField::Payload) << " - грузоподъёмность\n";
    std::cout << static_cast<int>(VehicleField::BodyVolume) << " - объём кузова\n";
    std::cout << static_cast<int>(VehicleField::Seats) << " - число мест\n";
    std::cout << static_cast<int>(VehicleField::Route) << " - маршрут\n";
    std::cout << static_cast<int>(VehicleField::BatteryCapacity) << " - " << BATTERY_CAPACITY_FIELD << '\n';
    while (true)
    {
        std::cout << "Параметр ";
        int field = input::read_int(std::cin, static_cast<int>(VehicleField::Brand), static_cast<int>(VehicleField::BatteryCapacity), "параметр");
        try
        {
            object.change_field(static_cast<VehicleField>(field));
            return;
        }
        catch (const InputError& error)
        {
            if (error.get_code() != static_cast<int>(ErrorCode::InvalidField))
                throw;
            std::cout << "Ошибка " << error.get_code() << ": " << error.get_message() << ".\n";
        }
    }
}
