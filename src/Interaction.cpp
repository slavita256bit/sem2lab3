#include "Interaction.h"
#include <iostream>
#include "Vehicle.h"
#include "InputError.h"

// Выбор и ввод поля
void interaction::edit_field(Vehicle& object)
{
    std::cout << static_cast<int>(VehicleField::Brand) << " - " << BRAND_FIELD_NAME << '\n';
    std::cout << static_cast<int>(VehicleField::Year) << " - " << YEAR_FIELD_NAME << '\n';
    std::cout << static_cast<int>(VehicleField::Payload) << " - " << PAYLOAD_FIELD_NAME << '\n';
    std::cout << static_cast<int>(VehicleField::BodyVolume) << " - " << BODY_VOLUME_FIELD_NAME << '\n';
    std::cout << static_cast<int>(VehicleField::Seats) << " - " << SEATS_FIELD_NAME << '\n';
    std::cout << static_cast<int>(VehicleField::Route) << " - " << ROUTE_FIELD_NAME << '\n';
    std::cout << static_cast<int>(VehicleField::BatteryCapacity) << " - " << BATTERY_CAPACITY_FIELD_NAME << '\n';
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
