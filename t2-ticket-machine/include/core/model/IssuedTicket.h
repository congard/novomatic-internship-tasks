#ifndef T2_TICKET_MACHINE_ISSUEDTICKET_H
#define T2_TICKET_MACHINE_ISSUEDTICKET_H

#include "Ticket.h"

namespace tmc {
struct IssuedTicket {
    Ticket ticket;
    size_t time;
    std::string id;
};
}

#endif //T2_TICKET_MACHINE_ISSUEDTICKET_H
