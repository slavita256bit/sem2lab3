#pragma once
#include "Error.h"

class ErrorFile : public Error
{
public:
    using Error::Error;

    // ErrorFile(ErrorCode code, const char* message) : Error(code, message) {}
};
