#include "DumpTruck.h"
#include "Bus.h"
#include "Trolleybus.h"
#include <typeinfo>
#include <cctype>
#include <iterator>

#define MAX_VEHICLE_LENGTH 20

int main()
{
    Vehicle* objects[MAX_VEHICLE_LENGTH] = {
        new Vehicle(String("Mercedes"), 2020),
        new Vehicle(String("Toyota"), 2021),
        new CargoVehicle(String("МАЗ"), 2021, 12.0),
        new CargoVehicle(String("КамАЗ"), 2022, 15.0),
        new DumpTruck(String("БелАЗ"), 2022, 40.0, 25.0),
        new DumpTruck(String("Caterpillar"), 2023, 50.0, 30.0),
        new PassengerVehicle(String("ВАЗ"), 2023, 18),
        new PassengerVehicle(String("Ford"), 2024, 16),
        new Bus(String("FlixBus"), 2024, 30, 15),
        new Bus(String("Неман"), 2025, 45, 7),
        new Trolleybus(String("Гомсельмаш"), 2025, 40, 80.0),
        new Trolleybus(String("Трансформер"), 2024, 35, 60.5)
    };

    std::size_t count = 0;
    while (count < MAX_VEHICLE_LENGTH && objects[count])
        count++;

    const std::type_info* class_types[] = {
        &typeid(Vehicle),
        &typeid(CargoVehicle),
        &typeid(DumpTruck),
        &typeid(PassengerVehicle),
        &typeid(Bus),
        &typeid(Trolleybus)
    };

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
        {
            // char choice = 'y';
            // std::cout << "Завершить программу? (y/n): ";
            // std::cin >> choice;
            // std::cout << '\n';
            //
            // if (std::tolower(static_cast<unsigned char>(choice)) == 'y')
            //     break;

            // continue;

            break;
        }

        if (action < 1 || action > 3)
        {
            std::cout << "Нет действия с таким номером.\n";
            continue;
        }

        std::cout << std::endl;
        std::cout << "1 - транспорт (Vehicle)\n";
        std::cout << "2 - грузовой (CargoVehicle)\n";
        std::cout << "3 - самосвал (DumpTruck)\n";
        std::cout << "4 - пассажирский (PassengerVehicle)\n";
        std::cout << "5 - автобус (Bus)\n";
        std::cout << "6 - троллейбус (Trolleybus)\n";
        std::cout << "Класс (0 - отмена): ";

        int type = 0;
        std::cin >> type;
        if (type == 0)
            continue;

        if (type < 1 || static_cast<std::size_t>(type) > std::size(class_types))
        {
            std::cout << "Нет класса с таким номером.\n";
            continue;
        }

        if (action == 2)
        {
            if (count == MAX_VEHICLE_LENGTH)
            {
                std::cout << "Массив транспорта заполнен.\n";
                continue;
            }

            Vehicle* new_object = nullptr;
            switch (type)
            {
                case 1: new_object = &(new Vehicle)->print_read_info(std::cin); break;
                case 2: new_object = &(new CargoVehicle)->print_read_info(std::cin); break;
                case 3: new_object = &(new DumpTruck)->print_read_info(std::cin); break;
                case 4: new_object = &(new PassengerVehicle)->print_read_info(std::cin); break;
                case 5: new_object = &(new Bus)->print_read_info(std::cin); break;
                case 6: new_object = &(new Trolleybus)->print_read_info(std::cin); break;
                default: continue;
            }

            objects[count++] = new_object;
        }

        std::cout << std::endl;
        Vehicle::print_table(std::cout, objects, count, *class_types[type - 1]);

        if (action != 3)
            continue;

        std::cout << "Номер объекта (0 - отмена): ";
        int index = 0;
        std::cin >> index;

        if (index == 0)
            continue;

        if (index < 1 || static_cast<std::size_t>(index) > count)
        {
            std::cout << "Нет объекта с таким номером.\n";
            continue;
        }

        if (typeid(*objects[index - 1]) != *class_types[type - 1])
        {
            std::cout << "Объект не относится к выбранному классу.\n";
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
            continue;

        objects[index - 1]->change_field(static_cast<VehicleField>(field_number));
        Vehicle::print_table(std::cout, objects, count, *class_types[type - 1]);
    }

    for (std::size_t i = count; i > 0; i--)
        delete objects[i - 1];

    return 0;
}

/*
*/
