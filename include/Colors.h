#pragma once
#include <iostream>
#include <ostream>

class Colored : public std::ostream
{
public:
    explicit Colored(std::streambuf* sb) : std::ostream(sb) {}

    template<typename T>
    Colored(std::streambuf* sb, const char* color, const T& value) : Colored(sb)
    {
        *this << color << value;
    }

    ~Colored() override
    {
        *this << "\033[0m";
        this->flush();
    }
};

namespace colored
{
    class Color
    {
    private:
        const char* code;

    public:
        constexpr explicit Color(const char* code) : code(code) {}

        template<typename T>
        Colored operator<<(const T& value) const
        {
            return {std::cout.rdbuf(), this->code, value};
        }

        Colored operator<<(std::ostream& (*manipulator)(std::ostream&)) const
        {
            return {std::cout.rdbuf(), this->code, manipulator};
        }
    };

    inline constexpr Color black("\033[30m");
    inline constexpr Color red("\033[31m");
    inline constexpr Color green("\033[32m");
    inline constexpr Color yellow("\033[33m");
    inline constexpr Color blue("\033[34m");
    inline constexpr Color magenta("\033[35m");
    inline constexpr Color cyan("\033[36m");
    inline constexpr Color white("\033[37m");
}
