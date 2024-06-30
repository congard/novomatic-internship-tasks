#ifndef TMC_DEMO_DEMOTICKETPROVIDER_H
#define TMC_DEMO_DEMOTICKETPROVIDER_H

#include <tulz/threading/ThreadPool.h>

#include "provider/TicketProvider.h"

namespace tmc::demo {
class DemoTicketProvider : public TicketProvider {
public:
    DemoTicketProvider();

    const std::vector<Ticket>& getTickets() const override;
    void buyTicket(const Ticket &ticket, const TicketCallback &callback) override;

private:
    std::vector<Ticket> m_tickets;
    tulz::ThreadPool m_pool;
};
}

#endif //TMC_DEMO_DEMOTICKETPROVIDER_H
