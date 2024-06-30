#include "hardware/DemoTicketPrinter.h"

namespace tmc::demo {
DemoTicketPrinter::DemoTicketPrinter()
    : m_pool()
{
    m_pool.setMaxThreadCount(1);
}

void DemoTicketPrinter::print(const IssuedTicket &ticket, const Callback &callback) {
    // simulate some work
    m_pool.start([=] {
        sleep(1);
        callback(ticket);
    });
}
}