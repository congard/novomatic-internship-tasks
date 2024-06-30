#ifndef T2_TICKET_MACHINE_TICKETPROVIDER_H
#define T2_TICKET_MACHINE_TICKETPROVIDER_H

#include <vector>
#include <variant>
#include <functional>

#include "model/Ticket.h"
#include "model/IssuedTicket.h"

namespace tmc {
class TicketProvider {
public:
    using ErrorDescription = std::string;
    using Result = std::variant<IssuedTicket, ErrorDescription>;
    using TicketCallback = std::function<void(Result)>;

public:
    virtual ~TicketProvider() = default;

    /**
     * @note Most likely (ideally) this function should return some kind of Future
     * (not necessary std::future, something more flexible and callback-based), but
     * most likely it will be an overkill for this task.
     * @return The tickets list
     */
    virtual const std::vector<Ticket>& getTickets() const = 0;

    virtual void buyTicket(const Ticket &ticket, const TicketCallback &callback) = 0;
};
}

#endif //T2_TICKET_MACHINE_TICKETPROVIDER_H
