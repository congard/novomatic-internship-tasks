#ifndef T2_TICKET_MACHINE_HARDWARERESULT_H
#define T2_TICKET_MACHINE_HARDWARERESULT_H

#include <variant>

#include "HardwareError.h"

namespace tmc {
template<typename T>
using HardwareResult = std::variant<T, HardwareError>;
}

#endif //T2_TICKET_MACHINE_HARDWARERESULT_H
