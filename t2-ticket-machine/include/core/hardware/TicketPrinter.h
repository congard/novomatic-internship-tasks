#ifndef T2_TICKET_MACHINE_TICKETPRINTER_H
#define T2_TICKET_MACHINE_TICKETPRINTER_H

#include <functional>
#include <variant>

#include "model/IssuedTicket.h"
#include "HardwareInterface.h"
#include "HardwareResult.h"

namespace tmc {
class TicketPrinter : public HardwareInterface {
public:
    using Result = HardwareResult<IssuedTicket>;
    using Callback = std::function<void(Result)>;

public:
    virtual void print(const IssuedTicket &ticket, const Callback &callback) = 0;
};
} // tmc

#endif //T2_TICKET_MACHINE_TICKETPRINTER_H
