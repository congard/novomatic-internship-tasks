#include "provider/DemoTicketProvider.h"

#include <format>
#include <chrono>

namespace tmc::demo {
inline constexpr static std::vector<Ticket> tickets() {
    return {
        {
            .id = 0,
            .category = Ticket::Category::Reduced,
            .price = 3,
            .timeMinutes = 20
        },
        {
            .id = 1,
            .category = Ticket::Category::Normal,
            .price = 4,
            .timeMinutes = 20
        },
        {
            .id = 2,
            .category = Ticket::Category::Reduced,
            .price = 8,
            .timeMinutes = 90
        },
        {
            .id = 3,
            .category = Ticket::Category::Normal,
            .price = 10,
            .timeMinutes = 60
        },
        {
            .id = 4,
            .category = Ticket::Category::Normal,
            .price = 15,
            .timeMinutes = 90
        }
    };
}

DemoTicketProvider::DemoTicketProvider()
    : m_tickets(tickets()),
      m_pool()
{
    m_pool.setMaxThreadCount(1);
}

const std::vector<Ticket>& DemoTicketProvider::getTickets() const {
    return m_tickets;
}

static uint64_t timeSinceEpochMs() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void DemoTicketProvider::buyTicket(const Ticket &ticket, const TicketCallback &callback) {
    // simulate some work
    m_pool.start([=] {
        sleep(1);
        callback(IssuedTicket {
            .ticket = ticket,
            .time = timeSinceEpochMs(),
            .id = std::format("kr-{}-{}-{}", ticket.id, ticket.timeMinutes, rand() % 1000)
        });
    });
}
}