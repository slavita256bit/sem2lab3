#pragma once
#include "String.h"
#include <iosfwd>

#define MIN_YEAR 1886
#define CURRENT_YEAR 2027

namespace input
{
    void check_brand(const String& brand);
    void check_int(int value, int min, int max, const String& field);
    void check_positive(double value, const String& field);
    String read_brand(std::istream& stream);
    int read_int(std::istream& stream, int min, int max, const String& field);
    int read_index(std::istream& stream, int count, const String& field);
    double read_positive(std::istream& stream, const String& field);
    static bool is_english(const String& text);
}
