#pragma once
#include "String.h"
#include <istream>

#define MIN_YEAR 1886

namespace input
{
    int current_year();
    void check_brand(const String& brand);
    void check_int(int value, int min, int max, const char* field);
    void check_positive(double value, const char* field);
    String read_brand(std::istream& stream);
    int read_int(std::istream& stream, int min, int max, const char* field);
    double read_positive(std::istream& stream, const char* field);
}
