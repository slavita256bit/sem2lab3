#include "Input.h"
#include "InputError.h"
#include "Vehicle.h"
#include <charconv>
#include <cctype>
#include <cmath>
#include <iostream>
#include <limits>

namespace input
{
    static bool is_english(const String& text);

    // Чтение одной строки с ограничением длины
    static String read_line(std::istream& stream, const String& field)
    {
        String line(MAX_LENGTH);
        stream.getline(line.begin(), line.get_length() + 1);
        if (stream)
        {
            int length = static_cast<int>(stream.gcount()) - (stream.eof() ? 0 : 1);
            return line(0, length);
        }

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
        throw InputError(ErrorCode::TextTooLong, "Строка длиннее 80 символов", field);
    }

    // Вывод ошибки, если ввод можно повторить
    static void retry_input(const InputError& error)
    {
        int code = error.get_code();
        if (code == static_cast<int>(ErrorCode::EndOfInput) || code == static_cast<int>(ErrorCode::StreamFailure))
            throw;

        std::cerr << "Ошибка " << code << " (" << error.get_field() << "): " << error.get_message() << ".\n";
        std::cout << "Повторите ввод ";
    }

    // Проверка марки
    void check_brand(const String& brand)
    {
        if (brand.get_length() > MAX_LENGTH)
            throw InputError(ErrorCode::TextTooLong, "Марка длиннее 80 символов", BRAND_FIELD_NAME);

        if (!is_english(brand))
            throw InputError(ErrorCode::InvalidBrand, "Нужна марка с латинскими буквами", BRAND_FIELD_NAME);
    }

    // Проверка диапазона целого числа
    void check_int(int value, int min, int max, const String& field)
    {
        if (value < min || value > max)
            throw InputError(ErrorCode::ValueOutOfRange, "Значение вне диапазона", field);
    }

    // Проверка положительного числа
    void check_positive(double value, const String& field)
    {
        if (!std::isfinite(value) || value <= 0)
            throw InputError(ErrorCode::ValueOutOfRange, "Нужно положительное конечное число", field);
    }

    // Ввод марки с повтором
    String read_brand(std::istream& stream)
    {
        while (true)
        {
            std::cout << "(1–" << MAX_LENGTH << " символов, латинские буквы, можно цифры и дефис): ";
            try
            {
                String brand = read_line(stream, BRAND_FIELD_NAME);
                check_brand(brand);
                return brand;
            }
            catch (const InputError& error)
            {
                retry_input(error);
            }
        }
    }

    // Преобразование всей строки в число
    template<typename T>
    static T parse_number(const String& line, const String& field)
    {
        T value = 0;
        auto result = std::from_chars(line.begin(), line.end(), value);
        if (result.ec == std::errc::invalid_argument)
            throw InputError(ErrorCode::InvalidNumber, "Введите число", field);
        if (result.ec == std::errc::result_out_of_range)
            throw InputError(ErrorCode::NumberOverflow, "Число слишком велико", field);
        if (result.ptr != line.end())
            throw InputError(ErrorCode::TrailingCharacters, "Лишние символы после числа", field);

        return value;
    }

    // Ввод целого числа с повтором
    int read_int(std::istream& stream, int min, int max, const String& field)
    {
        while (true)
        {
            std::cout << "(целое число, " << min << ".." << max << "): ";
            try
            {
                int value = parse_number<int>(read_line(stream, field), field);
                check_int(value, min, max, field);
                return value;
            }
            catch (const InputError& error)
            {
                retry_input(error);
            }
        }
    }

    // Ввод индекса с проверкой формата
    int read_index(std::istream& stream, int count, const String& field)
    {
        while (true)
        {
            std::cout << "(целое число, 0.." << count - 1 << "): ";
            try
            {
                return parse_number<int>(read_line(stream, field), field);
            }
            catch (const InputError& error)
            {
                retry_input(error);
            }
        }
    }

    // Ввод положительного числа с повтором
    double read_positive(std::istream& stream, const String& field)
    {
        while (true)
        {
            std::cout << "(конечное число больше 0, десятичная точка): ";
            try
            {
                auto value = parse_number<double>(read_line(stream, field), field);
                check_positive(value, field);
                return value;
            }
            catch (const InputError& error)
            {
                retry_input(error);
            }
        }
    }

    // Проверка марки с латинскими буквами
    static bool is_english(const String& text)
    {
        bool has_letter = false;
        for (char ch : text)
        {
            if (std::isdigit(static_cast<unsigned char>(ch)) || ch == '-')
                continue;

            if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')))
                return false;

            has_letter = true;
        }

        return has_letter;
    }

    /*
    // Проверка марки с латинскими буквами
    static bool is_english(const String& text, bool allow_uppercase = true, bool allow_lowercase = true)
    {
        bool has_letter = false;
        for (int i = 0; i < text.get_length(); i++)
        {
            char ch = text[i];
            if (std::isdigit(static_cast<unsigned char>(ch)) || ch == '-')
                continue;

            if (!((allow_uppercase && ch >= 'A' && ch <= 'Z') || (allow_lowercase && ch >= 'a' && ch <= 'z')))
                return false;

            has_letter = true;
        }

        return has_letter;
    }
    */
}
