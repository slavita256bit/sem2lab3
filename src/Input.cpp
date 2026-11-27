#include "Input.h"
#include "InputError.h"
#include <algorithm>
#include <charconv>
#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>

namespace input
{
    // Чтение одной строки с ограничением длины
    static int read_line(std::istream& stream, char (&line)[MAX_LENGTH + 1], const char* field)
    {
        stream.getline(line, sizeof(line));
        if (stream)
            return static_cast<int>(stream.gcount()) - (stream.eof() ? 0 : 1);

        if (stream.bad())
            throw InputError(ErrorCode::StreamFailure, "Ошибка потока ввода", field);
        if (stream.eof())
            throw InputError(ErrorCode::EndOfInput, "Конец ввода", field);
        if (stream.gcount() != MAX_LENGTH)
            throw InputError(ErrorCode::StreamFailure, "Ошибка потока ввода", field);

        stream.clear();
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (stream.bad())
            throw InputError(ErrorCode::StreamFailure, "Ошибка потока ввода", field);
        throw InputError(ErrorCode::TextTooLong, "Строка длиннее 80 байт", field);
    }

    // Вывод ошибки, если ввод можно повторить
    static void retry_input(const InputError& error)
    {
        int code = error.get_code();
        if (code == static_cast<int>(ErrorCode::EndOfInput) || code == static_cast<int>(ErrorCode::StreamFailure))
            throw;

        std::cout << "Ошибка " << code << " (" << error.get_field() << "): " << error.get_message() << ". Повторите ввод: ";
    }

    // Проверка результата преобразования числа
    static void check_conversion(const std::from_chars_result& result, const char* end, const char* field)
    {
        if (result.ec == std::errc::invalid_argument)
            throw InputError(ErrorCode::InvalidNumber, "Введите число", field);
        if (result.ec == std::errc::result_out_of_range)
            throw InputError(ErrorCode::NumberOverflow, "Число слишком велико", field);
        if (result.ptr != end)
            throw InputError(ErrorCode::TrailingCharacters, "Лишние символы после числа", field);
    }

    // Получение текущего года
    int current_year()
    {
        auto today = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
        return static_cast<int>(std::chrono::year_month_day(today).year());
    }

    // Проверка диапазонов русских букв в UTF-8
    static bool is_russian_letter(char first, char second)
    {
        auto lead = static_cast<char8_t>(first);
        auto tail = static_cast<char8_t>(second);
        if (lead == u8"А"[0])
            return (tail >= u8"А"[1] && tail <= u8"п"[1]) || tail == u8"Ё"[1];

        return lead == u8"р"[0] && ((tail >= u8"р"[1] && tail <= u8"я"[1]) || tail == u8"ё"[1]);
    }

    // Проверка марки
    void check_brand(const String& brand)
    {
        int length = brand.get_length();
        if (length > MAX_LENGTH)
            throw InputError(ErrorCode::TextTooLong, "Марка длиннее 80 байт", "марка");

        bool latin = false;
        bool russian = false;
        for (int i = 0; i < length; i++)
        {
            char c = brand[i];
            if ((c >= '0' && c <= '9') || c == '-')
                continue;

            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                latin = true;
            else if (i + 1 < length && is_russian_letter(c, brand[i + 1]))
            {
                russian = true;
                i++;
            }
            else
                throw InputError(ErrorCode::InvalidBrand, "Недопустимый символ в марке", "марка");
        }

        if (latin == russian)
            throw InputError(ErrorCode::InvalidBrand, "Нужны буквы одного алфавита", "марка");
    }

    // Проверка диапазона целого числа
    void check_int(int value, int min, int max, const char* field)
    {
        if (value < min || value > max)
            throw InputError(ErrorCode::ValueOutOfRange, "Значение вне диапазона", field);
    }

    // Проверка положительного числа
    void check_positive(double value, const char* field)
    {
        if (!std::isfinite(value) || value <= 0)
            throw InputError(ErrorCode::ValueOutOfRange, "Нужно положительное конечное число", field);
    }

    // Ввод марки с повтором
    String read_brand(std::istream& stream)
    {
        while (true)
        {
            try
            {
                char line[MAX_LENGTH + 1]{};
                int length = read_line(stream, line, "марка");
                if (std::find(line, line + length, '\0') != line + length)
                    throw InputError(ErrorCode::InvalidBrand, "Недопустимый символ в марке", "марка");
                String brand(line);
                check_brand(brand);
                return brand;
            }
            catch (const InputError& error)
            {
                retry_input(error);
            }
        }
    }

    // Ввод целого числа с повтором
    int read_int(std::istream& stream, int min, int max, const char* field)
    {
        while (true)
        {
            try
            {
                char line[MAX_LENGTH + 1]{};
                const char* end = line + read_line(stream, line, field);
                int value = 0;
                auto result = std::from_chars(line, end, value);
                check_conversion(result, end, field);
                check_int(value, min, max, field);
                return value;
            }
            catch (const InputError& error)
            {
                retry_input(error);
            }
        }
    }

    // Ввод положительного числа с повтором
    double read_positive(std::istream& stream, const char* field)
    {
        while (true)
        {
            try
            {
                char line[MAX_LENGTH + 1]{};
                const char* end = line + read_line(stream, line, field);
                double value = 0;
                auto result = std::from_chars(line, end, value);
                check_conversion(result, end, field);
                check_positive(value, field);
                return value;
            }
            catch (const InputError& error)
            {
                retry_input(error);
            }
        }
    }
}
