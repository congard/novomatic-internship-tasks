#ifndef T2_TICKET_MACHINE_HARDWAREERROR_H
#define T2_TICKET_MACHINE_HARDWAREERROR_H

#include <string>

namespace tmc {
struct HardwareError {
    int id;
    int deviceId;
    std::string description;
    void *data;
};
}

#endif //T2_TICKET_MACHINE_HARDWAREERROR_H
