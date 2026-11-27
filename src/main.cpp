#include "DumpTruck.h"
#include "Bus.h"
#include "Trolleybus.h"
#include "Interaction.h"
#include "InputError.h"
#include "ContainerError.h"
#include <sstream>

#define ADD_DEFAULTS
// #define DEMONSTRATE_ERRORS

int main()
{
#ifdef DEMONSTRATE_ERRORS
    // Ошибка 8: сбой входного потока
    try
    {
        std::istringstream broken;
        broken.setstate(std::ios::badbit);
        input::read_int(broken, 1, 10, "число");
    }
    catch (const InputError& error)
    {
        std::cout << "Ошибка " << error.get_code() << ": " << error.get_message() << ".\n";
    }

    BinaryTree<Bus> tree;

    // Ошибка 202: добавление пустого указателя
    try
    {
        tree.add(nullptr);
    }
    catch (const ContainerError& error)
    {
        std::cout << "Ошибка " << error.get_code() << ": " << error.get_message() << ".\n";
    }

    // Ошибка 203: нужного для операции объекта нет в дереве
    try
    {
        Bus bus("Test", 2027, 25, 1);
        tree.find(bus);
    }
    catch (const ContainerError& error)
    {
        std::cout << "Ошибка " << error.get_code() << ": " << error.get_message() << ".\n";
    }
#else
    BinaryTree<DumpTruck> dump_trucks;
    BinaryTree<Bus> buses;
    BinaryTree<Trolleybus> trolleybuses;

    try
    {
#ifdef ADD_DEFAULTS
        dump_trucks.add(DumpTruck("BelAZ", 2022, 40.0, 25.0));
        dump_trucks.add(DumpTruck("Caterpillar", 2023, 50.0, 30.0));
        buses.add(Bus("FlixBus", 2024, 30, 15));
        buses.add(Bus("Neman", 2025, 45, 7));
        trolleybuses.add(Trolleybus("Gomselmash", 2025, 40, 80.0));
        trolleybuses.add(Trolleybus("Transformer", 2024, 35, 60.5));
#endif

        while (true)
        {
            std::cout << '\n';
            std::cout << "1 - выбрать таблицу класса\n";
            std::cout << "2 - добавить объект\n";
            std::cout << "3 - изменить объект\n";
            std::cout << "4 - удалить объект\n";
            std::cout << "0 - завершить программу\n";
            std::cout << "Действие ";
            int action = input::read_int(std::cin, 0, 4, "действие");
            if (action == 0)
                break;

            std::cout << '\n';
            std::cout << "1 - самосвал (DumpTruck)\n";
            std::cout << "2 - автобус (Bus)\n";
            std::cout << "3 - троллейбус (Trolleybus)\n";
            std::cout << "Класс ";
            int type = input::read_int(std::cin, 1, 3, "класс");

            try
            {
                switch (type)
                {
                case 1: Interaction(dump_trucks).run(action); break;
                case 2: Interaction(buses).run(action); break;
                case 3: Interaction(trolleybuses).run(action); break;
                default: throw InputError(ErrorCode::ValueOutOfRange, "Неизвестный класс транспорта", "класс");
                }
            }
            catch (const ContainerError& error)
            {
                std::cout << "Ошибка " << error.get_code() << ": " << error.get_message();
                if (error.get_code() != static_cast<int>(ErrorCode::ObjectNotFound))
                    std::cout << " (" << error.get_number() << ")";
                std::cout << ".\n";
            }
        }
    }
    catch (const InputError& error)
    {
        std::cout << "Ошибка " << error.get_code() << " (" << error.get_field() << "): " << error.get_message() << ".\n";
        if (error.get_code() != static_cast<int>(ErrorCode::EndOfInput))
            return 1;
    }
    catch (const Error& error)
    {
        std::cout << "Ошибка " << error.get_code() << ": " << error.get_message() << ".\n";
        return 1;
    }
    catch (const std::bad_alloc&)
    {
        std::cout << "Недостаточно памяти.\n";
        return 1;
    }

#endif

    return 0;
}

/*
1
1
2
2
NewBus
2020
30
10
3
2
0
2
2019
4
2
0
1
1
1
2
1
3
0
*/
