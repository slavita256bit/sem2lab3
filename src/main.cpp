#include "DumpTruck.h"
#include "Bus.h"
#include "Trolleybus.h"
#include "BinaryTree.h"
#include <stdexcept>

#define ADD_DEFAULTS

int main()
{
    BinaryTree<DumpTruck> dump_trucks;
    BinaryTree<Bus> buses;
    BinaryTree<Trolleybus> trolleybuses;

#ifdef ADD_DEFAULTS
    dump_trucks.add(new DumpTruck(String("БелАЗ"), 2022, 40.0, 25.0));
    dump_trucks.add(new DumpTruck(String("Caterpillar"), 2023, 50.0, 30.0));
    buses.add(new Bus(String("FlixBus"), 2024, 30, 15));
    buses.add(new Bus(String("Неман"), 2025, 45, 7));
    trolleybuses.add(new Trolleybus(String("Гомсельмаш"), 2025, 40, 80.0));
    trolleybuses.add(new Trolleybus(String("Трансформер"), 2024, 35, 60.5));
#endif

    while (true)
    {
        std::cout << std::endl;
        std::cout << "1 - выбрать таблицу класса\n";
        std::cout << "2 - добавить объект\n";
        std::cout << "3 - изменить объект\n";
        std::cout << "0 - завершить программу\n";
        std::cout << "Действие: ";
        int action = 0;
        std::cin >> action;

        if (action == 0)
            break;

        if (action < 1 || action > 3)
        {
            std::cout << "Нет действия с таким номером.\n";
            continue;
        }

        std::cout << std::endl;
        std::cout << "1 - самосвал (DumpTruck)\n";
        std::cout << "2 - автобус (Bus)\n";
        std::cout << "3 - троллейбус (Trolleybus)\n";
        std::cout << "Класс (0 - отмена): ";

        int type = 0;
        std::cin >> type;
        if (type == 0)
            continue;

        if (type < 1 || type > 3)
        {
            std::cout << "Нет класса с таким номером.\n";
            continue;
        }

        Vehicle* object = nullptr;
        if (action == 2)
        {
            switch (type)
            {
            case 1: object = new DumpTruck; break;
            case 2: object = new Bus; break;
            case 3: object = new Trolleybus; break;
            default: continue;
            }

            object->print_read_info(std::cin);
        }
        else if (action == 3)
        {
            switch (type)
            {
            case 1: std::cout << dump_trucks; break;
            case 2: std::cout << buses; break;
            case 3: std::cout << trolleybuses; break;
            default: continue;
            }

            std::cout << "Номер объекта (0 - отмена): ";
            int number = 0;
            std::cin >> number;
            if (number == 0)
                continue;

            try
            {
                switch (type)
                {
                case 1: object = new DumpTruck(dump_trucks[number]); break;
                case 2: object = new Bus(buses[number]); break;
                case 3: object = new Trolleybus(trolleybuses[number]); break;
                default: continue;
                }
            }
            catch (const std::out_of_range&)
            {
                std::cout << "Нет объекта с таким номером.\n";
                continue;
            }

            std::cout << static_cast<int>(VehicleField::Brand) << " - марка\n";
            std::cout << static_cast<int>(VehicleField::Year) << " - год\n";
            std::cout << static_cast<int>(VehicleField::Payload) << " - грузоподъёмность\n";
            std::cout << static_cast<int>(VehicleField::BodyVolume) << " - объём кузова\n";
            std::cout << static_cast<int>(VehicleField::Seats) << " - число мест\n";
            std::cout << static_cast<int>(VehicleField::Route) << " - маршрут\n";
            std::cout << static_cast<int>(VehicleField::BatteryCapacity) << " - ёмкость аккумулятора\n";
            std::cout << "Параметр (0 - отмена): ";

            int field_number = 0;
            std::cin >> field_number;
            if (field_number == 0)
            {
                delete object;
                continue;
            }

            switch (type)
            {
            case 1: dump_trucks.find(*dynamic_cast<DumpTruck*>(object))->remove(); break;
            case 2: buses.find(*dynamic_cast<Bus*>(object))->remove(); break;
            case 3: trolleybuses.find(*dynamic_cast<Trolleybus*>(object))->remove(); break;
            default: break;
            }

            object->change_field(static_cast<VehicleField>(field_number));
        }

        if (object)
        {
            switch (type)
            {
            case 1: dump_trucks.add(dynamic_cast<DumpTruck*>(object)); break;
            case 2: buses.add(dynamic_cast<Bus*>(object)); break;
            case 3: trolleybuses.add(dynamic_cast<Trolleybus*>(object)); break;
            default: break;
            }
        }

        std::cout << std::endl;
        switch (type)
        {
        case 1: std::cout << dump_trucks; break;
        case 2: std::cout << buses; break;
        case 3: std::cout << trolleybuses; break;
        default: break;
        }
    }

    return 0;
}

/*
1 1
2 2 NewBus 2020 30 10
3 2 1 2 2019
1 1
1 2
1 3
0
*/
