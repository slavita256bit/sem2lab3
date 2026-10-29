#include "DumpTruck.h"
#include "Bus.h"
#include "Trolleybus.h"
#include <typeinfo>
#include <cctype>
#include <vector>

int main()
{
    Vehicle vehicle(String("Mercedes"), 2020);
    CargoVehicle cargo(String("МАЗ"), 2021, 12.0);
    DumpTruck dump(String("БелАЗ"), 2022, 40.0, 25.0);
    PassengerVehicle passenger(String("ВАЗ"), 2023, 18);
    Bus bus(String("FlixBus"), 2024, 30, 15);
    Trolleybus trolleybus(String("Белкоммунмаш"), 2025, 40, 600);

    /*
    Vehicle vehicle;             // Транспорт
    CargoVehicle cargo;          // Грузовой
    DumpTruck dump;              // Самосвал
    PassengerVehicle passenger;  // Пассажирский
    Bus bus;                     // Автобус
    Trolleybus trolleybus;       // Троллейбус

    std::cout << "Транспорт (марка, год выпуска): ";
    std::cin >> vehicle;
    std::cout << "Грузовой (марка, год, грузоподъёмность (т)): ";
    std::cin >> cargo;
    std::cout << "Самосвал (марка, год, грузоподъёмность (т), объём кузова (м3)): ";
    std::cin >> dump;
    std::cout << "Пассажирский (марка, год, количество мест): ";
    std::cin >> passenger;
    std::cout << "Автобус (марка, год, количество мест, номер маршрута): ";
    std::cin >> bus;
    std::cout << "Троллейбус (марка, год, количество мест, напряжение сети (В)): ";
    std::cin >> trolleybus;
    */

    while (true)
    {
        std::vector<Vehicle*> objects = {&vehicle, &cargo, &dump, &passenger, &bus, &trolleybus};

        auto& base = static_cast<Vehicle&>(dump);
        std::cout << std::endl;
        std::cout << "typeid после static_cast к Vehicle: " << typeid(base).name() << '\n';
        std::cout << "dynamic_cast автобуса к грузовому: " << (dynamic_cast<CargoVehicle*>(objects[4]) ? "good" : "nullptr") << '\n';
        std::cout << "dynamic_cast автобуса к грузовому: " << typeid(dynamic_cast<PassengerVehicle*>(objects[4])).name() << '\n';
        std::cout << std::endl << std::endl;

        Vehicle::print_table(std::cout, objects);

        while (true)
        {
            std::cout << "Номер объекта (1–" << objects.size() << ", 0—отмена): ";
            int index = 0;
            std::cin >> index;
            if (index == 0)
                break;

            if (index < 1 || static_cast<std::size_t>(index) > objects.size())
            {
                std::cout << "Нет объекта с таким номером.\n";
                continue;
            }

            std::cout << "1 — марка\n";
            std::cout << "2 — год\n";
            std::cout << "3 — грузоподъёмность\n";
            std::cout << "4 — объём кузова\n";
            std::cout << "5 — число мест\n";
            std::cout << "6 — маршрут\n";
            std::cout << "7 — напряжение сети\n";
            std::cout << "Параметр: ";

            int field = 0;
            std::cin >> field;
            objects[index - 1]->change_field(field);
            Vehicle::print_table(std::cout, objects);
        }

        char choice = 'y';
        std::cout << "\nЗавершить программу? (y/n): ";
        std::cin >> choice;
        std::cout << '\n';

        if (std::tolower(choice) == 'y')
            break;
    }

    return 0;
}

/*
3 4 32.5
5 6 42
0
y
*/
